/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "resource.h"
#include "afxdialogex.h"
#include "EditorSettingDlg.h"
#include "AppSettings.h"
#include "ScrollHelper.h"
#include "AppUtil.h"

// EditorSettingDlg dialog

IMPLEMENT_DYNAMIC(EditorSettingDlg, CDialogEx)

EditorSettingDlg::EditorSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING_EDITOR, pParent)
{
	m_pScrollHelper = std::make_unique<CScrollHelper>();
	m_pScrollHelper->AttachWnd(this);
	m_pScrollHelper->SetDisplaySize(0, 1500);
}

EditorSettingDlg::~EditorSettingDlg() {}

void EditorSettingDlg::UpdateGUISettings(BOOL bFromGUI)
{
	if (bFromGUI)
	{
		UpdateData(TRUE);
		FromLanguageSpellCheckCombo();
		//FromLanguageTranslateFromCombo();
		FromLanguageTranslateToCombo();
		FromCaretBlinkColorCombobox();
		FromFolderMarginStyleCombobox();
		FromIndicatorColorCombobox();
		FromIndicatorColorCombobox();
		FromIndicatorStyleCombobox();
		FromRenderIndicatorActionCombobox();
		FromDefaultEOLNewFileCombobox();
		FromIndentationTypeCombobox();

		AppSettingMgr.m_bAutoCompleteIgnoreCase = m_bAutoCompleteIgnoreCase;
		AppSettingMgr.m_bAutoCompleteIgnoreNumbers = m_bAutoCompleteIgnoreNumbers;
		AppSettingMgr.m_bDrawCaretLineFrame = m_bDrawCaretLineFrame;
		AppSettingMgr.m_bDrawFoldingLineUnderLineStyle = m_bDrawFoldingLineUnderLineStyle;
		AppSettingMgr.m_bEnableAutoComplete = m_bEnableAutoComplete;
		AppSettingMgr.m_bEnableAutoSearchWhenTyping = m_bEnableAutoSearchWhenTyping;
		AppSettingMgr.m_bEnableCaretBlink = m_bEnableCaretBlink;
		AppSettingMgr.m_bEnableHightLightFolder = m_bEnableHightLightFolder;
		AppSettingMgr.m_bEnableMultipleCursor = m_bEnableMultipleCursor;
		AppSettingMgr.m_bEnableProcessIndentationTab = m_bEnableProcessIndentationTab;
		AppSettingMgr.m_bEnableSynchronizeScrolling = m_bEnableSynchronizeScrolling;
		AppSettingMgr.m_bEnableUrlHighlight = m_bEnableUrlHighlight;
		AppSettingMgr.m_bKeepPreviousEditorState = m_bReturnPreviousEditorState;
		AppSettingMgr.m_bUseFolderMarginClassic = m_bUseFolderMarginClassic;
		AppSettingMgr.m_bAskBeforeReplaceInFiles = m_bAskBeforeReplaceInFiles;
		AppSettingMgr.m_bEnableAutoDetectCodePage = m_bEnableAutoDetectCodePage;
		AppSettingMgr.m_nLineSpaceAbove = m_nLineSpaceAbove;
		AppSettingMgr.m_nLineSpaceBelow = m_nLineSpaceBelow;
		AppSettingMgr.m_nIntervalAutoSaveFileMinutes = m_nIntervalAutoSaveFileMinutes;
		AppSettingMgr.m_nLongLineMaximum = m_nLongLineMaximum;
		AppSettingMgr.m_nPageAlignmentWidth = m_nPageAlignmentWidth;
		AppSettingMgr.m_bAutoSaveFileWhenCloseApp = m_bAutoSaveFileWhenCloseApp;
		AppSettingMgr.m_bAutoAddNewLineAtTheEOF = m_bAutoAddNewLineAtTheEOF;
		AppSettingMgr.m_EditorFontSetting._lfFaceName = m_lfFaceName;
		AppSettingMgr.m_EditorFontSetting._iPointSize = m_iPointSize;
		AppSettingMgr.m_EditorFontSetting ._isBold = m_isBold;
		AppSettingMgr.m_EditorFontSetting._isItalic = m_isItalic;
		AppSettingMgr.m_EditorFontSetting._isUnderline = m_isUnderline;
		AppSettingMgr.m_EditorFontSetting._color = m_color;
		AppSettingMgr.m_bUseUserIndentationSettings = m_bUseUserIndentationSettings;
		AppSettingMgr.m_nEditorIndentationWidth = m_nIndentationWidth;
	}
	else
	{
		InitLanguageSpellCheckCombo();
		InitLanguageTranslateFromCombo();
		InitLanguageTranslateToCombo();
		InitCaretBlinkColorCombobox();
		InitFolderMarginStyleCombobox();
		InitIndicatorColorCombobox();
		InitIndicatorColorCombobox();
		InitIndicatorStyleCombobox();
		InitRenderIndicatorActionCombobox();
		InitDefaultEOLNewFileCombobox();
		InitIndentationTypeCombobox();

		m_bAutoCompleteIgnoreCase = AppSettingMgr.m_bAutoCompleteIgnoreCase;
		m_bAutoCompleteIgnoreNumbers = AppSettingMgr.m_bAutoCompleteIgnoreNumbers;
		m_bDrawCaretLineFrame = AppSettingMgr.m_bDrawCaretLineFrame;
		m_bDrawFoldingLineUnderLineStyle = AppSettingMgr.m_bDrawFoldingLineUnderLineStyle;
		m_bEnableAutoComplete = AppSettingMgr.m_bEnableAutoComplete;
		m_bEnableAutoSearchWhenTyping = AppSettingMgr.m_bEnableAutoSearchWhenTyping;
		m_bEnableCaretBlink = AppSettingMgr.m_bEnableCaretBlink;
		m_bEnableHightLightFolder = AppSettingMgr.m_bEnableHightLightFolder;
		m_bEnableMultipleCursor = AppSettingMgr.m_bEnableMultipleCursor;
		m_bEnableProcessIndentationTab = AppSettingMgr.m_bEnableProcessIndentationTab;
		m_bEnableSynchronizeScrolling = AppSettingMgr.m_bEnableSynchronizeScrolling;
		m_bEnableUrlHighlight = AppSettingMgr.m_bEnableUrlHighlight;
		m_bReturnPreviousEditorState = AppSettingMgr.m_bKeepPreviousEditorState;
		m_bUseFolderMarginClassic = AppSettingMgr.m_bUseFolderMarginClassic;
		m_bAskBeforeReplaceInFiles = AppSettingMgr.m_bAskBeforeReplaceInFiles;
		m_bEnableAutoDetectCodePage = AppSettingMgr.m_bEnableAutoDetectCodePage;
		m_nLineSpaceAbove = AppSettingMgr.m_nLineSpaceAbove;
		m_nLineSpaceBelow = AppSettingMgr.m_nLineSpaceBelow;
		m_nIntervalAutoSaveFileMinutes = AppSettingMgr.m_nIntervalAutoSaveFileMinutes;
		m_nLongLineMaximum = AppSettingMgr.m_nLongLineMaximum;
		m_nPageAlignmentWidth = AppSettingMgr.m_nPageAlignmentWidth;
		m_bAutoSaveFileWhenCloseApp = AppSettingMgr.m_bAutoSaveFileWhenCloseApp;
		m_bAutoAddNewLineAtTheEOF = AppSettingMgr.m_bAutoAddNewLineAtTheEOF;
		m_lfFaceName = AppSettingMgr.m_EditorFontSetting._lfFaceName;
		m_iPointSize = AppSettingMgr.m_EditorFontSetting._iPointSize;
		m_isBold = AppSettingMgr.m_EditorFontSetting._isBold;
		m_isItalic = AppSettingMgr.m_EditorFontSetting._isItalic;
		m_isUnderline = AppSettingMgr.m_EditorFontSetting._isUnderline;
		m_color = AppSettingMgr.m_EditorFontSetting._color;
		m_bUseUserIndentationSettings = AppSettingMgr.m_bUseUserIndentationSettings;
		m_nIndentationWidth = AppSettingMgr.m_nEditorIndentationWidth;
		UpdateData(FALSE);
	}
}

void EditorSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, ID_AUTO_COMPLETE_IGNORE_CASE, m_bAutoCompleteIgnoreCase);
	DDX_Check(pDX, ID_AUTO_COMPLETE_IGNORE_NUMBERS, m_bAutoCompleteIgnoreNumbers);
	DDX_Check(pDX, ID_DRAW_CARET_LINE_FRAME, m_bDrawCaretLineFrame);
	DDX_Check(pDX, ID_DRAW_FOLDING_LINE_UNDER_LINE_STYLE, m_bDrawFoldingLineUnderLineStyle);
	DDX_Check(pDX, ID_ENABLE_AUTO_COMPLETE, m_bEnableAutoComplete);
	DDX_Check(pDX, ID_ENABLE_AUTO_SEARCH_WHEN_TYPING, m_bEnableAutoSearchWhenTyping);
	DDX_Check(pDX, ID_ENABLE_CARET_BLINK, m_bEnableCaretBlink);
	DDX_Check(pDX, ID_ENABLE_HIGHT_LIGHT_FOLDER, m_bEnableHightLightFolder);
	DDX_Check(pDX, ID_ENABLE_MULTIPLE_CURSOR, m_bEnableMultipleCursor);
	DDX_Check(pDX, ID_ENABLE_PROCESS_INDENTATION_TAB, m_bEnableProcessIndentationTab);
	DDX_Check(pDX, ID_ENABLE_SYNCHRONIZE_SCROLLING, m_bEnableSynchronizeScrolling);
	DDX_Check(pDX, ID_ENABLE_URL_HIGHLIGHT, m_bEnableUrlHighlight);
	DDX_Check(pDX, ID_RETURN_PREVIOUS_EDITOR_STATE, m_bReturnPreviousEditorState);
	DDX_Check(pDX, ID_USE_FOLDER_MARGIN_CLASSIC, m_bUseFolderMarginClassic);
	DDX_Check(pDX, ID_ASK_BEFORE_REPLACE_IN_FILES, m_bAskBeforeReplaceInFiles);
	DDX_Check(pDX, ID_ENABLE_AUTO_DETECT_CODE_PAGE, m_bEnableAutoDetectCodePage);
	DDX_Check(pDX, ID_AUTO_SAVE_FILE_WHEN_CLOSE_APP, m_bAutoSaveFileWhenCloseApp);
	DDX_Control(pDX, ID_LANGUAGE_SPELL_CHECK_COMBO, m_LanguageSpellCheckCombo);
	DDX_Control(pDX, ID_LANGUAGE_TRANSLATE_FROM_COMBO, m_LanguageTranslateFromCombo);
	DDX_Control(pDX, ID_LANGUAGE_TRANSLATE_TO_COMBO, m_LanguageTranslateToCombo);
	DDX_Text(pDX, ID_LINE_SPACE_ABOVE_EDIT, m_nLineSpaceAbove);
	DDX_Text(pDX, ID_LINE_SPACE_BELOW_EDIT, m_nLineSpaceBelow);
	DDX_Text(pDX, ID_LONG_LINE_MAXIMUM_EDIT, m_nLongLineMaximum);
	DDX_Text(pDX, ID_INTERVAL_MINUTES_EDIT, m_nIntervalAutoSaveFileMinutes);
	DDX_Control(pDX, ID_INDICATOR_COLOR_COMBO, m_IndicatorColorCombo);
	DDX_Control(pDX, ID_INDICATOR_STYLE_COMBO, m_IndicatorStyleCombo);
	DDX_Control(pDX, ID_FOLDER_MARGIN_STYLE_COMBO, m_FolderMarginStyleCombo);
	DDX_Text(pDX, ID_PAGE_ALIGNMENT_WIDTH_EDIT, m_nPageAlignmentWidth);
	DDX_Control(pDX, ID_RENDER_INDICATOR_ACTION_COMBO, m_RenderIndicatorActionCombo);
	DDX_Control(pDX, ID_CARET_BLINK_COLOR_COMBO, m_CaretBlinkColorCombo);
	DDX_Control(pDX, ID_DEFAULT_EOL_NEW_FILE_COMBO, m_DefaultEOLNewFileCombo);
	DDX_Check(pDX, ID_AUTO_ADD_NEW_LINE_AT_EOF, m_bAutoAddNewLineAtTheEOF);
	DDX_Control(pDX, IDC_COMBO_INDENTATION_TYPE, m_IndentationTypeCombo);
	DDX_Text(pDX, IDC_EDIT_INDENTATION_WIDTH, m_nIndentationWidth);
	DDX_Check(pDX, IDC_CHECK_USE_USER_CUSTOM_TAB_SETTINGS, m_bUseUserIndentationSettings);
}

BOOL EditorSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdateGUISettings(FALSE);
	OnBnClickedCheckUseUserCustomTabSettings();
	return TRUE;
}

BOOL EditorSettingDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			GetParent()->GetParent()->SendMessage(WM_CLOSE, 0, 0);
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void EditorSettingDlg::InitLanguageSpellCheckCombo()
{
	m_LanguageSpellCheckCombo.ResetContent();
	m_LanguageSpellCheckCombo.AddString(_T("English-USA"));
	m_LanguageSpellCheckCombo.SetCurSel(0);
}

void EditorSettingDlg::InitLanguageTranslateFromCombo()
{
	m_LanguageTranslateFromCombo.ResetContent();
	m_LanguageTranslateFromCombo.AddString(_T("English")); // support english only now
	m_LanguageTranslateFromCombo.SetCurSel(0);
	/*m_LanguageTranslateFromCombo.AddString(_T("Afrikaans"));
	m_LanguageTranslateFromCombo.AddString(_T("Albanian"));
	m_LanguageTranslateFromCombo.AddString(_T("Arabic"));
	m_LanguageTranslateFromCombo.AddString(_T("Azerbaijani"));
	m_LanguageTranslateFromCombo.AddString(_T("Basque"));
	m_LanguageTranslateFromCombo.AddString(_T("Belarusian"));
	m_LanguageTranslateFromCombo.AddString(_T("Bengali"));
	m_LanguageTranslateFromCombo.AddString(_T("Bulgarian"));
	m_LanguageTranslateFromCombo.AddString(_T("Catalan"));
	m_LanguageTranslateFromCombo.AddString(_T("Chinese Simplified"));
	m_LanguageTranslateFromCombo.AddString(_T("Chinese Traditional"));
	m_LanguageTranslateFromCombo.AddString(_T("Croatian"));
	m_LanguageTranslateFromCombo.AddString(_T("Czech"));
	m_LanguageTranslateFromCombo.AddString(_T("Danish"));
	m_LanguageTranslateFromCombo.AddString(_T("Dutch"));
	m_LanguageTranslateFromCombo.AddString(_T("English"));
	m_LanguageTranslateFromCombo.AddString(_T("Esperanto"));
	m_LanguageTranslateFromCombo.AddString(_T("Estonian"));
	m_LanguageTranslateFromCombo.AddString(_T("Filipino"));
	m_LanguageTranslateFromCombo.AddString(_T("Finnish"));
	m_LanguageTranslateFromCombo.AddString(_T("French"));
	m_LanguageTranslateFromCombo.AddString(_T("Galician"));
	m_LanguageTranslateFromCombo.AddString(_T("Georgian"));
	m_LanguageTranslateFromCombo.AddString(_T("German"));
	m_LanguageTranslateFromCombo.AddString(_T("Greek"));
	m_LanguageTranslateFromCombo.AddString(_T("Gujarati"));
	m_LanguageTranslateFromCombo.AddString(_T("Haitian Creole"));
	m_LanguageTranslateFromCombo.AddString(_T("Hebrew"));
	m_LanguageTranslateFromCombo.AddString(_T("Hindi"));
	m_LanguageTranslateFromCombo.AddString(_T("Hungarian"));
	m_LanguageTranslateFromCombo.AddString(_T("Icelandic"));
	m_LanguageTranslateFromCombo.AddString(_T("Indonesian"));
	m_LanguageTranslateFromCombo.AddString(_T("Irish"));
	m_LanguageTranslateFromCombo.AddString(_T("Italian"));
	m_LanguageTranslateFromCombo.AddString(_T("Japanese"));
	m_LanguageTranslateFromCombo.AddString(_T("Kannada"));
	m_LanguageTranslateFromCombo.AddString(_T("Korean"));
	m_LanguageTranslateFromCombo.AddString(_T("Latin"));
	m_LanguageTranslateFromCombo.AddString(_T("Latvian"));
	m_LanguageTranslateFromCombo.AddString(_T("Lithuanian"));
	m_LanguageTranslateFromCombo.AddString(_T("Macedonian"));
	m_LanguageTranslateFromCombo.AddString(_T("Malay"));
	m_LanguageTranslateFromCombo.AddString(_T("Maltese"));
	m_LanguageTranslateFromCombo.AddString(_T("Norwegian"));
	m_LanguageTranslateFromCombo.AddString(_T("Persian"));
	m_LanguageTranslateFromCombo.AddString(_T("Polish"));
	m_LanguageTranslateFromCombo.AddString(_T("Portuguese"));
	m_LanguageTranslateFromCombo.AddString(_T("Romanian"));
	m_LanguageTranslateFromCombo.AddString(_T("Russian"));
	m_LanguageTranslateFromCombo.AddString(_T("Serbian"));
	m_LanguageTranslateFromCombo.AddString(_T("Slovak"));
	m_LanguageTranslateFromCombo.AddString(_T("Slovenian"));
	m_LanguageTranslateFromCombo.AddString(_T("Spanish"));
	m_LanguageTranslateFromCombo.AddString(_T("Swahili"));
	m_LanguageTranslateFromCombo.AddString(_T("Swedish"));
	m_LanguageTranslateFromCombo.AddString(_T("Tamil"));
	m_LanguageTranslateFromCombo.AddString(_T("Telugu"));
	m_LanguageTranslateFromCombo.AddString(_T("Thai"));
	m_LanguageTranslateFromCombo.AddString(_T("Turkish"));
	m_LanguageTranslateFromCombo.AddString(_T("Ukrainian"));
	m_LanguageTranslateFromCombo.AddString(_T("Urdu"));
	m_LanguageTranslateFromCombo.AddString(_T("Vietnamese"));
	m_LanguageTranslateFromCombo.AddString(_T("Welsh"));
	m_LanguageTranslateFromCombo.AddString(_T("Yiddish"));*/
	/*if (AppSettingMgr.m_strLanguageTranslateFrom == _T("af")) m_LanguageTranslateFromCombo.SetCurSel(0);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("sq")) m_LanguageTranslateFromCombo.SetCurSel(1);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ar")) m_LanguageTranslateFromCombo.SetCurSel(2);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("az")) m_LanguageTranslateFromCombo.SetCurSel(3);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("eu")) m_LanguageTranslateFromCombo.SetCurSel(4);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("be")) m_LanguageTranslateFromCombo.SetCurSel(5);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("bn")) m_LanguageTranslateFromCombo.SetCurSel(6);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("bg")) m_LanguageTranslateFromCombo.SetCurSel(7);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ca")) m_LanguageTranslateFromCombo.SetCurSel(8);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("zh-CN")) m_LanguageTranslateFromCombo.SetCurSel(9);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("zh-TW")) m_LanguageTranslateFromCombo.SetCurSel(10);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("hr")) m_LanguageTranslateFromCombo.SetCurSel(11);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("cs")) m_LanguageTranslateFromCombo.SetCurSel(12);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("da")) m_LanguageTranslateFromCombo.SetCurSel(13);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("nl")) m_LanguageTranslateFromCombo.SetCurSel(14);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("en")) m_LanguageTranslateFromCombo.SetCurSel(15);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("eo")) m_LanguageTranslateFromCombo.SetCurSel(16);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("et")) m_LanguageTranslateFromCombo.SetCurSel(17);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("tl")) m_LanguageTranslateFromCombo.SetCurSel(18);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("fi")) m_LanguageTranslateFromCombo.SetCurSel(19);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("fr")) m_LanguageTranslateFromCombo.SetCurSel(20);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("gl")) m_LanguageTranslateFromCombo.SetCurSel(21);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ka")) m_LanguageTranslateFromCombo.SetCurSel(22);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("de")) m_LanguageTranslateFromCombo.SetCurSel(23);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("el")) m_LanguageTranslateFromCombo.SetCurSel(24);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("gu")) m_LanguageTranslateFromCombo.SetCurSel(25);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ht")) m_LanguageTranslateFromCombo.SetCurSel(26);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("iw")) m_LanguageTranslateFromCombo.SetCurSel(27);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("hi")) m_LanguageTranslateFromCombo.SetCurSel(28);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("hu")) m_LanguageTranslateFromCombo.SetCurSel(29);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("is")) m_LanguageTranslateFromCombo.SetCurSel(30);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("id")) m_LanguageTranslateFromCombo.SetCurSel(31);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ga")) m_LanguageTranslateFromCombo.SetCurSel(32);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("it")) m_LanguageTranslateFromCombo.SetCurSel(33);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ja")) m_LanguageTranslateFromCombo.SetCurSel(34);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("kn")) m_LanguageTranslateFromCombo.SetCurSel(35);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ko")) m_LanguageTranslateFromCombo.SetCurSel(36);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("la")) m_LanguageTranslateFromCombo.SetCurSel(37);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("lv")) m_LanguageTranslateFromCombo.SetCurSel(38);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("lt")) m_LanguageTranslateFromCombo.SetCurSel(39);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("mk")) m_LanguageTranslateFromCombo.SetCurSel(40);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ms")) m_LanguageTranslateFromCombo.SetCurSel(41);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("mt")) m_LanguageTranslateFromCombo.SetCurSel(42);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("no")) m_LanguageTranslateFromCombo.SetCurSel(43);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("fa")) m_LanguageTranslateFromCombo.SetCurSel(44);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("pl")) m_LanguageTranslateFromCombo.SetCurSel(45);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("pt")) m_LanguageTranslateFromCombo.SetCurSel(46);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ro")) m_LanguageTranslateFromCombo.SetCurSel(47);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ru")) m_LanguageTranslateFromCombo.SetCurSel(48);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("sr")) m_LanguageTranslateFromCombo.SetCurSel(49);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("sk")) m_LanguageTranslateFromCombo.SetCurSel(50);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("sl")) m_LanguageTranslateFromCombo.SetCurSel(51);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("es")) m_LanguageTranslateFromCombo.SetCurSel(52);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("sw")) m_LanguageTranslateFromCombo.SetCurSel(53);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("sv")) m_LanguageTranslateFromCombo.SetCurSel(54);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ta")) m_LanguageTranslateFromCombo.SetCurSel(55);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("te")) m_LanguageTranslateFromCombo.SetCurSel(56);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("th")) m_LanguageTranslateFromCombo.SetCurSel(57);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("tr")) m_LanguageTranslateFromCombo.SetCurSel(58);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("uk")) m_LanguageTranslateFromCombo.SetCurSel(59);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("ur")) m_LanguageTranslateFromCombo.SetCurSel(60);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("vi")) m_LanguageTranslateFromCombo.SetCurSel(61);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("cy")) m_LanguageTranslateFromCombo.SetCurSel(62);
	else if (AppSettingMgr.m_strLanguageTranslateFrom == _T("yi")) m_LanguageTranslateFromCombo.SetCurSel(63);*/
}

void EditorSettingDlg::InitLanguageTranslateToCombo()
{
	m_LanguageTranslateToCombo.ResetContent();
	m_LanguageTranslateToCombo.AddString(_T("Afrikaans"));
	m_LanguageTranslateToCombo.AddString(_T("Albanian"));
	m_LanguageTranslateToCombo.AddString(_T("Arabic"));
	m_LanguageTranslateToCombo.AddString(_T("Azerbaijani"));
	m_LanguageTranslateToCombo.AddString(_T("Basque"));
	m_LanguageTranslateToCombo.AddString(_T("Belarusian"));
	m_LanguageTranslateToCombo.AddString(_T("Bengali"));
	m_LanguageTranslateToCombo.AddString(_T("Bulgarian"));
	m_LanguageTranslateToCombo.AddString(_T("Catalan"));
	m_LanguageTranslateToCombo.AddString(_T("Chinese Simplified"));
	m_LanguageTranslateToCombo.AddString(_T("Chinese Traditional"));
	m_LanguageTranslateToCombo.AddString(_T("Croatian"));
	m_LanguageTranslateToCombo.AddString(_T("Czech"));
	m_LanguageTranslateToCombo.AddString(_T("Danish"));
	m_LanguageTranslateToCombo.AddString(_T("Dutch"));
	m_LanguageTranslateToCombo.AddString(_T("English"));
	m_LanguageTranslateToCombo.AddString(_T("Esperanto"));
	m_LanguageTranslateToCombo.AddString(_T("Estonian"));
	m_LanguageTranslateToCombo.AddString(_T("Filipino"));
	m_LanguageTranslateToCombo.AddString(_T("Finnish"));
	m_LanguageTranslateToCombo.AddString(_T("French"));
	m_LanguageTranslateToCombo.AddString(_T("Galician"));
	m_LanguageTranslateToCombo.AddString(_T("Georgian"));
	m_LanguageTranslateToCombo.AddString(_T("German"));
	m_LanguageTranslateToCombo.AddString(_T("Greek"));
	m_LanguageTranslateToCombo.AddString(_T("Gujarati"));
	m_LanguageTranslateToCombo.AddString(_T("Haitian Creole"));
	m_LanguageTranslateToCombo.AddString(_T("Hebrew"));
	m_LanguageTranslateToCombo.AddString(_T("Hindi"));
	m_LanguageTranslateToCombo.AddString(_T("Hungarian"));
	m_LanguageTranslateToCombo.AddString(_T("Icelandic"));
	m_LanguageTranslateToCombo.AddString(_T("Indonesian"));
	m_LanguageTranslateToCombo.AddString(_T("Irish"));
	m_LanguageTranslateToCombo.AddString(_T("Italian"));
	m_LanguageTranslateToCombo.AddString(_T("Japanese"));
	m_LanguageTranslateToCombo.AddString(_T("Kannada"));
	m_LanguageTranslateToCombo.AddString(_T("Korean"));
	m_LanguageTranslateToCombo.AddString(_T("Latin"));
	m_LanguageTranslateToCombo.AddString(_T("Latvian"));
	m_LanguageTranslateToCombo.AddString(_T("Lithuanian"));
	m_LanguageTranslateToCombo.AddString(_T("Macedonian"));
	m_LanguageTranslateToCombo.AddString(_T("Malay"));
	m_LanguageTranslateToCombo.AddString(_T("Maltese"));
	m_LanguageTranslateToCombo.AddString(_T("Norwegian"));
	m_LanguageTranslateToCombo.AddString(_T("Persian"));
	m_LanguageTranslateToCombo.AddString(_T("Polish"));
	m_LanguageTranslateToCombo.AddString(_T("Portuguese"));
	m_LanguageTranslateToCombo.AddString(_T("Romanian"));
	m_LanguageTranslateToCombo.AddString(_T("Russian"));
	m_LanguageTranslateToCombo.AddString(_T("Serbian"));
	m_LanguageTranslateToCombo.AddString(_T("Slovak"));
	m_LanguageTranslateToCombo.AddString(_T("Slovenian"));
	m_LanguageTranslateToCombo.AddString(_T("Spanish"));
	m_LanguageTranslateToCombo.AddString(_T("Swahili"));
	m_LanguageTranslateToCombo.AddString(_T("Swedish"));
	m_LanguageTranslateToCombo.AddString(_T("Tamil"));
	m_LanguageTranslateToCombo.AddString(_T("Telugu"));
	m_LanguageTranslateToCombo.AddString(_T("Thai"));
	m_LanguageTranslateToCombo.AddString(_T("Turkish"));
	m_LanguageTranslateToCombo.AddString(_T("Ukrainian"));
	m_LanguageTranslateToCombo.AddString(_T("Urdu"));
	m_LanguageTranslateToCombo.AddString(_T("Vietnamese"));
	m_LanguageTranslateToCombo.AddString(_T("Welsh"));
	m_LanguageTranslateToCombo.AddString(_T("Yiddish"));
	if (AppSettingMgr.m_strLanguageTranslateTo == _T("af")) m_LanguageTranslateToCombo.SetCurSel(0);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("sq")) m_LanguageTranslateToCombo.SetCurSel(1);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ar")) m_LanguageTranslateToCombo.SetCurSel(2);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("az")) m_LanguageTranslateToCombo.SetCurSel(3);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("eu")) m_LanguageTranslateToCombo.SetCurSel(4);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("be")) m_LanguageTranslateToCombo.SetCurSel(5);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("bn")) m_LanguageTranslateToCombo.SetCurSel(6);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("bg")) m_LanguageTranslateToCombo.SetCurSel(7);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ca")) m_LanguageTranslateToCombo.SetCurSel(8);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("zh-CN")) m_LanguageTranslateToCombo.SetCurSel(9);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("zh-TW")) m_LanguageTranslateToCombo.SetCurSel(10);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("hr")) m_LanguageTranslateToCombo.SetCurSel(11);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("cs")) m_LanguageTranslateToCombo.SetCurSel(12);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("da")) m_LanguageTranslateToCombo.SetCurSel(13);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("nl")) m_LanguageTranslateToCombo.SetCurSel(14);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("en")) m_LanguageTranslateToCombo.SetCurSel(15);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("eo")) m_LanguageTranslateToCombo.SetCurSel(16);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("et")) m_LanguageTranslateToCombo.SetCurSel(17);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("tl")) m_LanguageTranslateToCombo.SetCurSel(18);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("fi")) m_LanguageTranslateToCombo.SetCurSel(19);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("fr")) m_LanguageTranslateToCombo.SetCurSel(20);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("gl")) m_LanguageTranslateToCombo.SetCurSel(21);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ka")) m_LanguageTranslateToCombo.SetCurSel(22);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("de")) m_LanguageTranslateToCombo.SetCurSel(23);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("el")) m_LanguageTranslateToCombo.SetCurSel(24);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("gu")) m_LanguageTranslateToCombo.SetCurSel(25);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ht")) m_LanguageTranslateToCombo.SetCurSel(26);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("iw")) m_LanguageTranslateToCombo.SetCurSel(27);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("hi")) m_LanguageTranslateToCombo.SetCurSel(28);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("hu")) m_LanguageTranslateToCombo.SetCurSel(29);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("is")) m_LanguageTranslateToCombo.SetCurSel(30);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("id")) m_LanguageTranslateToCombo.SetCurSel(31);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ga")) m_LanguageTranslateToCombo.SetCurSel(32);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("it")) m_LanguageTranslateToCombo.SetCurSel(33);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ja")) m_LanguageTranslateToCombo.SetCurSel(34);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("kn")) m_LanguageTranslateToCombo.SetCurSel(35);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ko")) m_LanguageTranslateToCombo.SetCurSel(36);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("la")) m_LanguageTranslateToCombo.SetCurSel(37);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("lv")) m_LanguageTranslateToCombo.SetCurSel(38);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("lt")) m_LanguageTranslateToCombo.SetCurSel(39);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("mk")) m_LanguageTranslateToCombo.SetCurSel(40);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ms")) m_LanguageTranslateToCombo.SetCurSel(41);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("mt")) m_LanguageTranslateToCombo.SetCurSel(42);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("no")) m_LanguageTranslateToCombo.SetCurSel(43);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("fa")) m_LanguageTranslateToCombo.SetCurSel(44);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("pl")) m_LanguageTranslateToCombo.SetCurSel(45);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("pt")) m_LanguageTranslateToCombo.SetCurSel(46);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ro")) m_LanguageTranslateToCombo.SetCurSel(47);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ru")) m_LanguageTranslateToCombo.SetCurSel(48);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("sr")) m_LanguageTranslateToCombo.SetCurSel(49);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("sk")) m_LanguageTranslateToCombo.SetCurSel(50);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("sl")) m_LanguageTranslateToCombo.SetCurSel(51);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("es")) m_LanguageTranslateToCombo.SetCurSel(52);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("sw")) m_LanguageTranslateToCombo.SetCurSel(53);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("sv")) m_LanguageTranslateToCombo.SetCurSel(54);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ta")) m_LanguageTranslateToCombo.SetCurSel(55);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("te")) m_LanguageTranslateToCombo.SetCurSel(56);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("th")) m_LanguageTranslateToCombo.SetCurSel(57);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("tr")) m_LanguageTranslateToCombo.SetCurSel(58);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("uk")) m_LanguageTranslateToCombo.SetCurSel(59);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("ur")) m_LanguageTranslateToCombo.SetCurSel(60);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("vi")) m_LanguageTranslateToCombo.SetCurSel(61);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("cy")) m_LanguageTranslateToCombo.SetCurSel(62);
	else if (AppSettingMgr.m_strLanguageTranslateTo == _T("yi")) m_LanguageTranslateToCombo.SetCurSel(63);
}

void EditorSettingDlg::FromLanguageSpellCheckCombo()
{
}

void EditorSettingDlg::FromLanguageTranslateFromCombo()
{
	int iSel = m_LanguageTranslateFromCombo.GetCurSel();
	switch (iSel)
	{
	case 0: AppSettingMgr.m_strLanguageTranslateFrom = _T("af"); break;
	case 1: AppSettingMgr.m_strLanguageTranslateFrom = _T("sq"); break;
	case 2: AppSettingMgr.m_strLanguageTranslateFrom = _T("ar"); break;
	case 3: AppSettingMgr.m_strLanguageTranslateFrom = _T("az"); break;
	case 4: AppSettingMgr.m_strLanguageTranslateFrom = _T("eu"); break;
	case 5: AppSettingMgr.m_strLanguageTranslateFrom = _T("be"); break;
	case 6: AppSettingMgr.m_strLanguageTranslateFrom = _T("bn"); break;
	case 7: AppSettingMgr.m_strLanguageTranslateFrom = _T("bg"); break;
	case 8: AppSettingMgr.m_strLanguageTranslateFrom = _T("ca"); break;
	case 9: AppSettingMgr.m_strLanguageTranslateFrom = _T("zh-CN"); break;
	case 10: AppSettingMgr.m_strLanguageTranslateFrom = _T("zh-TW"); break;
	case 11: AppSettingMgr.m_strLanguageTranslateFrom = _T("hr"); break;
	case 12: AppSettingMgr.m_strLanguageTranslateFrom = _T("cs"); break;
	case 13: AppSettingMgr.m_strLanguageTranslateFrom = _T("da"); break;
	case 14: AppSettingMgr.m_strLanguageTranslateFrom = _T("nl"); break;
	case 15: AppSettingMgr.m_strLanguageTranslateFrom = _T("en"); break;
	case 16: AppSettingMgr.m_strLanguageTranslateFrom = _T("eo"); break;
	case 17: AppSettingMgr.m_strLanguageTranslateFrom = _T("et"); break;
	case 18: AppSettingMgr.m_strLanguageTranslateFrom = _T("tl"); break;
	case 19: AppSettingMgr.m_strLanguageTranslateFrom = _T("fi"); break;
	case 20: AppSettingMgr.m_strLanguageTranslateFrom = _T("fr"); break;
	case 21: AppSettingMgr.m_strLanguageTranslateFrom = _T("gl"); break;
	case 22: AppSettingMgr.m_strLanguageTranslateFrom = _T("ka"); break;
	case 23: AppSettingMgr.m_strLanguageTranslateFrom = _T("de"); break;
	case 24: AppSettingMgr.m_strLanguageTranslateFrom = _T("el"); break;
	case 25: AppSettingMgr.m_strLanguageTranslateFrom = _T("gu"); break;
	case 26: AppSettingMgr.m_strLanguageTranslateFrom = _T("ht"); break;
	case 27: AppSettingMgr.m_strLanguageTranslateFrom = _T("iw"); break;
	case 28: AppSettingMgr.m_strLanguageTranslateFrom = _T("hi"); break;
	case 29: AppSettingMgr.m_strLanguageTranslateFrom = _T("hu"); break;
	case 30: AppSettingMgr.m_strLanguageTranslateFrom = _T("is"); break;
	case 31: AppSettingMgr.m_strLanguageTranslateFrom = _T("id"); break;
	case 32: AppSettingMgr.m_strLanguageTranslateFrom = _T("ga"); break;
	case 33: AppSettingMgr.m_strLanguageTranslateFrom = _T("it"); break;
	case 34: AppSettingMgr.m_strLanguageTranslateFrom = _T("ja"); break;
	case 35: AppSettingMgr.m_strLanguageTranslateFrom = _T("kn"); break;
	case 36: AppSettingMgr.m_strLanguageTranslateFrom = _T("ko"); break;
	case 37: AppSettingMgr.m_strLanguageTranslateFrom = _T("la"); break;
	case 38: AppSettingMgr.m_strLanguageTranslateFrom = _T("lv"); break;
	case 39: AppSettingMgr.m_strLanguageTranslateFrom = _T("lt"); break;
	case 40: AppSettingMgr.m_strLanguageTranslateFrom = _T("mk"); break;
	case 41: AppSettingMgr.m_strLanguageTranslateFrom = _T("ms"); break;
	case 42: AppSettingMgr.m_strLanguageTranslateFrom = _T("mt"); break;
	case 43: AppSettingMgr.m_strLanguageTranslateFrom = _T("no"); break;
	case 44: AppSettingMgr.m_strLanguageTranslateFrom = _T("fa"); break;
	case 45: AppSettingMgr.m_strLanguageTranslateFrom = _T("pl"); break;
	case 46: AppSettingMgr.m_strLanguageTranslateFrom = _T("pt"); break;
	case 47: AppSettingMgr.m_strLanguageTranslateFrom = _T("ro"); break;
	case 48: AppSettingMgr.m_strLanguageTranslateFrom = _T("ru"); break;
	case 49: AppSettingMgr.m_strLanguageTranslateFrom = _T("sr"); break;
	case 50: AppSettingMgr.m_strLanguageTranslateFrom = _T("sk"); break;
	case 51: AppSettingMgr.m_strLanguageTranslateFrom = _T("sl"); break;
	case 52: AppSettingMgr.m_strLanguageTranslateFrom = _T("es"); break;
	case 53: AppSettingMgr.m_strLanguageTranslateFrom = _T("sw"); break;
	case 54: AppSettingMgr.m_strLanguageTranslateFrom = _T("sv"); break;
	case 55: AppSettingMgr.m_strLanguageTranslateFrom = _T("ta"); break;
	case 56: AppSettingMgr.m_strLanguageTranslateFrom = _T("te"); break;
	case 57: AppSettingMgr.m_strLanguageTranslateFrom = _T("th"); break;
	case 58: AppSettingMgr.m_strLanguageTranslateFrom = _T("tr"); break;
	case 59: AppSettingMgr.m_strLanguageTranslateFrom = _T("uk"); break;
	case 60: AppSettingMgr.m_strLanguageTranslateFrom = _T("ur"); break;
	case 61: AppSettingMgr.m_strLanguageTranslateFrom = _T("vi"); break;
	case 62: AppSettingMgr.m_strLanguageTranslateFrom = _T("cy"); break;
	case 63: AppSettingMgr.m_strLanguageTranslateFrom = _T("yi"); break;
	default:
		AppSettingMgr.m_strLanguageTranslateFrom = _T("en");
		break;
	}
}

void EditorSettingDlg::FromLanguageTranslateToCombo()
{
	int iSel = m_LanguageTranslateToCombo.GetCurSel();
	switch (iSel)
	{
	case 0: AppSettingMgr.m_strLanguageTranslateTo = _T("af"); break;
	case 1: AppSettingMgr.m_strLanguageTranslateTo = _T("sq"); break;
	case 2: AppSettingMgr.m_strLanguageTranslateTo = _T("ar"); break;
	case 3: AppSettingMgr.m_strLanguageTranslateTo = _T("az"); break;
	case 4: AppSettingMgr.m_strLanguageTranslateTo = _T("eu"); break;
	case 5: AppSettingMgr.m_strLanguageTranslateTo = _T("be"); break;
	case 6: AppSettingMgr.m_strLanguageTranslateTo = _T("bn"); break;
	case 7: AppSettingMgr.m_strLanguageTranslateTo = _T("bg"); break;
	case 8: AppSettingMgr.m_strLanguageTranslateTo = _T("ca"); break;
	case 9: AppSettingMgr.m_strLanguageTranslateTo = _T("zh-CN"); break;
	case 10: AppSettingMgr.m_strLanguageTranslateTo = _T("zh-TW"); break;
	case 11: AppSettingMgr.m_strLanguageTranslateTo = _T("hr"); break;
	case 12: AppSettingMgr.m_strLanguageTranslateTo = _T("cs"); break;
	case 13: AppSettingMgr.m_strLanguageTranslateTo = _T("da"); break;
	case 14: AppSettingMgr.m_strLanguageTranslateTo = _T("nl"); break;
	case 15: AppSettingMgr.m_strLanguageTranslateTo = _T("en"); break;
	case 16: AppSettingMgr.m_strLanguageTranslateTo = _T("eo"); break;
	case 17: AppSettingMgr.m_strLanguageTranslateTo = _T("et"); break;
	case 18: AppSettingMgr.m_strLanguageTranslateTo = _T("tl"); break;
	case 19: AppSettingMgr.m_strLanguageTranslateTo = _T("fi"); break;
	case 20: AppSettingMgr.m_strLanguageTranslateTo = _T("fr"); break;
	case 21: AppSettingMgr.m_strLanguageTranslateTo = _T("gl"); break;
	case 22: AppSettingMgr.m_strLanguageTranslateTo = _T("ka"); break;
	case 23: AppSettingMgr.m_strLanguageTranslateTo = _T("de"); break;
	case 24: AppSettingMgr.m_strLanguageTranslateTo = _T("el"); break;
	case 25: AppSettingMgr.m_strLanguageTranslateTo = _T("gu"); break;
	case 26: AppSettingMgr.m_strLanguageTranslateTo = _T("ht"); break;
	case 27: AppSettingMgr.m_strLanguageTranslateTo = _T("iw"); break;
	case 28: AppSettingMgr.m_strLanguageTranslateTo = _T("hi"); break;
	case 29: AppSettingMgr.m_strLanguageTranslateTo = _T("hu"); break;
	case 30: AppSettingMgr.m_strLanguageTranslateTo = _T("is"); break;
	case 31: AppSettingMgr.m_strLanguageTranslateTo = _T("id"); break;
	case 32: AppSettingMgr.m_strLanguageTranslateTo = _T("ga"); break;
	case 33: AppSettingMgr.m_strLanguageTranslateTo = _T("it"); break;
	case 34: AppSettingMgr.m_strLanguageTranslateTo = _T("ja"); break;
	case 35: AppSettingMgr.m_strLanguageTranslateTo = _T("kn"); break;
	case 36: AppSettingMgr.m_strLanguageTranslateTo = _T("ko"); break;
	case 37: AppSettingMgr.m_strLanguageTranslateTo = _T("la"); break;
	case 38: AppSettingMgr.m_strLanguageTranslateTo = _T("lv"); break;
	case 39: AppSettingMgr.m_strLanguageTranslateTo = _T("lt"); break;
	case 40: AppSettingMgr.m_strLanguageTranslateTo = _T("mk"); break;
	case 41: AppSettingMgr.m_strLanguageTranslateTo = _T("ms"); break;
	case 42: AppSettingMgr.m_strLanguageTranslateTo = _T("mt"); break;
	case 43: AppSettingMgr.m_strLanguageTranslateTo = _T("no"); break;
	case 44: AppSettingMgr.m_strLanguageTranslateTo = _T("fa"); break;
	case 45: AppSettingMgr.m_strLanguageTranslateTo = _T("pl"); break;
	case 46: AppSettingMgr.m_strLanguageTranslateTo = _T("pt"); break;
	case 47: AppSettingMgr.m_strLanguageTranslateTo = _T("ro"); break;
	case 48: AppSettingMgr.m_strLanguageTranslateTo = _T("ru"); break;
	case 49: AppSettingMgr.m_strLanguageTranslateTo = _T("sr"); break;
	case 50: AppSettingMgr.m_strLanguageTranslateTo = _T("sk"); break;
	case 51: AppSettingMgr.m_strLanguageTranslateTo = _T("sl"); break;
	case 52: AppSettingMgr.m_strLanguageTranslateTo = _T("es"); break;
	case 53: AppSettingMgr.m_strLanguageTranslateTo = _T("sw"); break;
	case 54: AppSettingMgr.m_strLanguageTranslateTo = _T("sv"); break;
	case 55: AppSettingMgr.m_strLanguageTranslateTo = _T("ta"); break;
	case 56: AppSettingMgr.m_strLanguageTranslateTo = _T("te"); break;
	case 57: AppSettingMgr.m_strLanguageTranslateTo = _T("th"); break;
	case 58: AppSettingMgr.m_strLanguageTranslateTo = _T("tr"); break;
	case 59: AppSettingMgr.m_strLanguageTranslateTo = _T("uk"); break;
	case 60: AppSettingMgr.m_strLanguageTranslateTo = _T("ur"); break;
	case 61: AppSettingMgr.m_strLanguageTranslateTo = _T("vi"); break;
	case 62: AppSettingMgr.m_strLanguageTranslateTo = _T("cy"); break;
	case 63: AppSettingMgr.m_strLanguageTranslateTo = _T("yi"); break;
	default:
		AppSettingMgr.m_strLanguageTranslateTo = _T("vi");
		break;
	}
}


void EditorSettingDlg::InitCaretBlinkColorCombobox()
{
	m_CaretBlinkColorCombo.ResetContent();
	m_CaretBlinkColorCombo.AddString(_T("Write Color"));
	m_CaretBlinkColorCombo.AddString(_T("Orrange Color"));
	m_CaretBlinkColorCombo.AddString(_T("Green Color"));
	m_CaretBlinkColorCombo.AddString(_T("Yellow Color"));
	m_CaretBlinkColorCombo.AddString(_T("Red Color"));
	m_CaretBlinkColorCombo.AddString(_T("Black Color"));
	switch (AppSettingMgr.m_CaretBlinkColor)
	{
	case EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_WHITE:
		m_CaretBlinkColorCombo.SetCurSel(0);
		break;
	case EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_ORRANGE:
		m_CaretBlinkColorCombo.SetCurSel(1);
		break;
	case EDITOR_CARET_BLINK_COLOR::BLINK_COLORR_GREEN:
		m_CaretBlinkColorCombo.SetCurSel(2);
		break;
	case EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_YELLOW:
		m_CaretBlinkColorCombo.SetCurSel(3);
		break;
	case EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_RED:
		m_CaretBlinkColorCombo.SetCurSel(4);
		break;
	case EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_BLACK:
		m_CaretBlinkColorCombo.SetCurSel(5);
		break;
	default:
		m_CaretBlinkColorCombo.SetCurSel(0);
		break;
	}
}

void EditorSettingDlg::InitFolderMarginStyleCombobox()
{
	m_FolderMarginStyleCombo.ResetContent();
	m_FolderMarginStyleCombo.AddString(_T("Arrow Style"));
	m_FolderMarginStyleCombo.AddString(_T("Plus Minus Style"));
	m_FolderMarginStyleCombo.AddString(_T("Tree Circle Styler"));
	m_FolderMarginStyleCombo.AddString(_T("Tree Box Style"));
	switch (AppSettingMgr.m_FolderMarginStyle)
	{
	case FOLDER_MARGIN_STYPE::STYLE_ARROW:
		m_FolderMarginStyleCombo.SetCurSel(0);
		break;
	case FOLDER_MARGIN_STYPE::STYLE_PLUS_MINUS:
		m_FolderMarginStyleCombo.SetCurSel(1);
		break;
	case FOLDER_MARGIN_STYPE::STYLE_TREE_CIRCLE:
		m_FolderMarginStyleCombo.SetCurSel(2);
		break;
	case FOLDER_MARGIN_STYPE::STYLE_TREE_BOX:
		m_FolderMarginStyleCombo.SetCurSel(3);
		break;
	default:
		m_FolderMarginStyleCombo.SetCurSel(0);
		break;
	}
}

void EditorSettingDlg::InitIndicatorColorCombobox()
{
	m_IndicatorColorCombo.ResetContent();
	m_IndicatorColorCombo.AddString(_T("Yellow Color"));
	m_IndicatorColorCombo.AddString(_T("Blue Color"));
	m_IndicatorColorCombo.AddString(_T("Orange Color"));
	switch (AppSettingMgr.m_IndicatorColor)
	{
	case EDITOR_INDICATOR_COLOR::INDICATOR_YELLOW:
		m_IndicatorColorCombo.SetCurSel(0);
		break;
	case EDITOR_INDICATOR_COLOR::INDICATOR_BLUE:
		m_IndicatorColorCombo.SetCurSel(1);
		break;
	case EDITOR_INDICATOR_COLOR::INDICATOR_ORANGE:
		m_IndicatorColorCombo.SetCurSel(2);
		break;
	default:
		m_IndicatorColorCombo.SetCurSel(0);
		break;
	}
}

void EditorSettingDlg::InitIndicatorStyleCombobox()
{
	m_IndicatorStyleCombo.ResetContent();
	m_IndicatorStyleCombo.AddString(_T("Box Style"));
	m_IndicatorStyleCombo.AddString(_T("Full Box Style"));
	switch (AppSettingMgr.m_IndicatorStyle)
	{
	case EDITOR_INDICATOR_STYLE::BOX:
		m_IndicatorStyleCombo.SetCurSel(0);
		break;
	case EDITOR_INDICATOR_STYLE::FULL_BOX:
		m_IndicatorStyleCombo.SetCurSel(1);
		break;
	default:
		m_IndicatorStyleCombo.SetCurSel(0);
		break;
	}
}


void EditorSettingDlg::FromCaretBlinkColorCombobox()
{
	int iSel = m_CaretBlinkColorCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_WHITE;
		break;
	case 1:
		AppSettingMgr.m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_ORRANGE;
		break;
	case 2:
		AppSettingMgr.m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLORR_GREEN;
		break;
	case 3:
		AppSettingMgr.m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_YELLOW;
		break;
	case 4:
		AppSettingMgr.m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_RED;
		break;
	case 5:
		AppSettingMgr.m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_BLACK;
		break;
	default:
		AppSettingMgr.m_CaretBlinkColor = EDITOR_CARET_BLINK_COLOR::BLINK_COLOR_WHITE;
		break;
	}
}

void EditorSettingDlg::FromFolderMarginStyleCombobox()
{
	int iSel = m_FolderMarginStyleCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_ARROW;
		break;
	case 1:
		AppSettingMgr.m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_PLUS_MINUS;
		break;
	case 2:
		AppSettingMgr.m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_TREE_CIRCLE;
		break;
	case 3:
		AppSettingMgr.m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_TREE_BOX;
		break;
	default:
		AppSettingMgr.m_FolderMarginStyle = FOLDER_MARGIN_STYPE::STYLE_ARROW;
		break;
	}
}

void EditorSettingDlg::FromIndicatorColorCombobox()
{
	int iSel = m_IndicatorColorCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_IndicatorColor = EDITOR_INDICATOR_COLOR::INDICATOR_YELLOW;
		break;
	case 1:
		AppSettingMgr.m_IndicatorColor = EDITOR_INDICATOR_COLOR::INDICATOR_BLUE;
		break;
	case 2:
		AppSettingMgr.m_IndicatorColor = EDITOR_INDICATOR_COLOR::INDICATOR_ORANGE;
		break;
	default:
		AppSettingMgr.m_IndicatorColor = EDITOR_INDICATOR_COLOR::INDICATOR_YELLOW;
		break;
	}
}

void EditorSettingDlg::FromIndicatorStyleCombobox()
{
	int iSel = m_IndicatorStyleCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_IndicatorStyle = EDITOR_INDICATOR_STYLE::BOX;
		break;
	case 1:
		AppSettingMgr.m_IndicatorStyle = EDITOR_INDICATOR_STYLE::FULL_BOX;
		break;
	default:
		AppSettingMgr.m_IndicatorStyle = EDITOR_INDICATOR_STYLE::BOX;
		break;
	}
}

void EditorSettingDlg::FromDefaultEOLNewFileCombobox()
{
	int iSel = m_DefaultEOLNewFileCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_DefaultFileEOL = SC_EOL_CRLF;
		break;
	case 1:
		AppSettingMgr.m_DefaultFileEOL = SC_EOL_CR;
		break;
	case 2:
		AppSettingMgr.m_DefaultFileEOL = SC_EOL_LF;
		break;
	default:
		AppSettingMgr.m_DefaultFileEOL = SC_EOL_CRLF;
		break;
	}
}

void EditorSettingDlg::FromIndentationTypeCombobox()
{
	int iSel = m_IndentationTypeCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_editorIndentationType = TabSpace::Tabs;
		break;
	case 1:
		AppSettingMgr.m_editorIndentationType = TabSpace::Spaces;
		break;
	default:
		AppSettingMgr.m_editorIndentationType = TabSpace::Tabs;
		break;
	}
}

void EditorSettingDlg::InitRenderIndicatorActionCombobox()
{
	m_RenderIndicatorActionCombo.ResetContent();
	m_RenderIndicatorActionCombo.AddString(_T("Single Click Event"));
	m_RenderIndicatorActionCombo.AddString(_T("Double Click Event"));
	switch (AppSettingMgr.m_RenderIndicatorAction)
	{
	case RENDER_INDICATOR_ACTION::SINGLE_CLICK_ACTION:
		m_RenderIndicatorActionCombo.SetCurSel(0);
		break;
	case RENDER_INDICATOR_ACTION::DOUBLE_CLICK_ACTION:
		m_RenderIndicatorActionCombo.SetCurSel(1);
		break;
	default:
		m_RenderIndicatorActionCombo.SetCurSel(0);
		break;
	}
}

void EditorSettingDlg::InitDefaultEOLNewFileCombobox()
{
	m_DefaultEOLNewFileCombo.ResetContent();
	m_DefaultEOLNewFileCombo.AddString(_T("Windows (CRLF)"));
	m_DefaultEOLNewFileCombo.AddString(_T("MacOS (CR)"));
	m_DefaultEOLNewFileCombo.AddString(_T("Linux (LF)"));
	switch (AppSettingMgr.m_DefaultFileEOL)
	{
	case SC_EOL_CRLF:
		m_DefaultEOLNewFileCombo.SetCurSel(0);
		break;
	case SC_EOL_CR:
		m_DefaultEOLNewFileCombo.SetCurSel(1);
		break;
	case SC_EOL_LF:
		m_DefaultEOLNewFileCombo.SetCurSel(2);
		break;
	default:
		m_DefaultEOLNewFileCombo.SetCurSel(0);
		break;
	}
}

void EditorSettingDlg::InitIndentationTypeCombobox()
{
	m_IndentationTypeCombo.ResetContent();
	m_IndentationTypeCombo.AddString(_T("Tab"));
	m_IndentationTypeCombo.AddString(_T("Spaces"));
	switch (AppSettingMgr.m_editorIndentationType)
	{
	case TabSpace::Tabs:
		m_IndentationTypeCombo.SetCurSel(0);
		break;
	case TabSpace::Spaces:
		m_IndentationTypeCombo.SetCurSel(1);
		break;
	default:
		m_IndentationTypeCombo.SetCurSel(0);
		break;
	}
}

void EditorSettingDlg::FromRenderIndicatorActionCombobox()
{
	int iSel = m_RenderIndicatorActionCombo.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_RenderIndicatorAction = RENDER_INDICATOR_ACTION::SINGLE_CLICK_ACTION;
		break;
	case 1:
		AppSettingMgr.m_RenderIndicatorAction = RENDER_INDICATOR_ACTION::DOUBLE_CLICK_ACTION;
		break;
	default:
		AppSettingMgr.m_RenderIndicatorAction = RENDER_INDICATOR_ACTION::SINGLE_CLICK_ACTION;
		break;
	}
}

BEGIN_MESSAGE_MAP(EditorSettingDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_EDITOR_FONT_NAME_BUTTON, &EditorSettingDlg::OnBnClickedEditorFontNameButton)
	ON_BN_CLICKED(IDC_CHECK_USE_USER_CUSTOM_TAB_SETTINGS, &EditorSettingDlg::OnBnClickedCheckUseUserCustomTabSettings)
END_MESSAGE_MAP()

// for scrolling //////////////////////////////////////////////////////////////

void EditorSettingDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pScrollHelper->OnHScroll(nSBCode, nPos, pScrollBar);
}

void EditorSettingDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pScrollHelper->OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL EditorSettingDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	BOOL wasScrolled = m_pScrollHelper->OnMouseWheel(nFlags, zDelta, pt);

	return wasScrolled;
}

void EditorSettingDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_pScrollHelper->OnSize(nType, cx, cy);
}

void EditorSettingDlg::OnBnClickedEditorFontNameButton()
{
	LOGFONTW lplfInitial;
	_tcsncpy_s(lplfInitial.lfFaceName, LF_FACESIZE, m_lfFaceName, m_lfFaceName.GetLength());
	CWindowDC dc(NULL); // screen DC
	int nDPI = dc.GetDeviceCaps(LOGPIXELSY);
	lplfInitial.lfHeight =  static_cast<LONG>(-(m_iPointSize * nDPI / 72.0 + 0.5));
	lplfInitial.lfWeight = m_isBold;
	lplfInitial.lfItalic = m_isItalic;
	lplfInitial.lfUnderline = m_isUnderline;
	CFontDialog dlg(&lplfInitial, CF_SCREENFONTS);
	dlg.m_cf.iPointSize = m_iPointSize * 10;
	dlg.m_cf.rgbColors = m_color;
	if (dlg.DoModal() == IDOK)
	{
		m_lfFaceName = dlg.GetFaceName();
		m_iPointSize = dlg.m_cf.iPointSize / 10;
		m_isBold = dlg.IsBold();
		m_isItalic = dlg.IsItalic();
		m_isUnderline = dlg.IsUnderline();
		m_color = dlg.GetColor();
	}
}

void EditorSettingDlg::OnBnClickedCheckUseUserCustomTabSettings()
{
	CButton* pCheckbox = (CButton*)GetDlgItem(IDC_CHECK_USE_USER_CUSTOM_TAB_SETTINGS);
	if (!pCheckbox->GetCheck())
	{
		GetDlgItem(IDC_COMBO_INDENTATION_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_INDENTATION_WIDTH)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_INDENTATION_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_INDENTATION_WIDTH)->EnableWindow(TRUE);
	}
}
