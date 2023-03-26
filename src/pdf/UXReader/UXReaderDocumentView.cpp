//
//	UXReaderDocumentView.cpp
//	UXReader v0.1
//
//	Copyright � 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderDocument.h"
#include "UXReaderDocumentView.h"
#include "UXReaderDocumentPane.h"
#include "UXReaderToolbarPane.h"
#include "UXReaderToolbarItem.h"
#include "UXReaderToolbarEdit.h"
#include "UXReaderToolbarText.h"
#include "UXReaderStatusPane.h"

using namespace UXReader;

//
//	Constants
//

constexpr int searchTimerTick = 100;
constexpr int searchTimerTock = 2000;

static wchar_t *const kWindowClassName = L"UXReaderDocumentViewClass";

//
//	UXReaderDocumentView methods
//

UXReader::UXReaderDocumentView::UXReaderDocumentView(const std::shared_ptr<UXReaderDocument>& document)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, this);

	m_Document = document; RegisterMessages();
}

UXReader::UXReaderDocumentView::~UXReaderDocumentView(void)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, this);

	m_ToolbarPane == nullptr; m_DocumentPane = nullptr; m_StatusPane = nullptr;

	m_Document = nullptr; m_WindowHandle = nullptr; m_ParentWindow = nullptr;

	//DBLog(L"%S 0x%p\n", __FUNCSIG__, this);
}

ATOM UXReader::UXReaderDocumentView::DoRegisterWindowClass(const HMODULE hModule)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, hModule);

	WNDCLASSEXW wcex; RtlSecureZeroMemory(&wcex, sizeof(wcex));

	wcex.hInstance = hModule;
	wcex.lpszClassName = kWindowClassName;
	wcex.style = 0; wcex.lpszMenuName = nullptr;
	wcex.lpfnWndProc = UXReaderDocumentView::WindowDispatch;
	wcex.hIcon = nullptr; wcex.hIconSm = nullptr; wcex.hbrBackground = nullptr;
	wcex.hCursor = UXReaderSupport::ArrowCursor();
	wcex.cbClsExtra = 0; wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEXW);

	return RegisterClassExW(&wcex);
}

BOOL UXReader::UXReaderDocumentView::UnRegisterWindowClass(const HMODULE hModule)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, hModule);

	return UnregisterClassW(kWindowClassName, hModule);
}

LRESULT CALLBACK UXReader::UXReaderDocumentView::WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	if (message == WM_NCCREATE) SetWindowLongPtrW(hWnd, GWLP_USERDATA, LONG_PTR((LPCREATESTRUCT(lParam))->lpCreateParams));

	UXReaderDocumentView *thisWindow = reinterpret_cast<UXReaderDocumentView *>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

	if (thisWindow != nullptr)
		return thisWindow->WindowProcedure(hWnd, message, wParam, lParam);
	else
		return DefWindowProcW(hWnd, message, wParam, lParam);
}

LRESULT UXReader::UXReaderDocumentView::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	auto entry = m_MessageMap.find(message);

	if (entry == m_MessageMap.end())
		return DefWindowProcW(hWnd, message, wParam, lParam);
	else
		return entry->second(hWnd, message, wParam, lParam);
}

bool UXReader::UXReaderDocumentView::Create(const HWND hParent, const int x, const int y, const int w, const int h)
{
	//DBLog(L"%S 0x%p %i %i %i %i\n", __FUNCSIG__, hParent, x, y, w, h);

	if ((m_Document == nullptr) || (m_Document->IsOpen() == false)) return false;

	const DWORD ws = (WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN); const DWORD es = (WS_EX_NOPARENTNOTIFY); // Window style

	const HWND hWnd = CreateWindowExW(es, kWindowClassName, nullptr, ws, x, y, w, h, hParent, HMENU(this), UXReaderSupport::Module(), this);

	if (hWnd == nullptr) { const DWORD ec = GetLastError(); DBLog(L"%S Unable to create window (%lu).\n", __FUNCSIG__, ec); }

	return (hWnd != nullptr);
}

void UXReader::UXReaderDocumentView::Destroy(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	DestroyWindow(m_WindowHandle);

	//DBLog(L"%S\n", __FUNCSIG__);
}

void UXReader::UXReaderDocumentView::UpdateXYWH(const int x, const int y, const int w, const int h)
{
	//DBLog(L"%S %i %i %i %i\n", __FUNCSIG__, x, y, w, h);

	SetWindowPos(m_WindowHandle, nullptr, x, y, w, h, (SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOZORDER));

	RedrawWindow(m_WindowHandle, nullptr, nullptr, (RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN)); // !!!
}

void UXReader::UXReaderDocumentView::UpdateWH(const int w, const int h)
{
	//DBLog(L"%S %i %i\n", __FUNCSIG__, w, h);

	SetWindowPos(m_WindowHandle, nullptr, 0, 0, w, h, (SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOMOVE | SWP_NOZORDER));

	RedrawWindow(m_WindowHandle, nullptr, nullptr, (RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN)); // !!!
}

//
//	Window message methods
//

void UXReader::UXReaderDocumentView::RegisterMessages(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	m_MessageMap.emplace(WM_CREATE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowCreate(h, m, w, l); });
	m_MessageMap.emplace(WM_SIZE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowSize(h, m, w, l); });
	m_MessageMap.emplace(WM_ERASEBKGND, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowErase(h, m, w, l); });
	m_MessageMap.emplace(WM_PAINT, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowPaint(h, m, w, l); });
	m_MessageMap.emplace(WM_TIMER, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowTimer(h, m, w, l); });

	m_MessageMap.emplace(UX_SEARCH_FOUND, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->SearchFound(h, m, w, l); });
}

LRESULT UXReader::UXReaderDocumentView::WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p 0x%p\n", __FUNCSIG__, hWnd, wParam, lParam);

	//CREATESTRUCTW *cs = reinterpret_cast<CREATESTRUCTW *>(lParam);

	m_WindowHandle = hWnd; m_ParentWindow = GetParent(hWnd);

	RECT rect; GetClientRect(hWnd, &rect); const int cx = 0; const int cy = 0;
	const int cw = (rect.right - rect.left); const int ch = (rect.bottom - rect.top);

	m_ToolbarPane = std::make_unique<UXReader::UXReaderToolbarPane>();
	m_DocumentPane = std::make_unique<UXReader::UXReaderDocumentPane>(m_Document);
	m_StatusPane = std::make_unique<UXReader::UXReaderStatusPane>();

	const int th = m_ToolbarPane->PaneHeight(); const int sh = m_StatusPane->PaneHeight();

	if (m_ToolbarPane->Create(hWnd, cx, cy, cw, th) == false) m_ToolbarPane = nullptr;
	if (m_DocumentPane->Create(hWnd, cx, th, cw, (ch-th-sh)) == false) m_DocumentPane = nullptr;
	if (m_StatusPane->Create(hWnd, cx, (ch-sh), cw, sh) == false) m_StatusPane = nullptr;

	if (m_ToolbarPane != nullptr) // UXReaderToolbarPane
	{
		if (auto item = m_ToolbarPane->NumberEditItem())
		{
			item->EnterSelect([this](int id) { this->NumberEnterSelect(id); });
			item->TextChanged([this](int id) { this->NumberTextChanged(id); });
			item->ChangeFocus([this](int id) { this->NumberChangeFocus(id); });
		}

		if (auto item = m_ToolbarPane->SearchEditItem())
		{
			item->EnterSelect([this](int id) { this->SearchEnterSelect(id); });
			item->TextChanged([this](int id) { this->SearchTextChanged(id); });
			item->ChangeFocus([this](int id) { this->SearchChangeFocus(id); });
		}

		if (auto item = m_ToolbarPane->PageDecrementItem())
		{
			item->ItemClicked([this](int id) { this->ToolbarItemClicked(id); });
		}

		if (auto item = m_ToolbarPane->PageIncrementItem())
		{
			item->ItemClicked([this](int id) { this->ToolbarItemClicked(id); });
		}

		if (auto item = m_ToolbarPane->ZoomDecrementItem())
		{
			item->ItemClicked([this](int id) { this->ToolbarItemClicked(id); });
		}

		if (auto item = m_ToolbarPane->ZoomIncrementItem())
		{
			item->ItemClicked([this](int id) { this->ToolbarItemClicked(id); });
		}
	}

	if (m_DocumentPane != nullptr) // UXReaderDocumentPane
	{
		//m_DocumentPane->ViewPortChanged([this]() { this->ViewPortChanged(); });
		m_DocumentPane->VisiblePagesChanged([this]() { this->VisiblePagesChanged(); });
		m_DocumentPane->CurrentPageChanged([this]() { this->CurrentPageChanged(); });
		auto sf = [this](bool cancel, int found) { this->SearchFinished(cancel, found); };
		auto sp = [this](int index, int found) { this->SearchProgress(index, found); };
		m_DocumentPane->SearchFinished(sf); m_DocumentPane->SearchProgress(sp);
	}

	return 0;
}

LRESULT UXReader::UXReaderDocumentView::WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p 0x%p\n", __FUNCSIG__, hWnd, wParam, lParam);

	if ((m_ToolbarPane == nullptr) && (m_DocumentPane == nullptr) && (m_StatusPane == nullptr))
	{
		InvalidateRect(hWnd, nullptr, FALSE);
	}
	else // Position and resize panes
	{
		const int cw = LOWORD(lParam); const int ch = HIWORD(lParam);
		const int cx = 0; const int cy = 0; int th = 0; int sh = 0;

		if (m_ToolbarPane != nullptr) th = m_ToolbarPane->PaneHeight();
		if (m_StatusPane != nullptr) sh = m_StatusPane->PaneHeight();

		if (m_ToolbarPane != nullptr) m_ToolbarPane->UpdateXYWH(cx, cy, cw, th);
		if (m_DocumentPane != nullptr) m_DocumentPane->UpdateXYWH(cx, th, cw, (ch-th-sh));
		if (m_StatusPane != nullptr) m_StatusPane->UpdateXYWH(cx, (ch-sh), cw, sh);
	}

	return 0;
}

LRESULT UXReader::UXReaderDocumentView::WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p 0x%p\n", __FUNCSIG__, hWnd, wParam, lParam);

	return 0;
}

LRESULT UXReader::UXReaderDocumentView::WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p 0x%p\n", __FUNCSIG__, hWnd, wParam, lParam);

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

LRESULT UXReader::UXReaderDocumentView::WindowTimer(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p 0x%p\n", __FUNCSIG__, hWnd, wParam, lParam);

	KillTimer(hWnd, wParam);

	switch (wParam) // Timer
	{
		case searchTimerTick: // Start search
		{
			if (auto item = m_ToolbarPane->SearchEditItem())
			{
				auto text = item->EditText(); StartSearch(text);
			}
			break;
		}
	}

	return 0;
}

LRESULT UXReader::UXReaderDocumentView::SearchFound(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p 0x%p\n", __FUNCSIG__, hWnd, wParam, lParam);

	return 0;
}

//
//	Support methods
//

void UXReader::UXReaderDocumentView::UpdateUserInterface(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (m_ToolbarPane != nullptr)
	{
		if (auto item = m_ToolbarPane->ZoomDecrementItem()) item->Enable(CanZoomDecrement());
		if (auto item = m_ToolbarPane->ZoomIncrementItem()) item->Enable(CanZoomIncrement());

		if (auto item = m_ToolbarPane->NumberEditItem()) item->Enable(true);
		if (auto item = m_ToolbarPane->SearchEditItem()) item->Enable(true);
	}
}

void UXReader::UXReaderDocumentView::VisiblePagesChanged(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (m_DocumentPane != nullptr)
	{
		UpdateUserInterface(); // Toolbar

		if (fn_UpdateWindowTitle != nullptr)
		{
			const auto& visiblePages = m_DocumentPane->VisiblePages();

			if (visiblePages.size() > 0)
			{
				std::wstring visible;

				auto it1 = visiblePages.begin();

				if (visiblePages.size() > 1) // Multiple
				{
					auto it2 = visiblePages.end(); --it2;

					std::wstring a = m_Document->PageLabel(*it1);
					std::wstring b = m_Document->PageLabel(*it2);

					visible = a + L", " + b;
				}
				else // Single page
				{
					visible = m_Document->PageLabel(*it1);
				}

				const int of = (m_Document->PageCount() - 1);
				std::wstring total = m_Document->PageLabel(of);

				const std::wstring& name = m_Document->Title();

				std::wstring text = name + L" (" + visible + L" of " + total + L")";

				fn_UpdateWindowTitle(text.data());
			}
		}
	}
}

void UXReader::UXReaderDocumentView::CurrentPageChanged(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if ((m_ToolbarPane != nullptr) && (m_DocumentPane != nullptr))
	{
		std::wstring page = m_Document->PageLabel(m_DocumentPane->CurrentPage());

		if (auto item = m_ToolbarPane->PageDecrementItem()) item->Enable(CanPageNumberDecrement());
		if (auto item = m_ToolbarPane->PageIncrementItem()) item->Enable(CanPageNumberIncrement());

		if (auto item = m_ToolbarPane->NumberEditItem()) item->EditText(page);
	}
}

void UXReader::UXReaderDocumentView::ToolbarItemClicked(const int id)
{
	//DBLog(L"%S 0x%08X\n", __FUNCSIG__, id);

	switch (id)
	{
		case UX_ZOOM_INCREMENT: { ZoomIncrement(); break; }
		case UX_ZOOM_DECREMENT: { ZoomDecrement(); break; }

		case UX_PAGE_INCREMENT: { PageNumberIncrement(); break; }
		case UX_PAGE_DECREMENT: { PageNumberDecrement(); break; }
	}
}

void UXReader::UXReaderDocumentView::StartSearch(const std::wstring& term)
{
	//DBLog(L"%S '%s'\n", __FUNCSIG__, term.data());

	if ((m_DocumentPane != nullptr) && (term != m_SearchTerm))
	{
		m_SearchTerm = term; m_DocumentPane->StartSearch(m_SearchTerm, 0);
	}
}

void UXReader::UXReaderDocumentView::SearchProgress(const int index, const int found)
{
	//DBLog(L"%S %i %i\n", __FUNCSIG__, index, found);

	if (auto item = m_ToolbarPane->SearchTextItem())
	{
		item->UpdateText(std::to_wstring(found), 0x00008200);
	}
}

void UXReader::UXReaderDocumentView::SearchFinished(bool cancel, const int found)
{
	//DBLog(L"%S %i %i\n", __FUNCSIG__, cancel, found);

	if (auto item = m_ToolbarPane->SearchTextItem())
	{
		const DWORD color = (cancel ? 0x00000000 : (found ? 0x00000000 : 0x000000E0));

		std::wstring text(cancel ? L"" : std::to_wstring(found)); item->UpdateText(text, color);
	}

	if ((cancel == false) && found) PostMessageW(m_WindowHandle, UX_SEARCH_FOUND, 0, found);
}

void UXReader::UXReaderDocumentView::SearchEnterSelect(const int id)
{
	//DBLog(L"%S 0x%08X\n", __FUNCSIG__, id);

	if (auto item = m_ToolbarPane->SearchEditItem())
	{
		auto text = item->EditText(); StartSearch(text);
	}
}

void UXReader::UXReaderDocumentView::SearchTextChanged(const int id)
{
	//DBLog(L"%S 0x%08X\n", __FUNCSIG__, id);

	if (auto item = m_ToolbarPane->SearchEditItem())
	{
		auto text = item->EditText(); if (text != m_SearchText)
		{
			m_SearchText = text; SetTimer(m_WindowHandle, searchTimerTick, searchTimerTock, nullptr);
		}
	}
}

void UXReader::UXReaderDocumentView::SearchChangeFocus(const int id)
{
	//DBLog(L"%S 0x%08X\n", __FUNCSIG__, id);

	if (id != 0)
		{ if (auto item = m_ToolbarPane->NumberEditItem()) item->GiveEditFocus(); }
	else
		SetFocus(m_ParentWindow);
}

void UXReader::UXReaderDocumentView::NumberEnterSelect(const int id)
{
	//DBLog(L"%S 0x%08X\n", __FUNCSIG__, id);

	if (auto item = m_ToolbarPane->NumberEditItem())
	{
		auto text = item->EditText(); //DBLog(L"%S '%s'\n", __FUNCSIG__, text.data());
	}
}

void UXReader::UXReaderDocumentView::NumberTextChanged(const int id)
{
	//DBLog(L"%S 0x%08X\n", __FUNCSIG__, id);

	if (auto item = m_ToolbarPane->NumberEditItem())
	{
		auto text = item->EditText(); //DBLog(L"%S '%s'\n", __FUNCSIG__, text.data());
	}
}

void UXReader::UXReaderDocumentView::NumberChangeFocus(const int id)
{
	//DBLog(L"%S 0x%08X\n", __FUNCSIG__, id);

	if (id != 0)
		{ if (auto item = m_ToolbarPane->SearchEditItem()) item->GiveEditFocus(); }
	else
		SetFocus(m_ParentWindow);
}

//
//	API methods
//

void UXReader::UXReaderDocumentView::UpdateWindowTitle(std::function<void(const wchar_t*)> updateWindowTitle)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, updateWindowTitle);

	fn_UpdateWindowTitle = updateWindowTitle;
}

void UXReader::UXReaderDocumentView::MouseWheelV(const WPARAM wParam, const LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p\n", __FUNCSIG__, wParam, lParam);

	if (m_DocumentPane != nullptr) m_DocumentPane->MouseWheelV(wParam, lParam);
}

void UXReader::UXReaderDocumentView::MouseWheelH(const WPARAM wParam, const LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p\n", __FUNCSIG__, wParam, lParam);

	if (m_DocumentPane != nullptr) m_DocumentPane->MouseWheelH(wParam, lParam);
}

bool UXReader::UXReaderDocumentView::ZoomScale(const int percent)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane != nullptr) ? m_DocumentPane->ZoomScale(percent) : false;
}

int UXReader::UXReaderDocumentView::ZoomScale(void) const
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane != nullptr) ? m_DocumentPane->ZoomScale() : false;
}

//
//	UI method
//

void UXReader::UXReaderDocumentView::ShowInformation(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanShowInformation()) {}
}

bool UXReader::UXReaderDocumentView::CanShowInformation(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return false;
}

void UXReader::UXReaderDocumentView::PrintDocument(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanPrintDocument()) {}
}

bool UXReader::UXReaderDocumentView::CanPrintDocument(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return false;
}

void UXReader::UXReaderDocumentView::CopyDocumentText(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanCopyDocumentText()) {}
}

bool UXReader::UXReaderDocumentView::CanCopyDocumentText(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return false;
}

void UXReader::UXReaderDocumentView::SelectAllDocumentText(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanSelectAllDocumentText()) {}
}

bool UXReader::UXReaderDocumentView::CanSelectAllDocumentText(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return false;
}

void UXReader::UXReaderDocumentView::SearchTextFocus(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanSearchTextFocus()) m_ToolbarPane->SearchEditItem()->GiveEditFocus();
}

bool UXReader::UXReaderDocumentView::CanSearchTextFocus(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_ToolbarPane && m_ToolbarPane->SearchEditItem());
}

void UXReader::UXReaderDocumentView::SearchHitIncrement(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanSearchHitIncrement()) {}
}

bool UXReader::UXReaderDocumentView::CanSearchHitIncrement(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return false;
}

void UXReader::UXReaderDocumentView::SearchHitDecrement(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanSearchHitDecrement()) {}
}

bool UXReader::UXReaderDocumentView::CanSearchHitDecrement(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return false;
}

void UXReader::UXReaderDocumentView::FindTextSelection(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanFindTextSelection()) {}
}

bool UXReader::UXReaderDocumentView::CanFindTextSelection(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return false;
}

void UXReader::UXReaderDocumentView::GotoTextSelection(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanGotoTextSelection()) {}
}

bool UXReader::UXReaderDocumentView::CanGotoTextSelection(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return false;
}

void UXReader::UXReaderDocumentView::HideDocumentSidebar(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanHideDocumentSidebar()) {}
}

bool UXReader::UXReaderDocumentView::CanHideDocumentSidebar(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return false;
}

void UXReader::UXReaderDocumentView::ShowDocumentOutline(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanShowDocumentOutline()) {}
}

bool UXReader::UXReaderDocumentView::CanShowDocumentOutline(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return false;
}

void UXReader::UXReaderDocumentView::ShowDocumentThumbs(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanShowDocumentThumbs()) {}
}

bool UXReader::UXReaderDocumentView::CanShowDocumentThumbs(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return false;
}

void UXReader::UXReaderDocumentView::ZoomIncrement(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanZoomIncrement()) m_DocumentPane->ZoomIncrement(1.25);
}

bool UXReader::UXReaderDocumentView::CanZoomIncrement(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanZoomIncrement() : false);
}

void UXReader::UXReaderDocumentView::ZoomDecrement(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanZoomDecrement()) m_DocumentPane->ZoomDecrement(1.25);
}

bool UXReader::UXReaderDocumentView::CanZoomDecrement(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanZoomDecrement() : false);
}

void UXReader::UXReaderDocumentView::ZoomFitWidth(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanZoomFitWidth()) m_DocumentPane->ZoomFitWidth();
}

bool UXReader::UXReaderDocumentView::CanZoomFitWidth(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanZoomFitWidth() : false);
}

void UXReader::UXReaderDocumentView::ZoomOneToOne(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanZoomOneToOne()) m_DocumentPane->ZoomOneToOne();
}

bool UXReader::UXReaderDocumentView::CanZoomOneToOne(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanZoomOneToOne() : false);
}

void UXReader::UXReaderDocumentView::PageNumberFocus(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanPageNumberFocus()) m_ToolbarPane->NumberEditItem()->GiveEditFocus();
}

bool UXReader::UXReaderDocumentView::CanPageNumberFocus(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_ToolbarPane && m_ToolbarPane->NumberEditItem());
}

void UXReader::UXReaderDocumentView::PageNumberIncrement(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanPageNumberIncrement()) m_DocumentPane->PageNumberIncrement();
}

bool UXReader::UXReaderDocumentView::CanPageNumberIncrement(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanPageNumberIncrement() : false);
}

void UXReader::UXReaderDocumentView::PageNumberDecrement(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanPageNumberDecrement()) m_DocumentPane->PageNumberDecrement();
}

bool UXReader::UXReaderDocumentView::CanPageNumberDecrement(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanPageNumberDecrement() : false);
}

void UXReader::UXReaderDocumentView::PageNavigateIncrement(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanPageNavigateIncrement()) {}
}

bool UXReader::UXReaderDocumentView::CanPageNavigateIncrement(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return false;
}

void UXReader::UXReaderDocumentView::PageNavigateDecrement(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanPageNavigateDecrement()) {}
}

bool UXReader::UXReaderDocumentView::CanPageNavigateDecrement(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return false;
}

void UXReader::UXReaderDocumentView::LineScrollIncrementY(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanLineScrollIncrementY()) m_DocumentPane->LineScrollIncrementY();
}

bool UXReader::UXReaderDocumentView::CanLineScrollIncrementY(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanViewPortScrollIncrementY() : false);
}

void UXReader::UXReaderDocumentView::LineScrollDecrementY(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanLineScrollDecrementY()) m_DocumentPane->LineScrollDecrementY();
}

bool UXReader::UXReaderDocumentView::CanLineScrollDecrementY(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanViewPortScrollDecrementY() : false);
}

void UXReader::UXReaderDocumentView::LineScrollIncrementX(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanLineScrollIncrementX()) m_DocumentPane->LineScrollIncrementX();
}

bool UXReader::UXReaderDocumentView::CanLineScrollIncrementX(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanViewPortScrollIncrementX() : false);
}

void UXReader::UXReaderDocumentView::LineScrollDecrementX(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanLineScrollDecrementX()) m_DocumentPane->LineScrollDecrementX();
}

bool UXReader::UXReaderDocumentView::CanLineScrollDecrementX(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanViewPortScrollDecrementX() : false);
}

void UXReader::UXReaderDocumentView::PageScrollIncrementY(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanPageScrollIncrementY()) m_DocumentPane->PageScrollIncrementY();
}

bool UXReader::UXReaderDocumentView::CanPageScrollIncrementY(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanViewPortScrollIncrementY() : false);
}

void UXReader::UXReaderDocumentView::PageScrollDecrementY(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanPageScrollDecrementY()) m_DocumentPane->PageScrollDecrementY();
}

bool UXReader::UXReaderDocumentView::CanPageScrollDecrementY(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanViewPortScrollDecrementY() : false);
}

void UXReader::UXReaderDocumentView::PageScrollIncrementX(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanPageScrollIncrementX()) m_DocumentPane->PageScrollIncrementX();
}

bool UXReader::UXReaderDocumentView::CanPageScrollIncrementX(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanViewPortScrollIncrementX() : false);
}

void UXReader::UXReaderDocumentView::PageScrollDecrementX(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanPageScrollDecrementX()) m_DocumentPane->PageScrollDecrementX();
}

bool UXReader::UXReaderDocumentView::CanPageScrollDecrementX(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanViewPortScrollDecrementX() : false);
}

void UXReader::UXReaderDocumentView::GotoMinimumDocumentY(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanGotoMinimumDocumentY()) m_DocumentPane->GotoMinimumDocumentY();
}

bool UXReader::UXReaderDocumentView::CanGotoMinimumDocumentY(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanViewPortScrollDecrementY() : false);
}

void UXReader::UXReaderDocumentView::GotoMaximumDocumentY(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanGotoMaximumDocumentY()) m_DocumentPane->GotoMaximumDocumentY();
}

bool UXReader::UXReaderDocumentView::CanGotoMaximumDocumentY(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanViewPortScrollIncrementY() : false);
}

void UXReader::UXReaderDocumentView::GotoMinimumDocumentX(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanGotoMinimumDocumentX()) m_DocumentPane->GotoMinimumDocumentX();
}

bool UXReader::UXReaderDocumentView::CanGotoMinimumDocumentX(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanViewPortScrollDecrementX() : false);
}

void UXReader::UXReaderDocumentView::GotoMaximumDocumentX(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (CanGotoMaximumDocumentX()) m_DocumentPane->GotoMaximumDocumentX();
}

bool UXReader::UXReaderDocumentView::CanGotoMaximumDocumentX(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_DocumentPane ? m_DocumentPane->CanViewPortScrollIncrementX() : false);
}
