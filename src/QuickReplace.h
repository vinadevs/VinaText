/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "ComboboxMultiLine.h"

// CQuickReplace dialog

class CQuickReplace : public CDialogEx
{
	DECLARE_DYNAMIC(CQuickReplace)

public:
	CQuickReplace(CWnd* pParent = NULL);   // standard constructor
	virtual ~CQuickReplace();
	void InitSearchReplaceFromEditor(const CString& strSearchWhat);
	CString GetSearchWhat();
	unsigned int GetSearchOption();
	void SaveDialogState();
	void LoadDialogState();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_QUICK_REPLACE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	virtual BOOL OnInitDialog();
	virtual void OnOK() {}
	virtual void OnCancel() {}

	BOOL m_bResetCaretPosition = TRUE;
	int m_nCurrentCaretPostion = 0;
	int m_nCurrentFirstLineVisible = 0;
	unsigned int m_nSearchOptions = 0;
	CStringArray m_strSearchWhats;
	CStringArray m_strReplaceWiths;
	CComboboxMultiLine	m_comboSearchWhat;
	CComboboxMultiLine	m_comboReplaceWith;
	CComboBox	m_comboSearchOption;

	void InitComboSearchOption();
	void EnableButtons(BOOL bEnable);
	void UpdateQuickSearchReplaceOptionCombo();
	void SaveSearchString(const CString& strSearch);
	void SaveReplaceString(const CString& strReplace);
	void DoSearchNext(CString strSearchWhat, BOOL bHideMessageBox = TRUE, BOOL bSaveSearchWord = TRUE);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSearchEditChange();
	afx_msg void OnCbnSelchangeEditorQuickSearchCombo();
	afx_msg void OnReplaceEditChange();
	afx_msg void OnCbnSelchangeEditorQuickReplaceCombo();
	afx_msg void OnBnClickedEditorQuickReplaceNext();
	afx_msg void OnBnClickedEditorQuickReplaceAll();
	afx_msg void OnCbnSelchangeEditorQuickReplaceOptionCombo();
	afx_msg void OnBnClickedEditorQuickSearchReplaceNext();
};
