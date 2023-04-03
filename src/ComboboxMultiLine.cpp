/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "ComboboxMultiLine.h"

#define ID_EDIT_CHILD_COMBOBOX 1001

LRESULT CComboboxMultiLine::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PASTE:
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
			return FALSE;
		}
		return TRUE;
	}
	return CComboBox::WindowProc(message, wParam, lParam);
}

BOOL CComboboxMultiLine::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
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

void CComboboxMultiLine::SetFocusEx()
{
	CEdit* pEdit = (CEdit*)GetDlgItem(ID_EDIT_CHILD_COMBOBOX);
	if (pEdit)
	{
		pEdit->SetFocus();
		pEdit->SetSel(0, -1); // select all text and move cursor at the end
		pEdit->SetSel(-1); //  remove selection
	}
}
