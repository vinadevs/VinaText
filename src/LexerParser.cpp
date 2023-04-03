/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "LexerParser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CLexingParser::CLexingParser()
{
	m_nPosition = 0;
}

CLexingParser::CLexingParser(const CString string, CString strDelim)
{
	m_Copy = string;
	m_Delimiter = strDelim;
	m_nPosition = 0;
}

CLexingParser::~CLexingParser()
{
}

void CLexingParser::SetString(const CString string)
{
	m_Copy = string;
	m_nPosition = 0;
}

CString CLexingParser::Next()
{
	CString strReturn;
	int nLen = m_Copy.GetLength();
	// if we have more characters in string
	while (nLen > m_nPosition)
	{
		//    check all delimiters
		for (int i = 0; i < m_Delimiter.GetLength(); i++)
		{
			//       if we find a delimiter or we find end of string return
			if (m_Copy.GetAt(m_nPosition) == m_Delimiter.GetAt(i))
			{
				m_nPosition++;
				return strReturn;
			}
		}
		//    copy char
		strReturn += m_Copy.GetAt(m_nPosition);
		m_nPosition++;
	}
	return strReturn;
}

BOOL CLexingParser::HasMoreTokens()
{
	if (m_nPosition == m_Copy.GetLength())
		return FALSE;
	return TRUE;
}

CString CLexingParser::NextString(BOOL bRemoveQuotes, CString strDefault)
{
	CString strReturn;
	int nLen = m_Copy.GetLength();
	// at end - return default
	if (nLen <= m_nPosition)
		return strDefault;
	// skip quotes if not wanted
	if (bRemoveQuotes)
	{
		//    skip to first quote
		while (nLen > m_nPosition && m_Copy.GetAt(m_nPosition) != '\"')
			m_nPosition++;
		m_nPosition++; // skip quote
  //    copy
		while (nLen > m_nPosition && m_Copy.GetAt(m_nPosition) != '\"')
		{
			strReturn += m_Copy.GetAt(m_nPosition);
			m_nPosition++;
		}
		m_nPosition++; // skip quote
  //    skip to next delimiter
		while (nLen > m_nPosition)
		{
			//       check all delimiters
			for (int i = 0; i < m_Delimiter.GetLength(); i++)
			{
				//          if we find a delimiter or we find end of string return
				if (m_Copy.GetAt(m_nPosition) == m_Delimiter.GetAt(i))
				{
					m_nPosition++;
					return strReturn;
				}
			}
		}
		return strReturn;
	}
	// if we have more characters in string
	while (nLen > m_nPosition)
	{
		//    check all delimiters
		for (int i = 0; i < m_Delimiter.GetLength(); i++)
		{
			//       if we find a delimiter or we find end of string return
			if (m_Copy.GetAt(m_nPosition) == m_Delimiter.GetAt(i))
			{
				m_nPosition++;
				return strReturn;
			}
		}
		//    copy char 
		strReturn += m_Copy.GetAt(m_nPosition);
		m_nPosition++;
	}
	// we did not find any tokens simply return 
	return strReturn;
}

int CLexingParser::NextInt(int nDefault)
{
	CString strReturn;
	int nLen = m_Copy.GetLength();
	// if we have more characters in string
	while (nLen > m_nPosition)
	{
		//    check all delimiters
		for (int i = 0; i < m_Delimiter.GetLength(); i++)
		{
			//       if we find a delimiter or we find end of string return
			if (m_Copy.GetAt(m_nPosition) == m_Delimiter.GetAt(i))
			{
				m_nPosition++;
				int nReturn = nDefault;
				int nFields = ::sscanf_s((LPCSTR)(LPCTSTR)strReturn, "%d", &nReturn);
				return nReturn;
			}
		}
		//    copy char
		strReturn += m_Copy.GetAt(m_nPosition);
		m_nPosition++;
	}
	int nReturn = nDefault;
	int nFields = ::sscanf_s((LPCSTR)(LPCTSTR)strReturn, "%d", &nReturn);
	return nReturn;
}

long CLexingParser::NextLong(long nDefault)
{
	CString strReturn;
	int nLen = m_Copy.GetLength();
	// if we have more characters in string
	while (nLen > m_nPosition)
	{
		//    check all delimiters
		for (int i = 0; i < m_Delimiter.GetLength(); i++)
		{
			//       if we find a delimiter or we find end of string return
			if (m_Copy.GetAt(m_nPosition) == m_Delimiter.GetAt(i))
			{
				m_nPosition++;
				long nReturn = nDefault;
				int nFields = ::sscanf_s((LPCSTR)(LPCTSTR)strReturn, "%ld", &nReturn);
				return nReturn;
			}
		}
		//    copy char
		strReturn += m_Copy.GetAt(m_nPosition);
		m_nPosition++;
	}
	long nReturn = nDefault;
	int nFields = ::sscanf_s((LPCSTR)(LPCTSTR)strReturn, "%ld", &nReturn);
	return nReturn;
}

float CLexingParser::NextFloat(float fDefault)
{
	CString strReturn;
	int nLen = m_Copy.GetLength();
	// if we have more characters in string
	while (nLen > m_nPosition)
	{
		//    check all delimiters
		for (int i = 0; i < m_Delimiter.GetLength(); i++)
		{
			//       if we find a delimiter or we find end of string return
			if (m_Copy.GetAt(m_nPosition) == m_Delimiter.GetAt(i))
			{
				m_nPosition++;
				float fReturn = fDefault;
				strReturn.Replace(',', '.'); // replace comma with dot for german numbers
				int nFields = ::sscanf_s((LPCSTR)(LPCTSTR)strReturn, "%g", &fReturn);
				return fReturn;
			}
		}
		//    copy char
		strReturn += m_Copy.GetAt(m_nPosition);
		m_nPosition++;
	}
	float fReturn = fDefault;
	strReturn.Replace(',', '.'); // replace comma with dot for german numbers
	int nFields = ::sscanf_s((LPCSTR)(LPCTSTR)strReturn, "%g", &fReturn);
	return fReturn;
}

double CLexingParser::NextDouble(double fDefault)
{
	CString strReturn;
	int nLen = m_Copy.GetLength();
	// if we have more characters in string
	while (nLen > m_nPosition)
	{
		//    check all delimiters
		for (int i = 0; i < m_Delimiter.GetLength(); i++)
		{
			//       if we find a delimiter or we find end of string return
			if (m_Copy.GetAt(m_nPosition) == m_Delimiter.GetAt(i))
			{
				m_nPosition++;
				double fReturn = fDefault;
				strReturn.Replace(',', '.'); // replace comma with dot for german numbers
				int nFields = ::sscanf_s((LPCSTR)(LPCTSTR)strReturn, "%lg", &fReturn);
				return fReturn;
			}
		}
		//    copy char
		strReturn += m_Copy.GetAt(m_nPosition);
		m_nPosition++;
	}
	double fReturn = fDefault;
	strReturn.Replace(',', '.'); // replace comma with dot for german numbers
	int nFields = ::sscanf_s((LPCSTR)(LPCTSTR)strReturn, "%lg", &fReturn);
	return fReturn;
}

BOOL CLexingParser::NextBool(BOOL bDefault)
{
	CString strReturn;
	int nLen = m_Copy.GetLength();
	// if we have more characters in string
	while (nLen > m_nPosition)
	{
		//    check all delimiters
		for (int i = 0; i < m_Delimiter.GetLength(); i++)
		{
			//       if we find a delimiter or we find end of string return
			if (m_Copy.GetAt(m_nPosition) == m_Delimiter.GetAt(i))
			{
				m_nPosition++;
				int nReturn = 0;
				int nFields = ::sscanf_s((LPCSTR)(LPCTSTR)strReturn, "%d", &nReturn);
				//          if we cant translate to number try keyword
				if (nFields < 1)
				{
					if (strReturn.CompareNoCase(BOOL_TRUE) == 0)
						return TRUE;
					else if (strReturn.CompareNoCase(BOOL_FALSE) == 0)
						return FALSE;
					else
						return bDefault;
				}
				else if (nReturn == 0)
					return FALSE;
				else
					return TRUE;
			}
		}
		//    copy char
		strReturn += m_Copy.GetAt(m_nPosition);
		m_nPosition++;
	}
	int nReturn = 0;
	int nFields = ::sscanf_s((LPCSTR)(LPCTSTR)strReturn, "%d", &nReturn);
	// if we cant translate to number try keyword
	if (nFields < 1)
	{
		if (strReturn.CompareNoCase(BOOL_TRUE) == 0)
			return TRUE;
		else if (strReturn.CompareNoCase(BOOL_FALSE) == 0)
			return FALSE;
		else
			return bDefault;
	}
	else if (nReturn == 0)
		return FALSE;
	else
		return TRUE;
}
