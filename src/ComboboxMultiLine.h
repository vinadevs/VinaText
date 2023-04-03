/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

// Combobox must set CBS_AUTOHSCROLL to prevent limited text entry

class CComboboxMultiLine : public CComboBox
{
public:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SetFocusEx();

private:
	void GetClipboardText();
	LPTSTR m_pText;
};
