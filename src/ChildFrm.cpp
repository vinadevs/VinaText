/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "VinaTextApp.h"
#include "MainFrm.h"
#include "EditorView.h"
#include "ImageView.h"
#include "PdfView.h"
#include "MediaView.h"
#include "HostView.h"
#include "FileExplorerView.h"
#include "ChildFrm.h"
#include "AppUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
END_MESSAGE_MAP()

// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	cs.style &= ~WS_SYSMENU;

	if (!CMDIChildWndEx::PreCreateWindow(cs))
		return FALSE;

	return TRUE;
}

BOOL CChildFrame::CanShowOnTaskBarTabs()
{
	return FALSE;
}

void CChildFrame::ActivateFrame(int nCmdShow)
{
	nCmdShow = SW_MAXIMIZE;
	CMDIChildWndEx::ActivateFrame(nCmdShow);
}

BOOL CChildFrame::IsEditorFrame()
{
	return DYNAMIC_DOWNCAST(CEditorView, GetActiveView()) != NULL;
}

BOOL CChildFrame::IsPdfFrame()
{
	return DYNAMIC_DOWNCAST(CPdfView, GetActiveView()) != NULL;
}

BOOL CChildFrame::IsImageFrame()
{
	return DYNAMIC_DOWNCAST(CImageView, GetActiveView()) != NULL;
}

BOOL CChildFrame::IsMediaFrame()
{
	return DYNAMIC_DOWNCAST(CMediaView, GetActiveView()) != NULL;
}

BOOL CChildFrame::IsHostFrame()
{
	return DYNAMIC_DOWNCAST(CHostView, GetActiveView()) != NULL;
}

BOOL CChildFrame::IsFileExplorerFrame()
{
	return DYNAMIC_DOWNCAST(CFileExplorerView, GetActiveView()) != NULL;
}

LPCTSTR CChildFrame::GetDocumentName(CObject** pObj)
{
	return CMDIChildWndEx::GetDocumentName(pObj);
}

// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame message handlers
