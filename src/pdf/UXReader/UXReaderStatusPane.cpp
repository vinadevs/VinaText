//
//	UXReaderStatusPane.cpp
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderStatusPane.h"

using namespace UXReader;

//
//	Constants
//

constexpr int DefaultPaneHeight = 25;

static wchar_t *const kWindowClassName = L"UXReaderStatusPaneClass";

//
//	UXReaderStatusPane methods
//

UXReader::UXReaderStatusPane::UXReaderStatusPane(void)
{

	RegisterMessages();
}

UXReader::UXReaderStatusPane::~UXReaderStatusPane(void)
{

	m_WindowHandle = nullptr; m_ParentWindow = nullptr;

}

ATOM UXReader::UXReaderStatusPane::DoRegisterWindowClass(const HMODULE hModule)
{

	WNDCLASSEXW wcex; RtlSecureZeroMemory(&wcex, sizeof(wcex));

	wcex.hInstance = hModule;
	wcex.lpszClassName = kWindowClassName;
	wcex.style = 0; wcex.lpszMenuName = nullptr;
	wcex.lpfnWndProc = UXReaderStatusPane::WindowDispatch;
	wcex.hIcon = nullptr; wcex.hIconSm = nullptr; wcex.hbrBackground = nullptr;
	wcex.hCursor = UXReaderSupport::ArrowCursor();
	wcex.cbClsExtra = 0; wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEXW);

	return RegisterClassExW(&wcex);
}

BOOL UXReader::UXReaderStatusPane::UnRegisterWindowClass(const HMODULE hModule)
{

	return UnregisterClassW(kWindowClassName, hModule);
}

LRESULT CALLBACK UXReader::UXReaderStatusPane::WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	if (message == WM_NCCREATE) SetWindowLongPtrW(hWnd, GWLP_USERDATA, LONG_PTR((LPCREATESTRUCT(lParam))->lpCreateParams));

	UXReaderStatusPane *thisWindow = reinterpret_cast<UXReaderStatusPane *>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

	if (thisWindow != nullptr)
		return thisWindow->WindowProcedure(hWnd, message, wParam, lParam);
	else
		return DefWindowProcW(hWnd, message, wParam, lParam);
}

LRESULT UXReader::UXReaderStatusPane::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	auto entry = m_MessageMap.find(message);

	if (entry == m_MessageMap.end())
		return DefWindowProcW(hWnd, message, wParam, lParam);
	else
		return entry->second(hWnd, message, wParam, lParam);
}

int UXReader::UXReaderStatusPane::PaneHeight(const HWND hWnd)
{

	if (m_PaneHeight == 0) // Determine pane height
	{
		m_PaneHeight = MulDiv(DefaultPaneHeight, UXReaderSupport::DPI(hWnd), 96);
	}

	return m_PaneHeight;
}

bool UXReader::UXReaderStatusPane::Create(const HWND hParent, const int x, const int y, const int w, const int h)
{

	const DWORD ws = (WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN); const DWORD es = (WS_EX_NOPARENTNOTIFY); // Window style

	const HWND hWnd = CreateWindowExW(es, kWindowClassName, nullptr, ws, x, y, w, h, hParent, HMENU(this), UXReaderSupport::Module(), this);

	if (hWnd == nullptr) { const DWORD ec = GetLastError(); DBLog(L"%S Unable to create window (%lu).\n", __FUNCSIG__, ec); }

	return (hWnd != nullptr);
}

void UXReader::UXReaderStatusPane::Destroy(void)
{

	DestroyWindow(m_WindowHandle);
}

void UXReader::UXReaderStatusPane::UpdateXYWH(const int x, const int y, const int w, const int h)
{

	SetWindowPos(m_WindowHandle, nullptr, x, y, w, h, (SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOZORDER));

	RedrawWindow(m_WindowHandle, nullptr, nullptr, (RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN)); // !!!
}

void UXReader::UXReaderStatusPane::UpdateWH(const int w, const int h)
{

	SetWindowPos(m_WindowHandle, nullptr, 0, 0, w, h, (SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOMOVE | SWP_NOZORDER));

	RedrawWindow(m_WindowHandle, nullptr, nullptr, (RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN)); // !!!
}

//
//	Window message methods
//

void UXReader::UXReaderStatusPane::RegisterMessages(void)
{

	m_MessageMap.emplace(WM_CREATE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowCreate(h, m, w, l); });
	m_MessageMap.emplace(WM_SIZE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowSize(h, m, w, l); });
	m_MessageMap.emplace(WM_ERASEBKGND, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowErase(h, m, w, l); });
	m_MessageMap.emplace(WM_PAINT, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowPaint(h, m, w, l); });
	m_MessageMap.emplace(WM_CONTEXTMENU, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->MenuContext(h, m, w, l); });
}

LRESULT UXReader::UXReaderStatusPane::WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//CREATESTRUCTW *cs = reinterpret_cast<CREATESTRUCTW *>(lParam);

	m_WindowHandle = hWnd; m_ParentWindow = GetParent(hWnd);

	m_SeparatorSize = MulDiv(1, UXReaderSupport::DPI(hWnd), 96);

	return 0;
}

LRESULT UXReader::UXReaderStatusPane::WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//const int cw = LOWORD(lParam); const int ch = HIWORD(lParam);

	return 0;
}

LRESULT UXReader::UXReaderStatusPane::WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	return 0;
}

LRESULT UXReader::UXReaderStatusPane::WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps {}; HDC hDC = BeginPaint(hWnd, &ps);

	if (IsRectEmpty(&ps.rcPaint) == FALSE) // Paint the requested area
	{
		RECT rect; GetClientRect(hWnd, &rect); RECT line = rect;
		rect.top += m_SeparatorSize; line.bottom = (line.top + m_SeparatorSize);
		FillRect(hDC, &rect, UXReaderSupport::StatusPaneBackgroundBrush());
		FillRect(hDC, &line, UXReaderSupport::PaneSeparatorLineBrush());

		//FillRect(hDC, &ps.rcPaint, UXReaderSupport::StatusPaneBackgroundBrush());
		//HGDIOBJ font = UXReaderSupport::SystemFont(hWnd); HGDIOBJ oldFont = SelectObject(hDC, font);
		//SetTextColor(hDC, 0x00000000); SetBkMode(hDC, TRANSPARENT); //RECT area; GetClientRect(hWnd, &area);
		//DrawTextW(hDC, kWindowClassName, -1, &rect, (DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP | DT_NOPREFIX));
		//SelectObject(hDC, oldFont);
	}

	EndPaint(hWnd, &ps);

	return 0;
}

LRESULT UXReader::UXReaderStatusPane::MenuContext(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	return 0;
}
