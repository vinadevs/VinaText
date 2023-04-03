/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "VinaTextApp.h"
#include "SearchNavigatePathDlg.h"
#include "afxdialogex.h"
#include "AppUtil.h"
#include "MainFrm.h"
#include "AppSettings.h"
#include "TreeHelper.h"
#include "FindPathWorker.h"
#include "VinaTextProgressBar.h"
#include "translator/POHandler.h"

// CSearchNavigatePathDlg dialog

IMPLEMENT_DYNAMIC(CSearchNavigatePathDlg, CDlgBase)

CSearchNavigatePathDlg::CSearchNavigatePathDlg(const CString& strFolder, CWnd* pParent /*=NULL*/)
	: CDlgBase(IDD_DIALOG_SEARCH_FILE, pParent)
{
	m_strFolder = strFolder;
	m_bMatchCase = FALSE;
	m_bSearchFileOnly = FALSE;
	m_bAddResultToEditor = FALSE;
	m_bAddResultToDockWindow = TRUE;
	m_bSearchWithSize = FALSE;
	m_bSearchWitheModifiedDate = FALSE;
	m_bSearchWitheCreatedDate = FALSE;
	m_bSearchInSubdirectory = TRUE;
	m_bSearchWithoutMatchName = FALSE;
	m_dMinFileSize = 0.0;
	m_dMaxFileSize = FILE_SIZE_LIMITATION;
	m_nRelaceResult = 0;
}

CSearchNavigatePathDlg::~CSearchNavigatePathDlg()
{
}

void CSearchNavigatePathDlg::SetSearchFolder(const CString & strFolder)
{
	m_strFolder = strFolder;
	UpdateData(FALSE);
}

void CSearchNavigatePathDlg::SetForcusOnEditFileName()
{
	m_EditUndoRedo.SetFocus();
}

void CSearchNavigatePathDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILE_NAME, m_EditUndoRedo);
	DDX_Control(pDX, IDC_EDIT_SEARCH_ON_PATH, m_EditFilePath);
	DDX_Control(pDX, IDC_EDIT_PATH_FILTER, m_EditUndoRedo2);
	DDX_Text(pDX, IDC_EDIT_SEARCH_ON_PATH, m_strFolder);
	DDX_Check(pDX, IDC_CHECK_SERACH_FILE_MATCH_CASE, m_bMatchCase);
	DDX_Check(pDX, IDC_CHECK_SERACH_FILE_ONLY, m_bSearchFileOnly);
	DDX_Check(pDX, IDC_CHECK_SERACH_FILE_ADD_TO_EDITOR, m_bAddResultToEditor);
	DDX_Check(pDX, IDC_CHECK_SERACH_IN_SUBDIRECTORY, m_bSearchInSubdirectory);
	DDX_Check(pDX, IDC_CHECK_SERACH_FILE_SIZE, m_bSearchWithSize);
	DDX_Check(pDX, IDC_CHECK_DATE_MODIFIED_BETWEEN, m_bSearchWitheModifiedDate);
	DDX_Check(pDX, IDC_CHECK_DATE_CREATED_BETWEEN, m_bSearchWitheCreatedDate);
	DDX_Check(pDX, IDC_CHECK_SEARCH_WITHOUT_MATCH_NAME, m_bSearchWithoutMatchName);
	DDX_Text(pDX, IDC_EDIT_MIN_FILE_SIZE, m_dMinFileSize);
	DDX_Text(pDX, IDC_EDIT_MAX_FILE_SIZE, m_dMaxFileSize);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START, m_StartModifiedDatePicker);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, m_EndModifiedDatePicker);
	DDX_Check(pDX, IDC_CHECK_ADD_TO_SEARCH_FILE_RESULT_WINDOW, m_bAddResultToDockWindow);
	DDX_Radio(pDX, IDC_RADIO_SEARCH_RESULT_REPLACE, m_nRelaceResult);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START_CREATED, m_StartCreatedDatePicker);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END_CREATED, m_EndCreatedDatePicker);
}

BOOL CSearchNavigatePathDlg::OnInitDialog()
{
	m_strDlgCaption = _T("Search/Navigate Path");

	CDlgBase::OnInitDialog();

	// dialog translation
	//SetDlgItemText(IDC_CHECK_ADD_TO_EDITOR, Native_Language("Add Result To New Editor"));

	// enable the browse button and put the control in file browse mode
	m_EditFilePath.EnableFolderBrowseButton();
	m_EditFilePath.SetCueBanner(_T("Search path..."));
	m_EditUndoRedo.SetCueBanner(_T("Search name..."));
	m_EditUndoRedo2.SetWindowText(_T("*.*;"));

	OnBnClickedCheckSerachFileSize();
	OnBnClickedCheckDateCreatedBetween();
	OnBnClickedCheckDateModifiedBetween();

	::DragAcceptFiles(m_hWnd, TRUE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSearchNavigatePathDlg::PostNcDestroy()
{
	/*Close & Delete a modeless Dialogs.
	A proper Way is : Override PostNcDestroy, OnOk() and OnCancel() for the Modeless Dialogs*/
	CDlgBase::PostNcDestroy();
	delete this;
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;
	pFrame->GetFileExplorerCtrl().ReleaseSearchFileDlg();
}

void CSearchNavigatePathDlg::OnCancel()
{
	if (m_hThreadFindBackground) // if find background is running, allow to stop thread...
	{
		DWORD dwExitCode = 0;
		if (::GetExitCodeThread(m_hThreadFindBackground, &dwExitCode))
		{
			if (dwExitCode == STILL_ACTIVE)
			{
				dwExitCode = 0;
				::TerminateThread(m_hThreadFindBackground, dwExitCode);
				m_hThreadFindBackground = NULL;
			}
		}
		GetDlgItem(IDC_BUTTON_SEARCH_PATH_NEXT_MATCH)->EnableWindow(TRUE);
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		m_pFindProgressBar.reset();
		return;
	}
	CDlgBase::DestroyWindow();
}

BOOL CSearchNavigatePathDlg::PreTranslateMessage(MSG * pMsg)
{
	switch (pMsg->message)
	{
		case WM_KEYDOWN:
		{
			switch (pMsg->wParam)
			{
			case VK_RETURN:
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000))
				{
					CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
					ASSERT(pFrame);
					if (pFrame)
					{
						pFrame->GetFileExplorerCtrl().OpenSelectedPath();
						m_EditUndoRedo.SetFocus();
					}
					return TRUE;
				}
				break;
			}
			case 'Q':
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
				{
					CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
					ASSERT(pFrame);
					if (pFrame)
					{
						pFrame->GetFileExplorerCtrl().SetFocus();
					}
					return TRUE;
				}
				break;
			}
			break;
			}
		}
	}
	return CDlgBase::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CSearchNavigatePathDlg, CDlgBase)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDOK, &CSearchNavigatePathDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_FILE_NAME, &CSearchNavigatePathDlg::OnEnChangeEditSearchName)
	ON_EN_CHANGE(IDC_EDIT_PATH_FILTER, &CSearchNavigatePathDlg::OnEnChangeEditFilter)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_PATH_NEXT_MATCH, &CSearchNavigatePathDlg::OnBnClickedButtonSearchPathNextMatch)
	ON_BN_CLICKED(IDC_CHECK_SERACH_FILE_SIZE, &CSearchNavigatePathDlg::OnBnClickedCheckSerachFileSize)
	ON_BN_CLICKED(IDC_CHECK_DATE_CREATED_BETWEEN, &CSearchNavigatePathDlg::OnBnClickedCheckDateCreatedBetween)
	ON_BN_CLICKED(IDC_CHECK_DATE_MODIFIED_BETWEEN, &CSearchNavigatePathDlg::OnBnClickedCheckDateModifiedBetween)
	ON_BN_CLICKED(IDC_CHECK_SEARCH_WITHOUT_MATCH_NAME, &CSearchNavigatePathDlg::OnBnClickedCheckSearchAllPath)
END_MESSAGE_MAP()

// CSearchNavigatePathDlg message handlers

UINT CSearchNavigatePathDlg::FindBackgroundThreadProc(LPVOID pParam)
{
	CFindPathWorker* pFinder = reinterpret_cast<CFindPathWorker*>(pParam);
	if (pFinder == NULL)
	{
		return 1;
	}
	pFinder->FindPathWithCondition();
	return 0; // thread completed successfully
}

void CSearchNavigatePathDlg::OnBnClickedOk()
{
	UpdateData();

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;

	// TODO: Add your control notification handler code here
	CString strSearchTarget;
	GetDlgItem(IDC_EDIT_FILE_NAME)->GetWindowTextW(strSearchTarget);
	int nIndex = strSearchTarget.ReverseFind(':'); // after : search target will reset
	if (nIndex != -1)
	{
		strSearchTarget = strSearchTarget.Right(strSearchTarget.GetLength() - nIndex - 1).Trim();
		if (strSearchTarget.IsEmpty())
		{
			AfxMessageBox(_T("[Search Error] After character [:], search target will reset!"));
			return;
		}
	}

	if (PathFileExists(m_strFolder) && !strSearchTarget.IsEmpty() || m_bSearchWithoutMatchName)
	{
		GetDlgItem(IDC_BUTTON_SEARCH_PATH_NEXT_MATCH)->EnableWindow(FALSE);
		GetDlgItem(IDOK)->EnableWindow(FALSE);

		BOOL bAppendResult;
		if (m_nRelaceResult == 0)
		{
			bAppendResult = FALSE;
			pFrame->ClearDataOnDockPane(DOCKABLE_PANE_TYPE::PATH_RESULT_PANE);
		}
		else
		{
			bAppendResult = TRUE;
		}

		CString strSearchFilter;
		GetDlgItem(IDC_EDIT_PATH_FILTER)->GetWindowTextW(strSearchFilter);

		auto startMeasureTime = OSUtils::StartBenchmark();
		
		CTime StartModifiedDate, EndModifiedDate, StartCreatedDate, EndCreatedDate;
		if (m_bSearchWitheModifiedDate)
		{
			m_StartModifiedDatePicker.GetTime(StartModifiedDate);
			m_EndModifiedDatePicker.GetTime(EndModifiedDate);
		}
		if (m_bSearchWitheCreatedDate)
		{
			m_StartCreatedDatePicker.GetTime(StartCreatedDate);
			m_EndCreatedDatePicker.GetTime(EndCreatedDate);
		}

		// background search start...
		CString strMessageProgressbar; strMessageProgressbar.Format(_T("Searching path..."));
		m_pFindProgressBar = std::make_unique<CVinaTextProgressBar>(0, 100, strMessageProgressbar, PROGRESS_BAR_TYPE::TYPE_SEARCH);
		m_pFindProgressBar->SetPos(0);

		std::unique_ptr<CFindPathWorker> pFinder = std::make_unique<CFindPathWorker>(m_strFolder,
			strSearchTarget,
			strSearchFilter,
			m_bMatchCase,
			m_bSearchFileOnly
			, m_bSearchWithSize,
			m_bSearchWitheModifiedDate,
			m_bSearchWitheCreatedDate,
			m_bSearchInSubdirectory,
			m_bSearchWithoutMatchName,
			m_dMinFileSize,
			m_dMaxFileSize,
			StartModifiedDate,
			EndModifiedDate,
			StartCreatedDate,
			EndCreatedDate);

		DWORD dwExitCode = 0;
		CWinThread* pThread = ::AfxBeginThread(FindBackgroundThreadProc, (LPVOID)pFinder.get(), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED | THREAD_TERMINATE, NULL);
		if (pThread)
		{
			m_hThreadFindBackground = pThread->m_hThread;
			pThread->m_bAutoDelete = TRUE;
			pThread->ResumeThread();
		}
		while (TRUE)
		{
			if (!::GetExitCodeThread(m_hThreadFindBackground, &dwExitCode))
			{
				break;
			}
			if (dwExitCode != STILL_ACTIVE)
			{
				break;
			}
			USE_THREAD_PUMP_UI;
			if (m_pFindProgressBar && pFinder)
			{
				int nCurPos = pFinder->GetCurrentFindProgress();
				m_pFindProgressBar->SetPos(nCurPos);
				CString strMessageProgressbar;
				strMessageProgressbar.Format(_T("Searching path %d%% completed..."), nCurPos);
				m_pFindProgressBar->SetText(strMessageProgressbar);
			}
		}
		m_hThreadFindBackground = NULL;
		m_pFindProgressBar.reset();
		GetDlgItem(IDC_BUTTON_SEARCH_PATH_NEXT_MATCH)->EnableWindow(TRUE);
		GetDlgItem(IDOK)->EnableWindow(TRUE);

		// update result to main thread...
		if (m_bAddResultToDockWindow) // send data to dock window
		{
			pFrame->AddPathResultDataToPane(pFinder->m_pathResultDataList, strSearchTarget, pFinder->m_nTotalSearch, OSUtils::StopBenchmark(startMeasureTime), bAppendResult, m_bSearchWithoutMatchName);
		}

		if (m_bAddResultToEditor) // send data to editor window
		{
			CString strResultSearch;
			for (int nItem = 0; nItem < pFinder->m_pathResultDataList.size(); nItem++)
			{
				strResultSearch += pFinder->m_pathResultDataList[nItem]._strPathName + _T(" | ") 
								+ pFinder->m_pathResultDataList[nItem]._strLocation + _T(" | ")
								+ pFinder->m_pathResultDataList[nItem]._strPathType + _T(" | ")
								+ pFinder->m_pathResultDataList[nItem]._strPathSize + _T(" | ")
								+ pFinder->m_pathResultDataList[nItem]._strReadOnly + _T(" | ")
								+ pFinder->m_pathResultDataList[nItem]._strPathCreatedTime + _T(" | ")
								+ pFinder->m_pathResultDataList[nItem]._strPathModifiedTime + EDITOR_NEW_LINE;
			}
			AppUtils::CreateNewEditorWithText(_T("Search Path Result"), strResultSearch);
		}

	}
	else
	{
		AfxMessageBox(_T("[Search Error] Invalid search name!"));
	}
}

void CSearchNavigatePathDlg::OnEnChangeEditSearchName()
{
	if (AppSettingMgr.m_bEnablePathNavigation)
	{
		CString strSearchWhat;
		m_EditUndoRedo.GetWindowText(strSearchWhat);
		CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
		ASSERT(pFrame);
		if (!pFrame) return;
		if (strSearchWhat.IsEmpty())
		{
			pFrame->RevealInExplorerWindow(m_strFolder);
			m_ListPathIgnore.clear();
		}
		else
		{
			int nIndex = strSearchWhat.ReverseFind(':'); // after : search target will reset
			if (nIndex != -1)
			{
				strSearchWhat = strSearchWhat.Right(strSearchWhat.GetLength() - nIndex - 1).Trim();
				if (strSearchWhat.IsEmpty())
				{
					m_ListPathIgnore.clear();
					return;
				}
			}
			CString strMatchedPath = pFrame->GetFileExplorerCtrl().GetPathNavigation(strSearchWhat.MakeLower());
			pFrame->RevealInExplorerWindow(strMatchedPath);
			if (PathFileExists(strMatchedPath))
			{
				m_ListPathIgnore.push_back(strMatchedPath);
			}
		}
		m_EditUndoRedo.SetFocus();
	}
}

void CSearchNavigatePathDlg::OnEnChangeEditFilter()
{
	CString strSearchFilter;
	m_EditUndoRedo2.GetWindowText(strSearchFilter);
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;
	if (strSearchFilter.IsEmpty())
	{
		m_EditUndoRedo2.SetWindowText(_T("*.*;"));
		m_EditUndoRedo2.SetFocusEx();
	}
}

void CSearchNavigatePathDlg::OnBnClickedButtonSearchPathNextMatch()
{
	// TODO: Add your control notification handler code here
	CString strSearchWhat;
	m_EditUndoRedo.GetWindowText(strSearchWhat);
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;
	if (PathFileExists(m_strFolder) && !strSearchWhat.IsEmpty() || m_bSearchWithoutMatchName)
	{
		int nIndex = strSearchWhat.ReverseFind(':'); // after : search target will reset
		if (nIndex != -1)
		{
			strSearchWhat = strSearchWhat.Right(strSearchWhat.GetLength() - nIndex - 1).Trim();
			if (strSearchWhat.IsEmpty())
			{
				m_ListPathIgnore.clear();
				return;
			}
		}
		CString strMatchedPath = pFrame->GetFileExplorerCtrl().GetPathNavigationIgnore(strSearchWhat.MakeLower(), m_ListPathIgnore);
		if (PathFileExists(strMatchedPath))
		{
			if (pFrame->GetFileExplorerCtrl().GetSelectedPath() == strMatchedPath)
			{
				if (m_ListPathIgnore.empty())
				{
					m_ListPathIgnore.push_back(strMatchedPath);
				}
				strMatchedPath = pFrame->GetFileExplorerCtrl().GetPathNavigationIgnore(strSearchWhat.MakeLower(), m_ListPathIgnore);
				pFrame->RevealInExplorerWindow(strMatchedPath);
				m_ListPathIgnore.push_back(strMatchedPath);
			}
			else
			{
				pFrame->RevealInExplorerWindow(strMatchedPath);
				m_ListPathIgnore.push_back(strMatchedPath);
			}
		}
		else
		{
			if (!m_ListPathIgnore.empty())
			{
				for (auto const& path : m_ListPathIgnore)
				{
					CString strTempPath = path;
					if (PathUtils::GetLastLevelPath(strTempPath).MakeLower().Find(strSearchWhat.MakeLower()) != -1)
					{
						pFrame->RevealInExplorerWindow(path);
						break;
					}
				}
				m_ListPathIgnore.clear();
			}
		}
	}
	else
	{
		AfxMessageBox(_T("[Search Error] Invalid search name!"));
	}
	m_EditUndoRedo.SetFocus();
}

void CSearchNavigatePathDlg::OnBnClickedCheckSerachFileSize()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_bSearchWithSize)
	{
		GetDlgItem(IDC_EDIT_MIN_FILE_SIZE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MAX_FILE_SIZE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_MIN_FILE_SIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MAX_FILE_SIZE)->EnableWindow(FALSE);
	}
}


void CSearchNavigatePathDlg::OnBnClickedCheckDateCreatedBetween()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_bSearchWitheCreatedDate)
	{
		GetDlgItem(IDC_DATETIMEPICKER_START_CREATED)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_END_CREATED)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_DATETIMEPICKER_START_CREATED)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_END_CREATED)->EnableWindow(FALSE);
	}
}


void CSearchNavigatePathDlg::OnBnClickedCheckDateModifiedBetween()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_bSearchWitheModifiedDate)
	{
		GetDlgItem(IDC_DATETIMEPICKER_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_END)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_DATETIMEPICKER_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_END)->EnableWindow(FALSE);
	}
}

void CSearchNavigatePathDlg::OnBnClickedCheckSearchAllPath()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_bSearchWithoutMatchName)
	{
		GetDlgItem(IDC_EDIT_FILE_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_SERACH_FILE_MATCH_CASE)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_FILE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_SERACH_FILE_MATCH_CASE)->EnableWindow(TRUE);
	}
}

void CSearchNavigatePathDlg::OnDropFiles(HDROP hDropInfo)
{
	CDlgBase::OnDropFiles(hDropInfo);
	int nCntFiles = DragQueryFile(hDropInfo, -1, 0, 0);
	if (nCntFiles == 1)
	{
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_SEARCH_ON_PATH);
		if (pEdit)
		{
			TCHAR szPath[_MAX_PATH];
			szPath[0] = 0;
			::DragQueryFile(hDropInfo, 0, szPath, _MAX_PATH);
			if (PathUtils::IsDirectory(szPath))
			{
				pEdit->SetWindowTextW(szPath);
			}
			else
			{
				pEdit->SetWindowTextW(PathUtils::GetContainerPath(szPath));
			}
		}
	}
	DragFinish(hDropInfo);
}