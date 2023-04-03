/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once
#include "afxwin.h"

class CDockPaneBase : public CDockablePane
{
	DECLARE_DYNCREATE(CDockPaneBase)

public:
	CDockPaneBase();
	virtual ~CDockPaneBase();
	virtual void UpdateUIVisual() {}

	DECLARE_MESSAGE_MAP()
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lp);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnBeforeFloat(CRect & rectFloat, AFX_DOCK_METHOD dockMethod);
};

#define IMPLEMENT_FONT_SETTING_DOCK_WINDOW \
	LOGFONT lf; \
	memset(&lf, 0, sizeof(LOGFONT)); \
	_tcscpy_s(lf.lfFaceName, 32 * sizeof(CHAR), AppSettingMgr.m_DockWindowFontSetting._font); \
	lf.lfHeight = AppSettingMgr.m_DockWindowFontSetting._lfHeight; \
	lf.lfWeight = AppSettingMgr.m_DockWindowFontSetting._lfWeight; \
	m_Font.CreateFontIndirect(&lf);