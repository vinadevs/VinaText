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

#define ID_EDITOR_CTRL_SEARCH 103

class CFindTextWorker
{
public:
	CFindTextWorker() = default;
	~CFindTextWorker() = default;
	void SetTargetSearchFolder(const CString& strPath);
	void SetSearchWhat(const CString& strSearchWhat);
	void SetSearchOptions(int nSearchOptions);
	void SetIncludeSubFolder(BOOL bIncludeSubFolder);
	void SetParentWindow(CWnd* pWndParent);
	int GetCurrentFindProgress() const;
	const CString& GetCurrentSearchPath() const;
	void FindInFolder();
	BOOL CheckFileFilter(const CString& strfileFilter);
	void SetFileFilter(const CString& strFilePath);

	static BOOL SearchAllInEditor(const CString& strFilePath, CEditorCtrl* pEditor, TEXT_RESULT_SEARCH_REPLACE_DATA& ResultSearchData, const CString& strSearchWhat, unsigned int nSearchOptions);
	static void SearchForwardOnEditor(CEditorCtrl* pEditor, const CString& strSearchWhat, unsigned int nSearchOptions, BOOL bHideMessageBox = FALSE);
	static void SearchBackwardOnEditor(CEditorCtrl* pEditor, const CString& strSearchWhat, unsigned int nSearchOptions, BOOL bHideMessageBox = FALSE);

	// return result data
	TEXT_RESULT_SEARCH_REPLACE_DATA m_ResultSearchData;
private:
	CString m_strTargetSearchPath;
	CString m_strSearchWhat;
	CString m_strCurSearchPath;
	int m_nSearchOptions = 0;
	int m_nFindProgress = 0;
	BOOL m_bIncludeSubFolder = TRUE;
	CWnd* m_pWndParent{nullptr};
	std::vector<CString> m_FileFilters;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CReplaceTextWorker
{
public:
	CReplaceTextWorker() = default;
	~CReplaceTextWorker() = default;
	void SetReplaceFolder(const CString& strFolder);
	void SetSearchWhat(const CString& strSearchWhat);
	void SetReplaceWith(const CString& strReplaceWith);
	void SetSearchOptions(int nSearchOptions);
	void SetIncludeSubFolder(BOOL bIncludeSubFolder);
	int GetCurrentReplaceProgress() const;
	const CString& GetCurrentReplacePath() const;
	void ReplaceInFolder();
	void SetFileFilter(const CString& strfileFilter);
	BOOL CheckFileFilter(const CString& strFilePath);
	void SetParentWindow(CWnd* pWndParent);
	void ReportFailedCases();

	static void ReplaceForwardOnEditor(CEditorCtrl* pEditor, const CString& strSearchWhat, const CString& strReplaceWith, unsigned int nSearchOptions, BOOL bHideMessageBox = FALSE);
	static BOOL ReplaceAllInEditor(const CString& strFilePath, CEditorCtrl* pEditor, TEXT_RESULT_SEARCH_REPLACE_DATA& ResultSearchData, const CString& strSearchWhat, const CString& strReplaceWith, unsigned int nSearchOptions);
	static BOOL ReplaceAllInSelection(CEditorCtrl* pEditor, const CString& strSearchWhat, const CString& strReplaceWith, unsigned int nSearchOptions);

	// return result data
	TEXT_RESULT_SEARCH_REPLACE_DATA m_ResultReplaceData;

	// failed replace files
	std::vector<CString> m_listFailedReplaceFiles;

private:
	CString m_strReplaceFolder;
	CString m_strSearchWhat;
	CString m_strReplaceWith;
	CString m_strCurReplacePath;
	int m_nSearchOptions = 0;
	int m_nReplaceProgress = 0;
	BOOL m_bIncludeSubFolder = TRUE;
	CWnd* m_pWndParent{ nullptr };
	std::vector<CString> m_FileFilters;
};