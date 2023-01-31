/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "SingleInstanceApp.h"

CSingleInstanceApp::CSingleInstanceApp(TCHAR *strMutexName)
{
	//Make sure that you use a name that is unique for this application otherwise
	//two apps may think they are the same if they are using same name for
	//3rd parm to CreateMutex

	m_lpszUID = strMutexName;
	m_hMutex = CreateMutex(NULL, FALSE, strMutexName); //do early
	m_dwLastError = GetLastError(); 

	// If two different applications register the same message string, 
	// the applications return the same message value. The message 
	// remains registered until the session ends. If the message is 
	// successfully registered, the return value is a message identifier 
	// in the range 0xC000 through 0xFFFF.

	ASSERT(m_uMsgCheckInst == NULL); // Only once
	m_uMsgCheckInst = ::RegisterWindowMessage(m_lpszUID);
	ASSERT(m_uMsgCheckInst >= 0xC000 && m_uMsgCheckInst <= 0xFFFF);
}

CSingleInstanceApp::~CSingleInstanceApp()
{
	if (m_hMutex)  //Do not forget to close handles.
	{
		DELETE_WIN32_HANDLE(m_hMutex)
	}
	m_uMsgCheckInst = NULL;
}

BOOL CSingleInstanceApp::IsAppAlreadyRunning()
{
	return (ERROR_ALREADY_EXISTS == m_dwLastError);
}

void CSingleInstanceApp::SendMessageToExistedInstance(CString strFileName)
{
	if (m_lpszUID != NULL)
	{
		// If another instance is found, pass document file name to it
		// only if command line contains FileNew or FileOpen parameters
		// and exit instance. In other cases such as FilePrint, etc., 
		// do not exit instance because framework will process the commands 
		// itself in invisible mode and will exit.

		if (FindAnotherInstance(m_lpszUID))
		{
			WPARAM wpCmdLine = NULL;
			wpCmdLine = (ATOM)::GlobalAddAtom(strFileName);
			BroadcastInstanceMessage(wpCmdLine, NULL);
		}
	}
}

BOOL CSingleInstanceApp::FindAnotherInstance(LPCTSTR lpszUID)
{
	ASSERT(lpszUID != NULL);

	// Create a new mutex. If fails means that process already exists:

	HANDLE hMutex = ::CreateMutex(NULL, FALSE, lpszUID);
	DWORD  dwError = ::GetLastError();

	if (hMutex != NULL)
	{
		// Close mutex handle
		::ReleaseMutex(hMutex);
		hMutex = NULL;

		// Another instance of application is running:

		if (dwError == ERROR_ALREADY_EXISTS || dwError == ERROR_ACCESS_DENIED)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CSingleInstanceApp::BroadcastInstanceMessage(WPARAM wParam, LPARAM lParam)
{
	ASSERT(m_uMsgCheckInst != NULL);

	// One process can terminate the other process by broadcasting the private message 
	// using the BroadcastSystemMessage function as follows:

	DWORD dwReceipents = BSM_APPLICATIONS;

	// Send the message to all other instances.
	// If the function succeeds, the return value is a positive value.
	// If the function is unable to broadcast the message, the return value is �1.

	LONG lRet = ::BroadcastSystemMessage(BSF_IGNORECURRENTTASK | BSF_FORCEIFHUNG |
		BSF_POSTMESSAGE, &dwReceipents, m_uMsgCheckInst, wParam, lParam);

	return (BOOL)(lRet != -1);
}
