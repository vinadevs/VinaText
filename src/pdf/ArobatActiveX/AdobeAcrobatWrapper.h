/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

// Pdf activeX interface 

class CAcrobatActiveXWrapper : public CWnd
{
protected:
	DECLARE_DYNCREATE(CAcrobatActiveXWrapper)
public:
	CLSID const& GetClsid();

	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL);

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
		UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL);

	CString get_src();

	void put_src(LPCTSTR newValue);

	BOOL LoadPDFFile(LPCTSTR fileName);

	void setShowToolbar(BOOL On);

	void gotoFirstPage();

	void gotoLastPage();

	void gotoNextPage();

	void gotoPreviousPage();

	void setCurrentPage(long n);

	void goForwardStack();

	void goBackwardStack();

	void setPageMode(LPCTSTR pageMode);

	void setLayoutMode(LPCTSTR layoutMode);

	void setNamedDest(LPCTSTR namedDest);

	void Print();

	void printWithDialog();

	void setZoom(float percent);

	void setZoomScroll(float percent, float left, float top);

	void setView(LPCTSTR viewMode);

	void setViewScroll(LPCTSTR viewMode, float offset);

	void setViewRect(float left, float top, float width, float height);

	void printPages(long from, long to);

	void printPagesFit(long from, long to, BOOL shrinkToFit);

	void printAll();

	void printAllFit(BOOL shrinkToFit);

	void setShowScrollbars(BOOL On);

	VARIANT GetVersions();

	void setCurrentHightlight(long a, long b, long c, long d);

	void setCurrentHighlight(long a, long b, long c, long d);

	void postMessage(VARIANT strArray);

	VARIANT get_messageHandler();

	void put_messageHandler(VARIANT newValue);

	void execCommand(VARIANT strArray);
};