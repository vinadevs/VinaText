/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "FileExplorerDlg.h"
#include "AppUtil.h"
#include "RAIIUtils.h"
#include "VinaTextApp.h"
#include "MainFrm.h"
#include "EditorDoc.h"
#include "AppSettings.h"

#ifndef TVS_EX_DOUBLEBUFFER
#define TVS_EX_DOUBLEBUFFER 0x0004
#endif //#ifndef TVS_EX_DOUBLEBUFFER

#ifndef TVS_EX_AUTOHSCROLL
#define TVS_EX_AUTOHSCROLL 0x0020
#endif //#ifndef TVS_EX_AUTOHSCROLL

#ifndef TVS_EX_FADEINOUTEXPANDOS
#define TVS_EX_FADEINOUTEXPANDOS 0x0040
#endif //#ifndef TVS_EX_FADEINOUTEXPANDOS

#ifndef TVM_SETEXTENDEDSTYLE
#define TVM_SETEXTENDEDSTYLE (TV_FIRST + 44)
#endif //#ifndef TVM_SETEXTENDEDSTYLE

// CFileExplorerDlg dialog

#pragma warning(suppress: 26409 26440 26433 26477)
IMPLEMENT_DYNAMIC(CFileExplorerDlg, CDialogEx)

CFileExplorerDlg::CFileExplorerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_FILE_EXPLORER, pParent), m_strRootPath(_T("C:\\"))
{
}

CFileExplorerDlg::~CFileExplorerDlg()
{
}

void CFileExplorerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILE_EXPLODER_CTRL, m_FileExplorerCtrl);
	DDX_FileTreeValue(pDX, m_FileExplorerCtrl, m_strRootPath);
}

#pragma warning(suppress: 26433 26440)
BEGIN_MESSAGE_MAP(CFileExplorerDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_EXPLORER_TB_GO_BACK, &CFileExplorerDlg::OnGoBack)
	ON_COMMAND(ID_EXPLORER_TB_GO_FORWARD, &CFileExplorerDlg::OnGoForward)
	ON_COMMAND(ID_EXPLORER_TB_REFRESH, &CFileExplorerDlg::OnRefresh)
	ON_COMMAND(ID_EXPLORER_TB_SEARCH_FILE, &CFileExplorerDlg::OnSearch)
	ON_COMMAND(ID_EXPLORER_TB_GOTO_PATH, &CFileExplorerDlg::OnGoto)
	ON_COMMAND(ID_EXPLORER_TB_GET_PATH_STRING, &CFileExplorerDlg::OnGetPath)
	ON_COMMAND(ID_EXPLORER_TB_BACK_TO_DESKTOP, &CFileExplorerDlg::OnBackToDesktop)
	ON_COMMAND(ID_EXPLORER_TB_DELETE, &CFileExplorerDlg::OnDelete)
	ON_COMMAND(ID_EXPLORER_TB_BOOKMARK_PATH, &CFileExplorerDlg::OnBookmark)
	ON_COMMAND(ID_EXPLORER_TB_PRINT_FILE, &CFileExplorerDlg::OnPrint)
	ON_COMMAND(ID_EXPLORER_TB_RENAME, &CFileExplorerDlg::OnRename)
END_MESSAGE_MAP()

// CFileExplorerDlg message handlers

void CFileExplorerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CLockCtrlRedraw locker(this);
	if (m_ExplorerToolBar.GetSafeHwnd())
	{
		CSize sizeToolbar = m_ExplorerToolBar.CalcFixedLayout(FALSE, TRUE);
		CRect rectClient;
		GetClientRect(rectClient);
		m_ExplorerToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), sizeToolbar.cy, SWP_NOACTIVATE | SWP_NOZORDER);
		if (m_FileExplorerCtrl.GetSafeHwnd())
		{
			m_FileExplorerCtrl.MoveWindow(0, sizeToolbar.cy, cx, cy - sizeToolbar.cy);
		}
	}
}

BOOL CFileExplorerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// init control
	m_FileExplorerCtrl.SendMessage(TVM_SETEXTENDEDSTYLE, 0, TVS_EX_DOUBLEBUFFER);
	m_FileExplorerCtrl.PopulateTree();
	UpdateUIVisual();
	m_FileExplorerCtrl.EnableToolTips(TRUE);
	if (AppSettingMgr.m_bUseWin10ExplorerStyle)
	{
		SetWindowTheme(m_FileExplorerCtrl, L"Explorer", NULL);
	}
	// load previous data
	CWinApp* pApp = AfxGetApp();
#pragma warning(suppress: 26496)
	AFXASSUME(pApp != NULL);
	if (!pApp) return FALSE;
	CString sRootFolder = pApp->GetProfileString(_T("Settings"), _T("Root Folder"), _T(""));
	if (!sRootFolder.IsEmpty())
	{
		m_FileExplorerCtrl.SetRootFolder(sRootFolder);
		const int nAddedFolderSize = pApp->GetProfileInt(_T("Settings"), _T("Added Folder Size"), 1);
		for (int i = 0; i < nAddedFolderSize; ++i)
		{
			CString sProfileString = _T("Added Folder %d");
			sProfileString.Format(sProfileString, i);
			CString sPath = pApp->GetProfileString(_T("Settings"), sProfileString, _T(""));
			if (sRootFolder != sPath)
			{
				m_FileExplorerCtrl.AddPath(sPath, false, true);
			}
		}
	}
	else
	{
		CString sSelPath = pApp->GetProfileString(_T("Settings"), _T("Last Path"), _T("C:\\"));
		const BOOL bExpanded = pApp->GetProfileInt(_T("Settings"), _T("Expanded"), FALSE);
		m_FileExplorerCtrl.SetSelectedPath(sSelPath, bExpanded);
	}

	// create toolbar
	BOOL retTB = m_ExplorerToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER_TOOLBAR_24);
	retTB = m_ExplorerToolBar.LoadToolBar(IDR_EXPLORER_TOOLBAR_24, 0, 0, TRUE /* Is locked */);
	if (!retTB)
	{
		TRACE0("Failed to create toolbar windows\n");
		return FALSE;      // fail to create
	}
	m_ExplorerToolBar.CleanUpLockedImages();
	m_ExplorerToolBar.LoadBitmap(IDR_EXPLORER_TOOLBAR_24, 0, 0, TRUE /* Locked */);
	m_ExplorerToolBar.SetPaneStyle(m_ExplorerToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_ExplorerToolBar.SetPaneStyle(m_ExplorerToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_ExplorerToolBar.SetOwner(this);
	m_ExplorerToolBar.SetRouteCommandsViaFrame(FALSE);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control 
}

void CFileExplorerDlg::UpdateUIVisual()
{
	m_FileExplorerCtrl.SetTextColor(IS_LIGHT_THEME ? BasicColors::black : BasicColors::white);
	m_FileExplorerCtrl.SetBkColor(AppSettingMgr.m_AppThemeColor);
}

#pragma warning(suppress: 26434)
void CFileExplorerDlg::OnSetFocus(CWnd* pOldWnd)
{
	__super::OnSetFocus(pOldWnd);
	m_FileExplorerCtrl.SetFocus();
}

void CFileExplorerDlg::OnGoBack()
{
	m_FileExplorerCtrl.OnBack();
}

void CFileExplorerDlg::OnGoForward()
{
	m_FileExplorerCtrl.OnForward();
}

void CFileExplorerDlg::OnRefresh()
{
	m_FileExplorerCtrl.OnRefresh();
}

void CFileExplorerDlg::OnSearch()
{
	m_FileExplorerCtrl.OnOptionsEditSearchFiles();
}

void CFileExplorerDlg::OnGoto()
{
	m_FileExplorerCtrl.OnJumpToPath();
}

void CFileExplorerDlg::OnGetPath()
{
	m_FileExplorerCtrl.OnGetFullPath();
}

void CFileExplorerDlg::OnBackToDesktop()
{
	m_FileExplorerCtrl.OnBackToOriginalExplorer();
}

void CFileExplorerDlg::OnDelete()
{
	m_FileExplorerCtrl.OnDelete();
}

void CFileExplorerDlg::OnBookmark()
{
	m_FileExplorerCtrl.OnBookMarkPath();
}

void CFileExplorerDlg::OnPrint()
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame); if (!pFrame) return;
	pFrame->OnPrintFileSetupDlg();
}

void CFileExplorerDlg::OnRename()
{
	m_FileExplorerCtrl.OnRename();
}

/////////////////////////////////////////////////////////////////////////////
// Debugger Toolbar

BOOL CExplorerToolBar::OnUserToolTip(CMFCToolBarButton * pButton, CString & strTTText) const
{
	if (pButton->m_nID == ID_EXPLORER_TB_GO_BACK)
		strTTText = _T("Goto Previous Selected Path");
	else if (pButton->m_nID == ID_EXPLORER_TB_GO_FORWARD)
		strTTText = _T("Goto Next Selected Path");
	else if (pButton->m_nID == ID_EXPLORER_TB_REFRESH)
		strTTText = _T("Refresh Explorer");
	else if (pButton->m_nID == ID_EXPLORER_TB_SEARCH_FILE)
		strTTText = _T("Search/Navigate At Path");
	else if (pButton->m_nID == ID_EXPLORER_TB_BACK_TO_DESKTOP)
		strTTText = _T("Back To Desktop");
	else if (pButton->m_nID == ID_EXPLORER_TB_DELETE)
		strTTText = _T("Delete Selected Path");
	else if (pButton->m_nID == ID_EXPLORER_TB_BOOKMARK_PATH)
		strTTText = _T("Bookmark Selected Path");
	else if (pButton->m_nID == ID_EXPLORER_TB_GET_PATH_STRING)
		strTTText = _T("Get Selected Path String");
	else if (pButton->m_nID == ID_EXPLORER_TB_PRINT_FILE)
		strTTText = _T("Print Selected Path");
	else if (pButton->m_nID == ID_EXPLORER_TB_RENAME)
		strTTText = _T("Rename Selected Path");
	else if (pButton->m_nID == ID_EXPLORER_TB_GOTO_PATH)
		strTTText = _T("Goto Any Path");
	return TRUE;
}