#pragma once

#include "DockPaneBase.h"

class CTextReferenceWindow : public CDockPaneBase
{
	// Construction
public:
	DECLARE_DYNCREATE(CTextReferenceWindow)
	CTextReferenceWindow();
	virtual ~CTextReferenceWindow();

	// Implementation
public:

protected:
	virtual void UpdateUIVisual();

protected:

	// Messages
	afx_msg LRESULT OnDockPaneUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};