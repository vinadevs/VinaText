/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "BookMarkPathDlg.h"
#include "AppUtil.h"
#include "SetBookmarkPathDlg.h"
#include "MainFrm.h"
#include "AppSettings.h"
#include "GuiUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif //#ifdef _DEBUG

#pragma warning(suppress: 26455)
CBookMarkPathDlg::CBookMarkPathDlg(CString strBookmarkFile, CWnd* pParent)
	: CDlgBase(CBookMarkPathDlg::IDD, pParent)
	, m_strBookmarkFile(strBookmarkFile)
{
}

void CBookMarkPathDlg::DoDataExchange(CDataExchange* pDX)
{
	//Let the base class do its thing
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BOOKMARK_PATH, m_listPath);
}

BOOL CBookMarkPathDlg::OnInitDialog()
{
	m_strDlgCaption = _T("Path Bookmark Table");
	CDlgBase::OnInitDialog();
	InitListBookmarkPath();
	UpdateData(FALSE);
	return TRUE;
}

void CBookMarkPathDlg::PostNcDestroy()
{
	/*Close & Delete a modeless Dialogs.
	A proper Way is : Override PostNcDestroy, OnOk() and OnCancel() for the Modeless Dialogs*/
	CDlgBase::PostNcDestroy();
	delete this;
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;
	pFrame->ReleaseBookMarkTableDialog();
}

void CBookMarkPathDlg::OnCancel()
{
	CDlgBase::DestroyWindow();
}

BOOL CBookMarkPathDlg::PreTranslateMessage(MSG * pMsg)
{
	switch (pMsg->message)
	{
		case WM_KEYDOWN:
		{
			switch (pMsg->wParam)
			{
				case 'C':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnBnClickedBookmarkCopyPath();
						return TRUE;
					}
					break;
				}
				case 'E':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnBnClickedBookmarkOpenContainer();
						return TRUE;
					}
					break;
				}
				case 'Q':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
					{
						OnBnClickedBookmarkRevealInExplorer();
						return TRUE;
					}
					break;
				}
				case 'T':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_MENU) & 0x8000))
					{
						OnBnClickedBookmarkOpenCmd();
						return TRUE;
					}
					break;
				}
				case VK_RETURN:
				{
					OnBnClickedBookmarkOpen();
					break;
				}
				case VK_DELETE:
				{
					OnBnClickedRemoveBookbarkPath();
					break;
				}
			}
		}
	}
	return CDlgBase::PreTranslateMessage(pMsg);
}

void CBookMarkPathDlg::InitListBookmarkPath(BOOL bIsAddBookMark)
{
	m_listPath.SetExtendedStyle(m_listPath.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	if (!PathFileExists(m_strBookmarkFile))
	{
		// Try to create the new file
		HANDLE hCreateFile = CreateFile(m_strBookmarkFile, // name of the file
			GENERIC_READ, // open for writing
			0,             // sharing mode, none in this case
			0,             // use default security descriptor
			CREATE_ALWAYS, // overwrite if exists
			FILE_ATTRIBUTE_NORMAL,
			0);
		if (!hCreateFile)
		{
			LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Bookmark Path] Failed to create file: ") + m_strBookmarkFile, BasicColors::orange);
		}
		else
		{
			DELETE_WIN32_HANDLE(hCreateFile)
			LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Bookmark Path] Created file: ") + m_strBookmarkFile);
		}
	}
	CStringArray arrPath;
	CString strFileContent;
	PathUtils::OpenFile(m_strBookmarkFile, strFileContent);
	AppUtils::SplitCString(strFileContent, EDITOR_NEW_LINE, arrPath);
	int nCountPath = static_cast<int>(arrPath.GetCount());

	if (!bIsAddBookMark)
	{
		m_listPath.InsertColumn(0, AfxCStringFormat(_T("Saved Paths (%d)"), nCountPath), LVCFMT_LEFT, 500);
		m_listPath.InsertColumn(1, L"Description", LVCFMT_CENTER, 70);
		m_listPath.InsertColumn(2, L"Status", LVCFMT_CENTER, 100);
	}

	m_listPath.DeleteAllItems();

	for (int i = 0; i < arrPath.GetSize(); ++i)
	{
		CString strStatusFile = _T("OK");
		CString strPath = arrPath[i].Trim();
		if (strPath.IsEmpty()) continue;
		if (!PathFileExists(strPath))
		{
			strStatusFile = _T("Not Existed");
		}
		int nItem;
		nItem = m_listPath.InsertItem(0, strPath);
		if (PathUtils::IsDirectory(strPath))
		{
			m_listPath.SetItemText(nItem, 1, _T("Folder"));
		}
		else
		{
			m_listPath.SetItemText(nItem, 1, _T("File"));
		}
		m_listPath.SetItemText(nItem, 2, strStatusFile);
	}
	m_listPath.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
}

#pragma warning(suppress: 26433 26440)
BEGIN_MESSAGE_MAP(CBookMarkPathDlg, CDlgBase)
	ON_BN_CLICKED(ID_ADD_BOOKBARK_PATH, &CBookMarkPathDlg::OnBnClickedAddBookbarkPath)
	ON_BN_CLICKED(ID_REMOVE_BOOKBARK_PATH, &CBookMarkPathDlg::OnBnClickedRemoveBookbarkPath)
	ON_BN_CLICKED(ID_BOOKMARK_OPEN, &CBookMarkPathDlg::OnBnClickedBookmarkOpen)
	ON_BN_CLICKED(ID_BOOKMARK_TO_EXPLORER, &CBookMarkPathDlg::OnBnClickedBookmarkToExplorer)
	ON_BN_CLICKED(ID_BOOKMARK_REVEAL_IN_EXPLORER, &CBookMarkPathDlg::OnBnClickedBookmarkRevealInExplorer)
	ON_BN_CLICKED(ID_BOOKMARK_COPY_PATH, &CBookMarkPathDlg::OnBnClickedBookmarkCopyPath)
	ON_BN_CLICKED(ID_BOOKMARK_OPEN_CMD, &CBookMarkPathDlg::OnBnClickedBookmarkOpenCmd)
	ON_BN_CLICKED(ID_BOOKMARK_CLEAR_ALL, &CBookMarkPathDlg::OnBnClickedBookmarkClearAll)
	ON_BN_CLICKED(ID_BOOKMARK_OPEN_CONTAINER, &CBookMarkPathDlg::OnBnClickedBookmarkOpenContainer)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BOOKMARK_PATH, &CBookMarkPathDlg::OnNMDblclkListBookmarkPath)
	ON_BN_CLICKED(ID_BOOKMARK_COPY_CLIPBOARD, &CBookMarkPathDlg::OnBnClickedBookmarkCopyClipboard)
END_MESSAGE_MAP()

void CBookMarkPathDlg::OnBnClickedAddBookbarkPath()
{
	CString strFolderPath = PathUtils::GetVinaTextAppDataPath();
	if (!PathFileExists(strFolderPath))
	{
		AfxMessageBox(_T("[Error] VinaText database path does not exist!"));
		return;
	}
	CSetPathDlg dlg;
	dlg.m_strDlgCaption = _T("Please enter path to add into bookmark table...");
	dlg.m_sPath = _T("C:\\");
	if (dlg.DoModal() == IDOK)
	{
		CString strPathBookmarkSave = strFolderPath + _T("path-book-mark.dat");
		PathUtils::SaveFileAppendNoDuplicateLine(strPathBookmarkSave, dlg.m_sPath + EDITOR_NEW_LINE_LF);
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> Added new bookmark path: %s"), dlg.m_sPath);
	}
	InitListBookmarkPath(TRUE);
	UpdateData(FALSE);
}

void CBookMarkPathDlg::OnBnClickedRemoveBookbarkPath()
{
	// TODO: Add your control notification handler code here
	int selectedRow = m_listPath.GetSelectionMark();
	if (selectedRow != -1)
	{
		auto strSelectedPath = m_listPath.GetItemText(selectedRow, 0);
		CString strFileContent;
		PathUtils::OpenFile(m_strBookmarkFile, strFileContent);

		CStringArray arrPath;
		CString strNewFileContent;
		AppUtils::SplitCString(strFileContent, EDITOR_NEW_LINE, arrPath);
		for (int i = 0; i < arrPath.GetSize(); ++i)
		{
			CString strPath = arrPath[i].Trim();
			if (strPath.IsEmpty()) continue;
			if (strPath != strSelectedPath.Trim())
			{
				strNewFileContent += strPath + EDITOR_NEW_LINE;
			}
		}
		PathUtils::SaveFileTrunc(m_strBookmarkFile, strNewFileContent);

		m_listPath.DeleteItem(selectedRow);
	}
	else
	{
		AfxMessageBox(_T("Please select one bookmark to proceed command!"));
	}
	UpdateData(FALSE);
}

void CBookMarkPathDlg::OnBnClickedBookmarkOpen()
{
	int selectedRow = m_listPath.GetSelectionMark();
	if (selectedRow != -1)
	{
		// Get sub item of selectedRow at the first column
		CString strSelectedPath = m_listPath.GetItemText(selectedRow, 0);
		if (!PathFileExists(strSelectedPath))
		{
			AfxMessageBoxFormat(MB_ICONWARNING, _T("[Path Error] %s does not exist!\n"), strSelectedPath);
			return;
		}
		if (PathUtils::IsDirectory(strSelectedPath))
		{
			CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
			ASSERT(pFrame);
			if (!pFrame) return;
			pFrame->RevealInExplorerWindow(strSelectedPath);
		}
		else
		{
			AppUtils::CreateDocumentFromFile(strSelectedPath);
		}
	}
	else
	{
		AfxMessageBox(_T("Please select one bookmark to proceed command!"));
	}
}

void CBookMarkPathDlg::OnBnClickedBookmarkToExplorer()
{
	int selectedRow = m_listPath.GetSelectionMark();
	if (selectedRow != -1)
	{
		// Get sub item of selectedRow at the first column
		CString strSelectedPath = m_listPath.GetItemText(selectedRow, 0);
		if (PathFileExists(strSelectedPath))
		{
			if (PathUtils::IsDirectory(strSelectedPath))
			{
				CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
				ASSERT(pFrame);
				if (!pFrame) return;
				if (pFrame->GetFileExplorerCtrl().GetRootFolder().IsEmpty())
				{
					pFrame->GetFileExplorerCtrl().SetRootFolder(strSelectedPath);
				}
				else if (pFrame->GetFileExplorerCtrl().GetRootFolder() != strSelectedPath)
				{
					pFrame->GetFileExplorerCtrl().AddPath(strSelectedPath, false);
				}
			}
			else
			{
				AppUtils::CreateDocumentFromFile(strSelectedPath);
			}
		}
	}
	else
	{
		AfxMessageBox(_T("Please select one bookmark to proceed command!"));
	}
}

void CBookMarkPathDlg::OnBnClickedBookmarkRevealInExplorer()
{
	// TODO: Add your control notification handler code here
	int selectedRow = m_listPath.GetSelectionMark();
	if (selectedRow != -1)
	{
		// Get sub item of selectedRow at the first column
		CString strSelectedPath = m_listPath.GetItemText(selectedRow, 0);
		if (!PathFileExists(strSelectedPath))
		{
			AfxMessageBoxFormat(MB_ICONWARNING, _T("[Path Error] %s does not exist!\n"), strSelectedPath);
			return;
		}
		CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
		ASSERT(pFrame);
		if (!pFrame) return;
		pFrame->RevealInExplorerWindow(strSelectedPath);
	}
	else
	{
		AfxMessageBox(_T("Please select one bookmark to proceed command!"));
	}
}

void CBookMarkPathDlg::OnBnClickedBookmarkCopyPath()
{
	// TODO: Add your control notification handler code here
	int selectedRow = m_listPath.GetSelectionMark();
	if (selectedRow != -1)
	{
		// Get sub item of selectedRow at the first column
		CString strSelectedPath = m_listPath.GetItemText(selectedRow, 0);
		if (!PathFileExists(strSelectedPath))
		{
			AfxMessageBoxFormat(MB_ICONWARNING, _T("[Path Error] %s does not exist!\n"), strSelectedPath);
			return;
		}
		if (OpenClipboard())
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
		}
	}
	else
	{
		AfxMessageBox(_T("Please select one bookmark to proceed command!"));
	}
}

void CBookMarkPathDlg::OnBnClickedBookmarkOpenCmd()
{
	// TODO: Add your control notification handler code here
	int selectedRow = m_listPath.GetSelectionMark();
	if (selectedRow != -1)
	{
		// Get sub item of selectedRow at the first column
		CString strSelectedPath = m_listPath.GetItemText(selectedRow, 0);
		if (!PathFileExists(strSelectedPath))
		{
			AfxMessageBoxFormat(MB_ICONWARNING, _T("[Path Error] %s does not exist!\n"), strSelectedPath);
			return;
		}
		if (PathUtils::IsDirectory(strSelectedPath))
		{
			SetCurrentDirectoryW(strSelectedPath);
		}
		else
		{
			CString strFolderParent = PathUtils::GetContainerPath(strSelectedPath);
			if (PathFileExists(strFolderParent))
			{
				SetCurrentDirectoryW(strFolderParent);
			}
		}
		OSUtils::CreateWin32Process(_T("cmd.exe"));
	}
	else
	{
		AfxMessageBox(_T("Please select one bookmark to proceed command!"));
	}
}

void CBookMarkPathDlg::OnBnClickedBookmarkClearAll()
{
	// TODO: Add your control notification handler code here
	m_listPath.DeleteAllItems();
}

void CBookMarkPathDlg::OnBnClickedBookmarkOpenContainer()
{
	// TODO: Add your control notification handler code here
	int selectedRow = m_listPath.GetSelectionMark();
	if (selectedRow != -1)
	{
		// Get sub item of selectedRow at the first column
		CString strSelectedPath = m_listPath.GetItemText(selectedRow, 0);
		if (!PathFileExists(strSelectedPath))
		{
			AfxMessageBoxFormat(MB_ICONWARNING, _T("[Path Error] %s does not exist!\n"), strSelectedPath);
			return;
		}
		CString strFolderParent = PathUtils::GetContainerPath(strSelectedPath);
		if (PathFileExists(strFolderParent))
		{
			PathUtils::OpenFileSystem(strFolderParent);
		}
	}
	else
	{
		AfxMessageBox(_T("Please select one bookmark to proceed command!"));
	}
}

void CBookMarkPathDlg::OnNMDblclkListBookmarkPath(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	OnBnClickedBookmarkOpen();
	*pResult = 0;
}


void CBookMarkPathDlg::OnBnClickedBookmarkCopyClipboard()
{
	// TODO: Add your control notification handler code here
	int selectedRow = m_listPath.GetSelectionMark();
	if (selectedRow != -1)
	{
		// Get sub item of selectedRow at the first column
		CString strSelectedPath = m_listPath.GetItemText(selectedRow, 0);
		if (!PathFileExists(strSelectedPath))
		{
			AfxMessageBoxFormat(MB_ICONWARNING, _T("[Path Error] %s does not exist!\n"), strSelectedPath);
			return;
		}
		GuiUtils::PushFileObjectToClipboard(strSelectedPath);
	}
	else
	{
		AfxMessageBox(_T("Please select one bookmark to proceed command!"));
	}
}