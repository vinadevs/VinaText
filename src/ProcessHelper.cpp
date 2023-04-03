#include "stdafx.h"
#include "ProcessHelper.h"
#include "AppUtil.h"
#include "MainFrm.h"

static void WinLoop()
{
	MSG msg;
	if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
}

void CProcessHelper::SetInheritHandles(BOOL val) { m_bInheritHandles = val; }
void CProcessHelper::SetCreationFlags(DWORD val) { m_dwCreationFlags = val; }
void CProcessHelper::SetEnvironment(LPVOID val) { m_lpEnvironment = val; }
void CProcessHelper::SetProcessDirectory(LPCTSTR val) { m_lpCurrentDirectory = val; }

#define BUFFER_SIZE_OUTPUT 2048

BOOL CProcessHelper::LaunchProcess(CString& strCmdLine, DWORD* pExitCode, BOOL bPrintOutput /*= TRUE*/, CMainFrame* pMainFrame /*= NULL*/, BOOL bDisableWER /*=TRUE*/, BOOL bCheckCancel/* = TRUE*/)
{
	m_bStopProcess = FALSE;

	HANDLE hReadPipe;
	HANDLE hWritePipe;
	HANDLE hErrReadPipe;
	HANDLE hErrWritePipe;

	SECURITY_ATTRIBUTES PipeAttributes;
	ZeroMemory(&PipeAttributes, sizeof( SECURITY_ATTRIBUTES ));

	PipeAttributes.nLength = sizeof( SECURITY_ATTRIBUTES ); 
	PipeAttributes.bInheritHandle = TRUE; 
	PipeAttributes.lpSecurityDescriptor = NULL; 

	if (!CreatePipe( &hReadPipe, &hWritePipe, &PipeAttributes, 0))
	{
		return FALSE;
	}
	if (!CreatePipe( &hErrReadPipe, &hErrWritePipe, &PipeAttributes, 0))
	{
		return FALSE;
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdOutput = hWritePipe;
	si.hStdError = hErrWritePipe;
	
	if (bPrintOutput)
	{
		LOG_OUTPUT_MESSAGE_WITH_TIME(strCmdLine);
	}

	LPTSTR szCmdline = strCmdLine.GetBuffer(strCmdLine.GetLength() + 1);

	UINT nErrMode = GetErrorMode();

	// WER (Windows Error Reporting) is disabled on Manframe and its child processes to avoid 
	// the dialog being displayed if a crash on the child process happens
	if (bDisableWER)
	{
		SetErrorMode(SEM_NOGPFAULTERRORBOX);
	}

	BOOL bRet = CreateProcessW( NULL,   // No module name (use command line)
		szCmdline,      // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		m_bInheritHandles,          // Set handle inheritance to FALSE
		m_dwCreationFlags,  // Creation flags
		m_lpEnvironment,           // Use parent's environment block
		m_lpCurrentDirectory,           // Use parent's starting directory
		&si,            // Pointer to STARTUPINFO structure
		&pi );          // Pointer to PROCESS_INFORMATION structure		
	strCmdLine.ReleaseBuffer();

	if (!bRet)
	{
		DWORD nCode = ::GetLastError();
		TRACE("CreateProcess Failed code: %d\n", nCode);
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error] Create process %s with failed code: %d"), strCmdLine, nCode);
		return FALSE;
	}

	if (pMainFrame)
	{
		pMainFrame->SendMessage(UWM_MAINFRAME_PROCESS_NOTIFY, (WPARAM)pi.hProcess, PROCESS_RUNNING);
	}

	DELETE_WIN32_HANDLE(pi.hThread);

	bool bQuitProcess = FALSE;

	BYTE pbBuffer[BUFFER_SIZE_OUTPUT*2];
	TCHAR tlog[BUFFER_SIZE_OUTPUT];

	DWORD dwRet;
	while ((dwRet = ::WaitForSingleObject( pi.hProcess, 100 )) != WAIT_ABANDONED)
	{
		DWORD dwAvailSize = 0;
		PeekNamedPipe( hReadPipe, NULL, 0, NULL, &dwAvailSize, NULL);
		if( dwAvailSize > 0 )
		{	
			DWORD dwRead = 0;
			ReadFile( hReadPipe, pbBuffer, sizeof( pbBuffer ), &dwRead, NULL );
			std::fill(tlog, tlog + BUFFER_SIZE_OUTPUT, 0);
			MultiByteToWideChar(CP_OEMCP, MB_PRECOMPOSED, (LPCSTR)pbBuffer , dwRead, tlog, (sizeof tlog) / 2);

			if (bPrintOutput)
			{
				LOG_OUTPUT_MESSAGE_FORMAT(tlog);
			}
		}
		PeekNamedPipe( hErrReadPipe, NULL, 0, NULL, &dwAvailSize, NULL);
		if (dwAvailSize > 0)
		{	
			DWORD dwRead = 0;
			ReadFile( hErrReadPipe, pbBuffer, sizeof( pbBuffer ), &dwRead, NULL );
			std::fill(tlog, tlog + BUFFER_SIZE_OUTPUT, 0);
			MultiByteToWideChar(CP_OEMCP, MB_PRECOMPOSED, (LPCSTR)pbBuffer , dwRead, tlog, (sizeof tlog) / 2);
			
			if (bPrintOutput)
			{
				LOG_OUTPUT_MESSAGE_FORMAT(tlog);
			}
		}

		if (bCheckCancel)
		{
			WinLoop();
			if (m_bStopProcess)
			{
				TerminateProcess(pi.hProcess, 0);
				// Set to its default Error Mode
				if (bDisableWER)
				{
					SetErrorMode(nErrMode);
				}
				break;
			}
		}

		if (dwRet == WAIT_OBJECT_0)
		{
			DWORD nExitCode = 0;
			::GetExitCodeProcess(pi.hProcess, &nExitCode);

			// Set to its default Error Mode
			if( bDisableWER ) 
				SetErrorMode(nErrMode);	
			
			if (pExitCode) *pExitCode = nExitCode;
			if (nExitCode != STILL_ACTIVE)
			{
				if (nExitCode == 1) bQuitProcess = TRUE;
				break;
			}
		}
	}

	if (pMainFrame)  // Inform the dialog that the process has finished running
	{
		pMainFrame->SendMessage(UWM_MAINFRAME_PROCESS_NOTIFY, (WPARAM)pi.hProcess, PROCESS_STOPPED);
	}

	DELETE_WIN32_HANDLE(pi.hProcess);
	DELETE_WIN32_HANDLE(hReadPipe);
	DELETE_WIN32_HANDLE(hWritePipe);
	DELETE_WIN32_HANDLE(hErrReadPipe);
	DELETE_WIN32_HANDLE(hErrWritePipe);

	return bQuitProcess;
}

void CProcessHelper::StopProcess()
{
	 m_bStopProcess = TRUE;
}
