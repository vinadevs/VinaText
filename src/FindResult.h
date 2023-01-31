/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList window

struct stListboxItem
{
	stListboxItem(LPCTSTR lpszMsg, COLORREF cColor)
	{
		str = lpszMsg;
		clr = cColor;
	};
	CString		str;
	COLORREF	clr;
};

class CResultList : public CListBox
{
	DECLARE_DYNAMIC(CResultList)
// Construction
public:
	CResultList();

// Implementation
public:
	virtual ~CResultList();
	void SetSeachWhatString(CString strSeachWhat) { m_strSeachWhat = strSeachWhat; }
	void ClearAll();
	CString GetAllText();

protected:
	CString m_strSeachWhat;
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnEditSelectall();
	afx_msg void OnEditSaveToFile();
	afx_msg void OnOutputGotoLine();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditViewLogInEditor();
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	DECLARE_MESSAGE_MAP()
};

class CFindResultPane : public CDockablePane
{
// Construction
public:
	CFindResultPane();
	void AddSearchData(CString strSearchWhat, CString strSearchScope, const RESULT_SEARCH_DATA& ResultSearchData, BOOL bAppendResult = FALSE, BOOL bShowFileNameOnly = FALSE);
	void AddReplaceData(CString strSearchWhat, CString strReplaceWith, CString strSearchScope, const RESULT_SEARCH_DATA& ResultSearchData, BOOL bAppendResult = FALSE, BOOL bShowFileNameOnly = FALSE);
	void AddString(CString str);
	void ClearAll();

// Attributes
protected:
	CResultList m_wndOutput;
	CFont	m_Font;

protected:
	void FillInitialWindow();
	void AdjusrHorzScroll(CListBox& wndListBox);
	void UpdateAppSetting();

// Implementation
public:
	virtual ~CFindResultPane();

protected:
	afx_msg LRESULT OnDockPaneUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};

