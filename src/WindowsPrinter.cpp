/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include <Commdlg.h>
#include "WindowsPrinter.h"
#include "Editor.h"
#include "ImageView.h"
#include "Memdc.h"

CWindowsPrinter::CWindowsPrinter(const CString& strDocumentPath, HWND hParent/*= NULL*/)
{
	m_hParentUI = hParent;
	m_strDocumentPath = strDocumentPath;
}

BOOL CWindowsPrinter::ShowPageSetupDlg()
{
	PAGESETUPDLG pDlg = { 0 };
	pDlg.lStructSize = sizeof(PAGESETUPDLG);
	pDlg.hwndOwner = m_hParentUI;
	pDlg.hInstance = nullptr;
	pDlg.Flags = PSD_DEFAULTMINMARGINS | PSD_MARGINS | PSD_DISABLEPAPER | PSD_DISABLEORIENTATION;

	pDlg.rtMargin.left = 2540;
	pDlg.rtMargin.top = 2540;
	pDlg.rtMargin.right = 2540;
	pDlg.rtMargin.bottom = 2540;

	if (!PageSetupDlg(&pDlg))
		return FALSE;

	return TRUE;
}

void CWindowsPrinter::PrintText(BOOL bShowPrinterDlg, CEditorCtrl* pEditorCtrl)
{
	ASSERT(m_hParentUI); ASSERT(pEditorCtrl);
	if (!m_hParentUI || !pEditorCtrl) return;
    PRINTDLGEX pDlg  = {0};
    pDlg.lStructSize = sizeof(PRINTDLGEX);
	pDlg.hwndOwner	 = m_hParentUI;
    pDlg.hInstance   = nullptr;
    pDlg.Flags       = PD_USEDEVMODECOPIESANDCOLLATE | PD_ALLPAGES | PD_RETURNDC | PD_NOCURRENTPAGE | PD_NOPAGENUMS;
    pDlg.nMinPage    = 1;
    pDlg.nMaxPage    = 0xffffU; // We do not know how many pages in the document
    pDlg.nCopies     = 1;
    pDlg.hDC         = nullptr;
    pDlg.nStartPage  = START_PAGE_GENERAL;

    // See if a range has been selected
    size_t startPos = pEditorCtrl->DoCommand(SCI_GETSELECTIONSTART);
    size_t endPos   = pEditorCtrl->DoCommand(SCI_GETSELECTIONEND);

    if (startPos == endPos)
        pDlg.Flags |= PD_NOSELECTION;
    else
        pDlg.Flags |= PD_SELECTION;

    if (!bShowPrinterDlg)
    {
        // Don't display dialog box, just use the default printer and options
        pDlg.Flags |= PD_RETURNDEFAULT;
    }

    HRESULT hResult = PrintDlgEx(&pDlg);
    if ((hResult != S_OK) || ((pDlg.dwResultAction != PD_RESULT_PRINT) && bShowPrinterDlg))
        return;

    // reset all indicators
    size_t length = pEditorCtrl->DoCommand(SCI_GETLENGTH);
    for (int i = INDIC_CONTAINER; i <= INDIC_MAX; ++i)
    {
        pEditorCtrl->DoCommand(SCI_SETINDICATORCURRENT, i);
        pEditorCtrl->DoCommand(SCI_INDICATORCLEARRANGE, 0, length);
    }
    // store and reset UI settings
    int viewWs = static_cast<int>(pEditorCtrl->DoCommand(SCI_GETVIEWWS));
    pEditorCtrl->DoCommand(SCI_SETVIEWWS, 0);
    int edgeMode = static_cast<int>(pEditorCtrl->DoCommand(SCI_GETEDGEMODE));
    pEditorCtrl->DoCommand(SCI_SETEDGEMODE, EDGE_NONE);
    pEditorCtrl->DoCommand(SCI_SETWRAPVISUALFLAGS, SC_WRAPVISUALFLAG_END);

	HDC hdc = pDlg.hDC; if (!hdc) return;

    RECT  rectMargins, rectPhysMargins;
    POINT ptPage;
    POINT ptDpi;

    // Get printer resolution
    ptDpi.x = GetDeviceCaps(hdc, LOGPIXELSX); // dpi in X direction
    ptDpi.y = GetDeviceCaps(hdc, LOGPIXELSY); // dpi in Y direction

    // Start by getting the physical page size (in device units).
    ptPage.x = GetDeviceCaps(hdc, PHYSICALWIDTH);  // device units
    ptPage.y = GetDeviceCaps(hdc, PHYSICALHEIGHT); // device units

    // Get the dimensions of the unprintable
    // part of the page (in device units).
    rectPhysMargins.left = GetDeviceCaps(hdc, PHYSICALOFFSETX);
    rectPhysMargins.top  = GetDeviceCaps(hdc, PHYSICALOFFSETY);

    // To get the right and lower unprintable area,
    // we take the entire width and height of the paper and
    // subtract everything else.
    rectPhysMargins.right = ptPage.x                      // total paper width
                            - GetDeviceCaps(hdc, HORZRES) // printable width
                            - rectPhysMargins.left;       // left unprintable margin

    rectPhysMargins.bottom = ptPage.y                      // total paper height
                             - GetDeviceCaps(hdc, VERTRES) // printable height
                             - rectPhysMargins.top;        // right unprintable margin

    wchar_t localeInfo[3];
    GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_IMEASURE, localeInfo, 3);
    // Metric system. '1' is US System
    int  defaultMargin = localeInfo[0] == '0' ? 2540 : 1000;
    RECT pagesetupMargin;
	pagesetupMargin.left = defaultMargin;
	pagesetupMargin.top = defaultMargin;
    pagesetupMargin.right = defaultMargin;
    pagesetupMargin.bottom = defaultMargin;

    if (pagesetupMargin.left != 0 || pagesetupMargin.right != 0 ||
        pagesetupMargin.top != 0 || pagesetupMargin.bottom != 0)
    {
        RECT rectSetup;

        // Convert the hundredths of millimeters (HiMetric) or
        // thousandths of inches (HiEnglish) margin values
        // from the Page Setup dialog to device units.
        // (There are 2540 hundredths of a mm in an inch.)

        if (localeInfo[0] == '0')
        {
            // Metric system. '1' is US System
            rectSetup.left   = MulDiv(pagesetupMargin.left, ptDpi.x, 2540);
            rectSetup.top    = MulDiv(pagesetupMargin.top, ptDpi.y, 2540);
            rectSetup.right  = MulDiv(pagesetupMargin.right, ptDpi.x, 2540);
            rectSetup.bottom = MulDiv(pagesetupMargin.bottom, ptDpi.y, 2540);
        }
        else
        {
            rectSetup.left   = MulDiv(pagesetupMargin.left, ptDpi.x, 1000);
            rectSetup.top    = MulDiv(pagesetupMargin.top, ptDpi.y, 1000);
            rectSetup.right  = MulDiv(pagesetupMargin.right, ptDpi.x, 1000);
            rectSetup.bottom = MulDiv(pagesetupMargin.bottom, ptDpi.y, 1000);
        }

        // Don't reduce margins below the minimum printable area
        rectMargins.left   = max(rectPhysMargins.left, rectSetup.left);
        rectMargins.top    = max(rectPhysMargins.top, rectSetup.top);
        rectMargins.right  = max(rectPhysMargins.right, rectSetup.right);
        rectMargins.bottom = max(rectPhysMargins.bottom, rectSetup.bottom);
    }
    else
    {
        rectMargins.left   = rectPhysMargins.left;
        rectMargins.top    = rectPhysMargins.top;
        rectMargins.right  = rectPhysMargins.right;
        rectMargins.bottom = rectPhysMargins.bottom;
    }

    // rectMargins now contains the values used to shrink the printable
    // area of the page.

    // Convert device coordinates into logical coordinates
    DPtoLP(hdc, reinterpret_cast<LPPOINT>(&rectMargins), 2);
    DPtoLP(hdc, reinterpret_cast<LPPOINT>(&rectPhysMargins), 2);

    // Convert page size to logical units and we're done!
    DPtoLP(hdc, static_cast<LPPOINT>(&ptPage), 1);

    DOCINFO      di      = { sizeof(DOCINFO), TEXT("Printing Text..."), nullptr, nullptr, 0 };
    di.lpszDocName       = m_strDocumentPath;
    di.lpszOutput        = nullptr;
    di.lpszDatatype      = nullptr;
    di.fwType            = 0;
    if (::StartDoc(hdc, &di) < 0)
    {
        ::DeleteDC(hdc);
		if (pDlg.hDevMode != nullptr)
			GlobalFree(pDlg.hDevMode);
		if (pDlg.hDevNames != nullptr)
			GlobalFree(pDlg.hDevNames);
		if (pDlg.lpPageRanges != nullptr)
			GlobalFree(pDlg.lpPageRanges);
        return;
    }

    size_t lengthDoc     = pEditorCtrl->DoCommand(SCI_GETLENGTH);
    size_t lengthDocMax  = lengthDoc;
    size_t lengthPrinted = 0;

    // Requested to print selection
    if (pDlg.Flags & PD_SELECTION)
    {
        if (startPos > endPos)
        {
            lengthPrinted = endPos;
            lengthDoc     = startPos;
        }
        else
        {
            lengthPrinted = startPos;
            lengthDoc     = endPos;
        }

        if (lengthDoc > lengthDocMax)
            lengthDoc = lengthDocMax;
    }

    // We must subtract the physical margins from the printable area
    Sci_RangeToFormat frPrint;
    frPrint.hdc           = hdc;
    frPrint.hdcTarget     = hdc;
    frPrint.rc.left       = rectMargins.left - rectPhysMargins.left;
    frPrint.rc.top        = rectMargins.top - rectPhysMargins.top;
    frPrint.rc.right      = ptPage.x - rectMargins.right - rectPhysMargins.left;
    frPrint.rc.bottom     = ptPage.y - rectMargins.bottom - rectPhysMargins.top;
    frPrint.rcPage.left   = 0;
    frPrint.rcPage.top    = 0;
    frPrint.rcPage.right  = ptPage.x - rectPhysMargins.left - rectPhysMargins.right - 1;
    frPrint.rcPage.bottom = ptPage.y - rectPhysMargins.top - rectPhysMargins.bottom - 1;

    // Print each page
    while (lengthPrinted < lengthDoc)
    {
        ::StartPage(hdc);

        frPrint.chrg.cpMin = static_cast<Sci_PositionCR>(lengthPrinted);
        frPrint.chrg.cpMax = static_cast<Sci_PositionCR>(lengthDoc);

        lengthPrinted = pEditorCtrl->DoCommand(SCI_FORMATRANGE, true, reinterpret_cast<LPARAM>(&frPrint));

        ::EndPage(hdc);
    }

    pEditorCtrl->DoCommand(SCI_FORMATRANGE, FALSE, 0);

    ::EndDoc(hdc);
    ::DeleteDC(hdc);

    if (pDlg.hDevMode != nullptr)
        GlobalFree(pDlg.hDevMode);
    if (pDlg.hDevNames != nullptr)
        GlobalFree(pDlg.hDevNames);
    if (pDlg.lpPageRanges != nullptr)
        GlobalFree(pDlg.lpPageRanges);

    // reset the UI
    pEditorCtrl->DoCommand(SCI_SETVIEWWS, viewWs);
    pEditorCtrl->DoCommand(SCI_SETEDGEMODE, edgeMode);
    pEditorCtrl->DoCommand(SCI_SETWRAPVISUALFLAGS, SC_WRAPVISUALFLAG_NONE);
}

void CWindowsPrinter::PrintImage(BOOL bShowPrinterDlg, CImageView* pView)
{
	ASSERT(m_hParentUI); ASSERT(pView);
	if (!m_hParentUI || !pView) return;
	PRINTDLGEX pDlg = { 0 };
	pDlg.lStructSize = sizeof(PRINTDLGEX);
	pDlg.hwndOwner = m_hParentUI;
	pDlg.hInstance = nullptr;
	pDlg.Flags = PD_USEDEVMODECOPIESANDCOLLATE | PD_ALLPAGES | PD_RETURNDC | PD_NOCURRENTPAGE | PD_NOPAGENUMS;
	pDlg.nMinPage = 1;
	pDlg.nMaxPage = 0xffffU; // We do not know how many pages in the document
	pDlg.nCopies = 1;
	pDlg.hDC = nullptr;
	pDlg.nStartPage = START_PAGE_GENERAL;

	if (!bShowPrinterDlg)
	{
		// Don't display dialog box, just use the default printer and options
		pDlg.Flags |= PD_RETURNDEFAULT;
	}

	HRESULT hResult = PrintDlgEx(&pDlg);
	if ((hResult != S_OK) || ((pDlg.dwResultAction != PD_RESULT_PRINT) && bShowPrinterDlg))
		return;

	HDC hdc = pDlg.hDC; if (!hdc) return;

	int cxsize = 0, cxpage = 0;
	int cysize = 0, cypage = 0;

	HBITMAP hBitmap = pView->GetCurrentBitmap(); // get current image loaded
	if (hBitmap)
	{
		cxpage = GetDeviceCaps(hdc, HORZRES);	
		cypage = GetDeviceCaps(hdc, VERTRES);
		BITMAP bitmap;
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		int bxWidth = 0, bxHeight = 0;
		bxWidth = bitmap.bmWidth;
		bxHeight = bitmap.bmHeight;
		HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hBitmap);

		DOCINFO  di = { sizeof(DOCINFO), TEXT("Printing Image..."), nullptr, nullptr, 0 };
		di.lpszDocName = m_strDocumentPath;
		di.lpszOutput = nullptr;
		di.lpszDatatype = nullptr;
		di.fwType = 0;
		if (::StartDoc(hdc, &di) < 0)
		{
			::DeleteDC(hdc);
			if (pDlg.hDevMode != nullptr)
				GlobalFree(pDlg.hDevMode);
			if (pDlg.hDevNames != nullptr)
				GlobalFree(pDlg.hDevNames);
			if (pDlg.lpPageRanges != nullptr)
				GlobalFree(pDlg.lpPageRanges);
			return;
		}

		StartPage(hdc);
		SetMapMode(hdc, MM_ISOTROPIC);
		SetWindowExtEx(hdc, cxpage, cypage, NULL);
		SetViewportExtEx(hdc, cxpage, cypage, NULL);

		SetViewportOrgEx(hdc, 0, 0, NULL);
		StretchBlt(hdc, 0, 0, cxpage, cypage, hdcMem, 0, 0, bxWidth, bxHeight, SRCCOPY);
		EndPage(hdc);
		EndDoc(hdc);
		DeleteDC(hdc);
		SelectObject(hdcMem, hbmOld);
		DeleteDC(hdcMem);
	}

	if (pDlg.hDevMode != nullptr)
		GlobalFree(pDlg.hDevMode);
	if (pDlg.hDevNames != nullptr)
		GlobalFree(pDlg.hDevNames);
	if (pDlg.lpPageRanges != nullptr)
		GlobalFree(pDlg.lpPageRanges);
}

void CWindowsPrinter::PrintPDF()
{
    ShellExecute(NULL, L"print", m_strDocumentPath, NULL, NULL, SW_HIDE);
    AfxMessageBox(_T("PDF file printed."), MB_ICONINFORMATION);
}
