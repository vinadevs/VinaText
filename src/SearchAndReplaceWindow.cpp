/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "SearchAndReplaceWindow.h"
#include "Resource.h"

IMPLEMENT_DYNCREATE(CSearchAndReplaceWindow, CDockPaneBase)

BEGIN_MESSAGE_MAP(CSearchAndReplaceWindow, CDockPaneBase)
	ON_WM_SHOWWINDOW()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(UMW_DOCK_PANE_UPDATE, &CSearchAndReplaceWindow::OnDockPaneUpdate)
END_MESSAGE_MAP()

CSearchAndReplaceWindow::CSearchAndReplaceWindow() {}

CSearchAndReplaceWindow::~CSearchAndReplaceWindow() {}

void CSearchAndReplaceWindow::InitSearchReplaceFromEditor(const CString& strSearchWhat, SEARCH_REPLACE_GOTO_DLG_TYPE searchType)
{
	if (m_SearchAndReplaceWindowDlg.m_hWnd != NULL)
	{
		m_SearchAndReplaceWindowDlg.InitSearchReplaceFromEditor(strSearchWhat, searchType);
	}
}

void CSearchAndReplaceWindow::SearchAllOnFileFromEditor(const CString& strSearchWhat, SEARCH_REPLACE_GOTO_DLG_TYPE searchType)
{
	if (m_SearchAndReplaceWindowDlg.m_hWnd != NULL)
	{
		m_SearchAndReplaceWindowDlg.SearchAllOnFileFromEditor(strSearchWhat, searchType);
	}
}

void CSearchAndReplaceWindow::SearchFromEditor(const CString& strSearchWhat, SEARCH_TYPE searchType,
	BOOL bSeacrhNext, BOOL bHideMessageBox, BOOL bSaveSearchWord)
{
	if (m_SearchAndReplaceWindowDlg.m_hWnd != NULL)
	{
		m_SearchAndReplaceWindowDlg.SearchFromEditor(strSearchWhat, searchType, bSeacrhNext, bHideMessageBox, bSaveSearchWord);
	}
}

void CSearchAndReplaceWindow::InitSearchReplaceFromExplorer(const CString& strFolderPath, SEARCH_REPLACE_GOTO_DLG_TYPE searchType)
{
	if (m_SearchAndReplaceWindowDlg.m_hWnd != NULL)
	{
		m_SearchAndReplaceWindowDlg.InitSearchReplaceFromExplorer(strFolderPath, searchType);
	}
}

void CSearchAndReplaceWindow::UpdateFoldingMap(BOOL bActiveDialogTab)
{
	if (m_SearchAndReplaceWindowDlg.m_hWnd != NULL)
	{
		m_SearchAndReplaceWindowDlg.UpdateFoldingMap(bActiveDialogTab);
		m_SearchAndReplaceWindowDlg.UpdateGotoRange(FALSE);
	}
}

void CSearchAndReplaceWindow::SaveDialogState()
{
	m_SearchAndReplaceWindowDlg.SaveDialogState();
}

LRESULT CSearchAndReplaceWindow::OnDockPaneUpdate(WPARAM wParam, LPARAM lParam)
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

void CSearchAndReplaceWindow::UpdateUIVisual()
{
	m_SearchAndReplaceWindowDlg.UpdateUIVisual();
}

int CSearchAndReplaceWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockPaneBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_SearchAndReplaceWindowDlg.Create(IDD_SEARCH_AND_REPLACE_DIALOG_PANE, this);
	m_SearchAndReplaceWindowDlg.ShowWindow(SW_SHOW);

	AdjustLayout();

	return 0;
}

void CSearchAndReplaceWindow::OnSize(UINT nType, int cx, int cy)
{
	CDockPaneBase::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here and/or call default
	m_SearchAndReplaceWindowDlg.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CSearchAndReplaceWindow::ClearAll()
{
	m_SearchAndReplaceWindowDlg.ClearAll();
}

CString CSearchAndReplaceWindow::GetSearchWhat()
{
	return m_SearchAndReplaceWindowDlg.GetSearchWhat();
}

unsigned int CSearchAndReplaceWindow::GetSearchOption()
{
	return m_SearchAndReplaceWindowDlg.GetSearchOption();
}
