/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "FileExplorerWindow.h"
#include "Resource.h"

IMPLEMENT_DYNCREATE(CFileExplorerWindow, CDockPaneBase)

BEGIN_MESSAGE_MAP(CFileExplorerWindow, CDockPaneBase)
	ON_WM_SHOWWINDOW()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_CONTEXTMENU()
	ON_MESSAGE(UMW_DOCK_PANE_UPDATE, &CFileExplorerWindow::OnDockPaneUpdate)
END_MESSAGE_MAP()

CFileExplorerWindow::CFileExplorerWindow()
{
	// CFileExplorerWindow constructor
}

CFileExplorerWindow::~CFileExplorerWindow()
{
	// CFileExplorerWindow destructor
}

int CFileExplorerWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockPaneBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_CFileExplorerDlg.Create(IDD_DIALOG_FILE_EXPLORER, this);
	m_CFileExplorerDlg.ShowWindow(SW_SHOW);

	AdjustLayout();

	return 0;
}

void CFileExplorerWindow::OnSize(UINT nType, int cx, int cy)
{
	CDockPaneBase::OnSize(nType, cx, cy);
	m_CFileExplorerDlg.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFileExplorerWindow::OnSetFocus(CWnd* pOldWnd)
{
	__super::OnSetFocus(pOldWnd);
	m_CFileExplorerDlg.SetFocus();
}

void CFileExplorerWindow::OnContextMenu(CWnd * pWnd, CPoint point)
{
	return; // disable dockpane menu
}

LRESULT CFileExplorerWindow::OnDockPaneUpdate(WPARAM wParam, LPARAM lParam)
{
	WORD wMsgTarget = LOWORD(wParam);
	WORD wMsgHint = HIWORD(wParam);

	if (MAIN_FRAME_UPDATE_MSG::MAIN_FRAME_UPDATE_ALL_DOCKPANE == wMsgTarget)
	{
		switch (wMsgHint)
		{
		case MAIN_FRAME_UPDATE_HINT::MAIN_FRAME_UPDATE_HINT_SETTING_CHANGED:
		{
			UpdateUIVisual();
		}
		break;
		}
	}
	return 0L;
}

void CFileExplorerWindow::UpdateUIVisual()
{
	m_CFileExplorerDlg.UpdateUIVisual();
}