#pragma once

#define UWM_MAINFRAME_PROCESS_NOTIFY WM_APP+201 

class CMainFrame;

class CProcessHelper
{
public:
	CProcessHelper() : m_bStopProcess(FALSE), m_bInheritHandles(TRUE), m_dwCreationFlags(CREATE_NO_WINDOW), m_lpEnvironment(NULL), m_lpCurrentDirectory(NULL) {}
	BOOL LaunchProcess(CString& strCmdLine, DWORD* pExitCode, BOOL bPrintOutput = TRUE, CMainFrame* pMainFrame = NULL, BOOL bDisableWER = TRUE, BOOL bCheckCancel = TRUE);  
	void StopProcess();
	void SetInheritHandles(BOOL val);
	void SetCreationFlags(DWORD val);
	void SetEnvironment(LPVOID val);
	void SetProcessDirectory(LPCTSTR val);

private:
	BOOL m_bStopProcess;
	BOOL m_bInheritHandles;
	DWORD m_dwCreationFlags;
	LPVOID m_lpEnvironment;
	LPCTSTR m_lpCurrentDirectory; 
};