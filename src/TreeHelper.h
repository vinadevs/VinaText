/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CItemTracker 

class CTreeAdvance;

class CItemTracker
{
public:
	CItemTracker();
	~CItemTracker() = default;
	void Begin(CTreeAdvance* pTree, HTREEITEM hItemBegin);
	void End();
	void Reset();
	BOOL IsTracking() const { return m_bIsTracking; }
	void OnItemChange(UINT nFlags, HTREEITEM hItemNew);
private:
	BOOL m_bIsTracking;
	CTreeAdvance* m_pTree;
	HTREEITEM m_hItemBegin;
	HTREEITEM m_hItemLast;
};

/////////////////////////////////////////////////////////////////////////////
// CTreeAdvance 

class CTreeAdvance : public CTreeCtrl
{
public:
	CTreeAdvance();
	virtual ~CTreeAdvance() = default;
	void SetParrentWindow(CWnd* pWnd) { m_pParrentCtrl = pWnd; }
	HTREEITEM AddRowItem(LPCTSTR lpcLabel = NULL, HTREEITEM pParent = NULL, int nImage = -1, DWORD_PTR dwDatar = NULL, BOOL bHaveChild = FALSE);
	HTREEITEM AddRowItemCheck(LPCTSTR lpcLabel = NULL, BOOL IsChecked = TRUE, HTREEITEM pParent = NULL, int nImage = -1, DWORD_PTR dwPtr = NULL, BOOL bHaveChild = FALSE);
	CImageList* SetImageList(CImageList * pImageList);
	void SetBoldTreeItem(HTREEITEM pItem, BOOL bBold);
	void SetCheckTreeItem(HTREEITEM pItem, BOOL bCheck);
	virtual void ExpandItem(HTREEITEM hItem, BOOL bExpand = TRUE);
	void SelectTreeItem(HTREEITEM hItem);
	void GetSelectedTreeItem(CList<HTREEITEM, HTREEITEM>& itemList) const;
	int GetAllChildItem(HTREEITEM hItem, std::vector<HTREEITEM>& vecChild) const;
	HTREEITEM GetNextBelowItem(HTREEITEM hItem);
	BOOL IsBold(HTREEITEM hItem) const;
	BOOL IsExpanded(HTREEITEM hItem) const;
	BOOL IsChecked(HTREEITEM hItem) const;
	BOOL HasCheckbox(HTREEITEM hItem) const;
	BOOL IsSelected(HTREEITEM hItem) const;
	virtual void ExpandAll(HTREEITEM hItem = NULL, BOOL bExpand = TRUE);
	void SetCheckAll(HTREEITEM hItem = NULL, BOOL bCheck = TRUE);
	void SetBoldAll(HTREEITEM hItem = NULL, BOOL bBold = TRUE);
	std::vector<CString> GetAllItemTexts();
	void InitilizeTreeItem();
	void AdjustLayout() {};
	void ClearSelection(HTREEITEM hItemExcept = NULL, HTREEITEM hItemRoot = NULL);
	BOOL SelectItemRange(HTREEITEM hItemFrom, HTREEITEM hItemTo);
	BOOL SelectItemRange_Join(HTREEITEM hItemFrom, HTREEITEM hItemTo);
	void SetNewStyle(long lStyleMask, BOOL bSetBits);
	void EnableSetBoldDbClick(BOOL bEnable = FALSE) { m_EnableSetBoldDbclick = bEnable; }

protected:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnNMClick(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
	void OnSetFocus(CWnd* pOldWnd);

protected:
	virtual void OnBeforeItemDelete(HTREEITEM hItem) {}
	virtual BOOL IsGray(HTREEITEM hItem) { return FALSE; }

private:
	CWnd *m_pParrentCtrl;
	HTREEITEM m_hItemFirstSel;
	BOOL m_EnableSetBoldDbclick = FALSE;
	CItemTracker m_tracker;
};

/////////////////////////////////////////////////////////////////////////////
// CItemIterator 

class CItemIterator
{
public:
	CItemIterator(const CTreeCtrl* pTree, HTREEITEM hRoot = NULL);
	~CItemIterator() = default;
	BOOL HasNext();
	HTREEITEM GetNext();
private:
	void NextItem();
private:
	const CTreeCtrl*   m_pTree;
	HTREEITEM m_hRoot, m_hNext;
};