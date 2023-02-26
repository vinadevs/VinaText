/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "BracketOutLineDlg.h"
#include "AppUtil.h"
#include "PathUtil.h"
#include "EditorDoc.h"
#include "Editor.h"
#include "ScrollHelper.h"
#include "AppSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBracketOutLineDlg 

IMPLEMENT_DYNAMIC(CBracketOutLineDlg, CDialogEx)

CBracketOutLineDlg::CBracketOutLineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBracketOutLineDlg::IDD, pParent)
{
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	_tcscpy_s(lf.lfFaceName, 32 * sizeof(CHAR), _T("Tahoma"));
	lf.lfHeight = 14;
	lf.lfWeight = FW_MEDIUM;
	m_Font.CreateFontIndirect(&lf);
}

CBracketOutLineDlg::~CBracketOutLineDlg()
{
}

void CBracketOutLineDlg::UpdateFoldingMap(int nFoldingLevel)
{
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		m_strFilePath = pDoc->GetPathName();
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor != NULL)
		{
			auto dataList = pEditor->GetFoldingLineDataList(nFoldingLevel);
			m_BracketTree.DeleteAllItems();
			HTREEITEM hRoot = m_BracketTree.InsertItem(pDoc->GetTitle() + _T(" (level ") 
				+ AppUtils::IntToCString(nFoldingLevel) + _T(" - ") + AppUtils::IntToCString(static_cast<int>(dataList.size())) + _T(" braces)"));
			m_BracketTree.SetItemImage(hRoot, 0, 0);
			for (auto const& data : dataList)
			{
				HTREEITEM hChild = m_BracketTree.InsertItem(AppUtils::LongToCString(data._lineNumber) + _T(" | ") + data._lineText, 4, 4, hRoot);
				m_BracketTree.SetItemImage(hChild, 0, 0);
			}
			m_BracketTree.InsertItem(_T(""), 4, 4, hRoot);
			m_BracketTree.InsertItem(_T(""), 4, 4, hRoot);
			m_BracketTree.Expand(hRoot, TVE_EXPAND);
		}
	}
}

void CBracketOutLineDlg::ClearAll()
{
	OnEditClear();
}

void CBracketOutLineDlg::UpdateUIVisual()
{
	m_BracketTree.SetBkColor(AppSettingMgr.m_ThemeColor);
}

void CBracketOutLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BRACKETS_OUTLINE_TREE, m_BracketTree);
}

BOOL CBracketOutLineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// init control
	DWORD dwExtendedStyle = m_BracketTree.GetExtendedStyle() | TVS_EX_DOUBLEBUFFER | TVS_EX_DRAWIMAGEASYNC;
	m_BracketTree.SetExtendedStyle(dwExtendedStyle, dwExtendedStyle);
	m_BracketTree.SetParrentWindow(this);
	m_BracketTree.SetTextColor(IS_LIGHT_THEME ? BasicColors::black : BasicColors::white);
	m_BracketTree.SetBkColor(AppSettingMgr.m_ThemeColor);
	m_BracketTree.EnableToolTips(TRUE);
	m_BracketTree.SetFont(&m_Font);
	m_BracketTree.EnableSetBoldDbClick(FALSE);
	if (!m_Bitmap.LoadBitmap(IDR_FOLDER_ROOT))
	{
		return FALSE;
	}
	m_ImageList.Create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 0);
	m_ImageList.Add(&m_Bitmap, RGB(255, 0, 255));
	m_BracketTree.SetImageList(&m_ImageList);
	UpdateFoldingMap(DEFAULT_FOLDONG_MAP_LEVEL);
	UpdateData(FALSE);
	return TRUE;
}

void CBracketOutLineDlg::OnEditRefresh()
{
	UpdateFoldingMap(DEFAULT_FOLDONG_MAP_LEVEL);
}

void CBracketOutLineDlg::OnEditLevel1()
{
	UpdateFoldingMap(1);
}

void CBracketOutLineDlg::OnEditLevel2()
{
	UpdateFoldingMap(2);
}

void CBracketOutLineDlg::OnEditLevel3()
{
	UpdateFoldingMap(3);
}

void CBracketOutLineDlg::OnEditLevel4()
{
	UpdateFoldingMap(4);
}

void CBracketOutLineDlg::OnEditLevel5()
{
	UpdateFoldingMap(5);
}

void CBracketOutLineDlg::OnEditLevel6()
{
	UpdateFoldingMap(6);
}

void CBracketOutLineDlg::OnEditLevel7()
{
	UpdateFoldingMap(7);
}

void CBracketOutLineDlg::OnEditLevel8()
{
	UpdateFoldingMap(8);
}

void CBracketOutLineDlg::OnEditLevel9()
{
	UpdateFoldingMap(9);
}

void CBracketOutLineDlg::OnEditSaveFile()
{
	TCHAR  szFilter[] = _T("Text File(*.txt)|*.txt|CSV File(*.csv)|*.csv||");
	CFileDialog fileDlg(FALSE, _T("txt"), _T("*.txt"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
	if (fileDlg.DoModal() == IDOK)
	{
		CString filename = fileDlg.GetPathName();
		std::vector<CString> vecItemText = m_BracketTree.GetAllItemTexts();
		CString strAllText;
		for (auto const& strLine : vecItemText)
		{ 
			strAllText += strLine + _T("\n");
		}
		PathUtils::SaveFileTrunc(filename, strAllText);
	}
}

void CBracketOutLineDlg::OnEditClear()
{
	auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		m_strFilePath.Empty();
		auto pEditor = pDoc->GetEditorCtrl();
		if (pEditor != NULL)
		{
			m_BracketTree.DeleteAllItems();
			HTREEITEM hRoot = m_BracketTree.InsertItem(pDoc->GetTitle());
			m_BracketTree.SetItemImage(hRoot, 0, 0);
		}
	}
}

BEGIN_MESSAGE_MAP(CBracketOutLineDlg, CDialogEx)
	ON_COMMAND(ID_EDIT_REFRESH_FOLDING_MAP, &CBracketOutLineDlg::OnEditRefresh)
	ON_COMMAND(ID_EDIT_FOLDING_MAP_LEVEL_1, &CBracketOutLineDlg::OnEditLevel1)
	ON_COMMAND(ID_EDIT_FOLDING_MAP_LEVEL_2, &CBracketOutLineDlg::OnEditLevel2)
	ON_COMMAND(ID_EDIT_FOLDING_MAP_LEVEL_3, &CBracketOutLineDlg::OnEditLevel3)
	ON_COMMAND(ID_EDIT_FOLDING_MAP_LEVEL_4, &CBracketOutLineDlg::OnEditLevel4)
	ON_COMMAND(ID_EDIT_FOLDING_MAP_LEVEL_5, &CBracketOutLineDlg::OnEditLevel5)
	ON_COMMAND(ID_EDIT_FOLDING_MAP_LEVEL_6, &CBracketOutLineDlg::OnEditLevel6)
	ON_COMMAND(ID_EDIT_FOLDING_MAP_LEVEL_7, &CBracketOutLineDlg::OnEditLevel7)
	ON_COMMAND(ID_EDIT_FOLDING_MAP_LEVEL_8, &CBracketOutLineDlg::OnEditLevel8)
	ON_COMMAND(ID_EDIT_FOLDING_MAP_LEVEL_9, &CBracketOutLineDlg::OnEditLevel9)
	ON_COMMAND(ID_EDIT_FOLDING_MAP_SAVE_FILE, &CBracketOutLineDlg::OnEditSaveFile)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, &CBracketOutLineDlg::OnEditClear)
	ON_WM_CONTEXTMENU()
	ON_WM_SIZE()
	ON_MESSAGE(TREE_ADVANCE_MESSAGE::MSG_TREE_SELECT_ITEM, &CBracketOutLineDlg::OnTreeItemSelect)
#pragma warning(suppress: 26454)
END_MESSAGE_MAP()

void CBracketOutLineDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRect recClient;
	GetClientRect(&recClient);
	if (m_BracketTree.GetSafeHwnd())
	{
		m_BracketTree.MoveWindow(recClient);
	}
}

LRESULT CBracketOutLineDlg::OnTreeItemSelect(WPARAM wParam, LPARAM lParam)
{
	HTREEITEM hTreeItem = (HTREEITEM)lParam;
	if (hTreeItem)
	{
		CString strTreeItemText = m_BracketTree.GetItemText(hTreeItem);
		int pos = strTreeItemText.Find(_T("|"));
		if (pos != -1)
		{
			auto pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetExistedDocument(m_strFilePath));
			if (!pDoc)
			{
				pDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
			}
			else
			{
				AppUtils::SetActiveDocument(pDoc);
			}
			if (pDoc)
			{
				auto pEditor = pDoc->GetEditorCtrl();
				if (pEditor != NULL)
				{
					long lEditorLine = AppUtils::CStringToLong(strTreeItemText.Mid(0, pos).Trim());
					pEditor->GotoLine(lEditorLine);
					pEditor->SetLineCenterDisplay(lEditorLine);
				}
			}
		}
	}
	return 0L;
}

void CBracketOutLineDlg::OnContextMenu(CWnd * pWnd, CPoint point)
{
	CMenu menu;
	if (menu.LoadMenu(IDR_FOLDING_LIST_CONTEXT_MENU))
	{
		CMenu* pSubMenu = menu.GetSubMenu(0);
		if (!pSubMenu) return;
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}
