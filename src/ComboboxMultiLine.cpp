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

#include "stdafx.h"
#include "ComboboxMultiLine.h"

#define ID_EDIT_CHILD_COMBOBOX 1001

/////////////////////////////////////////////////////////////////////////////
// CComboboxMultiLine

CComboboxMultiLine::CItemData::CItemData()
	:m_dwItemData(CB_ERR)
	,m_sItem(_T(""))
	,m_bState(TRUE)
	,m_bShowItemTooltip(TRUE)
{
}

CComboboxMultiLine::CItemData::CItemData(DWORD dwItemData, LPCTSTR lpszString)
	:m_bState(TRUE)
	,m_bShowItemTooltip(TRUE)
{
	m_dwItemData = dwItemData;
	m_sItem = lpszString;
	m_sInfo.Empty();
}

CComboboxMultiLine::CItemData::CItemData(DWORD dwItemData, LPCTSTR lpszString, BOOL bState)
	:m_bShowItemTooltip(TRUE)
{
	m_dwItemData = dwItemData;
	m_sItem = lpszString;
	m_sInfo.Empty();
	m_bState = bState;
}

CComboboxMultiLine::CItemData::CItemData(DWORD dwItemData, LPCTSTR lpszString, LPCTSTR lpszInfo, BOOL bState)
	:m_bShowItemTooltip(TRUE)
{
	m_dwItemData = dwItemData;
	m_sItem = lpszString;
	m_sInfo = lpszInfo;
	m_bState = bState;
}

CComboboxMultiLine::CItemData::CItemData(DWORD dwItemData, LPCTSTR lpszString, LPCTSTR lpszInfo, BOOL bState, BOOL bShowItemTooltip)
{
	m_dwItemData = dwItemData;
	m_sItem = lpszString;
	m_sInfo = lpszInfo;
	m_bState = bState;
	m_bShowItemTooltip = bShowItemTooltip;
}

CComboboxMultiLine::CItemData::~CItemData()
{
}

CComboboxMultiLine::CComboboxMultiLine()
	:m_nMode(MODE_STANDARD)
	,m_bEdit(FALSE)
	,m_dwStartSel(0)
	,m_dwEndSel(0)
	,m_bAlertBkg(FALSE)
	,m_bAlertText(FALSE)
	,m_bToolActive(FALSE)
	,m_bShowTooltip(FALSE)
	,m_bTooltipOnInfo(FALSE)
	,m_bShowEditTooltipOverItem(FALSE)
	,m_bEditTooltipOverItemPos(FALSE)
	,m_bAutoComplete(TRUE)
	,m_bAutoSelection(FALSE)
	,m_bAdjustDroppedWidth(FALSE)
{
	m_hWndToolTip = NULL;
	m_crAlertBkg = GetSysColor(COLOR_WINDOW);
	m_crAlertText = GetSysColor(COLOR_WINDOWTEXT);
	m_BrushAlert.CreateSolidBrush(m_crAlertBkg);
	memset(&m_ToolInfo, 0, sizeof(m_ToolInfo));
}

CComboboxMultiLine::~CComboboxMultiLine()
{
	m_BrushAlert.DeleteObject();
	::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
}

BEGIN_MESSAGE_MAP(CComboboxMultiLine, CComboBox)
	ON_WM_DESTROY()
	ON_WM_PASTE()
	ON_CONTROL_REFLECT_EX(CBN_CLOSEUP, OnCloseup)
	ON_CONTROL_REFLECT_EX(CBN_DROPDOWN, OnDropdown)
	ON_CONTROL_REFLECT_EX(CBN_SELENDOK, OnSelendok)
	ON_CONTROL_REFLECT_EX(CBN_SELCHANGE, OnSelchange)
	ON_CONTROL_REFLECT_EX(CBN_EDITCHANGE, OnEditchange)
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_MESSAGE(CB_ADDSTRING, OnAddString)
	ON_MESSAGE(CB_INSERTSTRING, OnInsertString)
	ON_MESSAGE(CB_DELETESTRING, OnDeleteString)
	ON_MESSAGE(CB_RESETCONTENT, OnResetContent)
	ON_MESSAGE(WMU_POSTCLOSEUP, OnPostCloseup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboboxMultiLine message handlers

void CComboboxMultiLine::PreSubclassWindow()
{
	COMBOBOXINFO cbi = { 0 };
	cbi.cbSize = sizeof(COMBOBOXINFO);
	if (::GetComboBoxInfo(m_hWnd, &cbi) && NULL != cbi.hwndList)
	{
#undef SubclassWindow
		if (m_ListBox.SubclassWindow(cbi.hwndList))
			m_ListBox.m_pComboBox = this;

		// create tooltip
		m_hWndToolTip = ::CreateWindowEx(WS_EX_TOPMOST,
										TOOLTIPS_CLASS,
										NULL,
										TTS_NOPREFIX | TTS_ALWAYSTIP,
										CW_USEDEFAULT,
										CW_USEDEFAULT,
										CW_USEDEFAULT,
										CW_USEDEFAULT,
										NULL,
										NULL,
										NULL,
										NULL);

		if (NULL != m_hWndToolTip)	// initialize toolinfo struct
		{
			memset(&m_ToolInfo, 0, sizeof(m_ToolInfo));
#if (NTDDI_VERSION >= NTDDI_WINXP)
			m_ToolInfo.cbSize = sizeof(TTTOOLINFO) - sizeof(void*);
#else
			m_ToolInfo.cbSize = sizeof(TTTOOLINFO);
#endif
			m_ToolInfo.uFlags = TTF_TRACK | TTF_TRANSPARENT;
			m_ToolInfo.hwnd = m_hWnd;
			::SendMessage(m_hWndToolTip, TTM_SETMAXTIPWIDTH, (WPARAM)0, (LPARAM)SHRT_MAX);
			::SendMessage(m_hWndToolTip, TTM_ADDTOOL, (WPARAM)0, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
		}
	}
	CComboBox::PreSubclassWindow();
}

BOOL CComboboxMultiLine::PreTranslateMessage(MSG* pMsg)
{
	if (MODE_STANDARD != m_nMode && WM_KEYDOWN == pMsg->message)
	{
		if (MODE_AUTOCOMPLETE == m_nMode && (VK_DELETE == pMsg->wParam || VK_BACK == pMsg->wParam))
			m_bAutoComplete = FALSE;
	}
	else if (pMsg->message == WM_KEYDOWN)
	{
		if (::GetKeyState(VK_CONTROL) < 0)
		{
			if (pMsg->wParam == 'V')
			{
				SendMessage(WM_PASTE); // custom paste data...
				return true;
			}
		}
	}
	return CComboBox::PreTranslateMessage(pMsg);
}

void CComboboxMultiLine::FitDropDownToItems()
{
	if (CBS_SIMPLE == (3 & GetStyle()) || NULL == m_ListBox.GetSafeHwnd())
		return;

	CRect rectEdit, rectDropDown, rectDropDownCli;
	GetWindowRect(rectEdit);
	m_ListBox.GetWindowRect(rectDropDown);
	m_ListBox.GetClientRect(rectDropDownCli);

	int nHeight = rectDropDown.Height() - rectDropDownCli.Height();
	const int nMaxHeight = GetSystemMetrics(SM_CYSCREEN) / 2;
	const int nCount = GetCount();
	for (int nIndex = 0; nIndex < nCount; ++nIndex)
	{
		nHeight += GetItemHeight(nIndex);
		if (nHeight > nMaxHeight)
			break;
	}

	CRect rcDropDownNew(rectDropDown.left, rectDropDown.top, rectDropDown.right, rectDropDown.top + nHeight);
	if (rectEdit.top > rectDropDown.top && rectEdit.top != rcDropDownNew.bottom)
		rcDropDownNew.top += (rectEdit.top - rcDropDownNew.bottom);
	m_ListBox.MoveWindow(rcDropDownNew);
}

BOOL CComboboxMultiLine::OnDropdown()
{
	// TODO: Add your control notification handler code here

	SetCursor(LoadCursor(NULL, IDC_ARROW));
	::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);

	if (! m_bAdjustDroppedWidth)
		return static_cast<BOOL>(Default());

	int dx = 0;
	CSize sz(0, 0);
	TEXTMETRIC tm;
	CString sLBText;
	CDC* pDC = GetDC();
	CFont* pFont = GetFont();
	// Select the listbox font, save the old font
	CFont* pOldFont = pDC->SelectObject(pFont);
	// Get the text metrics for avg char width
	pDC->GetTextMetrics(&tm);

	const int nCount = GetCount();
	for (int i = 0; i < nCount; ++i)
	{
		GetLBText(i, sLBText);
		sz = pDC->GetTextExtent(sLBText);
		// Add the avg width to prevent clipping
		sz.cx += tm.tmAveCharWidth;
		if (sz.cx > dx)
			dx = sz.cx;
	}

	// Select the old font back into the DC
	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);

	// Adjust the width for the vertical scroll bar and the left and right border.
	dx += GetSystemMetrics(SM_CXVSCROLL) + 2 * GetSystemMetrics(SM_CXEDGE);
	if (GetDroppedWidth() < dx)
		SetDroppedWidth(dx);

	return static_cast<BOOL>(Default());
}

HBRUSH CComboboxMultiLine::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);
	if (CBS_DROPDOWNLIST == (3 & GetStyle()) || CBS_SIMPLE == (3 & GetStyle()))
		return hbr;

	// TODO: Change any attributes of the DC here

	if (CTLCOLOR_EDIT == nCtlColor)
	{
		if (! m_bAlertText)
			pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		else
			pDC->SetTextColor(m_crAlertText);

		if (! m_bAlertBkg)
		{
			pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
		}
		else
		{
			pDC->SetBkColor(m_crAlertBkg);
			hbr = (HBRUSH)m_BrushAlert.GetSafeHandle();
		}
	}

	// TODO: Return a different brush if the default is not desired

	return hbr;
}

BOOL CComboboxMultiLine::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	// TODO: Add your specialized code here and/or call the base class

	if (CBS_DROPDOWNLIST != (3 & GetStyle()) || (! m_bAlertText && ! m_bAlertBkg) || WM_CTLCOLOREDIT != message)
		return CComboBox::OnChildNotify(message, wParam, lParam, pLResult);

	HDC hdcChild = (HDC)wParam;
	if (NULL != hdcChild)
	{
		if (m_bAlertText)
			SetTextColor(hdcChild, m_crAlertText);
		if (m_bAlertBkg)
			SetBkColor(hdcChild, m_crAlertBkg);
		*pLResult = (LRESULT)(m_BrushAlert.GetSafeHandle());
	}

	return TRUE;
	//	return CComboBox::OnChildNotify(message, wParam, lParam, pLResult);
}

void CComboboxMultiLine::SetFocusEx()
{
	CEdit* pEdit = (CEdit*)GetDlgItem(ID_EDIT_CHILD_COMBOBOX);
	if (pEdit)
	{
		int a, b;
		pEdit->GetSel(a, b);
		pEdit->SetFocus();
		pEdit->SetSel(a, b); // select all text and move cursor at the end
		pEdit->SetSel(-1); //  remove selection
	}
}

void CComboboxMultiLine::GetClipboardText()
{
	if (!OpenClipboard())
		return;

#ifdef UNICODE
	HANDLE hglb = ::GetClipboardData(CF_UNICODETEXT);
#else
	HANDLE hglb = ::GetClipboardData(CF_TEXT);
#endif
	if (hglb == NULL)
	{
		CloseClipboard();
		return;
	}
	m_pText = reinterpret_cast<LPTSTR>(::GlobalLock(hglb));
	if (m_pText != NULL)
	{
		::GlobalUnlock(hglb);
	}
	CloseClipboard();
}

void CComboboxMultiLine::OnPaste()
{
	try
	{
		GetClipboardText();
		CEdit* pEdit = (CEdit*)GetDlgItem(ID_EDIT_CHILD_COMBOBOX);
		if (pEdit)
		{
			pEdit->ReplaceSel(m_pText, TRUE);
		}
	}
	catch (...)
	{
		return;
	}
}

void CComboboxMultiLine::OnDestroy()
{
	if (NULL != m_ListBox.GetSafeHwnd())
		m_ListBox.UnsubclassWindow();

	CComboBox::OnDestroy();

	// TODO: Add your message handler code here

	POSITION pos = m_PtrList.GetHeadPosition();
	while (NULL != pos)
	{
		CItemData* pData = m_PtrList.GetNext(pos);
		if (NULL != pData)
		{
			delete pData;
			pData = NULL;
		}
	}
	m_PtrList.RemoveAll();
}

LRESULT CComboboxMultiLine::OnResetContent(WPARAM wParam, LPARAM lParam)
{
	m_sTypedText.Empty();

	POSITION pos = m_PtrList.GetHeadPosition();
	while (NULL != pos)
	{
		CItemData* pData = m_PtrList.GetNext(pos);
		if (NULL != pData)
		{
			delete pData;
			pData = NULL;
		}
	}
	m_PtrList.RemoveAll();

	return Default();
}

BOOL CComboboxMultiLine::OnSelendok()
{
	// TODO: Add your control notification handler code here

	::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);

	if (! GetDroppedState())
		return static_cast<BOOL>(Default());

	const int nIndex = GetCurSel();
	if (CB_ERR != nIndex)
	{
		GetLBText(nIndex, m_sTypedText);
		SetWindowText(m_sTypedText);
		m_dwStartSel = m_dwEndSel = m_sTypedText.GetLength();
		SetEditSel(m_dwStartSel, m_dwEndSel);
	}

	return static_cast<BOOL>(Default());
}

BOOL CComboboxMultiLine::OnSelchange()
{
	// TODO: Add your control notification handler code here

	::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);

	if (GetDroppedState())
	{
		m_dwStartSel = 0;
		m_dwEndSel = -1;
	}

	if (m_bEdit || MODE_STANDARD == m_nMode || CBS_SIMPLE == (3 & GetStyle()))
		return static_cast<BOOL>(Default());

	const int nIndex = GetCurSel();
	if (CB_ERR != nIndex)
	{
		GetLBText(nIndex, m_sTypedText);
		SetWindowText(m_sTypedText);
	}

	return static_cast<BOOL>(Default());
}

BOOL CComboboxMultiLine::OnEditchange()
{
	// TODO: Add your control notification handler code here

	::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);

	if (MODE_STANDARD == m_nMode || CBS_SIMPLE == (3 & GetStyle()))
		return static_cast<BOOL>(Default());

	SendMessage(CB_GETEDITSEL, (WPARAM)&m_dwStartSel, (LPARAM)&m_dwEndSel);

	GetWindowText(m_sTypedText);
	CString sEditText(m_sTypedText);
	sEditText.MakeLower();

	m_bEdit = TRUE;
	CString sTemp, sFirstOccurrence;
	POSITION pos = m_PtrList.GetHeadPosition();
	while (! m_sTypedText.IsEmpty() && pos)
	{
		CItemData* pData = m_PtrList.GetNext(pos);
		sTemp = pData->m_sItem;
		sTemp.MakeLower();
		if (0 == sTemp.Find(sEditText))
			AddItem(pData);
		else
			DeleteItem(pData);
	}

	if (GetCount() < 1 || m_sTypedText.IsEmpty())
	{
		if (GetDroppedState())
			ShowDropDown(FALSE);
		else
		{
			pos = m_PtrList.GetHeadPosition();
			while (NULL != pos)
				AddItem(m_PtrList.GetNext(pos));
		}
	}
	else
	{
		ShowDropDown();
		FitDropDownToItems();
		if (MODE_AUTOCOMPLETE == m_nMode && GetCount() > 0)
			GetLBText(0, sFirstOccurrence);
	}

	if (MODE_AUTOCOMPLETE == m_nMode && m_bAutoComplete && ! sFirstOccurrence.IsEmpty())
	{
		m_bAutoSelection = TRUE;
		SetWindowText(sFirstOccurrence);
		PostMessage(CB_SETEDITSEL, 0, MAKELPARAM(m_dwEndSel, sFirstOccurrence.GetLength()));
	}
	else
	{
		m_bAutoSelection = FALSE;
		SetWindowText(m_sTypedText);
		SetEditSel(m_dwStartSel, m_dwEndSel);
	}

	m_bAutoComplete = TRUE;

	return static_cast<BOOL>(Default());
}

BOOL CComboboxMultiLine::OnCloseup()
{
	// TODO: Add your control notification handler code here

	::SendMessage(*m_ListBox.GetToolTipHwnd(), TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)m_ListBox.GetToolInfo());

	POSITION pos = m_PtrList.GetHeadPosition();
	while (NULL != pos)
		AddItem(m_PtrList.GetNext(pos));

	if (m_bEdit && CBS_DROPDOWN == (3 & GetStyle()))
	{
		m_sCloseupText.Empty();
		GetWindowText(m_sCloseupText);
		if (! m_sCloseupText.IsEmpty())
			PostMessage(WMU_POSTCLOSEUP, (WPARAM)0, (LPARAM)(LPCTSTR)m_sCloseupText);
	}

	m_bEdit = FALSE;

	return static_cast<BOOL>(Default());
}

LRESULT CComboboxMultiLine::OnPostCloseup(WPARAM wParam, LPARAM lParam)
{
	CString sAutoCompletedText = (LPCTSTR)lParam;
	if (m_bAutoSelection || 0 != sAutoCompletedText.CompareNoCase(m_sTypedText))
		m_sTypedText = sAutoCompletedText;

	const int nIndex = FindStringExact(-1, m_sTypedText);
	SetCurSel(nIndex);
	if (CB_ERR == nIndex)
		SetWindowText(m_sTypedText);

	if (! m_bAutoSelection)
	{
		if (0 == m_dwStartSel && 0 == m_dwEndSel && CB_ERR != FindStringExact(-1, m_sTypedText))
			PostMessage(CB_SETEDITSEL, (WPARAM)0, MAKELPARAM(m_sTypedText.GetLength(), m_sTypedText.GetLength()));
		else
			PostMessage(CB_SETEDITSEL, (WPARAM)0, MAKELPARAM(m_dwStartSel, m_dwEndSel));
	}

	return (LRESULT)1;
}

LRESULT CComboboxMultiLine::OnAddString(WPARAM wParam, LPARAM lParam)
{
	const int nIndex = (int)Default();

	POSITION pos = (POSITION)wParam;
	if (NULL == pos)
	{
		CItemData* pData = new CItemData(CB_ERR, (LPCTSTR)lParam);
		m_PtrList.AddTail(pData);
		SetItemDataPtr(nIndex, pData);
	}

	return nIndex;
}

LRESULT CComboboxMultiLine::OnInsertString(WPARAM wParam, LPARAM lParam)
{
	const int nIndex = (int)Default();

	POSITION pos = (POSITION)wParam;
	if (NULL == pos)
	{
		CItemData* pData = new CItemData(CB_ERR, (LPCTSTR)lParam);
		m_PtrList.AddTail(pData);
		SetItemDataPtr(nIndex, pData);
	}

	return nIndex;
}

LRESULT CComboboxMultiLine::OnDeleteString(WPARAM wParam, LPARAM lParam)
{
	POSITION pos = (POSITION)lParam;
	if (NULL == pos)
	{
		CItemData* pData = (CItemData*)GetItemDataPtr((int)wParam);
		if (NULL != pData)
		{
			POSITION pos = m_PtrList.Find(pData);
			if (NULL != pos)
			{
				delete pData;
				m_PtrList.RemoveAt(pos);
			}
		}
	}

	return Default();
}
// Add item in dropdown list
int CComboboxMultiLine::AddItem(CItemData* pData)
{
	if (NULL == pData || TRUE == pData->m_bState)
		return CB_ERR;

	int nIndex = static_cast<int>(SendMessage(CB_ADDSTRING, (WPARAM)m_PtrList.Find(pData), (LPARAM)(LPCTSTR)pData->m_sItem));
	if (CB_ERR == nIndex || CB_ERRSPACE == nIndex)
		return nIndex;

	pData->m_bState = TRUE;
	SetItemData(nIndex, pData->m_dwItemData);
	SetItemDataPtr(nIndex, pData);

	return nIndex;
}
// Delete item from dropdown list
int CComboboxMultiLine::DeleteItem(CItemData* pData)
{
	int nIndex = CB_ERR;

	if (NULL == pData || FALSE == pData->m_bState)
		return nIndex;

	pData->m_bState = FALSE;
	const int nCount = GetCount();
	for (int i = 0; i < nCount; ++i)
	{
		if (pData == (CItemData*)GetItemDataPtr(i))
		{
			nIndex = static_cast<int>(SendMessage(CB_DELETESTRING, (WPARAM)i, (LPARAM)m_PtrList.Find(pData)));
			break;
		}
	}

	return nIndex;
}

int CComboboxMultiLine::SetItemData(int nIndex, DWORD dwItemData)
{
	if (CB_ERR == nIndex)
		return nIndex;

	CItemData* pData = (CItemData*)GetItemDataPtr(nIndex);
	if (NULL != pData)
	{
		pData->m_dwItemData = dwItemData;
		return 0;
	}

	return CB_ERR;
}

DWORD CComboboxMultiLine::GetItemData(int nIndex) const
{
	if (CB_ERR == nIndex)
		return nIndex;

	DWORD dwItemData = CB_ERR;

	CItemData* pData = (CItemData*)GetItemDataPtr(nIndex);
	if (NULL != pData)
		dwItemData = pData->m_dwItemData;

	return dwItemData;
}

void CComboboxMultiLine::SetAlertColorBkg(COLORREF crColor)
{
	m_crAlertBkg = crColor;
	m_BrushAlert.DeleteObject();
	m_BrushAlert.CreateSolidBrush(m_crAlertBkg);
}

void CComboboxMultiLine::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CComboBox::OnMouseMove(nFlags, point);

	if (! m_bShowTooltip)
		return;

	CRect rectClient;
	GetClientRect(&rectClient);
	const int nComboButtonWidth = GetSystemMetrics(SM_CXHTHUMB) + 2;
	rectClient.right = rectClient.right - nComboButtonWidth;

	if (rectClient.PtInRect(point) && ! m_bEdit && !GetDroppedState())
	{
		const int nIndex = GetCurSel();
		ClientToScreen(&rectClient);

		CString sText;
		if (! m_bTooltipOnInfo)
		{
			GetWindowText(sText);
		}
		else
		{
			if (CB_ERR != nIndex)
				GetLBInfo(nIndex, sText);
		}
		m_ToolInfo.lpszText = sText.GetBuffer(0);
		sText.ReleaseBuffer();

		if (! m_bTooltipOnInfo)
		{
			SIZE size;
			HDC hDC = ::GetDC(m_hWnd);
			CFont* pFont = GetFont();
			HFONT hOldFont = (HFONT)::SelectObject(hDC, (HFONT)*pFont);
			::GetTextExtentPoint32(hDC, sText, sText.GetLength(), &size);
			::SelectObject(hDC, hOldFont);
			::ReleaseDC(m_hWnd, hDC);

			if (! m_bToolActive && size.cx > rectClient.Width() - 6)
			{
				rectClient.left += 1;
				rectClient.top += 3;
				::SendMessage(m_hWndToolTip, TTM_UPDATETIPTEXT, (WPARAM)0, (LPARAM)&m_ToolInfo);
				::SendMessage(m_hWndToolTip, TTM_TRACKPOSITION, (WPARAM)0, (LPARAM)MAKELONG(rectClient.left, m_bEditTooltipOverItemPos ? rectClient.top - nComboButtonWidth - 1 : rectClient.top));
				::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)TRUE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
				m_bToolActive = TRUE;
				SetTimer(1, 80, NULL);
			}
			else	// text fits inside client rect
			{
				SetTimer(1, 80, NULL);
			}
		}
		else	// tooltip text is retrieved from additional info
		{
			if (! m_bToolActive && CB_ERR != nIndex && GetLBShowItemTooltipState(nIndex) && ! sText.IsEmpty())
			{
				::SendMessage(m_hWndToolTip, TTM_UPDATETIPTEXT, (WPARAM)0, (LPARAM)&m_ToolInfo);
				::SendMessage(m_hWndToolTip, TTM_TRACKPOSITION, (WPARAM)0, (LPARAM)MAKELONG(m_bShowEditTooltipOverItem ? rectClient.left + 1 : rectClient.right + nComboButtonWidth - 1, m_bEditTooltipOverItemPos ? rectClient.top - nComboButtonWidth - 1 : rectClient.top + 3));
				::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)TRUE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
				m_bToolActive = TRUE;
				SetTimer(1, 80, NULL);
			}
			else
			{
				SetTimer(1, 80, NULL);
			}
		}
	}
	else	// not inside client rect
	{
		::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
		m_bToolActive = FALSE;
		SetTimer(1, 80, NULL);
	}
}

void CComboboxMultiLine::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CComboBox::OnTimer(nIDEvent);

	CPoint point;
	::GetCursorPos(&point);
	ScreenToClient(&point);

	CRect rectClient;
	GetClientRect(&rectClient);
	rectClient.right = rectClient.right - (GetSystemMetrics(SM_CXHTHUMB) + 2);

	if (! rectClient.PtInRect(point))
	{
		KillTimer(nIDEvent);
		::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
		m_bToolActive = FALSE;
	}
}

int CComboboxMultiLine::AddStringWithInfo(LPCTSTR lpszString, LPCTSTR lpszInfo, BOOL bShowItemTooltip/* = TRUE*/)
{
	const int nIndex = (int)SendMessage(CB_ADDSTRING, (WPARAM)0, (LPARAM)lpszString);
	SetLBInfo(nIndex, lpszInfo, bShowItemTooltip);

	return nIndex;
}

int CComboboxMultiLine::InsertStringWithInfo(int nIndex, LPCTSTR lpszString, LPCTSTR lpszInfo, BOOL bShowItemTooltip/* = TRUE*/)
{
	SendMessage(CB_INSERTSTRING, (WPARAM)nIndex, (LPARAM)lpszString);
	SetLBInfo(nIndex, lpszInfo, bShowItemTooltip);

	return nIndex;
}

void CComboboxMultiLine::SetLBInfo(int nIndex, LPCTSTR lpszInfo, BOOL bShowItemTooltip/* = TRUE*/)
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(nIndex >= 0 && nIndex < GetCount());

	CItemData* pData = (CItemData*)GetItemDataPtr(nIndex);
	if (NULL != pData)
	{
		pData->m_sInfo = lpszInfo;
		pData->m_bShowItemTooltip = bShowItemTooltip;
	}
}

void CComboboxMultiLine::GetLBInfo(int nIndex, CString& rInfo) const
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(nIndex >= 0 && nIndex < GetCount());

	CItemData* pData = (CItemData*)GetItemDataPtr(nIndex);
	if (NULL != pData)
		rInfo = pData->m_sInfo;
}

void CComboboxMultiLine::SetLBShowItemTooltip(int nIndex, BOOL bShow/* = TRUE*/)
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(nIndex >= 0 && nIndex < GetCount());

	CItemData* pData = (CItemData*)GetItemDataPtr(nIndex);
	if (NULL != pData)
		pData->m_bShowItemTooltip = bShow;
}

BOOL CComboboxMultiLine::GetLBShowItemTooltipState(int nIndex) const
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(nIndex >= 0 && nIndex < GetCount());

	CItemData* pData = (CItemData*)GetItemDataPtr(nIndex);
	if (NULL != pData)
		return pData->m_bShowItemTooltip;

	return FALSE;
}
// find an list item by info string
int CComboboxMultiLine::FindInfo(int nStartAfter, LPCTSTR lpszString) const
{
	int nIndex = CB_ERR;
	CString sString(lpszString), sItem;
	sString.MakeLower();
	for (int i = nStartAfter + 1; i < GetCount(); ++i)
	{
		GetLBInfo(i, sItem);
		sItem.MakeLower();
		if (sItem.Find(sString) >= 0)
		{
			nIndex = i;
			break;
		}
	}

	return nIndex;
}
// find an list item by info string exact
int CComboboxMultiLine::FindInfoExact(int nIndexStart, LPCTSTR lpszFind) const
{
	CString sItem;
	int nIndex = CB_ERR;
	for (int i = nIndexStart + 1; i < GetCount(); ++i)
	{
		GetLBInfo(i, sItem);
		if (0 == sItem.CompareNoCase(lpszFind))
		{
			nIndex = i;
			break;
		}
	}

	return nIndex;
}
// select an list item by info string
int CComboboxMultiLine::SelectInfo(int nStartAfter, LPCTSTR lpszString)
{
	int nIndex = CB_ERR;
	CString sString(lpszString), sItem;
	sString.MakeLower();
	for (int i = nStartAfter + 1; i < GetCount(); ++i)
	{
		GetLBInfo(i, sItem);
		sItem.MakeLower();
		if (sItem.Find(sString) >= 0)
		{
			nIndex = i;
			SetCurSel(nIndex);
			break;
		}
	}

	return nIndex;
}