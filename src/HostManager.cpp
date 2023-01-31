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
	if (appType == HOST_APP_TYPE::MS_EDGE)
	{
		return AppUtils::GetVinaTextApp()->CreateNewHostDocument(
			L"Microsoft Edge",
			strAppPathToHost,
			strAppArguments,
			TRUE,
			FALSE,
			IDR_MSEDGE_DOC,
			HOST_METHOD::USE_FINDWINDOWS,
			2000,
			L"Chrome_WidgetWin_1",
			bOpenFileMode);
	}
	else if (appType == HOST_APP_TYPE::MS_PAINT)
	{
		return AppUtils::GetVinaTextApp()->CreateNewHostDocument(
			L"Microsoft Paint",
			strAppPathToHost,
			strAppArguments,
			TRUE,
			TRUE,
			IDR_MSPAINT_DOC,
			HOST_METHOD::USE_FINDWINDOWS,
			500,
			L"MSPaintApp",
			bOpenFileMode);
	}
	else if (appType == HOST_APP_TYPE::MS_OFFICE_EXCEL)
	{
		return AppUtils::GetVinaTextApp()->CreateNewHostDocument(
			L"Microsoft Excel",
			strAppPathToHost,
			strAppArguments,
			TRUE,
			FALSE,
			IDR_MSEXCEL_DOC,
			HOST_METHOD::USE_FINDWINDOWS,
			2000,
			L"XLMAIN",
			bOpenFileMode);
	}
	else if (appType == HOST_APP_TYPE::MS_OFFICE_PPT)
	{
		return AppUtils::GetVinaTextApp()->CreateNewHostDocument(
			L"Microsoft Powerpoint",
			strAppPathToHost,
			strAppArguments,
			TRUE,
			FALSE,
			IDR_MSPPT_DOC,
			HOST_METHOD::USE_FINDWINDOWS,
			2000,
			L"PPTFrameClass",
			bOpenFileMode);
	}
	else if (appType == HOST_APP_TYPE::MS_OFFICE_WORD)
	{
		return AppUtils::GetVinaTextApp()->CreateNewHostDocument(
			L"Microsoft Word",
			strAppPathToHost,
			strAppArguments,
			TRUE,
			FALSE,
			IDR_MSWORD_DOC,
			HOST_METHOD::USE_FINDWINDOWS,
			2000,
			L"OpusApp",
			bOpenFileMode);
	}
	else if (appType == HOST_APP_TYPE::TERMINAL_CMD)
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
	else if (appType == HOST_APP_TYPE::CHROME_BROWSER)
	{
		return AppUtils::GetVinaTextApp()->CreateNewHostDocument(
			L"Google Chrome",
			strAppPathToHost,
			strAppArguments,
			TRUE,
			FALSE,
			IDR_GOOGLE_CHROME_DOC,
			HOST_METHOD::USE_FINDWINDOWS,
			2000,
			L"Chrome_WidgetWin_1",
			bOpenFileMode);
	}
	else if (appType == HOST_APP_TYPE::FIREFOX_BROWSER)
	{
		return AppUtils::GetVinaTextApp()->CreateNewHostDocument(
			L"Mozilla Firefox",
			strAppPathToHost,
			strAppArguments,
			TRUE,
			FALSE,
			IDR_MOZILLA_FIREFOX_DOC,
			HOST_METHOD::USE_FINDWINDOWS,
			2000,
			L"MozillaWindowClass",
			bOpenFileMode);
	}
	else if (appType == HOST_APP_TYPE::FILE_EXPLORER)
	{
		return AppUtils::GetVinaTextApp()->CreateNewFileExplorerDocument(strAppArguments);
	}
	return NULL;
}
