//
//	UXReaderSupport.hpp
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

#ifndef NEGATORY
#define NEGATORY (-1)
#endif// NEGATORY

namespace UXReader
{
	class UXReaderSupport final
	{
		public: // Methods
			static UXReaderSupport& Instance(void)
			{
				static UXReaderSupport singleton; return singleton;
			}

			std::mutex Mutex;

			static HMODULE Module(void);

			static int UIS(const int dpi = 96);
			static int DPI(const HWND hWnd = nullptr);

			static std::wstring UTF16(const std::string& utf8);
			static std::string UTF8(const std::wstring& utf16);

			static HBRUSH PaneSeparatorLineBrush(void);
			static HBRUSH TestPaneBackgroundBrush(void);
			static HBRUSH StatusPaneBackgroundBrush(void);
			static HBRUSH ToolbarPaneBackgroundBrush(void);
			static HBRUSH ToolbarItemHighlightBrush(void);
			static HBRUSH ToolbarItemSelectedBrush(void);
			static HBRUSH DocumentBackgroundBrush(void);
			static HBRUSH EditControlFillBrush(void);
			static HBRUSH EditControlLineBrush(void);

			static HGDIOBJ SystemFont(const HWND hWnd);

			static HCURSOR WaitCursor(void);
			static HCURSOR ArrowCursor(void);
			static HCURSOR PointCursor(void);
			static HCURSOR BusyCursor(void);

		private: // Methods
			UXReaderSupport(void);
			~UXReaderSupport(void);

			UXReaderSupport(const UXReaderSupport&) = delete;
			UXReaderSupport& operator=(const UXReaderSupport&) = delete;
			UXReaderSupport& operator=(UXReaderSupport&&) = delete;
			UXReaderSupport(UXReaderSupport&&) = delete;

			HGDIOBJ GetSystemFont(const HWND hWnd);

		private: // Variables
			HBRUSH m_PaneSeparatorLineBrush = nullptr;
			HBRUSH m_TestPaneBackgroundBrush = nullptr;
			HBRUSH m_StatusPaneBackgroundBrush = nullptr;
			HBRUSH m_ToolbarPaneBackgroundBrush = nullptr;
			HBRUSH m_ToolbarItemHighlightBrush = nullptr;
			HBRUSH m_ToolbarItemSelectedBrush = nullptr;
			HBRUSH m_DocumentBackgroundBrush = nullptr;
			HBRUSH m_EditControlFillBrush = nullptr;
			HBRUSH m_EditControlLineBrush = nullptr;

			HGDIOBJ m_SystemFont = nullptr;

			HCURSOR m_WaitCursor = nullptr;
			HCURSOR m_ArrowCursor = nullptr;
			HCURSOR m_PointCursor = nullptr;
			HCURSOR m_BusyCursor = nullptr;
	};
}
