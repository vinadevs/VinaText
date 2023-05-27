#pragma once

#include "DockPaneBase.h"
#include "EditorDataStructure.h"

/////////////////////////////////////////////////////////////////////////////
// CBreakpointList

class CBreakpointList : public CListCtrl
{
	DECLARE_DYNAMIC(CBreakpointList)
	// Construction
public:
	CBreakpointList();
	virtual ~CBreakpointList();
	CString GetSelectedItemsText();
	CString GetItemsText();
	afx_msg void OnOutputGotoLine();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnEditClearSelected();
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditSaveToFile();
	afx_msg void OnEditViewLogInEditor();
	afx_msg void OnEditRevealPath();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CBreakpointDlg dialog

class CBreakpointDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBreakpointDlg)

public:
	CBreakpointDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBreakpointDlg();
	virtual void OnOK();
	virtual void OnCancel();
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCH_RESULT_DLG };
#endif
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void AddBreakpointData(const BREAKPOINT_LINE_DATA& data);
	void ClearBreakpointData();
	void ClearSelectedBreakpoint();
	void UpdateListCtrlVisual();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMoving(UINT nSide, LPRECT lpRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnInitDialog();
	afx_msg void OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOdfinditemList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOdcachehintList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedList(NMHDR * pNMHDR, LRESULT * pResult);

	void InitListCtrl();

	// Attributes
protected:
	CBreakpointList m_wndBreakpointList;
	BREAKPOINT_LINE_DATA_LIST m_BreakpointData;
	CFont m_Font;
};

/////////////////////////////////////////////////////////////////////////////
// CBreakpointWindow 

class CBreakpointWindow : public CDockPaneBase
{
	// Construction
public:
	DECLARE_DYNCREATE(CBreakpointWindow)
	CBreakpointWindow();
	virtual ~CBreakpointWindow();

	// Implementation
public:
	void AddBreakpointData(const BREAKPOINT_LINE_DATA& data);
	void ClearAll();

protected:
	virtual void UpdateUIVisual();

protected:
	CBreakpointDlg m_BreakpointPaneDlg;

	// Messages
	afx_msg LRESULT OnDockPaneUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};