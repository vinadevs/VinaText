//
//	UXReaderToolbarEdit.cpp
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderToolbarEdit.h"

using namespace UXReader;

//
//	Constants
//

constexpr int editLineInflate = 1;
constexpr int editFillInflate = 2;

static wchar_t *const kWindowClassName = L"UXReaderToolbarEditClass";

//
//	UXReaderToolbarEdit methods
//

UXReader::UXReaderToolbarEdit::UXReaderToolbarEdit(EditOptions_t options)
{
	//DBLog(L"%S 0x%p %i\n", __FUNCSIG__, this, id);

	m_EditOptions = options; m_ItemID = std::get<0>(options); RegisterMessages();
}

UXReader::UXReaderToolbarEdit::~UXReaderToolbarEdit(void)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, this);

	m_EditControl = nullptr; m_TooltipPane = nullptr;

	m_WindowHandle = nullptr; m_ParentWindow = nullptr;

	//DBLog(L"%S 0x%p\n", __FUNCSIG__, this);
}

ATOM UXReader::UXReaderToolbarEdit::DoRegisterWindowClass(const HMODULE hModule)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, hModule);

	WNDCLASSEXW wcex; RtlSecureZeroMemory(&wcex, sizeof(wcex));

	wcex.hInstance = hModule;
	wcex.lpszClassName = kWindowClassName;
	wcex.style = 0; wcex.lpszMenuName = nullptr;
	wcex.lpfnWndProc = UXReaderToolbarEdit::WindowDispatch;
	wcex.hIcon = nullptr; wcex.hIconSm = nullptr; wcex.hbrBackground = nullptr;
	wcex.hCursor = UXReaderSupport::ArrowCursor();
	wcex.cbClsExtra = 0; wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEXW);

	return RegisterClassExW(&wcex);
}

BOOL UXReader::UXReaderToolbarEdit::UnRegisterWindowClass(const HMODULE hModule)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, hModule);

	return UnregisterClassW(kWindowClassName, hModule);
}

LRESULT CALLBACK UXReader::UXReaderToolbarEdit::WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	if (message == WM_NCCREATE) SetWindowLongPtrW(hWnd, GWLP_USERDATA, LONG_PTR((LPCREATESTRUCT(lParam))->lpCreateParams));

	UXReaderToolbarEdit *thisWindow = reinterpret_cast<UXReaderToolbarEdit *>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

	if (thisWindow != nullptr)
		return thisWindow->WindowProcedure(hWnd, message, wParam, lParam);
	else
		return DefWindowProcW(hWnd, message, wParam, lParam);
}

LRESULT UXReader::UXReaderToolbarEdit::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	auto entry = m_MessageMap.find(message);

	if (entry == m_MessageMap.end())
		return DefWindowProcW(hWnd, message, wParam, lParam);
	else
		return entry->second(hWnd, message, wParam, lParam);
}

bool UXReader::UXReaderToolbarEdit::Create(const HWND hParent, const int x, const int y, const int w, const int h)
{
	//DBLog(L"%S 0x%p %i %i %i %i\n", __FUNCSIG__, hParent, x, y, w, h);

	const DWORD ws = (WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_CLIPCHILDREN); const DWORD es = (WS_EX_NOPARENTNOTIFY); // Window style

	const HWND hWnd = CreateWindowExW(es, kWindowClassName, nullptr, ws, x, y, w, h, hParent, HMENU(this), UXReaderSupport::Module(), this);

	if (hWnd == nullptr) { const DWORD ec = GetLastError(); DBLog(L"%S Unable to create window (%lu).\n", __FUNCSIG__, ec); }

	return (hWnd != nullptr);
}

void UXReader::UXReaderToolbarEdit::Destroy(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	DestroyWindow(m_WindowHandle);
}

void UXReader::UXReaderToolbarEdit::UpdateXYWH(const int x, const int y, const int w, const int h)
{
	//DBLog(L"%S %i %i %i %i\n", __FUNCSIG__, x, y, w, h);

	SetWindowPos(m_WindowHandle, nullptr, x, y, w, h, (SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOZORDER));

	RedrawWindow(m_WindowHandle, nullptr, nullptr, (RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN)); // !!!
}

void UXReader::UXReaderToolbarEdit::UpdateWH(const int w, const int h)
{
	//DBLog(L"%S %i %i\n", __FUNCSIG__, w, h);

	SetWindowPos(m_WindowHandle, nullptr, 0, 0, w, h, (SWP_NOACTIVATE | SWP_NOREDRAW | SWP_NOMOVE | SWP_NOZORDER));

	RedrawWindow(m_WindowHandle, nullptr, nullptr, (RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN)); // !!!
}

//
//	Window message methods
//

void UXReader::UXReaderToolbarEdit::RegisterMessages(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	m_MessageMap.emplace(WM_CREATE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowCreate(h, m, w, l); });
	m_MessageMap.emplace(WM_SIZE, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowSize(h, m, w, l); });
	m_MessageMap.emplace(WM_ERASEBKGND, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowErase(h, m, w, l); });
	m_MessageMap.emplace(WM_PAINT, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowPaint(h, m, w, l); });
	m_MessageMap.emplace(WM_COMMAND, [this](HWND h, UINT m, WPARAM w, LPARAM l) { return this->WindowCommand(h, m, w, l); });
}

LRESULT UXReader::UXReaderToolbarEdit::WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p 0x%p\n", __FUNCSIG__, hWnd, wParam, lParam);

	//CREATESTRUCTW *cs = reinterpret_cast<CREATESTRUCTW *>(lParam);

	m_WindowHandle = hWnd; m_ParentWindow = GetParent(hWnd); CreateEditControl(hWnd);

	return 0;
}

LRESULT UXReader::UXReaderToolbarEdit::WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p 0x%p\n", __FUNCSIG__, hWnd, wParam, lParam);

	//const int cw = LOWORD(lParam); const int ch = HIWORD(lParam);

	return 0;
}

LRESULT UXReader::UXReaderToolbarEdit::WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p 0x%p\n", __FUNCSIG__, hWnd, wParam, lParam);

	return 0;
}

LRESULT UXReader::UXReaderToolbarEdit::WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p 0x%p\n", __FUNCSIG__, hWnd, wParam, lParam);

	PAINTSTRUCT ps {}; HDC hDC = BeginPaint(hWnd, &ps);

	if (IsRectEmpty(&ps.rcPaint) == FALSE) // Paint the requested area
	{
		FillRect(hDC, &ps.rcPaint, UXReaderSupport::ToolbarPaneBackgroundBrush());
		//HGDIOBJ font = UXReaderSupport::SystemFont(hWnd); HGDIOBJ oldFont = SelectObject(hDC, font);
		//SetTextColor(hDC, 0x00000000); SetBkMode(hDC, TRANSPARENT); RECT area; GetClientRect(hWnd, &area);
		//DrawTextW(hDC, kWindowClassName, -1, &area, (DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP | DT_NOPREFIX));
		//SelectObject(hDC, oldFont);

		if (m_EditControl != nullptr) // Fill and frame edit control
		{
			RECT rect; GetWindowRect(m_EditControl, &rect); MapWindowPoints(nullptr, hWnd, LPPOINT(&rect), 2);
			InflateRect(&rect, editFillInflate, editFillInflate); FillRect(hDC, &rect, UXReaderSupport::EditControlFillBrush());
			InflateRect(&rect, editLineInflate, editLineInflate); FrameRect(hDC, &rect, UXReaderSupport::EditControlLineBrush());
		}
	}

	EndPaint(hWnd, &ps);

	return 0;
}

LRESULT UXReader::UXReaderToolbarEdit::WindowCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//DBLog(L"%S 0x%p 0x%p 0x%p\n", __FUNCSIG__, hWnd, wParam, lParam);

	const WORD control = LOWORD(wParam);

	if (control == m_ItemID)
	{
		const WORD code = HIWORD(wParam);

		if (code == (EN_CHANGE+0)) // Text
		{
			if (fn_TextChanged) fn_TextChanged(m_ItemID);
		}

		if (code == (EN_CHANGE+1)) // Enter
		{
			if (fn_EnterSelect) fn_EnterSelect(m_ItemID);
		}

		if (code == (EN_CHANGE+2)) // Escape
		{
			if (fn_ChangeFocus) fn_ChangeFocus(0x000000);
		}

		if (code == (EN_CHANGE+3)) // Tab
		{
			if (fn_ChangeFocus) fn_ChangeFocus(m_ItemID);
		}
	}

	return 0;
}

//
//	Edit control methods
//

void UXReader::UXReaderToolbarEdit::CreateEditControl(const HWND hWnd)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, hWnd);

	RECT rect; GetClientRect(hWnd, &rect); //const int cx = 0; const int cy = 0;
	const int cw = (rect.right - rect.left); const int ch = (rect.bottom - rect.top);

	int eh = 0; const HGDIOBJ editFont = UXReaderSupport::SystemFont(hWnd);

	if (const HDC hDC = GetDC(hWnd)) // Get text metrics
	{
		SetMapMode(hDC, MM_TEXT); // Pixel mapping mode
		const HGDIOBJ oldFont = SelectObject(hDC, editFont);
		TEXTMETRICW tm; RtlSecureZeroMemory(&tm, sizeof(tm));
		GetTextMetricsW(hDC, &tm); eh = tm.tmHeight;
		SelectObject(hDC, oldFont); ReleaseDC(hWnd, hDC);
	}

	const int ey = ((ch - eh) / 2); const int ex = (editFillInflate + editLineInflate); const int ew = (cw - ex - ex);
	const DWORD ws = (WS_CHILD | WS_VISIBLE | std::get<1>(m_EditOptions)); const DWORD es = (WS_EX_NOPARENTNOTIFY); // Window style
	m_EditControl = CreateWindowExW(es, WC_EDITW, nullptr, ws, ex, ey, ew, eh, hWnd, HMENU(INT_PTR(m_ItemID)), UXReaderSupport::Module(), nullptr);
	SendMessageW(m_EditControl, WM_SETFONT, WPARAM(editFont), 0); SendMessageW(m_EditControl, EM_LIMITTEXT, WPARAM(std::get<2>(m_EditOptions)), 0);
	WNDPROC oldEditProcedure = WNDPROC(SetWindowLongPtrW(m_EditControl, GWLP_WNDPROC, LONG_PTR(UXReaderToolbarEdit::EditSubclass)));
	SetWindowLongPtrW(m_EditControl, GWLP_USERDATA, LONG_PTR(oldEditProcedure)); AddItemTooltip(m_EditControl);
}

LRESULT CALLBACK UXReader::UXReaderToolbarEdit::EditSubclass(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WMLog(hWnd, message, wParam, lParam);

	if (const WNDPROC procedure = WNDPROC(GetWindowLongPtrW(hWnd, GWLP_USERDATA)))
	{
		switch (message) // Message
		{
			case WM_KEYDOWN: // Key down
			{
				switch (wParam) // Key code
				{
					case VK_RETURN: // Enter key
					{
						if (!(lParam & (1 << 30))) // Not repeating
						{
							const WORD idc = WORD(GetWindowLongPtrW(hWnd, GWL_ID)); const WORD cmd = (EN_CHANGE+1);
							PostMessageW(GetParent(hWnd), WM_COMMAND, MAKEWPARAM(idc, cmd), LPARAM(hWnd));
							return 0;
						}
						break;
					}

					case VK_ESCAPE: // Esc key
					{
						if (!(lParam & (1 << 30))) // Not repeating
						{
							const WORD idc = WORD(GetWindowLongPtrW(hWnd, GWL_ID)); const WORD cmd = (EN_CHANGE+2);
							PostMessageW(GetParent(hWnd), WM_COMMAND, MAKEWPARAM(idc, cmd), LPARAM(hWnd));
							return 0;
						}
						break;
					}

					case VK_TAB: // Tab key
					{
						if (!(lParam & (1 << 30))) // Not repeating
						{
							const WORD idc = WORD(GetWindowLongPtrW(hWnd, GWL_ID)); const WORD cmd = (EN_CHANGE+3);
							PostMessageW(GetParent(hWnd), WM_COMMAND, MAKEWPARAM(idc, cmd), LPARAM(hWnd));
							return 0;
						}
						break;
					}
				}
				break;
			}

			case WM_CHAR: // Character
			{
				switch (wParam) // Key code
				{
					case VK_RETURN: case VK_TAB: case VK_ESCAPE:
					{
						return 0;
					}
				}
				break;
			}

			case WM_MOUSEACTIVATE: // Mouse activate
			{
				return MA_ACTIVATE;
			}
		}

		return CallWindowProcW(procedure, hWnd, message, wParam, lParam);
	}

	return DefWindowProcW(hWnd, message, wParam, lParam);
}

void UXReader::UXReaderToolbarEdit::AddItemTooltip(const HWND hWnd)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, hWnd);

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

SIZE UXReader::UXReaderToolbarEdit::TextSize(const std::wstring& text) const
{
	//DBLog(L"%S '%s'\n", __FUNCSIG__, text.data());

	SIZE size {0, 0}; const HWND hWnd = m_WindowHandle;

	const HGDIOBJ editFont = UXReaderSupport::SystemFont(hWnd);

	if (const HDC hDC = GetDC(hWnd)) // Get text metrics
	{
		SetMapMode(hDC, MM_TEXT); // Pixel mapping mode
		const HGDIOBJ oldFont = SelectObject(hDC, editFont);
		TEXTMETRICW tm; RtlSecureZeroMemory(&tm, sizeof(tm));
		GetTextMetricsW(hDC, &tm); const int aw = tm.tmAveCharWidth;
		GetTextExtentPoint32W(hDC, text.data(), int(text.length()), &size);
		SelectObject(hDC, oldFont); ReleaseDC(hWnd, hDC); size.cx += aw;
	}

	return size;
}

//
//	API methods
//

void UXReader::UXReaderToolbarEdit::EnterSelect(std::function<void(int)> enterSelect)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, enterSelect);

	fn_EnterSelect = enterSelect;
}

void UXReader::UXReaderToolbarEdit::TextChanged(std::function<void(int)> textChanged)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, textChanged);

	fn_TextChanged = textChanged;
}

void UXReader::UXReaderToolbarEdit::ChangeFocus(std::function<void(int)> changeFocus)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, textChanged);

	fn_ChangeFocus = changeFocus;
}

void UXReader::UXReaderToolbarEdit::ClearEditText(void) const
{
	//DBLog(L"%S\n", __FUNCSIG__);

	SetWindowTextW(m_EditControl, L""); SetFocus(m_EditControl);
}

int UXReader::UXReaderToolbarEdit::EditTextLength(void) const
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return GetWindowTextLengthW(m_EditControl);
}

std::wstring UXReader::UXReaderToolbarEdit::EditText(void) const
{
	//DBLog(L"%S\n", __FUNCSIG__);

	wchar_t temp[512]; RtlSecureZeroMemory(temp, sizeof(temp));

	GetWindowTextW(m_EditControl, temp, 510);

	std::wstring text(temp); return text;
}

void UXReader::UXReaderToolbarEdit::EditText(const std::wstring& text) const
{
	//DBLog(L"%S '%s'\n", __FUNCSIG__, text.data());

	const SIZE size = TextSize(text);

	RECT rect; GetClientRect(m_EditControl, &rect);
	const int mw = (rect.right - rect.left);

	const wchar_t *show = ((size.cx < mw) ? text.data() : L"-");

	SetWindowTextW(m_EditControl, show);
}

void UXReader::UXReaderToolbarEdit::GiveEditFocus(void) const
{
	//DBLog(L"%S\n", __FUNCSIG__);

	SendMessageW(m_EditControl, EM_SETSEL, 0, -1);

	SetFocus(m_EditControl);
}

bool UXReader::UXReaderToolbarEdit::CanGiveEditFocus(void) const
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return (m_EditControl != nullptr);
}

void UXReader::UXReaderToolbarEdit::Enable(const bool enable)
{
	//DBLog(L"%S %i\n", __FUNCSIG__, enable);

	const HWND hWnd = m_WindowHandle;

	if ((IsWindowEnabled(hWnd) ? true : false) != enable)
	{
		EnableWindow(hWnd, enable); //RedrawEdit(hWnd);
	}
}
