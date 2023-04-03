/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once
#include "afxwin.h"

// CRemoveAfterBeforeWordDlg dialog

#include "DialogBase.h"

class CRemoveAfterBeforeWordDlg : public CDlgBase
{
	DECLARE_DYNAMIC(CRemoveAfterBeforeWordDlg)

public:
	CRemoveAfterBeforeWordDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRemoveAfterBeforeWordDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REMOVE_AFTER_BEFORE_WORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString m_strWord;
	CString m_strDlgStatic;
};
