//
//	UXReaderMainWindow.h
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderDocumentView;

	class UXReaderMainWindow final
	{
		private: // Variables
			HWND m_WindowHandle = nullptr;
			HACCEL m_Accelerators = nullptr;
			HMENU m_WindowMenu = nullptr;

			int m_MinimumWindowSize = 512;

			std::unique_ptr<UXReader::UXReaderDocumentView> m_DocumentView;

			std::map<UINT, std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>> m_MessageMap;

		public: // Methods
			UXReaderMainWindow(void);
			~UXReaderMainWindow(void);

			UXReaderMainWindow(const UXReaderMainWindow&) = delete;
			UXReaderMainWindow& operator=(const UXReaderMainWindow&) = delete;
			UXReaderMainWindow& operator=(UXReaderMainWindow&&) = delete;
			UXReaderMainWindow(UXReaderMainWindow&&) = delete;

			static wchar_t *const WindowClassName(void);
			static ATOM DoRegisterWindowClass(const HMODULE hModule);
			static BOOL UnRegisterWindowClass(const HMODULE hModule);

			bool Create(const wchar_t *pCmdLine, const int nCmdShow);
			bool PreTranslateMessage(MSG *pMsg) const;

		private: // Methods
			LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			static LRESULT CALLBACK WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowMinMax(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowClose(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowDestroy(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT CopyData(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT MenuInit(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT MenuContext(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT MouseActivate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT MouseWheelV(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT MouseWheelH(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			void RegisterMessages(void);
			HMENU MainWindowMenu(void) const;
			HACCEL MainAccelerators(void) const;
			HMENU MainContextMenu(void) const;

			void ShowOpenFileDialog(const HWND hWnd);
			void OpenDocumentFile(const wchar_t *filePath);
			void UpdateWindowTitle(const wchar_t *text);

		private: // UI methods
			void OpenDocument(void);
			bool CanOpenDocument(void);
			void ClearRecentFileList(void);
			bool CanClearRecentFileList(void);
			void OpenRecentFile(const int index);
			bool CanOpenRecentFile(const int index);
			void CloseAllDocuments(void);
			bool CanCloseAllDocuments(void);
			void CloseDocument(void);
			bool CanCloseDocument(void);

			void ActiveTabIncrement(void);
			bool CanActiveTabIncrement(void);
			void ActiveTabDecrement(void);
			bool CanActiveTabDecrement(void);

			void ShowAbout(void);
			bool CanShowAbout(void);

			void ShowInformation(void);
			bool CanShowInformation(void);
			void PrintDocument(void);
			bool CanPrintDocument(void);

			void CopyDocumentText(void);
			bool CanCopyDocumentText(void);
			void SelectAllDocumentText(void);
			bool CanSelectAllDocumentText(void);

			void SearchTextFocus(void);
			bool CanSearchTextFocus(void);
			void SearchHitIncrement(void);
			bool CanSearchHitIncrement(void);
			void SearchHitDecrement(void);
			bool CanSearchHitDecrement(void);
			void FindTextSelection(void);
			bool CanFindTextSelection(void);
			void GotoTextSelection(void);
			bool CanGotoTextSelection(void);

			void HideDocumentSidebar(void);
			bool CanHideDocumentSidebar(void);
			void ShowDocumentOutline(void);
			bool CanShowDocumentOutline(void);
			void ShowDocumentThumbs(void);
			bool CanShowDocumentThumbs(void);

			void ZoomIncrement(void);
			bool CanZoomIncrement(void);
			void ZoomDecrement(void);
			bool CanZoomDecrement(void);
			void ZoomFitWidth(void);
			bool CanZoomFitWidth(void);
			void ZoomOneToOne(void);
			bool CanZoomOneToOne(void);

			void PageNumberFocus(void);
			bool CanPageNumberFocus(void);
			void PageNumberIncrement(void);
			bool CanPageNumberIncrement(void);
			void PageNumberDecrement(void);
			bool CanPageNumberDecrement(void);
			void PageNavigateIncrement(void);
			bool CanPageNavigateIncrement(void);
			void PageNavigateDecrement(void);
			bool CanPageNavigateDecrement(void);

			void LineScrollIncrementY(void);
			bool CanLineScrollIncrementY(void);
			void LineScrollDecrementY(void);
			bool CanLineScrollDecrementY(void);
			void LineScrollIncrementX(void);
			bool CanLineScrollIncrementX(void);
			void LineScrollDecrementX(void);
			bool CanLineScrollDecrementX(void);

			void PageScrollIncrementY(void);
			bool CanPageScrollIncrementY(void);
			void PageScrollDecrementY(void);
			bool CanPageScrollDecrementY(void);
			void PageScrollIncrementX(void);
			bool CanPageScrollIncrementX(void);
			void PageScrollDecrementX(void);
			bool CanPageScrollDecrementX(void);

			void GotoMinimumDocumentY(void);
			bool CanGotoMinimumDocumentY(void);
			void GotoMaximumDocumentY(void);
			bool CanGotoMaximumDocumentY(void);
			void GotoMinimumDocumentX(void);
			bool CanGotoMinimumDocumentX(void);
			void GotoMaximumDocumentX(void);
			bool CanGotoMaximumDocumentX(void);
	};
}
