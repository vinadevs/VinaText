/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "MultiThreadWorker.h"
#include "AppSettings.h"
#include "MainFrm.h"

#define BUFFER_SIZE_OUTPUT 16384

/* Current process */
static HANDLE g_hProcess = NULL;
/* Child process's STDIN is the user input or data that you enter into the child process - READ */
static HANDLE g_hChildStd_IN_Rd = NULL;
/* Child process's STDIN is the user input or data that you enter into the child process - WRITE */
static HANDLE g_hChildStd_IN_Wr = NULL;
/* Child process's STDOUT is the program output or data that child process returns - READ */
static HANDLE g_hChildStd_OUT_Rd = NULL;
/* Child process's STDOUT is the program output or data that child process returns - WRITE */
static HANDLE g_hChildStd_OUT_Wr = NULL;
/* Force Cancel Worker*/
static BOOL g_bForceCancelWorker = FALSE;
/* Check IO IS Busy*/
static BOOL g_bIsIOBusy = FALSE;

static CCriticalSection g_csc;

static void CleanUpThread()
{
	ThreadWorkerMgr.m_bIsWorkerRunning = FALSE;
	DELETE_WIN32_HANDLE(g_hProcess);
	DELETE_WIN32_HANDLE(g_hChildStd_OUT_Rd);
	DELETE_WIN32_HANDLE(g_hChildStd_OUT_Wr);
	DELETE_WIN32_HANDLE(g_hChildStd_IN_Rd);
	DELETE_WIN32_HANDLE(g_hChildStd_IN_Wr);
}

UINT CEditorThreadCompiler::ThreadFunc(LPVOID pParam)
{
	CEditorThreadCompiler *pThis = reinterpret_cast<CEditorThreadCompiler*>(pParam);
	std::unique_ptr<CEditorThreadCompiler> pSharedParam;
	pSharedParam.reset(pThis);

	ASSERT(pSharedParam.get());
	if (!pSharedParam.get())
	{
		return 1;
	}

	pSharedParam->START_WIN32_PIPE_IPC_MODEL();

	return 0; // thread completed successfully
}

CEditorThreadCompiler::TaskItem CEditorThreadCompiler::GetCurrentTask()
{
	return m_Task;
}

BOOL CEditorThreadCompiler::IsDebuggerRunning()
{
	if (m_bIsWorkerRunning == TRUE && this->m_Task.processType == PROCESS_TYPE::DEBUGGING_TYPE)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CEditorThreadCompiler::IsRunning()
{
	return m_bIsWorkerRunning && g_hProcess;
}

void CEditorThreadCompiler::CreateWorkerThread(TaskItem task)
{
	m_bIsWorkerRunning = TRUE;
	CEditorThreadCompiler* pEditorWorker = new CEditorThreadCompiler();
	pEditorWorker->m_Task = task;
	this->m_Task = task;
	m_pThread = ::AfxBeginThread(ThreadFunc, (LPDWORD)pEditorWorker, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED | PROCESS_TERMINATE, NULL);
	if (m_pThread)
	{
		m_hThread = m_pThread->m_hThread;
		m_pThread->m_bAutoDelete = TRUE;
		m_pThread->ResumeThread();
	}
}

void CEditorThreadCompiler::WriteUserInputToPipe(CString strUserInput)
{
	SYNC_WAIT_UNTIL_OBJECT_BECAME_FALSE(g_bIsIOBusy)
		g_bIsIOBusy = TRUE;
	DWORD dwWritten = 0;
	char strPass[256];
	strcpy_s(strPass, CStringA(strUserInput).GetString());
	// write user input
	OVERLAPPED osWriteUserInput = { 0,0,0 };
	HANDLE hEventUserInput = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (hEventUserInput != NULL)
	{
		osWriteUserInput.hEvent = hEventUserInput;
		BOOL bRet = WriteFile(g_hChildStd_IN_Wr, strPass, (DWORD)strlen(strPass), &dwWritten, &osWriteUserInput);
		if (!bRet)
		{
			LOG_MESSAGE_FROM_THREAD(LOG_TARGET::MESSAGE_WINDOW, m_Task.pWndFrame, _T("[Error] Can not pass arguments to process..."), BasicColors::orange);
			g_bIsIOBusy = FALSE;
			return;
		}
		WaitForSingleObject(hEventUserInput, INFINITE);
		CloseHandle(hEventUserInput);
	}
	// enter command line
	OVERLAPPED osWriteReturn = { 0,0,0 };
	HANDLE hEventReturn = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (hEventReturn != NULL)
	{
		CString strEnterCommand = EDITOR_NEW_LINE_LF; // must be \n to trigger command
		osWriteReturn.hEvent = hEventReturn;
		BOOL bRet = WriteFile(g_hChildStd_IN_Wr, strEnterCommand, strEnterCommand.GetLength(), &dwWritten, &osWriteReturn);
		if (!bRet)
		{
			LOG_MESSAGE_FROM_THREAD(LOG_TARGET::MESSAGE_WINDOW, m_Task.pWndFrame, _T("[Error] Can not pass arguments to process..."), BasicColors::orange);
			g_bIsIOBusy = FALSE;
			return;
		}
		WaitForSingleObject(hEventReturn, INFINITE);
		CloseHandle(hEventReturn);
	}
	g_bIsIOBusy = FALSE;
}

void CEditorThreadCompiler::START_WIN32_PIPE_IPC_MODEL()
{
	// reset handles...
	g_hChildStd_IN_Rd = NULL;
	g_hChildStd_IN_Wr = NULL;
	g_hChildStd_OUT_Rd = NULL;
	g_hChildStd_OUT_Wr = NULL;

	BYTE pbBuffer[BUFFER_SIZE_OUTPUT];
	memset(pbBuffer, '\0', BUFFER_SIZE_OUTPUT);
	TCHAR tlog[BUFFER_SIZE_OUTPUT];

	SECURITY_ATTRIBUTES PipeAttributes;
	ZeroMemory(&PipeAttributes, sizeof(SECURITY_ATTRIBUTES));

	PipeAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	PipeAttributes.bInheritHandle = TRUE;
	PipeAttributes.lpSecurityDescriptor = NULL;

	// Child process's STDOUT is the program output or data that child process returns
	// Create a pipe for the child process's STDOUT. 
	if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &PipeAttributes, 0))
	{
		ThreadWorkerMgr.m_bIsWorkerRunning = FALSE;
		return;
	}

	// Ensure the read handle to the pipe for STDOUT is not inherited.
	if (!SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0))
	{
		ThreadWorkerMgr.m_bIsWorkerRunning = FALSE;
		return;
	}

	// Child process's STDIN is the user input or data that you enter into the child process
	// Create a pipe for the child process's STDIN. 
	if (!CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &PipeAttributes, 0))
	{
		ThreadWorkerMgr.m_bIsWorkerRunning = FALSE;
		return;
	}

	// Ensure the write handle to the pipe for STDIN is not inherited. 
	if (!SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0))
	{
		ThreadWorkerMgr.m_bIsWorkerRunning = FALSE;
		return;
	}

	// Create the child process. 

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdOutput = g_hChildStd_OUT_Wr;
	si.hStdError = g_hChildStd_OUT_Wr;
	si.hStdInput = g_hChildStd_IN_Rd;

	CString strCmdLine = m_Task.strCommandLine;
	CString strStartDir = m_Task.strRunFromDirectory;
	LPTSTR szCmdline = strCmdLine.GetBuffer(strCmdLine.GetLength() + 1);
	LPTSTR szStartDir = strStartDir.GetBuffer(strStartDir.GetLength() + 1);

	UINT nErrMode = GetErrorMode();

	SetErrorMode(SEM_NOGPFAULTERRORBOX);

	BOOL bRet = CreateProcessW(NULL,   // No module name (use command line)
		szCmdline,      // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		TRUE,           // Set handle inheritance to FALSE > to read Pipe need to set TRUE
		CREATE_NO_WINDOW,  // Creation flags
		NULL,           // Use parent's environment block
		szStartDir,     // starting directory
		&si,            // Pointer to STARTUPINFO structure
		&pi);           // Pointer to PROCESS_INFORMATION structure
	strCmdLine.ReleaseBuffer();
	strStartDir.ReleaseBuffer();

	g_hProcess = pi.hProcess;

	if (!bRet)
	{
		DWORD nLastError = ::GetLastError();
		TRACE("CreateProcess Failed code: %d\n", nLastError);
		if (m_Task.pWndGUI && ::IsWindow(m_Task.pWndGUI->GetSafeHwnd()))
		{
			if (m_Task.processType == PROCESS_TYPE::BUILDING_TYPE)
			{
				m_Task.pWndGUI->SendNotifyMessage(UWM_GUI_WORKER_HANDLER_BUILD_NOTIFY_EXIT_CODE, NULL, LPARAM(nLastError));
				LOG_MESSAGE_FROM_THREAD(LOG_TARGET::BUILD_WINDOW, m_Task.pWndFrame, _T("[Error] Can not create buid process..."), BasicColors::orange);
			}
			else if (m_Task.processType == PROCESS_TYPE::RUNNING_TYPE)
			{
				m_Task.pWndGUI->SendNotifyMessage(UWM_GUI_WORKER_HANDLER_RUN_NOTIFY_EXIT_CODE, NULL, LPARAM(nLastError));
				LOG_MESSAGE_FROM_THREAD(LOG_TARGET::BUILD_WINDOW, m_Task.pWndFrame, _T("[Error] Can not create program process..."), BasicColors::orange);
			}
			else if (m_Task.processType == PROCESS_TYPE::DEBUGGING_TYPE)
			{
				m_Task.pWndGUI->SendNotifyMessage(UWM_GUI_WORKER_HANDLER_DEBUG_NOTIFY_EXIT_CODE, NULL, LPARAM(nLastError));
				LOG_MESSAGE_FROM_THREAD(LOG_TARGET::BUILD_WINDOW, m_Task.pWndFrame, _T("[Error] Can not create debugger process..."), BasicColors::orange);
			}
		}

		// clean up...
		CleanUpThread();
		return;
	}
	else
	{
		DELETE_WIN32_HANDLE(pi.hThread)
	}

	while (true)
	{
		DWORD dwRet = ::WaitForSingleObject(pi.hProcess, 500);

		DWORD dwAvailSize = 0;

		PeekNamedPipe(g_hChildStd_OUT_Rd, NULL, 0, NULL, &dwAvailSize, NULL);
		if (dwAvailSize > 0)
		{
			DWORD dwRead = 0;
			ReadFile(g_hChildStd_OUT_Rd, pbBuffer, sizeof(pbBuffer), &dwRead, NULL);
			std::fill(tlog, tlog + BUFFER_SIZE_OUTPUT, 0);
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPCSTR)pbBuffer, dwRead, tlog, (sizeof tlog) / 2);
			LOG_MESSAGE_FROM_THREAD(LOG_TARGET::BUILD_WINDOW, m_Task.pWndFrame, tlog, RGB(255, 255, 255));
		}

		PeekNamedPipe(g_hChildStd_OUT_Wr, NULL, 0, NULL, &dwAvailSize, NULL);
		if (dwAvailSize > 0)
		{
			DWORD dwRead = 0;
			ReadFile(g_hChildStd_OUT_Wr, pbBuffer, sizeof(pbBuffer), &dwRead, NULL);
			std::fill(tlog, tlog + BUFFER_SIZE_OUTPUT, 0);
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPCSTR)pbBuffer, dwRead, tlog, (sizeof tlog) / 2);
			LOG_MESSAGE_FROM_THREAD(LOG_TARGET::BUILD_WINDOW, m_Task.pWndFrame, tlog, RGB(255, 255, 255));
		}

		if (g_bForceCancelWorker) // cancel from user
		{
			g_bForceCancelWorker = FALSE;
			BOOL bStopAnswer = TRUE;
			if (AppSettingMgr.m_bAskBeforeTerminateProgram)
			{
				if (IDYES != AfxMessageBox(_T("The program is running. Are you sure want to stop it?"), MB_YESNO | MB_ICONWARNING))
				{
					bStopAnswer = FALSE;
				}
			}
			if (pi.hProcess && bStopAnswer)
			{
				DWORD dwExitCode = 0;
				::TerminateProcess(pi.hProcess, (UINT)dwExitCode);
				if (::GetExitCodeProcess(pi.hProcess, &dwExitCode) == FALSE)
				{
					LOG_MESSAGE_FROM_THREAD(LOG_TARGET::BUILD_WINDOW, m_Task.pWndFrame, _T("[Error] Can not get exit code from process..."), BasicColors::orange);
				}
				if (STILL_ACTIVE == dwExitCode)
				{
					::TerminateProcess(pi.hProcess, (UINT)dwExitCode);
				}
				if (m_Task.pWndGUI && ::IsWindow(m_Task.pWndGUI->GetSafeHwnd()))
				{
					if (m_Task.processType == PROCESS_TYPE::BUILDING_TYPE)
					{
						m_Task.pWndGUI->SendNotifyMessage(UWM_GUI_WORKER_HANDLER_BUILD_NOTIFY_EXIT_CODE, (WPARAM)THREAD_STATUS::THREAD_STATUS_ABORT, LPARAM(dwExitCode));
					}
					else if (m_Task.processType == PROCESS_TYPE::RUNNING_TYPE)
					{
						m_Task.pWndGUI->SendNotifyMessage(UWM_GUI_WORKER_HANDLER_RUN_NOTIFY_EXIT_CODE, (WPARAM)THREAD_STATUS::THREAD_STATUS_ABORT, LPARAM(dwExitCode));
					}
					else if (m_Task.processType == PROCESS_TYPE::DEBUGGING_TYPE)
					{
						m_Task.pWndGUI->SendNotifyMessage(UWM_GUI_WORKER_HANDLER_DEBUG_NOTIFY_EXIT_CODE, (WPARAM)THREAD_STATUS::THREAD_STATUS_ABORT, LPARAM(dwExitCode));
					}
				}
			}
			break;
		}

		WORD state = THREAD_STATUS::THREAD_STATUS_FINISHED;

		if (WAIT_FAILED == dwRet)
		{
			state = THREAD_STATUS::THREAD_STATUS_FAILED;
		}
		else if (WAIT_OBJECT_0 == dwRet) // process finished...
		{
			DWORD dwExitCode = 0;
			if (::GetExitCodeProcess(pi.hProcess, &dwExitCode) == FALSE)
			{
				LOG_MESSAGE_FROM_THREAD(LOG_TARGET::BUILD_WINDOW, m_Task.pWndFrame, _T("[Error] Can not get exit code from process..."), BasicColors::orange);
			}
			if (STILL_ACTIVE == dwExitCode)
			{
				dwExitCode = 4;
				::TerminateProcess(pi.hProcess, (UINT)dwExitCode);
				state = THREAD_STATUS::THREAD_STATUS_FAILED;
			}
			if (m_Task.pWndGUI && ::IsWindow(m_Task.pWndGUI->GetSafeHwnd()))
			{
				if (m_Task.processType == PROCESS_TYPE::BUILDING_TYPE)
				{
					m_Task.pWndGUI->SendNotifyMessage(UWM_GUI_WORKER_HANDLER_BUILD_NOTIFY_EXIT_CODE, (WPARAM)state, LPARAM(dwExitCode));
				}
				else if (m_Task.processType == PROCESS_TYPE::RUNNING_TYPE)
				{
					m_Task.pWndGUI->SendNotifyMessage(UWM_GUI_WORKER_HANDLER_RUN_NOTIFY_EXIT_CODE, (WPARAM)state, LPARAM(dwExitCode));
				}
				else if (m_Task.processType == PROCESS_TYPE::DEBUGGING_TYPE)
				{
					m_Task.pWndGUI->SendNotifyMessage(UWM_GUI_WORKER_HANDLER_DEBUG_NOTIFY_EXIT_CODE, (WPARAM)state, LPARAM(dwExitCode));
				}
			}
			break;
		}
		else if (WAIT_OBJECT_0 + 1 == dwRet) // process running...
		{
			DWORD dwExitCode = 0;
			if (::GetExitCodeProcess(pi.hProcess, &dwExitCode) == FALSE)
			{
				LOG_MESSAGE_FROM_THREAD(LOG_TARGET::BUILD_WINDOW, m_Task.pWndFrame, _T("[Error] Can not get exit code from process..."), BasicColors::orange);
			}
			if (m_Task.pWndGUI && ::IsWindow(m_Task.pWndGUI->GetSafeHwnd()))
			{
				if (m_Task.processType == PROCESS_TYPE::BUILDING_TYPE)
				{
					m_Task.pWndGUI->SendNotifyMessage(UWM_GUI_WORKER_HANDLER_BUILD_NOTIFY_EXIT_CODE, (WPARAM)state, LPARAM(dwExitCode));
				}
				else if (m_Task.processType == PROCESS_TYPE::RUNNING_TYPE)
				{
					m_Task.pWndGUI->SendNotifyMessage(UWM_GUI_WORKER_HANDLER_RUN_NOTIFY_EXIT_CODE, (WPARAM)state, LPARAM(dwExitCode));
				}
				else if (m_Task.processType == PROCESS_TYPE::DEBUGGING_TYPE)
				{
					m_Task.pWndGUI->SendNotifyMessage(UWM_GUI_WORKER_HANDLER_DEBUG_NOTIFY_EXIT_CODE, (WPARAM)state, LPARAM(dwExitCode));
				}
			}
		}
		else if (WAIT_TIMEOUT == dwRet) // timeout, run loop...
		{
			state = THREAD_STATUS::THREAD_STATUS_RUNNING;
		}

		if (m_Task.pWndGUI && ::IsWindow(m_Task.pWndGUI->GetSafeHwnd())) // update progress...
		{
			if (m_Task.pWndGUI && ::IsWindow(m_Task.pWndGUI->GetSafeHwnd()))
			{
				LPARAM lProgress = 100;
				if (m_Task.processType == PROCESS_TYPE::BUILDING_TYPE)
				{
					LPCTSTR szProgressName = _T("Program is building...");
					m_Task.pWndGUI->SendNotifyMessage(UWM_GUI_WORKER_HANDLER_NOTIFY_PROGRESS, (WPARAM)szProgressName, lProgress);
				}
				else if (m_Task.processType == PROCESS_TYPE::RUNNING_TYPE)
				{
					LPCTSTR szProgressName = _T("Program is running...");
					m_Task.pWndGUI->SendNotifyMessage(UWM_GUI_WORKER_HANDLER_NOTIFY_PROGRESS, (WPARAM)szProgressName, lProgress);
				}
				else if (m_Task.processType == PROCESS_TYPE::DEBUGGING_TYPE)
				{
					LPCTSTR szProgressName = _T("Debugger is running...");
					m_Task.pWndGUI->SendNotifyMessage(UWM_GUI_WORKER_HANDLER_NOTIFY_PROGRESS, (WPARAM)szProgressName, lProgress);
				}
			}
		}

		if (THREAD_STATUS::THREAD_STATUS_RUNNING != state) break;
	}

	// clean up...
	CleanUpThread();
}

void CEditorThreadCompiler::StopThreadWorker()
{
	if (m_bIsWorkerRunning && g_hProcess)
	{
		g_bForceCancelWorker = TRUE;
	}
}

void CEditorThreadCompiler::FinalizeThreadWorker()
{
	if (m_bIsWorkerRunning && g_hProcess)
	{
		DWORD dwExitCode = 0;
		::TerminateProcess(g_hProcess, (UINT)dwExitCode);
		if (STILL_ACTIVE == dwExitCode)
		{
			::TerminateProcess(g_hProcess, (UINT)dwExitCode);
		}
	}
	// clean up...
	g_hProcess = NULL;
}