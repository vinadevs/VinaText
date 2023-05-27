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

#define UM_EDIT_USER_INPUT (WM_APP+311) 
#define UM_EDIT_TRACE_PREV (WM_USER + 0x112)
#define UM_EDIT_TRACE_NEXT (WM_USER + 0x113)

/////////////////////////////////////////////////////////////////////////////
// CRichEditCtrlBuild

struct BuildErrorDataLine
{
	long _lineNumber;
	CString _FilePath;
	BuildErrorDataLine(long lineNumber, CString FilePath)
	{
		_lineNumber = lineNumber;
		_FilePath = FilePath;
	}
};

typedef std::vector<BuildErrorDataLine> BuildErrorDataLineList;

/////////////////////////////////////////////////////////////////////////////
// Debugger Toolbar

class CDebuggerToolBar : public CMFCToolBar
{
public:
	CDebuggerToolBar() {};
	virtual ~CDebuggerToolBar() {};
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}
	virtual BOOL AllowShowOnList() const { return FALSE; }
	virtual BOOL OnUserToolTip(CMFCToolBarButton* pButton, CString& strTTText) const;
};

/////////////////////////////////////////////////////////////////////////////
// Message Log

class CRichEditCtrlBuild : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CRichEditCtrlBuild)
// Construction
public:
	CRichEditCtrlBuild();
	virtual ~CRichEditCtrlBuild();
	void ShowErrorLineOnEditor();
	CString GetTextLine(long nLineIndex, long lLineLength);

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
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditWrapLine();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnOutputGotoLine();
	afx_msg void OnEditViewLogInEditor();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void GetAllText(CString & strText);
	CString GetCurrentTextLine();
	void ShowEditorAnnotationLine(const CString & strline, BuildErrorDataLineList& errorLines, BOOL bGotoLine = TRUE);
	void CompilerMessageLineParser(CString& strLine, CString& strLineNumber, CString& strFilePath);
	BOOL m_bInMenu = FALSE;
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Command Line Interface

class CEditBuild : public CUndoRedoEditControl
{
	DECLARE_DYNAMIC(CEditBuild)
public:
	CEditBuild();
	virtual ~CEditBuild();
	CString GetCurrentText();
	void SetCaretAtEndline();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnSetFocus(CWnd * pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};

/////////////////////////////////////////////////////////////////////////////
// CBuildPaneDlg dialog

typedef std::vector<CString> HistoryUserInput;

class CBuildPaneDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBuildPaneDlg)

public:
	CBuildPaneDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBuildPaneDlg();
	virtual void OnOK();
	virtual void OnCancel();
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_DIALOG_BUILD_PANE };
#endif

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void UpdateLogVisual();
	void AddLogMessage(CString strMessage, COLORREF color);
	int GetNumVisibleLines(CRichEditCtrl * pCtrl);
	void ClearAll();
	void ShowErrorLineOnEditor();

protected:
	BOOL IsDebuggerMessage(CString& strMessage, BOOL& bStopDebugger, BOOL& bDisableOutputLog, BOOL& bIsNonObjectVariable);
	void RecordUserInput(const CString & strCommand);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMoving(UINT nSide, LPRECT lpRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnInitDialog();
	afx_msg LRESULT OnUserInput(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT TraceHistoryCmdPrev(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT TraceHistoryCmdNext(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnStartDebugger();
	afx_msg void OnShowCallStack();
	afx_msg void OnStopDebugger();
	afx_msg void OnRestartDebugger();
	afx_msg void OnStepOver();
	afx_msg void OnStepInto();
	afx_msg void OnStepOut();
	afx_msg void OnWatchVariableValue();
	afx_msg void OnWatchVariableType();
	afx_msg void OnAddBreakpoint();
	afx_msg void OnDeleteAllBreakPoints();
	afx_msg void OnUpdateStopDebugger(CCmdUI * pCmdUI);
	afx_msg void OnUpdateStartDebugger(CCmdUI * pCmdUI);
	afx_msg void OnUpdateReStartDebugger(CCmdUI * pCmdUI);
	afx_msg void OnUpdateShowCallStack(CCmdUI * pCmdUI);
	afx_msg void OnUpdateStepInto(CCmdUI * pCmdUI);
	afx_msg void OnUpdateStepOver(CCmdUI * pCmdUI);
	afx_msg void OnUpdateStepOut(CCmdUI * pCmdUI);
	afx_msg void OnUpdateWatchVariableValue(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWatchVariableType(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddBreakpoint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeleteAllBreakPoints(CCmdUI* pCmdUI);

// Attributes
protected:
	CRichEditCtrlBuild m_wndOutput;
	CEditBuild m_wndUserInput;
	CDebuggerToolBar m_wndDebuggerToolBar;
	HistoryUserInput m_HistoryUserInput;
	CFont	m_Font;
	long	m_lPointerLine = 0;
	CString m_strFileName;
};

/////////////////////////////////////////////////////////////////////////////
// CBuildPane 

class CBuildPane : public CDockPaneBase
{	
// Construction
public:
	DECLARE_DYNCREATE(CBuildPane)
	CBuildPane();
	virtual ~CBuildPane();

// Implementation
public:
	void AddLogMessage(CString strMsg, COLORREF color);
	void ClearAll();
	void ShowErrorLineOnEditor();

protected:
	virtual void UpdateUIVisual();

protected:
	CBuildPaneDlg m_LogPaneDlg;

	// Messages
	afx_msg LRESULT OnDockPaneUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};