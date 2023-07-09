/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

// this class for keeping temporary data while application is running
// or it can be used to store global variables
// all settings will not be saved into file

#include "Singleton.h"

class CTemporarySettings
{
public:
	BOOL m_bIsStartAppInstance = FALSE;
	BOOL m_bIsOpenInAdminMode = FALSE;
	BOOL m_bIsReloadDocument = FALSE;
	BOOL m_bIsSaveDocument = FALSE;
	BOOL m_bIsReloadByPreviewMode = FALSE;
	BOOL m_bIsClosingMainFrame = FALSE;
	HWND m_hLatestHostWND = NULL; // latest host window handle
	CString m_strFileExplorerNavigatePath;
	CString m_strComboboxQuickSearch;
protected:
	SINGLETON_IMPLEMENT(CTemporarySettings)
};

#define TemporarySettings CTemporarySettings::GetInstance()