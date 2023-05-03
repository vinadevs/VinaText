#include "stdafx.h"
#include "AppSettings.h"
#include "AppUtil.h"
#include "PathUtil.h"
#include "FileUtil.h"
#include "EditorDoc.h"
#include "EditorView.h"

void CAppSettings::RemoveDocumentUndefTitle(const CString& strTitle)
{
	int nDocUndefID = AppUtils::CStringToInt(strTitle.Mid(10).Trim());
	m_DocIDBuffer.erase(nDocUndefID);
}

CString CAppSettings::CreateDocumentUndefTitle()
{
	int nDocID = 1;
	BOOL bBreakFlag = TRUE;
	while (bBreakFlag)
	{
		// -> 1 3 4 6
		if (m_DocIDBuffer.find(nDocID) == m_DocIDBuffer.end())
		{
			m_DocIDBuffer.insert(nDocID);
			bBreakFlag = FALSE;
		}
		else
		{
			nDocID++;
		}
	}
	return AfxCStringFormat(_T(" untitled %d"), nDocID);
}

int CAppSettings::GetNewFileCopyID()
{
	return m_nFileCopyCounter++;
}

void CAppSettings::ResetEditorCaretInfo()
{
	m_RecentEditorCaretInfo.clear();
}

void CAppSettings::SaveRecentEditorCaretInfo(const CString& strPathName)
{
	CEditorDoc* pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetExistedDocument(strPathName));
	if (!pDoc) return;
	CEditorView* pView = pDoc->GetEditorView();
	if (!pView) return;
	CEditorCtrl* pEditor = pView->GetEditorCtrl();
	if (!pEditor) return;
	RecentEditorInfo data;
	data._nCurrentPosition = pEditor->GetCurrentPosition();
	data._nFirstVisibleLine = pEditor->GetFirstVisibleLine();
	data._nWrapMode = static_cast<int>(pEditor->IsEditorInWrapMode());
	if (data._nCurrentPosition != 0 || data._nFirstVisibleLine != 0 || data._nWrapMode != 0)
	{
		m_RecentEditorCaretInfo[AppUtils::CStringToStd(strPathName)] = data;
	}
}

RecentEditorInfo CAppSettings::GetRecentEditorCaretInfo(const CString& strPathName)
{
	const auto found = m_RecentEditorCaretInfo.find(AppUtils::CStringToStd(strPathName));
	if (found != m_RecentEditorCaretInfo.end())
	{
		return found->second;
	}
	return RecentEditorInfo();
}

void CAppSettings::ResetAllSettings()
{
	// general settings
	m_bOpenWindowCmdWhenRunProgram = FALSE;
	m_bEnableUrlHighlight = TRUE;
	m_bAutoSaveDocument = FALSE;
	m_bWarningForFileNotExist = TRUE;
	m_bRevealExplorerWhenSwitchFile = FALSE;
	m_bRevealExplorerWhenDlbClkFile = TRUE;
	m_bDrawFoldingLineUnderLineStyle = FALSE;
	m_bAutoSaveDocumentWhenbuild = TRUE;
	m_bDrawCaretLineFrame = TRUE;
	m_bEnableHightLightFolder = TRUE;
	m_bAllowOpenFileHasErrorBuild = FALSE;
	m_bDetectFileChangeFromOutSide = TRUE;
	m_bEnableAutoComplete = FALSE;
	m_bEnableProcessIndentationTab = TRUE;
	m_bAutoCompleteIgnoreNumbers = TRUE;
	m_bAutoCompleteIgnoreCase = TRUE;
	m_bCheckFileSizeBeforeOpen = TRUE;
	m_bDisplayMessageBoxForFileChange = FALSE;
	m_bAskBeforeTerminateProgram = FALSE;
	m_bEnableDisplayBuildErrorOnEditor = TRUE;
	m_bEnableWarningFlagForCAndCPP = TRUE;
	m_bAutoGenBuildConfigFile = TRUE;
	m_bUseWin10ExplorerStyle = FALSE;
	m_bEnablePreviewFile = FALSE;
	m_bHideAllTargetFileSystem = FALSE;
	m_bUseFolderMarginClassic = FALSE;
	m_bEnableCaretBlink = FALSE;
	m_bEnableMultipleCursor = TRUE;
	m_bKeepPreviousEditorState = TRUE;
	m_bEnableWindowSubsytemFlagForCAndCPP = FALSE;
	m_bEnableWFlagCPP11 = TRUE;
	m_bEnablePathNavigation = TRUE;
	m_bShowTrackingBar = TRUE;
	m_bSaveDataBookmarkWindow = TRUE;
	m_bAddHostPathToRecentList = TRUE;
	m_bEnableSynchronizeScrolling = FALSE;
	m_bEnableAutoSearchWhenTyping = TRUE;
	m_bAskBeforeReplaceInFiles = TRUE;
	m_bEnableAutoDetectCodePage = TRUE;
	m_bEnableShowHideFoldingMargin = FALSE;
	m_bAutoSaveFileWhenCloseApp = TRUE;

	m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_TREE_BOX;

	// indicator style
	m_IndicatorStyle = EDITOR_INDICATOR_STYLE::FULL_BOX;

	// auto save file interval
	m_nIntervalAutoSaveFileMinutes = 120;

	m_bUseInitialFilePickerPath = FALSE;
	m_strInitialFilePickerPath = _T("C:\\");
	m_strPythonFolderPath = _T("C:\\");
	m_strNodeJSFolderPath = _T("C:\\");
	m_strGitWindowFolderPath = _T("C:\\");
	m_strAntiVirusProgram = _T("C:\\Program Files\\Windows Defender\\MpCmdRun.exe");
	m_strAntiVirusArgument = _T("-Scan -ScanType 3 -File");
	m_strLanguageTranslateFrom = _T("en");
	m_strLanguageTranslateTo = _T("vi");

	// spell checker
	m_strLanguageSpellCheck = _T("en-us");

	m_DockWindowFontSetting._font = VINATEXT_TEXT_FONT_NAME[CONSOLAS];
	m_DockWindowFontSetting._lfHeight = 14;
	m_DockWindowFontSetting._lfWeight = FW_MEDIUM;

	m_DialogFontSetting._font = VINATEXT_TEXT_FONT_NAME[COURIER_NEW];
	m_DialogFontSetting._lfHeight = 14;
	m_DialogFontSetting._lfWeight = FW_MEDIUM;

	// font settings
	m_EditorFontSetting._font = VINATEXT_TEXT_FONT_NAME[COURIER_NEW];
	m_EditorFontSetting._bEnableBoldFont = FALSE;
	m_EditorFontSetting._bEnableItalicFont = FALSE;
	m_EditorFontSetting._bEnableUnderlineFont = FALSE;
	m_EditorFontSetting._nEditorTextFontSize = 12;
	m_EditorFontSetting._nEditorLineNumberFontSize = 12;

	// ui
	m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_YELLOW;
	m_ActiveTabColor = EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_GRAY;
	m_RenderIndicatorAction = RENDER_INDICATOR_ACTION::DOUBLE_CLICK_ACTION;
	m_IndicatorColor = EDITOR_INDICATOR_COLOR::INDICATOR_BLUE;
	m_AppThemeColor = EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_LIGHT;
	m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_OFFICE_2007_SILVER_LOOK;
	m_ApplicationLanguage = VINATEXT_DISPLAY_LANGUAGE::LANGUAGE_ENGLISH;

	// page width alignment text
	m_nPageAlignmentWidth = 78;
	m_nLongLineMaximum = 80;
	m_nRecentFileLimit = MAXIMUM_MOST_RECENT_FILE;
	m_nFilePreviewSizeLimit = 10000000; // 5 MB
	m_nLineSpaceAbove = 0;
	m_nLineSpaceBelow = 0;
	m_nExplorerExpandLimitLevel = 50;
	m_nExplorerExpandLimitFileOpen = 20;

	m_nFileCopyCounter = 0;
	m_DocIDBuffer.clear();

	m_nDialogComboboxLimitSave = 30;

	m_strBinaryFileExtensionList = _T("tga dds eot swf jar zip pyc pyo exe dll obj o a lib so dylib ncb sdf suo pdb idb .DS_Store class psd db lnk doc docx ppt pptx xlsx o 7z tar ios mdb sqlite xls lib pyd pptm opendb bin");

	m_BinaryFileExtensionList.RemoveAll();
	AppUtils::SplitCString(m_strBinaryFileExtensionList, CSTRING_SPACE, m_BinaryFileExtensionList);
}

BOOL CAppSettings::SaveSettingData()
{
	CString strJsonFilePath = PathUtils::GetVinaTextAppDataPath() + _T("vinatext-app-settings.json");
	JSonWriter jsonWriter(strJsonFilePath, "VinaText Setting");

	jsonWriter.AddBOOL("OpenWindowCmdWhenRunProgram", m_bOpenWindowCmdWhenRunProgram);
	jsonWriter.AddBOOL("EnableUrlHighlight", m_bEnableUrlHighlight);
	jsonWriter.AddBOOL("WarningForFileNotExist", m_bWarningForFileNotExist);
	jsonWriter.AddBOOL("RevealExplorerWhenSwitchFile", m_bRevealExplorerWhenSwitchFile);
	jsonWriter.AddBOOL("RevealExplorerWhenDlbClkFile", m_bRevealExplorerWhenDlbClkFile);
	jsonWriter.AddBOOL("DrawFoldingLineUnderLineStyle", m_bDrawFoldingLineUnderLineStyle);
	jsonWriter.AddBOOL("AutoSaveDocumentWhenbuild", m_bAutoSaveDocumentWhenbuild);
	jsonWriter.AddBOOL("DrawCaretLineFrame", m_bDrawCaretLineFrame);
	jsonWriter.AddBOOL("EnableHightLightFolder", m_bEnableHightLightFolder);
	jsonWriter.AddBOOL("EnableDisplayBuildErrorOnEditor", m_bEnableDisplayBuildErrorOnEditor);
	jsonWriter.AddBOOL("AllowOpenFileHasErrorBuild", m_bAllowOpenFileHasErrorBuild);
	jsonWriter.AddBOOL("DetectFileChangeFromOutSide", m_bDetectFileChangeFromOutSide);
	jsonWriter.AddBOOL("EnableAutoComplete", m_bEnableAutoComplete);
	jsonWriter.AddBOOL("EnableProcessIndentationTab", m_bEnableProcessIndentationTab);
	jsonWriter.AddBOOL("AutoCompleteIgnoreNumbers", m_bAutoCompleteIgnoreNumbers);
	jsonWriter.AddBOOL("AutoCompleteIgnoreCase", m_bAutoCompleteIgnoreCase);
	jsonWriter.AddBOOL("CheckFileSizeBeforeOpen", m_bCheckFileSizeBeforeOpen);
	jsonWriter.AddBOOL("DisplayMessageBoxForFileChange", m_bDisplayMessageBoxForFileChange);
	jsonWriter.AddBOOL("AskBeforeTerminateProgram", m_bAskBeforeTerminateProgram);
	jsonWriter.AddBOOL("EnableWarningFlagForCAndCPP", m_bEnableWarningFlagForCAndCPP);
	jsonWriter.AddBOOL("UseWin10ExplorerStyle", m_bUseWin10ExplorerStyle);
	jsonWriter.AddBOOL("EnablePreviewFile", m_bEnablePreviewFile);
	jsonWriter.AddBOOL("HideAllTargetFileSystem", m_bHideAllTargetFileSystem);
	jsonWriter.AddBOOL("UseFolderMarginClassic", m_bUseFolderMarginClassic);
	jsonWriter.AddBOOL("EnableCaretBlink", m_bEnableCaretBlink);
	jsonWriter.AddBOOL("EnableMultipleCursor", m_bEnableMultipleCursor);
	jsonWriter.AddBOOL("UseInitialFilePickerPath", m_bUseInitialFilePickerPath);
	jsonWriter.AddBOOL("KeepPreviousEditorState", m_bKeepPreviousEditorState);;
	jsonWriter.AddBOOL("EnableWindowSubsytemFlagForCAndCPP", m_bEnableWindowSubsytemFlagForCAndCPP);
	jsonWriter.AddBOOL("EnableWFlagCPP11", m_bEnableWFlagCPP11);
	jsonWriter.AddBOOL("EnablePathNavigation", m_bEnablePathNavigation);
	jsonWriter.AddBOOL("ShowTrackingBar", m_bShowTrackingBar);
	jsonWriter.AddBOOL("SaveDataBookmarkWindow", m_bSaveDataBookmarkWindow);
	jsonWriter.AddBOOL("AddHostPathToRecentList", m_bAddHostPathToRecentList);
	jsonWriter.AddBOOL("EnableSynchronizeScrolling", m_bEnableSynchronizeScrolling);
	jsonWriter.AddBOOL("EnableAutoSearchWhenTyping", m_bEnableAutoSearchWhenTyping);
	jsonWriter.AddBOOL("AskBeforeReplaceInFiles", m_bAskBeforeReplaceInFiles);
	jsonWriter.AddBOOL("EnableAutoDetectCodePage", m_bEnableAutoDetectCodePage);
	jsonWriter.AddBOOL("EnableShowHideFoldingMargin", m_bEnableShowHideFoldingMargin);
	jsonWriter.AddBOOL("AutoSaveFileWhenCloseApp", m_bAutoSaveFileWhenCloseApp);
	jsonWriter.AddValue("InitialFilePickerPath", AppUtils::CStringToStd(m_strInitialFilePickerPath));
	jsonWriter.AddValue("LanguageSpellCheck", AppUtils::CStringToStd(m_strLanguageSpellCheck));
	jsonWriter.AddValue("DockWindowFontName", AppUtils::CStringToStd(m_DockWindowFontSetting._font));
	jsonWriter.AddValue("BinaryFileExtensionList", AppUtils::CStringToStd(m_strBinaryFileExtensionList));
	jsonWriter.AddInteger("DockWindowFontHeight", m_DockWindowFontSetting._lfHeight);
	jsonWriter.AddInteger("DockWindowFontWeight", m_DockWindowFontSetting._lfWeight);
	jsonWriter.AddValue("DialogFontName", AppUtils::CStringToStd(m_DialogFontSetting._font));
	jsonWriter.AddInteger("DialogFontHeight", m_DialogFontSetting._lfHeight);
	jsonWriter.AddInteger("DialogFontWeight", m_DialogFontSetting._lfWeight);
	jsonWriter.AddValue("EditorFontName", AppUtils::CStringToStd(m_EditorFontSetting._font));
	jsonWriter.AddBOOL("EditorEnableBoldFont", m_EditorFontSetting._bEnableBoldFont);
	jsonWriter.AddBOOL("EditorEnableItalicFont", m_EditorFontSetting._bEnableItalicFont);
	jsonWriter.AddBOOL("EditorEnableUnderlineFont", m_EditorFontSetting._bEnableUnderlineFont);
	jsonWriter.AddInteger("EditorLineNumberFontSize", m_EditorFontSetting._nEditorLineNumberFontSize);
	jsonWriter.AddInteger("EditorTextFontSize", m_EditorFontSetting._nEditorTextFontSize);
	jsonWriter.AddInteger("FilePreviewSizeLimit", m_nFilePreviewSizeLimit);
	jsonWriter.AddInteger("FolderMarginStyle", m_FolderMarginStyle);
	jsonWriter.AddInteger("IndicatorStyle", m_IndicatorStyle);
	jsonWriter.AddInteger("IntervalAutoSaveFileMinutes", m_nIntervalAutoSaveFileMinutes);
	jsonWriter.AddValue("CaretBlinkColor", AppUtils::CStringToStd(AppUtils::ColorToRGBCString(m_CaretBlinkColor)));
	jsonWriter.AddValue("ActiveTabColor", AppUtils::CStringToStd(AppUtils::ColorToRGBCString(m_ActiveTabColor)));
	jsonWriter.AddValue("IndicatorColor", AppUtils::CStringToStd(AppUtils::ColorToRGBCString(m_IndicatorColor)));
	jsonWriter.AddValue("ApplicationThemeColor", AppUtils::CStringToStd(AppUtils::ColorToRGBCString(m_AppThemeColor)));
	jsonWriter.AddInteger("ApplicationThemeLook", m_ApplicationThemeLook);
	jsonWriter.AddInteger("ApplicationLanguage", m_ApplicationLanguage);
	jsonWriter.AddInteger("RenderIndicatorAction", m_RenderIndicatorAction);
	jsonWriter.AddInteger("PageAlignmentWidth", m_nPageAlignmentWidth);
	jsonWriter.AddInteger("LongLineColumnLimitation", m_nLongLineMaximum);
	jsonWriter.AddInteger("RecentFileLimit", m_nRecentFileLimit);
	jsonWriter.AddInteger("LineSpaceAbove", m_nLineSpaceAbove);
	jsonWriter.AddInteger("LineSpaceBelow", m_nLineSpaceBelow);
	jsonWriter.AddInteger("ExplorerExpandLimitLevel", m_nExplorerExpandLimitLevel);
	jsonWriter.AddInteger("ExplorerExpandLimitFileOpen", m_nExplorerExpandLimitFileOpen);
	jsonWriter.AddInteger("DialogComboboxLimitSave", m_nDialogComboboxLimitSave);
	jsonWriter.AddValue("NodeJSFolderPath", AppUtils::CStringToStd(m_strNodeJSFolderPath));
	jsonWriter.AddValue("PythonFolderPath", AppUtils::CStringToStd(m_strPythonFolderPath));
	jsonWriter.AddValue("GitWindowFolderPath", AppUtils::CStringToStd(m_strGitWindowFolderPath));
	jsonWriter.AddValue("AntiVirusProgram", AppUtils::CStringToStd(m_strAntiVirusProgram));
	jsonWriter.AddValue("AntiVirusArgument", AppUtils::CStringToStd(m_strAntiVirusArgument));
	jsonWriter.AddValue("LanguageTranslateFrom", AppUtils::CStringToStd(m_strLanguageTranslateFrom));
	jsonWriter.AddValue("LanguageTranslateTo", AppUtils::CStringToStd(m_strLanguageTranslateTo));

	jsonWriter.SaveFile();

	return TRUE;
}

BOOL CAppSettings::LoadSettingData()
{
	CString strJsonFilePath = PathUtils::GetVinaTextAppDataPath() + _T("vinatext-app-settings.json");
	if (!PathFileExists(strJsonFilePath))
	{
		ResetAllSettings();
		return FALSE;
	}

	JSonReader jsonReader(strJsonFilePath, "VinaText Setting");
	if (!jsonReader.LoadFile()) return FALSE;

	jsonReader.ReadBOOL("OpenWindowCmdWhenRunProgram", m_bOpenWindowCmdWhenRunProgram);
	jsonReader.ReadBOOL("EnableUrlHighlight", m_bEnableUrlHighlight);
	jsonReader.ReadBOOL("WarningForFileNotExist", m_bWarningForFileNotExist);
	jsonReader.ReadBOOL("RevealExplorerWhenSwitchFile", m_bRevealExplorerWhenSwitchFile);
	jsonReader.ReadBOOL("RevealExplorerWhenDlbClkFile", m_bRevealExplorerWhenDlbClkFile);
	jsonReader.ReadBOOL("DrawFoldingLineUnderLineStyle", m_bDrawFoldingLineUnderLineStyle);
	jsonReader.ReadBOOL("AutoSaveDocumentWhenbuild", m_bAutoSaveDocumentWhenbuild);
	jsonReader.ReadBOOL("DrawCaretLineFrame", m_bDrawCaretLineFrame);
	jsonReader.ReadBOOL("EnableHightLightFolder", m_bEnableHightLightFolder);
	jsonReader.ReadBOOL("EnableDisplayBuildErrorOnEditor", m_bEnableDisplayBuildErrorOnEditor);
	jsonReader.ReadBOOL("AllowOpenFileHasErrorBuild", m_bAllowOpenFileHasErrorBuild);
	jsonReader.ReadBOOL("DetectFileChangeFromOutSide", m_bDetectFileChangeFromOutSide);
	jsonReader.ReadBOOL("EnableAutoComplete", m_bEnableAutoComplete);
	jsonReader.ReadBOOL("EnableProcessIndentationTab", m_bEnableProcessIndentationTab);
	jsonReader.ReadBOOL("AutoCompleteIgnoreNumbers", m_bAutoCompleteIgnoreNumbers);
	jsonReader.ReadBOOL("AutoCompleteIgnoreCase", m_bAutoCompleteIgnoreCase);
	jsonReader.ReadBOOL("CheckFileSizeBeforeOpen", m_bCheckFileSizeBeforeOpen);
	jsonReader.ReadBOOL("DisplayMessageBoxForFileChange", m_bDisplayMessageBoxForFileChange);
	jsonReader.ReadBOOL("AskBeforeTerminateProgram", m_bAskBeforeTerminateProgram);
	jsonReader.ReadBOOL("EnableWarningFlagForCAndCPP", m_bEnableWarningFlagForCAndCPP);
	jsonReader.ReadBOOL("UseWin10ExplorerStyle", m_bUseWin10ExplorerStyle);
	jsonReader.ReadBOOL("EnablePreviewFile", m_bEnablePreviewFile);
	jsonReader.ReadBOOL("HideAllTargetFileSystem", m_bHideAllTargetFileSystem);
	jsonReader.ReadBOOL("UseFolderMarginClassic", m_bUseFolderMarginClassic);
	jsonReader.ReadBOOL("EnableCaretBlink", m_bEnableCaretBlink);
	jsonReader.ReadBOOL("EnableMultipleCursor", m_bEnableMultipleCursor);
	jsonReader.ReadBOOL("UseInitialFilePickerPath", m_bUseInitialFilePickerPath);
	jsonReader.ReadBOOL("KeepPreviousEditorState", m_bKeepPreviousEditorState);
	jsonReader.ReadBOOL("EnableWindowSubsytemFlagForCAndCPP", m_bEnableWindowSubsytemFlagForCAndCPP);
	jsonReader.ReadBOOL("EnableWFlagCPP11", m_bEnableWFlagCPP11);
	jsonReader.ReadBOOL("EnablePathNavigation", m_bEnablePathNavigation);
	jsonReader.ReadBOOL("ShowTrackingBar", m_bShowTrackingBar);
	jsonReader.ReadBOOL("SaveDataBookmarkWindow", m_bSaveDataBookmarkWindow);
	jsonReader.ReadBOOL("AddHostPathToRecentList", m_bAddHostPathToRecentList);
	jsonReader.ReadBOOL("EnableSynchronizeScrolling", m_bEnableSynchronizeScrolling);
	jsonReader.ReadBOOL("EnableAutoSearchWhenTyping", m_bEnableAutoSearchWhenTyping);
	jsonReader.ReadBOOL("AskBeforeReplaceInFiles", m_bAskBeforeReplaceInFiles);
	jsonReader.ReadBOOL("EnableAutoDetectCodePage", m_bEnableAutoDetectCodePage);
	jsonReader.ReadBOOL("AutoSaveFileWhenCloseApp", m_bAutoSaveFileWhenCloseApp);
	jsonReader.ReadBOOL("EnableShowHideFoldingMargin", m_bEnableShowHideFoldingMargin);
	jsonReader.ReadCString("BinaryFileExtensionList", m_strBinaryFileExtensionList);
	jsonReader.ReadCString("InitialFilePickerPath", m_strInitialFilePickerPath);
	jsonReader.ReadCString("LanguageSpellCheck", m_strLanguageSpellCheck);
	jsonReader.ReadCString("DockWindowFontName", m_DockWindowFontSetting._font);
	jsonReader.ReadInteger("DockWindowFontHeight", m_DockWindowFontSetting._lfHeight);
	jsonReader.ReadInteger("DockWindowFontWeight", m_DockWindowFontSetting._lfWeight);
	jsonReader.ReadCString("DialogFontName", m_DialogFontSetting._font);
	jsonReader.ReadInteger("DialogFontHeight", m_DialogFontSetting._lfHeight);
	jsonReader.ReadInteger("DialogFontWeight", m_DialogFontSetting._lfWeight);
	jsonReader.ReadCString("EditorFontName", m_EditorFontSetting._font);
	jsonReader.ReadBOOL("EditorEnableBoldFont", m_EditorFontSetting._bEnableBoldFont);
	jsonReader.ReadBOOL("EditorEnableItalicFont", m_EditorFontSetting._bEnableItalicFont);
	jsonReader.ReadBOOL("EditorEnableUnderlineFont", m_EditorFontSetting._bEnableUnderlineFont);
	jsonReader.ReadInteger("EditorLineNumberFontSize", m_EditorFontSetting._nEditorLineNumberFontSize);
	jsonReader.ReadInteger("EditorTextFontSize", m_EditorFontSetting._nEditorTextFontSize);
	jsonReader.ReadInteger("FilePreviewSizeLimit", m_nFilePreviewSizeLimit);
	jsonReader.ReadInteger("FolderMarginStyle", (int&)m_FolderMarginStyle);
	jsonReader.ReadInteger("IndicatorStyle", (int&)m_IndicatorStyle);
	jsonReader.ReadInteger("IntervalAutoSaveFileMinutes", (int&)m_nIntervalAutoSaveFileMinutes);
	jsonReader.ReadColor("CaretBlinkColor", (int&)m_CaretBlinkColor);
	jsonReader.ReadColor("ActiveTabColor", (int&)m_ActiveTabColor);
	jsonReader.ReadColor("IndicatorColor", (int&)m_IndicatorColor);
	jsonReader.ReadColor("ApplicationThemeColor", (int&)m_AppThemeColor);
	jsonReader.ReadInteger("ApplicationThemeLook", (int&)m_ApplicationThemeLook);
	jsonReader.ReadInteger("ApplicationLanguage", (int&)m_ApplicationLanguage);
	jsonReader.ReadInteger("RenderIndicatorAction", (int&)m_RenderIndicatorAction);
	jsonReader.ReadInteger("PageAlignmentWidth", m_nPageAlignmentWidth);
	jsonReader.ReadInteger("LongLineColumnLimitation", m_nLongLineMaximum);
	jsonReader.ReadInteger("RecentFileLimit", m_nRecentFileLimit);
	jsonReader.ReadInteger("LineSpaceAbove", m_nLineSpaceAbove);
	jsonReader.ReadInteger("LineSpaceBelow", m_nLineSpaceBelow);
	jsonReader.ReadInteger("ExplorerExpandLimitLevel", m_nExplorerExpandLimitLevel);
	jsonReader.ReadInteger("ExplorerExpandLimitFileOpen", m_nExplorerExpandLimitFileOpen);
	jsonReader.ReadInteger("DialogComboboxLimitSave", m_nDialogComboboxLimitSave);
	jsonReader.ReadCString("PythonFolderPath", m_strPythonFolderPath);
	jsonReader.ReadCString("NodeJSFolderPath", m_strNodeJSFolderPath);
	jsonReader.ReadCString("GitWindowFolderPath", m_strGitWindowFolderPath);
	jsonReader.ReadCString("AntiVirusProgram", m_strAntiVirusProgram);
	jsonReader.ReadCString("AntiVirusArgument", m_strAntiVirusArgument);
	jsonReader.ReadCString("LanguageTranslateFrom", m_strLanguageTranslateFrom);
	jsonReader.ReadCString("LanguageTranslateTo", m_strLanguageTranslateTo);

	m_BinaryFileExtensionList.RemoveAll();
	AppUtils::SplitCString(m_strBinaryFileExtensionList, CSTRING_SPACE, m_BinaryFileExtensionList);

	return TRUE;
}

BOOL CAppSettings::SaveRecentEditorCaretData()
{
	CString strJsonFilePath = PathUtils::GetVinaTextAppDataPath() + _T("recent-file-data.json");
	JSonWriter jsonWriter(strJsonFilePath, "VinaText Editor File State Data");
	jsonWriter.AddRecentEditorInfo("EditorFileStateData", m_RecentEditorCaretInfo);
	jsonWriter.SaveFile();
	return TRUE;
}

BOOL CAppSettings::LoadRecentEditorCaretData()
{
	CString strJsonFilePath = PathUtils::GetVinaTextAppDataPath() + _T("recent-file-data.json");
	if (!PathFileExists(strJsonFilePath))
	{
		ResetAllSettings();
		return FALSE;
	}
	JSonReader jsonReader(strJsonFilePath, "VinaText Editor File State Data");
	if (!jsonReader.LoadFile()) return FALSE;
	jsonReader.ReadRecentEditorInfo("EditorFileStateData", m_RecentEditorCaretInfo);
	return TRUE;
}