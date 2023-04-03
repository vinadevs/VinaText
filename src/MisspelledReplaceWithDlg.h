/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "afxwin.h"
#include "DialogBase.h"

// MisspelledReplaceWithDlg dialog

class MisspelledReplaceWithDlg : public CDlgBase
{
	DECLARE_DYNAMIC(MisspelledReplaceWithDlg)

public:
	MisspelledReplaceWithDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~MisspelledReplaceWithDlg();
	void SetSuggestionList(const std::vector<std::wstring>& suggestionList);
	void SetTargetWord(const CString& strTartgetWord);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MISSPELLED_REPLACE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	void DoReplace();

	CListBox m_ListSuggestion;
	std::vector<std::wstring> m_suggestionList;
	CString m_strTartgetWord;
	afx_msg void OnLbnDblclkListMisspelledReplace();
};
