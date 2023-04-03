/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "afxwin.h"
#include "UndoRedoEditControl.h"

// SettingDlgFileSystem dialog

class CEditDropNotifier : public CMFCEditBrowseCtrl
{
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

///////////////////////////////////////////////////////////////////

class SettingDlgFileSystem : public CDialogEx
{
	DECLARE_DYNAMIC(SettingDlgFileSystem)

public:
	SettingDlgFileSystem(CWnd* pParent = NULL);   // standard constructor
	virtual ~SettingDlgFileSystem();

// Dialog Data
	enum { IDD = IDD_DIALOG_SETTING_FILE_SYSTEM };

	void UpdateGUISettings(BOOL bFromGUI);

	HWND m_hWndChildDropFile = NULL;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnDropFiles(HDROP hDropInfo);
	virtual BOOL OnInitDialog();
	virtual void OnOK() {}
	virtual void OnCancel() {}
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	DECLARE_MESSAGE_MAP()
private:
	CString m_strInitialFilePickerPath;
	CEditDropNotifier m_EditInitialFilePickerPath;
	CString m_strNodeJSFolderPath;
	CEditDropNotifier m_EditNodeJSFolderPath;
	CString m_strPythonFolderPath;
	CEditDropNotifier m_EditPythonFolderPath;
	CString m_strGitWindowFolderPath;
	CEditDropNotifier m_EditGitWindowFolderPath;
	CString m_strAntiVirusArgument;
	CString m_strAntiVirusProgram;
	CEditDropNotifier m_EditAntiVirusProgram;
	CString m_strBinaryFileExtensionList;

	int m_nLineSpaceAbove;
	int m_nLineSpaceBelow;
	int m_nIntervalAutoSaveFileMinutes;
	int m_nExplorerExpandLimitFileOpen;
	int m_nExplorerExpandLimitLevel;
	int m_nFilePreviewSizeLimit;
	int m_nRecentFileLimit;

	void InitLanguageSpellCheckCombo();
	void InitLanguageTranslateFromCombo();
	void InitLanguageTranslateToCombo();
	void FromLanguageSpellCheckCombo();
	void FromLanguageTranslateFromCombo();
	void FromLanguageTranslateToCombo();

	CComboBox m_LanguageSpellCheckCombo;
	CComboBox m_LanguageTranslateFromCombo;
	CComboBox m_LanguageTranslateToCombo;

	CUndoRedoEditControl m_EditBinaryFileExtensionList;
public:
	int m_nLongLineMaximum;
};
