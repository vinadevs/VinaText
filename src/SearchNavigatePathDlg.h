/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "DialogBase.h"
#include "afxdtctl.h"

// CSearchNavigatePathDlg dialog

class CVinaTextProgressBar;

class CSearchNavigatePathDlg : public CDlgBase
{
	DECLARE_DYNAMIC(CSearchNavigatePathDlg)

public:
	CSearchNavigatePathDlg(const CString& strFolder, CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchNavigatePathDlg();
	void SetSearchFolder(const CString& strFolder);
	void SetForcusOnEditFileName();

// Dialog Data
	enum { IDD = IDD_DIALOG_SEARCH_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;   // DDX/DDV support
	virtual BOOL OnInitDialog() override;
	virtual void PostNcDestroy() override;
	virtual void OnCancel() override;
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditSearchName();
	afx_msg void OnEnChangeEditFilter();
	afx_msg void OnBnClickedButtonSearchPathNextMatch();

protected:
	CString m_strFolder;
	BOOL m_bMatchCase;
	BOOL m_bSearchFileOnly;
	BOOL m_bAddResultToEditor;
	BOOL m_bSearchWithSize;
	BOOL m_bSearchWitheModifiedDate;
	BOOL m_bSearchWitheCreatedDate;
	BOOL m_bSearchInSubdirectory;
	BOOL m_bSearchWithoutMatchName;
	BOOL m_bAddResultToDockWindow;
	int  m_nRelaceResult;
	double m_dMinFileSize;
	double m_dMaxFileSize;
	std::vector<CString> m_ListPathIgnore;
	CMFCEditBrowseCtrl m_EditFilePath;
	CDateTimeCtrl m_StartModifiedDatePicker;
	CDateTimeCtrl m_EndModifiedDatePicker;
	CDateTimeCtrl m_StartCreatedDatePicker;
	CDateTimeCtrl m_EndCreatedDatePicker;

	// background search
	std::unique_ptr<CVinaTextProgressBar> m_pFindProgressBar;
	static UINT FindBackgroundThreadProc(LPVOID pParam);
	HANDLE m_hThreadFindBackground = NULL;

	afx_msg void OnBnClickedCheckSerachFileSize();
	afx_msg void OnBnClickedCheckDateCreatedBetween();
	afx_msg void OnBnClickedCheckDateModifiedBetween();
	afx_msg void OnBnClickedCheckSearchAllPath();
	afx_msg void OnBnClickedButtonRevealSearchFolder();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
