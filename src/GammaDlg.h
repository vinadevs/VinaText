/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "DialogBase.h"

/////////////////////////////////////////////////////////////////////////////
// CGammaDlg dialog

class CGammaDlg : public CDlgBase
{
// Construction
public:
	CGammaDlg(CWnd* pParent = NULL);   // standard constructor

	enum { IDD = IDD_DIALOG_GAMMA };
	float	m_gamma;

// Overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	// Generated message map functions
	DECLARE_MESSAGE_MAP()
};
