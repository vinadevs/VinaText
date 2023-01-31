/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "DialogBase.h"

// CInsertBetweenLines dialog

class CInsertBetweenLines : public CDlgBase
{
	DECLARE_DYNAMIC(CInsertBetweenLines)

public:
	CInsertBetweenLines(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInsertBetweenLines();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_INSERT_BETWEEN_LINES };
#endif

	CString m_strInsertWhat;
	BOOL m_bInsertTopMost;
	BOOL m_bInsertBottomMost;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
