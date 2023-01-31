/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

class CSingleInstanceApp
{
protected:
	DWORD  m_dwLastError;
	HANDLE m_hMutex;

public:
	CSingleInstanceApp(TCHAR *strMutexName);
	~CSingleInstanceApp();
	BOOL IsAppAlreadyRunning();
	void SendMessageToExistedInstance(CString strFileName);
	UINT GetMsgCheckInst() { return m_uMsgCheckInst; }
	BOOL FindAnotherInstance(LPCTSTR lpszUID);
	BOOL BroadcastInstanceMessage(WPARAM wParam, LPARAM lParam);

protected:
	TCHAR *m_lpszUID = NULL;
	UINT   m_uMsgCheckInst = 0;
};