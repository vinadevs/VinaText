/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "VinaTextApp.h"
#include "MainFrm.h"
#include "HostDoc.h"
#include "HostView.h"
#include "AppUtil.h"
#include "AppSettings.h"

using namespace HostManager;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CHostView

IMPLEMENT_DYNCREATE(CHostView, CView)

CHostView::~CHostView()
{
	TerminateHostProcess();
}

BEGIN_MESSAGE_MAP(CHostView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnDisableUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnDisableUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnDisableUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnDisableUpdate)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHostView diagnostics

#ifdef _DEBUG
void CHostView::AssertValid() const
{
	CView::AssertValid();
}

void CHostView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHostView message handlers

namespace
{
	int CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
	{
		return reinterpret_cast<CHostView*>(lParam)->CheckThreadID(hwnd);
	}
}

void CHostView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CString strAppPathToHost = AppUtils::GetVinaTextApp()->m_STHostAppInfo.m_strAppPathToHost;
	CString strAppArguments = AppUtils::GetVinaTextApp()->m_STHostAppInfo.m_strAppArguments;
	CString strAppName = AppUtils::GetVinaTextApp()->m_STHostAppInfo.m_strAppName;
	CString strClassAppName = AppUtils::GetVinaTextApp()->m_STHostAppInfo.m_strClassAppName;
	BOOL bRemoveTitleBarWindow = AppUtils::GetVinaTextApp()->m_STHostAppInfo.m_bRemoveTitleBarWindow;
	BOOL bSilentStartup = AppUtils::GetVinaTextApp()->m_STHostAppInfo.m_bSilentStartup;
	BOOL bOpenFileMode = AppUtils::GetVinaTextApp()->m_STHostAppInfo.m_bOpenFileMode;
	int nAppIconID = AppUtils::GetVinaTextApp()->m_STHostAppInfo.m_nAppIconID;
	int nWaitTime = AppUtils::GetVinaTextApp()->m_STHostAppInfo.m_nWaitTime;
	HOST_METHOD HostMethod = AppUtils::GetVinaTextApp()->m_STHostAppInfo.m_HostMethod;
	if (!strAppPathToHost.IsEmpty() && !strAppName.IsEmpty())
	{
		m_pDocument->SetTitle(strAppName);
		if (nAppIconID != -1)
		{
			HICON hIcon = AfxGetApp()->LoadIcon(nAppIconID);
			this->GetParentFrame()->SetIcon(hIcon, FALSE);
		}
		m_hJob = CreateWin32ProcessJob(strAppName + OSUtils::GetGUIDGlobal()); // job name must be unique!
		m_hProcess = CreateWin32ProcessWithHWND(strAppPathToHost, strAppArguments, bOpenFileMode, nWaitTime, bSilentStartup, HostMethod, strClassAppName); // Start child application
		if (m_hWWND != NULL && ::SetParent(m_hWWND, this->m_hWnd)) // check for child app window handle and set parent of child app to CHostView
		{
			if (bRemoveTitleBarWindow)
			{
				SetWindowLong(m_hWWND, GWL_STYLE, WS_VISIBLE); // eraze title of child app window.
			}
			AppUtils::GetVinaTextApp()->m_hLatestHostWND = m_hWWND; // for global control
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Host Application] Create host document for %s successfuly..."), strAppName);
		}
		else // no child window for our process
		{
			AfxMessageBoxFormat(MB_ICONWARNING, _T("[Host Error] Create host document for %s failed. Please check if this application was installed on your PC!"), strAppName);
		}
	}
	else
	{
		AfxMessageBoxFormat(MB_ICONWARNING, _T("[Host Error] Can not start %s!"), strAppName);
	}
}

HANDLE CHostView::CreateWin32ProcessWithHWND(const CString& strAppPathToHost, const CString& strAppArguments, BOOL bOpenFileMode, int nWaitTime, BOOL bSilentStartup, HOST_METHOD HostMethod, const CString& strClassName)
{
	// the second parameter of CreateProcess should point to writable memory else it will raise access violation
	CString strCMD;
	if (bOpenFileMode)
	{
		strCMD = ESCAPSE_STRING_WITH_QUOTE(strAppPathToHost) + CSTRING_SPACE + ESCAPSE_STRING_WITH_QUOTE(strAppArguments);
	}
	else
	{
		strCMD = ESCAPSE_STRING_WITH_QUOTE(strAppPathToHost) + CSTRING_SPACE + strAppArguments;
	}
	PROCESS_INFORMATION processInfo;
	STARTUPINFO startupInfo;
	::ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(STARTUPINFO);
	startupInfo.lpReserved = NULL;
	startupInfo.lpReserved2 = NULL;
	startupInfo.cbReserved2 = 0;
	startupInfo.lpDesktop = NULL;
	startupInfo.lpTitle = NULL;
	startupInfo.dwFlags = STARTF_USESHOWWINDOW;
	startupInfo.dwX = 0;
	startupInfo.dwY = 0;
	startupInfo.dwFillAttribute = 0;
	if (bSilentStartup)
	{
		startupInfo.wShowWindow = SW_HIDE;
	}
	else
	{
		startupInfo.wShowWindow = SW_SHOWMAXIMIZED;
	}

	LPTSTR szCmdline = strCMD.GetBuffer(strCMD.GetLength() + 1);
	if (::CreateProcessW(NULL, (LPTSTR)szCmdline,
	NULL,  // process security
	NULL,  // thread security
	FALSE, // no inheritance
	0,     // no startup flags
	NULL,  // no special environment
	NULL,  // default startup directory
	&startupInfo,
	&processInfo))
	strCMD.ReleaseBuffer();
	{
		if (m_hJob)
		{
			if (!AssignProcessToJobObject(m_hJob, processInfo.hProcess))
			{
				LOG_OUTPUT_MESSAGE_COLOR(_T("[Host Error] Assign application process to host job failed!"));
				return NULL;
			}
		}
		Sleep(nWaitTime);
		if (HostMethod == HOST_METHOD::USE_ENUMWINDOWS)
		{
			m_dwThreadId = processInfo.dwThreadId;
			::EnumWindows(&EnumWindowsProc, reinterpret_cast<LPARAM>(this)); // Iterate all windows to look up host application
		}
		else if (HostMethod == HOST_METHOD::USE_FINDWINDOWS)
		{
			m_hWWND = ::FindWindow(strClassName, NULL); // Find window normal
		}
		else if (HostMethod == HOST_METHOD::USE_FOREGROUNDWINDOWS)
		{
			m_hWWND = ::GetForegroundWindow(); // Top most window is our target!
		}
	}
	return processInfo.hProcess;
}

HANDLE CHostView::CreateWin32ProcessJob(const CString & strJobName)
{
	HANDLE hJob = CreateJobObject(NULL, strJobName); // important, all child processes need to be grouped!!
	if (hJob == NULL)
	{
		AfxMessageBoxFormat(MB_ICONWARNING, _T("[Host Error] Create application process job for %s failed!"), strJobName);
		return NULL;
	}
	else
	{
		JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli;
		memset(&jeli, 0, sizeof(JOBOBJECT_EXTENDED_LIMIT_INFORMATION));
		memset(&jeli.BasicLimitInformation, 0, sizeof(JOBOBJECT_BASIC_LIMIT_INFORMATION));
		// Configure all child processes associated with the job to terminate when the main process terminated.
		jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
		if (!SetInformationJobObject(hJob, JobObjectExtendedLimitInformation, &jeli, sizeof(jeli)))
		{
			AfxMessageBox(_T("[Host Error] Set information application job object failed!"));
		}
	}
	return hJob;
}

int CHostView::CheckThreadID(HWND hwnd)
{
	DWORD pID;
	DWORD threadID = GetWindowThreadProcessId(hwnd, &pID); //get process id
	if (threadID == m_dwThreadId)
	{
		m_hWWND = hwnd; // hwnd is the window handle
		return 0;
	}
	return 1;
}

void CHostView::TerminateHostProcess()
{
	if (!TerminateJobObject(m_hJob, EXIT_CODE_TERMINATE))
	{
		AfxMessageBox(_T("[Host Error] Terminate application job object failed, please try to kill it from Task Manager!"));
	}
	TerminateProcess(m_hProcess, EXIT_CODE_TERMINATE);
	DELETE_WIN32_HANDLE(m_hProcess);
	DELETE_WIN32_HWND(m_hWWND);
}

void CHostView::OnDraw(CDC * pDC)
{
	// draw background
	CRect rect; GetClientRect(rect);
	HBRUSH hBrush = ::CreateSolidBrush(AppSettingMgr.m_AppThemeColor);
	::FillRect(pDC->m_hDC, rect, hBrush);
	DeleteObject(hBrush);
}

int CHostView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void CHostView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if (m_hWWND)
	{
		::MoveWindow(m_hWWND, 0, 0, cx, cy, TRUE);
	}
}

void CHostView::OnDisableUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(FALSE);
}