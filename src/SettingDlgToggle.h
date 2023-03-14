/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once
#include "afxwin.h"

// SettingDlgToggle dialog

class SettingDlgToggle : public CDialogEx
{
	DECLARE_DYNAMIC(SettingDlgToggle)

public:
	SettingDlgToggle(CWnd* pParent = NULL);   // standard constructor
	virtual ~SettingDlgToggle();

// Dialog Data
	enum { IDD = IDD_DIALOG_SETTING_TOGGLE };

	void UpdateGUISettings(BOOL bFromGUI);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK() {}
	virtual void OnCancel() {}
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	DECLARE_MESSAGE_MAP()

public:
	BOOL m_bAddHostPathToRecentList;
	BOOL m_bAllowOpenFileHasErrorBuild;
	BOOL m_bAskBeforeTerminateProgram;
	BOOL m_bAutoCompleteIgnoreCase;
	BOOL m_bAutoCompleteIgnoreNumbers;
	BOOL m_bAutoSaveDocumentWhenbuild;
	BOOL m_bCheckFileSizeBeforeOpen;
	BOOL m_bDetectFileChangeFromOutSide;
	BOOL m_bDisplayMessageBoxForFileChange;
	BOOL m_bDrawCaretLineFrame;
	BOOL m_bUseWin10ExplorerStyle;
	BOOL m_bWarningForFileNotExist;
	BOOL m_bDrawFoldingLineUnderLineStyle;
	BOOL m_bEditorEnableBoldFont;
	BOOL m_bEnableAutoComplete;
	BOOL m_bEnableAutoSearchWhenTyping;
	BOOL m_bEnableCaretBlink;
	BOOL m_bEnableDisplayBuildErrorOnEditor;
	BOOL m_bEnableHightLightFolder;
	BOOL m_bEnableMultipleCursor;
	BOOL m_bEnableMutilpleCursor;
	BOOL m_bEnablePathNavigation;
	BOOL m_bEnablePreviewFile;
	BOOL m_bEnableProcessIndentationTab;
	BOOL m_bEnableSynchronizeScrolling;
	BOOL m_bEnableUrlHighlight;
	BOOL m_bEnableWFlagCPP11;
	BOOL m_bEnableWarningFlagForCAndCPP;
	BOOL m_bEnableWindowSubsytemFlagForCAndCPP;
	BOOL m_bHideAllTargetFileSystem;
	BOOL m_bOpenWindowCmdWhenRunProgram;
	BOOL m_bReturnPreviousEditorState;
	BOOL m_bRevealExplorerWhenDoubleClickOnTab;
	BOOL m_bRevealExplorerWhenSwitchTab;
	BOOL m_bSaveDataBookmarkWindow;
	BOOL m_bShowTrackingBar;
	BOOL m_bUseFolderMarginClassic;
	BOOL m_bUseInitialFilePickerPath;
	BOOL m_bEditorEnableItalicFont;
	BOOL m_bEditorEnableUnderlineFont;
	BOOL m_bAskBeforeReplaceInFiles;
	BOOL m_bEnableAutoDetectCodePage;
	BOOL m_bEnableShowHideFoldingMargin;
};
