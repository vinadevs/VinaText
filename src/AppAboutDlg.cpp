/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "AppAboutDlg.h"

CAppAboutDlg::CAppAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAppAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CAppAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	auto hCalc = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hCalc, TRUE);
	return TRUE;
}

BEGIN_MESSAGE_MAP(CAppAboutDlg, CDialogEx)
END_MESSAGE_MAP()