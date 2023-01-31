/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

//////////////////////////////////
// UI utils

namespace GuiUtils
{
	void ShowToolTipOnScreen(HWND hwndTT, TOOLINFO ti, BOOL bShow, const CString& strText, int x, int y);
	HICON LoadIconWithSize(HINSTANCE hInstance, LPCWSTR lpIconName, int iconWidth, int iconHeight);
	std::unique_ptr<UINT[]> HIconToImageByte(HICON hIcon);
	HTREEITEM FindTreeCtrlItem(const CString & name, CTreeCtrl & tree, HTREEITEM hRoot);
	CSize GetTextSize(const CString& strText);
	BOOL PushFileObjectToClipboard(const CString& strFilePath);
	inline void ForceRedrawCWnd(CWnd * pWnd)
	{
		if (pWnd) 
		{
			pWnd->RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
		}
	}
}
