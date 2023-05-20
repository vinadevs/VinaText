/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "afxcmn.h"
#include "ProgrammingSettingDlg.h"
#include "GeneralSettingDlg.h"
#include "EditorSettingDlg.h"
#include "ExplorerSettingDlg.h"

// VinaTextSettingDlg dialog

class VinaTextSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VinaTextSettingDlg)

public:
	VinaTextSettingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~VinaTextSettingDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_APP_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	void UpdateSettings(BOOL bFromGUI);
	void UpdateApplicationLook();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedApply();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonResetSettings();

	CRect m_SaveRect;
	CImageList *m_pImglist;
	CFont *m_pFont;
	CWnd* m_pCurrentTabShow;
	CTabCtrl m_CTabCtrl;

	// tab dialogs
	ExplorerSettingDlg m_ExplorerSettingDlg;
	EditorSettingDlg m_EditorSettingDlg;
	GeneralSettingDlg m_GeneralSettingDlg;
	ProgrammingSettingDlg m_ProgrammingSettingDlg;

	// Apllication Look
	BOOL m_bShowAtStartup = FALSE;
	BOOL m_bOneNoteTabs = TRUE;
	BOOL m_bDockTabColors = FALSE;
	BOOL m_bRoundedTabs = FALSE;
	BOOL m_bCustomTooltips = TRUE;
	BOOL m_bActiveTabCloseButton = FALSE;
};
