/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "resource.h"
#include "afxwin.h"
#include "UndoRedoEditControl.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsPageEditorSetting dialog

class COptionsPageEditorSetting : public CMFCPropertyPage
{
	DECLARE_DYNCREATE(COptionsPageEditorSetting)

// Construction
public:
	COptionsPageEditorSetting();
	~COptionsPageEditorSetting();

	enum { IDD = IDD_OPTIONSPAGE1 };

// Overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL OnApply();

// Implementation
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnSettingModified();

	void InitSettings();
	void UpdateSettings();

public:
	CComboBox m_ComboEditorColorTheme;
	BOOL m_bEnableBoldFont;
	BOOL m_bEnableUrlLinkHighlight;
	CUndoRedoEditControl m_TextFontSizeEdit;
	CUndoRedoEditControl m_LineNumberFontSizeEdit;
	BOOL m_bEnableAutoSaveFile;
	BOOL m_bEnableSaveDocumentWhenBuild;
	BOOL m_bDisplayWarningFileNotExist;
	CUndoRedoEditControl m_AutoSaveIntervalTime;
	CString m_strTextFontSize;
	CString m_strLineNumberFontSize;
	CString m_strAutoSaveIntervalTime;
	CButton m_CreateNewCMDWindowRadio;
	CButton m_UseBuildWindowRadio;
};

/////////////////////////////////////////////////////////////////////////////
// COptionsPageFileSetting dialog

class COptionsPageFileSetting : public CMFCPropertyPage
{
	DECLARE_DYNCREATE(COptionsPageFileSetting)

// Construction
public:
	COptionsPageFileSetting();
	~COptionsPageFileSetting();

	enum { IDD = IDD_OPTIONSPAGE2 };

// Overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL OnApply();

// Implementation
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnSettingModified();

	void InitSettings();
	void UpdateSettings();

public:
	BOOL m_bRevealExplorerWindowWhenSwitchFile;
	BOOL m_bDetectFileChangeFromOutSide;
	BOOL m_bAllowOpenFileHasErrorBuild;
	BOOL m_bEnableHighlightFolderTracker;
	BOOL m_bDrawFoldingLine;
	CComboBox m_ComboEditorFoldingStyle;
};

/////////////////////////////////////////////////////////////////////////////
// COptionsPagePathSetting dialog

class COptionsPagePathSetting : public CMFCPropertyPage
{
	DECLARE_DYNCREATE(COptionsPagePathSetting)

	// Construction
public:
	COptionsPagePathSetting();
	~COptionsPagePathSetting();

	enum { IDD = IDD_OPTIONSPAGE3 };

	// Overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

														// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// COptionsPageBuildDebugSetting dialog

class COptionsPageBuildDebugSetting : public CMFCPropertyPage
{
	DECLARE_DYNCREATE(COptionsPageBuildDebugSetting)

	// Construction
public:
	COptionsPageBuildDebugSetting();
	~COptionsPageBuildDebugSetting();

	enum { IDD = IDD_OPTIONSPAGE4 };

	// Overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

														// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// COptionsPageTranslateSetting dialog

class COptionsPageTranslateSetting : public CMFCPropertyPage
{
	DECLARE_DYNCREATE(COptionsPageTranslateSetting)

	// Construction
public:
	COptionsPageTranslateSetting();
	~COptionsPageTranslateSetting();

	enum { IDD = IDD_OPTIONSPAGE5 };

	// Overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

														// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// COptionsPageGeneralSetting1 dialog

class COptionsPageGeneralSetting1 : public CMFCPropertyPage
{
	DECLARE_DYNCREATE(COptionsPageGeneralSetting1)

// Construction
public:
	COptionsPageGeneralSetting1();
	~COptionsPageGeneralSetting1();

	enum { IDD = IDD_OPTIONSPAGE6 };

// Overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// COptionsPageGeneralSetting1 dialog

class COptionsPageGeneralSetting2 : public CMFCPropertyPage
{
	DECLARE_DYNCREATE(COptionsPageGeneralSetting2)

	// Construction
public:
	COptionsPageGeneralSetting2();
	~COptionsPageGeneralSetting2();

	enum { IDD = IDD_OPTIONSPAGE7 };

	// Overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

														// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};