/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

////////////////////////////////////////////////////////////////////

class CDirectoryNotifier
{
public:
	CDirectoryNotifier() {}
	static UINT ThreadFunc(LPVOID pParam);
	BOOL StartWatchFile(CString strMonitorFile, CWnd* pNotifyWnd);
	BOOL StartWatchDirectory(CString strMonitorPath, CWnd* pNotifyWnd);
	void SetFileNotifyOptions(unsigned int FileNotifyOption) { m_FileNotifyOption = FileNotifyOption; }
	void CancelProcess();

	enum class WORK_STATUS : unsigned int
	{
		MORE_WORK_PENDING = 0,
		NO_MORE_WORK_PENDING = 1,
	};

protected:
	void ProcessDirectoryChanges(BYTE* pByte);
	void ProcessFileChangesModify(BYTE* pByte);
	void WatchProcess();
	void KillWatchThread();

	CWnd* m_pNotifyWnd = NULL;
	HANDLE m_hFileHandle = NULL;
	CString m_strPath;
	CString m_strFile;
	CWinThread* m_pThread = NULL;
	HANDLE		m_hThread = NULL;
	OVERLAPPED  m_overlapped;
	unsigned int m_FileNotifyOption;
};