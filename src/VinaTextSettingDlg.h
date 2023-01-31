/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "afxcmn.h"
#include "SettingDlgToggle.h"
#include "SettingDlgCustomize.h"
#include "SettingDlgFileSystem.h"

// VinaTextSettingDlg dialog

class VinaTextSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VinaTextSettingDlg)

public:
	VinaTextSettingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~VinaTextSettingDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_APP_SETTINGS };

	enum class TABACTIVE : unsigned int
	{
		SETTINGS_TAB_A = 0,
		SETTINGS_TAB_B = 1,
		SETTINGS_TAB_C = 1,
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	void UpdateSettings();
	void UpdateApplicationLook();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedApply();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);

	CRect m_SaveRect;
	CImageList *m_pImglist;
	CFont *m_pFont;
	CWnd* m_pCurrentTabShow;
	TABACTIVE m_uiActiveTab;
	SettingDlgToggle m_SettingDlgToggle;
	SettingDlgCustomize m_SettingDlgCustomize;
	SettingDlgFileSystem m_SettingDlgFileSystem;
	CTabCtrl m_CTabCtrl;

	// Apllication Look
	BOOL m_bShowAtStartup = FALSE;
	BOOL m_bOneNoteTabs = TRUE;
	BOOL m_bDockTabColors = FALSE;
	BOOL m_bRoundedTabs = FALSE;
	BOOL m_bCustomTooltips = TRUE;
	BOOL m_bActiveTabCloseButton = FALSE;
};
