/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "DialogBase.h"

class CSelectedPathDlg : public CDlgBase
{
	DECLARE_DYNAMIC(CSelectedPathDlg)
public:
	//Constructors
	CSelectedPathDlg(CWnd* pParent = NULL);

	//Member variables
	enum { IDD = IDD_SELECTEDPATH };

protected:
	//Methods
	virtual void OnCancel();
	virtual void DoDataExchange(CDataExchange* pDX) override;
	void SaveSearchPath(const CString& strSearchPath);
	void SaveDialogState();
	void LoadDialogState();

	virtual BOOL OnInitDialog();
	BOOL m_bExpandChildPath = TRUE;
	CComboBox m_ComboEditPath;
	CStringArray m_SearchPathArr;
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()
};
