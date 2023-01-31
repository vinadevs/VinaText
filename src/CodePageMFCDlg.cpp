/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "CodePageMFCDlg.h"
#include "AppUtil.h"
#include "VinaTextApp.h"
#include "EditorView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodePageMFCDlg dialog

CCodePageMFCDlg::CCodePageMFCDlg(CWnd* pParent /*=NULL*/)
	: CDlgBase(CCodePageMFCDlg::IDD, pParent)
{
}

void CCodePageMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INSTALLED, m_wndInstalled);
}

BEGIN_MESSAGE_MAP(CCodePageMFCDlg, CDlgBase)

	ON_BN_CLICKED(IDOK, &CCodePageMFCDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodePageMFCDlg message handlers

BOOL CCodePageMFCDlg::OnInitDialog()
{
	m_strDlgCaption = _T("VinaText System CodePage");

	CDlgBase::OnInitDialog();

	// Initialise list controls
	CCodePage objCodePages;
	InitListControl(m_wndInstalled, objCodePages.GetInstalled());
	
	if (m_bReopen)
	{
		GetDlgItem(IDOK)->SetWindowTextW(_T("Reopen File"));
	}
	else
	{
		GetDlgItem(IDOK)->SetWindowTextW(_T("Save File"));
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCodePageMFCDlg::InitListControl(CListCtrl& listControl, const CCodePage::CCodePageObject& cpObject)
{
	// Full row select looks best
	listControl.SetExtendedStyle(listControl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	// Get the control width
	CRect rect;
	listControl.GetClientRect(&rect);
	// Add columns
	listControl.InsertColumn(0, _T("Code Page"), LVCFMT_LEFT, 100);
	listControl.InsertColumn(1, _T("International Name"), LVCFMT_LEFT, 450);
	// Add each code page
	for (int  i = 0; i < cpObject.GetCount(); i++)
	{
		// ID
		CString strCodePageID;
		strCodePageID.Format(_T("%u"), cpObject[i]);
		int nIndex = listControl.InsertItem(i, strCodePageID);
		// Name
		CString strCodePageName = cpObject.GetName(i);
		if (cpObject[i] == 1147)
		{
			strCodePageName = strCodePageID + _T("  (IIBM EBCDIC France (20297 + Euro symbol); IBM EBCDIC (France-Euro))");
		}
		else if (cpObject[i] == 20297)
		{
			strCodePageName = strCodePageID + _T("  (IBM EBCDIC France)");
		}
		else if (strCodePageName.IsEmpty())
		{
			strCodePageName = strCodePageID + _T("  (Unknown Code Page)");
		}
		listControl.SetItemText(nIndex, 1, strCodePageName);
		// Store the code page ID as the item data ready for sorting the list
		listControl.SetItemData(nIndex, cpObject[i]);
	}
	listControl.SortItems(CompareFunc, 0);
}

int CALLBACK CCodePageMFCDlg::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM /*lParamSort*/)
{
	// Sort in ascending order of code page ID
	return lParam1 > lParam2;
}

void CCodePageMFCDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDlgBase::OnOK();
	int selectedRow = m_wndInstalled.GetSelectionMark();
	if (selectedRow != -1)
	{
		// Get sub item of selectedRow at the first column
		CString strCodePageID = m_wndInstalled.GetItemText(selectedRow, 0);
		CString strCodePageName = m_wndInstalled.GetItemText(selectedRow, 1);
		int nCodePageID = AppUtils::CStringToInt(strCodePageID);
		if (nCodePageID == 0)
		{
			nCodePageID = TF_ANSI;
		}
		// prepare new setting...
		CEditorDoc* pEditorActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
		if (pEditorActiveDoc)
		{		
			if (m_bReopen)
			{
				CEditorView* pEditorView = pEditorActiveDoc->GetEditorView();
				if (pEditorView)
				{
					pEditorView->SetEncodingFromUser(nCodePageID);
				}
			}
			else
			{
				CEditorCtrl* pEditorCtrl = pEditorActiveDoc->GetEditorCtrl();
				if (pEditorCtrl)
				{
					pEditorCtrl->SetSaveEncoding(nCodePageID);
				}
			}
			LOG_OUTPUT_MESSAGE_COLOR(AfxCStringFormat(_T("> [Changed Code Page] %s..."), strCodePageName), BasicColors::orangered);
		}
	}
}
