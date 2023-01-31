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
#include "HostDoc.h"
#include "HostView.h"
#include "AppUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHostDoc

IMPLEMENT_DYNCREATE(CHostDoc, CBaseDoc)

BEGIN_MESSAGE_MAP(CHostDoc, CBaseDoc)
END_MESSAGE_MAP()

// CHostDoc construction/destruction

CHostDoc::CHostDoc()
{
	// TODO: add one-time construction code here
}

CHostDoc::~CHostDoc()
{
}

BOOL CHostDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	return CBaseDoc::OnOpenDocument(lpszPathName);
}

// CHostDoc serialization

void CHostDoc::Serialize(CArchive& ar)
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

CHostView* CHostDoc::GetHostView() const
{
	POSITION pos = GetFirstViewPosition();
	CHostView* pView = (CHostView*)GetNextView(pos);
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

// CHostDoc diagnostics

#ifdef _DEBUG
void CHostDoc::AssertValid() const
{
	CBaseDoc::AssertValid();
}

void CHostDoc::Dump(CDumpContext& dc) const
{
	CBaseDoc::Dump(dc);
}
#endif //_DEBUG

// CHostDoc commands