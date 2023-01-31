/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "OptionsPages.h"
#include "AppSettings.h"
#include "AppUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
	void UpdateAppSettings()
	{
		UPDATE_MAIN_FRAME(MAIN_FRAME_UPDATE_MSG::MAIN_FRAME_UPDATE_ALL_DOCKPANE,
						MAIN_FRAME_UPDATE_HINT::MAIN_FRAME_UPDATE_HINT_SETTING_CHANGED,
						AppUtils::GetMDIActiveDocument());

		UPDATE_ALL_VIEWS(MSG_TARGET_UPDATE_ALL_VIEW,
						VIEW_UPDATE_HINT::VIEW_UPDATE_HINT_SETTING_CHANGED,
						AppUtils::GetMDIActiveDocument());

		LOG_OUTPUT_MESSAGE_COLOR(_T("> All settings updated..."));
	}
}

/////////////////////////////////////////////////////////////////////////////
// COptionsPageEditorSetting property page

IMPLEMENT_DYNCREATE(COptionsPageEditorSetting, CMFCPropertyPage)

COptionsPageEditorSetting::COptionsPageEditorSetting() : CMFCPropertyPage(COptionsPageEditorSetting::IDD)
, m_bEnableBoldFont(FALSE)
, m_bEnableSaveDocumentWhenBuild(FALSE)
, m_bDisplayWarningFileNotExist(FALSE)
{
}

COptionsPageEditorSetting::~COptionsPageEditorSetting()
{
}

BEGIN_MESSAGE_MAP(COptionsPageEditorSetting, CMFCPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_BOLD_FONT, &COptionsPageEditorSetting::OnSettingModified)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_URL_HIGHLIGHT, &COptionsPageEditorSetting::OnSettingModified)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_AUTO_SAVE_FILE, &COptionsPageEditorSetting::OnSettingModified)
	ON_BN_CLICKED(IDC_CHECK_AUTO_SAVE_DOCUMENT_WHEN_BUILD, &COptionsPageEditorSetting::OnSettingModified)
	ON_BN_CLICKED(IDC_CHECK_DISPLAY_WARNING_NOT_EXIST_FILE, &COptionsPageEditorSetting::OnSettingModified)
	ON_BN_CLICKED(IDC_RADIO_WINDOW_CMD_RUN_MODE, &COptionsPageEditorSetting::OnSettingModified)
	ON_BN_CLICKED(IDC_RADIO_WINDOW_BUILD_MODE, &COptionsPageEditorSetting::OnSettingModified)
	ON_CBN_SELCHANGE(IDC_COMBO_EDITOR_COLOR_THEME, &COptionsPageEditorSetting::OnSettingModified)
	ON_EN_CHANGE(IDC_EDIT_TEXT_FONT_SIZE, &COptionsPageEditorSetting::OnSettingModified)
	ON_EN_CHANGE(IDC_EDIT_LINE_NUMBER_FONT_SIZE, &COptionsPageEditorSetting::OnSettingModified)
	ON_EN_CHANGE(IDC_EDIT_INTERVAL_AUTO_SAVE, &COptionsPageEditorSetting::OnSettingModified)
END_MESSAGE_MAP()

void COptionsPageEditorSetting::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_EDITOR_COLOR_THEME, m_ComboEditorColorTheme);
	DDX_Check(pDX, IDC_CHECK_ENABLE_BOLD_FONT, m_bEnableBoldFont);
	DDX_Check(pDX, IDC_CHECK_ENABLE_URL_HIGHLIGHT, m_bEnableUrlLinkHighlight);
	DDX_Control(pDX, IDC_EDIT_TEXT_FONT_SIZE, m_TextFontSizeEdit);
	DDX_Control(pDX, IDC_EDIT_LINE_NUMBER_FONT_SIZE, m_LineNumberFontSizeEdit);
	DDX_Check(pDX, IDC_CHECK_ENABLE_AUTO_SAVE_FILE, m_bEnableAutoSaveFile);
	DDX_Check(pDX, IDC_CHECK_AUTO_SAVE_DOCUMENT_WHEN_BUILD, m_bEnableSaveDocumentWhenBuild);
	DDX_Check(pDX, IDC_CHECK_DISPLAY_WARNING_NOT_EXIST_FILE, m_bDisplayWarningFileNotExist);
	DDX_Control(pDX, IDC_EDIT_INTERVAL_AUTO_SAVE, m_AutoSaveIntervalTime);
	DDX_Text(pDX, IDC_EDIT_TEXT_FONT_SIZE, m_strTextFontSize);
	DDX_Text(pDX, IDC_EDIT_LINE_NUMBER_FONT_SIZE, m_strLineNumberFontSize);
	DDX_Text(pDX, IDC_EDIT_INTERVAL_AUTO_SAVE, m_strAutoSaveIntervalTime);
	DDX_Control(pDX, IDC_RADIO_WINDOW_CMD_RUN_MODE, m_CreateNewCMDWindowRadio);
	DDX_Control(pDX, IDC_RADIO_WINDOW_BUILD_MODE, m_UseBuildWindowRadio);
}

BOOL COptionsPageEditorSetting::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	InitSettings();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void COptionsPageEditorSetting::OnOK()
{
	UpdateSettings();
}

BOOL COptionsPageEditorSetting::OnApply()
{
	UpdateSettings();
	return TRUE;
}

void COptionsPageEditorSetting::OnSettingModified()
{
	SetModified(TRUE);
}

void COptionsPageEditorSetting::InitSettings()
{
	m_ComboEditorColorTheme.ResetContent();
	m_ComboEditorColorTheme.InsertString(0, _T("Blue Color Theme"));
	m_ComboEditorColorTheme.InsertString(1, _T("Gray Color Theme"));
	m_ComboEditorColorTheme.SetCurSel(AppSettingMgr.m_ThemeColor);

	m_bEnableBoldFont = AppSettingMgr.m_EditorFontSetting._bEnableBoldFont;
	m_bEnableUrlLinkHighlight = AppSettingMgr.m_bEnableUrlHighlight;
	m_bEnableAutoSaveFile = AppSettingMgr.m_bAutoSaveDocument;
	m_bEnableSaveDocumentWhenBuild = AppSettingMgr.m_bAutoSaveDocumentWhenbuild;
	m_bDisplayWarningFileNotExist = AppSettingMgr.m_bWarningForFileNotExist;
	m_strTextFontSize = AppUtils::IntToCString(AppSettingMgr.m_EditorFontSetting._nEditorTextFontSize);
	m_strLineNumberFontSize = AppUtils::IntToCString(AppSettingMgr.m_EditorFontSetting._nEditorLineNumberFontSize);
	m_strAutoSaveIntervalTime = AppUtils::IntToCString(AppSettingMgr.m_nIntervalMinutes);

	if (AppSettingMgr.m_bOpenWindowCmdWhenRunProgram)
	{
		m_CreateNewCMDWindowRadio.SetCheck(1);
		m_UseBuildWindowRadio.SetCheck(0);
	}
	else
	{
		m_CreateNewCMDWindowRadio.SetCheck(0);
		m_UseBuildWindowRadio.SetCheck(1);
	}
}

void COptionsPageEditorSetting::UpdateSettings()
{
	UpdateData(TRUE);

	int nCurSel = m_ComboEditorColorTheme.GetCurSel();
	if (nCurSel == 0)
	{
		AppSettingMgr.m_ThemeColor = EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_BLUE;
	}
	else if (nCurSel == 1)
	{
		AppSettingMgr.m_ThemeColor = EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_GRAY;
	}

	AppSettingMgr.m_EditorFontSetting._bEnableBoldFont = m_bEnableBoldFont;
	AppSettingMgr.m_bEnableUrlHighlight = m_bEnableUrlLinkHighlight;
	AppSettingMgr.m_bAutoSaveDocument = m_bEnableAutoSaveFile;
	AppSettingMgr.m_bAutoSaveDocumentWhenbuild = m_bEnableSaveDocumentWhenBuild;
	AppSettingMgr.m_bWarningForFileNotExist = m_bDisplayWarningFileNotExist;
	AppSettingMgr.m_EditorFontSetting._nEditorTextFontSize = AppUtils::CStringToInt(m_strTextFontSize);
	AppSettingMgr.m_EditorFontSetting._nEditorLineNumberFontSize = AppUtils::CStringToInt(m_strLineNumberFontSize);
	AppSettingMgr.m_nIntervalMinutes = AppUtils::CStringToInt(m_strAutoSaveIntervalTime);

	int nCheck = m_CreateNewCMDWindowRadio.GetCheck();
	if (nCheck == 1)
	{
		AppSettingMgr.m_bOpenWindowCmdWhenRunProgram = TRUE;
	}
	else
	{
		AppSettingMgr.m_bOpenWindowCmdWhenRunProgram = FALSE;
	}

	//now update all settings...
	UpdateAppSettings();
}

/////////////////////////////////////////////////////////////////////////////
// COptionsPageFileSetting property page

IMPLEMENT_DYNCREATE(COptionsPageFileSetting, CMFCPropertyPage)

COptionsPageFileSetting::COptionsPageFileSetting() : CMFCPropertyPage(COptionsPageFileSetting::IDD)
, m_bRevealExplorerWindowWhenSwitchFile(FALSE)
, m_bDetectFileChangeFromOutSide(FALSE)
, m_bAllowOpenFileHasErrorBuild(FALSE)
, m_bEnableHighlightFolderTracker(FALSE)
, m_bDrawFoldingLine(FALSE)
{
}

COptionsPageFileSetting::~COptionsPageFileSetting()
{
}

BEGIN_MESSAGE_MAP(COptionsPageFileSetting, CMFCPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_REVEAL_EXPLORER_WINDOW_WHEN_SWITCH_FILE, &COptionsPageFileSetting::OnSettingModified)
	ON_BN_CLICKED(IDC_CHECK_DETECT_FILE_CHANGE, &COptionsPageFileSetting::OnSettingModified)
	ON_BN_CLICKED(IDC_CHECK_ALLOW_OPEN_FILE_HAS_BUILD_ERROR, &COptionsPageFileSetting::OnSettingModified)
	ON_BN_CLICKED(IDC_CHECK_UPDATE_BRACKET_TREE_WHEN_SAVING, &COptionsPageFileSetting::OnSettingModified)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_HIGHLIGHT_FOLDER_TRACKER, &COptionsPageFileSetting::OnSettingModified)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_DRAW_FOLDING_LINE, &COptionsPageFileSetting::OnSettingModified)
	ON_CBN_SELCHANGE(IDC_COMBO_EDITOR_FOLDING_STYLE, &COptionsPageFileSetting::OnSettingModified)
END_MESSAGE_MAP()

void COptionsPageFileSetting::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_REVEAL_EXPLORER_WINDOW_WHEN_SWITCH_FILE, m_bRevealExplorerWindowWhenSwitchFile);
	DDX_Check(pDX, IDC_CHECK_DETECT_FILE_CHANGE, m_bDetectFileChangeFromOutSide);
	DDX_Check(pDX, IDC_CHECK_ALLOW_OPEN_FILE_HAS_BUILD_ERROR, m_bAllowOpenFileHasErrorBuild);
	DDX_Check(pDX, IDC_CHECK_ENABLE_HIGHLIGHT_FOLDER_TRACKER, m_bEnableHighlightFolderTracker);
	DDX_Check(pDX, IDC_CHECK_ENABLE_DRAW_FOLDING_LINE, m_bDrawFoldingLine);
	DDX_Control(pDX, IDC_COMBO_EDITOR_FOLDING_STYLE, m_ComboEditorFoldingStyle);
}

BOOL COptionsPageFileSetting::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	InitSettings();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void COptionsPageFileSetting::OnOK()
{
	UpdateSettings();
}

BOOL COptionsPageFileSetting::OnApply()
{
	UpdateSettings();
	return TRUE;
}

void COptionsPageFileSetting::OnSettingModified()
{
	SetModified(TRUE);
}

void COptionsPageFileSetting::InitSettings()
{
	m_ComboEditorFoldingStyle.ResetContent();
	m_ComboEditorFoldingStyle.InsertString(0, _T("Style Arrow"));
	m_ComboEditorFoldingStyle.InsertString(1, _T("Style Plus Minus"));
	m_ComboEditorFoldingStyle.InsertString(2, _T("Style Tree Circle"));
	m_ComboEditorFoldingStyle.InsertString(3, _T("Style Tree Box"));
	m_ComboEditorFoldingStyle.SetCurSel(AppSettingMgr.m_FolderMarginStyle);

	m_bRevealExplorerWindowWhenSwitchFile = AppSettingMgr.m_bRevealExplorerWhenSwitchFile;
	m_bDetectFileChangeFromOutSide = AppSettingMgr.m_bDetectFileChangeFromOutSide;
	m_bAllowOpenFileHasErrorBuild = AppSettingMgr.m_bAllowOpenFileHasErrorBuild;
	m_bEnableHighlightFolderTracker = AppSettingMgr.m_bEnableHightLightFolder;
	m_bDrawFoldingLine = AppSettingMgr.m_bDrawFoldingLineUnderLineStyle;
}

void COptionsPageFileSetting::UpdateSettings()
{
	UpdateData(TRUE);

	int nCurSel = m_ComboEditorFoldingStyle.GetCurSel();
	if (nCurSel == 0)
	{
		AppSettingMgr.m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_ARROW;
	}
	else if (nCurSel == 1)
	{
		AppSettingMgr.m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_PLUS_MINUS;
	}
	else if (nCurSel == 2)
	{
		AppSettingMgr.m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_TREE_CIRCLE;
	}
	else if (nCurSel == 3)
	{
		AppSettingMgr.m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_TREE_BOX;
	}

	AppSettingMgr.m_bRevealExplorerWhenSwitchFile = m_bRevealExplorerWindowWhenSwitchFile;
	AppSettingMgr.m_bDetectFileChangeFromOutSide = m_bDetectFileChangeFromOutSide;
	AppSettingMgr.m_bAllowOpenFileHasErrorBuild = m_bAllowOpenFileHasErrorBuild;
	AppSettingMgr.m_bEnableHightLightFolder = m_bEnableHighlightFolderTracker;
	AppSettingMgr.m_bDrawFoldingLineUnderLineStyle = m_bDrawFoldingLine;

	// now update all settings...
	UpdateAppSettings();
}

/////////////////////////////////////////////////////////////////////////////
// COptionsPageBuildDebugSetting property page

IMPLEMENT_DYNCREATE(COptionsPageBuildDebugSetting, CMFCPropertyPage)

COptionsPageBuildDebugSetting::COptionsPageBuildDebugSetting() : CMFCPropertyPage(COptionsPageBuildDebugSetting::IDD)
{
}

COptionsPageBuildDebugSetting::~COptionsPageBuildDebugSetting()
{
}

void COptionsPageBuildDebugSetting::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COptionsPageBuildDebugSetting, CMFCPropertyPage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsPageGeneralSetting1 property page

IMPLEMENT_DYNCREATE(COptionsPageGeneralSetting1, CMFCPropertyPage)

COptionsPageGeneralSetting1::COptionsPageGeneralSetting1() : CMFCPropertyPage(COptionsPageGeneralSetting1::IDD)
{
}

COptionsPageGeneralSetting1::~COptionsPageGeneralSetting1()
{
}

void COptionsPageGeneralSetting1::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COptionsPageGeneralSetting1, CMFCPropertyPage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsPageGeneralSetting1 property page

IMPLEMENT_DYNCREATE(COptionsPageGeneralSetting2, CMFCPropertyPage)

COptionsPageGeneralSetting2::COptionsPageGeneralSetting2() : CMFCPropertyPage(COptionsPageGeneralSetting2::IDD)
{
}

COptionsPageGeneralSetting2::~COptionsPageGeneralSetting2()
{
}

void COptionsPageGeneralSetting2::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COptionsPageGeneralSetting2, CMFCPropertyPage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsPagePathSetting property page

IMPLEMENT_DYNCREATE(COptionsPagePathSetting, CMFCPropertyPage)

COptionsPagePathSetting::COptionsPagePathSetting() : CMFCPropertyPage(COptionsPagePathSetting::IDD)
{
}

COptionsPagePathSetting::~COptionsPagePathSetting()
{
}

void COptionsPagePathSetting::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COptionsPagePathSetting, CMFCPropertyPage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsPageTranslateSetting property page

IMPLEMENT_DYNCREATE(COptionsPageTranslateSetting, CMFCPropertyPage)

COptionsPageTranslateSetting::COptionsPageTranslateSetting() : CMFCPropertyPage(COptionsPageTranslateSetting::IDD)
{
}

COptionsPageTranslateSetting::~COptionsPageTranslateSetting()
{
}

void COptionsPageTranslateSetting::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COptionsPageTranslateSetting, CMFCPropertyPage)
END_MESSAGE_MAP()

