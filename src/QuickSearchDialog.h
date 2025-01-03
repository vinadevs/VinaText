/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "QuickReplace.h"
#include "QuickSearch.h"

// CQuickSearchDialog dialog

#define MARGIN_EDITOR_SCROLLBAR 20

class CEditorView;

class CQuickSearchDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CQuickSearchDialog)

public:
	CQuickSearchDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CQuickSearchDialog();

	enum { IDD = IDD_DIALOG_QUICK_SEARCH_AND_REPLACE };

	virtual void OnCancel();
	void SetParentView(CEditorView* pEditorView);
	CEditorView* GetParentView() { return m_pEditorView; }
	void InitSearchReplaceFromEditor(const CString& strSearchWhat, SEARCH_REPLACE_GOTO_DLG_TYPE searchType);
	CString GetSearchWhat();
	unsigned int GetSearchOption();
	void SaveDialogState();

	enum class TABACTIVE : unsigned int
	{
		FIND_TAB = 0,
		REPLACE_TAB = 1,
	};

private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
	virtual void OnOK() {}
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMoving(UINT nSide, LPRECT lpRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void RenderIndicatorWordsAndCount(const CString & strSearchWhat, int nSearchOption);

	DECLARE_MESSAGE_MAP()

	CRect m_SaveRect;
	CImageList *m_pImglist;
	CFont *m_pFont;
	CWnd* m_pCurrentTabShow;
	TABACTIVE m_uiActiveTab;
	CEditorView* m_pEditorView;
	CTabCtrl m_CTabCtrl;
	CQuickReplace m_FindAndReplaceDlg;
	CQuickSearch m_FindDlg;
};
