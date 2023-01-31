/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "SetBookmarkPathDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif //#ifdef _DEBUG

#pragma warning(suppress: 26455)
CSetPathDlg::CSetPathDlg(CWnd* pParent) 
	: CDlgBase(CSetPathDlg::IDD, pParent)
{
}

void CSetPathDlg::DoDataExchange(CDataExchange* pDX)
{
  //Let the base class do its thing
  __super::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_FOLDER, m_EditPath);
  DDX_Text(pDX, IDC_FOLDER, m_sPath);
}

BOOL CSetPathDlg::OnInitDialog()
{
	CDlgBase::OnInitDialog();

	// enable the browse button and put the control in file browse mode
	m_EditPath.EnableFileBrowseButton();

	SET_FOCUS_ON_CHILD_DLG_CONTROL(m_EditPath);

	return FALSE;
}

#pragma warning(suppress: 26433 26440)
BEGIN_MESSAGE_MAP(CSetPathDlg, CDlgBase) 
END_MESSAGE_MAP()
