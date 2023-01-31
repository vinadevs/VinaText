/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "EditWithXDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(suppress: 26455)
CEditWithXDlg::CEditWithXDlg(CWnd* pParent) 
	: CDlgBase(CEditWithXDlg::IDD, pParent)
{
}

void CEditWithXDlg::DoDataExchange(CDataExchange* pDX)
{
	//Let the base class do its thing
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_X_INPUT, m_EditUndoRedo);
	DDX_Text(pDX, IDC_X_INPUT, m_sXInput);
}

BOOL CEditWithXDlg::OnInitDialog()
{
	CDlgBase::OnInitDialog();
	SET_FOCUS_ON_CHILD_DLG_CONTROL(m_EditUndoRedo);
	return FALSE;
}

#pragma warning(suppress: 26433 26440)
BEGIN_MESSAGE_MAP(CEditWithXDlg, CDlgBase) 
END_MESSAGE_MAP()
