/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "BookmarkWindow.h"
#include "VinaTextApp.h"
#include "MainFrm.h"
#include "EditorDoc.h"
#include "AppUtil.h"
#include "RAIIUtils.h"
#include "AppSettings.h"
#include "FileUtil.h"
#include "LocalizationHandler.h"

#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CBookmarkWindow, CDockPaneBase)

CBookmarkWindow::CBookmarkWindow()
{
}

CBookmarkWindow::~CBookmarkWindow()
{
}

BEGIN_MESSAGE_MAP(CBookmarkWindow, CDockPaneBase)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(UMW_DOCK_PANE_UPDATE, &CBookmarkWindow::OnDockPaneUpdate)
END_MESSAGE_MAP()

LRESULT CBookmarkWindow::OnDockPaneUpdate(WPARAM wParam, LPARAM lParam)
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

int CBookmarkWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockPaneBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_BookMarkPaneDlg.Create(IDD_SEARCH_RESULT_DLG, this))
	{
		TRACE0("Failed to create output dialog windows\n");
		return -1;      // fail to create
	}
	m_BookMarkPaneDlg.ShowWindow(SW_SHOW);
	return 0;
}

void CBookmarkWindow::OnSize(UINT nType, int cx, int cy)
{
	CDockPaneBase::OnSize(nType, cx, cy);
	m_BookMarkPaneDlg.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CBookmarkWindow::AddBookmarkData(const BOOKMARK_LINE_DATA & data)
{
	m_BookMarkPaneDlg.AddBookmarkData(data);
}

void CBookmarkWindow::ClearAll()
{
	m_BookMarkPaneDlg.ClearBookmarkData();
}

void CBookmarkWindow::UpdateUIVisual()
{
	m_BookMarkPaneDlg.UpdateListCtrlVisual();
}

/////////////////////////////////////////////////////////////////////////////
// CBookmarkDlg dialog

IMPLEMENT_DYNAMIC(CBookmarkDlg, CDialogEx)

CBookmarkDlg::CBookmarkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SEARCH_RESULT_DLG, pParent)
{
	IMPLEMENT_FONT_SETTING_DOCK_WINDOW
}

CBookmarkDlg::~CBookmarkDlg()
{
	SaveBookmarkData();
}

BEGIN_MESSAGE_MAP(CBookmarkDlg, CDialogEx)
	ON_WM_MOVING()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_SEARCH_RESULT, OnGetdispinfoList)
	ON_NOTIFY(LVN_ODFINDITEM, IDC_LIST_SEARCH_RESULT, OnOdfinditemList)
	ON_NOTIFY(LVN_ODCACHEHINT, IDC_LIST_SEARCH_RESULT, OnOdcachehintList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SEARCH_RESULT, OnItemchangedList)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SEARCH_RESULT, OnClickList)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_SEARCH_RESULT, OnKeydownList)
END_MESSAGE_MAP()

// CBookmarkDlg message handlers

void CBookmarkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SEARCH_RESULT, m_wndBookmarkList);
}

void CBookmarkDlg::AddBookmarkData(const BOOKMARK_LINE_DATA & data)
{
	if (data._bDeleteFromList)
	{
		m_BookmarkData.erase(std::remove_if(
			m_BookmarkData.begin(),
			m_BookmarkData.end(),
			[&](BOOKMARK_LINE_DATA const & internalData)
		{
			return internalData._strTargetFile.CompareNoCase(data._strTargetFile) == 0
				&& internalData._nLineNumber == data._nLineNumber;
		}),
		m_BookmarkData.end());
	}
	else
	{
		m_BookmarkData.push_back(data);
	}
	//Resize the list to add the elements to the list
	ListView_SetExtendedListViewStyle(m_wndBookmarkList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndBookmarkList.SetItemCount(static_cast<int>(m_BookmarkData.size()));
}

void CBookmarkDlg::ClearBookmarkData()
{
	// update editor
	for (auto const& data : m_BookmarkData)
	{
		auto pOpenedDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetExistedDocument(data._strTargetFile));
		if (pOpenedDoc && pOpenedDoc->GetEditorCtrl()->IsLineHasBookMark(data._nLineNumber))
		{
			pOpenedDoc->GetEditorCtrl()->DeleteBookMark(data._nLineNumber, data._strTargetFile);
		}
	}
	m_BookmarkData.clear();
	BOOKMARK_LINE_DATA_LIST().swap(m_BookmarkData);
	//Resize the list to add the elements to the list
	ListView_SetExtendedListViewStyle(m_wndBookmarkList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndBookmarkList.SetItemCount(0);
	m_wndBookmarkList.DeleteAllItems();
}

void CBookmarkDlg::ClearSelectedBoorkmark()
{
	if (m_wndBookmarkList.GetItemCount() == 0) return;
	CString strItem = m_wndBookmarkList.GetSelectedItemsText();
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
			m_BookmarkData.erase(std::remove_if(
				m_BookmarkData.begin(),
				m_BookmarkData.end(),
				[&](BOOKMARK_LINE_DATA const & internalData)
			{
				return internalData._strTargetFile.CompareNoCase(strFileTarget) == 0
					&& internalData._nLineNumber == nLineNumber;
			}),
				m_BookmarkData.end());
			//Resize the list to add the elements to the list
			ListView_SetExtendedListViewStyle(m_wndBookmarkList.m_hWnd, LVS_EX_FULLROWSELECT);
			m_wndBookmarkList.SetItemCount(static_cast<int>(m_BookmarkData.size()));
			// update editor
			auto pOpenedDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetExistedDocument(strFileTarget));
			if (pOpenedDoc && pOpenedDoc->GetEditorCtrl()->IsLineHasBookMark(nLineNumber))
			{
				pOpenedDoc->GetEditorCtrl()->DeleteBookMark(nLineNumber, strFileTarget);
			}
		}
		else
		{
			AfxMessageBox(_T("[Delete Error] bookmark path does not exist!"));
		}
		
	}
}

void CBookmarkDlg::OnMoving(UINT nSide, LPRECT lpRect)
{
	CDialogEx::OnMoving(nSide, lpRect);
	CRect CurRect;
	GetWindowRect(&CurRect);
	lpRect->left = CurRect.left;
	lpRect->top = CurRect.top;
	lpRect->right = CurRect.right;
	lpRect->bottom = CurRect.bottom;
}

void CBookmarkDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (!cx || !cy) return;
	CRect rectClient;
	GetClientRect(rectClient);
	if (m_wndBookmarkList.GetSafeHwnd())
	{
		m_wndBookmarkList.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void CBookmarkDlg::OnOK()
{
}

void CBookmarkDlg::OnCancel()
{
}

BOOL CBookmarkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UINT nMenuf = MF_BYCOMMAND | MF_GRAYED | MF_DISABLED;
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu)
	{
		pSysMenu->EnableMenuItem(SC_CLOSE, nMenuf);
	}
	InitListCtrl();
	LoadBookmarkData();
	return TRUE;
}

//This function is called when the list needs data. This is the most
//critical function when working with virtual lists.
void CBookmarkDlg::OnGetdispinfoList(NMHDR * pNMHDR, LRESULT * pResult)
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
			text = AppUtils::IntToCString(m_BookmarkData[itemid]._nLineNumber);
		}
		else if (pItem->iSubItem == 1)
		{
			//Text is _strTargetFile
			text = m_BookmarkData[itemid]._strTargetFile;
		}
		else if (pItem->iSubItem == 2)
		{
			//Text is _strLine
			text = m_BookmarkData[itemid]._strLine;
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
void CBookmarkDlg::OnOdfinditemList(NMHDR * pNMHDR, LRESULT * pResult)
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
	if (startPos >= m_wndBookmarkList.GetItemCount())
		startPos = 0;
	int currentPos = startPos;

	////Let's search...
	do
	{
		//Do this word begins with all characters in searchstr?
		if (m_BookmarkData[currentPos]._strTargetFile.Find(searchstr) != -1)
		{
			//Select this item and stop search.
			*pResult = currentPos;
			break;
		}
		//Go to next item
		currentPos++;
		//Need to restart at top?
		if (currentPos >= m_wndBookmarkList.GetItemCount())
			currentPos = 0;
		//Stop if back to start
	} while (currentPos != startPos);
}

//This is called to give you a chance to catch data. Useless in most cases
void CBookmarkDlg::OnOdcachehintList(NMHDR * pNMHDR, LRESULT * pResult)
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
void CBookmarkDlg::OnClickList(NMHDR * pNMHDR, LRESULT * pResult)
{
	NMLISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	LVHITTESTINFO hitinfo;
	//Copy click point
	hitinfo.pt = pNMListView->ptAction;
	//Make the hit test...
	int item = m_wndBookmarkList.HitTest(&hitinfo);

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
void CBookmarkDlg::OnKeydownList(NMHDR * pNMHDR, LRESULT * pResult)
{
	LV_KEYDOWN* pLVKeyDown = (LV_KEYDOWN*)pNMHDR;
	//If user press space, toggle flag on selected item
	if (pLVKeyDown->wVKey == VK_SPACE)
	{
	}
	*pResult = 0;
}

void CBookmarkDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if ((pNMListView->uChanged & LVIF_STATE) && (pNMListView->uNewState & LVIS_SELECTED))
	{
		m_wndBookmarkList.OnOutputGotoLine();
	}
}

void CBookmarkDlg::InitListCtrl()
{
	ListView_SetExtendedListViewStyle(m_wndBookmarkList.m_hWnd, LVS_EX_FULLROWSELECT);
	m_wndBookmarkList.InsertColumn(0, _T("Line Number"), LVCFMT_LEFT, 100);
	m_wndBookmarkList.InsertColumn(1, _T("File Path"), LVCFMT_LEFT, 600);
	m_wndBookmarkList.InsertColumn(2, _T("Line Text"), LVCFMT_LEFT, 800);
	UpdateListCtrlVisual();
}

void CBookmarkDlg::UpdateListCtrlVisual()
{
	m_wndBookmarkList.SetFont(&m_Font);
	m_wndBookmarkList.SetBkColor(AppSettingMgr.m_AppThemeColor);
	m_wndBookmarkList.SetTextColor(IS_LIGHT_THEME ? BasicColors::black : BasicColors::white);
	m_wndBookmarkList.SetTextBkColor(AppSettingMgr.m_AppThemeColor);
}

void CBookmarkDlg::SaveBookmarkData()
{
	CString strFilePath = PathUtils::GetVinaTextAppDataPath() + _T("bookmark-window-state.dat");
	CAppDataFile writer(strFilePath, CAppDataFile::SERIALIZE_MODE::WRITE);
	writer.SerializeBookmarkDataIn(m_BookmarkData);
}

void CBookmarkDlg::LoadBookmarkData()
{
	CString strJsonFilePath = PathUtils::GetVinaTextAppDataPath() + _T("bookmark-window-state.dat");
	if (!PathFileExists(strJsonFilePath))
	{
		return;
	}
	CString strFilePath = PathUtils::GetVinaTextAppDataPath() + _T("bookmark-window-state.dat");
	CAppDataFile reader(strFilePath, CAppDataFile::SERIALIZE_MODE::READ);
	BOOKMARK_LINE_DATA_LIST BookmarkDatalist;
	reader.SerializeBookmarkDataOut(BookmarkDatalist);
	for (auto const& bookmark : BookmarkDatalist)
	{
		AddBookmarkData(bookmark);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBookmarkList

IMPLEMENT_DYNAMIC(CBookmarkList, CListCtrl)

CBookmarkList::CBookmarkList()
{
}

CBookmarkList::~CBookmarkList()
{
}

CString CBookmarkList::GetSelectedItemsText()
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

CString CBookmarkList::GetItemsText()
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

void CBookmarkList::OnContextMenu(CWnd * pWnd, CPoint point)
{
	CMenu menu;
	if (menu.LoadMenu(IDR_BOOKMARK_WINDOW_CONTEXT_MENU))
	{
		CMenu* pSubMenu = menu.GetSubMenu(0);
		if (!pSubMenu) return;
		VinaTextLocalization.TranslateContextMenu(pSubMenu);
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

void CBookmarkList::OnEditCopy()
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

void CBookmarkList::OnEditClear()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		CBookmarkDlg* pPaneDlg = dynamic_cast<CBookmarkDlg*>(GetParent());
		if (pPaneDlg)
		{
			pPaneDlg->ClearBookmarkData();
		}
	}
}

void CBookmarkList::OnEditClearSelected()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		CBookmarkDlg* pPaneDlg = dynamic_cast<CBookmarkDlg*>(GetParent());
		if (pPaneDlg)
		{
			pPaneDlg->ClearSelectedBoorkmark();
		}
	}
}

void CBookmarkList::OnEditSelectall()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		SetItemState(-1, LVIS_SELECTED, LVIS_SELECTED);
	}
}

void CBookmarkList::OnEditSaveToFile()
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
	void GotoLineInEditor(CEditorCtrl* pEditor, const CString& strLineNumber, const CString& strFileTarget)
	{
		if (pEditor)
		{
			int nLine = AppUtils::CStringToInt(strLineNumber);
			pEditor->GotoLine(nLine);
			pEditor->SetLineCenterDisplay(nLine);
			if (!pEditor->IsLineHasBookMark(pEditor->AddBookMark(nLine, strFileTarget)))
			{
				pEditor->AddBookMark(nLine, strFileTarget);
			}
		}
	}
}

void CBookmarkList::OnOutputGotoLine()
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

void CBookmarkList::OnEditViewLogInEditor()
{
	if (GetFocus()->m_hWnd == m_hWnd)
	{
		CString text = GetItemsText();
		AppUtils::CreateNewEditorWithText(_T("Bookmark Data"), text);
	}
}

void CBookmarkList::OnEditRevealPath()
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

void CBookmarkList::OnLButtonDown(UINT nFlags, CPoint point)
{
	CListCtrl::OnLButtonDown(nFlags, point);
	OnOutputGotoLine();
}

void CBookmarkList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CListCtrl::OnLButtonDblClk(nFlags, point);
	OnEditRevealPath();
}

BOOL CBookmarkList::PreTranslateMessage(MSG * pMsg)
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

BEGIN_MESSAGE_MAP(CBookmarkList, CListCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, &CBookmarkList::OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, &CBookmarkList::OnEditClear)
	ON_COMMAND(ID_EDIT_CLEAR_SELECTED, &CBookmarkList::OnEditClearSelected)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CBookmarkList::OnEditSelectall)
	ON_COMMAND(ID_EDIT_SAVE_LOG_TO_FILE, &CBookmarkList::OnEditSaveToFile)
	ON_COMMAND(ID_EDIT_LOG_TO_EDITOR, &CBookmarkList::OnEditViewLogInEditor)
	ON_COMMAND(ID_EDIT_BOOKMARK_WINDOWN_REVEALPATH, &CBookmarkList::OnEditRevealPath)
END_MESSAGE_MAP()