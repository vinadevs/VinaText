//
//	UXReaderDocumentPage.hpp
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderDocument;
	class UXReaderSelection;
	class UXReaderAction;

	class UXReaderDocumentPage final
	{
		private: // Variables
			FPDF_PAGE m_pdfPage = nullptr;
			FPDF_TEXTPAGE m_TextPage = nullptr;
			FPDF_DOCUMENT m_pdfDocument = nullptr;

			UXReaderDocument* m_Document = nullptr;

			int m_PageIndex = 0; int m_Rotation = 0; UXPageSize m_PageSize;

			std::unique_ptr<std::vector<UXReaderAction>> m_PageLinks;
			std::unique_ptr<std::vector<UXReaderAction>> m_TextLinks;

			std::vector<UXReaderSelection> m_SearchSelections;

		public: // Methods
			UXReaderDocumentPage(const int index, UXReaderDocument* document);
			~UXReaderDocumentPage(void);

			UXReaderDocumentPage(void) = delete;
			UXReaderDocumentPage(const UXReaderDocumentPage&) = delete;
			UXReaderDocumentPage& operator=(const UXReaderDocumentPage&) = delete;
			UXReaderDocumentPage& operator=(UXReaderDocumentPage&&) = delete;
			UXReaderDocumentPage(UXReaderDocumentPage&&) = delete;

			bool IsOpen(void) const;

			const HBITMAP PageThumb(const HDC hDC, const int size) const;
			const HBITMAP PageBitmap(const HDC hDC, const double scale) const;
			void DrawPageArea(const FPDF_BITMAP pdfBitmap, const UXRect& pageArea, const double scale) const;
			void DrawOverPage(const HDC hDC, const UXRect& pageArea, const double scale) const;

			const UXReaderAction* ActionForPoint(const UXPoint& point);
			std::wstring ActionTooltip(const UXReaderAction* action);
			bool ExtractLinks(void);

			int SearchPage(const std::wstring& term, const int options, int& counter);
			void ClearSearch(void);

		private: // Methods
			const FPDF_TEXTPAGE TextPage(void);
			void TextPageClose(void);

			bool ExtractPageLinks(void);
			bool ExtractTextLinks(void);
	};
}
