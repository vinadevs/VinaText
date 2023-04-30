/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "resource.h"
#include "InsertBetweenLines.h"
#include "afxdialogex.h"

// CInsertBetweenLines dialog

IMPLEMENT_DYNAMIC(CInsertBetweenLines, CDlgBase)

CInsertBetweenLines::CInsertBetweenLines(CWnd* pParent /*=NULL*/)
	: CDlgBase(IDD_EDIT_INSERT_BETWEEN_LINES, pParent)
	, m_strInsertWhat(_T(""))
	, m_bInsertTopMost(FALSE)
	, m_bInsertBottomMost(FALSE)
{
}

CInsertBetweenLines::~CInsertBetweenLines()
{
}

void CInsertBetweenLines::DoDataExchange(CDataExchange* pDX)
{
	CDlgBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INSERT_WHAT, m_EditUndoRedo);
	DDX_Text(pDX, IDC_EDIT_INSERT_WHAT, m_strInsertWhat);
	DDX_Check(pDX, IDC_CHECK_INSERT_MOST_TOP, m_bInsertTopMost);
	DDX_Check(pDX, IDC_CHECK_INSERT_MOST_BOTTOM, m_bInsertBottomMost);
}

BOOL CInsertBetweenLines::OnInitDialog()
{
	m_strDlgCaption = _T("Insert Word Between Lines");

	CDlgBase::OnInitDialog();

	SET_FOCUS_ON_CHILD_DLG_CONTROL(m_EditUndoRedo);
	return FALSE;
}

BEGIN_MESSAGE_MAP(CInsertBetweenLines, CDialogEx)
END_MESSAGE_MAP()

// CInsertBetweenLines message handlers
