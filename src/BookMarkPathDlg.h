#pragma once
/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "DialogBase.h"

class CBookMarkPathDlg : public CDlgBase
{
public:
	//Constructors
	CBookMarkPathDlg(const CString& strBookmarkFile, CWnd* pParent = NULL);

	//Member variables
	enum { IDD = IDD_BOOKMARK_PATH_DLG };

	void InitListBookmarkPath(BOOL bIsAddBookMark = FALSE);

protected:
	//Methods
	virtual void DoDataExchange(CDataExchange* pDX) override;
	virtual BOOL OnInitDialog() override;
	virtual void PostNcDestroy() override;
	virtual void OnCancel() override;
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CListCtrl m_listPath;
	CString m_strBookmarkFile;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddBookbarkPath();
	afx_msg void OnBnClickedRemoveBookbarkPath();
	afx_msg void OnBnClickedBookmarkOpen();
	afx_msg void OnBnClickedBookmarkToExplorer();
	afx_msg void OnBnClickedBookmarkRevealInExplorer();
	afx_msg void OnBnClickedBookmarkCopyPath();
	afx_msg void OnBnClickedBookmarkOpenCmd();
	afx_msg void OnBnClickedBookmarkClearAll();
	afx_msg void OnBnClickedBookmarkOpenContainer();
	afx_msg void OnNMDblclkListBookmarkPath(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBookmarkCopyClipboard();
};
