//
//	UXReaderToolbarPane.h
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderToolbarItem;
	class UXReaderToolbarText;
	class UXReaderToolbarEdit;

	class UXReaderToolbarPane final
	{
		private: // Variables
			HWND m_WindowHandle = nullptr;
			HWND m_ParentWindow = nullptr;
			int m_SeparatorSize = 0;
			int m_PaneHeight = 0;

			std::unique_ptr<UXReaderToolbarEdit> m_NumberEditItem;

			std::unique_ptr<UXReaderToolbarEdit> m_SearchEditItem;
			std::unique_ptr<UXReaderToolbarText> m_SearchTextItem;

			std::unique_ptr<UXReaderToolbarItem> m_PageDecrementItem;
			std::unique_ptr<UXReaderToolbarItem> m_PageIncrementItem;

			std::unique_ptr<UXReaderToolbarItem> m_ZoomDecrementItem;
			std::unique_ptr<UXReaderToolbarItem> m_ZoomIncrementItem;

			std::map<UINT, std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>> m_MessageMap;

		public: // Methods
			UXReaderToolbarPane(void);
			~UXReaderToolbarPane(void);

			UXReaderToolbarPane(const UXReaderToolbarPane&) = delete;
			UXReaderToolbarPane& operator=(const UXReaderToolbarPane&) = delete;
			UXReaderToolbarPane& operator=(UXReaderToolbarPane&&) = delete;
			UXReaderToolbarPane(UXReaderToolbarPane&&) = delete;

			static ATOM DoRegisterWindowClass(const HMODULE hModule);
			static BOOL UnRegisterWindowClass(const HMODULE hModule);

			int PaneHeight(const HWND hWnd = nullptr);
			bool Create(const HWND hParent, const int x, const int y, const int w, const int h); void Destroy(void);
			void UpdateXYWH(const int x, const int y, const int w, const int h); void UpdateWH(const int w, const int h);

			UXReaderToolbarItem* PageDecrementItem(void) const;
			UXReaderToolbarItem* PageIncrementItem(void) const;

			UXReaderToolbarItem* ZoomDecrementItem(void) const;
			UXReaderToolbarItem* ZoomIncrementItem(void) const;

			UXReaderToolbarEdit* SearchEditItem(void) const;
			UXReaderToolbarText* SearchTextItem(void) const;

			UXReaderToolbarEdit* NumberEditItem(void) const;

		private: // Methods
			LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			static LRESULT CALLBACK WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT MenuContext(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			void AddToolbarItems(const HWND hWnd);
			void RegisterMessages(void);
	};
}
