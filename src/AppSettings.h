/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "EditorDataStructure.h"

enum FOLDER_MARGIN_STYPE
{
	STYLE_ARROW = 0,
	STYLE_PLUS_MINUS,
	STYLE_TREE_CIRCLE,
	STYLE_TREE_BOX,
};

enum EDITOR_TAB_ACTIVE_COLOR
{
	MDITAB_ACTIVE_COLOR_GRAY = RGB(230, 230, 230),
	MDITAB_ACTIVE_COLOR_ORRANGE = RGB(230, 159, 102),
	MDITAB_ACTIVE_COLOR_GREEN = RGB(166, 226, 46),
	MDITAB_ACTIVE_COLOR_YELLOW = RGB(230, 219, 116),
	MDITAB_NON_ACTIVE_COLOR = RGB(180, 180, 180),
};

enum EDITOR_THEME_BACKGROUND_COLOR
{
	THEME_BACKGROUND_COLOR_SIERRA_BLUE = RGB(39, 50, 50), // sierra blue
	THEME_BACKGROUND_COLOR_MONOKAI = RGB(39, 40, 34), // monokai
	THEME_BACKGROUND_COLOR_LIGHTING = RGB(255, 255, 255), // lighting
};

enum APPLICATION_THEME_LOOK
{
	THEME_OFFICE_2003 = 0, 
	THEME_VISUAL_STUDIO_2005,
	THEME_WINDOWS_XP_NATIVE,
	THEME_OFFICE_2007_AQUA,
	THEME_OFFICE_2007_OBSIDIAN_BLACK,
	THEME_OFFICE_2007_SILVER_LOOK,
	THEME_OFFICE_2007_LUNA_BLUE,
	THEME_VISUAL_STUDIO_2008_LOOK,
};

enum EDITOR_INDICATOR_COLOR
{
	INDICATOR_YELLOW = RGB(235, 245, 0),
	INDICATOR_WHITE = RGB(255, 255, 255),
	INDICATOR_BLACK = RGB(0, 0, 0),
};

enum EDITOR_INDICATOR_STYLE
{
	BOX = 0,
	FULL_BOX = 1,
};

enum RENDER_INDICATOR_ACTION
{
	SINGLE_CLICK_ACTION = 0,
	DOUBLE_CLICK_ACTION = 1,
};

enum EDITOR_CARET_BLINK_COLOR
{
	BLINK_COLOR_WHITE = RGB(255, 255, 255),
	BLINK_COLOR_ORRANGE = RGB(255, 69, 0),
	BLINK_COLORR_GREEN = RGB(0, 255, 0),
	BLINK_COLOR_YELLOW = RGB(235, 245, 0),
	BLINK_COLOR_RED = RGB(255, 0, 0),
	BLINK_COLOR_BLACK = RGB(0, 0, 0),
};

enum VINATEXT_TEXT_FONT
{
	TOHOMA,
	CONSOLAS,
	COURIER_NEW,
};

enum APPLICATION_LANGUAGE
{
	LANGUAGE_UNKNOWN = 0,
	LANGUAGE_ENGLISH = 1,
	LANGUAGE_VIETNAMESE = 2,
};

const CString VINATEXT_TEXT_FONT_NAME[] =
{
	_T("Tahoma"),
	_T("Consolas"),
	_T("Courier New"),
};

struct DockWindowFontSetting
{
	CString _font = VINATEXT_TEXT_FONT_NAME[CONSOLAS];
	int _lfHeight = 14;
	int _lfWeight = FW_MEDIUM;
};

struct DialogFontSetting
{
	CString _font = VINATEXT_TEXT_FONT_NAME[TOHOMA];
	int _lfHeight = 14;
	int _lfWeight = FW_MEDIUM;
};

struct EditorFontSetting
{
	CString _font = VINATEXT_TEXT_FONT_NAME[CONSOLAS];
	int _nEditorTextFontSize = 9;
	int _nEditorLineNumberFontSize = 9;
	BOOL _bEnableBoldFont = FALSE;
	BOOL _bEnableItalicFont = FALSE;
	BOOL _bEnableUnderlineFont = FALSE;
};

#define MAXIMUM_MOST_RECENT_FILE 16 // can not exceed this value

// general settings
class CAppSettings
{
public:
	void ResetAllSettings(); // all new variable members need to be initiated in this function also!

	// editor document ID
	void RemoveDocumentUndefTitle(const CString & strTitle);
	CString CreateDocumentUndefTitle();
	int GetNewFileCopyID();

	// editor recent file data
	void SaveRecentEditorInfo(const CString& strFileName);
	RecentEditorInfo GetRecentEditorInfo(const CString& strFileName);
	void ResetRecentEditorInfo();

	// save / load
	BOOL SaveSetting();
	BOOL LoadSetting();
	BOOL SaveRecentEditorData();
	BOOL LoadRecentEditorData();

	// all settings ///////////////////////////////////////////////////////////////////

	BOOL m_bOpenWindowCmdWhenRunProgram = FALSE;
	BOOL m_bEnableUrlHighlight = TRUE;
	BOOL m_bAutoSaveDocument = FALSE;
	BOOL m_bWarningForFileNotExist = TRUE;
	BOOL m_bRevealExplorerWhenSwitchFile = FALSE;
	BOOL m_bRevealExplorerWhenDlbClkFile = TRUE;
	BOOL m_bDrawFoldingLineUnderLineStyle = FALSE;
	BOOL m_bAutoSaveDocumentWhenbuild = TRUE;
	BOOL m_bDrawCaretLineFrame = TRUE;
	BOOL m_bEnableHightLightFolder = TRUE;
	BOOL m_bEnableDisplayBuildErrorOnEditor = TRUE;
	BOOL m_bAllowOpenFileHasErrorBuild = FALSE;
	BOOL m_bDetectFileChangeFromOutSide = TRUE;
	BOOL m_bEnableAutoComplete = TRUE;
	BOOL m_bEnableProcessIndentationTab = TRUE;
	BOOL m_bAutoCompleteIgnoreNumbers = TRUE;
	BOOL m_bAutoCompleteIgnoreCase = TRUE;
	BOOL m_bCheckFileSizeBeforeOpen = TRUE;
	BOOL m_bDisplayMessageBoxForFileChange = FALSE;
	BOOL m_bAskBeforeTerminateProgram = FALSE;
	BOOL m_bEnableWarningFlagForCAndCPP = TRUE;
	BOOL m_bEnableWFlagCPP11 = TRUE;
	BOOL m_bEnableWindowSubsytemFlagForCAndCPP = FALSE;
	BOOL m_bAutoGenBuildConfigFile = TRUE;
	BOOL m_bUseWin10ExplorerStyle = FALSE;
	BOOL m_bEnablePreviewFile = FALSE;
	BOOL m_bHideAllTargetFileSystem = FALSE;
	BOOL m_bUseFolderMarginClassic = FALSE;
	BOOL m_bEnableCaretBlink = FALSE;
	BOOL m_bEnableMutilpleCursor = TRUE;
	BOOL m_bUseInitialFilePickerPath = FALSE;
	BOOL m_bReturnPreviousEditorState = TRUE;
	BOOL m_bEnablePathNavigation = TRUE;
	BOOL m_bShowTrackingBar = TRUE;
	BOOL m_bSaveDataBookmarkWindow = TRUE;
	BOOL m_bAddHostPathToRecentList = TRUE;
	BOOL m_bEnableSynchronizeScrolling = FALSE;
	BOOL m_bEnableAutoSearchWhenTyping = TRUE;
	BOOL m_bAskBeforeReplaceInFiles = TRUE;
	BOOL m_bEnableAutoDetectCodePage = TRUE;

	// editor style
	FOLDER_MARGIN_STYPE m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_ARROW;
	EDITOR_INDICATOR_STYLE m_IndicatorStyle = EDITOR_INDICATOR_STYLE::BOX;
	
	// editor auto save file
	int m_nIntervalMinutes = 9;

	// paths
	CString m_strInitialFilePickerPath = _T("C:\\");
	CString m_strLangguageSpellCheck = _T("en-us");
	CString m_strNodeJSFolderPath = _T("C:\\");
	CString m_strPythonFolderPath = _T("C:\\");
	CString m_strGitWindowFolderPath = _T("C:\\Program Files\\Git");
	CString m_strAntiVirusProgram = _T("C:\\Program Files\\Windows Defender\\MpCmdRun.exe");
	CString m_strAntiVirusArgument = _T("-Scan -ScanType 3 -File");

	// translation
	CString m_strLanguageTranslateFrom = _T("en");
	CString m_strLanguageTranslateTo = _T("vi");

	// editorfont size
	DockWindowFontSetting m_DockWindowFontSetting;
	EditorFontSetting	  m_EditorFontSetting;
	DialogFontSetting	  m_DialogFontSetting;

	// ui
	EDITOR_CARET_BLINK_COLOR m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_YELLOW;
	EDITOR_TAB_ACTIVE_COLOR m_ActiveTabColor = EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_GRAY;
	RENDER_INDICATOR_ACTION m_RenderIndicatorAction = RENDER_INDICATOR_ACTION::DOUBLE_CLICK_ACTION;
	EDITOR_INDICATOR_COLOR m_IndicatorColor = EDITOR_INDICATOR_COLOR::INDICATOR_YELLOW;
	EDITOR_THEME_BACKGROUND_COLOR m_ThemeColor = EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_SIERRA_BLUE;
	APPLICATION_THEME_LOOK m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_WINDOWS_XP_NATIVE;
	APPLICATION_LANGUAGE m_ApplicationLanguage = APPLICATION_LANGUAGE::LANGUAGE_ENGLISH;

	// page width alignment text
	int m_nPageAlignmentWidth = 78;
	int m_nLongLineMaximum = 80;
	int m_nRecentFileLimit = MAXIMUM_MOST_RECENT_FILE;
	int m_nLineSpaceAbove = 2;
	int m_nLineSpaceBelow = 2;
	int m_nExplorerExpandLimitLevel = 50;
	int m_nExplorerExpandLimitFileOpen = 20;
	int m_nFilePreviewSizeLimit = 10000000; // 10 MB
	int m_nDialogComboboxLimitSave = 30;

	CStringArray m_BinaryFileExtensionList;
	CString m_strBinaryFileExtensionList = _T("tga dds eot swf jar zip pyc pyo exe dll obj o a lib so dylib ncb sdf suo pdb idb DS_Store class psd db lnk o 7z tar ios mdb sqlite lib pyd opendb bin");
	std::vector<CString>  m_MultipleClipboardBuffer;

private:
	// settings can not edit by users...
	int m_nFileCopyCounter = 0;
	std::unordered_map<std::string, RecentEditorInfo> m_RecentEditorCaretInfo;
	DocumentEmptyIDBuffer m_DocIDBuffer;
	// singleton
	SINGLETON_IMPLEMENT(CAppSettings)
};

#define AppSettingMgr CAppSettings::GetInstance()