/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "Singleton.h"

class CMainFrame;

// THIS MODULE USE TO INTERACT WITH EXTERNAL COMPILERS AND DEBUGGERS

class CEditorThreadCompiler : public CSingletonHelper<CEditorThreadCompiler>
{
public:
	enum THREAD_STATUS
	{
		THREAD_STATUS_ABORT = -1,
		THREAD_STATUS_FAILED = 0,
		THREAD_STATUS_RUNNING = 1,
		THREAD_STATUS_FINISHED = 2,
	};

	enum PROCESS_TYPE
	{
		UNKNOWN_TYPE = -1,
		BUILDING_TYPE,
		RUNNING_TYPE,
		DEBUGGING_TYPE,
	};

	struct TaskItem
	{
		VINATEXT_SUPPORTED_LANGUAGE currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_START; // need for add breakpoint at runtime
		CString		strRunFromDirectory;
		CString		strRunFromDocPath;
		CString		strCommandLine;
		CWnd*		pWndGUI = NULL;
		CMainFrame* pWndFrame = NULL;
		PROCESS_TYPE processType = PROCESS_TYPE::BUILDING_TYPE;
	};

	void START_WIN32_PIPE_IPC_MODEL();
	void StopThreadWorker();
	void FinalizeThreadWorker();
	void CreateWorkerThread(TaskItem task);
	void WriteUserInputToPipe(CString strUserInput);
	static UINT ThreadFunc(LPVOID pParam);
	TaskItem GetCurrentTask();
	BOOL IsDebuggerRunning();
	BOOL IsRunning();
	BOOL m_bIsWorkerRunning = FALSE;

protected:
	CWinThread* m_pThread = NULL;
	HANDLE		m_hThread = NULL;
	HANDLE      m_hGroupJob = NULL;
	TaskItem	m_Task;
};

#define ThreadWorkerMgr CEditorThreadCompiler::GetInstance()
