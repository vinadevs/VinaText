/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "QuickReplace.h"
#include "afxdialogex.h"
#include "AppUtil.h"
#include "EditorDoc.h"
#include "EditorView.h"
#include "Editor.h"
#include "MainFrm.h"
#include "AppSettings.h"
#include "FileUtil.h"

// CQuickReplace dialog

static CString g_strLatestReplace;

IMPLEMENT_DYNAMIC(CQuickReplace, CDialogEx)

CQuickReplace::CQuickReplace(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_QUICK_REPLACE, pParent)
{
}

CQuickReplace::~CQuickReplace()
{
}

BOOL CQuickReplace::PreTranslateMessage(MSG * pMsg)
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

BOOL CQuickReplace::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitComboSearchOption();
	m_comboSearchWhat.SetCueBanner(_T("target..."));
	m_comboReplaceWith.SetCueBanner(_T("replace with..."));
	LoadDialogState();
	m_comboReplaceWith.SetWindowTextW(g_strLatestReplace);
	UpdateData(FALSE);

	return TRUE;
}

void CQuickReplace::InitSearchReplaceFromEditor(const CString & strSearchWhat)
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
	m_comboSearchWhat.SetFocus();
}

void CQuickReplace::InitComboSearchOption()
{
	m_comboSearchOption.ResetContent();
	m_comboSearchOption.AddString(_T("  Default Mode"));
	m_comboSearchOption.AddString(_T("  Match Case Mode"));
	m_comboSearchOption.AddString(_T("  Match Whole Word Mode"));
	m_comboSearchOption.AddString(_T("  Match Case & Whole Word Mode"));
	m_comboSearchOption.AddString(_T("  Use Regular Expressions"));
	m_comboSearchOption.SetCurSel(0);
}

void CQuickReplace::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_EDITOR_QUICK_REPLACE_SEARCH_COMBO, m_comboSearchWhat);
	DDX_Control(pDX, ID_EDITOR_QUICK_REPLACE_OPTION_COMBO, m_comboSearchOption);
	DDX_Control(pDX, ID_EDITOR_QUICK_REPLACE_COMBO, m_comboReplaceWith);
}

BEGIN_MESSAGE_MAP(CQuickReplace, CDialogEx)
	ON_CBN_EDITCHANGE(ID_EDITOR_QUICK_REPLACE_SEARCH_COMBO, &CQuickReplace::OnSearchEditChange)
	ON_BN_CLICKED(ID_EDITOR_QUICK_REPLACE_NEXT, &CQuickReplace::OnBnClickedEditorQuickReplaceNext)
	ON_BN_CLICKED(ID_EDITOR_QUICK_REPLACE_ALL, &CQuickReplace::OnBnClickedEditorQuickReplaceAll)
	ON_CBN_SELCHANGE(ID_EDITOR_QUICK_REPLACE_OPTION_COMBO, &CQuickReplace::OnCbnSelchangeEditorQuickReplaceOptionCombo)
	ON_CBN_SELCHANGE(ID_EDITOR_QUICK_REPLACE_SEARCH_COMBO, &CQuickReplace::OnCbnSelchangeEditorQuickSearchCombo)
	ON_CBN_EDITCHANGE(ID_EDITOR_QUICK_REPLACE_COMBO, &CQuickReplace::OnReplaceEditChange)
	ON_CBN_SELCHANGE(ID_EDITOR_QUICK_REPLACE_COMBO, &CQuickReplace::OnCbnSelchangeEditorQuickReplaceCombo)
	ON_BN_CLICKED(ID_EDITOR_QUICK_SEARCH_REPLACE_NEXT, &CQuickReplace::OnBnClickedEditorQuickSearchReplaceNext)
END_MESSAGE_MAP()

// CQuickReplace message handlers

void CQuickReplace::EnableButtons(BOOL bEnable)
{
	GetDlgItem(ID_EDITOR_QUICK_SEARCH_REPLACE_NEXT)->EnableWindow(bEnable);
	GetDlgItem(ID_EDITOR_QUICK_REPLACE_NEXT)->EnableWindow(bEnable);
	GetDlgItem(ID_EDITOR_QUICK_REPLACE_ALL)->EnableWindow(bEnable);
}

void CQuickReplace::UpdateQuickSearchReplaceOptionCombo()
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

void CQuickReplace::SaveSearchString(const CString& strSearch)
{
	if (strSearch.IsEmpty()) return;
	for (int i = 0; i < m_strSearchWhats.GetSize(); i++)
	{
		if (m_strSearchWhats.GetAt(i) == strSearch) return;
	}
	m_strSearchWhats.Add(strSearch);
	m_comboSearchWhat.InsertString(0, strSearch);
}

void CQuickReplace::SaveReplaceString(const CString& strReplace)
{
	if (strReplace.IsEmpty()) return;
	for (int i = 0; i < m_strReplaceWiths.GetSize(); i++)
	{
		if (m_strReplaceWiths.GetAt(i) == strReplace) return;
	}
	m_strReplaceWiths.Add(strReplace);
	m_comboReplaceWith.AddString(strReplace);
}

void CQuickReplace::SaveDialogState()
{
	CString strJsonFilePath = PathUtils::GetVinaTextAppDataPath() + _T("quickreplace-dialog-state.json");
	JSonWriter jsonWriter(strJsonFilePath, "VinaText QuickReplace Dialog Saved States");
	
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

	nLimitData = 0;
	CString strReplaceCBData;
	for (int i = 0; i < m_comboReplaceWith.GetCount(); ++i)
	{
		if (nLimitData > AppSettingMgr.m_nDialogComboboxLimitSave) break;
		CString strCurText;
		m_comboReplaceWith.GetLBText(i, strCurText);
		strReplaceCBData += strCurText + SAPERATOR_JSON_DATA;
		nLimitData++;
	}
	jsonWriter.AddValue("combobox-replace-data", AppUtils::CStringToStd(strReplaceCBData));
	jsonWriter.SaveFile();
}

void CQuickReplace::LoadDialogState()
{
	CString strJsonFilePath = PathUtils::GetVinaTextAppDataPath() + _T("quickreplace-dialog-state.json");
	if (!PathFileExists(strJsonFilePath))
	{
		return;
	}
	JSonReader jsonReader(strJsonFilePath, "VinaText QuickReplace Dialog Saved States");
	if (!jsonReader.LoadFile()) return;

	CString strSearchCBData;
	jsonReader.ReadCString("combobox-search-data", strSearchCBData);
	m_comboSearchWhat.ResetContent();
	CStringArray arrLineSearch;
	AppUtils::SplitCString(strSearchCBData, SAPERATOR_JSON_DATA, arrLineSearch);
	for (auto i = arrLineSearch.GetSize() - 1; i >= 0; --i)
	{
		CString strText = arrLineSearch[i];
		if (strText.IsEmpty()) continue;
		if (m_comboSearchWhat.FindString(0, arrLineSearch[i]) < 0)
		{
			m_comboSearchWhat.InsertString(0, arrLineSearch[i]);
		}
	}

	CString strReplaceCBData;
	jsonReader.ReadCString("combobox-replace-data", strReplaceCBData);
	m_comboReplaceWith.ResetContent();
	CStringArray arrLineReplace;
	AppUtils::SplitCString(strReplaceCBData, SAPERATOR_JSON_DATA, arrLineReplace);
	for (auto i = arrLineReplace.GetSize() - 1; i >= 0; --i)
	{
		CString strText = arrLineReplace[i];
		if (strText.IsEmpty()) continue;
		if (m_comboReplaceWith.FindString(0, arrLineReplace[i]) < 0)
		{
			m_comboReplaceWith.InsertString(0, arrLineReplace[i]);
		}
	}
}

void CQuickReplace::OnSearchEditChange()
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
			pView->RenderIndicatorWordsAndCount(strSearchWhat, m_nSearchOptions);
			DoSearchNext(strSearchWhat, TRUE, FALSE);
			EnableButtons(TRUE);
		}
	}
}

void CQuickReplace::OnCbnSelchangeEditorQuickSearchCombo()
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

void CQuickReplace::OnReplaceEditChange()
{
	m_comboReplaceWith.GetWindowText(g_strLatestReplace);
}

void CQuickReplace::OnCbnSelchangeEditorQuickReplaceCombo()
{
	UpdateData(TRUE);
	int index = m_comboReplaceWith.GetCurSel();
	if (index != CB_ERR)
	{
		m_comboReplaceWith.GetLBText(index, g_strLatestReplace);
	}
}

void CQuickReplace::OnBnClickedEditorQuickReplaceNext()
{
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	if (strSearchWhat.IsEmpty())
	{
		return;
	}

	UpdateQuickSearchReplaceOptionCombo();

	CString strReplaceWith;
	m_comboReplaceWith.GetWindowText(strReplaceWith);

	if (strSearchWhat.CompareNoCase(strReplaceWith) == 0)
	{
		m_nSearchOptions |= SCFIND_MATCHCASE;
	}

	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		auto pActiveEditor = pDoc->GetEditorCtrl();
		if (pActiveEditor != NULL && !pActiveEditor->IsReadOnlyEditor())
		{
			SaveSearchString(strSearchWhat);
			SaveReplaceString(strReplaceWith);
			int nPos = pActiveEditor->ReplaceNext(strSearchWhat, strReplaceWith);
			if (nPos == -1)
			{
				::MessageBox(AfxGetMainWnd()->m_hWnd,
					AfxCStringFormat(_T("Word not found: %s"), strSearchWhat),
					_T("VinaText"),
					MB_ICONINFORMATION);
			}
		}
		else
		{
			AfxMessageBox(_T("Read only mode!"));
		}
	}
}

void CQuickReplace::OnBnClickedEditorQuickReplaceAll()
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;

	UpdateQuickSearchReplaceOptionCombo();

	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	CString strReplaceWith;
	m_comboReplaceWith.GetWindowText(strReplaceWith);

	TEXT_RESULT_SEARCH_REPLACE_DATA ResultSearchData;

	auto startMeasure = OSUtils::StartBenchmark();

	if (strSearchWhat.IsEmpty())
	{
		return;
	}

	if (strSearchWhat.CompareNoCase(strReplaceWith) == 0)
	{
		m_nSearchOptions |= VinaTextSearchEngine::OPTIONS::MATCH_CASE;
	}

	long lVisualLine = -1;
	long lCurrentLine = -1;
	CEditorCtrl* pActiveEditor = NULL;
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		pActiveEditor = pDoc->GetEditorCtrl();
		if (pActiveEditor != NULL && !pActiveEditor->IsReadOnlyEditor())
		{
			lVisualLine = pActiveEditor->GetFirstVisibleLine();
			lCurrentLine = pActiveEditor->GetCurrentLine();
		}
		else
		{
			AfxMessageBox(_T("Read only mode!"));
			return;
		}
	}

	if (pDoc)
	{
		if (pActiveEditor != NULL)
		{
			SaveSearchString(strSearchWhat);
			SaveReplaceString(strReplaceWith);
			pActiveEditor->SetSearchflags(m_nSearchOptions);
			if (pActiveEditor != NULL)
			{
				auto selectionProfiler = OSUtils::StartBenchmark();
				pActiveEditor->BeginUndoTransactions();
				int nCountReplaced = pActiveEditor->ReplaceAll(strSearchWhat, strReplaceWith);
				pActiveEditor->EndUndoTransactions();
				OSUtils::LogStopBenchmark(LOG_TARGET::MESSAGE_WINDOW, selectionProfiler, AfxCStringFormat(_T("> Replaced all %d occurrence(s) on current file - timelapse: "), nCountReplaced));
				return;
			}
		}
	}

	ResultSearchData._TimeMeasured = OSUtils::StopBenchmark(startMeasure);
	ResultSearchData._strSearchWhat = strSearchWhat;
	ResultSearchData._bAppendResult = FALSE;
	ResultSearchData._bShowFileNameOnly = FALSE;
	ResultSearchData._strScope = _T("Current File");
	ResultSearchData._strReplaceWith = strReplaceWith;
	ResultSearchData._bIsReplaceData = TRUE;
	ResultSearchData._nMatchedFiles = 1;
	ResultSearchData._nTotalSearchFile = 1;
	// send data to log window
	pFrame->AddSearchResultDataToPane(ResultSearchData);
	if (pDoc && pActiveEditor && lVisualLine != -1 && lCurrentLine != -1)
	{
		pActiveEditor->GotoLine(lCurrentLine);
		pActiveEditor->SetFirstVisibleLine(lVisualLine);
	}
}

void CQuickReplace::OnCbnSelchangeEditorQuickReplaceOptionCombo()
{
	UpdateQuickSearchReplaceOptionCombo();
	OnSearchEditChange();
}

void CQuickReplace::OnBnClickedEditorQuickSearchReplaceNext()
{
	UpdateData(TRUE);
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	DoSearchNext(strSearchWhat, FALSE);
}

void CQuickReplace::DoSearchNext(CString strSearchWhat, BOOL bHideMessageBox, BOOL bSaveSearchWord)
{
	if (strSearchWhat.IsEmpty())
	{
		return;
	}
	UpdateQuickSearchReplaceOptionCombo();
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
						::MessageBox(AfxGetMainWnd()->m_hWnd,
							AfxCStringFormat(_T("Word not found: %s"), strSearchWhat),
							_T("VinaText"),
							MB_ICONINFORMATION);
					}
				}
			}
			strSearchWhat.UnlockBuffer();
		}
	}
	m_comboSearchWhat.SetFocusEx();
}

CString CQuickReplace::GetSearchWhat()
{
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	return strSearchWhat;
}

unsigned int CQuickReplace::GetSearchOption()
{
	return m_nSearchOptions;
}