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

class GeneralSettingBrowse : public CMFCEditBrowseCtrl
{
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

// GeneralSettingDlg dialog

class GeneralSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GeneralSettingDlg)

public:
	GeneralSettingDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~GeneralSettingDlg();

	enum { IDD = IDD_DIALOG_SETTING_GENERAL };

	void UpdateGUISettings(BOOL bFromGUI);

	HWND m_hWndChildDropFile = NULL;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK() {}
	virtual void OnCancel() {}
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void InitActiveTabColorCombobox();
	void FromActiveTabColorCombobox();
	void InitThemeColorCombobox();
	void FromThemeColorCombobox();
	void InitApplicationThemLookCombobox();
	void FromApplicationThemLookCombobox();
	void InitDockWindowFontWeightCombobox();
	void InitDialogWindowFontWeightCombobox();
	void FromDockWindowFontWeightCombobox();
	void FromDialogWindowFontWeightCombobox();
	void InitDialogComboboxLimitSaveCombobox();
	void FromDialogComboboxLimitSaveCombobox();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedDockWindowFontNameButton();
	afx_msg void OnBnClickedDialogFontNameButton();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	CComboBox m_ActiveTabColorCombo;
	CComboBox m_ThemeColorCombo;
	CComboBox m_ApplicationThemLookCombo;
	CComboBox m_DockWindowFontWeightCombo;
	CComboBox m_DialogWindowFontWeightCombo;
	CComboBox m_DialogComboboxLimitSaveCombo;

	int m_nDialogFontHeight{0};
	int m_nDockWindowFontHeight{0};
	int m_nRecentFileLimit{0};

	BOOL m_bWarningForFileNotExist{ FALSE };
	BOOL m_bShowTrackingBar{ FALSE };
	BOOL m_bUseInitialFilePickerPath{ FALSE };
	BOOL m_bSaveDataBookmarkWindow{ FALSE };
	BOOL m_bDetectFileChangeFromOutSide{ FALSE };
	BOOL m_bCheckFileSizeBeforeOpen{ FALSE };
	BOOL m_bDisplayMessageBoxForFileChange{ FALSE };

	std::unique_ptr<CScrollHelper> m_pScrollHelper{ nullptr };

	CString m_strBinaryFileExtensionList;
	CString m_strInitialFilePickerPath;
	GeneralSettingBrowse m_EditInitialFilePickerPath;
};