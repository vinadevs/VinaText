/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once
#include "DialogBase.h"

// COpenTabWindows dialog

class COpenTabWindows : public CDlgBase
{
	DECLARE_DYNAMIC(COpenTabWindows)

public:
	COpenTabWindows(CWnd* pParent = nullptr);   // standard constructor
	virtual ~COpenTabWindows() {};

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OPEN_DOCUMENTS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog() override;
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void InitiateList();
	void OnCopyFullPath();

	CListCtrl m_listTab;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonCloseTabs();
	afx_msg void OnBnClickedButtonActiveTab();
	afx_msg void OnBnClickedButtonSaveTab();
	afx_msg void OnBnClickedButtonCopyPathTab();
	afx_msg void OnBnClickedOk();
};
