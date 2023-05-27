//
//	UXReaderDocumentPage.cpp
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderDocument.h"
#include "UXReaderDocumentPage.h"
#include "UXReaderAction.h"
#include "UXReaderDestination.h"
#include "UXReaderSelection.h"

using namespace UXReader;

//
//	Constants
//

static bool pageLinkEnabled = true;
static bool pageLinkOutline = true;
static bool pageLinkLogging = false;

static bool textLinkEnabled = false;
static bool textLinkOutline = false;
static bool textLinkLogging = false;

//
//	UXReaderDocumentPage methods
//

UXReader::UXReaderDocumentPage::UXReaderDocumentPage(const int index, UXReaderDocument* document)
{

	m_PageIndex = NEGATORY; m_Rotation = NEGATORY;

	if ((document != nullptr) && (document->IsOpen() == true))
	{
		m_Document = document; m_pdfDocument = document->pdfDocument();

		if (m_pdfPage = FPDF_LoadPage(m_pdfDocument, index)) // Open page
		{
			m_PageSize = document->PageSize(index); m_PageIndex = index;

			m_Rotation = FPDFPage_GetRotation(m_pdfPage);
		}
	}
}

UXReader::UXReaderDocumentPage::~UXReaderDocumentPage(void)
{

	m_PageLinks = nullptr; m_TextLinks = nullptr;

	if (m_TextPage != nullptr) { FPDFText_ClosePage(m_TextPage); m_TextPage = nullptr; }

	if (m_pdfPage != nullptr) { FPDF_ClosePage(m_pdfPage); m_pdfPage = nullptr; }

	m_pdfDocument = nullptr; m_Document = nullptr;

}

const FPDF_TEXTPAGE UXReader::UXReaderDocumentPage::TextPage(void)
{

	if (m_TextPage == nullptr) // Load on demand
	{
		m_TextPage = FPDFText_LoadPage(m_pdfPage);
	}

	return m_TextPage;
}

void UXReader::UXReaderDocumentPage::TextPageClose(void)
{

	if (m_TextPage != nullptr) // Release page text
	{
		FPDFText_ClosePage(m_TextPage); m_TextPage = nullptr;
	}
}

bool UXReader::UXReaderDocumentPage::IsOpen(void) const
{

	return (m_pdfPage != nullptr);
}

//
//	Draw methods
//

const HBITMAP UXReader::UXReaderDocumentPage::PageThumb(const HDC hDC, const int size) const
{

	const double ws = (double(size) / m_PageSize.w);
	const double hs = (double(size) / m_PageSize.h);

	const double ts = ((ws < hs) ? ws : hs);

	return PageBitmap(hDC, ts);
}

const HBITMAP UXReader::UXReaderDocumentPage::PageBitmap(const HDC hDC, const double scale) const
{

	HBITMAP pageBitmap = nullptr; // Page bitmap

	UXReaderSupport& support = UXReaderSupport::Instance();
	{
		std::lock_guard<std::mutex> lockGuard(support.Mutex);

		const int bw = int(m_PageSize.w * scale); // Bitmap width
		const int bh = int(m_PageSize.h * scale); // Bitmap height

		BITMAPINFOHEADER bmih; RtlSecureZeroMemory(&bmih, sizeof(bmih));
		bmih.biSize = sizeof(bmih); bmih.biWidth = bw; bmih.biHeight = -bh;
		bmih.biPlanes = 1; bmih.biBitCount = 32; bmih.biCompression = BI_RGB;
		bmih.biSizeImage = (bw * bh * 4); void *bitmapBits = nullptr;
		const BITMAPINFO *bmi = (BITMAPINFO *)&bmih;

		if (pageBitmap = CreateDIBSection(hDC, bmi, DIB_RGB_COLORS, &bitmapBits, nullptr, 0))
		{
			if (FPDF_BITMAP pdfBitmap = FPDFBitmap_CreateEx(bw, bh, FPDFBitmap_BGRx, bitmapBits, (bw * 4)))
			{
				FPDFBitmap_FillRect(pdfBitmap, 0, 0, bw, bh, 0xFFFFFFFF); // Fill white

				const FS_MATRIX matrix = { float(scale), 0.0f, 0.0f, float(scale), 0.0f, 0.0f };
				
				const FS_RECTF clip = {0.0f, 0.0f, float(bw), float(bh)}; // To bitmap

				const int options = (FPDF_ANNOT | FPDF_LCD_TEXT | FPDF_NO_CATCH);

				FPDF_RenderPageBitmapWithMatrix(pdfBitmap, m_pdfPage, &matrix, &clip, options);

				FPDFBitmap_Destroy(pdfBitmap); pdfBitmap = nullptr;
			}
		}
	}

	return pageBitmap;
}

void UXReader::UXReaderDocumentPage::DrawPageArea(const FPDF_BITMAP pdfBitmap, const UXRect& pageArea, const double scale) const
{

	UXReaderSupport& support = UXReaderSupport::Instance();
	{
		std::lock_guard<std::mutex> lockGuard(support.Mutex);

		const int bw = FPDFBitmap_GetWidth(pdfBitmap);
		const int bh = FPDFBitmap_GetHeight(pdfBitmap);

		const UXMatrix t = {1.0, 0.0, 0.0, -1.0, 0.0, m_PageSize.h};

		const UXRect flip = pageArea.transform(t); const UXRect area = flip.scale(scale, scale);

		const float tx = -area.xf(); const float ty = (area.hf() + area.yf());

		const FS_MATRIX matrix = { float(scale), 0.0f, 0.0f, float(scale), 0.0f, 0.0f };

		const FS_RECTF clip = {0.0f, 0.0f, float(bw), float(bh)}; // to bitmap

		const int options = (FPDF_ANNOT | FPDF_LCD_TEXT | FPDF_NO_CATCH);

		FPDF_RenderPageBitmapWithMatrix(pdfBitmap, m_pdfPage, &matrix, &clip, options);
	}
}

void UXReader::UXReaderDocumentPage::DrawOverPage(const HDC hDC, const UXRect& pageArea, const double scale) const
{

	UXReaderSupport& support = UXReaderSupport::Instance();
	{
		std::lock_guard<std::mutex> lockGuard(support.Mutex);

		if (m_SearchSelections.empty() == false) // Draw search selections
		{
			Gdiplus::Graphics graphics(hDC); graphics.SetPageUnit(Gdiplus::UnitPixel);

			Gdiplus::Color rectColor(63, 255, 255, 0); Gdiplus::SolidBrush rectBrush(rectColor);

			for (const UXReaderSelection& selection : m_SearchSelections) // O(n)
			{
				for (const UXRect& rectangle : selection.Rectangles()) // O(n)
				{
					if (pageArea.intersects(rectangle) == true) // Visible
					{
						UXRect rect = rectangle.offset(-pageArea.xd(), -pageArea.yd()); rect = rect.scale(scale, scale);

						graphics.FillRectangle(&rectBrush, rect.xf(), rect.yf(), rect.wf(), rect.hf());
					}
				}
			}
		}
	}

	if (pageLinkOutline || textLinkOutline)
	{
		Gdiplus::Graphics graphics(hDC); graphics.SetPageUnit(Gdiplus::UnitPixel);

		Gdiplus::Color rectColor(31, 0, 255, 0); Gdiplus::SolidBrush rectBrush(rectColor);

		if (pageLinkOutline && (m_PageLinks != nullptr)) // Draw page links
		{
			for (auto it = m_PageLinks->begin(); it != m_PageLinks->end(); ++it) // O(n)
			{
				for (const UXRect& rectangle : it->Rectangles()) // O(n)
				{
					if (pageArea.intersects(rectangle) == true) // Visible
					{
						UXRect rect = rectangle.offset(-pageArea.xd(), -pageArea.yd()); rect = rect.scale(scale, scale);

						graphics.FillRectangle(&rectBrush, rect.xf(), rect.yf(), rect.wf(), rect.hf());
					}
				}
			}
		}

		if (textLinkOutline && (m_TextLinks != nullptr)) // Draw text links
		{
			for (auto it = m_TextLinks->begin(); it != m_TextLinks->end(); ++it) // O(n)
			{
				for (const UXRect& rectangle : it->Rectangles()) // O(n)
				{
					if (pageArea.intersects(rectangle) == true) // Visible
					{
						UXRect rect = rectangle.offset(-pageArea.xd(), -pageArea.yd()); rect = rect.scale(scale, scale);

						graphics.FillRectangle(&rectBrush, rect.xf(), rect.yf(), rect.wf(), rect.hf());
					}
				}
			}
		}
	}
}

//
//	Link methods
//

bool UXReader::UXReaderDocumentPage::ExtractPageLinks(void)
{

	int linkIndex = 0; FPDF_LINK link = nullptr;

	m_PageLinks = std::make_unique<std::vector<UXReaderAction>>();

	while (FPDFLink_Enumerate(m_pdfPage, &linkIndex, &link))
	{
		if (const FPDF_ACTION action = FPDFLink_GetAction(link))
		{
			switch (FPDFAction_GetType(action))
			{
				case PDFACTION_URI: // URI
				{
					UXRect viewRect; FS_RECTF linkRect; std::string URI;

					if (FPDFLink_GetAnnotRect(link, &linkRect)) // Convert link rect
					{
						const UXRect temp(linkRect.left, linkRect.bottom, linkRect.right, linkRect.top);

						viewRect = ConvertToViewFromPage(temp, m_PageSize, m_Rotation);
					}

					if (const int bytes = FPDFAction_GetURIPath(m_pdfDocument, action, nullptr, 0))
					{
						URI.resize(bytes); void *buffer = &URI[0]; // String as data buffer hack

						if (FPDFAction_GetURIPath(m_pdfDocument, action, buffer, int(URI.size())))
						{
							URI.resize(URI.size() - 1); // Trim NUL
						}
					}

					if ((viewRect.empty() == false) && (URI.empty() == false))
					{
						m_PageLinks->emplace_back(URI, viewRect);
					}
					break;
				}

				case PDFACTION_GOTO: // Goto
				{
					UXRect viewRect; FS_RECTF linkRect;

					if (FPDFLink_GetAnnotRect(link, &linkRect)) // Convert link rect
					{
						const UXRect temp(linkRect.left, linkRect.bottom, linkRect.right, linkRect.top);

						viewRect = ConvertToViewFromPage(temp, m_PageSize, m_Rotation);
					}

					int index = NEGATORY; UXReaderDestination target;

					if (const FPDF_DEST dest = FPDFLink_GetDest(m_pdfDocument, link))
					{
						index = int(FPDFDest_GetDestPageIndex(m_pdfDocument, dest));

						FPDF_BOOL bX = FALSE; FPDF_BOOL bY = FALSE; FPDF_BOOL bZ = FALSE;
						FS_FLOAT pageX = 0.0f; FS_FLOAT pageY = 0.0f; FS_FLOAT zoom = 0.0f;
						FPDFDest_GetLocationInPage(dest, &bX, &bY, &bZ, &pageX, &pageY, &zoom);
						ConvertToViewFromPage(bX, bY, pageX, pageY, m_PageSize, m_Rotation);

						target = UXReaderDestination(index, bX, bY, bZ, pageX, pageY, zoom);
					}

					if ((viewRect.empty() == false) && (index != NEGATORY))
					{
						m_PageLinks->emplace_back(target, viewRect);
					}
					break;
				}

				case PDFACTION_REMOTEGOTO: // Remote goto
				{
					UXRect viewRect; FS_RECTF linkRect; std::wstring URI;

					if (FPDFLink_GetAnnotRect(link, &linkRect)) // Convert link rect
					{
						const UXRect temp(linkRect.left, linkRect.bottom, linkRect.right, linkRect.top);

						viewRect = ConvertToViewFromPage(temp, m_PageSize, m_Rotation);
					}

					if (const int bytes = FPDFAction_GetFilePath(action, nullptr, 0))
					{
						URI.resize(bytes / sizeof(wchar_t)); void *buffer = &URI[0];

						if (FPDFAction_GetFilePath(action, buffer, int(URI.size() * sizeof(wchar_t))))
						{
							URI.resize(URI.size() - 1); // Trim NUL
						}
					}

					int index = NEGATORY; UXReaderDestination target;

					if (const FPDF_DEST dest = FPDFLink_GetDest(m_pdfDocument, link))
					{
						index = int(FPDFDest_GetDestPageIndex(m_pdfDocument, dest));

						FPDF_BOOL bX = FALSE; FPDF_BOOL bY = FALSE; FPDF_BOOL bZ = FALSE;
						FS_FLOAT pageX = 0.0f; FS_FLOAT pageY = 0.0f; FS_FLOAT zoom = 0.0f;
						FPDFDest_GetLocationInPage(dest, &bX, &bY, &bZ, &pageX, &pageY, &zoom);
						ConvertToViewFromPage(bX, bY, pageX, pageY, m_PageSize, m_Rotation);

						target = UXReaderDestination(index, bX, bY, bZ, pageX, pageY, zoom);
					}

					if ((viewRect.empty() == false) && (URI.empty() == false) && (index != NEGATORY))
					{
						m_PageLinks->emplace_back(target, URI, viewRect);
					}
					break;
				}

				case PDFACTION_LAUNCH: // Launch
				{
					UXRect viewRect; FS_RECTF linkRect; std::wstring URI;

					if (FPDFLink_GetAnnotRect(link, &linkRect)) // Convert link rect
					{
						const UXRect temp(linkRect.left, linkRect.bottom, linkRect.right, linkRect.top);

						viewRect = ConvertToViewFromPage(temp, m_PageSize, m_Rotation);
					}

					if (const int bytes = FPDFAction_GetFilePath(action, nullptr, 0))
					{
						URI.resize(bytes / sizeof(wchar_t)); void *buffer = &URI[0];

						if (FPDFAction_GetFilePath(action, buffer, int(URI.size() * sizeof(wchar_t))))
						{
							URI.resize(URI.size() - 1); // Trim NUL
						}
					}

					if ((viewRect.empty() == false) && (URI.empty() == false))
					{
						m_PageLinks->emplace_back(URI, viewRect);
					}
					break;
				}
			}
		}
		else // Try FPDF_DEST for FPDF_LINK aka PDFACTION_GOTO
		{
			UXRect viewRect; FS_RECTF linkRect;

			if (FPDFLink_GetAnnotRect(link, &linkRect)) // Convert link rect
			{
				const UXRect temp(linkRect.left, linkRect.bottom, linkRect.right, linkRect.top);

				viewRect = ConvertToViewFromPage(temp, m_PageSize, m_Rotation);
			}

			int index = NEGATORY; UXReaderDestination target;

			if (const FPDF_DEST dest = FPDFLink_GetDest(m_pdfDocument, link))
			{
				index = int(FPDFDest_GetDestPageIndex(m_pdfDocument, dest));

				FPDF_BOOL bX = FALSE; FPDF_BOOL bY = FALSE; FPDF_BOOL bZ = FALSE;
				FS_FLOAT pageX = 0.0f; FS_FLOAT pageY = 0.0f; FS_FLOAT zoom = 0.0f;
				FPDFDest_GetLocationInPage(dest, &bX, &bY, &bZ, &pageX, &pageY, &zoom);
				ConvertToViewFromPage(bX, bY, pageX, pageY, m_PageSize, m_Rotation);

				target = UXReaderDestination(index, bX, bY, bZ, pageX, pageY, zoom);
			}

			if ((viewRect.empty() == false) && (index != NEGATORY))
			{
				m_PageLinks->emplace_back(target, viewRect);
			}
		}
	}

	m_PageLinks->shrink_to_fit();

	if (pageLinkLogging)
	{
		for (auto it = m_PageLinks->begin(); it != m_PageLinks->end(); ++it)
		{
			it->Description();
		}
	}

	return (m_PageLinks->empty() == false);
}

bool UXReader::UXReaderDocumentPage::ExtractTextLinks(void)
{

	m_TextLinks = std::make_unique<std::vector<UXReaderAction>>();

	if (const FPDF_TEXTPAGE textPage = TextPage()) // FPDF_TEXTPAGE
	{
		if (const FPDF_PAGELINK pageLink = FPDFLink_LoadWebLinks(textPage))
		{
			if (const int linkCount = FPDFLink_CountWebLinks(pageLink))
			{
				for (int linkIndex = 0; linkIndex < linkCount; ++linkIndex)
				{
					std::wstring URI; std::vector<UXRect> rectangles;

					if (const int unichars = FPDFLink_GetURL(pageLink, linkIndex, nullptr, 0))
					{
						URI.resize(unichars); unsigned short *buffer = (unsigned short *)&URI[0];

						if (const int length = FPDFLink_GetURL(pageLink, linkIndex, buffer, int(URI.size())))
						{
							URI.resize(length - 1); // Trim NUL
						}
					}

					if (const int rectCount = FPDFLink_CountRects(pageLink, linkIndex))
					{
						for (int rectIndex = 0; rectIndex < rectCount; ++rectIndex)
						{
							double x1 = 0.0; double y1 = 0.0; double x2 = 0.0; double y2 = 0.0;

							FPDFLink_GetRect(pageLink, linkIndex, rectIndex, &x1, &y2, &x2, &y1);

							const UXPoint pt1(x1, y1); const UXPoint pt2(x2, y2); const UXRect temp(pt1, pt2);

							const UXRect viewRect = ConvertToViewFromPage(temp, m_PageSize, m_Rotation);

							rectangles.push_back(viewRect);
						}
					}

					if ((rectangles.empty() == false) && (URI.empty() == false))
					{
						rectangles.shrink_to_fit(); m_TextLinks->emplace_back(URI, rectangles);
					}
				}
			}

			FPDFLink_CloseWebLinks(pageLink);
		}

		if (m_Document->ConserveMemory())
		{
			TextPageClose();
		}
	}

	m_TextLinks->shrink_to_fit();

	if (textLinkLogging)
	{
		for (auto it = m_TextLinks->begin(); it != m_TextLinks->end(); ++it)
		{
			it->Description();
		}
	}

	return (m_TextLinks->empty() == false);
}

bool UXReader::UXReaderDocumentPage::ExtractLinks(void)
{

	bool redraw = false;

	UXReaderSupport& support = UXReaderSupport::Instance();
	{
		std::lock_guard<std::mutex> lockGuard(support.Mutex);

		if (pageLinkEnabled && (m_PageLinks == nullptr))
		{
			if (ExtractPageLinks() == true) redraw = true;
		}

		if (textLinkEnabled && (m_TextLinks == nullptr))
		{
			if (ExtractTextLinks() == true) redraw = true;
		}
	}

	return (redraw && (pageLinkOutline || textLinkOutline));
}

const UXReaderAction* UXReader::UXReaderDocumentPage::ActionForPoint(const UXPoint& point)
{

	UXReaderAction* action = nullptr;

	if (pageLinkEnabled && (action == nullptr) && (m_PageLinks != nullptr))
	{
		for (auto it = m_PageLinks->begin(); it != m_PageLinks->end(); ++it) // O(n)
		{
			if (it->Contains(point)) { action = &(*it); break; }
		}
	}

	if (textLinkEnabled && (action == nullptr) && (m_TextLinks != nullptr))
	{
		for (auto it = m_TextLinks->begin(); it != m_TextLinks->end(); ++it) // O(n)
		{
			if (it->Contains(point)) { action = &(*it); break; }
		}
	}

	return action;
}

std::wstring UXReader::UXReaderDocumentPage::ActionTooltip(const UXReaderAction* action)
{

	std::wstring text;

	if (action != nullptr)
	{
		switch (action->Type())
		{
			case UXReaderActionType::URI:
			case UXReaderActionType::Launch:
			case UXReaderActionType::Link:
			{
				text = action->URI();
				break;
			}

			case UXReaderActionType::Goto:
			{
				const int index = action->Destination()->PageIndex();
				text = L"Goto Page " + m_Document->PageLabel(index);
				break;
			}

			case UXReaderActionType::RemoteGoto:
			{
				const int page = action->Destination()->PageNumber();
				text = L"Goto Page " + std::to_wstring(page) + L" In " + action->URI();
				break;
			}
		}
	}

	return text;
}

//
//	Search methods
//

int UXReader::UXReaderDocumentPage::SearchPage(const std::wstring& term, const int options, int& counter)
{

	std::vector<UXReaderSelection> selections;

	UXReaderSupport& support = UXReaderSupport::Instance();
	{
		std::lock_guard<std::mutex> lockGuard(support.Mutex);

		if (const FPDF_TEXTPAGE textPage = TextPage()) // FPDF_TEXTPAGE
		{
			FPDF_WIDESTRING text = reinterpret_cast<FPDF_WIDESTRING>(term.data());

			if (const FPDF_SCHHANDLE handle = FPDFText_FindStart(textPage, text, options, 0))
			{
				while (FPDFText_FindNext(handle)) // Loop over any search hits
				{
					const int index = FPDFText_GetSchResultIndex(handle);

					const int count = FPDFText_GetSchCount(handle);

					const int rc = FPDFText_CountRects(textPage, index, count);

					std::vector<UXRect> rectangles; rectangles.reserve(rc);

					for (int ri = 0; ri < rc; ++ri) // Get rectangles for search hit
					{
						double x1 = 0.0; double y1 = 0.0; double x2 = 0.0; double y2 = 0.0;

						FPDFText_GetRect(textPage, ri, &x1, &y2, &x2, &y1); // Page co-ordinates

						const double d = 1.0; x1 -= d; y1 -= d; x2 += d; y2 += d; // Outset rectangle

						const UXPoint pt1(x1, y1); const UXPoint pt2(x2, y2); const UXRect temp(pt1, pt2);

						rectangles.emplace_back(ConvertToViewFromPage(temp, m_PageSize, m_Rotation));
					}

					//std::wstring derp(count+1, 0); unsigned short *buffer = (unsigned short *)&derp[0];

					//const int cc = FPDFText_GetText(textPage, index, count, buffer); derp.resize(cc-1);

					selections.emplace_back(m_PageIndex, index, count, rectangles, ++counter);
				}

				FPDFText_FindClose(handle); selections.shrink_to_fit();
			}

			if (m_Document->ConserveMemory()) TextPageClose();
		}

		m_SearchSelections = std::move(selections);
	}

	return int(m_SearchSelections.size());
}

void UXReader::UXReaderDocumentPage::ClearSearch(void)
{

	m_SearchSelections.clear();
}
