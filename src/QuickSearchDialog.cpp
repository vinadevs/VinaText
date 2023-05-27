/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "resource.h"
#include "QuickSearchDialog.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "EditorDoc.h"
#include "EditorView.h"
#include "AppUtil.h"
#include "RAIIUtils.h"
#include "AppSettings.h"

// CQuickSearchDialog dialog

IMPLEMENT_DYNAMIC(CQuickSearchDialog, CDialogEx)

CQuickSearchDialog::CQuickSearchDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_QUICK_SEARCH_AND_REPLACE, pParent)
{
	m_pImglist = NULL;
	m_pFont = NULL;
	m_pCurrentTabShow = NULL;
	m_pEditorDoc = NULL;
	m_uiActiveTab = TABACTIVE::FIND_TAB;
}

CQuickSearchDialog::~CQuickSearchDialog()
{
	DELETE_POINTER_CPP(m_pImglist);
	DELETE_POINTER_CPP(m_pFont);
	m_pEditorDoc = NULL;
	RenderIndicatorWordsAndCount(_T(""), 0);
}

void CQuickSearchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_QUICK_SEARCH, m_CTabCtrl);
}

BEGIN_MESSAGE_MAP(CQuickSearchDialog, CDialogEx)
	ON_WM_MOVING()
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_QUICK_SEARCH, &CQuickSearchDialog::OnTcnSelchangeTab)
END_MESSAGE_MAP()

// CQuickSearchDialog message handlers

void CQuickSearchDialog::PostNcDestroy()
{
	/*Close & Delete a modeless Dialogs.
	A proper Way is : Override PostNcDestroy, OnOk() and OnCancel() for the Modeless Dialogs*/
	CDialogEx::PostNcDestroy();
	delete this;
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;
	pFrame->ReleaseQuickSearchDialog();
}

void CQuickSearchDialog::OnCancel()
{
	SaveDialogState();
	CDialogEx::DestroyWindow();
}

void CQuickSearchDialog::SetParentDocument(CEditorDoc * pEditorDoc)
{
	if (m_pEditorDoc)
	{
		CEditorView* pView = m_pEditorDoc->GetEditorView();
		if (pView)
		{
			pView->RenderIndicatorWordsAndCount(_T(""), 0, FALSE);
		}
	}
	m_pEditorDoc = pEditorDoc;
}

void CQuickSearchDialog::InitSearchReplaceFromEditor(const CString & strSearchWhat, SEARCH_REPLACE_GOTO_DLG_TYPE searchType)
{
	if (m_pCurrentTabShow != NULL)
	{
		m_pCurrentTabShow->ShowWindow(SW_HIDE);
		m_pCurrentTabShow = NULL;
	}

	if (searchType == SEARCH_REPLACE_GOTO_DLG_TYPE::SEARCH)
	{
		if (m_FindDlg.m_hWnd != NULL)
		{
			m_CTabCtrl.SetCurSel(0);
			m_uiActiveTab = TABACTIVE::FIND_TAB;
			m_FindDlg.ShowWindow(SW_SHOW);
			m_FindDlg.UpdateData(FALSE);
			m_FindDlg.SetFocus();
			m_pCurrentTabShow = &m_FindDlg;
			m_FindDlg.InitSearchReplaceFromEditor(strSearchWhat);
			m_FindAndReplaceDlg.InitSearchReplaceFromEditor(strSearchWhat);
			m_FindDlg.SetFocusComboSearchWhat();
		}
	}
	else if (searchType == SEARCH_REPLACE_GOTO_DLG_TYPE::REPLACE)
	{
		if (m_FindAndReplaceDlg.m_hWnd != NULL)
		{
			m_CTabCtrl.SetCurSel(1);
			m_uiActiveTab = TABACTIVE::REPLACE_TAB;
			m_FindAndReplaceDlg.ShowWindow(SW_SHOW);
			m_FindAndReplaceDlg.UpdateData(FALSE);
			m_FindAndReplaceDlg.SetFocus();
			m_pCurrentTabShow = &m_FindAndReplaceDlg;
			m_FindDlg.InitSearchReplaceFromEditor(strSearchWhat);
			m_FindAndReplaceDlg.InitSearchReplaceFromEditor(strSearchWhat);
		}
	}

	UpdateData(FALSE);
}

CString CQuickSearchDialog::GetSearchWhat()
{
	auto tabIndex = m_CTabCtrl.GetCurSel();
	CString strSearchWhat;
	switch (tabIndex)
	{
	case 0:
		strSearchWhat = m_FindDlg.GetSearchWhat();
		break;
	case 1:
		strSearchWhat = m_FindAndReplaceDlg.GetSearchWhat();
		break;
	}
	return strSearchWhat;
}

unsigned int CQuickSearchDialog::GetSearchOption()
{
	auto tabIndex = m_CTabCtrl.GetCurSel();
	unsigned int uiSearchOption;
	switch (tabIndex)
	{
	case 0:
		uiSearchOption = m_FindDlg.GetSearchOption();
		break;
	case 1:
		uiSearchOption = m_FindAndReplaceDlg.GetSearchOption();
		break;
	}
	return uiSearchOption;
}

void CQuickSearchDialog::SaveDialogState()
{
	m_FindDlg.SaveDialogState();
	m_FindAndReplaceDlg.SaveDialogState();
}

BOOL CQuickSearchDialog::OnInitDialog()
{
	// set initial position as active editor
	CEditorDoc* pEditorActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pEditorActiveDoc)
	{
		CEditorCtrl* pEditor = pEditorActiveDoc->GetEditorCtrl();
		if (pEditor)
		{
			CRect rect;
			GetWindowRect(rect);
			int dx = rect.Width();
			int dy = rect.Height();
			pEditor->GetWindowRect(rect);
			int wEditor = rect.Width();
			int hEditor = rect.Height();
			if (pEditor->IsVerticalScrollBarVisible())
			{
				rect.right = rect.right - MARGIN_EDITOR_SCROLLBAR;
			}
			rect.left = rect.right - dx;
			rect.bottom = rect.top + dy;
			MoveWindow(rect);
		}
	}

	CDialogEx::OnInitDialog();

	GetClientRect(&m_SaveRect);

	UINT nMenuf = (MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu)
	{
		pSysMenu->EnableMenuItem(SC_CLOSE, nMenuf);
	}

	m_pImglist = new CImageList();
	m_pImglist->Create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 2);
	m_pImglist->Add(AfxGetApp()->LoadIcon(IDR_SEARCH));
	m_pImglist->Add(AfxGetApp()->LoadIcon(IDR_REPLACE));
	m_CTabCtrl.SetImageList(m_pImglist);

	m_CTabCtrl.InsertItem(0, _T("     Search     "), 0);
	m_CTabCtrl.InsertItem(1, _T("     Replace     "), 1);

	m_pFont = new CFont();
	m_pFont->CreatePointFont(100, _T("Tahoma"));
	GetDlgItem(IDC_TAB_QUICK_SEARCH)->SetFont(m_pFont, TRUE);

	CRect rect;
	m_CTabCtrl.GetClientRect(&rect);

	// find dialog
	m_FindDlg.Create(IDD_DLG_QUICK_SEARCH, &m_CTabCtrl);
	m_FindDlg.SetWindowPos(NULL, 0, 23, rect.Width(), rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
	m_FindDlg.ShowWindow(SW_SHOW);
	m_pCurrentTabShow = &m_FindDlg;

	// replace dialog
	m_FindAndReplaceDlg.Create(IDD_DIALOG_QUICK_REPLACE, &m_CTabCtrl);
	m_FindAndReplaceDlg.SetWindowPos(NULL, 0, 23, rect.Width(), rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
	m_FindAndReplaceDlg.ShowWindow(SW_HIDE);

	UpdateData(FALSE);
	//attemted an unsupported operation
	return TRUE;  // return TRUE unless you set the focus to a control 
				  // EXCEPTION: OCX Property Pages should return FALSE 
}

void CQuickSearchDialog::OnTcnSelchangeTab(NMHDR * pNMHDR, LRESULT * pResult)
{
	// TODO: Add your control notification handler code here
	if (m_pCurrentTabShow != NULL)
	{
		m_pCurrentTabShow->ShowWindow(SW_HIDE);
		m_pCurrentTabShow = NULL;
	}

	auto tabIndex = m_CTabCtrl.GetCurSel();

	switch (tabIndex)
	{
	case 0:
		m_uiActiveTab = TABACTIVE::FIND_TAB;
		m_FindDlg.ShowWindow(SW_SHOW);
		m_FindDlg.UpdateData(FALSE);
		m_FindDlg.SetFocus();
		m_pCurrentTabShow = &m_FindDlg;
		m_FindDlg.InitSearchReplaceFromEditor(m_FindAndReplaceDlg.GetSearchWhat());
		RenderIndicatorWordsAndCount(m_FindDlg.GetSearchWhat(), m_FindDlg.GetSearchOption());
		break;
	case 1:
		m_uiActiveTab = TABACTIVE::REPLACE_TAB;
		m_FindAndReplaceDlg.ShowWindow(SW_SHOW);
		m_FindAndReplaceDlg.UpdateData(FALSE);
		m_FindAndReplaceDlg.SetFocus();
		m_pCurrentTabShow = &m_FindAndReplaceDlg;
		m_FindAndReplaceDlg.InitSearchReplaceFromEditor(m_FindDlg.GetSearchWhat());
		RenderIndicatorWordsAndCount(m_FindAndReplaceDlg.GetSearchWhat(), m_FindAndReplaceDlg.GetSearchOption());
		break;
	}
	*pResult = 0;

	UpdateData(FALSE);
}

void CQuickSearchDialog::OnMoving(UINT nSide, LPRECT lpRect)
{
	CDialogEx::OnMoving(nSide, lpRect);
	// Find Current location of the dialog
	CRect CurRect;
	GetWindowRect(&CurRect);
	// Set current location as the moving location
	lpRect->left = CurRect.left;
	lpRect->top = CurRect.top;
	lpRect->right = CurRect.right;
	lpRect->bottom = CurRect.bottom;
}

static void OffsetChildWindow(CWnd* child, int dx, int dy, int dw, int dh)
{
	if (!child) return;
	if (!child->GetParent()) return;
	if (!IsWindow(child->m_hWnd)) return;
	// Find child window's coordinates relative to top-left of parent
	CRect cRec;
	child->GetWindowRect(&cRec);
	CPoint cPoint(0, 0);
	ScreenToClient(child->GetParent()->GetSafeHwnd(), &cPoint);
	cRec.OffsetRect(cPoint);
	// Prevent negative size
	if ((cRec.Width() + dw) < 0) dw = -cRec.Width();
	if ((cRec.Height() + dh) < 0) dh = -cRec.Height();
	child->SetWindowPos(0, cRec.left + dx, cRec.top + dy, cRec.Width() + dw, cRec.Height() + dh, SWP_NOZORDER);
	child->Invalidate(FALSE);
}

void CQuickSearchDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (!cx || !cy) return;
	int dx = cx - m_SaveRect.right;
	int dy = cy - m_SaveRect.bottom;
	CLockCtrlRedraw locker(this);
	OffsetChildWindow(GetDlgItem(IDC_TAB_QUICK_SEARCH), 0, cy, dx, dy);
	if (m_CTabCtrl.m_hWnd != NULL)
	{
		m_CTabCtrl.MoveWindow(0, 0, cx, cy);
	}
	if (m_FindDlg.m_hWnd != NULL)
	{
		m_FindDlg.MoveWindow(0, 25, cx, cy);
	}
	if (m_FindAndReplaceDlg.m_hWnd != NULL)
	{
		m_FindAndReplaceDlg.MoveWindow(0, 25, cx, cy);
	}
	GetClientRect(&m_SaveRect);
}

void CQuickSearchDialog::RenderIndicatorWordsAndCount(const CString& strSearchWhat, int nSearchOption)
{
	CEditorView* pView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
	if (pView)
	{
		pView->RenderIndicatorWordsAndCount(strSearchWhat, nSearchOption);
	}
}