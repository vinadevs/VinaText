/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

// DiffEngine ////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////
// Original version from S.Rodriguez - Feb 2003
//////////////////////////////////////////////////////////////////////
//
//

#include "stdafx.h"
#include "FilePartition.h"

// Constructor
CFileLine::CFileLine()
{
	SetStatus(Normal);
}

// Accessors
long CFileLine::SetLine(/*in*/CString &s, /*in*/CFileOptions &o) // store string and build token
{
	m_s = s;

	CString so = GetLineWithOptions(s,o);
	
	long nToken = 0;
	long nLength = so.GetLength();
	TCHAR *lpString = so.GetBuffer(0);

	for (long i=0; i<nLength; i++)
		nToken += 2*nToken + *(lpString++); // (George V. Reilly hint)

	return nToken;
}

void CFileLine::SetLine(/*in*/CString &s, /*in*/LineStatus ls) // store string and status (does not eval ID)
{
	m_s = s;
	SetStatus(ls);
}


CString CFileLine::GetLine(/*in*/CFileOptions &o)
{
	if ( o.IsDefaultOptions() )
		return m_s;
	else
		return GetLineWithOptions(m_s,o);
}
	

CString CFileLine::GetLineWithOptions(/*in*/CString s,/*in*/CFileOptions &o)
{
	if ( o.IsDefaultOptions() )
		return s;
	
	CString so = s;

	// should we take care about indentation differences ?
	CString szIndentoption = o.GetOption( CString("indent") );
	if ( !szIndentoption.IsEmpty() && szIndentoption != _T("yes"))
	{
		// no, then remove all 09 and 20 chars from the begin of the string
		long nSize = so.GetLength();
		if (nSize>0)
		{
			TCHAR c;
			BOOL bIndentation = TRUE;
			long i = 0;
			for (i=0; i<nSize && bIndentation; i++)
			{
				c = so.GetAt(i);
				if (c!=0x20 && c!=0x09)
					bIndentation = FALSE;
			}
			so = bIndentation ? so : so.Right( so.GetLength()+1 - i);
		}
	}

	// should we care about case differences ?
	CString szCaseoption = o.GetOption( CString("case") );
	if ( !szCaseoption.IsEmpty() && szCaseoption!= _T("yes"))
	{
		// no, then make sure we lower the case
		so.MakeLower();
	}

	return so;
}

void CFileLine::SetStatus(/*in*/LineStatus ls)
{
	m_status = ls;
}

LineStatus CFileLine::GetStatus()
{
	return m_status;
}

// CFileOptions /////////////////////////////////////////////////////
//

CFileOptions::CFileOptions()
{
}

// Accessors
void CFileOptions::SetOption(/*in*/CString &szOptionName, /*in*/CString &szOptionValue)
{
	// is it a new option ?
	long nSize = static_cast<long>(m_arrOptions.GetSize());
	BOOL bFound = FALSE;
	for (long i=0; i<nSize && !bFound; i++)
	{
		CString s = m_arrOptions.GetAt(i);
		if (!s.IsEmpty() && s.Find(szOptionName,0)==0)
		{
			bFound = TRUE;
			long n = s.Find(_T(';'),0);
			if (n>-1)
				s = s.Left(n) + _T(";") + szOptionValue;
			else
				s = s + _T(";") + szOptionValue;

			m_arrOptions.SetAt(i, s);
		}
	} // for

	if (!bFound)
	{
		CString s = szOptionName + _T(";") + szOptionValue;
		m_arrOptions.Add(s);
	}
}

CString CFileOptions::GetOption(/*in*/CString &szOptionName)
{
	long nSize = static_cast<long>(m_arrOptions.GetSize());
	for (long i=0; i<nSize; i++)
	{
		CString s = m_arrOptions.GetAt(i);
		if (!s.IsEmpty() && s.Find(szOptionName,0)==0)
		{
			long n = s.Find(_T(';'),0);
			if (n>-1)
				return s.Right( s.GetLength() - (n+1) );
			else
				return CString("");
		}
	} // for

	return CString("");
}

BOOL CFileOptions::IsDefaultOptions()
{
	return GetOptionCount()==0;
}

long CFileOptions::GetOptionCount()
{
	return static_cast<long>(m_arrOptions.GetSize());
}

CString CFileOptions::GetOption(long i)
{
	return (i>=0 && i<GetOptionCount()) ? m_arrOptions.GetAt(i) : CString("");
}

// Methods
void CFileOptions::Copy(CFileOptions &src)
{
	long nbOptions = src.GetOptionCount();
	for (long i=0; i<nbOptions; i++)
		m_arrOptions.Add( src.GetOption(i) );
}

// CFilePartition ///////////////////////////////////////////////////
//
//

CFilePartition::CFilePartition()
{
}

CFilePartition::~CFilePartition()
{
	// remember to destroy those CFileLine objects
	long nSize = GetNBLines();
	for (long i=0; i<nSize; i++)
		delete m_arrLines.GetAt(i);
}

void CFilePartition::SetName(CString &szName)
{
	m_szFilename = szName;
}

CString CFilePartition::GetName()
{
	return m_szFilename;
}

void CFilePartition::SetOptions(/*in*/CFileOptions &options)
{
	m_options.Copy(options);
}

long CFilePartition::GetNBLines()
{
	return static_cast<long>(m_arrLines.GetSize());;
}

CString CFilePartition::GetLine(/*in*/long i)
{
	ASSERT( i>=0 && i<GetNBLines());

	CFileLine *pLine = NULL;
	if (i>=0 && i<GetNBLines())
		pLine = m_arrLines.GetAt(i);

	return pLine ? pLine->GetLine(m_options) : CString("");
}

CString CFilePartition::GetRawLine(/*in*/long i) // returns an arbitrary line (not filtered)
{
	CFileOptions o; // default options

	ASSERT( i>=0 && i<GetNBLines());

	CFileLine *pLine = NULL;
	if (i>=0 && i<GetNBLines())
		pLine = m_arrLines.GetAt(i);

	return pLine ? pLine->GetLine(o) : CString("");
}

LineStatus CFilePartition::GetStatusLine(/*in*/long i)
{
	ASSERT( i>=0 && i<GetNBLines());

	CFileLine *pLine = NULL;
	if (i>=0 && i<GetNBLines())
		pLine = m_arrLines.GetAt(i);

	return pLine ? pLine->GetStatus() : Normal;
}

long *CFilePartition::GetTokens()
{
	return m_arrTokens.GetData();
}

void CFilePartition::HowManyChanges(/*out*/int &nAdded, /*out*/int &nChanged, /*out*/int &nDeleted)
{
	nAdded = nChanged = nDeleted = 0;

	LineStatus currentStatus = Normal;

	CFileLine *pLine = NULL;
	long nSize = GetNBLines();
	for (long i=0; i<nSize; i++)
	{
		pLine = m_arrLines.GetAt(i);
		if (!pLine) continue;

		LineStatus ls = pLine->GetStatus();
		if (ls!=Normal && currentStatus!=ls)
		{
			switch (ls)
			{
				case Added: nAdded++; break;
				case Changed: nChanged++; break;
				case Deleted: nDeleted++; break;
			}
		}
	} // end for all lines
}

// PreProcess
//
// purpose : reads a file, on a line-by-line basis
//
BOOL CFilePartition::PreProcess(/*in*/CString &szFilename, /*in*/CFileOptions &options)
{
	ASSERT( !szFilename.IsEmpty() );
	if (szFilename.IsEmpty())
	{
		OutputDebugString(_T("error : empty input filename\r\n"));
		return FALSE;
	}

	SetName(szFilename);
	SetOptions(options);

	// read the file first,
	// and build the table of tokens

	CStdioFile f;
	if ( !f.Open(szFilename, CFile::modeRead) )
	{
		TCHAR szError[MAX_PATH];
		wsprintf(szError, _T("error : cannot open %s\r\n"), szFilename.GetBuffer(0) );
		OutputDebugString(szError);
		return FALSE;
	}

	// 
	CString s;
	while ( f.ReadString(s) )
		AddString(s);

	f.Close();

	return TRUE;
}

// PreProcessFolder
//
// purpose : list folders, files and subfolders
//           and then build a tree-like list out of it
//
BOOL CFilePartition::PreProcessFolder(/*in*/CString &szFolder, /*in*/CFileOptions &options)
{

	SetName(szFolder);
	SetOptions(options);

	long nIndent = 0;

	// make sure there is no trailing backslash
	while (!szFolder.IsEmpty() && szFolder.GetAt( szFolder.GetLength()-1 )== _T('\\'))
		szFolder = szFolder.Left( szFolder.GetLength()-1 );

	return PreProcessFolder(szFolder, options, nIndent);
}

BOOL CFilePartition::PreProcessFolder(/*in*/CString &szFolder, /*in*/CFileOptions &options, /*in/out*/long nIndent)
{
	if (szFolder.IsEmpty()) return FALSE;

	CSortedArray arrFiles;

	long i;
	CString szIndent;
	for (i=0; i<nIndent; i++)
		szIndent += _T("  ");

	// add this folder
	CString szCurrentFolder = szFolder;
	int nBackSlash = szCurrentFolder.ReverseFind(_T('\\'));
	if (nBackSlash>-1)
		szCurrentFolder = szCurrentFolder.Right( szCurrentFolder.GetLength()-(nBackSlash+1) );

	// add the folder in the partition
	AddString( szIndent + _T("+ ") + szCurrentFolder );


	CString szFolderWildCard = szFolder + _T("\\*.*");

	WIN32_FIND_DATA findFile;
	HANDLE hContext;
	hContext=::FindFirstFile(szFolderWildCard.GetBuffer(0), &findFile);
	if (  hContext != INVALID_HANDLE_VALUE )
	{
		do
		{
			if (wcscmp(findFile.cFileName, _T("."))!=0
				&& wcscmp(findFile.cFileName, _T(".."))!=0)
			{

				if (findFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
				{
					// it's a folder
					//
					CString szSubFolder = szFolder + _T("\\") + findFile.cFileName;
					PreProcessFolder(szSubFolder, options, nIndent+1);
				}
				else
				{
					// it's a file
					//
					// GetInformationByHandle
					
					OFSTRUCT ofstruct;
					BY_HANDLE_FILE_INFORMATION infostruct;
					HFILE hFile = OpenFile(szFolder + "\\" + findFile.cFileName,
											 &ofstruct, 
											 OF_READ | OF_SHARE_DENY_NONE);
					if (hFile = HFILE_ERROR && ::GetFileInformationByHandle( (HANDLE)hFile, &infostruct))
					{
						SYSTEMTIME stCreate;

						// Convert the local file time from UTC to system time.
						FileTimeToSystemTime(&infostruct.ftLastWriteTime, &stCreate);

						TCHAR sDate[128];
						wsprintf(sDate, _T("%02d/%02d/%d  %02d:%02d"),
								stCreate.wDay, stCreate.wMonth, stCreate.wYear,
								stCreate.wHour, stCreate.wMinute);

						::_lclose(hFile);

						arrFiles.InsertSorted( CString(findFile.cFileName + CString(_T(" (")) + sDate + _T(")")) );
					}
				}

			}
		}
		while (	::FindNextFile(hContext, &findFile) );

		::FindClose(hContext);
	}

	// add all files at this point
	long nbFiles = static_cast<long>(arrFiles.GetSize());
	for (i=0; i<nbFiles; i++)
		AddString( szIndent + _T("    ") + arrFiles.GetAt(i) );

	return TRUE;
}


void CFilePartition::AddString(/*in*/CString &s, /*in*/LineStatus ls)
{
	CFileLine *p = new CFileLine();
	ASSERT(p);
	if (p)
	{
		p->SetLine(s, ls);
		m_arrLines.Add( p );
	}
}

void CFilePartition::AddBlankLine()
{
	AddString(CString(""), Normal);
}

void CFilePartition::AddString(/*in*/CString &s)
{
	CFileLine *p = new CFileLine();
	ASSERT(p);
	if (p)
	{
		m_arrTokens.Add( p->SetLine(s, m_options) );
		m_arrLines.Add( p );
	}
}

void CFilePartition::Dump(/*in*/CString &szTitle)
{
	TCHAR s[MAX_PATH];
	wsprintf(s, _T("%s : %d lines\r\n\r\n"), szTitle.GetBuffer(0), GetNBLines());
	OutputDebugString(s);

	long nSize = GetNBLines();
	for (long i=0; i<nSize; i++)
	{
		LineStatus ls = GetStatusLine(i);
		if (ls==Normal) 
			OutputDebugString(_T("Normal "));
		else if (ls==Changed)
			OutputDebugString(_T("Changed "));
		else if (ls==Added)
			OutputDebugString(_T("Added "));
		else if (ls==Deleted)
			OutputDebugString(_T("Deleted "));

		OutputDebugString( GetLine(i) );
		OutputDebugString(_T("\r\n"));
	}
}

BOOL CFilePartition::MatchLine(/*in*/long i1, /*in*/CFilePartition &f2, /*out*/long &i2)
{
	ASSERT( m_arrTokens.GetSize()>0 );
	if ( m_arrTokens.GetSize()==0 ) return FALSE;

	ASSERT( i1<GetNBLines() );
	if ( i1>=GetNBLines() ) return FALSE; // should never happen though

	// try to match the current token from f1, into the a subset of f2 tokens
	//
	
	long nf1Token;
	nf1Token = m_arrTokens[i1];

	long *pf2Tokens = f2.GetTokens();
	if (!pf2Tokens)
		return FALSE;

	BOOL bFound = FALSE;
	long i = 0;
	long nf2SubsetLines = f2.GetNBLines() - i2;

	long *pf2Token = pf2Tokens + i2; // points to the right token

	while (!bFound && i<nf2SubsetLines)
	{
		if (nf1Token == *pf2Token) // fast compare
		{
			// make sure strings really match
			bFound = ( GetLine(i1).Compare( f2.GetLine(i2+i) )==0 ); 
		}

		pf2Token++;
		i++;
	}
	i--;

	if (bFound)
	{
		i2 += i;
		return TRUE;
	}

	return FALSE;
}