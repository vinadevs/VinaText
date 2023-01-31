/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "VinaTextApp.h"
#include "Resource.h"
#include "VinaTextSettingDlg.h"
#include "afxdialogex.h"
#include "AppUtil.h"
#include "AppSettings.h"
#include "RAIIUtils.h"
#include "MainFrm.h"

// VinaTextSettingDlg dialog

IMPLEMENT_DYNAMIC(VinaTextSettingDlg, CDialogEx)

VinaTextSettingDlg::VinaTextSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_APP_SETTINGS, pParent)
{
}

VinaTextSettingDlg::~VinaTextSettingDlg()
{
	DELETE_POINTER_CPP(m_pImglist);
	DELETE_POINTER_CPP(m_pFont);
}

void VinaTextSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_DIALOG_SETTINGS, m_CTabCtrl);
}

BOOL VinaTextSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);

	GetClientRect(&m_SaveRect);

	m_pImglist = new CImageList();
	m_pImglist->Create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 3);
	m_pImglist->Add(AfxGetApp()->LoadIcon(IDR_SETTING_TAB));
	m_pImglist->Add(AfxGetApp()->LoadIcon(IDR_SETTING_TAB));
	m_pImglist->Add(AfxGetApp()->LoadIcon(IDR_SETTING_TAB));
	m_CTabCtrl.SetImageList(m_pImglist);

	m_CTabCtrl.InsertItem(0, _T("           Toggle Setting                 "), 0);
	m_CTabCtrl.InsertItem(1, _T("           Customization Setting                "), 1);
	m_CTabCtrl.InsertItem(2, _T("           File System Setting                "), 2);

	m_pFont = new CFont();
	m_pFont->CreatePointFont(100, _T("Tahoma"));
	GetDlgItem(IDC_TAB_DIALOG_SETTINGS)->SetFont(m_pFont, TRUE);

	CRect rect;
	m_CTabCtrl.GetClientRect(&rect);

	// setting dialog A
	m_SettingDlgToggle.Create(IDD_DIALOG_SETTING_TOGGLE, &m_CTabCtrl);
	m_SettingDlgToggle.SetWindowPos(NULL, 0, 23, rect.Width(), rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
	m_SettingDlgToggle.ShowWindow(SW_SHOW);
	m_pCurrentTabShow = &m_SettingDlgToggle;

	// setting dialog B
	m_SettingDlgCustomize.Create(IDD_DIALOG_SETTING_CUSTOMIZE, &m_CTabCtrl);
	m_SettingDlgCustomize.SetWindowPos(NULL, 0, 23, rect.Width(), rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
	m_SettingDlgCustomize.ShowWindow(SW_HIDE);

	// setting dialog C
	m_SettingDlgFileSystem.Create(IDD_DIALOG_SETTING_FILE_SYSTEM, &m_CTabCtrl);
	m_SettingDlgFileSystem.SetWindowPos(NULL, 0, 23, rect.Width(), rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
	m_SettingDlgFileSystem.ShowWindow(SW_HIDE);

	UpdateData(FALSE);
	//attemted an unsupported operation
	return TRUE;  // return TRUE unless you set the focus to a control 
				  // EXCEPTION: OCX Property Pages should return FALSE 
}

BEGIN_MESSAGE_MAP(VinaTextSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_APPLY, &VinaTextSettingDlg::OnBnClickedApply)
	ON_BN_CLICKED(IDOK, &VinaTextSettingDlg::OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_DIALOG_SETTINGS, &VinaTextSettingDlg::OnTcnSelchangeTab)
END_MESSAGE_MAP()

// VinaTextSettingDlg message handlers


void VinaTextSettingDlg::UpdateSettings()
{
	CWaitCursor wait;
	// get latest settings
	m_SettingDlgToggle.UpdateGUISettings(TRUE);
	m_SettingDlgCustomize.UpdateGUISettings(TRUE);
	m_SettingDlgFileSystem.UpdateGUISettings(TRUE);
	// reflect new changes
	UpdateApplicationLook();
	AppUtils::UpdateSettingForEditors();
	UPDATE_MAIN_FRAME(MAIN_FRAME_UPDATE_MSG::MAIN_FRAME_UPDATE_ALL_DOCKPANE,
		MAIN_FRAME_UPDATE_HINT::MAIN_FRAME_UPDATE_HINT_SETTING_CHANGED);

}

void VinaTextSettingDlg::OnBnClickedApply()
{
	// TODO: Add your control notification handler code here
	UpdateSettings();
	AfxMessageBox(_T("New settings updated!"), MB_ICONINFORMATION);
	LOG_OUTPUT_MESSAGE_COLOR(_T("> [Application Setting] New settings updated..."));
}

void VinaTextSettingDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	UpdateSettings();
	AfxMessageBox(_T("New settings updated!"), MB_ICONINFORMATION);
	LOG_OUTPUT_MESSAGE_COLOR(_T("> [Application Setting] New settings updated..."));
}

void VinaTextSettingDlg::OnTcnSelchangeTab(NMHDR * pNMHDR, LRESULT * pResult)
{
	// TODO: Add your control notification handler code here
	if (m_pCurrentTabShow != NULL)
	{
		m_pCurrentTabShow->ShowWindow(SW_HIDE);
		m_pCurrentTabShow = NULL;
	}

	auto tabIndex = m_CTabCtrl.GetCurSel();

	switch (tabIndex)
	{
	case 0:
		m_uiActiveTab = TABACTIVE::SETTINGS_TAB_A;
		m_SettingDlgToggle.ShowWindow(SW_SHOW);
		m_SettingDlgToggle.UpdateData(FALSE);
		m_SettingDlgToggle.SetFocus();
		m_pCurrentTabShow = &m_SettingDlgToggle;
		break;
	case 1:
		m_uiActiveTab = TABACTIVE::SETTINGS_TAB_B;
		m_SettingDlgCustomize.ShowWindow(SW_SHOW);
		m_SettingDlgCustomize.UpdateData(FALSE);
		m_SettingDlgCustomize.SetFocus();
		m_pCurrentTabShow = &m_SettingDlgCustomize;
		break;
	case 2:
		m_uiActiveTab = TABACTIVE::SETTINGS_TAB_C;
		m_SettingDlgFileSystem.ShowWindow(SW_SHOW);
		m_SettingDlgFileSystem.UpdateData(FALSE);
		m_SettingDlgFileSystem.SetFocus();
		m_pCurrentTabShow = &m_SettingDlgFileSystem;
		break;
	}
	*pResult = 0;

	UpdateData(FALSE);
}

void VinaTextSettingDlg::UpdateApplicationLook()
{
	CMainFrame* pMainFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	if (pMainFrame != NULL)
	{
		pMainFrame->LockWindowUpdate();
	}

	CTabbedPane::m_StyleTabWnd = CMFCTabCtrl::STYLE_3D;

	switch (AppSettingMgr.m_ApplicationThemeLook)
	{
	case APPLICATION_THEME_LOOK::THEME_OFFICE_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		break;

	case APPLICATION_THEME_LOOK::THEME_VISUAL_STUDIO_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		if (m_bRoundedTabs)
		{
			CTabbedPane::m_StyleTabWnd = CMFCTabCtrl::STYLE_3D_ROUNDED;
		}
		CMFCVisualManagerVS2005::m_bRoundedAutohideButtons = m_bRoundedTabs;
		break;

	case APPLICATION_THEME_LOOK::THEME_WINDOWS_XP_NATIVE:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		break;

	case APPLICATION_THEME_LOOK::THEME_OFFICE_2007_LUNA_BLUE:
		CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		break;

	case APPLICATION_THEME_LOOK::THEME_OFFICE_2007_OBSIDIAN_BLACK:
		CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		break;

	case APPLICATION_THEME_LOOK::THEME_OFFICE_2007_AQUA:
		CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		break;

	case APPLICATION_THEME_LOOK::THEME_OFFICE_2007_SILVER_LOOK:
		CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		break;

	case APPLICATION_THEME_LOOK::THEME_VISUAL_STUDIO_2008_LOOK:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		break;
	}

	switch (AppSettingMgr.m_ApplicationThemeLook)
	{
	case 0: // Office 2003
	case 1: // VS.NET 2005
	case 2: // Windows XP
	case 3: // Office 2007
	case 4: // Office 2007
	case 5: // Office 2007
	case 6: // Office 2007
	case 7: // VS 2008
	{
		CWindowDC dc(NULL);
		theApp.m_bHiColorIcons = dc.GetDeviceCaps(BITSPIXEL) >= 16;
		CDockingManager::SetDockingMode(DT_SMART);
	}
	break;

	default:
		theApp.m_bHiColorIcons = FALSE;
	}

	CTabbedPane::ResetTabs();

	if (m_bCustomTooltips)
	{
		CMFCToolTipInfo params;
		params.m_bVislManagerTheme = TRUE;

		theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL, RUNTIME_CLASS(CMFCToolTipCtrl), &params);
	}
	else
	{
		theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL, NULL, NULL);
	}

	if (pMainFrame != NULL)
	{
		pMainFrame->OnChangeAppLook(m_bOneNoteTabs/* OneNote tabs */, m_bOneNoteTabs /* MDI tab colors*/, AppSettingMgr.m_ApplicationThemeLook != 0 /* VS.NET look */, m_bDockTabColors /* Dock tab colors*/, AppSettingMgr.m_ApplicationThemeLook == 1 || AppSettingMgr.m_ApplicationThemeLook == 7 /* VS 2005/2008 MDI tabs */, m_bActiveTabCloseButton);

		pMainFrame->UnlockWindowUpdate();
		pMainFrame->RedrawWindow();
	}
}