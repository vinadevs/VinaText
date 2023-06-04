/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "Singleton.h"

typedef std::deque<CString> RECENT_TAB_BUFFER;

class CRecentCloseMDITabManager
{
public:
	void PushTab(const CString& strPathName, BOOL bCloseTabEvent = TRUE);
	void EraseTab(const CString& strPathName);
	void EraseLastTab();
	CString PopTab();
	BOOL HasRecentClosedTab();
	void ResetData();
	const RECENT_TAB_BUFFER& GetData() { return m_RecentTab; }
protected:
	RECENT_TAB_BUFFER m_RecentTab;
	SINGLETON_IMPLEMENT(CRecentCloseMDITabManager)
};

#define RecentCloseMDITabManager CRecentCloseMDITabManager::GetInstance()