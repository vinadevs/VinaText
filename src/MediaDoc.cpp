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
#include "MediaDoc.h"
#include "MediaView.h"
#include "AppUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMediaDoc

IMPLEMENT_DYNCREATE(CMediaDoc, CBaseDoc)

BEGIN_MESSAGE_MAP(CMediaDoc, CBaseDoc)
END_MESSAGE_MAP()

// CMediaDoc construction/destruction

CMediaDoc::CMediaDoc()
{
	// TODO: add one-time construction code here
}

CMediaDoc::~CMediaDoc()
{
}

BOOL CMediaDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	return CBaseDoc::OnOpenDocument(lpszPathName);
}

CMediaView* CMediaDoc::GetMediaView() const
{
	POSITION pos = GetFirstViewPosition();
	CMediaView* pView = (CMediaView*)GetNextView(pos);
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

void CMediaDoc::ReloadPreviewDocument(const CString & strFilePath)
{
	if (PathFileExists(strFilePath))
	{
		SetPathName(strFilePath);
		AppUtils::GetVinaTextApp()->m_bIsReloadByPreviewMode = TRUE;
		GetMediaView()->UpdatePreviewFileContent();
		AppUtils::GetVinaTextApp()->m_bIsReloadByPreviewMode = FALSE;
	}
}

// CMediaDoc diagnostics

#ifdef _DEBUG
void CMediaDoc::AssertValid() const
{
	CBaseDoc::AssertValid();
}

void CMediaDoc::Dump(CDumpContext& dc) const
{
	CBaseDoc::Dump(dc);
}
#endif //_DEBUG

// CMediaDoc commands