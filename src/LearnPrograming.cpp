/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "VinaTextApp.h"
#include "MainFrm.h"
#include "LearnPrograming.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int idTree = 1;

/////////////////////////////////////////////////////////////////////////////
// CExplorerBar

CDynamicHelpViewBar::CDynamicHelpViewBar()
{
}

CDynamicHelpViewBar::~CDynamicHelpViewBar()
{
}

BEGIN_MESSAGE_MAP(CDynamicHelpViewBar, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//ON_COMMAND(ID_DHELP1, OnDhelp1)
	//ON_UPDATE_COMMAND_UI(ID_DHELP1, OnUpdateDhelp1)
	//ON_COMMAND(ID_DHELP2, OnDhelp2)
	//ON_UPDATE_COMMAND_UI(ID_DHELP2, OnUpdateDhelp2)
	//ON_COMMAND(ID_DHELP3, OnDhelp3)
	//ON_UPDATE_COMMAND_UI(ID_DHELP3, OnUpdateDhelp3)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_NOTIFY(TVN_SELCHANGED, idTree, OnSelectTree)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynamicHelpView message handlers

int CDynamicHelpViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowText(_T("Articles"));

	CRect rectDummy(0, 0, 0, 0);
	m_wndArticles.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |TVS_TRACKSELECT | TVS_NOTOOLTIPS | TVS_SINGLEEXPAND, rectDummy, this, idTree);

	m_DynamicHelpImages.Create(IDB_LEARN_PROGRAMING, 16, 0, RGB(249, 38, 114));
	m_wndArticles.SetImageList(&m_DynamicHelpImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_LEARN_PROGRAMING);
	m_wndToolBar.LoadToolBar(IDR_LEARN_PROGRAMING, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	FillHelp();
	AdjustLayout();
	return 0;
}

void CDynamicHelpViewBar::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CDynamicHelpViewBar::OnEraseWorkArea(CDC* /*pDC*/, CRect /*rectWorkArea*/)
{
	// Do nothing, favorites tree covers the whole working area
}

void CDynamicHelpViewBar::OnSelectTree(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
	// NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	HTREEITEM hTreeItem = m_wndArticles.GetSelectedItem();
	if (hTreeItem != NULL)
	{
	}

	*pResult = 0;
}

void CDynamicHelpViewBar::FillHelp()
{
	HTREEITEM hTreeItem = m_wndArticles.InsertItem(_T("Samples"), 0, 2, TVI_ROOT);
	m_wndArticles.SetItemData(hTreeItem, (DWORD) 1);

	hTreeItem = m_wndArticles.InsertItem(_T("Visual Studio Sample"), 5, 5, hTreeItem);
	m_wndArticles.SetItemData(hTreeItem, (DWORD) 2);

	hTreeItem = m_wndArticles.InsertItem(_T("Getting Started"), 1, 3, TVI_ROOT);
	m_wndArticles.SetItemData(hTreeItem, (DWORD) 1);

	hTreeItem = m_wndArticles.InsertItem(_T("Customizing Dynamic Help"), 5, 5, hTreeItem);
	m_wndArticles.SetItemData(hTreeItem, (DWORD) 2);
}

void CDynamicHelpViewBar::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndArticles.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CDynamicHelpViewBar::OnDhelp1()
{
	// TODO: Add your command handler code here
}

void CDynamicHelpViewBar::OnUpdateDhelp1(CCmdUI* /*pCmdUI*/)
{
	// TODO: Add your command update UI handler code here
}

void CDynamicHelpViewBar::OnDhelp2()
{
	// TODO: Add your command handler code here
}

void CDynamicHelpViewBar::OnUpdateDhelp2(CCmdUI* /*pCmdUI*/)
{
	// TODO: Add your command update UI handler code here
}

void CDynamicHelpViewBar::OnDhelp3()
{
	// TODO: Add your command handler code here
}

void CDynamicHelpViewBar::OnUpdateDhelp3(CCmdUI* /*pCmdUI*/)
{
	// TODO: Add your command update UI handler code here
}

void CDynamicHelpViewBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_wndArticles.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CDynamicHelpViewBar::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndArticles.SetFocus();
}

void CDynamicHelpViewBar::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_LEARN_PROGRAMING_TOOLBAR_24 : IDR_LEARN_PROGRAMING, 0, 0, TRUE /* Locked */);

	m_DynamicHelpImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_LEARN_PROGRAMING_24 : IDB_LEARN_PROGRAMING;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_DynamicHelpImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_DynamicHelpImages.Add(&bmp, RGB(255, 255, 255));

	m_wndArticles.SetImageList(&m_DynamicHelpImages, TVSIL_NORMAL);
}


