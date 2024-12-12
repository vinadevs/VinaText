/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

namespace HostManager
{
	enum HOST_APP_TYPE : unsigned int
	{
		TERMINAL_CMD,
		TERMINAL_POWERSHELL,
		FILE_EXPLORER,
		TERMINAL_WSL,
	};

	enum HOST_METHOD : unsigned int
	{
		USE_ENUMWINDOWS = 0,
		USE_FINDWINDOWS,
		USE_FOREGROUNDWINDOWS,
	};

	struct STHostAppInfo final
	{
		CString m_strAppName;
		CString m_strAppPathToHost;
		CString m_strAppArguments;
		CString m_strClassAppName;
		BOOL m_bRemoveTitleBarWindow;
		BOOL m_bSilentStartup;
		BOOL m_bOpenFileMode;
		UINT m_nAppIconID;
		int  m_nWaitTime;
		HOST_METHOD m_HostMethod;
	};

	CDocument* HostApplicaton(const HOST_APP_TYPE& appType, const CString& strAppPathToHost, const CString& strAppArguments = _T(""), BOOL bOpenFileMode = FALSE, BOOL bActiveExistedTab = TRUE);
}