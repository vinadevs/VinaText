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
#include "FileExplorerDoc.h"
#include "FileExplorerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFileExplorerDoc

IMPLEMENT_DYNCREATE(CFileExplorerDoc, CBaseDoc)

BEGIN_MESSAGE_MAP(CFileExplorerDoc, CBaseDoc)
END_MESSAGE_MAP()

// CFileExplorerDoc construction/destruction

CFileExplorerDoc::CFileExplorerDoc() {}

CFileExplorerDoc::~CFileExplorerDoc() {}

// CFileExplorerDoc diagnostics

#ifdef _DEBUG
void CFileExplorerDoc::AssertValid() const
{
	CBaseDoc::AssertValid();
}

void CFileExplorerDoc::Dump(CDumpContext& dc) const
{
	CBaseDoc::Dump(dc);
}
#endif //_DEBUG
