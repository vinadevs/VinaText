/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "MainFrm.h"
#include "BaseDoc.h"
#include "ViewBase.h"
#include "AppUtil.h"
#include "AppSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewBase

IMPLEMENT_DYNCREATE(CViewBase, CView)

CViewBase::~CViewBase()
{
}

BEGIN_MESSAGE_MAP(CViewBase, CView)
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewBase diagnostics

#ifdef _DEBUG
void CViewBase::AssertValid() const
{
	CView::AssertValid();
}

void CViewBase::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewBase message handlers

void CViewBase::OnActivateView(BOOL bActivate, CView * pActivateView, CView * pDeactiveView)
{
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
	if (AppSettingMgr.m_bRevealExplorerWhenSwitchFile)
	{
		pFrame->OnOpenFileExplorer();
	}
	pFrame->PostMessage(WM_COMMAND, (WPARAM)UMW_SET_COLOR_ACTIVE_TAB_MDI);
}

void CViewBase::OnDraw(CDC * pDC)
{
}

CBaseDoc* CViewBase::GetBaseDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBaseDoc)));
	return (CBaseDoc*)m_pDocument;
}