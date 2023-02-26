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
#include "EditorView.h"
#include "VinaTextProgressBar.h"
#include "MultiThreadWorker.h"
#include "AppSettings.h"
#include "AppSettings.h"
#include "FileUtil.h"

// CFindAndReplaceDlg dialog

IMPLEMENT_DYNAMIC(CFindAndReplaceDlg, CDialogEx)

CFindAndReplaceDlg::CFindAndReplaceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFindDlg::IDD, pParent)
{
	m_bMatchcase = FALSE;
	m_bMatchwords = FALSE;
	m_bMacthregex = FALSE;
	m_bAppendResult = FALSE;
	m_bShowFileNameOnly = FALSE;
	m_bExcludeSubFolder = FALSE;
	m_strFileFilter = _T("*.*");
	m_pScrollHelper = std::make_unique<CScrollHelper>();
	m_pScrollHelper->AttachWnd(this);
	m_pScrollHelper->SetDisplaySize(200, 560);
}

CFindAndReplaceDlg::~CFindAndReplaceDlg()
{
}

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

	return TRUE;
}

void CFindAndReplaceDlg::InitSearchReplaceFromEditor(const CString& strSearchWhat, BOOL bSelectEditbox)
{
	m_comboSearchWhat.SetWindowTextW(strSearchWhat);
	if (bSelectEditbox)
		m_comboSearchWhat.SetFocus();
	else
		m_comboSearchWhat.SetFocusEx();
	m_comboReplaceScope.SetCurSel(0);
	OnCbnSelchangeSearchScope();
	SaveSearchString(strSearchWhat);
	if (strSearchWhat.IsEmpty())
	{
		EnableButtons(FALSE);
	}
	else
	{
		EnableButtons(TRUE);
	}
}

void CFindAndReplaceDlg::InitSearchReplaceFromExplorer(const CString& strFolderPath)
{
	m_comboReplaceScope.SetCurSel(3);
	OnCbnSelchangeSearchScope();
	m_strSpecificPath = strFolderPath;
	m_comboReplaceWith.SetFocus();
	UpdateData(FALSE);
}

void CFindAndReplaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Control(pDX, ID_EDITOR_REPLACE_FILE_FILTER_EDIT, m_EditFilter);
	DDX_Control(pDX, ID_EDITOR_REPLACE_PATH_SPECIFIC_EDIT, m_EditSpecialPath);
	DDX_Check(pDX, ID_EDITOR_REPLACE_DLG_MATCHCASE_CHECKBOX, m_bMatchcase);
	DDX_Check(pDX, ID_EDITOR_REPLACE_DLG_WRAPAROUND_CHECKBOX, m_bMatchwords);
	DDX_Check(pDX, ID_EDITOR_REPLACE_DLG_REGEX_CHECKBOX, m_bMacthregex);
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
	if (strSearchWhat.IsEmpty())
	{
		return;
	}

	UpdateSearchOptions();

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
	if (strSearchWhat.IsEmpty())
	{
		return;
	}

	UpdateSearchOptions();

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
			SaveReplaceString(strSearchWhat);
			int nPos = pActiveEditor->ReplaceNext(strSearchWhat, strReplaceWith);
			if (nPos == -1)
			{
				AfxMessageBox(_T("WORD NOT FOUND."), MB_ICONINFORMATION);
			}
		}
		else
		{
			AfxMessageBox(_T("Read only mode!"));
		}
	}
}

void CFindAndReplaceDlg::OnReplaceAll()
{
	if (ThreadWorkerMgr.IsRunning() || ThreadWorkerMgr.IsDebuggerRunning())
	{
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Replace Warning] Program/Debugger is running now, do not allow replacement in files..."), BasicColors::orange);
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
	std::vector<CString> listFailedReplaceFiles;

	auto startMeasure = OSUtils::StartBenchmark();

	unsigned int nSearchOptions = VinaTextSearchEngine::OPTIONS::INT_SEARCH_OPTION;
	if (m_bMatchwords)
		nSearchOptions |= VinaTextSearchEngine::OPTIONS::MATCH_WORD;
	if (m_bMatchcase)
		nSearchOptions |= VinaTextSearchEngine::OPTIONS::MATCH_CASE;
	if (m_bMacthregex)
		nSearchOptions |= VinaTextSearchEngine::OPTIONS::REGEX;

	if (strSearchWhat.IsEmpty())
	{
		return;
	}

	if (strSearchWhat.CompareNoCase(strReplaceWith) == 0)
	{
		nSearchOptions |= VinaTextSearchEngine::OPTIONS::MATCH_CASE;
	}

	long lVisualLine = -1;
	long lCurrentLine = -1;
	CEditorCtrl* pActiveEditor = NULL;
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		pActiveEditor = pDoc->GetEditorCtrl();
		if (pActiveEditor != NULL)
		{
			lVisualLine = pActiveEditor->GetFirstVisibleLine();
			lCurrentLine = pActiveEditor->GetCurrentLine();
		}
	}

	if (strReplaceScope == _T("Current File"))
	{
		if (pDoc)
		{
			if (pActiveEditor != NULL && !pActiveEditor->IsReadOnlyEditor())
			{
				auto selectionProfiler = OSUtils::StartBenchmark();
				SaveSearchString(strSearchWhat);
				SaveReplaceString(strReplaceWith);
				pActiveEditor->SetSearchflags(nSearchOptions);
				pActiveEditor->BeginUndoTransactions();
				int nCountReplaced = pActiveEditor->ReplaceAll(strSearchWhat, strReplaceWith);
				pActiveEditor->EndUndoTransactions();
				OSUtils::LogStopBenchmark(LOG_TARGET::MESSAGE_WINDOW, selectionProfiler, AfxCStringFormat(_T("> Replaced all %d occurrence(s) on current file - timelapse: "), nCountReplaced));
				return;
			}
			else
			{
				AfxMessageBox(_T("Read only mode!"));
				return;
			}
		}
	}
	else if (strReplaceScope == _T("All Open Files"))
	{
		BOOL bUserAnwser = AskBeforeContinueReplace(strReplaceScope);
		if (!bUserAnwser) return;

		auto vecDocs = AppUtils::GetAllDocuments();
		ResultSearchData._nTotalSearchFile = (unsigned int)vecDocs.size();
		SaveSearchString(strSearchWhat);
		SaveReplaceString(strReplaceWith);
		for (auto const& doc : vecDocs)
		{
			if (doc)
			{
				auto pDocEditor = dynamic_cast<CEditorDoc*>(doc);
				if (pDocEditor)
				{
					auto pEditor = pDocEditor->GetEditorCtrl();
					if (pEditor != NULL)
					{
						CString strFile = pDocEditor->GetPathName();

						if (pEditor->IsReadOnlyEditor())
						{
							listFailedReplaceFiles.push_back(strFile);
							continue;
						}

						CString strScript;
						pEditor->GetText(strScript);
						if (strScript.IsEmpty()) continue;

						pEditor->SetSearchflags(nSearchOptions);
						BOOL bHasTrailingReturn = FALSE;
						if (strScript.GetAt(strScript.GetLength() - 1) == _T('\r'))
						{
							bHasTrailingReturn = TRUE;
						}
						std::vector<CString> listLine;
						AppUtils::SplitCString(strScript, pEditor->GetEOLCString(), listLine);
						std::wstring inputfile = AppUtils::CStringToWStd(strFile);
						std::wstring replace_what = AppUtils::CStringToWStd(strSearchWhat);
						std::wstring replace_with = AppUtils::CStringToWStd(strReplaceWith);
						pEditor->BeginUndoTransactions();
						if (!PathFileExists(strFile))
						{
							CReplaceWorker::ReplaceInDocument(pDocEditor->GetTitle(), listLine, replace_what, replace_with, ResultSearchData._vecResultSearchInfo, ResultSearchData._nMatchedFiles,
								ResultSearchData._nMatchedWords, ResultSearchData._nLineCounts, nSearchOptions, pEditor, bHasTrailingReturn);
						}
						else
						{
							CReplaceWorker replacer;
							replacer.SetFileFilter(m_strFileFilter);
							if (replacer.CheckFileFilter(strFile))
							{
								CReplaceWorker::ReplaceInDocument(pDocEditor->GetPathName(), listLine, replace_what, replace_with, ResultSearchData._vecResultSearchInfo, ResultSearchData._nMatchedFiles,
									ResultSearchData._nMatchedWords, ResultSearchData._nLineCounts, nSearchOptions, pEditor, bHasTrailingReturn);
							}
						}
						pEditor->EndUndoTransactions();
					}
				}
			}
		}
	}
	else if (strReplaceScope == _T("Container Folder"))
	{
		if (pDoc)
		{
			CString strFilePath = pDoc->GetPathName();
			CString strContainerFoler = PathUtils::GetContainerPath(strFilePath);

			BOOL bUserAnwser = AskBeforeContinueReplace(strContainerFoler);
			if (!bUserAnwser) return;

			GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_ALL_BTN)->SetWindowTextW(_T("Stop"));
			GetDlgItem(ID_EDITOR_REPLACE_DLG_FINDNEXT_BTN)->EnableWindow(FALSE);
			GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_BTN)->EnableWindow(FALSE);

			SaveSearchString(strSearchWhat);
			SaveReplaceString(strReplaceWith);

			// background replace start...
			CString strMessageProgressbar;
			strMessageProgressbar.Format(_T("Replacing text..."));
			m_pReplaceProgressBar = std::make_unique<CVinaTextProgressBar>(0, 100, strMessageProgressbar, PROGRESS_BAR_TYPE::TYPE_SEARCH);
			m_pReplaceProgressBar->SetPos(0);
			std::unique_ptr<CReplaceWorker> pReplacer = std::make_unique<CReplaceWorker>();
			pReplacer->SetActiveDocument(pDoc);
			pReplacer->SetReplaceFolder(strContainerFoler);
			pReplacer->SetSearchWhat(strSearchWhat);
			pReplacer->SetReplaceWith(strReplaceWith);
			pReplacer->SetIncludeSubFolder(!m_bExcludeSubFolder);
			pReplacer->SetSearchOptions(nSearchOptions);
			pReplacer->SetFileFilter(m_strFileFilter);
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
					strMessageProgressbar.Format(_T("Searching text %d%% completed..."), nCurPos);
					m_pReplaceProgressBar->SetText(strMessageProgressbar);
				}
			}
			m_hThreadReplaceBackground = NULL;
			m_pReplaceProgressBar.reset();
			// update result to main thread...
			ResultSearchData = pReplacer->m_ResultReplaceData;
			listFailedReplaceFiles = pReplacer->m_listFailedReplaceFiles;

			GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_ALL_BTN)->SetWindowTextW(_T("Replace All"));
			GetDlgItem(ID_EDITOR_REPLACE_DLG_FINDNEXT_BTN)->EnableWindow(TRUE);
			GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_BTN)->EnableWindow(TRUE);

		}
	}
	else if (strReplaceScope == _T("Specific Path"))
	{
		if (m_strSpecificPath.IsEmpty()) return;
		if (PathFileExists(m_strSpecificPath))
		{
			if (!PathUtils::IsDirectory(m_strSpecificPath))
			{
				if (PathUtils::IsFileReadOnly(m_strSpecificPath))
				{
					AfxMessageBox(_T("This file has read only attribute!"));
					return;
				}
				CReplaceWorker replacer;
				replacer.SetFileFilter(m_strFileFilter);
				if (replacer.CheckFileFilter(m_strFileFilter))
				{
					ResultSearchData._nTotalSearchFile = 1;
					SaveSearchString(strSearchWhat);
					SaveReplaceString(strReplaceWith);
					std::wstring inputfile = AppUtils::CStringToWStd(m_strSpecificPath);
					std::wstring outputfile = AppUtils::CStringToWStd(m_strSpecificPath);
					std::wstring replace_what = AppUtils::CStringToWStd(strSearchWhat);
					std::wstring replace_with = AppUtils::CStringToWStd(strReplaceWith);
					CReplaceWorker::ReplaceInFilePath(inputfile, outputfile, replace_what, replace_with, ResultSearchData._vecResultSearchInfo, ResultSearchData._nMatchedFiles,
						ResultSearchData._nMatchedWords, ResultSearchData._nLineCounts, nSearchOptions);
				}
			}
			else
			{
				BOOL bUserAnwser = AskBeforeContinueReplace(m_strSpecificPath);
				if (!bUserAnwser) return;

				GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_ALL_BTN)->SetWindowTextW(_T("Stop"));
				GetDlgItem(ID_EDITOR_REPLACE_DLG_FINDNEXT_BTN)->EnableWindow(FALSE);
				GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_BTN)->EnableWindow(FALSE);

				SaveSearchString(strSearchWhat);
				SaveReplaceString(strReplaceWith);
				// background replace start...
				CString strMessageProgressbar;
				strMessageProgressbar.Format(_T("Replacing text..."));
				m_pReplaceProgressBar = std::make_unique<CVinaTextProgressBar>(0, 100, strMessageProgressbar, PROGRESS_BAR_TYPE::TYPE_SEARCH);
				m_pReplaceProgressBar->SetPos(0);
				std::unique_ptr<CReplaceWorker> pReplacer = std::make_unique<CReplaceWorker>();
				pReplacer->SetActiveDocument(pDoc);
				pReplacer->SetReplaceFolder(m_strSpecificPath);
				pReplacer->SetSearchWhat(strSearchWhat);
				pReplacer->SetReplaceWith(strReplaceWith);
				pReplacer->SetIncludeSubFolder(!m_bExcludeSubFolder);
				pReplacer->SetSearchOptions(nSearchOptions);
				pReplacer->SetFileFilter(m_strFileFilter);
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
						strMessageProgressbar.Format(_T("Replacing text %d%% Completed..."), nCurPos);
						m_pReplaceProgressBar->SetText(strMessageProgressbar);
					}
				}
				m_hThreadReplaceBackground = NULL;
				m_pReplaceProgressBar.reset();
				// update result to main thread...
				ResultSearchData = pReplacer->m_ResultReplaceData;
				listFailedReplaceFiles = pReplacer->m_listFailedReplaceFiles;

				GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_ALL_BTN)->SetWindowTextW(_T("Replace All"));
				GetDlgItem(ID_EDITOR_REPLACE_DLG_FINDNEXT_BTN)->EnableWindow(TRUE);
				GetDlgItem(ID_EDITOR_REPLACE_DLG_REPLACE_BTN)->EnableWindow(TRUE);
			}
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
	if (pDoc && pActiveEditor && lVisualLine != -1 && lCurrentLine != -1)
	{
		pActiveEditor->GotoLine(lCurrentLine);
		pActiveEditor->SetFirstVisibleLine(lVisualLine);
	}
	// log list failed file
	if (listFailedReplaceFiles.size() > 0)
	{
		CString strLog;
		AfxMessageBox(_T("[Warning] Replacement finished but some file(s) has read only attribute, please check Message Window for detail!"));
		for (auto const& path : listFailedReplaceFiles)
		{
			strLog += path + EDITOR_NEW_LINE_LF;
		}
		LOG_OUTPUT_MESSAGE_COLOR(_T("\n___________| REPLACE TEXT - READ ONLY FILE(S) |________________________________________\n"));
		LOG_OUTPUT_MESSAGE_COLOR(strLog);
	}
}

BOOL CFindAndReplaceDlg::OnEraseBkgnd(CDC * pDC)
{
	CRect rect;
	GetClientRect(&rect);
	CBrush myBrush(AppSettingMgr.m_ThemeColor);    
	CBrush *pOld = pDC->SelectObject(&myBrush);
	BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOld);  
	return bRes;
}

void CFindAndReplaceDlg::OnClickCheckBoxRegex()
{
	UpdateData(TRUE);
	if (m_bMacthregex)
	{
		GetDlgItem(ID_EDITOR_REPLACE_REGEX_COMBO)->EnableWindow(TRUE);
		OnCbnSelchangeRegexPattern();
	}
	else
	{
		GetDlgItem(ID_EDITOR_REPLACE_DLG_FINDWHAT_COMBO)->SetWindowTextW(_T(""));
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
		return CreateSolidBrush(AppSettingMgr.m_ThemeColor);
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
	CReplaceWorker* pReplacer = reinterpret_cast<CReplaceWorker*>(pParam);
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
	m_comboReplaceScope.AddString(_T("All Open Files"));
	m_comboReplaceScope.AddString(_T("Container Folder"));
	m_comboReplaceScope.AddString(_T("Specific Path"));
	//m_comboReplaceScope.AddString(_T("Current Project"));
	m_comboReplaceScope.SetCurSel(0);
}

void CFindAndReplaceDlg::InitComboRegexPattern()
{
	m_combRegexPattern.ResetContent();
	m_combRegexPattern.AddString(_T("Match any character one time"));
	m_combRegexPattern.AddString(_T("Match any character zero or more times (wildcard *)"));
	m_combRegexPattern.AddString(_T("Match any character one or more times (wildcard ?)"));
	m_combRegexPattern.AddString(_T("Match any single character in the set 'abc'"));
	m_combRegexPattern.AddString(_T("Match any single character not in the set 'abc'"));
	m_combRegexPattern.AddString(_T("Match any single character in range a to f"));
	m_combRegexPattern.AddString(_T("Match any word character"));
	m_combRegexPattern.AddString(_T("Match any decimal digit"));
	m_combRegexPattern.AddString(_T("Match any whitespace character"));
	m_combRegexPattern.AddString(_T("Match any character zero or one time"));
	m_combRegexPattern.AddString(_T("Match any character zero or more times"));
	m_combRegexPattern.AddString(_T("Match any character one or more times"));
	m_combRegexPattern.AddString(_T("Match three consecutive decimal digits"));
	m_combRegexPattern.AddString(_T("Match at beginning or end of word"));
	m_combRegexPattern.AddString(_T("Match at beginning of line"));
	m_combRegexPattern.AddString(_T("Match a line break"));
	m_combRegexPattern.AddString(_T("Match at end of line"));
	m_combRegexPattern.AddString(_T("Capture and impicitily number the subexpression 'dog|cat'"));
	m_combRegexPattern.AddString(_T("Backreference the first captured subexpression"));
	m_combRegexPattern.AddString(_T("Capture subexpression 'dog|cat' and name it 'pet'"));
	m_combRegexPattern.AddString(_T("Backreference the captured subexpression named 'pet'"));
	m_combRegexPattern.AddString(_T("Space or Tab"));
	m_combRegexPattern.AddString(_T("Match any numeric character"));
	m_combRegexPattern.AddString(_T("C/C++ identifier"));
	m_combRegexPattern.AddString(_T("Quoted string"));
	m_combRegexPattern.AddString(_T("Match a hexadecimal number"));
	m_combRegexPattern.AddString(_T("Match integer and decimals"));
	m_combRegexPattern.SetCurSel(0);
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

	UpdateData(FALSE);
}

void CFindAndReplaceDlg::OnCbnSelchangeRegexPattern()
{
	int iSel = m_combRegexPattern.GetCurSel();
	if (iSel == 0)
	{
		m_comboSearchWhat.SetWindowTextW(_T("."));
	}
	else if (iSel == 1)
	{
		m_comboSearchWhat.SetWindowTextW(_T(".*"));
	}
	else if (iSel == 2)
	{
		m_comboSearchWhat.SetWindowTextW(_T(".+"));
	}
	else if (iSel == 3)
	{
		m_comboSearchWhat.SetWindowTextW(_T("[abc]"));
	}
	else if (iSel == 4)
	{
		m_comboSearchWhat.SetWindowTextW(_T("^[abc]"));
	}
	else if (iSel == 5)
	{
		m_comboSearchWhat.SetWindowTextW(_T("[a-f]"));
	}
	else if (iSel == 6)
	{
		m_comboSearchWhat.SetWindowTextW(_T("\\w"));
	}
	else if (iSel == 7)
	{
		m_comboSearchWhat.SetWindowTextW(_T("\\d"));
	}
	else if (iSel == 8)
	{
		m_comboSearchWhat.SetWindowTextW(_T("[^\\S\\r\\n]"));
	}
	else if (iSel == 9)
	{
		m_comboSearchWhat.SetWindowTextW(_T("be?"));
	}
	else if (iSel == 10)
	{
		m_comboSearchWhat.SetWindowTextW(_T("be*"));
	}
	else if (iSel == 11)
	{
		m_comboSearchWhat.SetWindowTextW(_T("be+"));
	}
	else if (iSel == 12)
	{
		m_comboSearchWhat.SetWindowTextW(_T("\\d{3}"));
	}
	else if (iSel == 13)
	{
		m_comboSearchWhat.SetWindowTextW(_T("\\b"));
	}
	else if (iSel == 14)
	{
		m_comboSearchWhat.SetWindowTextW(_T("^"));
	}
	else if (iSel == 15)
	{
		m_comboSearchWhat.SetWindowTextW(_T("\\r?\\n"));
	}
	else if (iSel == 16)
	{
		m_comboSearchWhat.SetWindowTextW(_T("(?=\r?$)"));
	}
	else if (iSel == 17)
	{
		m_comboSearchWhat.SetWindowTextW(_T("(dog|cat)"));
	}
	else if (iSel == 18)
	{
		m_comboSearchWhat.SetWindowTextW(_T("\\1"));
	}
	else if (iSel == 19)
	{
		m_comboSearchWhat.SetWindowTextW(_T("(?<pet>dog|cat)"));
	}
	else if (iSel == 20)
	{
		m_comboSearchWhat.SetWindowTextW(_T("\\k<pet>"));
	}
	else if (iSel == 21)
	{
		m_comboSearchWhat.SetWindowTextW(_T("[\\t]"));
	}
	else if (iSel == 22)
	{
		m_comboSearchWhat.SetWindowTextW(_T("\\d"));
	}
	else if (iSel == 23)
	{
		m_comboSearchWhat.SetWindowTextW(_T("\\b(_\\w+|[\\w-[0-9_]]\\w*)\\b"));
	}
	else if (iSel == 24)
	{
		m_comboSearchWhat.SetWindowTextW(_T("((\\\".+?\\\")|('.+?'))"));
	}
	else if (iSel == 25)
	{
		m_comboSearchWhat.SetWindowTextW(_T("\\b(_\\w+|[\\w-[0-9_]]\\w*)\\b"));
	}
	else if (iSel == 26)
	{
		m_comboSearchWhat.SetWindowTextW(_T("\\b[0-9]*\\.*[0-9]+\\b"));
	}
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
}

void CFindAndReplaceDlg::UpdateSearchOptions()
{
	UpdateData(TRUE);
	m_nSearchOptions = 0;
	if (m_bMatchwords)
		m_nSearchOptions |= SCFIND_WHOLEWORD;
	if (m_bMatchcase)
		m_nSearchOptions |= SCFIND_MATCHCASE;
	if (m_bMacthregex)
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

SycnFindReplaceSettings CFindAndReplaceDlg::GetSycnFindReplaceSettings()
{
	UpdateData(TRUE);
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	SycnFindReplaceSettings dataSync;
	dataSync._strSearchWhat = strSearchWhat;
	dataSync._strSpecificPath = m_strSpecificPath;
	dataSync._bAppendResult = m_bAppendResult;
	dataSync._bExcludeSubFolder = m_bExcludeSubFolder;
	dataSync._bMacthregex = m_bMacthregex;
	dataSync._bMatchcase = m_bMatchcase;
	dataSync._bMatchwords = m_bMatchwords;
	dataSync._bShowFileNameOnly = m_bShowFileNameOnly;
	dataSync._strFileFilter = m_strFileFilter;
	dataSync._nRegexPattern = m_combRegexPattern.GetCurSel();
	dataSync._nSearchScope = m_comboReplaceScope.GetCurSel();
	return dataSync;
}

void CFindAndReplaceDlg::SyncSearchReplaceSettings(const SycnFindReplaceSettings & settings)
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
	m_bMacthregex = settings._bMacthregex;
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
}

BOOL CFindAndReplaceDlg::AskBeforeContinueReplace(const CString& strWhereToReplace)
{
	if (!AppSettingMgr.m_bAskBeforeReplaceInFiles) return TRUE;
	CString strMsg;
	strMsg.Format(_T("[Caution] Application will replace text of file(s) in [%s], do you want to continue?"), strWhereToReplace);
	if (IDYES == AfxMessageBox(strMsg, MB_YESNO | MB_ICONWARNING))
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
		CEditorView* pView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
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