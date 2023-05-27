/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "MessageWindow.h"
#include "Resource.h"
#include "VinaTextApp.h"
#include "MainFrm.h"
#include "AppUtil.h"
#include "EditorDoc.h"
#include "RAIIUtils.h"
#include "AppSettings.h"
#include "LocalizationHandler.h"

#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMessagePane, CDockPaneBase)

CMessagePane::CMessagePane()
{
}

CMessagePane::~CMessagePane()
{
}

BEGIN_MESSAGE_MAP(CMessagePane, CDockPaneBase)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(UMW_DOCK_PANE_UPDATE, &CMessagePane::OnDockPaneUpdate)
END_MESSAGE_MAP()

LRESULT CMessagePane::OnDockPaneUpdate(WPARAM wParam, LPARAM lParam)
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

void CMessagePane::UpdateUIVisual()
{
	m_LogPaneDlg.UpdateLogVisual();
}

int CMessagePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockPaneBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_LogPaneDlg.Create(ID_DIALOG_MESSAGE_PANE, this))
	{
		TRACE0("Failed to create output dialog windows\n");
		return -1;      // fail to create
	}
	m_LogPaneDlg.ShowWindow(SW_SHOW);

	AdjustLayout();

	return 0;
}

void CMessagePane::OnSize(UINT nType, int cx, int cy)
{
	CDockPaneBase::OnSize(nType, cx, cy);
	m_LogPaneDlg.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CMessagePane::AddLogMessage(const CString& str, COLORREF color)
{
	m_LogPaneDlg.AddLogMessage(str, color);
}

void CMessagePane::ClearAll()
{
	m_LogPaneDlg.ClearAll();
}

/////////////////////////////////////////////////////////////////////////////
// CRichEditCtrlEX

IMPLEMENT_DYNAMIC(CRichEditCtrlEX, CRichEditCtrl)

CRichEditCtrlEX::CRichEditCtrlEX()
{
}

CRichEditCtrlEX::~CRichEditCtrlEX()
{
}

BEGIN_MESSAGE_MAP(CRichEditCtrlEX, CRichEditCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_WM_SETCURSOR()
	ON_WM_ENTERMENULOOP()
	ON_WM_EXITMENULOOP()
	ON_COMMAND(ID_EDIT_MESSAGE_WINDOWN_OPENPATH, &CRichEditCtrlEX::OnEditOpenPath)
	ON_COMMAND(ID_EDIT_MESSAGE_WINDOWN_REVEALPATH, &CRichEditCtrlEX::OnEditRevealPath)
	ON_COMMAND(ID_EDIT_COPY, &CRichEditCtrlEX::OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, &CRichEditCtrlEX::OnEditClear)
	ON_COMMAND(ID_EDIT_GOOGLE_IT, &CRichEditCtrlEX::OnEditGoolgeIt)
	ON_COMMAND(ID_EDIT_TRANSLATE_IT, &CRichEditCtrlEX::OnEditTranslateIt)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CRichEditCtrlEX::OnEditSelectAll)
	ON_COMMAND(ID_EDIT_WRAPLINE_OUTPUT, &CRichEditCtrlEX::OnEditWrapLine)
	ON_COMMAND(ID_EDIT_LOG_TO_EDITOR, &CRichEditCtrlEX::OnEditViewLogInEditor)
	ON_COMMAND(ID_EDIT_COUNT_MESSAGE_LINE, &CRichEditCtrlEX::OnEditCountMessageLine)
END_MESSAGE_MAP()

BOOL CRichEditCtrlEX::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	BOOL bRet = FALSE;
	if (!m_bInMenu)
	{
		bRet = CRichEditCtrl::OnSetCursor(pWnd, nHitTest, message);
	}
	else
	{
		if (CWinApp* pApp = AfxGetApp())
		{
			HCURSOR hCur = pApp->LoadStandardCursor(IDC_ARROW);
			if (hCur)
			{
				::SetCursor(hCur);
				bRet = TRUE;
			}
		}
	}
	return bRet;
}

void CRichEditCtrlEX::OnEnterMenuLoop(IN CONST BOOL bIsTrackPopupMenu)
{
	CRichEditCtrl::OnEnterMenuLoop(bIsTrackPopupMenu);
	if (bIsTrackPopupMenu)
		m_bInMenu = TRUE;
}

void CRichEditCtrlEX::OnExitMenuLoop(IN CONST BOOL bIsTrackPopupMenu)
{
	CRichEditCtrl::OnExitMenuLoop(bIsTrackPopupMenu);
	if (bIsTrackPopupMenu)
		m_bInMenu = FALSE;
}

void CRichEditCtrlEX::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	if (menu.LoadMenu(IDR_OUTPUT_WINDOW_CONTEXT_MENU))
	{
		CMenu* pSubMenu = menu.GetSubMenu(0);
		if (!pSubMenu) return;
		VinaTextLocalization.TranslateContextMenu(pSubMenu);
		CString strSelectedPath = GetSelText().Trim();
		if (!PathFileExists(strSelectedPath))
		{
			pSubMenu->DeleteMenu(ID_EDIT_MESSAGE_WINDOWN_OPENPATH, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_EDIT_MESSAGE_WINDOWN_REVEALPATH, MF_BYCOMMAND);
		}
		if (m_bEnableLineWrap)
		{
			pSubMenu->CheckMenuItem(ID_EDIT_WRAPLINE_OUTPUT, MF_CHECKED | MF_BYCOMMAND);
		}
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

void CRichEditCtrlEX::OnEditCopy()
{
	CString strSelectedText = GetSelText();
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

void CRichEditCtrlEX::OnEditOpenPath()
{
	CString strSelectedText = GetSelText().Trim();
	if (PathFileExists(strSelectedText))
	{
		if (PathUtils::IsDirectory(strSelectedText))
		{
			PathUtils::OpenFileSystem(strSelectedText);
		}
		else
		{
			AppUtils::CreateDocumentFromFile(strSelectedText);
		}
	}
	else
	{
		AfxMessageBox(_T("[Open Path Error] path does not exist!"));
	}
}

void CRichEditCtrlEX::OnEditRevealPath()
{
	CString strSelectedText = GetSelText().Trim();
	strSelectedText.Replace(_T("\""), _T(""));
	if (PathFileExists(strSelectedText))
	{
		CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
		ASSERT(pFrame);
		if (!pFrame) return;
		pFrame->RevealInExplorerWindow(strSelectedText);
	}
	else
	{
		AfxMessageBox(_T("[Reveal In Explorer Error] path does not exist!"));
	}
}

void CRichEditCtrlEX::OnEditClear()
{
	SetWindowText(_T(""));
	UpdateData(FALSE);
}

void CRichEditCtrlEX::OnEditGoolgeIt()
{
	CString strSelectedText = GetSelText();
	CString strGoogleInstance = GOOGLE_SEARCH_API;
	strSelectedText.Replace(_T(" "), _T("+"));
	strGoogleInstance += strSelectedText;
	OSUtils::CreateProcessAsynchronous(TEXT("open"), strGoogleInstance, _T(""), _T(""), SW_MAXIMIZE);
}

void CRichEditCtrlEX::OnEditTranslateIt()
{
	CString strSelectedText = GetSelText();
	CString strGoogleTranslatePrefix = GOOGLE_TRANSLATE_PREFIX_API;
	CString strGoogleTranslateSuffix = GOOGLE_TRANSLATE_SUFFIX_API;
	strGoogleTranslatePrefix += strSelectedText + strGoogleTranslateSuffix;
	OSUtils::CreateProcessAsynchronous(TEXT("open"), strGoogleTranslatePrefix, _T(""), _T(""), SW_MAXIMIZE);
}

void CRichEditCtrlEX::OnEditSelectAll()
{
	CRichEditCtrl::SetSel(0, -1);
}

void CRichEditCtrlEX::OnEditViewLogInEditor()
{
	CString text = GetAllText();
	AppUtils::CreateNewEditorWithText(_T("Message Data"), text);
}

void CRichEditCtrlEX::OnEditWrapLine()
{
	TOGGLE_FLAG(m_bEnableLineWrap);
	if (m_bEnableLineWrap)
	{
		SetTargetDevice(NULL, 0);
	}
	else
	{
		SetTargetDevice(NULL, 1);
	}
}

void CRichEditCtrlEX::OnEditCountMessageLine()
{
	CString strSelectedText = GetSelText();
	int nLineCount = 0;
	if (strSelectedText.IsEmpty())
	{
		nLineCount = GetLineCount() - 1;
	}
	else
	{
		auto vectorLine = AppUtils::SplitterCString(strSelectedText, "\r");
		nLineCount = static_cast<int>(vectorLine.size());
	}
	AfxMessageBoxFormat(MB_ICONINFORMATION, _T("%d lines"), nLineCount);
}

CString CRichEditCtrlEX::GetCurrentTextLine()
{
	int nLineNum = LineFromChar(LineIndex(-1));
	CString strLine;
	const int nLineIndex = LineIndex(nLineNum);
	if (-1 != nLineIndex)
	{
		const int nLineLength = LineLength(nLineIndex);
		if (nLineLength > 0)
		{
			GetLine(nLineNum, strLine.GetBuffer(nLineLength), nLineLength + 1);
			strLine.ReleaseBuffer();
		}
	}
	return strLine;
}

CString CRichEditCtrlEX::GetAllText()
{
	CString strAllText;
	int lineCnt = GetLineCount();
	for (int i = 0; i < lineCnt; i++)
	{
		const int nLineIndex = LineIndex(i);
		if (-1 != nLineIndex)
		{
			const int nLineLength = LineLength(nLineIndex);
			if (nLineLength > 0)
			{
				CString strLine;
				GetLine(i, strLine.GetBuffer(nLineLength), nLineLength + 1);
				strLine.ReleaseBuffer();
				if (i == lineCnt - 1)
				{
					strAllText += strLine;
				}
				else
				{
					strAllText += strLine + _T("\r");
				}
			}
		}
	}
	return strAllText;
}

BOOL CRichEditCtrlEX::PreTranslateMessage(MSG * pMsg)
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
		}
		if (::GetKeyState(VK_CONTROL) < 0)
		{
			if (pMsg->wParam == 'E')
			{
				OnEditViewLogInEditor();
				return TRUE;
			}
			if (pMsg->wParam == 'O')
			{
				OnEditOpenPath();
				return TRUE;
			}
			if (pMsg->wParam == 'W')
			{
				OnEditWrapLine();
				return TRUE;
			}
			if (pMsg->wParam == 'L')
			{
				OnEditCountMessageLine();
				return TRUE;
			}
			if (pMsg->wParam == VK_DELETE)
			{
				OnEditClear();
				return TRUE;
			}
		}
		if (pMsg->wParam == VK_F1)
		{
			OnEditTranslateIt();
			return TRUE;
		}
		if (pMsg->wParam == VK_F3)
		{
			OnEditGoolgeIt();
			return TRUE;
		}
	}
	return CRichEditCtrl::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// CMessagePaneDlg dialog

IMPLEMENT_DYNAMIC(CMessagePaneDlg, CDialogEx)

CMessagePaneDlg::CMessagePaneDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ID_DIALOG_MESSAGE_PANE, pParent)
{
	IMPLEMENT_FONT_SETTING_DOCK_WINDOW
}

CMessagePaneDlg::~CMessagePaneDlg()
{
}

void CMessagePaneDlg::OnOK()
{
}

void CMessagePaneDlg::OnCancel()
{
}

BEGIN_MESSAGE_MAP(CMessagePaneDlg, CDialogEx)
	ON_WM_MOVING()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMessagePaneDlg message handlers

void CMessagePaneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CMessagePaneDlg::AddLogMessage(const CString& str, COLORREF color)
{
	if (str.IsEmpty()) return;

	long lVisible = 0;
	long lInsertionPoint = 0;
	CHARFORMAT cf;

	// Initialize character format structure
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR;
	cf.dwEffects = 0; // To disable CFE_AUTOCOLOR
	cf.crTextColor = color;

	// Set insertion point to end of text
	lInsertionPoint = m_wndOutput.GetWindowTextLength();
	m_wndOutput.SetSel(lInsertionPoint, -1);

	// Set the character format
	m_wndOutput.SetSelectionCharFormat(cf);

	if (str.Find('\n') != -1)
	{
		m_wndOutput.ReplaceSel(str);
	}
	else
	{
		m_wndOutput.ReplaceSel(str + '\n');
	}

	lVisible = GetNumVisibleLines(&m_wndOutput);

	if (&m_wndOutput != m_wndOutput.GetFocus())
	{
		m_wndOutput.LineScroll(INT_MAX);
		m_wndOutput.LineScroll(1 - lVisible);
	}
}

int CMessagePaneDlg::GetNumVisibleLines(CRichEditCtrl* pCtrl)
{
	CRect rect;
	long lFirstChar, lLastChar;
	long lFirstLine, lLastLine;

	// Get client rect of rich edit control
	pCtrl->GetClientRect(rect);

	// Get character index close to upper left corner
	lFirstChar = pCtrl->CharFromPos(CPoint(0, 0));

	// Get character index close to lower right corner
	lLastChar = pCtrl->CharFromPos(CPoint(rect.right, rect.bottom));
	if (lLastChar < 0)
	{
		lLastChar = pCtrl->GetTextLength();
	}

	// Convert to lines
	lFirstLine = pCtrl->LineFromChar(lFirstChar);
	lLastLine = pCtrl->LineFromChar(lLastChar);

	return (lLastLine - lFirstLine);
}

void CMessagePaneDlg::ClearAll()
{
	m_wndOutput.SetWindowText(_T(""));
	m_wndOutput.UpdateData(FALSE);
}

void CMessagePaneDlg::OnMoving(UINT nSide, LPRECT lpRect)
{
	CDialogEx::OnMoving(nSide, lpRect);

	CRect CurRect;
	GetWindowRect(&CurRect);

	lpRect->left = CurRect.left;
	lpRect->top = CurRect.top;
	lpRect->right = CurRect.right;
	lpRect->bottom = CurRect.bottom;
}

void CMessagePaneDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (!cx || !cy) return;

	CRect rc;
	GetClientRect(rc);

	if (m_wndOutput.GetSafeHwnd())
	{
		m_wndOutput.SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

BOOL CMessagePaneDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UINT nMenuf = MF_BYCOMMAND | MF_GRAYED | MF_DISABLED;
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu)
	{
		pSysMenu->EnableMenuItem(SC_CLOSE, nMenuf);
	}

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	const DWORD dwStyle = ES_MULTILINE | ES_READONLY | ES_WANTRETURN | WS_VSCROLL | WS_HSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE;
	if (!m_wndOutput.Create(dwStyle, rectDummy, this, ID_RICHEDIT_OUTPUT_PANE))
	{
		TRACE0("Failed to create output windows\n");
		return -1;      // fail to create
	}

	// To turn word wrap on - based on window width
	m_wndOutput.SetTargetDevice(NULL, 0);
	m_wndOutput.SetFont(&m_Font);
	m_wndOutput.SetBackgroundColor(FALSE, AppSettingMgr.m_AppThemeColor);
	m_wndOutput.LimitText(0xfffffff);
	m_wndOutput.m_bEnableLineWrap = FALSE;
	AddLogMessage(_T("> Thank you for using VinaText, copyright(C) www.vinatext.dev\n"),
		IS_LIGHT_THEME ? BasicColors::black : BasicColors::white);

	UpdateData(FALSE);
	return TRUE;
}

void CMessagePaneDlg::UpdateLogVisual()
{
	m_wndOutput.SetWindowText(_T(""));
	m_wndOutput.UpdateData(FALSE);
	m_wndOutput.SetFont(&m_Font);
	m_wndOutput.SetBackgroundColor(FALSE, AppSettingMgr.m_AppThemeColor);
}