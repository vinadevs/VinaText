/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "SearchEngine.h"

class CFindPathWorker
{
public:
	CFindPathWorker(CString strFolder,
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
		CTime EndCreatedDate);

	CFindPathWorker(CString strFolder);

	~CFindPathWorker() = default;

	void FindPathWithCondition();
	void FindAllFiles();
	void FindAllFolders();

	int GetCurrentFindProgress() const;

	// results
	PATH_RESULT_DATA_LIST m_pathResultDataList;
	int m_nTotalSearch = 0;
	int m_nFindProgress = 0;

protected:
	void GetPathInformation(const CString& strPath, const CString& strLastLevelPath);
	BOOL CheckFileFilter(const CString & strFilePath);

private:
	CString m_strFolder;
	CString m_strSearchTarget;
	BOOL m_bMatchCase;
	BOOL m_bSearchFileOnly;
	BOOL m_bSearchWithSize;
	BOOL m_bSearchWitheModifiedDate;
	BOOL m_bSearchWitheCreatedDate;
	BOOL m_bSearchInSubdirectory;
	BOOL m_bSearchWithoutMatchName;
	double m_dMinFileSize;
	double m_dMaxFileSize;
	CTime m_StartModifiedDate;
	CTime m_EndModifiedDate;
	CTime m_StartCreatedDate;
	CTime m_EndCreatedDate;
	std::vector<CString> m_FileFilters;
};


