/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "AppUtil.h"
#include "OSUtil.h"
#include "MainFrm.h"

///////////////////////////////// OS Utils //////////////////////////////////////

LONGLONG OSUtils::StartBenchmark()
{
	LONGLONG counterBegin;
	QueryPerformanceCounter((PLARGE_INTEGER)&counterBegin);
	return counterBegin;
}

double OSUtils::StopBenchmark(LONGLONG counterBegin)
{
	LONGLONG counterEnd = 0;
	QueryPerformanceCounter((PLARGE_INTEGER)&counterEnd);
	LONGLONG freq;
	QueryPerformanceFrequency((PLARGE_INTEGER)&freq);
	double dElaspedTime = (double)(counterEnd - counterBegin) / (double)freq;
	return dElaspedTime;
}

void OSUtils::LogStopBenchmark(LOG_TARGET target, LONGLONG counterBegin, const CString& strMessage, COLORREF color)
{
	LONGLONG counterEnd = 0;
	QueryPerformanceCounter((PLARGE_INTEGER)&counterEnd);
	LONGLONG freq;
	QueryPerformanceFrequency((PLARGE_INTEGER)&freq);
	float fElaspedTime = (float)(counterEnd - counterBegin) / (float)freq;
	LOG_MESSAGE(target, strMessage + AppUtils::FloatToCString(fElaspedTime) + _T("s"), color);
}

void OSUtils::CreateProcessAsynchronous(const CString & lpVerb, const CString & cmd, const CString & args, const CString & cDir, BOOL show)
{
	::ShellExecute(::GetDesktopWindow(), lpVerb, cmd, args, cDir, show);
	LOG_OUTPUT_MESSAGE_COLOR(_T("> [System Command Line] ") + cmd + CSTRING_SPACE + args, BasicColors::orange);
}

unsigned long OSUtils::CreateProcessSynchronous(const CString & lpVerb, const CString & cmd, const CString & args, const CString & cDir, BOOL show)
{
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = ::GetDesktopWindow();
	ShExecInfo.lpVerb = lpVerb;
	ShExecInfo.lpFile = cmd;
	ShExecInfo.lpParameters = args;
	ShExecInfo.lpDirectory = cDir;
	ShExecInfo.nShow = show;
	ShExecInfo.hInstApp = NULL;

	ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	unsigned long exitCode;
	if (::GetExitCodeProcess(ShExecInfo.hProcess, &exitCode) == FALSE)
	{
		GetLastErrorAsString();
		return exitCode;
	}

	LOG_OUTPUT_MESSAGE_COLOR(_T("> [System Command Line] ") + cmd + CSTRING_SPACE + args, BasicColors::orange);
	return exitCode;
}

BOOL OSUtils::CreateWin32Process(CString strCmdLine)
{
	//	IMPORTANT NOTE: IF WE CREATE A PROCESS THAT RUN IN SILENT MODE, BE CAREFULLY WITH JOB ISSUE.
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	LPTSTR szCmdline = strCmdLine.GetBuffer(strCmdLine.GetLength() + 1);
	BOOL bRet = CreateProcessW(NULL,   // No module name (use command line)
		szCmdline,      // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags.
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory.
		&si,            // Pointer to STARTUPINFO structure
		&pi);          // Pointer to PROCESS_INFORMATION structure
	strCmdLine.ReleaseBuffer();
	if (!bRet)
	{
		DWORD nCode = ::GetLastError();
		TRACE("CreateProcess Failed code: %d\n", nCode);
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [System Command Line] failed run: ") + strCmdLine, BasicColors::orange);
		return FALSE;
	}
	DELETE_WIN32_HANDLE(pi.hProcess);
	DELETE_WIN32_HANDLE(pi.hThread);
	LOG_OUTPUT_MESSAGE_COLOR(_T("> [System Command Line] ") + strCmdLine, BasicColors::orange);
	return TRUE;
}

int OSUtils::RunSystemCMD(const CString& strCmdLine)
{
	int ret = ::_wsystem(AppUtils::CStringToWStd(strCmdLine).c_str());
	LOG_OUTPUT_MESSAGE_COLOR(_T("> [System Command Line] ") + strCmdLine, BasicColors::orange);
	return ret;
}

int OSUtils::GetProcessID(const CString& processName, std::vector<DWORD>& vecProcessID)
{
	int iCntProcess = 0;
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (processName.Find(processInfo.szExeFile) != -1)
	{
		vecProcessID.push_back(processInfo.th32ProcessID);
		iCntProcess++;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (processName.Find(processInfo.szExeFile) != -1)
		{
			vecProcessID.push_back(processInfo.th32ProcessID);
			iCntProcess++;
		}
	}
	CloseHandle(processesSnapshot);
	return iCntProcess;
}


DWORD OSUtils::GetProcessCount(const std::wstring& processName)
{
	DWORD dwCntProcess = 0;
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		dwCntProcess++;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			dwCntProcess++;
		}
	}
	CloseHandle(processesSnapshot);
	return dwCntProcess;

}

DWORD OSUtils::GetProcIdFromHWND(HWND hwnd)
{
	DWORD uiProc;
	::GetWindowThreadProcessId(hwnd, &uiProc);
	return uiProc;
}

HWND OSUtils::GetHWNDFromProcessID(DWORD uiPId)
{
	HWND hTmpWnd = ::FindWindow(NULL, NULL);

	while (hTmpWnd != NULL)
	{
		if (::GetParent(hTmpWnd) == NULL)
		{
			if (uiPId == GetProcIdFromHWND(hTmpWnd))
				return hTmpWnd;
		}
		hTmpWnd = ::GetWindow(hTmpWnd, GW_HWNDNEXT);
	}
	return NULL;
}

HWND OSUtils::GetHWNDFromClassNameAndProgramPath(const CString& strClassName, const CString& strExecName)
{
	HWND hTmpWnd = ::FindWindowExW(NULL, NULL, strClassName, strExecName);
	return hTmpWnd;
}

void OSUtils::KillProcessByID(std::vector<DWORD>& vecProcessID)
{
	for (auto const& processId : vecProcessID)
	{
		const HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, processId);
		TerminateProcess(hProcess, 1);
		CloseHandle(hProcess);
	}
}

int OSUtils::KillProcessByName(const CString& strProcessName)
{
	std::string strStopCmd = AppUtils::CStringToStd(AfxCStringFormat(_T("taskkill /F /T /IM %s"), strProcessName));
	return WinExec(strStopCmd.c_str(), SW_HIDE);
}

CString OSUtils::GetLastErrorAsString()
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	);
	CString fmsg = (LPCTSTR)lpMsgBuf;
	LocalFree(lpMsgBuf);
	return fmsg;
}

#define CMD_PATSE_COMMAND 0xfff1
void OSUtils::PatseClipboardToCMD(HWND hCMD)
{
	if (hCMD)
	{
		SendMessage(hCMD, WM_COMMAND, CMD_PATSE_COMMAND, 0);
	}
}

void OSUtils::ChangeIME(HWND hWnd, DWORD dwNewKeybLayout, BOOL bOpen)
{
	if (bOpen)
	{
		//DWORD dwNewKeybLayout = 0x00000412; // Layout must be already loaded!
		PostMessage(hWnd, WM_INPUTLANGCHANGEREQUEST, 0, (LPARAM)dwNewKeybLayout);
		PostMessage(hWnd, WM_INPUTLANGCHANGE, 0, (LPARAM)dwNewKeybLayout);
		HIMC himc = ImmGetContext(hWnd);
		ImmSetOpenStatus(himc, TRUE);
	}
	else
	{
		HIMC himc = ImmGetContext(hWnd);
		ImmSetOpenStatus(himc, FALSE);
	}
}

CString OSUtils::GetRegistryAppPath(const CString & strEXEName)
{
	CString strFullPath = _T("");
	TCHAR valData[MAX_PATH] = { '\0' };
	DWORD valDataLen = MAX_PATH * sizeof(TCHAR);
	DWORD valType;
	HKEY hKey2Check = NULL;
	CString strAppEntry = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\");
	strAppEntry += strEXEName;
	::RegOpenKeyEx(HKEY_LOCAL_MACHINE, strAppEntry, 0, KEY_READ, &hKey2Check);
	::RegQueryValueEx(hKey2Check, _T(""), nullptr, &valType, reinterpret_cast<LPBYTE>(valData), &valDataLen);
	if (hKey2Check && valData[0] != '\0')
	{
		strFullPath = valData;
	}
	::RegCloseKey(hKey2Check);
	return strFullPath;
}

void OSUtils::DeleteRegistryKey(const CString& lpSubKey)
{
	HKEY hKey;
	LONG result = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software"), 0, KEY_WRITE, &hKey);
	if (result == ERROR_SUCCESS)
	{
		result = RegDeleteTree(hKey, lpSubKey);
		if (result != ERROR_SUCCESS)
		{
			assert(FALSE);
		}
		RegCloseKey(hKey);
	}
	else
	{
		assert(FALSE);
	}
}

void OSUtils::OpenFileInWebBrowser(const CString& strEXEName, const CString& strFilePath)
{
	if (strEXEName.Find(_T("MicrosoftEdge")) != -1)
	{
		::ShellExecute(NULL, _T("open"), strFilePath, NULL, NULL, SW_SHOW);
	}
	else
	{
		CString strAppPath = OSUtils::GetRegistryAppPath(strEXEName);
		if (strAppPath.IsEmpty())
		{
			int nAnwser = AfxMessageBoxFormat(MB_YESNO | MB_ICONWARNING, _T("[%s] has not installed on this computer yet. You can change web browser in language setting file. Do you want to open it by default web browser?"), strEXEName);
			if (IDYES == nAnwser)
			{
				::ShellExecute(NULL, _T("open"), strFilePath, NULL, NULL, SW_SHOW);
			}
		}
		else
		{
			::ShellExecute(NULL, TEXT("open"), strAppPath, ESCAPSE_STRING_WITH_QUOTE(strFilePath), NULL, SW_SHOWNORMAL);
		}
	}
}

CString OSUtils::GetGUIDGlobal()
{
	CString strListID(L"ERROR_GUIID");
	RPC_WSTR guidStr;
	GUID guid;
	HRESULT hr = CoCreateGuid(&guid);
	if (hr == S_OK)
	{
		if (UuidToString(&guid, &guidStr) == RPC_S_OK)
		{
			strListID = (LPTSTR)guidStr;
			RpcStringFree(&guidStr);
		}
	}
	return strListID;
}

tm* OSUtils::AddDays(tm* time, int days)
{
	time_t epoch = mktime(time);
	epoch += (60 * 60 * 24 * days);
	return localtime(&epoch);
}

tm* OSUtils::GetCurrentTimeEx()
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	struct tm* currentDate = std::localtime(&now_c);
	return currentDate;
}

CString OSUtils::DateToCStringYMD(tm * time)
{
	const int BUFFER_SIZE = 256;
	char* lOutString = new char[BUFFER_SIZE];
	strftime(lOutString, BUFFER_SIZE, "%Y-%m-%d", time);
	CString strTime(lOutString);
	DELETE_POINTER_CPP_ARRAY(lOutString)
	return strTime;
}

CString OSUtils::DateToCStringABDHMSY(tm * time, BOOL bDisableSpecialChar)
{
	const int BUFFER_SIZE = 256;
	char* lOutString = new char[BUFFER_SIZE];
	if (bDisableSpecialChar)
	{
		strftime(lOutString, BUFFER_SIZE, "%a %b %d %H-%M-%S %Y", time);
	}
	else
	{
		strftime(lOutString, BUFFER_SIZE, "%a %b %d %H:%M:%S %Y", time);
	}
	CString strTime(lOutString);
	DELETE_POINTER_CPP_ARRAY(lOutString)
	return strTime;
}

std::wstring OSUtils::GetCMDConsoleResult(const wchar_t* cmd)
{
	wchar_t buffer[128];
	std::wstring result = L"";
	FILE* pipe = _wpopen(cmd, L"r");
	if (!pipe) throw std::runtime_error("_popen() failed!");
	try
	{
		while (fgetws(buffer, sizeof(buffer), pipe) != NULL)
		{
			result += buffer;
		}
	}
	catch (...)
	{
		_pclose(pipe);
		throw;
	}
	_pclose(pipe);
	return result;
}

#define SUCCESS_SHELL_EXEC_RET 32
void OSUtils::UseAdministrationHandler()
{
	if (IDYES == AfxMessageBox(_T("[Access is denied] This file maybe use by other processes or need administration right to edit.\n- Do you want to reopen VinaText with administration rights?"), MB_YESNO | MB_ICONWARNING))
	{
		CString strPathVinaTextExe = PathUtils::GetVinaTextExePath();
		if (PathFileExists(strPathVinaTextExe))
		{
			const intptr_t bRet = reinterpret_cast<intptr_t>(::ShellExecute(AppUtils::GetMainFrame()->GetSafeHwnd(), TEXT("runas"), strPathVinaTextExe, _T(" -openWithAdminRight "), NULL, SW_SHOW));
			if (bRet)
			{
				if (bRet < SUCCESS_SHELL_EXEC_RET)
				{
					AfxMessageBox(_T("[Administration Error] Can not reopen VinaText with administration rights!"));
				}
				else
				{
					AppUtils::GetMainFrame()->DestroyWindow();
				}
			}
		}
		else
		{
			CString strMsg; strMsg.Format(_T("[Path Error] \"%s\" does not exist...\n"), strPathVinaTextExe);
			LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strMsg, BasicColors::orange);
		}
	} 
}

void OSUtils::RestartAppplication()
{
	CString strPathVinaTextExe = PathUtils::GetVinaTextExePath();
	if (PathFileExists(strPathVinaTextExe))
	{
		const BOOL bRet = OSUtils::CreateWin32Process(strPathVinaTextExe + _T(" -restartApplication "));
		if (!bRet)
		{
			AfxMessageBox(_T("[Error] Could not restart VinaText."));
		}
		else
		{
			AppUtils::GetMainFrame()->DestroyWindow();
		}
	}
	else
	{
		CString strMsg; strMsg.Format(_T("[Path Error] \"%s\" does not exist...\n"), strPathVinaTextExe);
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strMsg, BasicColors::orange);
	}
}
