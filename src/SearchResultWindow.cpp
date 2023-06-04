/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "SearchResultWindow.h"
#include "VinaTextApp.h"
#include "MainFrm.h"
#include "EditorDoc.h"
#include "AppUtil.h"
#include "RAIIUtils.h"
#include "AppSettings.h"
#include "LocalizationHandler.h"

#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CString g_strSearchFilterMessage = _T("> > > File Filter...");

IMPLEMENT_DYNCREATE(CSearchResultWindow, CDockPaneBase)

CSearchResultWindow::CSearchResultWindow()
{
}

CSearchResultWindow::~CSearchResultWindow()
{
}

BEGIN_MESSAGE_MAP(CSearchResultWindow, CDockPaneBase)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(UMW_DOCK_PANE_UPDATE, &CSearchResultWindow::OnDockPaneUpdate)
END_MESSAGE_MAP()

LRESULT CSearchResultWindow::OnDockPaneUpdate(WPARAM wParam, LPARAM lParam)
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

int CSearchResultWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockPaneBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_ResultPaneDlg.Create(IDD_SEARCH_RESULT_DLG, this))
	{
		TRACE0("Failed to create search result dialog windows\n");
		return -1;      // fail to create
	}
	m_ResultPaneDlg.ShowWindow(SW_SHOW);
	return 0;
}

void CSearchResultWindow::OnSize(UINT nType, int cx, int cy)
{
	CDockPaneBase::OnSize(nType, cx, cy);
	m_ResultPaneDlg.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}


void CSearchResultWindow::AddResultData(const TEXT_RESULT_SEARCH_REPLACE_DATA & ResultSearchData)
{
	m_ResultPaneDlg.InitResult(ResultSearchData);
}

void CSearchResultWindow::ClearAll()
{
	m_ResultPaneDlg.ClearResult();
}

void CSearchResultWindow::UpdateUIVisual()
{
	m_ResultPaneDlg.UpdateListCtrlVisual();
}

/////////////////////////////////////////////////////////////////////////////
// CSearchResultDlg dialog

IMPLEMENT_DYNAMIC(CSearchResultDlg, CDialogEx)

CSearchResultDlg::CSearchResultDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SEARCH_RESULT_DLG, pParent)
{
	IMPLEMENT_FONT_SETTING_DOCK_WINDOW
}

CSearchResultDlg::~CSearchResultDlg()
{
}

void CSearchResultDlg::OnOK()
{
}

void CSearchResultDlg::OnCancel()
{
}

BEGIN_MESSAGE_MAP(CSearchResultDlg, CDialogEx)
	ON_WM_MOVING()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_SEARCH_RESULT, OnGetdispinfoList)
	ON_NOTIFY(LVN_ODFINDITEM, IDC_LIST_SEARCH_RESULT, OnOdfinditemList)
	ON_NOTIFY(LVN_ODCACHEHINT, IDC_LIST_SEARCH_RESULT, OnOdcachehintList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SEARCH_RESULT, OnItemchangedList)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SEARCH_RESULT, OnClickList)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_SEARCH_RESULT, OnKeydownList)
	ON_EN_CHANGE(ID_FILTER_SEARCH_RESULT_PANE, OnFilterTextChanged)
END_MESSAGE_MAP()

// CSearchResultDlg message handlers

void CSearchResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SEARCH_RESULT, m_wndResultList);
}

void CSearchResultDlg::InitResult(const TEXT_RESULT_SEARCH_REPLACE_DATA & ResultSearchData)
{
	if (ResultSearchData._bAppendResult)
	{
		m_DisplayResultSearchData._bAppendResult = ResultSearchData._bAppendResult;
		m_DisplayResultSearchData._bShowFileNameOnly = ResultSearchData._bShowFileNameOnly;
		m_DisplayResultSearchData._nMatchedFiles = ResultSearchData._nMatchedFiles;
		m_DisplayResultSearchData._nMatchedWords = ResultSearchData._nMatchedWords;
		m_DisplayResultSearchData._nTotalSearchFile = ResultSearchData._nTotalSearchFile;
		m_DisplayResultSearchData._strReplaceWith = ResultSearchData._strReplaceWith;
		m_DisplayResultSearchData._strScope = ResultSearchData._strScope;
		m_DisplayResultSearchData._strSearchWhat = ResultSearchData._strSearchWhat;
		m_DisplayResultSearchData._TimeMeasured = ResultSearchData._TimeMeasured;
		APPEND_VECTOR_HELPER(m_DisplayResultSearchData._vecSearchDataLine, ResultSearchData._vecSearchDataLine);
		APPEND_VECTOR_HELPER(m_OriginalResultSearchInfo, ResultSearchData._vecSearchDataLine);
	}
	else
	{
		m_DisplayResultSearchData = ResultSearchData;
		m_OriginalResultSearchInfo = ResultSearchData._vecSearchDataLine;
	}
	//Resize the list to add the elements to the list
	ListView_SetExtendedListViewStyle(m_wndResultList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndResultList.SetItemCount(static_cast<int>(m_DisplayResultSearchData._vecSearchDataLine.size()));
	CString strResult;
	if (ResultSearchData._bIsReplaceData)
	{
		strResult = _T("[Replace all \"%s\" with \"%s\" in %s] searched files: %d - matched files: %d | searched lines: %d | replaced words: %d | time: %fs");
		strResult.Format(strResult, ResultSearchData._strSearchWhat, ResultSearchData._strReplaceWith, ResultSearchData._strScope, (int)ResultSearchData._nTotalSearchFile, (int)ResultSearchData._nMatchedFiles, (int)ResultSearchData._nLineCounts,
			(int)ResultSearchData._nMatchedWords, ResultSearchData._TimeMeasured);
		m_wndResultList.SetSeachWhatString(ResultSearchData._strReplaceWith);
	}
	else
	{
		strResult = _T("[Search all \"%s\" in %s] searched files: %d - matched files: %d | searched lines: %d - matched lines: %d | matched words: %d | time: %fs");
		strResult.Format(strResult, ResultSearchData._strSearchWhat, ResultSearchData._strScope, (int)ResultSearchData._nTotalSearchFile, (int)ResultSearchData._nMatchedFiles, (int)ResultSearchData._nLineCounts,
			(int)ResultSearchData._vecSearchDataLine.size(), (int)ResultSearchData._nMatchedWords, ResultSearchData._TimeMeasured);
		m_wndResultList.SetSeachWhatString(ResultSearchData._strSearchWhat);
	}
	g_strSearchFilterMessage = strResult;
	m_wndEditFilter.SetWindowTextW(g_strSearchFilterMessage);
	m_wndResultList.SetSeachOptions(ResultSearchData._nSearchOptions);
}

void CSearchResultDlg::ClearResult()
{
	m_DisplayResultSearchData.Reset();
	m_OriginalResultSearchInfo.clear();
	std::vector<SEARCH_DATA_LINE>().swap(m_OriginalResultSearchInfo);
	//Resize the list to add the elements to the list
	ListView_SetExtendedListViewStyle(m_wndResultList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndResultList.SetItemCount(0);
	m_wndResultList.DeleteAllItems();
	g_strSearchFilterMessage = _T("> > > File Filter...");
	m_wndEditFilter.SetWindowTextW(g_strSearchFilterMessage);
}

void CSearchResultDlg::DeleteAPath(const CString & strFullPath)
{
	m_DisplayResultSearchData._vecSearchDataLine.erase(std::remove_if(
		m_DisplayResultSearchData._vecSearchDataLine.begin(),
		m_DisplayResultSearchData._vecSearchDataLine.end(),
		[&](SEARCH_DATA_LINE const & data)
	{
		if (data._strTargetFile == strFullPath) return true;
		else return false;
	}),
	m_DisplayResultSearchData._vecSearchDataLine.end());

	m_OriginalResultSearchInfo.erase(std::remove_if(
		m_OriginalResultSearchInfo.begin(),
		m_OriginalResultSearchInfo.end(),
		[&](SEARCH_DATA_LINE const & data)
	{
		if (data._strTargetFile == strFullPath) return true;
		else return false;
	}),
	m_OriginalResultSearchInfo.end());
	//Resize the list to add the elements to the list
	ListView_SetExtendedListViewStyle(m_wndResultList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndResultList.SetItemCount(static_cast<int>(m_DisplayResultSearchData._vecSearchDataLine.size()));
	m_wndResultList.SetItemState(-1, LVIS_FOCUSED, LVIS_SELECTED);
}

void CSearchResultDlg::DeleteARow(const CString & strFullPath, unsigned int nLineNumber)
{
	m_DisplayResultSearchData._vecSearchDataLine.erase(std::remove_if(
		m_DisplayResultSearchData._vecSearchDataLine.begin(),
		m_DisplayResultSearchData._vecSearchDataLine.end(),
		[&](SEARCH_DATA_LINE const & data)
	{
		if (data._strTargetFile == strFullPath && data._nLineNumber == nLineNumber) return true;
		else return false;
	}),
		m_DisplayResultSearchData._vecSearchDataLine.end());

	m_OriginalResultSearchInfo.erase(std::remove_if(
		m_OriginalResultSearchInfo.begin(),
		m_OriginalResultSearchInfo.end(),
		[&](SEARCH_DATA_LINE const & data)
	{
		if (data._strTargetFile == strFullPath && data._nLineNumber == nLineNumber) return true;
		else return false;
	}),
	m_OriginalResultSearchInfo.end());
	//Resize the list to add the elements to the list
	ListView_SetExtendedListViewStyle(m_wndResultList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndResultList.SetItemCount(static_cast<int>(m_DisplayResultSearchData._vecSearchDataLine.size()));
	m_wndResultList.SetItemState(-1, LVIS_FOCUSED, LVIS_SELECTED);
}

void CSearchResultDlg::OnMoving(UINT nSide, LPRECT lpRect)
{
	CDialogEx::OnMoving(nSide, lpRect);
	CRect CurRect;
	GetWindowRect(&CurRect);
	lpRect->left = CurRect.left;
	lpRect->top = CurRect.top;
	lpRect->right = CurRect.right;
	lpRect->bottom = CurRect.bottom;
}

void CSearchResultDlg::OnSize(UINT nType, int cx, int cy)
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

BOOL CSearchResultDlg::OnInitDialog()
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
void CSearchResultDlg::OnGetdispinfoList(NMHDR * pNMHDR, LRESULT * pResult)
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
			//Text is _strTargetFile
			if (m_DisplayResultSearchData._bShowFileNameOnly)
			{
				text = PathUtils::GetFilenameFromPath(m_DisplayResultSearchData._vecSearchDataLine[itemid]._strTargetFile);
			}
			else
			{
				text = m_DisplayResultSearchData._vecSearchDataLine[itemid]._strTargetFile;
			}
		}
		else if (pItem->iSubItem == 1)
		{
			//Text is _strLine
			text = m_DisplayResultSearchData._vecSearchDataLine[itemid]._strLine;
		}
		else if (pItem->iSubItem == 2)
		{
			//Text is _nLineNumber
			text = AppUtils::IntToCString(m_DisplayResultSearchData._vecSearchDataLine[itemid]._nLineNumber);
		}
		else if (pItem->iSubItem == 3)
		{
			//Text is _nColumnNumber
			text = AppUtils::IntToCString(m_DisplayResultSearchData._vecSearchDataLine[itemid]._nColumnNumber);
		}
		else if (pItem->iSubItem == 4)
		{
			//Text is _nPositionNumber
			text = AppUtils::IntToCString(m_DisplayResultSearchData._vecSearchDataLine[itemid]._nPositionNumber);
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
void CSearchResultDlg::OnOdfinditemList(NMHDR * pNMHDR, LRESULT * pResult)
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
		if (m_DisplayResultSearchData._vecSearchDataLine[currentPos]._strTargetFile.Find(searchstr) != -1)
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
void CSearchResultDlg::OnOdcachehintList(NMHDR * pNMHDR, LRESULT * pResult)
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
void CSearchResultDlg::OnClickList(NMHDR * pNMHDR, LRESULT * pResult)
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
void CSearchResultDlg::OnKeydownList(NMHDR * pNMHDR, LRESULT * pResult)
{
	LV_KEYDOWN* pLVKeyDown = (LV_KEYDOWN*)pNMHDR;
	//If user press space, toggle flag on selected item
	if (pLVKeyDown->wVKey == VK_SPACE)
	{
	}
	*pResult = 0;
}

void CSearchResultDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if ((pNMListView->uChanged & LVIF_STATE) && (pNMListView->uNewState & LVIS_SELECTED))
	{
		m_wndResultList.OnOutputPreviewFile();
	}
}

void CSearchResultDlg::OnFilterTextChanged()
{
	m_DisplayResultSearchData._vecSearchDataLine = m_OriginalResultSearchInfo;
	CString strFilterText = m_wndEditFilter.GetCurrentText();
	if (!strFilterText.IsEmpty() && strFilterText != _T(">"))
	{
		TEXT_RESULT_SEARCH_REPLACE_DATA filterData;
		if (strFilterText.Find(_T(">")) != -1) // exclude filter
		{
			strFilterText.Replace(_T(">"), _T(""));
			if (strFilterText.Find(_T(",")) != -1) // multiple filter
			{
				std::vector<CString> vecFilters = AppUtils::SplitterCString(strFilterText, ",");
				for (auto const& info : m_DisplayResultSearchData._vecSearchDataLine)
				{
					CString strTemp = info._strTargetFile;
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
						filterData._vecSearchDataLine.push_back(info);
					}
				}
			}
			else
			{
				for (auto const& info : m_DisplayResultSearchData._vecSearchDataLine)
				{
					CString strTemp = info._strTargetFile;
					if (strTemp.MakeLower().Find(strFilterText.MakeLower()) == -1)
					{
						filterData._vecSearchDataLine.push_back(info);
					}
				}
			}
		}
		else
		{
			if (strFilterText.Find(_T(",")) != -1) // multiple and filter
			{
				std::vector<CString> vecFilters = AppUtils::SplitterCString(strFilterText, ",");
				for (auto const& info : m_DisplayResultSearchData._vecSearchDataLine)
				{
					CString strTemp = info._strTargetFile;
					for (auto filter : vecFilters)
					{
						if (strTemp.MakeLower().Find(filter.MakeLower()) != -1)
						{
							filterData._vecSearchDataLine.push_back(info);
							break;
						}
					}
				}
			}
			else
			{
				for (auto const& info : m_DisplayResultSearchData._vecSearchDataLine)
				{
					CString strTemp = info._strTargetFile;
					if (strTemp.MakeLower().Find(strFilterText.MakeLower()) != -1)
					{
						filterData._vecSearchDataLine.push_back(info);
					}
				}
			}
		}
		m_DisplayResultSearchData._vecSearchDataLine = filterData._vecSearchDataLine;
	}
	//Resize the list to add the elements to the list
	ListView_SetExtendedListViewStyle(m_wndResultList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndResultList.SetItemCount(static_cast<int>(m_DisplayResultSearchData._vecSearchDataLine.size()));
}

void CSearchResultDlg::InitListCtrl()
{
	ListView_SetExtendedListViewStyle(m_wndResultList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndResultList.InsertColumn(0, _T("Path"), LVCFMT_LEFT, 500);
	m_wndResultList.InsertColumn(1, _T("Text"), LVCFMT_LEFT, 500);
	m_wndResultList.InsertColumn(2, _T("Line"), LVCFMT_LEFT, 100);
	m_wndResultList.InsertColumn(3, _T("Column"), LVCFMT_LEFT, 100);
	m_wndResultList.InsertColumn(4, _T("Position"), LVCFMT_LEFT, 100);
	UpdateListCtrlVisual();
}

void CSearchResultDlg::InitFilterCtrl()
{
	if (!m_wndEditFilter.CreateEx(WS_EX_STATICEDGE, _T("edit"), _T(""),
		WS_CHILD | WS_VISIBLE | ES_MULTILINE, CRect(0, 0, 0, 0), this, ID_FILTER_SEARCH_RESULT_PANE))
	{
		TRACE0("Failed to create user input edit\n");
		return;
	}
	m_wndEditFilter.SetFont(&m_Font);
	m_wndEditFilter.ModifyStyleEx(NULL, WS_EX_STATICEDGE);
	m_wndEditFilter.SetWindowTextW(g_strSearchFilterMessage);
}

void CSearchResultDlg::UpdateListCtrlVisual()
{
	m_wndResultList.SetFont(&m_Font);
	m_wndResultList.SetBkColor(AppSettingMgr.m_AppThemeColor);
	m_wndResultList.SetTextColor(IS_LIGHT_THEME ? BasicColors::black : BasicColors::white);
	m_wndResultList.SetTextBkColor(AppSettingMgr.m_AppThemeColor);
}

/////////////////////////////////////////////////////////////////////////////
// CSearchResultList

IMPLEMENT_DYNAMIC(CSearchResultList, CListCtrl)

CSearchResultList::CSearchResultList()
{
}

CSearchResultList::~CSearchResultList()
{
}

CString CSearchResultList::GetSelectedItemsText()
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

CString CSearchResultList::GetItemsText()
{
	CString strSelectedItemsText;
	int nColumns = GetHeaderCtrl()->GetItemCount();
	CString strPreviousTargetFile;
	for (int nItem = 0; nItem < GetItemCount(); nItem++)
	{
		CString strFilePath = GetItemText(nItem, 0).Trim();
		if (strPreviousTargetFile != strFilePath)
		{
			strSelectedItemsText += _T("______FILE__ ") + strFilePath + EDITOR_NEW_LINE;
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
		strSelectedItemsText +=CSTRING_SPACE + strFullLineText + EDITOR_NEW_LINE;
		strPreviousTargetFile = strFilePath;
	}
	return strSelectedItemsText;
}

void CSearchResultList::OnContextMenu(CWnd * pWnd, CPoint point)
{
	CMenu menu;
	if (menu.LoadMenu(IDR_TEXT_RESULT_WINDOW_CONTEXT_MENU))
	{
		CMenu* pSubMenu = menu.GetSubMenu(0);
		if (!pSubMenu) return;
		VinaTextLocalization.TranslateContextMenu(pSubMenu);
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

void CSearchResultList::OnEditCopy()
{
	CString strSelectedText =  GetSelectedItemsText();
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

void CSearchResultList::OnEditClear()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		CSearchResultDlg* pPaneDlg = dynamic_cast<CSearchResultDlg*>(GetParent());
		if (pPaneDlg)
		{
			pPaneDlg->ClearResult();
		}
	}
}

void CSearchResultList::OnEditDelete()
{
	CSearchResultDlg* pPaneDlg = dynamic_cast<CSearchResultDlg*>(GetParent());
	if (pPaneDlg)
	{
		std::vector<std::pair<CString, int>> listPathToDelete;
		POSITION pos = GetFirstSelectedItemPosition();
		while (pos)
		{
			int nItem = GetNextSelectedItem(pos);
			CString strLineNumber = GetItemText(nItem, 2).Trim();
			CString strFullPath = GetItemText(nItem, 0).Trim();
			listPathToDelete.push_back(std::make_pair(strFullPath, AppUtils::CStringToInt(strLineNumber)));
		}
		for (auto const& path : listPathToDelete)
		{
			// remove from list path
			pPaneDlg->DeleteARow(path.first, path.second);
		}
	}
	SetFocus();
}

void CSearchResultList::OnEditSelectAll()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		SetItemState(-1, LVIS_SELECTED, LVIS_SELECTED);
	}
}

void CSearchResultList::OnEditSaveToFile()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		TCHAR  szFilter[] = _T("CSV File(*.csv)|*.csv||");
		CFileDialog fileDlg(FALSE, _T("csv"), _T("*.csv"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
		if (fileDlg.DoModal() == IDOK)
		{
			CString filename = fileDlg.GetPathName();
			CString text = GetItemsText();
			PathUtils::SaveFileTruncate(filename, text);
		}
	}
}

namespace
{
	void GotoLineInEditor(CEditorCtrl* pEditor, const CString& strLineNumber, const CString& strSeachWhat, unsigned int uiSearchOptions)
	{
		if (pEditor)
		{
			int nLine = AppUtils::CStringToInt(strLineNumber);
			pEditor->GotoLine(nLine);
			pEditor->SetLineCenterDisplay(nLine);
			pEditor->RenderSearchResultInLine(nLine, strSeachWhat, uiSearchOptions);
		}
	}
}

void CSearchResultList::OnOutputPreviewFile()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		POSITION pos = GetFirstSelectedItemPosition();
		while (pos)
		{
			int nItem = GetNextSelectedItem(pos);
			CString strLineNumber = GetItemText(nItem, 2).Trim();
			CString strFileTarget = GetItemText(nItem, 0).Trim();
			if (strFileTarget.IsEmpty() || strLineNumber.IsEmpty()) return;
			if (PathFileExists(strFileTarget))
			{
				auto pActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
				auto pOpenedDoc = AppUtils::GetExistedDocument(strFileTarget);
				if (!pOpenedDoc)
				{
					if (pActiveDoc && pActiveDoc->IsPreviewMode() && !pActiveDoc->IsModified()) // if there is a preview doc then reload file content
					{
						pActiveDoc->ReloadPreviewDocument(strFileTarget);
						GotoLineInEditor(pActiveDoc->GetEditorCtrl(), strLineNumber, m_strSeachWhat, m_uiSearchOptions);
					}
					else // create new preview document if there is no any
					{
						CDocument* pNewPreviewDoc = AppUtils::CreateDocumentFromFile(strFileTarget);
						auto pNewPreviewEditorDoc = dynamic_cast<CEditorDoc*>(pNewPreviewDoc);
						if (pNewPreviewEditorDoc)
						{
							pNewPreviewEditorDoc->SetPreviewMode(TRUE);
							GotoLineInEditor(pNewPreviewEditorDoc->GetEditorCtrl(), strLineNumber, m_strSeachWhat, m_uiSearchOptions);
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
							GotoLineInEditor(pEditorOpenedDoc->GetEditorCtrl(), strLineNumber, m_strSeachWhat, m_uiSearchOptions);
						}
					}
					else
					{
						auto pEditorOpenedDoc = dynamic_cast<CEditorDoc*>(pOpenedDoc);
						if (pEditorOpenedDoc)
						{
							GotoLineInEditor(pEditorOpenedDoc->GetEditorCtrl(), strLineNumber, m_strSeachWhat, m_uiSearchOptions);
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
										GotoLineInEditor(pEditorDoc->GetEditorCtrl(), strLineNumber, m_strSeachWhat, m_uiSearchOptions);
									}
								}
								break;
							}
							else break;
						}
					}
				}
			}
			break; // only support one row for this operation!
		}
	}
	SetFocus();
}

void CSearchResultList::OnEditViewLogInEditor()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		CString text = GetItemsText();
		AppUtils::CreateNewEditorWithText(_T("Search Text Result"), text);
	}
}

void CSearchResultList::OnEditCopyFullPath()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		CString strCopiedPaths;
		POSITION pos = GetFirstSelectedItemPosition();
		while (pos)
		{
			int nItem = GetNextSelectedItem(pos);
			CString strFullPath = GetItemText(nItem, 0).Trim();
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

void CSearchResultList::OnEditCountSelection()
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

void CSearchResultList::OnEditSendToRecyclebin()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		POSITION hasData = GetFirstSelectedItemPosition(); if (!hasData) return;
		if (IDYES == AfxMessageBox(_T("Are you sure want to delete it?"), MB_YESNO | MB_ICONWARNING))
		{
			CSearchResultDlg* pPaneDlg = dynamic_cast<CSearchResultDlg*>(GetParent());
			if (pPaneDlg)
			{
				std::vector<CString> listPathToDelete;
				POSITION pos = GetFirstSelectedItemPosition();
				while (pos)
				{
					int nItem = GetNextSelectedItem(pos);
					CString strFullPath = GetItemText(nItem, 0).Trim();
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
							LOG_OUTPUT_MESSAGE_FORMAT(_T("[Error] Path %s does not allow to delete!"), strFullPath);
						}
					}
				}
				// remove from list path result window
				for (auto const& path : listPathToDelete)
				{
					pPaneDlg->DeleteAPath(path);
				}
			}
		}
	}
	SetFocus();
}

void CSearchResultList::OnEditRevealPath()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		POSITION pos = GetFirstSelectedItemPosition();
		while (pos)
		{
			int nItem = GetNextSelectedItem(pos);
			CString strFullPath = GetItemText(nItem, 0).Trim();
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

void CSearchResultList::OnLButtonDown(UINT nFlags, CPoint point)
{
	CListCtrl::OnLButtonDown(nFlags, point);
	OnOutputPreviewFile();
}

void CSearchResultList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CListCtrl::OnLButtonDblClk(nFlags, point);
	OnEditRevealPath();
}

BOOL CSearchResultList::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
		{
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
				OnEditSelectAll();
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

BEGIN_MESSAGE_MAP(CSearchResultList, CListCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, &CSearchResultList::OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, &CSearchResultList::OnEditClear)
	ON_COMMAND(ID_EDIT_DELETE_FROM_LIST, &CSearchResultList::OnEditDelete)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CSearchResultList::OnEditSelectAll)
	ON_COMMAND(ID_EDIT_SAVE_LOG_TO_FILE, &CSearchResultList::OnEditSaveToFile)
	ON_COMMAND(ID_EDIT_LOG_TO_EDITOR, &CSearchResultList::OnEditViewLogInEditor)
	ON_COMMAND(ID_EDIT_SEARCH_RESULT_WINDOWN_REVEALPATH, &CSearchResultList::OnEditRevealPath)
	ON_COMMAND(ID_EDIT_COPY_FULL_PATH, &CSearchResultList::OnEditCopyFullPath)
	ON_COMMAND(ID_EDIT_COUNT_SELECTION, &CSearchResultList::OnEditCountSelection)
	ON_COMMAND(ID_EDIT_SEND_RECYCLE_BIN, &CSearchResultList::OnEditSendToRecyclebin)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditFilter

IMPLEMENT_DYNAMIC(CEditFilter, CUndoRedoEditControl)

CEditFilter::CEditFilter()
{
}

CEditFilter::~CEditFilter()
{
}

CString CEditFilter::GetCurrentText()
{
	CString str;
	GetWindowText(str);
	return str;
}

BEGIN_MESSAGE_MAP(CEditFilter, CUndoRedoEditControl)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

BOOL CEditFilter::PreTranslateMessage(MSG* pMsg)
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

HBRUSH CEditFilter::CtlColor(CDC* pDC, UINT nCtlColor)
{
	pDC->SetTextColor(BasicColors::white);
	pDC->SetBkColor(BasicColors::light_green);
	return ::GetSysColorBrush(COLOR_WINDOW);
}

void CEditFilter::OnSetFocus(CWnd * pOldWnd)
{
	CUndoRedoEditControl::OnSetFocus(pOldWnd);
	if (GetCurrentText() == g_strSearchFilterMessage)
	{
		SetWindowTextW(_T(""));
	}
}

void CEditFilter::OnKillFocus(CWnd * pNewWnd)
{
	CUndoRedoEditControl::OnKillFocus(pNewWnd);
	if (GetCurrentText().IsEmpty())
	{
		SetWindowTextW(g_strSearchFilterMessage);
	}
}

void CEditFilter::SetCaretAtEndline()
{
	SetFocus();
	SetSel(0, -1);
	SetSel(-1);
}