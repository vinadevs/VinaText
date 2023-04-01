//
//	UXReaderDocumentPane.cpp
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderDocument.h"
#include "UXReaderDocumentPane.h"
#include "UXReaderDocumentPage.h"
#include "UXReaderPageCache.h"
#include "UXReaderAction.h"
#include "UXReaderDestination.h"
#include "UXReaderSelection.h"

using namespace UXReader;

//
//	Constants
//

constexpr int paintTimerTick = 100;
constexpr int paintTimerTock = 300;

constexpr int cachePagesLimit = 16;
constexpr int useBitmapsLimit = 3072;

constexpr double lineScrollFactor = 0.08;
constexpr double wheelScrollFactor = 0.08;
constexpr double pageScrollFactor = 0.95;

static wchar_t *const kWindowClassName = L"UXReaderDocumentPaneClass";

//
//	UXReaderDocumentPane methods
//

UXReader::UXReaderDocumentPane::UXReaderDocumentPane(const std::shared_ptr<UXReaderDocument>& document)
{

	m_Document = document; m_CurrentPage = NEGATORY; RegisterMessages();
}

UXReader::UXReaderDocumentPane::~UXReaderDocumentPane(void)
{

	SetCursor(UXReaderSupport::WaitCursor());

	CancelSearch(); m_PageFrames.clear(); m_VisiblePages.clear();

	m_Action = nullptr; m_PaneTooltip = nullptr; m_PageCache = nullptr; m_Document = nullptr;

	m_WindowHandle = nullptr; m_ParentWindow = nullptr;

}

ATOM UXReader::UXReaderDocumentPane::DoRegisterWindowClass(const HMODULE hModule)
{

	WNDCLASSEXW wcex; RtlSecureZeroMemory(&wcex, sizeof(wcex));

	wcex.hInstance = hModule;
	wcex.lpszClassName = kWindowClassName;
	wcex.style = 0; wcex.lpszMenuName = nullptr;
	wcex.lpfnWndProc = UXReaderDocumentPane::WindowDispatch;
	wcex.hIcon = nullptr; wcex.hIconSm = nullptr; wcex.hbrBackground = nullptr;
	wcex.hCursor = UXReaderSupport::ArrowCursor();
	wcex.cbClsExtra = 0; wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEXW);

	return RegisterClassExW(&wcex);
}

BOOL UXReader::UXReaderDocumentPane::UnRegisterWindowClass(const HMODULE hModule)
{

	return UnregisterClassW(kWindowClassName, hModule);
}

LRESULT CALLBACK UXReader::UXReaderDocumentPane::WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	if (message == WM_NCCREATE) SetWindowLongPtrW(hWnd, GWLP_USERDATA, LONG_PTR((LPCREATESTRUCT(lParam))->lpCreateParams));

	UXReaderDocumentPane *thisWindow = reinterpret_cast<UXReaderDocumentPane *>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

	if (thisWindow != nullptr)
		return thisWindow->WindowProcedure(hWnd, message, wParam, lParam);
	else
		return DefWindowProcW(hWnd, message, wParam, lParam);
}

LRESULT UXReader::UXReaderDocumentPane::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	auto entry = m_MessageMap.find(message);

	if (entry == m_MessageMap.end())
		return DefWindowProcW(hWnd, message, wParam, lParam);
	else
		return entry->second(hWnd, message, wParam, lParam);
}

bool UXReader::UXReaderDocumentPane::Create(const HWND hParent, const int x, const int y, const int w, const int h)
{

	if ((m_Document == nullptr) || (m_Document->IsOpen() == false)) return false;

	const DWORD ws = (WS_CHILD | WS_VISIBLE | WS_DISABLED); const DWORD es = (WS_EX_NOPARENTNOTIFY); // Window style

	const HWND hWnd = CreateWindowExW(es, kWindowClassName, nullptr, ws, x, y, w, h, hParent, HMENU(this), UXReaderSupport::Module(), this);

	if (hWnd == nullptr) { const DWORD ec = GetLastError(); DBLog(L"%S Unable to create window (%lu).\n", __FUNCSIG__, ec); }

	return (hWnd != nullptr);
}

void UXReader::UXReaderDocumentPane::Destroy(void)
{

	DestroyWindow(m_WindowHandle);

}

void UXReader::UXReaderDocumentPane::UpdateXYWH(const int x, const int y, const int w, const int h)
{

	SetWindowPos(m_WindowHandle, nullptr, x, y, w, h, (SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOZORDER));

	RedrawWindow(m_WindowHandle, nullptr, nullptr, (RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN)); // !!!
}

void UXReader::UXReaderDocumentPane::UpdateWH(const int w, const int h)
{

	SetWindowPos(m_WindowHandle, nullptr, 0, 0, w, h, (SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOMOVE | SWP_NOZORDER));

	RedrawWindow(m_WindowHandle, nullptr, nullptr, (RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN)); // !!!
}

void UXReader::UXReaderDocumentPane::ViewPortChanged(std::function<void(void)> viewPortChanged)
{

	fn_ViewPortChanged = viewPortChanged;
}

void UXReader::UXReaderDocumentPane::VisiblePagesChanged(std::function<void(void)> visiblePagesChanged)
{

	fn_VisiblePagesChanged = visiblePagesChanged;
}

void UXReader::UXReaderDocumentPane::CurrentPageChanged(std::function<void(void)> currentPageChanged)
{

	fn_CurrentPageChanged = currentPageChanged;
}

void UXReader::UXReaderDocumentPane::SearchFinished(std::function<void(bool, int)> searchFinished)
{

	fn_SearchFinished = searchFinished;
}

void UXReader::UXReaderDocumentPane::SearchProgress(std::function<void(int, int)> searchProgress)
{

	fn_SearchProgress = searchProgress;
}

const std::set<int>& UXReader::UXReaderDocumentPane::VisiblePages(void) const
{

	return m_VisiblePages;
}

int UXReader::UXReaderDocumentPane::CurrentPage(void) const
{

	return m_CurrentPage;
}

//
//	Window message methods
//

void UXReader::UXReaderDocumentPane::RegisterMessages(void)
{

	m_MessageMap.emplace(WM_CREATE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowCreate(h, m, w, l); });
	m_MessageMap.emplace(WM_SIZE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowSize(h, m, w, l); });
	m_MessageMap.emplace(WM_ERASEBKGND, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowErase(h, m, w, l); });
	m_MessageMap.emplace(WM_PAINT, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowPaint(h, m, w, l); });
	m_MessageMap.emplace(WM_VSCROLL, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowScrollV(h, m, w, l); });
	m_MessageMap.emplace(WM_HSCROLL, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowScrollH(h, m, w, l); });
	m_MessageMap.emplace(WM_NOTIFY, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowNotify(h, m, w, l); });
	m_MessageMap.emplace(WM_TIMER, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowTimer(h, m, w, l); });
	m_MessageMap.emplace(WM_CONTEXTMENU, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->MenuContext(h, m, w, l); });
	m_MessageMap.emplace(WM_SETCURSOR, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->MouseCursor(h, m, w, l); });
	m_MessageMap.emplace(WM_MOUSEMOVE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->MouseMove(h, m, w, l); });
	m_MessageMap.emplace(WM_LBUTTONDOWN, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->MouseDown(h, m, w, l); });
	m_MessageMap.emplace(WM_LBUTTONUP, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->MouseLift(h, m, w, l); });
}

LRESULT UXReader::UXReaderDocumentPane::WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//CREATESTRUCTW *cs = reinterpret_cast<CREATESTRUCTW *>(lParam);

	m_WindowHandle = hWnd; m_ParentWindow = GetParent(hWnd);

	m_UIS = UXReaderSupport::UIS(UXReaderSupport::DPI(hWnd)); const double uis = (m_UIS / 100.0);

	const size_t pageCacheSize = size_t(612 * 792 * sizeof(uint32_t) * uis * cachePagesLimit);

	m_PageCache = std::make_unique<UXReaderPageCache>(pageCacheSize); // Page bitmap cache

	m_ZoomMaximumScale = (8.0 * uis); m_ZoomMinimumScale = (0.5 * uis); // Set zoom limits

	CreateScrollBars(hWnd); LayoutPages(hWnd); UpdateClientRect(hWnd); UpdateScrollBars(hWnd);

	AddPaneToolTip(hWnd); EnableWindow(hWnd, TRUE);

	return 0;
}

LRESULT UXReader::UXReaderDocumentPane::WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//const int cw = LOWORD(lParam); const int ch = HIWORD(lParam);

	UpdateClientRect(hWnd); ResizeScrollBars(hWnd);

	return 0;
}

LRESULT UXReader::UXReaderDocumentPane::WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	return 0;
}

LRESULT UXReader::UXReaderDocumentPane::WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps {}; HDC hDC = BeginPaint(hWnd, &ps);

	if (IsRectEmpty(&ps.rcPaint) == FALSE) HandlePaint(hWnd, hDC);

	EndPaint(hWnd, &ps);

	return 0;
}

LRESULT UXReader::UXReaderDocumentPane::WindowScrollV(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (LOWORD(wParam))
	{
		case SB_LINEUP: { LineScrollDecrementY(); break; }
		case SB_LINEDOWN: { LineScrollIncrementY(); break; }

		case SB_PAGEUP: { PageScrollDecrementY(); break; }
		case SB_PAGEDOWN: { PageScrollIncrementY(); break; }

		case SB_THUMBTRACK: // Absolute Y position
		{
			SCROLLINFO si; RtlSecureZeroMemory(&si, sizeof(si));
			si.cbSize = sizeof(si); si.fMask = SIF_TRACKPOS;
			GetScrollInfo(hWnd, SB_VERT, &si); // Y
			UpdateViewPortY(si.nTrackPos); break;
		}
	}

	return 0;
}

LRESULT UXReader::UXReaderDocumentPane::WindowScrollH(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (LOWORD(wParam))
	{
		case SB_LINELEFT: { LineScrollDecrementX(); break; }
		case SB_LINERIGHT: { LineScrollIncrementX(); break; }

		case SB_PAGELEFT: { PageScrollDecrementX(); break; }
		case SB_PAGERIGHT: { PageScrollIncrementX(); break; }

		case SB_THUMBTRACK: // Absolute X position
		{
			SCROLLINFO si; RtlSecureZeroMemory(&si, sizeof(si));
			si.cbSize = sizeof(si); si.fMask = SIF_TRACKPOS;
			GetScrollInfo(hWnd, SB_HORZ, &si); // X
			UpdateViewPortX(si.nTrackPos); break;
		}
	}

	return 0;
}

LRESULT UXReader::UXReaderDocumentPane::WindowNotify(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if (NMTTDISPINFOW *ttdi = reinterpret_cast<NMTTDISPINFOW *>(lParam))
	{
		if (ttdi->hdr.code == TTN_GETDISPINFOW) ttdi->lpszText = LPWSTR(m_LinkDescription.data());
	}

	return 0;
}

LRESULT UXReader::UXReaderDocumentPane::WindowTimer(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	KillTimer(hWnd, wParam);

	switch (wParam) // Timer
	{
		case paintTimerTick: // Post paint timeout
		{
			PostPaintTimeout(hWnd); break;
		}
	}

	return 0;
}

LRESULT UXReader::UXReaderDocumentPane::MenuContext(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//m_Document->HexDump();

	return 0;
}

LRESULT UXReader::UXReaderDocumentPane::MouseCursor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if ((HWND(wParam) == hWnd) && (LOWORD(lParam) == HTCLIENT))
	{
		SetMouseCursorShape(hWnd); return TRUE;
	}

	return DefWindowProcW(hWnd, message, wParam, lParam);
}

LRESULT UXReader::UXReaderDocumentPane::MouseMove(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//const int mouseX = GET_X_LPARAM(lParam); const int mouseY = GET_Y_LPARAM(lParam);

	return 0;
}

LRESULT UXReader::UXReaderDocumentPane::MouseDown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//const int mouseX = GET_X_LPARAM(lParam); const int mouseY = GET_Y_LPARAM(lParam);

	return 0;
}

LRESULT UXReader::UXReaderDocumentPane::MouseLift(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	const int mouseX = GET_X_LPARAM(lParam); const int mouseY = GET_Y_LPARAM(lParam);

	MouseClicked(mouseX, mouseY);

	return 0;
}

void UXReader::UXReaderDocumentPane::MouseWheelV(const WPARAM wParam, const LPARAM lParam)
{

	if (IsWindowEnabled(m_WindowHandle))
	{
		const int delta = GET_WHEEL_DELTA_WPARAM(wParam);

		if (GET_KEYSTATE_WPARAM(wParam) & MK_CONTROL)
		{
			if (delta < 0) ZoomDecrement(1.25);
			if (delta > 0) ZoomIncrement(1.25);
		}
		else if (GET_KEYSTATE_WPARAM(wParam) & MK_SHIFT)
		{
			if (delta < 0) WheelScrollIncrementX();
			if (delta > 0) WheelScrollDecrementX();
		}
		else // Scroll - up or down
		{
			if (delta < 0) WheelScrollIncrementY();
			if (delta > 0) WheelScrollDecrementY();
		}
	}
}

void UXReader::UXReaderDocumentPane::MouseWheelH(const WPARAM wParam, const LPARAM lParam)
{

	if (IsWindowEnabled(m_WindowHandle))
	{
		const int delta = GET_WHEEL_DELTA_WPARAM(wParam);

		if (delta > 0) WheelScrollIncrementX();
		if (delta < 0) WheelScrollDecrementX();
	}
}

//
//	View port support methods
//

void UXReader::UXReaderDocumentPane::UpdateClientRect(const HWND hWnd)
{

	RECT rect; GetClientRect(hWnd, &rect);
	m_ClientRectH = (rect.bottom - rect.top);
	m_ClientRectW = (rect.right - rect.left);

	const double viewPortH = (m_ClientRectH / m_ZoomScale);
	const double viewPortW = (m_ClientRectW / m_ZoomScale);

	m_ViewPortH = ((viewPortH < m_CanvasH) ? viewPortH : m_CanvasH);
	m_ViewPortW = ((viewPortW < m_CanvasW) ? viewPortW : m_CanvasW);

	m_ViewPortMaximumY = (m_CanvasH - m_ViewPortH);
	m_ViewPortMaximumX = (m_CanvasW - m_ViewPortW);

	if (m_CanvasH <= viewPortH) m_ViewPortY = m_ViewPortMinimumY;
	if (m_CanvasW <= viewPortW) m_ViewPortX = m_ViewPortMinimumX;
}

void UXReader::UXReaderDocumentPane::CreateScrollBars(const HWND hWnd) const
{

	ShowScrollBar(hWnd, SB_BOTH, TRUE);

	SCROLLINFO si_v; RtlSecureZeroMemory(&si_v, sizeof(si_v));
	si_v.cbSize = sizeof(si_v); si_v.fMask = (SIF_ALL | SIF_DISABLENOSCROLL);
	SetScrollInfo(hWnd, SB_VERT, &si_v, TRUE);

	SCROLLINFO si_h; RtlSecureZeroMemory(&si_h, sizeof(si_h));
	si_h.cbSize = sizeof(si_h); si_h.fMask = (SIF_ALL | SIF_DISABLENOSCROLL);
	SetScrollInfo(hWnd, SB_HORZ, &si_h, TRUE);
}

void UXReader::UXReaderDocumentPane::UpdateScrollBars(const HWND hWnd) const
{

	SCROLLINFO si_v; RtlSecureZeroMemory(&si_v, sizeof(si_v));
	si_v.cbSize = sizeof(si_v); si_v.fMask = (SIF_ALL | SIF_DISABLENOSCROLL);
	si_v.nMin = int(m_ViewPortMinimumY); si_v.nMax = int(m_CanvasH) - 1;
	si_v.nPos = int(m_ViewPortY); si_v.nPage = int(m_ViewPortH);
	SetScrollInfo(hWnd, SB_VERT, &si_v, TRUE);

	SCROLLINFO si_h; RtlSecureZeroMemory(&si_h, sizeof(si_h));
	si_h.cbSize = sizeof(si_h); si_h.fMask = (SIF_ALL | SIF_DISABLENOSCROLL);
	si_h.nMin = int(m_ViewPortMinimumX); si_h.nMax = int(m_CanvasW) - 1;
	si_h.nPos = int(m_ViewPortX); si_h.nPage = int(m_ViewPortW);
	SetScrollInfo(hWnd, SB_HORZ, &si_h, TRUE);
}

void UXReader::UXReaderDocumentPane::ResizeScrollBars(const HWND hWnd) const
{

	SCROLLINFO si_v; RtlSecureZeroMemory(&si_v, sizeof(si_v));
	si_v.cbSize = sizeof(si_v); si_v.fMask = (SIF_POS | SIF_PAGE | SIF_DISABLENOSCROLL);
	si_v.nPos = int(m_ViewPortY); si_v.nPage = int(m_ViewPortH);
	SetScrollInfo(hWnd, SB_VERT, &si_v, TRUE);

	SCROLLINFO si_h; RtlSecureZeroMemory(&si_h, sizeof(si_h));
	si_h.cbSize = sizeof(si_h); si_h.fMask = (SIF_POS | SIF_PAGE | SIF_DISABLENOSCROLL);
	si_h.nPos = int(m_ViewPortX); si_h.nPage = int(m_ViewPortW);
	SetScrollInfo(hWnd, SB_HORZ, &si_h, TRUE);
}

void UXReader::UXReaderDocumentPane::UpdateScrollBarY(const HWND hWnd) const
{

	SCROLLINFO si_v; RtlSecureZeroMemory(&si_v, sizeof(si_v));
	si_v.cbSize = sizeof(si_v); si_v.fMask = (SIF_POS | SIF_DISABLENOSCROLL);
	si_v.nPos = int(m_ViewPortY); si_v.nPage = int(m_ViewPortH);
	SetScrollInfo(hWnd, SB_VERT, &si_v, TRUE);
}

void UXReader::UXReaderDocumentPane::UpdateScrollBarX(const HWND hWnd) const
{

	SCROLLINFO si_h; RtlSecureZeroMemory(&si_h, sizeof(si_h));
	si_h.cbSize = sizeof(si_h); si_h.fMask = (SIF_POS | SIF_DISABLENOSCROLL);
	si_h.nPos = int(m_ViewPortX); si_h.nPage = int(m_ViewPortW);
	SetScrollInfo(hWnd, SB_HORZ, &si_h, TRUE);
}

//
//	View port update methods
//

void UXReader::UXReaderDocumentPane::RedrawPaneContent(void) const
{

	InvalidateRect(m_WindowHandle, nullptr, FALSE);
}

void UXReader::UXReaderDocumentPane::ViewPortDidChange(void) const
{

	InvalidateRect(m_WindowHandle, nullptr, FALSE);

	if (fn_ViewPortChanged) fn_ViewPortChanged();
}

void UXReader::UXReaderDocumentPane::UpdateViewPortX(double viewPortX)
{

	if (viewPortX < m_ViewPortMinimumX) viewPortX = m_ViewPortMinimumX; else if (viewPortX > m_ViewPortMaximumX) viewPortX = m_ViewPortMaximumX;

	if (viewPortX != m_ViewPortX) { m_ViewPortX = viewPortX; UpdateScrollBarX(m_WindowHandle); ViewPortDidChange(); }
}

void UXReader::UXReaderDocumentPane::UpdateViewPortY(double viewPortY)
{

	if (viewPortY < m_ViewPortMinimumY) viewPortY = m_ViewPortMinimumY; else if (viewPortY > m_ViewPortMaximumY) viewPortY = m_ViewPortMaximumY;

	if (viewPortY != m_ViewPortY) { m_ViewPortY = viewPortY; UpdateScrollBarY(m_WindowHandle); ViewPortDidChange(); }
}

void UXReader::UXReaderDocumentPane::UpdateViewPortXY(double viewPortX, double viewPortY)
{

	bool viewPortChanged = false; // View port changed

	if (viewPortX < m_ViewPortMinimumX) viewPortX = m_ViewPortMinimumX; else if (viewPortX > m_ViewPortMaximumX) viewPortX = m_ViewPortMaximumX;
	if (viewPortY < m_ViewPortMinimumY) viewPortY = m_ViewPortMinimumY; else if (viewPortY > m_ViewPortMaximumY) viewPortY = m_ViewPortMaximumY;

	if (viewPortX != m_ViewPortX) { m_ViewPortX = viewPortX; UpdateScrollBarX(m_WindowHandle); viewPortChanged = true; }
	if (viewPortY != m_ViewPortY) { m_ViewPortY = viewPortY; UpdateScrollBarY(m_WindowHandle); viewPortChanged = true; }

	if (viewPortChanged == true) ViewPortDidChange();
}

void UXReader::UXReaderDocumentPane::CenterViewPort(const UXPoint& point)
{

	const double viewPortX = (point.x - (m_ViewPortW * 0.5));
	const double viewPortY = (point.y - (m_ViewPortH * 0.5));

	UpdateViewPortXY(viewPortX, viewPortY);
}

void UXReader::UXReaderDocumentPane::GotoRectOnPage(const int index, const UXRect& rect)
{

	const UXRect& pageFrame = m_PageFrames.at(index);

	const UXRect targetRect = rect.offset(pageFrame.xd(), pageFrame.yd());

	const UXRect viewPort(m_ViewPortX, m_ViewPortY, m_ViewPortW, m_ViewPortH);

	if (viewPort.intersects(targetRect) == false) CenterViewPort(targetRect.center());
}

double UXReader::UXReaderDocumentPane::LimitScrollFactor(double value) const
{

	if (value < 0.005) value = 0.005; else if (value > 0.995) value = 0.995;

	return value;
}

void UXReader::UXReaderDocumentPane::ViewPortScrollDecrementY(double factor)
{

	if (CanViewPortScrollDecrementY() == true)
	{
		const double amount = (m_ClientRectH * LimitScrollFactor(factor));

		const double viewPortY = (m_ViewPortY - (amount / m_ZoomScale));

		UpdateViewPortY(viewPortY);
	}
}

bool UXReader::UXReaderDocumentPane::CanViewPortScrollDecrementY(void) const
{

	return (m_ViewPortY > m_ViewPortMinimumY);
}

void UXReader::UXReaderDocumentPane::ViewPortScrollIncrementY(double factor)
{

	if (CanViewPortScrollIncrementY() == true)
	{
		const double amount = (m_ClientRectH * LimitScrollFactor(factor));

		const double viewPortY = (m_ViewPortY + (amount / m_ZoomScale));

		UpdateViewPortY(viewPortY);
	}
}

bool UXReader::UXReaderDocumentPane::CanViewPortScrollIncrementY(void) const
{

	return (m_ViewPortY < m_ViewPortMaximumY);
}

void UXReader::UXReaderDocumentPane::ViewPortScrollDecrementX(double factor)
{

	if (CanViewPortScrollDecrementX() == true)
	{
		const double amount = (m_ClientRectW * LimitScrollFactor(factor));

		const double viewPortX = (m_ViewPortX - (amount / m_ZoomScale));

		UpdateViewPortX(viewPortX);
	}
}

bool UXReader::UXReaderDocumentPane::CanViewPortScrollDecrementX(void) const
{

	return (m_ViewPortX > m_ViewPortMinimumX);
}

void UXReader::UXReaderDocumentPane::ViewPortScrollIncrementX(double factor)
{

	if (CanViewPortScrollIncrementX() == true)
	{
		const double amount = (m_ClientRectW * LimitScrollFactor(factor));

		const double viewPortX = (m_ViewPortX + (amount / m_ZoomScale));

		UpdateViewPortX(viewPortX);
	}
}

bool UXReader::UXReaderDocumentPane::CanViewPortScrollIncrementX(void) const
{

	return (m_ViewPortX < m_ViewPortMaximumX);
}

//
//	View port scroll methods
//

void UXReader::UXReaderDocumentPane::LineScrollDecrementY(void)
{

	if (CanViewPortScrollDecrementY()) ViewPortScrollDecrementY(lineScrollFactor);
}

void UXReader::UXReaderDocumentPane::LineScrollIncrementY(void)
{

	if (CanViewPortScrollIncrementY()) ViewPortScrollIncrementY(lineScrollFactor);
}

void UXReader::UXReaderDocumentPane::LineScrollDecrementX(void)
{

	if (CanViewPortScrollDecrementX()) ViewPortScrollDecrementX(lineScrollFactor);
}

void UXReader::UXReaderDocumentPane::LineScrollIncrementX(void)
{

	if (CanViewPortScrollIncrementX()) ViewPortScrollIncrementX(lineScrollFactor);
}

void UXReader::UXReaderDocumentPane::WheelScrollDecrementY(void)
{

	if (CanViewPortScrollDecrementY()) ViewPortScrollDecrementY(wheelScrollFactor);
}

void UXReader::UXReaderDocumentPane::WheelScrollIncrementY(void)
{

	if (CanViewPortScrollIncrementY()) ViewPortScrollIncrementY(wheelScrollFactor);
}

void UXReader::UXReaderDocumentPane::WheelScrollDecrementX(void)
{

	if (CanViewPortScrollDecrementX()) ViewPortScrollDecrementX(wheelScrollFactor);
}

void UXReader::UXReaderDocumentPane::WheelScrollIncrementX(void)
{

	if (CanViewPortScrollIncrementX()) ViewPortScrollIncrementX(wheelScrollFactor);
}

void UXReader::UXReaderDocumentPane::PageScrollDecrementY(void)
{

	if (CanViewPortScrollDecrementY()) ViewPortScrollDecrementY(pageScrollFactor);
}

void UXReader::UXReaderDocumentPane::PageScrollIncrementY(void)
{

	if (CanViewPortScrollIncrementY()) ViewPortScrollIncrementY(pageScrollFactor);
}

void UXReader::UXReaderDocumentPane::PageScrollDecrementX(void)
{

	if (CanViewPortScrollDecrementX()) ViewPortScrollDecrementX(pageScrollFactor);
}

void UXReader::UXReaderDocumentPane::PageScrollIncrementX(void)
{

	if (CanViewPortScrollIncrementX()) ViewPortScrollIncrementX(pageScrollFactor);
}

void UXReader::UXReaderDocumentPane::GotoMaximumDocumentY(void)
{

	if (CanViewPortScrollIncrementY()) UpdateViewPortY(m_ViewPortMaximumY);
}

void UXReader::UXReaderDocumentPane::GotoMinimumDocumentY(void)
{

	if (CanViewPortScrollDecrementY()) UpdateViewPortY(m_ViewPortMinimumY);
}

void UXReader::UXReaderDocumentPane::GotoMaximumDocumentX(void)
{

	if (CanViewPortScrollIncrementX()) UpdateViewPortX(m_ViewPortMaximumX);
}

void UXReader::UXReaderDocumentPane::GotoMinimumDocumentX(void)
{

	if (CanViewPortScrollDecrementX()) UpdateViewPortX(m_ViewPortMinimumX);
}

//
//	Goto page methods
//

void UXReader::UXReaderDocumentPane::GotoDocumentPage(const int index)
{

	if (CanGotoDocumentPage(index) == true)
	{
		const UXRect& pageFrame = m_PageFrames.at(index);

		UpdateViewPortXY(pageFrame.xd(), pageFrame.yd());
	}
}

bool UXReader::UXReaderDocumentPane::CanGotoDocumentPage(const int index)
{

	return m_Document->IsValidPageIndex(index);
}

void UXReader::UXReaderDocumentPane::PageNumberDecrement(void)
{

	if (CanPageNumberDecrement()) GotoDocumentPage(m_CurrentPage - 1);
}

bool UXReader::UXReaderDocumentPane::CanPageNumberDecrement(void)
{

	return (m_CurrentPage > m_Document->MinimumPage());
}

void UXReader::UXReaderDocumentPane::PageNumberIncrement(void)
{

	if (CanPageNumberIncrement()) GotoDocumentPage(m_CurrentPage + 1);
}

bool UXReader::UXReaderDocumentPane::CanPageNumberIncrement(void)
{

	return (m_CurrentPage < m_Document->MaximumPage());
}

void UXReader::UXReaderDocumentPane::GotoAction(const UXReaderAction *action)
{

	if (const UXReaderDestination* destination = action->Destination())
	{
		const int index = destination->PageIndex();

		const UXRect& pageFrame = m_PageFrames.at(index);

		double x = pageFrame.xd(); if (destination->hasX()) x += destination->X();
		double y = pageFrame.yd(); if (destination->hasY()) y += destination->Y();

		UpdateViewPortXY(x, y);
	}
}

//
//	Zoom methods
//

double UXReader::UXReaderDocumentPane::LimitZoomScale(double value)
{

	if (value < 0.1) value = 1.0;
	else if (value > m_ZoomMaximumScale) value = m_ZoomMaximumScale;
	else if (value < m_ZoomMinimumScale) value = m_ZoomMinimumScale;

	return value;
}

void UXReader::UXReaderDocumentPane::SetInitialZoomScale(const HWND hWnd)
{

	RECT rect; GetClientRect(hWnd, &rect);

	const double clientRectW = (rect.right - rect.left);

	const int gap = MulDiv(2, m_UIS, 100); // Page side gap

	m_ZoomScale = LimitZoomScale((clientRectW - gap) / m_CanvasW);
}

bool UXReader::UXReaderDocumentPane::UpdateZoomScale(double scale)
{

	bool status = false; // Updated

	scale = LimitZoomScale(scale); // Limit

	if (scale != m_ZoomScale) // Change zoom scale
	{
		const double centerY = (m_ViewPortY + (m_ViewPortH * 0.5));
		const double centerX = (m_ViewPortX + (m_ViewPortW * 0.5));

		m_PageCache->PurgePageBitmapCache(); m_ZoomScale = scale;

		const double viewPortH = (m_ClientRectH / m_ZoomScale);
		const double viewPortW = (m_ClientRectW / m_ZoomScale);

		m_ViewPortH = ((viewPortH < m_CanvasH) ? viewPortH : m_CanvasH);
		m_ViewPortW = ((viewPortW < m_CanvasW) ? viewPortW : m_CanvasW);

		m_ViewPortMaximumY = (m_CanvasH - m_ViewPortH);
		m_ViewPortMaximumX = (m_CanvasW - m_ViewPortW);

		double viewPortY = (centerY - (m_ViewPortH * 0.5));
		double viewPortX = (centerX - (m_ViewPortW * 0.5));

		if (viewPortY < m_ViewPortMinimumY) viewPortY = m_ViewPortMinimumY;
		if (viewPortY > m_ViewPortMaximumY) viewPortY = m_ViewPortMaximumY;

		if (viewPortX < m_ViewPortMinimumX) viewPortX = m_ViewPortMinimumX;
		if (viewPortX > m_ViewPortMaximumX) viewPortX = m_ViewPortMaximumX;

		m_ViewPortY = viewPortY; m_ViewPortX = viewPortX; status = true;

		ResizeScrollBars(m_WindowHandle); ViewPortDidChange();
	}

	return status;
}

void UXReader::UXReaderDocumentPane::ZoomDecrement(const double amount)
{

	if (CanZoomDecrement()) UpdateZoomScale(m_ZoomScale / amount);
}

bool UXReader::UXReaderDocumentPane::CanZoomDecrement(void)
{

	return (m_ZoomScale > m_ZoomMinimumScale);
}

void UXReader::UXReaderDocumentPane::ZoomIncrement(const double amount)
{

	if (CanZoomIncrement()) UpdateZoomScale(m_ZoomScale * amount);
}

bool UXReader::UXReaderDocumentPane::CanZoomIncrement(void)
{

	return (m_ZoomScale < m_ZoomMaximumScale);
}

void UXReader::UXReaderDocumentPane::ZoomFitWidth(void)
{

	const int gap = MulDiv(2, m_UIS, 100); // Page side gap

	if (CanZoomFitWidth()) UpdateZoomScale((m_ClientRectW - gap) / m_CanvasW);
}

bool UXReader::UXReaderDocumentPane::CanZoomFitWidth(void)
{

	const int gap = MulDiv(2, m_UIS, 100); // Page side gap

	return (m_ZoomScale != ((m_ClientRectW - gap) / m_CanvasW));
}

void UXReader::UXReaderDocumentPane::ZoomOneToOne(void)
{

	const double one = MulDiv(1, m_UIS, 100);

	if (CanZoomOneToOne()) UpdateZoomScale(one);
}

bool UXReader::UXReaderDocumentPane::CanZoomOneToOne(void)
{

	const double one = MulDiv(1, m_UIS, 100);

	return (m_ZoomScale != one);
}

bool UXReader::UXReaderDocumentPane::ZoomScale(const int percent)
{

	return UpdateZoomScale(MulDiv(percent, m_UIS, 100) / 100.0);
}

int UXReader::UXReaderDocumentPane::ZoomScale(void) const
{

	return MulDiv(int(m_ZoomScale * 100.0), m_UIS, 100);
}

//
//	Document draw methods
//

void UXReader::UXReaderDocumentPane::LayoutPages(const HWND hWnd)
{

	const double space = 1.0;

	double tw = 0.0; double th = space;

	const int pageCount = m_Document->PageCount();

	for (int index = 0; index < pageCount; ++index) // O(n)
	{
		const UXPageSize& pageSize = m_Document->PageSize(index);

		th += (pageSize.h + space); if (tw < pageSize.w) tw = pageSize.w;
	}

	m_CanvasH = th; m_CanvasW = tw;

	double py = space; m_PageFrames.reserve(pageCount);

	for (int index = 0; index < pageCount; ++index) // O(n)
	{
		const UXPageSize& pageSize = m_Document->PageSize(index);

		const double px = ((tw - pageSize.w) * 0.5);

		UXPoint pageOrigin = {px, py}; // Page x, y

		UXRect pageFrame = {pageOrigin, pageSize};

		m_PageFrames.push_back(pageFrame);

		py += (pageSize.h + space);
	}

	SetInitialZoomScale(hWnd);
}

bool UXReader::UXReaderDocumentPane::UsePageBitmaps(void) const
{

	const double lesser = ((m_CanvasW < m_CanvasH) ? m_CanvasW : m_CanvasH);

	const int points = int(lesser * m_ZoomScale); const bool use = (points <= useBitmapsLimit);


	return use;
}

void UXReader::UXReaderDocumentPane::DirectPaint(const HWND hWnd)
{

	//UpdateScrollBarY(hWnd);

	if (const HDC hDC = GetDC(hWnd))
	{
		HandlePaint(hWnd, hDC); ReleaseDC(hWnd, hDC);
	}
}

void UXReader::UXReaderDocumentPane::HandlePaint(const HWND hWnd, const HDC hDC)
{

	KillTimer(hWnd, paintTimerTick);

	std::set<int> visiblePages; int currentPage = NEGATORY;

	if (const HDC mDC = CreateCompatibleDC(hDC))
	{
		RECT rect; GetClientRect(hWnd, &rect);
		const int cw = (rect.right - rect.left);
		const int ch = (rect.bottom - rect.top);

		if (const HBITMAP hBitmap = CreateCompatibleBitmap(hDC, cw, ch))
		{
			const HGDIOBJ oldObject = SelectObject(mDC, hBitmap);

			const double viewPortW = (double(cw) / m_ZoomScale);
			const double viewPortH = (double(ch) / m_ZoomScale);

			const double viewPortM = (m_ViewPortY + (viewPortH * 0.5));

			const double ox = ((viewPortW > m_CanvasW) ? ((viewPortW - m_CanvasW) * 0.5) : 0.0);
			const double oy = ((viewPortH > m_CanvasH) ? ((viewPortH - m_CanvasH) * 0.5) : 0.0);

			const UXRect viewPort(m_ViewPortX, m_ViewPortY, m_ViewPortW, m_ViewPortH);

			FillRect(mDC, &rect, UXReaderSupport::DocumentBackgroundBrush());

			const int pageCount = m_Document->PageCount();

			for (int index = 0; index < pageCount; ++index) // O(n)
			{
				const UXRect& pageFrame = m_PageFrames.at(index);

				if (viewPort.intersects(pageFrame)) // Is visible
				{
					UXRect intersect = viewPort.intersect(pageFrame);

					UXRect pageArea = intersect.offset(-pageFrame.xd(), -pageFrame.yd());

					UXRect portArea = intersect.offset(-m_ViewPortX + ox, -m_ViewPortY + oy);

					UXRect clientArea = portArea.scale(m_ZoomScale, m_ZoomScale);

					if (pageFrame.yd() <= viewPortM) currentPage = index;

					DrawPage(mDC, index, pageArea, clientArea);

					visiblePages.insert(index); // Add
				}
			}

			BitBlt(hDC, 0, 0, cw, ch, mDC, 0, 0, SRCCOPY);

			SelectObject(mDC, oldObject); DeleteObject(hBitmap);
		}

		DeleteDC(mDC); m_PageCache->PrunePageBitmapCache();
	}

	SetTimer(hWnd, paintTimerTick, paintTimerTock, nullptr);

	HandlePageChanges(currentPage, visiblePages);
}

void UXReader::UXReaderDocumentPane::HandlePageChanges(int currentPage, const std::set<int>& visiblePages)
{

	bool currentPageChanged = false;
	bool visiblePagesChanged = false;

	if (currentPage != NEGATORY)
	{
		if (currentPage != m_CurrentPage)
		{
			m_CurrentPage = currentPage;

			currentPageChanged = true;
		}
	}

	if (visiblePages != m_VisiblePages)
	{
		m_VisiblePages = std::move(visiblePages);

		visiblePagesChanged = true;
	}

	if (visiblePagesChanged && fn_VisiblePagesChanged)
	{
		fn_VisiblePagesChanged();
	}

	if (currentPageChanged && fn_CurrentPageChanged)
	{
		fn_CurrentPageChanged();
	}
}

void UXReader::UXReaderDocumentPane::DrawPage(const HDC hDC, const int index, const UXRect& pageArea, const UXRect& clientArea)
{

	if (const auto documentPage = m_Document->DocumentPage(index))
	{
		HBITMAP hCached = nullptr; // Page bitmap

		if (UsePageBitmaps() == true) // Cached bitmaps
		{
			hCached = m_PageCache->CachedPageBitmap(index);

			if (hCached == nullptr) // Create bitmap and cache it
			{
				if (hCached = documentPage->PageBitmap(hDC, m_ZoomScale))
				{
					m_PageCache->CachePageBitmap(index, hCached);
				}
			}
		}

		if (const HDC mDC = CreateCompatibleDC(hDC)) // DIB-backed context
		{
			const int cw = clientArea.wi(); const int ch = clientArea.hi();

			BITMAPINFOHEADER bmih; RtlSecureZeroMemory(&bmih, sizeof(bmih));
			bmih.biSize = sizeof(bmih); bmih.biWidth = cw; bmih.biHeight = -ch;
			bmih.biPlanes = 1; bmih.biBitCount = 32; bmih.biCompression = BI_RGB;
			bmih.biSizeImage = (cw * ch * 4); void *bitmapBits = nullptr;
			const BITMAPINFO *bmi = (BITMAPINFO *)&bmih;

			if (const HBITMAP hBitmap = CreateDIBSection(hDC, bmi, DIB_RGB_COLORS, &bitmapBits, nullptr, 0))
			{
				const HGDIOBJ oldBitmap = SelectObject(mDC, hBitmap);

				if (hCached == nullptr) // Draw from document
				{
					if (FPDF_BITMAP pdfBitmap = FPDFBitmap_CreateEx(cw, ch, FPDFBitmap_BGRx, bitmapBits, (cw * 4)))
					{
						FPDFBitmap_FillRect(pdfBitmap, 0, 0, cw, ch, 0xFFFFFFFF); // Fill white

						documentPage->DrawPageArea(pdfBitmap, pageArea, m_ZoomScale);

						FPDFBitmap_Destroy(pdfBitmap); pdfBitmap = nullptr;
					}
				}
				else // Draw from cached bitmap
				{
					if (const HDC bDC = CreateCompatibleDC(hDC))
					{
						const HGDIOBJ oldCached = SelectObject(bDC, hCached);

						const int px = int(round(pageArea.xd() * m_ZoomScale));
						const int py = int(round(pageArea.yd() * m_ZoomScale));

						BitBlt(mDC, 0, 0, cw, ch, bDC, px, py, SRCCOPY);

						SelectObject(bDC, oldCached); DeleteDC(bDC);
					}
				}

				documentPage->DrawOverPage(mDC, pageArea, m_ZoomScale);

				const int cx = clientArea.xi(); const int cy = clientArea.yi();

				BitBlt(hDC, cx, cy, cw, ch, mDC, 0, 0, SRCCOPY); // Blit

				SelectObject(mDC, oldBitmap); DeleteObject(hBitmap);
			}

			DeleteDC(mDC);
		}
	}
}

void UXReader::UXReaderDocumentPane::PostPaintTimeout(const HWND hWnd)
{

	bool redraw = false;

	for (const int index : m_VisiblePages) // O(n)
	{
		if (const auto documentPage = m_Document->DocumentPage(index))
		{
			if (documentPage->ExtractLinks() == true) redraw = true;
		}
	}

	if (redraw == true) RedrawPaneContent();

	SetMouseCursorShape(hWnd);
}

//
//	Document link methods
//

void UXReader::UXReaderDocumentPane::AddPaneToolTip(const HWND hWnd)
{

	const DWORD ws = (WS_POPUP | TTS_NOPREFIX); const DWORD es = (WS_EX_TOPMOST);

	if (m_PaneTooltip = CreateWindowExW(es, TOOLTIPS_CLASSW, nullptr, ws, 0, 0, 0, 0, hWnd, nullptr, UXReaderSupport::Module(), nullptr))
	{
		SetWindowPos(m_PaneTooltip, HWND_TOPMOST, 0, 0, 0, 0, (SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE));

		TOOLINFOW ti; RtlSecureZeroMemory(&ti, sizeof(ti)); ti.cbSize = sizeof(ti); ti.uFlags = (TTF_IDISHWND | TTF_SUBCLASS);
		ti.hwnd = hWnd; ti.uId = UINT_PTR(hWnd); ti.lpszText = LPSTR_TEXTCALLBACKW; //GetClientRect(hWnd, &ti.rect);

		SendMessageW(m_PaneTooltip, TTM_ADDTOOL, 0, LPARAM(&ti)); SendMessageW(m_PaneTooltip, TTM_ACTIVATE, FALSE, 0);
	}
}

void UXReader::UXReaderDocumentPane::SetMouseCursorShape(const HWND hWnd)
{

	POINT cursorXY; GetCursorPos(&cursorXY); MapWindowPoints(GetDesktopWindow(), hWnd, &cursorXY, 1);

	const HCURSOR arrow = (m_Searching ? UXReaderSupport::BusyCursor() : UXReaderSupport::ArrowCursor());

	SetCursor(IsMouseOverLink(cursorXY.x, cursorXY.y) ? UXReaderSupport::PointCursor() : arrow);
}

UXPoint UXReader::UXReaderDocumentPane::MouseToViewPort(const int x, const int y) const
{

	UXPoint point; // View port coordinates

	const double clientPortH = (m_ClientRectH / m_ZoomScale);
	const double clientPortW = (m_ClientRectW / m_ZoomScale);

	const double ty = ((clientPortH > m_CanvasH) ? ((clientPortH - m_CanvasH) * 0.5) : 0.0);
	const double tx = ((clientPortW > m_CanvasW) ? ((clientPortW - m_CanvasW) * 0.5) : 0.0);

	point.y = (m_ViewPortY + (double(y) / m_ZoomScale) - ty);
	point.x = (m_ViewPortX + (double(x) / m_ZoomScale) - tx);

	return point;
}

UXPoint UXReader::UXReaderDocumentPane::PageAreaPoint(const int index, const UXPoint& point) const
{

	const UXRect& pageFrame = m_PageFrames.at(index);

	return point.translate(-pageFrame.xd(), -pageFrame.yd());
}

int UXReader::UXReaderDocumentPane::PageUnderPoint(const UXPoint& point) const
{

	int index = NEGATORY; // Page under point

	for (const int visible : m_VisiblePages) // O(n)
	{
		const UXRect& pageFrame = m_PageFrames.at(visible);

		if (pageFrame.contains(point) == true)
		{
			index = visible; break;
		}
	}

	return index;
}

bool UXReader::UXReaderDocumentPane::IsMouseOverLink(const int x, const int y)
{

	bool status = false; // Result status

	const UXPoint viewPort = MouseToViewPort(x, y);

	const int index = PageUnderPoint(viewPort);

	if (index != NEGATORY) // Check if inside link on page
	{
		if (const auto documentPage = m_Document->DocumentPage(index))
		{
			const UXPoint point = PageAreaPoint(index, viewPort);

			const UXReaderAction* action = documentPage->ActionForPoint(point);

			if (action != m_Action) // UXReaderAction changed - update things
			{
				m_Action = action; const BOOL enable = (m_Action ? TRUE : FALSE);

				m_LinkDescription = documentPage->ActionTooltip(m_Action);

				SendMessageW(m_PaneTooltip, TTM_ACTIVATE, enable, 0);
			}

			if (action != nullptr) status = true;
		}
	}

	return status;
}

bool UXReader::UXReaderDocumentPane::MouseClicked(const int x, const int y)
{

	bool status = false; // Result status

	const UXPoint viewPort = MouseToViewPort(x, y);

	const int index = PageUnderPoint(viewPort);

	if (index != NEGATORY) // Check if inside link on page
	{
		if (const auto documentPage = m_Document->DocumentPage(index))
		{
			const UXPoint point = PageAreaPoint(index, viewPort);

			if (const UXReaderAction* action = documentPage->ActionForPoint(point))
			{
				switch (action->Type()) // UXReaderActionType
				{
					case UXReaderActionType::URI: // Open raw link
					{
						const wchar_t *uri = action->URI().data();
						ShellExecuteW(nullptr, L"open", uri, nullptr, nullptr, SW_SHOWNORMAL);
						break;
					}

					case UXReaderActionType::Goto:
					{
						GotoAction(action); break;
					}
				}
			}
		}
	}

	return status;
}

//
//	Search methods
//

void UXReader::UXReaderDocumentPane::CancelSearch(void)
{

	m_CancelSearch = true;

	if (m_SearchThread.joinable()) m_SearchThread.join();

	m_CancelSearch = false; m_Searching = false;
}

void UXReader::UXReaderDocumentPane::ClearSearch(void)
{

	m_Document->EnumerateCachedPages([](int index, const std::shared_ptr<UXReaderDocumentPage>& documentPage)
	{
		documentPage->ClearSearch();
	});
}

void UXReader::UXReaderDocumentPane::StartSearch(const std::wstring& term, const int options)
{

	CancelSearch(); ClearSearch(); m_SearchTerm = term;

	if (term.empty() == true) // Cleared search
	{
		RedrawPaneContent(); if (fn_SearchFinished) fn_SearchFinished(true, 0);
	}
	else // Search for term using options on a seperate thread
	{
		m_SearchThread = std::thread(&UXReader::UXReaderDocumentPane::SearchDocument, this, options);

		SetThreadPriority(m_SearchThread.native_handle(), THREAD_PRIORITY_BELOW_NORMAL);

		m_Searching = m_SearchThread.joinable(); SetMouseCursorShape(m_WindowHandle);
	}
}

void UXReader::UXReaderDocumentPane::SearchDocument(const int options)
{

	int found = 0; const int pageCount = m_Document->PageCount();

	for (int index = 0; ((index < pageCount) && !m_CancelSearch); ++index)
	{
		if (const auto documentPage = m_Document->DocumentPage(index))
		{
			if (m_CancelSearch == false) // Search not cancelled
			{
				documentPage->SearchPage(m_SearchTerm, options, found);

				if (m_CancelSearch == false) // Search not cancelled
				{
					if (fn_SearchProgress) fn_SearchProgress(index, found);

					Sleep(1); // Enable responsive UI hack
				}
			}
		}
	}

	if (fn_SearchFinished) fn_SearchFinished(m_CancelSearch, found);

	RedrawPaneContent(); m_Searching = false;
}
