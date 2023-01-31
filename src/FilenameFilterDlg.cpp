/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "FilenameFilterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(suppress: 26455)
CFileExtensionFilterDlg::CFileExtensionFilterDlg(CWnd* pParent) 
	: CDlgBase(CFileExtensionFilterDlg::IDD, pParent)
{
}

void CFileExtensionFilterDlg::DoDataExchange(CDataExchange* pDX)
{
  //Let the base class do its thing
  __super::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_MASK, m_EditUndoRedo);
  DDX_Text(pDX, IDC_MASK, m_sMask);
}

BOOL CFileExtensionFilterDlg::OnInitDialog()
{
	m_strDlgCaption = _T("Display file extensions only");
	CDlgBase::OnInitDialog();
	SET_FOCUS_ON_CHILD_DLG_CONTROL(m_EditUndoRedo);
	return FALSE;
}

#pragma warning(suppress: 26433 26440)
BEGIN_MESSAGE_MAP(CFileExtensionFilterDlg, CDlgBase)
	ON_EN_CHANGE(IDC_MASK, OnFilterEditChange)
END_MESSAGE_MAP()

void CFileExtensionFilterDlg::OnFilterEditChange()
{
	CString strSearchFilter;
	m_EditUndoRedo.GetWindowText(strSearchFilter);
	if (strSearchFilter.IsEmpty())
	{
		m_EditUndoRedo.SetWindowText(_T("*.*;"));
		m_EditUndoRedo.SetFocusEx();
	}
}