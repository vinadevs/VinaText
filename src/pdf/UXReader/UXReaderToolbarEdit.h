//
//	UXReaderToolbarEdit.h
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderToolbarEdit final
	{
		public: // Types
			using EditOptions_t = std::tuple<int, DWORD, int>;

		private: // Variables
			HWND m_WindowHandle = nullptr;
			HWND m_ParentWindow = nullptr;

			int m_ItemID = 0;
			HWND m_EditControl = nullptr;
			HWND m_TooltipPane = nullptr;

			EditOptions_t m_EditOptions {0, 0, 0};

			std::function<void(int)> fn_EnterSelect;
			std::function<void(int)> fn_TextChanged;
			std::function<void(int)> fn_ChangeFocus;

			std::map<UINT, std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>> m_MessageMap;

		public: // Methods
			UXReaderToolbarEdit(EditOptions_t options);
			~UXReaderToolbarEdit(void);

			UXReaderToolbarEdit(void) = delete;
			UXReaderToolbarEdit(const UXReaderToolbarEdit&) = delete;
			UXReaderToolbarEdit& operator=(const UXReaderToolbarEdit&) = delete;
			UXReaderToolbarEdit& operator=(UXReaderToolbarEdit&&) = delete;
			UXReaderToolbarEdit(UXReaderToolbarEdit&&) = delete;

			static ATOM DoRegisterWindowClass(const HMODULE hModule);
			static BOOL UnRegisterWindowClass(const HMODULE hModule);

			bool Create(const HWND hParent, const int x, const int y, const int w, const int h); void Destroy(void);
			void UpdateXYWH(const int x, const int y, const int w, const int h); void UpdateWH(const int w, const int h);

			void EnterSelect(std::function<void(int)> enterSelect);
			void TextChanged(std::function<void(int)> textChanged);
			void ChangeFocus(std::function<void(int)> changeFocus);

			void ClearEditText(void) const;
			int EditTextLength(void) const;
			std::wstring EditText(void) const;
			void EditText(const std::wstring& text) const;

			void GiveEditFocus(void) const;
			bool CanGiveEditFocus(void) const;

			void Enable(const bool enable);

		private: // Methods
			LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			static LRESULT CALLBACK WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			static LRESULT CALLBACK EditSubclass(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			void RegisterMessages(void);
			void CreateEditControl(const HWND hWnd);
			SIZE TextSize(const std::wstring& text) const;
			void AddItemTooltip(const HWND hWnd);
	};
}
