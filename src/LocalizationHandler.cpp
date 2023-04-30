/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "LocalizationHandler.h"
#include "PathUtil.h"

static const int VN_CODEPAGE = 1258;

void LocalizationHandler::InitLocalizationDatabase(VINATEXT_DISPLAY_LANGUAGE lang)
{
	if(m_AppLanguage == lang) return;
	m_pLocalDatabase.reset(nullptr);
	m_pLocalDatabase = std::make_unique<Localization::LocalizationDatabase>();
	m_AppLanguage = lang;
	if (lang == VINATEXT_DISPLAY_LANGUAGE::LANGUAGE_VIETNAMESE)
	{
		m_pLocalDatabase->Load(PathUtils::GetVinaTextPOPath() + _T("VinaText_Language_VN.mo"));
	}
}

void LocalizationHandler::InitFromSetting()
{
	VINATEXT_DISPLAY_LANGUAGE app_lang = AppSettingMgr.m_ApplicationLanguage;
	if (VINATEXT_DISPLAY_LANGUAGE::LANGUAGE_UNKNOWN == app_lang)
	{
		int nCurACP = ::GetACP();
		if (nCurACP == VN_CODEPAGE)
		{
			app_lang = VINATEXT_DISPLAY_LANGUAGE::LANGUAGE_VIETNAMESE;
		}
	}
	InitLocalizationDatabase(VINATEXT_DISPLAY_LANGUAGE::LANGUAGE_VIETNAMESE);
}

static void CreateMenuByPosition(CMenu* pMenu, UINT nPos, CString strText)
{
	if (!pMenu) return;
	MENUITEMINFO memuInfo;
	ZeroMemory(&memuInfo, sizeof(MENUITEMINFO));
	memuInfo.cbSize = sizeof(MENUITEMINFO);
	memuInfo.fMask = MIIM_STRING;
	memuInfo.dwTypeData = strText.GetBuffer(strText.GetLength() + 1);
	pMenu->SetMenuItemInfo(nPos, &memuInfo, TRUE);
	strText.ReleaseBuffer();
}

void LocalizationHandler::TranslateContextMenu(CMenu* pMenu)
{
	if (!pMenu) return;
	CString strText;
	for (int i = 0; i < pMenu->GetMenuItemCount(); ++i)
	{
		pMenu->GetMenuString(i, strText, MF_BYPOSITION);
		CreateMenuByPosition(pMenu, i, GetLocalizedString(strText));
		CMenu* pSubMenu = pMenu->GetSubMenu(i);
		if (pSubMenu)
		{
			TranslateContextMenu(pSubMenu); // recursion...
		}
	}
}

const WCHAR* LocalizationHandler::GetLocalizedString(const WCHAR *wstr) const
{
	if (NULL == wstr) return NULL;
	if (_tcslen(wstr) != 0)
	{
		if (m_pLocalDatabase)
		{
			const WCHAR* pPOStr = m_pLocalDatabase->GetStringPO(wstr);
			if (pPOStr)
			{
				return pPOStr;
			}

		}
	}
	return wstr;
}