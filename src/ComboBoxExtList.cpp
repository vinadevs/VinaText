/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

// Original version could be found here by _Flaviu
// https://www.codeproject.com/Articles/187753/Extended-CComboBox

#include "stdafx.h"
#include "ComboboxMultiLine.h"

/////////////////////////////////////////////////////////////////////////////
// CComboBoxExtList

CComboBoxExtList::CComboBoxExtList()
	:m_bShowTooltip(TRUE)
	,m_bTooltipOnInfo(FALSE)
	,m_bShowListTooltipOverItem(FALSE)
	,m_bToolActive(FALSE)
	,m_nPrevItem(-1)
	,m_pComboBox(NULL)
	,m_hWndToolTip(NULL)
{
	memset(&m_ToolInfo, 0, sizeof(m_ToolInfo));
}

BEGIN_MESSAGE_MAP(CComboBoxExtList, CListBox)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_MESSAGE(LB_FINDSTRING, CComboBoxExtList::OnLbFindString)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboBoxExtList message handlers

void CComboBoxExtList::PreSubclassWindow()
{
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

	CListBox::PreSubclassWindow();
}

LRESULT CComboBoxExtList::OnLbFindString(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(LB_FINDSTRINGEXACT, wParam, lParam);
}

void CComboBoxExtList::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CListBox::OnMouseMove(nFlags, point);

	if (NULL == m_pComboBox || ! m_bShowTooltip)
		return;

	CRect rectClient;
	GetClientRect(&rectClient);

	if (rectClient.PtInRect(point))
	{
		CPoint pointScreen;
		::GetCursorPos(&pointScreen);
		BOOL bOutside = FALSE;
		const int nItem = ItemFromPoint(point, bOutside);  // calculate listbox item number (if any)

		if (! bOutside && nItem >= 0 && m_nPrevItem != nItem)
		{
			m_nPrevItem = nItem;
			m_bToolActive = FALSE;

			CString sText;
			if (! m_bTooltipOnInfo)
				GetText(nItem, sText);
			else
				m_pComboBox->GetLBInfo(nItem, sText);
			m_ToolInfo.lpszText = sText.GetBuffer(0);
			sText.ReleaseBuffer();

			CRect rect;
			GetItemRect(nItem, &rect);
			ClientToScreen(&rect);

			if (! m_bTooltipOnInfo)
			{
				SIZE size;
				HDC hDC = ::GetDC(m_hWnd);
				CFont* pFont = GetFont();
				HFONT hOldFont = (HFONT)::SelectObject(hDC, (HFONT)*pFont);
				::GetTextExtentPoint32(hDC, sText, sText.GetLength(), &size);
				::SelectObject(hDC, hOldFont);
				::ReleaseDC(m_hWnd, hDC);

				if (! m_bToolActive && size.cx > rect.Width() - 3)
				{
					::SendMessage(m_hWndToolTip, TTM_UPDATETIPTEXT, (WPARAM)0, (LPARAM)&m_ToolInfo);
					::SendMessage(m_hWndToolTip, TTM_TRACKPOSITION, (WPARAM)0, (LPARAM)MAKELONG(rect.left, rect.top));
					::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)TRUE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
					m_bToolActive = TRUE;
				}
				else
				{
					::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
					m_bToolActive = FALSE;
					SetTimer(1, 80, NULL);
				}
			}
			else	// tooltip text is retrieved from additional info
			{
				if (! m_bToolActive && m_pComboBox->GetLBShowItemTooltipState(nItem) && ! sText.IsEmpty())
				{
					::SendMessage(m_hWndToolTip, TTM_UPDATETIPTEXT, (WPARAM)0, (LPARAM)&m_ToolInfo);
					::SendMessage(m_hWndToolTip, TTM_TRACKPOSITION, (WPARAM)0, (LPARAM)MAKELONG(m_bShowListTooltipOverItem ? rect.left : rect.right + 1, rect.top));
					::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)TRUE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
					m_bToolActive = TRUE;
				}
				else
				{
					::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
					m_bToolActive = FALSE;
					SetTimer(1, 80, NULL);
				}
			}
		}
	}
	else
	{
		::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
		m_bToolActive = FALSE;
		m_nPrevItem = -1;
		SetTimer(1, 80, NULL);
	}
}

void CComboBoxExtList::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CListBox::OnTimer(nIDEvent);

	CPoint point;
	::GetCursorPos(&point);
	ScreenToClient(&point);

	CRect rectClient;
	GetClientRect(&rectClient);

	if (! rectClient.PtInRect(point) || 0 == (GetStyle() & WS_VISIBLE))
	{
		KillTimer(nIDEvent);
		::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
		m_bToolActive = FALSE;
		m_nPrevItem = -1;
	}
}