/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "GuiUtils.h"
#include "AppUtil.h"

//////////////////////////////////
// Editor UI utils

void GuiUtils::ShowToolTipOnScreen(HWND hwndTT, TOOLINFO ti, BOOL bShow, const CString & strText, int x, int y)
{
	if (bShow)
	{
		unsigned int uid = 0; // for ti initialization
							  // CREATE A TOOLTIP WINDOW
		hwndTT = CreateWindowEx(WS_EX_TOPMOST,
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
			NULL
		);
		// INITIALIZE MEMBERS OF THE TOOLINFO STRUCTURE
		ti.cbSize = TTTOOLINFO_V1_SIZE;
		ti.uFlags = TTF_TRACK;
		ti.hwnd = NULL;
		ti.hinst = NULL;
		ti.uId = uid;
		ti.lpszText = (LPTSTR)(LPCTSTR)strText;
		// ToolTip control will cover the whole window
		ti.rect.left = 0;
		ti.rect.top = 0;
		ti.rect.right = 0;
		ti.rect.bottom = 0;
		// SEND AN ADDTOOL MESSAGE TO THE TOOLTIP CONTROL WINDOW
		::SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO)&ti);
		::SendMessage(hwndTT, TTM_TRACKPOSITION, 0, (LPARAM)(DWORD)MAKELONG(x, y));
		::SendMessage(hwndTT, TTM_TRACKACTIVATE, true, (LPARAM)(LPTOOLINFO)&ti);
	}
	else
	{
		::SendMessage(hwndTT, TTM_TRACKACTIVATE, false, (LPARAM)(LPTOOLINFO)&ti);
	}
}

HICON GuiUtils::LoadIconWithSize(HINSTANCE hInstance, LPCWSTR lpIconName, int iconWidth, int iconHeight)
{
	if (iconWidth == 0)
		iconWidth = GetSystemMetrics(SM_CXSMICON);
	if (iconHeight == 0)
		iconHeight = GetSystemMetrics(SM_CYSMICON);
	HICON hIcon = NULL;
	if (FAILED(LoadIconWithScaleDown(hInstance, lpIconName, iconWidth, iconHeight, &hIcon)))
	{
		// fallback, just in case
		hIcon = static_cast<HICON>(LoadImage(hInstance, lpIconName, IMAGE_ICON, iconWidth, iconHeight, LR_DEFAULTCOLOR));
	}
	return hIcon;
}

std::unique_ptr<UINT[]> GuiUtils::HIconToImageByte(HICON hIcon)
{
	if (hIcon == NULL)
		return NULL;

	ICONINFO iconInfo;
	if (!GetIconInfo(hIcon, &iconInfo))
		return NULL;

	BITMAP bm;
	if (!GetObject(iconInfo.hbmColor, sizeof(BITMAP), &bm))
		return NULL;

	int        width = bm.bmWidth;
	int        height = bm.bmHeight;
	int        bytesPerScanLine = (width * 3 + 3) & 0xFFFFFFFC;
	int        size = bytesPerScanLine * height;
	BITMAPINFO infoHeader;
	infoHeader.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	infoHeader.bmiHeader.biWidth = width;
	infoHeader.bmiHeader.biHeight = height;
	infoHeader.bmiHeader.biPlanes = 1;
	infoHeader.bmiHeader.biBitCount = 24;
	infoHeader.bmiHeader.biCompression = BI_RGB;
	infoHeader.bmiHeader.biSizeImage = size;

	auto   ptrb = std::make_unique<BYTE[]>(2LL * size + 4LL * height * width);
	LPBYTE pixelsIconRGB = ptrb.get();
	LPBYTE alphaPixels = pixelsIconRGB + size;
	HDC hDC = CreateCompatibleDC(NULL);
	HBITMAP hBmpOld = static_cast<HBITMAP>(SelectObject(hDC, static_cast<HGDIOBJ>(iconInfo.hbmColor)));
	if (!GetDIBits(hDC, iconInfo.hbmColor, 0, height, static_cast<LPVOID>(pixelsIconRGB), &infoHeader, DIB_RGB_COLORS))
		return NULL;

	SelectObject(hDC, hBmpOld);
	if (!GetDIBits(hDC, iconInfo.hbmMask, 0, height, static_cast<LPVOID>(alphaPixels), &infoHeader, DIB_RGB_COLORS))
		return NULL;

	auto imagePixels = std::make_unique<UINT[]>(static_cast<size_t>(height) * width);
	int  lsSrc = width * 3;
	int  vsDest = height - 1;
	for (int y = 0; y < height; y++)
	{
		int linePosSrc = (vsDest - y) * lsSrc;
		int linePosDest = y * width;
		for (int x = 0; x < width; x++)
		{
			int currentDestPos = linePosDest + x;
			int currentSrcPos = linePosSrc + x * 3;
			imagePixels[currentDestPos] = (static_cast<UINT>((((pixelsIconRGB[currentSrcPos + 2] /*Red*/) | (pixelsIconRGB[currentSrcPos + 1] << 8 /*Green*/)) | pixelsIconRGB[currentSrcPos] << 16 /*Blue*/) | ((alphaPixels[currentSrcPos] ? 0 : 0xff) << 24)) & 0xffffffff);
		}
	}
	return imagePixels;
}

// name - the name of the item that is searched for
// tree - a reference to the tree control
// hRoot - the handle to the item where the search begins
HTREEITEM GuiUtils::FindTreeCtrlItem(const CString& name, CTreeCtrl& tree, HTREEITEM hRoot)
{
	// check whether the current item is the searched one
	CString text = tree.GetItemText(hRoot);
	if (text.Compare(name) == 0)
		return hRoot;
	// get a handle to the first child item
	HTREEITEM hSub = tree.GetChildItem(hRoot);
	// iterate as long a new item is found
	while (hSub)
	{
		// check the children of the current item
		HTREEITEM hFound = GuiUtils::FindTreeCtrlItem(name, tree, hSub);
		if (hFound)
			return hFound;

		// get the next sibling of the current item
		hSub = tree.GetNextSiblingItem(hSub);
	}
	// return NULL if nothing was found
	return NULL;
}

CSize GuiUtils::GetTextSize(const CString & strText)
{
	HDC textHDC = ::GetDC(NULL);
	CDC *pDC = CDC::FromHandle(textHDC);
	return CSize(pDC->GetTextExtent(strText));
}

// This simple function takes a path and gets a shell UI object from it.   
// We convert the path to a pidl with SHParseDisplayName, then bind to the   
// pidl's parent with SHBindToParent, then ask the parent for the UI object   
// of the child with IShellFolder::GetUIObjectOf  

class COleInitialize
{
public:
	COleInitialize() : m_hrOLE(OleInitialize(NULL)) { }
	~COleInitialize() { if (SUCCEEDED(m_hrOLE)) OleUninitialize(); }
	operator HRESULT() const { return m_hrOLE; }
	HRESULT m_hrOLE;
};

HRESULT GetUIObjectOfFile(HWND hwnd, LPCWSTR pszPath, REFIID riid, void **ppv)
{
	*ppv = NULL;
	HRESULT hr;
	LPITEMIDLIST pidl;
	SFGAOF sfgao;
	// Translates a Shell namespace object's display name into an item identifier list   
	// and returns the attributes of the object. This function is the preferred method   
	// to convert a string to a PIDL.  
	hr = SHParseDisplayName(pszPath, NULL, &pidl, SFGAO_CANCOPY, &sfgao);
	if (SUCCEEDED(hr)) {
		IShellFolder *psf;
		LPCITEMIDLIST pidlChild;
		if (SUCCEEDED(hr = SHBindToParent(pidl, IID_IShellFolder, (void**)&psf, &pidlChild))) {
			hr = psf->GetUIObjectOf(hwnd, 1, &pidlChild, riid, NULL, ppv);
			psf->Release();
		}
		CoTaskMemFree(pidl);
	}
	return hr;
}

BOOL GuiUtils::PushFileObjectToClipboard(const CString & strFilePath)
{
	COleInitialize init;
	CComPtr<IDataObject> spdto;
	if (SUCCEEDED(init) &&
		SUCCEEDED(GetUIObjectOfFile(nullptr,strFilePath, IID_PPV_ARGS(&spdto))) &&
		SUCCEEDED(OleSetClipboard(spdto)) &&
		SUCCEEDED(OleFlushClipboard()))
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> Copied to clipboard file %s..."), strFilePath);
		return TRUE;
	}
	return FALSE;
}