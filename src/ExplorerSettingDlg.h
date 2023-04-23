/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once
#include "afxdialogex.h"

class ExplorerSettingBrowse : public CMFCEditBrowseCtrl
{
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

// ExplorerSettingDlg dialog

class ExplorerSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ExplorerSettingDlg)

public:
	ExplorerSettingDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ExplorerSettingDlg() {};

	enum { IDD = IDD_DIALOG_SETTING_EXPLORER };

	HWND m_hWndChildDropFile = NULL;

	void UpdateGUISettings(BOOL bFromGUI);

protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK() {}
	virtual void OnCancel() {}
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	afx_msg void OnDropFiles(HDROP hDropInfo);

	BOOL m_bEnablePathNavigation {FALSE};
	BOOL m_bEnablePreviewFile{ FALSE };
	BOOL m_bHideAllTargetFileSystem{ FALSE };
	BOOL m_bRevealExplorerWhenDlbClkFile{ FALSE };
	BOOL m_bRevealExplorerWhenSwitchFile{ FALSE };
	BOOL m_bUseWin10ExplorerStyle{ FALSE };

	int m_nExplorerExpandLimitFileOpen{ 0 };
	int m_nExplorerExpandLimitLevel{ 0 };
	int m_nFilePreviewSizeLimit{ 0 };

	CString m_strAntiVirusArgument;
	CString m_strAntiVirusProgram;
	ExplorerSettingBrowse m_EditAntiVirusProgram;
};
