/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "UndoRedoEditControl.h"

class CProjectTempateCreator : public CDialogEx
{
	DECLARE_DYNAMIC(CProjectTempateCreator)

public:
	CProjectTempateCreator(const CString& strFolder, CWnd* pParent = NULL);   // standard constructor
	virtual ~CProjectTempateCreator();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROJECT_TEMPLATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	CString m_strFolder;
	CUndoRedoEditControl m_EditProjectName;
	CMFCEditBrowseCtrl m_EditProjectLocation;
	CComboBox	m_ComboProjectLanguage;
	CComboBox	m_ComboProjectType;

	void InitComboProjectLanguage();
	void InitComboProjectType();
	afx_msg void OnCbnSelchangeComboProjectLanguage();
	afx_msg void OnCbnSelchangeComboProjectType();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
