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
#include "ExplorerSettingDlg.h"
#include "AppSettings.h"
#include "PathUtil.h"
#include "ScrollHelper.h"

// ExplorerSettingDlg dialog

IMPLEMENT_DYNAMIC(ExplorerSettingDlg, CDialogEx)

ExplorerSettingDlg::ExplorerSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING_EXPLORER, pParent) {
	m_pScrollHelper = std::make_unique<CScrollHelper>();
	m_pScrollHelper->AttachWnd(this);
	m_pScrollHelper->SetDisplaySize(0, 1500);
}

ExplorerSettingDlg::~ExplorerSettingDlg() {}

void ExplorerSettingDlg::UpdateGUISettings(BOOL bFromGUI)
{
	if (bFromGUI)
	{
		UpdateData(TRUE);
		AppSettingMgr.m_bEnablePathNavigation = m_bEnablePathNavigation;
		AppSettingMgr.m_bEnablePreviewFile = m_bEnablePreviewFile;
		AppSettingMgr.m_bHideAllTargetFileSystem = m_bHideAllTargetFileSystem;
		AppSettingMgr.m_bRevealExplorerWhenDlbClkFile = m_bRevealExplorerWhenDlbClkFile;
		AppSettingMgr.m_bRevealExplorerWhenSwitchFile = m_bRevealExplorerWhenSwitchFile;
		AppSettingMgr.m_bUseWin10ExplorerStyle = m_bUseWin10ExplorerStyle;
		AppSettingMgr.m_nExplorerExpandLimitFileOpen = m_nExplorerExpandLimitFileOpen;
		AppSettingMgr.m_nExplorerExpandLimitLevel = m_nExplorerExpandLimitLevel;
		AppSettingMgr.m_nFilePreviewSizeLimit = m_nFilePreviewSizeLimit;
		AppSettingMgr.m_strAntiVirusArgument = m_strAntiVirusArgument;
		AppSettingMgr.m_strAntiVirusProgram = m_strAntiVirusProgram;
	}
	else
	{
		m_bEnablePathNavigation = AppSettingMgr.m_bEnablePathNavigation;
		m_bEnablePreviewFile = AppSettingMgr.m_bEnablePreviewFile;
		m_bHideAllTargetFileSystem = AppSettingMgr.m_bHideAllTargetFileSystem;
		m_bRevealExplorerWhenDlbClkFile = AppSettingMgr.m_bRevealExplorerWhenDlbClkFile;
		m_bRevealExplorerWhenSwitchFile = AppSettingMgr.m_bRevealExplorerWhenSwitchFile;
		m_bUseWin10ExplorerStyle = AppSettingMgr.m_bUseWin10ExplorerStyle;
		m_nExplorerExpandLimitFileOpen = AppSettingMgr.m_nExplorerExpandLimitFileOpen;
		m_nExplorerExpandLimitLevel = AppSettingMgr.m_nExplorerExpandLimitLevel;
		m_nFilePreviewSizeLimit = AppSettingMgr.m_nFilePreviewSizeLimit;
		m_strAntiVirusArgument = AppSettingMgr.m_strAntiVirusArgument;
		m_strAntiVirusProgram = AppSettingMgr.m_strAntiVirusProgram;
	}
}

BOOL ExplorerSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_EditAntiVirusProgram.EnableFileBrowseButton();

	UpdateGUISettings(FALSE);

	UpdateData(FALSE);

	return TRUE;
}

BOOL ExplorerSettingDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			GetParent()->GetParent()->SendMessage(WM_CLOSE, 0, 0);
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void ExplorerSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, ID_ENABLE_PATH_NAVIGATION, m_bEnablePathNavigation);
	DDX_Check(pDX, ID_ENABLE_PREVIEW_FILE, m_bEnablePreviewFile);
	DDX_Check(pDX, ID_HIDE_ALL_TARGET_FILE_SYSTEM, m_bHideAllTargetFileSystem);
	DDX_Check(pDX, ID_REVEAL_EXPLORER_WHEN_DLB_CLK_FILE, m_bRevealExplorerWhenDlbClkFile);
	DDX_Check(pDX, ID_REVEAL_EXPLORER_WHEN_SWITCH_FILE, m_bRevealExplorerWhenSwitchFile);
	DDX_Check(pDX, ID_USE_WIN10_EXPLORER_STYLE, m_bUseWin10ExplorerStyle);
	DDX_Text(pDX, ID_EXPLORER_EXPAND_LIMIT_FILE_OPEN_EDIT, m_nExplorerExpandLimitFileOpen);
	DDX_Text(pDX, ID_EXPLORER_EXPAND_LIMIT_LEVEL_EDIT, m_nExplorerExpandLimitLevel);
	DDX_Text(pDX, ID_FILE_PREVIEW_SIZE_LIMIT_EDIT, m_nFilePreviewSizeLimit);
	DDX_Control(pDX, ID_ANTI_VIRUS_PROGRAM_EDIT, m_EditAntiVirusProgram);
	DDX_Text(pDX, ID_ANTI_VIRUS_ARGUMENT_EDIT, m_strAntiVirusArgument);
	DDX_Text(pDX, ID_ANTI_VIRUS_PROGRAM_EDIT, m_strAntiVirusProgram);
}

void ExplorerSettingDlg::OnDropFiles(HDROP hDropInfo)
{
	CDialogEx::OnDropFiles(hDropInfo);
	int nCntFiles = DragQueryFile(hDropInfo, -1, 0, 0);
	if (nCntFiles == 1)
	{
		CEdit* pEdit = dynamic_cast<CEdit*>(FromHandle(m_hWndChildDropFile));
		if (pEdit)
		{
			TCHAR szPath[_MAX_PATH];
			szPath[0] = 0;
			::DragQueryFile(hDropInfo, 0, szPath, _MAX_PATH);
			if (m_hWndChildDropFile == m_EditAntiVirusProgram.m_hWnd)
			{
				if (PathUtils::IsDirectory(szPath))
				{
					AfxMessageBox(_T("[Error] This setting requires an execution file, not folder!"));
				}
				else
				{
					pEdit->SetWindowTextW(szPath);
				}
			}
		}
	}
	DragFinish(hDropInfo);
}

BEGIN_MESSAGE_MAP(ExplorerSettingDlg, CDialogEx)
	ON_WM_DROPFILES()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// for scrolling //////////////////////////////////////////////////////////////

void ExplorerSettingDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pScrollHelper->OnHScroll(nSBCode, nPos, pScrollBar);
}

void ExplorerSettingDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pScrollHelper->OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL ExplorerSettingDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	BOOL wasScrolled = m_pScrollHelper->OnMouseWheel(nFlags, zDelta, pt);

	return wasScrolled;
}

void ExplorerSettingDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_pScrollHelper->OnSize(nType, cx, cy);
}

///////////////////////////////////////////////////////////////////

BOOL ExplorerSettingBrowse::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_DROPFILES)
	{
		ExplorerSettingDlg* pParent = dynamic_cast<ExplorerSettingDlg*>(GetParent());
		if (pParent)
		{
			pParent->m_hWndChildDropFile = this->m_hWnd;
			pParent->SendMessage(WM_DROPFILES, pMsg->wParam, pMsg->lParam);
			return TRUE; // got it
		}
	}
	return FALSE; // allow default processing
}
