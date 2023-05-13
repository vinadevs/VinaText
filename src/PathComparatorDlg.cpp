/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "resource.h"
#include "afxdialogex.h"
#include "PathComparatorDlg.h"
#include "MainFrm.h"
#include "DiffEngine.h"
#include "PathUtil.h"
#include "VinaTextApp.h"
#include "WebDoc.h"

// CPathComparatorDlg dialog

IMPLEMENT_DYNAMIC(CPathComparatorDlg, CDialogEx)

CPathComparatorDlg::CPathComparatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PATH_COMPARATOR, pParent)
	, m_CheckDiffMatchCase(TRUE)
	, m_CheckDiffMatchIndentation(TRUE)
{
}

CPathComparatorDlg::~CPathComparatorDlg()
{
}

void CPathComparatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LEFT_SIDE_PATH_COMPARATOR, m_LeftSideEdit);
	DDX_Control(pDX, IDC_RIGHT_SIDE_PATH_COMPARATOR, m_RightSideEdit);
	DDX_Check(pDX, IDC_CHECK_DIFF_MATCH_CASE, m_CheckDiffMatchCase);
	DDX_Check(pDX, IDC_CHECK_DIFF_MATCH_INDENTATION, m_CheckDiffMatchIndentation);
}

BOOL CPathComparatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);
	m_LeftSideEdit.EnableFileBrowseButton();
	m_RightSideEdit.EnableFileBrowseButton();
	SET_FOCUS_ON_CHILD_DLG_CONTROL(m_LeftSideEdit);
	return FALSE;
}

void CPathComparatorDlg::PostNcDestroy()
{
	/*Close & Delete a modeless Dialogs.
	A proper Way is : Override PostNcDestroy, OnOk() and OnCancel() for the Modeless Dialogs*/
	CDialogEx::PostNcDestroy();
	delete this;
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;
	pFrame->ReleasePathComparatorToolDialog();
}

void CPathComparatorDlg::OnCancel()
{
	CDialogEx::DestroyWindow();
}

BEGIN_MESSAGE_MAP(CPathComparatorDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPathComparatorDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CPathComparatorDlg message handlers

void CPathComparatorDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	CFileOptions options;
	if (!m_CheckDiffMatchCase) options.SetOption(CString("case"), CString("no"));
	if (!m_CheckDiffMatchIndentation) options.SetOption(CString("indent"), CString("no"));
	CString strLeftPath;
	m_LeftSideEdit.GetWindowText(strLeftPath);
	CString strRightPath;
	m_RightSideEdit.GetWindowText(strRightPath);
	// make sure those files exist
	if (!PathFileExists(strLeftPath))
	{
		TCHAR szError[MAX_PATH];
		wsprintf(szError, _T("[Left Path Error] %s does not exist."), strLeftPath.GetBuffer(0));
		AfxMessageBox(szError);
		return;
	}

	if (!PathFileExists(strRightPath))
	{
		TCHAR szError[MAX_PATH];
		wsprintf(szError, _T("[Right Path Error] %s does not exist."), strRightPath.GetBuffer(0));
		AfxMessageBox(szError);
		return;
	}
	if (!DoDiff(strLeftPath, strRightPath, options))
	{
		AfxMessageBox(_T("[Compare Error] operation was failed!"));
	}
	else
	{
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [Compare Path] Diff process finished, generating result..."));
	}
}

BOOL CPathComparatorDlg::DoDiff(CString& strLeftPath, CString& strRightPath, CFileOptions& options)
{
	CFilePartition f1;
	CFilePartition f2;
	BOOL bFile1IsAFolder = PathUtils::IsDirectory(strLeftPath);
	BOOL bFile2IsAFolder = PathUtils::IsDirectory(strRightPath);
	if (bFile1IsAFolder && bFile2IsAFolder)
	{
		// process folders
		f1.PreProcessFolder(strLeftPath, options);
		f2.PreProcessFolder(strRightPath, options);
	}
	else if (!bFile1IsAFolder && !bFile2IsAFolder)
	{
		// process files
		f1.PreProcess(strLeftPath, options);
		f2.PreProcess(strRightPath, options);
	}
	else
	{
		// error (folder and a file cannot match, anyway)
		TCHAR szError[MAX_PATH];
		wsprintf(szError, _T("[Invalid Pair] %s cannot be compared with %s."), strLeftPath.GetBuffer(0), strRightPath.GetBuffer(0));
		AfxMessageBox(szError);
		return FALSE;
	}
	CFilePartition leftSideFPBis, rightSideFPBis;
	CDiffEngine dE;
	dE.Diff(f1, f2, leftSideFPBis, rightSideFPBis);
	// open with the default browser
	CWebDoc* pDoc = dynamic_cast<CWebDoc*>(AppUtils::GetVinaTextApp()->CreateWebDocument());
	if (!pDoc) return FALSE;
	pDoc->SetTitle(_T("Path Compare Result"));
	HRESULT hr = pDoc->LoadHTMLContent(dE.Serialize(leftSideFPBis, rightSideFPBis));
	if (hr == E_FAIL || hr == E_NOINTERFACE)
	{
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [Compare Path] HTML error, can not render the content..."));
		return FALSE;
	}
	strLeftPath.ReleaseBuffer();
	strRightPath.ReleaseBuffer();
	return TRUE;
}