/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

/////////////////////////// DATABASE FOR LANGUAGE /////////////////////////////////

class CLanguageDatabase
{
public:
	CLanguageDatabase() = default;
	virtual ~CLanguageDatabase() = default;
	
	void SetLanguageName(const CString& str);
	void SetLanguageExtension(const CString& str);
	void SetLanguageCommentSymbol(const CString& str);
	void SetLanguageCommentStart(const CString& str);
	void SetLanguageCommentEnd(const CString& str);
	void SetLanguageAutoComplete(const CString& str);
	void SetCompilerPath(const CString& str);
	void SetDebuggerPath(const CString& str);
	void SetSnipppetCode(const CString& str);

	CString GetLanguageName() const;
	CString GetLanguageExtension() const;
	CString GetLanguageCommentSymbol() const;
	CString GetLanguageCommentStart() const;
	CString GetLanguageCommentEnd() const;
	CString GetLanguageKeyWords() const;
	CString GetCompilerPath() const;
	CString GetDebuggerPath() const;
	CString GetSnipppetCode() const;

private:
	CString m_strLanguageName;
	CString m_strExtension;
	CString m_strCommentLine;
	CString m_strCommentStart;
	CString m_strCommentEnd;
	CString m_strKeyWords;
	CString m_strCompilerPath;
	CString m_steDebuggerPath;
	CString m_strSnipppetCode;
};