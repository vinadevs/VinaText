//
//	UXReaderToolbarText.h
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderToolbarText final
	{
		private: // Variables
			HWND m_WindowHandle = nullptr;
			HWND m_ParentWindow = nullptr;

			HBRUSH m_BackgroundBrush = nullptr;

			std::wstring m_Text; DWORD m_TextColor = 0x00000000; int m_ItemID = 0;

			std::map<UINT, std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>> m_MessageMap;

		public: // Methods
			UXReaderToolbarText(const int id);
			~UXReaderToolbarText(void);

			UXReaderToolbarText(void) = delete;
			UXReaderToolbarText(const UXReaderToolbarText&) = delete;
			UXReaderToolbarText& operator=(const UXReaderToolbarText&) = delete;
			UXReaderToolbarText& operator=(UXReaderToolbarText&&) = delete;
			UXReaderToolbarText(UXReaderToolbarText&&) = delete;

			static ATOM DoRegisterWindowClass(const HMODULE hModule);
			static BOOL UnRegisterWindowClass(const HMODULE hModule);

			bool Create(const HWND hParent, const int x, const int y, const int w, const int h); void Destroy(void);
			void UpdateXYWH(const int x, const int y, const int w, const int h); void UpdateWH(const int w, const int h);

			void RenderText(const std::wstring& text, const DWORD textColor = 0x00000000);
			void UpdateText(const std::wstring& text, const DWORD textColor = 0x00000000);

			void BackgroundBrush(const HBRUSH hBrush);

		private: // Methods
			LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			static LRESULT CALLBACK WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			void HandlePaint(const HWND hWnd, const HDC hDC);
			void RegisterMessages(void);
	};
}
