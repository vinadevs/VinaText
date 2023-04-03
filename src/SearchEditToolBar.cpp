#include "stdafx.h"
#include "SearchEditToolBar.h"
#include "MainFrm.h"
#include "EditorDoc.h"

#pragma warning(disable:4996)

/////////////////////////////////////////////////////////////////////////////
// CSearchEditToolBar

IMPLEMENT_DYNAMIC(CSearchEditToolBar, CUndoRedoEditControl)

CSearchEditToolBar::CSearchEditToolBar()
{
}

CSearchEditToolBar::~CSearchEditToolBar()
{
}

void CSearchEditToolBar::SetFocusEx()
{
	SetFocus();
	SetSel(0, -1); // select all text and move cursor at the end
	SetSel(-1); //  remove selection
}

BEGIN_MESSAGE_MAP(CSearchEditToolBar, CUndoRedoEditControl)
END_MESSAGE_MAP()

BOOL CSearchEditToolBar::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			CString str;
			GetWindowText(str);
			return true;
		}
		else if (pMsg->wParam == VK_ESCAPE)
		{
			auto pActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
			if (pActiveDoc && pActiveDoc->GetEditorCtrl())
			{
				SetWindowTextW(_T(""));
				pActiveDoc->GetEditorCtrl()->SetFocus();
			}
			return true;
		}
		if (::GetKeyState(VK_CONTROL) < 0)
		{
			if (pMsg->wParam == 'C')
			{
				SendMessage(WM_COPY); // send command message to child control
				return true;
			}
			if (pMsg->wParam == 'X')
			{
				SendMessage(WM_CUT); // send command message to child control
				return true;
			}
			if (pMsg->wParam == 'V')
			{
				SendMessage(WM_PASTE); // send command message to child control
				return true;
			}
		}
	}
	return CUndoRedoEditControl::PreTranslateMessage(pMsg);
}
