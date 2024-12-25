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
#include "afxtaskdialog.h"

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
	m_pImglist->Create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 4);
	m_pImglist->Add(AfxGetApp()->LoadIcon(IDR_EDITOR_DOC));
	m_pImglist->Add(AfxGetApp()->LoadIcon(IDR_SETTING_TAB));
	m_pImglist->Add(AfxGetApp()->LoadIcon(IDR_BRACKETS_OUTLINE));
	m_pImglist->Add(AfxGetApp()->LoadIcon(IDR_FILE_EXPLORER_DOC));
	m_CTabCtrl.SetImageList(m_pImglist);

	m_CTabCtrl.InsertItem(0, _T("   Editor Settings   "), 0);
	m_CTabCtrl.InsertItem(1, _T("   General Settings   "), 1);
	m_CTabCtrl.InsertItem(2, _T("   Programming Settings   "), 2);
	m_CTabCtrl.InsertItem(3, _T("   Explorer Settings   "), 3);

	m_pFont = new CFont();
	m_pFont->CreatePointFont(100, _T("Tahoma"));
	GetDlgItem(IDC_TAB_DIALOG_SETTINGS)->SetFont(m_pFont, TRUE);

	CRect rect;
	m_CTabCtrl.GetClientRect(&rect);

	m_EditorSettingDlg.Create(IDD_DIALOG_SETTING_EDITOR, &m_CTabCtrl);
	m_EditorSettingDlg.SetWindowPos(NULL, 0, 23, rect.Width(), rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
	m_EditorSettingDlg.ShowWindow(SW_SHOW);
	m_pCurrentTabShow = &m_EditorSettingDlg;

	m_GeneralSettingDlg.Create(IDD_DIALOG_SETTING_GENERAL, &m_CTabCtrl);
	m_GeneralSettingDlg.SetWindowPos(NULL, 0, 23, rect.Width(), rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
	m_GeneralSettingDlg.ShowWindow(SW_HIDE);

	m_ProgrammingSettingDlg.Create(IDD_DIALOG_SETTING_PROGRAMMING, &m_CTabCtrl);
	m_ProgrammingSettingDlg.SetWindowPos(NULL, 0, 23, rect.Width(), rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
	m_ProgrammingSettingDlg.ShowWindow(SW_HIDE);

	m_ExplorerSettingDlg.Create(IDD_DIALOG_SETTING_EXPLORER, &m_CTabCtrl);
	m_ExplorerSettingDlg.SetWindowPos(NULL, 0, 23, rect.Width(), rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
	m_ExplorerSettingDlg.ShowWindow(SW_HIDE);

	UpdateData(FALSE);
	//attemted an unsupported operation
	return TRUE;  // return TRUE unless you set the focus to a control 
				  // EXCEPTION: OCX Property Pages should return FALSE 
}

BEGIN_MESSAGE_MAP(VinaTextSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_APPLY, &VinaTextSettingDlg::OnBnClickedApply)
	ON_BN_CLICKED(IDOK, &VinaTextSettingDlg::OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_DIALOG_SETTINGS, &VinaTextSettingDlg::OnTcnSelchangeTab)
	ON_BN_CLICKED(IDC_BUTTON_RESET_SETTINGS, &VinaTextSettingDlg::OnBnClickedButtonResetSettings)
END_MESSAGE_MAP()

// VinaTextSettingDlg message handlers


void VinaTextSettingDlg::UpdateSettings(BOOL bFromGUI)
{
	CWaitCursor wait;
	m_GeneralSettingDlg.UpdateGUISettings(bFromGUI);
	m_EditorSettingDlg.UpdateGUISettings(bFromGUI);
	m_ProgrammingSettingDlg.UpdateGUISettings(bFromGUI);
	m_ExplorerSettingDlg.UpdateGUISettings(bFromGUI);
	if (bFromGUI) // reflect new changes
	{
		UpdateApplicationLook();
		AppUtils::UpdateSettingsForVinatext();
	}
}

void VinaTextSettingDlg::OnBnClickedApply()
{
	UpdateSettings(TRUE);
}

void VinaTextSettingDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
	UpdateSettings(TRUE);
	AfxMessageBox(_T("New settings updated."), MB_ICONINFORMATION);
	LOG_OUTPUT_MESSAGE_COLOR(_T("> [Prerefence] new settings updated..."));
}

void VinaTextSettingDlg::OnBnClickedButtonResetSettings()
{
	constexpr int RESET_SETTINGS_ONLY_APP_ID = 501;
	constexpr int RESET_ALL_AND_RESTART_APP_ID = 502;
	constexpr int CANCEL_ID = 503;
	auto fTaskResetDialog = [&]() -> BOOL
	{
		CString strMessage = _T("[Warning] This operation will reset all your settings to original default state, please choose an action:");
		CTaskDialog dlg(_T(""), strMessage, _T("VinaText"), 0/*TDCBF_OK_BUTTON*/);
		dlg.SetMainIcon(TD_WARNING_ICON);
		dlg.AddCommandControl(RESET_SETTINGS_ONLY_APP_ID, _T("Reset all settings but do NOT restart Vinatext."));
		dlg.AddCommandControl(RESET_ALL_AND_RESTART_APP_ID, _T("Reset all settings and window placements then restart Vinatext."));
		dlg.AddCommandControl(CANCEL_ID, _T("Cancel"));
		dlg.SetDialogWidth(300);
		dlg.SetDefaultCommandControl(RESET_SETTINGS_ONLY_APP_ID);
		dlg.DoModal();
		return dlg.GetSelectedCommandControlID();
	};

	int nUserOption = fTaskResetDialog();
	if (nUserOption == RESET_SETTINGS_ONLY_APP_ID)
	{
		AppSettingMgr.ResetAllSettings();
		// Load original settings to dialog setting
		UpdateSettings(FALSE);
		// Update original to App GUI
		UpdateSettings(TRUE);
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Prerefence] all settings reset to original default state..."));
	}
	else if (nUserOption == RESET_ALL_AND_RESTART_APP_ID)
	{
		AppSettingMgr.ResetAllSettings();
		AppSettingMgr.ResetWindowPlacements();
		AppUtils::CloseAllDocument();
		OSUtils::RestartAppplication();
	}
}

void VinaTextSettingDlg::OnTcnSelchangeTab(NMHDR * pNMHDR, LRESULT * pResult)
{
	if (m_pCurrentTabShow != NULL)
	{
		m_pCurrentTabShow->ShowWindow(SW_HIDE);
		m_pCurrentTabShow = NULL;
	}

	auto tabIndex = m_CTabCtrl.GetCurSel();

	switch (tabIndex)
	{
	case 0:
		m_EditorSettingDlg.ShowWindow(SW_SHOW);
		m_EditorSettingDlg.UpdateData(FALSE);
		m_EditorSettingDlg.SetFocus();
		m_pCurrentTabShow = &m_EditorSettingDlg;
		break;
	case 1:
		m_GeneralSettingDlg.ShowWindow(SW_SHOW);
		m_GeneralSettingDlg.UpdateData(FALSE);
		m_GeneralSettingDlg.SetFocus();
		m_pCurrentTabShow = &m_GeneralSettingDlg;
		break;
	case 2:
		m_ProgrammingSettingDlg.ShowWindow(SW_SHOW);
		m_ProgrammingSettingDlg.UpdateData(FALSE);
		m_ProgrammingSettingDlg.SetFocus();
		m_pCurrentTabShow = &m_ProgrammingSettingDlg;
		break;
	case 3:
		m_ExplorerSettingDlg.ShowWindow(SW_SHOW);
		m_ExplorerSettingDlg.UpdateData(FALSE);
		m_ExplorerSettingDlg.SetFocus();
		m_pCurrentTabShow = &m_ExplorerSettingDlg;
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

	CWindowDC dc(NULL);
	CDockingManager::SetDockingMode(DT_SMART);

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