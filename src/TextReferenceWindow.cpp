#include "stdafx.h"
#include "TextReferenceWindow.h"

#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CTextReferenceWindow, CDockPaneBase)

CTextReferenceWindow::CTextReferenceWindow()
{
}

CTextReferenceWindow::~CTextReferenceWindow()
{
}

BEGIN_MESSAGE_MAP(CTextReferenceWindow, CDockPaneBase)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(UMW_DOCK_PANE_UPDATE, &CTextReferenceWindow::OnDockPaneUpdate)
END_MESSAGE_MAP()

LRESULT CTextReferenceWindow::OnDockPaneUpdate(WPARAM wParam, LPARAM lParam)
{
	WORD wMsgTarget = LOWORD(wParam);
	WORD wMsgHint = HIWORD(wParam);

	if (MAIN_FRAME_UPDATE_MSG::MAIN_FRAME_UPDATE_ALL_DOCKPANE == wMsgTarget)
	{
		switch (wMsgHint)
		{
		case MAIN_FRAME_UPDATE_HINT::MAIN_FRAME_UPDATE_HINT_SETTING_CHANGED:
		{
			UpdateUIVisual();
		}
		break;
		}
	}
	return 0L;
}

int CTextReferenceWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockPaneBase::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void CTextReferenceWindow::OnSize(UINT nType, int cx, int cy)
{
	CDockPaneBase::OnSize(nType, cx, cy);
}

void CTextReferenceWindow::UpdateUIVisual()
{
}