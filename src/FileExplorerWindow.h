/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "DockPaneBase.h"
#include "FileExplorerDlg.h"

class CFileExplorerWindow : public CDockPaneBase
{
public:
	DECLARE_DYNCREATE(CFileExplorerWindow)
	CFileExplorerWindow();
	virtual ~CFileExplorerWindow();
	virtual void UpdateUIVisual();

	CFileExplorerCtrl& GetFileExplorerCtrl() { return m_CFileExplorerDlg.GetFileExplorerCtrl(); }

protected:
	// DockWnd Update Message
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd * pOldWnd);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg LRESULT OnDockPaneUpdate(WPARAM wParam, LPARAM lParam);
	CFileExplorerDlg m_CFileExplorerDlg;
};

