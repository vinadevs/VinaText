/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "SettingDlgFileSystem.h"
#include "afxdialogex.h"
#include "AppSettings.h"
#include "AppUtil.h"
#include "PathUtil.h"

// SettingDlgFileSystem dialog

IMPLEMENT_DYNAMIC(SettingDlgFileSystem, CDialogEx)

SettingDlgFileSystem::SettingDlgFileSystem(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SETTING_FILE_SYSTEM, pParent)
	, m_strInitialFilePickerPath(_T(""))
	, m_strNodeJSFolderPath(_T(""))
	, m_strPythonFolderPath(_T(""))
	, m_strGitWindowFolderPath(_T(""))
	, m_strAntiVirusArgument(_T(""))
	, m_strAntiVirusProgram(_T(""))
	, m_strBinaryFileExtensionList(_T(""))
	, m_nLineSpaceAbove(0)
	, m_nLineSpaceBelow(0)
	, m_nIntervalAutoSaveFileMinutes(0)
	, m_nExplorerExpandLimitFileOpen(0)
	, m_nExplorerExpandLimitLevel(0)
	, m_nFilePreviewSizeLimit(0)
	, m_nRecentFileLimit(0)
	, m_nLongLineMaximum(0)
{

}

SettingDlgFileSystem::~SettingDlgFileSystem()
{
}

BOOL SettingDlgFileSystem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_EditInitialFilePickerPath.EnableFolderBrowseButton();
	m_EditNodeJSFolderPath.EnableFolderBrowseButton();
	m_EditPythonFolderPath.EnableFolderBrowseButton();
	m_EditGitWindowFolderPath.EnableFolderBrowseButton();
	m_EditAntiVirusProgram.EnableFileBrowseButton();

	UpdateGUISettings(FALSE);

	UpdateData(FALSE);

	return TRUE;
}

BOOL SettingDlgFileSystem::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			GetParent()->GetParent()->SendMessage(WM_CLOSE, 0, 0);
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void SettingDlgFileSystem::InitLanguageSpellCheckCombo()
{
	m_LanguageSpellCheckCombo.ResetContent();
	m_LanguageSpellCheckCombo.AddString(_T("English-USA"));
	m_LanguageSpellCheckCombo.SetCurSel(0);
}

void SettingDlgFileSystem::InitLanguageTranslateFromCombo()
{
	m_LanguageTranslateFromCombo.ResetContent();
	m_LanguageTranslateFromCombo.AddString(_T("English")); // support english only now
	m_LanguageTranslateFromCombo.SetCurSel(0);
	/*m_LanguageTranslateFromCombo.AddString(_T("Afrikaans"));
	m_LanguageTranslateFromCombo.AddString(_T("Albanian"));
	m_LanguageTranslateFromCombo.AddString(_T("Arabic"));
	m_LanguageTranslateFromCombo.AddString(_T("Azerbaijani"));
	m_LanguageTranslateFromCombo.AddString(_T("Basque"));
	m_LanguageTranslateFromCombo.AddString(_T("Belarusian"));
	m_LanguageTranslateFromCombo.AddString(_T("Bengali"));
	m_LanguageTranslateFromCombo.AddString(_T("Bulgarian"));
	m_LanguageTranslateFromCombo.AddString(_T("Catalan"));
	m_LanguageTranslateFromCombo.AddString(_T("Chinese Simplified"));
	m_LanguageTranslateFromCombo.AddString(_T("Chinese Traditional"));
	m_LanguageTranslateFromCombo.AddString(_T("Croatian"));
	m_LanguageTranslateFromCombo.AddString(_T("Czech"));
	m_LanguageTranslateFromCombo.AddString(_T("Danish"));
	m_LanguageTranslateFromCombo.AddString(_T("Dutch"));
	m_LanguageTranslateFromCombo.AddString(_T("English"));
	m_LanguageTranslateFromCombo.AddString(_T("Esperanto"));
	m_LanguageTranslateFromCombo.AddString(_T("Estonian"));
	m_LanguageTranslateFromCombo.AddString(_T("Filipino"));
	m_LanguageTranslateFromCombo.AddString(_T("Finnish"));
	m_LanguageTranslateFromCombo.AddString(_T("French"));
	m_LanguageTranslateFromCombo.AddString(_T("Galician"));
	m_LanguageTranslateFromCombo.AddString(_T("Georgian"));
	m_LanguageTranslateFromCombo.AddString(_T("German"));
	m_LanguageTranslateFromCombo.AddString(_T("Greek"));
	m_LanguageTranslateFromCombo.AddString(_T("Gujarati"));
	m_LanguageTranslateFromCombo.AddString(_T("Haitian Creole"));
	m_LanguageTranslateFromCombo.AddString(_T("Hebrew"));
	m_LanguageTranslateFromCombo.AddString(_T("Hindi"));
	m_LanguageTranslateFromCombo.AddString(_T("Hungarian"));
	m_LanguageTranslateFromCombo.AddString(_T("Icelandic"));
	m_LanguageTranslateFromCombo.AddString(_T("Indonesian"));
	m_LanguageTranslateFromCombo.AddString(_T("Irish"));
	m_LanguageTranslateFromCombo.AddString(_T("Italian"));
	m_LanguageTranslateFromCombo.AddString(_T("Japanese"));
	m_LanguageTranslateFromCombo.AddString(_T("Kannada"));
	m_LanguageTranslateFromCombo.AddString(_T("Korean"));
	m_LanguageTranslateFromCombo.AddString(_T("Latin"));
	m_LanguageTranslateFromCombo.AddString(_T("Latvian"));
	m_LanguageTranslateFromCombo.AddString(_T("Lithuanian"));
	m_LanguageTranslateFromCombo.AddString(_T("Macedonian"));
	m_LanguageTranslateFromCombo.AddString(_T("Malay"));
	m_LanguageTranslateFromCombo.AddString(_T("Maltese"));
	m_LanguageTranslateFromCombo.AddString(_T("Norwegian"));
	m_LanguageTranslateFromCombo.AddString(_T("Persian"));
	m_LanguageTranslateFromCombo.AddString(_T("Polish"));
	m_LanguageTranslateFromCombo.AddString(_T("Portuguese"));
	m_LanguageTranslateFromCombo.AddString(_T("Romanian"));
	m_LanguageTranslateFromCombo.AddString(_T("Russian"));
	m_LanguageTranslateFromCombo.AddString(_T("Serbian"));
	m_LanguageTranslateFromCombo.AddString(_T("Slovak"));
	m_LanguageTranslateFromCombo.AddString(_T("Slovenian"));
	m_LanguageTranslateFromCombo.AddString(_T("Spanish"));
	m_LanguageTranslateFromCombo.AddString(_T("Swahili"));
	m_LanguageTranslateFromCombo.AddString(_T("Swedish"));
	m_LanguageTranslateFromCombo.AddString(_T("Tamil"));
	m_LanguageTranslateFromCombo.AddString(_T("Telugu"));
	m_LanguageTranslateFromCombo.AddString(_T("Thai"));
	m_LanguageTranslateFromCombo.AddString(_T("Turkish"));
	m_LanguageTranslateFromCombo.AddString(_T("Ukrainian"));
	m_LanguageTranslateFromCombo.AddString(_T("Urdu"));
	m_LanguageTranslateFromCombo.AddString(_T("Vietnamese"));
	m_LanguageTranslateFromCombo.AddString(_T("Welsh"));
	m_LanguageTranslateFromCombo.AddString(_T("Yiddish"));*/
	/*if (AppSettingMgr.m_strLanguageTranslateFrom == _T("af")) m_LanguageTranslateFromCombo.SetCurSel(0);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("sq")) m_LanguageTranslateFromCombo.SetCurSel(1);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ar")) m_LanguageTranslateFromCombo.SetCurSel(2);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("az")) m_LanguageTranslateFromCombo.SetCurSel(3);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("eu")) m_LanguageTranslateFromCombo.SetCurSel(4);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("be")) m_LanguageTranslateFromCombo.SetCurSel(5);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("bn")) m_LanguageTranslateFromCombo.SetCurSel(6);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("bg")) m_LanguageTranslateFromCombo.SetCurSel(7);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ca")) m_LanguageTranslateFromCombo.SetCurSel(8);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("zh-CN")) m_LanguageTranslateFromCombo.SetCurSel(9);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("zh-TW")) m_LanguageTranslateFromCombo.SetCurSel(10);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("hr")) m_LanguageTranslateFromCombo.SetCurSel(11);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("cs")) m_LanguageTranslateFromCombo.SetCurSel(12);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("da")) m_LanguageTranslateFromCombo.SetCurSel(13);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("nl")) m_LanguageTranslateFromCombo.SetCurSel(14);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("en")) m_LanguageTranslateFromCombo.SetCurSel(15);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("eo")) m_LanguageTranslateFromCombo.SetCurSel(16);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("et")) m_LanguageTranslateFromCombo.SetCurSel(17);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("tl")) m_LanguageTranslateFromCombo.SetCurSel(18);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("fi")) m_LanguageTranslateFromCombo.SetCurSel(19);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("fr")) m_LanguageTranslateFromCombo.SetCurSel(20);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("gl")) m_LanguageTranslateFromCombo.SetCurSel(21);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ka")) m_LanguageTranslateFromCombo.SetCurSel(22);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("de")) m_LanguageTranslateFromCombo.SetCurSel(23);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("el")) m_LanguageTranslateFromCombo.SetCurSel(24);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("gu")) m_LanguageTranslateFromCombo.SetCurSel(25);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ht")) m_LanguageTranslateFromCombo.SetCurSel(26);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("iw")) m_LanguageTranslateFromCombo.SetCurSel(27);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("hi")) m_LanguageTranslateFromCombo.SetCurSel(28);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("hu")) m_LanguageTranslateFromCombo.SetCurSel(29);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("is")) m_LanguageTranslateFromCombo.SetCurSel(30);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("id")) m_LanguageTranslateFromCombo.SetCurSel(31);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ga")) m_LanguageTranslateFromCombo.SetCurSel(32);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("it")) m_LanguageTranslateFromCombo.SetCurSel(33);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ja")) m_LanguageTranslateFromCombo.SetCurSel(34);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("kn")) m_LanguageTranslateFromCombo.SetCurSel(35);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ko")) m_LanguageTranslateFromCombo.SetCurSel(36);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("la")) m_LanguageTranslateFromCombo.SetCurSel(37);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("lv")) m_LanguageTranslateFromCombo.SetCurSel(38);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("lt")) m_LanguageTranslateFromCombo.SetCurSel(39);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("mk")) m_LanguageTranslateFromCombo.SetCurSel(40);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ms")) m_LanguageTranslateFromCombo.SetCurSel(41);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("mt")) m_LanguageTranslateFromCombo.SetCurSel(42);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("no")) m_LanguageTranslateFromCombo.SetCurSel(43);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("fa")) m_LanguageTranslateFromCombo.SetCurSel(44);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("pl")) m_LanguageTranslateFromCombo.SetCurSel(45);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("pt")) m_LanguageTranslateFromCombo.SetCurSel(46);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ro")) m_LanguageTranslateFromCombo.SetCurSel(47);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ru")) m_LanguageTranslateFromCombo.SetCurSel(48);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("sr")) m_LanguageTranslateFromCombo.SetCurSel(49);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("sk")) m_LanguageTranslateFromCombo.SetCurSel(50);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("sl")) m_LanguageTranslateFromCombo.SetCurSel(51);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("es")) m_LanguageTranslateFromCombo.SetCurSel(52);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("sw")) m_LanguageTranslateFromCombo.SetCurSel(53);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("sv")) m_LanguageTranslateFromCombo.SetCurSel(54);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ta")) m_LanguageTranslateFromCombo.SetCurSel(55);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("te")) m_LanguageTranslateFromCombo.SetCurSel(56);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("th")) m_LanguageTranslateFromCombo.SetCurSel(57);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("tr")) m_LanguageTranslateFromCombo.SetCurSel(58);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("uk")) m_LanguageTranslateFromCombo.SetCurSel(59);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ur")) m_LanguageTranslateFromCombo.SetCurSel(60);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("vi")) m_LanguageTranslateFromCombo.SetCurSel(61);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("cy")) m_LanguageTranslateFromCombo.SetCurSel(62);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("yi")) m_LanguageTranslateFromCombo.SetCurSel(63);*/
}

void SettingDlgFileSystem::InitLanguageTranslateToCombo()
{
	m_LanguageTranslateToCombo.ResetContent();
	m_LanguageTranslateToCombo.AddString(_T("Afrikaans"));
	m_LanguageTranslateToCombo.AddString(_T("Albanian"));
	m_LanguageTranslateToCombo.AddString(_T("Arabic"));
	m_LanguageTranslateToCombo.AddString(_T("Azerbaijani"));
	m_LanguageTranslateToCombo.AddString(_T("Basque"));
	m_LanguageTranslateToCombo.AddString(_T("Belarusian"));
	m_LanguageTranslateToCombo.AddString(_T("Bengali"));
	m_LanguageTranslateToCombo.AddString(_T("Bulgarian"));
	m_LanguageTranslateToCombo.AddString(_T("Catalan"));
	m_LanguageTranslateToCombo.AddString(_T("Chinese Simplified"));
	m_LanguageTranslateToCombo.AddString(_T("Chinese Traditional"));
	m_LanguageTranslateToCombo.AddString(_T("Croatian"));
	m_LanguageTranslateToCombo.AddString(_T("Czech"));
	m_LanguageTranslateToCombo.AddString(_T("Danish"));
	m_LanguageTranslateToCombo.AddString(_T("Dutch"));
	m_LanguageTranslateToCombo.AddString(_T("English"));
	m_LanguageTranslateToCombo.AddString(_T("Esperanto"));
	m_LanguageTranslateToCombo.AddString(_T("Estonian"));
	m_LanguageTranslateToCombo.AddString(_T("Filipino"));
	m_LanguageTranslateToCombo.AddString(_T("Finnish"));
	m_LanguageTranslateToCombo.AddString(_T("French"));
	m_LanguageTranslateToCombo.AddString(_T("Galician"));
	m_LanguageTranslateToCombo.AddString(_T("Georgian"));
	m_LanguageTranslateToCombo.AddString(_T("German"));
	m_LanguageTranslateToCombo.AddString(_T("Greek"));
	m_LanguageTranslateToCombo.AddString(_T("Gujarati"));
	m_LanguageTranslateToCombo.AddString(_T("Haitian Creole"));
	m_LanguageTranslateToCombo.AddString(_T("Hebrew"));
	m_LanguageTranslateToCombo.AddString(_T("Hindi"));
	m_LanguageTranslateToCombo.AddString(_T("Hungarian"));
	m_LanguageTranslateToCombo.AddString(_T("Icelandic"));
	m_LanguageTranslateToCombo.AddString(_T("Indonesian"));
	m_LanguageTranslateToCombo.AddString(_T("Irish"));
	m_LanguageTranslateToCombo.AddString(_T("Italian"));
	m_LanguageTranslateToCombo.AddString(_T("Japanese"));
	m_LanguageTranslateToCombo.AddString(_T("Kannada"));
	m_LanguageTranslateToCombo.AddString(_T("Korean"));
	m_LanguageTranslateToCombo.AddString(_T("Latin"));
	m_LanguageTranslateToCombo.AddString(_T("Latvian"));
	m_LanguageTranslateToCombo.AddString(_T("Lithuanian"));
	m_LanguageTranslateToCombo.AddString(_T("Macedonian"));
	m_LanguageTranslateToCombo.AddString(_T("Malay"));
	m_LanguageTranslateToCombo.AddString(_T("Maltese"));
	m_LanguageTranslateToCombo.AddString(_T("Norwegian"));
	m_LanguageTranslateToCombo.AddString(_T("Persian"));
	m_LanguageTranslateToCombo.AddString(_T("Polish"));
	m_LanguageTranslateToCombo.AddString(_T("Portuguese"));
	m_LanguageTranslateToCombo.AddString(_T("Romanian"));
	m_LanguageTranslateToCombo.AddString(_T("Russian"));
	m_LanguageTranslateToCombo.AddString(_T("Serbian"));
	m_LanguageTranslateToCombo.AddString(_T("Slovak"));
	m_LanguageTranslateToCombo.AddString(_T("Slovenian"));
	m_LanguageTranslateToCombo.AddString(_T("Spanish"));
	m_LanguageTranslateToCombo.AddString(_T("Swahili"));
	m_LanguageTranslateToCombo.AddString(_T("Swedish"));
	m_LanguageTranslateToCombo.AddString(_T("Tamil"));
	m_LanguageTranslateToCombo.AddString(_T("Telugu"));
	m_LanguageTranslateToCombo.AddString(_T("Thai"));
	m_LanguageTranslateToCombo.AddString(_T("Turkish"));
	m_LanguageTranslateToCombo.AddString(_T("Ukrainian"));
	m_LanguageTranslateToCombo.AddString(_T("Urdu"));
	m_LanguageTranslateToCombo.AddString(_T("Vietnamese"));
	m_LanguageTranslateToCombo.AddString(_T("Welsh"));
	m_LanguageTranslateToCombo.AddString(_T("Yiddish"));
	if (AppSettingMgr.m_strLanguageTranslateTo == _T("af")) m_LanguageTranslateToCombo.SetCurSel(0);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("sq")) m_LanguageTranslateToCombo.SetCurSel(1);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ar")) m_LanguageTranslateToCombo.SetCurSel(2);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("az")) m_LanguageTranslateToCombo.SetCurSel(3);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("eu")) m_LanguageTranslateToCombo.SetCurSel(4);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("be")) m_LanguageTranslateToCombo.SetCurSel(5);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("bn")) m_LanguageTranslateToCombo.SetCurSel(6);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("bg")) m_LanguageTranslateToCombo.SetCurSel(7);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ca")) m_LanguageTranslateToCombo.SetCurSel(8);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("zh-CN")) m_LanguageTranslateToCombo.SetCurSel(9);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("zh-TW")) m_LanguageTranslateToCombo.SetCurSel(10);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("hr")) m_LanguageTranslateToCombo.SetCurSel(11);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("cs")) m_LanguageTranslateToCombo.SetCurSel(12);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("da")) m_LanguageTranslateToCombo.SetCurSel(13);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("nl")) m_LanguageTranslateToCombo.SetCurSel(14);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("en")) m_LanguageTranslateToCombo.SetCurSel(15);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("eo")) m_LanguageTranslateToCombo.SetCurSel(16);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("et")) m_LanguageTranslateToCombo.SetCurSel(17);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("tl")) m_LanguageTranslateToCombo.SetCurSel(18);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("fi")) m_LanguageTranslateToCombo.SetCurSel(19);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("fr")) m_LanguageTranslateToCombo.SetCurSel(20);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("gl")) m_LanguageTranslateToCombo.SetCurSel(21);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ka")) m_LanguageTranslateToCombo.SetCurSel(22);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("de")) m_LanguageTranslateToCombo.SetCurSel(23);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("el")) m_LanguageTranslateToCombo.SetCurSel(24);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("gu")) m_LanguageTranslateToCombo.SetCurSel(25);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ht")) m_LanguageTranslateToCombo.SetCurSel(26);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("iw")) m_LanguageTranslateToCombo.SetCurSel(27);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("hi")) m_LanguageTranslateToCombo.SetCurSel(28);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("hu")) m_LanguageTranslateToCombo.SetCurSel(29);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("is")) m_LanguageTranslateToCombo.SetCurSel(30);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("id")) m_LanguageTranslateToCombo.SetCurSel(31);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ga")) m_LanguageTranslateToCombo.SetCurSel(32);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("it")) m_LanguageTranslateToCombo.SetCurSel(33);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ja")) m_LanguageTranslateToCombo.SetCurSel(34);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("kn")) m_LanguageTranslateToCombo.SetCurSel(35);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ko")) m_LanguageTranslateToCombo.SetCurSel(36);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("la")) m_LanguageTranslateToCombo.SetCurSel(37);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("lv")) m_LanguageTranslateToCombo.SetCurSel(38);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("lt")) m_LanguageTranslateToCombo.SetCurSel(39);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("mk")) m_LanguageTranslateToCombo.SetCurSel(40);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ms")) m_LanguageTranslateToCombo.SetCurSel(41);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("mt")) m_LanguageTranslateToCombo.SetCurSel(42);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("no")) m_LanguageTranslateToCombo.SetCurSel(43);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("fa")) m_LanguageTranslateToCombo.SetCurSel(44);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("pl")) m_LanguageTranslateToCombo.SetCurSel(45);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("pt")) m_LanguageTranslateToCombo.SetCurSel(46);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ro")) m_LanguageTranslateToCombo.SetCurSel(47);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ru")) m_LanguageTranslateToCombo.SetCurSel(48);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("sr")) m_LanguageTranslateToCombo.SetCurSel(49);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("sk")) m_LanguageTranslateToCombo.SetCurSel(50);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("sl")) m_LanguageTranslateToCombo.SetCurSel(51);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("es")) m_LanguageTranslateToCombo.SetCurSel(52);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("sw")) m_LanguageTranslateToCombo.SetCurSel(53);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("sv")) m_LanguageTranslateToCombo.SetCurSel(54);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ta")) m_LanguageTranslateToCombo.SetCurSel(55);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("te")) m_LanguageTranslateToCombo.SetCurSel(56);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("th")) m_LanguageTranslateToCombo.SetCurSel(57);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("tr")) m_LanguageTranslateToCombo.SetCurSel(58);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("uk")) m_LanguageTranslateToCombo.SetCurSel(59);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ur")) m_LanguageTranslateToCombo.SetCurSel(60);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("vi")) m_LanguageTranslateToCombo.SetCurSel(61);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("cy")) m_LanguageTranslateToCombo.SetCurSel(62);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("yi")) m_LanguageTranslateToCombo.SetCurSel(63);
}

void SettingDlgFileSystem::FromLanguageSpellCheckCombo()
{
}

void SettingDlgFileSystem::FromLanguageTranslateFromCombo()
{
	int iSel = m_LanguageTranslateFromCombo.GetCurSel();
	switch (iSel)
	{
	case 0: AppSettingMgr.m_strLanguageTranslateFrom = _T("af"); break;
	case 1: AppSettingMgr.m_strLanguageTranslateFrom = _T("sq"); break;
	case 2: AppSettingMgr.m_strLanguageTranslateFrom = _T("ar"); break;
	case 3: AppSettingMgr.m_strLanguageTranslateFrom = _T("az"); break;
	case 4: AppSettingMgr.m_strLanguageTranslateFrom = _T("eu"); break;
	case 5: AppSettingMgr.m_strLanguageTranslateFrom = _T("be"); break;
	case 6: AppSettingMgr.m_strLanguageTranslateFrom = _T("bn"); break;
	case 7: AppSettingMgr.m_strLanguageTranslateFrom = _T("bg"); break;
	case 8: AppSettingMgr.m_strLanguageTranslateFrom = _T("ca"); break;
	case 9: AppSettingMgr.m_strLanguageTranslateFrom = _T("zh-CN"); break;
	case 10: AppSettingMgr.m_strLanguageTranslateFrom = _T("zh-TW"); break;
	case 11: AppSettingMgr.m_strLanguageTranslateFrom = _T("hr"); break;
	case 12: AppSettingMgr.m_strLanguageTranslateFrom = _T("cs"); break;
	case 13: AppSettingMgr.m_strLanguageTranslateFrom = _T("da"); break;
	case 14: AppSettingMgr.m_strLanguageTranslateFrom = _T("nl"); break;
	case 15: AppSettingMgr.m_strLanguageTranslateFrom = _T("en"); break;
	case 16: AppSettingMgr.m_strLanguageTranslateFrom = _T("eo"); break;
	case 17: AppSettingMgr.m_strLanguageTranslateFrom = _T("et"); break;
	case 18: AppSettingMgr.m_strLanguageTranslateFrom = _T("tl"); break;
	case 19: AppSettingMgr.m_strLanguageTranslateFrom = _T("fi"); break;
	case 20: AppSettingMgr.m_strLanguageTranslateFrom = _T("fr"); break;
	case 21: AppSettingMgr.m_strLanguageTranslateFrom = _T("gl"); break;
	case 22: AppSettingMgr.m_strLanguageTranslateFrom = _T("ka"); break;
	case 23: AppSettingMgr.m_strLanguageTranslateFrom = _T("de"); break;
	case 24: AppSettingMgr.m_strLanguageTranslateFrom = _T("el"); break;
	case 25: AppSettingMgr.m_strLanguageTranslateFrom = _T("gu"); break;
	case 26: AppSettingMgr.m_strLanguageTranslateFrom = _T("ht"); break;
	case 27: AppSettingMgr.m_strLanguageTranslateFrom = _T("iw"); break;
	case 28: AppSettingMgr.m_strLanguageTranslateFrom = _T("hi"); break;
	case 29: AppSettingMgr.m_strLanguageTranslateFrom = _T("hu"); break;
	case 30: AppSettingMgr.m_strLanguageTranslateFrom = _T("is"); break;
	case 31: AppSettingMgr.m_strLanguageTranslateFrom = _T("id"); break;
	case 32: AppSettingMgr.m_strLanguageTranslateFrom = _T("ga"); break;
	case 33: AppSettingMgr.m_strLanguageTranslateFrom = _T("it"); break;
	case 34: AppSettingMgr.m_strLanguageTranslateFrom = _T("ja"); break;
	case 35: AppSettingMgr.m_strLanguageTranslateFrom = _T("kn"); break;
	case 36: AppSettingMgr.m_strLanguageTranslateFrom = _T("ko"); break;
	case 37: AppSettingMgr.m_strLanguageTranslateFrom = _T("la"); break;
	case 38: AppSettingMgr.m_strLanguageTranslateFrom = _T("lv"); break;
	case 39: AppSettingMgr.m_strLanguageTranslateFrom = _T("lt"); break;
	case 40: AppSettingMgr.m_strLanguageTranslateFrom = _T("mk"); break;
	case 41: AppSettingMgr.m_strLanguageTranslateFrom = _T("ms"); break;
	case 42: AppSettingMgr.m_strLanguageTranslateFrom = _T("mt"); break;
	case 43: AppSettingMgr.m_strLanguageTranslateFrom = _T("no"); break;
	case 44: AppSettingMgr.m_strLanguageTranslateFrom = _T("fa"); break;
	case 45: AppSettingMgr.m_strLanguageTranslateFrom = _T("pl"); break;
	case 46: AppSettingMgr.m_strLanguageTranslateFrom = _T("pt"); break;
	case 47: AppSettingMgr.m_strLanguageTranslateFrom = _T("ro"); break;
	case 48: AppSettingMgr.m_strLanguageTranslateFrom = _T("ru"); break;
	case 49: AppSettingMgr.m_strLanguageTranslateFrom = _T("sr"); break;
	case 50: AppSettingMgr.m_strLanguageTranslateFrom = _T("sk"); break;
	case 51: AppSettingMgr.m_strLanguageTranslateFrom = _T("sl"); break;
	case 52: AppSettingMgr.m_strLanguageTranslateFrom = _T("es"); break;
	case 53: AppSettingMgr.m_strLanguageTranslateFrom = _T("sw"); break;
	case 54: AppSettingMgr.m_strLanguageTranslateFrom = _T("sv"); break;
	case 55: AppSettingMgr.m_strLanguageTranslateFrom = _T("ta"); break;
	case 56: AppSettingMgr.m_strLanguageTranslateFrom = _T("te"); break;
	case 57: AppSettingMgr.m_strLanguageTranslateFrom = _T("th"); break;
	case 58: AppSettingMgr.m_strLanguageTranslateFrom = _T("tr"); break;
	case 59: AppSettingMgr.m_strLanguageTranslateFrom = _T("uk"); break;
	case 60: AppSettingMgr.m_strLanguageTranslateFrom = _T("ur"); break;
	case 61: AppSettingMgr.m_strLanguageTranslateFrom = _T("vi"); break;
	case 62: AppSettingMgr.m_strLanguageTranslateFrom = _T("cy"); break;
	case 63: AppSettingMgr.m_strLanguageTranslateFrom = _T("yi"); break;
	default:
		AppSettingMgr.m_strLanguageTranslateFrom = _T("en");
		break;
	}
}

void SettingDlgFileSystem::FromLanguageTranslateToCombo()
{
	int iSel = m_LanguageTranslateToCombo.GetCurSel();
	switch (iSel)
	{
	case 0: AppSettingMgr.m_strLanguageTranslateTo = _T("af"); break;
	case 1: AppSettingMgr.m_strLanguageTranslateTo = _T("sq"); break;
	case 2: AppSettingMgr.m_strLanguageTranslateTo = _T("ar"); break;
	case 3: AppSettingMgr.m_strLanguageTranslateTo = _T("az"); break;
	case 4: AppSettingMgr.m_strLanguageTranslateTo = _T("eu"); break;
	case 5: AppSettingMgr.m_strLanguageTranslateTo = _T("be"); break;
	case 6: AppSettingMgr.m_strLanguageTranslateTo = _T("bn"); break;
	case 7: AppSettingMgr.m_strLanguageTranslateTo = _T("bg"); break;
	case 8: AppSettingMgr.m_strLanguageTranslateTo = _T("ca"); break;
	case 9: AppSettingMgr.m_strLanguageTranslateTo = _T("zh-CN"); break;
	case 10: AppSettingMgr.m_strLanguageTranslateTo = _T("zh-TW"); break;
	case 11: AppSettingMgr.m_strLanguageTranslateTo = _T("hr"); break;
	case 12: AppSettingMgr.m_strLanguageTranslateTo = _T("cs"); break;
	case 13: AppSettingMgr.m_strLanguageTranslateTo = _T("da"); break;
	case 14: AppSettingMgr.m_strLanguageTranslateTo = _T("nl"); break;
	case 15: AppSettingMgr.m_strLanguageTranslateTo = _T("en"); break;
	case 16: AppSettingMgr.m_strLanguageTranslateTo = _T("eo"); break;
	case 17: AppSettingMgr.m_strLanguageTranslateTo = _T("et"); break;
	case 18: AppSettingMgr.m_strLanguageTranslateTo = _T("tl"); break;
	case 19: AppSettingMgr.m_strLanguageTranslateTo = _T("fi"); break;
	case 20: AppSettingMgr.m_strLanguageTranslateTo = _T("fr"); break;
	case 21: AppSettingMgr.m_strLanguageTranslateTo = _T("gl"); break;
	case 22: AppSettingMgr.m_strLanguageTranslateTo = _T("ka"); break;
	case 23: AppSettingMgr.m_strLanguageTranslateTo = _T("de"); break;
	case 24: AppSettingMgr.m_strLanguageTranslateTo = _T("el"); break;
	case 25: AppSettingMgr.m_strLanguageTranslateTo = _T("gu"); break;
	case 26: AppSettingMgr.m_strLanguageTranslateTo = _T("ht"); break;
	case 27: AppSettingMgr.m_strLanguageTranslateTo = _T("iw"); break;
	case 28: AppSettingMgr.m_strLanguageTranslateTo = _T("hi"); break;
	case 29: AppSettingMgr.m_strLanguageTranslateTo = _T("hu"); break;
	case 30: AppSettingMgr.m_strLanguageTranslateTo = _T("is"); break;
	case 31: AppSettingMgr.m_strLanguageTranslateTo = _T("id"); break;
	case 32: AppSettingMgr.m_strLanguageTranslateTo = _T("ga"); break;
	case 33: AppSettingMgr.m_strLanguageTranslateTo = _T("it"); break;
	case 34: AppSettingMgr.m_strLanguageTranslateTo = _T("ja"); break;
	case 35: AppSettingMgr.m_strLanguageTranslateTo = _T("kn"); break;
	case 36: AppSettingMgr.m_strLanguageTranslateTo = _T("ko"); break;
	case 37: AppSettingMgr.m_strLanguageTranslateTo = _T("la"); break;
	case 38: AppSettingMgr.m_strLanguageTranslateTo = _T("lv"); break;
	case 39: AppSettingMgr.m_strLanguageTranslateTo = _T("lt"); break;
	case 40: AppSettingMgr.m_strLanguageTranslateTo = _T("mk"); break;
	case 41: AppSettingMgr.m_strLanguageTranslateTo = _T("ms"); break;
	case 42: AppSettingMgr.m_strLanguageTranslateTo = _T("mt"); break;
	case 43: AppSettingMgr.m_strLanguageTranslateTo = _T("no"); break;
	case 44: AppSettingMgr.m_strLanguageTranslateTo = _T("fa"); break;
	case 45: AppSettingMgr.m_strLanguageTranslateTo = _T("pl"); break;
	case 46: AppSettingMgr.m_strLanguageTranslateTo = _T("pt"); break;
	case 47: AppSettingMgr.m_strLanguageTranslateTo = _T("ro"); break;
	case 48: AppSettingMgr.m_strLanguageTranslateTo = _T("ru"); break;
	case 49: AppSettingMgr.m_strLanguageTranslateTo = _T("sr"); break;
	case 50: AppSettingMgr.m_strLanguageTranslateTo = _T("sk"); break;
	case 51: AppSettingMgr.m_strLanguageTranslateTo = _T("sl"); break;
	case 52: AppSettingMgr.m_strLanguageTranslateTo = _T("es"); break;
	case 53: AppSettingMgr.m_strLanguageTranslateTo = _T("sw"); break;
	case 54: AppSettingMgr.m_strLanguageTranslateTo = _T("sv"); break;
	case 55: AppSettingMgr.m_strLanguageTranslateTo = _T("ta"); break;
	case 56: AppSettingMgr.m_strLanguageTranslateTo = _T("te"); break;
	case 57: AppSettingMgr.m_strLanguageTranslateTo = _T("th"); break;
	case 58: AppSettingMgr.m_strLanguageTranslateTo = _T("tr"); break;
	case 59: AppSettingMgr.m_strLanguageTranslateTo = _T("uk"); break;
	case 60: AppSettingMgr.m_strLanguageTranslateTo = _T("ur"); break;
	case 61: AppSettingMgr.m_strLanguageTranslateTo = _T("vi"); break;
	case 62: AppSettingMgr.m_strLanguageTranslateTo = _T("cy"); break;
	case 63: AppSettingMgr.m_strLanguageTranslateTo = _T("yi"); break;
	default:
		AppSettingMgr.m_strLanguageTranslateTo = _T("vi");
		break;
	}
}

void SettingDlgFileSystem::UpdateGUISettings(BOOL bFromGUI)
{
	if (bFromGUI)
	{
		UpdateData(TRUE);

		FromLanguageSpellCheckCombo();
		//FromLanguageTranslateFromCombo();
		FromLanguageTranslateToCombo();
		AppSettingMgr.m_BinaryFileExtensionList.RemoveAll();
		AppUtils::SplitCString(m_strBinaryFileExtensionList, CSTRING_SPACE, AppSettingMgr.m_BinaryFileExtensionList);
		AppSettingMgr.m_strBinaryFileExtensionList = m_strBinaryFileExtensionList;
		AppSettingMgr.m_strInitialFilePickerPath = m_strInitialFilePickerPath;
		AppSettingMgr.m_strNodeJSFolderPath = m_strNodeJSFolderPath;
		AppSettingMgr.m_strPythonFolderPath = m_strPythonFolderPath;
		AppSettingMgr.m_strGitWindowFolderPath = m_strGitWindowFolderPath;
		AppSettingMgr.m_strAntiVirusArgument = m_strAntiVirusArgument;
		AppSettingMgr.m_strAntiVirusProgram = m_strAntiVirusProgram;
		AppSettingMgr.m_nLineSpaceAbove = m_nLineSpaceAbove;
		AppSettingMgr.m_nLineSpaceBelow = m_nLineSpaceBelow;
		AppSettingMgr.m_nIntervalAutoSaveFileMinutes = m_nIntervalAutoSaveFileMinutes;
		AppSettingMgr.m_nExplorerExpandLimitFileOpen = m_nExplorerExpandLimitFileOpen;
		AppSettingMgr.m_nExplorerExpandLimitLevel = m_nExplorerExpandLimitLevel;
		AppSettingMgr.m_nFilePreviewSizeLimit = m_nFilePreviewSizeLimit;
		AppSettingMgr.m_nRecentFileLimit = m_nRecentFileLimit;
		AppSettingMgr.m_nLongLineMaximum = m_nLongLineMaximum;
	}
	else
	{
		InitLanguageSpellCheckCombo();
		InitLanguageTranslateFromCombo();
		InitLanguageTranslateToCombo();

		m_strBinaryFileExtensionList = AppSettingMgr.m_strBinaryFileExtensionList;
		m_strInitialFilePickerPath = AppSettingMgr.m_strInitialFilePickerPath;
		m_strNodeJSFolderPath = AppSettingMgr.m_strNodeJSFolderPath;
		m_strPythonFolderPath = AppSettingMgr.m_strPythonFolderPath;
		m_strGitWindowFolderPath = AppSettingMgr.m_strGitWindowFolderPath;
		m_strAntiVirusArgument = AppSettingMgr.m_strAntiVirusArgument;
		m_strAntiVirusProgram = AppSettingMgr.m_strAntiVirusProgram;
		m_nLineSpaceAbove = AppSettingMgr.m_nLineSpaceAbove;
		m_nLineSpaceBelow = AppSettingMgr.m_nLineSpaceBelow;
		m_nIntervalAutoSaveFileMinutes = AppSettingMgr.m_nIntervalAutoSaveFileMinutes;
		m_nExplorerExpandLimitFileOpen = AppSettingMgr.m_nExplorerExpandLimitFileOpen;
		m_nExplorerExpandLimitLevel = AppSettingMgr.m_nExplorerExpandLimitLevel;
		m_nFilePreviewSizeLimit = AppSettingMgr.m_nFilePreviewSizeLimit;
		m_nRecentFileLimit = AppSettingMgr.m_nRecentFileLimit;
		m_nLongLineMaximum = AppSettingMgr.m_nLongLineMaximum;
	}
}

void SettingDlgFileSystem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_INITIAL_FILE_PICKER_PATH_EDIT, m_EditInitialFilePickerPath);
	DDX_Control(pDX, ID_NODE_JS_FOLDER_PATH_EDIT, m_EditNodeJSFolderPath);
	DDX_Control(pDX, ID_PYTHON_FOLDER_PATH_EDIT, m_EditPythonFolderPath);
	DDX_Control(pDX, ID_GIT_WINDOW_FOLDER_PATH_EDIT, m_EditGitWindowFolderPath);
	DDX_Control(pDX, ID_ANTI_VIRUS_PROGRAM_EDIT, m_EditAntiVirusProgram);
	DDX_Text(pDX, ID_INITIAL_FILE_PICKER_PATH_EDIT, m_strInitialFilePickerPath);
	DDX_Text(pDX, ID_NODE_JS_FOLDER_PATH_EDIT, m_strNodeJSFolderPath);
	DDX_Text(pDX, ID_PYTHON_FOLDER_PATH_EDIT, m_strPythonFolderPath);
	DDX_Text(pDX, ID_GIT_WINDOW_FOLDER_PATH_EDIT, m_strGitWindowFolderPath);
	DDX_Text(pDX, ID_ANTI_VIRUS_ARGUMENT_EDIT, m_strAntiVirusArgument);
	DDX_Text(pDX, ID_ANTI_VIRUS_PROGRAM_EDIT, m_strAntiVirusProgram);
	DDX_Text(pDX, ID_LINE_SPACE_ABOVE_EDIT, m_nLineSpaceAbove);
	DDX_Text(pDX, ID_LINE_SPACE_BELOW_EDIT, m_nLineSpaceBelow);
	DDX_Text(pDX, ID_INTERVAL_MINUTES_EDIT, m_nIntervalAutoSaveFileMinutes);
	DDX_Text(pDX, ID_EXPLORER_EXPAND_LIMIT_FILE_OPEN_EDIT, m_nExplorerExpandLimitFileOpen);
	DDX_Text(pDX, ID_EXPLORER_EXPAND_LIMIT_LEVEL_EDIT, m_nExplorerExpandLimitLevel);
	DDX_Text(pDX, ID_FILE_PREVIEW_SIZE_LIMIT_EDIT, m_nFilePreviewSizeLimit);
	DDX_Text(pDX, ID_RECENT_FILE_LIMIT_EDIT, m_nRecentFileLimit);
	DDX_Text(pDX, ID_BINARY_FILE_EXTENSION_LIST, m_strBinaryFileExtensionList);
	DDX_Control(pDX, ID_BINARY_FILE_EXTENSION_LIST, m_EditBinaryFileExtensionList);
	DDX_Control(pDX, ID_LANGUAGE_SPELL_CHECK_COMBO, m_LanguageSpellCheckCombo);
	DDX_Control(pDX, ID_LANGUAGE_TRANSLATE_FROM_COMBO, m_LanguageTranslateFromCombo);
	DDX_Control(pDX, ID_LANGUAGE_TRANSLATE_TO_COMBO, m_LanguageTranslateToCombo);
	DDX_Text(pDX, ID_LONG_LINE_MAXIMUM_EDIT, m_nLongLineMaximum);
}

BEGIN_MESSAGE_MAP(SettingDlgFileSystem, CDialogEx)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

// SettingDlgFileSystem message handlers

void SettingDlgFileSystem::OnDropFiles(HDROP hDropInfo)
{
	CDialogEx::OnDropFiles(hDropInfo);
	int nCntFiles = DragQueryFile(hDropInfo, -1, 0, 0);
	if (nCntFiles == 1)
	{
		CEdit* pEdit = dynamic_cast<CEdit*>(FromHandle(m_hWndChildDropFile));
		if (pEdit)
		{
			TCHAR szPath[_MAX_PATH];
			szPath[0] = 0;
			::DragQueryFile(hDropInfo, 0, szPath, _MAX_PATH);
			if (m_hWndChildDropFile == m_EditAntiVirusProgram.m_hWnd)
			{
				if (PathUtils::IsDirectory(szPath))
				{
					AfxMessageBox(_T("[Error] This setting requires an execution file, not folder!"));
				}
				else
				{
					pEdit->SetWindowTextW(szPath);
				}
			}
			else
			{
				if (PathUtils::IsDirectory(szPath))
				{
					pEdit->SetWindowTextW(szPath);
				}
				else
				{
					pEdit->SetWindowTextW(PathUtils::GetContainerPath(szPath));
				}
			}
		}
	}
	DragFinish(hDropInfo);
}

///////////////////////////////////////////////////////////////////

BOOL CEditDropNotifier::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_DROPFILES)
	{
		SettingDlgFileSystem* pParent = dynamic_cast<SettingDlgFileSystem*>(GetParent());
		if (pParent)
		{
			pParent->m_hWndChildDropFile = this->m_hWnd;
			pParent->SendMessage(WM_DROPFILES, pMsg->wParam, pMsg->lParam);
			return TRUE; // got it
		}
	}
	return FALSE; // allow default processing
}
