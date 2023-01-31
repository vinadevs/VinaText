/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "PODictionary.h"
#include "../AppSettings.h"

////////////////// Language Translator API /////////////////////////////

#define Native_Language(str) AppTranslator.GetPOString(_T(str))

////// Translator /////////////////////////////////

class CDictionaryPortableObject;

class CPOHandler
{
	SINGLETON_IMPLEMENT(CPOHandler)
public:
	void InitFromSetting();
	void SelectLanguage(APPLICATION_LANGUAGE lang);
	APPLICATION_LANGUAGE GetCurrentLanguage() const { return m_AppLanguage; }
	void ToNativeContextMenu(CMenu * pMenu);
	const WCHAR* GetPOString(const WCHAR *wstr) const;
private:
	APPLICATION_LANGUAGE m_AppLanguage = APPLICATION_LANGUAGE::LANGUAGE_UNKNOWN;
	std::unique_ptr<CDictionaryPortableObject> m_pDictionary = NULL;
};

#define AppTranslator CPOHandler::GetInstance()