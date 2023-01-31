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
#include "EditorDoc.h"
#include "Editor.h"

void CFindWorker::SetFindFolder(const CString & strFolder)
{
	m_strFindFolder = strFolder;
}

void CFindWorker::SetSearchWhat(const CString & strSearchWhat)
{
	m_strSearchWhat = strSearchWhat;
}

void CFindWorker::SetSearchOptions(int nSearchOptions)
{
	m_nSearchOptions = nSearchOptions;
}

void CFindWorker::SetIncludeSubFolder(BOOL bIncludeSubFolder)
{
	m_bIncludeSubFolder = bIncludeSubFolder;
}

void CFindWorker::FindInFolder()
{
	std::vector<CString> vecFilePath;
	m_nFindProgress = 20;
	PathUtils::GetAllFilesFromFolder(m_strFindFolder, vecFilePath, m_bIncludeSubFolder);
	auto nTotalFile = vecFilePath.size();
	for (auto const& filepath : vecFilePath)
	{
		m_ResultSearchData._nTotalSearchFile++;
		if (PathFileExists(filepath) && CheckFileFilter(filepath))
		{
			std::wstring strFile = AppUtils::CStringToWStd(filepath);
			std::wifstream fileTarget;
			std::wstring strLine;
			fileTarget.open(strFile.c_str());
			if (fileTarget.is_open())
			{
				unsigned int curLine = 0;
				while (std::getline(fileTarget, strLine))
				{
					curLine++;
					auto nWordCount = (unsigned int)VinaTextSearchEngine::COUNT_WORD(strLine.c_str(), AppUtils::CStringToWStd(m_strSearchWhat).c_str(), m_nSearchOptions);
					if (nWordCount > 0)
					{
						m_ResultSearchData._nMatchedFiles++;
						m_ResultSearchData._nMatchedWords += nWordCount;
						RESULT_SEARCH_DATA data;
						data._nMatched = nWordCount;
						data._nLineNumber = curLine;
						data._strLine = AppUtils::WStdToCString(strLine);
						data._strTargetFile = filepath;
						m_ResultSearchData._vecResultSearchInfo.push_back(data);
					}
				}
				fileTarget.close();
				m_ResultSearchData._nLineCounts += curLine;
			}
			m_nFindProgress = 20 + static_cast<int>(m_ResultSearchData._nTotalSearchFile * 80 / nTotalFile);
		}
	}
}

BOOL CFindWorker::CheckFileFilter(const CString & strFilePath)
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

void CFindWorker::SetFileFilter(const CString& strfileFilter)
{
	m_FileFilters = AppUtils::SplitterCString(strfileFilter, ";");
}

int CFindWorker::GetCurrentFindProgress() const
{
	return m_nFindProgress;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CReplaceWorker::SetActiveDocument(CEditorDoc * pActiveDoc)
{
	m_pActiveDoc = pActiveDoc;
}

void CReplaceWorker::SetReplaceFolder(const CString & strFolder)
{
	m_strReplaceFolder = strFolder;
}

void CReplaceWorker::SetSearchWhat(const CString & strSearchWhat)
{
	m_strSearchWhat = strSearchWhat;
}

void CReplaceWorker::SetReplaceWith(const CString & strReplaceWith)
{
	m_strReplaceWith = strReplaceWith;
}

void CReplaceWorker::SetSearchOptions(int nSearchOptions)
{
	m_nSearchOptions = nSearchOptions;
}

void CReplaceWorker::SetIncludeSubFolder(BOOL bIncludeSubFolder)
{
	m_bIncludeSubFolder = bIncludeSubFolder;
}

int CReplaceWorker::GetCurrentReplaceProgress() const
{
	return m_nReplaceProgress;
}

void CReplaceWorker::ReplaceInFolder()
{
	std::vector<CString> vecFindPath, vecReplacePath;
	m_nReplaceProgress = 20;
	PathUtils::GetAllFilesFromFolder(m_strReplaceFolder, vecFindPath, m_bIncludeSubFolder);
	for (auto const& findpath : vecFindPath)
	{
		if (PathFileExists(findpath) && !PathUtils::IsFileReadOnly(findpath))
		{
			if (CheckFileFilter(findpath))
			{
				std::wstring strFile = AppUtils::CStringToWStd(findpath);
				std::wifstream fileSTREAM;
				std::wstring strLine;
				fileSTREAM.open(strFile.c_str());
				if (fileSTREAM.is_open())
				{
					unsigned int curLine = 0;
					while (std::getline(fileSTREAM, strLine))
					{
						curLine++;
						auto nWordCount = (unsigned int)VinaTextSearchEngine::COUNT_WORD(strLine.c_str(), AppUtils::CStringToWStd(m_strSearchWhat).c_str(), m_nSearchOptions);
						if (nWordCount > 0)
						{
							vecReplacePath.push_back(findpath);
						}
					}
					fileSTREAM.close();
				}
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
		if (PathFileExists(replacepath) && CheckFileFilter(replacepath))
		{
			auto pDocFileExist = AppUtils::GetExistedDocument(replacepath);
			if (pDocFileExist)
			{
				auto pDocEditor = dynamic_cast<CEditorDoc*>(pDocFileExist);
				if (pDocEditor)
				{
					auto pEditor = pDocEditor->GetEditorCtrl();
					if (pEditor != NULL)
					{
						pEditor->SetSearchflags(m_nSearchOptions);
						CString strScript;
						pEditor->GetText(strScript);
						if (strScript.IsEmpty()) continue;
						BOOL bHasTrailingReturn = FALSE;
						if (strScript.GetAt(strScript.GetLength() - 1) == _T('\r'))
						{
							bHasTrailingReturn = TRUE;
						}
						std::vector<CString> listLine;
						AppUtils::SplitCString(strScript, listLine);
						std::wstring inputfile = AppUtils::CStringToWStd(pDocEditor->GetPathName());
						std::wstring replace_what = AppUtils::CStringToWStd(m_strSearchWhat);
						std::wstring replace_with = AppUtils::CStringToWStd(m_strReplaceWith);
						pEditor->BeginUndoTransactions();
						if (PathFileExists(m_pActiveDoc->GetPathName()))
						{
							ReplaceInDocument(pDocEditor->GetPathName(), listLine, replace_what, replace_with, m_ResultReplaceData._vecResultSearchInfo,
								m_ResultReplaceData._nMatchedFiles, m_ResultReplaceData._nMatchedWords, m_ResultReplaceData._nLineCounts,
								m_nSearchOptions, pEditor, bHasTrailingReturn);
						}
						pEditor->EndUndoTransactions();
					}
				}
			}
			else
			{
				std::wstring inputfile = AppUtils::CStringToWStd(replacepath);
				std::wstring outputfile = AppUtils::CStringToWStd(replacepath);
				std::wstring replace_what = AppUtils::CStringToWStd(m_strSearchWhat);
				std::wstring replace_with = AppUtils::CStringToWStd(m_strReplaceWith);
				ReplaceInFilePath(inputfile, outputfile, replace_what, replace_with, m_ResultReplaceData._vecResultSearchInfo,
					m_ResultReplaceData._nMatchedFiles, m_ResultReplaceData._nMatchedWords,
					m_ResultReplaceData._nLineCounts, m_nSearchOptions);
			}
			m_nReplaceProgress = 20 + static_cast<int>(m_ResultReplaceData._nTotalSearchFile * 80 / nTotalFile);
		}
	}
}

BOOL CReplaceWorker::CheckFileFilter(const CString & strFilePath)
{
	if (m_FileFilters.empty()) return TRUE;
	if (m_FileFilters[0].Trim() == _T("*.*")) return TRUE;
	CString strFileExt = PathUtils::GetFileExtention(strFilePath);
	if (std::find_if(m_FileFilters.begin(), m_FileFilters.end(), [&](CString &strExt)
	{
		return strExt.Trim().Mid(2) == strFileExt.Trim();
	}) != m_FileFilters.end())
	{
		return TRUE;
	}
	return FALSE;
}

void CReplaceWorker::SetFileFilter(const CString& strfileFilter)
{
	m_FileFilters = AppUtils::SplitterCString(strfileFilter, ";");
}

void CReplaceWorker::ReplaceInDocument(const CString& strDocPath,
	const std::vector<CString>& listInputLine,
	std::wstring replace_what, std::wstring replace_with,
	std::vector<RESULT_SEARCH_DATA>& vecResultSearchInfo,
	unsigned int & nMatchedFiles,
	unsigned int & nMatchedWords,
	unsigned int& nLineCounts,
	int nSearchOptions, CEditorCtrl* pCScintillaEditor /*= NULL*/,
	BOOL bHasTrailingReturn)
{
	if (PathFileExists(strDocPath))
	{
		if (PathUtils::IsBinaryFile(strDocPath, FILE_BINNARY | FILE_MEDIA | FILE_IMAGE | FILE_OFFICE | FILE_PDF)) return; // do not replace binary file...
	}
	std::wstring strLine;
	std::wstring strOutputText;
	unsigned int curLine = 0;
	for (int i = 0; i < listInputLine.size(); ++i)
	{
		curLine++;
		strLine = AppUtils::CStringToWStd(*std::next(listInputLine.begin(), i));
		auto strNewLine = strLine;
		auto nWordCount = (unsigned int)VinaTextSearchEngine::COUNT_WORD(strLine.c_str(), replace_what.c_str(), nSearchOptions);
		if (nWordCount > 0)
		{
			nMatchedFiles++;
			strNewLine = VinaTextSearchEngine::REPLACE_WORD(strLine.c_str(), replace_what.c_str(), replace_with.c_str(), nSearchOptions);
			{
				nMatchedWords += nWordCount;
				RESULT_SEARCH_DATA data;
				data._nMatched = nWordCount;
				data._nLineNumber = curLine;
				data._strLine = AppUtils::WStdToCString(strNewLine);
				data._strTargetFile = strDocPath;
				vecResultSearchInfo.push_back(data);
			}
		}
		if (listInputLine.size() - 1 == i)
		{
			if (bHasTrailingReturn)
			{
				strOutputText += strNewLine + EDITOR_NEW_LINE;
			}
			else
			{
				strOutputText += strNewLine;
			}
		}
		else
		{
			strOutputText += strNewLine + EDITOR_NEW_LINE;
		}
	}
	nLineCounts += curLine;
	if (pCScintillaEditor)
	{
		long nVisualLine = pCScintillaEditor->GetFirstVisibleLine();
		pCScintillaEditor->SetTextToEditor(AppUtils::WStdToCString(strOutputText));
		pCScintillaEditor->SetFirstVisibleLine(nVisualLine);
	}
}

void CReplaceWorker::ReplaceInFilePath(std::wstring inputfile,
	std::wstring outputfile, std::wstring replace_what,
	std::wstring replace_with, std::vector<RESULT_SEARCH_DATA>& vecResultSearchInfo,
	unsigned int & nMatchedFiles, unsigned int & nMatchedWords, unsigned int& nLineCounts, int nSearchOptions,
	CEditorCtrl * pCScintillaEditor)
{
	CString strInputFile = AppUtils::WStdToCString(inputfile);
	if (PathUtils::IsBinaryFile(strInputFile, FILE_BINNARY | FILE_MEDIA | FILE_IMAGE | FILE_OFFICE | FILE_PDF)) return; // do not replace binary file...
	BOOL bHasTrailingReturn = PathUtils::IsFileHasTrailingReturn(strInputFile);
	std::wifstream ifs(inputfile);
	if (!ifs) return;
	std::wstring strLine;
	std::wstring strOutputText;
	unsigned int curLine = 0;
	while (std::getline(ifs, strLine))
	{
		curLine++;
		auto strNewLine = strLine;
		auto nWordCount = (unsigned int)VinaTextSearchEngine::COUNT_WORD(strLine.c_str(), replace_what.c_str(), nSearchOptions);
		if (nWordCount > 0)
		{
			nMatchedFiles++;
			strNewLine = VinaTextSearchEngine::REPLACE_WORD(strLine.c_str(), replace_what.c_str(), replace_with.c_str(), nSearchOptions);
			{
				nMatchedWords += nWordCount;
				RESULT_SEARCH_DATA data;
				data._nMatched = nWordCount;
				data._nLineNumber = curLine;
				data._strLine = AppUtils::WStdToCString(strNewLine);
				data._strTargetFile = AppUtils::WStdToCString(outputfile);
				vecResultSearchInfo.push_back(data);
			}
		}
		if (ifs.eof())
		{
			if (bHasTrailingReturn)
			{
				strOutputText += strNewLine + EDITOR_NEW_LINE;
			}
			else
			{
				strOutputText += strNewLine;
			}
		}
		else
		{
			strOutputText += strNewLine + EDITOR_NEW_LINE;
		}
	}
	ifs.close();
	nLineCounts += curLine;
	if (pCScintillaEditor)
	{
		long nVisualLine = pCScintillaEditor->GetFirstVisibleLine();
		pCScintillaEditor->SetTextToEditor(AppUtils::WStdToCString(strOutputText));
		pCScintillaEditor->SetFirstVisibleLine(nVisualLine);
	}
	else
	{
		AppUtils::ReplaceAllInWStdString(strOutputText, L"\r", L"\n");
		std::wofstream file(outputfile, std::wios::trunc);
		if (!file) return;
		file << strOutputText;
		file.close();
	}
}