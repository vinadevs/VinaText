/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once
#include "afxdialogex.h"
#include "FilePartition.h"

// CPathComparatorDlg dialog

class CPathComparatorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPathComparatorDlg)

public:
	CPathComparatorDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPathComparatorDlg();

	enum { IDD = IDD_DIALOG_PATH_COMPARATOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog() override;
	virtual void PostNcDestroy() override;
	virtual void OnCancel() override;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();

private:
	CMFCEditBrowseCtrl m_LeftSideEdit;
	CMFCEditBrowseCtrl m_RightSideEdit;
	BOOL m_CheckDiffMatchCase;
	BOOL m_CheckDiffMatchIndentation;

	BOOL DoDiff(CString& strLeftPath, CString& strRightPath, CFileOptions& o);
};
