/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "SpellChecker.h"
#include "Editor.h"
#include "AppUtil.h"

namespace
{
	HRESULT CreateSpellCheckerFactory(_COM_Outptr_ ISpellCheckerFactory** spellCheckerFactory)
	{
		HRESULT hr = CoCreateInstance(__uuidof(SpellCheckerFactory), nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(spellCheckerFactory));
		if (FAILED(hr))
		{
			*spellCheckerFactory = nullptr;
		}
		return hr;
	}

	HRESULT GetEnumString(_In_ IEnumString* enumString, std::vector<std::wstring>& listAvailableLanguages)
	{
		HRESULT hr = S_OK;
		while (S_OK == hr)
		{
			LPOLESTR string = nullptr;
			hr = enumString->Next(1, &string, nullptr);

			if (S_OK == hr)
			{
				listAvailableLanguages.push_back(string);
				CoTaskMemFree(string);
			}
		}

		return (SUCCEEDED(hr) ? S_OK : hr);
	}

	HRESULT GetAvailableLanguages(_In_ ISpellCheckerFactory* spellCheckerFactory, std::vector<std::wstring>& listAvailableLanguages)
	{
		IEnumString* enumLanguages = nullptr;
		HRESULT hr = spellCheckerFactory->get_SupportedLanguages(&enumLanguages);

		if (SUCCEEDED(hr))
		{
			hr = GetEnumString(enumLanguages, listAvailableLanguages);
		}

		if (nullptr != enumLanguages)
		{
			enumLanguages->Release();
		}

		return hr;
	}
}

CSpellChecker::~CSpellChecker()
{
	Finalize();
}

BOOL CSpellChecker::Initilize(CEditorCtrl * pEditorCtrl, const std::wstring & langugueToCheck, const LangKeywordDataset & LangKeywordDataset)
{
	ASSERT(pEditorCtrl);
	if (pEditorCtrl)
	{
		m_pEditorCtrl = pEditorCtrl;
		m_LangKeywordDataset = LangKeywordDataset;
		m_strLangugueToCheck = langugueToCheck;
		HRESULT hr = CreateSpellCheckerFactory(&m_pSpellCheckerFactory);
		if (SUCCEEDED(hr))
		{
			BOOL supported = FALSE;
			hr = m_pSpellCheckerFactory->IsSupported(m_strLangugueToCheck.c_str(), &supported);
			if (supported)
			{
				hr = m_pSpellCheckerFactory->CreateSpellChecker(m_strLangugueToCheck.c_str(), &m_pSpellChecker);
			}
			if (SUCCEEDED(hr))
			{
				m_nBufLen = 1024;
				m_pBuffer = std::make_unique<char[]>(m_nBufLen);
				m_strWordChars.clear();
				for (int ch = 0; ch < 256; ++ch)
				{
					if (ch >= 0x80 || isalnum(ch) || ch == '_' || ch == '\'')
						m_strWordChars += static_cast<char>(ch);
				}
				return TRUE;
			}
			else
			{
				ASSERT(m_pSpellChecker);
			}
		}
		else
		{
			ASSERT(m_pSpellCheckerFactory);
		}
	}
	LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error] Failed initilization spell checker for languague %s..."), AppUtils::WStdToCString(m_strLangugueToCheck));
	return FALSE;
}

void CSpellChecker::Finalize()
{
	if (m_pSpellCheckerFactory)
	{
		m_pSpellCheckerFactory->Release();
		m_pSpellCheckerFactory = nullptr;
	}
	if (m_pSpellChecker)
	{
		m_pSpellChecker->Release();
		m_pSpellChecker = nullptr;
	}
}

void CSpellChecker::GetSpellCheckSupportLanguages(std::vector<std::wstring>& listAvailableLanguages)
{
	ASSERT(m_pSpellCheckerFactory);
	GetAvailableLanguages(m_pSpellCheckerFactory, listAvailableLanguages);
}

void CSpellChecker::StartSpellCheckingSession()
{
	ASSERT(m_pSpellCheckerFactory);
	ASSERT(m_pSpellChecker);
	if (m_pSpellCheckerFactory && m_pSpellChecker)
	{ 
		auto wordCharsBuffer = m_pEditorCtrl->GetWordChars();
		m_pEditorCtrl->DoCommand(SCI_SETWORDCHARS, 0, reinterpret_cast<sptr_t>(wordCharsBuffer.c_str()));
		m_pEditorCtrl->DoCommand(SCI_SETWORDCHARS, 0, reinterpret_cast<sptr_t>(m_strWordChars.c_str()));

		Sci_TextRange textRange{};
		auto          firstLine = m_pEditorCtrl->DoCommand(SCI_GETFIRSTVISIBLELINE);
		auto          lastLine = firstLine + m_pEditorCtrl->DoCommand(SCI_LINESONSCREEN);
		textRange.chrg.cpMin = static_cast<Sci_PositionCR>(m_pEditorCtrl->DoCommand(SCI_POSITIONFROMLINE, firstLine));
		textRange.chrg.cpMax = textRange.chrg.cpMin;
		auto lastPos = m_pEditorCtrl->DoCommand(SCI_POSITIONFROMLINE, lastLine) + m_pEditorCtrl->DoCommand(SCI_LINELENGTH, lastLine);
		auto textLength = m_pEditorCtrl->DoCommand(SCI_GETLENGTH);

		if (lastPos < 0)
			lastPos = textLength - textRange.chrg.cpMin;

		auto start = GetTickCount64();
		while (textRange.chrg.cpMax < lastPos)
		{
			textRange.chrg.cpMin = static_cast<Sci_PositionCR>(m_pEditorCtrl->DoCommand(SCI_WORDSTARTPOSITION, textRange.chrg.cpMax + 1, TRUE));
			if (textRange.chrg.cpMin < textRange.chrg.cpMax)
				break;
			textRange.chrg.cpMax = static_cast<Sci_PositionCR>(m_pEditorCtrl->DoCommand(SCI_WORDENDPOSITION, textRange.chrg.cpMin, TRUE));
			if (textRange.chrg.cpMin == textRange.chrg.cpMax)
			{
				textRange.chrg.cpMax++;
				// since Scintilla squiggles to the end of the text even if told to stop one char before it,
				// we have to clear here the squiggly lines to the end.
				if (textRange.chrg.cpMin)
				{
					m_pEditorCtrl->DoCommand(SCI_SETINDICATORCURRENT, INDIC_SPELL_CHECKER);
					m_pEditorCtrl->DoCommand(SCI_INDICATORCLEARRANGE, textRange.chrg.cpMin - 1, textRange.chrg.cpMax - textRange.chrg.cpMin + 1);
				}
				continue;
			}
			if (m_pEditorCtrl->DoCommand(SCI_INDICATORVALUEAT, INDIC_URL_HOTSPOT, textRange.chrg.cpMin))
				continue;

			int style = static_cast<int>(m_pEditorCtrl->DoCommand(SCI_GETSTYLEAT, textRange.chrg.cpMin));
			
			assert(textRange.chrg.cpMax >= textRange.chrg.cpMin);
			if (m_nBufLen < (textRange.chrg.cpMax - textRange.chrg.cpMin + 2))
			{
				m_nBufLen = textRange.chrg.cpMax - textRange.chrg.cpMin + 1024;
				m_pBuffer = std::make_unique<char[]>(m_nBufLen);
			}
			textRange.lpstrText = m_pBuffer.get();
			if (textRange.chrg.cpMax < textLength)
			{
				textRange.chrg.cpMax++;
				m_pEditorCtrl->DoCommand(SCI_GETTEXTRANGE, 0, reinterpret_cast<sptr_t>(&textRange));
			}
			else
			{
				m_pEditorCtrl->DoCommand(SCI_GETTEXTRANGE, 0, reinterpret_cast<sptr_t>(&textRange));
				textRange.chrg.cpMax++;
			}
			auto len = strlen(textRange.lpstrText);
			if (len == 0)
			{
				textRange.chrg.cpMax--;
				m_pEditorCtrl->DoCommand(SCI_GETTEXTRANGE, 0, reinterpret_cast<sptr_t>(&textRange));
				len = strlen(textRange.lpstrText);
				textRange.chrg.cpMax++;
				len++;
			}
			if (len)
				textRange.lpstrText[len - 1] = 0;
			textRange.chrg.cpMax--;
			if (textRange.lpstrText[0])
			{
				std::wstring wsWord = AppUtils::GetUnicodeWString(textRange.lpstrText, true);
				// ignore words that contain numbers/digits
				if (std::any_of(wsWord.begin(), wsWord.end(), ::iswdigit))
					continue;

				// ignore keywords of the currently selected lexer
				if (std::find(m_LangKeywordDataset.begin(), m_LangKeywordDataset.end(), CString(textRange.lpstrText)) != m_LangKeywordDataset.end())
					continue;

				IEnumSpellingError* enumSpellingError = nullptr;
				HRESULT               hr = m_pSpellChecker->Check(wsWord.c_str(), &enumSpellingError);
				bool                  misspelled = false;
				if (SUCCEEDED(hr))
				{
					ISpellingError* spellingError = nullptr;
					hr = enumSpellingError->Next(&spellingError);
					if (hr == S_OK)
					{
						CORRECTIVE_ACTION action = CORRECTIVE_ACTION_NONE;
						spellingError->get_CorrectiveAction(&action);
						if (action != CORRECTIVE_ACTION_NONE)
						{
							// mark word as misspelled
							misspelled = true;
							m_pEditorCtrl->DoCommand(SCI_SETINDICATORCURRENT, INDIC_SPELL_CHECKER);
							m_pEditorCtrl->DoCommand(SCI_INDICATORFILLRANGE, textRange.chrg.cpMin, textRange.chrg.cpMax - textRange.chrg.cpMin);
						}
					}
				}

				if (!misspelled)
				{
					// mark word as correct (remove the squiggle line)
					m_pEditorCtrl->DoCommand(SCI_SETINDICATORCURRENT, INDIC_SPELL_CHECKER);
					m_pEditorCtrl->DoCommand(SCI_INDICATORCLEARRANGE, textRange.chrg.cpMin, textRange.chrg.cpMax - textRange.chrg.cpMin);
					m_pEditorCtrl->DoCommand(SCI_INDICATORCLEARRANGE, textRange.chrg.cpMin, textRange.chrg.cpMax - textRange.chrg.cpMin + 1);
				}
			}
		}
	}
}

void CSpellChecker::GetSuggestionReplaceList(std::vector<std::wstring>& suggestionList, std::wstring& strCurrentWord)
{
	if (m_pSpellChecker)
	{
		auto wordCharsBuffer = m_pEditorCtrl->GetWordChars();
		m_pEditorCtrl->DoCommand(SCI_SETWORDCHARS, 0, reinterpret_cast<sptr_t>(wordCharsBuffer.c_str()));
		m_pEditorCtrl->DoCommand(SCI_SETWORDCHARS, 0, reinterpret_cast<sptr_t>(m_strWordChars.c_str()));
		strCurrentWord = AppUtils::GetUnicodeWString(AppUtils::CStringToStd(m_pEditorCtrl->GetCurrentWord()), true);
		IEnumStringPtr enumSpellingSuggestions = nullptr;
		HRESULT hr = m_pSpellChecker->Suggest(strCurrentWord.c_str(), &enumSpellingSuggestions);
		if (SUCCEEDED(hr))
		{
			hr = S_OK;
			while (hr == S_OK)
			{
				LPOLESTR suggestion = nullptr;
				hr = enumSpellingSuggestions->Next(1, &suggestion, nullptr);

				if (S_OK == hr)
				{
					suggestionList.push_back(suggestion);
					CoTaskMemFree(suggestion);
				}
			}
		}
		else
		{
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error] Failed get suggestion list from spell checker for languague %s..."), AppUtils::WStdToCString(m_strLangugueToCheck));
		}
	}
}