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
#include "EditorDoc.h"
#include "FindResult.h"
#include "AppUtil.h"
#include "RAIIUtils.h"
#include "AppSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning(disable : 4996)

/////////////////////////////////////////////////////////////////////////////
// COutputBar

CFindResultPane::CFindResultPane()
{
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	_tcscpy_s(lf.lfFaceName, 32 * sizeof(CHAR), AppSettingMgr.m_DockWindowFontSetting._font);
	lf.lfHeight = AppSettingMgr.m_DockWindowFontSetting._lfHeight;
	lf.lfWeight = AppSettingMgr.m_DockWindowFontSetting._lfWeight;
	m_Font.CreateFontIndirect(&lf);
}

CFindResultPane::~CFindResultPane()
{
}

BEGIN_MESSAGE_MAP(CFindResultPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_MESSAGE(UMW_DOCK_PANE_UPDATE, &CFindResultPane::OnDockPaneUpdate)
END_MESSAGE_MAP()

int CFindResultPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectClient(0, 0, lpCreateStruct->cx, lpCreateStruct->cy);

	const DWORD dwStyle = LBS_NOTIFY | LBS_EXTENDEDSEL | LBS_MULTIPLESEL |
		LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

	if (!m_wndOutput.Create(dwStyle, rectClient, this, 1))
	{
		TRACE0("Failed to create output window\n");
		return -1;      // fail to create
	}

	m_wndOutput.ModifyStyleEx(NULL, WS_EX_STATICEDGE);
	m_wndOutput.SetFont(&m_Font);
	FillInitialWindow();

	return 0;
}

void CFindResultPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	CRect rc;
	GetClientRect(rc);
	if (m_wndOutput.GetSafeHwnd())
	{
		m_wndOutput.SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
		AdjusrHorzScroll(m_wndOutput);
	}
}

void CFindResultPane::AdjusrHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	int cxExtentMax = 0;
	for (int i = 0; i < wndListBox.GetCount(); i ++)
	{
		CString strItem;
		wndListBox.GetText(i, strItem);
		cxExtentMax = max(cxExtentMax, dc.GetTextExtent(strItem).cx);
	}
	wndListBox.SetHorizontalExtent(cxExtentMax);
}

void CFindResultPane::FillInitialWindow()
{
	m_wndOutput.AddString(_T("The search result will be displayed here..."));
}

void CFindResultPane::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	m_wndOutput.GetWindowRect(rect);
	ScreenToClient(rect);

	rect.InflateRect(1, 1);
	dc.Draw3dRect(rect, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFindResultPane::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndOutput.SetFocus();
}

void CFindResultPane::AddSearchData(CString strSearchWhat, CString strSearchScope, const RESULT_SEARCH_DATA& ResultSearchData, BOOL bAppendResult, BOOL bShowFileNameOnly)
{
	CLockCtrlRedraw lock(this);
	if (bAppendResult == FALSE)
	{
		m_wndOutput.ResetContent();
	}
	m_wndOutput.SetSeachWhatString(strSearchWhat);
	CString strResult = _T("Search all \"%s\" in the scope %s:");
	strResult.Format(strResult, strSearchWhat, strSearchScope);
	AddString(strResult);
	CString strPreviousTargetFile;
	for (auto const& data : ResultSearchData._vecResultSearchInfo)
	{
		if (strPreviousTargetFile != data._strTargetFile)
		{
			AddString(_T("\n________________________________________________________________________\n"));
		}

		CString _strFile;
		if (bShowFileNameOnly)
		{ 
			_strFile = PathUtils::GetFilenameFromPath(data._strTargetFile);
		}
		else
		{
			_strFile = data._strTargetFile;
		}
		CString strLine =CSTRING_SPACE + _strFile + _T(" | ") + AppUtils::IntToCString(data._nLineNumber) +
			+_T(" | ") + data._strLine.Mid(0, 200) + _T(" | (") + AppUtils::IntToCString(data._nMatched) + _T(" matcheds)");

		strLine.Replace(_T("\r"), _T(""));
		AddString(strLine);
		strPreviousTargetFile = data._strTargetFile;
	}
	AddString(_T("\n________________________________________________________________________\n"));
	CString strTotalResult = _T("> [Search statistics] searched files: %d - matched lines: %d - matched words: %d - time: %fs");
	strTotalResult.Format(strTotalResult, (int)ResultSearchData._nFile, 
		(int)ResultSearchData._vecResultSearchInfo.size(), ResultSearchData._nMatchedWords, ResultSearchData._TimeMeasured);
	AddString(strTotalResult);
}

void CFindResultPane::AddReplaceData(CString strSearchWhat, CString strReplaceWith, CString strSearchScope, const RESULT_SEARCH_DATA& ResultSearchData, BOOL bAppendResult, BOOL bShowFileNameOnly)
{
	CLockCtrlRedraw lock(this);
	if (bAppendResult == FALSE)
	{
		m_wndOutput.ResetContent();
	}
	m_wndOutput.SetSeachWhatString(strReplaceWith);
	CString strResult = _T("Replace all \"%s\" with \"%s\" in the scope %s:");
	strResult.Format(strResult, strSearchWhat, strReplaceWith, strSearchScope);
	AddString(strResult);
	CString strPreviousTargetFile;
	for (auto const& data : ResultSearchData._vecResultSearchInfo)
	{
		if (strPreviousTargetFile != data._strTargetFile)
		{
			AddString(_T("\n________________________________________________________________________\n"));
		}

		CString _strFile;
		if (bShowFileNameOnly)
		{
			_strFile = PathUtils::GetFilenameFromPath(data._strTargetFile);
		}
		else
		{
			_strFile = data._strTargetFile;
		}
		CString strLine =CSTRING_SPACE + data._strTargetFile + _T(" | ") + AppUtils::IntToCString(data._nLineNumber) +
			+_T(" | ") + data._strLine.Mid(0, 200) + _T(" | (") + AppUtils::IntToCString(data._nMatched) + _T(" replaceds)");

		strLine.Replace(_T("\r"), _T(""));
		AddString(strLine);
		strPreviousTargetFile = data._strTargetFile;
	}
	AddString(_T("\n________________________________________________________________________\n"));
	CString strTotalResult = _T("> [Replace statistics] replaced files: %d - replaced lines: %d - replaced words: %d - time: %fs");
	strTotalResult.Format(strTotalResult, (int)ResultSearchData._nFile, 
		(int)ResultSearchData._vecResultSearchInfo.size(), ResultSearchData._nMatchedWords, ResultSearchData._TimeMeasured);;
	AddString(strTotalResult);
}

void CFindResultPane::AddString(CString str)
{
	int iItem = m_wndOutput.AddString(str);
	m_wndOutput.SetTopIndex(iItem);
}

void CFindResultPane::ClearAll()
{
	m_wndOutput.ClearAll();
}

LRESULT CFindResultPane::OnDockPaneUpdate(WPARAM wParam, LPARAM lParam)
{
	WORD wMsgTarget = LOWORD(wParam);
	WORD wMsgHint = HIWORD(wParam);

	if (MAIN_FRAME_UPDATE_MSG::MAIN_FRAME_UPDATE_ALL_DOCKPANE == wMsgTarget)
	{
		switch (wMsgHint)
		{
		case MAIN_FRAME_UPDATE_HINT::MAIN_FRAME_UPDATE_HINT_SETTING_CHANGED:
		{
			UpdateAppSetting();
		}
		break;
		}
	}
	return 0L;
}

void CFindResultPane::UpdateAppSetting()
{
}

/////////////////////////////////////////////////////////////////////////////
// CResultList1

IMPLEMENT_DYNAMIC(CResultList, CListBox)

CResultList::CResultList()
{
}

CResultList::~CResultList()
{
}

void CResultList::ClearAll()
{
	CListBox::ResetContent();
}

CString CResultList::GetAllText()
{
	CString strAllText;
	int lineCnt = GetCount();
	for (int i = 0; i < lineCnt; i++)
	{
		CString strLine;
		CListBox::GetText(i, strLine);
		strAllText += strLine + _T("\r");
	}
	return strAllText;
}

BEGIN_MESSAGE_MAP(CResultList, CListBox)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, &CResultList::OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, &CResultList::OnEditClear)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CResultList::OnEditSelectall)
	ON_COMMAND(ID_EDIT_SAVE_LOG_TO_FILE, &CResultList::OnEditSaveToFile)
	ON_COMMAND(ID_EDIT_LOG_TO_EDITOR, &CResultList::OnEditViewLogInEditor)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultList message handlers

void CResultList::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_SEARCH_RESULT_WINDOW_CONTEXT_MENU);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}

	SetFocus();
}

void CResultList::OnEditCopy()
{
	CArray<int, int> sels;
	int n = CListBox::GetSelCount();
	if (n <= 0)
		return; // nothing to copy

	sels.SetSize(n);
	CListBox::GetSelItems(n, sels.GetData());

	CString s;
	//*****************************************************************************
	// This segment of code only works if the listbox is non-owner-draw,          *
	// or is owner-draw with LBS_HASSTRINGS                                       *
	// So first check to make sure this is true                                   *
	//*****************************************************************************
	ASSERT((GetStyle() & (LBS_OWNERDRAWFIXED | LBS_OWNERDRAWVARIABLE)) == 0 || //*
		(GetStyle() & LBS_HASSTRINGS) == LBS_HASSTRINGS);                   //*

	for (int i = 0; i < n; i++)                                                 
	{ /* copy items */                                                    
		CString t;                                                              
		CListBox::GetText(sels[i], t);                                         
		t += _T("\r");                                                       
		s += t;                                                              
	} /* copy items */                                                      

	HGLOBAL g = ::GlobalAlloc(GMEM_MOVEABLE, (s.GetLength() + 1) * sizeof(TCHAR));
	if (g == NULL)
	{ /* alloc failed */
		ASSERT(FALSE);  // failed to allocate memory
		return;
	} /* alloc failed */

	LPTSTR p = (LPTSTR)::GlobalLock(g);
	if (p == NULL)
	{ /* lock failed */
		ASSERT(FALSE);
		return;
	} /* lock failed */

	StringCchCopy(p, s.GetLength() + 1, (LPCTSTR)s);

	::GlobalUnlock(g);

	if (!OpenClipboard())
	{ /* clipboard open failed */
		ASSERT(FALSE);
		GlobalFree(g);
		return;
	} /* clipboard open failed */

	if (!EmptyClipboard())
	{ /* empty failed */
		ASSERT(FALSE);
		GlobalFree(g);
		return;
	} /* empty failed */

#ifdef _UNICODE
#define CF_ CF_UNICODETEXT 
#else
#define CF_ CF_TEXT
#endif
	if (::SetClipboardData(CF_, g) == NULL)
	{ /* SetClipboardData failed */
		ASSERT(FALSE); //
		::CloseClipboard();
		::GlobalFree(g);
		return;
	} /* SetClipboardData failed */
	::CloseClipboard();
}

void CResultList::OnEditClear()
{
	CListBox::ResetContent();
}

void CResultList::OnEditSelectall()
{
	if (::IsWindow(m_hWnd))
	{
		SelItemRange(TRUE, 0, GetCount() - 1);
	}
}

void CResultList::OnEditSaveToFile()
{
	TCHAR  szFilter[] = _T("Text File(*.txt)|*.txt|CSV File(*.csv)|*.csv||");
	CFileDialog fileDlg(FALSE, _T("txt"), _T("*.txt"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
	if (fileDlg.DoModal() == IDOK)
	{
		CString filename = fileDlg.GetPathName();
		CString text = GetAllText();
		PathUtils::SaveFileTrunc(filename, text);
	}
}

void CResultList::OnOutputGotoLine()
{
	if (CListBox::GetCount() == 0) return;
	int iSel = GetCurSel();
	if (iSel != LB_ERR)
	{
		CString strItem;
		CListBox::GetText(iSel, strItem);
		if (!strItem.IsEmpty())
		{
			int nPos = strItem.Find(_T("|"));
			CString strFileTarget = strItem.Mid(0, nPos).Trim();
			CString strLineTarget = strItem.Mid(nPos + 1).Trim();
			int nPos2 = strLineTarget.Find(_T("|"));
			CString strLineNumber = strLineTarget.Mid(0, nPos2).Trim();
			if (strFileTarget.IsEmpty() || strLineNumber.IsEmpty()) return;
			if (PathFileExists(strFileTarget))
			{
				auto pOpenedDoc = AppUtils::GetExistedDocument(strFileTarget);
				if (!pOpenedDoc)
				{
					AppUtils::CreateDocumentFromFile(strFileTarget);
					auto pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
					if (pEditorDoc)
					{
						auto pEditor = pEditorDoc->GetEditorCtrl();
						if (pEditor)
						{
							int nLine = AppUtils::CStringToInt(strLineNumber);
							pEditor->GotoLine(nLine);
							pEditor->SetLineCenterDisplay(nLine);
							pEditor->RenderSearchResultInLine(nLine, m_strSeachWhat);
						}
					}
				}
				else
				{
					if (AppUtils::SetActiveDocument(pOpenedDoc))
					{
						auto pEditorDoc = dynamic_cast<CEditorDoc*>(pOpenedDoc);
						if (pEditorDoc)
						{
							auto pEditor = pEditorDoc->GetEditorCtrl();
							if (pEditor)
							{
								int nLine = AppUtils::CStringToInt(strLineNumber);
								pEditor->GotoLine(nLine);
								pEditor->SetLineCenterDisplay(nLine);
								pEditor->RenderSearchResultInLine(nLine, m_strSeachWhat);
							}
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
										auto pEditor = pEditorDoc->GetEditorCtrl();
										if (pEditor)
										{
											int nLine = AppUtils::CStringToInt(strLineNumber);
											pEditor->GotoLine(nLine);
											pEditor->SetLineCenterDisplay(nLine);
											pEditor->RenderSearchResultInLine(nLine, m_strSeachWhat);
										}
									}
								}
								break;
							}
							else
							{
								break;
							}
						}
					}
				}
			}
		}
	}
}

HBRUSH CResultList::CtlColor(CDC * pDC, UINT nCtlColor)
{
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkMode(TRANSPARENT);
	return CreateSolidBrush(AppSettingMgr.m_ThemeColor);
}

void CResultList::OnLButtonDown(UINT nFlags, CPoint point)
{
	CListBox::OnLButtonDown(nFlags, point);
	OnOutputGotoLine();
}

void CResultList::OnEditViewLogInEditor()
{
	CString text = GetAllText();
	AppUtils::CreateNewEditorWithText(_T("Find Result Data"), text);
}

BOOL CResultList::PreTranslateMessage(MSG * pMsg)
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
		}
	}
	return CListBox::PreTranslateMessage(pMsg);
}