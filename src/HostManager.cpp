/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "VinaTextApp.h"
#include "HostManager.h"
#include "AppUtil.h"

CDocument * HostManager::HostApplicaton(const HOST_APP_TYPE & appType, const CString & strAppPathToHost, const CString & strAppArguments, BOOL bOpenFileMode, BOOL bActiveExistedTab)
{
	CDocument* pExistedDoc = AppUtils::GetExistedDocument(strAppArguments);
	if (pExistedDoc)
	{
		if (bActiveExistedTab)
		{
			AppUtils::SetActiveDocument(pExistedDoc); return pExistedDoc;
		}
		else 
			AppUtils::CloseMDIDocument(pExistedDoc);
	}
	if (appType == HOST_APP_TYPE::TERMINAL_CMD)
	{
		return AppUtils::GetVinaTextApp()->CreateNewHostDocument(
			L"Terminal CMD",
			strAppPathToHost,
			strAppArguments,
			TRUE,
			TRUE,
			IDR_TERMINAL_DOC,
			HOST_METHOD::USE_ENUMWINDOWS,
			500,
			NULL,
			bOpenFileMode);
	}
	else if (appType == HOST_APP_TYPE::TERMINAL_POWERSHELL)
	{
		return AppUtils::GetVinaTextApp()->CreateNewHostDocument(
			L"Terminal Powershell",
			strAppPathToHost,
			strAppArguments,
			TRUE,
			TRUE,
			IDR_TERMINAL_DOC,
			HOST_METHOD::USE_ENUMWINDOWS,
			500,
			NULL,
			bOpenFileMode);
	}
	else if (appType == HOST_APP_TYPE::TERMINAL_WSL)
	{
	return AppUtils::GetVinaTextApp()->CreateNewHostDocument(
		L"Terminal WSL",
		strAppPathToHost,
		strAppArguments,
		TRUE,
		TRUE,
		IDR_TERMINAL_DOC,
		HOST_METHOD::USE_ENUMWINDOWS,
		500,
		NULL,
		bOpenFileMode);
	}
	else if (appType == HOST_APP_TYPE::FILE_EXPLORER)
	{
		return AppUtils::GetVinaTextApp()->CreateNewFileExplorerDocument(strAppArguments);
	}
	return NULL;
}
