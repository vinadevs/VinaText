/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

// Directory notifier manager
class CDirectoryNotifier;

class CDirectoryNotifierManager
{
public:
	BOOL AddNotifier(CDirectoryNotifier* pNotifier, CString strFileName);
	void RemoveNotifier(CString strFileName);

protected:
	CAtlMap_CString<CDirectoryNotifier*> m_MapNotifier;
	SINGLETON_IMPLEMENT(CDirectoryNotifierManager)
};

#define DirectoryNotifierMgr CDirectoryNotifierManager::GetInstance()