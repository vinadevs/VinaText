/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "SettingDlgToggle.h"
#include "afxdialogex.h"
#include "AppSettings.h"

// SettingDlgToggle dialog

IMPLEMENT_DYNAMIC(SettingDlgToggle, CDialogEx)

SettingDlgToggle::SettingDlgToggle(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SETTING_TOGGLE, pParent)
	, m_bAddHostPathToRecentList(FALSE)
	, m_bAllowOpenFileHasErrorBuild(FALSE)
	, m_bAskBeforeTerminateProgram(FALSE)
	, m_bAutoCompleteIgnoreCase(FALSE)
	, m_bAutoCompleteIgnoreNumbers(FALSE)
	, m_bAutoSaveDocumentWhenbuild(FALSE)
	, m_bCheckFileSizeBeforeOpen(FALSE)
	, m_bDetectFileChangeFromOutSide(FALSE)
	, m_bDisplayMessageBoxForFileChange(FALSE)
	, m_bDrawCaretLineFrame(FALSE)
	, m_bUseWin10ExplorerStyle(FALSE)
	, m_bWarningForFileNotExist(FALSE)
	, m_bDrawFoldingLineUnderLineStyle(FALSE)
	, m_bEditorEnableBoldFont(FALSE)
	, m_bEnableAutoComplete(FALSE)
	, m_bEnableAutoSearchWhenTyping(FALSE)
	, m_bEnableCaretBlink(FALSE)
	, m_bEnableDisplayBuildErrorOnEditor(FALSE)
	, m_bEnableHightLightFolder(FALSE)
	, m_bEnableMultipleCursor(FALSE)
	, m_bEnablePathNavigation(FALSE)
	, m_bEnablePreviewFile(FALSE)
	, m_bEnableProcessIndentationTab(FALSE)
	, m_bEnableSynchronizeScrolling(FALSE)
	, m_bEnableUrlHighlight(FALSE)
	, m_bEnableWFlagCPP11(FALSE)
	, m_bEnableWarningFlagForCAndCPP(FALSE)
	, m_bEnableWindowSubsytemFlagForCAndCPP(FALSE)
	, m_bHideAllTargetFileSystem(FALSE)
	, m_bOpenWindowCmdWhenRunProgram(FALSE)
	, m_bReturnPreviousEditorState(FALSE)
	, m_bRevealExplorerWhenDoubleClickOnTab(FALSE)
	, m_bRevealExplorerWhenSwitchTab(FALSE)
	, m_bSaveDataBookmarkWindow(FALSE)
	, m_bShowTrackingBar(FALSE)
	, m_bUseFolderMarginClassic(FALSE)
	, m_bUseInitialFilePickerPath(FALSE)
	, m_bEditorEnableItalicFont(FALSE)
	, m_bEditorEnableUnderlineFont(FALSE)
	, m_bAskBeforeReplaceInFiles(FALSE)
	, m_bEnableAutoDetectCodePage(FALSE)
	, m_bEnableShowHideFoldingMargin(FALSE)
{

}

SettingDlgToggle::~SettingDlgToggle()
{
}

void SettingDlgToggle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, ID_ADD_HOST_PATH_TO_RECENT_LIST, m_bAddHostPathToRecentList);
	DDX_Check(pDX, ID_ALLOW_OPEN_FILE_HAS_ERROR_BUILD, m_bAllowOpenFileHasErrorBuild);
	DDX_Check(pDX, ID_ASK_BEFORE_TERMINATE_PROGRAM, m_bAskBeforeTerminateProgram);
	DDX_Check(pDX, ID_AUTO_COMPLETE_IGNORE_CASE, m_bAutoCompleteIgnoreCase);
	DDX_Check(pDX, ID_AUTO_COMPLETE_IGNORE_NUMBERS, m_bAutoCompleteIgnoreNumbers);
	DDX_Check(pDX, ID_AUTO_SAVE_DOCUMENT_WHENBUILD, m_bAutoSaveDocumentWhenbuild);
	DDX_Check(pDX, ID_CHECK_FILE_SIZE_BEFORE_OPEN, m_bCheckFileSizeBeforeOpen);
	DDX_Check(pDX, ID_DETECT_FILE_CHANGE_FROM_OUT_SIDE, m_bDetectFileChangeFromOutSide);
	DDX_Check(pDX, ID_DISPLAY_MESSAGE_BOX_FOR_FILE_CHANGE, m_bDisplayMessageBoxForFileChange);
	DDX_Check(pDX, ID_DRAW_CARET_LINE_FRAME, m_bDrawCaretLineFrame);
	DDX_Check(pDX, ID_USE_WIN10_EXPLORER_STYLE, m_bUseWin10ExplorerStyle);
	DDX_Check(pDX, ID_WARNING_FOR_FILE_NOT_EXIST, m_bWarningForFileNotExist);
	DDX_Check(pDX, ID_DRAW_FOLDING_LINE_UNDER_LINE_STYLE, m_bDrawFoldingLineUnderLineStyle);
	DDX_Check(pDX, ID_EDITOR_ENABLE_BOLD_FONT, m_bEditorEnableBoldFont);
	DDX_Check(pDX, ID_ENABLE_AUTO_COMPLETE, m_bEnableAutoComplete);
	DDX_Check(pDX, ID_ENABLE_AUTO_SEARCH_WHEN_TYPING, m_bEnableAutoSearchWhenTyping);
	DDX_Check(pDX, ID_ENABLE_CARET_BLINK, m_bEnableCaretBlink);
	DDX_Check(pDX, ID_ENABLE_DISPLAY_BUILD_ERROR_ON_EDITOR, m_bEnableDisplayBuildErrorOnEditor);
	DDX_Check(pDX, ID_ENABLE_HIGHT_LIGHT_FOLDER, m_bEnableHightLightFolder);
	DDX_Check(pDX, ID_ENABLE_MULTIPLE_CURSOR, m_bEnableMultipleCursor);
	DDX_Check(pDX, ID_ENABLE_PATH_NAVIGATION, m_bEnablePathNavigation);
	DDX_Check(pDX, ID_ENABLE_PREVIEW_FILE, m_bEnablePreviewFile);
	DDX_Check(pDX, ID_ENABLE_PROCESS_INDENTATION_TAB, m_bEnableProcessIndentationTab);
	DDX_Check(pDX, ID_ENABLE_SYNCHRONIZE_SCROLLING, m_bEnableSynchronizeScrolling);
	DDX_Check(pDX, ID_ENABLE_URL_HIGHLIGHT, m_bEnableUrlHighlight);
	DDX_Check(pDX, ID_ENABLE_WFLAG_CPP11, m_bEnableWFlagCPP11);
	DDX_Check(pDX, ID_ENABLE_WARNING_FLAG_FOR_C_AND_CPP, m_bEnableWarningFlagForCAndCPP);
	DDX_Check(pDX, ID_ENABLE_WINDOW_SUBSYTEM_FLAG_FOR_C_AND_CPP, m_bEnableWindowSubsytemFlagForCAndCPP);
	DDX_Check(pDX, ID_HIDE_ALL_TARGET_FILE_SYSTEM, m_bHideAllTargetFileSystem);
	DDX_Check(pDX, ID_OPEN_WINDOW_CMD_WHEN_RUN_PROGRAM, m_bOpenWindowCmdWhenRunProgram);
	DDX_Check(pDX, ID_RETURN_PREVIOUS_EDITOR_STATE, m_bReturnPreviousEditorState);
	DDX_Check(pDX, ID_REVEAL_EXPLORER_WHEN_DLB_CLK_FILE, m_bRevealExplorerWhenDoubleClickOnTab);
	DDX_Check(pDX, ID_REVEAL_EXPLORER_WHEN_SWITCH_FILE, m_bRevealExplorerWhenSwitchTab);
	DDX_Check(pDX, ID_SAVE_DATA_BOOKMARK_WINDOW, m_bSaveDataBookmarkWindow);
	DDX_Check(pDX, ID_SHOW_TRACKING_BAR, m_bShowTrackingBar);
	DDX_Check(pDX, ID_USE_FOLDER_MARGIN_CLASSIC, m_bUseFolderMarginClassic);
	DDX_Check(pDX, ID_ALLOW_USE_INITIAL_FILE_PICKER_PATH, m_bUseInitialFilePickerPath);
	DDX_Check(pDX, ID_EDITOR_ENABLE_ITALIC_FONT, m_bEditorEnableItalicFont);
	DDX_Check(pDX, ID_EDITOR_ENABLE_UNDERLINE_FONT, m_bEditorEnableUnderlineFont);
	DDX_Check(pDX, ID_ASK_BEFORE_REPLACE_IN_FILES, m_bAskBeforeReplaceInFiles);
	DDX_Check(pDX, ID_ENABLE_AUTO_DETECT_CODE_PAGE, m_bEnableAutoDetectCodePage);
}

BOOL SettingDlgToggle::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UpdateGUISettings(FALSE);

	UpdateData(FALSE);

	return TRUE;
}

BOOL SettingDlgToggle::PreTranslateMessage(MSG * pMsg)
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

void SettingDlgToggle::UpdateGUISettings(BOOL bFromGUI)
{
	if (bFromGUI)
	{
		UpdateData(TRUE);

		AppSettingMgr.m_bAddHostPathToRecentList = m_bAddHostPathToRecentList;
		AppSettingMgr.m_bAllowOpenFileHasErrorBuild = m_bAllowOpenFileHasErrorBuild;
		AppSettingMgr.m_bAskBeforeTerminateProgram = m_bAskBeforeTerminateProgram;
		AppSettingMgr.m_bAutoCompleteIgnoreCase = m_bAutoCompleteIgnoreCase;
		AppSettingMgr.m_bAutoCompleteIgnoreNumbers = m_bAutoCompleteIgnoreNumbers;
		AppSettingMgr.m_bAutoSaveDocumentWhenbuild = m_bAutoSaveDocumentWhenbuild;
		AppSettingMgr.m_bCheckFileSizeBeforeOpen = m_bCheckFileSizeBeforeOpen;
		AppSettingMgr.m_bDetectFileChangeFromOutSide = m_bDetectFileChangeFromOutSide;
		AppSettingMgr.m_bDisplayMessageBoxForFileChange = m_bDisplayMessageBoxForFileChange;
		AppSettingMgr.m_bDrawCaretLineFrame = m_bDrawCaretLineFrame;
		AppSettingMgr.m_bUseWin10ExplorerStyle = m_bUseWin10ExplorerStyle;
		AppSettingMgr.m_bWarningForFileNotExist = m_bWarningForFileNotExist;
		AppSettingMgr.m_bDrawFoldingLineUnderLineStyle = m_bDrawFoldingLineUnderLineStyle;
		AppSettingMgr.m_EditorFontSetting._bEnableBoldFont = m_bEditorEnableBoldFont;
		AppSettingMgr.m_EditorFontSetting._bEnableItalicFont = m_bEditorEnableItalicFont;
		AppSettingMgr.m_EditorFontSetting._bEnableUnderlineFont = m_bEditorEnableUnderlineFont;
		AppSettingMgr.m_bEnableAutoComplete = m_bEnableAutoComplete;
		AppSettingMgr.m_bEnableAutoSearchWhenTyping = m_bEnableAutoSearchWhenTyping;
		AppSettingMgr.m_bEnableCaretBlink = m_bEnableCaretBlink;
		AppSettingMgr.m_bEnableDisplayBuildErrorOnEditor = m_bEnableDisplayBuildErrorOnEditor;
		AppSettingMgr.m_bEnableHightLightFolder = m_bEnableHightLightFolder;
		AppSettingMgr.m_bEnableMultipleCursor = m_bEnableMultipleCursor;
		AppSettingMgr.m_bEnablePathNavigation = m_bEnablePathNavigation;
		AppSettingMgr.m_bEnablePreviewFile = m_bEnablePreviewFile;
		AppSettingMgr.m_bEnableProcessIndentationTab = m_bEnableProcessIndentationTab;
		AppSettingMgr.m_bEnableSynchronizeScrolling = m_bEnableSynchronizeScrolling;
		AppSettingMgr.m_bEnableUrlHighlight = m_bEnableUrlHighlight;
		AppSettingMgr.m_bEnableWFlagCPP11 = m_bEnableWFlagCPP11;
		AppSettingMgr.m_bEnableWarningFlagForCAndCPP = m_bEnableWarningFlagForCAndCPP;
		AppSettingMgr.m_bEnableWindowSubsytemFlagForCAndCPP = m_bEnableWindowSubsytemFlagForCAndCPP;
		AppSettingMgr.m_bHideAllTargetFileSystem = m_bHideAllTargetFileSystem;
		AppSettingMgr.m_bOpenWindowCmdWhenRunProgram = m_bOpenWindowCmdWhenRunProgram;
		AppSettingMgr.m_bKeepPreviousEditorState = m_bReturnPreviousEditorState;
		AppSettingMgr.m_bRevealExplorerWhenDlbClkFile = m_bRevealExplorerWhenDoubleClickOnTab;
		AppSettingMgr.m_bRevealExplorerWhenSwitchFile = m_bRevealExplorerWhenSwitchTab;
		AppSettingMgr.m_bSaveDataBookmarkWindow = m_bSaveDataBookmarkWindow;
		AppSettingMgr.m_bShowTrackingBar = m_bShowTrackingBar;
		AppSettingMgr.m_bUseFolderMarginClassic = m_bUseFolderMarginClassic;
		AppSettingMgr.m_bUseInitialFilePickerPath = m_bUseInitialFilePickerPath;
		AppSettingMgr.m_bAskBeforeReplaceInFiles = m_bAskBeforeReplaceInFiles;
		AppSettingMgr.m_bEnableAutoDetectCodePage = m_bEnableAutoDetectCodePage;
	}
	else
	{
		m_bAddHostPathToRecentList = AppSettingMgr.m_bAddHostPathToRecentList;
		m_bAllowOpenFileHasErrorBuild = AppSettingMgr.m_bAllowOpenFileHasErrorBuild;
		m_bAskBeforeTerminateProgram = AppSettingMgr.m_bAskBeforeTerminateProgram;
		m_bAutoCompleteIgnoreCase = AppSettingMgr.m_bAutoCompleteIgnoreCase;
		m_bAutoCompleteIgnoreNumbers = AppSettingMgr.m_bAutoCompleteIgnoreNumbers;
		m_bAutoSaveDocumentWhenbuild = AppSettingMgr.m_bAutoSaveDocumentWhenbuild;
		m_bCheckFileSizeBeforeOpen = AppSettingMgr.m_bCheckFileSizeBeforeOpen;
		m_bDetectFileChangeFromOutSide = AppSettingMgr.m_bDetectFileChangeFromOutSide;
		m_bDisplayMessageBoxForFileChange = AppSettingMgr.m_bDisplayMessageBoxForFileChange;
		m_bDrawCaretLineFrame = AppSettingMgr.m_bDrawCaretLineFrame;
		m_bUseWin10ExplorerStyle = AppSettingMgr.m_bUseWin10ExplorerStyle;
		m_bWarningForFileNotExist = AppSettingMgr.m_bWarningForFileNotExist;
		m_bDrawFoldingLineUnderLineStyle = AppSettingMgr.m_bDrawFoldingLineUnderLineStyle;
		m_bEditorEnableBoldFont = AppSettingMgr.m_EditorFontSetting._bEnableBoldFont;
		m_bEditorEnableItalicFont = AppSettingMgr.m_EditorFontSetting._bEnableItalicFont;
		m_bEditorEnableUnderlineFont = AppSettingMgr.m_EditorFontSetting._bEnableUnderlineFont;
		m_bEnableAutoComplete = AppSettingMgr.m_bEnableAutoComplete;
		m_bEnableAutoSearchWhenTyping = AppSettingMgr.m_bEnableAutoSearchWhenTyping;
		m_bEnableCaretBlink = AppSettingMgr.m_bEnableCaretBlink;
		m_bEnableDisplayBuildErrorOnEditor = AppSettingMgr.m_bEnableDisplayBuildErrorOnEditor;
		m_bEnableHightLightFolder = AppSettingMgr.m_bEnableHightLightFolder;
		m_bEnableMultipleCursor = AppSettingMgr.m_bEnableMultipleCursor;
		m_bEnablePathNavigation = AppSettingMgr.m_bEnablePathNavigation;
		m_bEnablePreviewFile = AppSettingMgr.m_bEnablePreviewFile;
		m_bEnableProcessIndentationTab = AppSettingMgr.m_bEnableProcessIndentationTab;
		m_bEnableSynchronizeScrolling = AppSettingMgr.m_bEnableSynchronizeScrolling;
		m_bEnableUrlHighlight = AppSettingMgr.m_bEnableUrlHighlight;
		m_bEnableWFlagCPP11 = AppSettingMgr.m_bEnableWFlagCPP11;
		m_bEnableWarningFlagForCAndCPP = AppSettingMgr.m_bEnableWarningFlagForCAndCPP;
		m_bEnableWindowSubsytemFlagForCAndCPP = AppSettingMgr.m_bEnableWindowSubsytemFlagForCAndCPP;
		m_bHideAllTargetFileSystem = AppSettingMgr.m_bHideAllTargetFileSystem;
		m_bOpenWindowCmdWhenRunProgram = AppSettingMgr.m_bOpenWindowCmdWhenRunProgram;
		m_bReturnPreviousEditorState = AppSettingMgr.m_bKeepPreviousEditorState;
		m_bRevealExplorerWhenDoubleClickOnTab = AppSettingMgr.m_bRevealExplorerWhenDlbClkFile;
		m_bRevealExplorerWhenSwitchTab = AppSettingMgr.m_bRevealExplorerWhenSwitchFile;
		m_bSaveDataBookmarkWindow = AppSettingMgr.m_bSaveDataBookmarkWindow;
		m_bShowTrackingBar = AppSettingMgr.m_bShowTrackingBar;
		m_bUseFolderMarginClassic = AppSettingMgr.m_bUseFolderMarginClassic;
		m_bUseInitialFilePickerPath = AppSettingMgr.m_bUseInitialFilePickerPath;
		m_bAskBeforeReplaceInFiles = AppSettingMgr.m_bAskBeforeReplaceInFiles;
		m_bEnableAutoDetectCodePage = AppSettingMgr.m_bEnableAutoDetectCodePage;
	}
}

BEGIN_MESSAGE_MAP(SettingDlgToggle, CDialogEx)

END_MESSAGE_MAP()