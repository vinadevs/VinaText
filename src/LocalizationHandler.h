/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "LocalizationDatabase.h"
#include "AppSettings.h"

////////////////// Language Translator API /////////////////////////////

#define Native_Language(str) VinaTextLocalization.GetLocalizedString(_T(str))

////// Translator /////////////////////////////////

class LocalizationDatabase;

class LocalizationHandler
{
	SINGLETON_IMPLEMENT(LocalizationHandler)
public:
	void InitFromSetting();
	VINATEXT_DISPLAY_LANGUAGE GetCurrentLanguage() const { return m_AppLanguage; }
	const WCHAR* GetLocalizedString(const WCHAR* wstr) const;
	void TranslateContextMenu(CMenu * pMenu);
private:
	void InitLocalizationDatabase(VINATEXT_DISPLAY_LANGUAGE lang);

	VINATEXT_DISPLAY_LANGUAGE m_AppLanguage = VINATEXT_DISPLAY_LANGUAGE::LANGUAGE_UNKNOWN;
	std::unique_ptr<Localization::LocalizationDatabase> m_pLocalDatabase = NULL;
};

#define VinaTextLocalization LocalizationHandler::GetInstance()