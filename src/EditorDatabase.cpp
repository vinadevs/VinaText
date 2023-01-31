/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "EditorDatabase.h"

/////////////////////////// DATABASE FOR LANGUAGE /////////////////////////////////

void CLanguageDatabase::SetLanguageName(const CString & str)
{
	m_strLanguageName = str;
}

void CLanguageDatabase::SetLanguageExtension(const CString & str)
{
	m_strExtension = str;
}

void CLanguageDatabase::SetLanguageCommentSymbol(const CString & str)
{
	m_strCommentLine = str;
}

void CLanguageDatabase::SetLanguageCommentStart(const CString & str)
{
	m_strCommentStart = str;
}

void CLanguageDatabase::SetLanguageCommentEnd(const CString & str)
{
	m_strCommentEnd = str;
}

void CLanguageDatabase::SetLanguageAutoComplete(const CString & str)
{
	m_strKeyWords = str;
}

void CLanguageDatabase::SetCompilerPath(const CString & str)
{
	m_strCompilerPath = str;
}

void CLanguageDatabase::SetDebuggerPath(const CString & str)
{
	m_steDebuggerPath = str;
}

void CLanguageDatabase::SetSnipppetCode(const CString & str)
{
	m_strSnipppetCode = str;
}

CString CLanguageDatabase::GetLanguageName() const
{
	return m_strLanguageName;
}

CString CLanguageDatabase::GetLanguageExtension() const
{
	return m_strExtension;
}

CString CLanguageDatabase::GetLanguageCommentSymbol() const
{
	return m_strCommentLine;
}

CString CLanguageDatabase::GetLanguageCommentStart() const
{
	return m_strCommentStart;
}

CString CLanguageDatabase::GetLanguageCommentEnd() const
{
	return m_strCommentEnd;
}

CString CLanguageDatabase::GetLanguageKeyWords() const
{
	return m_strKeyWords;
}

CString CLanguageDatabase::GetCompilerPath() const
{
	return m_strCompilerPath;
}

CString CLanguageDatabase::GetDebuggerPath() const
{
	return m_steDebuggerPath;
}

CString CLanguageDatabase::GetSnipppetCode() const
{
	return m_strSnipppetCode;
}
