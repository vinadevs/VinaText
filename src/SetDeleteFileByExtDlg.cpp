/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "SetDeleteFileByExtDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif //#ifdef _DEBUG

#pragma warning(suppress: 26455)
CDeleteFileExtensionDlg::CDeleteFileExtensionDlg(CWnd* pParent)
	: CDlgBase(CDeleteFileExtensionDlg::IDD, pParent)
{
}

void CDeleteFileExtensionDlg::DoDataExchange(CDataExchange* pDX)
{
	//Let the base class do its thing
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PATH, m_EditPath);
	DDX_Control(pDX, IDC_EXTENSION_INPUT, m_EditUndoRedo2);
	DDX_Text(pDX, IDC_PATH, m_sPath);
	DDX_Text(pDX, IDC_EXTENSION_INPUT, m_sExt);
}

BOOL CDeleteFileExtensionDlg::OnInitDialog()
{
	m_strDlgCaption = _T("Send File In Folder To Recycle Bin...");

	CDlgBase::OnInitDialog();

	// enable the browse button and put the control in file browse mode
	m_EditPath.EnableFolderBrowseButton();

	return TRUE;
}

void CDeleteFileExtensionDlg::OnFilterEditChange()
{
	CString strSearchFilter;
	m_EditUndoRedo2.GetWindowText(strSearchFilter);
	if (strSearchFilter.IsEmpty())
	{
		m_EditUndoRedo2.SetWindowText(_T("*.*;"));
		m_EditUndoRedo2.SetFocusEx();
	}
}

void CDeleteFileExtensionDlg::OnBnClickedOk()
{
	if (IDYES == AfxMessageBox(_T("Are you sure want to delete it?"), MB_YESNO | MB_ICONWARNING))
	{
		CDlgBase::OnOK();
	}
}

#pragma warning(suppress: 26433 26440)
BEGIN_MESSAGE_MAP(CDeleteFileExtensionDlg, CDlgBase)
	ON_EN_CHANGE(IDC_EXTENSION_INPUT, OnFilterEditChange)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()
