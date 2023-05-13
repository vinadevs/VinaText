/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "WebDoc.h"
#include "WebView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWebView

IMPLEMENT_DYNCREATE(CWebView, CHtmlView)

BEGIN_MESSAGE_MAP(CWebView, CHtmlView)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

CWebView::CWebView() {}

CWebView::~CWebView() {}

HRESULT CWebView::Render(CString& html)
{
    if(!html.GetLength()) return E_FAIL;
    CComPtr<IDispatch> disp = GetHtmlDocument();
    if(!disp)
    {
        //not initialized, try again
        Navigate(_T("about:"));
        disp = GetHtmlDocument();
        if(!disp)
            return E_NOINTERFACE;
    }
    CComQIPtr<IHTMLDocument2> doc2 = disp;
    if(!doc2) return E_NOINTERFACE;
    int nCharsize = sizeof(html.GetAt(0));
    IStream *pIstream = SHCreateMemStream(
        reinterpret_cast<const BYTE*>(html.GetBuffer()), nCharsize * html.GetLength());
    HRESULT hr = E_FAIL;
    if(pIstream)
    {
        CComQIPtr<IPersistStreamInit> psi = doc2;
        if(psi)
            hr = psi->Load(pIstream);
        pIstream->Release();
    }
    html.ReleaseBuffer();
    return hr;
}

/////////////////////////////////////////////////////////////////////////////
// CWebView diagnostics

#ifdef _DEBUG
void CWebView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CWebView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CWebDoc* CWebView::GetWebDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWebDoc)));
	return (CWebDoc*)m_pDocument;
}
#endif //_DEBUG

void CWebView::OnDestroy()
{
	CHtmlView::OnDestroy();
	CView::OnDestroy();	// Fixes CHtmlView bug
}
