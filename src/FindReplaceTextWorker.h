/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "SearchEngine.h"

class CEditorDoc;
class CEditorCtrl;

class CFindWorker
{
public:
	CFindWorker() = default;
	~CFindWorker() = default;
	void SetFindFolder(const CString& strFolder);
	void SetSearchWhat(const CString& strSearchWhat);
	void SetSearchOptions(int nSearchOptions);
	void SetIncludeSubFolder(BOOL bIncludeSubFolder);
	int GetCurrentFindProgress()const;
	void FindInFolder();
	BOOL CheckFileFilter(const CString& strfileFilter);
	void SetFileFilter(const CString& strFilePath);

	// return result data
	TEXT_RESULT_SEARCH_REPLACE_DATA m_ResultSearchData;
private:
	CString m_strFindFolder;
	CString m_strSearchWhat;
	int m_nSearchOptions = 0;
	int m_nFindProgress = 0;
	BOOL m_bIncludeSubFolder = TRUE;
	std::vector<CString> m_FileFilters;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CReplaceWorker
{
public:
	CReplaceWorker() = default;
	~CReplaceWorker() = default;
	void SetActiveDocument(CEditorDoc* pActiveDoc);
	void SetReplaceFolder(const CString& strFolder);
	void SetSearchWhat(const CString& strSearchWhat);
	void SetReplaceWith(const CString& strReplaceWith);
	void SetSearchOptions(int nSearchOptions);
	void SetIncludeSubFolder(BOOL bIncludeSubFolder);
	int GetCurrentReplaceProgress()const;
	void ReplaceInFolder();
	void SetFileFilter(const CString& strfileFilter);
	BOOL CheckFileFilter(const CString& strFilePath);

	// return result data
	TEXT_RESULT_SEARCH_REPLACE_DATA m_ResultReplaceData;

	// failed replace files
	std::vector<CString> m_listFailedReplaceFiles;

	static void ReplaceInDocument(const CString& strDocPath, const std::vector<CString>& listInputLine,
		std::wstring replace_what,
		std::wstring replace_with,
		std::vector<RESULT_SEARCH_DATA>& vecResultSearchInfo,
		unsigned int & nMatchedFiles,
		unsigned int & nMatchedWords,
		unsigned int& nLineCounts,
		int nSearchOptions,
		CEditorCtrl * pCScintillaEditor = NULL,
		BOOL bHasTrailingReturn = FALSE);

	static void ReplaceInFilePath(std::wstring inputfile, std::wstring outputfile,
		std::wstring replace_what, std::wstring replace_with,
		std::vector<RESULT_SEARCH_DATA>& vecResultSearchInfo,
		unsigned int & nMatchedFiles,
		unsigned int& nMatchedWords,
		unsigned int& nLineCounts,
		int nSearchOptions,
		CEditorCtrl* pCScintillaEditor = NULL);

private:
	CString m_strReplaceFolder;
	CString m_strSearchWhat;
	CString m_strReplaceWith;
	int m_nSearchOptions = 0;
	int m_nReplaceProgress = 0;
	BOOL m_bIncludeSubFolder = TRUE;
	CEditorDoc* m_pActiveDoc = NULL;
	std::vector<CString> m_FileFilters;
};