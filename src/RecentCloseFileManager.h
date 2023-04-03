/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

typedef std::stack<CString> RECENT_TAB_BUFFER;

class CRecentCloseMDITabManager
{
public:
	void PushTab(const CString& strPathName);
	CString PopTab();
	BOOL HasRecentClosedTab();

protected:
	RECENT_TAB_BUFFER m_RecentTab;
	SINGLETON_IMPLEMENT(CRecentCloseMDITabManager)
};

#define RecentCloseMDITabManager CRecentCloseMDITabManager::GetInstance()