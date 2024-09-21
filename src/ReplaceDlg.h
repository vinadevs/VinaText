/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "resource.h"
#include "UndoRedoEditControl.h"
#include "ComboboxMultiLine.h"
#include "FindReplaceTextWorker.h"
#include "WndResizer.h"

// CFindAndReplaceDlg dialog

class CScrollHelper;
class CVinaTextProgressBar;

class CFindAndReplaceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFindAndReplaceDlg)

public:
	CFindAndReplaceDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFindAndReplaceDlg();
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	enum { IDD = IDD_REPLACE };

	virtual BOOL OnInitDialog();
	void InitSearchReplaceFromEditor(const CString& strSearchWhat);
	void InitSearchReplaceFromExplorer(const CString& strFolderPath);
	void SaveSearchString(const CString& strSearch);
	void SaveReplaceString(const CString& strReplace);
	void SaveDialogState();
	void LoadDialogState();
	void ClearAll();
	void UpdateSearchOptions();
	CString GetSearchWhat();
	unsigned int GetSearchOption();

	ADVANCED_SEARCH_DATA GetSycnFindReplaceSettings();
	void SyncSearchReplaceSettings(const ADVANCED_SEARCH_DATA& settings);
	void UpdateUIVisual();

protected:
	BOOL	m_bMatchcase;
	BOOL	m_bMatchwords;
	BOOL	m_bMatchregex;
	BOOL	m_bAppendResult;
	BOOL	m_bShowFileNameOnly;
	BOOL	m_bExcludeSubFolder;
	CStringArray m_strSearchWhats;
	CStringArray m_strReplaceWiths;
	CComboboxMultiLine	m_comboSearchWhat;
	CComboboxMultiLine	m_comboReplaceWith;
	CComboBox	m_comboReplaceScope;
	CComboBox	m_combRegexPattern;
	CString		m_strFileFilter;
	CString		m_strSpecificPath;
	std::unique_ptr<CScrollHelper> m_pScrollHelper{nullptr};
	CMFCEditBrowseCtrl m_EditSpecialPath;
	CUndoRedoEditControl m_EditFilter;
	int m_nSearchOptions = 0;

	// background replace
	std::unique_ptr<CVinaTextProgressBar> m_pReplaceProgressBar{nullptr};
	static UINT ReplaceBackgroundThreadProc(LPVOID pParam);
	HANDLE m_hThreadReplaceBackground = NULL;
	CWndResizer m_resizer;

	BOOL AskBeforeContinueReplace(const CString& strWhereToReplace);
	void EnableButtons(BOOL bEnable);
	void DoSearchNext(CString strSearchWhat, BOOL bHideMessageBox = TRUE, BOOL bSaveSearchWord = TRUE);
	void InitComboReplaceScope();
	void InitComboRegexPattern();
	void ReplaceAllInDocument(CDocument* pDoc, TEXT_RESULT_SEARCH_REPLACE_DATA& ResultSearchData, const CString& strSearchWhat, const CString& strReplaceWith, unsigned int nSearchOptions);
	void RegisterResizingControls();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK() {}
	virtual void OnCancel() {}
	afx_msg void OnFindNext();
	afx_msg void OnReplaceWith();
	afx_msg void OnReplaceAll();
	afx_msg void OnCbnSelchangeSearchScope();
	afx_msg void OnCbnSelchangeRegexPattern();
	afx_msg void OnFilterEditChange();
	afx_msg void OnSearchEditChange();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnCbnSelchangeSearchEditCombo();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClickCheckBoxRegex();
	afx_msg HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};
