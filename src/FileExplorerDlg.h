/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "afxcmn.h"
#include "FileExplorerCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// Debugger Toolbar

class CExplorerToolBar : public CMFCToolBar
{
public:
	CExplorerToolBar() {};
	virtual ~CExplorerToolBar() {};
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}
	virtual BOOL AllowShowOnList() const { return FALSE; }
	virtual BOOL OnUserToolTip(CMFCToolBarButton* pButton, CString& strTTText) const;
};

// CFileExplorerDlg dialog

class CFileExplorerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileExplorerDlg)

public:
	CFileExplorerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFileExplorerDlg();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK() {};
	virtual void OnCancel() {};

	CFileExplorerCtrl& GetFileExplorerCtrl () { return m_FileExplorerCtrl; }
	void UpdateUIVisual();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FILE_EXPLORER };
#endif

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnInitDialog();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnGoBack();
	afx_msg void OnGoForward();
	afx_msg void OnRefresh();
	afx_msg void OnSearch();
	afx_msg void OnGoto();
	afx_msg void OnGetPath();
	afx_msg void OnBackToDesktop();
	afx_msg void OnDelete();
	afx_msg void OnBookmark();
	afx_msg void OnShowProperties();
	afx_msg void OnRename();

protected:
	CExplorerToolBar m_ExplorerToolBar;
	CFileExplorerCtrl m_FileExplorerCtrl;
	CString m_strRootPath;
	HICON m_hIcon;
};