/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "FindPathWorker.h"
#include "AppUtil.h"
#include "PathUtil.h"
#include "OSUtil.h"

constexpr int InitialProgress = 20;

CFindPathWorker::CFindPathWorker(CString strFolder,
	CString strSearchTarget,
	CString strSearchFilter,
	BOOL bMatchCase,
	BOOL bSearchFileOnly,
	BOOL bSearchWithSize,
	BOOL bSearchWitheModifiedDate,
	BOOL bSearchWitheCreatedDate,
	BOOL bSearchInSubdirectory,
	BOOL bSearchWithoutMatchName,
	double dMinFileSize,
	double dMaxFileSize,
	CTime StartModifiedDate,
	CTime EndModifiedDate,
	CTime StartCreatedDate,
	CTime EndCreatedDate)
{
	m_strFolder = strFolder;
	m_strSearchTarget = strSearchTarget;
	m_bMatchCase = bMatchCase;
	m_bSearchFileOnly = bSearchFileOnly;
	m_bSearchWithSize = bSearchWithSize;
	m_bSearchWitheModifiedDate = bSearchWitheModifiedDate;
	m_bSearchWitheCreatedDate = bSearchWitheCreatedDate;
	m_bSearchInSubdirectory = bSearchInSubdirectory;
	m_bSearchWithoutMatchName = bSearchWithoutMatchName;
	m_dMinFileSize = dMinFileSize;
	m_dMaxFileSize = dMaxFileSize;
	m_StartModifiedDate = StartModifiedDate;
	m_EndModifiedDate = EndModifiedDate;
	m_StartCreatedDate = StartCreatedDate;
	m_EndCreatedDate = EndCreatedDate;
	m_FileFilters = AppUtils::SplitterCString(strSearchFilter, ";");
}

CFindPathWorker::CFindPathWorker(CString strFolder)
{
	m_strFolder = strFolder;
}

void CFindPathWorker::FindPathWithCondition()
{
	std::vector<CString> vecPath;
	m_nFindProgress = InitialProgress;
	PathUtils::GetAllPathFromFolder(m_strFolder, vecPath, m_bSearchInSubdirectory);
	m_nTotalSearch = (int)vecPath.size();
	for (int i = 0; i < vecPath.size(); i++)
	{
		if (PathFileExists(vecPath[i]) && CheckFileFilter(vecPath[i]))
		{
			// do search file
			if (m_bSearchFileOnly)
			{
				if (PathUtils::IsDirectory(vecPath[i])) continue;
			}
			CString strLastLevelPath = PathUtils::GetLastLevelPath(vecPath[i]);
			if (m_bSearchWithoutMatchName)
			{
				GetPathInformation(vecPath[i], strLastLevelPath);
			}
			else
			{
				if (m_bMatchCase)
				{
					if (strLastLevelPath.Find(m_strSearchTarget) != -1)
					{
						GetPathInformation(vecPath[i], strLastLevelPath);
					}
				}
				else
				{
					CString strOriginalLastLevelPath = strLastLevelPath;
					strLastLevelPath.MakeLower();
					if (strLastLevelPath.Find(m_strSearchTarget.MakeLower()) != -1)
					{
						GetPathInformation(vecPath[i], strOriginalLastLevelPath);
					}
				}
			}
		}
		// update progress
		m_nFindProgress = InitialProgress + static_cast<int>((i + 1) * 80 / m_nTotalSearch);
	}
}

void CFindPathWorker::FindAllFiles()
{
	std::vector<CString> vecFilePath;
	PathUtils::GetAllPathFromFolder(m_strFolder, vecFilePath, FALSE);
	m_nTotalSearch = (int)vecFilePath.size();
	for (int i = 0; i < vecFilePath.size(); i++)
	{
		// do search file
		if (PathUtils::IsDirectory(vecFilePath[i])) continue;

		PATH_RESULT_DATA data;

		data._strPathName = PathUtils::GetLastLevelPath(vecFilePath[i]);
		data._strLocation = PathUtils::GetContainerPath(vecFilePath[i]);

		data._strPathType = _T("File");
		LONGLONG llFileSize = PathUtils::GetFileSize(vecFilePath[i]);
		data._strPathSize = CString(std::unique_ptr<char>(PathUtils::SizeMemoryToString(llFileSize)).get());

		if (PathUtils::IsFileReadOnly(vecFilePath[i]))
		{
			data._strReadOnly += _T("Yes");
		}
		else
		{
			data._strReadOnly += _T("No");
		}

		data._strPathCreatedTime = PathUtils::GetFileTimePropertyCString(vecFilePath[i], FILE_TIME_PROPERTY::FILE_TIME_CREATED);
		data._strPathModifiedTime = PathUtils::GetFileTimePropertyCString(vecFilePath[i], FILE_TIME_PROPERTY::FILE_TIME_LAST_MODIFIED);

		m_pathResultDataList.push_back(data);
	}
}

void CFindPathWorker::FindAllFolders()
{
	std::vector<CString> vecFilePath;
	PathUtils::GetAllPathFromFolder(m_strFolder, vecFilePath, FALSE);
	m_nTotalSearch = (int)vecFilePath.size();
	for (int i = 0; i < vecFilePath.size(); i++)
	{
		// do search folder
		if (PathUtils::IsDirectory(vecFilePath[i]))
		{
			PATH_RESULT_DATA data;

			data._strPathName = PathUtils::GetLastLevelPath(vecFilePath[i]);
			data._strLocation = PathUtils::GetContainerPath(vecFilePath[i]);

			data._strPathType = _T("Folder");

			if (PathUtils::IsFileReadOnly(vecFilePath[i]))
			{
				data._strReadOnly += _T("Yes");
			}
			else
			{
				data._strReadOnly += _T("No");
			}

			data._strPathCreatedTime = PathUtils::GetFileTimePropertyCString(vecFilePath[i], FILE_TIME_PROPERTY::FILE_TIME_CREATED);
			data._strPathModifiedTime = PathUtils::GetFileTimePropertyCString(vecFilePath[i], FILE_TIME_PROPERTY::FILE_TIME_LAST_MODIFIED);

			m_pathResultDataList.push_back(data);
		}
	}
}

int CFindPathWorker::GetCurrentFindProgress() const
{
	return m_nFindProgress;
}

void CFindPathWorker::GetPathInformation(const CString & strPath, const CString & strLastLevelPath)
{
	PATH_RESULT_DATA data;

	data._strPathName = strLastLevelPath;
	data._strLocation = PathUtils::GetContainerPath(strPath);
	if (PathUtils::IsDirectory(strPath))
	{
		data._strPathType = _T("Folder");
	}
	else
	{
		data._strPathType = _T("File");
		LONGLONG llFileSize = PathUtils::GetFileSize(strPath);
		if (m_bSearchWithSize && (llFileSize < m_dMinFileSize || llFileSize > m_dMaxFileSize))
		{
			return;
		}
		data._strPathSize = CString(std::unique_ptr<char>(PathUtils::SizeMemoryToString(llFileSize)).get());
	}

	if (PathUtils::IsFileReadOnly(strPath))
	{
		data._strReadOnly += _T("Yes");
	}
	else
	{
		data._strReadOnly += _T("No");
	}

	if (m_bSearchWitheModifiedDate)
	{
		CTime _PathModifiedTime = PathUtils::GetFileTimeProperty(strPath, FILE_TIME_PROPERTY::FILE_TIME_LAST_MODIFIED);
		if (_PathModifiedTime < m_StartModifiedDate || _PathModifiedTime > m_EndModifiedDate)
		{
			return;
		}
	}

	if (m_bSearchWitheCreatedDate)
	{
		CTime _PathCreatedTime = PathUtils::GetFileTimeProperty(strPath, FILE_TIME_PROPERTY::FILE_TIME_CREATED);
		if (_PathCreatedTime < m_StartCreatedDate || _PathCreatedTime > m_EndCreatedDate)
		{
			return;
		}
	}

	data._strPathCreatedTime = PathUtils::GetFileTimePropertyCString(strPath, FILE_TIME_PROPERTY::FILE_TIME_CREATED);
	data._strPathModifiedTime = PathUtils::GetFileTimePropertyCString(strPath, FILE_TIME_PROPERTY::FILE_TIME_LAST_MODIFIED);

	m_pathResultDataList.push_back(data);
}

BOOL CFindPathWorker::CheckFileFilter(const CString & strFilePath)
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