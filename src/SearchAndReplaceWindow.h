/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "DockPaneBase.h"
#include "SearchAndReplaceDlg.h"

class CSearchAndReplaceWindow : public CDockPaneBase
{
	DECLARE_DYNCREATE(CSearchAndReplaceWindow)
public:
	CSearchAndReplaceWindow();
	virtual ~CSearchAndReplaceWindow();

	void InitSearchReplaceFromEditor(const CString& strSearchWhat, SEARCH_REPLACE_GOTO_DLG_TYPE searchType);
	void SearchFromEditor(const CString& strSearchWhat, SEARCH_TYPE searchType, BOOL bSeacrhNext = TRUE, BOOL bHideMessageBox = TRUE, BOOL bSaveSearchWord = TRUE);
	void InitSearchReplaceFromExplorer(const CString& strFolderPath, SEARCH_REPLACE_GOTO_DLG_TYPE searchType);
	void UpdateFoldingMap(BOOL bActiveDialogTab = TRUE);
	void SaveDialogState();
	void ClearAll();
	CString GetSearchWhat();
	unsigned int GetSearchOption();

protected:
	DECLARE_MESSAGE_MAP()

	virtual void UpdateUIVisual();

	CSearchAndReplaceWindowDlg m_SearchAndReplaceWindowDlg;

	afx_msg LRESULT OnDockPaneUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

