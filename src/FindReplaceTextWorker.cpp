/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "FindReplaceTextWorker.h"
#include "AppUtil.h"
#include "PathUtil.h"
#include "OSUtil.h"
#include "EditorDoc.h"
#include "Editor.h"

constexpr int InitialProgress = 0;

void CFindTextWorker::SetTargetSearchFolder(const CString & strPath)
{
	m_strTargetSearchPath = strPath;
}

void CFindTextWorker::SetSearchWhat(const CString & strSearchWhat)
{
	m_strSearchWhat = strSearchWhat;
}

void CFindTextWorker::SetSearchOptions(int nSearchOptions)
{
	m_nSearchOptions = nSearchOptions;
}

void CFindTextWorker::SetIncludeSubFolder(BOOL bIncludeSubFolder)
{
	m_bIncludeSubFolder = bIncludeSubFolder;
}

void CFindTextWorker::SetParentWindow(CWnd* pWndParent)
{
	m_pWndParent = pWndParent;
}

BOOL CFindTextWorker::SearchForwardOnEditor(CEditorCtrl* pEditor, const CString& strSearchWhat, unsigned int nSearchOptions, BOOL bHideMessageBox)
{
	pEditor->SetSearchflags(nSearchOptions);
	if (!pEditor->SearchForward(strSearchWhat))
	{
		int nVisualLine = pEditor->GetFirstVisibleLine();
		int nCurPos = pEditor->GetCurrentPosition();
		pEditor->GotoPosition(0);
		if (!pEditor->SearchForward(strSearchWhat))
		{
			pEditor->SetFirstVisibleLine(nVisualLine);
			pEditor->GotoPosition(nCurPos);
			if (!bHideMessageBox)
			{
				::MessageBox(AfxGetMainWnd()->m_hWnd, AfxCStringFormat(_T("Word not found: %s"), strSearchWhat), _T("Search Text"), MB_ICONINFORMATION);
				return FALSE;
			}
		}
	}
	return TRUE;
}

BOOL CFindTextWorker::SearchBackwardOnEditor(CEditorCtrl* pEditor, const CString& strSearchWhat, unsigned int nSearchOptions, BOOL bHideMessageBox)
{
	pEditor->SetSearchflags(nSearchOptions);
	if (!pEditor->SearchBackward(strSearchWhat))
	{
		int nVisualLine = pEditor->GetFirstVisibleLine();
		int nCurPos = pEditor->GetCurrentPosition();
		int nLines = pEditor->GetLineCount();
		int nLineEndPos = pEditor->GetLineEndPosition(nLines);
		pEditor->GotoPosition(nLineEndPos);
		if (!pEditor->SearchBackward(strSearchWhat))
		{
			pEditor->SetFirstVisibleLine(nVisualLine);
			pEditor->GotoPosition(nCurPos);
			if (!bHideMessageBox)
			{
				::MessageBox(AfxGetMainWnd()->m_hWnd, AfxCStringFormat(_T("Word not found: %s"), strSearchWhat), _T("Search Text"), MB_ICONINFORMATION);
				return FALSE;
			}
		}
	}
	return TRUE;
}

BOOL CFindTextWorker::SearchAllInEditor(const CString& strFilePath,
	CEditorCtrl* pEditor,
	TEXT_RESULT_SEARCH_REPLACE_DATA& ResultSearchData,
	const CString& strSearchWhat,
	unsigned int nSearchOptions)
{
	unsigned int uiMatchedWords = 0;
	int nCurPosition = pEditor->GetCurrentPosition();
	int startRange = 0;
	int endRange = pEditor->GetTextLength();
	int targetStart = 0;
	int targetEnd = 0;
	int nSearchedLine = -1;
	// set search options
	pEditor->DoCommand(SCI_SETSEARCHFLAGS, nSearchOptions);
	while (targetStart != -1 && targetStart != -2)
	{
		targetStart = pEditor->SearchTextInRange(strSearchWhat, startRange, endRange);
		if (targetStart == -1 || targetStart == -2)
		{
			break;
		}
		targetEnd = static_cast<int>(pEditor->DoCommand(SCI_GETTARGETEND));
		if (targetEnd > endRange)
		{
			break;
		}
		int indicatorLength = targetEnd - targetStart;
		if (indicatorLength > 0)
		{
			uiMatchedWords++;
			int nCurSearchLine = pEditor->GetLineFromPosition(targetStart) + 1;
			if (nSearchedLine != nCurSearchLine)
			{
				nSearchedLine = nCurSearchLine;
				SEARCH_DATA_LINE dataLine;
				dataLine._nLineNumber = nCurSearchLine;
				dataLine._nColumnNumber = pEditor->GetColumnAtPosition(targetStart);
				dataLine._nPositionNumber = targetStart;
				CString strTextLine;
				pEditor->GetTextFromLine(nCurSearchLine, strTextLine);
				dataLine._strLine = strTextLine;
				dataLine._strTargetFile = strFilePath;
				ResultSearchData._vecSearchDataLine.push_back(dataLine);
			}
		}
		else
		{
			break;
		}
		if (targetStart + indicatorLength == endRange)
		{
			break;
		}
		startRange = targetStart + indicatorLength;
	}
	ResultSearchData._nMatchedWords += uiMatchedWords;
	ResultSearchData._nLineCounts += pEditor->GetLineCount();
	ResultSearchData._nSearchOptions = nSearchOptions;
	return uiMatchedWords > 0 ? TRUE : FALSE;
}

void CFindTextWorker::FindInFolder()
{
	CRect rectEditor;
	rectEditor.SetRectEmpty();
	std::unique_ptr<CEditorCtrl> pEditor = std::make_unique<CEditorCtrl>();
	pEditor->Create(_T("Search Editor"), WS_CHILD | WS_CLIPCHILDREN | WS_EX_RTLREADING, rectEditor, m_pWndParent, ID_EDITOR_CTRL_SEARCH);
	if (::IsWindow(pEditor->GetSafeHwnd()))
	{
		std::vector<CString> vecSearchPath;
		m_nFindProgress = InitialProgress;
		PathUtils::GetAllFilesFromFolder(m_strTargetSearchPath, vecSearchPath, m_bIncludeSubFolder);
		auto nTotalFile = vecSearchPath.size();
		for (auto const& searchpath : vecSearchPath)
		{
			m_ResultSearchData._nTotalSearchFile++;
			if (PathFileExists(searchpath) && CheckFileFilter(searchpath))
			{
				pEditor->SetTextToEditor(PathUtils::FileContentToUtf8(searchpath));
				m_ResultSearchData._vecSearchDataLine.reserve(m_ResultSearchData._vecSearchDataLine.size() + pEditor->GetLineCount());
				if (CFindTextWorker::SearchAllInEditor(searchpath, pEditor.get(), m_ResultSearchData, m_strSearchWhat, m_nSearchOptions))
				{
					m_ResultSearchData._nMatchedFiles++;
				}
				m_strCurSearchPath = searchpath;
				m_nFindProgress = InitialProgress + static_cast<int>(m_ResultSearchData._nTotalSearchFile * 100 / nTotalFile);
			}
		}
	}
}

BOOL CFindTextWorker::CheckFileFilter(const CString & strFilePath)
{
	if (m_FileFilters.empty()) return TRUE;
	if (m_FileFilters[0].Trim() == _T("*.*")) return TRUE;
	CString strFileExt = PathUtils::GetFileExtention(strFilePath);
	if (std::find_if(m_FileFilters.begin(), m_FileFilters.end(), [&](CString &strExt) {
		return strExt.Trim().Mid(2) == strFileExt.Trim();
	}) != m_FileFilters.end()) {
		return TRUE;
	}
	return FALSE;
}

void CFindTextWorker::SetFileFilter(const CString& strfileFilter)
{
	m_FileFilters = AppUtils::SplitterCString(strfileFilter, ";");
}

int CFindTextWorker::GetCurrentFindProgress() const
{
	return m_nFindProgress;
}

const CString& CFindTextWorker::GetCurrentSearchPath() const
{
	return m_strCurSearchPath;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CReplaceTextWorker::SetReplaceFolder(const CString & strFolder)
{
	m_strReplaceFolder = strFolder;
}

void CReplaceTextWorker::SetSearchWhat(const CString & strSearchWhat)
{
	m_strSearchWhat = strSearchWhat;
}

void CReplaceTextWorker::SetReplaceWith(const CString & strReplaceWith)
{
	m_strReplaceWith = strReplaceWith;
}

void CReplaceTextWorker::SetSearchOptions(int nSearchOptions)
{
	m_nSearchOptions = nSearchOptions;
}

void CReplaceTextWorker::SetIncludeSubFolder(BOOL bIncludeSubFolder)
{
	m_bIncludeSubFolder = bIncludeSubFolder;
}

int CReplaceTextWorker::GetCurrentReplaceProgress() const
{
	return m_nReplaceProgress;
}

const CString& CReplaceTextWorker::GetCurrentReplacePath() const
{
	return m_strCurReplacePath;
}

void CReplaceTextWorker::ReplaceInFolder()
{
	CRect rectEditor;
	rectEditor.SetRectEmpty();
	std::unique_ptr<CEditorCtrl> pEditor = std::make_unique<CEditorCtrl>();
	pEditor->Create(_T("Replace Editor"), WS_CHILD | WS_CLIPCHILDREN | WS_EX_RTLREADING, rectEditor, m_pWndParent, ID_EDITOR_CTRL_SEARCH);
	if (::IsWindow(pEditor->GetSafeHwnd()))
	{
		std::vector<CString> vecFindPath, vecReplacePath;
		m_nReplaceProgress = InitialProgress;
		PathUtils::GetAllFilesFromFolder(m_strReplaceFolder, vecFindPath, m_bIncludeSubFolder);
		for (auto const& findpath : vecFindPath)
		{
			if (PathFileExists(findpath) && !PathUtils::IsFileReadOnly(findpath))
			{
				if (CheckFileFilter(findpath))
				{
					vecReplacePath.push_back(findpath);
				}
			}
			else
			{
				m_listFailedReplaceFiles.push_back(findpath);
			}
		}
		auto nTotalFile = vecReplacePath.size();
		for (auto const& replacepath : vecReplacePath)
		{
			m_ResultReplaceData._nTotalSearchFile++;
			if (CheckFileFilter(replacepath))
			{
				pEditor->SetTextToEditor(PathUtils::FileContentToUtf8(replacepath));
				m_ResultReplaceData._vecSearchDataLine.reserve(m_ResultReplaceData._vecSearchDataLine.size() + pEditor->GetLineCount());
				if (CReplaceTextWorker::ReplaceAllInEditor(replacepath, pEditor.get(), m_ResultReplaceData, m_strSearchWhat, m_strReplaceWith, m_nSearchOptions))
				{
					m_ResultReplaceData._nMatchedFiles++;
					pEditor->SaveFile(replacepath);
				}
				m_strCurReplacePath = replacepath;
				m_nReplaceProgress = InitialProgress + static_cast<int>(m_ResultReplaceData._nTotalSearchFile * 100 / nTotalFile);
			}
		}
	}
}

BOOL CReplaceTextWorker::CheckFileFilter(const CString & strFilePath)
{
	if (m_FileFilters.empty()) return TRUE;
	if (m_FileFilters[0].Trim() == _T("*.*")) return TRUE;
	CString strFileExt = PathUtils::GetFileExtention(strFilePath);
	if (std::find_if(m_FileFilters.begin(), m_FileFilters.end(), [&](CString &strExt) {
		return strExt.Trim().Mid(2) == strFileExt.Trim();
	}) != m_FileFilters.end()) {
		return TRUE;
	}
	return FALSE;
}

void CReplaceTextWorker::SetFileFilter(const CString& strfileFilter)
{
	m_FileFilters = AppUtils::SplitterCString(strfileFilter, ";");
}

void CReplaceTextWorker::SetParentWindow(CWnd* pWndParent)
{
	m_pWndParent = pWndParent;
}

BOOL CReplaceTextWorker::ReplaceForwardOnEditor(CEditorCtrl* pEditor, const CString& strSearchWhat, const CString& strReplaceWith, unsigned int nSearchOptions, BOOL bHideMessageBox)
{
	pEditor->SetSearchflags(nSearchOptions);
	if (pEditor->ReplaceNext(strSearchWhat, strReplaceWith) == -1)
	{
		if (!bHideMessageBox)
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd, AfxCStringFormat(_T("Word not found: %s"), strSearchWhat), _T("Replace Text"), MB_ICONINFORMATION);
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CReplaceTextWorker::ReplaceAllInEditor(const CString& strFilePath, CEditorCtrl* pEditor, TEXT_RESULT_SEARCH_REPLACE_DATA& ResultSearchData, const CString& strSearchWhat, const CString& strReplaceWith, unsigned int nSearchOptions)
{
	pEditor->SetSearchflags(nSearchOptions);
	ResultSearchData._nSearchOptions = nSearchOptions;
	pEditor->BeginUndoTransactions();
	BOOL bMatchedFile = pEditor->ReplaceAll(strFilePath, strSearchWhat, strReplaceWith, ResultSearchData);
	pEditor->EndUndoTransactions();
	return bMatchedFile;
}

BOOL CReplaceTextWorker::ReplaceAllInSelection(CEditorCtrl* pEditor, const CString& strSearchWhat, const CString& strReplaceWith, unsigned int nSearchOptions)
{
	pEditor->SetSearchflags(nSearchOptions);
	pEditor->BeginUndoTransactions();
	BOOL bMatchedFile = pEditor->ReplaceAllInSelection(strSearchWhat, strReplaceWith);
	pEditor->EndUndoTransactions();
	return bMatchedFile;
}

void CReplaceTextWorker::ReportFailedCases()
{
	// log list failed file
	if (m_listFailedReplaceFiles.size() > 0)
	{
		CString strLog;
		AfxMessageBox(_T("Replacement finished but some file(s) has read only attribute, please check Message Window for detail."), MB_ICONINFORMATION);
		for (auto const& path : m_listFailedReplaceFiles)
		{
			strLog += path + EDITOR_NEW_LINE_LF;
		}
		LOG_OUTPUT_MESSAGE_COLOR(_T("\n___________| REPLACE TEXT - READ ONLY FILE(S) |________________________________________\n"));
		LOG_OUTPUT_MESSAGE_COLOR(strLog);
	}
}