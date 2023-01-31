/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "DialogBase.h"

// CReopenFileWithPasswordDlg dialog

class CReopenFileWithPasswordDlg : public CDlgBase
{
	DECLARE_DYNAMIC(CReopenFileWithPasswordDlg)

public:
	CReopenFileWithPasswordDlg(CString strFileSavePath, CWnd* pParent = NULL);   // standard constructor
	virtual ~CReopenFileWithPasswordDlg();

	enum { IDD = IDD_OPEN_FILE_WITH_PASSWORD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	CString m_strFileReopenPath;
public:
	afx_msg void OnBnClickedCheckShowPassword();
};
