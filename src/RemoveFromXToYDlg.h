/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

// CRemoveFromXToYDlg dialog

#include "DialogBase.h"

class CRemoveFromXToYDlg : public CDlgBase
{
	DECLARE_DYNAMIC(CRemoveFromXToYDlg)

public:
	CRemoveFromXToYDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRemoveFromXToYDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_REMOVE_FROM_X_TO_Y };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString m_strFromX;
	CString m_strToY;
	BOOL m_bRemoveFromEndLine;
};
