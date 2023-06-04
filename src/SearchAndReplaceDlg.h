/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "afxcmn.h"
#include "FindDlg.h"
#include "ReplaceDlg.h"
#include "GotoDlg.h"
#include "BracketOutLineDlg.h"

// CSearchAndReplaceWindowDlg dialog

class CSearchAndReplaceWindowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchAndReplaceWindowDlg)

public:
	CSearchAndReplaceWindowDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchAndReplaceWindowDlg();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support[
	virtual BOOL OnInitDialog();
	virtual void OnOK() {}
	virtual void OnCancel() {}

	void InitSearchReplaceFromEditor(const CString& strSearchWhat, SEARCH_REPLACE_GOTO_DLG_TYPE searchType );
	void SearchFromEditor(const CString& strSearchWhat, SEARCH_TYPE searchType, BOOL bSeacrhNext = TRUE, BOOL bHideMessageBox = TRUE, BOOL bSaveSearchWord = TRUE);
	void InitSearchReplaceFromExplorer(const CString& strFolderPath, SEARCH_REPLACE_GOTO_DLG_TYPE searchType);
	void UpdateFoldingMap(BOOL bActiveDialogTab = TRUE);
	void UpdateGotoRange(BOOL bActiveDialogTab = TRUE);
	void SaveDialogState();
	void ClearAll();
	CString GetSearchWhat();
	unsigned int GetSearchOption();
	void UpdateUIVisual();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCH_AND_REPLACE_DIALOG_PANE };
#endif

	DECLARE_MESSAGE_MAP()
	afx_msg void OnMoving(UINT nSide, LPRECT lpRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);

	enum class TABACTIVE : unsigned int
	{
		FIND_TAB = 0,
		FIND_REPLACE_TAB = 1,
		GOTO_TAB = 2,
		BRACKET_OUTLINE_TAB = 3,
	};

protected:
	CRect m_SaveRect;
	CImageList *m_pImglist;
	CFont *m_pFont;
	CTabCtrl m_CTabCtrl;
	CWnd* m_pCurrentTabShow;
	TABACTIVE m_uiActiveTab;
	CStringArray m_strFindstrings;

	// function dialogs
	CFindAndReplaceDlg m_FindAndReplaceDlg;
	CBracketOutLineDlg m_BracketOutLineDlg;
	CFindDlg m_FindDlg;
	CGotoDlg m_GotoDlg;
};