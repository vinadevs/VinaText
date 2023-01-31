/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "ReopenFileWithPasswordDlg.h"
#include "afxdialogex.h"
#include "Cryptography.h"
#include "MainFrm.h"

// CReopenFileWithPasswordDlg dialog

IMPLEMENT_DYNAMIC(CReopenFileWithPasswordDlg, CDlgBase)

CReopenFileWithPasswordDlg::CReopenFileWithPasswordDlg(CString strFileSavePath, CWnd* pParent /*=NULL*/)
	: CDlgBase(IDD_OPEN_FILE_WITH_PASSWORD_DIALOG, pParent)
{
	m_strFileReopenPath = strFileSavePath;
}

CReopenFileWithPasswordDlg::~CReopenFileWithPasswordDlg()
{
}

void CReopenFileWithPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_KEY, m_EditUndoRedo);
}

void CReopenFileWithPasswordDlg::OnBnClickedOk()
{
	CDlgBase::OnOK();
	CString strPassWord;
	GetDlgItem(IDC_EDIT_KEY)->GetWindowTextW(strPassWord);

	if (strPassWord.IsEmpty())
	{
		AfxMessageBox(_T("[Error] Password is invalid!"));
		return;
	}

	CCryptographyIO oCngAes;
	BOOL bSHAMethod = TRUE;
	BOOL bEncrypt = FALSE;

	CString strFileToCrypt;
	strFileToCrypt.Format(_T("%s.Unlocked"), m_strFileReopenPath);

	if (oCngAes.CryptFile(bEncrypt, bSHAMethod, m_strFileReopenPath, strFileToCrypt, strPassWord))
	{
		AfxMessageBox(_T("Unlock file with password ****** succeeded!"), MB_ICONINFORMATION);
		CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
		ASSERT(pFrame);
		if (!pFrame) return;
		pFrame->RevealInExplorerWindow(strFileToCrypt);
	}
	else
	{
		AfxMessageBox(_T("[Error] Unlock file with password ****** failed!"));
		if (PathFileExists(strFileToCrypt))
		{
			::DeleteFileW(strFileToCrypt);
		}
	}
}

void CReopenFileWithPasswordDlg::OnBnClickedCancel()
{
	CDlgBase::OnCancel();
}

BOOL CReopenFileWithPasswordDlg::OnInitDialog()
{
	m_strDlgCaption = _T("Unlock File With Password...");

	CDlgBase::OnInitDialog();

	m_EditUndoRedo.SetCueBanner(_T("Password..."));

	SET_FOCUS_ON_CHILD_DLG_CONTROL(m_EditUndoRedo);

	return FALSE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CReopenFileWithPasswordDlg, CDlgBase)
	ON_BN_CLICKED(IDOK, &CReopenFileWithPasswordDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CReopenFileWithPasswordDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_SHOW_PASSWORD, &CReopenFileWithPasswordDlg::OnBnClickedCheckShowPassword)
END_MESSAGE_MAP()


// CReopenFileWithPasswordDlg message handlers


void CReopenFileWithPasswordDlg::OnBnClickedCheckShowPassword()
{
	// TODO: Add your control notification handler code here
	CButton* m_pCheckPassword = (CButton*)GetDlgItem(IDC_CHECK_SHOW_PASSWORD);
	if (m_pCheckPassword)
	{
		int ChkBoxState = m_pCheckPassword->GetCheck();
		if (ChkBoxState == BST_UNCHECKED)
		{
			m_EditUndoRedo.SetPasswordChar(0x25CF);
			m_EditUndoRedo.Invalidate();
		}
		else if (ChkBoxState == BST_CHECKED)
		{
			m_EditUndoRedo.SetPasswordChar(0);
			m_EditUndoRedo.Invalidate();
		}
	}
}
