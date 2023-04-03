//
//	UXReaderDocumentPane.h
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderDocument;
	class UXReaderPageCache;
	class UXReaderSelection;
	class UXReaderAction;

	class UXReaderDocumentPane final
	{
		private: // Variables
			HWND m_WindowHandle = nullptr;
			HWND m_ParentWindow = nullptr;
			HWND m_PaneTooltip = nullptr;

			int m_UIS = 100;

			std::shared_ptr<UXReaderDocument> m_Document;

			std::unique_ptr<UXReaderPageCache> m_PageCache;

			std::vector<UXRect> m_PageFrames;

			std::set<int> m_VisiblePages;

			int m_CurrentPage = 0;

			double m_CanvasH = 0.0;
			double m_CanvasW = 0.0;
			double m_ViewPortH = 0.0;
			double m_ViewPortW = 0.0;
			double m_ViewPortY = 0.0;
			double m_ViewPortX = 0.0;
			double m_ClientRectH = 0.0;
			double m_ClientRectW = 0.0;
			double m_ViewPortMinimumY = 0.0;
			double m_ViewPortMaximumY = 0.0;
			double m_ViewPortMinimumX = 0.0;
			double m_ViewPortMaximumX = 0.0;
			double m_ZoomMinimumScale = 0.5;
			double m_ZoomMaximumScale = 8.0;
			double m_ZoomScale = 1.0;

			std::wstring m_LinkDescription;
			const UXReaderAction* m_Action = nullptr;

			std::thread m_SearchThread;
			bool m_CancelSearch = false; bool m_Searching = false;
			std::wstring m_SearchTerm;

			std::function<void(void)> fn_ViewPortChanged;
			std::function<void(void)> fn_VisiblePagesChanged;
			std::function<void(void)> fn_CurrentPageChanged;

			std::function<void(bool, int)> fn_SearchFinished;
			std::function<void(int, int)> fn_SearchProgress;

			std::map<UINT, std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>> m_MessageMap;

		public: // Methods
			UXReaderDocumentPane(const std::shared_ptr<UXReaderDocument>& document);
			~UXReaderDocumentPane(void);

			UXReaderDocumentPane(void) = delete;
			UXReaderDocumentPane(const UXReaderDocumentPane&) = delete;
			UXReaderDocumentPane& operator=(const UXReaderDocumentPane&) = delete;
			UXReaderDocumentPane& operator=(UXReaderDocumentPane&&) = delete;
			UXReaderDocumentPane(UXReaderDocumentPane&&) = delete;

			static ATOM DoRegisterWindowClass(const HMODULE hModule);
			static BOOL UnRegisterWindowClass(const HMODULE hModule);

			bool Create(const HWND hParent, const int x, const int y, const int w, const int h); void Destroy(void);
			void UpdateXYWH(const int x, const int y, const int w, const int h); void UpdateWH(const int w, const int h);

			void ViewPortChanged(std::function<void(void)> viewPortChanged);
			void VisiblePagesChanged(std::function<void(void)> visiblePagesChanged);
			void CurrentPageChanged(std::function<void(void)> currentPageChanged);
			void SearchFinished(std::function<void(bool, int)> searchFinished);
			void SearchProgress(std::function<void(int, int)> searchProgress);

			const std::set<int>& VisiblePages(void) const;
			int CurrentPage(void) const;

			void StartSearch(const std::wstring& term, const int options);

		private: // Methods
			LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			static LRESULT CALLBACK WindowDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowErase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowScrollV(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowScrollH(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowNotify(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT WindowTimer(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT MenuContext(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT MouseCursor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT MouseMove(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT MouseDown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT MouseLift(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			void RegisterMessages(void);

			void UpdateClientRect(const HWND hWnd);
			void CreateScrollBars(const HWND hWnd) const;
			void UpdateScrollBars(const HWND hWnd) const;
			void ResizeScrollBars(const HWND hWnd) const;
			void UpdateScrollBarY(const HWND hWnd) const;
			void UpdateScrollBarX(const HWND hWnd) const;

			void RedrawPaneContent(void) const;
			void ViewPortDidChange(void) const;
			void UpdateViewPortX(double viewPortX);
			void UpdateViewPortY(double viewPortY);
			void UpdateViewPortXY(double viewPortX, double viewPortY);
			void CenterViewPort(const UXPoint& point);
			void GotoRectOnPage(const int index, const UXRect& rect);
			void GotoAction(const UXReaderAction * action);

			double LimitScrollFactor(double value) const;
			void ViewPortScrollDecrementY(double factor);
			void ViewPortScrollIncrementY(double factor);
			void ViewPortScrollDecrementX(double factor);
			void ViewPortScrollIncrementX(double factor);

			double LimitZoomScale(double value);
			void SetInitialZoomScale(const HWND hWnd);
			bool UpdateZoomScale(double scale);

			void WheelScrollDecrementY(void);
			void WheelScrollIncrementY(void);
			void WheelScrollDecrementX(void);
			void WheelScrollIncrementX(void);

			void LayoutPages(const HWND hWnd);
			bool UsePageBitmaps(void) const;
			void DirectPaint(const HWND hWnd);
			void HandlePaint(const HWND hWnd, const HDC hDC);
			void DrawPage(const HDC hDC, const int index, const UXRect& pageArea, const UXRect& clientArea);
			void HandlePageChanges(int currentPage, const std::set<int>& visiblePages);
			void PostPaintTimeout(const HWND hWnd);

			void AddPaneToolTip(const HWND hWnd);
			void SetMouseCursorShape(const HWND hWnd);
			UXPoint MouseToViewPort(const int x, const int y) const;
			UXPoint PageAreaPoint(const int index, const UXPoint& point) const;
			int PageUnderPoint(const UXPoint& point) const;
			bool IsMouseOverLink(const int x, const int y);
			bool MouseClicked(const int x, const int y);

			void CancelSearch(void);
			void ClearSearch(void);
			void SearchDocument(const int options);

		public: // API
			void MouseWheelV(const WPARAM wParam, const LPARAM lParam);
			void MouseWheelH(const WPARAM wParam, const LPARAM lParam);

			bool CanViewPortScrollDecrementY(void) const;
			bool CanViewPortScrollIncrementY(void) const;
			bool CanViewPortScrollDecrementX(void) const;
			bool CanViewPortScrollIncrementX(void) const;

			void LineScrollDecrementY(void);
			void LineScrollIncrementY(void);
			void LineScrollDecrementX(void);
			void LineScrollIncrementX(void);

			void PageScrollDecrementY(void);
			void PageScrollIncrementY(void);
			void PageScrollDecrementX(void);
			void PageScrollIncrementX(void);

			void GotoMaximumDocumentY(void);
			void GotoMinimumDocumentY(void);
			void GotoMaximumDocumentX(void);
			void GotoMinimumDocumentX(void);

			void GotoDocumentPage(const int index);
			bool CanGotoDocumentPage(const int index);
			void PageNumberDecrement(void);
			bool CanPageNumberDecrement(void);
			void PageNumberIncrement(void);
			bool CanPageNumberIncrement(void);

			void ZoomDecrement(const double amount);
			bool CanZoomDecrement(void);
			void ZoomIncrement(const double amount);
			bool CanZoomIncrement(void);
			void ZoomFitWidth(void);
			bool CanZoomFitWidth(void);
			void ZoomOneToOne(void);
			bool CanZoomOneToOne(void);

			bool ZoomScale(const int percent);
			int ZoomScale(void) const;
	};
}
