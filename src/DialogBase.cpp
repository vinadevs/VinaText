/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "DialogBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif //#ifdef _DEBUG

#pragma warning(suppress: 26455)

CDlgBase::CDlgBase(UINT nIDTemplate, CWnd * pParent)
	: CDialogEx(nIDTemplate, pParent)
{
}

BEGIN_MESSAGE_MAP(CDlgBase, CDialogEx)
END_MESSAGE_MAP()

BOOL CDlgBase::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);

	SetWindowText(m_strDlgCaption);

	return TRUE;
}
