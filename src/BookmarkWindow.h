/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "DockPaneBase.h"
#include "EditorDataStructure.h"

/////////////////////////////////////////////////////////////////////////////
// CBookmarkList

class CBookmarkList : public CListCtrl
{
	DECLARE_DYNAMIC(CBookmarkList)
	// Construction
public:
	CBookmarkList();
	virtual ~CBookmarkList();
	CString GetSelectedItemsText();
	CString GetItemsText();
	afx_msg void OnOutputGotoLine();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnEditClearSelected();
	afx_msg void OnEditSelectall();
	afx_msg void OnEditSaveToFile();
	afx_msg void OnEditViewLogInEditor();
	afx_msg void OnEditRevealPath();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CBookmarkDlg dialog

class CBookmarkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBookmarkDlg)

public:
	CBookmarkDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBookmarkDlg();
	virtual void OnOK();
	virtual void OnCancel();
	void UpdateListCtrlVisual();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCH_RESULT_DLG };
#endif
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void AddBookmarkData(const BOOKMARK_LINE_DATA& data);
	void ClearBookmarkData();
	void ClearSelectedBoorkmark();
	void SaveBookmarkData();
	void LoadBookmarkData();

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
	CBookmarkList m_wndBookmarkList;
	BOOKMARK_LINE_DATA_LIST m_BookmarkData;
	CFont m_Font;
};

/////////////////////////////////////////////////////////////////////////////
// CBookmarkWindow 

class CBookmarkWindow : public CDockPaneBase
{
	// Construction
public:
	DECLARE_DYNCREATE(CBookmarkWindow)
	CBookmarkWindow();
	virtual ~CBookmarkWindow();

	// Implementation
public:
	void AddBookmarkData(const BOOKMARK_LINE_DATA& data);
	void ClearAll();

protected:
	virtual void UpdateUIVisual();

protected:
	CBookmarkDlg m_BookMarkPaneDlg;

	// Messages
	afx_msg LRESULT OnDockPaneUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};