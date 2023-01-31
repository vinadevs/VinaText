/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include <spellcheck.h>

class CEditorCtrl;

class CSpellChecker
{
public:
	CSpellChecker() = default;
	~CSpellChecker();
	BOOL Initilize(CEditorCtrl * pEditorCtrl, const std::wstring & langugueToCheck, const LangKeywordDataset & LangKeywordDataset);
	void Finalize();
	void GetSpellCheckSupportLanguages(std::vector<std::wstring>& listAvailableLanguages);
	void StartSpellCheckingSession();
	void GetSuggestionReplaceList(std::vector<std::wstring>& suggestionList, std::wstring& strCurrentWord);
private:
	CEditorCtrl*			  m_pEditorCtrl;
	int                       m_nBufLen = 1024;
	std::unique_ptr<char[]>   m_pBuffer = nullptr;;
	ISpellCheckerFactory*     m_pSpellCheckerFactory = nullptr;
	ISpellChecker*            m_pSpellChecker = nullptr;
	std::string               m_strWordChars;
	std::wstring              m_strLangugueToCheck;
	LangKeywordDataset        m_LangKeywordDataset;
};