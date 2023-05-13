/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VinaTextApp.h"
#endif
#include "MainFrm.h"
#include "WebDoc.h"
#include "WebView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWebDoc

IMPLEMENT_DYNCREATE(CWebDoc, CDocument)

BEGIN_MESSAGE_MAP(CWebDoc, CDocument)
END_MESSAGE_MAP()

// CWebDoc construction/destruction

CWebDoc::CWebDoc() {}

CWebDoc::~CWebDoc() {}

CWebView* CWebDoc::GetWebView() const
{
	POSITION pos = GetFirstViewPosition();
	CWebView* pView = (CWebView*)GetNextView(pos);
	if (pView)
	{
		return pView;
	}
	else
	{
		ASSERT(pView);
		return NULL;
	}
}

HRESULT CWebDoc::LoadHTMLContent(CString& strHTMLContent)
{
	return GetWebView()->Render(strHTMLContent);
}

void CWebDoc::OnCloseDocument()
{
	CDocument::OnCloseDocument();
	AppUtils::CheckLastOpenDocument();
}

// CWebDoc diagnostics

#ifdef _DEBUG
void CWebDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWebDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
