/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

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
#include "TemporarySettings.h"
#include "FileUtil.h"
#include "FindReplaceTextWorker.h"
#include "QuickSearchDialog.h"

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
	CString strSearchWhatCB = strSearchWhat;
	if (strSearchWhatCB.IsEmpty())
	{
		m_comboSearchWhat.GetWindowText(strSearchWhatCB);
		if (strSearchWhatCB.IsEmpty())
			EnableButtons(FALSE);
		else
			EnableButtons(TRUE);
	}
	else
	{
		EnableButtons(TRUE);
	}
	m_comboSearchWhat.SetWindowTextW(strSearchWhatCB);
	m_comboSearchWhat.SetFocus();
}

void CQuickSearch::InitComboSearchOption(unsigned int uiSearchOptions)
{
	m_comboSearchOption.SetCurSel(uiSearchOptions);
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
	UpdateQuickSearchOptionCombo();
	return m_nSearchOptions;
}

void CQuickSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_EDITOR_QUICK_SEARCH_COMBO, m_comboSearchWhat);
	DDX_Control(pDX, ID_EDITOR_QUICK_SEARCH_OPTION_COMBO, m_comboSearchOption);
	DDX_Control(pDX, ID_EDITOR_QUICK_SEARCH_RESULT_COMBO, m_comboSearchResult);
}

BOOL CQuickSearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitComboSearchOption();
	InitComboSearchResult();
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
		else if (pMsg->wParam == VK_RETURN && GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnBnClickedEditorQuickSearchAll();
			return TRUE;
		}
		else if (pMsg->wParam == VK_RETURN && GetKeyState(VK_SHIFT) & 0x8000)
		{
			OnBnClickedEditorQuickSearchPrevious();
			return TRUE;
		}
		else if (pMsg->wParam == 'H' && GetKeyState(VK_CONTROL) & 0x8000)
		{
			auto const pParent = GetParent()->GetParent();
			auto const pQSDialog = dynamic_cast<CQuickSearchDialog*>(pParent);
			if (pQSDialog)
			{
				CString strSearchWhat;
				m_comboSearchWhat.GetWindowText(strSearchWhat);
				pQSDialog->InitSearchReplaceFromEditor(strSearchWhat, SEARCH_REPLACE_GOTO_DLG_TYPE::REPLACE);
				return TRUE;
			}
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
	auto const pView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
	if (pView)
	{
		auto pEditor = pView->GetEditorCtrl();
		if (pEditor != NULL)
		{
			if (bSaveSearchWord)
			{
				SaveSearchString(strSearchWhat);
			}
			if (!CFindTextWorker::SearchForwardOnEditor(pEditor, strSearchWhat, m_nSearchOptions, bHideMessageBox))
			{
				m_comboSearchWhat.SetFocus();
			}
		}
	}
}

void CQuickSearch::DoSeachPrevious(CString strSearchWhat)
{
	if (strSearchWhat.IsEmpty())
	{
		return;
	}
	UpdateQuickSearchOptionCombo();
	auto const pView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
	if (pView)
	{
		auto pEditor = pView->GetEditorCtrl();
		if (pEditor != NULL)
		{
			SaveSearchString(strSearchWhat);
			if (!CFindTextWorker::SearchBackwardOnEditor(pEditor, strSearchWhat, m_nSearchOptions))
			{
				m_comboSearchWhat.SetFocus();
			}
		}
	}
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
	BOOL bCantFoundWord = FALSE;
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	const auto pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pEditorDoc)
	{
		UpdateQuickSearchOptionCombo();
		UpdateQuickSearchResultCombo();
		if (m_nAddResultTo == ADD_RESULT_TO::SEARCH_RESULT_WINDOW)
		{
			SaveSearchString(strSearchWhat);
			auto startMeasure = OSUtils::StartBenchmark();;
			CString strFilePath = pEditorDoc->GetPathName();
			if (strFilePath.IsEmpty())
			{
				strFilePath = pEditorDoc->GetTitle();
			}
			TEXT_RESULT_SEARCH_REPLACE_DATA ResultSearchData;
			if (CFindTextWorker::SearchAllInEditor(strFilePath, pEditorDoc->GetEditorCtrl(), ResultSearchData, strSearchWhat, m_nSearchOptions))
			{
				ResultSearchData._nTotalSearchFile = 1;
				ResultSearchData._nMatchedFiles = 1;
				ResultSearchData._TimeMeasured = OSUtils::StopBenchmark(startMeasure);
				ResultSearchData._strSearchWhat = strSearchWhat;
				ResultSearchData._bAppendResult = FALSE;
				ResultSearchData._bShowFileNameOnly = FALSE;
				ResultSearchData._strScope = _T("Current File");
				// send data to log window
				CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
				ASSERT(pFrame); if (!pFrame) return;
				pFrame->AddSearchResultDataToPane(ResultSearchData);
			}
			else
			{
				bCantFoundWord = TRUE;
			}
		}
		else if (m_nAddResultTo == ADD_RESULT_TO::SELECTION_TEXT)
		{
			if (pEditorDoc->GetEditorView()->SelectAllOccurrences(strSearchWhat, m_nSearchOptions))
			{
				pEditorDoc->GetEditorView()->SetFocus();
				pEditorDoc->GetEditorCtrl()->UpdateMainSelectionInCurrentView();
			}
			else
			{
				bCantFoundWord = TRUE;
			}
		}
		else if (m_nAddResultTo == ADD_RESULT_TO::BOOKMARK_BAR)
		{
			if (pEditorDoc->GetEditorView()->BookmarkAllOccurrences(strSearchWhat, m_nSearchOptions))
			{ 
			}
			else
			{
				bCantFoundWord = TRUE;
			}
		}
	}
	if (bCantFoundWord)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd, AfxCStringFormat(_T("Word not found: %s"), strSearchWhat), _T("Search All Text"), MB_ICONINFORMATION);
		m_comboSearchWhat.SetFocus();
	}
}

void CQuickSearch::UpdateQuickSearchOptionCombo()
{
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

void CQuickSearch::UpdateQuickSearchResultCombo()
{
	int nSel = m_comboSearchResult.GetCurSel();
	if (nSel == 0)
	{
		m_nAddResultTo = ADD_RESULT_TO::SEARCH_RESULT_WINDOW;
	}
	else if (nSel == 1)
	{
		m_nAddResultTo = ADD_RESULT_TO::SELECTION_TEXT;
	}
	else if (nSel == 2)
	{
		m_nAddResultTo = ADD_RESULT_TO::BOOKMARK_BAR;
	}
}

void CQuickSearch::InitComboSearchResult()
{
	m_comboSearchResult.ResetContent();
	m_comboSearchResult.AddString(_T("  Search All Results"));
	m_comboSearchResult.AddString(_T("  Select All Results"));
	m_comboSearchResult.AddString(_T("  Bookmark All Results"));
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
	jsonWriter.AddValue("combobox-search-option", std::to_string(m_comboSearchOption.GetCurSel()));
	jsonWriter.AddValue("combobox-search-result", std::to_string(m_comboSearchResult.GetCurSel()));
	jsonWriter.SaveFile();
	TemporarySettings.m_strComboboxQuickSearch = GetSearchWhat();
}

void CQuickSearch::LoadDialogState()
{
	CString strJsonFilePath = PathUtils::GetVinaTextAppDataPath() + _T("quicksearch-dialog-state.json");
	if (!PathFileExists(strJsonFilePath))
	{
		m_comboSearchOption.SetCurSel(0);
		m_comboSearchResult.SetCurSel(0);
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
		if (arrLine[i].IsEmpty()) continue;
		if (m_comboSearchWhat.FindString(0, arrLine[i]) < 0)
		{
			m_comboSearchWhat.InsertString(0, arrLine[i]);
		}
	}
	m_comboSearchWhat.SetWindowTextW(TemporarySettings.m_strComboboxQuickSearch);
	CString strSearchOptionData;
	jsonReader.ReadCString("combobox-search-option", strSearchOptionData);
	if (!strSearchOptionData.IsEmpty())
		m_comboSearchOption.SetCurSel(AppUtils::CStringToInt(strSearchOptionData));
	else
		m_comboSearchOption.SetCurSel(0);
	CString strSearchResultData;
	jsonReader.ReadCString("combobox-search-result", strSearchResultData);
	if (!strSearchResultData.IsEmpty())
		m_comboSearchResult.SetCurSel(AppUtils::CStringToInt(strSearchResultData));
	else
		m_comboSearchResult.SetCurSel(0);

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