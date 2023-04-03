/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "afxwin.h"

// SettingDlgCustomize dialog

class SettingDlgCustomize : public CDialogEx
{
	DECLARE_DYNAMIC(SettingDlgCustomize)

public:
	SettingDlgCustomize(CWnd* pParent = NULL);   // standard constructor
	virtual ~SettingDlgCustomize();

	// Dialog Data
	enum { IDD = IDD_DIALOG_SETTING_CUSTOMIZE };

	void UpdateGUISettings(BOOL bFromGUI);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK() {}
	virtual void OnCancel() {}
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	void InitActiveTabColorCombobox();
	void InitCaretBlinkColorCombobox();
	void InitFolderMarginStyleCombobox();
	void InitIndicatorColorCombobox();
	void InitIndicatorStyleCombobox();
	void InitThemeColorCombobox();
	void InitRenderIndicatorActionCombobox();
	void InitDialogComboboxLimitSaveCombobox();
	void InitDockWindowFontWeightCombobox();
	void InitDialogWindowFontWeightCombobox();
	void InitApplicationThemLookCombobox();

	void FromActiveTabColorCombobox();
	void FromCaretBlinkColorCombobox();
	void FromFolderMarginStyleCombobox();
	void FromIndicatorColorCombobox();
	void FromIndicatorStyleCombobox();
	void FromThemeColorCombobox();
	void FromRenderIndicatorActionCombobox();
	void FromDialogComboboxLimitSaveCombobox();
	void FromDockWindowFontWeightCombobox();
	void FromDialogWindowFontWeightCombobox();
	void FromApplicationThemLookCombobox();

	CComboBox m_ActiveTabColorCombo;
	CComboBox m_CaretBlinkColorCombo;
	int m_nDialogFontHeight;
	int m_nDockWindowFontHeight;
	afx_msg void OnBnClickedDockWindowFontNameButton();
	afx_msg void OnBnClickedEditorFontNameButton();
	afx_msg void OnBnClickedDialogFontNameButton();
	int m_nEditorLineNumberFontSize;
	int m_nEditorTextFontSize;
	CComboBox m_FolderMarginStyleCombo;
	CComboBox m_IndicatorColorCombo;
	CComboBox m_IndicatorStyleCombo;
	CComboBox m_ThemeColorCombo;
	int m_nPageAlignmentWidth;
	CComboBox m_RenderIndicatorActionCombo;
	CComboBox m_DialogComboboxLimitSaveCombo;
	CComboBox m_DockWindowFontWeightCombo;
	CComboBox m_DialogWindowFontWeightCombo;
	CComboBox m_ApplicationThemLookCombo;
	DECLARE_MESSAGE_MAP()
};
	
