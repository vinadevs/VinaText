/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once
#include "afxdialogex.h"

class CScrollHelper;

class ProgrammingSettingBrowse : public CMFCEditBrowseCtrl
{
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

// ProgrammingSettingDlg dialog

class ProgrammingSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ProgrammingSettingDlg)

public:
	ProgrammingSettingDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ProgrammingSettingDlg();

	enum { IDD = IDD_DIALOG_SETTING_PROGRAMMING };

	void UpdateGUISettings(BOOL bFromGUI);

	HWND m_hWndChildDropFile = NULL;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK() {}
	virtual void OnCancel() {}
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void InitDefaultTerminalWindowsCombobox();
	void FromDefaultTerminalWindowsCombobox();

	CComboBox m_DefaultToolbarTerminalWindows;

	BOOL m_bAllowOpenFileHasErrorBuild{ FALSE };
	BOOL m_bAskBeforeTerminateProgram{ FALSE };
	BOOL m_bAutoSaveDocumentWhenbuild{ FALSE };
	BOOL m_bEnableDisplayBuildErrorOnEditor{ FALSE };
	BOOL m_bEnableWarningFlagForCAndCPP{ FALSE };
	BOOL m_bEnableWindowSubsytemFlagForCAndCPP{ FALSE };
	BOOL m_bOpenWindowCmdWhenRunProgram{ FALSE };

	CString m_strNodeJSFolderPath;
	ProgrammingSettingBrowse m_EditNodeJSFolderPath;
	CString m_strPythonFolderPath;
	ProgrammingSettingBrowse m_EditPythonFolderPath;

	std::unique_ptr<CScrollHelper> m_pScrollHelper{ nullptr };
};
