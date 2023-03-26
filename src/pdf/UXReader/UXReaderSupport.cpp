//
//	UXReaderSupport.cpp
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderSupport.h"
#include "UXReaderLibrary.h"

using namespace UXReader;

//
//	UXReaderSupport methods
//

UXReader::UXReaderSupport::UXReaderSupport(void)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, this);

	m_WaitCursor = LoadCursor(nullptr, IDC_WAIT);
	m_ArrowCursor = LoadCursor(nullptr, IDC_ARROW);
	m_PointCursor = LoadCursor(nullptr, IDC_HAND);
	m_BusyCursor = LoadCursor(nullptr, IDC_APPSTARTING);

	m_PaneSeparatorLineBrush = CreateSolidBrush(0x00B0B0B0);
	m_TestPaneBackgroundBrush = CreateSolidBrush(0x00E8E8E8);
	m_StatusPaneBackgroundBrush = CreateSolidBrush(0x00F8F8F8);
	m_ToolbarPaneBackgroundBrush = CreateSolidBrush(0x00F8F8F8);
	m_ToolbarItemHighlightBrush = CreateSolidBrush(0x00E2E2E2);
	m_ToolbarItemSelectedBrush = CreateSolidBrush(0x00DADADA);
	m_DocumentBackgroundBrush = CreateSolidBrush(0x00484848);
	m_EditControlFillBrush = CreateSolidBrush(0x00FFFFFF);
	m_EditControlLineBrush = CreateSolidBrush(0x00D0D0D0);
}

UXReader::UXReaderSupport::~UXReaderSupport(void)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, this);

	if (m_PaneSeparatorLineBrush != nullptr)
	{
		DeleteObject(m_PaneSeparatorLineBrush);
	}

	if (m_TestPaneBackgroundBrush != nullptr)
	{
		DeleteObject(m_TestPaneBackgroundBrush);
	}

	if (m_StatusPaneBackgroundBrush != nullptr)
	{
		DeleteObject(m_StatusPaneBackgroundBrush);
	}

	if (m_ToolbarPaneBackgroundBrush != nullptr)
	{
		DeleteObject(m_ToolbarPaneBackgroundBrush);
	}

	if (m_ToolbarItemHighlightBrush != nullptr)
	{
		DeleteObject(m_ToolbarItemHighlightBrush);
	}

	if (m_ToolbarItemSelectedBrush != nullptr)
	{
		DeleteObject(m_ToolbarItemSelectedBrush);
	}

	if (m_DocumentBackgroundBrush != nullptr)
	{
		DeleteObject(m_DocumentBackgroundBrush);
	}

	if (m_EditControlFillBrush != nullptr)
	{
		DeleteObject(m_EditControlFillBrush);
	}

	if (m_EditControlLineBrush != nullptr)
	{
		DeleteObject(m_EditControlLineBrush);
	}

	if (m_WaitCursor != nullptr) DeleteObject(m_WaitCursor);
	if (m_ArrowCursor != nullptr) DeleteObject(m_ArrowCursor);
	if (m_PointCursor != nullptr) DeleteObject(m_PointCursor);
	if (m_BusyCursor != nullptr) DeleteObject(m_BusyCursor);

	if (m_SystemFont != nullptr) DeleteObject(m_SystemFont);

	//DBLog(L"%S 0x%p\n", __FUNCSIG__, this);
}

HMODULE UXReader::UXReaderSupport::Module(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	return UXReaderLibrary::Module();
}

//
//	User interface methods
//

int UXReader::UXReaderSupport::UIS(const int dpi)
{
	//DBLog(L"%S %i\n", __FUNCSIG__, dpi);

	return MulDiv(100, dpi, 96);
}

int UXReader::UXReaderSupport::DPI(const HWND hWnd)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, hWnd);

	int dpi = 96; // Default DPI

	if (const HDC hDC = GetDC(hWnd))
	{
		dpi = GetDeviceCaps(hDC, LOGPIXELSX);

		ReleaseDC(hWnd, hDC);
	}

	return dpi;
}

//
//	String methods
//

std::wstring UXReader::UXReaderSupport::UTF16(const std::string &utf8)
{
	//DBLog(L"%S '%S'\n", __FUNCSIG__, utf8.data());

	std::wstring utf16;

	if (utf8.empty() == false) // Convert UTF8 string to UTF16 string
	{
		if (const int size = MultiByteToWideChar(CP_UTF8, 0, utf8.data(), int(utf8.size()), LPWSTR(utf16.data()), int(utf16.size())))
		{
			utf16.resize(size, 0); MultiByteToWideChar(CP_UTF8, 0, utf8.data(), int(utf8.size()), LPWSTR(utf16.data()), int(utf16.size()));
		}
	}

	//DBLog(L"%S '%s'\n", __FUNCSIG__, utf16.data());

	return utf16;
}

std::string UXReader::UXReaderSupport::UTF8(const std::wstring& utf16)
{
	//DBLog(L"%S '%s'\n", __FUNCSIG__, utf16.data());

	std::string utf8;

	if (utf16.empty() == false) // Convert UTF16 string to UTF8 string
	{
		if (const int size = WideCharToMultiByte(CP_UTF8, 0, utf16.data(), int(utf16.size()), LPSTR(utf8.data()), int(utf8.size()), nullptr, nullptr))
		{
			utf8.resize(size, 0); WideCharToMultiByte(CP_UTF8, 0, utf16.data(), int(utf16.size()), LPSTR(utf8.data()), int(utf8.size()), nullptr, nullptr);
		}
	}

	//DBLog(L"%S '%S'\n", __FUNCSIG__, utf8.data());

	return utf8;
}

//
//	Color methods
//

HBRUSH UXReader::UXReaderSupport::PaneSeparatorLineBrush(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXReaderSupport& Instance = UXReaderSupport::Instance();

	return Instance.m_PaneSeparatorLineBrush;
}

HBRUSH UXReader::UXReaderSupport::TestPaneBackgroundBrush(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXReaderSupport& Instance = UXReaderSupport::Instance();

	return Instance.m_TestPaneBackgroundBrush;
}

HBRUSH UXReader::UXReaderSupport::StatusPaneBackgroundBrush(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXReaderSupport& Instance = UXReaderSupport::Instance();

	return Instance.m_StatusPaneBackgroundBrush;
}

HBRUSH UXReader::UXReaderSupport::ToolbarPaneBackgroundBrush(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXReaderSupport& Instance = UXReaderSupport::Instance();

	return Instance.m_ToolbarPaneBackgroundBrush;
}

HBRUSH UXReader::UXReaderSupport::ToolbarItemHighlightBrush(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXReaderSupport& Instance = UXReaderSupport::Instance();

	return Instance.m_ToolbarItemHighlightBrush;
}

HBRUSH UXReader::UXReaderSupport::ToolbarItemSelectedBrush(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXReaderSupport& Instance = UXReaderSupport::Instance();

	return Instance.m_ToolbarItemSelectedBrush;
}

HBRUSH UXReader::UXReaderSupport::DocumentBackgroundBrush(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXReaderSupport& Instance = UXReaderSupport::Instance();

	return Instance.m_DocumentBackgroundBrush;
}

HBRUSH UXReader::UXReaderSupport::EditControlFillBrush(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXReaderSupport& Instance = UXReaderSupport::Instance();

	return Instance.m_EditControlFillBrush;
}

HBRUSH UXReader::UXReaderSupport::EditControlLineBrush(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXReaderSupport& Instance = UXReaderSupport::Instance();

	return Instance.m_EditControlLineBrush;
}

//
//	Cursor methods
//

HCURSOR UXReader::UXReaderSupport::WaitCursor(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXReaderSupport& Instance = UXReaderSupport::Instance();

	return Instance.m_WaitCursor;
}

HCURSOR UXReader::UXReaderSupport::ArrowCursor(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXReaderSupport& Instance = UXReaderSupport::Instance();

	return Instance.m_ArrowCursor;
}

HCURSOR UXReader::UXReaderSupport::PointCursor(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXReaderSupport& Instance = UXReaderSupport::Instance();

	return Instance.m_PointCursor;
}

HCURSOR UXReader::UXReaderSupport::BusyCursor(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXReaderSupport& Instance = UXReaderSupport::Instance();

	return Instance.m_BusyCursor;
}

//
//	Font methods
//

HGDIOBJ UXReader::UXReaderSupport::GetSystemFont(const HWND hWnd)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, hWnd);

	const int fontSize = 9; const int PPI = 72;

	NONCLIENTMETRICSW ncm {}; ncm.cbSize = sizeof(NONCLIENTMETRICSW);

	if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0))
	{
		ncm.lfMessageFont.lfHeight = -MulDiv(fontSize, DPI(hWnd), PPI);

		m_SystemFont = CreateFontIndirectW(&ncm.lfMessageFont);
	}
	else // Use default font
	{
		m_SystemFont = GetStockObject(DEFAULT_GUI_FONT);
	}

	return m_SystemFont;
}

HGDIOBJ UXReader::UXReaderSupport::SystemFont(const HWND hWnd)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, hWnd);

	UXReaderSupport& Instance = UXReaderSupport::Instance();

	return Instance.GetSystemFont(hWnd);
}
