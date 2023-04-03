/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "SaveFileWithPassWordDlg.h"
#include "afxdialogex.h"
#include "Cryptography.h"
#include "MainFrm.h"

// CSaveFileWithPassWordDlg dialog

IMPLEMENT_DYNAMIC(CSaveFileWithPassWordDlg, CDlgBase)

CSaveFileWithPassWordDlg::CSaveFileWithPassWordDlg(CString strFileSavePath, CWnd* pParent /*=NULL*/)
	: CDlgBase(IDD_SAVE_FILE_WITH_PASSWORD_DIALOG, pParent)
{
	m_strFileSavePath = strFileSavePath;
}

CSaveFileWithPassWordDlg::~CSaveFileWithPassWordDlg()
{
}

void CSaveFileWithPassWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_KEY, m_EditUndoRedo);
}

void CSaveFileWithPassWordDlg::OnBnClickedOk()
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
	BOOL bEncrypt = TRUE;

	CString strFileToCrypt;
	strFileToCrypt.Format(_T("%s.Locked"), m_strFileSavePath);

	if (oCngAes.CryptFile(bEncrypt, bSHAMethod, m_strFileSavePath, strFileToCrypt, strPassWord))
	{
		AfxMessageBox (_T("Lock file with password ****** succeeded!"), MB_ICONINFORMATION);
		CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
		ASSERT(pFrame);
		if (!pFrame) return;
		pFrame->RevealInExplorerWindow(strFileToCrypt);
	}
	else
	{
		AfxMessageBox(_T("[Error] Lock file with password ****** failed!"));
	}
}

void CSaveFileWithPassWordDlg::OnBnClickedCancel()
{
	CDlgBase::OnCancel();
}

BOOL CSaveFileWithPassWordDlg::OnInitDialog()
{
	m_strDlgCaption = _T("Lock File With Password...");

	CDlgBase::OnInitDialog();

	m_EditUndoRedo.SetCueBanner(_T("Password..."));

	SET_FOCUS_ON_CHILD_DLG_CONTROL(m_EditUndoRedo);

	return FALSE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CSaveFileWithPassWordDlg, CDlgBase)
	ON_BN_CLICKED(IDOK, &CSaveFileWithPassWordDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSaveFileWithPassWordDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_SHOW_PASSWORD, &CSaveFileWithPassWordDlg::OnBnClickedCheckShowPassword)
END_MESSAGE_MAP()


// CSaveFileWithPassWordDlg message handlers


void CSaveFileWithPassWordDlg::OnBnClickedCheckShowPassword()
{
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
