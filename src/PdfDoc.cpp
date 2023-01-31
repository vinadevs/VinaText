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
#include "afxdatarecovery.h"
#include "MainFrm.h"
#include "PdfDoc.h"
#include "PdfView.h"
#include "AppUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPdfDoc

IMPLEMENT_DYNCREATE(CPdfDoc, CBaseDoc)

BEGIN_MESSAGE_MAP(CPdfDoc, CBaseDoc)
END_MESSAGE_MAP()

// CPdfDoc construction/destruction

CPdfDoc::CPdfDoc()
{
	// TODO: add one-time construction code here
}

CPdfDoc::~CPdfDoc()
{
}

BOOL CPdfDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	return CBaseDoc::OnOpenDocument(lpszPathName);
}

// CPdfDoc serialization

void CPdfDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

CPdfView* CPdfDoc::GetPdfView() const
{
	POSITION pos = GetFirstViewPosition();
	CPdfView* pView = (CPdfView*)GetNextView(pos);
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

void CPdfDoc::ReloadPreviewDocument(const CString & strFilePath)
{
	if (PathFileExists(strFilePath))
	{
		SetPathName(strFilePath);
		AppUtils::GetVinaTextApp()->m_bIsReloadByPreviewMode = TRUE;
		GetPdfView()->UpdatePreviewFileContent();
		AppUtils::GetVinaTextApp()->m_bIsReloadByPreviewMode = FALSE;
	}
}

// CPdfDoc diagnostics

#ifdef _DEBUG
void CPdfDoc::AssertValid() const
{
	CBaseDoc::AssertValid();
}

void CPdfDoc::Dump(CDumpContext& dc) const
{
	CBaseDoc::Dump(dc);
}
#endif //_DEBUG

// CPdfDoc commands