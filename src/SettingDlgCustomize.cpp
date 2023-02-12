/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "SettingDlgCustomize.h"
#include "afxdialogex.h"
#include "AppSettings.h"
#include "AppUtil.h"

// SettingDlgCustomize dialog

IMPLEMENT_DYNAMIC(SettingDlgCustomize, CDialogEx)

SettingDlgCustomize::SettingDlgCustomize(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SETTING_CUSTOMIZE, pParent)
	, m_nDialogFontHeight(0)
	, m_nDockWindowFontHeight(0)
	, m_nEditorLineNumberFontSize(0)
	, m_nEditorTextFontSize(0)
	, m_nPageAlignmentWidth(0)
{
}

SettingDlgCustomize::~SettingDlgCustomize()
{
}

void SettingDlgCustomize::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_ACTIVE_TAB_COLOR_COMBO, m_ActiveTabColorCombo);
	DDX_Control(pDX, ID_CARET_BLINK_COLOR_COMBO, m_CaretBlinkColorCombo);
	DDX_Text(pDX, ID_DIALOG_FONT_HEIGHT_EDIT, m_nDialogFontHeight);
	DDX_Text(pDX, ID_DOCK_WINDOW_FONT_HEIGHT_EDIT, m_nDockWindowFontHeight);
	DDX_Text(pDX, ID_EDITOR_LINE_NUMBER_FONT_SIZE_EDIT, m_nEditorLineNumberFontSize);
	DDX_Text(pDX, ID_EDITOR_TEXT_FONT_SIZE_EDIT, m_nEditorTextFontSize);
	DDX_Control(pDX, ID_FOLDER_MARGIN_STYLE_COMBO, m_FolderMarginStyleCombo);
	DDX_Control(pDX, ID_INDICATOR_COLOR_COMBO, m_IndicatorColorCombo);
	DDX_Control(pDX, ID_INDICATOR_STYLE_COMBO, m_IndicatorStyleCombo);
	DDX_Control(pDX, ID_THEME_COLOR_COMBO, m_ThemeColorCombo);
	DDX_Text(pDX, ID_PAGE_ALIGNMENT_WIDTH_EDIT, m_nPageAlignmentWidth);
	DDX_Control(pDX, ID_RENDER_INDICATOR_ACTION_COMBO, m_RenderIndicatorActionCombo);
	DDX_Control(pDX, ID_DIALOG_COMBOBOX_LIMIT_SAVE_COMBO, m_DialogComboboxLimitSaveCombo);
	DDX_Control(pDX, ID_DIALOG_FONT_WEIGHT_COMBO, m_DialogWindowFontWeightCombo);
	DDX_Control(pDX, ID_DOCK_WINDOW_FONT_WEIGHT_COMBO, m_DockWindowFontWeightCombo);
	DDX_Control(pDX, ID_THEME_LOOK_COMBO, m_ApplicationThemLookCombo);
}

BOOL SettingDlgCustomize::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UpdateGUISettings(FALSE);

	UpdateData(FALSE);

	return TRUE;
}

BOOL SettingDlgCustomize::PreTranslateMessage(MSG * pMsg)
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

void SettingDlgCustomize::InitActiveTabColorCombobox()
{
	m_ActiveTabColorCombo.ResetContent();
	m_ActiveTabColorCombo.AddString(_T("Gray Color"));
	m_ActiveTabColorCombo.AddString(_T("Orrange Color"));
	m_ActiveTabColorCombo.AddString(_T("Green Color"));
	m_ActiveTabColorCombo.AddString(_T("Yellow Color"));
	switch (AppSettingMgr.m_ActiveTabColor)
	{
	case EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_GRAY:
		m_ActiveTabColorCombo.SetCurSel(0);
		break;
	case EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_ORRANGE:
		m_ActiveTabColorCombo.SetCurSel(1);
		break;
	case EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_GREEN:
		m_ActiveTabColorCombo.SetCurSel(2);
		break;
	case EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_YELLOW:
		m_ActiveTabColorCombo.SetCurSel(3);
		break;
	default:
		m_ActiveTabColorCombo.SetCurSel(0);
		break;
	}
}

void SettingDlgCustomize::InitCaretBlinkColorCombobox()
{
	m_CaretBlinkColorCombo.ResetContent();
	m_CaretBlinkColorCombo.AddString(_T("Write Color"));
	m_CaretBlinkColorCombo.AddString(_T("Orrange Color"));
	m_CaretBlinkColorCombo.AddString(_T("Green Color"));
	m_CaretBlinkColorCombo.AddString(_T("Yellow Color"));
	m_CaretBlinkColorCombo.AddString(_T("Red Color"));
	m_CaretBlinkColorCombo.AddString(_T("Black Color"));
	switch (AppSettingMgr.m_CaretBlinkColor)
	{
	case EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_WHITE:
		m_CaretBlinkColorCombo.SetCurSel(0);
		break;
	case EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_ORRANGE:
		m_CaretBlinkColorCombo.SetCurSel(1);
		break;
	case EDITOR_CARET_BLINK_COLOR::BLINK_COLORR_GREEN:
		m_CaretBlinkColorCombo.SetCurSel(2);
		break;
	case EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_YELLOW:
		m_CaretBlinkColorCombo.SetCurSel(3);
		break;
	case EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_RED:
		m_CaretBlinkColorCombo.SetCurSel(4);
		break;
	case EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_BLACK:
		m_CaretBlinkColorCombo.SetCurSel(5);
		break;
	default:
		m_CaretBlinkColorCombo.SetCurSel(0);
		break;
	}
}

void SettingDlgCustomize::InitFolderMarginStyleCombobox()
{
	m_FolderMarginStyleCombo.ResetContent();
	m_FolderMarginStyleCombo.AddString(_T("Arrow Style"));
	m_FolderMarginStyleCombo.AddString(_T("Plus Minus Style"));
	m_FolderMarginStyleCombo.AddString(_T("Tree Circle Styler"));
	m_FolderMarginStyleCombo.AddString(_T("Tree Box Style"));
	switch (AppSettingMgr.m_FolderMarginStyle)
	{
	case FOLDER_MARGIN_STYPE::STYLE_ARROW:
		m_FolderMarginStyleCombo.SetCurSel(0);
		break;
	case FOLDER_MARGIN_STYPE::STYLE_PLUS_MINUS:
		m_FolderMarginStyleCombo.SetCurSel(1);
		break;
	case FOLDER_MARGIN_STYPE::STYLE_TREE_CIRCLE:
		m_FolderMarginStyleCombo.SetCurSel(2);
		break;
	case FOLDER_MARGIN_STYPE::STYLE_TREE_BOX:
		m_FolderMarginStyleCombo.SetCurSel(3);
		break;
	default:
		m_FolderMarginStyleCombo.SetCurSel(0);
		break;
	}
}

void SettingDlgCustomize::InitIndicatorColorCombobox()
{
	m_IndicatorColorCombo.ResetContent();
	m_IndicatorColorCombo.AddString(_T("Yellow Color"));
	m_IndicatorColorCombo.AddString(_T("Write Color"));
	m_IndicatorColorCombo.AddString(_T("Black Color"));
	switch (AppSettingMgr.m_IndicatorColor)
	{
	case EDITOR_INDICATOR_COLOR::INDICATOR_YELLOW:
		m_IndicatorColorCombo.SetCurSel(0);
		break;
	case EDITOR_INDICATOR_COLOR::INDICATOR_WHITE:
		m_IndicatorColorCombo.SetCurSel(1);
		break;
	case EDITOR_INDICATOR_COLOR::INDICATOR_BLACK:
		m_IndicatorColorCombo.SetCurSel(2);
		break;
	default:
		m_IndicatorColorCombo.SetCurSel(0);
		break;
	}
}

void SettingDlgCustomize::InitIndicatorStyleCombobox()
{
	m_IndicatorStyleCombo.ResetContent();
	m_IndicatorStyleCombo.AddString(_T("Box Style"));
	m_IndicatorStyleCombo.AddString(_T("Full Box Style"));
	switch (AppSettingMgr.m_IndicatorStyle)
	{
	case EDITOR_INDICATOR_STYLE::BOX:
		m_IndicatorStyleCombo.SetCurSel(0);
		break;
	case EDITOR_INDICATOR_STYLE::FULL_BOX:
		m_IndicatorStyleCombo.SetCurSel(1);
		break;
	default:
		m_IndicatorStyleCombo.SetCurSel(0);
		break;
	}
}

void SettingDlgCustomize::InitThemeColorCombobox()
{
	m_ThemeColorCombo.ResetContent();
	m_ThemeColorCombo.AddString(_T("Sierra Blue Theme"));
	m_ThemeColorCombo.AddString(_T("Monokai Theme"));
	m_ThemeColorCombo.AddString(_T("Lighting Theme"));
	switch (AppSettingMgr.m_ThemeColor)
	{
	case EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_SIERRA_BLUE:
		m_ThemeColorCombo.SetCurSel(0);
		break;
	case EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_MONOKAI:
		m_ThemeColorCombo.SetCurSel(1);
		break;
	case EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_LIGHT:
		m_ThemeColorCombo.SetCurSel(2);
		break;
	default:
		m_ThemeColorCombo.SetCurSel(0);
		break;
	}
}

void SettingDlgCustomize::InitRenderIndicatorActionCombobox()
{
	m_RenderIndicatorActionCombo.ResetContent();
	m_RenderIndicatorActionCombo.AddString(_T("Single Click Event"));
	m_RenderIndicatorActionCombo.AddString(_T("Double Click Event"));
	switch (AppSettingMgr.m_RenderIndicatorAction)
	{
	case RENDER_INDICATOR_ACTION::SINGLE_CLICK_ACTION:
		m_RenderIndicatorActionCombo.SetCurSel(0);
		break;
	case RENDER_INDICATOR_ACTION::DOUBLE_CLICK_ACTION:
		m_RenderIndicatorActionCombo.SetCurSel(1);
		break;
	default:
		m_RenderIndicatorActionCombo.SetCurSel(0);
		break;
	}
}

void SettingDlgCustomize::InitDialogComboboxLimitSaveCombobox()
{
	m_DialogComboboxLimitSaveCombo.ResetContent();
	m_DialogComboboxLimitSaveCombo.AddString(_T("10"));
	m_DialogComboboxLimitSaveCombo.AddString(_T("20"));
	m_DialogComboboxLimitSaveCombo.AddString(_T("30"));
	m_DialogComboboxLimitSaveCombo.AddString(_T("40"));
	switch (AppSettingMgr.m_nDialogComboboxLimitSave)
	{
	case 10:
		m_DialogComboboxLimitSaveCombo.SetCurSel(0);
		break;
	case 20:
		m_DialogComboboxLimitSaveCombo.SetCurSel(1);
		break;
	case 30:
		m_DialogComboboxLimitSaveCombo.SetCurSel(2);
		break;
	case 40:
		m_DialogComboboxLimitSaveCombo.SetCurSel(3);
		break;
	default:
		m_DialogComboboxLimitSaveCombo.SetCurSel(0);
		break;
	}
}

void SettingDlgCustomize::InitDockWindowFontWeightCombobox()
{
	m_DockWindowFontWeightCombo.ResetContent();
	m_DockWindowFontWeightCombo.AddString(_T("Normal"));
	m_DockWindowFontWeightCombo.AddString(_T("Medium"));
	m_DockWindowFontWeightCombo.AddString(_T("Semi-Bold"));
	m_DockWindowFontWeightCombo.AddString(_T("Bold"));
	switch (AppSettingMgr.m_DockWindowFontSetting._lfWeight)
	{
	case FW_NORMAL:
		m_DockWindowFontWeightCombo.SetCurSel(0);
		break;
	case FW_MEDIUM:
		m_DockWindowFontWeightCombo.SetCurSel(1);
		break;
	case FW_SEMIBOLD:
		m_DockWindowFontWeightCombo.SetCurSel(2);
		break;
	case FW_BOLD:
		m_DockWindowFontWeightCombo.SetCurSel(3);
		break;
	default:
		m_DockWindowFontWeightCombo.SetCurSel(0);
		break;
	}
}

void SettingDlgCustomize::InitDialogWindowFontWeightCombobox()
{
	m_DialogWindowFontWeightCombo.ResetContent();
	m_DialogWindowFontWeightCombo.AddString(_T("Normal"));
	m_DialogWindowFontWeightCombo.AddString(_T("Medium"));
	m_DialogWindowFontWeightCombo.AddString(_T("Semi-Bold"));
	m_DialogWindowFontWeightCombo.AddString(_T("Bold"));
	switch (AppSettingMgr.m_DockWindowFontSetting._lfWeight)
	{
	case FW_NORMAL:
		m_DialogWindowFontWeightCombo.SetCurSel(0);
		break;
	case FW_MEDIUM:
		m_DialogWindowFontWeightCombo.SetCurSel(1);
		break;
	case FW_SEMIBOLD:
		m_DialogWindowFontWeightCombo.SetCurSel(2);
		break;
	case FW_BOLD:
		m_DialogWindowFontWeightCombo.SetCurSel(3);
		break;
	default:
		m_DialogWindowFontWeightCombo.SetCurSel(0);
		break;
	}
}

void SettingDlgCustomize::InitApplicationThemLookCombobox()
{
	m_ApplicationThemLookCombo.ResetContent();
	m_ApplicationThemLookCombo.AddString(_T("Office 2003 Look"));
	m_ApplicationThemLookCombo.AddString(_T("Visual Studio 2005 Look"));
	m_ApplicationThemLookCombo.AddString(_T("Windows XP Native Look"));
	m_ApplicationThemLookCombo.AddString(_T("Office 2007 Aqua Look"));
	m_ApplicationThemLookCombo.AddString(_T("Office 2007 Obsidian Black Look"));
	m_ApplicationThemLookCombo.AddString(_T("Office 2007 Silver Look"));
	m_ApplicationThemLookCombo.AddString(_T("Office 2007 Luna Blue Look"));
	m_ApplicationThemLookCombo.AddString(_T("Visual Studio 2008 Look"));
	switch (AppSettingMgr.m_ApplicationThemeLook)
	{
	case APPLICATION_THEME_LOOK::THEME_OFFICE_2003:
		m_ApplicationThemLookCombo.SetCurSel(0);
		break;
	case APPLICATION_THEME_LOOK::THEME_VISUAL_STUDIO_2005:
		m_ApplicationThemLookCombo.SetCurSel(1);
		break;
	case APPLICATION_THEME_LOOK::THEME_WINDOWS_XP_NATIVE:
		m_ApplicationThemLookCombo.SetCurSel(2);
		break;
	case APPLICATION_THEME_LOOK::THEME_OFFICE_2007_AQUA:
		m_ApplicationThemLookCombo.SetCurSel(3);
		break;
	case APPLICATION_THEME_LOOK::THEME_OFFICE_2007_LUNA_BLUE:
		m_ApplicationThemLookCombo.SetCurSel(4);
		break;
	case APPLICATION_THEME_LOOK::THEME_OFFICE_2007_OBSIDIAN_BLACK:
		m_ApplicationThemLookCombo.SetCurSel(5);
		break;
	case APPLICATION_THEME_LOOK::THEME_OFFICE_2007_SILVER_LOOK:
		m_ApplicationThemLookCombo.SetCurSel(6);
		break;
	case APPLICATION_THEME_LOOK::THEME_VISUAL_STUDIO_2008_LOOK:
		m_ApplicationThemLookCombo.SetCurSel(7);
		break;
	default:
		m_ApplicationThemLookCombo.SetCurSel(0);
		break;
	}
}

void SettingDlgCustomize::FromActiveTabColorCombobox()
{
	int iSel = m_ActiveTabColorCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_ActiveTabColor = EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_GRAY;
		break;
	case 1:
		AppSettingMgr.m_ActiveTabColor = EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_ORRANGE;
		break;
	case 2:
		AppSettingMgr.m_ActiveTabColor = EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_GREEN;
		break;
	case 3:
		AppSettingMgr.m_ActiveTabColor = EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_YELLOW;
		break;
	default:
		AppSettingMgr.m_ActiveTabColor = EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_GRAY;
		break;
	}
}

void SettingDlgCustomize::FromCaretBlinkColorCombobox()
{
	int iSel = m_CaretBlinkColorCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_WHITE;
		break;
	case 1:
		AppSettingMgr.m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_ORRANGE;
		break;
	case 2:
		AppSettingMgr.m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLORR_GREEN;
		break;
	case 3:
		AppSettingMgr.m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_YELLOW;
		break;
	case 4:
		AppSettingMgr.m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_RED;
		break;
	case 5:
		AppSettingMgr.m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_BLACK;
		break;
	default:
		AppSettingMgr.m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_WHITE;
		break;
	}
}

void SettingDlgCustomize::FromFolderMarginStyleCombobox()
{
	int iSel = m_FolderMarginStyleCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_ARROW;
		break;
	case 1:
		AppSettingMgr.m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_PLUS_MINUS;
		break;
	case 2:
		AppSettingMgr.m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_TREE_CIRCLE;
		break;
	case 3:
		AppSettingMgr.m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_TREE_BOX;
		break;
	default:
		AppSettingMgr.m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_ARROW;
		break;
	}
}

void SettingDlgCustomize::FromIndicatorColorCombobox()
{
	int iSel = m_IndicatorColorCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_IndicatorColor = EDITOR_INDICATOR_COLOR::INDICATOR_YELLOW;
		break;
	case 1:
		AppSettingMgr.m_IndicatorColor = EDITOR_INDICATOR_COLOR::INDICATOR_WHITE;
		break;
	case 2:
		AppSettingMgr.m_IndicatorColor = EDITOR_INDICATOR_COLOR::INDICATOR_BLACK;
		break;
	default:
		AppSettingMgr.m_IndicatorColor = EDITOR_INDICATOR_COLOR::INDICATOR_YELLOW;
		break;
	}
}

void SettingDlgCustomize::FromIndicatorStyleCombobox()
{
	int iSel = m_IndicatorStyleCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_IndicatorStyle = EDITOR_INDICATOR_STYLE::BOX;
		break;
	case 1:
		AppSettingMgr.m_IndicatorStyle = EDITOR_INDICATOR_STYLE::FULL_BOX;
		break;
	default:
		AppSettingMgr.m_IndicatorStyle = EDITOR_INDICATOR_STYLE::BOX;
		break;
	}
}

void SettingDlgCustomize::FromThemeColorCombobox()
{
	int iSel = m_ThemeColorCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_ThemeColor = EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_SIERRA_BLUE;
		break;
	case 1:
		AppSettingMgr.m_ThemeColor = EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_MONOKAI;
		break;
	case 2:
		AppSettingMgr.m_ThemeColor = EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_LIGHT;
		break;
	default:
		AppSettingMgr.m_ThemeColor = EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_SIERRA_BLUE;
		break;
	}
}

void SettingDlgCustomize::FromRenderIndicatorActionCombobox()
{
	int iSel = m_RenderIndicatorActionCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_RenderIndicatorAction = RENDER_INDICATOR_ACTION::SINGLE_CLICK_ACTION;
		break;
	case 1:
		AppSettingMgr.m_RenderIndicatorAction = RENDER_INDICATOR_ACTION::DOUBLE_CLICK_ACTION;
		break;
	default:
		AppSettingMgr.m_RenderIndicatorAction = RENDER_INDICATOR_ACTION::SINGLE_CLICK_ACTION;
		break;
	}
}

void SettingDlgCustomize::FromDialogComboboxLimitSaveCombobox()
{
	int iSel = m_DialogComboboxLimitSaveCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_nDialogComboboxLimitSave = 10;
		break;
	case 1:
		AppSettingMgr.m_nDialogComboboxLimitSave = 20;
		break;
	case 2:
		AppSettingMgr.m_nDialogComboboxLimitSave = 30;
		break;
	case 3:
		AppSettingMgr.m_nDialogComboboxLimitSave = 40;
		break;
	default:
		AppSettingMgr.m_nDialogComboboxLimitSave = 10;
		break;
	}
}

void SettingDlgCustomize::FromDockWindowFontWeightCombobox()
{
	int iSel = m_DockWindowFontWeightCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_DockWindowFontSetting._lfWeight = FW_NORMAL;
		break;
	case 1:
		AppSettingMgr.m_DockWindowFontSetting._lfWeight = FW_MEDIUM;
		break;
	case 2:
		AppSettingMgr.m_DockWindowFontSetting._lfWeight = FW_SEMIBOLD;
		break;
	case 3:
		AppSettingMgr.m_DockWindowFontSetting._lfWeight = FW_BOLD;
		break;
	default:
		AppSettingMgr.m_DockWindowFontSetting._lfWeight = 10;
		break;
	}
}

void SettingDlgCustomize::FromDialogWindowFontWeightCombobox()
{
	int iSel = m_DialogComboboxLimitSaveCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_DialogFontSetting._lfWeight = FW_NORMAL;
		break;
	case 1:
		AppSettingMgr.m_DialogFontSetting._lfWeight = FW_MEDIUM;
		break;
	case 2:
		AppSettingMgr.m_DialogFontSetting._lfWeight = FW_SEMIBOLD;
		break;
	case 3:
		AppSettingMgr.m_DialogFontSetting._lfWeight = FW_BOLD;
		break;
	default:
		AppSettingMgr.m_DialogFontSetting._lfWeight = 10;
		break;
	}
}

void SettingDlgCustomize::FromApplicationThemLookCombobox()
{
	int iSel = m_ApplicationThemLookCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_OFFICE_2003;
		break;
	case 1:
		AppSettingMgr.m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_VISUAL_STUDIO_2005;
		break;
	case 2:
		AppSettingMgr.m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_WINDOWS_XP_NATIVE;
		break;
	case 3:
		AppSettingMgr.m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_OFFICE_2007_AQUA;
		break;
	case 4:
		AppSettingMgr.m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_OFFICE_2007_OBSIDIAN_BLACK;
		break;
	case 5:
		AppSettingMgr.m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_OFFICE_2007_SILVER_LOOK;
		break;
	case 6:
		AppSettingMgr.m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_OFFICE_2007_LUNA_BLUE;
		break;
	case 7:
		AppSettingMgr.m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_VISUAL_STUDIO_2008_LOOK;
		break;
	default:
		AppSettingMgr.m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_OFFICE_2003;
		break;
	}
}

void SettingDlgCustomize::UpdateGUISettings(BOOL bFromGUI)
{
	if (bFromGUI)
	{
		UpdateData(TRUE);

		FromActiveTabColorCombobox();
		FromCaretBlinkColorCombobox();
		FromFolderMarginStyleCombobox();
		FromIndicatorColorCombobox();
		FromIndicatorColorCombobox();
		FromIndicatorStyleCombobox();
		FromThemeColorCombobox();
		FromRenderIndicatorActionCombobox();
		FromDialogComboboxLimitSaveCombobox();
		FromDockWindowFontWeightCombobox();
		FromDialogWindowFontWeightCombobox();
		FromApplicationThemLookCombobox();

		AppSettingMgr.m_DialogFontSetting._lfHeight = m_nDialogFontHeight;
		AppSettingMgr.m_DockWindowFontSetting._lfHeight = m_nDockWindowFontHeight;
		AppSettingMgr.m_EditorFontSetting._nEditorLineNumberFontSize = m_nEditorLineNumberFontSize;
		AppSettingMgr.m_EditorFontSetting._nEditorTextFontSize = m_nEditorTextFontSize;
		AppSettingMgr.m_nPageAlignmentWidth = m_nPageAlignmentWidth;

		CButton* pButtonDock = (CButton*)GetDlgItem(ID_DOCK_WINDOW_FONT_NAME_BUTTON);
		if (pButtonDock)
		{
			pButtonDock->GetWindowTextW(AppSettingMgr.m_DockWindowFontSetting._font);
		}

		CButton* pButtonEditor = (CButton*)GetDlgItem(ID_EDITOR_FONT_NAME_BUTTON);
		if (pButtonEditor)
		{
			pButtonEditor->GetWindowTextW(AppSettingMgr.m_EditorFontSetting._font);
		}

		CButton* pButtonDlg = (CButton*)GetDlgItem(ID_DIALOG_FONT_NAME_BUTTON);
		if (pButtonDlg)
		{
			pButtonDlg->GetWindowTextW(AppSettingMgr.m_DialogFontSetting._font);
		}
	}
	else
	{
		InitActiveTabColorCombobox();
		InitCaretBlinkColorCombobox();
		InitFolderMarginStyleCombobox();
		InitIndicatorColorCombobox();
		InitIndicatorColorCombobox();
		InitIndicatorStyleCombobox();
		InitThemeColorCombobox();
		InitRenderIndicatorActionCombobox();
		InitDialogComboboxLimitSaveCombobox();
		InitDockWindowFontWeightCombobox();
		InitDialogWindowFontWeightCombobox();
		InitApplicationThemLookCombobox();

		m_nDialogFontHeight = AppSettingMgr.m_DialogFontSetting._lfHeight;
		m_nDockWindowFontHeight = AppSettingMgr.m_DockWindowFontSetting._lfHeight;
		m_nEditorLineNumberFontSize = AppSettingMgr.m_EditorFontSetting._nEditorLineNumberFontSize;
		m_nEditorTextFontSize = AppSettingMgr.m_EditorFontSetting._nEditorTextFontSize;
		m_nPageAlignmentWidth = AppSettingMgr.m_nPageAlignmentWidth;

		CButton* pButtonDock = (CButton*)GetDlgItem(ID_DOCK_WINDOW_FONT_NAME_BUTTON);
		if (pButtonDock)
		{
			pButtonDock->SetWindowTextW(AppSettingMgr.m_DockWindowFontSetting._font);
		}

		CButton* pButtonEditor = (CButton*)GetDlgItem(ID_EDITOR_FONT_NAME_BUTTON);
		if (pButtonEditor)
		{
			pButtonEditor->SetWindowTextW(AppSettingMgr.m_EditorFontSetting._font);
		}

		CButton* pButtonDlg = (CButton*)GetDlgItem(ID_DIALOG_FONT_NAME_BUTTON);
		if (pButtonDlg)
		{
			pButtonDlg->SetWindowTextW(AppSettingMgr.m_DialogFontSetting._font);
		}
	}
}

BEGIN_MESSAGE_MAP(SettingDlgCustomize, CDialogEx)
	ON_BN_CLICKED(ID_DOCK_WINDOW_FONT_NAME_BUTTON, &SettingDlgCustomize::OnBnClickedDockWindowFontNameButton)
	ON_BN_CLICKED(ID_EDITOR_FONT_NAME_BUTTON, &SettingDlgCustomize::OnBnClickedEditorFontNameButton)
	ON_BN_CLICKED(ID_DIALOG_FONT_NAME_BUTTON, &SettingDlgCustomize::OnBnClickedDialogFontNameButton)
END_MESSAGE_MAP()

// SettingDlgCustomize message handlers

void SettingDlgCustomize::OnBnClickedDockWindowFontNameButton()
{
	CFontDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		CButton* pButton = (CButton*)GetDlgItem(ID_DOCK_WINDOW_FONT_NAME_BUTTON);
		if (pButton)
		{
			pButton->SetWindowTextW(dlg.GetFaceName());
		}
	}
}

void SettingDlgCustomize::OnBnClickedEditorFontNameButton()
{
	CFontDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		CButton* pButton = (CButton*)GetDlgItem(ID_EDITOR_FONT_NAME_BUTTON);
		if (pButton)
		{
			pButton->SetWindowTextW(dlg.GetFaceName());
		}
	}
}

void SettingDlgCustomize::OnBnClickedDialogFontNameButton()
{	
	CFontDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		CButton* pButton = (CButton*)GetDlgItem(ID_DIALOG_FONT_NAME_BUTTON);
		if (pButton)
		{
			pButton->SetWindowTextW(dlg.GetFaceName());
		}
	}
}
