/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "DockPaneBase.h"
#include "Editor.h"
#include "UndoRedoEditControl.h"

/////////////////////////////////////////////////////////////////////////////
// CRichEditCtrlEX

class CRichEditCtrlEX : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CRichEditCtrlEX)
// Construction
public:
	CRichEditCtrlEX();
	virtual ~CRichEditCtrlEX();

	BOOL m_bEnableLineWrap = FALSE;

protected:
	afx_msg	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT message);
	afx_msg void OnEnterMenuLoop(IN CONST BOOL bIsTrackPopupMenu);
	afx_msg void OnExitMenuLoop(IN CONST BOOL bIsTrackPopupMenu);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditOpenPath();
	afx_msg void OnEditRevealPath();
	afx_msg void OnEditClear();
	afx_msg void OnEditGoolgeIt();
	afx_msg void OnEditTranslateIt();
	afx_msg void OnEditSelectall();
	afx_msg void OnEditViewLogInEditor();
	afx_msg void OnEditWrapLine();
	afx_msg void OnEditCountMessageLine();
	CString GetCurrentTextLine();
	CString GetAllText();
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	DECLARE_MESSAGE_MAP()
	BOOL m_bInMenu = FALSE;
};

/////////////////////////////////////////////////////////////////////////////
// CMessagePaneDlg dialog

class CMessagePaneDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMessagePaneDlg)

public:
	CMessagePaneDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMessagePaneDlg();
	virtual void OnOK();
	virtual void OnCancel();
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_DIALOG_MESSAGE_PANE };
#endif

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void AddLogMessage(CString str, COLORREF col = RGB(200, 200, 200));
	int GetNumVisibleLines(CRichEditCtrl * pCtrl);
	void ClearAll();
	void UpdateDlgFont();
	void UpdateLogVisual();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnMoving(UINT nSide, LPRECT lpRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnInitDialog();

// Attributes
protected:
	CRichEditCtrlEX m_wndOutput;
	CFont	m_Font;
};

/////////////////////////////////////////////////////////////////////////////
// CMessagePane 

class CMessagePane : public CDockPaneBase
{	
// Construction
public:
	DECLARE_DYNCREATE(CMessagePane)
	CMessagePane();
	virtual ~CMessagePane();

// Implementation
public:
	void AddLogMessage( CString strMsg, COLORREF col = 0 );
	void ClearAll();

protected:
	virtual void UpdateUIVisual();

protected:
	CMessagePaneDlg m_LogPaneDlg;

	// Messages
	afx_msg LRESULT OnDockPaneUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};