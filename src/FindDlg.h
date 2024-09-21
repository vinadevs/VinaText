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

class CScrollHelper;
class CVinaTextProgressBar;
class CEditorCtrl;
class CFindDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFindDlg)
public:
	CFindDlg(CWnd* pParent = NULL);
	virtual ~CFindDlg();

	void InitSearchReplaceFromEditor(const CString & strSearchWhat, BOOL bSelectEditbox = TRUE);
	void InitSearchReplaceFromExplorer(const CString& strFolderPath);
	void SearchFromEditor(const CString& strSearchWhat, SEARCH_TYPE searchType, BOOL bSeacrhNext = TRUE, BOOL bHideMessageBox = TRUE, BOOL bSaveSearchWord = TRUE);
	void SetFocusComboSearchWhat();
	void SaveDialogState();
	void LoadDialogState();
	void ClearAll();
	void UpdateSearchOptions();
	CString GetSearchWhat();
	unsigned int GetSearchOption();
	void EnableButtons(BOOL bEnable);

	ADVANCED_SEARCH_DATA GetSycnFindReplaceSettings();
	void SyncSearchReplaceSettings(const ADVANCED_SEARCH_DATA& settings);
	void UpdateUIVisual();

	enum { IDD = IDD_FIND };

protected:
	void SaveSearchString(const CString& strSearch);
	void InitComboSearchScope();
	void InitComboRegexPattern();
	void DoSearchNext(CString strSearchWhat, BOOL bHideMessageBox = TRUE, BOOL bSaveSearchWord = TRUE);
	void DoSeachPrevious(CString strSearchWhat);
	void SearchAllInDocument(CDocument* pDoc, TEXT_RESULT_SEARCH_REPLACE_DATA& ResultSearchData, const CString& strSearchWhat, unsigned int nSearchOptions);
	void RegisterResizingControls();

	CWndResizer m_resizer;
	CUndoRedoEditControl m_EditFilter;
	CMFCEditBrowseCtrl m_EditSpecialPath;
	CStringArray m_strSearchWhats;
	CComboboxMultiLine	m_comboSearchWhat;
	CComboBox	m_comboSearchScope;
	CComboBox   m_combRegexPattern;
	CString		m_strFileFilter;
	CString		m_strSpecificPath;
	BOOL	m_bMatchcase;
	BOOL	m_bMatchregex;
	BOOL	m_bMatchwords;
	BOOL	m_bAppendResult;
	BOOL	m_bShowFileNameOnly;
	BOOL	m_bExcludeSubFolder;
	std::unique_ptr<CScrollHelper> m_pScrollHelper{nullptr};
	int m_nSearchOptions = 0;

	// background search
	std::unique_ptr<CVinaTextProgressBar> m_pFindProgressBar{nullptr};
	static UINT FindBackgroundThreadProc(LPVOID pParam);
	HANDLE m_hThreadFindBackground = NULL;

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    
	virtual void OnOK() {}
	virtual void OnCancel() {}

	afx_msg void OnSearchNext();
	afx_msg void OnSeachPrevious();
	afx_msg void OnSearchAll();
	afx_msg void OnClickCheckBoxRegex();
	afx_msg void OnCbnSelchangeSearchScope();
	afx_msg void OnCbnSelchangeRegexPattern();
	afx_msg void OnSearchEditChange();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnCbnSelchangeSearchEditCombo();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFilterEditChange();
	DECLARE_MESSAGE_MAP()
};