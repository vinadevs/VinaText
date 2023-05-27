#pragma once
/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "DockPaneBase.h"
#include "SearchEngine.h"
#include "UndoRedoEditControl.h"

/////////////////////////////////////////////////////////////////////////////
// CPathResultList

class CPathResultList : public CListCtrl
{
	DECLARE_DYNAMIC(CPathResultList)
	// Construction
public:
	CPathResultList();
	virtual ~CPathResultList();
	CString GetSelectedItemsText();
	CString GetItemsText();
	afx_msg void OpenSelectedPath();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnEditDelete();
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditSaveToFile();
	afx_msg void OnEditRevealPath();
	afx_msg void OnEditCopyFullPath();
	afx_msg void OnEditViewLogInEditor();
	afx_msg void OnEditCountSelection();
	afx_msg void OnEditSendToRecyclebin();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Filter Interface

class CPathEditFilter : public CUndoRedoEditControl
{
	DECLARE_DYNAMIC(CPathEditFilter)
public:
	CPathEditFilter();
	virtual ~CPathEditFilter();
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
// CPathResultDlg dialog

class CPathResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPathResultDlg)

public:
	CPathResultDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPathResultDlg();
	virtual void OnOK();
	virtual void OnCancel();
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILE_RESULT_DLG };
#endif
	void UpdateListCtrlVisual();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void InitResult(const PATH_RESULT_DATA_LIST & ResultSearchData, const CString & strSeachWhat, int nSearchTotal, double dTimeMeasured, BOOL bAppendResult, BOOL bSearchWithoutMatchName);
	void ClearResult();
	void DeleteAResult(const CString& strFullPath);

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
	afx_msg void OnFilterTextChanged();

	void InitListCtrl();
	void InitFilterCtrl();

	// Attributes
protected:
	PATH_RESULT_DATA_LIST m_DisplayResultSearchData;
	PATH_RESULT_DATA_LIST m_OriginalResultSearchInfo;
	CPathResultList m_wndResultList;
	CPathEditFilter m_wndEditFilter;
	CFont m_Font;
};

/////////////////////////////////////////////////////////////////////////////
// CPathResultWindow 

class CPathResultWindow : public CDockPaneBase
{
	// Construction
public:
	DECLARE_DYNCREATE(CPathResultWindow)
	CPathResultWindow();
	virtual ~CPathResultWindow();

	// Implementation
public:
	void AddResultData(const PATH_RESULT_DATA_LIST& ResultSearchData, const CString & strSeachWhat, int nSearchTotal, double dTimeMeasured, BOOL bAppendResult, BOOL bSearchWithoutMatchName);
	void ClearAll();

protected:
	virtual void UpdateUIVisual();

protected:
	CPathResultDlg m_ResultPaneDlg;

	// Messages
	afx_msg LRESULT OnDockPaneUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};