/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "SearchAndReplaceDlg.h"
#include "afxdialogex.h"
#include "AppUtil.h"
#include "RAIIUtils.h"
#include "AppSettings.h"
#include "EditorDoc.h"
#include "EditorView.h"

// CSearchAndReplaceWindowDlg dialog

IMPLEMENT_DYNAMIC(CSearchAndReplaceWindowDlg, CDialogEx)

CSearchAndReplaceWindowDlg::CSearchAndReplaceWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SEARCH_AND_REPLACE_DIALOG_PANE, pParent)
{
	m_pImglist = NULL;
	m_pFont = NULL;
	m_pCurrentTabShow = NULL;
	m_uiActiveTab = TABACTIVE::FIND_TAB;
}

CSearchAndReplaceWindowDlg::~CSearchAndReplaceWindowDlg()
{
	DELETE_POINTER_CPP(m_pImglist);
	DELETE_POINTER_CPP(m_pFont);
}

void CSearchAndReplaceWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_PANE_SEARCH_AND_REPLACE_TAB, m_CTabCtrl);
}

void CSearchAndReplaceWindowDlg::InitSearchReplaceFromEditor(const CString& strSearchWhat, SEARCH_REPLACE_GOTO_DLG_TYPE searchType )
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
			m_uiActiveTab = TABACTIVE::FIND_REPLACE_TAB;
			m_FindAndReplaceDlg.ShowWindow(SW_SHOW);
			m_FindAndReplaceDlg.UpdateData(FALSE);
			m_FindAndReplaceDlg.SetFocus();
			m_pCurrentTabShow = &m_FindAndReplaceDlg;
			m_FindDlg.InitSearchReplaceFromEditor(strSearchWhat);
			m_FindAndReplaceDlg.InitSearchReplaceFromEditor(strSearchWhat);
		}
	}
	else if (searchType == SEARCH_REPLACE_GOTO_DLG_TYPE::GOTO)
	{
		if (m_GotoDlg.m_hWnd != NULL)
		{
			m_CTabCtrl.SetCurSel(2);
			m_uiActiveTab = TABACTIVE::GOTO_TAB;
			m_GotoDlg.ShowWindow(SW_SHOW);
			m_GotoDlg.UpdateData(FALSE);
			m_GotoDlg.SetFocus();
			m_pCurrentTabShow = &m_GotoDlg;
			m_GotoDlg.InitGotoRangeByDocument();
			m_GotoDlg.InitGotoInfoFromEditor(strSearchWhat);
		}
	}

	UpdateData(FALSE);
}

void CSearchAndReplaceWindowDlg::SearchAllOnFileFromEditor(const CString& strSearchWhat, SEARCH_REPLACE_GOTO_DLG_TYPE searchType)
{
	if (searchType == SEARCH_REPLACE_GOTO_DLG_TYPE::SEARCH)
	{
		if (m_FindDlg.m_hWnd != NULL)
		{
			m_FindDlg.SearchAllOnFileFromEditor(strSearchWhat);
		}
	}
}

void CSearchAndReplaceWindowDlg::SearchFromEditor(const CString& strSearchWhat,
	SEARCH_TYPE searchType, BOOL bSeacrhNext, BOOL bHideMessageBox, BOOL bSaveSearchWord)
{
	if (m_FindDlg.m_hWnd != NULL)
	{
		m_FindDlg.SearchFromEditor(strSearchWhat, searchType, bSeacrhNext, bHideMessageBox, bSaveSearchWord);
	}
	if (bSaveSearchWord)
	{
		if (m_FindAndReplaceDlg.m_hWnd != NULL)
		{
			m_FindAndReplaceDlg.SaveSearchString(strSearchWhat);
		}
	}
}

void CSearchAndReplaceWindowDlg::InitSearchReplaceFromExplorer(const CString& strFolderPath, SEARCH_REPLACE_GOTO_DLG_TYPE searchType)
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
			m_FindDlg.InitSearchReplaceFromExplorer(strFolderPath);
			m_FindAndReplaceDlg.InitSearchReplaceFromExplorer(strFolderPath);
			m_FindDlg.SetFocusComboSearchWhat();
		}
	}
	else if (searchType == SEARCH_REPLACE_GOTO_DLG_TYPE::REPLACE)
	{
		if (m_FindAndReplaceDlg.m_hWnd != NULL)
		{
			m_CTabCtrl.SetCurSel(0);
			m_uiActiveTab = TABACTIVE::FIND_REPLACE_TAB;
			m_FindAndReplaceDlg.ShowWindow(SW_SHOW);
			m_FindAndReplaceDlg.UpdateData(FALSE);
			m_FindAndReplaceDlg.SetFocus();
			m_pCurrentTabShow = &m_FindAndReplaceDlg;
			m_FindDlg.InitSearchReplaceFromExplorer(strFolderPath);
			m_FindAndReplaceDlg.InitSearchReplaceFromExplorer(strFolderPath);
		}
	}
}

void CSearchAndReplaceWindowDlg::UpdateFoldingMap(BOOL bActiveDialogTab)
{
	if (bActiveDialogTab)
	{
		if (m_pCurrentTabShow != NULL)
		{
			m_pCurrentTabShow->ShowWindow(SW_HIDE);
			m_pCurrentTabShow = NULL;
		}

		if (m_BracketOutLineDlg.m_hWnd != NULL)
		{
			m_CTabCtrl.SetCurSel(3);
			m_uiActiveTab = TABACTIVE::BRACKET_OUTLINE_TAB;
			m_BracketOutLineDlg.ShowWindow(SW_SHOW);
			m_BracketOutLineDlg.UpdateData(FALSE);
			m_BracketOutLineDlg.SetFocus();
			m_pCurrentTabShow = &m_BracketOutLineDlg;
			m_BracketOutLineDlg.UpdateFoldingMap(DEFAULT_FOLDONG_MAP_LEVEL);
		}
	}
	else
	{
		if (m_BracketOutLineDlg.m_hWnd != NULL)
		{
			m_BracketOutLineDlg.UpdateFoldingMap(DEFAULT_FOLDONG_MAP_LEVEL);
		}
	}
}

void CSearchAndReplaceWindowDlg::UpdateGotoRange(BOOL bActiveDialogTab)
{
	if (bActiveDialogTab)
	{
		if (m_pCurrentTabShow != NULL)
		{
			m_pCurrentTabShow->ShowWindow(SW_HIDE);
			m_pCurrentTabShow = NULL;
		}
		if (m_BracketOutLineDlg.m_hWnd != NULL)
		{
			m_CTabCtrl.SetCurSel(2);
			m_uiActiveTab = TABACTIVE::GOTO_TAB;
			m_GotoDlg.ShowWindow(SW_SHOW);
			m_GotoDlg.UpdateData(FALSE);
			m_GotoDlg.SetFocus();
			m_pCurrentTabShow = &m_GotoDlg;
		}
	}
	else
	{
		if (m_GotoDlg.m_hWnd != NULL)
		{
			m_GotoDlg.InitGotoRangeByDocument();
		}
	}
}

void CSearchAndReplaceWindowDlg::SaveDialogState()
{
	m_FindDlg.SaveDialogState();
	m_FindAndReplaceDlg.SaveDialogState();
}

void CSearchAndReplaceWindowDlg::ClearAll()
{
	if (m_FindDlg.m_hWnd != NULL && m_FindAndReplaceDlg.m_hWnd != NULL
		&& m_GotoDlg.m_hWnd != NULL && m_BracketOutLineDlg.m_hWnd != NULL)
	{
		m_FindDlg.ClearAll();
		m_FindAndReplaceDlg.ClearAll();
		m_GotoDlg.ClearAll();
		m_BracketOutLineDlg.ClearAll();
	}
}

BEGIN_MESSAGE_MAP(CSearchAndReplaceWindowDlg, CDialogEx)
	ON_WM_MOVING()
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, ID_PANE_SEARCH_AND_REPLACE_TAB, &CSearchAndReplaceWindowDlg::OnTcnSelchangeTab)
END_MESSAGE_MAP()

// CSearchAndReplaceWindowDlg message handlers

void CSearchAndReplaceWindowDlg::OnMoving(UINT nSide, LPRECT lpRect)
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

void CSearchAndReplaceWindowDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (!cx || !cy) return;
	int dx = cx - m_SaveRect.right;
	int dy = cy - m_SaveRect.bottom;
	CLockCtrlRedraw locker(this);
	OffsetChildWindow(GetDlgItem(ID_PANE_SEARCH_AND_REPLACE_TAB), 0, cy, dx, dy);
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
	if (m_GotoDlg.m_hWnd != NULL)
	{
		m_GotoDlg.MoveWindow(0, 25, cx, cy);
	}
	if (m_BracketOutLineDlg.m_hWnd != NULL)
	{
		m_BracketOutLineDlg.MoveWindow(0, 25, cx, cy);
	}
	GetClientRect(&m_SaveRect);
}

BOOL CSearchAndReplaceWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetClientRect(&m_SaveRect);

	UINT nMenuf = (MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu)
	{
		pSysMenu->EnableMenuItem(SC_CLOSE, nMenuf);
	}

	m_pImglist = new CImageList();
	m_pImglist->Create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 3);
	m_pImglist->Add(AfxGetApp()->LoadIcon(IDR_SEARCH));
	m_pImglist->Add(AfxGetApp()->LoadIcon(IDR_REPLACE));
	m_pImglist->Add(AfxGetApp()->LoadIcon(IDR_GOTO));
	m_pImglist->Add(AfxGetApp()->LoadIcon(IDR_BRACKETS_OUTLINE));
	m_CTabCtrl.SetImageList(m_pImglist);

	m_CTabCtrl.InsertItem(0, _T("Search In Files"), 0);
	m_CTabCtrl.InsertItem(1, _T("Replace In Files"), 1);
	m_CTabCtrl.InsertItem(3, _T("Goto"), 2);
	m_CTabCtrl.InsertItem(4, _T("Folding Map"), 3);

	m_pFont = new CFont();
	m_pFont->CreatePointFont(100, _T("Tahoma"));
	GetDlgItem(ID_PANE_SEARCH_AND_REPLACE_TAB)->SetFont(m_pFont, TRUE);

	CRect rect;
	m_CTabCtrl.GetClientRect(&rect);

	// find dialog
	m_FindDlg.Create(IDD_FIND, &m_CTabCtrl);
	m_FindDlg.SetWindowPos(NULL, 2, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_FindDlg.ShowWindow(SW_SHOW);
	m_pCurrentTabShow = &m_FindDlg;

	// replace dialog
	m_FindAndReplaceDlg.Create(IDD_REPLACE, &m_CTabCtrl);
	m_FindAndReplaceDlg.SetWindowPos(NULL, 2, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_FindAndReplaceDlg.ShowWindow(SW_HIDE);

	// goto dialog
	m_GotoDlg.Create(IDD_POS, &m_CTabCtrl);
	m_GotoDlg.SetWindowPos(NULL, 2, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_GotoDlg.ShowWindow(SW_HIDE);

	// bracket outline dialog
	m_BracketOutLineDlg.Create(IDD_BRACKET_OUTLINE, &m_CTabCtrl);
	m_BracketOutLineDlg.SetWindowPos(NULL, 2, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_BracketOutLineDlg.ShowWindow(SW_HIDE);

	UpdateData(FALSE);
	//attemted an unsupported operation
	return TRUE;  // return TRUE unless you set the focus to a control 
				  // EXCEPTION: OCX Property Pages should return FALSE 
}

void CSearchAndReplaceWindowDlg::OnTcnSelchangeTab(NMHDR * pNMHDR, LRESULT * pResult)
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
		m_FindDlg.SyncSearchReplaceSettings(m_FindAndReplaceDlg.GetSycnFindReplaceSettings());
		break;
	case 1:
		m_uiActiveTab = TABACTIVE::FIND_REPLACE_TAB;
		m_FindAndReplaceDlg.ShowWindow(SW_SHOW);
		m_FindAndReplaceDlg.UpdateData(FALSE);
		m_FindAndReplaceDlg.SetFocus();
		m_pCurrentTabShow = &m_FindAndReplaceDlg;
		m_FindAndReplaceDlg.SyncSearchReplaceSettings(m_FindDlg.GetSycnFindReplaceSettings());
		break;
	case 2:
		m_uiActiveTab = TABACTIVE::GOTO_TAB;
		m_GotoDlg.ShowWindow(SW_SHOW);
		m_GotoDlg.UpdateData(FALSE);
		m_GotoDlg.SetFocus();
		m_GotoDlg.InitGotoRangeByDocument();
		m_pCurrentTabShow = &m_GotoDlg;
		break;
	case 3:
		m_uiActiveTab = TABACTIVE::BRACKET_OUTLINE_TAB;
		m_BracketOutLineDlg.ShowWindow(SW_SHOW);
		m_BracketOutLineDlg.UpdateData(FALSE);
		m_BracketOutLineDlg.SetFocus();
		m_pCurrentTabShow = &m_BracketOutLineDlg;
		break;
	}
	*pResult = 0;

	UpdateData(FALSE);
}

CString CSearchAndReplaceWindowDlg::GetSearchWhat()
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

unsigned int CSearchAndReplaceWindowDlg::GetSearchOption()
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

void CSearchAndReplaceWindowDlg::UpdateUIVisual()
{
	m_FindDlg.UpdateUIVisual();
	m_FindAndReplaceDlg.UpdateUIVisual();
	m_GotoDlg.UpdateUIVisual();
	m_BracketOutLineDlg.UpdateUIVisual();
}
