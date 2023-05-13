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
#include "MainFrm.h"

void CRecentCloseMDITabManager::PushTab(const CString& strPathName, BOOL bCloseTabEvent/*= TRUE*/)
{
	if (PathFileExists(strPathName))
	{
		if (bCloseTabEvent)
		{
			if (m_RecentTab.size() > AppSettingMgr.m_nRecentFileLimit)
			{
				ResetData();
			}
			else
			{
				EraseTab(strPathName);
			}
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Close File] %s..."), strPathName);
		}
		m_RecentTab.push_front(strPathName);
	}
}

void CRecentCloseMDITabManager::EraseTab(const CString& strPathName)
{
	auto found = std::find(m_RecentTab.begin(), m_RecentTab.end(), strPathName);
	if (found != m_RecentTab.end()) m_RecentTab.erase(found);
}

CString CRecentCloseMDITabManager::PopTab()
{
	CString strPathName;
	if (!m_RecentTab.empty())
	{
		strPathName = m_RecentTab.front();
		m_RecentTab.pop_front();
	}
	return strPathName;
}

BOOL CRecentCloseMDITabManager::HasRecentClosedTab()
{
	return !m_RecentTab.empty();
}

void CRecentCloseMDITabManager::ResetData()
{
	RECENT_TAB_BUFFER().swap(m_RecentTab);
}
