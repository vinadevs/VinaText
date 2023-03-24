/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "afxdialogex.h"
#include "QuickGotoLine.h"
#include "EditorDoc.h"
#include "Editor.h"
#include "AppUtil.h"

IMPLEMENT_DYNAMIC(QuickGotoLine, CDialogEx)

QuickGotoLine::QuickGotoLine(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GOTO_LINE, pParent) {}

BOOL QuickGotoLine::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor != NULL)
		{
			CString strLabelText = _T("Line Number (1 - ") + AppUtils::IntToCString(pEditor->GetLineCount()) + _T("):");
			GetDlgItem(IDC_STATIC_GOTO_LINE)->SetWindowTextW(strLabelText);
			GetDlgItem(IDC_EDIT_GOTO_LINE_NUMBER)->SetWindowTextW(AppUtils::IntToCString(pEditor->GetCurrentLine()));	
		}
	}
	UpdateData(FALSE);
	m_EditLine.SetFocusEx();
	return FALSE;
}

void QuickGotoLine::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_GOTO_LINE_NUMBER, m_EditLine);
}

BEGIN_MESSAGE_MAP(QuickGotoLine, CDialogEx)
	ON_BN_CLICKED(IDOK, &QuickGotoLine::OnBnClickedButtonGotoLine)
END_MESSAGE_MAP()

void QuickGotoLine::OnBnClickedButtonGotoLine()
{
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor != NULL)
		{
			CString strLineNumber;
			m_EditLine.GetWindowText(strLineNumber);
			pEditor->GotoLine(AppUtils::CStringToInt(strLineNumber));
			pEditor->SetFocus();
		}
	}
	CDialogEx::OnOK();
}
