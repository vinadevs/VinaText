/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "DialogBase.h"

class CDeleteFileExtensionDlg : public CDlgBase
{
public:
	//Constructors
	CDeleteFileExtensionDlg(CWnd* pParent = NULL);

	//Member variables
	enum { IDD = IDD_REMOVE_FILE_WITH_EXTENSION };
	CString m_sPath;
	CString m_sExt;

protected:
	//Methods
	void DoDataExchange(CDataExchange* pDX) override;

	virtual BOOL OnInitDialog();

	CMFCEditBrowseCtrl m_EditPath;
	afx_msg void OnFilterEditChange();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()
};
