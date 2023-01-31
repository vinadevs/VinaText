/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

class CHelpToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

/////////////////////////////////////////////////////////////////////////////
// CDynamicHelpVieBar window

class CDynamicHelpViewBar : public CDockablePane
{
// Construction
public:
	CDynamicHelpViewBar();

	void AdjustLayout();

// Attributes
protected:
	CHelpToolBar m_wndToolBar;
	CTreeCtrl m_wndArticles;
	CImageList m_DynamicHelpImages;

// Operations
public:
	void OnChangeVisualStyle();

protected:
	virtual void OnEraseWorkArea(CDC* pDC, CRect rectWorkArea);
	void FillHelp();

// Implementation
public:
	virtual ~CDynamicHelpViewBar();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDhelp1();
	afx_msg void OnUpdateDhelp1(CCmdUI* pCmdUI);
	afx_msg void OnDhelp2();
	afx_msg void OnUpdateDhelp2(CCmdUI* pCmdUI);
	afx_msg void OnDhelp3();
	afx_msg void OnUpdateDhelp3(CCmdUI* pCmdUI);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSelectTree(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
};

