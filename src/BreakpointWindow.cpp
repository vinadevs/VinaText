/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "BreakpointWindow.h"
#include "VinaTextApp.h"
#include "MainFrm.h"
#include "EditorDoc.h"
#include "EditorView.h"
#include "AppUtil.h"
#include "RAIIUtils.h"
#include "AppSettings.h"
#include "FileUtil.h"
#include "translator/POHandler.h"

#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CBreakpointWindow, CDockPaneBase)

CBreakpointWindow::CBreakpointWindow()
{
}

CBreakpointWindow::~CBreakpointWindow()
{
}

BEGIN_MESSAGE_MAP(CBreakpointWindow, CDockPaneBase)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(UMW_DOCK_PANE_UPDATE, &CBreakpointWindow::OnDockPaneUpdate)
END_MESSAGE_MAP()

LRESULT CBreakpointWindow::OnDockPaneUpdate(WPARAM wParam, LPARAM lParam)
{
	WORD wMsgTarget = LOWORD(wParam);
	WORD wMsgHint = HIWORD(wParam);

	if (MAIN_FRAME_UPDATE_MSG::MAIN_FRAME_UPDATE_ALL_DOCKPANE == wMsgTarget)
	{
		switch (wMsgHint)
		{
		case MAIN_FRAME_UPDATE_HINT::MAIN_FRAME_UPDATE_HINT_SETTING_CHANGED:
		{
			UpdateUIVisual();
		}
		break;
		}
	}
	return 0L;
}

int CBreakpointWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockPaneBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_BreakpointPaneDlg.Create(IDD_SEARCH_RESULT_DLG, this))
	{
		TRACE0("Failed to create output dialog windows\n");
		return -1;      // fail to create
	}
	m_BreakpointPaneDlg.ShowWindow(SW_SHOW);
	return 0;
}

void CBreakpointWindow::OnSize(UINT nType, int cx, int cy)
{
	CDockPaneBase::OnSize(nType, cx, cy);
	m_BreakpointPaneDlg.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CBreakpointWindow::AddBreakpointData(const BREAKPOINT_LINE_DATA & data)
{
	m_BreakpointPaneDlg.AddBreakpointData(data);
}

void CBreakpointWindow::ClearAll()
{
	m_BreakpointPaneDlg.ClearBreakpointData();
}

void CBreakpointWindow::UpdateUIVisual()
{
	m_BreakpointPaneDlg.UpdateDlgFont();
	m_BreakpointPaneDlg.UpdateListCtrlVisual();
}

/////////////////////////////////////////////////////////////////////////////
// CBreakpointDlg dialog

IMPLEMENT_DYNAMIC(CBreakpointDlg, CDialogEx)

CBreakpointDlg::CBreakpointDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SEARCH_RESULT_DLG, pParent)
{
	UpdateDlgFont();
}

CBreakpointDlg::~CBreakpointDlg()
{
}

BEGIN_MESSAGE_MAP(CBreakpointDlg, CDialogEx)
	ON_WM_MOVING()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_SEARCH_RESULT, OnGetdispinfoList)
	ON_NOTIFY(LVN_ODFINDITEM, IDC_LIST_SEARCH_RESULT, OnOdfinditemList)
	ON_NOTIFY(LVN_ODCACHEHINT, IDC_LIST_SEARCH_RESULT, OnOdcachehintList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SEARCH_RESULT, OnItemchangedList)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SEARCH_RESULT, OnClickList)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_SEARCH_RESULT, OnKeydownList)
END_MESSAGE_MAP()

// CBreakpointDlg message handlers

void CBreakpointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SEARCH_RESULT, m_wndBreakpointList);
}

void CBreakpointDlg::UpdateDlgFont()
{
	IMPLEMENT_FONT_SETTING_DOCK_WINDOW
}

void CBreakpointDlg::AddBreakpointData(const BREAKPOINT_LINE_DATA & data)
{
	if (data._bDeleteFromList)
	{
		m_BreakpointData.erase(std::remove_if(
			m_BreakpointData.begin(),
			m_BreakpointData.end(),
			[&](BREAKPOINT_LINE_DATA const & internalData)
		{
			return internalData._strTargetFile.CompareNoCase(data._strTargetFile) == 0
				&& internalData._nLineNumber == data._nLineNumber;
		}),
			m_BreakpointData.end());
	}
	else
	{
		m_BreakpointData.push_back(data);
	}
	//Resize the list to add the elements to the list
	ListView_SetExtendedListViewStyle(m_wndBreakpointList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndBreakpointList.SetItemCount(static_cast<int>(m_BreakpointData.size()));
}

void CBreakpointDlg::ClearBreakpointData()
{
	// update editor
	for (auto const& data : m_BreakpointData)
	{
		auto pOpenedDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetExistedDocument(data._strTargetFile));
		if (pOpenedDoc)
		{
			CEditorView* pView = pOpenedDoc->GetEditorView();
			if (pView)
			{
				CEditorCtrl* pEditor = pView->GetEditorCtrl();
				if (pEditor)
				{
					pEditor->DeleteBreakPoint(pView->GetCurrentDocLanguague(), data._nLineNumber, data._strTargetFile);
				}
			}
		}
	}
	m_BreakpointData.clear();
	BREAKPOINT_LINE_DATA_LIST().swap(m_BreakpointData);
	//Resize the list to add the elements to the list
	ListView_SetExtendedListViewStyle(m_wndBreakpointList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndBreakpointList.SetItemCount(0);
	m_wndBreakpointList.DeleteAllItems();
}

void CBreakpointDlg::ClearSelectedBreakpoint()
{
	if (m_wndBreakpointList.GetItemCount() == 0) return;
	CString strItem = m_wndBreakpointList.GetSelectedItemsText();
	if (!strItem.IsEmpty())
	{
		int nPos1 = strItem.Find(_T("|"));
		CString strLineNumber = strItem.Mid(0, nPos1).Trim();
		int nLineNumber = AppUtils::CStringToInt(strLineNumber);
		CString strRemain = strItem.Mid(nPos1 + 1).Trim();
		int nPos2 = strRemain.Find(_T("|"));
		CString strFileTarget = strRemain.Mid(0, nPos2).Trim();
		strFileTarget.Replace(_T("\""), _T(""));
		if (PathFileExists(strFileTarget))
		{
			// update list
			m_BreakpointData.erase(std::remove_if(
				m_BreakpointData.begin(),
				m_BreakpointData.end(),
				[&](BREAKPOINT_LINE_DATA const & internalData)
			{
				return internalData._strTargetFile.CompareNoCase(strFileTarget) == 0
					&& internalData._nLineNumber == nLineNumber;
			}),
				m_BreakpointData.end());
			//Resize the list to add the elements to the list
			ListView_SetExtendedListViewStyle(m_wndBreakpointList.m_hWnd, LVS_EX_FULLROWSELECT);
			m_wndBreakpointList.SetItemCount(static_cast<int>(m_BreakpointData.size()));
			// update editor
			auto pOpenedDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetExistedDocument(strFileTarget));
			if (pOpenedDoc)
			{
				CEditorView* pView = pOpenedDoc->GetEditorView();
				if (pView)
				{
					CEditorCtrl* pEditor = pView->GetEditorCtrl();
					if (pEditor)
					{
						pEditor->DeleteBreakPoint(pView->GetCurrentDocLanguague(), nLineNumber, strFileTarget);
					}
				}
			}
		}
		else
		{
			AfxMessageBox(_T("[Delete Error] Breakpoint path does not exist!"));
		}

	}
}

void CBreakpointDlg::OnMoving(UINT nSide, LPRECT lpRect)
{
	CDialogEx::OnMoving(nSide, lpRect);
	CRect CurRect;
	GetWindowRect(&CurRect);
	lpRect->left = CurRect.left;
	lpRect->top = CurRect.top;
	lpRect->right = CurRect.right;
	lpRect->bottom = CurRect.bottom;
}

void CBreakpointDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (!cx || !cy) return;
	CRect rectClient;
	GetClientRect(rectClient);
	if (m_wndBreakpointList.GetSafeHwnd())
	{
		m_wndBreakpointList.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void CBreakpointDlg::OnOK()
{
}

void CBreakpointDlg::OnCancel()
{
}

BOOL CBreakpointDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UINT nMenuf = MF_BYCOMMAND | MF_GRAYED | MF_DISABLED;
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu)
	{
		pSysMenu->EnableMenuItem(SC_CLOSE, nMenuf);
	}
	InitListCtrl();
	return TRUE;
}

//This function is called when the list needs data. This is the most
//critical function when working with virtual lists.
void CBreakpointDlg::OnGetdispinfoList(NMHDR * pNMHDR, LRESULT * pResult)
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	//Create a pointer to the item
	LV_ITEM* pItem = &(pDispInfo)->item;
	//Which item number?
	int itemid = pItem->iItem;

	//Do the list need text information?
	if (pItem->mask & LVIF_TEXT)
	{
		CString text;
		//Which column?
		if (pItem->iSubItem == 0)
		{
			//Text is _nLineNumber
			text = AppUtils::IntToCString(m_BreakpointData[itemid]._nLineNumber);
		}
		else if (pItem->iSubItem == 1)
		{
			//Text is _strTargetFile
			text = m_BreakpointData[itemid]._strTargetFile;
		}
		else if (pItem->iSubItem == 2)
		{
			//Text is _strLine
			text = m_BreakpointData[itemid]._strLine;
			// remove junks from result, make it beautiful...
			text = AppUtils::RemoveJunkFromCString(text);
		}
		else if (pItem->iSubItem == 3)
		{
			//Text is _strTargetFile
			text = m_BreakpointData[itemid]._strTargetLanguage;
		}
		else if (pItem->iSubItem == 4)
		{
			//Text is _strTargetFile
			text = m_BreakpointData[itemid]._strProcessName;
		}
		//Copy the text to the LV_ITEM structure
		//Maximum number of characters is in pItem->cchTextMax
		lstrcpyn(pItem->pszText, text, pItem->cchTextMax);
	}
	////Do the list need image information?
	//if (pItem->mask & LVIF_IMAGE)
	//{
	//	//Set which image to use
	//	pItem->iImage = m_DisplayResultSearchData[itemid].m_image;

	//	//Show check box?
	//	if (IsCheckBoxesVisible())
	//	{
	//		//To enable check box, we have to enable state mask...
	//		pItem->mask |= LVIF_STATE;
	//		pItem->stateMask = LVIS_STATEIMAGEMASK;

	//		if (m_DisplayResultSearchData[itemid].m_checked)
	//		{
	//			//Turn check box on..
	//			pItem->state = INDEXTOSTATEIMAGEMASK(2);
	//		}
	//		else
	//		{
	//			//Turn check box off
	//			pItem->state = INDEXTOSTATEIMAGEMASK(1);
	//		}
	//	}
	//}
	*pResult = 0;
}

//This functions is called when the user "writes" in the list box to find an item.
void CBreakpointDlg::OnOdfinditemList(NMHDR * pNMHDR, LRESULT * pResult)
{
	// pNMHDR has information about the item we should find
	// In pResult we should save which item that should be selected
	NMLVFINDITEM* pFindInfo = (NMLVFINDITEM*)pNMHDR;

	/* pFindInfo->iStart is from which item we should search.
	We search to bottom, and then restart at top and will stop
	at pFindInfo->iStart, unless we find an item that match
	*/

	// Set the default return value to -1
	// That means we didn't find any match.
	*pResult = -1;

	//Is search NOT based on string?
	if ((pFindInfo->lvfi.flags & LVFI_STRING) == 0)
	{
		//This will probably never happend...
		return;
	}

	//This is the string we search for
	CString searchstr = pFindInfo->lvfi.psz;

	//	TRACE(_T("Find: %s\n"), searchstr);

	int startPos = pFindInfo->iStart;
	//Is startPos outside the list (happens if last item is selected)
	if (startPos >= m_wndBreakpointList.GetItemCount())
		startPos = 0;
	int currentPos = startPos;

	////Let's search...
	do
	{
		//Do this word begins with all characters in searchstr?
		if (m_BreakpointData[currentPos]._strTargetFile.Find(searchstr) != -1)
		{
			//Select this item and stop search.
			*pResult = currentPos;
			break;
		}
		//Go to next item
		currentPos++;
		//Need to restart at top?
		if (currentPos >= m_wndBreakpointList.GetItemCount())
			currentPos = 0;
		//Stop if back to start
	} while (currentPos != startPos);
}

//This is called to give you a chance to catch data. Useless in most cases
void CBreakpointDlg::OnOdcachehintList(NMHDR * pNMHDR, LRESULT * pResult)
{
	NMLVCACHEHINT* pCacheHint = (NMLVCACHEHINT*)pNMHDR;
	/*	TRACE(	_T("Chache item %d to item %d\n"),
	pCacheHint->iFrom,
	pCacheHint->iTo );*/
	//... cache the data pCacheHint->iFrom to pCacheHint->iTo ...
	*pResult = 0;
}

//This is called when user clicks on the list. 
//If you had check box you have to write code to make them possible to toggle.
void CBreakpointDlg::OnClickList(NMHDR * pNMHDR, LRESULT * pResult)
{
	NMLISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	LVHITTESTINFO hitinfo;
	//Copy click point
	hitinfo.pt = pNMListView->ptAction;
	//Make the hit test...
	int item = m_wndBreakpointList.HitTest(&hitinfo);

	if (item != -1)
	{
		//We hit one item... did we hit state image (check box)?
		//This test only works if we are in list or report mode.
		if ((hitinfo.flags & LVHT_ONITEMSTATEICON) != 0)
		{
		}
	}
	*pResult = 0;
}

//This is called when a key i pressed down
void CBreakpointDlg::OnKeydownList(NMHDR * pNMHDR, LRESULT * pResult)
{
	LV_KEYDOWN* pLVKeyDown = (LV_KEYDOWN*)pNMHDR;
	//If user press space, toggle flag on selected item
	if (pLVKeyDown->wVKey == VK_SPACE)
	{
	}
	*pResult = 0;
}

void CBreakpointDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if ((pNMListView->uChanged & LVIF_STATE) && (pNMListView->uNewState & LVIS_SELECTED))
	{
		m_wndBreakpointList.OnOutputGotoLine();
	}
}

void CBreakpointDlg::InitListCtrl()
{
	ListView_SetExtendedListViewStyle(m_wndBreakpointList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndBreakpointList.InsertColumn(0, _T("Line Number"), LVCFMT_LEFT, 100);
	m_wndBreakpointList.InsertColumn(1, _T("File Path"), LVCFMT_LEFT, 400);
	m_wndBreakpointList.InsertColumn(2, _T("Line Text"), LVCFMT_LEFT, 400);
	m_wndBreakpointList.InsertColumn(3, _T("Language"), LVCFMT_LEFT, 200);
	m_wndBreakpointList.InsertColumn(4, _T("Process"), LVCFMT_LEFT, 200);
	UpdateListCtrlVisual();
}

void CBreakpointDlg::UpdateListCtrlVisual()
{
	m_wndBreakpointList.SetFont(&m_Font);
	m_wndBreakpointList.SetBkColor(AppSettingMgr.m_ThemeColor);
	m_wndBreakpointList.SetTextColor(IS_LIGHT_THEME ? BasicColors::black : BasicColors::white);
	m_wndBreakpointList.SetTextBkColor(AppSettingMgr.m_ThemeColor);
}

/////////////////////////////////////////////////////////////////////////////
// CBreakpointList

IMPLEMENT_DYNAMIC(CBreakpointList, CListCtrl)

CBreakpointList::CBreakpointList()
{
}

CBreakpointList::~CBreakpointList()
{
}

CString CBreakpointList::GetSelectedItemsText()
{
	CString strSelectedItemsText;
	int nColumns = GetHeaderCtrl()->GetItemCount();
	POSITION pos = GetFirstSelectedItemPosition();
	while (pos)
	{
		int nItem = GetNextSelectedItem(pos);
		CString strFullLineText;
		for (int i = 0; i < nColumns; i++)
		{
			if (i != nColumns - 1)
				strFullLineText += GetItemText(nItem, i).Trim() + _T(" | ");
			else
				strFullLineText += GetItemText(nItem, i).Trim();
		}
		if (strFullLineText.IsEmpty()) continue;
		strSelectedItemsText += strFullLineText + EDITOR_NEW_LINE;
	}
	return strSelectedItemsText;
}

CString CBreakpointList::GetItemsText()
{
	CString strSelectedItemsText;
	int nColumns = GetHeaderCtrl()->GetItemCount();
	CString strPreviousTargetFile;
	for (int nItem = 0; nItem < GetItemCount(); nItem++)
	{
		CString strFilePath = GetItemText(nItem, 2).Trim();
		if (strPreviousTargetFile != strFilePath)
		{
			strSelectedItemsText += _T("______File__ ") + strFilePath + EDITOR_NEW_LINE;
		}
		CString strFullLineText;
		for (int i = 0; i < nColumns; i++)
		{
			if (i != nColumns - 1)
				strFullLineText += GetItemText(nItem, i).Trim() + _T(" | ");
			else
				strFullLineText += GetItemText(nItem, i).Trim();
		}
		if (strFullLineText.IsEmpty()) continue;
		strSelectedItemsText += CSTRING_SPACE + strFullLineText + EDITOR_NEW_LINE;
		strPreviousTargetFile = strFilePath;
	}
	return strSelectedItemsText;
}

void CBreakpointList::OnContextMenu(CWnd * pWnd, CPoint point)
{
	CMenu menu;
	if (menu.LoadMenu(IDR_BREAKPOINT_WINDOW_CONTEXT_MENU))
	{
		CMenu* pSubMenu = menu.GetSubMenu(0);
		if (!pSubMenu) return;
		AppTranslator.ToNativeContextMenu(pSubMenu);
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

void CBreakpointList::OnEditCopy()
{
	CString strSelectedText = GetSelectedItemsText();
	if (strSelectedText.IsEmpty()) return;
	if (OpenClipboard())
	{
		GLOBALHANDLE hGlobal;
		TCHAR* pGlobal;
		EmptyClipboard();
		hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT | GMEM_SHARE, (strSelectedText.GetLength() + 1) * sizeof(TCHAR));
		pGlobal = (TCHAR*)GlobalLock(hGlobal);
		_tcscpy(pGlobal, (LPTSTR)(LPCTSTR)strSelectedText);
		GlobalUnlock(hGlobal);
		SetClipboardData(CF_UNICODETEXT, hGlobal);
		CloseClipboard();
	}
}

void CBreakpointList::OnEditClear()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		CBreakpointDlg* pPaneDlg = dynamic_cast<CBreakpointDlg*>(GetParent());
		if (pPaneDlg)
		{
			pPaneDlg->ClearBreakpointData();
		}
	}
}

void CBreakpointList::OnEditClearSelected()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		CBreakpointDlg* pPaneDlg = dynamic_cast<CBreakpointDlg*>(GetParent());
		if (pPaneDlg)
		{
			pPaneDlg->ClearSelectedBreakpoint();
		}
	}
}

void CBreakpointList::OnEditSelectall()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		SetItemState(-1, LVIS_SELECTED, LVIS_SELECTED);
	}
}

void CBreakpointList::OnEditSaveToFile()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		TCHAR  szFilter[] = _T("CSV File(*.csv)|*.csv||");
		CFileDialog fileDlg(FALSE, _T("csv"), _T("*.csv"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
		if (fileDlg.DoModal() == IDOK)
		{
			CString filename = fileDlg.GetPathName();
			CString text = GetItemsText();
			PathUtils::SaveFileTrunc(filename, text);
		}
	}
}

namespace
{
	void GotoLineInEditor(CEditorCtrl* pEditor, const CString& strLineNumber, const CString& strFileTarget)
	{
		if (pEditor)
		{
			int nLine = AppUtils::CStringToInt(strLineNumber);
			pEditor->GotoLine(nLine);
			pEditor->SetLineCenterDisplay(nLine);
		}
	}
}

void CBreakpointList::OnOutputGotoLine()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		if (CListCtrl::GetItemCount() == 0) return;
		CString strItem = GetSelectedItemsText();
		if (!strItem.IsEmpty())
		{
			int nPos1 = strItem.Find(_T("|"));
			CString strLineNumber = strItem.Mid(0, nPos1).Trim();
			CString strRemain = strItem.Mid(nPos1 + 1).Trim();
			int nPos2 = strRemain.Find(_T("|"));
			CString strFileTarget = strRemain.Mid(0, nPos2).Trim();
			if (strFileTarget.IsEmpty() || strLineNumber.IsEmpty()) return;
			if (PathFileExists(strFileTarget))
			{
				auto pActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
				auto pOpenedDoc = AppUtils::GetExistedDocument(strFileTarget);
				if (!pOpenedDoc)
				{
					if (pActiveDoc)
					{
						if (pActiveDoc->IsPreviewMode() && !pActiveDoc->IsModified()) // if there is a preview doc then reload file content
						{
							pActiveDoc->ReloadPreviewDocument(strFileTarget);
							GotoLineInEditor(pActiveDoc->GetEditorCtrl(), strLineNumber, strFileTarget);
						}
						else // create new preview document if there is no any
						{
							CDocument* pNewPreviewDoc = AppUtils::CreateDocumentFromFile(strFileTarget);
							auto pNewPreviewEditorDoc = dynamic_cast<CEditorDoc*>(pNewPreviewDoc);
							if (pNewPreviewEditorDoc)
							{
								pNewPreviewEditorDoc->SetPreviewMode(TRUE);
								GotoLineInEditor(pNewPreviewEditorDoc->GetEditorCtrl(), strLineNumber, strFileTarget);
							}
						}
					}
				}
				else
				{
					if (pOpenedDoc != pActiveDoc)
					{
						AppUtils::SetActiveDocument(pOpenedDoc);
						AppUtils::CloseAllPreviewDocument(PREVIEW_TYPE::PREVIEW_EDITOR);
						auto pEditorOpenedDoc = dynamic_cast<CEditorDoc*>(pOpenedDoc);
						if (pEditorOpenedDoc)
						{
							GotoLineInEditor(pEditorOpenedDoc->GetEditorCtrl(), strLineNumber, strFileTarget);
						}
					}
					else
					{
						auto pEditorOpenedDoc = dynamic_cast<CEditorDoc*>(pOpenedDoc);
						if (pEditorOpenedDoc)
						{
							GotoLineInEditor(pEditorOpenedDoc->GetEditorCtrl(), strLineNumber, strFileTarget);
						}
					}
				}
			}
			else
			{
				POSITION p1 = AfxGetApp()->GetFirstDocTemplatePosition();
				while (p1)
				{
					CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(p1);
					POSITION p2 = doctempl->GetFirstDocPosition();
					while (p2)
					{
						CDocument* doc = doctempl->GetNextDoc(p2);
						POSITION p3 = doc->GetFirstViewPosition();
						while (p3)
						{
							CString strDocName = doc->GetPathName();
							if (strDocName.IsEmpty())
							{
								strDocName = doc->GetTitle();
							}
							if (strDocName.Trim().Find(strFileTarget.Trim()) != -1)
							{
								if (AppUtils::SetActiveDocument(doc))
								{
									auto pEditorDoc = dynamic_cast<CEditorDoc*>(doc);
									if (pEditorDoc)
									{
										GotoLineInEditor(pEditorDoc->GetEditorCtrl(), strLineNumber, strFileTarget);
									}
								}
								break;
							}
							else break;
						}
					}
				}
			}
		}
	}
	SetFocus();
}

void CBreakpointList::OnEditViewLogInEditor()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		CString text = GetItemsText();
		AppUtils::CreateNewEditorWithText(_T("Breakpoint Data"), text);
	}
}

void CBreakpointList::OnEditRevealPath()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		if (CListCtrl::GetItemCount() == 0) return;
		CString strItem = GetSelectedItemsText();
		if (!strItem.IsEmpty())
		{
			int nPos1 = strItem.Find(_T("|"));
			CString strLineNumber = strItem.Mid(0, nPos1).Trim();
			CString strRemain = strItem.Mid(nPos1 + 1).Trim();
			int nPos2 = strRemain.Find(_T("|"));
			CString strFileTarget = strRemain.Mid(0, nPos2).Trim();
			strFileTarget.Replace(_T("\""), _T(""));
			if (PathFileExists(strFileTarget))
			{
				CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
				ASSERT(pFrame);
				if (!pFrame) return;
				pFrame->RevealInExplorerWindow(strFileTarget);
			}
			else
			{
				AfxMessageBox(_T("[Reveal In Explorer Error] path does not exist!"));
			}
		}
	}
	SetFocus();
}

void CBreakpointList::OnLButtonDown(UINT nFlags, CPoint point)
{
	CListCtrl::OnLButtonDown(nFlags, point);
	OnOutputGotoLine();
}

void CBreakpointList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CListCtrl::OnLButtonDblClk(nFlags, point);
	OnEditRevealPath();
}

BOOL CBreakpointList::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (::GetKeyState(VK_CONTROL) < 0)
		{
			if (pMsg->wParam == 'A')
			{
				OnEditSelectall();
				return true;
			}
			if (pMsg->wParam == 'C')
			{
				OnEditCopy();
				return true;
			}
			if (pMsg->wParam == 'E')
			{
				OnEditViewLogInEditor();
				return TRUE;
			}
			if (pMsg->wParam == 'S')
			{
				OnEditSaveToFile();
				return TRUE;
			}
			if (pMsg->wParam == VK_DELETE)
			{
				OnEditClear();
				return TRUE;
			}
		}
		else if (pMsg->wParam == VK_DELETE)
		{
			OnEditClearSelected();
			return TRUE;
		}
	}
	return CListCtrl::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CBreakpointList, CListCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, &CBreakpointList::OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, &CBreakpointList::OnEditClear)
	ON_COMMAND(ID_EDIT_CLEAR_SELECTED, &CBreakpointList::OnEditClearSelected)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CBreakpointList::OnEditSelectall)
	ON_COMMAND(ID_EDIT_SAVE_LOG_TO_FILE, &CBreakpointList::OnEditSaveToFile)
	ON_COMMAND(ID_EDIT_LOG_TO_EDITOR, &CBreakpointList::OnEditViewLogInEditor)
	ON_COMMAND(ID_EDIT_BREAKPOINT_WINDOWN_REVEALPATH, &CBreakpointList::OnEditRevealPath)
END_MESSAGE_MAP()