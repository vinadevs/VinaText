/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "afxdialogex.h"
#include "UndoRedoEditControl.h"

class QuickGotoLine : public CDialogEx
{
	DECLARE_DYNAMIC(QuickGotoLine)

public:
	QuickGotoLine(CWnd* pParent = nullptr);   // standard constructor
	virtual ~QuickGotoLine() = default;
	virtual BOOL OnInitDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GOTO_LINE };
#endif

	afx_msg void OnBnClickedButtonGotoLine();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CUndoRedoEditControl m_EditLine;

	DECLARE_MESSAGE_MAP()
};
