/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "InsertAfterWordInLineDlg.h"
#include "afxdialogex.h"
#include "Resource.h"

// CInsertAfterWordInLineDlg dialog

IMPLEMENT_DYNAMIC(CInsertAfterWordInLineDlg, CDlgBase)

CInsertAfterWordInLineDlg::CInsertAfterWordInLineDlg(CWnd* pParent /*=NULL*/)
	: CDlgBase(IDD_EDIT_INSERT_AFTER_WORD_IN_LINE, pParent)
	, m_strWord(_T(""))
	, m_strInsertWhat(_T(""))
{
}

CInsertAfterWordInLineDlg::~CInsertAfterWordInLineDlg()
{
}

void CInsertAfterWordInLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INSERT_AFTER_WORD, m_EditUndoRedo);
	DDX_Control(pDX, IDC_EDIT_INSERT_WHAT, m_EditUndoRedo2);
	DDX_Text(pDX, IDC_EDIT_INSERT_AFTER_WORD, m_strWord);
	DDX_Text(pDX, IDC_EDIT_INSERT_WHAT, m_strInsertWhat);
}

BOOL CInsertAfterWordInLineDlg::OnInitDialog()
{
	m_strDlgCaption = _T("Insert After Word In Line");

	CDlgBase::OnInitDialog();

	GetDlgItem(IDC_STATIC_TARGET_WORD)->SetWindowTextW(m_strDlgStatic);

	SET_FOCUS_ON_CHILD_DLG_CONTROL(m_EditUndoRedo);
	return FALSE;
}

BEGIN_MESSAGE_MAP(CInsertAfterWordInLineDlg, CDlgBase)
END_MESSAGE_MAP()

// CInsertAfterWordInLineDlg message handlers
