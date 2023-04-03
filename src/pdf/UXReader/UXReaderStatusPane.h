//
//	UXReaderStatusPane.h
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderStatusPane final
	{
		private: // Variables
			HWND m_WindowHandle = nullptr;
			HWND m_ParentWindow = nullptr;
			int m_SeparatorSize = 0;
			int m_PaneHeight = 0;

			std::map<UINT, std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>> m_MessageMap;

		public: // Methods
			UXReaderStatusPane(void);
			~UXReaderStatusPane(void);

			UXReaderStatusPane(const UXReaderStatusPane&) = delete;
			UXReaderStatusPane& operator=(const UXReaderStatusPane&) = delete;
			UXReaderStatusPane& operator=(UXReaderStatusPane&&) = delete;
			UXReaderStatusPane(UXReaderStatusPane&&) = delete;

			static ATOM DoRegisterWindowClass(const HMODULE hModule);
			static BOOL UnRegisterWindowClass(const HMODULE hModule);

			int PaneHeight(const HWND hWnd = nullptr);
			bool Create(const HWND hParent, const int x, const int y, const int w, const int h); void Destroy(void);
			void UpdateXYWH(const int x, const int y, const int w, const int h); void UpdateWH(const int w, const int h);

		private: // Methods
			LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			static LRESULT CALLBACK WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT MenuContext(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			void RegisterMessages(void);
	};
}
