/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Editor.h"
#include "LexerParser.h"
#include "EditorDatabase.h"
#include "AppSettings.h"
#include "VinaTextApp.h"

#include "StringHelper.h"
#include "Debugger.h"
#include "SmartHandle.h"
#include "MultiThreadWorker.h"

#include "Hpsutils.h"
#include "GuiUtils.h"
#include "PathUtil.h"
#include "OSUtil.h"
#include "AppUtil.h"
#include "UnicodeUtils.h"

#include "TextFile.h"

#include "EditorLexerDark.h"
#include "EditorLexerLight.h"
#include "EditorColorDark.h"
#include "EditorColorLight.h"

CEditorCtrl::CEditorCtrl()
{
	m_wideBuf = std::make_unique<wchar_t[]>(m_wideBufSize);
	m_charBuf = std::make_unique<char[]>(m_charBufSize);
}

CEditorCtrl::~CEditorCtrl()
{
	if (PathFileExists(m_strFilePath))
	{
		VinaTextDebugger.RemoveBreakPointDataInFile(m_strFilePath);
	}
	m_CreateLexerFunc = NULL;
	m_GetLexerNameFromID = NULL;
}

void CEditorCtrl::ReleaseDocument()
{
	DoCommand(SCI_SETDOCPOINTER, 0, 0);
	if (m_DocumentID > 0)
	{
		DoCommand(SCI_RELEASEDOCUMENT, 0, m_DocumentID);
	}
}

BOOL CEditorCtrl::Create(const CString& strWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	if (!CWnd::CreateEx(WS_EX_CLIENTEDGE | WS_EX_COMPOSITED, STR_SCINTILLAWND, strWindowName, dwStyle, rect, pParentWnd, (UINT)nID))
	{
		return FALSE;
	}
	// load dll lexers
	CVinaTextApp* pApp = AppUtils::GetVinaTextApp();
	if (pApp)
	{
		FARPROC pFunCreateLexer = GetProcAddress(pApp->m_hDllLexer, LEXILLA_CREATELEXER);
		m_CreateLexerFunc = (Lexilla::CreateLexerFn)(pFunCreateLexer);
		if (!m_CreateLexerFunc)
		{
			ASSERT(m_CreateLexerFunc); return FALSE;
		}
#if 0
		FARPROC pFunGetLexerNameFromID = GetProcAddress(pApp->m_hDllLexer, LEXILLA_LEXERNAMEFROMID);
		m_GetLexerNameFromID = (Lexilla::LexerNameFromIDFn)(pFunGetLexerNameFromID);
#endif
	}
	// retrieve a pointer to the message handling function of the Scintilla Edit Control and call it directly to execute a command
	m_DirectFunc = (DirectFunc)::SendMessage(this->m_hWnd, SCI_GETDIRECTFUNCTION, 0, 0);
	m_pDirectPtr = (DirectPtr)::SendMessage(this->m_hWnd, SCI_GETDIRECTPOINTER, 0, 0);
	if (!m_DirectFunc)
	{
		ASSERT(m_DirectFunc); return FALSE;
	}
	if (!m_pDirectPtr)
	{
		ASSERT(m_pDirectPtr); return FALSE;
	}
	return TRUE;
}

void CEditorCtrl::InitilizeSetting(CLanguageDatabase* pDatabase)
{
	DoCommand(SCI_SETIMEINTERACTION, SC_IME_WINDOWED);

	// Preset theme colors
	if (IS_LIGHT_THEME)
	{
		m_AppThemeColorSet._lineNumberColor = EditorColorLight::linenumber;
		m_AppThemeColorSet._selectionTextColor = EditorColorLight::black;
		m_AppThemeColorSet._editorTextColor = EditorColorLight::editorTextColor;
		m_AppThemeColorSet._editorMarginBarColor = EditorColorLight::editorMarginBarColor;
		m_AppThemeColorSet._editorFolderBackColor = EditorColorLight::editorFolderBackColor;
		m_AppThemeColorSet._editorFolderForeColor = EditorColorLight::editorFolderForeColor;
		m_AppThemeColorSet._editorCaretColor = EditorColorLight::editorCaretColor;
		m_AppThemeColorSet._editorIndicatorColor = EditorColorLight::editorIndicatorColor;
		m_AppThemeColorSet._editorSpellCheckColor = EditorColorLight::editorSpellCheckColor;
		m_AppThemeColorSet._editorTagMatchColor = EditorColorLight::editorTagMatchColor;
	}
	else
	{
		m_AppThemeColorSet._lineNumberColor = EditorColorDark::linenumber;
		m_AppThemeColorSet._selectionTextColor = EditorColorDark::white;
		m_AppThemeColorSet._editorTextColor = EditorColorDark::editorTextColor;
		m_AppThemeColorSet._editorMarginBarColor = EditorColorDark::editorMarginBarColor;
		m_AppThemeColorSet._editorFolderBackColor = EditorColorDark::editorFolderBackColor;
		m_AppThemeColorSet._editorFolderForeColor = EditorColorDark::editorFolderForeColor;
		m_AppThemeColorSet._editorCaretColor = EditorColorDark::editorCaretColor;
		m_AppThemeColorSet._editorIndicatorColor = EditorColorDark::editorIndicatorColor;
		m_AppThemeColorSet._editorSpellCheckColor = EditorColorDark::editorSpellCheckColor;
		m_AppThemeColorSet._editorTagMatchColor = EditorColorDark::editorTagMatchColor;
	}

	// Editor font settings
	SetColorForStyle(STYLE_DEFAULT,
		m_AppThemeColorSet._editorTextColor,
		AppSettingMgr.m_AppThemeColor,
		AppSettingMgr.m_EditorFontSetting._nEditorTextFontSize,
		AppUtils::CStringToStd(AppSettingMgr.m_EditorFontSetting._font).c_str());

	DoCommand(SCI_STYLESETBOLD, STYLE_DEFAULT, AppSettingMgr.m_EditorFontSetting._bEnableBoldFont);
	DoCommand(SCI_STYLESETITALIC, STYLE_DEFAULT, AppSettingMgr.m_EditorFontSetting._bEnableItalicFont);
	DoCommand(SCI_STYLESETUNDERLINE, STYLE_DEFAULT, AppSettingMgr.m_EditorFontSetting._bEnableUnderlineFont);

	// This message sets all styles to have the same attributes as STYLE_DEFAULT.
	// If you are setting up Scintilla for syntax colouring, it is likely that the
	// lexical styles you set will be very similar.
	DoCommand(SCI_STYLECLEARALL);

	// init lexer editor
	if (m_strLexerName.IsEmpty()) {
		m_strLexerName = LEXER_PLAIN_TEXT;
	}
	AppSettingMgr.m_AppThemeColor == THEME_BACKGROUND_COLOR_LIGHT ?
		EditorLexerLight::LoadLexer(pDatabase, this, m_strLexerName):
		EditorLexerDark::LoadLexer(pDatabase, this, m_strLexerName);

	SetTabSettings(m_tabSpace);

	SetDisplayLinenumbers(TRUE);

	SetColorForStyle(STYLE_LINENUMBER,
		m_AppThemeColorSet._lineNumberColor,
		m_AppThemeColorSet._editorMarginBarColor,
		AppSettingMgr.m_EditorFontSetting._nEditorLineNumberFontSize,
		AppUtils::CStringToStd(AppSettingMgr.m_EditorFontSetting._font).c_str());

	// folding
	DoCommand(SCI_SETPROPERTY, (WPARAM)"fold", reinterpret_cast<LPARAM>("1"));
	DoCommand(SCI_SETPROPERTY, (WPARAM)"fold.compact", reinterpret_cast<LPARAM>("0"));
	DoCommand(SCI_SETPROPERTY, (WPARAM)"fold.html", reinterpret_cast<LPARAM>("1"));
	DoCommand(SCI_SETPROPERTY, (WPARAM)"fold.html.preprocessor", reinterpret_cast<LPARAM>("1"));
	DoCommand(SCI_SETPROPERTY, (WPARAM)"fold.comment", reinterpret_cast<LPARAM>("1"));
	DoCommand(SCI_SETPROPERTY, (WPARAM)"fold.at.else", reinterpret_cast<LPARAM>("1"));
	DoCommand(SCI_SETPROPERTY, (WPARAM)"fold.flags", reinterpret_cast<LPARAM>("1"));
	DoCommand(SCI_SETPROPERTY, (WPARAM)"fold.preprocessor", reinterpret_cast<LPARAM>("1"));
	DoCommand(SCI_SETPROPERTY, (WPARAM)"styling.within.preprocessor", reinterpret_cast<LPARAM>("1"));
	DoCommand(SCI_SETPROPERTY, (WPARAM)"asp.default.language", reinterpret_cast<LPARAM>("1"));
	if (AppSettingMgr.m_bDrawFoldingLineUnderLineStyle)
	{
		DoCommand(SCI_SETFOLDFLAGS, SC_FOLDFLAG_LINEAFTER_CONTRACTED, 0);
	}
	DoCommand(SCI_FOLDDISPLAYTEXTSETSTYLE, SC_FOLDDISPLAYTEXT_BOXED, 0);

	if (m_strLexerName == _T("cpp") || m_strLexerName == _T("c") || m_strLexerName == _T("cs")
		|| m_strLexerName == _T("java") || m_strLexerName == _T("javascript") || m_strLexerName == _T("typescript")
		|| m_strLexerName == _T("phpscript") || m_strLexerName == _T("rust") || m_strLexerName == _T("kix")
		|| m_strLexerName == _T("markdown") || m_strLexerName == _T("css") || m_strLexerName == _T("bash"))
	{
		DoCommand(SCI_SETDEFAULTFOLDDISPLAYTEXT, 0, reinterpret_cast<LPARAM>(FOLDED_MARKER_CPP));
	}
	else if (m_strLexerName == _T("hypertext") || m_strLexerName == _T("xml"))
	{
		DoCommand(SCI_SETDEFAULTFOLDDISPLAYTEXT, 0, reinterpret_cast<LPARAM>(FOLDED_MARKER_HTML));
	}
	else
	{
		DoCommand(SCI_SETDEFAULTFOLDDISPLAYTEXT, 0, reinterpret_cast<LPARAM>(FOLDED_MARKER_TEXT));
	}

	if (m_strLexerName == _T("python"))
	{
		DoCommand(SCI_SETINDENTATIONGUIDES, SC_IV_LOOKFORWARD, 0);
	}
	else
	{
		DoCommand(SCI_SETINDENTATIONGUIDES, SC_IV_LOOKBOTH, 0);
	}

	//There are 32 markers available, and numbers 0 to 24 have no pre - defined use.The numbers 25 to 31 are used for folding, but if you don't need that, you could use those numbers as well.
	//The first step is to choose a number for each of the markers you want to set up : let's say 4 for arrows, and 5 for circles (probably some constants should be defined for these).
	//The margin mask is a 32 - bit value.To set it, you need to flip the bit that corresponds with each of the marker numbers that should be enabled for that margin :
	//There are 32 markers available, and numbers 0 to 24 have no pre - defined use.The numbers 25 to 31 are used for folding
	//Then you need to define the markers themselves
	//So we have 3 types of margin are line number, breakpoint, foldding from left to right 2, 1 ,0
	DoCommand(SCI_SETMARGINS, VINATEXT_MAXIMUM_MARGIN);
	DoCommand(SCI_SETMARGINTYPEN, SC_SETMARGINTYPE_LINENUM, SC_MARGIN_NUMBER);
	DoCommand(SCI_SETMARGINTYPEN, SC_SETMARGINTYPE_MAKER, SC_MARGIN_SYMBOL);
	DoCommand(SCI_SETMARGINTYPEN, SC_SETMARGINTYPE_FOLDING, SC_MARGIN_SYMBOL);
	DoCommand(SCI_SETMARGINMASKN, SC_SETMARGINTYPE_LINENUM, ~SC_MASK_FOLDERS);
	DoCommand(SCI_SETMARGINMASKN, SC_SETMARGINTYPE_MAKER, ~SC_MASK_FOLDERS);
	DoCommand(SCI_SETMARGINMASKN, SC_SETMARGINTYPE_MAKER, // multiple maker in one margin number 2
			(1 << SC_MARKER_ENABLE_BREAKPOINT)
			| (1 << SC_MARKER_DISABLE_BREAKPOINT)
			| (1 << SC_MARKER_INSTRUCTION_POINTER)
			| (1 << SC_MARKER_BOOKMARK));
	DoCommand(SCI_SETMARGINMASKN, SC_SETMARGINTYPE_FOLDING, 1 << SC_MARKER_FOLDING);
	DoCommand(SCI_SETMARGINMASKN, SC_SETMARGINTYPE_LINENUM, 1 << SC_MARKER_LINE_NUMBER);
	DoCommand(SCI_SETMARGINMASKN, SC_SETMARGINTYPE_FOLDING, SC_MASK_FOLDERS);

	//Register Enable breakpoint maker
	DoCommand(SCI_MARKERDEFINE, SC_MARKER_ENABLE_BREAKPOINT, SC_MARK_CIRCLE);
	DoCommand(SCI_MARKERSETFORE, SC_MARKER_ENABLE_BREAKPOINT, RGB(255, 255, 255));
	DoCommand(SCI_MARKERSETBACK, SC_MARKER_ENABLE_BREAKPOINT, RGB(255, 0, 0));

	//Register Disable breakpoint maker
	DoCommand(SCI_MARKERDEFINE, SC_MARKER_DISABLE_BREAKPOINT, SC_MARK_CIRCLE);
	DoCommand(SCI_MARKERSETFORE, SC_MARKER_DISABLE_BREAKPOINT, RGB(255, 0, 0));

	//Register Debug Pointer maker
	DoCommand(SCI_MARKERDEFINE, SC_MARKER_INSTRUCTION_POINTER, SC_MARK_SHORTARROW);
	DoCommand(SCI_MARKERSETFORE, SC_MARKER_INSTRUCTION_POINTER, RGB(0, 0, 0));
	DoCommand(SCI_MARKERSETBACK, SC_MARKER_INSTRUCTION_POINTER, RGB(255, 255, 0));

	//Register Enable bookmark maker
	DoCommand(SCI_MARKERDEFINE, SC_MARKER_BOOKMARK, SC_MARK_BOOKMARK);
	DoCommand(SCI_MARKERSETFORE, SC_MARKER_BOOKMARK, RGB(255, 0, 0));
	DoCommand(SCI_MARKERSETBACK, SC_MARKER_BOOKMARK, RGB(255, 255, 255));

	DoCommand(SCI_SETMARGINSENSITIVEN, SC_SETMARGINTYPE_FOLDING, TRUE);
	DoCommand(SCI_SETMARGINSENSITIVEN, SC_SETMARGINTYPE_MAKER, TRUE);
	if (AppSettingMgr.m_bUseFolderMarginClassic)
	{
		DoCommand(SCI_SETFOLDMARGINCOLOUR, 1, RGB(0, 0, 0));
		DoCommand(SCI_SETFOLDMARGINHICOLOUR, 1, RGB(96, 96, 96));
	}
	else
	{
		DoCommand(SCI_SETFOLDMARGINCOLOUR, 1, m_AppThemeColorSet._editorMarginBarColor);
		DoCommand(SCI_SETFOLDMARGINHICOLOUR, 1, m_AppThemeColorSet._editorMarginBarColor);
	}

	// folder style
	if (AppSettingMgr.m_FolderMarginStyle == FOLDER_MARGIN_STYPE::STYLE_ARROW)
	{
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPEN, SC_MARK_ARROWDOWN);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDER, SC_MARK_ARROW);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY);
	}
	else if (AppSettingMgr.m_FolderMarginStyle == FOLDER_MARGIN_STYPE::STYLE_PLUS_MINUS)
	{
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDER, SC_MARK_PLUS);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY);
	}
	else if (AppSettingMgr.m_FolderMarginStyle == FOLDER_MARGIN_STYPE::STYLE_TREE_CIRCLE)
	{
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPEN, SC_MARK_CIRCLEMINUS);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDER, SC_MARK_CIRCLEPLUS);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERSUB, SC_MARK_VLINE);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERTAIL, SC_MARK_LCORNERCURVE);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEREND, SC_MARK_CIRCLEPLUSCONNECTED);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPENMID, SC_MARK_CIRCLEMINUSCONNECTED);
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_TCORNERCURVE);
	}
	else if (AppSettingMgr.m_FolderMarginStyle == FOLDER_MARGIN_STYPE::STYLE_TREE_BOX)
	{
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPEN, SC_MARK_BOXMINUS);
		DoCommand(SCI_MARKERSETFORE, SC_MARKNUM_FOLDEROPEN, RGB(255, 255, 255));
		DoCommand(SCI_MARKERSETBACK, SC_MARKNUM_FOLDEROPEN, RGB(128, 128, 128));
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDER, SC_MARK_BOXPLUS);
		DoCommand(SCI_MARKERSETFORE, SC_MARKNUM_FOLDER, RGB(255, 255, 255));
		DoCommand(SCI_MARKERSETBACK, SC_MARKNUM_FOLDER, RGB(128, 128, 128));
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERSUB, SC_MARK_VLINE);
		DoCommand(SCI_MARKERSETFORE, SC_MARKNUM_FOLDERSUB, RGB(255, 255, 255));
		DoCommand(SCI_MARKERSETBACK, SC_MARKNUM_FOLDERSUB, RGB(128, 128, 128));
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERTAIL, SC_MARK_LCORNER);
		DoCommand(SCI_MARKERSETFORE, SC_MARKNUM_FOLDERTAIL, RGB(255, 255, 255));
		DoCommand(SCI_MARKERSETBACK, SC_MARKNUM_FOLDERTAIL, RGB(0, 0, 0));
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEREND, SC_MARK_BOXPLUSCONNECTED);
		DoCommand(SCI_MARKERSETFORE, SC_MARKNUM_FOLDEREND, RGB(255, 255, 255));
		DoCommand(SCI_MARKERSETBACK, SC_MARKNUM_FOLDEREND, RGB(0, 0, 0));
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPENMID, SC_MARK_BOXMINUSCONNECTED);
		DoCommand(SCI_MARKERSETFORE, SC_MARKNUM_FOLDEROPENMID, RGB(255, 255, 255));
		DoCommand(SCI_MARKERSETBACK, SC_MARKNUM_FOLDEROPENMID, RGB(0, 0, 0));
		DoCommand(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_TCORNER);
		DoCommand(SCI_MARKERSETFORE, SC_MARKNUM_FOLDERMIDTAIL, RGB(255, 255, 255));
		DoCommand(SCI_MARKERSETBACK, SC_MARKNUM_FOLDERMIDTAIL, RGB(0, 0, 0));
	}
	DoCommand(SCI_MARKERSETFORE, SC_MARKNUM_FOLDEROPEN, m_AppThemeColorSet._editorFolderForeColor);
	DoCommand(SCI_MARKERSETBACK, SC_MARKNUM_FOLDEROPEN, m_AppThemeColorSet._editorFolderBackColor);
	DoCommand(SCI_MARKERSETFORE, SC_MARKNUM_FOLDER, m_AppThemeColorSet._editorFolderForeColor);
	DoCommand(SCI_MARKERSETBACK, SC_MARKNUM_FOLDER, m_AppThemeColorSet._editorFolderBackColor);
	DoCommand(SCI_MARKERSETFORE, SC_MARKNUM_FOLDERSUB, m_AppThemeColorSet._editorFolderForeColor);
	DoCommand(SCI_MARKERSETBACK, SC_MARKNUM_FOLDERSUB, m_AppThemeColorSet._editorFolderBackColor);
	DoCommand(SCI_MARKERSETFORE, SC_MARKNUM_FOLDERTAIL, m_AppThemeColorSet._editorFolderForeColor);
	DoCommand(SCI_MARKERSETBACK, SC_MARKNUM_FOLDERTAIL, m_AppThemeColorSet._editorFolderBackColor);
	DoCommand(SCI_MARKERSETFORE, SC_MARKNUM_FOLDEREND, m_AppThemeColorSet._editorFolderForeColor);
	DoCommand(SCI_MARKERSETBACK, SC_MARKNUM_FOLDEREND, m_AppThemeColorSet._editorFolderBackColor);
	DoCommand(SCI_MARKERSETFORE, SC_MARKNUM_FOLDEROPENMID, m_AppThemeColorSet._editorFolderForeColor);
	DoCommand(SCI_MARKERSETBACK, SC_MARKNUM_FOLDEROPENMID, m_AppThemeColorSet._editorFolderBackColor);
	DoCommand(SCI_MARKERSETFORE, SC_MARKNUM_FOLDERMIDTAIL, m_AppThemeColorSet._editorFolderForeColor);
	DoCommand(SCI_MARKERSETBACK, SC_MARKNUM_FOLDERMIDTAIL, m_AppThemeColorSet._editorFolderBackColor);

	if (AppSettingMgr.m_bEnableHightLightFolder)
	{
		DoCommand(SCI_MARKERENABLEHIGHLIGHT, 1);
	}
	else
	{
		DoCommand(SCI_MARKERENABLEHIGHLIGHT, 0);
	}

	DoCommand(SCI_MARKERDEFINE, 1, SC_MARK_BOOKMARK);

	SetDisplayLinenumbers(TRUE);
	SetDisplaySelection(TRUE);
	m_strLexerName == LEXER_PLAIN_TEXT ? SetDisplayFolding(FALSE) : SetDisplayFolding(TRUE);

	// change cursor when hover margin bar
	DoCommand(SCI_SETMARGINCURSORN, SC_SETMARGINTYPE_LINENUM, SC_CURSOR_RIGHT_HAND);
	DoCommand(SCI_SETMARGINCURSORN, SC_SETMARGINTYPE_MAKER, SC_CURSOR_RIGHT_HAND);
	DoCommand(SCI_SETMARGINCURSORN, SC_SETMARGINTYPE_FOLDING, SC_CURSOR_RIGHT_HAND);

	// auto complete options
	if (AppSettingMgr.m_bAutoCompleteIgnoreCase)
	{
		DoCommand(SCI_AUTOCSETIGNORECASE, 1);
	}
	DoCommand(SCI_AUTOCSETSEPARATOR, WORD_AUTOCSETSEPARATOR);
	DoCommand(SCI_AUTOCSETTYPESEPARATOR, IMAGE_AUTOCSETSEPARATOR);
	DoCommand(SCI_AUTOCSETMAXWIDTH, 100);

	// set icon for auto complete list box
	int iconWidth = GetSystemMetrics(SM_CXSMICON);
	int iconHeight = GetSystemMetrics(SM_CYSMICON);
	DoCommand(SCI_RGBAIMAGESETWIDTH, iconWidth);
	DoCommand(SCI_RGBAIMAGESETHEIGHT, iconHeight);
	HICON hIcon = GuiUtils::LoadIconWithSize(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_AUTO_COMPLETE), iconWidth, iconHeight);
	std::unique_ptr<UINT[]> pImageBytes = GuiUtils::HIconToImageByte(hIcon);
	DoCommand(SCI_REGISTERRGBAIMAGE, 0, reinterpret_cast<sptr_t>(pImageBytes.get()));

	// ensure that all of the lines currently displayed can be completely scrolled
	DoCommand(SCI_SETSCROLLWIDTHTRACKING, 1);
	// Now the horizontal scroll bars should only appear if anydisplayed lines exceed the width of the window
	DoCommand(SCI_SETSCROLLWIDTH, 1);
	// Setting this to 0 allows scrolling one page below the last line.
	DoCommand(SCI_SETENDATLASTLINE, 0);
	
	if (!m_bEditorInitiated)
	{
		DoCommand(SCI_SETWRAPMODE, SC_WRAP_NONE);
	}
	DoCommand(SCI_SETWRAPVISUALFLAGS, SC_WRAPVISUALFLAG_END);

	DoCommand(SCI_SETCARETFORE, m_AppThemeColorSet._editorCaretColor);
	DoCommand(SCI_SETADDITIONALCARETFORE, m_AppThemeColorSet._editorCaretColor);

	if (AppSettingMgr.m_bDrawCaretLineFrame)
	{
		DoCommand(SCI_SETCARETLINEFRAME, 1);
	}
	else
	{
		DoCommand(SCI_SETCARETLINEFRAME, 0);
	}
	DoCommand(SCI_SETCARETLINEVISIBLE, 1);
	DoCommand(SCI_SETCARETLINEVISIBLEALWAYS, 1);
	DoCommand(SCI_SETCARETLINEBACK, m_AppThemeColorSet._editorTextColor);
	DoCommand(SCI_SETCARETLINEBACKALPHA, 100);
	DoCommand(SCI_SETCARETWIDTH, 2);

	if (AppSettingMgr.m_bEnableUrlHighlight)
	{
		RenderHotSpotForUrlLinks();
	}

	// menu pop up
	DoCommand(SCI_USEPOPUP, 0, 0);
	// long line checker
	DoCommand(SCI_SETEDGECOLUMN, AppSettingMgr.m_nLongLineMaximum);
	// selection
	SetSelectionTextColor(m_AppThemeColorSet._selectionTextColor, 60);

	if (AppSettingMgr.m_bEnableCaretBlink)
	{
		DoCommand(SCI_SETCARETPERIOD, 500, 0);
		DoCommand(SCI_SETADDITIONALCARETSBLINK, TRUE);
	}
	else
	{
		DoCommand(SCI_SETCARETPERIOD, 0, 0);
		DoCommand(SCI_SETADDITIONALCARETSBLINK, FALSE);
	}

	EnableMultiCursorMode(AppSettingMgr.m_bEnableMultipleCursor);

	// set dwell timer, change to 0 if we want to use feature showhide folding bar
	DoCommand(SCI_SETMOUSEDWELLTIME, SC_TIME_FOREVER);

	// disable SCEN_CHANGE to avoid averhead
	DoCommand(SCI_SETCOMMANDEVENTS, 0);

	// set space line ascent
	DoCommand(SCI_SETEXTRAASCENT, AppSettingMgr.m_nLineSpaceAbove);
	DoCommand(SCI_SETEXTRADESCENT, AppSettingMgr.m_nLineSpaceBelow);

	DoCommand(SCI_SETMOUSEWHEELCAPTURES, 0);

	// set indicator styles (foreground and alpha maybe overridden by style settings)
	DoCommand(SCI_INDICSETSTYLE, STYLE_BRACELIGHT, INDIC_FULLBOX);
	DoCommand(SCI_STYLESETFORE, STYLE_BRACELIGHT, BasicColors::red);
	DoCommand(SCI_INDICSETALPHA, STYLE_BRACELIGHT, 120);
	DoCommand(SCI_INDICSETOUTLINEALPHA, STYLE_BRACELIGHT, 120);
	DoCommand(SCI_STYLESETBOLD, STYLE_BRACELIGHT, 1);

	DoCommand(SCI_INDICSETSTYLE, STYLE_BRACEBAD, INDIC_FULLBOX);
	DoCommand(SCI_STYLESETFORE, STYLE_BRACEBAD, BasicColors::blue);
	DoCommand(SCI_INDICSETALPHA, STYLE_BRACEBAD, 120);
	DoCommand(SCI_INDICSETOUTLINEALPHA, STYLE_BRACEBAD, 120);
	DoCommand(SCI_STYLESETBOLD, STYLE_BRACEBAD, 1);

	//DoCommand(SCI_INDICSETSTYLE, INDIC_BRACEMATCH, INDIC_ROUNDBOX);
	//DoCommand(SCI_INDICSETALPHA, INDIC_BRACEMATCH, 30);
	//DoCommand(SCI_INDICSETOUTLINEALPHA, INDIC_BRACEMATCH, 0);
	//DoCommand(SCI_INDICSETUNDER, INDIC_BRACEMATCH, true);
	//DoCommand(SCI_INDICSETFORE, INDIC_BRACEMATCH, RGB(0, 150, 0));

	DoCommand(SCI_INDICSETFORE, INDIC_TAGMATCH, m_AppThemeColorSet._editorTagMatchColor);
	DoCommand(SCI_INDICSETFORE, INDIC_TAGATTR, m_AppThemeColorSet._editorTagMatchColor);
	DoCommand(SCI_INDICSETSTYLE, INDIC_TAGMATCH, INDIC_DASH);
	DoCommand(SCI_INDICSETSTYLE, INDIC_TAGATTR, INDIC_DASH);
	DoCommand(SCI_INDICSETALPHA, INDIC_TAGMATCH, 50);
	DoCommand(SCI_INDICSETALPHA, INDIC_TAGATTR, 50);
	DoCommand(SCI_INDICSETUNDER, INDIC_TAGMATCH, 1);
	DoCommand(SCI_INDICSETUNDER, INDIC_TAGATTR, 1);

	DoCommand(SCI_INDICSETSTYLE, INDIC_SPELL_CHECKER, INDIC_SQUIGGLELOW);
	DoCommand(SCI_INDICSETFORE, INDIC_SPELL_CHECKER, m_AppThemeColorSet._editorSpellCheckColor);
	DoCommand(SCI_INDICSETUNDER, INDIC_SPELL_CHECKER, 1);
}

void CEditorCtrl::ResetUndoSavePoint()
{
	DoCommand(SCI_EMPTYUNDOBUFFER);
	DoCommand(SCI_SETSAVEPOINT, 0, 0);
}

void CEditorCtrl::LoadExternalSettings(CLanguageDatabase* pDatabase)
{
	CString strLanguageSettingFilePath = PathUtils::GetLanguageSettingFilePath(pDatabase->GetLanguageName());

	if (!PathFileExists(strLanguageSettingFilePath)) return;

	CStdioFile stdFile;
	if (stdFile.Open(strLanguageSettingFilePath, CFile::modeRead))
	{
		CString strLine;
		BOOL bStartReadCompilerPathSession = FALSE;
		BOOL bStartReadDebuggerPathSession = FALSE;
		BOOL bStartReadAutoCompleteSession = FALSE;
		CString strCompilerPath;
		CString strDebuggerPath;
		CString strAutoCompletes;
		while (stdFile.ReadString(strLine))
		{
			if (strLine.IsEmpty()) continue;
			if (strLine.Find(_T("@@ compiler path:")) != -1)
			{
				bStartReadCompilerPathSession = TRUE;
				continue;
			}
			else if (strLine.Find(_T("@@ debugger path:")) != -1)
			{
				bStartReadCompilerPathSession = FALSE;
				bStartReadDebuggerPathSession = TRUE;
				bStartReadAutoCompleteSession = FALSE;
				continue;
			}
			else if (strLine.Find(_T("@@ auto complete:")) != -1)
			{
				bStartReadDebuggerPathSession = FALSE;
				bStartReadAutoCompleteSession = TRUE;
				bStartReadCompilerPathSession = FALSE;
				continue;
			}

			if (bStartReadCompilerPathSession)
			{
				strCompilerPath += strLine.Trim();
			}
			else if (bStartReadDebuggerPathSession)
			{
				strDebuggerPath += strLine.Trim();
			}
			else if (bStartReadAutoCompleteSession)
			{
				strAutoCompletes += CSTRING_SPACE + strLine.Trim();
			}
		}
		pDatabase->SetLanguageAutoComplete(strAutoCompletes);
		pDatabase->SetCompilerPath(strCompilerPath);
		pDatabase->SetDebuggerPath(strDebuggerPath);
	}
	stdFile.Close();
}

void CEditorCtrl::SetColorForStyle(int style, COLORREF fore, COLORREF back, int size, const char* face)
{
	DoCommand(SCI_STYLESETFORE, style, fore);
	DoCommand(SCI_STYLESETBACK, style, back);
	if (size >= 1)
	{
		DoCommand(SCI_STYLESETSIZE, style, size);
	}
	if (face)
	{
		DoCommand(SCI_STYLESETFONT, style, reinterpret_cast<LPARAM>(face));
	}
}

void CEditorCtrl::SetTextToEditor(const CString& strText)
{
	if (IsReadOnlyEditor()) return;
	CT2A bufferUTF8(strText, TF_UTF8);
	LPCTSTR szUTF8 = (LPCTSTR)bufferUTF8.m_psz;
	if (szUTF8 != NULL)
	{
		DoCommand(SCI_SETTEXT, 0, reinterpret_cast<LPARAM>(szUTF8));
	}
	SetFocus();
}

void CEditorCtrl::GetText(CString& strText)
{
	auto GetTextFromEditor = [&]() -> char*
	{
		int lLen = (int)DoCommand(SCI_GETLENGTH) + 1;
		if (lLen > 0)
		{
			char* pReturn = new char[lLen + 1];
			if (pReturn != NULL)
			{
				*pReturn = '\0';
				DoCommand(SCI_GETTEXT, lLen, reinterpret_cast<LPARAM>(pReturn));
				return pReturn;
			}
		}
		return NULL;
	};

	std::unique_ptr<char> szText;
	szText.reset(GetTextFromEditor());
	if (szText != NULL)
	{
		auto uiCodePage = AppUtils::GetCurrentCodePage();
		AppUtils::SetCurrentCodePage(TF_UTF8);
		CString str = AppUtils::ArrayCharToCString(szText.get());
		AppUtils::SetCurrentCodePage(uiCodePage);
		strText = str;
	}
}

CString CEditorCtrl::GetAllText()
{
	auto GetTextFromEditor = [&]() -> char*
	{
		int lLen = (int)DoCommand(SCI_GETLENGTH) + 1;
		if (lLen > 0)
		{
			char* pReturn = new char[lLen + 1];
			if (pReturn != NULL)
			{
				*pReturn = '\0';
				DoCommand(SCI_GETTEXT, lLen, reinterpret_cast<LPARAM>(pReturn));
				return pReturn;
			}
		}
		return NULL;
	};

	CString strText;
	std::unique_ptr<char> szText;
	szText.reset(GetTextFromEditor());
	if (szText != NULL)
	{
		auto uiCodePage = AppUtils::GetCurrentCodePage();
		AppUtils::SetCurrentCodePage(TF_UTF8);
		CString str = AppUtils::ArrayCharToCString(szText.get());
		AppUtils::SetCurrentCodePage(uiCodePage);
		strText = str;
	}
	return strText;
}

void CEditorCtrl::GetTextRange(Sci_TextRange* txtRange)
{
	DoCommand(SCI_GETTEXTRANGE, 0, sptr_t(txtRange));
}

void CEditorCtrl::AddText(const CString& strText)
{
	if (strText.GetLength() <= 0) return;

	char* bufUtf8 = NULL;
	CREATE_BUFFER_FROM_CSTRING(bufUtf8, strText)
		if (bufUtf8 != NULL)
		{
			DoCommand(SCI_INSERTTEXT, 0, reinterpret_cast<LPARAM>(bufUtf8));
		}
	DELETE_POINTER_CPP_ARRAY(bufUtf8);
}

void CEditorCtrl::InsertText(const CString& strText, int pos)
{
	if (strText.GetLength() <= 0) return;
	CT2A bufferUTF8(strText, TF_UTF8);
	LPCTSTR szUTF8 = (LPCTSTR)bufferUTF8.m_psz;
	if (szUTF8 != NULL)
	{
		DoCommand(SCI_INSERTTEXT, pos, reinterpret_cast<LPARAM>(szUTF8));
	}
}

void CEditorCtrl::InsertTextAtCurrentPos(const CString& strText)
{
	if (strText.GetLength() <= 0) return;

	int nSelections = GetSelectionNumber();

	if (nSelections > SINGLE_SELECTION) return;

	CT2A bufferUTF8(strText, TF_UTF8);
	LPCTSTR szUTF8 = (LPCTSTR)bufferUTF8.m_psz;
	if (szUTF8 != NULL)
	{
		DoCommand(SCI_INSERTTEXT, GetCurrentPosition(), reinterpret_cast<LPARAM>(szUTF8));
		SetCurrentPosition(GetCurrentPosition() + strText.GetLength());
	}
}

void CEditorCtrl::InsertTextAtSelectionNumber(const CString& strText, int lSelectionCaretPosN)
{
	CT2A bufferUTF8(strText, TF_UTF8);
	LPCTSTR szUTF8 = (LPCTSTR)bufferUTF8.m_psz;
	if (szUTF8 != NULL)
	{
		DoCommand(SCI_INSERTTEXT, lSelectionCaretPosN, reinterpret_cast<LPARAM>(szUTF8));
	}
}

int CEditorCtrl::GetSelectionNumberCaret(int nSelectionNumber)
{
	return (int)DoCommand(SCI_GETSELECTIONNCARET, nSelectionNumber);
}

int CEditorCtrl::GetSelectionNumberAnchor(int nSelectionNumber)
{
	return (int)DoCommand(SCI_GETSELECTIONNANCHOR, nSelectionNumber);
}

void CEditorCtrl::InsertTextInMultiSelectionMode(const CString& strText, int nSelections, BOOL bIsBracket)
{
	std::vector<int> vecCaret;
	vecCaret.reserve(nSelections);
	for (int i = 0; i < nSelections; ++i)
	{
		int lSelectionCaretPosN = GetSelectionNumberCaret(i);
		vecCaret.push_back(lSelectionCaretPosN);
		InsertTextAtSelectionNumber(strText, lSelectionCaretPosN + strText.GetLength());
	}
	if (bIsBracket)
	{
		for (int i = 0; i < vecCaret.size(); ++i)
		{
			if (i == 0)
			{
				DoCommand(SCI_SETSELECTION, vecCaret[i] + strText.GetLength() - 1, vecCaret[i] + strText.GetLength() - 1);
			}
			else
			{
				DoCommand(SCI_ADDSELECTION, vecCaret[i] + strText.GetLength() - 1, vecCaret[i] + strText.GetLength() - 1);
			}
		}
	}
	else
	{
		for (int i = 0; i < vecCaret.size(); ++i)
		{
			if (i == 0)
			{
				DoCommand(SCI_SETSELECTION, vecCaret[i] + strText.GetLength(), vecCaret[i] + strText.GetLength());
			}
			else
			{
				DoCommand(SCI_ADDSELECTION, vecCaret[i] + strText.GetLength(), vecCaret[i] + strText.GetLength());
			}
		}
	}
}

void CEditorCtrl::AppendText(const CString& strText, int pos)
{
	if (strText.GetLength() <= 0) return;

	CT2A bufferUTF8(strText, TF_UTF8);
	LPCTSTR szUTF8 = (LPCTSTR)bufferUTF8.m_psz;
	if (szUTF8 != NULL)
	{
		DoCommand(SCI_APPENDTEXT, pos, reinterpret_cast<LPARAM>(szUTF8));
	}
}

void CEditorCtrl::ReplaceSelectionWithText(const CString& strText)
{
	CT2A bufferUTF8(strText, TF_UTF8);
	LPCTSTR szUTF8 = (LPCTSTR)bufferUTF8.m_psz;
	if (szUTF8 != NULL)
	{
		size_t start = GetSelectionStartPosition();
		DoCommand(SCI_REPLACESEL, 0, (LPARAM)"");
		DoCommand(SCI_ADDTEXT, strText.GetLength(), reinterpret_cast<LPARAM>(szUTF8));
		DoCommand(SCI_SETSEL, start, start + strText.GetLength());
	}
}

void CEditorCtrl::ReplaceSelectionNWithText(const CString& strText, int nSel)
{
	int anchorPos = GetSelectionNumberAnchor(nSel);
	int curPos = GetSelectionNumberCaret(nSel);
	CString strSelectedText;
	if (anchorPos > curPos)
	{
		RemoveTextRange(curPos, anchorPos - curPos);
	}
	else if (anchorPos < curPos)
	{
		RemoveTextRange(anchorPos, curPos - anchorPos);
	}
	else
	{
		int lLine = GetLineFromPosition(curPos);
		RemoveLine(lLine);
	}
}

void CEditorCtrl::ReplaceCurrentWord(const CString& strNewWord)
{
	int currentPos = int(DoCommand(SCI_GETCURRENTPOS));
	int startPos = int(DoCommand(SCI_WORDSTARTPOSITION, currentPos, 1));
	int endPos = int(DoCommand(SCI_WORDENDPOSITION, currentPos, true));
	SetSelectionRange(startPos, endPos);
	ReplaceSelectionWithText(strNewWord);
}

void CEditorCtrl::ReplaceLine(int lLine, const CString& strText)
{
	if (lLine < 0) return;
	int StartLinePos = GetLineStartPosition(lLine);
	int EndLinePos = GetLineEndPosition(lLine);
	SetStartSelection(StartLinePos);
	SetEndSelection(EndLinePos);
	ReplaceSelectionWithText(strText);
}

void CEditorCtrl::RemoveLine(int lLine)
{
	if (lLine < 0) return;
	int StartLinePos = GetLineStartPosition(lLine);
	int EndLinePos = GetLineEndPosition(lLine);
	RemoveTextRange(StartLinePos, GetLineLength(lLine));
}

void CEditorCtrl::RemoveTextRange(int lStart, int lLengthDelete)
{
	DoCommand(SCI_DELETERANGE, lStart, lLengthDelete);
}

void CEditorCtrl::RemoveSelectionText()
{
	DoCommand(SCI_TARGETFROMSELECTION, 0, 0);
	DoCommand(SCI_REPLACETARGET, 0, reinterpret_cast<LPARAM>(""));
}

void CEditorCtrl::GetTextFromLine(int nline, CString& strText)
{
	auto GetTextFromEditor = [&]() -> char*
	{
		int lLen = (int)DoCommand(SCI_LINELENGTH, nline - 1);
		if (lLen > 0)
		{
			char* pReturn = new char[lLen + 1];
			if (pReturn != NULL)
			{
				*pReturn = '\0';
				DoCommand(SCI_GETLINE, nline - 1, reinterpret_cast<LPARAM>(pReturn));
				pReturn[lLen] = '\0';
				return pReturn;
			}
		}
		return NULL;
	};

	std::unique_ptr<char> szText;
	szText.reset(GetTextFromEditor());
	if (szText != NULL)
	{
		auto uiCodePage = AppUtils::GetCurrentCodePage();
		AppUtils::SetCurrentCodePage(TF_UTF8);
		CString st = AppUtils::ArrayCharToCString(szText.get());
		st.Replace(EDITOR_NEW_LINE_CR, _T(""));
		st.Replace(EDITOR_NEW_LINE_LF, _T(""));
		AppUtils::SetCurrentCodePage(uiCodePage);
		strText = st;
	}
}

CString CEditorCtrl::GetTextFromCurrentLine()
{
	CString strLine;
	GetTextFromLine(GetCurrentLine(), strLine);
	return strLine;
}

CString CEditorCtrl::GetRecentAddedText()
{
	CString strWord;
	int curPos = int(DoCommand(SCI_GETCURRENTPOS));
	int startPos = int(DoCommand(SCI_WORDSTARTPOSITION, curPos, 1));
	if (curPos == startPos) return strWord;
	GetTextRange(strWord, startPos, curPos);
	return strWord;
}

CString CEditorCtrl::GetCurrentWord()
{
	int currentPos = int(DoCommand(SCI_GETCURRENTPOS));
	int startPos = int(DoCommand(SCI_WORDSTARTPOSITION, currentPos, 1));
	int endPos = int(DoCommand(SCI_WORDENDPOSITION, currentPos, true));
	CString strWord;
	GetTextRange(strWord, startPos, endPos);
	return strWord;
}

void CEditorCtrl::Cut()
{
	DoCommand(SCI_CUT);
}

void CEditorCtrl::CutLine()
{
	int nCurrentLine = GetCurrentLine();
	SetStartSelection(GetLineStartPosition(nCurrentLine - 1));
	SetEndSelection(GetLineEndPosition(nCurrentLine - 1));
	DoCommand(SCI_CUT);
}

void CEditorCtrl::Copy()
{
	DoCommand(SCI_COPY);
}

void CEditorCtrl::CopyLine()
{
	DoCommand(SCI_COPYALLOWLINE);
}

void CEditorCtrl::CopyText(const CString& strText, int length)
{
	char* bufUtf8 = NULL;
	CREATE_BUFFER_FROM_CSTRING(bufUtf8, strText)
		if (bufUtf8 != NULL)
		{
			DoCommand(SCI_COPYTEXT, length, reinterpret_cast<LPARAM>(bufUtf8));
		}
	DELETE_POINTER_CPP_ARRAY(bufUtf8);
}

void CEditorCtrl::CopyRange(int posStart, int posEnd)
{
	DoCommand(SCI_COPYRANGE, posStart, posEnd);
}

void CEditorCtrl::Paste()
{
	DoCommand(SCI_PASTE);
}

void CEditorCtrl::Clear()
{
	DoCommand(SCI_CLEAR);
}

void CEditorCtrl::SelectAll()
{
	DoCommand(SCI_SELECTALL);
}

void CEditorCtrl::ClearSelection(int lCaret)
{
	DoCommand(SCI_SETEMPTYSELECTION, lCaret);
}

void CEditorCtrl::DropSelections()
{
	int anchorPos = GetSelectionNumberAnchor(0);
	int curPos = GetSelectionNumberCaret(0);
	ClearSelection(curPos);
	SetCurrentAnchor(anchorPos);
	SetCurrentPosition(curPos);
}

int CEditorCtrl::GetSelectionStartPosition()
{
	return (int)DoCommand(SCI_GETSELECTIONSTART);
}

int CEditorCtrl::GetSelectionEndPosition()
{
	return (int)DoCommand(SCI_GETSELECTIONEND);
}

CString CEditorCtrl::GetSelectedText()
{
	int nSelections = GetSelectionNumber();
	if (nSelections == 1)
	{
		int lLen = (GetSelectionEndPosition() - GetSelectionStartPosition()) + 1;
		if (lLen > 0)
		{
			char* pReturn = new char[lLen + 1];
			if (pReturn != NULL)
			{
				*pReturn = '\0';
				DoCommand(SCI_GETSELTEXT, 0, reinterpret_cast<LPARAM>(pReturn));
				auto uiCodePage = AppUtils::GetCurrentCodePage();
				AppUtils::SetCurrentCodePage(TF_UTF8);
				CString strReturn = AppUtils::ArrayCharToCString(pReturn);
				AppUtils::SetCurrentCodePage(uiCodePage);
				DELETE_POINTER_CPP_ARRAY(pReturn)
					return strReturn;
			}
		}
	}
	return _T("");
}

CString CEditorCtrl::GetSelectedTextAtSelection(int nSel)
{
	int anchorPos = GetSelectionNumberAnchor(nSel);
	int curPos = GetSelectionNumberCaret(nSel);
	CString strSelectedText;
	if (anchorPos > curPos)
	{
		GetTextRange(strSelectedText, curPos, anchorPos);
	}
	else if (anchorPos < curPos)
	{
		GetTextRange(strSelectedText, anchorPos, curPos);
	}
	else
	{
		int lLine = GetLineFromPosition(curPos);
		GetTextFromLine(lLine + 1, strSelectedText);
	}
	return strSelectedText;
}

CString CEditorCtrl::GetUserTextLexer()
{
	return m_strUserTextLexer;;
}

void CEditorCtrl::SetUserTextLexer(const CString& strUserLexerName)
{
	m_strUserTextLexer = m_strUserTextLexer;
}

CString CEditorCtrl::GetFileExtension()
{
	return m_strFileExtension;
}

CString CEditorCtrl::GetLexerName()
{
	return m_strLexerName;
}

BOOL CEditorCtrl::CanPaste()
{
	return DoCommand(SCI_CANPASTE) != 0;
}

void CEditorCtrl::SetLexer(const char* m_strLexerNameName)
{
	if (m_strLexerNameName != NULL)
	{
		void* pLexer = m_CreateLexerFunc(m_strLexerNameName);
		DoCommand(SCI_SETILEXER, 0, reinterpret_cast<LPARAM>(pLexer));
	}
}

void CEditorCtrl::SetKeywords(const char* keywords, int nKeyWordSet)
{
	DoCommand(SCI_SETKEYWORDS, nKeyWordSet, reinterpret_cast<LPARAM>(keywords));
}

int CEditorCtrl::GetLineIndentPos(int nLine)
{
	int nIndPos = (int)DoCommand(SCI_GETLINEINDENTPOSITION, (WPARAM)nLine);
	return nIndPos;
}

int CEditorCtrl::GetCurrentLine()
{
	int lPos = (int)DoCommand(SCI_GETCURRENTPOS);
	return (int)DoCommand(SCI_LINEFROMPOSITION, lPos, 0) + 1;
}

// The return value is 0 if position <= 0. The return value is the last line if position is beyond the end of the document.
int CEditorCtrl::GetLineFromPosition(int position)
{
	return (int)DoCommand(SCI_LINEFROMPOSITION, position, 0);
}

CString CEditorCtrl::GetWordFromPosition(int lPosition)
{
	char word[10000];
	int wordStart = GetWordStartPosition(lPosition, TRUE);
	int wordEnd = GetWordEndPosition(lPosition, TRUE);
	Sci_TextRange tr;
	tr.chrg.cpMin = wordStart;
	tr.chrg.cpMax = wordEnd;
	tr.lpstrText = word;
	DoCommand(SCI_GETTEXTRANGE, 0, sptr_t(&tr));
	CString strWord(word);
	return strWord;
}

void CEditorCtrl::SelectWordFromPosition(int lPosition)
{
	int wordStart = GetWordStartPosition(lPosition, TRUE);
	int wordEnd = GetWordEndPosition(lPosition, TRUE);
	SetSelectionRange(wordStart, wordEnd);
}

int CEditorCtrl::GetWordStartPosition(int lPosition, BOOL bOnlyWordCharacters)
{
	return (int)DoCommand(SCI_WORDSTARTPOSITION, lPosition, bOnlyWordCharacters);
}

int CEditorCtrl::GetWordEndPosition(int lPosition, BOOL bOnlyWordCharacters)
{
	return (int)DoCommand(SCI_WORDENDPOSITION, lPosition, bOnlyWordCharacters);
}

int CEditorCtrl::GetCurrentColumn()
{
	int lPos = (int)DoCommand(SCI_GETCURRENTPOS);
	return (int)DoCommand(SCI_GETCOLUMN, lPos, 0);
}

int CEditorCtrl::GetCurrentPosition()
{
	return (int)DoCommand(SCI_GETCURRENTPOS);
}

int CEditorCtrl::GetCurrentAnchor()
{
	return (int)DoCommand(SCI_GETANCHOR);
}

void CEditorCtrl::SetCurrentPosition(int lPos)
{
	if (lPos < 0) return;
	DoCommand(SCI_SETCURRENTPOS, lPos, 0);
}

void CEditorCtrl::SetCurrentAnchor(int lPos)
{
	if (lPos < 0) return;
	DoCommand(SCI_SETANCHOR, lPos, 0);
}

void CEditorCtrl::SetFirstVisibleLine(int line)
{
	if (line < 0) return;
	int nDisplayedLine = static_cast<int>(DoCommand(SCI_GETFIRSTVISIBLELINE));
	int nDocLine = static_cast<int>(DoCommand(SCI_DOCLINEFROMVISIBLE, nDisplayedLine));
	if (nDocLine != line)
	{
		int nLineToShow = static_cast<int>(DoCommand(SCI_VISIBLEFROMDOCLINE, line));
		DoCommand(SCI_SETFIRSTVISIBLELINE, nLineToShow);
	}
}

int CEditorCtrl::GetFirstVisibleLine()
{
	if (IsEditorInWrapMode())
	{
		return GetFirstVisibleDocumentLine();
	}
	else
	{
		return (int)DoCommand(SCI_GETFIRSTVISIBLELINE);
	}
}

int CEditorCtrl::GetFirstVisibleDocumentLine()
{
	int nFirstVisibleLine = (int)DoCommand(SCI_GETFIRSTVISIBLELINE);
	return GetDocumentLineFromVisibleLine(nFirstVisibleLine);
}

int CEditorCtrl::GetVisibleLineFromDocumentLine(int nDocLine)
{
	return (int)DoCommand(SCI_VISIBLEFROMDOCLINE, nDocLine);
}

int CEditorCtrl::GetDocumentLineFromVisibleLine(int nVisibleLine)
{
	return (int)DoCommand(SCI_DOCLINEFROMVISIBLE, nVisibleLine);
}

int CEditorCtrl::GetEndVisibleLine()
{
	int nFirstVisualLine = GetFirstVisibleLine();
	auto nbLineOnScreen = GetLineOnScreen();
	auto nbLines = min(nbLineOnScreen, 400);
	auto nEndLineOnScreen = nFirstVisualLine + nbLines;
	return nEndLineOnScreen;
}

BOOL CEditorCtrl::IsSelectionEmpty()
{
	return (BOOL)DoCommand(SCI_GETSELECTIONEMPTY, 0, 0);
}

BOOL CEditorCtrl::IsTextSelected()
{
	int lPos = (int)DoCommand(SCI_GETCURRENTPOS);
	int lAnc = (int)DoCommand(SCI_GETANCHOR);
	if (lPos == lAnc)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

void CEditorCtrl::GotoPosition(int lPos)
{
	// need to remove folders before search
	ExpandAllFoldings();
	DoCommand(SCI_GOTOPOS, lPos, 0);
}

void CEditorCtrl::GotoPointXY(int lX, int lY)
{
	// need to remove folders before search
	ExpandAllFoldings();
	int lPos = (int)DoCommand(SCI_POSITIONFROMPOINT, lX, lY);
	GotoPosition(lPos);
}

int CEditorCtrl::GetLineNumberWidth(int nLineOnScreen)
{
	LRESULT lrFirstVisibleLineVis = DoCommand(SCI_GETFIRSTVISIBLELINE);
	LRESULT lrLastVisibleLineVis = nLineOnScreen + lrFirstVisibleLineVis + 1;
	LRESULT lrLastVisibleLineDoc = DoCommand(SCI_DOCLINEFROMVISIBLE, lrLastVisibleLineVis);
	int lineNumberDigits = 0;
	if (lrLastVisibleLineDoc < 10) lrLastVisibleLineDoc = 1;
	else if (lrLastVisibleLineDoc < 100) lineNumberDigits = 2;
	else if (lrLastVisibleLineDoc < 1000) lineNumberDigits = 3;
	else if (lrLastVisibleLineDoc < 10000) lineNumberDigits = 4;
	else if (lrLastVisibleLineDoc < 100000) lineNumberDigits = 5;
	else if (lrLastVisibleLineDoc < 1000000) lineNumberDigits = 6;
	else
	{
		lineNumberDigits = 7;
		lrLastVisibleLineDoc /= 1000000;
		while (lrLastVisibleLineDoc)
		{
			lrLastVisibleLineDoc /= 10;
			++lineNumberDigits;
		}
	}
	lineNumberDigits = lineNumberDigits < 3 ? 3 : lineNumberDigits;
	return 8 + lineNumberDigits * static_cast<int>(DoCommand(SCI_TEXTWIDTH, STYLE_LINENUMBER, reinterpret_cast<LPARAM>("8")));
}

int CEditorCtrl::GetLinenumberChars()
{
	LRESULT lLines = DoCommand(SCI_GETLINECOUNT, 0, 0);

	int nChars = 2; // Added an extra char to allow until 9999 lines even with maximum zoom
	while (lLines > 0)
	{
		lLines = lLines / 10;
		nChars++;
	}
	return nChars;
}

void CEditorCtrl::IndentAll()
{
	DoCommand(SCI_SELECTALL);
	DoCommand(SCI_TAB);
}

BOOL CEditorCtrl::IsBraceCharacter(int nCharValue)
{
	switch (nCharValue)
	{
	case '(':
	case ')':
	case '[':
	case ']':
	case '{':
	case '}':
	case '<':
	case '>':
		return TRUE;
	}
	return FALSE;
}

int CEditorCtrl::GetCharacterAtPosition(int nPos)
{
	return static_cast<int>(DoCommand(SCI_GETCHARAT, nPos));
}

int CEditorCtrl::GetColumnAtPosition(int nPos)
{
	return static_cast<int>(DoCommand(SCI_GETCOLUMN, nPos));
}

void CEditorCtrl::DoBraceMatchHighlight()
{
	int lStart = static_cast<int>(DoCommand(SCI_GETCURRENTPOS));
	int lEnd = static_cast<int>(DoCommand(SCI_BRACEMATCH, lStart - 1, 0));
	// if there is a matching brace highlight it
	if (lEnd >= 0)
	{
		DoCommand(SCI_BRACEHIGHLIGHT, lStart - 1, lEnd);
		int nColumnHightlight = static_cast<int>(DoCommand(SCI_GETCOLUMN, lStart - 1));
		DoCommand(SCI_SETHIGHLIGHTGUIDE, nColumnHightlight);
	}
	// if there is NO matching brace erase old highlight
	else
	{
		DoCommand(SCI_BRACEHIGHLIGHT, -1, -1);
		DoCommand(SCI_SETHIGHLIGHTGUIDE, 0);
	}
}

SearchResult CEditorCtrl::FindTextResult(const char* text, sptr_t start, sptr_t end, int flags)
{
	SearchResult returnValue = { 0 };
	Sci_TextToFind search{};
	search.lpstrText = const_cast<char*>(text);
	search.chrg.cpMin = static_cast<Sci_PositionCR>(start);
	search.chrg.cpMax = static_cast<Sci_PositionCR>(end);
	auto result = DoCommand(SCI_FINDTEXT, flags, reinterpret_cast<LPARAM>(&search));
	if (-1 == result)
	{
		returnValue.success = false;
	}
	else
	{
		returnValue.success = true;
		returnValue.start = search.chrgText.cpMin;
		returnValue.end = search.chrgText.cpMax;
	}
	return returnValue;
}

SearchResult CEditorCtrl::FindOpenTag(const std::string& tagName, sptr_t start, sptr_t end)
{
	std::string search("<");
	search.append(tagName);
	SearchResult openTagFound = { 0 };
	openTagFound.success = false;
	SearchResult result{};
	int        nextChar = 0;
	sptr_t     styleAt = 0;
	auto       searchStart = start;
	auto       searchEnd = end;
	bool       forwardSearch = (start < end);
	do
	{
		result = FindTextResult(search.c_str(), searchStart, searchEnd, 0);
		if (result.success)
		{
			nextChar = static_cast<int>(DoCommand(SCI_GETCHARAT, result.end));
			styleAt = DoCommand(SCI_GETSTYLEAT, result.start);
			if (styleAt != SCE_H_CDATA && styleAt != SCE_H_DOUBLESTRING && styleAt != SCE_H_SINGLESTRING)
			{
				// We've got an open tag for this tag name (i.e. nextChar was space or '>')
				// Now we need to find the end of the start tag.

				// Common case, the tag is an empty tag with no whitespace. e.g. <TAGNAME>
				if (nextChar == '>')
				{
					openTagFound.end = result.end;
					openTagFound.success = true;
				}
				else if (AppUtils::IsXMLWhitespace(nextChar))
				{
					auto closeAnglePosition = FindCloseAngle(result.end, forwardSearch ? end : start);
					if (-1 != closeAnglePosition && '/' != DoCommand(SCI_GETCHARAT, closeAnglePosition - 1))
					{
						openTagFound.end = closeAnglePosition;
						openTagFound.success = true;
					}
				}
			}
		}

		if (forwardSearch)
		{
			searchStart = result.end + 1;
		}
		else
		{
			searchStart = result.start - 1;
		}

		// Loop while we've found a <TAGNAME, but it's either in a CDATA section,
		// or it's got more none whitespace characters after it. e.g. <TAGNAME2
	} while (result.success && !openTagFound.success);

	openTagFound.start = result.start;

	return openTagFound;
}

sptr_t CEditorCtrl::FindCloseAngle(sptr_t startPosition, sptr_t endPosition)
{
	// We'll search for the next '>', and check it's not in an attribute using the style
	SearchResult closeAngle{};

	bool   isValidClose = false;
	sptr_t returnPosition = -1;

	// Only search forwards
	if (startPosition > endPosition)
	{
		auto temp = endPosition;
		endPosition = startPosition;
		startPosition = temp;
	}

	do
	{
		isValidClose = false;

		closeAngle = FindTextResult(">", startPosition, endPosition, 0);
		if (closeAngle.success)
		{
			int style = static_cast<int>(DoCommand(SCI_GETSTYLEAT, closeAngle.start));
			// As int as we're not in an attribute (  <TAGNAME attrib="val>ue"> is VALID XML. )
			if (style != SCE_H_DOUBLESTRING && style != SCE_H_SINGLESTRING)
			{
				returnPosition = closeAngle.start;
				isValidClose = true;
			}
			else
			{
				startPosition = closeAngle.end;
			}
		}

	} while (closeAngle.success && isValidClose == false);

	return returnPosition;
}

SearchResult CEditorCtrl::FindCloseTag(const std::string& tagName, sptr_t start, sptr_t end)
{
	std::string search("</");
	search.append(tagName);
	SearchResult closeTagFound = { 0 };
	closeTagFound.success = false;
	SearchResult result{};
	int        nextChar = 0;
	sptr_t     styleAt = 0;
	auto       searchStart = start;
	auto       searchEnd = end;
	bool       forwardSearch = (start < end);
	bool       validCloseTag = false;
	do
	{
		validCloseTag = false;
		result = FindTextResult(search.c_str(), searchStart, searchEnd, 0);
		if (result.success)
		{
			nextChar = static_cast<int>(DoCommand(SCI_GETCHARAT, result.end));
			styleAt = DoCommand(SCI_GETSTYLEAT, result.start);

			// Setup the parameters for the next search, if there is one.
			if (forwardSearch)
			{
				searchStart = result.end + 1;
			}
			else
			{
				searchStart = result.start - 1;
			}

			if (styleAt != SCE_H_CDATA && styleAt != SCE_H_SINGLESTRING && styleAt != SCE_H_DOUBLESTRING) // If what we found was in CDATA section, it's not a valid tag.
			{
				// Common case - '>' follows the tag name directly
				if (nextChar == '>')
				{
					validCloseTag = true;
					closeTagFound.start = result.start;
					closeTagFound.end = result.end;
					closeTagFound.success = true;
				}
				else if (AppUtils::IsXMLWhitespace(nextChar)) // Otherwise, if it's whitespace, then allow whitespace until a '>' - any other character is invalid.
				{
					auto whitespacePoint = result.end;
					do
					{
						++whitespacePoint;
						nextChar = static_cast<int>(DoCommand(SCI_GETCHARAT, whitespacePoint));

					} while (AppUtils::IsXMLWhitespace(nextChar));

					if (nextChar == '>')
					{
						validCloseTag = true;
						closeTagFound.start = result.start;
						closeTagFound.end = whitespacePoint;
						closeTagFound.success = true;
					}
				}
			}
		}

	} while (result.success && !validCloseTag);

	return closeTagFound;
}

std::vector<std::pair<sptr_t, sptr_t>> CEditorCtrl::GetAttributesPos(sptr_t start, sptr_t end)
{
	std::vector<std::pair<sptr_t, sptr_t>> attributes;

	auto          bufLen = end - start + 1;
	auto          buf = std::make_unique<char[]>(bufLen + 1);
	Sci_TextRange tr{};
	tr.chrg.cpMin = static_cast<Sci_PositionCR>(start);
	tr.chrg.cpMax = static_cast<Sci_PositionCR>(end);
	tr.lpstrText = buf.get();
	DoCommand(SCI_GETTEXTRANGE, 0, reinterpret_cast<LPARAM>(&tr));

	enum class AttrStates
	{
		Attr_Invalid,
		Attr_Key,
		Attr_Pre_Assign,
		Attr_Assign,
		Attr_String,
		Attr_Value,
		Attr_Valid
	} state = AttrStates::Attr_Invalid;

	sptr_t startPos = -1;
	sptr_t oneMoreChar = 1;
	sptr_t i = 0;
	for (; i < bufLen; i++)
	{
		switch (buf[i])
		{
		case ' ':
		case '\t':
		case '\n':
		case '\r':
		{
			if (state == AttrStates::Attr_Key)
				state = AttrStates::Attr_Pre_Assign;
			else if (state == AttrStates::Attr_Value)
			{
				state = AttrStates::Attr_Valid;
				oneMoreChar = 0;
			}
		}
		break;

		case '=':
		{
			if (state == AttrStates::Attr_Key || state == AttrStates::Attr_Pre_Assign)
				state = AttrStates::Attr_Assign;
			else if (state == AttrStates::Attr_Assign || state == AttrStates::Attr_Value)
				state = AttrStates::Attr_Invalid;
		}
		break;

		case '"':
		{
			if (state == AttrStates::Attr_String)
			{
				state = AttrStates::Attr_Valid;
				oneMoreChar = 1;
			}
			else if (state == AttrStates::Attr_Key || state == AttrStates::Attr_Pre_Assign || state == AttrStates::Attr_Value)
				state = AttrStates::Attr_Invalid;
			else if (state == AttrStates::Attr_Assign)
				state = AttrStates::Attr_String;
		}
		break;

		default:
		{
			if (state == AttrStates::Attr_Invalid)
			{
				state = AttrStates::Attr_Key;
				startPos = i;
			}
			else if (state == AttrStates::Attr_Pre_Assign)
				state = AttrStates::Attr_Invalid;
			else if (state == AttrStates::Attr_Assign)
				state = AttrStates::Attr_Value;
		}
		}

		if (state == AttrStates::Attr_Valid)
		{
			attributes.push_back(std::pair<sptr_t, sptr_t>(start + startPos, start + i + oneMoreChar));
			state = AttrStates::Attr_Invalid;
		}
	}
	if (state == AttrStates::Attr_Value)
		attributes.push_back(std::pair<sptr_t, sptr_t>(start + startPos, start + i - 1));

	return attributes;
}

bool CEditorCtrl::GetXmlHtmlTagsPosition(XmlHtmlTagsPosition& tagPositions)
{
	bool       tagFound = false;
	auto       caret = DoCommand(SCI_GETCURRENTPOS);
	auto       searchStartPoint = caret;
	sptr_t     styleAt = 0;
	SearchResult openFound{};

	// Search back for the previous open angle bracket.
	// Keep looking whilst the angle bracket found is inside an XML attribute
	do
	{
		openFound = FindTextResult("<", searchStartPoint, 0, 0);
		styleAt = DoCommand(SCI_GETSTYLEAT, openFound.start);
		searchStartPoint = openFound.start - 1;
	} while (openFound.success && (styleAt == SCE_H_DOUBLESTRING || styleAt == SCE_H_SINGLESTRING) && searchStartPoint > 0);

	if (openFound.success && styleAt != SCE_H_CDATA)
	{
		// Found the "<" before the caret, now check there isn't a > between that position and the caret.
		SearchResult closeFound{};
		searchStartPoint = openFound.start;
		do
		{
			closeFound = FindTextResult(">", searchStartPoint, caret, 0);
			styleAt = DoCommand(SCI_GETSTYLEAT, closeFound.start);
			searchStartPoint = closeFound.end;
		} while (closeFound.success && (styleAt == SCE_H_DOUBLESTRING || styleAt == SCE_H_SINGLESTRING) && searchStartPoint <= caret);

		if (!closeFound.success)
		{
			// We're in a tag (either a start tag or an end tag)
			auto nextChar = DoCommand(SCI_GETCHARAT, openFound.start + 1);

			/////////////////////////////////////////////////////////////////////////
			// CURSOR IN CLOSE TAG
			/////////////////////////////////////////////////////////////////////////
			if ('/' == nextChar)
			{
				tagPositions.tagCloseStart = openFound.start;
				auto docLength = DoCommand(SCI_GETLENGTH);
				auto endCloseTag = FindTextResult(">", caret, docLength, 0);
				if (endCloseTag.success)
				{
					tagPositions.tagCloseEnd = endCloseTag.end;
				}
				// Now find the tagName
				auto position = openFound.start + 2;

				// UTF-8 or ASCII tag name
				std::string tagName;
				nextChar = DoCommand(SCI_GETCHARAT, position);
				// Checking for " or ' is actually wrong here, but it means it works better with invalid XML
				while (position < docLength && !AppUtils::IsXMLWhitespace(static_cast<int>(nextChar)) && nextChar != '/' && nextChar != '>' && nextChar != '\"' && nextChar != '\'')
				{
					tagName.push_back(static_cast<char>(nextChar));
					++position;
					nextChar = DoCommand(SCI_GETCHARAT, position);
				}

				// Now we know where the end of the tag is, and we know what the tag is called
				if (!tagName.empty())
				{
					/* Now we need to find the open tag.  The logic here is that we search for "<TAGNAME",
					* then check the next character - if it's one of '>', ' ', '\"' then we know we've found
					* a relevant tag.
					* We then need to check if either
					*    a) this tag is a self-closed tag - e.g. <TAGNAME attrib="value" />
					* or b) this tag has another closing tag after it and before our closing tag
					*       e.g.  <TAGNAME attrib="value">some text</TAGNAME></TAGNA|ME>
					*             (cursor represented by |)
					* If it's either of the above, then we continue searching, but only up to the
					* the point of the last find. (So in the (b) example above, we'd only search backwards
					* from the first "<TAGNAME...", as we know there's a close tag for the opened tag.

					* NOTE::  NEED TO CHECK THE ROTTEN CASE: ***********************************************************
					* <TAGNAME attrib="value"><TAGNAME>something</TAGNAME></TAGNAME></TAGNA|ME>
					* Maybe count all closing tags between start point and start of our end tag.???
					*/
					auto       currentEndPoint = tagPositions.tagCloseStart;
					auto       openTagsRemaining = 1;
					SearchResult nextOpenTag{};
					do
					{
						nextOpenTag = FindOpenTag(tagName, currentEndPoint, 0);
						if (nextOpenTag.success)
						{
							--openTagsRemaining;
							// Open tag found
							// Now we need to check how many close tags there are between the open tag we just found,
							// and our close tag
							// eg. (Cursor == | )
							// <TAGNAME attrib="value"><TAGNAME>something</TAGNAME></TAGNAME></TAGNA|ME>
							//                         ^^^^^^^^ we've found this guy
							//                                           ^^^^^^^^^^ ^^^^^^^^ Now we need to count these fellas
							SearchResult inBetweenCloseTag{};
							auto       currentStartPosition = nextOpenTag.end;
							auto       closeTagsFound = 0;
							bool       forwardSearch = (currentStartPosition < currentEndPoint);

							do
							{
								inBetweenCloseTag = FindCloseTag(tagName, currentStartPosition, currentEndPoint);

								if (inBetweenCloseTag.success)
								{
									++closeTagsFound;
									if (forwardSearch)
									{
										currentStartPosition = inBetweenCloseTag.end;
									}
									else
									{
										currentStartPosition = inBetweenCloseTag.start - 1;
									}
								}

							} while (inBetweenCloseTag.success);

							// If we didn't find any close tags between the open and our close,
							// and there's no open tags remaining to find
							// then the open we found was the right one, and we can return it
							if (0 == closeTagsFound && 0 == openTagsRemaining)
							{
								tagPositions.tagOpenStart = nextOpenTag.start;
								tagPositions.tagOpenEnd = nextOpenTag.end + 1;
								tagPositions.tagNameEnd = nextOpenTag.start + static_cast<sptr_t>(tagName.size()) + 1; /* + 1 to account for '<' */
								tagFound = true;
							}
							else
							{
								// Need to find the same number of opening tags, without closing tags etc.
								openTagsRemaining += closeTagsFound;
								currentEndPoint = nextOpenTag.start;
							}
						}
					} while (!tagFound && openTagsRemaining > 0 && nextOpenTag.success);
				}
			}
			else
			{
				/////////////////////////////////////////////////////////////////////////
				// CURSOR IN OPEN TAG
				/////////////////////////////////////////////////////////////////////////
				auto position = openFound.start + 1;
				auto docLength = DoCommand(SCI_GETLENGTH);

				tagPositions.tagOpenStart = openFound.start;

				std::string tagName;
				nextChar = DoCommand(SCI_GETCHARAT, position);
				// Checking for " or ' is actually wrong here, but it means it works better with invalid XML
				while (position < docLength && !AppUtils::IsXMLWhitespace(static_cast<int>(nextChar)) && nextChar != '/' && nextChar != '>' && nextChar != '\"' && nextChar != '\'')
				{
					tagName.push_back(static_cast<char>(nextChar));
					++position;
					nextChar = DoCommand(SCI_GETCHARAT, position);
				}

				// Now we know where the end of the tag is, and we know what the tag is called
				if (!tagName.empty())
				{
					// First we need to check if this is a self-closing tag.
					// If it is, then we can just return this tag to highlight itself.
					tagPositions.tagNameEnd = openFound.start + tagName.size() + 1;
					auto closeAnglePosition = FindCloseAngle(position, docLength);
					if (-1 != closeAnglePosition)
					{
						tagPositions.tagOpenEnd = closeAnglePosition + 1;
						// If it's a self closing tag
						if (DoCommand(SCI_GETCHARAT, closeAnglePosition - 1) == '/')
						{
							// Set it as found, and mark that there's no close tag
							tagPositions.tagCloseEnd = -1;
							tagPositions.tagCloseStart = -1;
							tagFound = true;
						}
						else
						{
							// It's a normal open tag

							/* Now we need to find the close tag.  The logic here is that we search for "</TAGNAME",
							* then check the next character - if it's '>' or whitespace followed by '>' then we've
							* found a relevant tag.
							* We then need to check if
							* our tag has another opening tag after it and before the closing tag we've found
							*       e.g.  <TA|GNAME><TAGNAME attrib="value">some text</TAGNAME></TAGNAME>
							*             (cursor represented by |)
							*/
							auto       currentStartPosition = tagPositions.tagOpenEnd;
							auto       closeTagsRemaining = 1;
							SearchResult nextCloseTag{};
							do
							{
								nextCloseTag = FindCloseTag(tagName, currentStartPosition, docLength);
								if (nextCloseTag.success)
								{
									--closeTagsRemaining;
									// Open tag found
									// Now we need to check how many close tags there are between the open tag we just found,
									// and our close tag
									// eg. (Cursor == | )
									// <TAGNAM|E attrib="value"><TAGNAME>something</TAGNAME></TAGNAME></TAGNAME>
									//                                            ^^^^^^^^ we've found this guy
									//                         ^^^^^^^^^ Now we need to find this fella
									SearchResult inBetweenOpenTag{};
									auto       currentEndPosition = nextCloseTag.start;
									sptr_t     openTagsFound = 0;

									do
									{
										inBetweenOpenTag = FindOpenTag(tagName, currentStartPosition, currentEndPosition);

										if (inBetweenOpenTag.success)
										{
											++openTagsFound;
											currentStartPosition = inBetweenOpenTag.end;
										}

									} while (inBetweenOpenTag.success);

									// If we didn't find any open tags between our open and the close,
									// and there's no close tags remaining to find
									// then the close we found was the right one, and we can return it
									if (0 == openTagsFound && 0 == closeTagsRemaining)
									{
										tagPositions.tagCloseStart = nextCloseTag.start;
										tagPositions.tagCloseEnd = nextCloseTag.end + 1;
										tagFound = true;
									}
									else
									{
										// Need to find the same number of closing tags, without opening tags etc.
										closeTagsRemaining += static_cast<int>(openTagsFound);
										currentStartPosition = nextCloseTag.end;
									}
								}
							} while (!tagFound && closeTagsRemaining > 0 && nextCloseTag.success);
						} // end if (selfclosingtag)... else {
					}     // end if (-1 != closeAngle)  {

				} // end if !tagName.empty()
			}     // end open tag test
		}
	}
	return tagFound;
}

void CEditorCtrl::DoXMLHTMLTagsHightlight()
{
	// basically the same as MatchBraces(), but much more complicated since
	// finding xml tags is harder than just finding braces...

	sptr_t startFilePosition = 0;
	sptr_t endFilePosition = DoCommand(SCI_GETLENGTH);
	DoCommand(SCI_SETINDICATORCURRENT, INDIC_TAGMATCH);
	DoCommand(SCI_INDICATORCLEARRANGE, startFilePosition, endFilePosition - startFilePosition);
	DoCommand(SCI_SETINDICATORCURRENT, INDIC_TAGATTR);
	DoCommand(SCI_INDICATORCLEARRANGE, startFilePosition, endFilePosition - startFilePosition);

	// Get the original targets and search options to restore after tag matching operation
	auto originalStartPos = DoCommand(SCI_GETTARGETSTART);
	auto originalEndPos = DoCommand(SCI_GETTARGETEND);
	auto originalSearchFlags = DoCommand(SCI_GETSEARCHFLAGS);

	XmlHtmlTagsPosition tagPositions = { 0 };

	// Detect if it's a xml/html tag
	if (GetXmlHtmlTagsPosition(tagPositions))
	{
		DoCommand(SCI_SETINDICATORCURRENT, INDIC_TAGMATCH);
		int openTagTailLen = 2;

		// Coloring the close tag first
		if ((tagPositions.tagCloseStart != -1) && (tagPositions.tagCloseEnd != -1))
		{
			DoCommand(SCI_INDICATORFILLRANGE, tagPositions.tagCloseStart, tagPositions.tagCloseEnd - tagPositions.tagCloseStart);
			// tag close is present, so it's not single tag
			openTagTailLen = 1;
		}

		// Coloring the open tag
		DoCommand(SCI_INDICATORFILLRANGE, tagPositions.tagOpenStart, tagPositions.tagNameEnd - tagPositions.tagOpenStart);
		DoCommand(SCI_INDICATORFILLRANGE, tagPositions.tagOpenEnd - openTagTailLen, openTagTailLen);

		// Coloring its attributes
		/*auto attributes = GetAttributesPos(tagPositions.tagNameEnd, tagPositions.tagOpenEnd - openTagTailLen);
		DoCommand(SCI_SETINDICATORCURRENT, INDIC_TAGATTR);
		for (const auto& iter : attributes)
		{
			DoCommand(SCI_INDICATORFILLRANGE, iter.first, iter.second - iter.first);
		}*/

		// Coloring indent guide line position
		if (DoCommand(SCI_GETINDENTATIONGUIDES) != 0)
		{
			auto columnAtCaret = DoCommand(SCI_GETCOLUMN, tagPositions.tagOpenStart);
			auto columnOpposite = DoCommand(SCI_GETCOLUMN, tagPositions.tagCloseStart);

			auto lineAtCaret = DoCommand(SCI_LINEFROMPOSITION, tagPositions.tagOpenStart);
			auto lineOpposite = DoCommand(SCI_LINEFROMPOSITION, tagPositions.tagCloseStart);

			if (tagPositions.tagCloseStart != -1 && lineAtCaret != lineOpposite)
			{
				DoCommand(SCI_BRACEHIGHLIGHT, tagPositions.tagOpenStart, tagPositions.tagCloseEnd - 1);
				DoCommand(SCI_SETHIGHLIGHTGUIDE, (columnAtCaret < columnOpposite) ? columnAtCaret : columnOpposite);
			}
		}
	}

	// restore the original targets and search options to avoid the conflict with search/replace function
	DoCommand(SCI_SETTARGETSTART, originalStartPos);
	DoCommand(SCI_SETTARGETEND, originalEndPos);
	DoCommand(SCI_SETSEARCHFLAGS, originalSearchFlags);
}

int CEditorCtrl::FindNextMatchWordPostion(const CString& strSearhWord, int lStartSearchPos, int nSearchFlag)
{
	ExpandAllFoldings();
	CT2A stUTF8(strSearhWord, TF_UTF8);
	LPCTSTR szUTF8 = (LPCTSTR)stUTF8.m_psz;
	int lPos = lStartSearchPos;
	Sci_TextToFind tf;
	tf.lpstrText = (const char*)szUTF8;
	tf.chrg.cpMin = lPos;
	tf.chrg.cpMax = (Sci_PositionCR)DoCommand(SCI_GETLENGTH);
	lPos = (int)DoCommand(SCI_FINDTEXT, nSearchFlag, sptr_t(&tf));
	return lPos;
}

int CEditorCtrl::FindPreviousMatchWordPostion(const CString& strSearhWord, int lStartSearchPos, int lMinSel, int nSearchFlag)
{
	ExpandAllFoldings();
	CT2A stUTF8(strSearhWord, TF_UTF8);
	LPCTSTR szUTF8 = (LPCTSTR)stUTF8.m_psz;
	int lPos = lStartSearchPos;
	Sci_TextToFind tf;
	tf.lpstrText = (const char*)szUTF8;
	if (lMinSel >= 0)
		tf.chrg.cpMin = lMinSel;
	else
		tf.chrg.cpMin = lPos - 1;
	tf.chrg.cpMax = 0;
	lPos = (int)DoCommand(SCI_FINDTEXT, nSearchFlag, sptr_t(&tf));
	return lPos;
}

BOOL CEditorCtrl::SearchForward(const CString& strText)
{
	if (strText.IsEmpty())
	{
		return FALSE;
	}

	// need to remove folders before search
	ExpandAllFoldings();

	CT2A stUTF8(strText, TF_UTF8);
	LPCTSTR szUTF8 = (LPCTSTR)stUTF8.m_psz;

	int lPos = GetCurrentPosition();
	Sci_TextToFind tf;
	tf.lpstrText = (const char*)szUTF8;
	tf.chrg.cpMin = lPos;
	tf.chrg.cpMax = (Sci_PositionCR)DoCommand(SCI_GETLENGTH);
	lPos = (int)DoCommand(SCI_FINDTEXT, m_nSearchflags, sptr_t(&tf));
	if (lPos >= 0)
	{
		SetFocus();
		GotoPosition(lPos);
		SetSelectionTextColor(BasicColors::yellow, 90);
		DoCommand(SCI_SETSEL, tf.chrgText.cpMin, tf.chrgText.cpMax);
		SetLineCenterKeepView(GetCurrentLine());
		return TRUE;
	}
	return FALSE;
}

BOOL CEditorCtrl::SearchBackward(const CString& strText)
{
	if (strText.IsEmpty())
		return FALSE;

	// need to remove folders before search
	ExpandAllFoldings();

	CT2A stUTF8(strText, TF_UTF8);
	LPCTSTR szUTF8 = (LPCTSTR)stUTF8.m_psz;

	int lPos = GetCurrentPosition();
	int lMinSel = GetSelectionStartPosition();
	Sci_TextToFind tf;
	tf.lpstrText = (const char*)szUTF8;
	if (lMinSel >= 0)
		tf.chrg.cpMin = lMinSel;
	else
		tf.chrg.cpMin = lPos - 1;
	tf.chrg.cpMax = 0;
	lPos = static_cast<int>(DoCommand(SCI_FINDTEXT, m_nSearchflags, sptr_t(&tf)));
	if (lPos >= 0)
	{
		SetFocus();
		GotoPosition(lPos);
		SetSelectionTextColor(BasicColors::yellow, 90);
		DoCommand(SCI_SETSEL, tf.chrgText.cpMin, tf.chrgText.cpMax);
		SetLineCenterBackwardDisplay(GetCurrentLine());
		return TRUE;
	}
	return FALSE;
}

void CEditorCtrl::SetDisplayLinenumbers(BOOL bFlag)
{
	m_bLinenumbers = bFlag;
	if (!bFlag) // if display is turned off we set margin 0 to 0
	{
		DoCommand(SCI_SETMARGINWIDTHN, 0, 0);
	}
	else // if display is turned on we set margin 0 to the calculated width
	{
		int nLineOnScreen = static_cast<int>(DoCommand(SCI_LINESONSCREEN));
		if (nLineOnScreen)
		{
			DoCommand(SCI_SETMARGINWIDTHN, 0, GetLineNumberWidth(nLineOnScreen));
		}
	}
}

void CEditorCtrl::SetDisplaySelection(BOOL bFlag)
{
	m_bSelection = bFlag;
	if (bFlag)
		DoCommand(SCI_SETMARGINWIDTHN, 1, VINATEXT_MARGINWIDTH);
	else
		DoCommand(SCI_SETMARGINWIDTHN, 1, 0);
}

void CEditorCtrl::SetDisplayFolding(BOOL bFlag)
{
	m_bFolding = bFlag;
	if (bFlag)
		DoCommand(SCI_SETMARGINWIDTHN, 2, VINATEXT_MARGINWIDTH);
	else
		DoCommand(SCI_SETMARGINWIDTHN, 2, 0);
}

int CEditorCtrl::GetCurrentStyle()
{
	int lPos = (int)DoCommand(SCI_GETCURRENTPOS, 0, 0);
	return (int)DoCommand(SCI_GETSTYLEAT, lPos, 0);
}

int CEditorCtrl::GetCurrentLineFoldinglevel(int lLine)
{
	int levelFolding = (DoCommand(SCI_GETFOLDLEVEL, lLine, 0)) & SC_FOLDLEVELNUMBERMASK;
	return levelFolding - 1024;
}

BOOL CEditorCtrl::IsLineHasFoldingLevel(int lLine)
{
	if (DoCommand(SCI_GETFOLDLEVEL, lLine) & SC_FOLDLEVELHEADERFLAG)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CEditorCtrl::IsLineExpanded(int lLine)
{
	return static_cast<BOOL>(DoCommand(SCI_GETFOLDEXPANDED, lLine));
}

void CEditorCtrl::ExpandFoldedLine(int lPosition)
{
	int nLine = (int)DoCommand(SCI_LINEFROMPOSITION, lPosition, 0);
	if (GetLineEndPosition(nLine) == lPosition && !IsLineExpanded(nLine))
	{
		DoCommand(SCI_FOLDLINE, nLine, SC_FOLDACTION_EXPAND);
	}
}

void CEditorCtrl::DoToggleFolding(int lPosition)
{
	int nLine = (int)DoCommand(SCI_LINEFROMPOSITION, lPosition, 0);
	DoCommand(SCI_FOLDLINE, nLine, SC_FOLDACTION_TOGGLE);
}

void CEditorCtrl::GotoLine(int lLine)
{
	if (lLine < 0) return;

	ExpandAllFoldings();
	DoCommand(SCI_GOTOLINE, lLine - 1, 0);
	SetLineCenterDisplay(GetCurrentLine());
}

void CEditorCtrl::SetScrollCaret()
{
	DoCommand(SCI_SCROLLCARET);
}

void CEditorCtrl::SetLineCenterDisplay(int lLine)
{
	if (lLine < 0) return;
	int linesOnScreen = GetLineOnScreen();
	linesOnScreen = linesOnScreen - 2;
	int start = lLine - (linesOnScreen / 2);
	if (start < 0)
	{
		start = 0;
	}
	SetFirstVisibleLine(start);
}

void CEditorCtrl::SetLineCenterKeepView(int lLine)
{
	if (lLine < 0) return;
	int linesOnScreen = GetLineOnScreen();
	int nFisrtLinevisible = GetFirstVisibleLine();
	int lastLineVisible = nFisrtLinevisible + linesOnScreen;
	if (lastLineVisible <= lLine || nFisrtLinevisible == 0)
	{
		linesOnScreen = linesOnScreen - 2;
		int start = lLine - (linesOnScreen / 2);
		if (start < 0)
		{
			start = 0;
		}
		SetFirstVisibleLine(start);
	}
}

void CEditorCtrl::UpdateMainSelectionInCurrentView()
{
	int nFisrtLinevisible = GetFirstVisibleLine();
	for (int nsel = 0; nsel < GetSelectionNumber(); ++nsel)
	{
		int nLineSel = GetLineFromSelection(nsel);
		if (nFisrtLinevisible + GetLineOnScreen() / 2 < nLineSel)
		{
			DoCommand(SCI_SETMAINSELECTION, nsel);
			break;
		}
	}
}

int CEditorCtrl::GetLineOnScreen()
{
	return (int)DoCommand(SCI_LINESONSCREEN);
}

void CEditorCtrl::SetLineCenterBackwardDisplay(int lLine)
{
	if (lLine < 0) return;
	int linesOnScreen = GetLineOnScreen();
	int firstLineVisible = GetFirstVisibleLine();
	if (firstLineVisible + 1 >= lLine)
	{
		linesOnScreen = linesOnScreen - 2;
		int start = lLine - (linesOnScreen / 2);
		SetFirstVisibleLine(start);
	}
}

namespace // File IO
{
	wchar_t WideCharSwap(wchar_t nValue)
	{
		return (((nValue >> 8)) | (nValue << 8));
	}

	UINT64 WordSwapBytes(UINT64 nValue)
	{
		return ((nValue & 0xff00ff00ff00ff) << 8) | ((nValue >> 8) & 0xff00ff00ff00ff); // swap BYTESs in WORDs
	}

	UINT32 DwordSwapBytes(UINT32 nValue)
	{
		UINT32 nRet = (nValue << 16) | (nValue >> 16);                     // swap WORDs
		nRet = ((nRet & 0xff00ff) << 8) | ((nRet >> 8) & 0xff00ff); // swap BYTESs in WORDs
		return nRet;
	}

	UINT64 DwordSwapBytes(UINT64 nValue)
	{
		UINT64 nRet = ((nValue & 0xffff0000ffffL) << 16) | ((nValue >> 16) & 0xffff0000ffffL); // swap WORDs in DWORDs
		nRet = ((nRet & 0xff00ff00ff00ff) << 8) | ((nRet >> 8) & 0xff00ff00ff00ff);     // swap BYTESs in WORDs
		return nRet;
	}

	EOLFormat SenseEOLFormat(const char* data, DWORD len)
	{
		for (size_t i = 0; i < len; i++)
		{
			if (data[i] == '\r')
			{
				if (i + 1 < len && data[i + 1] == '\n')
					return EOLFormat::Win_Format;
				else
					return EOLFormat::Mac_Format;
			}
			if (data[i] == '\n')
				return EOLFormat::Unix_Format;
		}
		return EOLFormat::Unknown_Format;
	}

	void CheckForTabs(const char* data, DWORD len, TabSpace& tabSpace)
	{
		if (tabSpace != TabSpace::Tabs)
		{
			for (DWORD i = 0; i < len; ++i)
			{
				if (data[i] == '\t')
				{
					tabSpace = TabSpace::Tabs;
					break;
				}
			}
		}
	}

	void ReadUtf8Buffer(ILoader& loader, bool hasBOM, bool bFirst, DWORD& lenFile, char* data, EOLFormat& eolFormat, TabSpace& tabSpace)
	{
		char* pData = data;
		// Nothing to convert, just pass it to Scintilla
		if (bFirst && hasBOM)
		{
			pData += 3;
			lenFile -= 3;
		}
		if (eolFormat == EOLFormat::Unknown_Format)
			eolFormat = SenseEOLFormat(pData, lenFile);
		if (tabSpace != TabSpace::Tabs)
			CheckForTabs(pData, lenFile, tabSpace);
		loader.AddData(pData, lenFile);
		if (bFirst && hasBOM)
			lenFile += 3;
	}

	void ReadUtf16LeBuffer(ILoader& loader, bool hasBOM, bool bFirst, DWORD& lenFile,
		char* data, char* charBuf, int charBufSize, wchar_t* wideBuf, EOLFormat& eolFormat, TabSpace& tabSpace)
	{
		char* pData = data;
		if (bFirst && hasBOM)
		{
			pData += 2;
			lenFile -= 2;
		}
		memcpy(wideBuf, pData, lenFile);
		int charLen = WideCharToMultiByte(TF_UTF8, 0, wideBuf, lenFile / 2, charBuf, charBufSize, nullptr, nullptr);
		if (eolFormat == EOLFormat::Unknown_Format)
			eolFormat = SenseEOLFormat(charBuf, charLen);
		if (tabSpace != TabSpace::Tabs)
			CheckForTabs(charBuf, charLen, tabSpace);
		loader.AddData(charBuf, charLen);
		if (bFirst && hasBOM)
			lenFile += 2;
	}

	void ReadUtf16BeBuffer(ILoader& loader, bool hasBOM, bool bFirst, DWORD& lenFile, char* data, char* charBuf, int charBufSize, wchar_t* wideBuf, EOLFormat& eolFormat, TabSpace& tabSpace)
	{
		char* pData = data;
		if (bFirst && hasBOM)
		{
			pData += 2;
			lenFile -= 2;
		}
		memcpy(wideBuf, pData, lenFile);
		// make in place WORD BYTEs swap
		UINT64* pQw = reinterpret_cast<UINT64*>(wideBuf);
		int     nQWords = lenFile / 8;
		for (int nQWord = 0; nQWord < nQWords; nQWord++)
			pQw[nQWord] = WordSwapBytes(pQw[nQWord]);

		wchar_t* pW = reinterpret_cast<wchar_t*>(pQw);
		int      nWords = lenFile / 2;
		for (int nWord = nQWords * 4; nWord < nWords; nWord++)
			pW[nWord] = WideCharSwap(pW[nWord]);

		int charLen = WideCharToMultiByte(TF_UTF8, 0, wideBuf, lenFile / 2, charBuf, charBufSize, nullptr, nullptr);
		if (eolFormat == EOLFormat::Unknown_Format)
			eolFormat = SenseEOLFormat(charBuf, charLen);
		if (tabSpace != TabSpace::Tabs)
			CheckForTabs(charBuf, charLen, tabSpace);
		loader.AddData(charBuf, charLen);
		if (bFirst && hasBOM)
			lenFile += 2;
	}

	void ReadUtf32BeBuffer(DWORD lenFile, char* data)
	{
		UINT64* p64 = reinterpret_cast<UINT64*>(data);
		int     nQWords = lenFile / 8;
		for (int nQWord = 0; nQWord < nQWords; nQWord++)
			p64[nQWord] = DwordSwapBytes(p64[nQWord]);

		UINT32* p32 = reinterpret_cast<UINT32*>(p64);
		int     nDWords = lenFile / 4;
		for (int nDword = nQWords * 2; nDword < nDWords; nDword++)
			p32[nDword] = DwordSwapBytes(p32[nDword]);
	}

	void ReadUtf32LeBuffer(ILoader& loader, bool hasBOM, bool bFirst, DWORD& lenFile, char* data, char* charBuf, int charBufSize, wchar_t* wideBuf, EOLFormat& eolFormat, TabSpace& tabSpace)
	{
		char* pData = data;
		if (bFirst && hasBOM)
		{
			pData += 4;
			lenFile -= 4;
		}
		// UTF32 have four bytes per char
		int     nReadChars = lenFile / 4;
		UINT32* p32 = reinterpret_cast<UINT32*>(pData);

		// fill buffer
		wchar_t* pOut = static_cast<wchar_t*>(wideBuf);
		for (int i = 0; i < nReadChars; ++i, ++pOut)
		{
			UINT32 zChar = p32[i];
			if (zChar >= 0x110000)
			{
				*pOut = 0xfffd; // ? mark
			}
			else if (zChar >= 0x10000)
			{
				zChar -= 0x10000;
				pOut[0] = ((zChar >> 10) & 0x3ff) | 0xd800; // lead surrogate
				pOut[1] = (zChar & 0x7ff) | 0xdc00;         // trail surrogate
				pOut++;
			}
			else
			{
				*pOut = static_cast<wchar_t>(zChar);
			}
		}
		int charLen = WideCharToMultiByte(TF_UTF8, 0, wideBuf, nReadChars, charBuf, charBufSize, nullptr, nullptr);
		if (eolFormat == EOLFormat::Unknown_Format)
			eolFormat = SenseEOLFormat(charBuf, charLen);
		if (tabSpace != TabSpace::Tabs)
			CheckForTabs(charBuf, charLen, tabSpace);
		loader.AddData(charBuf, charLen);
		if (bFirst && hasBOM)
			lenFile += 4;
	}

	void ReadEncodingBuffer(ILoader& loader, int encoding, DWORD lenFile, int& incompleteMultiByteChar, char* data, char* charBuf, int charBufSize, wchar_t* wideBuf, EOLFormat& eolFormat, TabSpace& tabSpace)
	{
		// For other encodings, ask system if there are any invalid characters; note that it will
		// not correctly know if the last character is cut when there are invalid characters inside the text
		int wideLen = MultiByteToWideChar(encoding, (lenFile == -1) ? 0 : MB_ERR_INVALID_CHARS, data, lenFile, nullptr, 0);
		if (wideLen == 0 && GetLastError() == ERROR_NO_UNICODE_TRANSLATION)
		{
			// Test without last byte
			if (lenFile > 1)
				wideLen = MultiByteToWideChar(encoding, MB_ERR_INVALID_CHARS, data, lenFile - 1, nullptr, 0);
			if (wideLen == 0)
			{
				// don't have to check that the error is still ERROR_NO_UNICODE_TRANSLATION,
				// since only the length parameter changed

				// TODO: should warn user about incorrect loading due to invalid characters
				// We still load the file, but the system will either strip or replace invalid characters
				// (including the last character, if cut in half)
				wideLen = MultiByteToWideChar(encoding, 0, data, lenFile, nullptr, 0);
			}
			else
			{
				// We found a valid text by removing one byte.
				incompleteMultiByteChar = 1;
			}
		}
		if (wideLen > 0)
		{
			MultiByteToWideChar(encoding, 0, data, lenFile - incompleteMultiByteChar, wideBuf, wideLen);
			int charLen = WideCharToMultiByte(TF_UTF8, 0, wideBuf, wideLen, charBuf, charBufSize, nullptr, nullptr);
			if (eolFormat == EOLFormat::Unknown_Format)
				eolFormat = SenseEOLFormat(charBuf, charLen);
			if (tabSpace != TabSpace::Tabs)
				CheckForTabs(charBuf, charLen, tabSpace);
			loader.AddData(charBuf, charLen);
		}
	}

	bool SaveAsUtf16(char* buf, size_t lengthDoc, CAutoFile& hFile, std::wstring& err, int _encoding, bool _bHasBOM, int _encodingSaving, bool _bHasBOMSaving)
	{
		constexpr int writeWideBufSize = WriteBlockSize * 2;
		auto          wideBuf = std::make_unique<wchar_t[]>(writeWideBufSize);
		err.clear();
		DWORD bytesWritten = 0;

		auto encoding = _encoding;
		auto hasBOM = _bHasBOM;
		if (_encodingSaving != TF_INT)
		{
			encoding = _encodingSaving;
			hasBOM = _bHasBOMSaving;
		}

		if (hasBOM)
		{
			BOOL result = FALSE;
			if (encoding == 1200)
				result = WriteFile(hFile, "\xFF\xFE", 2, &bytesWritten, nullptr);
			else
				result = WriteFile(hFile, "\xFE\xFF", 2, &bytesWritten, nullptr);
			if (!result || bytesWritten != 2)
			{
				err = OSUtils::GetLastErrorAsString();
				return false;
			}
		}
		char* writeBuf = buf;
		do
		{
			int charStart = UTF8Helper::characterStart(writeBuf, static_cast<int>(min(WriteBlockSize, lengthDoc)));
			int wideLen = MultiByteToWideChar(TF_UTF8, 0, writeBuf, charStart, wideBuf.get(), writeWideBufSize);
			if (encoding == 1201)
			{
				UINT64* pQw = reinterpret_cast<UINT64*>(wideBuf.get());
				int     nQWords = wideLen / 4;
				for (int nQWord = 0; nQWord < nQWords; nQWord++)
					pQw[nQWord] = WordSwapBytes(pQw[nQWord]);
				auto* pW = reinterpret_cast<wchar_t*>(pQw);
				int   nWords = wideLen;
				for (int nWord = nQWords * 4; nWord < nWords; nWord++)
					pW[nWord] = WideCharSwap(pW[nWord]);
			}
			if (!WriteFile(hFile, wideBuf.get(), wideLen * 2, &bytesWritten, nullptr) || wideLen != static_cast<int>(bytesWritten / 2))
			{
				err = OSUtils::GetLastErrorAsString();
				return false;
			}
			writeBuf += charStart;
			lengthDoc -= charStart;
		} while (lengthDoc > 0);
		return true;
	}

	bool SaveAsUtf32(char* buf, size_t lengthDoc, CAutoFile& hFile, std::wstring& err, int _encoding, bool _bHasBOM, int _encodingSaving, bool _bHasBOMSaving)
	{
		constexpr int writeWideBufSize = WriteBlockSize * 2;
		auto          writeWideBuf = std::make_unique<wchar_t[]>(writeWideBufSize);
		auto          writeWide32Buf = std::make_unique<wchar_t[]>(writeWideBufSize * 2);
		DWORD         bytesWritten = 0;
		BOOL          result = FALSE;

		auto encoding = _encoding;
		if (_encodingSaving != TF_INT)
			encoding = _encodingSaving;

		if (encoding == 12000)
			result = WriteFile(hFile, "\xFF\xFE\0\0", 4, &bytesWritten, nullptr);
		else
			result = WriteFile(hFile, "\0\0\xFE\xFF", 4, &bytesWritten, nullptr);
		if (!result || bytesWritten != 4)
		{
			err = OSUtils::GetLastErrorAsString();
			return false;
		}
		char* writeBuf = buf;
		do
		{
			int charStart = UTF8Helper::characterStart(writeBuf, static_cast<int>(min(WriteBlockSize, lengthDoc)));
			int wideLen = MultiByteToWideChar(TF_UTF8, 0, writeBuf, charStart, writeWideBuf.get(), writeWideBufSize);

			LPCWSTR pIn = static_cast<LPCWSTR>(writeWideBuf.get());
			UINT32* pOut = reinterpret_cast<UINT32*>(writeWide32Buf.get());
			int     nOutDWord = 0;
			for (int nInWord = 0; nInWord < wideLen; nInWord++, nOutDWord++)
			{
				UINT32 zChar = pIn[nInWord];
				if ((zChar & 0xfc00) == 0xd800) // lead surrogate
				{
					if (nInWord + 1 < wideLen && (pIn[nInWord + 1] & 0xfc00) == 0xdc00) // trail surrogate follows
						zChar = 0x10000 + ((zChar & 0x3ff) << 10) + (pIn[++nInWord] & 0x3ff);
					else
						zChar = 0xfffd; // ? mark
				}
				else if ((zChar & 0xfc00) == 0xdc00) // trail surrogate without lead
					zChar = 0xfffd;                  // ? mark
				pOut[nOutDWord] = zChar;
			}

			if (encoding == 12001)
			{
				UINT64* p64 = reinterpret_cast<UINT64*>(writeWide32Buf.get());
				int     nQWords = wideLen / 2;
				for (int nQWord = 0; nQWord < nQWords; nQWord++)
					p64[nQWord] = DwordSwapBytes(p64[nQWord]);

				UINT32* p32 = reinterpret_cast<UINT32*>(p64);
				int     nDWords = wideLen;
				for (int nDword = nQWords * 2; nDword < nDWords; nDword++)
					p32[nDword] = DwordSwapBytes(p32[nDword]);
			}
			if (!WriteFile(hFile, writeWide32Buf.get(), wideLen * 4, &bytesWritten, nullptr) || wideLen != static_cast<int>(bytesWritten / 4))
			{
				err = OSUtils::GetLastErrorAsString();
				return false;
			}
			writeBuf += charStart;
			lengthDoc -= charStart;
		} while (lengthDoc > 0);
		return true;
	}

	bool SaveAsUtf8(char* buf, size_t lengthDoc, CAutoFile& hFile, std::wstring& err, bool _bHasBOM, int _encodingSaving, bool _bHasBOMSaving)
	{
		// UTF8: save the buffer as it is
		DWORD bytesWritten = 0;
		auto  hasBOM = _bHasBOM;
		if (_encodingSaving != TF_INT)
			hasBOM = _bHasBOMSaving;

		if (hasBOM)
		{
			if (!WriteFile(hFile, "\xEF\xBB\xBF", 3, &bytesWritten, nullptr) || bytesWritten != 3)
			{
				err = OSUtils::GetLastErrorAsString();
				return false;
			}
		}
		do
		{
			DWORD writeLen = static_cast<DWORD>(min(WriteBlockSize, lengthDoc));
			if (!WriteFile(hFile, buf, writeLen, &bytesWritten, nullptr))
			{
				err = OSUtils::GetLastErrorAsString();
				return false;
			}
			lengthDoc -= writeLen;
			buf += writeLen;
		} while (lengthDoc > 0);
		return true;
	}

	bool SaveAsOther(char* buf, size_t lengthDoc, CAutoFile& hFile, std::wstring& err
		, int _encoding, bool _bHasBOM,
		int _encodingSaving, bool _bHasBOMSaving)
	{
		constexpr int wideBufSize = WriteBlockSize * 2;
		auto          wideBuf = std::make_unique<wchar_t[]>(wideBufSize);
		constexpr int charBufSize = wideBufSize * 2;
		auto          charBuf = std::make_unique<char[]>(charBufSize);
		// first convert to wide char, then to the requested codepage
		DWORD bytesWritten = 0;
		auto  encoding = _encoding;
		if (_encodingSaving != TF_INT)
			encoding = _encodingSaving;

		char* writeBuf = buf;
		do
		{
			int  charStart = UTF8Helper::characterStart(writeBuf, static_cast<int>(min(WriteBlockSize, lengthDoc)));
			int  wideLen = MultiByteToWideChar(TF_UTF8, 0, writeBuf, charStart, wideBuf.get(), wideBufSize);
			BOOL usedDefaultChar = FALSE;
			int  charLen = WideCharToMultiByte(encoding < 0 ? CP_ACP : encoding, 0, wideBuf.get(), wideLen, charBuf.get(), charBufSize, nullptr, & usedDefaultChar);
			if (usedDefaultChar && _encodingSaving == -1)
			{
				// stream could not be properly converted to ANSI, write it 'as is'
				if (!WriteFile(hFile, writeBuf, charStart, &bytesWritten, nullptr) || charLen != static_cast<int>(bytesWritten))
				{
					err = OSUtils::GetLastErrorAsString();
					return false;
				}
			}
			else
			{
				if (!WriteFile(hFile, charBuf.get(), charLen, &bytesWritten, nullptr) || charLen != static_cast<int>(bytesWritten))
				{
					err = OSUtils::GetLastErrorAsString();
					return false;
				}
			}
			writeBuf += charStart;
			lengthDoc -= charStart;
		} while (lengthDoc > 0);
		return true;
	}
}  // File IO

void CEditorCtrl::DetectFileLexer(const CString& strFilePath)
{
	int nIndex = strFilePath.ReverseFind('.');
	if (nIndex != -1)
	{
		m_strFileExtension = strFilePath.Right(strFilePath.GetLength() - nIndex - 1).Trim();
	}
	else
	{
		m_strFileExtension.Empty();
	}
	m_strLexerName = GetLexerNameFromExtension(m_strFileExtension);
}

void CEditorCtrl::SetTabSettings(TabSpace ts)
{
	DoCommand(SCI_SETTABWIDTH, 4);
	if (ts == TabSpace::Default)
		DoCommand(SCI_SETUSETABS, 1);
	else
		DoCommand(SCI_SETUSETABS, ts == TabSpace::Tabs ? 1 : 0);
	DoCommand(SCI_SETBACKSPACEUNINDENTS, 1);
	DoCommand(SCI_SETTABINDENTS, 1);
	DoCommand(SCI_SETTABDRAWMODE, 1);
}

BOOL CEditorCtrl::LoadFile(const CString& strFilePath, int nLoadEncoding, BOOL bCreateIfMissing)
{
	if (!PathFileExists(strFilePath))
	{
		UndoRedoRecordingStart();
		return FALSE;
	}
	auto startMeasureTime = OSUtils::StartBenchmark();

	DetectFileLexer(strFilePath);

	CAutoFile hFile = CreateFile(strFilePath, GENERIC_READ, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, bCreateIfMissing ? CREATE_NEW : OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (!hFile)
	{
		// Capture the access denied error, while it's valid.
		return FALSE;
	}
	BY_HANDLE_FILE_INFORMATION fi;
	if (!GetFileInformationByHandle(hFile, &fi))
	{
		return FALSE;
	}
	m_bIsFileHasROAttribute = (fi.dwFileAttributes & (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM)) != 0;
	m_strFilePath = strFilePath;
	unsigned __int64 fileSize = static_cast<__int64>(fi.nFileSizeHigh) << 32 | fi.nFileSizeLow;
	// add more room for Scintilla (usually 1/6 more for editing)
	unsigned __int64 bufferSizeRequested = fileSize + min(1 << 20, fileSize / 6);

	// Setup our scratch scintilla control to load the data
	DoCommand(SCI_SETSTATUS, SC_STATUS_OK); // reset error status
	DoCommand(SCI_SETDOCPOINTER, 0, 0);
	m_bIsReadOnlyEditor = DoCommand(SCI_GETREADONLY) != 0;
	if (m_bIsReadOnlyEditor)
		DoCommand(SCI_SETREADONLY, false); // we need write access
	DoCommand(SCI_SETUNDOCOLLECTION, 0);
	DoCommand(SCI_CLEARALL);
	DoCommand(SCI_SETCODEPAGE, TF_UTF8); // default codepage is utf-8
	int docOptions = SC_DOCUMENTOPTION_DEFAULT;
	if (bufferSizeRequested > INT_MAX)
		docOptions = SC_DOCUMENTOPTION_TEXT_LARGE | SC_DOCUMENTOPTION_STYLES_NONE;
	ILoader* pdocLoad = reinterpret_cast<ILoader*>(DoCommand(SCI_CREATELOADER, static_cast<uptr_t>(bufferSizeRequested), docOptions));
	if (pdocLoad == nullptr)
	{
		return FALSE;
	}
	auto& loader = *pdocLoad;

	UndoRedoRecordingStop();

	DWORD lenFile = 0;
	int   incompleteMultiByteChar = 0;
	bool  bFirst = true;
	bool  preferUtf8 = false;
	bool  inconclusive = false;
	bool  encodingSet = nLoadEncoding != TF_INT;

	int   skip = 0;
	do
	{
		if (!ReadFile(hFile, m_data + incompleteMultiByteChar, ReadBlockSize - incompleteMultiByteChar, &lenFile, nullptr))
			lenFile = 0;
		else
			lenFile += incompleteMultiByteChar;
		incompleteMultiByteChar = 0;

		if ((!encodingSet) || (inconclusive && nLoadEncoding == CP_ACP))
		{
			if (AppSettingMgr.m_bEnableAutoDetectCodePage)
			{
				std::unique_ptr<TextFile> pReader = std::make_unique<TextFile>();
				long lSizeBuffer = 0;
				std::unique_ptr<char> pBufferFileContent(PathUtils::OpenFileToBuffer(strFilePath, &lSizeBuffer));
				nLoadEncoding = pReader->GuessCodepage(pBufferFileContent.get(), lSizeBuffer, m_strEncodingName);
				if (nLoadEncoding == TF_INT)
				{
					nLoadEncoding = GetCodepageFromBuf(m_data + skip, lenFile - skip, m_bHasBOM, inconclusive, skip);
				}
			}
			else
			{
				nLoadEncoding = GetCodepageFromBuf(m_data + skip, lenFile - skip, m_bHasBOM, inconclusive, skip);
			}
			if (inconclusive && nLoadEncoding == CP_ACP)
			{
				nLoadEncoding = TF_UTF8;
			}
		}
		encodingSet = true;

		m_encodingLoading = nLoadEncoding;

		switch (nLoadEncoding)
		{
		case TF_INT:
		case TF_UTF8:
			ReadUtf8Buffer(loader, m_bHasBOM, bFirst, lenFile, m_data, m_format, m_tabSpace);
			break;
		case TF_UTF16LE: // UTF16_LE
			ReadUtf16LeBuffer(loader, m_bHasBOM, bFirst, lenFile, m_data, m_charBuf.get(), m_charBufSize, m_wideBuf.get(), m_format, m_tabSpace);
			break;
		case TF_UTF16BE: // UTF16_BE
			ReadUtf16BeBuffer(loader, m_bHasBOM, bFirst, lenFile, m_data, m_charBuf.get(), m_charBufSize, m_wideBuf.get(), m_format, m_tabSpace);
			break;
		case TF_UTF32BE: // UTF32_BE
			ReadUtf32BeBuffer(lenFile, m_data);
		case TF_UTF32LE: // UTF32_LE
			ReadUtf32LeBuffer(loader, m_bHasBOM, bFirst, lenFile, m_data, m_charBuf.get(), m_charBufSize, m_wideBuf.get(), m_format, m_tabSpace);
			break;
		default:
			ReadEncodingBuffer(loader, nLoadEncoding, lenFile, incompleteMultiByteChar, m_data, m_charBuf.get(), m_charBufSize, m_wideBuf.get(), m_format, m_tabSpace);
			break;
		}

		if (incompleteMultiByteChar != 0) // copy bytes to next buffer
			memcpy(m_data, m_data + ReadBlockSize - incompleteMultiByteChar, incompleteMultiByteChar);

		bFirst = false;
	} while (lenFile == ReadBlockSize);

	if (preferUtf8 && inconclusive && m_encodingLoading == CP_ACP)
		m_encodingLoading = TF_UTF8;

	if (m_format == EOLFormat::Unknown_Format)
		m_format = EOLFormat::Win_Format;

	uptr_t loadedDoc = reinterpret_cast<sptr_t>(pdocLoad->ConvertToDocument()); // loadedDoc has reference count 1
	DoCommand(SCI_SETDOCPOINTER, 0, loadedDoc); // doc in scratch has reference count 2 (loadedDoc 1, added one)
	DoCommand(SCI_SETUNDOCOLLECTION, 1);
	DoCommand(SCI_EMPTYUNDOBUFFER);
	DoCommand(SCI_SETSAVEPOINT);

	// Now the horizontal scroll bars should only appear if anydisplayed lines exceed the width of the window
	DoCommand(SCI_SETSCROLLWIDTH, 1);

	switch (m_format)
	{
	case EOLFormat::Win_Format:
		SetEOLFile(SC_EOL_CRLF);
		break;
	case EOLFormat::Unix_Format:
		SetEOLFile(SC_EOL_LF);
		break;
	case EOLFormat::Mac_Format:
		SetEOLFile(SC_EOL_CR);
		break;
	default:
		break;
	}

	if (m_bIsReadOnlyEditor || m_bIsFileHasROAttribute || m_bIsWriteProtected)
	{
		DoCommand(SCI_SETREADONLY, true);
		m_bIsReadOnlyEditor = true;
	}

	m_DocumentID = DoCommand(SCI_GETDOCPOINTER); // save this document ID for release later

	UndoRedoRecordingStart();

	if (!AppUtils::GetVinaTextApp()->m_bIsReloadByPreviewMode && !AppUtils::GetVinaTextApp()->m_bIsReloadDocument)
	{
		CString strMsg = AfxCStringFormat(_T("> [Load File] %s - timelapse: "), strFilePath);
		OSUtils::LogStopBenchmark(LOG_TARGET::MESSAGE_WINDOW, startMeasureTime, strMsg);
	}
	return TRUE;
}

BOOL CEditorCtrl::SaveFileWithEncoding(const CString& strFilePath)
{
	if (strFilePath.IsEmpty())
		return FALSE;
	CAutoFile hFile = CreateFile(strFilePath, GENERIC_WRITE, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (!hFile.IsValid())
	{
		return FALSE;
	}

	size_t lengthDoc = DoCommand(SCI_GETLENGTH);
	// get characters directly from Scintilla buffer
	char* buf = reinterpret_cast<char*>(DoCommand(SCI_GETCHARACTERPOINTER));
	bool         bRetSave = FALSE;
	std::wstring err;
	auto         encoding = m_encodingLoading;
	if (m_encodingSaving != TF_INT)
		encoding = m_encodingSaving;

	switch (encoding)
	{
	case TF_UTF8:
	case TF_INT:
		bRetSave = SaveAsUtf8(buf, lengthDoc, hFile, err, m_bHasBOM, m_encodingSaving, m_bHasBOMSaving);
		break;
	case TF_UTF16LE: // UTF16_LE
	case TF_UTF16BE: // UTF16_BE
		bRetSave = SaveAsUtf16(buf, lengthDoc, hFile, err, m_encodingLoading, m_bHasBOM, m_encodingSaving, m_bHasBOMSaving);
		break;
	case TF_UTF32LE: // UTF32_LE
	case TF_UTF32BE: // UTF32_BE
		bRetSave = SaveAsUtf32(buf, lengthDoc, hFile, err, m_encodingLoading, m_bHasBOM, m_encodingSaving, m_bHasBOMSaving);
		break;
	default:
		bRetSave = SaveAsOther(buf, lengthDoc, hFile, err, m_encodingLoading, m_bHasBOM, m_encodingSaving, m_bHasBOMSaving);
		break;
	}
	if (!bRetSave)
		LOG_OUTPUT_MESSAGE_FORMAT(_T("[Save File Error] %s %s"), strFilePath, err.c_str());
	return TRUE;
}

BOOL CEditorCtrl::SaveFile(const CString& strFilePath)
{
	if (strFilePath.IsEmpty())
		return FALSE;

	auto startMeasureTime = OSUtils::StartBenchmark();

	m_strFilePath = strFilePath;

	DetectFileLexer(strFilePath);

	DWORD attributes = INVALID_FILE_ATTRIBUTES;
	DWORD err = 0;
	// when opening files, always 'share' as much as possible to reduce problems with virus scanners
	CAutoFile hFile = CreateFile(strFilePath, GENERIC_WRITE, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (!hFile.IsValid())
		err = GetLastError();
	// If the file can't be created, check if the file attributes are the reason we can't open
	// the file for writing. If so, remove the offending ones, we'll re-apply them later.
	// If we can't get the attributes or they aren't the ones we thought were causing the
	// problem or we can't remove them; fall through and go with our original error.
	if (!hFile.IsValid() && err == ERROR_ACCESS_DENIED)
	{
		DWORD undesiredAttributes = FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM;
		attributes = GetFileAttributes(strFilePath);
		if (attributes != INVALID_FILE_ATTRIBUTES && (attributes & undesiredAttributes) != 0)
		{
			DWORD desiredAttributes = attributes & ~undesiredAttributes;
			if (SetFileAttributes(strFilePath, desiredAttributes))
			{
				hFile = CreateFile(strFilePath, GENERIC_WRITE, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
			}
		}
	}

	if (!hFile.IsValid())
	{
		return FALSE;
	}

	if (SaveFileWithEncoding(strFilePath))
	{
		DoCommand(SCI_SETSAVEPOINT);
		if (m_encodingSaving != TF_INT)
		{
			m_encodingLoading = m_encodingSaving;
			m_encodingSaving = -1;
			m_bHasBOM = m_bHasBOMSaving;
			m_bHasBOMSaving = false;
		}
	}
	if (attributes != INVALID_FILE_ATTRIBUTES)
	{
		// reset the file attributes after saving
		SetFileAttributes(strFilePath, attributes);
	}

	CString strMsg;
	if (AppUtils::GetVinaTextApp()->m_bIsOpenInAdminMode)
	{
		strMsg = AfxCStringFormat(_T("> [Save File Administrator] %s - timelapse: "), strFilePath);
	}
	else
	{
		strMsg = AfxCStringFormat(_T("> [Save File] %s - timelapse: "), strFilePath);
	}
	OSUtils::LogStopBenchmark(LOG_TARGET::MESSAGE_WINDOW, startMeasureTime, strMsg);

	return TRUE;
}

#if 0
BOOL CEditorCtrl::LoadDataFileToEditor(const CString& szFile, CString& m_strLexerNameNameOut)
{
	if (!PathFileExists(szFile))
	{
		UndoRedoRecordingStart();
		return FALSE;
	}

	auto startMeasureTime = OSUtils::StartBenchmark();
	std::unique_ptr<TextFile> tf_in = std::make_unique<TextFile>();

	m_strFilePath = szFile;

	int nIndex = szFile.ReverseFind('.');
	if (nIndex != -1)
	{
		m_strFileExtension = szFile.Right(szFile.GetLength() - nIndex - 1).Trim();
	}
	else
	{
		m_strFileExtension.Empty();
	}

	m_strLexerName = GetLexerNameFromExtension(m_strFileExtension);
	m_strLexerNameNameOut = m_strLexerName;

	SetEOLFile(SC_EOL_CR);

	CString strEditorText;
	// set user codepage...
	if (AppUtils::GetVinaTextApp()->m_bUseUserCodePage)
	{
		m_encodingLoading = AppUtils::GetVinaTextApp()->m_nUserCodePage;
		m_strEncodingName = AppUtils::GetVinaTextApp()->m_strUserCodePageName;
	}
	else // fake reading, auto detect codepage... 
	{
		long lSize = 0;
		char* bufferFileContent = PathUtils::OpenFileToBuffer(szFile, &lSize);
		m_encodingLoading = tf_in->GuessCodepage(bufferFileContent, lSize, m_strEncodingName);
		if (m_encodingLoading == CP_INVALID)
		{
			m_encodingLoading = CP_ACP; // default to ANSI code page
			m_strEncodingName = _T("ANSI");
		}
		DELETE_POINTER_C(bufferFileContent);
	}
	tf_in->SetCodePage(m_encodingLoading);

	// save original file encoding...
	if (m_encodingLoading != TF_UTF8)
	{
		AppUtils::GetVinaTextApp()->m_UserEncoding = TF_ANSI;
	}
	else if (m_encodingLoading == TF_UTF8)
	{
		AppUtils::GetVinaTextApp()->m_UserEncoding = TF_UTF8;
		m_strEncodingName = _T("UTF-8");
	}
	int result = tf_in->Open(szFile, TF_READ, AppUtils::GetVinaTextApp()->m_UserEncoding);
	if (result < 0)
	{
		TCHAR* errmsg = GetLastErrorString();
		LOG_OUTPUT_MESSAGE_FORMAT(_T("%s\n"), errmsg);
		return FALSE;
	}

	// real reading, load file data to editor...
	BOOL bLinuxFileDetectFlag = FALSE;
	TCHAR* lineBuffer = NULL;
	while (1)
	{
		result = tf_in->ReadLine(NULL, &lineBuffer);
		if (result < 0)
		{
			if (result == TF_ERROR) // else TF_EOF
			{
				TCHAR* errmsg = GetLastErrorString();
				LOG_OUTPUT_MESSAGE_FORMAT(_T("%s\n"), errmsg);
			}
			if (bLinuxFileDetectFlag)
			{
				strEditorText = strEditorText.Mid(0, strEditorText.GetLength() - 1);
			}
			break;
		}
		else
		{
			if (sizeof(lineBuffer) > 1 && lineBuffer[_tcslen(lineBuffer) - 1] != '\r')
			{
				bLinuxFileDetectFlag = TRUE;
				strEditorText += lineBuffer;
				strEditorText += EDITOR_NEW_LINE_CR;
			}
			else
			{
				strEditorText += lineBuffer;
			}
		}
	}
	free_block(lineBuffer); lineBuffer = NULL;
	tf_in->Close();

	UndoRedoRecordingStop();
	SetTextToEditor(strEditorText);
	UndoRedoRecordingStart();

	if (!AppUtils::GetVinaTextApp()->m_bIsReloadByPreviewMode)
	{
		CString strMsg = AfxCStringFormat(_T("> [Load File] %s - timelapse: "), szFile);
		OSUtils::LogStopBenchmark(LOG_TARGET::MESSAGE_WINDOW, startMeasureTime, strMsg);
	}

	DoCommand(SCI_SETSAVEPOINT, 0, 0);

	return TRUE;
}

BOOL CEditorCtrl::SaveEditorDataToFile(const CString& szFile, CString& m_strLexerNameNameOut)
{
	if (szFile.IsEmpty())
	{
		return FALSE;
	}
	m_strFilePath = szFile;

	int nIndex = szFile.ReverseFind('.');
	if (nIndex != -1)
	{
		m_strFileExtension = szFile.Right(szFile.GetLength() - nIndex - 1).Trim();
	}
	else
	{
		m_strFileExtension.Empty();
	}
	m_strLexerName = GetLexerNameFromExtension(m_strFileExtension);
	m_strLexerNameNameOut = m_strLexerName;

	auto startMeasureTime = OSUtils::StartBenchmark();
	std::unique_ptr<TextFile> tf_out = std::make_unique<TextFile>();
	int result = tf_out->Open(szFile, TF_WRITE, AppUtils::GetVinaTextApp()->m_UserEncoding);
	if (result < 0)
	{
		TCHAR* errmsg = GetLastErrorString();
		LOG_OUTPUT_MESSAGE_FORMAT(_T("%s\n"), errmsg);
		return FALSE;
	}

	// set codepage...
	if (AppUtils::GetVinaTextApp()->m_bUseUserCodePage)
	{
		m_encodingLoading = AppUtils::GetVinaTextApp()->m_nUserCodePage;
		m_strEncodingName = AppUtils::GetVinaTextApp()->m_strUserCodePageName;
	}
	else
	{
		// use original file encoding...
		if (AppUtils::GetVinaTextApp()->m_UserEncoding == TF_ANSI)
		{
			m_encodingLoading = CP_ACP;
			m_strEncodingName = _T("ANSI");
		}
		else if (AppUtils::GetVinaTextApp()->m_UserEncoding == TF_UTF8)
		{
			m_encodingLoading = TF_UTF8;
			m_strEncodingName = _T("UTF-8");
		}
	}
	tf_out->SetCodePage(m_encodingLoading);

	for (int i = 0; i < GetLineCount(); ++i)
	{
		CString strLine;
		GetTextFromLine(i + 1, strLine);
		result = tf_out->WriteString(NULL, strLine);
		if (result >= 0 && i != GetLineCount() - 1)
		{
			result = tf_out->WriteChar(NULL, '\n');
		}
		if (result < 0)
		{
			if (result == TF_ERROR) // else TF_EOF
			{
				TCHAR* errmsg = GetLastErrorString();
				LOG_OUTPUT_MESSAGE_FORMAT(_T("%s\n"), errmsg);
			}
			break;
		}
	}
	tf_out->Close();

	CString strMsg = AfxCStringFormat(_T("> [Save File] %s - timelapse: "), szFile);
	OSUtils::LogStopBenchmark(LOG_TARGET::MESSAGE_WINDOW, startMeasureTime, strMsg);

	DoCommand(SCI_SETSAVEPOINT, 0, 0);
	return TRUE;
}
#endif

CString CEditorCtrl::GetLexerNameFromExtension(const CString& szExtension)
{
	int lexerIndex = 0;
	CString pExtension = EditorLanguageDef::arrLangExtensions[lexerIndex];
	while (!pExtension.IsEmpty())
	{
		CLexingParser parser(EditorLanguageDef::arrLangExtensions[lexerIndex], _T("|"));
		while (parser.HasMoreTokens())
		{
			if (parser.Next().CompareNoCase(szExtension) == 0)
			{
				return AppUtils::StdToCString(EditorLanguageDef::arrLexerNames[lexerIndex]);
			}
		}
		lexerIndex++;
		pExtension = EditorLanguageDef::arrLangExtensions[lexerIndex];
	}
	return LEXER_PLAIN_TEXT;
}

void CEditorCtrl::SetFontname(int nStyle, CString szFontname)
{
	char* bufUtf8 = NULL;
	CREATE_BUFFER_FROM_CSTRING(bufUtf8, szFontname)
		if (bufUtf8 != NULL)
		{
			DoCommand(SCI_STYLESETFONT, nStyle, reinterpret_cast<LPARAM>(bufUtf8));
		}
	DELETE_POINTER_CPP_ARRAY(bufUtf8);
}

void CEditorCtrl::SetFontheight(int nStyle, int nHeight)
{
	DoCommand(SCI_STYLESETSIZE, nStyle, (int)nHeight);
}

void CEditorCtrl::SetForeground(int nStyle, COLORREF crForeground)
{
	DoCommand(SCI_STYLESETFORE, nStyle, (int)crForeground);
}

void CEditorCtrl::SetBackground(int nStyle, COLORREF crBackground)
{
	DoCommand(SCI_STYLESETBACK, nStyle, (int)crBackground);
}

void CEditorCtrl::SetBold(int nStyle, BOOL bFlag)
{
	DoCommand(SCI_STYLESETBOLD, nStyle, (int)bFlag);
}

void CEditorCtrl::SetItalic(int nStyle, BOOL bFlag)
{
	DoCommand(SCI_STYLESETITALIC, nStyle, (int)bFlag);
}

void CEditorCtrl::SetUnderline(int nStyle, BOOL bFlag)
{
	DoCommand(SCI_STYLESETUNDERLINE, nStyle, (int)bFlag);
}

BOOL CEditorCtrl::GetOverstrike()
{
	return (BOOL)DoCommand(SCI_GETOVERTYPE, 0, 0);
}

void CEditorCtrl::SetOverstrike(BOOL bOverstrike)
{
	DoCommand(SCI_SETOVERTYPE, bOverstrike, 0);
}

void CEditorCtrl::Refresh()
{
	DoCommand(SCI_COLOURISE, 0, -1);
}

void CEditorCtrl::SetSelectionTextColor(COLORREF color, unsigned int nAlpha)
{
	DoCommand(SCI_SETSELBACK, 1, color);
	DoCommand(SCI_SETSELALPHA, nAlpha);
}

BOOL CEditorCtrl::AddBreakPoint(VINATEXT_SUPPORTED_LANGUAGE language, int lLine, const CString& strFileName)
{
	if (AppUtils::IsLanguageSupportDebugger(language))
	{
		if (lLine < 0)
		{
			return FALSE;
		}
		if (DoCommand(SCI_MARKERADD, lLine - 1, SC_MARKER_ENABLE_BREAKPOINT) != -1)
		{
			VinaTextDebugger.AddBreakPointData(language, lLine, strFileName);
			CString strLangName = AppUtils::GetLanguageStringName(language);
			LOG_BUILD_MESSAGE_FORMAT(_T("Added a %s breakpoint at file %s, line %d."), strLangName, strFileName, lLine);
			return TRUE;
		}
	}
	else
	{
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [Debug Warning] Can not add breakpoint for this file format..."), BasicColors::orange);
	}
	return FALSE;
}

BOOL CEditorCtrl::DeleteBreakPoint(VINATEXT_SUPPORTED_LANGUAGE language, int lLine, const CString& strFileName)
{
	if (lLine < 0)
	{
		return FALSE;
	}
	if (IsLineHasBreakPoint(lLine))
	{
		DoCommand(SCI_MARKERDELETE, lLine - 1, SC_MARKER_ENABLE_BREAKPOINT);
		VinaTextDebugger.RemoveBreakPointDataInLine(language, lLine, strFileName);
		CString strLangName = AppUtils::GetLanguageStringName(language);
		LOG_BUILD_MESSAGE_FORMAT(_T("Removed a %s breakpoint at file %s, line %d."), strLangName, strFileName, lLine);
		return TRUE;
	}
	return FALSE;
}

void CEditorCtrl::DeleteAllBreakPoint()
{
	DoCommand(SCI_MARKERDELETEALL, SC_MARKER_ENABLE_BREAKPOINT);
}

BOOL CEditorCtrl::IsLineHasBreakPoint(int lLine)
{
	int nMarker = static_cast<int>(DoCommand(SCI_MARKERGET, lLine - 1, SC_MARKER_ENABLE_BREAKPOINT));
	// check mask for markerbit 0
	if (nMarker & 0x1)
	{
		return TRUE;
	}
	return FALSE;
}

void CEditorCtrl::FindNextBreakPoint()
{
	int lLine = static_cast<int>(DoCommand(SCI_MARKERNEXT, GetCurrentLine(), SC_SETMARGINTYPE_MAKER));
	if (lLine >= 0)
	{
		GotoLine(lLine + 1);
	}
}

void CEditorCtrl::FindPreviousBreakPoint()
{
	int lLine = static_cast<int>(DoCommand(SCI_MARKERPREVIOUS, GetCurrentLine() - 2, SC_SETMARGINTYPE_MAKER));
	if (lLine >= 0)
	{
		GotoLine(lLine + 1);
	}
}

void CEditorCtrl::AddDisableBreakPoint(int lLine)
{
	if (lLine < 0)
	{
		return;
	}
	DoCommand(SCI_MARKERADD, lLine - 1, SC_MARKER_DISABLE_BREAKPOINT);
}

void CEditorCtrl::DeleteDisableBreakPoint(int lLine)
{
	if (lLine < 0)
	{
		return;
	}
	if (IsLineHasDisableBreakPoint(lLine))
	{
		DoCommand(SCI_MARKERDELETE, lLine - 1, SC_MARKER_DISABLE_BREAKPOINT);
	}
}

void CEditorCtrl::DeleteAllDisableBreakPoint()
{
	DoCommand(SCI_MARKERDELETEALL, SC_MARKER_DISABLE_BREAKPOINT);
}

BOOL CEditorCtrl::IsLineHasDisableBreakPoint(int lLine)
{
	int nMarker = static_cast<int>(DoCommand(SCI_MARKERGET, lLine - 1, SC_MARKER_DISABLE_BREAKPOINT));
	// check mask for markerbit 0
	if (nMarker & 0x1)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CEditorCtrl::HasBreakPoints()
{
	int lLine = static_cast<int>(DoCommand(SCI_MARKERNEXT, 0, SC_SETMARGINTYPE_MAKER));
	if (lLine >= 0)
	{
		return TRUE;
	}
	return FALSE;
}

void CEditorCtrl::AddDebugPointer(int lLine)
{
	if (lLine < 0)
	{
		return;
	}
	DoCommand(SCI_MARKERADD, lLine - 1, SC_MARKER_INSTRUCTION_POINTER);
}

void CEditorCtrl::DeleteDebugPointer(int lLine)
{
	if (lLine < 0)
	{
		return;
	}
	if (IsLineHasDebugPointer(lLine))
	{
		DoCommand(SCI_MARKERDELETE, lLine - 1, SC_MARKER_INSTRUCTION_POINTER);
	}
}

void CEditorCtrl::DeleteAllDebugPointer()
{
	DoCommand(SCI_MARKERDELETEALL, SC_MARKER_INSTRUCTION_POINTER);
}

BOOL CEditorCtrl::IsLineHasDebugPointer(int lLine)
{
	int nMarker = static_cast<int>(DoCommand(SCI_MARKERGET, lLine - 1, SC_MARKER_INSTRUCTION_POINTER));
	// check mask for markerbit 0
	if (nMarker & 0x1)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CEditorCtrl::AddBookMark(int lLine, const CString& strFileName)
{
	if (lLine < 0 || IsLineHasBookMark(lLine))
	{
		return FALSE;
	}
	DoCommand(SCI_MARKERADD, lLine - 1, SC_MARKER_BOOKMARK);
	LOG_OUTPUT_MESSAGE_FORMAT(_T("> Added a bookmark at file %s, line %d."), strFileName, lLine);
	return TRUE;
}

BOOL CEditorCtrl::DeleteBookMark(int lLine, const CString& strFileName)
{
	if (lLine < 0)
	{
		return FALSE;
	}
	DoCommand(SCI_MARKERDELETE, lLine - 1, SC_MARKER_BOOKMARK);
	LOG_OUTPUT_MESSAGE_FORMAT(_T("> Removed a bookmark at file %s, line %d."), strFileName, lLine);
	return TRUE;
}

void CEditorCtrl::DeleteAllBookMark()
{
	DoCommand(SCI_MARKERDELETEALL, SC_MARKER_BOOKMARK);
}

BOOL CEditorCtrl::IsLineHasBookMark(int lLine)
{
	int nMarker = static_cast<int>(DoCommand(SCI_MARKERGET, lLine - 1, SC_MARKER_BOOKMARK));
	// check mask for markerbit 0
	if (nMarker == 8 || nMarker == 9)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CEditorCtrl::HasBookmarks()
{
	int lLine = static_cast<int>(DoCommand(SCI_MARKERNEXT, 0, SC_SETMARGINTYPE_MAKER));
	if (lLine >= 0)
	{
		return TRUE;
	}
	return FALSE;
}

void CEditorCtrl::ReplaceSearchedText(const CString& strText)
{
	if (strText.IsEmpty()) return;
	char* bufUtf8 = NULL;
	CREATE_BUFFER_FROM_CSTRING(bufUtf8, strText)
		if (bufUtf8 != NULL)
		{
			// set target search
			DoCommand(SCI_SETSEARCHFLAGS, m_nSearchflags);
			DoCommand(SCI_TARGETFROMSELECTION, 0, 0);
			if (m_nSearchflags & SCFIND_REGEXP)
			{
				DoCommand(SCI_REPLACETARGETRE, strText.GetLength(), reinterpret_cast<LPARAM>(bufUtf8));
			}
			else
			{
				DoCommand(SCI_REPLACETARGET, strText.GetLength(), reinterpret_cast<LPARAM>(bufUtf8));
			}
		}
	DELETE_POINTER_CPP_ARRAY(bufUtf8);
}

int CEditorCtrl::ReplaceNext(const CString& szFind, const CString& szReplace)
{
	if (szFind.IsEmpty()) return 0;

	char* bufUtf8_szFind = NULL;
	{
		CREATE_BUFFER_FROM_CSTRING(bufUtf8_szFind, szFind)
	}
	if (bufUtf8_szFind == NULL) return 0;

	char* bufUtf8_szReplace = NULL;
	{
		CREATE_BUFFER_FROM_CSTRING(bufUtf8_szReplace, szReplace)
	}
	if (bufUtf8_szReplace == NULL) return 0;

	// set target search
	DoCommand(SCI_SETSEARCHFLAGS, m_nSearchflags);

	int nLen = 0;
	int lStart = GetSelectionStartPosition();
	int lEnd = static_cast<int>(DoCommand(SCI_GETTEXTLENGTH, 0, 0));
	DoCommand(SCI_SETTARGETSTART, lStart);
	DoCommand(SCI_SETTARGETEND, lEnd);
	int lPos = static_cast<int>(DoCommand(SCI_SEARCHINTARGET, szFind.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szFind)));
	if (lPos < lEnd && lPos >= 0)
	{
		if (m_nSearchflags & SCFIND_REGEXP)
		{
			nLen = static_cast<int>(DoCommand(SCI_REPLACETARGETRE, szReplace.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szReplace)));
		}
		else
		{
			nLen = static_cast<int>(DoCommand(SCI_REPLACETARGET, szReplace.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szReplace)));
		}
		DoCommand(SCI_SETTARGETSTART, lPos + nLen);
		DoCommand(SCI_SETTARGETEND, lEnd);
		lPos = static_cast<int>(DoCommand(SCI_SEARCHINTARGET, szFind.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szFind)));
		if (lPos >= 0)
		{
			int lLine = GetLineFromPosition(lPos);
			SetLineCenterKeepView(lLine);
			SetSelectionRange(lPos, lPos + szFind.GetLength());
		}
	}
	if (lPos >= lEnd || lPos < 0)
	{
		lStart = 0;
		lEnd = static_cast<int>(DoCommand(SCI_GETTEXTLENGTH, 0, 0));
		DoCommand(SCI_SETTARGETSTART, lStart, 0);
		DoCommand(SCI_SETTARGETEND, lEnd, 0);
		lPos = static_cast<int>(DoCommand(SCI_SEARCHINTARGET, szFind.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szFind)));
		if (lPos >= 0)
		{
			int lLine = GetLineFromPosition(lPos);
			SetLineCenterKeepView(lLine);
			SetSelectionRange(lPos, lPos + szFind.GetLength());
		}
	}
	DELETE_POINTER_CPP_ARRAY(bufUtf8_szFind);
	DELETE_POINTER_CPP_ARRAY(bufUtf8_szReplace);

	return lPos;
}

int CEditorCtrl::ReplaceAll(const CString& szFind, const CString& szReplace)
{
	if (szFind.IsEmpty()) return 0;

	char* bufUtf8_szFind = NULL;
	{
		CREATE_BUFFER_FROM_CSTRING(bufUtf8_szFind, szFind)
	}
	if (bufUtf8_szFind == NULL) return 0;

	char* bufUtf8_szReplace = NULL;
	{
		CREATE_BUFFER_FROM_CSTRING(bufUtf8_szReplace, szReplace)
	}
	if (bufUtf8_szReplace == NULL) return 0;

	// set target search
	DoCommand(SCI_SETSEARCHFLAGS, m_nSearchflags);

	int nCountReplace = 0;
	CString strSelectedText = GetSelectedText();
	if (!strSelectedText.IsEmpty() && strSelectedText != szFind) // replace all in selection scope
	{
		int lLenToReplace = 0;
		int lStartSelection = GetSelectionStartPosition();
		int lEndSelection = GetSelectionEndPosition();
		DoCommand(SCI_SETTARGETSTART, lStartSelection);
		DoCommand(SCI_SETTARGETEND, lEndSelection);
		int lPosToReplace = static_cast<int>(DoCommand(SCI_SEARCHINTARGET, szFind.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szFind)));
		while (lPosToReplace < lEndSelection && lPosToReplace >= 0)
		{
			if (m_nSearchflags & SCFIND_REGEXP)
			{
				lLenToReplace = static_cast<int>(DoCommand(SCI_REPLACETARGETRE, szReplace.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szReplace)));
			}
			else
			{
				lLenToReplace = static_cast<int>(DoCommand(SCI_REPLACETARGET, szReplace.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szReplace)));
			}
			if (lLenToReplace >= 0)
			{
				nCountReplace++;
			}
			lEndSelection = GetSelectionEndPosition();
			DoCommand(SCI_SETTARGETSTART, lPosToReplace + lLenToReplace);
			DoCommand(SCI_SETTARGETEND, lEndSelection);
			lPosToReplace = static_cast<int>(DoCommand(SCI_SEARCHINTARGET, szFind.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szFind)));
		}
	}
	else // replace all in file scope
	{
		int nDeltaReplaceLength = szFind.GetLength() - szReplace.GetLength();
		int lLen = 0;
		int lStart = 0;
		int lEnd = static_cast<int>(DoCommand(SCI_GETTEXTLENGTH, 0, 0));
		int lPosAnchor = GetCurrentAnchor();
		int lPosCaret = GetCurrentPosition();
		if (lPosAnchor < lPosCaret)
		{
			lStart = lPosAnchor;
		}
		else
		{
			lStart = lPosCaret;
		}
		DoCommand(SCI_SETTARGETSTART, lStart, 0);
		DoCommand(SCI_SETTARGETEND, lEnd, 0);
		int lPos = static_cast<int>(DoCommand(SCI_SEARCHINTARGET, szFind.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szFind)));
		int lPosFirstMatched = lPos;
		while (lPos < lEnd && lPos >= 0)
		{
			if (m_nSearchflags & SCFIND_REGEXP)
			{
				lLen = static_cast<int>(DoCommand(SCI_REPLACETARGETRE, szReplace.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szReplace)));
			}
			else
			{
				lLen = static_cast<int>(DoCommand(SCI_REPLACETARGET, szReplace.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szReplace)));
			}
			if (lLen >= 0)
			{
				nCountReplace++;
				lEnd = static_cast<int>(DoCommand(SCI_GETTEXTLENGTH, 0, 0));
				DoCommand(SCI_SETTARGETSTART, lPos + lLen);
				DoCommand(SCI_SETTARGETEND, lEnd);
				lPos = static_cast<int>(DoCommand(SCI_SEARCHINTARGET, szFind.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szFind)));
			}
		}
		if (lPos >= lEnd || lPos < 0) // back to start file position
		{
			lLen = 0;
			lStart = 0;
			lEnd = lPosFirstMatched;
			DoCommand(SCI_SETTARGETSTART, lStart, 0);
			DoCommand(SCI_SETTARGETEND, lEnd, 0);
			int lPos = static_cast<int>(DoCommand(SCI_SEARCHINTARGET, szFind.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szFind)));
			while (lPos < lEnd && lPos >= 0)
			{
				if (m_nSearchflags & SCFIND_REGEXP)
				{
					lLen = static_cast<int>(DoCommand(SCI_REPLACETARGETRE, szReplace.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szReplace)));
				}
				else
				{
					lLen = static_cast<int>(DoCommand(SCI_REPLACETARGET, szReplace.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szReplace)));
				}
				if (lLen >= 0)
				{
					DoCommand(SCI_SETTARGETSTART, lPos + lLen);
					lEnd -= nDeltaReplaceLength;
					DoCommand(SCI_SETTARGETEND, lEnd);
					lPos = static_cast<int>(DoCommand(SCI_SEARCHINTARGET, szFind.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szFind)));
					nCountReplace++;
				}
			}
		}
		if (lPosFirstMatched >= 0)
		{
			lStart = lPosFirstMatched;
			lEnd = static_cast<int>(DoCommand(SCI_GETTEXTLENGTH, 0, 0));
			DoCommand(SCI_SETTARGETSTART, lStart, 0);
			DoCommand(SCI_SETTARGETEND, lEnd, 0);
			lPosFirstMatched = static_cast<int>(DoCommand(SCI_SEARCHINTARGET, szReplace.GetLength(), reinterpret_cast<LPARAM>(bufUtf8_szReplace)));
			int lCurrentCaretPos = lPosFirstMatched + szReplace.GetLength();
			ClearSelection(lCurrentCaretPos);
			DoCommand(SCI_ADDUNDOACTION, lCurrentCaretPos, UNDO_NONE);
		}
	}
	DELETE_POINTER_CPP_ARRAY(bufUtf8_szFind);
	DELETE_POINTER_CPP_ARRAY(bufUtf8_szReplace);
	return nCountReplace;
}

int CEditorCtrl::SearchTextInRange(const CString& strText, int lStartRange, int lEndRange)
{
	CT2A stUTF8(strText, TF_UTF8);
	LPCTSTR szUTF8 = (LPCTSTR)stUTF8.m_psz;
	DoCommand(SCI_SETTARGETRANGE, lStartRange, lEndRange);
	const char* target = (const char*)(szUTF8);
	int targetLength = static_cast<int>(strlen(target));
	int len = (strText.GetLength() > targetLength) ? strText.GetLength() : targetLength;
	return static_cast<int>(DoCommand(SCI_SEARCHINTARGET, len, reinterpret_cast<LPARAM>(target)));
}

int CEditorCtrl::SearchTextInEditor(const CString& strText)
{
	int startRange = 0;
	int endRange = GetTextLength();
	return SearchTextInRange(strText, startRange, endRange);
}

void CEditorCtrl::GetTextRange(CString& strText, size_t start, size_t end)
{
	auto GetTextFromEditor = [&]() -> char*
	{
		int lLen = (int)DoCommand(SCI_GETLENGTH) + 1;
		if (lLen > 0)
		{
			char* pReturn = new char[lLen + 1];
			if (pReturn != NULL)
			{
				Sci_TextRange tr;
				tr.chrg.cpMin = static_cast<int>(start);
				tr.chrg.cpMax = static_cast<int>(end);
				tr.lpstrText = pReturn;
				DoCommand(SCI_GETTEXTRANGE, 0, reinterpret_cast<LPARAM>(&tr));
				return pReturn;
			}
		}
		return NULL;
	};

	std::unique_ptr<char> szText;
	szText.reset(GetTextFromEditor());
	if (szText != NULL)
	{
		auto uiCodePage = AppUtils::GetCurrentCodePage();
		AppUtils::SetCurrentCodePage(TF_UTF8);
		CString str = AppUtils::ArrayCharToCString(szText.get());
		AppUtils::SetCurrentCodePage(uiCodePage);
		strText = str;
	}
}

void CEditorCtrl::GetTextRange(char* strText, int lStart, int lEnd)
{
	Sci_TextRange tr;
	tr.chrg.cpMin = lStart;
	tr.chrg.cpMax = lEnd;
	tr.lpstrText = strText;
	DoCommand(SCI_GETTEXTRANGE, 0, reinterpret_cast<LPARAM>(&tr));
}

int CEditorCtrl::GetLineCount()
{
	int lineCount = (int)DoCommand(SCI_GETLINECOUNT);
	return lineCount;
}

int CEditorCtrl::GetLineEnd()
{
	int endPos = (int)DoCommand(SCI_GETLENGTH);
	return (int)DoCommand(SCI_LINEFROMPOSITION, endPos);
}

void CEditorCtrl::RemoveIndicatorSpellCheck()
{
	sptr_t startFilePosition = 0;
	sptr_t endFilePosition = DoCommand(SCI_GETLENGTH);
	DoCommand(SCI_SETINDICATORCURRENT, INDIC_SPELL_CHECKER);
	DoCommand(SCI_INDICATORCLEARRANGE, startFilePosition, endFilePosition - startFilePosition);
}

void CEditorCtrl::RemoveIndicatorHightLightRenders()
{
	sptr_t startFilePosition = 0;
	sptr_t endFilePosition = DoCommand(SCI_GETLENGTH);
	if (m_strUserTextLexer != "python")
	{
		DoCommand(SCI_SETINDICATORCURRENT, INDIC_HIGHLIGHT_PYTHON);
		DoCommand(SCI_INDICATORCLEARRANGE, startFilePosition, endFilePosition - startFilePosition);
	}
	else
	{
		DoCommand(SCI_SETINDICATORCURRENT, INDIC_HIGHLIGHT_GENERAL);
		DoCommand(SCI_INDICATORCLEARRANGE, startFilePosition, endFilePosition - startFilePosition);
	}
}

void CEditorCtrl::RemoveEachIndicatorHightLight(sptr_t startPosition, sptr_t endPosition)
{
	if (m_strUserTextLexer != "python")
	{
		DoCommand(SCI_SETINDICATORCURRENT, INDIC_HIGHLIGHT_PYTHON);
		DoCommand(SCI_INDICATORCLEARRANGE, startPosition, endPosition - startPosition);
	}
	else
	{
		DoCommand(SCI_SETINDICATORCURRENT, INDIC_HIGHLIGHT_GENERAL);
		DoCommand(SCI_INDICATORCLEARRANGE, startPosition, endPosition - startPosition);
	}
}

void CEditorCtrl::RemoveAllIndicators()
{
	sptr_t startFilePosition = 0;
	sptr_t endFilePosition = DoCommand(SCI_GETLENGTH);
	DoCommand(SCI_SETINDICATORCURRENT, INDIC_TAGMATCH);
	DoCommand(SCI_INDICATORCLEARRANGE, startFilePosition, endFilePosition - startFilePosition);
	DoCommand(SCI_SETINDICATORCURRENT, INDIC_TAGATTR);
	DoCommand(SCI_INDICATORCLEARRANGE, startFilePosition, endFilePosition - startFilePosition);
	DoCommand(SCI_SETINDICATORCURRENT, INDIC_SPELL_CHECKER);
	DoCommand(SCI_INDICATORCLEARRANGE, startFilePosition, endFilePosition - startFilePosition);
	if (m_strUserTextLexer != "python")
	{
		DoCommand(SCI_SETINDICATORCURRENT, INDIC_HIGHLIGHT_PYTHON);
		DoCommand(SCI_INDICATORCLEARRANGE, startFilePosition, endFilePosition - startFilePosition);
	}
	else
	{
		DoCommand(SCI_SETINDICATORCURRENT, INDIC_HIGHLIGHT_GENERAL);
		DoCommand(SCI_INDICATORCLEARRANGE, startFilePosition, endFilePosition - startFilePosition);
	}
}

void CEditorCtrl::RemoveAnotations()
{
	DoCommand(SCI_ANNOTATIONCLEARALL);
}

void CEditorCtrl::AddIndicators(int startPos, int lengthWord)
{
	DoCommand(SCI_INDICATORFILLRANGE, startPos, lengthWord);
}

int CEditorCtrl::GetTextLength()
{
	int lLength = (int)DoCommand(SCI_GETLENGTH);
	if (lLength > 0)
	{
		return lLength;
	}
	else
	{
		return 0;
	}
}

void CEditorCtrl::EnableTextWrappingMode(BOOL bEnable)
{
	if (bEnable)
		DoCommand(SCI_SETWRAPMODE, SC_WRAP_WORD);
	else
		DoCommand(SCI_SETWRAPMODE, SC_WRAP_NONE);
}

void CEditorCtrl::EnableLongLineChecker(BOOL bEnable)
{
	if (bEnable)
		DoCommand(SCI_SETEDGEMODE, EDGE_LINE);
	else
		DoCommand(SCI_SETEDGEMODE, EDGE_NONE);
}

BOOL CEditorCtrl::IsEditorInWrapMode()
{
	int nMode = (int)DoCommand(SCI_GETWRAPMODE);
	if (nMode > 0)
		return TRUE;
	else
		return FALSE;
}

BOOL CEditorCtrl::IsEditorLongLineCheckerEnable()
{
	int nMode = (int)DoCommand(SCI_GETEDGEMODE);
	if (nMode > 0)
		return TRUE;
	else
		return FALSE;
}

void CEditorCtrl::EnableBidirectionalRightToLeft(BOOL bEnable)
{
	long exStyle = static_cast<long>(::GetWindowLongPtr(this->GetSafeHwnd(), GWL_EXSTYLE));
	exStyle = bEnable ? exStyle | WS_EX_LAYOUTRTL : exStyle & (~WS_EX_LAYOUTRTL);
	::SetWindowLongPtr(this->GetSafeHwnd(), GWL_EXSTYLE, exStyle);
	BOOL bWraped = IsEditorInWrapMode();
	EnableTextWrappingMode(!bWraped);
	EnableTextWrappingMode(bWraped);
}

BOOL CEditorCtrl::GetBidirectionalRightToLeft()
{
	long exStyle = static_cast<long>(::GetWindowLongPtr(this->GetSafeHwnd(), GWL_EXSTYLE));
	return (exStyle & WS_EX_LAYOUTRTL) != 0;
}

int CEditorCtrl::GetLineStartPosition(int lLine)
{
	return (int)DoCommand(SCI_POSITIONFROMLINE, lLine, 0);
}

int CEditorCtrl::GetLineEndPosition(int lLine)
{
	return (int)DoCommand(SCI_GETLINEENDPOSITION, lLine, 0);
}

void CEditorCtrl::SetStartSelection(int lPos)
{
	DoCommand(SCI_SETSELECTIONSTART, lPos, 0);
}

void CEditorCtrl::SetEndSelection(int lPos)
{
	DoCommand(SCI_SETSELECTIONEND, lPos, 0);
}

void CEditorCtrl::SetSelectionRange(int lStartPos, int lEndPos)
{
	DoCommand(SCI_SETSELECTIONSTART, lStartPos, 0);
	DoCommand(SCI_SETSELECTIONEND, lEndPos, 0);
}

void CEditorCtrl::SetModEventMask(int eventMask)
{
	DoCommand(SCI_SETMODEVENTMASK, eventMask, 0);
}

int CEditorCtrl::GetLineLength(int curLine)
{
	return (int)DoCommand(SCI_LINELENGTH, curLine);
}

void CEditorCtrl::EnableDisplayWhiteSpace(BOOL bEnable)
{
	if (bEnable)
		DoCommand(SCI_SETVIEWWS, SCWS_VISIBLEALWAYS);
	else
		DoCommand(SCI_SETVIEWWS, SCWS_INVISIBLE);
}

BOOL CEditorCtrl::GetDisplayWhiteSpace()
{
	int nMode = (int)DoCommand(SCI_GETVIEWWS);
	if (nMode > 0)
		return TRUE;
	else
		return FALSE;
}

void CEditorCtrl::EnableDisplayTabIndentation(BOOL bEnable)
{
	if (bEnable)
		DoCommand(SCI_SETINDENTATIONGUIDES, SC_IV_LOOKBOTH, 0);
	else
		DoCommand(SCI_SETINDENTATIONGUIDES, SC_IV_NONE, 0);
}

BOOL CEditorCtrl::GetDisplayTabIndentation()
{
	int nMode = (int)DoCommand(SCI_GETINDENTATIONGUIDES);
	if (nMode > 0)
		return TRUE;
	else
		return FALSE;
}

void CEditorCtrl::ExpandAllFoldings()
{
	DoCommand(SCI_FOLDALL, SC_FOLDACTION_EXPAND);
}

void CEditorCtrl::CollapseAllFoldings()
{
	DoCommand(SCI_FOLDALL, SC_FOLDACTION_CONTRACT);
}

void CEditorCtrl::ToggleAllFoldings()
{
	DoCommand(SCI_FOLDALL, SC_FOLDACTION_TOGGLE);
}

void CEditorCtrl::ToggleCurrentFolding()
{
	int lCurLine = GetCurrentLine();
	int lParentFoldLine = static_cast<int>(DoCommand(SCI_GETFOLDPARENT, lCurLine));
	DoCommand(SCI_FOLDLINE, lParentFoldLine, SC_FOLDACTION_TOGGLE);
}

int CEditorCtrl::GetCurrentFolddingLevel()
{
	return m_CurrentFoldingLevel;
}

void CEditorCtrl::FoldingWithLevel(int level2Collapse = -1)
{
	if (level2Collapse == -1) return;
	m_CurrentFoldingLevel = level2Collapse;
	FoldingLevelStack levelStack;
	auto maxLine = DoCommand(SCI_GETLINECOUNT, 0, 0);
	int  mode = 0;
	for (auto line = 0; line < maxLine; ++line)
	{
		auto info = DoCommand(SCI_GETFOLDLEVEL, line, 0);
		if ((info & SC_FOLDLEVELHEADERFLAG) != 0)
		{
			int level = info & SC_FOLDLEVELNUMBERMASK;
			level -= SC_FOLDLEVELBASE;
			levelStack.push(level);
			if (level2Collapse < 0 || levelStack.levelCount == level2Collapse)
			{
				mode = DoCommand(SCI_GETFOLDEXPANDED, line, 0) ? 0 : 1;
				break;
			}
		}
	}
	BOOL bHasFolder = FALSE;
	for (auto line = 0; line < maxLine; ++line)
	{
		auto info = DoCommand(SCI_GETFOLDLEVEL, line, 0);
		if ((info & SC_FOLDLEVELHEADERFLAG) != 0)
		{
			int level = info & SC_FOLDLEVELNUMBERMASK;
			level -= SC_FOLDLEVELBASE;
			levelStack.push(level);
			if (level2Collapse < 0 || levelStack.levelCount == level2Collapse)
			{
				if (DoCommand(SCI_GETFOLDEXPANDED, line, 0) != mode)
				{
					auto endStyled = DoCommand(SCI_GETENDSTYLED, 0, 0);
					auto len = DoCommand(SCI_GETTEXTLENGTH, 0, 0);
					if (endStyled < len)
					{
						DoCommand(SCI_COLOURISE, 0, -1);
					}
					auto headerLine = 0;
					if (info & SC_FOLDLEVELHEADERFLAG)
					{
						headerLine = line;
					}
					else
					{
						headerLine = static_cast<int>(DoCommand(SCI_GETFOLDPARENT, line, 0));
						if (headerLine == -1)
							return;
					}
					if (DoCommand(SCI_GETFOLDEXPANDED, headerLine, 0) != mode)
					{
						bHasFolder = TRUE;
						if (m_strLexerName == _T("cpp") || m_strLexerName == _T("c") || m_strLexerName == _T("cs")
							|| m_strLexerName == _T("java") || m_strLexerName == _T("javascript") || m_strLexerName == _T("typescript")
							|| m_strLexerName == _T("phpscript") || m_strLexerName == _T("rust") || m_strLexerName == _T("kix")
							|| m_strLexerName == _T("markdown") || m_strLexerName == _T("css"))
						{
							DoCommand(SCI_TOGGLEFOLDSHOWTEXT, headerLine, reinterpret_cast<LPARAM>(FOLDED_MARKER_CPP));
						}
						else if (m_strLexerName == _T("hypertext") || m_strLexerName == _T("xml"))
						{
							DoCommand(SCI_TOGGLEFOLDSHOWTEXT, headerLine, reinterpret_cast<LPARAM>(FOLDED_MARKER_HTML));
						}
						else
						{
							DoCommand(SCI_TOGGLEFOLDSHOWTEXT, headerLine, reinterpret_cast<LPARAM>(FOLDED_MARKER_TEXT));
						}
					}
				}
			}
		}
	}
	if (!bHasFolder)
	{
		AfxMessageBoxFormat(MB_ICONINFORMATION, _T("The current file has no folding level %d. Please try a smaller level."), level2Collapse);
	}
}

void CEditorCtrl::HideLines(int lLineStart, int lLineEnd)
{
	if (lLineStart < 0 || lLineEnd < 0) return;
	DoCommand(SCI_HIDELINES, lLineStart, lLineEnd);
}

void CEditorCtrl::ShowLines(int lLineStart, int lLineEnd)
{
	if (lLineStart < 0 || lLineEnd < 0) return;
	DoCommand(SCI_SHOWLINES, lLineStart, lLineEnd);
}

void CEditorCtrl::SetReadOnlyEditor(BOOL bEnable)
{
	if (m_bIsFileHasROAttribute && !bEnable)
	{
		if (IDYES == AfxMessageBox(_T("[File Warning] This file has read only attribute, do you want change to edit mode?"), MB_YESNO | MB_ICONWARNING))
		{
			// change file system attribute
			SetFileAttributes(m_strFilePath, GetFileAttributes(m_strFilePath) & ~FILE_ATTRIBUTE_READONLY);
			// update editor
			DoCommand(SCI_SETREADONLY, bEnable);
			m_bIsReadOnlyEditor = false;
		}
	}
	else
	{
		DoCommand(SCI_SETREADONLY, bEnable);
		m_bIsReadOnlyEditor = bEnable ? true : false;
	}
}

BOOL CEditorCtrl::IsReadOnlyEditor()
{
	BOOL bIsROEditor = (BOOL)DoCommand(SCI_GETREADONLY);
	if (bIsROEditor || m_bIsReadOnlyEditor)
	{
		return TRUE;
	}
	return FALSE;
}

CString CEditorCtrl::GetEOLCString()
{
	int currentEOL = (int)DoCommand(SCI_GETEOLMODE);
	switch (currentEOL)
	{
	case SC_EOL_CRLF:
		return _T("\r\n");
	case SC_EOL_CR:
		return _T("\r");
	case SC_EOL_LF:
		return _T("\n");
	default:
		break;
	}
	return _T("\r\n");
}

CString CEditorCtrl::GetEOLName()
{
	int currentEOL = (int)DoCommand(SCI_GETEOLMODE);
	switch (currentEOL)
	{
	case SC_EOL_CRLF:
		return _T("Windows(CRLF)");
	case SC_EOL_CR:
		return _T("MacOS(CR)");
	case SC_EOL_LF:
		return _T("Linux(LF)");
	default:
		break;
	}
	return _T("Window(CRLF)");
}

int CEditorCtrl::GetSelectionNumber()
{
	return (int)DoCommand(SCI_GETSELECTIONS);
}

int CEditorCtrl::GetMainSelection()
{
	return (int)DoCommand(SCI_GETMAINSELECTION);
}

int CEditorCtrl::GetMultiSelectionStart(int nSelectionNumber)
{
	return (int)DoCommand(SCI_GETSELECTIONNSTART, nSelectionNumber);
}

int CEditorCtrl::GetMultiSelectionEnd(int nSelectionNumber)
{
	return (int)DoCommand(SCI_GETSELECTIONNEND, nSelectionNumber);
}

int CEditorCtrl::GetLineFromSelection(int nSelectionNumber)
{
	int nSelStart = (int)DoCommand(SCI_GETSELECTIONNEND, nSelectionNumber);
	int nLineStart = (int)DoCommand(SCI_LINEFROMPOSITION, nSelStart, 0);
	return nLineStart;
}

void CEditorCtrl::SetNextMainSelection()
{
	DoCommand(SCI_ROTATESELECTION);
}

int CEditorCtrl::GetSelectionMode()
{
	return (int)DoCommand(SCI_GETSELECTIONMODE, 0, 0);
}

int CEditorCtrl::GetSelectionNAnchorVirtualSpace(int nSel)
{
	return (int)DoCommand(SCI_GETSELECTIONNANCHORVIRTUALSPACE, nSel);
}

int CEditorCtrl::GetSelectionNCaretVirtualSpace(int nSel)
{
	return (int)DoCommand(SCI_GETSELECTIONNCARETVIRTUALSPACE, nSel);
}

int CEditorCtrl::GetRectangularSelectionAnchor()
{
	return (int)DoCommand(SCI_GETRECTANGULARSELECTIONANCHOR);
}

int CEditorCtrl::GetRectangularSelectionCaret()
{
	return (int)DoCommand(SCI_GETRECTANGULARSELECTIONCARET);
}

int CEditorCtrl::GetRectangularSelectionAnchorVirtualSpace()
{
	return (int)DoCommand(SCI_GETRECTANGULARSELECTIONANCHORVIRTUALSPACE);
}

int CEditorCtrl::GetRectangularSelectionCaretVirtualSpace()
{
	return (int)DoCommand(SCI_GETRECTANGULARSELECTIONCARETVIRTUALSPACE);
}

void CEditorCtrl::SetEOLFile(int eol)
{
	DoCommand(SCI_SETEOLMODE, eol);
}

int CEditorCtrl::GetEditorCodePage()
{
	return (int)DoCommand(SCI_GETCODEPAGE);
}

int CEditorCtrl::GetEncoding()
{
	return m_encodingLoading;
}

CString CEditorCtrl::GetEncodingName()
{
	CString strEncodingName;
	switch (m_encodingLoading)
	{
	case TF_UTF8:
		strEncodingName = L"UTF-8";
		break;
	case 1200:
		strEncodingName = L"UTF-16 LE";
		break;
	case 1201:
		strEncodingName = L"UTF-16 BE";
		break;
	case 12001:
		strEncodingName = L"UTF-32 BE";
		break;
	case 12000:
		strEncodingName = L"UTF-32 LE";
		break;
	case 0:
		strEncodingName = L"ANSI";
		break;
	case -1:
		strEncodingName = L"UTF-8";
		break;
	default:
		if (static_cast<UINT>(m_encodingLoading) == GetACP())
			strEncodingName = L"ANSI";
		else
			strEncodingName = AfxCStringFormat(L"CP - %d", m_encodingLoading);
		break;
	}
	if (m_bHasBOM)
		strEncodingName += L" (BOM)";

	if ((m_encodingSaving != TF_INT) &&
		((m_encodingLoading != m_encodingSaving)
			|| (m_bHasBOM != m_bHasBOMSaving)))
	{
		switch (m_encodingSaving)
		{
		case TF_UTF8:
			strEncodingName = L"UTF-8";
			break;
		case 1200:
			strEncodingName = L"UTF-16 LE";
			break;
		case 1201:
			strEncodingName = L"UTF-16 BE";
			break;
		case 12001:
			strEncodingName = L"UTF-32 BE";
			break;
		case 12000:
			strEncodingName = L"UTF-32 LE";
			break;
		case 0:
			strEncodingName = L"ANSI";
			break;
		default:
			if (static_cast<UINT>(m_encodingLoading) == GetACP())
				strEncodingName = L"ANSI";
			else
				strEncodingName = AfxCStringFormat(L"CP - %d", m_encodingLoading);
			break;
		}
		if (m_bHasBOMSaving)
			strEncodingName += L" (BOM)";
	}
	return strEncodingName;
}

void CEditorCtrl::SetSaveEncoding(int encoding)
{
	m_encodingSaving = encoding;
}

void CEditorCtrl::SetEditorCodePage(int codePage)
{
	DoCommand(SCI_SETCODEPAGE, codePage);
}

void CEditorCtrl::SetAnnotationText(const CString& strText, int lLine)
{
	if (strText.IsEmpty())
		return;

	if (lLine < 0) return;

	if (lLine == GetLineCount())
	{
		lLine = lLine - 1;
	}

	CT2A stUTF8(strText, TF_UTF8);
	LPCTSTR szUTF8 = (LPCTSTR)stUTF8.m_psz;

	DoCommand(SCI_ANNOTATIONSETSTYLE, lLine, STYLE_DEFAULT);
	DoCommand(SCI_ANNOTATIONSETTEXT, lLine, reinterpret_cast<LPARAM>(szUTF8));
	DoCommand(SCI_ANNOTATIONSETVISIBLE, ANNOTATION_BOXED, 0);
}

void CEditorCtrl::ClearAllAnnotationText()
{
	DoCommand(SCI_ANNOTATIONCLEARALL);
}

void CEditorCtrl::StartRenderStyleUrl(int lStartStyling, int lLength)
{
	DoCommand(SCI_SETHOTSPOTACTIVEFORE, 1, m_AppThemeColorSet._editorTextColor);
	DoCommand(SCI_SETHOTSPOTACTIVEBACK, 1, AppSettingMgr.m_AppThemeColor);
	DoCommand(SCI_STARTSTYLING, lStartStyling, 2);
	DoCommand(SCI_SETSTYLING, lLength, 2);
}

void CEditorCtrl::EnableShowEOL(BOOL bEnable)
{
	DoCommand(SCI_SETVIEWEOL, bEnable);
}

BOOL CEditorCtrl::GetShowEOL()
{
	return (int)DoCommand(SCI_GETVIEWEOL);
}

void CEditorCtrl::ConvertEOL(int nModeEOL)
{
	DoCommand(SCI_CONVERTEOLS, nModeEOL, 0);
}

void CEditorCtrl::EnableMultiCursorMode(BOOL bEnable)
{
	DoCommand(SCI_SETMULTIPLESELECTION, bEnable);
	DoCommand(SCI_SETADDITIONALSELECTIONTYPING, bEnable);
	DoCommand(SCI_SETMULTIPASTE, SC_MULTIPASTE_EACH);
	DoCommand(SCI_SETVIRTUALSPACEOPTIONS, SCVS_RECTANGULARSELECTION);
	DoCommand(SCI_AUTOCSETMULTI, SC_MULTIAUTOC_EACH);
}

void CEditorCtrl::EnableHotpotStyle(BOOL bEnable)
{
	if (bEnable)
	{
		DoCommand(SCI_STYLESETHOTSPOT, 2, 1);
		DoCommand(SCI_SETHOTSPOTACTIVEUNDERLINE, 1);
	}
	else
	{
		DoCommand(SCI_STYLESETHOTSPOT, 2, 0);
		DoCommand(SCI_SETHOTSPOTACTIVEUNDERLINE, 0);
	}
}

BOOL CEditorCtrl::GetMultiSelectionModeState()
{
	return (int)DoCommand(SCI_GETMULTIPLESELECTION);
}

int CEditorCtrl::GetTabSize()
{
	return (int)DoCommand(SCI_GETTABWIDTH);
}

void CEditorCtrl::SetEditorInitiationState(BOOL bState)
{
	m_bEditorInitiated = bState;
}

void CEditorCtrl::SetLanguageCFontStyle(int iItem, COLORREF rgb)
{
	if (iItem == SCE_C_WORD || iItem == SCE_C_PREPROCESSOR || iItem == SCE_C_OPERATOR)
	{
		SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		DoCommand(SCI_STYLESETBOLD, iItem, 1);
	}
	else if (iItem == SCE_C_STRING || iItem == SCE_C_CHARACTER)
	{
		SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		DoCommand(SCI_STYLESETITALIC, iItem, 1);
	}
	else
	{
		SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
	}
}

void CEditorCtrl::SetLanguageBashFontStyle(int iItem, COLORREF rgb)
{
	if (iItem == SCE_C_NUMBER || iItem == SCE_C_COMMENTDOC)
	{
		SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		DoCommand(SCI_STYLESETBOLD, iItem, 1);
	}
	else if (iItem == SCE_C_PREPROCESSOR || iItem == SCE_C_STRING || iItem == SCE_C_CHARACTER)
	{
		SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		DoCommand(SCI_STYLESETITALIC, iItem, 1);
	}
	else
	{
		SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
	}
}

void CEditorCtrl::GetFunctionListFromEditor(const TCHAR* pszChars, int lLength, std::vector<CString>& vecFunctionList)
{
	if (lLength == 0) return;

	int nIdentBegin = -1;
	int nPreviousIdent = -1;
	int I = 0;
	for (I = 0;; nPreviousIdent = I, I = static_cast<int>(::CharNext(pszChars + I) - pszChars))
	{
		if (I == nPreviousIdent)
		{
			break;
		}
		if (StringHelper::xisalnum(pszChars[I])
			|| pszChars[I] == '.' && I > 0
			&& (!StringHelper::xisalpha(pszChars[nPreviousIdent])
				&& !StringHelper::xisalpha(pszChars[I + 1])))
		{
			if (nIdentBegin == -1)
			{
				nIdentBegin = I;
			}
		}
		else
		{
			if (nIdentBegin >= 0)
			{
				for (int j = I; j < lLength; j++)
				{
					if (!StringHelper::xisspace(pszChars[j]))
					{
						if (pszChars[j] == '(')
						{
							CString strFunctionString(pszChars);
							CString strFunction = strFunctionString.Mid(nIdentBegin, j - nIdentBegin).Trim();
							if (strFunction != _T("if") &&
								strFunction != _T("for") &&
								strFunction != _T("while") &&
								strFunction != _T("return"))
							{
								vecFunctionList.push_back(strFunction);
							}
						}
						break;
					}
				}
				nIdentBegin = -1;
			}
		}
	}
	if (nIdentBegin >= 0)
	{
		for (int j = I; j < lLength; j++)
		{
			if (!StringHelper::xisspace(pszChars[j]))
			{
				if (pszChars[j] == '(')
				{
					CString strFunctionString(pszChars);
					CString strFunction = strFunctionString.Mid(nIdentBegin, j - nIdentBegin).Trim();
					if (strFunction != _T("if") &&
						strFunction != _T("for") &&
						strFunction != _T("while") &&
						strFunction != _T("return"))
					{
						vecFunctionList.push_back(strFunction);
					}
				}
				break;
			}
		}
	}
}

void CEditorCtrl::RenderSearchResultInLine(int lLine, const CString& strWord)
{
	if (strWord.IsEmpty()) return;

	CString strLine;
	GetTextFromLine(lLine + 1, strLine);

	int startRange = GetLineStartPosition(lLine - 1);
	int endRange = GetLineEndPosition(lLine - 1);

	int targetStart = 0;
	int targetEnd = 0;

	RemoveIndicatorHightLightRenders();
	SetIndicatorForHighlightWord();

	// set target search
	DoCommand(SCI_SETSEARCHFLAGS, m_nSearchflags);
	while (targetStart != -1 && targetStart != -2)
	{
		targetStart = SearchTextInRange(strWord, startRange, endRange);

		if (targetStart == -1 || targetStart == -2)
		{
			break;
		}
		targetEnd = int(DoCommand(SCI_GETTARGETEND));

		if (targetEnd > endRange)
		{
			break;
		}

		int indicatorLength = targetEnd - targetStart;

		if (indicatorLength > 0)
		{
			DoCommand(SCI_INDICATORFILLRANGE, targetStart, indicatorLength);
			DoCommand(SCI_SCROLLRANGE, targetStart + indicatorLength, targetStart);
		}
		else
		{
			break;
		}
		if (targetStart + indicatorLength == endRange)
		{
			break;
		}
		startRange = targetStart + indicatorLength;
	}
}

void CEditorCtrl::RenderHotSpotForUrlLinks()
{
	DoCommand(SCI_INDICSETSTYLE, INDIC_URL_HOTSPOT, INDIC_PLAIN);
	DoCommand(SCI_INDICSETHOVERSTYLE, INDIC_URL_HOTSPOT, INDIC_FULLBOX);
	DoCommand(SCI_INDICSETALPHA, INDIC_URL_HOTSPOT, 70);
	DoCommand(SCI_INDICSETFORE, INDIC_URL_HOTSPOT, BasicColors::orange);
	DoCommand(SCI_INDICSETFLAGS, INDIC_URL_HOTSPOT, SC_INDICFLAG_VALUEFORE);
	DoCommand(SCI_SETINDICATORCURRENT, INDIC_URL_HOTSPOT);
	LRESULT indicFore = DoCommand(SCI_STYLEGETFORE, STYLE_DEFAULT);
	DoCommand(SCI_SETINDICATORVALUE, indicFore);

	int startPos = 0;
	int endPos = GetTextLength();
	if (startPos >= endPos) return;
	UINT currentCP = static_cast<UINT>(DoCommand(SCI_GETCODEPAGE));
	std::unique_ptr<char[]> pEncodedText = std::make_unique<char[]>(endPos - startPos + 1);
	GetTextRange(pEncodedText.get(), startPos, endPos);
	std::unique_ptr<TCHAR[]> pWideText = std::make_unique<TCHAR[]>(endPos - startPos + 1);
	int wideTextLen = MultiByteToWideChar(currentCP, 0, pEncodedText.get(), endPos - startPos + 1, (LPWSTR)pWideText.get(), endPos - startPos + 1) - 1;
	if (wideTextLen > 0)
	{
		int startWide = 0;
		int lenWide = 0;
		int startEncoded = 0;
		int lenEncoded = 0;
		while (TRUE)
		{
			BOOL bUrlDetected = AppUtils::IsUrlHyperLink((LPWSTR)pWideText.get(), wideTextLen, startWide, &lenWide);
			if (lenWide <= 0) break;
			ASSERT((startWide + lenWide) <= wideTextLen);
			lenEncoded = WideCharToMultiByte(currentCP, 0, &pWideText.get()[startWide], lenWide, NULL, 0, NULL, NULL);
			if (bUrlDetected)
			{
				DoCommand(SCI_INDICATORFILLRANGE, startEncoded + startPos, lenEncoded);
			}
			else
			{
				DoCommand(SCI_INDICATORCLEARRANGE, startEncoded + startPos, lenEncoded);
			}
			startWide += lenWide;
			startEncoded += lenEncoded;
			if ((startWide >= wideTextLen) || ((startEncoded + startPos) >= endPos)) break;
		}
		//ASSERT((startEncoded + startPos) == endPos);
		//ASSERT(startWide == wideTextLen);
	}
}

void CEditorCtrl::SetIndicatorForHighlightWord()
{
	if (m_strUserTextLexer != "python")
	{
		if (AppSettingMgr.m_IndicatorStyle == EDITOR_INDICATOR_STYLE::FULL_BOX)
		{
			DoCommand(SCI_INDICSETSTYLE, INDIC_HIGHLIGHT_PYTHON, INDIC_FULLBOX);
		}
		else if (AppSettingMgr.m_IndicatorStyle == EDITOR_INDICATOR_STYLE::BOX)
		{
			DoCommand(SCI_INDICSETSTYLE, INDIC_HIGHLIGHT_PYTHON, INDIC_BOX);
		}
		else
		{
			DoCommand(SCI_INDICSETSTYLE, INDIC_HIGHLIGHT_GENERAL, INDIC_BOX);
		}
		DoCommand(SCI_INDICSETALPHA, INDIC_HIGHLIGHT_PYTHON, 100);
		DoCommand(SCI_INDICSETFORE, INDIC_HIGHLIGHT_PYTHON, m_AppThemeColorSet._editorIndicatorColor);
		DoCommand(SCI_SETINDICATORCURRENT, INDIC_HIGHLIGHT_PYTHON);
	}
	else
	{
		if (AppSettingMgr.m_IndicatorStyle == EDITOR_INDICATOR_STYLE::FULL_BOX)
		{
			DoCommand(SCI_INDICSETSTYLE, INDIC_HIGHLIGHT_GENERAL, INDIC_FULLBOX);
		}
		else if (AppSettingMgr.m_IndicatorStyle == EDITOR_INDICATOR_STYLE::BOX)
		{
			DoCommand(SCI_INDICSETSTYLE, INDIC_HIGHLIGHT_GENERAL, INDIC_BOX);
		}
		else
		{
			DoCommand(SCI_INDICSETSTYLE, INDIC_HIGHLIGHT_GENERAL, INDIC_BOX);
		}
		DoCommand(SCI_INDICSETALPHA, INDIC_HIGHLIGHT_GENERAL, 100);
		DoCommand(SCI_INDICSETFORE, INDIC_HIGHLIGHT_GENERAL, m_AppThemeColorSet._editorIndicatorColor);
		DoCommand(SCI_SETINDICATORCURRENT, INDIC_HIGHLIGHT_GENERAL);
	}
	LRESULT indicatorForeground = DoCommand(SCI_STYLEGETFORE, STYLE_DEFAULT);
	DoCommand(SCI_SETINDICATORVALUE, indicatorForeground);
}

void CEditorCtrl::UpdateCaretLineVisible()
{
	if (DoCommand(SCI_GETSELECTIONEMPTY, 0, 0) && DoCommand(SCI_GETSELECTIONS) == SINGLE_SELECTION)
	{
		DoCommand(SCI_SETSELBACK, 1, m_AppThemeColorSet._selectionTextColor);
		DoCommand(SCI_SETSELALPHA, 60);
		DoCommand(SCI_SETCARETLINEVISIBLE, 1);
	}
	else
	{
		DoCommand(SCI_SETCARETLINEVISIBLE, 0);
	}
}

FoldingLineDataList CEditorCtrl::GetFoldingLineDataList(int levelMax)
{
	FoldingLineDataList datalist;
	int lFirstLineVisiable = GetFirstVisibleLine();
	ExpandAllFoldings();
	for (int level2Collapse = 1; level2Collapse <= levelMax; ++level2Collapse)
	{
		FoldingLevelStack levelStack;
		auto maxLine = DoCommand(SCI_GETLINECOUNT, 0, 0);
		int  mode = 0;
		for (auto line = 0; line < maxLine; ++line)
		{
			auto info = DoCommand(SCI_GETFOLDLEVEL, line, 0);
			if ((info & SC_FOLDLEVELHEADERFLAG) != 0)
			{
				int level = info & SC_FOLDLEVELNUMBERMASK;
				level -= SC_FOLDLEVELBASE;
				levelStack.push(level);
				if (level2Collapse < 0 || levelStack.levelCount == level2Collapse)
				{
					mode = DoCommand(SCI_GETFOLDEXPANDED, line, 0) ? 0 : 1;
					break;
				}
			}
		}
		for (auto line = 0; line < maxLine; ++line)
		{
			auto info = DoCommand(SCI_GETFOLDLEVEL, line, 0);
			if ((info & SC_FOLDLEVELHEADERFLAG) != 0)
			{
				int level = info & SC_FOLDLEVELNUMBERMASK;
				level -= SC_FOLDLEVELBASE;
				levelStack.push(level);
				if (level2Collapse < 0 || levelStack.levelCount == level2Collapse)
				{
					if (DoCommand(SCI_GETFOLDEXPANDED, line, 0) != mode)
					{
						auto endStyled = DoCommand(SCI_GETENDSTYLED, 0, 0);
						auto len = DoCommand(SCI_GETTEXTLENGTH, 0, 0);
						if (endStyled < len)
						{
							DoCommand(SCI_COLOURISE, 0, -1);
						}
						auto headerLine = 0;
						if (info & SC_FOLDLEVELHEADERFLAG)
						{
							headerLine = line;
						}
						else
						{
							headerLine = static_cast<int>(DoCommand(SCI_GETFOLDPARENT, line, 0));
							if (headerLine == -1)
							{
								return datalist;
							}
						}
						if (DoCommand(SCI_GETFOLDEXPANDED, headerLine, 0) != mode)
						{
							CString strLineText;
							GetTextFromLine(headerLine + 1, strLineText);
							CString strLineTextTemp = strLineText;
							if ((m_strLexerName == _T("cpp") || m_strLexerName == _T("c") || m_strLexerName == _T("cs")
								|| m_strLexerName == _T("java") || m_strLexerName == _T("javascript") || m_strLexerName == _T("typescript")
								|| m_strLexerName == _T("phpscript") || m_strLexerName == _T("rust") || m_strLexerName == _T("kix")
								|| m_strLexerName == _T("markdown")))
							{
								CString strLineText2;
								GetTextFromLine(headerLine, strLineText2);
								if (strLineTextTemp.Trim() == _T("{"))
								{
									datalist.push_back(FoldingLineData(headerLine + 1, strLineText2));
								}
								else
								{
									strLineText.Replace(_T("{"), _T(""));
									datalist.push_back(FoldingLineData(headerLine + 1, strLineText));
								}
							}
							else if (m_strLexerName == _T("python"))
							{
								if (strLineText.Find(_T("class ")) != -1 || strLineText.Find(_T("def ")) != -1
									|| strLineText.Find(_T("if ")) != -1 && strLineTextTemp.Find(_T("elif ")) != -1
									|| strLineText.Find(_T("for ")) != -1 && strLineTextTemp.Find(_T("while ")) != -1
									|| strLineText.Find(_T("return ")) != -1)
								{
									strLineText.Replace(_T(":"), _T(""));
									datalist.push_back(FoldingLineData(headerLine + 1, strLineText));
								}
							}
							else
							{
								datalist.push_back(FoldingLineData(headerLine + 1, strLineText));
							}
						}
					}
				}
			}
		}
	}
	std::sort(datalist.begin(), datalist.end(), [](const FoldingLineData& a, const FoldingLineData& b)
		{
			return a._lineNumber < b._lineNumber;
		});
	SetFirstVisibleLine(lFirstLineVisiable);
	return datalist;
}

void CEditorCtrl::LoadPythonHightlight()
{
	AppSettingMgr.m_AppThemeColor == THEME_BACKGROUND_COLOR_LIGHT ?
		EditorLexerLight::Init_python_Editor_NoDB(this) :
		EditorLexerDark::Init_python_Editor_NoDB(this);
}

void CEditorCtrl::LoadCPPHightlight()
{
	AppSettingMgr.m_AppThemeColor == THEME_BACKGROUND_COLOR_LIGHT ?
		EditorLexerLight::Init_python_Editor_NoDB(this) :
		EditorLexerDark::Init_python_Editor_NoDB(this);
}

void CEditorCtrl::LoadHTMLHightlight()
{
	AppSettingMgr.m_AppThemeColor == THEME_BACKGROUND_COLOR_LIGHT ?
		EditorLexerLight::Init_python_Editor_NoDB(this) :
		EditorLexerDark::Init_python_Editor_NoDB(this);
}

void CEditorCtrl::RemoveTextHightlight()
{
	AppSettingMgr.m_AppThemeColor == THEME_BACKGROUND_COLOR_LIGHT ?
		EditorLexerLight::Init_text_Editor(this) :
		EditorLexerDark::Init_text_Editor(this);
}

void CEditorCtrl::ShowHideFoldingMargin(int nPosMouseX)
{
	if (AppSettingMgr.m_bEnableShowHideFoldingMargin)
	{
		if (m_bIsContextMenuPopup)
		{
			DoCommand(SCI_SETMARGINMASKN, SC_SETMARGINTYPE_FOLDING, ~SC_MASK_FOLDERS);
		}
		else
		{
			int nMask = static_cast<int>(DoCommand(SCI_GETMARGINMASKN, SC_SETMARGINTYPE_FOLDING));
			nMask = nPosMouseX <= 0 || nPosMouseX > VINATEXT_MARGINWIDTH * 2 + GetLineNumberWidth(static_cast<int>(DoCommand(SCI_LINESONSCREEN)) ? (nMask & ~SC_MASK_FOLDERS) : (nMask | SC_MASK_FOLDERS));
			DoCommand(SCI_SETMARGINMASKN, SC_SETMARGINTYPE_FOLDING, nMask);
		}
	}
	else
	{
		DoCommand(SCI_SETMARGINMASKN, SC_SETMARGINTYPE_FOLDING, ~SC_MASK_FOLDERS);
	}

}

void CEditorCtrl::SetContextMenuPopupFlag(BOOL bFlag)
{
	m_bIsContextMenuPopup = bFlag;
}

std::string CEditorCtrl::GetWordChars()
{
	int len = static_cast<int>(DoCommand(SCI_GETWORDCHARS));
	auto lineBuffer = std::make_unique<char[]>(len + 1);
	DoCommand(SCI_GETWORDCHARS, 0, reinterpret_cast<LPARAM>(lineBuffer.get()));
	lineBuffer[len] = '\0';
	return lineBuffer.get();
}

std::string CEditorCtrl::GetWhitespaceChars()
{
	int len = static_cast<int>(DoCommand(SCI_GETWHITESPACECHARS));
	auto lineBuffer = std::make_unique<char[]>(len + 1);
	DoCommand(SCI_GETWHITESPACECHARS, 0, reinterpret_cast<LPARAM>(lineBuffer.get()));
	return lineBuffer.get();
}

TabSpace CEditorCtrl::GetTabSpace()
{
	return m_tabSpace;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// text database transaction, actually trantraction will be processed in external dll, below functions are just pre-processing...

void CEditorCtrl::SetIncreaseSelectionMode(BOOL bFlag, BOOL bIsSearchFromStartFile)
{
	m_bIncreaseSelectionMode = bFlag;
	m_bSearchFromStartFile = bIsSearchFromStartFile;
}

BOOL CEditorCtrl::IsHorizonScrollBarVisible()
{
	BOOL bScroll = (GetStyle() & WS_HSCROLL) > 0 ? TRUE : FALSE;
	return bScroll;
}

void CEditorCtrl::DoMatchSelectedText()
{
	static Sci_PositionCR lastStopPosition = 0;
	int                  firstLine = static_cast<int>(DoCommand(SCI_GETFIRSTVISIBLELINE));
	int                  lastLine = firstLine + static_cast<int>(DoCommand(SCI_LINESONSCREEN));
	int                  startStylePos = static_cast<int>(DoCommand(SCI_POSITIONFROMLINE, firstLine));

	startStylePos = max(startStylePos, 0);
	int endStylePos = static_cast<int>(DoCommand(SCI_POSITIONFROMLINE, lastLine)) + static_cast<int>(DoCommand(SCI_LINELENGTH, lastLine));
	if (endStylePos < 0)
	{
		endStylePos = static_cast<int>(DoCommand(SCI_GETLENGTH));
	}

	int len = endStylePos - startStylePos;
	if (len <= 0)
	{
		RePaintUI();
		return;
	}

	// reset indicators
	RemoveIndicatorHightLightRenders();
	SetIndicatorForHighlightWord();
	DoCommand(SCI_INDICATORCLEARRANGE, startStylePos, len);

	auto selTextLen = DoCommand(SCI_GETSELTEXT);
	if (selTextLen <= 1) // Includes zero terminator so 1 means 0.
	{
		RePaintUI();
		return;
	}

	auto origSelStart = DoCommand(SCI_GETSELECTIONSTART);
	auto origSelEnd = DoCommand(SCI_GETSELECTIONEND);
	auto selStartLine = DoCommand(SCI_LINEFROMPOSITION, origSelStart, 0);
	auto selEndLine = DoCommand(SCI_LINEFROMPOSITION, origSelEnd, 0);
	if (selStartLine != selEndLine)
	{
		RePaintUI();
		return;
	}

	auto selStartPos = DoCommand(SCI_GETSELECTIONSTART);
	auto selTextBuffer = std::make_unique<char[]>(selTextLen + 1);
	DoCommand(SCI_GETSELTEXT, 0, reinterpret_cast<LPARAM>(selTextBuffer.get()));
	if (selTextBuffer[0] == 0)
	{
		RePaintUI();
		return;
	}

	if (GetWordFromPosition(GetCurrentPosition()) != CString(selTextBuffer.get()))
	{
		RePaintUI();
		return;
	}

	std::string sSelText = selTextBuffer.get();
	STDStringHelper::trim(sSelText);
	if (sSelText.empty())
	{
		RePaintUI();
		return;
	}

	auto textBuffer = std::make_unique<char[]>(len + 1LL);
	Sci_TextRange textRange{};
	textRange.lpstrText = textBuffer.get();
	textRange.chrg.cpMin = startStylePos;
	textRange.chrg.cpMax = endStylePos;
	DoCommand(SCI_GETTEXTRANGE, 0, reinterpret_cast<LPARAM>(&textRange));

	const char* startPos = strstr(textBuffer.get(), selTextBuffer.get());
	while (startPos)
	{
		// don't style the selected text itself
		if (selStartPos != static_cast<sptr_t>(startStylePos + (startPos - textBuffer.get())))
		{
			DoCommand(SCI_INDICATORFILLRANGE, startStylePos + (startPos - textBuffer.get()), selTextLen - 1);
		}
		startPos = strstr(startPos + 1, selTextBuffer.get());
	}

	RePaintUI();
}

BOOL CEditorCtrl::IsVerticalScrollBarVisible()
{
	BOOL bScroll = (GetStyle() & WS_VSCROLL) > 0 ? TRUE : FALSE;
	return bScroll;
}

void CEditorCtrl::Undo()
{
	if (GetSelectionNumber() > SINGLE_SELECTION || IsEditorInWrapMode())
	{
		int nVisualLine = GetFirstVisibleLine();
		DoCommand(SCI_UNDO);
		SetFirstVisibleLine(nVisualLine);
	}
	else
	{
		int lFisrtVisibleLineBeforeUndo = GetFirstVisibleLine();
		int lEndVisibleLineBeforeUndo = GetEndVisibleLine();
		DoCommand(SCI_UNDO); // undo normal...
		int lCurLineAfterUndo = GetCurrentLine();
		if (lCurLineAfterUndo < lFisrtVisibleLineBeforeUndo || lCurLineAfterUndo > lEndVisibleLineBeforeUndo)
		{
			SetLineCenterDisplay(lCurLineAfterUndo);
		}
	}
}

void CEditorCtrl::Redo()
{
	if (GetSelectionNumber() > SINGLE_SELECTION || IsEditorInWrapMode())
	{
		int nVisualLine = GetFirstVisibleLine();
		DoCommand(SCI_REDO);
		SetFirstVisibleLine(nVisualLine);
	}
	else
	{
		int lFisrtVisibleLineBeforeUndo = GetFirstVisibleLine();
		int lEndVisibleLineBeforeUndo = GetEndVisibleLine();
		DoCommand(SCI_REDO); // undo normal...
		int lCurLineAfterRedo = GetCurrentLine();
		if (lCurLineAfterRedo < lFisrtVisibleLineBeforeUndo || lCurLineAfterRedo > lEndVisibleLineBeforeUndo)
		{
			SetLineCenterDisplay(lCurLineAfterRedo);
		}
	}
}

void CEditorCtrl::BeginUndoTransactions()
{
	DoCommand(SCI_BEGINUNDOACTION);
}

void CEditorCtrl::EndUndoTransactions()
{
	DoCommand(SCI_ENDUNDOACTION);
}

void CEditorCtrl::StartRecordMacro()
{
	DoCommand(SCI_ENDUNDOACTION);
}

void CEditorCtrl::StopRecordMacro()
{
	DoCommand(SCI_ENDUNDOACTION);
}

BOOL CEditorCtrl::IsAllowUndo()
{
	return DoCommand(SCI_CANUNDO) != 0;
}

BOOL CEditorCtrl::IsAllowRedo()
{
	return DoCommand(SCI_CANREDO) != 0;
}

BOOL CEditorCtrl::IsRectangleSelection()
{
	return (BOOL)DoCommand(SCI_SELECTIONISRECTANGLE, 0, 0);
}

BOOL CEditorCtrl::IsMultiOrRectangleSelection()
{
	if (GetSelectionNumber() > SINGLE_SELECTION || IsRectangleSelection())
	{
		return TRUE;
	}
	return FALSE;
}

void CEditorCtrl::UndoRedoRecordingStart()
{
	InterlockedExchange(&m_UndoActionToken, UNDOREDO_FREE); // clear
	UndoRedoSelection selEmpty;
	unsigned int utokenMap;
	MultiCaretTransaction(-1, selEmpty, utokenMap);
	DoCommand(SCI_SETUNDOCOLLECTION, true);
}

void CEditorCtrl::UndoRedoRecordingStop()
{
	int const curToken = InterlockedOr(&m_UndoActionToken, 0L);
	if (curToken >= 0)
	{
		EndUndoAction(curToken);
	}
	UndoRedoSelection selEmpty;
	unsigned int utokenMap;
	MultiCaretTransaction(-1, selEmpty, utokenMap);
	DoCommand(SCI_SETUNDOCOLLECTION, false);
	DoCommand(SCI_EMPTYUNDOBUFFER);
}

BOOL CEditorCtrl::InUndoRedoTransaction()
{
	return (InterlockedOr(&m_UndoActionToken, 0L) != UNDOREDO_FREE);
}

void CEditorCtrl::EndUndoAction(int token)
{
	if ((token >= 0) && (token == (int)InterlockedOr(&m_UndoActionToken, 0L)))
	{
		SaveRedoMultiSelection(token);
		DoCommand(SCI_ENDUNDOACTION);
		InterlockedExchange(&m_UndoActionToken, UNDOREDO_FREE);
	}
}

BOOL CEditorCtrl::GetUndoCollection()
{
	return (BOOL)DoCommand(SCI_GETUNDOCOLLECTION, 0, 0);
}

void CEditorCtrl::ResetMapUndoRedoSelection()
{
	m_MapUndoRedoSelection.clear();
}

int CEditorCtrl::MultiCaretTransaction(int token, UndoRedoSelection& selection, unsigned int& utokenMap)
{
	static unsigned int uiTokenCnt = 0U;

	// indexing is unsigned
	unsigned int utoken = (token >= 0) ? (unsigned int)token : 0U;

	if (!GetUndoCollection())
	{
		return -1;
	}

	// get or set map item request ?
	if ((token >= 0) && (utoken < uiTokenCnt))
	{
		if (selection.IsEmpty())
		{
			// this is a get request
			selection = m_MapUndoRedoSelection[utoken];
			utokenMap = utoken;
		}
		else
		{
			// this is a set request (fill redo pos)
			assert(false); // not used yet
		}
		// don't clear map item here (token used in redo/undo again)
	}
	else if (token < 0)
	{
		// set map new item request
		token = (int)uiTokenCnt;
		m_MapUndoRedoSelection[uiTokenCnt] = selection;
		uiTokenCnt = (uiTokenCnt < (unsigned int)INT_MAX) ? (uiTokenCnt + 1U) : 0U;  // round robin next
	}
	return token;
}

BOOL CEditorCtrl::RestoreMultiSelection(int token, BOOL bUndo)
{
	if (InUndoRedoTransaction())
	{
		return FALSE;
	}
	UndoRedoSelection undoRedoSelection;
	unsigned int utokenMap = 0;
	if (MultiCaretTransaction(token, undoRedoSelection, utokenMap) >= 0 && utokenMap > 0U)
	{
		if (!bUndo && undoRedoSelection.curPos_redo.size() > 1) // if redo mode and start multi redo action, we offset min position 1
		{
			Sci_Position minCaretPos = *min_element(undoRedoSelection.curPos_redo.begin(), undoRedoSelection.curPos_redo.end());
			for (size_t i = 0; i < undoRedoSelection.curPos_redo.size(); ++i)
			{
				if (undoRedoSelection.curPos_redo[i] == minCaretPos)
				{
					undoRedoSelection.curPos_redo[i]++;
					undoRedoSelection.anchorPos_redo[i]++;
				}
			}
		}
		// we are inside undo/redo transaction, so do delayed PostMessage() instead of DoCommand()
		Sci_Position PosAnchor = 0;
		Sci_Position PosCur = 0;
		Sci_Position PosAnchorVS = 0;
		Sci_Position PosCurVS = 0;
		PosAnchor = bUndo ? array_front(undoRedoSelection.anchorPos_undo) : array_front(undoRedoSelection.anchorPos_redo);
		PosCur = bUndo ? array_front(undoRedoSelection.curPos_undo) : array_front(undoRedoSelection.curPos_redo);
		PosAnchorVS = bUndo ? array_front(undoRedoSelection.anchorVS_undo) : array_front(undoRedoSelection.anchorVS_redo);
		PosCurVS = bUndo ? array_front(undoRedoSelection.curVS_undo) : array_front(undoRedoSelection.curVS_redo);

		if (PosAnchor > 0 && PosCur > 0)
		{
			// Ensure that the first and last lines of a selection are always unfolded
			// This needs to be done _before_ the SCI_SETSEL message
			Sci_Position const anchorPosLine = GetLineFromPosition(static_cast<int>(PosAnchor));
			Sci_Position const currPosLine = GetLineFromPosition(static_cast<int>(PosCur));
			PostMessage(SCI_ENSUREVISIBLE, anchorPosLine, 0);
			if (anchorPosLine != currPosLine)
			{
				PostMessage(SCI_ENSUREVISIBLE, currPosLine, 0);
			}

			int const selectionMode = (bUndo) ? undoRedoSelection.selMode_undo : undoRedoSelection.selMode_redo;

			PostMessage(SCI_SETSELECTIONMODE, (WPARAM)((selectionMode == SEL_MULTI_MODE) ? SC_SEL_STREAM : selectionMode), 0);

			switch (selectionMode)
			{
			case SEL_MULTI_MODE:
			{
				unsigned int i = 0;
				Sci_PositionU const selCount = bUndo ? array_len(undoRedoSelection.anchorPos_undo) : array_len(undoRedoSelection.anchorPos_redo);
				Sci_PositionU const selCountVS = bUndo ? array_len(undoRedoSelection.anchorVS_undo) : array_len(undoRedoSelection.anchorVS_redo);
				PostMessage(SCI_SETSELECTION, (WPARAM)(PosCur), (LPARAM)(PosAnchor));
				if (PosAnchorVS && PosCurVS)
				{
					PostMessage(SCI_SETSELECTIONNANCHORVIRTUALSPACE, (WPARAM)0, (LPARAM)(PosAnchorVS));
					PostMessage(SCI_SETSELECTIONNCARETVIRTUALSPACE, (WPARAM)0, (LPARAM)(PosCurVS));
				}
				PostMessage(SCI_CANCEL, 0, 0); // (!) else shift-key selection behavior is kept

				++i;
				while (i < selCount)
				{
					PosAnchor = bUndo ? array_eltptr(undoRedoSelection.anchorPos_undo, i) : array_eltptr(undoRedoSelection.anchorPos_redo, i);
					PosCur = bUndo ? array_eltptr(undoRedoSelection.curPos_undo, i) : array_eltptr(undoRedoSelection.curPos_redo, i);
					if (PosAnchor && PosCur)
					{
						PostMessage(SCI_ADDSELECTION, (WPARAM)(PosCur), (LPARAM)(PosAnchor));
						if (i < selCountVS)
						{
							PosAnchorVS = bUndo ? array_eltptr(undoRedoSelection.anchorVS_undo, i) : array_eltptr(undoRedoSelection.anchorVS_redo, i);
							PosCurVS = bUndo ? array_eltptr(undoRedoSelection.curVS_undo, i) : array_eltptr(undoRedoSelection.curVS_redo, i);
							if (PosAnchorVS && PosCurVS)
							{
								PostMessage(SCI_SETSELECTIONNANCHORVIRTUALSPACE, (WPARAM)i, (LPARAM)(PosAnchorVS));
								PostMessage(SCI_SETSELECTIONNCARETVIRTUALSPACE, (WPARAM)i, (LPARAM)(PosCurVS));
							}
						}
					}
					++i;
				}
			}
			break;

			case SC_SEL_RECTANGLE:
			case SC_SEL_THIN:
				PostMessage(SCI_SETRECTANGULARSELECTIONANCHOR, (WPARAM)(PosAnchor), 0);
				PostMessage(SCI_SETRECTANGULARSELECTIONCARET, (WPARAM)(PosCur), 0);
				if (PosAnchorVS && PosCurVS)
				{
					PostMessage(SCI_SETRECTANGULARSELECTIONANCHORVIRTUALSPACE, (WPARAM)(PosAnchorVS), 0);
					PostMessage(SCI_SETRECTANGULARSELECTIONCARETVIRTUALSPACE, (WPARAM)(PosCurVS), 0);
				}
				PostMessage(SCI_CANCEL, 0, 0); // (!) else shift-key selection behavior is kept
				break;

			case SC_SEL_LINES:
			case SC_SEL_STREAM:
			default:
				if (PosAnchor && PosCur)
				{
					PostMessage(SCI_SETSELECTION, (WPARAM)(PosCur), (LPARAM)(PosAnchor));
				}
				PostMessage(SCI_CANCEL, 0, 0); // (!) else shift-key selection behavior is kept
				break;
			}
		}
		PostMessage(SCI_CHOOSECARETX, 0, 0);
	}
	return true;
}

void CEditorCtrl::RePaintUI()
{
	DoCommand(WM_NCPAINT, static_cast<WPARAM>(1), 0);
}

int CEditorCtrl::SaveUndoMultiSelection()
{
	static Sci_PositionU _s_iSelection = 0; // index

	UndoRedoSelection sel;

	int const numOfSel = GetSelectionNumber();

	// each single selection of a multi-selection will call thid method
	// we are only interested in the first call
	if (0 == _s_iSelection) {
		_s_iSelection = numOfSel;
	}
	if ((numOfSel - 1) != --_s_iSelection) {
		return -1;
	}

	int const selMode = ((numOfSel > 1) && !IsRectangleSelection()) ? SEL_MULTI_MODE : GetSelectionMode();

	sel.selMode_undo = selMode;

	switch (selMode)
	{
	case SEL_MULTI_MODE:
	{
		for (int i = 0; i < numOfSel; ++i)
		{
			int const anchorPos = GetSelectionNumberAnchor(i);
			array_push_back(sel.anchorPos_undo, anchorPos);
			int const curPos = GetSelectionNumberCaret(i);
			array_push_back(sel.curPos_undo, curPos);

			int const anchorVS = GetSelectionNAnchorVirtualSpace(i);
			array_push_back(sel.anchorVS_undo, anchorVS);
			int const curVS = GetSelectionNCaretVirtualSpace(i);
			array_push_back(sel.curVS_undo, curVS);
		}
	}
	break;

	case SC_SEL_RECTANGLE:
	case SC_SEL_THIN:
	{
		Sci_Position const anchorPos = GetRectangularSelectionAnchor();
		array_push_back(sel.anchorPos_undo, anchorPos);
		Sci_Position const curPos = GetRectangularSelectionCaret();
		array_push_back(sel.curPos_undo, curPos);
		Sci_Position const anchorVS = GetRectangularSelectionAnchorVirtualSpace();
		array_push_back(sel.anchorVS_undo, anchorVS);
		Sci_Position const curVS = GetRectangularSelectionCaretVirtualSpace();
		array_push_back(sel.curVS_undo, curVS);
	}
	break;

	case SC_SEL_LINES:
	case SC_SEL_STREAM:
	default:
	{
		Sci_Position const anchorPos = GetCurrentAnchor();
		array_push_back(sel.anchorPos_undo, anchorPos);
		Sci_Position const curPos = GetCurrentPosition();
		array_push_back(sel.curPos_undo, curPos);
		Sci_Position const dummy = (Sci_Position)-1;
		array_push_back(sel.anchorVS_undo, dummy);
		array_push_back(sel.curVS_undo, dummy);
	}
	break;
	}

	unsigned int utokenMap;
	int const token = MultiCaretTransaction(-1, sel, utokenMap);

	if (token >= 0)
	{
		DoCommand(SCI_ADDUNDOACTION, token, UNDO_NONE);
	}
	_s_iSelection = 0; // reset

	return token;
}

void CEditorCtrl::SaveRedoMultiSelection(int token)
{
	static Sci_PositionU _s_iSelection = 0;  // index
	if (token < 0)
	{
		return;
	}
	UndoRedoSelection undoRedoSelection;
	Sci_PositionU const numOfSel = GetSelectionNumber();

	// each single selection of a multi-selection will call this method
	// we are only interested in the last call
	if (0 == _s_iSelection)
	{
		_s_iSelection = numOfSel;
	}

	if (0 != --_s_iSelection)
	{
		return;
	}

	unsigned int utokenMap;
	if (MultiCaretTransaction(token, undoRedoSelection, utokenMap) >= 0)
	{
		int const selMode = ((numOfSel > 1) && !IsRectangleSelection()) ? SEL_MULTI_MODE : GetSelectionMode();

		m_MapUndoRedoSelection[utokenMap].selMode_redo = selMode;

		switch (selMode)
		{
		case SEL_MULTI_MODE:
		{
			for (int i = 0; i < numOfSel; ++i)
			{
				int const anchorPos = GetSelectionNumberAnchor(i);
				array_push_back(m_MapUndoRedoSelection[utokenMap].anchorPos_redo, anchorPos);
				int const curPos = GetSelectionNumberCaret(i);
				array_push_back(m_MapUndoRedoSelection[utokenMap].curPos_redo, curPos);
				int const anchorVS = GetSelectionNAnchorVirtualSpace(i);
				array_push_back(m_MapUndoRedoSelection[utokenMap].anchorVS_redo, anchorVS);
				int const curVS = GetSelectionNCaretVirtualSpace(i);
				array_push_back(m_MapUndoRedoSelection[utokenMap].curVS_redo, curVS);
			}
		}
		break;

		case SC_SEL_RECTANGLE:
		case SC_SEL_THIN:
		{
			Sci_Position const anchorPos = GetRectangularSelectionAnchor();
			array_push_back(m_MapUndoRedoSelection[utokenMap].anchorPos_redo, anchorPos);
			Sci_Position const curPos = GetRectangularSelectionCaret();
			array_push_back(m_MapUndoRedoSelection[utokenMap].curPos_redo, curPos);
			Sci_Position const anchorVS = GetRectangularSelectionAnchorVirtualSpace();
			array_push_back(m_MapUndoRedoSelection[utokenMap].anchorVS_redo, anchorVS);
			Sci_Position const curVS = GetRectangularSelectionCaretVirtualSpace();
			array_push_back(m_MapUndoRedoSelection[utokenMap].curVS_redo, curVS);
		}
		break;

		case SC_SEL_LINES:
		case SC_SEL_STREAM:
		default:
		{
			Sci_Position const anchorPos = GetCurrentAnchor();
			array_push_back(m_MapUndoRedoSelection[utokenMap].anchorPos_redo, anchorPos);
			Sci_Position const curPos = GetCurrentPosition();
			array_push_back(m_MapUndoRedoSelection[utokenMap].curPos_redo, curPos);
		}
		break;
		}
	}
}

// text database transaction, actually trantraction will be processed in external dll, above functions are just pre-processing...
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////