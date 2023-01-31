/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "StdAfx.h"
#include "DockPaneBase.h"
#include "MainFrm.h"

IMPLEMENT_DYNCREATE(CDockPaneBase, CDockablePane)

CDockPaneBase::CDockPaneBase(void) 
{
}

CDockPaneBase::~CDockPaneBase(void)
{
}

int CDockPaneBase::OnCreate(LPCREATESTRUCT lp)
{
	if (CDockablePane::OnCreate(lp) == -1)
		return -1;

	return 0;
}

void CDockPaneBase::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
}

BOOL CDockPaneBase::OnBeforeFloat(CRect & rectFloat, AFX_DOCK_METHOD dockMethod)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return FALSE;
	pFrame->ReactiveTabAfterFloatPane();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CDockPaneBase, CDockablePane)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


