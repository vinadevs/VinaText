//
//	UXReaderToolbarItem.cpp
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderToolbarItem.h"

using namespace UXReader;

//
//	Constants
//

static wchar_t *const kWindowClassName = L"UXReaderToolbarItemClass";

//
//	UXReaderToolbarItem methods
//

UXReader::UXReaderToolbarItem::UXReaderToolbarItem(const int id)
{

	m_ItemID = id; RegisterMessages();
}

UXReader::UXReaderToolbarItem::~UXReaderToolbarItem(void)
{

	m_WindowHandle = nullptr; m_ParentWindow = nullptr; m_TooltipPane = nullptr; m_Icon = nullptr;

}

ATOM UXReader::UXReaderToolbarItem::DoRegisterWindowClass(const HMODULE hModule)
{

	WNDCLASSEXW wcex; RtlSecureZeroMemory(&wcex, sizeof(wcex));

	wcex.hInstance = hModule;
	wcex.lpszClassName = kWindowClassName;
	wcex.style = 0; wcex.lpszMenuName = nullptr;
	wcex.lpfnWndProc = UXReaderToolbarItem::WindowDispatch;
	wcex.hIcon = nullptr; wcex.hIconSm = nullptr; wcex.hbrBackground = nullptr;
	wcex.hCursor = UXReaderSupport::ArrowCursor();
	wcex.cbClsExtra = 0; wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEXW);

	return RegisterClassExW(&wcex);
}

BOOL UXReader::UXReaderToolbarItem::UnRegisterWindowClass(const HMODULE hModule)
{

	return UnregisterClassW(kWindowClassName, hModule);
}

LRESULT CALLBACK UXReader::UXReaderToolbarItem::WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	if (message == WM_NCCREATE) SetWindowLongPtrW(hWnd, GWLP_USERDATA, LONG_PTR((LPCREATESTRUCT(lParam))->lpCreateParams));

	UXReaderToolbarItem *thisWindow = reinterpret_cast<UXReaderToolbarItem *>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

	if (thisWindow != nullptr)
		return thisWindow->WindowProcedure(hWnd, message, wParam, lParam);
	else
		return DefWindowProcW(hWnd, message, wParam, lParam);
}

LRESULT UXReader::UXReaderToolbarItem::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	auto entry = m_MessageMap.find(message);

	if (entry == m_MessageMap.end())
		return DefWindowProcW(hWnd, message, wParam, lParam);
	else
		return entry->second(hWnd, message, wParam, lParam);
}

bool UXReader::UXReaderToolbarItem::Create(const HWND hParent, const int x, const int y, const int w, const int h)
{

	const DWORD ws = (WS_CHILD | WS_VISIBLE | WS_DISABLED); const DWORD es = (WS_EX_NOPARENTNOTIFY); // Window style

	const HWND hWnd = CreateWindowExW(es, kWindowClassName, nullptr, ws, x, y, w, h, hParent, HMENU(this), UXReaderSupport::Module(), this);

	if (hWnd == nullptr) { const DWORD ec = GetLastError(); DBLog(L"%S Unable to create window (%lu).\n", __FUNCSIG__, ec); }

	return (hWnd != nullptr);
}

void UXReader::UXReaderToolbarItem::Destroy(void)
{

	DestroyWindow(m_WindowHandle);
}

void UXReader::UXReaderToolbarItem::UpdateXYWH(const int x, const int y, const int w, const int h)
{

	SetWindowPos(m_WindowHandle, nullptr, x, y, w, h, (SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOZORDER));

	RedrawWindow(m_WindowHandle, nullptr, nullptr, (RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN)); // !!!
}

void UXReader::UXReaderToolbarItem::UpdateWH(const int w, const int h)
{

	SetWindowPos(m_WindowHandle, nullptr, 0, 0, w, h, (SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOMOVE | SWP_NOZORDER));

	RedrawWindow(m_WindowHandle, nullptr, nullptr, (RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN)); // !!!
}

//
//	Window message methods
//

void UXReader::UXReaderToolbarItem::RegisterMessages(void)
{

	m_MessageMap.emplace(WM_CREATE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowCreate(h, m, w, l); });
	m_MessageMap.emplace(WM_SIZE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowSize(h, m, w, l); });
	m_MessageMap.emplace(WM_ERASEBKGND, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowErase(h, m, w, l); });
	m_MessageMap.emplace(WM_PAINT, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowPaint(h, m, w, l); });
	m_MessageMap.emplace(WM_MOUSEMOVE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->MouseMove(h, m, w, l); });
	m_MessageMap.emplace(WM_MOUSELEAVE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->MouseLeave(h, m, w, l); });
	m_MessageMap.emplace(WM_LBUTTONDOWN, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->MouseDown(h, m, w, l); });
	m_MessageMap.emplace(WM_LBUTTONUP, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->MouseLift(h, m, w, l); });
}

LRESULT UXReader::UXReaderToolbarItem::WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//CREATESTRUCTW *cs = reinterpret_cast<CREATESTRUCTW *>(lParam);

	m_WindowHandle = hWnd; m_ParentWindow = GetParent(hWnd); AddItemTooltip(hWnd);

	m_HighlightInset = MulDiv(2, UXReaderSupport::DPI(hWnd), 96); GetClientRect(hWnd, &m_HighlightArea);

	InflateRect(&m_HighlightArea, -m_HighlightInset, -m_HighlightInset);

	if (const HDC hDC = GetDC(hWnd))
	{
		m_Icon = UXReaderResource::Icon(hDC, m_ItemID, 20, 20); ReleaseDC(hWnd, hDC);
	}

	return 0;
}

LRESULT UXReader::UXReaderToolbarItem::WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//const int cw = LOWORD(lParam); const int ch = HIWORD(lParam);

	return 0;
}

LRESULT UXReader::UXReaderToolbarItem::WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	return 0;
}

LRESULT UXReader::UXReaderToolbarItem::WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps {}; HDC hDC = BeginPaint(hWnd, &ps);

	if (IsRectEmpty(&ps.rcPaint) == FALSE) // Paint the requested area
	{
		RECT area; GetClientRect(hWnd, &area); const int cx = 0; const int cy = 0;
		const int cw = (area.right - area.left); const int ch = (area.bottom - area.top);

		FillRect(hDC, &area, UXReaderSupport::ToolbarPaneBackgroundBrush());

		if (m_MouseDown == true)
			FillRect(hDC, &m_HighlightArea, UXReaderSupport::ToolbarItemSelectedBrush());
		else if (m_TrackingMouse == true)
			FillRect(hDC, &m_HighlightArea, UXReaderSupport::ToolbarItemHighlightBrush());

		if (m_Icon != nullptr) // Draw icon
		{
			if (const HDC memDC = CreateCompatibleDC(hDC))
			{
				BITMAP bm; RtlSecureZeroMemory(&bm, sizeof(bm));

				if (GetObjectW(m_Icon, sizeof(bm), &bm) != 0) // Blit
				{
					const int iw = bm.bmWidth; const int ix = ((cw - iw) / 2);
					const int ih = bm.bmHeight; const int iy = ((ch - ih) / 2);

					const BYTE alpha = (IsWindowEnabled(hWnd) ? 255 : 95);
					const HGDIOBJ oldObject = SelectObject(memDC, m_Icon);
					BLENDFUNCTION bf = {AC_SRC_OVER, 0, alpha, AC_SRC_ALPHA};
					GdiAlphaBlend(hDC, ix, iy, iw, ih, memDC, cx, cy, iw, ih, bf);
					SelectObject(memDC, oldObject); DeleteDC(memDC);
				}
			}
		}
	}

	EndPaint(hWnd, &ps);

	return 0;
}

LRESULT UXReader::UXReaderToolbarItem::MouseMove(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if (m_TrackingMouse == false) { TrackMouse(hWnd); RedrawItem(hWnd); }

	return 0;
}

LRESULT UXReader::UXReaderToolbarItem::MouseLeave(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	m_TrackingMouse = m_MouseDown = false; RedrawItem(hWnd);

	return 0;
}

LRESULT UXReader::UXReaderToolbarItem::MouseDown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	m_MouseDown = true; RedrawItem(hWnd);

	return 0;
}

LRESULT UXReader::UXReaderToolbarItem::MouseLift(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	m_MouseDown = false; RedrawItem(hWnd);

	if (fn_ItemClicked) fn_ItemClicked(m_ItemID);

	return 0;
}

//
//	Support methods
//

void UXReader::UXReaderToolbarItem::RedrawItem(const HWND hWnd)
{

	InvalidateRect(hWnd, nullptr, FALSE);
}

void UXReader::UXReaderToolbarItem::AddItemTooltip(const HWND hWnd)
{

	const HMODULE hModule = UXReaderSupport::Module();

	const DWORD ws = (WS_POPUP | TTS_NOPREFIX); const DWORD es = (WS_EX_TOPMOST);

	if (m_TooltipPane = CreateWindowExW(es, TOOLTIPS_CLASSW, nullptr, ws, 0, 0, 0, 0, hWnd, nullptr, hModule, nullptr))
	{
		SetWindowPos(m_TooltipPane, HWND_TOPMOST, 0, 0, 0, 0, (SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE));

		TOOLINFOW ti; RtlSecureZeroMemory(&ti, sizeof(ti)); ti.cbSize = sizeof(ti); ti.uFlags = TTF_SUBCLASS;
		ti.hwnd = hWnd; ti.lpszText = LPWSTR(UXReaderResource::String(m_ItemID)); GetClientRect(hWnd, &ti.rect);

		SendMessageW(m_TooltipPane, TTM_ADDTOOL, 0, LPARAM(&ti));
	}
}

void UXReader::UXReaderToolbarItem::TrackMouse(const HWND hWnd)
{

	m_MouseDown = ((GetKeyState(VK_LBUTTON) & 0x8000) ? true : false);

	TRACKMOUSEEVENT tme; tme.cbSize = sizeof(tme); tme.hwndTrack = hWnd;

	tme.dwHoverTime = HOVER_DEFAULT; tme.dwFlags = TME_LEAVE;

	m_TrackingMouse = TrackMouseEvent(&tme);
}

void UXReader::UXReaderToolbarItem::ItemClicked(std::function<void(int)> itemClicked)
{

	fn_ItemClicked = itemClicked;
}

void UXReader::UXReaderToolbarItem::Enable(const bool enable)
{

	const HWND hWnd = m_WindowHandle;

	if ((IsWindowEnabled(hWnd) ? true : false) != enable)
	{
		if (enable == false) m_TrackingMouse = m_MouseDown = false;

		EnableWindow(hWnd, enable); RedrawItem(hWnd);
	}
}
