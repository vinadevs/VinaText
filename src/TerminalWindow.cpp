#include "stdafx.h"
#include "TerminalWindow.h"

#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CTerminalWindow, CDockPaneBase)

CTerminalWindow::CTerminalWindow()
{
}

CTerminalWindow::~CTerminalWindow()
{
}

BEGIN_MESSAGE_MAP(CTerminalWindow, CDockPaneBase)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(UMW_DOCK_PANE_UPDATE, &CTerminalWindow::OnDockPaneUpdate)
END_MESSAGE_MAP()

LRESULT CTerminalWindow::OnDockPaneUpdate(WPARAM wParam, LPARAM lParam)
{
	WORD wMsgTarget = LOWORD(wParam);
	WORD wMsgHint = HIWORD(wParam);

	if (MAIN_FRAME_UPDATE_MSG::MAIN_FRAME_UPDATE_ALL_DOCKPANE == wMsgTarget)
	{
		switch (wMsgHint)
		{
		case MAIN_FRAME_UPDATE_HINT::MAIN_FRAME_UPDATE_HINT_SETTING_CHANGED:
		{
			UpdateAppSetting();
		}
		break;
		}
	}
	return 0L;
}

int CTerminalWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockPaneBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CTerminalWindow::OnSize(UINT nType, int cx, int cy)
{
	CDockPaneBase::OnSize(nType, cx, cy);
}

void CTerminalWindow::UpdateAppSetting()
{
}