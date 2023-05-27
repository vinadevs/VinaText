//
//	UXReaderToolbarText.cpp
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderToolbarText.h"

using namespace UXReader;

//
//	Constants
//

static wchar_t *const kWindowClassName = L"UXReaderToolbarTextClass";

//
//	UXReaderToolbarText methods
//

UXReader::UXReaderToolbarText::UXReaderToolbarText(const int id)
{

	m_ItemID = id; RegisterMessages();
}

UXReader::UXReaderToolbarText::~UXReaderToolbarText(void)
{

	m_WindowHandle = nullptr; m_ParentWindow = nullptr;

}

ATOM UXReader::UXReaderToolbarText::DoRegisterWindowClass(const HMODULE hModule)
{

	WNDCLASSEXW wcex; RtlSecureZeroMemory(&wcex, sizeof(wcex));

	wcex.hInstance = hModule;
	wcex.lpszClassName = kWindowClassName;
	wcex.style = 0; wcex.lpszMenuName = nullptr;
	wcex.lpfnWndProc = UXReaderToolbarText::WindowDispatch;
	wcex.hIcon = nullptr; wcex.hIconSm = nullptr; wcex.hbrBackground = nullptr;
	wcex.hCursor = UXReaderSupport::ArrowCursor();
	wcex.cbClsExtra = 0; wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEXW);

	return RegisterClassExW(&wcex);
}

BOOL UXReader::UXReaderToolbarText::UnRegisterWindowClass(const HMODULE hModule)
{

	return UnregisterClassW(kWindowClassName, hModule);
}

LRESULT CALLBACK UXReader::UXReaderToolbarText::WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	if (message == WM_NCCREATE) SetWindowLongPtrW(hWnd, GWLP_USERDATA, LONG_PTR((LPCREATESTRUCT(lParam))->lpCreateParams));

	UXReaderToolbarText *thisWindow = reinterpret_cast<UXReaderToolbarText *>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

	if (thisWindow != nullptr)
		return thisWindow->WindowProcedure(hWnd, message, wParam, lParam);
	else
		return DefWindowProcW(hWnd, message, wParam, lParam);
}

LRESULT UXReader::UXReaderToolbarText::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	auto entry = m_MessageMap.find(message);

	if (entry == m_MessageMap.end())
		return DefWindowProcW(hWnd, message, wParam, lParam);
	else
		return entry->second(hWnd, message, wParam, lParam);
}

bool UXReader::UXReaderToolbarText::Create(const HWND hParent, const int x, const int y, const int w, const int h)
{

	const DWORD ws = (WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN); const DWORD es = (WS_EX_NOPARENTNOTIFY); // Window style

	const HWND hWnd = CreateWindowExW(es, kWindowClassName, nullptr, ws, x, y, w, h, hParent, HMENU(this), UXReaderSupport::Module(), this);

	if (hWnd == nullptr) { const DWORD ec = GetLastError(); DBLog(L"%S Unable to create window (%lu).\n", __FUNCSIG__, ec); }

	return (hWnd != nullptr);
}

void UXReader::UXReaderToolbarText::Destroy(void)
{

	DestroyWindow(m_WindowHandle);
}

void UXReader::UXReaderToolbarText::UpdateXYWH(const int x, const int y, const int w, const int h)
{

	SetWindowPos(m_WindowHandle, nullptr, x, y, w, h, (SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOZORDER));

	RedrawWindow(m_WindowHandle, nullptr, nullptr, (RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN)); // !!!
}

void UXReader::UXReaderToolbarText::UpdateWH(const int w, const int h)
{

	SetWindowPos(m_WindowHandle, nullptr, 0, 0, w, h, (SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOMOVE | SWP_NOZORDER));

	RedrawWindow(m_WindowHandle, nullptr, nullptr, (RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN)); // !!!
}

//
//	Window message methods
//

void UXReader::UXReaderToolbarText::RegisterMessages(void)
{

	m_MessageMap.emplace(WM_CREATE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowCreate(h, m, w, l); });
	m_MessageMap.emplace(WM_SIZE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowSize(h, m, w, l); });
	m_MessageMap.emplace(WM_ERASEBKGND, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowErase(h, m, w, l); });
	m_MessageMap.emplace(WM_PAINT, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowPaint(h, m, w, l); });
}

LRESULT UXReader::UXReaderToolbarText::WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//CREATESTRUCTW *cs = reinterpret_cast<CREATESTRUCTW *>(lParam);

	m_WindowHandle = hWnd; m_ParentWindow = GetParent(hWnd);

	m_BackgroundBrush = UXReaderSupport::ToolbarPaneBackgroundBrush();

	return 0;
}

LRESULT UXReader::UXReaderToolbarText::WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//const int cw = LOWORD(lParam); const int ch = HIWORD(lParam);

	return 0;
}

LRESULT UXReader::UXReaderToolbarText::WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	return 0;
}

LRESULT UXReader::UXReaderToolbarText::WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps {}; HDC hDC = BeginPaint(hWnd, &ps);

	if (IsRectEmpty(&ps.rcPaint) == FALSE) HandlePaint(hWnd, hDC);

	EndPaint(hWnd, &ps);

	return 0;
}

//
//	API methods
//

void UXReader::UXReaderToolbarText::HandlePaint(const HWND hWnd, const HDC hDC)
{

	const UINT options = (DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP | DT_NOPREFIX);

	RECT area; GetClientRect(hWnd, &area); FillRect(hDC, &area, m_BackgroundBrush);
	const HGDIOBJ font = UXReaderSupport::SystemFont(hWnd); const HGDIOBJ oldFont = SelectObject(hDC, font);
	SetTextColor(hDC, m_TextColor); SetBkMode(hDC, TRANSPARENT); //SetBkColor(hDC, 0x00FFFFFF);
	DrawTextW(hDC, m_Text.data(), int(m_Text.length()), &area, options);
	SelectObject(hDC, oldFont);
}

void UXReader::UXReaderToolbarText::RenderText(const std::wstring& text, const DWORD textColor)
{

	if ((text != m_Text) || (textColor != m_TextColor))
	{
		m_Text = text; m_TextColor = textColor; const HWND hWnd = m_WindowHandle;

		if (HDC hDC = GetDC(hWnd)) { HandlePaint(hWnd, hDC); ReleaseDC(hWnd, hDC); }
	}
}

void UXReader::UXReaderToolbarText::UpdateText(const std::wstring& text, const DWORD textColor)
{

	if ((text != m_Text) || (textColor != m_TextColor))
	{
		m_Text = text; m_TextColor = textColor; InvalidateRect(m_WindowHandle, nullptr, FALSE);
	}
}

void UXReader::UXReaderToolbarText::BackgroundBrush(const HBRUSH hBrush)
{

	if (hBrush != m_BackgroundBrush)
	{
		m_BackgroundBrush = hBrush; InvalidateRect(m_WindowHandle, nullptr, FALSE);
	}
}
