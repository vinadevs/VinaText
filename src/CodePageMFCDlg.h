/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CodePageMFC.h"
#include "DialogBase.h"

/////////////////////////////////////////////////////////////////////////////
// CCodePageMFCDlg dialog

class CCodePageMFCDlg : public CDlgBase
{
// Construction
public:
	CCodePageMFCDlg(CWnd* pParent = NULL);	// standard constructor

	enum { IDD = IDD_CODEPAGEMFC_DIALOG };
	CListCtrl	m_wndInstalled;

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	void SetDlgModeReopen(BOOL bReopen) { m_bReopen = bReopen; }

// Implementation
protected:
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	void InitListControl(CListCtrl& listControl, const CCodePage::CCodePageObject& cpObject);
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
public:
	afx_msg void OnBnClickedOk();

protected:
	BOOL m_bReopen;
};