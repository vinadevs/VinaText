/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

//////////////////////////////////
// operation system utils

#include "AppSettings.h"

class CMainFrame;

namespace OSUtils
{
	CString     GetGUIDGlobal();
	tm *        AddDays(tm * time, int days);
	tm *        GetCurrentTimeEx();
	CString     DateToCStringYMD(tm * time);
	CString     DateToCStringABDHMSY(tm * time, BOOL bDisableSpecialChar = FALSE);
	LONGLONG    StartBenchmark();
	double	    StopBenchmark(LONGLONG counterBegin);
	void	    LogStopBenchmark(LOG_TARGET target, LONGLONG counterBegin, const CString& strMessage, COLORREF color = IS_LIGHT_THEME ? RGB(0, 0, 0) : RGB(255, 255, 255));
	void	    CreateProcessAsynchronous(const CString& lpVerb, const CString& cmd, const CString& args, const CString& cDir, BOOL show = FALSE);
	unsigned long CreateProcessSynchronous(const CString& lpVerb, const CString& cmd, const CString& args, const CString& cDir, BOOL show = FALSE);
	BOOL		CreateWin32Process(CString strCmdLine);
	int		    RunSystemCMD(const CString& strCmdLine);
	int			GetProcessID(const CString& processName, std::vector<DWORD>& vecProcessID);
	DWORD		GetProcessCount(const std::wstring& processName);
	DWORD		GetProcIdFromHWND(HWND hwnd);
	HWND		GetHWNDFromProcessID(DWORD uiPId);
	HWND        GetHWNDFromClassNameAndProgramPath(const CString& strClassName, const CString& strExecName);
	void		KillProcessByID(std::vector<DWORD>& vecProcessID);
	int		    KillProcessByName(const CString& strProcessName);
	CString		GetLastErrorAsString();
	void		PatseClipboardToCMD(HWND hCMD);
	void		ChangeIME(HWND hWnd, DWORD dwNewKeybLayout, BOOL bOpen);
	CString		GetRegistryAppPath(const CString& strEXEName);
	void        DeleteRegistryKey(const CString& lpSubKey);
	void		OpenFileInWebBrowser(const CString & strEXEName, const CString & strFilePath);
	std::wstring GetCMDConsoleResult(const wchar_t * cmd);
	void	    UseAdministrationHandler();
	void	    RestartApplication();
}