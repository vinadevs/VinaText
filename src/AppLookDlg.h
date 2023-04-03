/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CAppLookDlg dialog

class CAppLookDlg : public CDialogEx
{
// Construction
public:
	CAppLookDlg(BOOL bStartup, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	enum { IDD = IDD_APP_LOOK };
	CComboBox m_wndStyle;
	CButton m_wndRoundedTabs;
	CButton m_wndDockTabColors;
	CButton m_wndOneNoteTabs;
	CButton m_wndOK;
	CButton m_wndCancel;
	BOOL m_bShowAtStartup;
	BOOL m_bOneNoteTabs;
	BOOL m_bDockTabColors;
	BOOL m_bRoundedTabs;
	BOOL m_bCustomTooltips;
	int m_nAppLook;
	int m_nStyle;
	BOOL m_bActiveTabCloseButton;

// Overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnApply();
	afx_msg void OnAppLook();

	DECLARE_MESSAGE_MAP()

	const BOOL m_bStartup;

	void SetLook();
};
