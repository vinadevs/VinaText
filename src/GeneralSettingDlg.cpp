/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "resource.h"
#include "afxdialogex.h"
#include "GeneralSettingDlg.h"
#include "AppSettings.h"
#include "AppUtil.h"
#include "PathUtil.h"
#include "ScrollHelper.h"

// GeneralSettingDlg dialog

constexpr int DEFAULT_LFWEIGHT = 10;

IMPLEMENT_DYNAMIC(GeneralSettingDlg, CDialogEx)

GeneralSettingDlg::GeneralSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING_GENERAL, pParent)
{
	m_pScrollHelper = std::make_unique<CScrollHelper>();
	m_pScrollHelper->AttachWnd(this);
	m_pScrollHelper->SetDisplaySize(0, 1500);
}

GeneralSettingDlg::~GeneralSettingDlg() {}

void GeneralSettingDlg::UpdateGUISettings(BOOL bFromGUI)
{
	if (bFromGUI)
	{
		UpdateData(TRUE);

		FromActiveTabColorCombobox();
		FromThemeColorCombobox();
		FromApplicationThemLookCombobox();
		FromDialogComboboxLimitSaveCombobox();

		AppSettingMgr.m_strInitialFilePickerPath = m_strInitialFilePickerPath;
		AppSettingMgr.m_bWarningForFileNotExist = m_bWarningForFileNotExist;
		AppSettingMgr.m_bShowTrackingBar = m_bShowTrackingBar;
		AppSettingMgr.m_bUseInitialFilePickerPath = m_bUseInitialFilePickerPath;
		AppSettingMgr.m_bDisplayMessageBoxForFileChange = m_bDisplayMessageBoxForFileChange;
		AppSettingMgr.m_bUseInstallPathAsAppDataPath = m_bUseInstallPathAsAppDataPath;
		AppSettingMgr.m_bSaveDataBookmarkWindow = m_bSaveDataBookmarkWindow;
		AppSettingMgr.m_bDetectFileChangeFromOutSide = m_bDetectFileChangeFromOutSide;
		AppSettingMgr.m_bCheckFileSizeBeforeOpen = m_bCheckFileSizeBeforeOpen;
		m_nRecentFileLimit > 16 ? AppSettingMgr.m_nRecentFileLimit = 16 : AppSettingMgr.m_nRecentFileLimit = m_nRecentFileLimit;
		m_dPDFPageScrollSpeed > 10 ? AppSettingMgr.m_dPdfViewerWheelScrollFactor = 0.1 : AppSettingMgr.m_dPdfViewerWheelScrollFactor = (m_dPDFPageScrollSpeed / 100);

		AppSettingMgr.m_BinaryFileExtensionList.RemoveAll();
		AppUtils::SplitCString(m_strBinaryFileExtensionList, CSTRING_SPACE, AppSettingMgr.m_BinaryFileExtensionList);
		AppSettingMgr.m_strBinaryFileExtensionList = m_strBinaryFileExtensionList;
	}
	else
	{
		InitActiveTabColorCombobox();
		InitThemeColorCombobox();
		InitApplicationThemLookCombobox();
		InitDialogComboboxLimitSaveCombobox();

		m_strInitialFilePickerPath = AppSettingMgr.m_strInitialFilePickerPath;
		m_bWarningForFileNotExist = AppSettingMgr.m_bWarningForFileNotExist;
		m_bShowTrackingBar = AppSettingMgr.m_bShowTrackingBar;
		m_bUseInitialFilePickerPath = AppSettingMgr.m_bUseInitialFilePickerPath;
		m_bDisplayMessageBoxForFileChange = AppSettingMgr.m_bDisplayMessageBoxForFileChange;
		m_bSaveDataBookmarkWindow = AppSettingMgr.m_bSaveDataBookmarkWindow;
		m_bDetectFileChangeFromOutSide = AppSettingMgr.m_bDetectFileChangeFromOutSide;
		m_bCheckFileSizeBeforeOpen = AppSettingMgr.m_bCheckFileSizeBeforeOpen;
		m_bUseInstallPathAsAppDataPath = AppSettingMgr.m_bUseInstallPathAsAppDataPath;
		m_nRecentFileLimit = AppSettingMgr.m_nRecentFileLimit;
		m_dPDFPageScrollSpeed = AppSettingMgr.m_dPdfViewerWheelScrollFactor * 100;
		m_strBinaryFileExtensionList = AppSettingMgr.m_strBinaryFileExtensionList;

		UpdateData(FALSE);
	}
}

void GeneralSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_ACTIVE_TAB_COLOR_COMBO, m_ActiveTabColorCombo);
	DDX_Control(pDX, ID_THEME_COLOR_COMBO, m_ThemeColorCombo);
	DDX_Control(pDX, ID_THEME_LOOK_COMBO, m_ApplicationThemLookCombo);
	DDX_Control(pDX, ID_INITIAL_FILE_PICKER_PATH_EDIT, m_EditInitialFilePickerPath);
	DDX_Text(pDX, ID_INITIAL_FILE_PICKER_PATH_EDIT, m_strInitialFilePickerPath);
	DDX_Check(pDX, ID_WARNING_FOR_FILE_NOT_EXIST, m_bWarningForFileNotExist);
	DDX_Check(pDX, ID_SHOW_TRACKING_BAR, m_bShowTrackingBar);
	DDX_Check(pDX, ID_ALLOW_USE_INITIAL_FILE_PICKER_PATH, m_bUseInitialFilePickerPath);
	DDX_Check(pDX, ID_SAVE_DATA_BOOKMARK_WINDOW, m_bSaveDataBookmarkWindow);
	DDX_Check(pDX, ID_DETECT_FILE_CHANGE_FROM_OUT_SIDE, m_bDetectFileChangeFromOutSide);
	DDX_Check(pDX, ID_CHECK_FILE_SIZE_BEFORE_OPEN, m_bCheckFileSizeBeforeOpen);
	DDX_Check(pDX, ID_DISPLAY_MESSAGE_BOX_FOR_FILE_CHANGE, m_bDisplayMessageBoxForFileChange);
	DDX_Check(pDX, ID_USE_INSTALL_PATH_AS_APPDATA_PATH, m_bUseInstallPathAsAppDataPath);
	DDX_Control(pDX, ID_DIALOG_COMBOBOX_LIMIT_SAVE_COMBO, m_DialogComboboxLimitSaveCombo);
	DDX_Text(pDX, ID_RECENT_FILE_LIMIT_EDIT, m_nRecentFileLimit);
	DDX_Text(pDX, ID_SETTING_PDF_WHEEL_SCROLL_SPEED, m_dPDFPageScrollSpeed);
	DDX_Text(pDX, ID_BINARY_FILE_EXTENSION_LIST, m_strBinaryFileExtensionList);
}

BOOL GeneralSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_EditInitialFilePickerPath.EnableFolderBrowseButton();

	UpdateGUISettings(FALSE);

	return TRUE;
}

BOOL GeneralSettingDlg::PreTranslateMessage(MSG* pMsg)
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

void GeneralSettingDlg::InitActiveTabColorCombobox()
{
	m_ActiveTabColorCombo.ResetContent();
	m_ActiveTabColorCombo.AddString(_T("Gray Color"));
	m_ActiveTabColorCombo.AddString(_T("Green Color"));
	m_ActiveTabColorCombo.AddString(_T("Yellow Color"));
	switch (AppSettingMgr.m_ActiveTabColor)
	{
	case EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_GRAY:
		m_ActiveTabColorCombo.SetCurSel(0);
		break;
	case EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_GREEN:
		m_ActiveTabColorCombo.SetCurSel(1);
		break;
	case EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_YELLOW:
		m_ActiveTabColorCombo.SetCurSel(2);
		break;
	default:
		m_ActiveTabColorCombo.SetCurSel(0);
		break;
	}
}

void GeneralSettingDlg::FromActiveTabColorCombobox()
{
	int iSel = m_ActiveTabColorCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_ActiveTabColor = EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_GRAY;
		break;
	case 1:
		AppSettingMgr.m_ActiveTabColor = EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_GREEN;
		break;
	case 2:
		AppSettingMgr.m_ActiveTabColor = EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_YELLOW;
		break;
	default:
		AppSettingMgr.m_ActiveTabColor = EDITOR_TAB_ACTIVE_COLOR::MDITAB_ACTIVE_COLOR_GRAY;
		break;
	}
}

void GeneralSettingDlg::InitThemeColorCombobox()
{
	m_ThemeColorCombo.ResetContent();
	m_ThemeColorCombo.AddString(_T("Sierra Blue Color Background"));
	m_ThemeColorCombo.AddString(_T("Monokai Color Background"));
	m_ThemeColorCombo.AddString(_T("Lighting Color Background"));
	switch (AppSettingMgr.m_AppThemeColor)
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

void GeneralSettingDlg::FromThemeColorCombobox()
{
	int iSel = m_ThemeColorCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_AppThemeColor = EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_SIERRA_BLUE;
		break;
	case 1:
		AppSettingMgr.m_AppThemeColor = EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_MONOKAI;
		break;
	case 2:
		AppSettingMgr.m_AppThemeColor = EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_LIGHT;
		break;
	default:
		AppSettingMgr.m_AppThemeColor = EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_SIERRA_BLUE;
		break;
	}
}

void GeneralSettingDlg::InitApplicationThemLookCombobox()
{
	m_ApplicationThemLookCombo.ResetContent();
	m_ApplicationThemLookCombo.AddString(_T("Office Classic GUI"));
	m_ApplicationThemLookCombo.AddString(_T("Visual Classic GUI"));
	m_ApplicationThemLookCombo.AddString(_T("Windows Native Look"));
	m_ApplicationThemLookCombo.AddString(_T("Office Modern Aqua GUI"));
	m_ApplicationThemLookCombo.AddString(_T("Office Modern Luna Blue GUI"));
	m_ApplicationThemLookCombo.AddString(_T("Office Modern Black GUI"));
	m_ApplicationThemLookCombo.AddString(_T("Office Modern Silver GUI"));
	m_ApplicationThemLookCombo.AddString(_T("Visual Modern GUI"));
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

void GeneralSettingDlg::FromApplicationThemLookCombobox()
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
		AppSettingMgr.m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_OFFICE_2007_LUNA_BLUE;
		break;
	case 5:
		AppSettingMgr.m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_OFFICE_2007_OBSIDIAN_BLACK;
		break;
	case 6:
		AppSettingMgr.m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_OFFICE_2007_SILVER_LOOK;
		break;
	case 7:
		AppSettingMgr.m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_VISUAL_STUDIO_2008_LOOK;
		break;
	default:
		AppSettingMgr.m_ApplicationThemeLook = APPLICATION_THEME_LOOK::THEME_OFFICE_2003;
		break;
	}
}

void GeneralSettingDlg::InitDialogComboboxLimitSaveCombobox()
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

void GeneralSettingDlg::FromDialogComboboxLimitSaveCombobox()
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

BEGIN_MESSAGE_MAP(GeneralSettingDlg, CDialogEx)
	ON_WM_DROPFILES()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_USE_INSTALL_PATH_AS_APPDATA_PATH, &GeneralSettingDlg::OnBnClickedUseInstallPathAsAppdataPath)
END_MESSAGE_MAP()

// for scrolling //////////////////////////////////////////////////////////////

void GeneralSettingDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pScrollHelper->OnHScroll(nSBCode, nPos, pScrollBar);
}

void GeneralSettingDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pScrollHelper->OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL GeneralSettingDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	BOOL wasScrolled = m_pScrollHelper->OnMouseWheel(nFlags, zDelta, pt);

	return wasScrolled;
}

void GeneralSettingDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_pScrollHelper->OnSize(nType, cx, cy);
}

void GeneralSettingDlg::OnDropFiles(HDROP hDropInfo)
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
			if (!PathUtils::IsDirectory(szPath))
			{
				AfxMessageBox(_T("[Path Error] This setting requires a folder path, not file path."));
			}
			else
			{
				pEdit->SetWindowTextW(szPath);
			}
		}
	}
	DragFinish(hDropInfo);
}

void GeneralSettingDlg::OnBnClickedUseInstallPathAsAppdataPath()
{
	CButton* pCheckbox = (CButton*)GetDlgItem(ID_USE_INSTALL_PATH_AS_APPDATA_PATH);
	if (!pCheckbox->GetCheck())
	{
		CString strPortableAppDataPath = PathUtils::GetVinaTextAppDataPath();
		AfxMessageBoxFormat(MB_ICONINFORMATION, _T("Please delete portable folder \"%s\" when you want to use default app data path."), strPortableAppDataPath);
	}
}

///////////////////////////////////////////////////////////////////

BOOL GeneralSettingBrowse::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_DROPFILES)
	{
		GeneralSettingDlg* pParent = dynamic_cast<GeneralSettingDlg*>(GetParent());
		if (pParent)
		{
			pParent->m_hWndChildDropFile = this->m_hWnd;
			pParent->SendMessage(WM_DROPFILES, pMsg->wParam, pMsg->lParam);
			return TRUE; // got it
		}
	}
	return FALSE; // allow default processing
}
