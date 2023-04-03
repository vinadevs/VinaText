//
//	UXReaderMainWindow.cpp
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderMainWindow.h"
#include "UXReaderDocument.h"
#include "UXReaderDocumentView.h"

using namespace UXReader;

//
//	Constants
//

constexpr int windowBorderInset = 16;
constexpr int minimumWindowSize = 640;

static wchar_t *const kWindowTitle = L"UXReader";

static wchar_t *const kWindowClassName = L"UXReaderMainWindowClass";

//
//	UXReaderMainWindow methods
//

UXReaderMainWindow::UXReaderMainWindow(void)
{

	RegisterMessages();
}

UXReaderMainWindow::~UXReaderMainWindow(void)
{

	if (m_Accelerators != nullptr) DestroyAcceleratorTable(m_Accelerators); m_Accelerators = nullptr;

	m_DocumentView = nullptr; m_WindowHandle = nullptr; m_WindowMenu = nullptr;

}

wchar_t *const UXReaderMainWindow::WindowClassName(void)
{

	return kWindowClassName;
}

ATOM UXReaderMainWindow::DoRegisterWindowClass(const HMODULE hModule)
{

	WNDCLASSEXW wcex; RtlSecureZeroMemory(&wcex, sizeof(wcex));

	wcex.hInstance = hModule;
	wcex.lpszClassName = kWindowClassName;
	wcex.style = 0; wcex.lpszMenuName = nullptr;
	wcex.lpfnWndProc = UXReaderMainWindow::WindowDispatch;
	wcex.hIcon = LoadIconW(hModule, MAKEINTRESOURCEW(IDI_TINKER_ICON));
	wcex.hIconSm = LoadIconW(hModule, MAKEINTRESOURCEW(IDI_TINKER_ICON));
	wcex.hbrBackground = nullptr; wcex.hCursor = UXReaderSupport::ArrowCursor();
	wcex.cbClsExtra = 0; wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEXW);

	return RegisterClassExW(&wcex);
}

BOOL UXReaderMainWindow::UnRegisterWindowClass(const HMODULE hModule)
{

	return UnregisterClassW(kWindowClassName, hModule);
}

LRESULT CALLBACK UXReaderMainWindow::WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	if (message == WM_NCCREATE) SetWindowLongPtrW(hWnd, GWLP_USERDATA, LONG_PTR((LPCREATESTRUCT(lParam))->lpCreateParams));

	UXReaderMainWindow *thisWindow = reinterpret_cast<UXReaderMainWindow *>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

	if (thisWindow != nullptr)
		return thisWindow->WindowProcedure(hWnd, message, wParam, lParam);
	else
		return DefWindowProcW(hWnd, message, wParam, lParam);
}

LRESULT UXReaderMainWindow::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	auto entry = m_MessageMap.find(message);

	if (entry == m_MessageMap.end())
		return DefWindowProcW(hWnd, message, wParam, lParam);
	else
		return entry->second(hWnd, message, wParam, lParam);
}

bool UXReaderMainWindow::Create(const wchar_t *pCmdLine, const int nCmdShow)
{

	bool status = false; // Create result status

	m_Accelerators = MainAccelerators();

	if (const HMENU hMenu = MainWindowMenu())
	{
		const int dpi = UXReaderSupport::DPI(); const int uis = UXReaderSupport::UIS(dpi);

		m_MinimumWindowSize = ((MulDiv(minimumWindowSize, uis, 100) >> 1) << 1);

		RECT workArea; SystemParametersInfoW(SPI_GETWORKAREA, 0, &workArea, 0);
		const int dw = (workArea.right - workArea.left); const int dh = (workArea.bottom - workArea.top);
		int ww = 0; int wh = 0; const int wi = ((MulDiv(windowBorderInset, uis, 100) >> 1) << 1);

		if (dw >= dh) // Landscape display
		{
			wh = (dh - wi); ww = ((wh / 6) * 5);
		}
		else // Handle portrait mode display (tablets)
		{
			ww = (dw - wi); wh = ((ww / 3) * 4);

			const int mh = (dh - wi); if (wh > mh) wh = mh;
		}

		wh = ((wh >> 1) << 1); ww = ((ww >> 1) << 1); const int wy = ((dh - wh) >> 1); const int wx = ((dw - ww) >> 1);

		const DWORD ws = (WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN); const DWORD es = (WS_EX_APPWINDOW); // Main window style

		const HWND hWnd = CreateWindowExW(es, kWindowClassName, kWindowTitle, ws, wx, wy, ww, wh, nullptr, hMenu, UXReaderSupport::Module(), this);

		if (hWnd == nullptr) { const DWORD ec = GetLastError(); DBLog(L"%S Unable to create window (%lu).\n", __FUNCSIG__, ec); }

		if (hWnd == nullptr) DestroyMenu(hMenu); else { ShowWindow(hWnd, nCmdShow); UpdateWindow(hWnd); status = true; }
	}

	return status;
}

HACCEL UXReaderMainWindow::MainAccelerators(void) const
{

	#define FNONE 0x00

	std::vector<ACCEL> accelerators;

	accelerators.push_back({(FVIRTKEY | FALT), VK_F4, UXM_APP_EXIT});
	accelerators.push_back({(FVIRTKEY | FCONTROL), 'Q', UXM_APP_EXIT});
	accelerators.push_back({(FVIRTKEY | FCONTROL), 'O', UXM_OPEN_DOCUMENT});
	accelerators.push_back({(FVIRTKEY | FCONTROL), 'W', UXM_CLOSE_DOCUMENT});
	accelerators.push_back({(FVIRTKEY | FCONTROL | FSHIFT), 'W', UXM_CLOSE_ALL});
	accelerators.push_back({(FVIRTKEY | FCONTROL), 'I', UXM_DOCUMENT_INFO});
	accelerators.push_back({(FVIRTKEY | FCONTROL), 'P', UXM_PRINT_DOCUMENT});
	accelerators.push_back({(FVIRTKEY | FCONTROL), VK_F4, UXM_CLOSE_DOCUMENT});

	accelerators.push_back({(FVIRTKEY | FCONTROL), 'C', UXM_COPY_TEXT});
	accelerators.push_back({(FVIRTKEY | FCONTROL), 'A', UXM_SELECT_ALL});
	accelerators.push_back({(FVIRTKEY | FCONTROL), 'F', UXM_FIND_TEXT});
	accelerators.push_back({(FVIRTKEY | FCONTROL), 'N', UXM_FIND_INCREMENT});
	accelerators.push_back({(FVIRTKEY | FCONTROL), 'M', UXM_FIND_DECREMENT});
	accelerators.push_back({(FVIRTKEY | FCONTROL), 'E', UXM_FIND_SELECTION});
	accelerators.push_back({(FVIRTKEY | FCONTROL), 'J', UXM_GOTO_SELECTION});

	accelerators.push_back({(FVIRTKEY | FCONTROL), '2', UXM_HIDE_SIDEBAR});
	accelerators.push_back({(FVIRTKEY | FCONTROL), '3', UXM_SHOW_OUTLINE});
	accelerators.push_back({(FVIRTKEY | FCONTROL), '4', UXM_SHOW_THUMBS});
	accelerators.push_back({(FVIRTKEY | FCONTROL), VK_OEM_PLUS, UXM_ZOOM_INCREMENT});
	accelerators.push_back({(FVIRTKEY | FCONTROL), VK_OEM_MINUS, UXM_ZOOM_DECREMENT});
	accelerators.push_back({(FVIRTKEY | FCONTROL), '0', UXM_ZOOM_FIT_WIDTH});
	accelerators.push_back({(FVIRTKEY | FCONTROL), '1', UXM_ZOOM_ONE_TO_ONE});

	accelerators.push_back({(FVIRTKEY | FCONTROL), 'G', UXM_GOTO_PAGE});
	accelerators.push_back({(FVIRTKEY | FCONTROL), VK_PRIOR, UXM_PAGE_DECREMENT});
	accelerators.push_back({(FVIRTKEY | FCONTROL), VK_NEXT, UXM_PAGE_INCREMENT});

	accelerators.push_back({(FVIRTKEY | FNONE), VK_PRIOR, UXM_PAGING_DECREMENT_Y});
	accelerators.push_back({(FVIRTKEY | FNONE), VK_NEXT, UXM_PAGING_INCREMENT_Y});
	accelerators.push_back({(FVIRTKEY | FSHIFT), VK_PRIOR, UXM_PAGING_DECREMENT_X});
	accelerators.push_back({(FVIRTKEY | FSHIFT), VK_NEXT, UXM_PAGING_INCREMENT_X});

	accelerators.push_back({(FVIRTKEY | FNONE), VK_HOME, UXM_MINIMUM_DOCUMENT_Y});
	accelerators.push_back({(FVIRTKEY | FNONE), VK_END, UXM_MAXIMUM_DOCUMENT_Y});
	accelerators.push_back({(FVIRTKEY | FSHIFT), VK_HOME, UXM_MINIMUM_DOCUMENT_X});
	accelerators.push_back({(FVIRTKEY | FSHIFT), VK_END, UXM_MAXIMUM_DOCUMENT_X});

	accelerators.push_back({(FVIRTKEY | FNONE), VK_UP, UXM_SCROLL_DECREMENT_Y});
	accelerators.push_back({(FVIRTKEY | FNONE), VK_DOWN, UXM_SCROLL_INCREMENT_Y});
	accelerators.push_back({(FVIRTKEY | FNONE), VK_LEFT, UXM_SCROLL_DECREMENT_X});
	accelerators.push_back({(FVIRTKEY | FNONE), VK_RIGHT, UXM_SCROLL_INCREMENT_X});

	accelerators.push_back({(FVIRTKEY | FSHIFT), VK_SPACE, UXM_PAGING_DECREMENT_Y});
	accelerators.push_back({(FVIRTKEY | FNONE), VK_SPACE, UXM_PAGING_INCREMENT_Y});

	accelerators.push_back({(FVIRTKEY | FCONTROL | FSHIFT), VK_TAB, UXM_ACTIVE_TAB_DECREMENT});
	accelerators.push_back({(FVIRTKEY | FCONTROL | FNONE), VK_TAB, UXM_ACTIVE_TAB_INCREMENT});

	accelerators.push_back({(FVIRTKEY | FCONTROL), '5', UXM_STEP_INCREMENT});
	accelerators.push_back({(FVIRTKEY | FCONTROL), '6', UXM_STEP_DECREMENT});

	accelerators.push_back({(FVIRTKEY | FNONE), VK_F1, UXM_APP_ABOUT});

	return CreateAcceleratorTableW(accelerators.data(), int(accelerators.size()));
}

HMENU UXReader::UXReaderMainWindow::MainWindowMenu(void) const
{

	const HMENU hList = CreatePopupMenu();
	AppendMenuW(hList, MF_GRAYED, UXM_CLEAR_RECENT, L"&Clear Recent");

	const HMENU hFile = CreatePopupMenu();
	AppendMenuW(hFile, MF_GRAYED, UXM_OPEN_DOCUMENT, L"&Open...\tCtrl+O");
	AppendMenuW(hFile, MF_POPUP, UINT_PTR(hList), L"&Recent Files");
	AppendMenuW(hFile, MF_GRAYED, UXM_CLOSE_ALL, L"Close &All\tShift+Ctrl+W");
	AppendMenuW(hFile, MF_GRAYED, UXM_CLOSE_DOCUMENT, L"&Close\tCtrl+W");
	AppendMenuW(hFile, MF_SEPARATOR, 0, nullptr);
	AppendMenuW(hFile, MF_GRAYED, UXM_DOCUMENT_INFO, L"&Information...\tCtrl+I");
	AppendMenuW(hFile, MF_GRAYED, UXM_PRINT_DOCUMENT, L"&Print...\tCtrl+P");
	AppendMenuW(hFile, MF_SEPARATOR, 0, nullptr);
	AppendMenuW(hFile, MF_GRAYED, UXM_APP_EXIT, L"E&xit\tAlt+F4");

	const HMENU hEdit = CreatePopupMenu();
	AppendMenuW(hEdit, MF_GRAYED, UXM_COPY_TEXT, L"&Copy\tCtrl+C");
	AppendMenuW(hEdit, MF_GRAYED, UXM_SELECT_ALL, L"Select &All\tCtrl+A");
	AppendMenuW(hEdit, MF_SEPARATOR, 0, nullptr);
	AppendMenuW(hEdit, MF_GRAYED, UXM_FIND_TEXT, L"&Find...\tCtrl+F");
	AppendMenuW(hEdit, MF_GRAYED, UXM_FIND_INCREMENT, L"Find &Next\tCtrl+N");
	AppendMenuW(hEdit, MF_GRAYED, UXM_FIND_DECREMENT, L"Find &Previous\tCtrl+M");
	AppendMenuW(hEdit, MF_SEPARATOR, 0, nullptr);
	AppendMenuW(hEdit, MF_GRAYED, UXM_FIND_SELECTION, L"Find &Selection\tCtrl+E");
	AppendMenuW(hEdit, MF_GRAYED, UXM_GOTO_SELECTION, L"&Goto Selection\tCtrl+J");

	const HMENU hView = CreatePopupMenu();
	AppendMenuW(hView, MF_GRAYED, UXM_HIDE_SIDEBAR, L"&Hide Sidebar\tCtrl+2");
	AppendMenuW(hView, MF_GRAYED, UXM_SHOW_OUTLINE, L"Table of &Contents\tCtrl+3");
	AppendMenuW(hView, MF_GRAYED, UXM_SHOW_THUMBS, L"&Thumbnails\tCtrl+4");
	AppendMenuW(hView, MF_SEPARATOR, 0, nullptr);
	AppendMenuW(hView, MF_GRAYED, UXM_ZOOM_INCREMENT, L"Zoom &In\tCtrl +");
	AppendMenuW(hView, MF_GRAYED, UXM_ZOOM_DECREMENT, L"Zoom &Out\tCtrl -");
	AppendMenuW(hView, MF_GRAYED, UXM_ZOOM_FIT_WIDTH, L"Zoom &Fit Width\tCtrl+0");
	AppendMenuW(hView, MF_GRAYED, UXM_ZOOM_ONE_TO_ONE, L"&Zoom Actual\tCtrl+1");

	const HMENU hGoto = CreatePopupMenu();
	AppendMenuW(hGoto, MF_GRAYED, UXM_GOTO_PAGE, L"&Goto Page...\tCtrl+G");
	AppendMenuW(hGoto, MF_SEPARATOR, 0, nullptr);
	AppendMenuW(hGoto, MF_GRAYED, UXM_PAGING_DECREMENT_Y, L"Page &Up\tPgUp");
	AppendMenuW(hGoto, MF_GRAYED, UXM_PAGING_INCREMENT_Y, L"Page &Down\tPgDn");
	AppendMenuW(hGoto, MF_GRAYED, UXM_MINIMUM_DOCUMENT_Y, L"&First Page\tHome");
	AppendMenuW(hGoto, MF_GRAYED, UXM_MAXIMUM_DOCUMENT_Y, L"&Last Page\tEnd");
	AppendMenuW(hGoto, MF_SEPARATOR, 0, nullptr);
	AppendMenuW(hGoto, MF_GRAYED, UXM_STEP_INCREMENT, L"Step F&orward\tCtrl+5");
	AppendMenuW(hGoto, MF_GRAYED, UXM_STEP_DECREMENT, L"Step B&ack\tCtrl+6");

	const HMENU hHelp = CreatePopupMenu();
	AppendMenuW(hHelp, MF_GRAYED, UXM_APP_ABOUT, L"&About...\tF1");

	const HMENU hMenu = CreateMenu();
	AppendMenuW(hMenu, MF_POPUP, UINT_PTR(hFile), L"&File");
	AppendMenuW(hMenu, MF_POPUP, UINT_PTR(hEdit), L"&Edit");
	AppendMenuW(hMenu, MF_POPUP, UINT_PTR(hView), L"&View");
	AppendMenuW(hMenu, MF_POPUP, UINT_PTR(hGoto), L"&Go");
	AppendMenuW(hMenu, MF_POPUP, UINT_PTR(hHelp), L"&Help");

	return hMenu;
}

HMENU UXReader::UXReaderMainWindow::MainContextMenu(void) const
{

	const HMENU hMenu = CreatePopupMenu();

	AppendMenuW(hMenu, MF_GRAYED, UXM_OPEN_DOCUMENT, L"&Open...\tCtrl+O");
	AppendMenuW(hMenu, MF_SEPARATOR, 0, nullptr);
	AppendMenuW(hMenu, MF_STRING, UXM_APP_EXIT, L"E&xit\tAlt+F4");

	return hMenu;
}

bool UXReaderMainWindow::PreTranslateMessage(MSG *pMsg) const
{

	if (pMsg->hwnd == m_WindowHandle) // UXReaderMainWindow message
	{
		if (TranslateAcceleratorW(pMsg->hwnd, m_Accelerators, pMsg) == FALSE)
		{
			TranslateMessage(pMsg); DispatchMessageW(pMsg);
		}
	}
	else // Message for some other window
	{
		TranslateMessage(pMsg); DispatchMessageW(pMsg);
	}

	return true;
}

//
//	Window message methods
//

void UXReaderMainWindow::RegisterMessages(void)
{

	m_MessageMap.emplace(WM_CREATE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowCreate(h, m, w, l); });
	m_MessageMap.emplace(WM_SIZE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowSize(h, m, w, l); });
	m_MessageMap.emplace(WM_GETMINMAXINFO, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowMinMax(h, m, w, l); });
	m_MessageMap.emplace(WM_ERASEBKGND, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowErase(h, m, w, l); });
	m_MessageMap.emplace(WM_PAINT, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowPaint(h, m, w, l); });
	m_MessageMap.emplace(WM_CLOSE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowClose(h, m, w, l); });
	m_MessageMap.emplace(WM_DESTROY, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowDestroy(h, m, w, l); });
	m_MessageMap.emplace(WM_COPYDATA, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->CopyData(h, m, w, l); });
	m_MessageMap.emplace(WM_INITMENUPOPUP, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->MenuInit(h, m, w, l); });
	m_MessageMap.emplace(WM_CONTEXTMENU, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->MenuContext(h, m, w, l); });
	m_MessageMap.emplace(WM_COMMAND, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowCommand(h, m, w, l); });
	m_MessageMap.emplace(WM_MOUSEACTIVATE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->MouseActivate(h, m, w, l); });
	m_MessageMap.emplace(WM_MOUSEWHEEL, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->MouseWheelV(h, m, w, l); });
	m_MessageMap.emplace(WM_MOUSEHWHEEL, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->MouseWheelH(h, m, w, l); });
}

LRESULT UXReaderMainWindow::WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//CREATESTRUCTW *cs = reinterpret_cast<CREATESTRUCTW *>(lParam);

	ChangeWindowMessageFilterEx(hWnd, WM_COPYDATA, MSGFLT_ALLOW, 0);

	m_WindowHandle = hWnd;

	return 0;
}

LRESULT UXReaderMainWindow::WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	const int cw = LOWORD(lParam); const int ch = HIWORD(lParam);

	if (m_DocumentView == nullptr)
		InvalidateRect(hWnd, nullptr, FALSE);
	else
		m_DocumentView->UpdateWH(cw, ch);

	return 0;
}

LRESULT UXReaderMainWindow::WindowMinMax(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	MINMAXINFO *minMaxInfo = reinterpret_cast<MINMAXINFO *>(lParam);
	minMaxInfo->ptMinTrackSize = {m_MinimumWindowSize, m_MinimumWindowSize};

	return 0;
}

LRESULT UXReaderMainWindow::WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	return 0;
}

LRESULT UXReaderMainWindow::WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps {}; HDC hDC = BeginPaint(hWnd, &ps);

	if (IsRectEmpty(&ps.rcPaint) == FALSE) // Paint the requested area
	{
		FillRect(hDC, &ps.rcPaint, UXReaderSupport::DocumentBackgroundBrush());
		//HGDIOBJ font = UXReaderSupport::SystemFont(hWnd); HGDIOBJ oldFont = SelectObject(hDC, font);
		//SetTextColor(hDC, 0x00FFFFFF); SetBkMode(hDC, TRANSPARENT); RECT area; GetClientRect(hWnd, &area);
		//DrawTextW(hDC, kWindowClassName, -1, &area, (DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP | DT_NOPREFIX));
		//SelectObject(hDC, oldFont);
	}

	EndPaint(hWnd, &ps);

	return 0;
}

LRESULT UXReaderMainWindow::WindowClose(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	DestroyWindow(hWnd);

	return 0;
}

LRESULT UXReaderMainWindow::WindowDestroy(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	PostQuitMessage(0);

	return 0;
}

LRESULT UXReaderMainWindow::CopyData(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	const COPYDATASTRUCT *cds = reinterpret_cast<COPYDATASTRUCT *>(lParam);

	if ((cds != nullptr) && (cds->dwData == 0x0042) && (cds->cbData > 0))
	{
		DBLog(L"%S '%s'\n", __FUNCSIG__, cds->lpData);
	}

	return 0;
}

LRESULT UXReaderMainWindow::MenuInit(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if (HIWORD(lParam) == FALSE)
	{
		const HMENU hMenu = HMENU(wParam);

		if (const int items = GetMenuItemCount(hMenu))
		{
			for (int item = 0; item < items; item++)
			{
				const int id = GetMenuItemID(hMenu, item);

				if (id < UXM_APP_NONE) continue; // Skip

				bool enable = false; bool check = false;

				switch (id) // Menu item identifier
				{
					case UXM_OPEN_DOCUMENT:
					{
						enable = CanOpenDocument(); break;
					}

					case UXM_CLEAR_RECENT:
					{
						enable = CanClearRecentFileList(); break;
					}

					case UXM_CLOSE_ALL:
					{
						enable = CanCloseAllDocuments(); break;
					}

					case UXM_CLOSE_DOCUMENT:
					{
						enable = CanCloseDocument(); break;
					}

					case UXM_DOCUMENT_INFO:
					{
						enable = CanShowInformation(); break;
					}

					case UXM_PRINT_DOCUMENT:
					{
						enable = CanPrintDocument(); break;
					}

					case UXM_COPY_TEXT:
					{
						enable = CanCopyDocumentText(); break;
					}

					case UXM_SELECT_ALL:
					{
						enable = CanSelectAllDocumentText(); break;
					}

					case UXM_FIND_TEXT:
					{
						enable = CanSearchTextFocus(); break;
					}

					case UXM_FIND_INCREMENT:
					{
						enable = CanSearchHitIncrement(); break;
					}

					case UXM_FIND_DECREMENT:
					{
						enable = CanSearchHitDecrement(); break;
					}

					case UXM_FIND_SELECTION:
					{
						enable = CanFindTextSelection(); break;
					}

					case UXM_GOTO_SELECTION:
					{
						enable = CanGotoTextSelection(); break;
					}

					case UXM_HIDE_SIDEBAR:
					{
						enable = CanHideDocumentSidebar(); break;
					}

					case UXM_SHOW_OUTLINE:
					{
						enable = CanShowDocumentOutline(); break;
					}

					case UXM_SHOW_THUMBS:
					{
						enable = CanShowDocumentThumbs(); break;
					}

					case UXM_ZOOM_INCREMENT:
					{
						enable = CanZoomIncrement(); break;
					}

					case UXM_ZOOM_DECREMENT:
					{
						enable = CanZoomDecrement(); break;
					}

					case UXM_ZOOM_FIT_WIDTH:
					{
						enable = CanZoomFitWidth(); break;
					}

					case UXM_ZOOM_ONE_TO_ONE:
					{
						enable = CanZoomOneToOne(); break;
					}

					case UXM_GOTO_PAGE:
					{
						enable = CanPageNumberFocus(); break;
					}

					case UXM_PAGE_INCREMENT:
					{
						enable = CanPageNumberIncrement(); break;
					}

					case UXM_PAGE_DECREMENT:
					{
						enable = CanPageNumberDecrement(); break;
					}

					case UXM_STEP_INCREMENT:
					{
						enable = CanPageNavigateIncrement(); break;
					}

					case UXM_STEP_DECREMENT:
					{
						enable = CanPageNavigateDecrement(); break;
					}

					case UXM_SCROLL_INCREMENT_Y:
					{
						enable = CanLineScrollIncrementY(); break;
					}

					case UXM_SCROLL_DECREMENT_Y:
					{
						enable = CanLineScrollDecrementY(); break;
					}

					case UXM_SCROLL_INCREMENT_X:
					{
						enable = CanLineScrollIncrementX(); break;
					}

					case UXM_SCROLL_DECREMENT_X:
					{
						enable = CanLineScrollDecrementX(); break;
					}

					case UXM_PAGING_INCREMENT_Y:
					{
						enable = CanPageScrollIncrementY(); break;
					}

					case UXM_PAGING_DECREMENT_Y:
					{
						enable = CanPageScrollDecrementY(); break;
					}

					case UXM_PAGING_INCREMENT_X:
					{
						enable = CanPageScrollIncrementX(); break;
					}

					case UXM_PAGING_DECREMENT_X:
					{
						enable = CanPageScrollDecrementX(); break;
					}

					case UXM_MINIMUM_DOCUMENT_Y:
					{
						enable = CanGotoMinimumDocumentY(); break;
					}

					case UXM_MAXIMUM_DOCUMENT_Y:
					{
						enable = CanGotoMaximumDocumentY(); break;
					}

					case UXM_MINIMUM_DOCUMENT_X:
					{
						enable = CanGotoMinimumDocumentX(); break;
					}

					case UXM_MAXIMUM_DOCUMENT_X:
					{
						enable = CanGotoMaximumDocumentX(); break;
					}

					case UXM_ACTIVE_TAB_INCREMENT:
					{
						enable = CanActiveTabIncrement(); break;
					}

					case UXM_ACTIVE_TAB_DECREMENT:
					{
						enable = CanActiveTabDecrement(); break;
					}

					case UXM_APP_ABOUT:
					{
						enable = CanShowAbout(); break;
					}

					case UXM_APP_EXIT:
					{
						enable = true; break;
					}
				}

				UINT checked = (check ? MF_CHECKED : MF_UNCHECKED);
				CheckMenuItem(hMenu, item, (MF_BYPOSITION | checked));

				UINT enabled = (enable ? MF_ENABLED : MF_GRAYED);
				EnableMenuItem(hMenu, item, (MF_BYPOSITION | enabled));
			}
		}
	}

	return 0;
}

LRESULT UXReaderMainWindow::MenuContext(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	const int px = GET_X_LPARAM(lParam); const int py = GET_Y_LPARAM(lParam);

	if ((px >= 0) && (py >= 0)) // Valid right click screen coordinates
	{
		if (const HMENU hContextMenu = MainContextMenu()) // Show the context menu
		{
			const UINT flags = (TPM_RIGHTBUTTON | (GetSystemMetrics(SM_MENUDROPALIGNMENT) ? TPM_RIGHTALIGN : TPM_LEFTALIGN));

			TrackPopupMenuEx(hContextMenu, flags, px, py, hWnd, nullptr); DestroyMenu(hContextMenu);
		}
	}

	return 0;
}

LRESULT UXReaderMainWindow::WindowCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (LOWORD(wParam)) // WM_COMMAND
	{
		case UXM_OPEN_DOCUMENT:
		{
			OpenDocument(); break;
		}

		case UXM_CLEAR_RECENT:
		{
			ClearRecentFileList(); break;
		}

		case UXM_CLOSE_ALL:
		{
			CloseAllDocuments(); break;
		}

		case UXM_CLOSE_DOCUMENT:
		{
			CloseDocument(); break;
		}

		case UXM_DOCUMENT_INFO:
		{
			ShowInformation(); break;
		}

		case UXM_PRINT_DOCUMENT:
		{
			PrintDocument(); break;
		}

		case UXM_COPY_TEXT:
		{
			CopyDocumentText(); break;
		}

		case UXM_SELECT_ALL:
		{
			SelectAllDocumentText(); break;
		}

		case UXM_FIND_TEXT:
		{
			SearchTextFocus(); break;
		}

		case UXM_FIND_INCREMENT:
		{
			SearchHitIncrement(); break;
		}

		case UXM_FIND_DECREMENT:
		{
			SearchHitDecrement(); break;
		}

		case UXM_FIND_SELECTION:
		{
			FindTextSelection(); break;
		}

		case UXM_GOTO_SELECTION:
		{
			GotoTextSelection(); break;
		}

		case UXM_HIDE_SIDEBAR:
		{
			HideDocumentSidebar(); break;
		}

		case UXM_SHOW_OUTLINE:
		{
			ShowDocumentOutline(); break;
		}

		case UXM_SHOW_THUMBS:
		{
			ShowDocumentThumbs(); break;
		}

		case UXM_ZOOM_INCREMENT:
		{
			ZoomIncrement(); break;
		}

		case UXM_ZOOM_DECREMENT:
		{
			ZoomDecrement(); break;
		}

		case UXM_ZOOM_FIT_WIDTH:
		{
			ZoomFitWidth(); break;
		}

		case UXM_ZOOM_ONE_TO_ONE:
		{
			ZoomOneToOne(); break;
		}

		case UXM_GOTO_PAGE:
		{
			PageNumberFocus(); break;
		}

		case UXM_PAGE_INCREMENT:
		{
			PageNumberIncrement(); break;
		}

		case UXM_PAGE_DECREMENT:
		{
			PageNumberDecrement(); break;
		}

		case UXM_STEP_INCREMENT:
		{
			PageNavigateIncrement(); break;
		}

		case UXM_STEP_DECREMENT:
		{
			PageNavigateDecrement(); break;
		}

		case UXM_SCROLL_INCREMENT_Y:
		{
			LineScrollIncrementY(); break;
		}

		case UXM_SCROLL_DECREMENT_Y:
		{
			LineScrollDecrementY(); break;
		}

		case UXM_SCROLL_INCREMENT_X:
		{
			LineScrollIncrementX(); break;
		}

		case UXM_SCROLL_DECREMENT_X:
		{
			LineScrollDecrementX(); break;
		}

		case UXM_PAGING_INCREMENT_Y:
		{
			PageScrollIncrementY(); break;
		}

		case UXM_PAGING_DECREMENT_Y:
		{
			PageScrollDecrementY(); break;
		}

		case UXM_PAGING_INCREMENT_X:
		{
			PageScrollIncrementX(); break;
		}

		case UXM_PAGING_DECREMENT_X:
		{
			PageScrollDecrementX(); break;
		}

		case UXM_MINIMUM_DOCUMENT_Y:
		{
			GotoMinimumDocumentY(); break;
		}

		case UXM_MAXIMUM_DOCUMENT_Y:
		{
			GotoMaximumDocumentY(); break;
		}

		case UXM_MINIMUM_DOCUMENT_X:
		{
			GotoMinimumDocumentX(); break;
		}

		case UXM_MAXIMUM_DOCUMENT_X:
		{
			GotoMaximumDocumentX(); break;
		}

		case UXM_ACTIVE_TAB_INCREMENT:
		{
			ActiveTabIncrement(); break;
		}

		case UXM_ACTIVE_TAB_DECREMENT:
		{
			ActiveTabDecrement(); break;
		}

		case UXM_APP_ABOUT:
		{
			ShowAbout(); break;
		}

		case UXM_APP_EXIT:
		{
			PostMessageW(hWnd, WM_CLOSE, 0, 0); break;
		}

		default: // Default handler
		{
			return DefWindowProcW(hWnd, message, wParam, lParam);
		}
	}

	return 0;
}

LRESULT UXReader::UXReaderMainWindow::MouseActivate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if (GetFocus() != hWnd) SetFocus(hWnd);

	return MA_ACTIVATE;
}

LRESULT UXReaderMainWindow::MouseWheelV(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if (m_DocumentView != nullptr) m_DocumentView->MouseWheelV(wParam, lParam);

	return 0;
}

LRESULT UXReaderMainWindow::MouseWheelH(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if (m_DocumentView != nullptr) m_DocumentView->MouseWheelH(wParam, lParam);

	return 0;
}

//
//	Support methods
//

void UXReaderMainWindow::ShowOpenFileDialog(const HWND hWnd)
{

	wchar_t file[MAX_PATH]; RtlSecureZeroMemory(file, sizeof(file));
	wchar_t path[MAX_PATH]; RtlSecureZeroMemory(path, sizeof(path));

	OPENFILENAMEW ofn; RtlSecureZeroMemory(&ofn, sizeof(ofn)); ofn.lStructSize = sizeof(ofn); ofn.hwndOwner = hWnd;
	ofn.lpstrFile = file; ofn.nMaxFile = MAX_PATH; ofn.Flags = (OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST);
	if (SHGetFolderPathW(nullptr, CSIDL_PERSONAL, nullptr, SHGFP_TYPE_CURRENT, path) == S_OK) { ofn.lpstrInitialDir = path; }
	ofn.lpstrTitle = L"Open PDF"; ofn.lpstrFilter = L"PDFs\0*.pdf\0\0"; ofn.nFilterIndex = 1;

	if (GetOpenFileNameW(&ofn) != FALSE) OpenDocumentFile(file);
}

void UXReaderMainWindow::OpenDocumentFile(const wchar_t *filePath)
{

	if (const HDC hDC = GetDC(m_WindowHandle))
	{
		RECT rect; GetClientRect(m_WindowHandle, &rect);
		FillRect(hDC, &rect, UXReaderSupport::DocumentBackgroundBrush());
		ReleaseDC(m_WindowHandle, hDC);
	}

	const HCURSOR oldCursor = SetCursor(UXReaderSupport::WaitCursor());

	auto document = std::make_shared<UXReader::UXReaderDocument>(filePath);

	int errorCode = 0; if (document->OpenWithPassword(nullptr, errorCode) == true)
	{
		RECT rect; GetClientRect(m_WindowHandle, &rect); const int cx = 0; const int cy = 0;
		const int cw = (rect.right - rect.left - 100); const int ch = (rect.bottom - rect.top - 100 );

		m_DocumentView = std::make_unique<UXReader::UXReaderDocumentView>(document);
		if (m_DocumentView->Create(m_WindowHandle, cx, cy, cw, ch) == false) m_DocumentView = nullptr;

		if (m_DocumentView) m_DocumentView->UpdateWindowTitle([this](const wchar_t *text)
		{
			this->UpdateWindowTitle(text);
		});
	}

	SetCursor(oldCursor);
}

void UXReader::UXReaderMainWindow::UpdateWindowTitle(const wchar_t *text)
{

	SetWindowTextW(m_WindowHandle, text);
}

//
//	UI methods -> UXReaderMainWindow
//

void UXReaderMainWindow::OpenDocument(void)
{

	if (CanOpenDocument()) ShowOpenFileDialog(m_WindowHandle);
}

bool UXReader::UXReaderMainWindow::CanOpenDocument(void)
{

	return (m_DocumentView == nullptr);
}

void UXReader::UXReaderMainWindow::ClearRecentFileList(void)
{

	if (CanClearRecentFileList()) {}
}

bool UXReader::UXReaderMainWindow::CanClearRecentFileList(void)
{

	return false;
}

void UXReader::UXReaderMainWindow::OpenRecentFile(const int index)
{

	if (CanOpenRecentFile(index)) {}
}

bool UXReader::UXReaderMainWindow::CanOpenRecentFile(const int index)
{

	return false;
}

void UXReader::UXReaderMainWindow::CloseAllDocuments(void)
{

	if (CanCloseAllDocuments()) {}
}

bool UXReader::UXReaderMainWindow::CanCloseAllDocuments(void)
{

	return false;
}

void UXReaderMainWindow::CloseDocument(void)
{

	if (CanCloseDocument()) { m_DocumentView->Destroy(); m_DocumentView = nullptr; }

	SetWindowTextW(m_WindowHandle, kWindowTitle);
}

bool UXReader::UXReaderMainWindow::CanCloseDocument(void)
{

	return (m_DocumentView != nullptr);
}

void UXReader::UXReaderMainWindow::ActiveTabIncrement(void)
{

	if (CanActiveTabIncrement()) {}
}

bool UXReader::UXReaderMainWindow::CanActiveTabIncrement(void)
{

	return false;
}

void UXReader::UXReaderMainWindow::ActiveTabDecrement(void)
{

	if (CanActiveTabDecrement()) {}
}

bool UXReader::UXReaderMainWindow::CanActiveTabDecrement(void)
{

	return false;
}

void UXReader::UXReaderMainWindow::ShowAbout(void)
{

	if (CanShowAbout()) {}
}

bool UXReader::UXReaderMainWindow::CanShowAbout(void)
{

	return false;
}

//
//	UI methods -> UXReaderDocumentView
//

void UXReader::UXReaderMainWindow::ShowInformation(void)
{

	if (CanShowInformation()) m_DocumentView->ShowInformation();
}

bool UXReader::UXReaderMainWindow::CanShowInformation(void)
{

	return (m_DocumentView ? m_DocumentView->CanShowInformation() : false);
}

void UXReader::UXReaderMainWindow::PrintDocument(void)
{

	if (CanPrintDocument()) m_DocumentView->PrintDocument();
}

bool UXReader::UXReaderMainWindow::CanPrintDocument(void)
{

	return (m_DocumentView ? m_DocumentView->CanPrintDocument() : false);
}

void UXReader::UXReaderMainWindow::CopyDocumentText(void)
{

	if (CanCopyDocumentText()) m_DocumentView->CopyDocumentText();
}

bool UXReader::UXReaderMainWindow::CanCopyDocumentText(void)
{

	return (m_DocumentView ? m_DocumentView->CanCopyDocumentText() : false);
}

void UXReader::UXReaderMainWindow::SelectAllDocumentText(void)
{

	if (CanSelectAllDocumentText()) m_DocumentView->SelectAllDocumentText();
}

bool UXReader::UXReaderMainWindow::CanSelectAllDocumentText(void)
{

	return (m_DocumentView ? m_DocumentView->CanSelectAllDocumentText() : false);
}

void UXReader::UXReaderMainWindow::SearchTextFocus(void)
{

	if (CanSearchTextFocus()) m_DocumentView->SearchTextFocus();
}

bool UXReader::UXReaderMainWindow::CanSearchTextFocus(void)
{

	return (m_DocumentView ? m_DocumentView->CanSearchTextFocus() : false);
}

void UXReader::UXReaderMainWindow::SearchHitIncrement(void)
{

	if (CanSearchHitIncrement()) m_DocumentView->SearchHitIncrement();
}

bool UXReader::UXReaderMainWindow::CanSearchHitIncrement(void)
{

	return (m_DocumentView ? m_DocumentView->CanSearchHitIncrement() : false);
}

void UXReader::UXReaderMainWindow::SearchHitDecrement(void)
{

	if (CanSearchHitDecrement()) m_DocumentView->SearchHitDecrement();
}

bool UXReader::UXReaderMainWindow::CanSearchHitDecrement(void)
{

	return (m_DocumentView ? m_DocumentView->CanSearchHitDecrement() : false);
}

void UXReader::UXReaderMainWindow::FindTextSelection(void)
{

	if (CanFindTextSelection()) m_DocumentView->FindTextSelection();
}

bool UXReader::UXReaderMainWindow::CanFindTextSelection(void)
{

	return (m_DocumentView ? m_DocumentView->CanFindTextSelection() : false);
}

void UXReader::UXReaderMainWindow::GotoTextSelection(void)
{

	if (CanGotoTextSelection()) m_DocumentView->GotoTextSelection();
}

bool UXReader::UXReaderMainWindow::CanGotoTextSelection(void)
{

	return (m_DocumentView ? m_DocumentView->CanGotoTextSelection() : false);
}

void UXReader::UXReaderMainWindow::HideDocumentSidebar(void)
{

	if (CanHideDocumentSidebar()) m_DocumentView->HideDocumentSidebar();
}

bool UXReader::UXReaderMainWindow::CanHideDocumentSidebar(void)
{

	return (m_DocumentView ? m_DocumentView->CanHideDocumentSidebar() : false);
}

void UXReader::UXReaderMainWindow::ShowDocumentOutline(void)
{

	if (CanShowDocumentOutline()) m_DocumentView->ShowDocumentOutline();
}

bool UXReader::UXReaderMainWindow::CanShowDocumentOutline(void)
{

	return (m_DocumentView ? m_DocumentView->CanShowDocumentOutline() : false);
}

void UXReader::UXReaderMainWindow::ShowDocumentThumbs(void)
{

	if (CanShowDocumentThumbs()) m_DocumentView->ShowDocumentThumbs();
}

bool UXReader::UXReaderMainWindow::CanShowDocumentThumbs(void)
{

	return (m_DocumentView ? m_DocumentView->CanShowDocumentThumbs() : false);
}

void UXReader::UXReaderMainWindow::ZoomIncrement(void)
{

	if (CanZoomIncrement()) m_DocumentView->ZoomIncrement();
}

bool UXReader::UXReaderMainWindow::CanZoomIncrement(void)
{

	return (m_DocumentView ? m_DocumentView->CanZoomIncrement() : false);
}

void UXReader::UXReaderMainWindow::ZoomDecrement(void)
{

	if (CanZoomDecrement()) m_DocumentView->ZoomDecrement();
}

bool UXReader::UXReaderMainWindow::CanZoomDecrement(void)
{

	return (m_DocumentView ? m_DocumentView->CanZoomDecrement() : false);
}

void UXReader::UXReaderMainWindow::ZoomFitWidth(void)
{

	if (CanZoomFitWidth()) m_DocumentView->ZoomFitWidth();
}

bool UXReader::UXReaderMainWindow::CanZoomFitWidth(void)
{

	return (m_DocumentView ? m_DocumentView->CanZoomFitWidth() : false);
}

void UXReader::UXReaderMainWindow::ZoomOneToOne(void)
{

	if (CanZoomOneToOne()) m_DocumentView->ZoomOneToOne();
}

bool UXReader::UXReaderMainWindow::CanZoomOneToOne(void)
{

	return (m_DocumentView ? m_DocumentView->CanZoomOneToOne() : false);
}

void UXReader::UXReaderMainWindow::PageNumberFocus(void)
{

	if (CanPageNumberFocus()) m_DocumentView->PageNumberFocus();
}

bool UXReader::UXReaderMainWindow::CanPageNumberFocus(void)
{

	return (m_DocumentView ? m_DocumentView->CanPageNumberFocus() : false);
}

void UXReader::UXReaderMainWindow::PageNumberIncrement(void)
{

	if (CanPageNumberIncrement()) m_DocumentView->PageNumberIncrement();
}

bool UXReader::UXReaderMainWindow::CanPageNumberIncrement(void)
{

	return (m_DocumentView ? m_DocumentView->CanPageNumberIncrement() : false);
}

void UXReader::UXReaderMainWindow::PageNumberDecrement(void)
{

	if (CanPageNumberDecrement()) m_DocumentView->PageNumberDecrement();
}

bool UXReader::UXReaderMainWindow::CanPageNumberDecrement(void)
{

	return (m_DocumentView ? m_DocumentView->CanPageNumberDecrement() : false);
}

void UXReader::UXReaderMainWindow::PageNavigateIncrement(void)
{

	if (CanPageNavigateIncrement()) m_DocumentView->PageNavigateIncrement();
}

bool UXReader::UXReaderMainWindow::CanPageNavigateIncrement(void)
{

	return (m_DocumentView ? m_DocumentView->CanPageNavigateIncrement() : false);
}

void UXReader::UXReaderMainWindow::PageNavigateDecrement(void)
{

	if (CanPageNavigateDecrement()) m_DocumentView->PageNavigateDecrement();
}

bool UXReader::UXReaderMainWindow::CanPageNavigateDecrement(void)
{

	return (m_DocumentView ? m_DocumentView->CanPageNavigateDecrement() : false);
}

void UXReader::UXReaderMainWindow::LineScrollIncrementY(void)
{

	if (CanLineScrollIncrementY()) m_DocumentView->LineScrollIncrementY();
}

bool UXReader::UXReaderMainWindow::CanLineScrollIncrementY(void)
{

	return (m_DocumentView ? m_DocumentView->CanLineScrollIncrementY() : false);
}

void UXReader::UXReaderMainWindow::LineScrollDecrementY(void)
{

	if (CanLineScrollDecrementY()) m_DocumentView->LineScrollDecrementY();
}

bool UXReader::UXReaderMainWindow::CanLineScrollDecrementY(void)
{

	return (m_DocumentView ? m_DocumentView->CanLineScrollDecrementY() : false);
}

void UXReader::UXReaderMainWindow::LineScrollIncrementX(void)
{

	if (CanLineScrollIncrementX()) m_DocumentView->LineScrollIncrementX();
}

bool UXReader::UXReaderMainWindow::CanLineScrollIncrementX(void)
{

	return (m_DocumentView ? m_DocumentView->CanLineScrollIncrementX() : false);
}

void UXReader::UXReaderMainWindow::LineScrollDecrementX(void)
{

	if (CanLineScrollDecrementX()) m_DocumentView->LineScrollDecrementX();
}

bool UXReader::UXReaderMainWindow::CanLineScrollDecrementX(void)
{

	return (m_DocumentView ? m_DocumentView->CanLineScrollDecrementX() : false);
}

void UXReader::UXReaderMainWindow::PageScrollIncrementY(void)
{

	if (CanPageScrollIncrementY()) m_DocumentView->PageScrollIncrementY();
}

bool UXReader::UXReaderMainWindow::CanPageScrollIncrementY(void)
{

	return (m_DocumentView ? m_DocumentView->CanPageScrollIncrementY() : false);
}

void UXReader::UXReaderMainWindow::PageScrollDecrementY(void)
{

	if (CanPageScrollDecrementY()) m_DocumentView->PageScrollDecrementY();
}

bool UXReader::UXReaderMainWindow::CanPageScrollDecrementY(void)
{

	return (m_DocumentView ? m_DocumentView->CanPageScrollDecrementY() : false);
}

void UXReader::UXReaderMainWindow::PageScrollIncrementX(void)
{

	if (CanPageScrollIncrementX()) m_DocumentView->PageScrollIncrementX();
}

bool UXReader::UXReaderMainWindow::CanPageScrollIncrementX(void)
{

	return (m_DocumentView ? m_DocumentView->CanPageScrollIncrementX() : false);
}

void UXReader::UXReaderMainWindow::PageScrollDecrementX(void)
{

	if (CanPageScrollDecrementX()) m_DocumentView->PageScrollDecrementX();
}

bool UXReader::UXReaderMainWindow::CanPageScrollDecrementX(void)
{

	return (m_DocumentView ? m_DocumentView->CanPageScrollDecrementX() : false);
}

void UXReader::UXReaderMainWindow::GotoMinimumDocumentY(void)
{

	if (CanGotoMinimumDocumentY()) m_DocumentView->GotoMinimumDocumentY();
}

bool UXReader::UXReaderMainWindow::CanGotoMinimumDocumentY(void)
{

	return (m_DocumentView ? m_DocumentView->CanGotoMinimumDocumentY() : false);
}

void UXReader::UXReaderMainWindow::GotoMaximumDocumentY(void)
{

	if (CanGotoMaximumDocumentY()) m_DocumentView->GotoMaximumDocumentY();
}

bool UXReader::UXReaderMainWindow::CanGotoMaximumDocumentY(void)
{

	return (m_DocumentView ? m_DocumentView->CanGotoMaximumDocumentY() : false);
}

void UXReader::UXReaderMainWindow::GotoMinimumDocumentX(void)
{

	if (CanGotoMinimumDocumentX()) m_DocumentView->GotoMinimumDocumentX();
}

bool UXReader::UXReaderMainWindow::CanGotoMinimumDocumentX(void)
{

	return (m_DocumentView ? m_DocumentView->CanGotoMinimumDocumentX() : false);
}

void UXReader::UXReaderMainWindow::GotoMaximumDocumentX(void)
{

	if (CanGotoMaximumDocumentX()) m_DocumentView->GotoMaximumDocumentX();
}

bool UXReader::UXReaderMainWindow::CanGotoMaximumDocumentX(void)
{

	return (m_DocumentView ? m_DocumentView->CanGotoMaximumDocumentX() : false);
}
