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

/////////////////////////////////////////////////////////////////////////////
// CComboBoxExtList window

class CComboboxMultiLine;

class CComboBoxExtList : public CListBox
{
// Construction
public:
	CComboBoxExtList();

// Attributes
public:
	BOOL m_bShowTooltip;
	BOOL m_bTooltipOnInfo;
	BOOL m_bShowListTooltipOverItem; // this has meaning only when m_bTooltipOnInfo == TRUE
	CComboboxMultiLine* m_pComboBox;

// Operations
public:
	TOOLINFO* GetToolInfo() { return &m_ToolInfo; }
	HWND* GetToolTipHwnd() { return &m_hWndToolTip; }

// Overrides
	protected:
	virtual void PreSubclassWindow();

// Implementation
public:
	virtual ~CComboBoxExtList() {};

protected:
	int m_nPrevItem;
	BOOL m_bToolActive;
	HWND m_hWndToolTip;
	TOOLINFO m_ToolInfo;

	// Generated message map functions
protected:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnLbFindString(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};