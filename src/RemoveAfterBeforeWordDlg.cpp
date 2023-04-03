/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "RemoveAfterBeforeWordDlg.h"
#include "afxdialogex.h"
#include "resource.h"

// CRemoveAfterBeforeWordDlg dialog

IMPLEMENT_DYNAMIC(CRemoveAfterBeforeWordDlg, CDlgBase)

CRemoveAfterBeforeWordDlg::CRemoveAfterBeforeWordDlg(CWnd* pParent /*=NULL*/)
	: CDlgBase(IDD_DIALOG_REMOVE_AFTER_BEFORE_WORD, pParent)
	, m_strWord(_T(""))
{
}

CRemoveAfterBeforeWordDlg::~CRemoveAfterBeforeWordDlg()
{
}

void CRemoveAfterBeforeWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TARGET_WORD, m_EditUndoRedo);
	DDX_Text(pDX, IDC_EDIT_TARGET_WORD, m_strWord);
}

BOOL CRemoveAfterBeforeWordDlg::OnInitDialog()
{
	CDlgBase::OnInitDialog();

	GetDlgItem(IDC_STATIC_TARGET_WORD)->SetWindowTextW(m_strDlgStatic);

	SET_FOCUS_ON_CHILD_DLG_CONTROL(m_EditUndoRedo);
	return FALSE;
}

BEGIN_MESSAGE_MAP(CRemoveAfterBeforeWordDlg, CDlgBase)
END_MESSAGE_MAP()

// CRemoveAfterBeforeWordDlg message handlers
