/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "GammaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGammaDlg dialog
CGammaDlg::CGammaDlg(CWnd* pParent /*=NULL*/)
	: CDlgBase(CGammaDlg::IDD, pParent)
{
	m_gamma = 0.0f;
}

void CGammaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgBase::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GAMMA, m_gamma);
}

BOOL CGammaDlg::OnInitDialog()
{
	m_strDlgCaption = _T("Change Image Gamma");
	CDlgBase::OnInitDialog();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CGammaDlg, CDlgBase)
END_MESSAGE_MAP()
