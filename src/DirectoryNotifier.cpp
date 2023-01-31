/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "DirectoryNotifier.h"
#include "DirectoryNotifyManager.h"
#include "AppUtil.h"
#include "AppSettings.h"

#define BUFFER_SIZE_OUTPUT 4096

UINT CDirectoryNotifier::ThreadFunc(LPVOID pParam)
{
	CDirectoryNotifier *pThis = reinterpret_cast<CDirectoryNotifier*>(pParam);
	
	std::unique_ptr<CDirectoryNotifier> pSharedParam;
	pSharedParam.reset(pThis);

	BOOL bIsNotifierExisted = DirectoryNotifierMgr.AddNotifier(pSharedParam.get(), pSharedParam.get()->m_strFile);

	if (bIsNotifierExisted)
	{
		return 1;
	}

	ASSERT(pSharedParam.get());
	if (!pSharedParam.get())
	{
		return 1;
	}

	pSharedParam.get()->WatchProcess();

	return 0; // thread completed successfully
}

BOOL CDirectoryNotifier::StartWatchFile(CString strMonitorFile, CWnd* pNotifyWnd)
{
	m_pNotifyWnd = pNotifyWnd;
	m_strFile = strMonitorFile;
	m_strPath = PathUtils::GetContainerPathFromPath(strMonitorFile);

	m_hFileHandle = CreateFile(
		m_strPath,
		FILE_LIST_DIRECTORY | GENERIC_READ,
		FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
		NULL);

	if (m_hFileHandle == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	CDirectoryNotifier* pDirectoryNotifier = new CDirectoryNotifier();
	pDirectoryNotifier->m_strFile = m_strFile;
	pDirectoryNotifier->m_strPath = m_strPath;
	pDirectoryNotifier->m_hFileHandle = m_hFileHandle;
	pDirectoryNotifier->m_pNotifyWnd = m_pNotifyWnd;
	pDirectoryNotifier->m_FileNotifyOption = m_FileNotifyOption;
	m_pThread = ::AfxBeginThread(ThreadFunc, (LPDWORD)pDirectoryNotifier, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED | PROCESS_TERMINATE, NULL);
	if (m_pThread)
	{
		pDirectoryNotifier->m_hThread = m_pThread->m_hThread;
		pDirectoryNotifier->m_pThread = m_pThread;
		m_pThread->m_bAutoDelete = FALSE;
		m_pThread->ResumeThread();
	}

	return TRUE;
}

BOOL CDirectoryNotifier::StartWatchDirectory(CString strMonitorPath, CWnd* pNotifyWnd)
{
	m_pNotifyWnd = pNotifyWnd;
	m_strPath = strMonitorPath;

	m_hFileHandle = CreateFile(
		m_strPath,
		FILE_LIST_DIRECTORY | GENERIC_READ,
		FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
		NULL);

	if (m_hFileHandle == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	CDirectoryNotifier* pDirectoryNotifier = new CDirectoryNotifier();
	pDirectoryNotifier->m_strPath = m_strPath;
	pDirectoryNotifier->m_hFileHandle = m_hFileHandle;
	pDirectoryNotifier->m_pNotifyWnd = m_pNotifyWnd;
	pDirectoryNotifier->m_FileNotifyOption = m_FileNotifyOption;
	m_pThread = ::AfxBeginThread(ThreadFunc, (LPDWORD)pDirectoryNotifier, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED | PROCESS_TERMINATE, NULL);
	if (m_pThread)
	{
		pDirectoryNotifier->m_hThread = m_pThread->m_hThread;
		pDirectoryNotifier->m_pThread = m_pThread;
		m_pThread->m_bAutoDelete = FALSE;
		m_pThread->ResumeThread();
	}

	return TRUE;
}

void CDirectoryNotifier::CancelProcess()
{
	KillWatchThread();
}

void CDirectoryNotifier::WatchProcess()
{
	m_overlapped = { 0 };
	::ResetEvent(m_overlapped.hEvent);
	DWORD error;
	BYTE lpBuffer[4096];
	DWORD dwBytesReturned = 0;

	if(!::ReadDirectoryChangesW(m_hFileHandle, lpBuffer, BUFFER_SIZE_OUTPUT,
		FALSE, m_FileNotifyOption,
		&dwBytesReturned, &m_overlapped, NULL))
	{
		error = GetLastError();
		if (error != ERROR_IO_PENDING)
		{
			KillWatchThread();
		}
	}

	BYTE* pByte = lpBuffer;

	while (true)
	{
		BOOL bIsWait = TRUE;

		/*WORK_STATUS status = ProcessListOfExistingFiles();

		if (status == WORK_STATUS::MORE_WORK_PENDING)
		{
			bIsWait = FALSE;
		}
		else if (status == WORK_STATUS::NO_MORE_WORK_PENDING)
		{
			bIsWait = TRUE;
		}*/

		DWORD dw = 0;
		if (!::GetOverlappedResult(m_hFileHandle, &m_overlapped, &dw, bIsWait))
		{
			error = GetLastError();
			if (error == ERROR_IO_INCOMPLETE)
			{
				continue;
			}
			KillWatchThread();
		}

		ProcessDirectoryChanges(pByte);

		::ResetEvent(m_overlapped.hEvent);

		if (!::ReadDirectoryChangesW(m_hFileHandle, lpBuffer, BUFFER_SIZE_OUTPUT,
			FALSE, m_FileNotifyOption,
			&dwBytesReturned, &m_overlapped, NULL))
		{
			error = GetLastError();
			if (error != ERROR_IO_PENDING)
			{
				KillWatchThread();
			}
		}
	}
	
	// kill thread...
	KillWatchThread();
}

void CDirectoryNotifier::KillWatchThread()
{
	DWORD exit_code = NULL;
	if (m_pThread != NULL)
	{
		GetExitCodeThread(m_pThread->m_hThread, &exit_code);
		if (exit_code == STILL_ACTIVE)
		{
			::TerminateThread(m_pThread->m_hThread, 0);
			DELETE_WIN32_HANDLE(m_pThread->m_hThread)
		}
		DELETE_POINTER_CPP(m_pThread)
	}
	DELETE_WIN32_HANDLE(m_hFileHandle)
	DELETE_WIN32_HANDLE(m_overlapped.hEvent)
}

void CDirectoryNotifier::ProcessDirectoryChanges(BYTE* pByte)
{
	if (!pByte) return;

	while (1)
	{
		char fileName[MAX_PATH] = "";
		FILE_NOTIFY_INFORMATION* fni = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(pByte);

		int ret = ::WideCharToMultiByte(CP_ACP, 0, fni->FileName, fni->FileNameLength / sizeof(WCHAR), fileName, sizeof(fileName), NULL, NULL);
		
		CString strTempPath = m_strPath;
		strTempPath += "\\";
		strTempPath += fileName;

		switch (fni->Action) 
		{
		case FILE_ACTION_ADDED:
			if (PathUtils::IsDirectory(strTempPath))
			{
			}
			else
			{
				if (m_pNotifyWnd && ::IsWindow(m_pNotifyWnd->GetSafeHwnd()))
				{
					m_pNotifyWnd->PostMessage(UWM_GUI_DIRECTORY_NOTIFIER_FILE_CHANGE, NULL, NULL);
				}
			}
			break;
		case FILE_ACTION_MODIFIED:
			if (PathUtils::IsDirectory(strTempPath))
			{
			}
			else
			{
				if (m_pNotifyWnd && ::IsWindow(m_pNotifyWnd->GetSafeHwnd()))
				{
					m_pNotifyWnd->PostMessage(UWM_GUI_DIRECTORY_NOTIFIER_FILE_CHANGE, NULL, NULL);
				}
			}
			break;
		case FILE_ACTION_REMOVED:
			if (PathUtils::IsDirectory(strTempPath))
			{
			}
			else
			{
				if (m_pNotifyWnd && ::IsWindow(m_pNotifyWnd->GetSafeHwnd()))
				{
					m_pNotifyWnd->PostMessage(UWM_GUI_DIRECTORY_NOTIFIER_FILE_CHANGE, NULL, NULL);
				}
			}
			break;
		case FILE_ACTION_RENAMED_NEW_NAME:
			if (PathUtils::IsDirectory(strTempPath))
			{
			}
			else
			{
				if (m_pNotifyWnd && ::IsWindow(m_pNotifyWnd->GetSafeHwnd()))
				{
					m_pNotifyWnd->PostMessage(UWM_GUI_DIRECTORY_NOTIFIER_FILE_CHANGE, NULL, NULL);
				}
			}
			break;
		case FILE_ACTION_RENAMED_OLD_NAME:
			if (PathUtils::IsDirectory(strTempPath))
			{
			}
			else
			{
				if (m_pNotifyWnd && ::IsWindow(m_pNotifyWnd->GetSafeHwnd()))
				{
					m_pNotifyWnd->PostMessage(UWM_GUI_DIRECTORY_NOTIFIER_FILE_CHANGE, NULL, NULL);
				}
			}
			break;
		default:
			if (PathUtils::IsDirectory(strTempPath))
			{	
			}
			else
			{
			}
			break;
		}
		::memset(fileName, '\0', sizeof(fileName));

		if (!fni->NextEntryOffset) break;  // this was last entry
		pByte += fni->NextEntryOffset;
	}
}

void CDirectoryNotifier::ProcessFileChangesModify(BYTE * pByte)
{
	if (!pByte) return;

	while (1)
	{
		char fileName[MAX_PATH] = "";
		FILE_NOTIFY_INFORMATION* fni = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(pByte);

		int ret = ::WideCharToMultiByte(CP_ACP, 0, fni->FileName, fni->FileNameLength / sizeof(WCHAR), fileName, sizeof(fileName), NULL, NULL);
		CString strTempPath = m_strPath;
		strTempPath += "\\";
		strTempPath += fileName;

		switch (fni->Action) 
		{
			case FILE_ACTION_ADDED:
				if (PathUtils::IsDirectory(strTempPath))
				{
				}
				else
				{
					if (m_strFile.CompareNoCase(strTempPath) == 0)
					{
						if (m_pNotifyWnd && ::IsWindow(m_pNotifyWnd->GetSafeHwnd()))
						{
							m_pNotifyWnd->PostMessage(UWM_GUI_DIRECTORY_NOTIFIER_FILE_CHANGE, NULL, NULL);
						}
					}
				}
				break;
			default:
				if (PathUtils::IsDirectory(strTempPath))
				{
				}
				else
				{
				}
				break;
		}
		::memset(fileName, '\0', sizeof(fileName));

		if (!fni->NextEntryOffset) break;  // this was last entry
		pByte += fni->NextEntryOffset;
	}
}
