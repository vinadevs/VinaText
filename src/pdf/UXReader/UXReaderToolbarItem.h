//
//	UXReaderToolbarItem.h
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderToolbarItem final
	{
		private: // Variables
			HWND m_WindowHandle = nullptr;
			HWND m_ParentWindow = nullptr;

			int m_ItemID = 0;
			HBITMAP m_Icon = nullptr;
			HWND m_TooltipPane = nullptr;

			RECT m_HighlightArea {};
			int m_HighlightInset = 0;

			std::function<void(int)> fn_ItemClicked;

			bool m_TrackingMouse = false; bool m_MouseDown = false;

			std::map<UINT, std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>> m_MessageMap;

		public: // Methods
			UXReaderToolbarItem(const int id);
			~UXReaderToolbarItem(void);

			UXReaderToolbarItem(void) = delete;
			UXReaderToolbarItem(const UXReaderToolbarItem&) = delete;
			UXReaderToolbarItem& operator=(const UXReaderToolbarItem&) = delete;
			UXReaderToolbarItem& operator=(UXReaderToolbarItem&&) = delete;
			UXReaderToolbarItem(UXReaderToolbarItem&&) = delete;

			static ATOM DoRegisterWindowClass(const HMODULE hModule);
			static BOOL UnRegisterWindowClass(const HMODULE hModule);

			bool Create(const HWND hParent, const int x, const int y, const int w, const int h); void Destroy(void);
			void UpdateXYWH(const int x, const int y, const int w, const int h); void UpdateWH(const int w, const int h);

			void ItemClicked(std::function<void(int)> itemClicked);

			void Enable(const bool enable);

		private: // Methods
			LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			static LRESULT CALLBACK WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT MouseMove(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT MouseLeave(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT MouseDown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT MouseLift(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			void RegisterMessages(void);
			void RedrawItem(const HWND hWnd);
			void AddItemTooltip(const HWND hWnd);
			void TrackMouse(const HWND hWnd);
	};
}
