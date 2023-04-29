/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "Singleton.h"
#include "NamedPipe.h"

enum class VINATEXT_CMD_OPTION : unsigned int
{
	VINATEXT_CMD_OPTION_INIT = 0,
	VINATEXT_CMD_MOVE_TO_NEW_WINDOW = 1,
	VINATEXT_CMD_REOPEN_WITH_ADMIN_RIGHT = 2,
}; 

class CCommandLineInfoEx : public CCommandLineInfo
{
public:
	CCommandLineInfoEx();
	virtual ~CCommandLineInfoEx();
	virtual void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast) override;
	VINATEXT_CMD_OPTION m_cmdOption = VINATEXT_CMD_OPTION::VINATEXT_CMD_OPTION_INIT;
};

class CConsoleHepler
{
public:
	BOOL Open();
	BOOL Close();
	void Write(LPCTSTR szText);
	void WriteLine(LPCTSTR szLine = _T(""));
	void SetOutputToNamedPipe(BOOL bOutToNamedPipe);
	void SetNamedPipeName(const CString& stPipeName);
	void CreateNamedPipe();
	void CloseNamedPipe();
	BOOL IsOutputToNamedPipe();
	CConsoleHepler();
	~CConsoleHepler();
	SINGLETON_CUSTOM_CON_DESTRUCTOR(CConsoleHepler)

private:				
	BOOL RedirectStdOut();
	BOOL WriteNamedPipe(const CString& stMsg);
	static BOOL m_bConsoleReady;
	static BOOL m_bOutToNamedPipe;
	static CNamedPipe* m_NamedPipe;
	static CString m_strPipeName;
};