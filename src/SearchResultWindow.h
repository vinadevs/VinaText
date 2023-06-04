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
// CSearchResultList

class CSearchResultList : public CListCtrl
{
	DECLARE_DYNAMIC(CSearchResultList)
	// Construction
public:
	CSearchResultList();
	virtual ~CSearchResultList();
	void SetSeachWhatString(const CString& strSeachWhat) { m_strSeachWhat = strSeachWhat; }
	void SetSeachOptions(unsigned int uiSearchOptions) { m_uiSearchOptions = uiSearchOptions; }
	CString GetSelectedItemsText();
	CString GetItemsText();
	afx_msg void OnOutputPreviewFile();

protected:
	CString m_strSeachWhat;
	unsigned int m_uiSearchOptions;
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditSaveToFile();
	afx_msg void OnEditViewLogInEditor();
	afx_msg void OnEditRevealPath();
	afx_msg void OnEditDelete();
	afx_msg void OnEditCopyFullPath();
	afx_msg void OnEditCountSelection();
	afx_msg void OnEditSendToRecyclebin();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Filter Interface

class CEditFilter : public CUndoRedoEditControl
{
	DECLARE_DYNAMIC(CEditFilter)
public:
	CEditFilter();
	virtual ~CEditFilter();
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
// CSearchResultDlg dialog

class CSearchResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchResultDlg)

public:
	CSearchResultDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchResultDlg();
	virtual void OnOK();
	virtual void OnCancel();
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCH_RESULT_DLG };
#endif
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void InitResult(const TEXT_RESULT_SEARCH_REPLACE_DATA& ResultSearchData);
	void ClearResult();
	void DeleteAPath(const CString& strFullPath);
	void DeleteARow(const CString& strFullPath, unsigned int nLineNumber);
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
	afx_msg void OnFilterTextChanged();

	void InitListCtrl();
	void InitFilterCtrl();

	// Attributes
protected:
	TEXT_RESULT_SEARCH_REPLACE_DATA m_DisplayResultSearchData;
	std::vector<SEARCH_DATA_LINE> m_OriginalResultSearchInfo;
	CSearchResultList m_wndResultList;
	CEditFilter m_wndEditFilter;
	CFont m_Font;
};

/////////////////////////////////////////////////////////////////////////////
// CSearchResultWindow 

class CSearchResultWindow : public CDockPaneBase
{
	// Construction
public:
	DECLARE_DYNCREATE(CSearchResultWindow)
	CSearchResultWindow();
	virtual ~CSearchResultWindow();

	// Implementation
public:
	void AddResultData(const TEXT_RESULT_SEARCH_REPLACE_DATA& ResultSearchData);
	void ClearAll();

protected:
	virtual void UpdateUIVisual();

protected:
	CSearchResultDlg m_ResultPaneDlg;

	// Messages
	afx_msg LRESULT OnDockPaneUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};