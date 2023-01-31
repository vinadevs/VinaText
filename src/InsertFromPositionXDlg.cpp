/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "InsertFromPositionXDlg.h"
#include "afxdialogex.h"
#include "Resource.h"

// CInsertFromPositionXDlg dialog

IMPLEMENT_DYNAMIC(CInsertFromPositionXDlg, CDlgBase)

CInsertFromPositionXDlg::CInsertFromPositionXDlg(CWnd* pParent /*=NULL*/)
	: CDlgBase(IDD_EDIT_INSERT_AT_POSITION_X, pParent)
	, m_strPositionX(_T(""))
	, m_strInsertWhat(_T(""))
	, m_bInsertFromLineEnd(FALSE)
{
}

CInsertFromPositionXDlg::~CInsertFromPositionXDlg()
{
}

void CInsertFromPositionXDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INSERT_POSITION_X, m_EditUndoRedo);
	DDX_Control(pDX, IDC_EDIT_INSERT_WHAT, m_EditUndoRedo2);
	DDX_Text(pDX, IDC_EDIT_INSERT_POSITION_X, m_strPositionX);
	DDX_Text(pDX, IDC_EDIT_INSERT_WHAT, m_strInsertWhat);
	DDX_Check(pDX, IDC_CHECK_INSERT_FROM_END_LINE, m_bInsertFromLineEnd);
}

BOOL CInsertFromPositionXDlg::OnInitDialog()
{
	m_strDlgCaption = _T("Insert From Position In Line");

	CDlgBase::OnInitDialog();

	SET_FOCUS_ON_CHILD_DLG_CONTROL(m_EditUndoRedo);
	return FALSE;
}

BEGIN_MESSAGE_MAP(CInsertFromPositionXDlg, CDlgBase)
END_MESSAGE_MAP()

// CInsertFromPositionXDlg message handlers
