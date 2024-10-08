/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once
#include "afxdialogex.h"

class CScrollHelper;

// EditorSettingDlg dialog

class EditorSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EditorSettingDlg)

public:
	EditorSettingDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EditorSettingDlg();

	enum { IDD = IDD_DIALOG_SETTING_EDITOR };

	void UpdateGUISettings(BOOL bFromGUI);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK() {}
	virtual void OnCancel() {}
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedEditorFontNameButton();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedCheckUseUserCustomTabSettings();

	void InitLanguageSpellCheckCombo();
	void InitLanguageTranslateFromCombo();
	void InitLanguageTranslateToCombo();
	void InitCaretBlinkColorCombobox();
	void InitFolderMarginStyleCombobox();
	void InitIndicatorColorCombobox();
	void InitIndicatorStyleCombobox();
	void InitRenderIndicatorActionCombobox();
	void InitDefaultEOLNewFileCombobox();
	void InitIndentationTypeCombobox();
	void FromLanguageSpellCheckCombo();
	void FromLanguageTranslateFromCombo();
	void FromLanguageTranslateToCombo();
	void FromRenderIndicatorActionCombobox();
	void FromCaretBlinkColorCombobox();
	void FromFolderMarginStyleCombobox();
	void FromIndicatorColorCombobox();
	void FromIndicatorStyleCombobox();
	void FromDefaultEOLNewFileCombobox();
	void FromIndentationTypeCombobox();

	CComboBox m_LanguageSpellCheckCombo;
	CComboBox m_LanguageTranslateFromCombo;
	CComboBox m_LanguageTranslateToCombo;
	CComboBox m_IndicatorColorCombo;
	CComboBox m_IndicatorStyleCombo;
	CComboBox m_FolderMarginStyleCombo;
	CComboBox m_RenderIndicatorActionCombo;
	CComboBox m_CaretBlinkColorCombo;
	CComboBox m_DefaultEOLNewFileCombo;
	CComboBox m_IndentationTypeCombo;

	BOOL m_bAutoCompleteIgnoreCase{ FALSE };
	BOOL m_bAutoCompleteIgnoreNumbers{ FALSE };
	BOOL m_bDrawCaretLineFrame{ FALSE };
	BOOL m_bDrawFoldingLineUnderLineStyle{ FALSE };
	BOOL m_bEnableAutoComplete{ FALSE };
	BOOL m_bEnableAutoSearchWhenTyping{ FALSE };
	BOOL m_bEnableCaretBlink{ FALSE };
	BOOL m_bEnableHightLightFolder{ FALSE };
	BOOL m_bEnableMultipleCursor{ FALSE };
	BOOL m_bEnableProcessIndentationTab{ FALSE };
	BOOL m_bEnableSynchronizeScrolling{ FALSE };
	BOOL m_bEnableUrlHighlight{ FALSE };
	BOOL m_bReturnPreviousEditorState{ FALSE };
	BOOL m_bUseFolderMarginClassic{ FALSE };
	BOOL m_bAskBeforeReplaceInFiles{ FALSE };
	BOOL m_bEnableAutoDetectCodePage{ FALSE };
	BOOL m_bAutoSaveFileWhenCloseApp{ FALSE };
	BOOL m_bAutoAddNewLineAtTheEOF{ FALSE };
	BOOL m_bUseUserIndentationSettings{ FALSE };

	int m_nLineSpaceAbove{ 0 };
	int m_nLineSpaceBelow{ 0 };
	int m_nIntervalAutoSaveFileMinutes{ 0 };
	int m_nLongLineMaximum{ 0 };
	int m_nPageAlignmentWidth{ 0 };
	int m_nIndentationWidth{ 4 };

	CString m_lfFaceName = _T("Courier New");
	int m_iPointSize = 12;
	BOOL m_isBold = FALSE;
	BOOL m_isItalic = FALSE;
	BOOL m_isUnderline = FALSE;
	COLORREF m_color = RGB(0, 0, 0);

	std::unique_ptr<CScrollHelper> m_pScrollHelper{ nullptr };
};
