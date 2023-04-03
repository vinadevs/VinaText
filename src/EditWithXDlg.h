/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "DialogBase.h"

class CEditWithXDlg : public CDlgBase
{
public:
	//Constructors / Destructors
	CEditWithXDlg(CWnd* pParent = NULL);

	//Member variables
	enum { IDD = IDD_EDIT_WITH_X };
	CString m_sXInput;

protected:
	void DoDataExchange(CDataExchange* pDX) override;
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
