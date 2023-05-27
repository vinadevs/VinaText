/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "EditorDataStructure.h"
#include "Singleton.h"

static const CString VINATEXT_TEXT_FONT_NAME[] =
{
	_T("Tahoma"),
	_T("Consolas"),
	_T("Courier New"),
};

struct AppGuiFontSetting
{
	CString _font = VINATEXT_TEXT_FONT_NAME[CONSOLAS];
	int _lfHeight = 14;
	int _lfWeight = FW_MEDIUM;
};

struct EditorFontSetting
{
	CString _lfFaceName = VINATEXT_TEXT_FONT_NAME[COURIER_NEW];
	int _iPointSize = 12;
	BOOL _isBold = FALSE;
	BOOL _isItalic = FALSE;
	BOOL _isUnderline = FALSE;
	COLORREF _color = RGB(0, 0, 0);
};

#define MDITAB_SETTINGS_COLOR RGB(230, 159, 102)

// VinaText general settings
////////////////////////////////////////////////////////////////////////////////
// All new settings need be added into void CAppSettings::ResetAllSettings() too.
////////////////////////////////////////////////////////////////////////////////
class CAppSettings
{
public:
	void ResetAllSettings();

	// editor document ID
	void RemoveDocumentUndefTitle(const CString& strTitle);
	CString CreateDocumentUndefTitle();
	int GetNewFileCopyID();

	// editor recent file data
	void SaveRecentEditorCaretInfo(const CString& strPathName);
	RecentEditorInfo GetRecentEditorCaretInfo(const CString& strPathName);
	void ResetEditorCaretInfo();

	// save/load from file
	BOOL SaveSettingData();
	BOOL LoadSettingData();
	BOOL SaveRecentEditorCaretData();
	BOOL LoadRecentEditorCaretData();

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
	BOOL m_bEnableMultipleCursor = TRUE;
	BOOL m_bUseInitialFilePickerPath = FALSE;
	BOOL m_bKeepPreviousEditorState = TRUE;
	BOOL m_bEnablePathNavigation = TRUE;
	BOOL m_bShowTrackingBar = TRUE;
	BOOL m_bSaveDataBookmarkWindow = TRUE;
	BOOL m_bAddHostPathToRecentList = TRUE;
	BOOL m_bEnableSynchronizeScrolling = FALSE;
	BOOL m_bEnableAutoSearchWhenTyping = TRUE;
	BOOL m_bAskBeforeReplaceInFiles = TRUE;
	BOOL m_bEnableAutoDetectCodePage = TRUE;
	BOOL m_bEnableShowHideFoldingMargin = FALSE;
	BOOL m_bAutoSaveFileWhenCloseApp = TRUE;
	BOOL m_bAutoAddNewLineAtTheEOF = FALSE;

	// editor style
	FOLDER_MARGIN_STYPE m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_TREE_BOX;
	EDITOR_INDICATOR_STYLE m_IndicatorStyle = EDITOR_INDICATOR_STYLE::FULL_BOX;
	
	// editor auto save file
	int m_nIntervalAutoSaveFileMinutes = 120;

	// paths
	CString m_strInitialFilePickerPath = _T("C:\\");
	CString m_strLanguageSpellCheck = _T("en-us");
	CString m_strNodeJSFolderPath = _T("C:\\");
	CString m_strPythonFolderPath = _T("C:\\");
	CString m_strAntiVirusProgram = _T("C:\\Program Files\\Windows Defender\\MpCmdRun.exe");
	CString m_strAntiVirusArgument = _T("-Scan -ScanType 3 -File");

	// translation
	CString m_strLanguageTranslateFrom = _T("en");
	CString m_strLanguageTranslateTo = _T("vi");

	// editorfont size
	AppGuiFontSetting m_AppGuiFontSetting;
	EditorFontSetting m_EditorFontSetting;

	// ui
	EDITOR_CARET_BLINK_COLOR m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_YELLOW;
	EDITOR_TAB_ACTIVE_COLOR m_ActiveTabColor = EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_GRAY;
	RENDER_INDICATOR_ACTION m_RenderIndicatorAction = RENDER_INDICATOR_ACTION::DOUBLE_CLICK_ACTION;
	EDITOR_INDICATOR_COLOR m_IndicatorColor = EDITOR_INDICATOR_COLOR::INDICATOR_BLUE;
	EDITOR_THEME_BACKGROUND_COLOR m_AppThemeColor = EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_LIGHT;
	APPLICATION_THEME_LOOK m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_OFFICE_2007_SILVER_LOOK;
	VINATEXT_DISPLAY_LANGUAGE m_ApplicationLanguage = VINATEXT_DISPLAY_LANGUAGE::LANGUAGE_ENGLISH;

	// toolbar
	DEFAULT_TOOLBAR_TERMINAL m_DefaultToolbarTerminal = DEFAULT_TOOLBAR_TERMINAL::MS_CMD;

	// eol for new file
	int m_DefaultFileEOL = SC_EOL_CRLF;

	// page width alignment text
	int m_nPageAlignmentWidth = 78;
	int m_nLongLineMaximum = 80;
	int m_nRecentFileLimit = 16;
	int m_nLineSpaceAbove = 0;
	int m_nLineSpaceBelow = 0;
	int m_nExplorerExpandLimitLevel = 50;
	int m_nExplorerExpandLimitFileOpen = 20;
	int m_nFilePreviewSizeLimit = 10000000; // 10 MB
	int m_nDialogComboboxLimitSave = 30;
	int m_nEditorZoomFactor = 0;

	CStringArray m_BinaryFileExtensionList;
	CString m_strBinaryFileExtensionList = _T("tga dds eot swf jar zip pyc pyo exe dll obj o a lib so dylib ncb sdf suo pdb idb DS_Store class psd db lnk o 7z tar ios mdb sqlite lib pyd opendb bin");
	std::vector<CString>  m_MultipleClipboardBuffer;

private:
	// settings can not edit by users...
	int m_nFileCopyCounter = 0;
	// Editor caret info state
	typedef std::unordered_map<std::string, RecentEditorInfo> MapRecentEditorInfo;
	MapRecentEditorInfo m_RecentEditorCaretInfo;

	// Document ID
	typedef std::unordered_set<int> DocumentEmptyIDBuffer;
	DocumentEmptyIDBuffer m_DocIDBuffer;
	// singleton
	SINGLETON_IMPLEMENT(CAppSettings)
};

#define AppSettingMgr CAppSettings::GetInstance()
#define IS_LIGHT_THEME AppSettingMgr.m_AppThemeColor == THEME_BACKGROUND_COLOR_LIGHT