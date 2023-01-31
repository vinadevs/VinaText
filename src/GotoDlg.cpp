/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "GotoDlg.h"
#include "AppUtil.h"
#include "EditorDoc.h"
#include "Editor.h"
#include "ScrollHelper.h"
#include "AppSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGotoDlg, CDialogEx)

CGotoDlg::CGotoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGotoDlg::IDD, pParent)
{
	m_pScrollHelper = std::make_unique<CScrollHelper>();
	m_pScrollHelper->AttachWnd(this);
	m_pScrollHelper->SetDisplaySize(200, 560);
}

CGotoDlg::~CGotoDlg()
{
}

BOOL CGotoDlg::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			auto pActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
			if (pActiveDoc && pActiveDoc->GetEditorCtrl())
			{
				pActiveDoc->GetEditorCtrl()->SetFocus();
			}
			return true;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CGotoDlg::InitGotoInfoFromEditor(CString strSearchWhat)
{
	m_EditLine.SetWindowTextW(strSearchWhat);
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor != NULL)
		{
			m_EditPosition.SetWindowTextW(AppUtils::IntToCString(pEditor->GetCurrentPosition()));
		}
	}
	GetDlgItem(IDC_LINE)->SetFocus();
}

void CGotoDlg::InitGotoRangeByDocument()
{
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor != NULL)
		{
			CStatic* pStatic = (CStatic*)GetDlgItem(ID_EDITOR_GOTO_LINE_STATIC);
			int nLineCnt = pEditor->GetLineCount();
			CString strLineRange;
			strLineRange.Format(_T("Goto Line (1 - %d):"), nLineCnt);
			pStatic->SetWindowText(strLineRange);
		}
	}
}

void CGotoDlg::ClearAll()
{
	m_EditPosition.SetWindowTextW(_T(""));
	m_EditLine.SetWindowTextW(_T(""));
	m_EditPointX.SetWindowTextW(_T(""));
	m_EditPointY.SetWindowTextW(_T(""));
}

void CGotoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_POSITION, m_EditPosition);
	DDX_Control(pDX, IDC_LINE, m_EditLine);
	DDX_Control(pDX, ID_EDITOR_GOTO_POINT_X, m_EditPointX);
	DDX_Control(pDX, ID_EDITOR_GOTO_POINT_Y, m_EditPointY);
}

BOOL CGotoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowTheme(GetDlgItem(ID_EDITOR_GOTO_POSITION_STATIC)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_GOTO_LINE_STATIC)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_GOTO_POINT_X_STATIC)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_GOTO_POINT_Y_STATIC)->GetSafeHwnd(), L"wstr", L"wstr");

	UpdateData(FALSE);

	return TRUE;
}

void CGotoDlg::OnGotoLine()
{
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor != NULL)
		{
			CString strLineNumber;
			m_EditLine.GetWindowText(strLineNumber);
			pEditor->GotoLine(AppUtils::CStringToInt(strLineNumber));
			pEditor->SetFocus();
		}
	}
}

void CGotoDlg::OnGotoPosition()
{
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor != NULL)
		{
			CString strPosNumber;
			m_EditPosition.GetWindowText(strPosNumber);
			pEditor->GotoPosition(AppUtils::CStringToInt(strPosNumber));
			pEditor->SetFocus();
		}
	}
}

void CGotoDlg::OnGotoPoint()
{
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor != NULL)
		{
			CString strPointX;
			m_EditPointX.GetWindowText(strPointX);
			CString strPointY;
			m_EditPointY.GetWindowText(strPointY);
			pEditor->GotoPointXY(AppUtils::CStringToInt(strPointX), AppUtils::CStringToInt(strPointY));
			pEditor->SetFocus();
		}
	}
}

void CGotoDlg::OnEnChangeEditLineNum()
{
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor)
		{
			auto fCheckLineNumber = [&](long n) -> BOOL
			{
				int nLineCnt = pEditor->GetLineCount();
				if (n < 1 || n > nLineCnt) return FALSE;
				return TRUE;
			};

			CString strLineNumber;
			m_EditLine.GetWindowText(strLineNumber);
			if (fCheckLineNumber(_wtol(strLineNumber)))
			{
				CButton* pButton = (CButton*)GetDlgItem(ID_EDITOR_LINE_GO);
				if (pButton)
				{
					pButton->EnableWindow(TRUE);
				}
			}
			else
			{
				CButton* pButton = (CButton*)GetDlgItem(ID_EDITOR_LINE_GO);
				if (pButton)
				{
					pButton->EnableWindow(FALSE);
				}
			}
		}
	}
}

void CGotoDlg::OnEnChangeEditPositionNum()
{
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor)
		{
			auto fCheckLineNumber = [&](long n) -> BOOL
			{
				int nTextLength = pEditor->GetTextLength();
				if (n < 0 || n > nTextLength) return FALSE;
				return TRUE;
			};

			CString strTextLength;
			m_EditPosition.GetWindowText(strTextLength);
			if (fCheckLineNumber(_wtol(strTextLength)))
			{
				CButton* pButton = (CButton*)GetDlgItem(ID_EDITOR_POSITION_GO);
				if (pButton)
				{
					pButton->EnableWindow(TRUE);
				}
			}
			else
			{
				CButton* pButton = (CButton*)GetDlgItem(ID_EDITOR_POSITION_GO);
				if (pButton)
				{
					pButton->EnableWindow(FALSE);
				}
			}
		}
	}
}

BOOL CGotoDlg::OnEraseBkgnd(CDC * pDC)
{
	CRect rect;
	GetClientRect(&rect);
	CBrush myBrush(AppSettingMgr.m_ThemeColor);    // dialog background color
	CBrush *pOld = pDC->SelectObject(&myBrush);
	BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOld);    // restore old brush
	return bRes;
}

HBRUSH CGotoDlg::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == ID_EDITOR_GOTO_POSITION_STATIC
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_LINE_GO
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_POSITION_GO
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_POINT_GO
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_GOTO_LINE_STATIC
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_GOTO_POINT_X_STATIC
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_GOTO_POINT_Y_STATIC)
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		return CreateSolidBrush(AppSettingMgr.m_ThemeColor);
	}
	return hbr;
}

BEGIN_MESSAGE_MAP(CGotoDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_EDITOR_LINE_GO, OnGotoLine)
	ON_BN_CLICKED(ID_EDITOR_POSITION_GO, OnGotoPosition)
	ON_BN_CLICKED(ID_EDITOR_POINT_GO, OnGotoPoint)
	ON_EN_CHANGE(IDC_LINE, OnEnChangeEditLineNum)
	ON_EN_CHANGE(IDC_POSITION, OnEnChangeEditPositionNum)
	ON_BN_CLICKED(ID_EDITOR_LINE_GO_PREVIOUS_PARAH, &CGotoDlg::OnBnClickedEditorLineGoPreviousParah)
	ON_BN_CLICKED(ID_EDITOR_LINE_GO_NEXT_PARAH, &CGotoDlg::OnBnClickedEditorLineGoNextParah)
	ON_BN_CLICKED(ID_EDITOR_LINE_GO_TO_CARET, &CGotoDlg::OnBnClickedEditorLineGoToCaret)
END_MESSAGE_MAP()

// for scrolling //////////////////////////////////////////////////////////////

void CGotoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pScrollHelper->OnHScroll(nSBCode, nPos, pScrollBar);
}

void CGotoDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pScrollHelper->OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CGotoDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	BOOL wasScrolled = m_pScrollHelper->OnMouseWheel(nFlags, zDelta, pt);

	return wasScrolled;
}

void CGotoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_pScrollHelper->OnSize(nType, cx, cy);
}

void CGotoDlg::OnBnClickedEditorLineGoPreviousParah()
{
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor != NULL)
		{
			pEditor->DoCommand(SCI_PARAUP);
			pEditor->SetFocus();
		}
	}
}

void CGotoDlg::OnBnClickedEditorLineGoNextParah()
{
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor != NULL)
		{
			pEditor->DoCommand(SCI_PARADOWN);
			pEditor->SetFocus();
		}
	}
}

void CGotoDlg::OnBnClickedEditorLineGoToCaret()
{
	// TODO: Add your control notification handler code here
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor != NULL)
		{
			pEditor->SetLineCenterDisplay(pEditor->GetCurrentLine());
			pEditor->SetFocus();
		}
	}
}
