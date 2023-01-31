/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "PathResultWindow.h"
#include "VinaTextApp.h"
#include "MainFrm.h"
#include "EditorDoc.h"
#include "ImageDoc.h"
#include "PdfDoc.h"
#include "MediaDoc.h"
#include "AppUtil.h"
#include "RAIIUtils.h"
#include "AppSettings.h"
#include "translator/POHandler.h"

#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CString g_strSearchFilterMessage = _T("> > > Path Filter...");

IMPLEMENT_DYNCREATE(CPathResultWindow, CDockPaneBase)

CPathResultWindow::CPathResultWindow()
{
}

CPathResultWindow::~CPathResultWindow()
{
}

BEGIN_MESSAGE_MAP(CPathResultWindow, CDockPaneBase)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(UMW_DOCK_PANE_UPDATE, &CPathResultWindow::OnDockPaneUpdate)
END_MESSAGE_MAP()

LRESULT CPathResultWindow::OnDockPaneUpdate(WPARAM wParam, LPARAM lParam)
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

int CPathResultWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockPaneBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_ResultPaneDlg.Create(IDD_SEARCH_RESULT_DLG, this))
	{
		TRACE0("Failed to create path result dialog windows\n");
		return -1;      // fail to create
	}
	m_ResultPaneDlg.ShowWindow(SW_SHOW);
	return 0;
}

void CPathResultWindow::OnSize(UINT nType, int cx, int cy)
{
	CDockPaneBase::OnSize(nType, cx, cy);
	m_ResultPaneDlg.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}


void CPathResultWindow::AddResultData(const PATH_RESULT_DATA_LIST & ResultSearchData, const CString & strSeachWhat, int nSearchTotal, double dTimeMeasured, BOOL bAppendResult, BOOL bSearchWithoutMatchName)
{
	m_ResultPaneDlg.InitResult(ResultSearchData, strSeachWhat, nSearchTotal, dTimeMeasured, bAppendResult, bSearchWithoutMatchName);
}

void CPathResultWindow::ClearAll()
{
	m_ResultPaneDlg.ClearResult();
}

void CPathResultWindow::UpdateUIVisual()
{
	m_ResultPaneDlg.UpdateDlgFont();
	m_ResultPaneDlg.UpdateListCtrlVisual();
}

/////////////////////////////////////////////////////////////////////////////
// CPathResultDlg dialog

IMPLEMENT_DYNAMIC(CPathResultDlg, CDialogEx)

CPathResultDlg::CPathResultDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SEARCH_RESULT_DLG, pParent)
{
	UpdateDlgFont();
}

CPathResultDlg::~CPathResultDlg()
{
}

void CPathResultDlg::OnOK()
{
}

void CPathResultDlg::OnCancel()
{
}

BEGIN_MESSAGE_MAP(CPathResultDlg, CDialogEx)
	ON_WM_MOVING()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_SEARCH_RESULT, OnGetdispinfoList)
	ON_NOTIFY(LVN_ODFINDITEM, IDC_LIST_SEARCH_RESULT, OnOdfinditemList)
	ON_NOTIFY(LVN_ODCACHEHINT, IDC_LIST_SEARCH_RESULT, OnOdcachehintList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SEARCH_RESULT, OnItemchangedList)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SEARCH_RESULT, OnClickList)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_SEARCH_RESULT, OnKeydownList)
	ON_EN_CHANGE(ID_FILTER_FILE_RESULT_PANE, OnFilterTextChanged)
END_MESSAGE_MAP()

// CPathResultDlg message handlers

void CPathResultDlg::UpdateDlgFont()
{
	IMPLEMENT_FONT_SETTING_DOCK_WINDOW
}

void CPathResultDlg::UpdateListCtrlVisual()
{
	m_wndResultList.SetFont(&m_Font);
	m_wndResultList.SetBkColor(AppSettingMgr.m_ThemeColor);
	m_wndResultList.SetTextColor(RGB(255, 255, 255));
	m_wndResultList.SetTextBkColor(AppSettingMgr.m_ThemeColor);
}

void CPathResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SEARCH_RESULT, m_wndResultList);
}

void CPathResultDlg::InitResult(const PATH_RESULT_DATA_LIST & ResultSearchData, const CString& strSeachWhat, int nSearchTotal, double dTimeMeasured, BOOL bAppendResult, BOOL bSearchWithoutMatchName)
{
	if (bAppendResult)
	{
		APPEND_VECTOR_HELPER(m_DisplayResultSearchData, ResultSearchData);
		APPEND_VECTOR_HELPER(m_OriginalResultSearchInfo, ResultSearchData);
	}
	else
	{
		m_DisplayResultSearchData = ResultSearchData;
		m_OriginalResultSearchInfo = ResultSearchData;
	}
	//Resize the list to add the elements to the list
	ListView_SetExtendedListViewStyle(m_wndResultList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndResultList.SetItemCount(static_cast<int>(m_DisplayResultSearchData.size()));
	CString strResult;
	if (bSearchWithoutMatchName)
	{
		strResult.Format(_T("[Search all paths] searched paths: %d - macthed paths: %d - time: %fs"), nSearchTotal, int(ResultSearchData.size()), dTimeMeasured);
	}
	else
	{
		strResult.Format(_T("[Search all paths matched with \"%s\"] searched paths: %d - macthed paths: %d - time: %fs"), strSeachWhat, nSearchTotal, int(ResultSearchData.size()), dTimeMeasured);
	}
	g_strSearchFilterMessage = strResult;
	m_wndEditFilter.SetWindowTextW(g_strSearchFilterMessage);
}

void CPathResultDlg::ClearResult()
{
	m_DisplayResultSearchData.clear();
	PATH_RESULT_DATA_LIST().swap(m_DisplayResultSearchData);
	m_OriginalResultSearchInfo.clear();
	PATH_RESULT_DATA_LIST().swap(m_OriginalResultSearchInfo);
	//Resize the list to add the elements to the list
	ListView_SetExtendedListViewStyle(m_wndResultList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndResultList.SetItemCount(0);
	m_wndResultList.DeleteAllItems();
	g_strSearchFilterMessage = _T("> > > Path Filter...");
	m_wndEditFilter.SetWindowTextW(g_strSearchFilterMessage);
}

void CPathResultDlg::DeleteAResult(const CString & strFullPath)
{
	m_DisplayResultSearchData.erase(std::remove_if(
		m_DisplayResultSearchData.begin(),
		m_DisplayResultSearchData.end(),
		[&](PATH_RESULT_DATA const & data)
	{
		CString strFileTarget = data._strLocation + _T("\\") + data._strPathName;
		if (strFileTarget == strFullPath) return true;
		else return false;
	}),
	m_DisplayResultSearchData.end());

	m_OriginalResultSearchInfo.erase(std::remove_if(
		m_OriginalResultSearchInfo.begin(),
		m_OriginalResultSearchInfo.end(),
		[&](PATH_RESULT_DATA const & data)
	{
		CString strFileTarget = data._strLocation + _T("\\") + data._strPathName;
		if (strFileTarget == strFullPath) return true;
		else return false;
	}),
	m_OriginalResultSearchInfo.end());
	//Resize the list to add the elements to the list
	ListView_SetExtendedListViewStyle(m_wndResultList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndResultList.SetItemCount(static_cast<int>(m_DisplayResultSearchData.size()));
	m_wndResultList.SetItemState(-1, LVIS_FOCUSED , LVIS_SELECTED);
}

void CPathResultDlg::OnMoving(UINT nSide, LPRECT lpRect)
{
	CDialogEx::OnMoving(nSide, lpRect);
	CRect CurRect;
	GetWindowRect(&CurRect);
	lpRect->left = CurRect.left;
	lpRect->top = CurRect.top;
	lpRect->right = CurRect.right;
	lpRect->bottom = CurRect.bottom;
}

void CPathResultDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (!cx || !cy) return;
	LOGFONT lf;
	m_Font.GetLogFont(&lf);
	UINT nTxtHeight = (UINT)lf.lfHeight + 2;
	CRect rectClient;
	GetClientRect(rectClient);
	if (m_wndResultList.GetSafeHwnd())
	{
		m_wndResultList.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height() - nTxtHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	}
	if (m_wndEditFilter.GetSafeHwnd())
	{
		m_wndEditFilter.MoveWindow(0, cy - nTxtHeight, cx, nTxtHeight);
	}
}

BOOL CPathResultDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UINT nMenuf = MF_BYCOMMAND | MF_GRAYED | MF_DISABLED;
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu)
	{
		pSysMenu->EnableMenuItem(SC_CLOSE, nMenuf);
	}
	InitListCtrl();
	InitFilterCtrl();
	return TRUE;
}

//This function is called when the list needs data. This is the most
//critical function when working with virtual lists.
void CPathResultDlg::OnGetdispinfoList(NMHDR * pNMHDR, LRESULT * pResult)
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
			//Text is _strPathName
			text = m_DisplayResultSearchData[itemid]._strPathName;
		}
		else if (pItem->iSubItem == 1)
		{
			//Text is _strLocation
			text = m_DisplayResultSearchData[itemid]._strLocation;
		}
		else if (pItem->iSubItem == 2)
		{
			//Text is _strPathType
			text = m_DisplayResultSearchData[itemid]._strPathType;
		}
		else if (pItem->iSubItem == 3)
		{
			//Text is _strPathSize
			text = m_DisplayResultSearchData[itemid]._strPathSize;
		}
		else if (pItem->iSubItem == 4)
		{
			//Text is _strReadOnly
			text = m_DisplayResultSearchData[itemid]._strReadOnly;
		}
		else if (pItem->iSubItem == 5)
		{
			//Text is _strPathCreatedTime
			text = m_DisplayResultSearchData[itemid]._strPathCreatedTime;
		}
		else if (pItem->iSubItem == 6)
		{
			//Text is _strPathModifiedTime
			text = m_DisplayResultSearchData[itemid]._strPathModifiedTime;
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
void CPathResultDlg::OnOdfinditemList(NMHDR * pNMHDR, LRESULT * pResult)
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
	if (startPos >= m_wndResultList.GetItemCount())
		startPos = 0;
	int currentPos = startPos;

	////Let's search...
	do
	{
		//Do this word begins with all characters in searchstr?
		if (m_DisplayResultSearchData[currentPos]._strPathName.Find(searchstr) != -1)
		{
			//Select this item and stop search.
			*pResult = currentPos;
			break;
		}
		//Go to next item
		currentPos++;
		//Need to restart at top?
		if (currentPos >= m_wndResultList.GetItemCount())
			currentPos = 0;
		//Stop if back to start
	} while (currentPos != startPos);
}

//This is called to give you a chance to catch data. Useless in most cases
void CPathResultDlg::OnOdcachehintList(NMHDR * pNMHDR, LRESULT * pResult)
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
void CPathResultDlg::OnClickList(NMHDR * pNMHDR, LRESULT * pResult)
{
	NMLISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	LVHITTESTINFO hitinfo;
	//Copy click point
	hitinfo.pt = pNMListView->ptAction;
	//Make the hit test...
	int item = m_wndResultList.HitTest(&hitinfo);

	if (item != -1)
	{
		//We hit one item... did we hit state image (check box)?
		//This test only works if we are in list or report mode.
		if ((hitinfo.flags & LVHT_ONITEMSTATEICON) != 0)
		{
		}
	}
	if (m_wndEditFilter.GetCurrentText().IsEmpty())
	{
		m_wndEditFilter.SetWindowTextW(g_strSearchFilterMessage);
	}
	*pResult = 0;
}

//This is called when a key i pressed down
void CPathResultDlg::OnKeydownList(NMHDR * pNMHDR, LRESULT * pResult)
{
	LV_KEYDOWN* pLVKeyDown = (LV_KEYDOWN*)pNMHDR;
	//If user press space, toggle flag on selected item
	if (pLVKeyDown->wVKey == VK_SPACE)
	{
	}
	*pResult = 0;
}

void CPathResultDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if ((pNMListView->uChanged & LVIF_STATE) && (pNMListView->uNewState & LVIS_SELECTED)) {}
}

void CPathResultDlg::OnFilterTextChanged()
{
	m_DisplayResultSearchData = m_OriginalResultSearchInfo;
	CString strFilterText = m_wndEditFilter.GetCurrentText();
	if (!strFilterText.IsEmpty() && strFilterText != _T(">"))
	{
		PATH_RESULT_DATA_LIST filterData;
		if (strFilterText.Find(_T(">")) != -1) // exclude filter
		{
			strFilterText.Replace(_T(">"), _T(""));
			if (strFilterText.Find(_T(",")) != -1) // multiple filter
			{
				std::vector<CString> vecFilters = AppUtils::SplitterCString(strFilterText, ",");
				for (auto const& info : m_DisplayResultSearchData)
				{
					CString strTemp = info._strLocation + _T("\\") + info._strPathName;
					size_t nCountCheck = 0;
					for (auto filter : vecFilters)
					{
						if (strTemp.MakeLower().Find(filter.MakeLower()) == -1)
						{
							nCountCheck++;
						}
					}
					if (nCountCheck == vecFilters.size())
					{
						filterData.push_back(info);
					}
				}
			}
			else
			{
				for (auto const& info : m_DisplayResultSearchData)
				{
					CString strTemp = info._strLocation + _T("\\") + info._strPathName;
					if (strTemp.MakeLower().Find(strFilterText.MakeLower()) == -1)
					{
						filterData.push_back(info);
					}
				}
			}
		}
		else
		{
			if (strFilterText.Find(_T(",")) != -1) // multiple and filter
			{
				std::vector<CString> vecFilters = AppUtils::SplitterCString(strFilterText, ",");
				for (auto const& info : m_DisplayResultSearchData)
				{
					CString strTemp = info._strLocation + _T("\\") + info._strPathName;
					for (auto filter : vecFilters)
					{
						if (strTemp.MakeLower().Find(filter.MakeLower()) != -1)
						{
							filterData.push_back(info);
							break;
						}
					}
				}
			}
			else 
			{
				for (auto const& info : m_DisplayResultSearchData)
				{
					CString strTemp = info._strLocation + _T("\\") + info._strPathName;
					if (strTemp.MakeLower().Find(strFilterText.MakeLower()) != -1)
					{
						filterData.push_back(info);
					}
				}
			}
		}
		m_DisplayResultSearchData = filterData;
	}
	//Resize the list to add the elements to the list
	ListView_SetExtendedListViewStyle(m_wndResultList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndResultList.SetItemCount(static_cast<int>(m_DisplayResultSearchData.size()));
}

void CPathResultDlg::InitListCtrl()
{
	ListView_SetExtendedListViewStyle(m_wndResultList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndResultList.InsertColumn(0, _T("Path Name"), LVCFMT_LEFT, 250);
	m_wndResultList.InsertColumn(1, _T("Location"), LVCFMT_LEFT, 600);
	m_wndResultList.InsertColumn(2, _T("Path Type"), LVCFMT_LEFT, 100);
	m_wndResultList.InsertColumn(3, _T("File Size"), LVCFMT_LEFT, 100);
	m_wndResultList.InsertColumn(4, _T("Read Only"), LVCFMT_LEFT, 100);
	m_wndResultList.InsertColumn(5, _T("Created Time"), LVCFMT_LEFT, 200);
	m_wndResultList.InsertColumn(6, _T("Modifed Time"), LVCFMT_LEFT, 200);
	UpdateListCtrlVisual();
}

void CPathResultDlg::InitFilterCtrl()
{
	if (!m_wndEditFilter.CreateEx(WS_EX_STATICEDGE, _T("edit"), _T(""),
		WS_CHILD | WS_VISIBLE | ES_MULTILINE, CRect(0, 0, 0, 0), this, ID_FILTER_FILE_RESULT_PANE))
	{
		TRACE0("Failed to create user input edit\n");
		return;
	}
	m_wndEditFilter.SetFont(&m_Font);
	m_wndEditFilter.ModifyStyleEx(NULL, WS_EX_STATICEDGE);
	m_wndEditFilter.SetWindowTextW(g_strSearchFilterMessage);
}

/////////////////////////////////////////////////////////////////////////////
// CPathResultList

IMPLEMENT_DYNAMIC(CPathResultList, CListCtrl)

CPathResultList::CPathResultList()
{
}

CPathResultList::~CPathResultList()
{
}

CString CPathResultList::GetSelectedItemsText()
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

CString CPathResultList::GetItemsText()
{
	CString strSelectedItemsText;
	int nColumns = GetHeaderCtrl()->GetItemCount();
	for (int nItem = 0; nItem < GetItemCount(); nItem++)
	{
		CString strFullLineText;
		for (int i = 0; i < nColumns; i++)
		{
			if (i != nColumns - 1)
				strFullLineText += GetItemText(nItem, i).Trim() + _T(" , ");
			else
				strFullLineText += GetItemText(nItem, i).Trim();
		}
		if (strFullLineText.IsEmpty()) continue;
		strSelectedItemsText += CSTRING_SPACE + strFullLineText + EDITOR_NEW_LINE;
	}
	return strSelectedItemsText;
}

void CPathResultList::OnContextMenu(CWnd * pWnd, CPoint point)
{
	CMenu menu;
	if (menu.LoadMenu(IDR_PATH_RESULT_WINDOW_CONTEXT_MENU))
	{
		CMenu* pSubMenu = menu.GetSubMenu(0);
		if (!pSubMenu) return;
		AppTranslator.ToNativeContextMenu(pSubMenu);
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

void CPathResultList::OnEditCopy()
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

void CPathResultList::OnEditClear()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		CPathResultDlg* pPaneDlg = dynamic_cast<CPathResultDlg*>(GetParent());
		if (pPaneDlg)
		{
			pPaneDlg->ClearResult();
		}
	}
}

void CPathResultList::OnEditDelete()
{
	CPathResultDlg* pPaneDlg = dynamic_cast<CPathResultDlg*>(GetParent());
	if (pPaneDlg)
	{
		std::vector<CString> listPathToDelete;
		POSITION pos = GetFirstSelectedItemPosition();
		while (pos)
		{
			int nItem = GetNextSelectedItem(pos);
			CString strFullPath = GetItemText(nItem, 1).Trim() + _T("\\") + GetItemText(nItem, 0).Trim();
			listPathToDelete.push_back(strFullPath);
		}
		for (auto const& path : listPathToDelete)
		{
			// remove from list path
			pPaneDlg->DeleteAResult(path);
		}
	}
	SetFocus();
}

void CPathResultList::OnEditSelectall()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		SetItemState(-1, LVIS_SELECTED, LVIS_SELECTED);
	}
}

void CPathResultList::OnEditSaveToFile()
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

void CPathResultList::OpenSelectedPath()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		POSITION pos = GetFirstSelectedItemPosition();
		while (pos)
		{
			int nItem = GetNextSelectedItem(pos);
			CString strFileTarget = GetItemText(nItem, 1).Trim() + _T("\\") + GetItemText(nItem, 0).Trim();
			if (strFileTarget.IsEmpty()) return;
			if (PathFileExists(strFileTarget))
			{
				if (!PathUtils::IsDirectory(strFileTarget) && !PathUtils::IsBinaryFile(strFileTarget, FILE_BINNARY | FILE_OFFICE))
				{
					if (PathUtils::IsImageFile(strFileTarget)) // preview image file
					{
						auto pActiveDoc = dynamic_cast<CImageDoc*>(AppUtils::GetMDIActiveDocument());
						auto pOpenedDoc = AppUtils::GetExistedDocument(strFileTarget);
						if (!pOpenedDoc)
						{
							if (pActiveDoc && pActiveDoc->IsPreviewMode() && !pActiveDoc->IsModified()) // if there is a preview doc then reload file content
							{
								pActiveDoc->ReloadPreviewDocument(strFileTarget);
							}
							else // create new preview document if there is no any
							{
								CDocument* pNewPreviewDoc = AppUtils::CreateDocumentFromFile(strFileTarget);
								auto pNewPreviewImageDoc = dynamic_cast<CImageDoc*>(pNewPreviewDoc);
								if (pNewPreviewImageDoc)
								{
									pNewPreviewImageDoc->SetPreviewMode(TRUE);
								}
							}
						}
						else
						{
							if (pOpenedDoc != pActiveDoc)
							{
								AppUtils::SetActiveDocument(pOpenedDoc);
								AppUtils::CloseAllPreviewDocument(PREVIEW_TYPE::PREVIEW_IMAGE);
							}
						}
					}
					else if (PathUtils::IsPdfFile(strFileTarget)) // preview pdf file
					{
						auto pActiveDoc = dynamic_cast<CPdfDoc*>(AppUtils::GetMDIActiveDocument());
						auto pOpenedDoc = AppUtils::GetExistedDocument(strFileTarget);
						if (!pOpenedDoc)
						{
							if (pActiveDoc && pActiveDoc->IsPreviewMode() && !pActiveDoc->IsModified()) // if there is a preview doc then reload file content
							{
								pActiveDoc->ReloadPreviewDocument(strFileTarget);
							}
							else // create new preview document if there is no any
							{
								CDocument* pNewPreviewDoc = AppUtils::CreateDocumentFromFile(strFileTarget);
								auto pNewPreviewPdfDoc = dynamic_cast<CPdfDoc*>(pNewPreviewDoc);
								if (pNewPreviewPdfDoc)
								{
									pNewPreviewPdfDoc->SetPreviewMode(TRUE);
								}
							}
						}
						else
						{
							if (pOpenedDoc != pActiveDoc)
							{
								AppUtils::SetActiveDocument(pOpenedDoc);
								AppUtils::CloseAllPreviewDocument(PREVIEW_TYPE::PREVIEW_PDF);
							}
						}
					}
					else if (PathUtils::IsMediaFile(strFileTarget)) // preview media file
					{
						auto pActiveDoc = dynamic_cast<CMediaDoc*>(AppUtils::GetMDIActiveDocument());
						auto pOpenedDoc = AppUtils::GetExistedDocument(strFileTarget);
						if (!pOpenedDoc)
						{
							if (pActiveDoc && pActiveDoc->IsPreviewMode() && !pActiveDoc->IsModified()) // if there is a preview doc then reload file content
							{
								pActiveDoc->ReloadPreviewDocument(strFileTarget);
							}
							else // create new preview document if there is no any
							{
								CDocument* pNewPreviewDoc = AppUtils::CreateDocumentFromFile(strFileTarget);
								auto pNewPreviewMediaDoc = dynamic_cast<CMediaDoc*>(pNewPreviewDoc);
								if (pNewPreviewMediaDoc)
								{
									pNewPreviewMediaDoc->SetPreviewMode(TRUE);
								}
							}
						}
						else
						{
							if (pOpenedDoc != pActiveDoc)
							{
								AppUtils::SetActiveDocument(pOpenedDoc);
								AppUtils::CloseAllPreviewDocument(PREVIEW_TYPE::PREVIEW_MEDIA);
							}
						}
					}
					else // preview text file
					{
						auto pActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
						auto pOpenedDoc = AppUtils::GetExistedDocument(strFileTarget);
						if (!pOpenedDoc)
						{
							if (pActiveDoc && pActiveDoc->IsPreviewMode() && !pActiveDoc->IsModified()) // if there is a preview doc then reload file content
							{
								pActiveDoc->ReloadPreviewDocument(strFileTarget);
							}
							else // create new preview document if there is no any
							{
								CDocument* pNewPreviewDoc = AppUtils::CreateDocumentFromFile(strFileTarget);
								auto pNewPreviewEditorDoc = dynamic_cast<CEditorDoc*>(pNewPreviewDoc);
								if (pNewPreviewEditorDoc)
								{
									pNewPreviewEditorDoc->SetPreviewMode(TRUE);
								}
							}
						}
						else
						{
							if (pOpenedDoc != pActiveDoc)
							{
								AppUtils::SetActiveDocument(pOpenedDoc);
								AppUtils::CloseAllPreviewDocument(PREVIEW_TYPE::PREVIEW_EDITOR);
							}
						}
					}
				}
				else
				{
					CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
					ASSERT(pFrame);
					if (!pFrame) return;
					pFrame->RevealInExplorerWindow(strFileTarget);
				}
			}
			else
			{
				AfxMessageBox(_T("[Path Error] selected path does not exist!"));
			}
		}
	}
	SetFocus();
}

void CPathResultList::OnEditRevealPath()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		std::vector<std::pair<CString, int>> listPathToDelete;
		POSITION pos = GetFirstSelectedItemPosition();
		while (pos)
		{
			int nItem = GetNextSelectedItem(pos);
			CString strFullPath = GetItemText(nItem, 1).Trim() + _T("\\") + GetItemText(nItem, 0).Trim();
			if (PathFileExists(strFullPath))
			{
				CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
				ASSERT(pFrame);
				if (!pFrame) return;
				pFrame->RevealInExplorerWindow(strFullPath);
				break; // only support one row for this operation!
			}
			else
			{
				AfxMessageBox(_T("[Reveal In Explorer Error] path does not exist!"));
			}
		}
	}
	SetFocus();
}

void CPathResultList::OnEditCopyFullPath()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		CString strCopiedPaths;
		POSITION pos = GetFirstSelectedItemPosition();
		while (pos)
		{
			int nItem = GetNextSelectedItem(pos);
			CString strFullPath = GetItemText(nItem, 1).Trim() + _T("\\") + GetItemText(nItem, 0).Trim();
			if (PathFileExists(strFullPath))
			{
				strCopiedPaths += strFullPath + EDITOR_NEW_LINE_CR_LF;
			}
		}
		if (OpenClipboard())
		{
			GLOBALHANDLE hGlobal;
			TCHAR* pGlobal;
			EmptyClipboard();
			hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT | GMEM_SHARE, (strCopiedPaths.GetLength() + 1) * sizeof(TCHAR));
			pGlobal = (TCHAR*)GlobalLock(hGlobal);
			_tcscpy(pGlobal, (LPTSTR)(LPCTSTR)strCopiedPaths);
			GlobalUnlock(hGlobal);
			SetClipboardData(CF_UNICODETEXT, hGlobal);
			CloseClipboard();
		}
	}
	SetFocus();
}

void CPathResultList::OnEditViewLogInEditor()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		CString text = GetItemsText();
		AppUtils::CreateNewEditorWithText(_T("Path Text Result"), text);
	}
}

void CPathResultList::OnEditCountSelection()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		int nCount = 0;
		POSITION pos = GetFirstSelectedItemPosition();
		while (pos)
		{
			int nItem = GetNextSelectedItem(pos);
			nCount++;
		}
		AfxMessageBoxFormat(MB_ICONINFORMATION, _T("%d selected rows."), nCount);
	}
}

void CPathResultList::OnEditSendToRecyclebin()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		POSITION hasData = GetFirstSelectedItemPosition(); if (!hasData) return;
		if (IDYES == AfxMessageBox(_T("Are you sure want to delete it?"), MB_YESNO | MB_ICONWARNING))
		{
			CPathResultDlg* pPaneDlg = dynamic_cast<CPathResultDlg*>(GetParent());
			if (pPaneDlg)
			{
				std::vector<CString> listPathToDelete;
				POSITION pos = GetFirstSelectedItemPosition();
				while (pos)
				{
					int nItem = GetNextSelectedItem(pos);
					CString strFullPath = GetItemText(nItem, 1).Trim() + _T("\\") + GetItemText(nItem, 0).Trim();
					if (PathFileExists(strFullPath))
					{
						// close document before change file in system...
						AppUtils::CloseDocumentByFilePath(strFullPath);
						Sleep(500); // wait for closing completed
						if (PathUtils::SendToRecycleBin(this->GetSafeHwnd(), strFullPath))
						{
							// remove from explorer also...
							CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
							ASSERT(pFrame);
							if (!pFrame) return;
							HTREEITEM hDeleteItem = pFrame->GetFileExplorerCtrl().PathToItem(strFullPath);
							if (hDeleteItem)
							{
								pFrame->GetFileExplorerCtrl().DeleteItem(hDeleteItem);
							}
							listPathToDelete.push_back(strFullPath);
						}
						else
						{
							LOG_OUTPUT_MESSAGE_FORMAT(_T("[Delete Error] Path %s does not allow to delete!"), strFullPath);
						}
					}
				}
				// remove from list path result window
				for (auto const& path : listPathToDelete)
				{
					pPaneDlg->DeleteAResult(path);
				}
			}
		}
	}
	SetFocus();
}

void CPathResultList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CListCtrl::OnLButtonDblClk(nFlags, point);
	OpenSelectedPath();
}

BOOL CPathResultList::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
		{
			if (pMsg->wParam == 'Q')
			{
				OnEditRevealPath();
				return TRUE;
			}
			if (pMsg->wParam == 'C')
			{
				OnEditCopyFullPath();
				return TRUE;
			}
		}
		else if (::GetKeyState(VK_CONTROL) < 0)
		{
			if (pMsg->wParam == 'A')
			{
				OnEditSelectall();
				return TRUE;
			}
			if (pMsg->wParam == 'C')
			{
				OnEditCopy();
				return TRUE;
			}
			if (pMsg->wParam == 'E')
			{
				OnEditViewLogInEditor();
				return TRUE;
			}
			if (pMsg->wParam == 'R')
			{
				OnEditCountSelection();
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
		else if (::GetKeyState(VK_SHIFT) < 0)
		{
			if (pMsg->wParam == VK_DELETE)
			{
				OnEditSendToRecyclebin();
				return TRUE;
			}
		}
		else if (pMsg->wParam == VK_DELETE)
		{
			OnEditDelete();
			return TRUE;
		}
	}
	return CListCtrl::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CPathResultList, CListCtrl)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, &CPathResultList::OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, &CPathResultList::OnEditClear)
	ON_COMMAND(ID_EDIT_DELETE_FROM_LIST, &CPathResultList::OnEditDelete)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CPathResultList::OnEditSelectall)
	ON_COMMAND(ID_EDIT_SAVE_LOG_TO_FILE, &CPathResultList::OnEditSaveToFile)
	ON_COMMAND(ID_EDIT_PATH_RESULT_WINDOWN_REVEALPATH, &CPathResultList::OnEditRevealPath)
	ON_COMMAND(ID_EDIT_COPY_FULL_PATH, &CPathResultList::OnEditCopyFullPath)
	ON_COMMAND(ID_EDIT_COUNT_SELECTION, &CPathResultList::OnEditCountSelection)
	ON_COMMAND(ID_EDIT_LOG_TO_EDITOR, &CPathResultList::OnEditViewLogInEditor)
	ON_COMMAND(ID_EDIT_SEND_RECYCLE_BIN, &CPathResultList::OnEditSendToRecyclebin)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPathEditFilter

IMPLEMENT_DYNAMIC(CPathEditFilter, CUndoRedoEditControl)

CPathEditFilter::CPathEditFilter()
{
}

CPathEditFilter::~CPathEditFilter()
{
}

CString CPathEditFilter::GetCurrentText()
{
	CString str;
	GetWindowText(str);
	return str;
}

BEGIN_MESSAGE_MAP(CPathEditFilter, CUndoRedoEditControl)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

BOOL CPathEditFilter::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
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
				return TRUE;
			}
			if (pMsg->wParam == 'X')
			{
				SendMessage(WM_CUT); // send command message to child control
				return TRUE;
			}
			if (pMsg->wParam == 'V')
			{
				SendMessage(WM_PASTE); // send command message to child control
				return TRUE;
			}
		}
	}
	return CUndoRedoEditControl::PreTranslateMessage(pMsg);
}

HBRUSH CPathEditFilter::CtlColor(CDC* pDC, UINT nCtlColor)
{
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkColor(RGB(47, 79, 79));
	return ::GetSysColorBrush(COLOR_WINDOW);
}

void CPathEditFilter::OnSetFocus(CWnd * pOldWnd)
{
	CUndoRedoEditControl::OnSetFocus(pOldWnd);
	if (GetCurrentText() == g_strSearchFilterMessage)
	{
		SetWindowTextW(_T(""));
	}
}

void CPathEditFilter::OnKillFocus(CWnd * pNewWnd)
{
	CUndoRedoEditControl::OnKillFocus(pNewWnd);
	if (GetCurrentText().IsEmpty())
	{
		SetWindowTextW(g_strSearchFilterMessage);
	}
}

void CPathEditFilter::SetCaretAtEndline()
{
	SetFocus();
	SetSel(0, -1);
	SetSel(-1);
}