/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "RemoveFromXToYDlg.h"
#include "afxdialogex.h"
#include "resource.h"

// CRemoveFromXToYDlg dialog

IMPLEMENT_DYNAMIC(CRemoveFromXToYDlg, CDlgBase)

CRemoveFromXToYDlg::CRemoveFromXToYDlg(CWnd* pParent /*=NULL*/)
	: CDlgBase(IDD_EDIT_REMOVE_FROM_X_TO_Y, pParent)
	, m_strFromX(_T(""))
	, m_strToY(_T(""))
	, m_bRemoveFromEndLine(FALSE)
{
}

CRemoveFromXToYDlg::~CRemoveFromXToYDlg()
{
}

void CRemoveFromXToYDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_REMOVE_FROM_X, m_EditUndoRedo);
	DDX_Control(pDX, IDC_EDIT_REMOVE_TO_Y, m_EditUndoRedo2);
	DDX_Text(pDX, IDC_EDIT_REMOVE_FROM_X, m_strFromX);
	DDX_Text(pDX, IDC_EDIT_REMOVE_TO_Y, m_strToY);
	DDX_Check(pDX, IDC_CHECK_REMOVE_FROM_END_LINE, m_bRemoveFromEndLine);
}

BOOL CRemoveFromXToYDlg::OnInitDialog()
{
	CDlgBase::OnInitDialog();
	SET_FOCUS_ON_CHILD_DLG_CONTROL(m_EditUndoRedo);
	return FALSE;
}

BEGIN_MESSAGE_MAP(CRemoveFromXToYDlg, CDlgBase)
END_MESSAGE_MAP()