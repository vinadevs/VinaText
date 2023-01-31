#pragma once

#include "DockPaneBase.h"

class CTerminalWindow : public CDockPaneBase
{
	// Construction
public:
	DECLARE_DYNCREATE(CTerminalWindow)
	CTerminalWindow();
	virtual ~CTerminalWindow();

	// Implementation
public:

protected:
	virtual void UpdateAppSetting();

protected:

	// Messages
	afx_msg LRESULT OnDockPaneUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};