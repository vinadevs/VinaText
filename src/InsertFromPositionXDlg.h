/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

// CInsertFromPositionXDlg dialog

#include "DialogBase.h"

class CInsertFromPositionXDlg : public CDlgBase
{
	DECLARE_DYNAMIC(CInsertFromPositionXDlg)

public:
	CInsertFromPositionXDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInsertFromPositionXDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_INSERT_AT_POSITION_X };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString m_strPositionX;
	CString m_strInsertWhat;
	BOOL m_bInsertFromLineEnd;
};
