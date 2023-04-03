/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "DirectoryNotifier.h"
#include "DirectoryNotifyManager.h"

BOOL CDirectoryNotifierManager::AddNotifier(CDirectoryNotifier* pNotifier, CString strFileName)
{
	if (pNotifier != NULL)
	{
		auto ptr = m_MapNotifier.Lookup(strFileName);
		if (!ptr)
		{
			m_MapNotifier[strFileName] = pNotifier;
			return FALSE;
		}
	}
	return TRUE;
}

void CDirectoryNotifierManager::RemoveNotifier(CString strFileName)
{
	auto ptr = m_MapNotifier.Lookup(strFileName);
	if (ptr)
	{
		ptr->m_value->CancelProcess();
		m_MapNotifier.RemoveKey(strFileName);
	}
}