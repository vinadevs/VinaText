//
//	UXReaderToolbarPane.cpp
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderToolbarPane.h"
#include "UXReaderToolbarItem.h"
#include "UXReaderToolbarEdit.h"
#include "UXReaderToolbarText.h"

using namespace UXReader;

//
//	Constants
//

constexpr int defaultPaneHeight = 35;

static wchar_t *const kWindowClassName = L"UXReaderToolbarPaneClass";

//
//	UXReaderToolbarPane methods
//

UXReader::UXReaderToolbarPane::UXReaderToolbarPane(void)
{

	RegisterMessages();
}

UXReader::UXReaderToolbarPane::~UXReaderToolbarPane(void)
{

	m_NumberEditItem = nullptr; m_SearchEditItem = nullptr; m_SearchTextItem = nullptr;

	m_PageDecrementItem = nullptr; m_PageIncrementItem = nullptr;

	m_ZoomDecrementItem = nullptr; m_ZoomIncrementItem = nullptr;

	m_WindowHandle = nullptr; m_ParentWindow = nullptr;

}

ATOM UXReader::UXReaderToolbarPane::DoRegisterWindowClass(const HMODULE hModule)
{

	WNDCLASSEXW wcex; RtlSecureZeroMemory(&wcex, sizeof(wcex));

	wcex.hInstance = hModule;
	wcex.lpszClassName = kWindowClassName;
	wcex.style = 0; wcex.lpszMenuName = nullptr;
	wcex.lpfnWndProc = UXReaderToolbarPane::WindowDispatch;
	wcex.hIcon = nullptr; wcex.hIconSm = nullptr; wcex.hbrBackground = nullptr;
	wcex.hCursor = UXReaderSupport::ArrowCursor();
	wcex.cbClsExtra = 0; wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEXW);

	return RegisterClassExW(&wcex);
}

BOOL UXReader::UXReaderToolbarPane::UnRegisterWindowClass(const HMODULE hModule)
{

	return UnregisterClassW(kWindowClassName, hModule);
}

LRESULT CALLBACK UXReader::UXReaderToolbarPane::WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	if (message == WM_NCCREATE) SetWindowLongPtrW(hWnd, GWLP_USERDATA, LONG_PTR((LPCREATESTRUCT(lParam))->lpCreateParams));

	UXReaderToolbarPane *thisWindow = reinterpret_cast<UXReaderToolbarPane *>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

	if (thisWindow != nullptr)
		return thisWindow->WindowProcedure(hWnd, message, wParam, lParam);
	else
		return DefWindowProcW(hWnd, message, wParam, lParam);
}

LRESULT UXReader::UXReaderToolbarPane::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	auto entry = m_MessageMap.find(message);

	if (entry == m_MessageMap.end())
		return DefWindowProcW(hWnd, message, wParam, lParam);
	else
		return entry->second(hWnd, message, wParam, lParam);
}

int UXReader::UXReaderToolbarPane::PaneHeight(const HWND hWnd)
{

	if (m_PaneHeight == 0) // Determine pane height
	{
		m_PaneHeight = MulDiv(defaultPaneHeight, UXReaderSupport::DPI(hWnd), 96);
	}

	return m_PaneHeight;
}

bool UXReader::UXReaderToolbarPane::Create(const HWND hParent, const int x, const int y, const int w, const int h)
{

	const DWORD ws = (WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN); const DWORD es = (WS_EX_NOPARENTNOTIFY); // Window style

	const HWND hWnd = CreateWindowExW(es, kWindowClassName, nullptr, ws, x, y, w, h, hParent, HMENU(this), UXReaderSupport::Module(), this);

	if (hWnd == nullptr) { const DWORD ec = GetLastError(); DBLog(L"%S Unable to create window (%lu).\n", __FUNCSIG__, ec); }

	return (hWnd != nullptr);
}

void UXReader::UXReaderToolbarPane::Destroy(void)
{

	DestroyWindow(m_WindowHandle);
}

void UXReader::UXReaderToolbarPane::UpdateXYWH(const int x, const int y, const int w, const int h)
{

	SetWindowPos(m_WindowHandle, nullptr, x, y, w, h, (SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOZORDER));

	RedrawWindow(m_WindowHandle, nullptr, nullptr, (RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN)); // !!!
}

void UXReader::UXReaderToolbarPane::UpdateWH(const int w, const int h)
{

	SetWindowPos(m_WindowHandle, nullptr, 0, 0, w, h, (SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOMOVE | SWP_NOZORDER));

	RedrawWindow(m_WindowHandle, nullptr, nullptr, (RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN)); // !!!
}

//
//	Window message methods
//

void UXReader::UXReaderToolbarPane::RegisterMessages(void)
{

	m_MessageMap.emplace(WM_CREATE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowCreate(h, m, w, l); });
	m_MessageMap.emplace(WM_SIZE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowSize(h, m, w, l); });
	m_MessageMap.emplace(WM_ERASEBKGND, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowErase(h, m, w, l); });
	m_MessageMap.emplace(WM_PAINT, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowPaint(h, m, w, l); });
	m_MessageMap.emplace(WM_CONTEXTMENU, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->MenuContext(h, m, w, l); });
}

LRESULT UXReader::UXReaderToolbarPane::WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//CREATESTRUCTW *cs = reinterpret_cast<CREATESTRUCTW *>(lParam);

	m_WindowHandle = hWnd; m_ParentWindow = GetParent(hWnd);

	m_SeparatorSize = MulDiv(1, UXReaderSupport::DPI(hWnd), 96);

	AddToolbarItems(hWnd);

	return 0;
}

LRESULT UXReader::UXReaderToolbarPane::WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//const int cw = LOWORD(lParam); const int ch = HIWORD(lParam);

	return 0;
}

LRESULT UXReader::UXReaderToolbarPane::WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	return 0;
}

LRESULT UXReader::UXReaderToolbarPane::WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps {}; HDC hDC = BeginPaint(hWnd, &ps);

	if (IsRectEmpty(&ps.rcPaint) == FALSE) // Paint the requested area
	{
		RECT rect; GetClientRect(hWnd, &rect); RECT line = rect;
		rect.bottom -= m_SeparatorSize; line.top = (line.bottom - m_SeparatorSize);
		FillRect(hDC, &rect, UXReaderSupport::ToolbarPaneBackgroundBrush());
		FillRect(hDC, &line, UXReaderSupport::PaneSeparatorLineBrush());
	}

	EndPaint(hWnd, &ps);

	return 0;
}

LRESULT UXReader::UXReaderToolbarPane::MenuContext(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	return 0;
}

//
//	Support methods
//

void UXReader::UXReaderToolbarPane::AddToolbarItems(const HWND hWnd)
{

	const int DPI = UXReaderSupport::DPI(hWnd);

	RECT rect; GetClientRect(hWnd, &rect); rect.bottom -= m_SeparatorSize;
	const int cw = (rect.right - rect.left); const int ch = (rect.bottom - rect.top);
	const int in = MulDiv(8, DPI, 96); const int sp = MulDiv(2, DPI, 96);
	const int nw = 48; const int ew = 256; const int tw = 128;
	const int iw = ch; const int cy = 0; int cx = in;

	const DWORD NO = ES_CENTER; const DWORD SO = (ES_LEFT | ES_AUTOHSCROLL);

	UXReaderToolbarEdit::EditOptions_t numberEditOptions = std::make_tuple(UX_NUMBER_EDIT_FIELD, NO, 9);
	UXReaderToolbarEdit::EditOptions_t searchEditOptions = std::make_tuple(UX_SEARCH_EDIT_FIELD, SO, 99);

	m_ZoomIncrementItem = std::make_unique<UXReaderToolbarItem>(UX_ZOOM_INCREMENT);
	if (m_ZoomIncrementItem->Create(hWnd, cx, cy, iw, ch)) cx += (iw + sp); else m_ZoomIncrementItem = nullptr;

	m_ZoomDecrementItem = std::make_unique<UXReaderToolbarItem>(UX_ZOOM_DECREMENT);
	if (m_ZoomDecrementItem->Create(hWnd, cx, cy, iw, ch)) cx += (iw + sp); else m_ZoomDecrementItem = nullptr;

	m_PageIncrementItem = std::make_unique<UXReaderToolbarItem>(UX_PAGE_INCREMENT);
	if (m_PageIncrementItem->Create(hWnd, cx, cy, iw, ch)) cx += (iw + sp); else m_PageIncrementItem = nullptr;

	m_PageDecrementItem = std::make_unique<UXReaderToolbarItem>(UX_PAGE_DECREMENT);
	if (m_PageDecrementItem->Create(hWnd, cx, cy, iw, ch)) cx += (iw + sp); else m_PageDecrementItem = nullptr;

	m_NumberEditItem = std::make_unique<UXReaderToolbarEdit>(numberEditOptions); cx += in;
	if (m_NumberEditItem->Create(hWnd, cx, cy, nw, ch)) cx += (nw + sp); else m_NumberEditItem = nullptr;

	m_SearchEditItem = std::make_unique<UXReaderToolbarEdit>(searchEditOptions); cx += (in+in);
	if (m_SearchEditItem->Create(hWnd, cx, cy, ew, ch)) cx += (ew + sp); else m_SearchEditItem = nullptr;

	m_SearchTextItem = std::make_unique<UXReaderToolbarText>(UX_SEARCH_TEXT_FIELD); cx += (in+in);
	if (m_SearchTextItem->Create(hWnd, cx, cy, tw, ch)) cx += (tw + sp); else m_SearchTextItem = nullptr;
}

UXReaderToolbarItem* UXReader::UXReaderToolbarPane::PageDecrementItem(void) const
{

	return m_PageDecrementItem.get();
}

UXReaderToolbarItem* UXReader::UXReaderToolbarPane::PageIncrementItem(void) const
{

	return m_PageIncrementItem.get();
}

UXReaderToolbarItem* UXReader::UXReaderToolbarPane::ZoomDecrementItem(void) const
{

	return m_ZoomDecrementItem.get();
}

UXReaderToolbarItem* UXReader::UXReaderToolbarPane::ZoomIncrementItem(void) const
{

	return m_ZoomIncrementItem.get();
}

UXReaderToolbarEdit* UXReader::UXReaderToolbarPane::SearchEditItem(void) const
{

	return m_SearchEditItem.get();
}

UXReaderToolbarText* UXReader::UXReaderToolbarPane::SearchTextItem(void) const
{

	return m_SearchTextItem.get();
}

UXReaderToolbarEdit* UXReader::UXReaderToolbarPane::NumberEditItem(void) const
{

	return m_NumberEditItem.get();
}
