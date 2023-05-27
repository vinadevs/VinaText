/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "ComboboxMultiLine.h"

// CQuickSearch dialog

class CQuickSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CQuickSearch)

public:
	CQuickSearch(CWnd* pParent = NULL);   // standard constructor
	virtual ~CQuickSearch();
	void InitSearchReplaceFromEditor(const CString& strSearchWhat);
	void SetFocusComboSearchWhat();
	CString GetSearchWhat();
	unsigned int GetSearchOption();
	void SaveDialogState();
	void LoadDialogState();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_QUICK_SEARCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	virtual void OnOK() {}
	virtual void OnCancel() {}

	BOOL m_bResetCaretPosition = TRUE;
	int m_nCurrentCaretPostion = 0;
	int m_nCurrentFirstLineVisible = 0;
	CComboboxMultiLine	m_comboSearchWhat;
	CComboBox	m_comboSearchOption;
	CStringArray m_strSearchWhats;
	unsigned int m_nSearchOptions = 0;
	void DoSearchNext(CString strSearchWhat, BOOL bHideMessageBox = TRUE, BOOL bSaveSearchWord = TRUE);
	void DoSeachPrevious(CString strSearchWhat);
	void SaveSearchString(const CString& strSearch);
	void InitComboSearchOption();
	void EnableButtons(BOOL bEnable);
	void UpdateQuickSearchOptionCombo();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSearchEditChange();
	afx_msg void OnBnClickedEditorQuickSearchNext();
	afx_msg void OnBnClickedEditorQuickSearchPrevious();
	afx_msg void OnBnClickedEditorQuickSearchAll();
	afx_msg void OnCbnSelchangeEditorQuickSearchOptionCombo();
	afx_msg void OnCbnSelchangeEditorQuickSearchCombo();
};
