/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "TreeHelper.h"
#include <functional>
#include "AppUtil.h"
#include "RAIIUtils.h"

/////////////////////////////////////////////////////////////////////////////
// CTreeAdvance 

CTreeAdvance::CTreeAdvance() : m_pParrentCtrl(NULL)
{
	m_hItemFirstSel = NULL;
}

void CTreeAdvance::InitilizeTreeItem()
{
	DeleteAllItems();
	m_hItemFirstSel = NULL;
	m_tracker.Reset();
}


BEGIN_MESSAGE_MAP(CTreeAdvance, CTreeCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CTreeAdvance::OnCustomDraw)
	ON_NOTIFY_REFLECT(NM_CLICK, &CTreeAdvance::OnNMClick)
	ON_NOTIFY_REFLECT(TVN_DELETEITEM, &CTreeAdvance::OnDeleteItem)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

HTREEITEM CTreeAdvance::AddRowItem(LPCTSTR lpcLabel, HTREEITEM pParent, int nImage, DWORD_PTR dwData, BOOL bHaveChild) {
	HTREEITEM hItem = NULL;
	hItem = InsertItem(TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM, LPSTR_TEXTCALLBACK, I_IMAGECALLBACK, I_IMAGECALLBACK, 0, 0, 0, pParent, TVI_LAST);
	TVITEM tvItem = { 0 };
	tvItem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_CHILDREN;
	tvItem.pszText = LPSTR_TEXTCALLBACK;
	tvItem.iImage = I_IMAGECALLBACK;
	tvItem.iSelectedImage = I_IMAGECALLBACK;
	tvItem.cChildren = bHaveChild;
	tvItem.hItem = hItem;
	SetItem(&tvItem);
	SetItemState(hItem, INDEXTOSTATEIMAGEMASK(0), TVIS_STATEIMAGEMASK);
	SetItemData(hItem, dwData);
	return hItem;
}

HTREEITEM CTreeAdvance::AddRowItemCheck(LPCTSTR lpcLabel, BOOL IsChecked, HTREEITEM pParent, int nImage, DWORD_PTR dwData, BOOL bHaveChild)
{
	HTREEITEM hItem = NULL;
	hItem = InsertItem(TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM, LPSTR_TEXTCALLBACK, I_IMAGECALLBACK, I_IMAGECALLBACK, 0, 0, 0, pParent, TVI_LAST);

	TVITEM tvItem = { 0 };
	tvItem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_CHILDREN;
	tvItem.pszText = LPSTR_TEXTCALLBACK;
	tvItem.iImage = I_IMAGECALLBACK;
	tvItem.iSelectedImage = I_IMAGECALLBACK;
	tvItem.cChildren = bHaveChild;
	tvItem.hItem = hItem;
	SetItem(&tvItem);

	if (IsChecked)
		SetItemState(hItem, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK);
	else
		SetItemState(hItem, INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK);
	SetItemData(hItem, dwData);
	return hItem;
}

CImageList* CTreeAdvance::SetImageList(CImageList * pImageList)
{
	return __super::SetImageList(pImageList, LVSIL_NORMAL);
}

void CTreeAdvance::SetBoldTreeItem(HTREEITEM hItem, BOOL bFlg)
{
	if (!hItem) return;

	int nState = bFlg ? TVIS_BOLD : 0;
	SetItemState(hItem, nState, TVIS_BOLD);
}

void CTreeAdvance::SetCheckTreeItem(HTREEITEM hItem, BOOL bFlag)
{
	if (!HasCheckbox(hItem)) return;

	int idx = (bFlag ? INDEXTOSTATEIMAGEMASK(2) : INDEXTOSTATEIMAGEMASK(1));
	SetItemState(hItem, idx, TVIS_STATEIMAGEMASK);
}

void CTreeAdvance::SelectTreeItem(HTREEITEM hItem)
{
	ClearSelection(hItem);
	m_hItemFirstSel = NULL;

	SelectItem(hItem);
}

void CTreeAdvance::GetSelectedTreeItem(CList<HTREEITEM, HTREEITEM>& itemList) const
{
	CItemIterator itr(this);
	while (itr.HasNext())
	{
		HTREEITEM hItem = itr.GetNext();
		if (GetItemState(hItem, TVIS_SELECTED) & TVIS_SELECTED)
			itemList.AddTail(hItem);
	}
}

int CTreeAdvance::GetAllChildItem(HTREEITEM hItem, std::vector<HTREEITEM>& vecChild) const
{
	if (!ItemHasChildren(hItem)) return 0;

	int nChild = 0;
	HTREEITEM hChild = GetChildItem(hItem);
	while (hChild)
	{
		vecChild.push_back(hChild);
		++nChild;
		hChild = GetNextItem(hChild, TVGN_NEXT);
	}
	return nChild;
}

void CTreeAdvance::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	UINT flag = 0;
	HTREEITEM hItem = HitTest(point, &flag);

	if (hItem)
	{
		BOOL bBold = IsBold(hItem);
		if (m_EnableSetBoldDbclick)
		{
			SetBoldTreeItem(hItem, !bBold);
		}
		if (m_pParrentCtrl)
		{
			m_pParrentCtrl->PostMessage(TREE_ADVANCE_MESSAGE::MSG_TREE_DOUBLE_CLICK, (WPARAM)0, (LPARAM)hItem);
		}
	}
	return;
}

void CTreeAdvance::OnRButtonDown(UINT nFlags, CPoint point)
{
	UINT flag;
	HTREEITEM hItem = HitTest(point, &flag);
	if (hItem && !IsSelected(hItem))
	{
		ClearSelection(hItem);
		m_hItemFirstSel = NULL;
		SelectItem(hItem);
	}

	__super::OnRButtonDown(nFlags, point);

	if (m_pParrentCtrl)
	{
		m_pParrentCtrl->PostMessage(TREE_ADVANCE_MESSAGE::MSG_TREE_RIGHT_CLICK, (WPARAM)0, (LPARAM)hItem);
	}
}

void CTreeAdvance::OnLButtonDown(UINT nFlags, CPoint point)
{
	UINT flag;
	HTREEITEM hItem = HitTest(point, &flag);

	SetFocus();
	if (!(TVHT_ONITEMBUTTON & flag))
		m_tracker.Begin(this, hItem);

	if ((nFlags & MK_CONTROL) && (nFlags & MK_SHIFT))
	{
		if (hItem)
		{
			HTREEITEM hItemOld = GetSelectedItem();
			UINT uOldSelState = hItemOld ?
				GetItemState(hItemOld, TVIS_SELECTED) : 0;

			if (hItemOld == hItem)
				SelectItem(NULL);	
			__super::OnLButtonDown(nFlags, point);

			SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED);

			if (hItemOld && hItemOld != hItem)
				SetItemState(hItemOld, uOldSelState, TVIS_SELECTED);

			SelectItemRange_Join(hItemOld, hItem);

			m_hItemFirstSel = NULL;
		}
	}
	else if (nFlags & MK_CONTROL)
	{
		if (hItem)
		{
			UINT uNewSelState =
				GetItemState(hItem, TVIS_SELECTED) & TVIS_SELECTED ?
				0 : TVIS_SELECTED;

			HTREEITEM hItemOld = GetSelectedItem();
			UINT uOldSelState = hItemOld ?
				GetItemState(hItemOld, TVIS_SELECTED) : 0;

			if (hItemOld == hItem)
				SelectItem(NULL);	
			__super::OnLButtonDown(nFlags, point);

			SetItemState(hItem, uNewSelState, TVIS_SELECTED);
			if (hItemOld && hItemOld != hItem)
				SetItemState(hItemOld, uOldSelState, TVIS_SELECTED);

			m_hItemFirstSel = NULL;

		}
	}
	else if (nFlags & MK_SHIFT)
	{
		if (!m_hItemFirstSel)
			m_hItemFirstSel = GetSelectedItem();

		if (GetSelectedItem() == hItem)
			SelectItem(NULL);
		__super::OnLButtonDown(nFlags, point);

		if (m_hItemFirstSel)
		{
			SelectItemRange(m_hItemFirstSel, hItem);
		}
	}
	else
	{
		ClearSelection(hItem);
		m_hItemFirstSel = NULL;

		SelectItem(hItem);

		__super::OnLButtonDown(nFlags, point);
	}

	if (TVHT_ONITEMSTATEICON & flag)
	{
		if (m_pParrentCtrl)
		{
			m_pParrentCtrl->PostMessage(TREE_ADVANCE_MESSAGE::MSG_CLICK_CHECKBOX, 0, (LPARAM)hItem);
		}
	}
	else if (TVHT_ONITEMBUTTON & flag)
	{
		if (m_pParrentCtrl)
		{
			m_pParrentCtrl->PostMessage(TREE_ADVANCE_MESSAGE::MSG_EXPAND_CHECKBOX, (WPARAM)0, (LPARAM)hItem);
		}
	}
	else if (hItem)
	{
		if (m_pParrentCtrl)
		{
			m_pParrentCtrl->PostMessage(TREE_ADVANCE_MESSAGE::MSG_TREE_SELECT_ITEM, (WPARAM)0, (LPARAM)hItem);
		}
	}


}

int CTreeAdvance::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;
	::SetWindowTheme(*this, L"explorer", 0);

	return 0;
}

void CTreeAdvance::OnSetFocus(CWnd* pOldWnd)
{
	__super::OnSetFocus(pOldWnd);
	m_pParrentCtrl->SendMessage(WM_SETFOCUS, (WPARAM)pOldWnd);
}

void CTreeAdvance::OnNMClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;

	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	UINT flags;
	HTREEITEM hItem = HitTest(point, &flags);
	if (TVHT_ONITEM & flags)
	{
		m_tracker.End();
		if (m_pParrentCtrl)
			m_pParrentCtrl->PostMessage(TREE_ADVANCE_MESSAGE::MSG_TREE_LEFT_BUTTON_UP, (WPARAM)0, (LPARAM)hItem);
	}
}

void CTreeAdvance::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_tracker.End();

	__super::OnLButtonUp(nFlags, point);

	if (m_pParrentCtrl)
	{
		UINT flag;
		HTREEITEM hItem = HitTest(point, &flag);
		m_pParrentCtrl->PostMessage(TREE_ADVANCE_MESSAGE::MSG_TREE_LEFT_BUTTON_UP, (WPARAM)0, (LPARAM)hItem);
	}
}

void CTreeAdvance::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_tracker.IsTracking())
	{
		UINT flag;
		HTREEITEM hItem = HitTest(point, &flag);
		m_tracker.OnItemChange(nFlags, hItem);
	}

	__super::OnMouseMove(nFlags, point);
}

void CTreeAdvance::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (VK_SPACE == nChar)
	{
		if (m_pParrentCtrl)
		{
			HTREEITEM hItem = GetSelectedItem();
			m_pParrentCtrl->PostMessage(TREE_ADVANCE_MESSAGE::MSG_CLICK_CHECKBOX, 0, (LPARAM)hItem);
		}
	}
	return __super::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CTreeAdvance::IsBold(HTREEITEM hItem) const
{
	if (!hItem) return FALSE;
	if (TVIS_BOLD & GetItemState(hItem, TVIS_BOLD))
		return TRUE;
	return FALSE;
}

BOOL CTreeAdvance::IsExpanded(HTREEITEM hItem) const
{
	if (!hItem) return FALSE;
	if (TVIS_EXPANDED & GetItemState(hItem, TVIS_EXPANDED))
		return TRUE;
	return FALSE;
}

BOOL CTreeAdvance::IsChecked(HTREEITEM hItem) const
{
	if (!hItem) return FALSE;
	if (GetItemState(hItem, TVIS_STATEIMAGEMASK) & INDEXTOSTATEIMAGEMASK(2))
		return TRUE;
	return FALSE;
}

BOOL CTreeAdvance::HasCheckbox(HTREEITEM hItem) const
{
	if (!hItem) return FALSE;
	if (GetItemState(hItem, TVIS_STATEIMAGEMASK) & TVIS_STATEIMAGEMASK)
		return TRUE;
	return FALSE;
}

BOOL CTreeAdvance::IsSelected(HTREEITEM hItem) const
{
	if (!hItem) return FALSE;
	if (GetItemState(hItem, TVIS_SELECTED) & TVIS_SELECTED)
		return TRUE;
	return FALSE;
}

void CTreeAdvance::ExpandItem(HTREEITEM hItem, BOOL bExpand)
{
	if (!hItem) return;
	int nState = bExpand ? TVIS_EXPANDED : 0;
	SetItemState(hItem, nState, TVIS_EXPANDED);
}

void CTreeAdvance::ExpandAll(HTREEITEM hItem, BOOL bExpand)
{
	CLockCtrlRedraw locker(this);
	int nState = bExpand ? TVIS_EXPANDED : 0;
	CItemIterator itr(this, hItem);
	while (itr.HasNext())
	{
		hItem = itr.GetNext();
		SetItemState(hItem, nState, TVIS_EXPANDED);
	}
}

void CTreeAdvance::SetCheckAll(HTREEITEM hItem, BOOL bCheck)
{
	CItemIterator itr(this, hItem);

	while (itr.HasNext())
	{
		HTREEITEM hNextItem = itr.GetNext();
		SetCheckTreeItem(hNextItem, bCheck);
	}
}

void CTreeAdvance::SetBoldAll(HTREEITEM hItem, BOOL bBold)
{
	CItemIterator itr(this, hItem);
	while (itr.HasNext())
	{
		HTREEITEM hNext = itr.GetNext();
		SetBoldTreeItem(hNext, bBold);
	}
}

std::vector<CString> CTreeAdvance::GetAllItemTexts()
{
	std::vector<CString> result;
	CItemIterator itr(this, GetRootItem());
	result.reserve(GetCount());
	while (itr.HasNext())
	{
		HTREEITEM hNextItem = itr.GetNext();
		CString strTreeItemText = GetItemText(hNextItem);
		result.push_back(strTreeItemText);
	}
	return result;
}

void CTreeAdvance::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTVCUSTOMDRAW pNMTVCD = (LPNMTVCUSTOMDRAW)pNMHDR;
	if (pNMTVCD == NULL)
	{
		*pResult = -1;
		return;
	}

	*pResult = CDRF_DODEFAULT;

	if (pNMTVCD->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYPOSTPAINT | CDRF_NOTIFYITEMDRAW;
	}
	else if (pNMTVCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
		if (IsGray((HTREEITEM)pNMTVCD->nmcd.dwItemSpec))
		{
			pNMTVCD->clrText = RGB(128, 128, 128);
			return;
		}
		if (IsBold((HTREEITEM)pNMTVCD->nmcd.dwItemSpec))
		{
			pNMTVCD->clrText = RGB(0, 0, 255);
			return;
		}
	}
}

void CTreeAdvance::ClearSelection(HTREEITEM hItemExcept, HTREEITEM hItemRoot)
{
	CItemIterator itr(this, hItemRoot);
	while (itr.HasNext())
	{
		HTREEITEM hItem = itr.GetNext();
		if (hItem != hItemExcept && (GetItemState(hItem, TVIS_SELECTED) & TVIS_SELECTED))
			SetItemState(hItem, 0, TVIS_SELECTED);
	}
}

BOOL CTreeAdvance::SelectItemRange(HTREEITEM hItemFrom, HTREEITEM hItemTo)
{
	HTREEITEM hItem = GetRootItem();

	while (hItem && hItem != hItemFrom && hItem != hItemTo)
	{
		hItem = GetNextVisibleItem(hItem);
		SetItemState(hItem, 0, TVIS_SELECTED);
	}

	if (!hItem) return FALSE;

	SelectItem(hItemTo);
	if (hItem == hItemTo)
	{
		hItemTo = hItemFrom;
		hItemFrom = hItem;
	}
	UINT uState = TVIS_SELECTED;
	while (hItem)
	{
		SetItemState(hItem, uState, TVIS_SELECTED);
		if (hItem == hItemTo)
			uState = 0;

		hItem = GetNextVisibleItem(hItem);
	}

	return TRUE;
}

BOOL CTreeAdvance::SelectItemRange_Join(HTREEITEM hItemFrom, HTREEITEM hItemTo)
{
	HTREEITEM hItem = GetRootItem();
	while (hItem && hItem != hItemFrom && hItem != hItemTo)
	{
		hItem = GetNextVisibleItem(hItem);
	}

	HTREEITEM hItemEnd = (hItem == hItemFrom) ? hItemTo : hItemFrom;
	while (hItem)
	{
		SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED);

		if (hItem == hItemEnd)
			break;

		hItem = GetNextVisibleItem(hItem);
	}

	return TRUE;
}

void CTreeAdvance::SetNewStyle(long lStyleMask, BOOL bSetBits)
{
	long lStyleOld;
	lStyleOld = GetWindowLong(m_hWnd, GWL_STYLE);
	lStyleOld &= ~lStyleMask;
	if (bSetBits) lStyleOld |= lStyleMask;
	SetWindowLong(m_hWnd, GWL_STYLE, lStyleOld);
	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
}

HTREEITEM CTreeAdvance::GetNextBelowItem(HTREEITEM hItem)
{
	HTREEITEM hNext = NULL;

	if (ItemHasChildren(hItem))
	{
		return GetChildItem(hItem);  
	}
	else
	{
		while ((hNext = GetNextSiblingItem(hItem)) == NULL)
		{
			if ((hItem = GetParentItem(hItem)) == NULL)
			{
				return NULL;
			}
		}
	}
	return hNext;
}

void CTreeAdvance::OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;
	HTREEITEM hDelItem = pNMTreeView->itemOld.hItem;
	OnBeforeItemDelete(hDelItem);
}

/////////////////////////////////////////////////////////////////////////////
// CItemIterator 

CItemIterator::CItemIterator(const CTreeCtrl* pTree, HTREEITEM hRoot)
	: m_pTree(pTree)
	, m_hRoot(hRoot)
	, m_hNext(hRoot)
{
	if (!pTree)
	{
		m_hRoot = m_hNext = NULL;
		return;
	}
	if (NULL == m_hRoot)
	{
		m_hNext = pTree->GetRootItem();
	}
}

BOOL CItemIterator::HasNext()
{
	return (m_hNext != NULL);
}

HTREEITEM CItemIterator::GetNext()
{
	HTREEITEM hRet = m_hNext;
	NextItem();
	return hRet;
}

void CItemIterator::NextItem()
{
	if (NULL == m_hNext) return;
	HTREEITEM hItem = m_hNext;
	m_hNext = m_pTree->GetChildItem(hItem);
	if (!m_hNext)
	{
		if (hItem == m_hRoot) return;
		if (!(m_hNext = m_pTree->GetNextSiblingItem(hItem)))
		{
			HTREEITEM hParentItem = hItem;
			while (!m_hNext)
			{
				if (!(hParentItem = m_pTree->GetParentItem(hParentItem))) break;
				if (hParentItem == m_hRoot) break;
				m_hNext = m_pTree->GetNextSiblingItem(hParentItem);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CItemTracker 

CItemTracker::CItemTracker()
{
	m_bIsTracking = FALSE;
	m_pTree = NULL;
	m_hItemBegin = NULL;
	m_hItemLast = NULL;
}

void CItemTracker::Begin(CTreeAdvance* pTree, HTREEITEM hItemBegin)
{
	if (m_bIsTracking || !pTree) { End(); return; }
	m_pTree = pTree;
	m_bIsTracking = TRUE;
	m_hItemBegin = hItemBegin ? hItemBegin : m_pTree->GetLastVisibleItem();
	m_hItemLast = hItemBegin;
}

void CItemTracker::End()
{
	Reset();
}

void CItemTracker::Reset()
{
	m_bIsTracking = FALSE;
	m_pTree = NULL;
	m_hItemBegin = NULL;
	m_hItemLast = NULL;
}

void CItemTracker::OnItemChange(UINT nFlags, HTREEITEM hItemNew)
{
	if (m_bIsTracking)
	{
		if (hItemNew && hItemNew != m_hItemLast)
		{
			if (nFlags & MK_CONTROL)
			{
				HTREEITEM hItemOld = m_pTree->GetSelectedItem();
				UINT uOldSelState = hItemOld ?
					m_pTree->GetItemState(hItemOld, TVIS_SELECTED) : 0;

				if (hItemOld == hItemNew) m_pTree->SelectItem(NULL);		

				m_pTree->SetItemState(hItemNew, TVIS_SELECTED, TVIS_SELECTED);

				if (hItemOld && hItemOld != hItemNew)
					m_pTree->SetItemState(hItemOld, uOldSelState, TVIS_SELECTED);

				m_pTree->SelectItemRange_Join(m_hItemBegin, hItemNew);

				m_hItemLast = hItemNew;
			}
			else
			{
				m_pTree->SelectItemRange(m_hItemBegin, hItemNew);
				m_hItemLast = hItemNew;
			}
		}
	}
}