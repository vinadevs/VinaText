//
//	UXReaderBlankPane.cpp
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderBlankPane.h"

using namespace UXReader;

//
//	Constants
//

static wchar_t *const kWindowClassName = L"UXReaderBlankPaneClass";

//
//	UXReaderBlankPane methods
//

UXReader::UXReaderBlankPane::UXReaderBlankPane(void)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, this);

	RegisterMessages();
}

UXReader::UXReaderBlankPane::~UXReaderBlankPane(void)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, this);

	m_WindowHandle = nullptr; m_ParentWindow = nullptr;

	//DBLog(L"%S 0x%p\n", __FUNCSIG__, this);
}

ATOM UXReader::UXReaderBlankPane::DoRegisterWindowClass(const HMODULE hModule)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, hModule);

	WNDCLASSEXW wcex; RtlSecureZeroMemory(&wcex, sizeof(wcex));

	wcex.hInstance = hModule;
	wcex.lpszClassName = kWindowClassName;
	wcex.style = 0; wcex.lpszMenuName = nullptr;
	wcex.lpfnWndProc = UXReaderBlankPane::WindowDispatch;
	wcex.hIcon = nullptr; wcex.hIconSm = nullptr; wcex.hbrBackground = nullptr;
	wcex.hCursor = UXReaderSupport::ArrowCursor();
	wcex.cbClsExtra = 0; wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEXW);

	return RegisterClassExW(&wcex);
}

BOOL UXReader::UXReaderBlankPane::UnRegisterWindowClass(const HMODULE hModule)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, hModule);

	return UnregisterClassW(kWindowClassName, hModule);
}

LRESULT CALLBACK UXReader::UXReaderBlankPane::WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	if (message == WM_NCCREATE) SetWindowLongPtrW(hWnd, GWLP_USERDATA, LONG_PTR((LPCREATESTRUCT(lParam))->lpCreateParams));

	UXReaderBlankPane *thisWindow = reinterpret_cast<UXReaderBlankPane *>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

	if (thisWindow != nullptr)
		return thisWindow->WindowProcedure(hWnd, message, wParam, lParam);
	else
		return DefWindowProcW(hWnd, message, wParam, lParam);
}

LRESULT UXReader::UXReaderBlankPane::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	auto entry = m_MessageMap.find(message);

	if (entry == m_MessageMap.end())
		return DefWindowProcW(hWnd, message, wParam, lParam);
	else
		return entry->second(hWnd, message, wParam, lParam);
}

bool UXReader::UXReaderBlankPane::Create(const HWND hParent, const int x, const int y, const int w, const int h)
{
	//DBLog(L"%S 0x%p %i %i %i %i\n", __FUNCSIG__, hParent, x, y, w, h);

	const DWORD ws = (WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN); const DWORD es = (WS_EX_NOPARENTNOTIFY); // Window style

	const HWND hWnd = CreateWindowExW(es, kWindowClassName, nullptr, ws, x, y, w, h, hParent, HMENU(this), UXReaderSupport::Module(), this);

	if (hWnd == nullptr) { const DWORD ec = GetLastError(); DBLog(L"%S Unable to create window (%lu).\n", __FUNCSIG__, ec); }

	return (hWnd != nullptr);
}

void UXReader::UXReaderBlankPane::Destroy(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	DestroyWindow(m_WindowHandle);
}

void UXReader::UXReaderBlankPane::UpdateXYWH(const int x, const int y, const int w, const int h)
{
	//DBLog(L"%S %i %i %i %i\n", __FUNCSIG__, x, y, w, h);

	SetWindowPos(m_WindowHandle, nullptr, x, y, w, h, (SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOZORDER));

	RedrawWindow(m_WindowHandle, nullptr, nullptr, (RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN)); // !!!
}

void UXReader::UXReaderBlankPane::UpdateWH(const int w, const int h)
{
	//DBLog(L"%S %i %i\n", __FUNCSIG__, w, h);

	SetWindowPos(m_WindowHandle, nullptr, 0, 0, w, h, (SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOMOVE | SWP_NOZORDER));

	RedrawWindow(m_WindowHandle, nullptr, nullptr, (RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN)); // !!!
}

//
//	Window message methods
//

void UXReader::UXReaderBlankPane::RegisterMessages(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	m_MessageMap.emplace(WM_CREATE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowCreate(h, m, w, l); });
	m_MessageMap.emplace(WM_SIZE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowSize(h, m, w, l); });
	m_MessageMap.emplace(WM_ERASEBKGND, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowErase(h, m, w, l); });
	m_MessageMap.emplace(WM_PAINT, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowPaint(h, m, w, l); });
}

LRESULT UXReader::UXReaderBlankPane::WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p 0x%p\n", __FUNCSIG__, hWnd, wParam, lParam);

	//CREATESTRUCTW *cs = reinterpret_cast<CREATESTRUCTW *>(lParam);

	m_WindowHandle = hWnd; m_ParentWindow = GetParent(hWnd);

	return 0;
}

LRESULT UXReader::UXReaderBlankPane::WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p 0x%p\n", __FUNCSIG__, hWnd, wParam, lParam);

	//const int cw = LOWORD(lParam); const int ch = HIWORD(lParam);

	return 0;
}

LRESULT UXReader::UXReaderBlankPane::WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p 0x%p\n", __FUNCSIG__, hWnd, wParam, lParam);

	return 0;
}

LRESULT UXReader::UXReaderBlankPane::WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p 0x%p\n", __FUNCSIG__, hWnd, wParam, lParam);

	PAINTSTRUCT ps {}; HDC hDC = BeginPaint(hWnd, &ps);

	if (IsRectEmpty(&ps.rcPaint) == FALSE) // Paint the requested area
	{
		FillRect(hDC, &ps.rcPaint, UXReaderSupport::DocumentBackgroundBrush());
		HGDIOBJ font = UXReaderSupport::SystemFont(hWnd); HGDIOBJ oldFont = SelectObject(hDC, font);
		SetTextColor(hDC, 0x00FFFFFF); SetBkMode(hDC, TRANSPARENT); RECT area; GetClientRect(hWnd, &area);
		DrawTextW(hDC, kWindowClassName, -1, &area, (DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP | DT_NOPREFIX));
		SelectObject(hDC, oldFont);
	}

	EndPaint(hWnd, &ps);

	return 0;
}
