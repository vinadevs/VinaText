/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "BuildWindow.h"
#include "Resource.h"
#include "VinaTextApp.h"
#include "MainFrm.h"
#include "AppUtil.h"
#include "EditorDoc.h"
#include "EditorView.h"
#include "MultiThreadWorker.h"
#include "AppSettings.h"
#include "Debugger.h"
#include "RAIIUtils.h"
#include "LocalizationHandler.h"

#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CBuildPane, CDockPaneBase)

CBuildPane::CBuildPane()
{
}

CBuildPane::~CBuildPane()
{
}

BEGIN_MESSAGE_MAP(CBuildPane, CDockPaneBase)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(UMW_DOCK_PANE_UPDATE, &CBuildPane::OnDockPaneUpdate)
END_MESSAGE_MAP()

LRESULT CBuildPane::OnDockPaneUpdate(WPARAM wParam, LPARAM lParam)
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

void CBuildPane::UpdateUIVisual()
{
	m_LogPaneDlg.UpdateLogVisual();
}

int CBuildPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockPaneBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_LogPaneDlg.Create(ID_DIALOG_BUILD_PANE, this))
	{
		TRACE0("Failed to create output dialog windows\n");
		return -1;      // fail to create
	}

	m_LogPaneDlg.ShowWindow(SW_SHOW);

	AdjustLayout();

	return 0;
}

void CBuildPane::OnSize(UINT nType, int cx, int cy)
{
	CDockPaneBase::OnSize(nType, cx, cy);
	m_LogPaneDlg.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CBuildPane::AddLogMessage(CString strMsg, COLORREF color)
{
	m_LogPaneDlg.AddLogMessage(strMsg, color);
}

void CBuildPane::ClearAll()
{
	m_LogPaneDlg.ClearAll();
}

void CBuildPane::ShowErrorLineOnEditor()
{
	m_LogPaneDlg.ShowErrorLineOnEditor();
}

/////////////////////////////////////////////////////////////////////////////
// CRichEditCtrlBuild

IMPLEMENT_DYNAMIC(CRichEditCtrlBuild, CRichEditCtrl)

CRichEditCtrlBuild::CRichEditCtrlBuild()
{
}

CRichEditCtrlBuild::~CRichEditCtrlBuild()
{
}

static BOOL IsBuildInformationMessage(const CString& strline)
{
	if (strline.Find(_T(">------ VinaText build started | Project:")) != -1 || strline.Find(_T("[SystemTime]")) != -1 || strline.Find(_T("[MainFile]")) != -1 ||
		strline.Find(_T("[Language]")) != -1 || strline.Find(_T("[CommandLine]")) != -1 || strline.Find(_T("[Message]")) != -1 || strline.Find(_T("[Error]")) != -1)
	{
		return TRUE;
	}
	return FALSE;
}
void CRichEditCtrlBuild::ShowEditorAnnotationLine(const CString& strline, BuildErrorDataLineList& errorLines, BOOL bGotoLine)
{
	if (AppSettingMgr.m_bEnableDisplayBuildErrorOnEditor == FALSE)
	{
		return;
	}
	// ignore build info messages
	if (IsBuildInformationMessage(strline))
	{
		return;
	}
	CString strCurrentLine = strline;
	if (!strCurrentLine.IsEmpty())
	{
		CString strFileTarget;
		CString strLineNumber;
		// now passing line to get error information...
		CompilerMessageLineParser(strCurrentLine, strLineNumber, strFileTarget);
		if (strFileTarget.IsEmpty() || strLineNumber.IsEmpty()) return;
		CDocument * pOpenedDoc = AppUtils::GetExistedDocument(strFileTarget);
		if (pOpenedDoc)
		{
			strFileTarget = pOpenedDoc->GetPathName();
		}
		if (PathFileExists(strFileTarget))
		{
			if (pOpenedDoc == NULL)
			{
				pOpenedDoc = AppUtils::GetExistedDocument(strFileTarget);
			}
			if (!pOpenedDoc && AppSettingMgr.m_bAllowOpenFileHasErrorBuild)
			{
				AppUtils::CreateDocumentFromFile(strFileTarget);
				CEditorDoc * pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
				if (pEditorDoc)
				{
					auto pEditor = pEditorDoc->GetEditorCtrl();
					if (pEditor)
					{
						int nLine = AppUtils::CStringToInt(strLineNumber);
						errorLines.push_back(BuildErrorDataLine(nLine, strFileTarget));
						if (bGotoLine)
						{
							pEditor->GotoLine(nLine);
							pEditor->SetLineCenterDisplay(nLine);
						}
						pEditor->SetAnnotationText(strCurrentLine, nLine - 1);
					}
				}
			}
			else
			{
				if (AppUtils::SetActiveDocument(pOpenedDoc))
				{
					CEditorDoc * pEditorDoc = dynamic_cast<CEditorDoc*>(pOpenedDoc);
					if (pEditorDoc)
					{
						auto pEditor = pEditorDoc->GetEditorCtrl();
						if (pEditor)
						{
							int nLine = AppUtils::CStringToInt(strLineNumber);
							errorLines.push_back(BuildErrorDataLine(nLine, strFileTarget));
							if (bGotoLine)
							{
								pEditor->GotoLine(nLine);
								pEditor->SetLineCenterDisplay(nLine);
							}
							pEditor->SetAnnotationText(strCurrentLine, nLine - 1);
						}
					}
				}
			}
		}
	}
}

void CRichEditCtrlBuild::ShowErrorLineOnEditor()
{
	int lineCnt = GetLineCount();
	BuildErrorDataLineList errorLines;
	for (int i = 0; i < lineCnt; i++)
	{
		const int nLineIndex = LineIndex(i);
		if (-1 != nLineIndex)
		{
			const int nLineLength = LineLength(nLineIndex);
			if (nLineLength > 0)
			{
				CString strLine = GetTextLine(i, nLineLength);
				ShowEditorAnnotationLine(strLine, errorLines, FALSE);
			}
		}
	}
	if (errorLines.empty())
	{
		return;
	}
	CString strActiveDocPath = (*errorLines.begin())._FilePath;
	int nLine = (*errorLines.begin())._lineNumber;
	auto pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetExistedDocument(strActiveDocPath));
	if (pEditorDoc)
	{
		AppUtils::SetActiveDocument(pEditorDoc);
		auto pEditor = pEditorDoc->GetEditorCtrl();
		if (pEditor)
		{
			pEditor->GotoLine(nLine);
			pEditor->SetLineCenterDisplay(nLine);
		}
	}
}

CString CRichEditCtrlBuild::GetTextLine(long nLineIndex, long lLineLength)
{
	CString strLine;
	GetLine(nLineIndex, strLine.GetBuffer(lLineLength), lLineLength + 1);
	strLine.ReleaseBuffer();
	return strLine;
}

BEGIN_MESSAGE_MAP(CRichEditCtrlBuild, CRichEditCtrl)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	ON_WM_ENTERMENULOOP()
	ON_WM_EXITMENULOOP()
	ON_COMMAND(ID_EDIT_BUILD_WINDOWN_OPENPATH, &CRichEditCtrlBuild::OnEditOpenPath)
	ON_COMMAND(ID_EDIT_BUILD_WINDOWN_REVEALPATH, &CRichEditCtrlBuild::OnEditRevealPath)
	ON_COMMAND(ID_EDIT_COPY, &CRichEditCtrlBuild::OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, &CRichEditCtrlBuild::OnEditClear)
	ON_COMMAND(ID_EDIT_GOOGLE_IT, &CRichEditCtrlBuild::OnEditGoolgeIt)
	ON_COMMAND(ID_EDIT_TRANSLATE_IT, &CRichEditCtrlBuild::OnEditTranslateIt)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CRichEditCtrlBuild::OnEditSelectAll)
	ON_COMMAND(ID_EDIT_WRAPLINE_BUILD, &CRichEditCtrlBuild::OnEditWrapLine)
	ON_COMMAND(ID_EDIT_LOG_TO_EDITOR, &CRichEditCtrlBuild::OnEditViewLogInEditor)
END_MESSAGE_MAP()

BOOL CRichEditCtrlBuild::OnSetCursor(CWnd* pWnd,UINT nHitTest,UINT message)
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

void CRichEditCtrlBuild::OnEnterMenuLoop(IN CONST BOOL bIsTrackPopupMenu)
{
	CRichEditCtrl::OnEnterMenuLoop(bIsTrackPopupMenu);
	if (bIsTrackPopupMenu) m_bInMenu = TRUE;
}

void CRichEditCtrlBuild::OnExitMenuLoop(IN CONST BOOL bIsTrackPopupMenu)
{
	CRichEditCtrl::OnExitMenuLoop(bIsTrackPopupMenu);
	if (bIsTrackPopupMenu) m_bInMenu = FALSE;
}

void CRichEditCtrlBuild::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	if (menu.LoadMenu(IDR_BUILD_WINDOW_CONTEXT_MENU))
	{
		CMenu* pSubMenu = menu.GetSubMenu(0);
		if (!pSubMenu) return;
		VinaTextLocalization.TranslateContextMenu(pSubMenu);
		CString strSelectedPath = GetSelText().Trim();
		if (!PathFileExists(strSelectedPath))
		{
			pSubMenu->DeleteMenu(ID_EDIT_BUILD_WINDOWN_OPENPATH, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_EDIT_BUILD_WINDOWN_REVEALPATH, MF_BYCOMMAND);
		}
		if (m_bEnableLineWrap)
		{
			pSubMenu->CheckMenuItem(ID_EDIT_WRAPLINE_BUILD, MF_CHECKED | MF_BYCOMMAND);
		}
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

void CRichEditCtrlBuild::OnEditCopy()
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

void CRichEditCtrlBuild::OnEditOpenPath()
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
			CDocument* pDoc = AppUtils::CreateDocumentFromFile(strSelectedText);
			AppUtils::SetActiveDocument(pDoc);
		}
	}
	else
	{
		AfxMessageBox(_T("[Open Path Error] path does not exist!"));
	}
}

void CRichEditCtrlBuild::OnEditRevealPath()
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

void CRichEditCtrlBuild::OnEditClear()
{
	SetWindowText(_T(""));
	UpdateData(FALSE);
}

void CRichEditCtrlBuild::OnEditGoolgeIt()
{
	CString strSelectedText = GetSelText();
	CString strGoogleInstance = GOOGLE_SEARCH_API;
	strSelectedText.Replace(_T(" "), _T("+"));
	strGoogleInstance += strSelectedText;
	OSUtils::CreateProcessAsynchronous(TEXT("open"), strGoogleInstance, _T(""), _T(""), SW_MAXIMIZE);
}

void CRichEditCtrlBuild::OnEditTranslateIt()
{
	CString strSelectedText = GetSelText();
	CString strGoogleTranslatePrefix = GOOGLE_TRANSLATE_PREFIX_API;
	CString strGoogleTranslateSuffix = GOOGLE_TRANSLATE_SUFFIX_API;
	strGoogleTranslatePrefix += strSelectedText + strGoogleTranslateSuffix;
	OSUtils::CreateProcessAsynchronous(TEXT("open"), strGoogleTranslatePrefix, _T(""), _T(""), SW_MAXIMIZE);
}

void CRichEditCtrlBuild::OnEditSelectAll()
{
	CRichEditCtrl::SetSel(0, -1);
}

void CRichEditCtrlBuild::GetAllText(CString& strText)
{
	int lineCnt = GetLineCount();
	for (int i = 0; i < lineCnt; i++)
	{
		const int nLineIndex = LineIndex(i);
		if (-1 != nLineIndex)
		{
			const int nLineLength = LineLength(nLineIndex);
			if (nLineLength > 0)
			{
				CString strLine = GetTextLine(i, nLineLength);
				strText += strLine + _T("\n");
			}
		}
	}
}

void CRichEditCtrlBuild::OnEditWrapLine()
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

void CRichEditCtrlBuild::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CRichEditCtrl::OnLButtonDown(nFlags, point);
	OnOutputGotoLine();
}

void CRichEditCtrlBuild::OnOutputGotoLine()
{
	CString strCurrentLine = GetCurrentTextLine();
	BuildErrorDataLineList errorLines;
	ShowEditorAnnotationLine(strCurrentLine, errorLines, TRUE);
}

void CRichEditCtrlBuild::OnEditViewLogInEditor()
{
	CString strAllText;
	GetAllText(strAllText);
	AppUtils::CreateNewEditorWithText(_T("Build Data"), strAllText);
}

BOOL CRichEditCtrlBuild::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN || pMsg->message == WM_SYSKEYUP)
	{
		if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
		{
			if (pMsg->wParam == 'Q')
			{
				OnEditRevealPath();
				return TRUE;
			}
		}
		if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_MENU) & 0x8000))
		{
			CBuildPaneDlg* pPaneDlg = dynamic_cast<CBuildPaneDlg*>(GetParent());
			if (pPaneDlg)
			{
				pPaneDlg->OnShowCallStack();
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
			if (pMsg->wParam == VK_DELETE)
			{
				OnEditClear();
				return TRUE;
			}
			if (pMsg->wParam == VK_F11)
			{
				CBuildPaneDlg* pPaneDlg = dynamic_cast<CBuildPaneDlg*>(GetParent());
				if (pPaneDlg)
				{
					pPaneDlg->OnStepOut();
					return TRUE;
				}
			}
			if (pMsg->wParam == VK_F5)
			{
				CBuildPaneDlg* pPaneDlg = dynamic_cast<CBuildPaneDlg*>(GetParent());
				if (pPaneDlg)
				{
					pPaneDlg->OnStopDebugger();
					return TRUE;
				}
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
		CBuildPaneDlg* pPaneDlg = dynamic_cast<CBuildPaneDlg*>(GetParent());
		if (pPaneDlg)
		{
			if (pMsg->wParam == VK_F5)
			{
				pPaneDlg->OnStartDebugger();
				return TRUE;
			}
			if (pMsg->wParam == VK_F10)
			{
				pPaneDlg->OnStepOver();
				return TRUE;
			}
			if (pMsg->wParam == VK_F11)
			{
				pPaneDlg->OnStepInto();
				return TRUE;
			}
		}
	}
	return CRichEditCtrl::PreTranslateMessage(pMsg);
}

CString CRichEditCtrlBuild::GetCurrentTextLine()
{
	int nLineNum = LineFromChar(LineIndex(-1));
	CString strLine;
	const int nLineIndex = LineIndex(nLineNum);
	if (-1 != nLineIndex)
	{
		const int nLineLength = LineLength(nLineIndex);
		if (nLineLength > 1)
		{
			GetLine(nLineNum, strLine.GetBuffer(nLineLength), nLineLength + 1);
			strLine.ReleaseBuffer();
		}
	}
	return strLine;
}

void CRichEditCtrlBuild::CompilerMessageLineParser(CString & strLine, CString & strLineNumber, CString & strFilePath)
{
	// PYTHON ERROR LINE ///////////////////////////
	//  File "C:\Users\Desktop\test.py", line 15
	if (strLine.Find(_T(".py\", line ")) != -1 && strLine.Find(_T("File \"")) != -1) // python error line...
	{
		int nPos1 = strLine.Find(_T("File \""));
		int nPos2 = strLine.Find(_T("\", line "));
		int nPos3 = strLine.Find(_T(", in "));
		if (nPos3 == -1)
		{
			strLineNumber = strLine.Mid(nPos2 + 8).Trim();
		}
		else
		{
			strLineNumber = strLine.Mid(nPos2 + 8, nPos3 - nPos2 - 8).Trim();
		}
		strFilePath = strLine.Mid(nPos1 + 6, nPos2 - nPos1 - 6).Trim();
		CString strErrorText;
		int lineCnt = GetLineCount();
		BOOL bStartGetText = FALSE;
		for (int i = 0; i < lineCnt; i++)
		{
			const int nLineIndex = LineIndex(i);
			if (-1 != nLineIndex)
			{
				const int nLineLength = LineLength(nLineIndex);
				if (nLineLength > 0)
				{
					CString strLine = GetTextLine(i, nLineLength);
					if (strLine.IsEmpty())
					{
						continue;
					}
					if (strLine.Find(_T("[ RUN ...")) != -1 || strLine.Find(_T("[ DEBUG ...")) != -1)
					{
						bStartGetText = TRUE;
						continue;
					}
					if (strLine.Find(_T("... END ]")) != -1)
					{
						bStartGetText = FALSE;
					}
					if (bStartGetText)
					{
						strErrorText += strLine + _T("\n");
					}
				}
			}
		}
		strLine = strErrorText;
	}
	// C++ ERROR LINE ///////////////////////////
	// C:\Users\Desktop\test.cpp:12:3: error: expected initializer before 'printf'
	// C:\Users\Desktop\CodeTest\DCAD_macro.cpp:3:10: fatal error: stdafx.h: No such file or directory
	else if ((strLine.Find(_T(".cpp:")) != -1 || strLine.Find(_T(".h:")) != -1) && strLine.Find(_T(" error: ")) != -1) // C++ error line...
	{
		int nPos0 = strLine.Find(_T(" error: "));
		int nPos1 = strLine.Find(_T(".cpp:"));
		CString strTempLine = strLine.Mid(nPos1 + 5);
		int nPos2 = strTempLine.Find(_T(":"));
		{
			strLineNumber = strTempLine.Mid(0, nPos2).Trim();
		}
		strFilePath = strLine.Mid(0, nPos1 + 4).Trim();
		strLine = _T(">") + strLine.Mid(nPos0) + _T(" at line ") + strLineNumber;
	}
	// C ERROR LINE ///////////////////////////
	// C:\Users\Desktop\test.c:12:3: error: expected initializer before 'printf'
	else if ((strLine.Find(_T(".c:")) != -1 || strLine.Find(_T(".h:")) != -1) && strLine.Find(_T(" error: ")) != -1) // C error line...
	{
		int nPos0 = strLine.Find(_T(" error: "));
		int nPos1 = strLine.Find(_T(".c:"));
		CString strTempLine = strLine.Mid(nPos1 + 3);
		int nPos2 = strTempLine.Find(_T(":"));
		{
			strLineNumber = strTempLine.Mid(0, nPos2).Trim();
		}
		strFilePath = strLine.Mid(0, nPos1 + 2).Trim();
		strLine = _T(">") + strLine.Mid(nPos0) + _T(" at line ") + strLineNumber;
	}
	// JAVA ERROR LINE ///////////////////////////
	// C:\Users\VinaText\Desktop\CodeTest\FirstJavaProgram.java:18: error: 
	else if (strLine.Find(_T(".java:")) != -1 && strLine.Find(_T(" error: ")) != -1) // C++ error line...
	{
		int nPos0 = strLine.Find(_T(" error: "));
		int nPos1 = strLine.Find(_T(".java:"));
		CString strTempLine = strLine.Mid(nPos1 + 6);
		int nPos2 = strTempLine.Find(_T(":"));
		{
			strLineNumber = strTempLine.Mid(0, nPos2).Trim();
		}
		strFilePath = strLine.Mid(0, nPos1 + 5).Trim();
		strLine = _T(">") + strLine.Mid(nPos0) + _T(" at line ") + strLineNumber;
	}
	// JAVASCRIPT ERROR LINE ///////////////////////////
	// C:\Users\VinaText\Desktop\CodeTest\test.js:2
	else if (strLine.Find(_T(".js:")) != -1) // Javascript error line...
	{
		int nPos0 = strLine.ReverseFind(_T(':'));
		strLineNumber = strLine.Mid(nPos0 + 1).Trim();
		strFilePath = strLine.Mid(0, nPos0).Trim();
		CString strErrorText;
		int lineCnt = GetLineCount();
		BOOL bStartGetText = FALSE;
		for (int i = 0; i < lineCnt; i++)
		{
			const int nLineIndex = LineIndex(i);
			if (-1 != nLineIndex)
			{
				const int nLineLength = LineLength(nLineIndex);
				if (nLineLength > 0)
				{
					CString strLine = GetTextLine(i, nLineLength);
					if ((strLine.Find(_T(" at ")) != -1 && strLine.Find(_T(".js")) != -1) || strLine.IsEmpty())
					{
						continue;
					}
					if (strLine.Find(_T("[ RUN ...")) != -1 || strLine.Find(_T("[ DEBUG ...")) != -1)
					{
						bStartGetText = TRUE;
						continue;
					}
					if (strLine.Find(_T("... END ]")) != -1)
					{
						bStartGetText = FALSE;
					}
					if (bStartGetText)
					{
						strErrorText += strLine + _T("\n");
					}
				}
			}
		}
		strLine = strErrorText;
	}
	// C-SHAPE ERROR LINE ///////////////////////////
	// c:\Users\VinaText\Desktop\CodeTest\test.cs(15,21): error CS1002: ; expected
	else if (strLine.Find(_T(".cs(")) != -1 && strLine.Find(_T("): error CS")) != -1) // C# error line...
	{
		int nPos0 = strLine.Find(_T("("));
		int nPos1 = strLine.Find(_T(","));
		int nPos3 = strLine.Find(_T("): error CS"));
		strLineNumber = strLine.Mid(nPos0 + 1, nPos1 - nPos0 - 1).Trim();
		strFilePath = strLine.Mid(0, nPos0).Trim();
		strLine = _T(">") + strLine.Mid(nPos3 + 2) + _T(" at line ") + strLineNumber;
	}
	// PASCAL .PP ERROR LINE ///////////////////////////
	// test.pp(3,1) Fatal: Syntax error, ";" expected but "BEGIN" found
	else if (strLine.Find(_T(".pp(")) != -1 && strLine.Find(_T(") Fatal: ")) != -1 || strLine.Find(_T(") Error: ")) != -1) // Pascal error line...
	{
		int nPos0 = strLine.Find(_T("("));
		int nPos1 = strLine.Find(_T(","));
		strLineNumber = strLine.Mid(nPos0 + 1, nPos1 - nPos0 - 1).Trim();
		strFilePath = strLine.Mid(0, nPos0).Trim();
		int nPos3 = strLine.Find(_T(") Fatal: "));
		if (nPos3 == -1)
		{
			nPos3 = strLine.Find(_T(") Error: "));
			strLine = _T("> ") + strLine.Mid(nPos3 + 2) + _T(" at line ") + strLineNumber;
		}
		else
		{
			strLine = _T("> ") + strLine.Mid(nPos3 + 2) + _T(" at line ") + strLineNumber;
		}
	}
	// PASCAL .PAS ERROR LINE ///////////////////////////
	// test.pas(3,1) Fatal: Syntax error, ";" expected but "BEGIN" found
	else if (strLine.Find(_T(".pas(")) != -1 && strLine.Find(_T(") Fatal: ")) != -1 || strLine.Find(_T(") Error: ")) != -1) // Pascal error line...
	{
		int nPos0 = strLine.Find(_T("("));
		int nPos1 = strLine.Find(_T(","));
		strLineNumber = strLine.Mid(nPos0 + 1, nPos1 - nPos0 - 1).Trim();
		strFilePath = strLine.Mid(0, nPos0).Trim();
		int nPos3 = strLine.Find(_T(") Fatal: "));
		if (nPos3 == -1)
		{
			nPos3 = strLine.Find(_T(") Error: "));
			strLine = _T("> ") + strLine.Mid(nPos3 + 2) + _T(" at line ") + strLineNumber;
		}
		else
		{
			strLine = _T("> ") + strLine.Mid(nPos3 + 2) + _T(" at line ") + strLineNumber;
		}
	}
	// PHP ERROR LINE ///////////////////////////
	// Fatal error: Uncaught Error: Call to undefined function arraymerge() in C:\Users\VinaText\Desktop\CodeTest\test.php:21
	// Parse error : syntax error, unexpected 'array' (T_ARRAY)in C : \Users\VinaText\Desktop\CodeTest\test.php on line 24
	else if ((strLine.Find(_T(".php")) != -1 && strLine.Find(_T("error")) != -1 && strLine.Find(_T(" on line ")) != -1 && strLine.Find(_T("in ")) != -1)
		|| (strLine.Find(_T(".php:")) != -1 && strLine.Find(_T("error")) != -1) && strLine.Find(_T("in ")) != -1) // Php error line...
	{
		int nPos0 = strLine.Find(_T("in "));
		int nPos1 = strLine.Find(_T(" on line "));
		if (nPos1 == -1)
		{
			nPos1 = strLine.Find(_T(".php:"));
			strLineNumber = strLine.Mid(nPos1 + 5).Trim();
			strFilePath = strLine.Mid(nPos0 + 3, nPos1 - nPos0 - 3).Trim();
		}
		else
		{
			strLineNumber = strLine.Mid(nPos1 + 9).Trim();
			strFilePath = strLine.Mid(nPos0 + 3, nPos1 - nPos0 - 3).Trim();
		}
	}
	// RUST ERROR LINE ///////////////////////////
	// error: mismatched closing delimiter : `}`
	// --> C:\Users\Desktop\CodeTest\testrust.rs:8 : 16
	else if (strLine.Find(_T(".rs:")) != -1 && strLine.Find(_T("--> ")) != -1) // Rust error line...
	{
		int nPos0 = strLine.Find(_T(".rs:"));
		int nPos1 = strLine.ReverseFind(_T(':'));
		int nPos2 = strLine.Find(_T("--> "));
		strLineNumber = strLine.Mid(nPos0 + 4, nPos1 - nPos0 - 4).Trim();
		strFilePath = strLine.Mid(nPos2 + 4, nPos0 - nPos2 - 1).Trim();
		CString strErrorText;
		int lineCnt = GetLineCount();
		BOOL bStartGetText = FALSE;
		for (int i = 0; i < lineCnt; i++)
		{
			const int nLineIndex = LineIndex(i);
			if (-1 != nLineIndex)
			{
				const int nLineLength = LineLength(nLineIndex);
				if (nLineLength > 0)
				{
					CString strLine = GetTextLine(i, nLineLength);
					if (strLine.Find(_T("error")) != -1 && strLine.Find(_T(": ")) != -1)
					{
						strErrorText += strLine; break;
					}
				}
			}
		}
		strLine = strErrorText;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEditBuild

IMPLEMENT_DYNAMIC(CEditBuild, CUndoRedoEditControl)

CEditBuild::CEditBuild()
{
}

CEditBuild::~CEditBuild()
{
}

CString CEditBuild::GetCurrentText()
{
	CString str;
	GetWindowText(str);
	return str;
}

BEGIN_MESSAGE_MAP(CEditBuild, CUndoRedoEditControl)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

BOOL CEditBuild::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			CString str;
			GetWindowText(str);
			GetParent()->SendMessage(UM_EDIT_USER_INPUT, (WPARAM)LPCTSTR(str), NULL);
			SetWindowText(_T(""));
			return true;
		}
		else if (pMsg->wParam == VK_ESCAPE)
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

		if (pMsg->wParam == VK_UP)
		{
			GetParent()->SendMessage(UM_EDIT_TRACE_PREV);
			return TRUE;
		}
		if (pMsg->wParam == VK_DOWN)
		{
			GetParent()->SendMessage(UM_EDIT_TRACE_NEXT);
			return TRUE;
		}
	}
	return CUndoRedoEditControl::PreTranslateMessage(pMsg);
}

HBRUSH CEditBuild::CtlColor(CDC* pDC, UINT nCtlColor)
{
	pDC->SetTextColor(BasicColors::white);
	pDC->SetBkColor(BasicColors::light_green);
	return ::CreateSolidBrush(BasicColors::light_green);
}

void CEditBuild::OnSetFocus(CWnd * pOldWnd)
{
	CUndoRedoEditControl::OnSetFocus(pOldWnd);
	if (GetCurrentText() == _T("> > > ..."))
	{
		SetWindowTextW(_T(""));
	}
}

void CEditBuild::OnKillFocus(CWnd * pNewWnd)
{
	CUndoRedoEditControl::OnKillFocus(pNewWnd);
	if (GetCurrentText().IsEmpty())
	{
		SetWindowTextW(_T("> > > ..."));
	}
}

void CEditBuild::SetCaretAtEndline()
{
	SetFocus();
	SetSel(0, -1);
	SetSel(-1);
}

/////////////////////////////////////////////////////////////////////////////
// CBuildPaneDlg dialog

IMPLEMENT_DYNAMIC(CBuildPaneDlg, CDialogEx)

CBuildPaneDlg::CBuildPaneDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ID_DIALOG_BUILD_PANE, pParent)
{
	IMPLEMENT_FONT_SETTING_DOCK_WINDOW
}

CBuildPaneDlg::~CBuildPaneDlg()
{
}

void CBuildPaneDlg::OnOK()
{
}

void CBuildPaneDlg::OnCancel()
{
}

BEGIN_MESSAGE_MAP(CBuildPaneDlg, CDialogEx)
	ON_WM_MOVING()
	ON_WM_SIZE()
	ON_MESSAGE(UM_EDIT_TRACE_PREV, &CBuildPaneDlg::TraceHistoryCmdPrev)
	ON_MESSAGE(UM_EDIT_TRACE_NEXT, &CBuildPaneDlg::TraceHistoryCmdNext)
	ON_MESSAGE(UM_EDIT_USER_INPUT, &CBuildPaneDlg::OnUserInput)
	ON_COMMAND(ID_DEBUGGER_START, &CBuildPaneDlg::OnStartDebugger)
	ON_COMMAND(ID_DEBUGGER_CALL_STACK, &CBuildPaneDlg::OnShowCallStack)
	ON_COMMAND(ID_DEBUGGER_STOP, &CBuildPaneDlg::OnStopDebugger)
	ON_COMMAND(ID_DEBUGGER_RESTART, &CBuildPaneDlg::OnRestartDebugger)
	ON_COMMAND(ID_DEBUGGER_STEPINTO, &CBuildPaneDlg::OnStepInto)
	ON_COMMAND(ID_DEBUGGER_STEPOVER, &CBuildPaneDlg::OnStepOver)
	ON_COMMAND(ID_DEBUGGER_STEPOUT, &CBuildPaneDlg::OnStepOut)
	ON_COMMAND(ID_DEBUGGER_VARIABLE_VALUE, &CBuildPaneDlg::OnWatchVariableValue)
	ON_COMMAND(ID_DEBUGGER_VARIABLE_TYPE, &CBuildPaneDlg::OnWatchVariableType)
	ON_COMMAND(ID_OPTIONS_ADD_NEW_BREAKPOINT, &CBuildPaneDlg::OnAddBreakpoint)
	ON_COMMAND(ID_OPTIONS_DELETE_ALL_BREAKPOINT, &CBuildPaneDlg::OnDeleteAllBreakPoints)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_START, &CBuildPaneDlg::OnUpdateStartDebugger)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_STOP, &CBuildPaneDlg::OnUpdateStopDebugger)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_RESTART, &CBuildPaneDlg::OnUpdateReStartDebugger)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_CALL_STACK, &CBuildPaneDlg::OnUpdateShowCallStack)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_STEPINTO, &CBuildPaneDlg::OnUpdateStepInto)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_STEPOVER, &CBuildPaneDlg::OnUpdateStepOver)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_STEPOUT, &CBuildPaneDlg::OnUpdateStepOut)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_ADD_NEW_BREAKPOINT, &CBuildPaneDlg::OnUpdateAddBreakpoint)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DELETE_ALL_BREAKPOINT, &CBuildPaneDlg::OnUpdateDeleteAllBreakPoints)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_VARIABLE_VALUE, OnUpdateWatchVariableValue)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_VARIABLE_TYPE, OnUpdateWatchVariableType)
END_MESSAGE_MAP()

// CBuildPaneDlg message handlers

void CBuildPaneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CBuildPaneDlg::UpdateLogVisual()
{
	m_wndOutput.SetWindowText(_T(""));
	m_wndOutput.UpdateData(FALSE);
	m_wndOutput.SetFont(&m_Font);
	m_wndOutput.SetBackgroundColor(FALSE, AppSettingMgr.m_AppThemeColor);
	m_wndUserInput.SetFont(&m_Font);
}

void CBuildPaneDlg::AddLogMessage(CString strMessage, COLORREF color)
{
	if (strMessage.IsEmpty()) return;

	// remove junks from message, make it beautiful...
	strMessage = AppUtils::RemoveJunkFromCString(strMessage);

	if (strMessage.Find(_T("undefined reference to `WinMain'")) != -1) // can not find main() in a C/C++ program!
	{
		AfxMessageBox(_T("[C/C++ Build Error] Can not find function main() in current file!"));
	}

	BOOL bDisableOutputLog = FALSE;
	if (ThreadWorkerMgr.IsDebuggerRunning())
	{
		m_lPointerLine = 0;
		BOOL bStopDebugger = FALSE;
		BOOL bIsNonObjectVariable = FALSE;
		if (IsDebuggerMessage(strMessage, bStopDebugger, bDisableOutputLog, bIsNonObjectVariable))
		{
			// ask mainframe to update editor margin UI debugger pointers...
			if (m_lPointerLine > 0 && PathFileExists(m_strFileName) && bStopDebugger == FALSE)
			{
				LPCTSTR szFileName = m_strFileName;
				ThreadWorkerMgr.GetCurrentTask().pWndFrame->SendNotifyMessage(
							UWM_GUI_WORKER_HANDLER_DEBUG_NOTIFY_LINE_PONITER,
							(WPARAM)szFileName,
							(LPARAM)m_lPointerLine);
			}

			if (VinaTextDebugger.GetCurrentDocLanguage() == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
			{
				if (m_lPointerLine == 1 && VinaTextDebugger.IsThisBreakPointExist(m_lPointerLine, m_strFileName))
				{
					VinaTextDebugger.RemoveCommandLineFromQueue(CMD_CONTINUE_PDB);
				}
				if (bIsNonObjectVariable) // watch a standard python data type
				{
					VinaTextDebugger.WatchVariableValueNonObject();
				}
			}

			if (bStopDebugger || strMessage.Find(_T("Program exited with code")) != -1)
			{
				OnStopDebugger();
			}

			if (VinaTextDebugger.GetCurrentDocLanguage() == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
			{
				if (strMessage.Find(_T("debug> Break on start in ")) != -1 && strMessage.Find(_T(".js:")) != -1 && VinaTextDebugger.IsThisBreakPointExist(m_lPointerLine, m_strFileName))
				{
					VinaTextDebugger.RemoveCommandLineFromQueue(CMD_CONTINUE_NODEJS);
				}
				strMessage.Replace(_T("debug> "), _T("")); // remove useless text
			}
		}
		// run debugger command lines
		if (strMessage.Find(_T(": warning: ")) == -1 && strMessage.Find(_T("Free Pascal Compiler version")) == -1) // ignore these message, do not run debugger command!
		{
			VinaTextDebugger.RunNextCommandLine();
		}
	}

	if (bDisableOutputLog == FALSE)
	{
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

		if (strMessage.Find('\n') != -1)
		{
			m_wndOutput.ReplaceSel(strMessage);
		}
		else
		{
			m_wndOutput.ReplaceSel(strMessage + '\n');
		}

		lVisible = GetNumVisibleLines(&m_wndOutput);

		if (&m_wndOutput != m_wndOutput.GetFocus())
		{
			m_wndOutput.LineScroll(INT_MAX);
			m_wndOutput.LineScroll(1 - lVisible);
		}
	}
}

int CBuildPaneDlg::GetNumVisibleLines(CRichEditCtrl* pCtrl)
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

void CBuildPaneDlg::ClearAll()
{
	m_wndOutput.SetWindowText(_T(""));
	m_wndOutput.UpdateData(FALSE);
}

void CBuildPaneDlg::ShowErrorLineOnEditor()
{
	m_wndOutput.ShowErrorLineOnEditor();
}

static int g_the_first_nodejs_debugger_message = 0;

// THIS IS MAIN DEBUGGING PARSER, EVERYTHING RECEIVED FROM DEBUGGER WILL BE PROCESSED HERE, SO BE CAREFULLY!!

BOOL CBuildPaneDlg::IsDebuggerMessage(CString& strMessage, BOOL& bStopDebugger, BOOL& bDisableOutputLog, BOOL& bIsNonObjectVariable)
{
	auto fParseStepOverMessage = [&](const CString& strMessage) -> void {
		CStringArray arrLine;
		AppUtils::SplitCString(strMessage, _T("\n"), arrLine);
		for (int i = 0; i < arrLine.GetSize(); ++i)
		{
			if (arrLine[i].IsEmpty()) continue;
			if (isdigit(arrLine[i][0]))
			{
				CString strTempMessage = arrLine[i];
				int i = 0;
				for (; i < strTempMessage.GetLength(); i++)
				{
					if (isalpha(strTempMessage[i])) break;
				}
				//get the first chars, which are digits
				strTempMessage = strTempMessage.Mid(0, i).Trim();
				// convert the text to an integer
				if (!strTempMessage.IsEmpty())
				{
					m_lPointerLine = AppUtils::CStringToInt(strTempMessage);
					break;
				}
			}
		}
	};

	if (strMessage.Find(_T(" breakpoint at file ")) != -1 || strMessage.Find(_T("Free Pascal Compiler version")) != -1) // from non debugger messages!
	{
		return FALSE;
	}
	else if (VinaTextDebugger.GetCurrentDocLanguage() == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
	{
		if (strMessage.Find(_T("\n(Pdb) ")) != -1) // python debugger!
		{
			//> c:\users\desktop\test.py(9)<module>()
			//	->def partition(arr, low, high) :
			//	(Pdb)
			CStringArray arrLine;
			AppUtils::SplitCString(strMessage, _T("\n"), arrLine);
			for (int i = 0; i < arrLine.GetSize(); ++i)
			{
				if (arrLine[i].IsEmpty()) continue;
				int pos1 = arrLine[i].Find(_T("> "));
				int pos2 = arrLine[i].Find(_T(".py("));
				if (pos1 != -1 && pos2 != -1)
				{
					m_strFileName = arrLine[i].Mid(pos1 + 1, pos2 + 3 - pos1 - 1).Trim();
					int pos3 = arrLine[i].Find(_T(")"));
					CString strLine = arrLine[i].Mid(pos2 + 4, pos3 - pos2 - 4).Trim();
					m_lPointerLine = AppUtils::CStringToLong(strLine);
					break;
				}
			}

			if ((strMessage.Find(_T("Restarting ")) != -1 && strMessage.Find(_T(" with arguments:")) != -1) || strMessage.Find(_T("The program finished and will be restarted")) != -1) // restart Python debugger!
			{
				bStopDebugger = TRUE;
			}

			if (strMessage.Find(_T("*** TypeError: vars() argument must have __dict__ attribute")) != -1) // can not watch a non-object variable
			{
				bDisableOutputLog = TRUE;
				bIsNonObjectVariable = TRUE;
			}

			if (VinaTextDebugger.GetCurrentCommandLine() == CMD_CALL_STACK_PDB)
			{
				if (strMessage.Find(_T("\n(Pdb)")) != -1 && strMessage.Find(_T(")run()")) != -1) // python call stack message!
				{
					bDisableOutputLog = FALSE;
					strMessage = _T("\n________________ CALL STACK PYTHON ___________________________________\n")
						+ strMessage + _T("\n____________________________________________________________________\n");
				}
			}
			return TRUE;
		}
	}
	else if (VinaTextDebugger.GetCurrentDocLanguage() == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP)
	{
		if (strMessage.Find(_T("GNU gdb (GDB) ")) != -1) // ignore GDB header
		{
			bDisableOutputLog = TRUE;
			return TRUE;
		}
		else if (strMessage.Find(_T("(gdb)")) != -1)
		{
			if (strMessage.Find(_T(" at ")) != -1 && (strMessage.Find(_T(".cpp")) != -1 || strMessage.Find(_T(".h")) != -1)) // c++ frame, breakpoint message!
			{
				CStringArray arrLine;
				AppUtils::SplitCString(strMessage, _T("\n"), arrLine);
				for (int i = 0; i < arrLine.GetSize(); ++i)
				{
					if (arrLine[i].IsEmpty()) continue;
					int pos1 = arrLine[i].Find(_T(" at "));
					int pos2 = arrLine[i].Find(_T(".cpp:"));
					int pos3 = arrLine[i].Find(_T(".h:"));
					if (pos1 != -1 && pos2 != -1)
					{
						m_strFileName = arrLine[i].Mid(pos1 + 4, pos2 - pos1).Trim();
						CString strLineNumber = arrLine[i].Mid(pos2 + 5).Trim();
						m_lPointerLine = AppUtils::CStringToLong(strLineNumber);
						break;
					}
					else if (pos1 != -1 && pos3 != -1)
					{
						m_strFileName = arrLine[i].Mid(pos1 + 4, pos3 - pos1 - 2).Trim();
						CString strLineNumber = arrLine[i].Mid(pos3 + 3).Trim();
						m_lPointerLine = AppUtils::CStringToLong(strLineNumber);
						break;
					}
				}
				if (VinaTextDebugger.GetCurrentCommandLine() == CMD_CALL_STACK_GDB)
				{
					if (strMessage.Find(_T("#0")) != -1) // c++ call stack message!
					{
						bDisableOutputLog = FALSE;
						strMessage = _T("\n_____ CALL STACK & LOCAL VARIABLE INFORMATION C++ ____________________\n")
							+ strMessage + _T("\n___________________________________________________________________\n");
					}
				}
			}
			else // step over processing
			{
				fParseStepOverMessage(strMessage);
			}
		}
		//(gdb)Continuing.
		//	[Inferior 1 (process 18852) exited normally]
		//(gdb) (gdb) No stack.
		bStopDebugger = FALSE;
		if (strMessage.Find(_T("[Inferior ")) != -1 && strMessage.Find(_T(" (process ")) != -1
			&& strMessage.Find(_T("\n(gdb) ")) != -1 && strMessage.Find(_T("]")) != -1) // process exit normally, end debugger!
		{
			bStopDebugger = TRUE;
		}
		if (strMessage.Find(_T("Continuing.")) != -1 && m_lPointerLine == 0) // user use continue command, if there is no any next breakpoint then end debugger!
		{
			bStopDebugger = TRUE;
		}
		if (strMessage.Find(_T("The program is not being run.")) != -1) // process exit normally, end debugger!
		{
			bStopDebugger = TRUE;
		}
		if (strMessage.Find(_T("[Thread ")) != -1) // remove spare info...
		{
			strMessage = strMessage.Mid(0, strMessage.Find(_T("[Thread ")));
			return TRUE;
		}
		return TRUE;
	}
	else if (VinaTextDebugger.GetCurrentDocLanguage() == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C)
	{
		if (strMessage.Find(_T("GNU gdb (GDB) ")) != -1) // ignore GDB header
		{
			bDisableOutputLog = TRUE;
			return TRUE;
		}
		else if (strMessage.Find(_T("(gdb)")) != -1)
		{
			if (strMessage.Find(_T(" at ")) != -1 && (strMessage.Find(_T(".c")) != -1 || strMessage.Find(_T(".h")) != -1)) // c frame, breakpoint message!
			{
				CStringArray arrLine;
				AppUtils::SplitCString(strMessage, _T("\n"), arrLine);
				for (int i = 0; i < arrLine.GetSize(); ++i)
				{
					if (arrLine[i].IsEmpty()) continue;
					int pos1 = arrLine[i].Find(_T(" at "));
					int pos2 = arrLine[i].Find(_T(".c:"));
					int pos3 = arrLine[i].Find(_T(".h:"));
					if (pos1 != -1 && pos2 != -1)
					{
						m_strFileName = arrLine[i].Mid(pos1 + 4, pos2 - pos1 - 2).Trim();
						CString strLineNumber = arrLine[i].Mid(pos2 + 3).Trim();
						m_lPointerLine = AppUtils::CStringToLong(strLineNumber);
						break;
					}
					else if (pos1 != -1 && pos3 != -1)
					{
						m_strFileName = arrLine[i].Mid(pos1 + 4, pos3 - pos1 - 2).Trim();
						CString strLineNumber = arrLine[i].Mid(pos3 + 3).Trim();
						m_lPointerLine = AppUtils::CStringToLong(strLineNumber);
						break;
					}
				}
				if (VinaTextDebugger.GetCurrentCommandLine() == CMD_CALL_STACK_GDB)
				{
					if (strMessage.Find(_T("#0")) != -1) // c call stack message!
					{
						bDisableOutputLog = FALSE;
						strMessage = _T("\n_____ CALL STACK & LOCAL VARIABLE INFORMATION C _______________________\n")
							+ strMessage + _T("\n___________________________________________________________________\n");
					}
				}
			}
			else // step over processing , NOT STABLE ONE NEED TO IMPROVE THIS BLOCK CODE!!
			{
				fParseStepOverMessage(strMessage);
			}
		}

		//(gdb)Continuing.
		//	[Inferior 1 (process 18852) exited normally]
		//(gdb) (gdb) No stack.
		bStopDebugger = FALSE;
		if (strMessage.Find(_T("[Inferior ")) != -1 && strMessage.Find(_T(" (process ")) != -1
			&& strMessage.Find(_T("\n(gdb) ")) != -1 && strMessage.Find(_T("]")) != -1) // process exit normally, end debugger!
		{
			bStopDebugger = TRUE;
		}
		if (strMessage.Find(_T("Continuing.")) != -1 && m_lPointerLine == 0) // user use continue command, if there is no any next breakpoint then end debugger!
		{
			bStopDebugger = TRUE;
		}
		if (strMessage.Find(_T("The program is not being run.")) != -1) // process exit normally, end debugger!
		{
			bStopDebugger = TRUE;
		}
		if (strMessage.Find(_T("[Thread ")) != -1) // remove spare info...
		{
			strMessage = strMessage.Mid(0, strMessage.Find(_T("[Thread ")));
			return TRUE;
		}
		return TRUE;
	}
	else if (VinaTextDebugger.GetCurrentDocLanguage() == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
	{
		g_the_first_nodejs_debugger_message++;
		if ((strMessage.Find(_T("debug> break in ")) != -1 || strMessage.Find(_T("debug> Break on start in ")) != -1) && strMessage.Find(_T(".js:")) != -1) // NodeJs debugger!
		{
			//debug> break in C: \Users\VinaText\Desktop\CodeTest\test.js:43
			//41
			//}
			//>43 var sortedArray = quickSort(items, 0, items.length - 1);
			//44 console.log(sortedArray); //prints [2,3,5,6,7,9]
			//debug>
			CStringArray arrLine;
			AppUtils::SplitCString(strMessage, _T("\n"), arrLine);
			for (int i = 0; i < arrLine.GetSize(); ++i)
			{
				if (arrLine[i].IsEmpty()) continue;
				int pos1 = arrLine[i].Find(_T("break in "));
				int pos2 = arrLine[i].Find(_T(".js:"));
				if (pos1 != -1 && pos2 != -1)
				{
					m_strFileName = arrLine[i].Mid(pos1 + 9, pos2 + 3 - pos1 - 9).Trim();
					CString strLine = arrLine[i].Mid(pos2 + 4).Trim();
					m_lPointerLine = AppUtils::CStringToLong(strLine);
					break;
				}
				else
				{
					pos1 = arrLine[i].Find(_T("debug> Break on start in "));
					if (pos1 != -1 && pos2 != -1)
					{
						m_strFileName = arrLine[i].Mid(pos1 + 25, pos2 + 3 - pos1 - 25).Trim();
						CString strLine = arrLine[i].Mid(pos2 + 4).Trim();
						m_lPointerLine = AppUtils::CStringToLong(strLine);
						break;
					}
				}
			}
		}
		else if (strMessage.Find(_T("disconnect...")) != -1 || strMessage.Find(_T("Waiting for the")) != -1) // restart NodeJs debugger!
		{
			if (g_the_first_nodejs_debugger_message == 1)
			{
				g_the_first_nodejs_debugger_message = 0;
				strMessage += _T("[WARNING] There are maybe errors on javascript source files, so debugger can not launch successfully.\nPlease try to run again with non-debug mode...");
			}
			bStopDebugger = TRUE;
		}
		else if (VinaTextDebugger.GetCurrentCommandLine() == CMD_CALL_STACK_NODEJS)
		{
			if (strMessage.Find(_T("\n#")) != -1 && strMessage.Find(_T(".js:")) != -1) // python call stack message!
			{
				bDisableOutputLog = FALSE;
				strMessage = _T("\n________________ CALL STACK JAVACRIPT ________________________________\n")
					+ strMessage + _T("\n____________________________________________________________________\n");
			}
		}
		return TRUE;
	}
	else if (VinaTextDebugger.GetCurrentDocLanguage() == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
	{
		if (strMessage.Find(_T("GNU gdb (GDB) ")) != -1) // ignore GDB header
		{
			bDisableOutputLog = TRUE;
			return TRUE;
		}
		else if (strMessage.Find(_T("(gdb)")) != -1)
		{
			if (strMessage.Find(_T(" at ")) != -1 && (strMessage.Find(_T(".pp")) != -1)) // pascal frame, breakpoint message!
			{
				//Breakpoint 1, main() at D :/FPC/3.2.2/demo/text/hello.pp:11
				CStringArray arrLine;
				AppUtils::SplitCString(strMessage, _T("\n"), arrLine);
				for (int i = 0; i < arrLine.GetSize(); ++i)
				{
					if (arrLine[i].IsEmpty()) continue;
					int pos1 = arrLine[i].Find(_T(" at "));
					int pos2 = arrLine[i].Find(_T(".pp:"));
					if (pos1 != -1 && pos2 != -1)
					{
						m_strFileName = arrLine[i].Mid(pos1 + 4, pos2 - pos1 - 1).Trim();
						CString strLineNumber = arrLine[i].Mid(pos2 + 4).Trim();
						m_lPointerLine = AppUtils::CStringToLong(strLineNumber);
						break;
					}
				}
				if (VinaTextDebugger.GetCurrentCommandLine() == CMD_CALL_STACK_GDB)
				{
					if (strMessage.Find(_T("#0")) != -1) // pascal call stack message!
					{
						bDisableOutputLog = FALSE;
						strMessage = _T("\n_____ CALL STACK & LOCAL VARIABLE INFORMATION PASCAL __________________\n")
							+ strMessage + _T("\n_______________________________________________________________________\n");
					}
				}

			}
			else // step over processing , NOT STABLE ONE NEED TO IMPROVE THIS BLOCK CODE!!
			{
				fParseStepOverMessage(strMessage);
			}
		}
		//(gdb)Continuing.
		//	[Inferior 1 (process 18852) exited normally]
		//(gdb) (gdb) No stack.
		bStopDebugger = FALSE;
		if (strMessage.Find(_T("[Inferior ")) != -1 && strMessage.Find(_T(" (process ")) != -1
			&& strMessage.Find(_T("\n(gdb) ")) != -1 && strMessage.Find(_T("]")) != -1) // process exit normally, end debugger!
		{
			bStopDebugger = TRUE;
		}
		if (strMessage.Find(_T("Continuing.")) != -1 && m_lPointerLine == 0) // user use continue command, if there is no any next breakpoint then end debugger!
		{
			bStopDebugger = TRUE;
		}
		if (strMessage.Find(_T("The program is not being run.")) != -1) // process exit normally, end debugger!
		{
			bStopDebugger = TRUE;
		}
		if (strMessage.Find(_T("[Thread ")) != -1) // remove spare info...
		{
			strMessage = strMessage.Mid(0, strMessage.Find(_T("[Thread ")));
			return TRUE;
		}
		return TRUE;
	}
	return FALSE;
}

void CBuildPaneDlg::OnMoving(UINT nSide, LPRECT lpRect)
{
	CDialogEx::OnMoving(nSide, lpRect);

	CRect CurRect;
	GetWindowRect(&CurRect);

	lpRect->left = CurRect.left;
	lpRect->top = CurRect.top;
	lpRect->right = CurRect.right;
	lpRect->bottom = CurRect.bottom;
}

void CBuildPaneDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (!cx || !cy) return;

	LOGFONT lf;
	m_Font.GetLogFont(&lf);
	UINT nTxtHeight = (UINT)lf.lfHeight + 2;

	CRect rectClient;
	GetClientRect(rectClient);

	if (m_wndDebuggerToolBar.GetSafeHwnd())
	{
		CSize sizeToolbar = m_wndDebuggerToolBar.CalcFixedLayout(FALSE, TRUE);
		CRect rectClient;
		GetClientRect(rectClient);
		m_wndDebuggerToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), sizeToolbar.cy, SWP_NOACTIVATE | SWP_NOZORDER);
		if (m_wndOutput.GetSafeHwnd())
		{
			m_wndOutput.MoveWindow(0, sizeToolbar.cy, cx, cy - sizeToolbar.cy - nTxtHeight);
		}
	}

	if (m_wndUserInput.GetSafeHwnd())
	{
		m_wndUserInput.MoveWindow(0, cy - nTxtHeight, cx, nTxtHeight);
	}
}

BOOL CBuildPaneDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UINT nMenuf = MF_BYCOMMAND | MF_GRAYED | MF_DISABLED;
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu)
	{
		pSysMenu->EnableMenuItem(SC_CLOSE, nMenuf);
	}
	// create debugger toolbar
	BOOL retTB = m_wndDebuggerToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_BUILD_WINDOW);
	retTB = m_wndDebuggerToolBar.LoadToolBar(IDR_TOOLBAR_DEBUGGER_24, 0, 0, TRUE /* Is locked */);
	if (!retTB)
	{
		TRACE0("Failed to create toolbar windows\n");
		return FALSE;      // fail to create
	}
	m_wndDebuggerToolBar.CleanUpLockedImages();
	m_wndDebuggerToolBar.LoadBitmap(IDR_TOOLBAR_DEBUGGER_24, 0, 0, TRUE /* Locked */);
	m_wndDebuggerToolBar.SetPaneStyle(m_wndDebuggerToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndDebuggerToolBar.SetPaneStyle(m_wndDebuggerToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndDebuggerToolBar.SetOwner(this);
	m_wndDebuggerToolBar.SetRouteCommandsViaFrame(FALSE);

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	const DWORD dwStyle = ES_MULTILINE | ES_READONLY | ES_WANTRETURN | WS_VSCROLL | WS_HSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE;
	if (!m_wndOutput.Create(dwStyle, rectDummy, this, ID_RICHEDIT_OUTPUT_PANE))
	{
		TRACE0("Failed to create output windows\n");
		return FALSE;      // fail to create
	}
	// To turn word wrap on - based on window width
	m_wndOutput.SetFont(&m_Font);
	m_wndOutput.SetBackgroundColor(FALSE, AppSettingMgr.m_AppThemeColor);
	m_wndOutput.LimitText(0xfffffff);
	m_wndOutput.m_bEnableLineWrap = FALSE;

	if (!m_wndUserInput.CreateEx(WS_EX_STATICEDGE, _T("edit"), _T(""),
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, CRect(0, 0, 0, 0), this, ID_USER_INPUT_OUTPUT_PANE))
	{
		TRACE0("Failed to create user input edit\n");
		return FALSE;
	}
	m_wndUserInput.SetFont(&m_Font);
	m_wndUserInput.ModifyStyleEx(NULL, WS_EX_STATICEDGE);
	m_wndUserInput.SetWindowTextW(_T("> > > ..."));

	AddLogMessage(_T("Program log message will be displayed here...\n"),
		IS_LIGHT_THEME ? BasicColors::black : BasicColors::white);

	UpdateData(FALSE);
	return TRUE;
}

LRESULT CBuildPaneDlg::OnUserInput(WPARAM wParam, LPARAM lParam)
{
	TCHAR *pUserInput = (TCHAR*)wParam;
	CString strUserInput = pUserInput;
	RecordUserInput(strUserInput);
	if (ThreadWorkerMgr.IsRunning())
	{
		ThreadWorkerMgr.WriteUserInputToPipe(strUserInput);
	}
	else
	{
		AddLogMessage(_T("[Error] There is no running program now...\n"),
			IS_LIGHT_THEME ? BasicColors::black : BasicColors::white);
		return -1;
	}
	return 0;
}

void CBuildPaneDlg::RecordUserInput(const CString & strCommand)
{
	m_HistoryUserInput.push_back(strCommand);
	m_HistoryUserInput.erase(VectorUtils::Uniquify(m_HistoryUserInput.begin(), m_HistoryUserInput.end()), m_HistoryUserInput.end());
}

void CBuildPaneDlg::OnStartDebugger()
{
	auto pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pEditorDoc)
	{
		auto pView = pEditorDoc->GetEditorView();
		if (pView)
		{
			pView->OnStartDebugger();
		}
	}
}

void CBuildPaneDlg::OnShowCallStack()
{
	VinaTextDebugger.ShowCallStack();
}

void CBuildPaneDlg::OnStopDebugger()
{
	if (ThreadWorkerMgr.IsRunning())
	{
		ThreadWorkerMgr.StopThreadWorker();
	}
}

void CBuildPaneDlg::OnRestartDebugger()
{
	VinaTextDebugger.Restart();
}

void CBuildPaneDlg::OnStepOver()
{
	VinaTextDebugger.StepOver();
}

void CBuildPaneDlg::OnStepInto()
{
	VinaTextDebugger.StepInto();
}

void CBuildPaneDlg::OnStepOut()
{
	VinaTextDebugger.StepOut();
}

void CBuildPaneDlg::OnWatchVariableValue()
{
	CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pEditorDoc)
	{
		pEditorDoc->GetEditorView()->OnWatchVariableValue();
	}
}

void CBuildPaneDlg::OnWatchVariableType()
{
	CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pEditorDoc)
	{
		pEditorDoc->GetEditorView()->OnWatchVariableType();
	}
}

void CBuildPaneDlg::OnAddBreakpoint()
{
	CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pEditorDoc)
	{
		pEditorDoc->GetEditorView()->OnOptionsAddBreakPoint();
	}
}

void CBuildPaneDlg::OnDeleteAllBreakPoints()
{
	CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pEditorDoc)
	{
		pEditorDoc->GetEditorView()->OnOptionsDeleteAllBreakPoint();
	}
}

void CBuildPaneDlg::OnUpdateStopDebugger(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(ThreadWorkerMgr.IsRunning());
}

void CBuildPaneDlg::OnUpdateStartDebugger(CCmdUI * pCmdUI)
{
	if (!ThreadWorkerMgr.IsRunning()
		|| ThreadWorkerMgr.IsDebuggerRunning())
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CBuildPaneDlg::OnUpdateReStartDebugger(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(ThreadWorkerMgr.IsDebuggerRunning());
}

void CBuildPaneDlg::OnUpdateShowCallStack(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(ThreadWorkerMgr.IsDebuggerRunning());
}

void CBuildPaneDlg::OnUpdateStepInto(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(ThreadWorkerMgr.IsDebuggerRunning());
}

void CBuildPaneDlg::OnUpdateStepOver(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(ThreadWorkerMgr.IsDebuggerRunning());
}

void CBuildPaneDlg::OnUpdateStepOut(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(ThreadWorkerMgr.IsDebuggerRunning());
}

void CBuildPaneDlg::OnUpdateWatchVariableValue(CCmdUI* pCmdUI)
{
	CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pEditorDoc)
	{
		pEditorDoc->GetEditorView()->OnUpdateWatchVariableValue(pCmdUI);
	}
}

void CBuildPaneDlg::OnUpdateWatchVariableType(CCmdUI* pCmdUI)
{
	CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pEditorDoc)
	{
		pEditorDoc->GetEditorView()->OnUpdateWatchVariableType(pCmdUI);
	}
}

void CBuildPaneDlg::OnUpdateAddBreakpoint(CCmdUI* pCmdUI)
{
	CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pEditorDoc)
	{
		pEditorDoc->GetEditorView()->OnUpdateOptionsAddBreakPoint(pCmdUI);
	}
}

void CBuildPaneDlg::OnUpdateDeleteAllBreakPoints(CCmdUI* pCmdUI)
{
	CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pEditorDoc)
	{
		pEditorDoc->GetEditorView()->OnUpdateOptionsDeleteAllBreakPoints(pCmdUI);
	}
}

LRESULT CBuildPaneDlg::TraceHistoryCmdPrev(WPARAM wParam, LPARAM lParam)
{
	bool bCheck = FALSE;
	if (m_HistoryUserInput.empty()) return -1;
	CString strCurrentText = m_wndUserInput.GetCurrentText();
	if (strCurrentText.IsEmpty())
	{
		m_wndUserInput.Clear();
		m_wndUserInput.SetWindowText(m_HistoryUserInput.back());
		m_wndUserInput.SetCaretAtEndline();
		return 0;
	}
	else
	{
		std::vector<CString>::iterator itPrev, itCurr, itNext;
		itCurr = m_HistoryUserInput.begin();
		while (itCurr != m_HistoryUserInput.end())
		{
			if (*itCurr == strCurrentText)
			{
				if (itCurr != m_HistoryUserInput.begin())
				{
					itPrev = itCurr; --itPrev;
					m_wndUserInput.Clear();
					m_wndUserInput.SetWindowText(*itPrev);
					m_wndUserInput.SetCaretAtEndline();
					bCheck = TRUE;
					break;
				}
			}
			++itCurr;
		}
	}
	if (!bCheck)
	{
		m_wndUserInput.Clear();
		m_wndUserInput.SetWindowText(m_HistoryUserInput.back());
		m_wndUserInput.SetCaretAtEndline();
	}
	return 0;
}

LRESULT CBuildPaneDlg::TraceHistoryCmdNext(WPARAM wParam, LPARAM lParam)
{
	bool bCheck = FALSE;
	if (m_HistoryUserInput.empty()) return -1;
	CString strCurrentText = m_wndUserInput.GetCurrentText();
	if (strCurrentText.IsEmpty())
	{
		m_wndUserInput.Clear();
		m_wndUserInput.SetWindowText(m_HistoryUserInput.front());
		m_wndUserInput.SetCaretAtEndline();
		return 0;
	}
	else
	{
		std::vector<CString>::iterator itPrev, itCurr, itNext;
		itCurr = m_HistoryUserInput.begin();
		while (itCurr != m_HistoryUserInput.end())
		{
			if (*itCurr == strCurrentText)
			{
				itNext = itCurr;
				if (++itNext != m_HistoryUserInput.end())
				{
					m_wndUserInput.Clear();
					m_wndUserInput.SetWindowText(*itNext);
					m_wndUserInput.SetCaretAtEndline();
					bCheck = TRUE;
					break;
				}
			}
			++itCurr;
		}
	}
	if (!bCheck)
	{
		m_wndUserInput.Clear();
		m_wndUserInput.SetWindowText(m_HistoryUserInput.front());
		m_wndUserInput.SetCaretAtEndline();
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// Debugger Toolbar

BOOL CDebuggerToolBar::OnUserToolTip(CMFCToolBarButton * pButton, CString & strTTText) const
{
	if (pButton->m_nID == ID_DEBUGGER_START)
		strTTText = _T("Start Debugging");
	else if (pButton->m_nID == ID_DEBUGGER_CALL_STACK)
		strTTText = _T("Call Stack");
	else if (pButton->m_nID == ID_DEBUGGER_STOP)
		strTTText = _T("Stop Debugging");
	else if (pButton->m_nID == ID_DEBUGGER_RESTART)
		strTTText = _T("Restart Debugging");
	else if (pButton->m_nID == ID_DEBUGGER_STEPINTO)
		strTTText = _T("Step Into");
	else if (pButton->m_nID == ID_DEBUGGER_STEPOVER)
		strTTText = _T("Step Over");
	else if (pButton->m_nID == ID_DEBUGGER_STEPOUT)
		strTTText = _T("Step Out");
	else if (pButton->m_nID == ID_DEBUGGER_VARIABLE_VALUE)
		strTTText = _T("Print Out Selected (Text) Variable Value");
	else if (pButton->m_nID == ID_DEBUGGER_VARIABLE_TYPE)
		strTTText = _T("Print Out Selected (Text) Variable Type");
	else if (pButton->m_nID == ID_OPTIONS_ADD_NEW_BREAKPOINT)
		strTTText = _T("Add New Breakpoint At Current Line");
	else if (pButton->m_nID == ID_OPTIONS_DELETE_ALL_BREAKPOINT)
		strTTText = _T("Delete All Breakpoints");
	return TRUE;
}