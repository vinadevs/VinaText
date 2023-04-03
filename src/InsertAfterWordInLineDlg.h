/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

// CInsertAfterWordInLineDlg dialog

#include "DialogBase.h"

class CInsertAfterWordInLineDlg : public CDlgBase
{
	DECLARE_DYNAMIC(CInsertAfterWordInLineDlg)

public:
	CInsertAfterWordInLineDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInsertAfterWordInLineDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_INSERT_AFTER_WORD_IN_LINE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString m_strWord;
	CString m_strInsertWhat;
	CString m_strDlgStatic;
};
