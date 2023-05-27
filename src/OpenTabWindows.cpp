/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "afxdialogex.h"
#include "OpenTabWindows.h"
#include "resource.h"
#include "AppUtil.h"
#include "EditorDoc.h"
#include "ImageDoc.h"

// COpenTabWindows dialog

IMPLEMENT_DYNAMIC(COpenTabWindows, CDlgBase)

COpenTabWindows::COpenTabWindows(CWnd* pParent /*=nullptr*/)
	: CDlgBase(IDD_DIALOG_OPEN_DOCUMENTS, pParent)
{
}

void COpenTabWindows::DoDataExchange(CDataExchange* pDX)
{
	CDlgBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_OPEN_TAB, m_listTab);
}

BOOL COpenTabWindows::OnInitDialog()
{
	m_strDlgCaption = _T("Current Windows");
	CDlgBase::OnInitDialog();
	InitiateList();
	m_listTab.SetFocus();
	return TRUE;
}

BOOL COpenTabWindows::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
	{
		switch (pMsg->wParam)
		{
		case 'C':
		{
			if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
			{
				OnCopyFullPath();
				return TRUE;
			}
			break;
		}
		case 'A':
		{
			if ((GetKeyState(VK_CONTROL) & 0x8000))
			{
				OnSelectAll();
				return TRUE;
			}
			break;
		}
		case VK_RETURN:
		{
			OnBnClickedButtonActiveTab();
			break;
		}
		}
	}
	}
	return CDlgBase::PreTranslateMessage(pMsg);
}

void COpenTabWindows::OnSelectAll()
{
	m_listTab.SetItemState(-1, LVIS_SELECTED, LVIS_SELECTED);
}

void COpenTabWindows::InitiateList()
{
	m_listTab.DeleteAllItems();

	m_listTab.SetExtendedStyle(m_listTab.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listTab.InsertColumn(0, L"File Name", LVCFMT_LEFT, 150);
	m_listTab.InsertColumn(1, L"Full Path", LVCFMT_LEFT, 500);

	const auto listOpenTabs = AppUtils::GetAllDocuments();
	for (int i = (int)listOpenTabs.size() - 1; i >= 0; --i)
	{
		CString strFileName = listOpenTabs[i]->GetTitle();
		CString strFilePath = listOpenTabs[i]->GetPathName();
		int nItem = 0;
		nItem = m_listTab.InsertItem(0, listOpenTabs[i]->GetTitle());
		if (PathFileExists(strFilePath))
			m_listTab.SetItemText(nItem, 1, strFilePath);
		else
			m_listTab.SetItemText(nItem, 1, L"N/A");
	}
	m_listTab.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
}

void COpenTabWindows::OnCopyFullPath()
{
	int selectedRow = m_listTab.GetSelectionMark();
	if (selectedRow != -1)
	{
		CString strSelectedPath = m_listTab.GetItemText(selectedRow, 1);
		if (PathFileExists(strSelectedPath) && OpenClipboard())
		{
			GLOBALHANDLE hGlobal;
			TCHAR* pGlobal;
			EmptyClipboard();
			hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT | GMEM_SHARE, (strSelectedPath.GetLength() + 1) * sizeof(TCHAR));
			pGlobal = (TCHAR*)GlobalLock(hGlobal);
			_tcscpy(pGlobal, (LPTSTR)(LPCTSTR)strSelectedPath);
			GlobalUnlock(hGlobal);
			SetClipboardData(CF_UNICODETEXT, hGlobal);
			CloseClipboard();
			AfxMessageBox(_T("Full Path Copied."), MB_ICONINFORMATION);
		}
	}
}

BEGIN_MESSAGE_MAP(COpenTabWindows, CDlgBase)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_TAB, &COpenTabWindows::OnBnClickedButtonCloseTabs)
	ON_BN_CLICKED(IDC_BUTTON_ACTIVE_TAB, &COpenTabWindows::OnBnClickedButtonActiveTab)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_TAB, &COpenTabWindows::OnBnClickedButtonSaveTab)
	ON_BN_CLICKED(IDC_BUTTON_COPY_PATH_TAB, &COpenTabWindows::OnBnClickedButtonCopyPathTab)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_OPEN_TAB, &COpenTabWindows::OnNMDblclkList)
	ON_BN_CLICKED(IDOK, &COpenTabWindows::OnBnClickedOk)
END_MESSAGE_MAP()

// COpenTabWindows message handlers

void COpenTabWindows::OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	OnBnClickedButtonActiveTab();
	*pResult = 0;
}

void COpenTabWindows::OnBnClickedButtonCloseTabs()
{
	if (m_listTab.GetSelectedCount() == 0) return;
	POSITION pos = m_listTab.GetFirstSelectedItemPosition();
	while (pos)
	{
		int nItem = m_listTab.GetNextSelectedItem(pos);
		CString strFullPath = m_listTab.GetItemText(nItem, 1);
		if (PathFileExists(strFullPath))
		{
			AppUtils::CloseDocumentByFilePath(strFullPath);
		}
	}
	InitiateList();
}

void COpenTabWindows::OnBnClickedButtonActiveTab()
{
	int selectedRow = m_listTab.GetSelectionMark();
	if (selectedRow != -1)
	{
		CString strFileName = m_listTab.GetItemText(selectedRow, 0);
		const auto document = AppUtils::GetDocumentFromTitle(strFileName);
		if (document && document != AppUtils::GetMDIActiveDocument()) AppUtils::SetActiveDocument(document);
	}
}

void COpenTabWindows::OnBnClickedButtonSaveTab()
{
	int selectedRow = m_listTab.GetSelectionMark();
	if (selectedRow != -1)
	{
		CString strFileName = m_listTab.GetItemText(selectedRow, 0);
		const auto document = AppUtils::GetDocumentFromTitle(strFileName);
		if (document && document->IsModified())
		{
			if (document->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
			{
				CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(document);
				if (pEditorDoc)
				{
					pEditorDoc->OnFileSave();
				}
			}
			else if (document->IsKindOf(RUNTIME_CLASS(CImageDoc)))
			{
				CImageDoc* pImageDoc = dynamic_cast<CImageDoc*>(document);
				if (pImageDoc)
				{
					pImageDoc->OnFileSave();
				}
			}
			InitiateList();
		}
	}
}

void COpenTabWindows::OnBnClickedOk()
{
	OnBnClickedButtonActiveTab();
	CDlgBase::OnOK();
}

void COpenTabWindows::OnBnClickedButtonCopyPathTab()
{
	OnCopyFullPath();
}
