/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "POHandler.h"
#include "../PathUtil.h"

static const int VN_CODEPAGE = 1258;

void CPOHandler::SelectLanguage(APPLICATION_LANGUAGE lang)
{
	if(m_AppLanguage == lang) return;
	m_pDictionary.reset(NULL);
	m_pDictionary = std::make_unique<CDictionaryPortableObject>();
	m_AppLanguage = lang;
	if (lang == APPLICATION_LANGUAGE::LANGUAGE_VIETNAMESE)
	{
		m_pDictionary->Load(PathUtils::GetVinaTextPOPath() + _T("VinaText_Language_VN.mo"));
	}
}

void CPOHandler::InitFromSetting()
{
	APPLICATION_LANGUAGE app_lang = AppSettingMgr.m_ApplicationLanguage;
	if (APPLICATION_LANGUAGE::LANGUAGE_UNKNOWN == app_lang)
	{
		int nCurACP = ::GetACP();
		if (nCurACP == VN_CODEPAGE)
		{
			app_lang = APPLICATION_LANGUAGE::LANGUAGE_VIETNAMESE;
		}
	}
	SelectLanguage(APPLICATION_LANGUAGE::LANGUAGE_VIETNAMESE);
}

static void CreateMenuByPosition(CMenu* pMenu, UINT nPos, CString strText)
{
	if (!pMenu) return;
	MENUITEMINFO mii;
	ZeroMemory(&mii, sizeof(MENUITEMINFO));
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STRING;
	mii.dwTypeData = strText.GetBuffer(strText.GetLength() + 1);
	pMenu->SetMenuItemInfo(nPos, &mii, TRUE);
	strText.ReleaseBuffer();
}

void CPOHandler::ToNativeContextMenu(CMenu* pMenu)
{
	if (!pMenu) return;
	CString strText;
	for (int i = 0; i < pMenu->GetMenuItemCount(); ++i)
	{
		pMenu->GetMenuString(i, strText, MF_BYPOSITION);
		CreateMenuByPosition(pMenu, i, GetPOString(strText));
		CMenu* pSubMenu = pMenu->GetSubMenu(i);
		if (pSubMenu)
		{
			ToNativeContextMenu(pSubMenu); // recursion...
		}
	}
}

const WCHAR* CPOHandler::GetPOString(const WCHAR *wstr) const
{
	if (NULL == wstr) return NULL;
	if (_tcslen(wstr) != 0)
	{
		if (m_pDictionary)
		{
			const WCHAR* pPOStr = m_pDictionary->GetStringPO(wstr);
			if (pPOStr)
			{
				//AfxMessageBox(pPOStr);
				return pPOStr;
			}

		}
	}
	return wstr;
}