/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "RecentCloseFileManager.h"
#include "AppUtil.h"

void CRecentCloseMDITabManager::PushTab(const CString& strPathName)
{
	if (PathFileExists(strPathName))
	{
		m_RecentTab.push(strPathName);
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Close File] %s..."), strPathName);
	}
}

CString CRecentCloseMDITabManager::PopTab()
{
	CString strPathName;
	if (!m_RecentTab.empty())
	{
		strPathName = m_RecentTab.top();
		m_RecentTab.pop();
	}
	return strPathName;
}

BOOL CRecentCloseMDITabManager::HasRecentClosedTab()
{
	return !m_RecentTab.empty();
}
