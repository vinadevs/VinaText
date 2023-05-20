/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

// Original version could be found here by _Flaviu
// https://www.codeproject.com/Articles/187753/Extended-CComboBox

#pragma once

#include <afxtempl.h>
#include "ComboBoxExtList.h"

#define WMU_POSTCLOSEUP							(WM_USER + 64)
/////////////////////////////////////////////////////////////////////////////
// CComboboxMultiLine window

class CComboboxMultiLine : public CComboBox
{
// Construction
public:
	CComboboxMultiLine();

// Attributes
public:
	enum
	{
		MODE_STANDARD			= 0,
		MODE_DROPDOWN			= 1,
		MODE_AUTOCOMPLETE		= 2
	};

// Operations
public:
	BOOL IsAlertBkg() const { return m_bAlertBkg; }
	BOOL IsAlertText() const { return m_bAlertText; }
	BOOL IsAdjustedDroppedWidth() const { return m_bAdjustDroppedWidth; }
	int GetMode() const { return m_nMode; }
	void SetMode(int nMode = CComboboxMultiLine::MODE_STANDARD) { m_nMode = nMode; }
	void AdjustDroppedWidth(BOOL bAdjustDroppedWidth = TRUE) { m_bAdjustDroppedWidth = bAdjustDroppedWidth; }
	COLORREF GetAlertColorBkg() const { return m_crAlertBkg; }
	void SetAlertColorBkg(COLORREF crColor);
	COLORREF GetAlertColorText() const { return m_crAlertText; }
	void SetAlertColorText(COLORREF crColor) { m_crAlertText = crColor; }
	void SetFocusEx();
	int AddStringWithInfo(LPCTSTR lpszString, LPCTSTR lpszInfo, BOOL bShowItemTooltip = TRUE);
	int InsertStringWithInfo(int nIndex, LPCTSTR lpszString, LPCTSTR lpszInfo, BOOL bShowItemTooltip = TRUE);
	void SetLBInfo(int nIndex, LPCTSTR lpszInfo, BOOL bShowItemTooltip = TRUE);
	void GetLBInfo(int nIndex, CString& rInfo) const;
	void SetLBShowItemTooltip(int nIndex, BOOL bShow = TRUE);
	BOOL GetLBShowItemTooltipState(int nIndex) const;
	int FindInfo(int nStartAfter, LPCTSTR lpszString) const;
	int FindInfoExact(int nIndexStart, LPCTSTR lpszFind) const;
	int SelectInfo(int nStartAfter, LPCTSTR lpszString);

	void AlertBkg(BOOL bAlert = TRUE, BOOL bRedraw = FALSE)
	{
		m_bAlertBkg = bAlert;
		if(bRedraw)
			Invalidate();
	}
	void AlertText(BOOL bAlert = TRUE, BOOL bRedraw = FALSE)
	{
		m_bAlertText = bAlert;
		if(bRedraw)
			Invalidate();
	}

	void SetEditTooltip(BOOL bShowTooltip, BOOL bTooltipOnInfo = FALSE, BOOL bShowEditTooltipOverItem = FALSE)
	{
		m_bShowTooltip = bShowTooltip;
		m_bTooltipOnInfo = bTooltipOnInfo;
		m_bShowEditTooltipOverItem = bShowEditTooltipOverItem;
	}
	void GetEditTooltip(BOOL& bShowTooltip, BOOL& bTooltipOnInfo, BOOL& bShowEditTooltipOverItem)
	{
		bShowTooltip = m_bShowTooltip;
		bTooltipOnInfo = m_bTooltipOnInfo;
		bShowEditTooltipOverItem = m_bShowEditTooltipOverItem;
	}
	void SetListTooltip(BOOL bShowTooltip, BOOL bTooltipOnInfo = FALSE, BOOL bShowListTooltipOverItem = FALSE)
	{
		m_ListBox.m_bShowTooltip = bShowTooltip;
		m_ListBox.m_bTooltipOnInfo = bTooltipOnInfo;
		m_ListBox.m_bShowListTooltipOverItem = bShowListTooltipOverItem;
	}
	void GetListTooltip(BOOL& bShowTooltip, BOOL& bTooltipOnInfo, BOOL& bShowListTooltipOverItem)
	{
		bShowTooltip = m_ListBox.m_bShowTooltip;
		bTooltipOnInfo = m_ListBox.m_bTooltipOnInfo;
		bShowListTooltipOverItem = m_ListBox.m_bShowListTooltipOverItem;
	}
	void SetEditTooltipOverItemPosition(BOOL bAbove = TRUE)
	{
		m_bEditTooltipOverItemPos = bAbove;
	}
	BOOL GetEditTooltipOverItemPosition() const
	{
		return m_bEditTooltipOverItemPos;
	}

	void GetClipboardText();

// Overrides
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	protected:
	virtual void PreSubclassWindow();

// Implementation
public:
	virtual ~CComboboxMultiLine();
	DWORD GetItemData(int nIndex) const;
	int SetItemData(int nIndex, DWORD dwItemData);
	TOOLINFO* GetToolInfo() { return &m_ToolInfo; }
	HWND* GetToolTipHwnd() { return &m_hWndToolTip; }
	CComboBoxExtList* GetListBox() { return &m_ListBox; }

protected:
	BOOL m_bEdit;
	BOOL m_bAutoSelection;
	BOOL m_bToolActive;
	HWND m_hWndToolTip;
	TOOLINFO m_ToolInfo;
	CString m_sTypedText;
	CString m_sCloseupText;
	CComboBoxExtList m_ListBox;
	DWORD m_dwStartSel, m_dwEndSel;

protected:
	LPTSTR m_pText;
	int m_nMode;
	BOOL m_bAlertBkg;
	BOOL m_bAlertText;
	BOOL m_bAdjustDroppedWidth;
	BOOL m_bAutoComplete;
	BOOL m_bShowTooltip;
	BOOL m_bTooltipOnInfo;
	BOOL m_bShowEditTooltipOverItem;	// this item make sense only when m_bTooltipOnInfo == TRUE
	BOOL m_bEditTooltipOverItemPos;		// this item make sense only when m_bShowEditTooltipOverItem == TRUE
	CBrush m_BrushAlert;
	COLORREF m_crAlertBkg;
	COLORREF m_crAlertText;

	class CItemData : public CObject
	{
    // Attributes
	public:
		DWORD m_dwItemData;
		CString m_sItem;
		CString m_sInfo;
		BOOL m_bState;
		BOOL m_bShowItemTooltip;

    // Implementation
	public:
		CItemData();
		CItemData(DWORD dwItemData, LPCTSTR lpszString);
		CItemData(DWORD dwItemData, LPCTSTR lpszString, BOOL bState);
		CItemData(DWORD dwItemData, LPCTSTR lpszString, LPCTSTR lpszInfo, BOOL bState);
		CItemData(DWORD dwItemData, LPCTSTR lpszString, LPCTSTR lpszInfo, BOOL bState, BOOL bShowItemTooltip);
		virtual ~CItemData();
	};

	CTypedPtrList<CPtrList, CItemData*> m_PtrList;

protected:
	virtual void FitDropDownToItems();
	virtual int AddItem(CItemData* pData);
	virtual int DeleteItem(CItemData* pData);

// Generated message map functions
protected:
	afx_msg void OnPaste();
	afx_msg void OnDestroy();
	afx_msg BOOL OnCloseup();
	afx_msg BOOL OnDropdown();
	afx_msg BOOL OnSelendok();
	afx_msg BOOL OnSelchange();
	afx_msg BOOL OnEditchange();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnAddString(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnInsertString(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDeleteString(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnResetContent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPostCloseup(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};