/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "DialogBase.h"

// CCreateNewMultiplePathDlg dialog

class CCreateNewMultiplePathDlg : public CDlgBase
{
	DECLARE_DYNAMIC(CCreateNewMultiplePathDlg)
public:
	CCreateNewMultiplePathDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCreateNewMultiplePathDlg();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATE_NEW_MULTIPLE };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CMFCEditBrowseCtrl m_EditDataPath;
	BOOL m_bOverwriteFileIfExisted;
};
