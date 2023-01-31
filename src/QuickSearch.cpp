// QuickSearch.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "QuickSearch.h"
#include "afxdialogex.h"
#include "AppUtil.h"
#include "EditorDoc.h"
#include "EditorView.h"
#include "Editor.h"
#include "MainFrm.h"
#include "AppSettings.h"
#include "FileUtil.h"

// CQuickSearch dialog

IMPLEMENT_DYNAMIC(CQuickSearch, CDialogEx)

CQuickSearch::CQuickSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_QUICK_SEARCH, pParent)
{
}

CQuickSearch::~CQuickSearch()
{
}

void CQuickSearch::InitSearchReplaceFromEditor(const CString & strSearchWhat)
{
	m_comboSearchWhat.SetWindowTextW(strSearchWhat);
	m_comboSearchWhat.SetFocus();
	SaveSearchString(strSearchWhat);
	if (strSearchWhat.IsEmpty())
	{
		EnableButtons(FALSE);
	}
	else
	{
		EnableButtons(TRUE);
	}
	UpdateData(TRUE);
}

void CQuickSearch::SetFocusComboSearchWhat()
{
	m_comboSearchWhat.SetFocus();
}

CString CQuickSearch::GetSearchWhat()
{
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	return strSearchWhat;
}

unsigned int CQuickSearch::GetSearchOption()
{
	return m_nSearchOptions;
}

void CQuickSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_EDITOR_QUICK_SEARCH_COMBO, m_comboSearchWhat);
	DDX_Control(pDX, ID_EDITOR_QUICK_SEARCH_OPTION_COMBO, m_comboSearchOption);
}

BOOL CQuickSearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitComboSearchOption();
	m_comboSearchWhat.SetCueBanner(_T("target..."));
	LoadDialogState();
	UpdateData(FALSE);

	return TRUE;
}

BOOL CQuickSearch::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			GetParent()->GetParent()->SendMessage(WM_CLOSE, 0, 0);
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CQuickSearch, CDialogEx)
	ON_CBN_EDITCHANGE(ID_EDITOR_QUICK_SEARCH_COMBO, &CQuickSearch::OnSearchEditChange)
	ON_BN_CLICKED(ID_EDITOR_QUICK_SEARCH_NEXT, &CQuickSearch::OnBnClickedEditorQuickSearchNext)
	ON_BN_CLICKED(ID_EDITOR_QUICK_SEARCH_PREVIOUS, &CQuickSearch::OnBnClickedEditorQuickSearchPrevious)
	ON_BN_CLICKED(ID_EDITOR_QUICK_SEARCH_ALL, &CQuickSearch::OnBnClickedEditorQuickSearchAll)
	ON_CBN_SELCHANGE(ID_EDITOR_QUICK_SEARCH_OPTION_COMBO, &CQuickSearch::OnCbnSelchangeEditorQuickSearchOptionCombo)
	ON_CBN_SELCHANGE(ID_EDITOR_QUICK_SEARCH_COMBO, &CQuickSearch::OnCbnSelchangeEditorQuickSearchCombo)
END_MESSAGE_MAP()

// CQuickSearch message handlers

void CQuickSearch::DoSearchNext(CString strSearchWhat, BOOL bHideMessageBox, BOOL bSaveSearchWord)
{
	if (strSearchWhat.IsEmpty())
	{
		return;
	}
	UpdateQuickSearchOptionCombo();
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor != NULL)
		{
			if (bSaveSearchWord)
			{
				SaveSearchString(strSearchWhat);
			}
			pEditor->SetSearchflags(m_nSearchOptions);
			if (!pEditor->SearchForward(strSearchWhat.LockBuffer()))
			{
				int nVisualLine = pEditor->GetFirstVisibleLine();
				int nCurPos = pEditor->GetCurrentPosition();
				pEditor->GotoPosition(0);
				if (!pEditor->SearchForward(strSearchWhat.LockBuffer()))
				{
					pEditor->SetFirstVisibleLine(nVisualLine);
					pEditor->GotoPosition(nCurPos);
					if (!bHideMessageBox)
					{
						AfxMessageBox(_T("WORD NOT FOUND."), MB_ICONINFORMATION);
					}
				}
			}
			strSearchWhat.UnlockBuffer();
		}
	}
	m_comboSearchWhat.SetFocusEx();
}

void CQuickSearch::DoSeachPrevious(CString strSearchWhat)
{
	if (strSearchWhat.IsEmpty())
	{
		return;
	}
	UpdateQuickSearchOptionCombo();
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor != NULL)
		{
			SaveSearchString(strSearchWhat);
			pEditor->SetSearchflags(m_nSearchOptions);
			if (!pEditor->SearchBackward(strSearchWhat.LockBuffer()))
			{
				int nVisualLine = pEditor->GetFirstVisibleLine();
				int nCurPos = pEditor->GetCurrentPosition();
				int nLines = pEditor->GetLineCount();
				int nLineEndPos = pEditor->GetLineEndPosition(nLines);
				pEditor->GotoPosition(nLineEndPos);
				if (!pEditor->SearchBackward(strSearchWhat.LockBuffer()))
				{
					pEditor->SetFirstVisibleLine(nVisualLine);
					pEditor->GotoPosition(nCurPos);
					AfxMessageBox(_T("WORD NOT FOUND."), MB_ICONINFORMATION);
				}
			}
			strSearchWhat.UnlockBuffer();
		}
	}
	m_comboSearchWhat.SetFocusEx();
}

void CQuickSearch::OnBnClickedEditorQuickSearchNext()
{
	UpdateData(TRUE);
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	DoSearchNext(strSearchWhat, FALSE);
}

void CQuickSearch::OnBnClickedEditorQuickSearchPrevious()
{
	UpdateData(TRUE);
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	DoSeachPrevious(strSearchWhat);
}

void CQuickSearch::OnBnClickedEditorQuickSearchAll()
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;

	UpdateQuickSearchOptionCombo();

	TEXT_RESULT_SEARCH_REPLACE_DATA ResultSearchData;

	auto startMeasure = OSUtils::StartBenchmark();

	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	if (strSearchWhat.IsEmpty())
	{
		return;
	}

	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor != NULL)
		{
			SaveSearchString(strSearchWhat);
			pEditor->SetSearchflags(m_nSearchOptions);
			CString strFile = pDoc->GetPathName();
			std::wstring strLine;
			CString strScript;
			pEditor->GetText(strScript);
			if (strScript.IsEmpty()) return;
			std::vector<CString> listLine;
			AppUtils::SplitCString(strScript, listLine);
			unsigned int curLine = 0;
			unsigned int MatchedWords = 0;
			ResultSearchData._nMatchedFiles = 1;
			ResultSearchData._nTotalSearchFile = 1;
			ResultSearchData._vecResultSearchInfo.reserve(listLine.size());
			for (int i = 0; i < listLine.size(); ++i)
			{
				strLine = AppUtils::CStringToWStd(*std::next(listLine.begin(), i));
				curLine++;
				auto nWordCount = (unsigned int)VinaTextSearchEngine::COUNT_WORD(strLine.c_str(), AppUtils::CStringToWStd(strSearchWhat).c_str(), m_nSearchOptions);
				if (nWordCount > 0)
				{
					MatchedWords += nWordCount;
					RESULT_SEARCH_DATA data;
					data._nMatched = nWordCount;
					data._nLineNumber = curLine;
					data._strLine = AppUtils::WStdToCString(strLine);
					if (strFile.IsEmpty())
					{
						data._strTargetFile = pDoc->GetTitle();
					}
					else
					{
						data._strTargetFile = strFile;
					}
					ResultSearchData._vecResultSearchInfo.push_back(data);
				}
			}
			ResultSearchData._nMatchedWords = MatchedWords;
			ResultSearchData._nLineCounts = static_cast<unsigned int>(listLine.size());
		}
	}

	ResultSearchData._TimeMeasured = OSUtils::StopBenchmark(startMeasure);
	ResultSearchData._strSearchWhat = strSearchWhat;
	ResultSearchData._bAppendResult = FALSE;
	ResultSearchData._bShowFileNameOnly = FALSE;
	ResultSearchData._strScope = _T("Current File");
	// send data to log window
	pFrame->AddSearchResultDataToPane(ResultSearchData);
	m_comboSearchWhat.SetFocusEx();
}

void CQuickSearch::UpdateQuickSearchOptionCombo()
{
	UpdateData(TRUE);
	m_nSearchOptions = 0;
	int nSel = m_comboSearchOption.GetCurSel();
	if (nSel == 0)
	{
		m_nSearchOptions |= VinaTextSearchEngine::OPTIONS::INT_SEARCH_OPTION;
	}
	else if (nSel == 1)
	{
		m_nSearchOptions |= VinaTextSearchEngine::OPTIONS::MATCH_CASE;
	}
	else if (nSel == 2)
	{
		m_nSearchOptions |= VinaTextSearchEngine::OPTIONS::MATCH_WORD;
	}
	else if (nSel == 3)
	{
		m_nSearchOptions |= VinaTextSearchEngine::OPTIONS::MATCH_CASE;
		m_nSearchOptions |= VinaTextSearchEngine::OPTIONS::MATCH_WORD;
	}
	else if (nSel == 4)
	{
		m_nSearchOptions |= VinaTextSearchEngine::OPTIONS::REGEX;
	}
}
void CQuickSearch::OnCbnSelchangeEditorQuickSearchOptionCombo()
{
	UpdateQuickSearchOptionCombo();
	OnSearchEditChange();
}

void CQuickSearch::OnCbnSelchangeEditorQuickSearchCombo()
{
	CEditorView* pView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
	if (pView)
	{
		UpdateData(TRUE);
		CString strSearchWhat;
		int index = m_comboSearchWhat.GetCurSel();
		if (index != CB_ERR)
		{
			m_comboSearchWhat.GetLBText(index, strSearchWhat);
		}
		if (m_bResetCaretPosition)
		{
			m_nCurrentFirstLineVisible = pView->GetEditorCtrl()->GetFirstVisibleLine();
			m_nCurrentCaretPostion = pView->GetEditorCtrl()->GetCurrentPosition();
			m_bResetCaretPosition = FALSE;
		}
		if (strSearchWhat.IsEmpty())
		{
			m_bResetCaretPosition = TRUE;
			pView->GetEditorCtrl()->SetCurrentPosition(m_nCurrentCaretPostion);
			pView->GetEditorCtrl()->SetFirstVisibleLine(m_nCurrentFirstLineVisible);
			pView->RenderIndicatorWordsAndCount(_T(""), 0);
			EnableButtons(FALSE);
		}
		else
		{
			if (AppSettingMgr.m_bEnableAutoSearchWhenTyping)
			{
				pView->RenderIndicatorWordsAndCount(strSearchWhat, m_nSearchOptions);
				DoSearchNext(strSearchWhat, TRUE, FALSE);
			}
			EnableButtons(TRUE);
		}
	}
}

void CQuickSearch::SaveSearchString(const CString& strSearch)
{
	if (strSearch.IsEmpty()) return;
	for (int i = 0; i < m_strSearchWhats.GetSize(); i++)
	{
		if (m_strSearchWhats.GetAt(i) == strSearch) return;
	}
	m_strSearchWhats.Add(strSearch);
	m_comboSearchWhat.InsertString(0, strSearch);
}

void CQuickSearch::InitComboSearchOption()
{
	m_comboSearchOption.ResetContent();
	m_comboSearchOption.AddString(_T("  Default Mode"));
	m_comboSearchOption.AddString(_T("  Match Case Mode"));
	m_comboSearchOption.AddString(_T("  Match Whole Word Mode"));
	m_comboSearchOption.AddString(_T("  Match Case & Whole Word Mode"));
	m_comboSearchOption.AddString(_T("  Use Regular Expressions"));
	m_comboSearchOption.SetCurSel(0);
}

void CQuickSearch::SaveDialogState()
{
	CString strJsonFilePath = PathUtils::GetVinaTextAppDataPath() + _T("quicksearch-dialog-state.json");
	JSonWriter jsonWriter(strJsonFilePath, "VinaText Quicksearch Dialog Saved States");
	int nLimitData = 0;
	CString strSearchCBData;
	for (int i = 0; i < m_comboSearchWhat.GetCount(); ++i)
	{
		if (nLimitData > AppSettingMgr.m_nDialogComboboxLimitSave) break;
		CString strCurText;
		m_comboSearchWhat.GetLBText(i, strCurText);
		strSearchCBData += strCurText + SAPERATOR_JSON_DATA;
		nLimitData++;
	}
	jsonWriter.AddValue("combobox-search-data", AppUtils::CStringToStd(strSearchCBData));
	jsonWriter.SaveFile();
}

void CQuickSearch::LoadDialogState()
{
	CString strJsonFilePath = PathUtils::GetVinaTextAppDataPath() + _T("quicksearch-dialog-state.json");
	if (!PathFileExists(strJsonFilePath))
	{
		return;
	}
	JSonReader jsonReader(strJsonFilePath, "VinaText Quicksearch Dialog Saved States");
	if (!jsonReader.LoadFile()) return;
	CString strSearchCBData;
	jsonReader.ReadCString("combobox-search-data", strSearchCBData);
	m_comboSearchWhat.ResetContent();
	CStringArray arrLine;
	AppUtils::SplitCString(strSearchCBData, SAPERATOR_JSON_DATA, arrLine);
	for (auto i = arrLine.GetSize() - 1; i >= 0; --i)
	{
		CString strText = arrLine[i];
		if (strText.IsEmpty()) continue;
		if (m_comboSearchWhat.FindString(0, strText) < 0)
		{
			m_comboSearchWhat.InsertString(0, strText);
		}
	}
}

void CQuickSearch::OnSearchEditChange()
{
	CEditorView* pView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
	if (pView)
	{
		UpdateData(TRUE);
		CString strSearchWhat;
		m_comboSearchWhat.GetWindowText(strSearchWhat);
		if (m_bResetCaretPosition)
		{
			m_nCurrentFirstLineVisible = pView->GetEditorCtrl()->GetFirstVisibleLine();
			m_nCurrentCaretPostion = pView->GetEditorCtrl()->GetCurrentPosition();
			m_bResetCaretPosition = FALSE;
		}
		if (strSearchWhat.IsEmpty())
		{
			m_bResetCaretPosition = TRUE;
			pView->GetEditorCtrl()->SetCurrentPosition(m_nCurrentCaretPostion);
			pView->GetEditorCtrl()->SetFirstVisibleLine(m_nCurrentFirstLineVisible);
			pView->RenderIndicatorWordsAndCount(_T(""), 0);
			EnableButtons(FALSE);
		}
		else
		{
			if (AppSettingMgr.m_bEnableAutoSearchWhenTyping)
			{
				pView->RenderIndicatorWordsAndCount(strSearchWhat, m_nSearchOptions);
				DoSearchNext(strSearchWhat, TRUE, FALSE);
			}
			EnableButtons(TRUE);
		}
	}
}

void CQuickSearch::EnableButtons(BOOL bEnable)
{
	GetDlgItem(ID_EDITOR_QUICK_SEARCH_PREVIOUS)->EnableWindow(bEnable);
	GetDlgItem(ID_EDITOR_QUICK_SEARCH_NEXT)->EnableWindow(bEnable);
	GetDlgItem(ID_EDITOR_QUICK_SEARCH_ALL)->EnableWindow(bEnable);
}