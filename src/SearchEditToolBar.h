/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "UndoRedoEditControl.h"

/////////////////////////////////////////////////////////////////////////////
// CSearchEditToolBar

class CSearchEditToolBar : public CUndoRedoEditControl
{
	DECLARE_DYNAMIC(CSearchEditToolBar)
public:
	CSearchEditToolBar();
	virtual ~CSearchEditToolBar();
	void SetParent(CWnd* pWndParent) { m_pWndParent = pWndParent; }
	void SetFocusEx();
	BOOL m_IsInitialTextFromView = FALSE;

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CWnd* m_pWndParent = NULL;
};