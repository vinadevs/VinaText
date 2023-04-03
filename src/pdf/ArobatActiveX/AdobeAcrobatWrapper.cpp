/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "AdobeAcrobatWrapper.h"

// runtime activeX
IMPLEMENT_DYNCREATE(CAcrobatActiveXWrapper, CWnd)

CLSID const& CAcrobatActiveXWrapper::GetClsid()
{
	static CLSID const clsid = { 0xCA8A9780, 0x280D, 0x11CF, { 0xA2, 0x4D, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };
	return clsid;
}

BOOL CAcrobatActiveXWrapper::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
	const RECT& rect, CWnd* pParentWnd, UINT nID,
	CCreateContext* pContext /*= NULL*/)
{
	return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID);
}

BOOL CAcrobatActiveXWrapper::Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
	UINT nID, CFile* pPersist /*= NULL*/, BOOL bStorage /*= FALSE*/,
	BSTR bstrLicKey /*= NULL*/)
{
	return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey);
}

CString CAcrobatActiveXWrapper::get_src()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CAcrobatActiveXWrapper::put_src(LPCTSTR newValue)
{
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
}

BOOL CAcrobatActiveXWrapper::LoadPDFFile(LPCTSTR fileName)
{
	BOOL result;
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, fileName);
	return result;
}

void CAcrobatActiveXWrapper::setShowToolbar(BOOL On)
{
	static BYTE parms[] = VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, On);
}

void CAcrobatActiveXWrapper::gotoFirstPage()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CAcrobatActiveXWrapper::gotoLastPage()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CAcrobatActiveXWrapper::gotoNextPage()
{
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CAcrobatActiveXWrapper::gotoPreviousPage()
{
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CAcrobatActiveXWrapper::setCurrentPage(long n)
{
	static BYTE parms[] = VTS_I4;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, n);
}

void CAcrobatActiveXWrapper::goForwardStack()
{
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CAcrobatActiveXWrapper::goBackwardStack()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CAcrobatActiveXWrapper::setPageMode(LPCTSTR pageMode)
{
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pageMode);
}

void CAcrobatActiveXWrapper::setLayoutMode(LPCTSTR layoutMode)
{
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, layoutMode);
}

void CAcrobatActiveXWrapper::setNamedDest(LPCTSTR namedDest)
{
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, namedDest);
}

void CAcrobatActiveXWrapper::Print()
{
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CAcrobatActiveXWrapper::printWithDialog()
{
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CAcrobatActiveXWrapper::setZoom(float percent)
{
	static BYTE parms[] = VTS_R4;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, percent);
}

void CAcrobatActiveXWrapper::setZoomScroll(float percent, float left, float top)
{
	static BYTE parms[] = VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms, percent, left, top);
}

void CAcrobatActiveXWrapper::setView(LPCTSTR viewMode)
{
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms, viewMode);
}

void CAcrobatActiveXWrapper::setViewScroll(LPCTSTR viewMode, float offset)
{
	static BYTE parms[] = VTS_BSTR VTS_R4;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms, viewMode, offset);
}

void CAcrobatActiveXWrapper::setViewRect(float left, float top, float width, float height)
{
	static BYTE parms[] = VTS_R4 VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms, left, top, width, height);
}

void CAcrobatActiveXWrapper::printPages(long from, long to)
{
	static BYTE parms[] = VTS_I4 VTS_I4;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms, from, to);
}

void CAcrobatActiveXWrapper::printPagesFit(long from, long to, BOOL shrinkToFit)
{
	static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms, from, to, shrinkToFit);
}

void CAcrobatActiveXWrapper::printAll()
{
	InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CAcrobatActiveXWrapper::printAllFit(BOOL shrinkToFit)
{
	static BYTE parms[] = VTS_BOOL;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms, shrinkToFit);
}

void CAcrobatActiveXWrapper::setShowScrollbars(BOOL On)
{
	static BYTE parms[] = VTS_BOOL;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms, On);
}

VARIANT CAcrobatActiveXWrapper::GetVersions()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void CAcrobatActiveXWrapper::setCurrentHightlight(long a, long b, long c, long d)
{
	static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, a, b, c, d);
}

void CAcrobatActiveXWrapper::setCurrentHighlight(long a, long b, long c, long d)
{
	static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, a, b, c, d);
}

void CAcrobatActiveXWrapper::postMessage(VARIANT strArray)
{
	static BYTE parms[] = VTS_VARIANT;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &strArray);
}

VARIANT CAcrobatActiveXWrapper::get_messageHandler()
{
	VARIANT result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void CAcrobatActiveXWrapper::put_messageHandler(VARIANT newValue)
{
	static BYTE parms[] = VTS_VARIANT;
	InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
}

void CAcrobatActiveXWrapper::execCommand(VARIANT strArray)
{
	static BYTE parms[] = VTS_VARIANT;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &strArray);
}