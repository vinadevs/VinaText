//
//	UXReaderDocumentView.h
//	UXReader v0.1
//
//	Copyright � 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderDocument;
	class UXReaderToolbarPane;
	class UXReaderDocumentPane;
	class UXReaderStatusPane;

	class UXReaderDocumentView final
	{
		private: // Variables
			HWND m_WindowHandle = nullptr;
			HWND m_ParentWindow = nullptr;

			std::shared_ptr<UXReaderDocument> m_Document;

			std::unique_ptr<UXReaderToolbarPane> m_ToolbarPane;

			std::unique_ptr<UXReaderDocumentPane> m_DocumentPane;

			std::unique_ptr<UXReaderStatusPane> m_StatusPane;

			std::function<void(const wchar_t *)> fn_UpdateWindowTitle;

			std::wstring m_SearchTerm; std::wstring m_SearchText;

			std::map<UINT, std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>> m_MessageMap;

		public: // Methods
			UXReaderDocumentView(const std::shared_ptr<UXReaderDocument>& document);
			~UXReaderDocumentView(void);

			UXReaderDocumentView(const UXReaderDocumentView&) = delete;
			UXReaderDocumentView& operator=(const UXReaderDocumentView&) = delete;
			UXReaderDocumentView& operator=(UXReaderDocumentView&&) = delete;
			UXReaderDocumentView(UXReaderDocumentView&&) = delete;

			static ATOM DoRegisterWindowClass(const HMODULE hModule);
			static BOOL UnRegisterWindowClass(const HMODULE hModule);

			void ResetDocument(const std::shared_ptr<UXReaderDocument>& document) { m_Document = document; };
			bool Create(const HWND hParent, const int x, const int y, const int w, const int h); void Destroy(void);
			void UpdateXYWH(const int x, const int y, const int w, const int h); void UpdateWH(const int w, const int h);

			void UpdateWindowTitle(std::function<void(const wchar_t *)> updateWindowTitle);

			void MouseWheelV(const WPARAM wParam, const LPARAM lParam);
			void MouseWheelH(const WPARAM wParam, const LPARAM lParam);

			bool ZoomScale(const int percent);
			int ZoomScale(void) const;

		private: // Methods
			LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			static LRESULT CALLBACK WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowTimer(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT SearchFound(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			void RegisterMessages(void);
			void UpdateUserInterface(void);
			void VisiblePagesChanged(void);
			void CurrentPageChanged(void);
			void ToolbarItemClicked(const int id);

			void StartSearch(const std::wstring & term);
			void SearchFinished(bool cancel, const int found);
			void SearchProgress(const int index, const int found);
			void SearchEnterSelect(const int id);
			void SearchTextChanged(const int id);
			void SearchChangeFocus(const int id);

			void NumberEnterSelect(const int id);
			void NumberTextChanged(const int id);
			void NumberChangeFocus(const int id);

		public: // UI
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
