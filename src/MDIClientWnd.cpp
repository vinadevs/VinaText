/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "VinaTextApp.h"
#include "MDIClientWnd.h"

// CMDIClientWnd

IMPLEMENT_DYNAMIC(CMDIClientWnd, CWnd)

CMDIClientWnd::CMDIClientWnd()
{
}

CMDIClientWnd::~CMDIClientWnd()
{
}

BEGIN_MESSAGE_MAP(CMDIClientWnd, CWnd)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMDIClientWnd message handlers

BOOL CMDIClientWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	// Set brush to desired background color
	CBrush backBrush(RGB(255, 128, 128));

	// Save old brush
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);

	CRect rect;
	pDC->GetClipBox(&rect);     // Erase the area needed
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);

	return CWnd::OnEraseBkgnd(pDC);
}