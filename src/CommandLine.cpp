/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "CommandLine.h"
#include "CommandLine.h"

#pragma warning (disable:4312)

CCommandLineInfoEx::CCommandLineInfoEx()
{
}

CCommandLineInfoEx::~CCommandLineInfoEx()
{
}

void CCommandLineInfoEx::ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast)
{
	CString strParam(pszParam);
	if (bFlag)
	{
		if (strParam == _T("moveFileToNewInstance"))
		{
			m_cmdOption = VINATEXT_CMD_OPTION::VINATEXT_CMD_MOVE_TO_NEW_WINDOW;
			return;
		}
		else if (strParam == _T("openWithAdminRight"))
		{
			m_cmdOption = VINATEXT_CMD_OPTION::VINATEXT_CMD_REOPEN_WITH_ADMIN_RIGHT;
			return;
		}
	}
	CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
}

////////////////////////////////////////////////////////////////////////

BOOL CConsoleHepler::m_bOutToNamedPipe = FALSE;
CString CConsoleHepler::m_strPipeName = PIPE_CMD_OUTPUT_CONSOLE
CNamedPipe* CConsoleHepler::m_NamedPipe = NULL;
BOOL CConsoleHepler::m_bConsoleReady = FALSE;

CConsoleHepler::CConsoleHepler()
{
}

CConsoleHepler::~CConsoleHepler()
{
	Close();
}

void CConsoleHepler::SetOutputToNamedPipe(BOOL bOutToNamedPipe)
{
	m_bOutToNamedPipe = bOutToNamedPipe;
}

BOOL CConsoleHepler::Open()
{
	if (m_bConsoleReady ||   // The console is already Open and Ready
		m_bOutToNamedPipe)  // Or the output goes to a named pipe
		return TRUE;

	// Standard output
	if (!m_bOutToNamedPipe)
	{
		FreeConsole(); // This is done to prevent "Access denied" error

		BOOL bConsoleExists = FALSE;

		if (AttachConsole(ATTACH_PARENT_PROCESS))
		{
			bConsoleExists = TRUE;
		}
		else if (AllocConsole()) // If still it's not possible to attach the console to the parent console (or there is no parent console) try to alloc our own new console
		{
			bConsoleExists = TRUE;
		}

		// Now we have a console, try to redirect GUI stdout to it
		if (bConsoleExists)
		{
			if (RedirectStdOut())
				m_bConsoleReady = TRUE;
			else
				m_bConsoleReady = FALSE;
		}
		else
			m_bConsoleReady = FALSE;

		if (m_bConsoleReady)
			_tsetlocale(LC_ALL, _T(""));  // Set Console output to the System's locale settings
	}

	return m_bConsoleReady;
}

BOOL CConsoleHepler::Close()
{
	if (!m_bOutToNamedPipe)
	{
		m_bConsoleReady = FALSE;
		return FreeConsole();
	}
	return TRUE;
}

void CConsoleHepler::Write(LPCTSTR szText)
{
	CString stText(szText);

	if (m_bConsoleReady)
	{
		if (!m_bOutToNamedPipe) // stdout
		{
			int nCharCnt;
			HANDLE std_out = GetStdHandle(STD_OUTPUT_HANDLE);
			WriteConsole(std_out, (const char*)(LPCTSTR)stText, (DWORD)stText.GetLength(), (LPDWORD)&nCharCnt, NULL);
		}
		else // named pipe
		{
			WriteNamedPipe(szText);
		}
	}
}

void CConsoleHepler::WriteLine(LPCTSTR szText)
{
	CString stNewLine(szText);
	stNewLine += _T("\n");

	if (m_bConsoleReady)
	{
		Write(stNewLine);
	}
}

BOOL CConsoleHepler::RedirectStdOut()
{
	int osfh = _open_osfhandle((intptr_t)GetStdHandle(STD_OUTPUT_HANDLE), 8); // 8 = Append mode
	if ((HANDLE)osfh != INVALID_HANDLE_VALUE)
	{
		*stdout = *_tfdopen(osfh, _T("a"));	// Open in append mode
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CConsoleHepler::SetNamedPipeName(const CString& stPipeName)
{
	m_strPipeName = stPipeName;
}

BOOL CConsoleHepler::WriteNamedPipe(const CString& stMsg)
{
	// Write the string down the named pipe								
	CStringA sMsgA(stMsg);

	char szWriteBuf[4096];
	strcpy_s(szWriteBuf, (const char *)sMsgA);

	DWORD dwWritten = 0;
	if (!m_NamedPipe->Write(&szWriteBuf, sizeof(szWriteBuf) - sizeof(char), &dwWritten))
	{
		return FALSE;
	}

	m_NamedPipe->Flush();
	return TRUE;
}

void CConsoleHepler::CloseNamedPipe()
{
	if (m_NamedPipe)
	{
		m_NamedPipe->Disconnect();
		delete m_NamedPipe;
	}
}

BOOL CConsoleHepler::IsOutputToNamedPipe()
{
	return m_bOutToNamedPipe;
}

void CConsoleHepler::CreateNamedPipe()
{
	m_NamedPipe = new CNamedPipe;

	if (m_strPipeName.IsEmpty())
	{
		return;
	}

	// Create the server pipe
	if (!m_NamedPipe->Create(m_strPipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_WAIT, 1, 4096, 4096, 1, NULL))
	{
		return;
	}

	// the thread will block until connected
	if (!m_NamedPipe->Connect())
	{
		return;
	}

	m_bConsoleReady = TRUE;

}