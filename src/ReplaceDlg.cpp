/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "ReplaceDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "AppUtil.h"
#include "EditorDoc.h"
#include "Editor.h"
#include "ScrollHelper.h"
#include "ComboboxRegexHelper.h"
#include "EditorView.h"
#include "VinaTextProgressBar.h"
#include "MultiThreadWorker.h"
#include "AppSettings.h"
#include "AppSettings.h"
#include "FileUtil.h"
#include "GuiUtils.h"
#include "SearchAndReplaceDlg.h"

// CFindAndReplaceDlg dialog

IMPLEMENT_DYNAMIC(CFindAndReplaceDlg, CDialogEx)

CFindAndReplaceDlg::CFindAndReplaceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFindDlg::IDD, pParent)
{
	m_bMatchcase = FALSE;
	m_bMatchwords = FALSE;
	m_bMatchregex = FALSE;
	m_bAppendResult = FALSE;
	m_bShowFileNameOnly = FALSE;
	m_bExcludeSubFolder = FALSE;
	m_strFileFilter = _T("*.*");
	m_pScrollHelper = std::make_unique<CScrollHelper>();
	m_pScrollHelper->AttachWnd(this);
	m_pScrollHelper->SetDisplaySize(200, 560);
}

CFindAndReplaceDlg::~CFindAndReplaceDlg() {}

BOOL CFindAndReplaceDlg::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			auto pActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
			if (pActiveDoc && pActiveDoc->GetEditorCtrl())
			{
				pActiveDoc->GetEditorCtrl()->SetFocus();
			}
			return true;
		}
		else if (pMsg->wParam == 'F')
		{
			if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
			{
				auto const pParent = GetParent()->GetParent();
				auto const pQSDialog = dynamic_cast<CSearchAndReplaceWindowDlg*>(pParent);
				if (pQSDialog)
				{
					CString strSearchWhat;
					m_comboSearchWhat.GetWindowText(strSearchWhat);
					pQSDialog->InitSearchReplaceFromEditor(strSearchWhat, SEARCH_REPLACE_GOTO_DLG_TYPE::SEARCH);
					return TRUE;
				}
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CFindAndReplaceDlg, CDialogEx)
	ON_CBN_EDITCHANGE(ID_EDITOR_REPLACE_DLG_FINDWHAT_COMBO, OnSearchEditChange)
	ON_EN_CHANGE(ID_EDITOR_REPLACE_FILE_FILTER_EDIT, OnFilterEditChange)
	ON_BN_CLICKED(ID_EDITOR_REPLACE_DLG_CANCEL_BTN, OnCancel)
	ON_BN_CLICKED(ID_EDITOR_REPLACE_DLG_FINDNEXT_BTN, OnFindNext)
	ON_BN_CLICKED(ID_EDITOR_REPLACE_DLG_REPLACE_BTN, OnReplaceWith)
	ON_BN_CLICKED(ID_EDITOR_REPLACE_DLG_REPLACE_ALL_BTN, OnReplaceAll)
	ON_BN_CLICKED(ID_EDITOR_REPLACE_DLG_REGEX_CHECKBOX, OnClickCheckBoxRegex)
	ON_CBN_SELCHANGE(ID_EDITOR_REPLACE_DLG_FINDWHAT_COMBO, OnCbnSelchangeSearchEditCombo)
	ON_CBN_SELCHANGE(ID_EDITOR_REPLACE_DLG_SCOPE_COMBO, OnCbnSelchangeSearchScope)
	ON_CBN_SELCHANGE(ID_EDITOR_REPLACE_REGEX_COMBO, OnCbnSelchangeRegexPattern)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

// CFindAndReplaceDlg message handlers

BOOL CFindAndReplaceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitComboReplaceScope();
	InitComboRegexPattern();

	SetWindowTheme(GetDlgItem(ID_EDITOR_REPLACE_DLG_FINDWHAT_STATIC)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_REPLACE_DLG_MATCHCASE_CHECKBOX)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_REPLACE_DLG_WRAPAROUND_CHECKBOX)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACEWITH_STATIC)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_REPLACE_DLG_OPTIONS_STATIC)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_REPLACE_SCOPE_STATIC)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_REPLACE_FILE_FILTER_STATIC)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_REPLACE_DLG_REGEX_CHECKBOX)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_REPLACE_FILE_SPECIFIC_PATH_STATIC)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_REPLACE_PATTERN_STATIC)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_REPLACE_CHECK_APPEND_SEACH_RESULT)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_REPLACE_CHECK_SHOW_FILE_NAME)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_REPLACE_CHECK_EXCLUDE_SUB_FOLDER)->GetSafeHwnd(), L"wstr", L"wstr");

	OnCbnSelchangeSearchScope();

	m_EditSpecialPath.EnableFolderBrowseButton();

	m_comboSearchWhat.SetCueBanner(_T("target..."));
	m_comboReplaceWith.SetCueBanner(_T("replace with..."));

	OnClickCheckBoxRegex();

	LoadDialogState();

	OnSearchEditChange();

	UpdateData(FALSE);

	::DragAcceptFiles(m_hWnd, TRUE);

	RegisterResizingControls();

	return TRUE;
}

void CFindAndReplaceDlg::InitSearchReplaceFromEditor(const CString& strSearchWhat)
{
	CString strCurrentSearchWhat;
	m_comboSearchWhat.GetWindowText(strCurrentSearchWhat);
	if (strSearchWhat.IsEmpty() && strCurrentSearchWhat.IsEmpty())
	{
		m_comboSearchWhat.SetFocus();
		EnableButtons(FALSE);
	}
	else
	{
		if (!strSearchWhat.IsEmpty())
			m_comboSearchWhat.SetWindowTextW(strSearchWhat);
		else
			m_comboSearchWhat.SetWindowTextW(strCurrentSearchWhat);
		SaveSearchString(strSearchWhat);
		m_comboReplaceWith.SetFocus();
		EnableButtons(TRUE);
	}
}

void CFindAndReplaceDlg::InitSearchReplaceFromExplorer(const CString& strFolderPath)
{
	m_comboReplaceScope.SetCurSel(3);
	OnCbnSelchangeSearchScope();
	m_strSpecificPath = strFolderPath;
	m_comboSearchWhat.SetFocus();
	UpdateData(FALSE);
}

void CFindAndReplaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Control(pDX, ID_EDITOR_REPLACE_FILE_FILTER_EDIT, m_EditFilter);
	DDX_Control(pDX, ID_EDITOR_REPLACE_PATH_SPECIFIC_EDIT, m_EditSpecialPath);
	DDX_Check(pDX, ID_EDITOR_REPLACE_DLG_MATCHCASE_CHECKBOX, m_bMatchcase);
	DDX_Check(pDX, ID_EDITOR_REPLACE_DLG_WRAPAROUND_CHECKBOX, m_bMatchwords);
	DDX_Check(pDX, ID_EDITOR_REPLACE_DLG_REGEX_CHECKBOX, m_bMatchregex);
	DDX_Check(pDX, ID_EDITOR_REPLACE_CHECK_APPEND_SEACH_RESULT, m_bAppendResult);
	DDX_Check(pDX, ID_EDITOR_REPLACE_CHECK_SHOW_FILE_NAME, m_bShowFileNameOnly);
	DDX_Check(pDX, ID_EDITOR_REPLACE_CHECK_EXCLUDE_SUB_FOLDER, m_bExcludeSubFolder);
	DDX_Control(pDX, ID_EDITOR_REPLACE_DLG_FINDWHAT_COMBO, m_comboSearchWhat);
	DDX_Control(pDX, ID_EDITOR_REPLACE_REGEX_COMBO, m_combRegexPattern);
	DDX_Control(pDX, ID_EDITOR_REPLACE_DLG_REPLACEWITH_COMBO, m_comboReplaceWith);
	DDX_Control(pDX, ID_EDITOR_REPLACE_DLG_SCOPE_COMBO, m_comboReplaceScope);
	DDX_Text(pDX, ID_EDITOR_REPLACE_FILE_FILTER_EDIT, m_strFileFilter);
	DDX_Text(pDX, ID_EDITOR_REPLACE_PATH_SPECIFIC_EDIT, m_strSpecificPath);
}

void CFindAndReplaceDlg::DoSearchNext(CString strSearchWhat, BOOL bHideMessageBox, BOOL bSaveSearchWord)
{
	if (strSearchWhat.IsEmpty()) return;
	UpdateSearchOptions();
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
			CFindTextWorker::SearchForwardOnEditor(pEditor, strSearchWhat, m_nSearchOptions, bHideMessageBox);
		}
	}
}

void CFindAndReplaceDlg::OnFindNext()
{
	UpdateData(TRUE);
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	DoSearchNext(strSearchWhat, FALSE);
	m_comboSearchWhat.SetFocusEx();
}

void CFindAndReplaceDlg::OnReplaceWith()
{
	UpdateData(TRUE);
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	if (strSearchWhat.IsEmpty()) return;
	UpdateSearchOptions();
	CString strReplaceWith;
	m_comboReplaceWith.GetWindowText(strReplaceWith);
	if (strSearchWhat.CompareNoCase(strReplaceWith) == 0)
	{
		m_nSearchOptions |= SCFIND_MATCHCASE;
	}
	auto const pView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
	if (pView)
	{
		auto pEditor = pView->GetEditorCtrl();
		if (pEditor != NULL && !pEditor->IsReadOnlyEditor())
		{
			SaveSearchString(strSearchWhat);
			SaveReplaceString(strSearchWhat);
			CReplaceTextWorker::ReplaceForwardOnEditor(pEditor, strSearchWhat, strReplaceWith, m_nSearchOptions);
		}
		else
		{
			AfxMessageBox(_T("Can not replace text on this file. It is read only."));
		}
	}
}

void CFindAndReplaceDlg::ReplaceAllInDocument(CDocument* pDoc,
	TEXT_RESULT_SEARCH_REPLACE_DATA& ResultSearchData,
	const CString& strSearchWhat,
	const CString& strReplaceWith,
	unsigned int nSearchOptions)
{
	auto const pEditorDoc = dynamic_cast<CEditorDoc*>(pDoc);
	if (pEditorDoc)
	{
		CString strFilePath = pEditorDoc->GetPathName();
		if (strFilePath.IsEmpty())
		{
			strFilePath = pEditorDoc->GetTitle();
		}
		auto pEditor = pEditorDoc->GetEditorCtrl();
		if (pEditor != NULL && !pEditor->IsReadOnlyEditor())
		{
			if (CReplaceTextWorker::ReplaceAllInEditor(strFilePath, pEditor, ResultSearchData, strSearchWhat, strReplaceWith, nSearchOptions))
			{
				ResultSearchData._nMatchedFiles++;
			}
		}
		else
		{
			AfxMessageBoxFormat(MB_ICONWARNING, _T("Can not replace text on the file \"%s\". It is read only."), strFilePath);
			return;
		}
	}
}

void CFindAndReplaceDlg::RegisterResizingControls()
{
	BOOL bOk = FALSE;
	bOk = m_resizer.Hook(this);
	ASSERT(bOk);

	bOk = m_resizer.SetAnchor(ID_EDITOR_REPLACE_PATH_SPECIFIC_EDIT, ANCHOR_HORIZONTALLY);
	ASSERT(bOk);
	bOk = m_resizer.SetAnchor(ID_EDITOR_REPLACE_REGEX_COMBO, ANCHOR_HORIZONTALLY);
	ASSERT(bOk);
	bOk = m_resizer.SetAnchor(ID_EDITOR_REPLACE_DLG_SCOPE_COMBO, ANCHOR_HORIZONTALLY);
	ASSERT(bOk);
	bOk = m_resizer.SetAnchor(ID_EDITOR_REPLACE_FILE_FILTER_EDIT, ANCHOR_HORIZONTALLY);
	ASSERT(bOk);
	bOk = m_resizer.SetAnchor(ID_EDITOR_REPLACE_DLG_OPTIONS_STATIC, ANCHOR_HORIZONTALLY);
	ASSERT(bOk);
	bOk = m_resizer.SetAnchor(ID_EDITOR_REPLACE_DLG_REPLACEWITH_COMBO, ANCHOR_HORIZONTALLY);
	ASSERT(bOk);
	bOk = m_resizer.SetAnchor(ID_EDITOR_REPLACE_DLG_FINDWHAT_COMBO, ANCHOR_HORIZONTALLY);
	ASSERT(bOk);
}

void CFindAndReplaceDlg::OnReplaceAll()
{
	if (ThreadWorkerMgr.IsRunning() || ThreadWorkerMgr.IsDebuggerRunning())
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd, _T("Program/Debugger is running now, do not allow replacement in files..."), _T("Replace Text"), MB_ICONWARNING);
		return;
	}

	UpdateData(TRUE);

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;

	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	CString strReplaceWith;
	m_comboReplaceWith.GetWindowText(strReplaceWith);
	CString strReplaceScope;
	m_comboReplaceScope.GetWindowText(strReplaceScope);

	if (m_bAppendResult == FALSE && strReplaceScope != _T("Current File"))
	{
		pFrame->ClearDataOnDockPane(DOCKABLE_PANE_TYPE::SEARCH_RESULT_PANE);
	}

	if (m_hThreadReplaceBackground) // if replace background is running, allow to stop thread...
	{
		DWORD dwExitCode = 0;
		if (::GetExitCodeThread(m_hThreadReplaceBackground, &dwExitCode))
		{
			if (dwExitCode == STILL_ACTIVE)
			{
				dwExitCode = 0;
				::TerminateThread(m_hThreadReplaceBackground, dwExitCode);
				m_hThreadReplaceBackground = NULL;
			}
		}
		GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_ALL_BTN)->SetWindowTextW(_T("Replace All"));
		GetDlgItem(ID_EDITOR_REPLACE_DLG_FINDNEXT_BTN)->EnableWindow(TRUE);
		GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_BTN)->EnableWindow(TRUE);
		m_pReplaceProgressBar.reset();
		return;
	}

	// replace results
	TEXT_RESULT_SEARCH_REPLACE_DATA ResultSearchData;

	auto startMeasure = OSUtils::StartBenchmark();

	UpdateSearchOptions();

	if (strSearchWhat.IsEmpty()) return;

	SaveSearchString(strSearchWhat);
	SaveReplaceString(strReplaceWith);

	if (strSearchWhat.CompareNoCase(strReplaceWith) == 0)
	{
		m_nSearchOptions |= SCFIND_MATCHCASE;
	}

	if (strReplaceScope == _T("Current File"))
	{
		ResultSearchData._nTotalSearchFile = 1;
		ReplaceAllInDocument(AppUtils::GetMDIActiveDocument(), ResultSearchData, strSearchWhat, strReplaceWith, m_nSearchOptions);
	}
	else if (strReplaceScope == _T("All Opened Files"))
	{
		BOOL bUserAnwser = AskBeforeContinueReplace(strReplaceScope);
		if (!bUserAnwser) return;

		auto vecDocs = AppUtils::GetAllDocuments();
		ResultSearchData._nTotalSearchFile = (unsigned int)vecDocs.size();
		for (auto const& doc : vecDocs)
		{
			ReplaceAllInDocument(doc, ResultSearchData, strSearchWhat, strReplaceWith, m_nSearchOptions);
		}
	}
	else if (strReplaceScope == _T("Container Folder"))
	{
		auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
		if (pDoc)
		{
			CString strFilePath = pDoc->GetPathName();
			if (PathFileExists(strFilePath))
			{
				CString strContainerFoler = PathUtils::GetContainerPath(strFilePath);
				BOOL bUserAnwser = AskBeforeContinueReplace(strContainerFoler);
				if (!bUserAnwser) return;

				GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_ALL_BTN)->SetWindowTextW(_T("Stop"));
				GetDlgItem(ID_EDITOR_REPLACE_DLG_FINDNEXT_BTN)->EnableWindow(FALSE);
				GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_BTN)->EnableWindow(FALSE);

				// background replace start...
				CString strMessageProgressbar;
				strMessageProgressbar.Format(_T("Replacing text..."));
				m_pReplaceProgressBar = std::make_unique<CVinaTextProgressBar>(0, 100, strMessageProgressbar, PROGRESS_BAR_TYPE::TYPE_SEARCH);
				m_pReplaceProgressBar->SetPos(0);
				std::unique_ptr<CReplaceTextWorker> pReplacer = std::make_unique<CReplaceTextWorker>();
				pReplacer->SetReplaceFolder(strContainerFoler);
				pReplacer->SetSearchWhat(strSearchWhat);
				pReplacer->SetReplaceWith(strReplaceWith);
				pReplacer->SetIncludeSubFolder(!m_bExcludeSubFolder);
				pReplacer->SetSearchOptions(m_nSearchOptions);
				pReplacer->SetFileFilter(m_strFileFilter);
				pReplacer->SetParentWindow(this);
				DWORD dwExitCode = 0;
				CWinThread* pThread = ::AfxBeginThread(ReplaceBackgroundThreadProc, (LPVOID)pReplacer.get(), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED | THREAD_TERMINATE, NULL);
				if (pThread)
				{
					m_hThreadReplaceBackground = pThread->m_hThread;
					pThread->m_bAutoDelete = TRUE;
					pThread->ResumeThread();
				}
				while (TRUE)
				{
					if (!::GetExitCodeThread(m_hThreadReplaceBackground, &dwExitCode))
					{
						break;
					}
					if (dwExitCode != STILL_ACTIVE)
					{
						break;
					}
					USE_THREAD_PUMP_UI;
					if (m_pReplaceProgressBar && pReplacer) // avoid crashing when stop searching
					{
						int nCurPos = pReplacer->GetCurrentReplaceProgress();
						m_pReplaceProgressBar->SetPos(nCurPos);
						CString strMessageProgressbar;
						strMessageProgressbar.Format(_T("%s, %d%% completed..."), pReplacer->GetCurrentReplacePath(), nCurPos);
						m_pReplaceProgressBar->SetText(strMessageProgressbar);
					}
				}
				pReplacer->ReportFailedCases();
				m_hThreadReplaceBackground = NULL;
				m_pReplaceProgressBar.reset();
				// update result to main thread...
				ResultSearchData = pReplacer->m_ResultReplaceData;
				GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_ALL_BTN)->SetWindowTextW(_T("Replace All"));
				GetDlgItem(ID_EDITOR_REPLACE_DLG_FINDNEXT_BTN)->EnableWindow(TRUE);
				GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_BTN)->EnableWindow(TRUE);
			}
			else
			{
				AfxMessageBox(_T("[Replace In Container Folder Error] current file path does not exist."));
				return;
			}
		}
	}
	else if (strReplaceScope == _T("Specific Path"))
	{
		if (m_strSpecificPath.IsEmpty())
		{
			AfxMessageBox(_T("[Replace In Path Error] specific path is empty."));
			return;
		}
		if (PathFileExists(m_strSpecificPath))
		{
			if (!PathUtils::IsDirectory(m_strSpecificPath))
			{
				if (PathUtils::IsFileReadOnly(m_strSpecificPath))
				{
					AfxMessageBoxFormat(MB_ICONWARNING, _T("Can not replace text on the file \"%s\". It is read only."), m_strSpecificPath);
					return;
				}
				CReplaceTextWorker replacer;
				replacer.SetFileFilter(m_strFileFilter);
				if (replacer.CheckFileFilter(m_strFileFilter))
				{
					CRect rectEditor;
					rectEditor.SetRectEmpty();
					std::unique_ptr<CEditorCtrl> pEditor = std::make_unique<CEditorCtrl>();
					pEditor->Create(_T("Replace Editor"), WS_CHILD | WS_CLIPCHILDREN | WS_EX_RTLREADING, rectEditor, this, ID_EDITOR_CTRL_SEARCH);
					if (::IsWindow(pEditor->GetSafeHwnd()))
					{
						pEditor->LoadFile(m_strSpecificPath);
						ResultSearchData._nTotalSearchFile = 1;
						if (CReplaceTextWorker::ReplaceAllInEditor(m_strSpecificPath, pEditor.get(), ResultSearchData, strSearchWhat, strReplaceWith, m_nSearchOptions))
						{
							ResultSearchData._nMatchedFiles = 1;
						}
					}
				}
			}
			else
			{
				auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
				BOOL bUserAnwser = AskBeforeContinueReplace(m_strSpecificPath);
				if (!bUserAnwser) return;

				GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_ALL_BTN)->SetWindowTextW(_T("Stop"));
				GetDlgItem(ID_EDITOR_REPLACE_DLG_FINDNEXT_BTN)->EnableWindow(FALSE);
				GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_BTN)->EnableWindow(FALSE);

				// background replace start...
				CString strMessageProgressbar;
				strMessageProgressbar.Format(_T("Replacing text..."));
				m_pReplaceProgressBar = std::make_unique<CVinaTextProgressBar>(0, 100, strMessageProgressbar, PROGRESS_BAR_TYPE::TYPE_SEARCH);
				m_pReplaceProgressBar->SetPos(0);
				std::unique_ptr<CReplaceTextWorker> pReplacer = std::make_unique<CReplaceTextWorker>();
				pReplacer->SetReplaceFolder(m_strSpecificPath);
				pReplacer->SetSearchWhat(strSearchWhat);
				pReplacer->SetReplaceWith(strReplaceWith);
				pReplacer->SetIncludeSubFolder(!m_bExcludeSubFolder);
				pReplacer->SetSearchOptions(m_nSearchOptions);
				pReplacer->SetFileFilter(m_strFileFilter);
				pReplacer->SetParentWindow(this);
				DWORD dwExitCode = 0;
				CWinThread* pThread = ::AfxBeginThread(ReplaceBackgroundThreadProc, (LPVOID)pReplacer.get(), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED | THREAD_TERMINATE, NULL);
				if (pThread)
				{
					m_hThreadReplaceBackground = pThread->m_hThread;
					pThread->m_bAutoDelete = TRUE;
					pThread->ResumeThread();
				}
				while (TRUE)
				{
					if (!::GetExitCodeThread(m_hThreadReplaceBackground, &dwExitCode))
					{
						break;
					}
					if (dwExitCode != STILL_ACTIVE)
					{
						break;
					}
					USE_THREAD_PUMP_UI;
					if (m_pReplaceProgressBar && pReplacer) // avoid crashing when stop searching
					{
						int nCurPos = pReplacer->GetCurrentReplaceProgress();
						m_pReplaceProgressBar->SetPos(nCurPos);
						CString strMessageProgressbar;
						strMessageProgressbar.Format(_T("%s - %d%% completed..."), pReplacer->GetCurrentReplacePath(), nCurPos);
						m_pReplaceProgressBar->SetText(strMessageProgressbar);
					}
				}
				pReplacer->ReportFailedCases();
				m_hThreadReplaceBackground = NULL;
				m_pReplaceProgressBar.reset();
				// update result to main thread...
				ResultSearchData = pReplacer->m_ResultReplaceData;
				GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_ALL_BTN)->SetWindowTextW(_T("Replace All"));
				GetDlgItem(ID_EDITOR_REPLACE_DLG_FINDNEXT_BTN)->EnableWindow(TRUE);
				GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_BTN)->EnableWindow(TRUE);
			}
		}
		else
		{
			AfxMessageBox(_T("[Replace In Path Error] specific path does not exist."));
			return;
		}
	}
	ResultSearchData._TimeMeasured = OSUtils::StopBenchmark(startMeasure);
	ResultSearchData._strSearchWhat = strSearchWhat;
	ResultSearchData._bAppendResult = m_bAppendResult;
	ResultSearchData._bShowFileNameOnly = m_bShowFileNameOnly;
	ResultSearchData._strScope = strReplaceScope;
	ResultSearchData._strReplaceWith = strReplaceWith;
	ResultSearchData._bIsReplaceData = TRUE;
	// send data to log window
	pFrame->AddSearchResultDataToPane(ResultSearchData);
}

BOOL CFindAndReplaceDlg::OnEraseBkgnd(CDC * pDC)
{
	CRect rect;
	GetClientRect(&rect);
	CBrush myBrush(AppSettingMgr.m_AppThemeColor);    
	CBrush *pOld = pDC->SelectObject(&myBrush);
	BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOld);  
	return bRes;
}

void CFindAndReplaceDlg::OnClickCheckBoxRegex()
{
	UpdateData(TRUE);
	if (m_bMatchregex)
	{
		GetDlgItem(ID_EDITOR_REPLACE_REGEX_COMBO)->EnableWindow(TRUE);
		if (GetSearchWhat().IsEmpty())
		{
			OnCbnSelchangeRegexPattern();
		}
	}
	else
	{
		GetDlgItem(ID_EDITOR_REPLACE_REGEX_COMBO)->EnableWindow(FALSE);
	}
}

HBRUSH CFindAndReplaceDlg::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == ID_EDITOR_REPLACE_DLG_MATCHCASE_CHECKBOX
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_REPLACE_DLG_WRAPAROUND_CHECKBOX
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_REPLACE_DLG_REPLACEWITH_STATIC
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_REPLACE_DLG_FINDWHAT_STATIC
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_REPLACE_DLG_OPTIONS_STATIC
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_REPLACE_DLG_REGEX_CHECKBOX
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_REPLACE_FILE_FILTER_STATIC
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_REPLACE_SCOPE_STATIC
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_REPLACE_FILE_SPECIFIC_PATH_STATIC
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_REPLACE_PATTERN_STATIC
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_REPLACE_CHECK_APPEND_SEACH_RESULT
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_REPLACE_CHECK_SHOW_FILE_NAME
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_REPLACE_CHECK_EXCLUDE_SUB_FOLDER
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_REPLACE_DLG_FINDNEXT_BTN
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_REPLACE_DLG_REPLACE_BTN
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_REPLACE_DLG_REPLACE_ALL_BTN)
	{
		pDC->SetTextColor(IS_LIGHT_THEME ? BasicColors::black : BasicColors::white);
		pDC->SetBkMode(TRANSPARENT);
		return CreateSolidBrush(AppSettingMgr.m_AppThemeColor);
	}
	return hbr;
}

void CFindAndReplaceDlg::SaveSearchString(const CString& strSearch)
{
	if (strSearch.IsEmpty()) return;
	for (int i = 0; i < m_strSearchWhats.GetSize(); i++)
	{
		if (m_strSearchWhats.GetAt(i) == strSearch) return;
	}
	m_strSearchWhats.Add(strSearch);
	m_comboSearchWhat.InsertString(0, strSearch);
}

void CFindAndReplaceDlg::SaveReplaceString(const CString& strReplace)
{
	if (strReplace.IsEmpty()) return;
	for (int i = 0; i < m_strReplaceWiths.GetSize(); i++)
	{
		if (m_strReplaceWiths.GetAt(i) == strReplace) return;
	}
	m_strReplaceWiths.Add(strReplace);
	m_comboReplaceWith.AddString(strReplace);
}

void CFindAndReplaceDlg::SaveDialogState()
{
	CString strJsonFilePath = PathUtils::GetVinaTextAppDataPath() + _T("advancereplace-dialog-state.json");
	JSonWriter jsonWriter(strJsonFilePath, "VinaText Advance Replace Dialog Saved States");

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

void CFindAndReplaceDlg::LoadDialogState()
{
	CString strJsonFilePath = PathUtils::GetVinaTextAppDataPath() + _T("advancereplace-dialog-state.json");
	if (!PathFileExists(strJsonFilePath))
	{
		return;
	}
	JSonReader jsonReader(strJsonFilePath, "VinaText Advance Replace Dialog Saved States");
	if (!jsonReader.LoadFile()) return;

	CString strSearchCBData;
	jsonReader.ReadCString("combobox-search-data", strSearchCBData);
	m_comboSearchWhat.ResetContent();
	CStringArray arrLineSearch;
	AppUtils::SplitCString(strSearchCBData, SAPERATOR_JSON_DATA, arrLineSearch);
	for (int i = static_cast<int>(arrLineSearch.GetSize()) - 1; i >= 0; --i)
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
	for (int i = static_cast<int>(arrLineReplace.GetSize()) - 1; i >= 0; --i)
	{
		CString strText = arrLineReplace[i];
		if (strText.IsEmpty()) continue;
		if (m_comboReplaceWith.FindString(0, arrLineReplace[i]) < 0)
		{
			m_comboReplaceWith.InsertString(0, arrLineReplace[i]);
		}
	}
}

void CFindAndReplaceDlg::ClearAll()
{
	m_comboSearchWhat.ResetContent();
	m_comboReplaceWith.ResetContent();
}

UINT CFindAndReplaceDlg::ReplaceBackgroundThreadProc(LPVOID pParam)
{
	CReplaceTextWorker* pReplacer = reinterpret_cast<CReplaceTextWorker*>(pParam);
	if (pReplacer == NULL)
	{
		return 1;
	}
	pReplacer->ReplaceInFolder();
	return 0; // thread completed successfully
}

void CFindAndReplaceDlg::InitComboReplaceScope()
{
	m_comboReplaceScope.ResetContent();
	m_comboReplaceScope.AddString(_T("Current File"));
	m_comboReplaceScope.AddString(_T("All Opened Files"));
	m_comboReplaceScope.AddString(_T("Container Folder"));
	m_comboReplaceScope.AddString(_T("Specific Path"));
	//m_comboReplaceScope.AddString(_T("Current Project"));
	m_comboReplaceScope.SetCurSel(0);
}

void CFindAndReplaceDlg::InitComboRegexPattern()
{
	ComboboxRegexHelper::PopulateRegexFields(m_combRegexPattern);
}

void CFindAndReplaceDlg::OnCbnSelchangeSearchScope()
{
	int iSel = m_comboReplaceScope.GetCurSel();
	if (iSel == 3)
	{
		GetDlgItem(ID_EDITOR_REPLACE_PATH_SPECIFIC_EDIT)->EnableWindow(TRUE);
		GetDlgItem(ID_EDITOR_REPLACE_PATH_SPECIFIC_EDIT)->SetFocus();
	}
	else
	{
		GetDlgItem(ID_EDITOR_REPLACE_PATH_SPECIFIC_EDIT)->EnableWindow(FALSE);
	}

	if (iSel != 0)
	{
		GetDlgItem(ID_EDITOR_REPLACE_FILE_FILTER_EDIT)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(ID_EDITOR_REPLACE_FILE_FILTER_EDIT)->EnableWindow(FALSE);
	}
}

void CFindAndReplaceDlg::OnCbnSelchangeRegexPattern()
{
	ComboboxRegexHelper::SetSearchFields(m_comboSearchWhat, m_combRegexPattern);
	OnSearchEditChange();
}

void CFindAndReplaceDlg::OnFilterEditChange()
{
	CString strSearchFilter;
	m_EditFilter.GetWindowText(strSearchFilter);
	if (strSearchFilter.IsEmpty())
	{
		m_EditFilter.SetWindowText(_T("*.*;"));
		m_EditFilter.SetFocusEx();
	}
}

// for scrolling //////////////////////////////////////////////////////////////

void CFindAndReplaceDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pScrollHelper->OnHScroll(nSBCode, nPos, pScrollBar);
}

void CFindAndReplaceDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pScrollHelper->OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CFindAndReplaceDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	BOOL wasScrolled = m_pScrollHelper->OnMouseWheel(nFlags, zDelta, pt);

	return wasScrolled;
}

void CFindAndReplaceDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_pScrollHelper->OnSize(nType, cx, cy);

	const std::vector<int> buttonIDs = { ID_EDITOR_REPLACE_DLG_FINDNEXT_BTN, ID_EDITOR_REPLACE_DLG_REPLACE_BTN, ID_EDITOR_REPLACE_DLG_REPLACE_ALL_BTN };
	CRect rect; GetClientRect(&rect);
	GuiUtils::ResizeControlsHorizontally(this, buttonIDs, rect.Width(), rect.Height());
}

void CFindAndReplaceDlg::UpdateSearchOptions()
{
	UpdateData(TRUE);
	m_nSearchOptions = 0;
	if (m_bMatchwords)
		m_nSearchOptions |= SCFIND_WHOLEWORD;
	if (m_bMatchcase)
		m_nSearchOptions |= SCFIND_MATCHCASE;
	if (m_bMatchregex)
		m_nSearchOptions |= SCFIND_REGEXP;
}

CString CFindAndReplaceDlg::GetSearchWhat()
{
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	return strSearchWhat;
}

unsigned int CFindAndReplaceDlg::GetSearchOption()
{
	UpdateSearchOptions();
	return m_nSearchOptions;
}

ADVANCED_SEARCH_DATA CFindAndReplaceDlg::GetSycnFindReplaceSettings()
{
	UpdateData(TRUE);
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	ADVANCED_SEARCH_DATA dataSync;
	dataSync._strSearchWhat = strSearchWhat;
	dataSync._strSpecificPath = m_strSpecificPath;
	dataSync._bAppendResult = m_bAppendResult;
	dataSync._bExcludeSubFolder = m_bExcludeSubFolder;
	dataSync._bMacthregex = m_bMatchregex;
	dataSync._bMatchcase = m_bMatchcase;
	dataSync._bMatchwords = m_bMatchwords;
	dataSync._bShowFileNameOnly = m_bShowFileNameOnly;
	dataSync._strFileFilter = m_strFileFilter;
	dataSync._nRegexPattern = m_combRegexPattern.GetCurSel();
	dataSync._nSearchScope = m_comboReplaceScope.GetCurSel();
	return dataSync;
}

void CFindAndReplaceDlg::SyncSearchReplaceSettings(const ADVANCED_SEARCH_DATA & settings)
{
	m_comboSearchWhat.SetWindowTextW(settings._strSearchWhat);
	m_comboSearchWhat.SetFocusEx();
	m_comboReplaceScope.SetCurSel(settings._nSearchScope);
	m_combRegexPattern.SetCurSel(settings._nRegexPattern);
	OnCbnSelchangeSearchScope();
	SaveSearchString(settings._strSearchWhat);
	m_strSpecificPath = settings._strSpecificPath;
	m_bAppendResult = settings._bAppendResult;
	m_bExcludeSubFolder = settings._bExcludeSubFolder;
	m_bMatchregex = settings._bMacthregex;
	m_bMatchcase = settings._bMatchcase;
	m_bMatchwords = settings._bMatchwords;
	m_bShowFileNameOnly = settings._bShowFileNameOnly;
	m_strFileFilter = settings._strFileFilter;
	if (settings._strSearchWhat.IsEmpty())
	{
		EnableButtons(FALSE);
	}
	else
	{
		EnableButtons(TRUE);
	}
	UpdateData(FALSE);
	OnClickCheckBoxRegex();
}

void CFindAndReplaceDlg::UpdateUIVisual()
{
	GuiUtils::ForceRedrawCWnd(this);
}

BOOL CFindAndReplaceDlg::AskBeforeContinueReplace(const CString& strWhereToReplace)
{
	if (!AppSettingMgr.m_bAskBeforeReplaceInFiles) return TRUE;
	int anwser = ::MessageBox(AfxGetMainWnd()->m_hWnd, AfxCStringFormat(_T("[Warning] VinaText will replace text of file(s) in [%s], do you want to continue?"),
		strWhereToReplace), _T("Search And Replace Text"), MB_YESNO | MB_ICONINFORMATION);
	if (IDYES == anwser)
	{
		return TRUE;
	}
	return FALSE;
}

void CFindAndReplaceDlg::EnableButtons(BOOL bEnable)
{
	GetDlgItem(ID_EDITOR_REPLACE_DLG_FINDNEXT_BTN)->EnableWindow(bEnable);
	GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_BTN)->EnableWindow(bEnable);
	GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_ALL_BTN)->EnableWindow(bEnable);
}

void CFindAndReplaceDlg::OnSearchEditChange()
{
	UpdateData(TRUE);
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	if (strSearchWhat.IsEmpty())
	{
		EnableButtons(FALSE);
	}
	else
	{
		if (AppSettingMgr.m_bEnableAutoSearchWhenTyping)
		{
			DoSearchNext(strSearchWhat, TRUE, FALSE);
		}
		EnableButtons(TRUE);
	}
}

void CFindAndReplaceDlg::OnDropFiles(HDROP hDropInfo)
{
	CDialogEx::OnDropFiles(hDropInfo);
	int nCntFiles = DragQueryFile(hDropInfo, -1, 0, 0);
	if (nCntFiles == 1)
	{
		TCHAR szPath[_MAX_PATH];
		szPath[0] = 0;
		::DragQueryFile(hDropInfo, 0, szPath, _MAX_PATH);
		if (PathUtils::IsDirectory(szPath))
		{
			InitSearchReplaceFromExplorer(szPath);
		}
		else
		{
			InitSearchReplaceFromExplorer(PathUtils::GetContainerPath(szPath));
		}
	}
	DragFinish(hDropInfo);
}

void CFindAndReplaceDlg::OnCbnSelchangeSearchEditCombo()
{
	UpdateData(TRUE);
	CString strSearchWhat;
	int index = m_comboSearchWhat.GetCurSel();
	if (index != CB_ERR)
	{
		m_comboSearchWhat.GetLBText(index, strSearchWhat);
	}
	if (strSearchWhat.IsEmpty())
	{
		EnableButtons(FALSE);
	}
	else
	{
		CEditorView* pView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
		if (AppSettingMgr.m_bEnableAutoSearchWhenTyping)
		{
			DoSearchNext(strSearchWhat, TRUE, FALSE);
		}
		EnableButtons(TRUE);
	}
}