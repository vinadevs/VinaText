/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "EditorDataStructure.h"

#pragma warning(disable : 4996)

class CLanguageDatabase;

class CEditorCtrl : public CWin32Base
{
public:
	CEditorCtrl();
	virtual ~CEditorCtrl();
	void ReleaseDocument();
	virtual BOOL Create(CString strWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	void InitilizeSetting(CLanguageDatabase* pDatabase);
	void ResetUndoSavePoint();
	void SetTextToEditor(const CString& strText);
	void GetText(CString &strText);
	CString GetAllText();
	void GetTextRange(Sci_TextRange *txtRange);
	void GetTextRange(CString & strText, size_t start, size_t end);
	void GetTextRange(char* strText, int lStart, int lEnd);
	void GetTextFromLine(int nline, CString &strText);
	CString GetTextFromCurrentLine();
	CString GetRecentAddedText();
	CString GetCurrentWord();
	void AddText(const CString& strText);
	void InsertText(const CString& strText, int pos);
	void InsertTextAtCurrentPos(const CString& strText);
	void InsertTextAtSelectionNumber(const CString& strText, int lSelectionCaretPosN);
	int GetSelectionNumberCaret(int nSelectionNumber);
	int GetSelectionNumberAnchor(int nSelectionNumber);
	void InsertTextInMultiSelectionMode(const CString& strText, int nSelections, BOOL bIsBracket = FALSE);
	void AppendText(const CString& strText, int pos);
	void ReplaceSelectionWithText(const CString& strText);
	void ReplaceSelectionNWithText(const CString& strText, int nSel);
	void ReplaceCurrentWord(const CString& strNewWord);
	void ReplaceLine(int lLine, const CString& strText);
	void RemoveLine(int lLine);
	void RemoveTextRange(int lStart, int lLengthDelete);
	void RemoveSelectionText();

	void Cut();
	void CutLine();
	void Copy();
	void CopyLine();
	void CopyText(const CString& strText, int length);
	void CopyRange(int posStart, int posEnd);
	void Paste();
	void Clear();	
	BOOL CanPaste();
	void SelectAll();	
	void ClearSelection(int lCaret);
	void DropSelections();
	int GetSelectionStartPosition();
	int GetSelectionEndPosition();
	CString GetSelectedText();	
	CString GetSelectedTextAtSelection(int nSel);
	void SetLexer(const char* czLexerName);
	CString GetLexerNameFromExtension(const CString& szExtension);
	void SetKeywords(const char* keywords, int nKeyWordSet = 0);
	int GetLineIndentPos(int nLine);
	int GetCurrentLine();
	int GetLineFromPosition(int position);
	CString GetWordFromPosition(int lPosition);
	void SelectWordFromPosition(int lPosition);
	int GetWordStartPosition(int lPosition, BOOL bOnlyWordCharacters);
	int GetWordEndPosition(int lPosition, BOOL bOnlyWordCharacters);
	int GetCurrentColumn();
	int GetCurrentPosition();	
	int GetCurrentAnchor();
	void SetCurrentPosition(int lPos);
	void SetCurrentAnchor(int lPos);
	void SetFirstVisibleLine(int line);
	int GetFirstVisibleLine();
	int GetFirstVisibleDocumentLine();
	int GetVisibleLineFromDocumentLine(int nDocLine);
	int GetDocumentLineFromVisibleLine(int nVisibleLine);
	int GetEndVisibleLine();
	BOOL IsSelectionEmpty();
	BOOL IsTextSelected();
	void GotoPosition(int lPos);
	void GotoPointXY(int lX, int lY);
	void SetLineNumberWidth();
	int GetLineNumberWidth();
	int GetLinenumberChars();
	void IndentAll();
	BOOL IsBraceCharacter(int nCharValue);
	int GetCharacterAtPosition(int nPos);
	int GetColumnAtPosition(int nPos);
	void SetIncreaseSelectionMode(BOOL bFlag, BOOL bIsSearchFromStartFile);
	BOOL IsVerticalScrollBarVisible();
	BOOL IsHorizonScrollBarVisible();

	// brace and tag hightlights
	void DoMatchSelectedText(); // for matched selection text from mouse
	void DoBraceMatchHighlight(); // for {}
	SearchResult FindTextResult(const char * text, sptr_t start, sptr_t end, int flags);
	SearchResult FindOpenTag(const std::string & tagName, sptr_t start, sptr_t end);
	sptr_t FindCloseAngle(sptr_t startPosition, sptr_t endPosition);
	SearchResult FindCloseTag(const std::string & tagName, sptr_t start, sptr_t end);
	std::vector<std::pair<sptr_t, sptr_t>> GetAttributesPos(sptr_t start, sptr_t end);
	bool GetXmlHtmlTagsPosition(XmlHtmlTagsPosition & xmlTags);
	void DoXMLHTMLTagsHightlight(); // for </ >
	// brace and tag hightlights

	// search and replace
	void ReplaceSearchedText(const CString & strText);
	int ReplaceNext(const CString & szFind, const CString & szReplace);
	int ReplaceAll(const CString& szFind, const CString& szReplace);
	int SearchTextInRange(const CString& strText, int lStartRange, int lEndRange);
	int SearchTextInEditor(const CString & strText);
	void SetSearchflags(int nSearchflags) { m_nSearchflags = nSearchflags; };
	BOOL SearchForward(const CString& strText);
	BOOL SearchBackward(const CString& strText);
	int FindNextMatchWordPostion(const CString & strSearhWord, int lStartSearchPos, int nSearchFlag);
	int FindPreviousMatchWordPostion(const CString & strSearhWord, int lStartSearchPos, int lMinSel, int nSearchFlag);
	// search and replace

	BOOL GetDisplayLinenumbers() { return m_bLinenumbers; };
	BOOL GetDisplaySelection() { return m_bSelection; };
	BOOL GetDisplayFolding() { return m_bFolding; };
	void SetDisplayLinenumbers(BOOL bFlag = TRUE);
	void SetDisplaySelection(BOOL bFlag = TRUE);
	void SetDisplayFolding(BOOL bFlag = TRUE);
	int GetCurrentStyle();
	int GetCurrentLineFoldinglevel(int lLine);
	BOOL LineHasFoldingLevel(int lLine);
	void ExpandFoldedLine(int lPosition);
	void DoTolggleFolding(int lPosition);
	void GotoLine(int lLine);
	void SetScrollCaret();
	void SetLineCenterDisplay(int lLine);
	void SetLineCenterKeepView(int lLine);
	void UpdateMainSelectionInCurrentView();
	int GetLineOnScreen();
	void SetLineCenterBackwardDisplay(int lLine);
	void DetectFileLexer(const CString & strFilePath);
	void SetTabSettings(TabSpace ts);
	BOOL LoadFile(const CString& strFilePath, int nLoadEncoding = -1, BOOL bCreateIfMissing = FALSE);
	BOOL SaveFile(const CString& strFilePath);
	BOOL UpdateLanguageDatabase(CLanguageDatabase* pDatabase, const CString& czLexer);
	void SetFontname(int nStyle, CString szFontname);
	void SetFontheight(int nStyle, int nHeight);
	void SetForeground(int nStyle, COLORREF crForeground);
	void SetBackground(int nStyle, COLORREF crBackground);
	void SetBold(int nStyle, BOOL bFlag);
	void SetItalic(int nStyle, BOOL bFlag);
	void SetUnderline(int nStyle, BOOL bFlag);
	BOOL GetOverstrike();
	void SetOverstrike(BOOL bOverstrike);
	void Refresh();
	void SetSelectionTextColor(COLORREF color, unsigned int nAlpha);

	// margin makers
	BOOL AddBreakPoint(VINATEXT_SUPPORTED_LANGUAGE language, int lLine, const CString& strFileName);
	BOOL DeleteBreakPoint(VINATEXT_SUPPORTED_LANGUAGE language, int lLine, const CString& strFileName);
	void DeleteAllBreakPoint();
	BOOL IsLineHasBreakPoint(int lLine);
	void FindNextBreakPoint();
	void FindPreviousBreakPoint();
	void AddDisableBreakPoint(int lLine);
	void DeleteDisableBreakPoint(int lLine);
	void DeleteAllDisableBreakPoint();
	BOOL IsLineHasDisableBreakPoint(int lLine);
	BOOL HasBreakPoints();
	void AddDebugPointer(int lLine);
	void DeleteDebugPointer(int lLine);
	void DeleteAllDebugPointer();
	BOOL IsLineHasDebugPointer(int lLine);
	BOOL AddBookMark(int lLine, const CString& strFileName);
	BOOL DeleteBookMark(int lLine, const CString& strFileName);
	void DeleteAllBookMark();
	BOOL IsLineHasBookMark(int lLine);
	BOOL HasBookmarks();
	// margin makers

	int GetLineCount();
	int GetLineEnd();
	void RemoveIndicatorSpellCheck();
	void RemoveIndicatorHightLightRenders();
	void RemoveEachIndicatorHightLight(sptr_t startPosition, sptr_t endPosition);
	void RemoveAllIndicators();
	void RemoveAnotations();
	void AddIndicators(int startPos, int lengthWord);
	int GetTextLength();
	void EnableTextWrappingMode(BOOL bEnable);
	void EnableLongLineChecker(BOOL bEnable);
	BOOL IsEditorInWrapMode();
	BOOL IsEditorLongLineCheckerEnable();
	void EnableBidirectionalRightToLeft(BOOL bEnable);
	BOOL GetBidirectionalRightToLeft();
	int GetLineStartPosition(int lLine);
	int GetLineEndPosition(int lLine);
	void SetStartSelection(int lPos);
	void SetEndSelection(int lPos);
	void SetSelectionRange(int lStartPos, int lEndPos);
	void SetModEventMask(int eventMask);
	int GetLineLength(int curLine);
	void EnableDisplayWhiteSpace(BOOL bEnable);
	BOOL GetDisplayWhiteSpace();
	void EnableDisplayTabIndentation(BOOL bEnable);
	BOOL GetDisplayTabIndentation();
	void ExpandAllFoldings();
	void CollapseAllFoldings();
	void ToggleAllFoldings();
	void ToggleCurrentFolding();
	void FoldingWithLevel(int level2Collapse);
	void HideLines(int lLineStart, int lLineEnd);
	void ShowLines(int lLineStart, int lLineEnd);
	void SetReadOnlyEditor(BOOL bEnable);
	BOOL IsReadOnlyEditor();
	int GetEOLFile();
	CString GetEOLCString();
	CString GetEOLName();

	// multiple selections
	int GetSelectionNumber();
	int GetMainSelection();
	int GetMultiSelectionStart(int nSelectionNumber); // selection number 0 , 1, 2, ...
	int GetMultiSelectionEnd(int nSelectionNumber); // selection number 0 , 1, 2, ...
	int GetLineFromSelection(int nSelectionNumber);
	void SetNextMainSelection();
	int GetSelectionMode();
	int GetSelectionNAnchorVirtualSpace(int nSel);
	int GetSelectionNCaretVirtualSpace(int nSel);
	int GetRectangularSelectionAnchor();
	int GetRectangularSelectionCaret();
	int GetRectangularSelectionAnchorVirtualSpace();
	int GetRectangularSelectionCaretVirtualSpace();
	BOOL IsRectangleSelection();
	BOOL IsMultiOrRectangleSelection();
	// multiple selections

	void SetEOLFile(int eol);
	int GetEditorCodePage(); // codepage from scintilla, not use to read/write data
	void SetEditorCodePage(int codePage);
	int GetEncoding(); // encoding from text file, will be use to read/write data
	CString GetEncodingName();
	void SetSaveEncoding(int encoding); // set encoding from user, will be use to read/write data
	void SetAnnotationText(const CString& strText, int lLine);
	void ClearAllAnnotationText();
	void EnableShowEOL(BOOL bEnable);
	BOOL GetShowEOL();
	void ConvertEOL(int nModeEOL);
	void EnableMultiCursorMode(BOOL bEnable);
	void EnableHotpotStyle(BOOL bEnable);
	void StartRenderStyleUrl(int lStartStyling, int lLength);
	void RenderHotSpotForUrlLinks();
	void SetIndicatorForHighlightWord();
	void UpdateCaretLineVisible();
	BOOL GetMultiSelectionModeState();
	int GetTabSize();
	void SetEditorInitiationState(BOOL bState);
	void SetLanguageCFontStyle(int iItem, COLORREF rgb);
	void GetFunctionListFromEditor(const TCHAR *pszChars, int lLength, std::vector<CString>& vecFunctionList);
	void RenderSearchResultInLine(int lLine, const CString& strWord);
	FoldingLineDataList GetFoldingLineDataList(int levelMax = 3);

	// for database languagues
	void Init_python_Editor(CLanguageDatabase* pDatabase);
	void Init_cpp_Editor(CLanguageDatabase* pDatabase);
	void Init_ada_Editor(CLanguageDatabase* pDatabase);
	void Init_asm_Editor(CLanguageDatabase* pDatabase);
	void Init_inno_Editor(CLanguageDatabase* pDatabase);
	void Init_bash_Editor(CLanguageDatabase* pDatabase);
	void Init_batch_Editor(CLanguageDatabase* pDatabase);
	void Init_c_Editor(CLanguageDatabase * pDatabase);
	void Init_cmake_Editor(CLanguageDatabase* pDatabase);
	void Init_cshape_Editor(CLanguageDatabase* pDatabase);
	void Init_css_Editor(CLanguageDatabase* pDatabase);
	void Init_erlang_Editor(CLanguageDatabase* pDatabase);
	void Init_fortran_Editor(CLanguageDatabase* pDatabase);
	void Init_html_Editor(CLanguageDatabase* pDatabase);
	void Init_java_Editor(CLanguageDatabase* pDatabase);
	void Init_javascript_Editor(CLanguageDatabase* pDatabase);
	void Init_typescript_Editor(CLanguageDatabase* pDatabase);
	void Init_lua_Editor(CLanguageDatabase* pDatabase);
	void Init_matlab_Editor(CLanguageDatabase* pDatabase);
	void Init_pascal_Editor(CLanguageDatabase* pDatabase);
	void Init_perl_Editor(CLanguageDatabase* pDatabase);
	void Init_php_Editor(CLanguageDatabase* pDatabase);
	void Init_powershell_Editor(CLanguageDatabase* pDatabase);
	void Init_ruby_Editor(CLanguageDatabase* pDatabase);
	void Init_rust_Editor(CLanguageDatabase* pDatabase);
	void Init_golang_Editor(CLanguageDatabase* pDatabase);
	void Init_sql_Editor(CLanguageDatabase* pDatabase);
	void Init_tcl_Editor(CLanguageDatabase* pDatabase);
	void Init_vb_Editor(CLanguageDatabase* pDatabase);
	void Init_verilog_Editor(CLanguageDatabase* pDatabase);
	void Init_vhdl_Editor(CLanguageDatabase* pDatabase);
	void Init_xml_Editor(CLanguageDatabase* pDatabase);
	void Init_json_Editor(CLanguageDatabase * pDatabase);
	void Init_markdown_Editor(CLanguageDatabase * pDatabase);
	void Init_protobuf_Editor(CLanguageDatabase * pDatabase);
	void Init_r_Editor(CLanguageDatabase * pDatabase);
	void Init_flexlicense_Editor(CLanguageDatabase * pDatabase);
	void Init_resource_Editor(CLanguageDatabase * pDatabase);
	void Init_autoit_Editor(CLanguageDatabase* pDatabase);
	// for database languagues

	// only highlight text
	void LoadPythonHightlight();
	void LoadCPPHightlight();
	void LoadHTMLHightlight();
	void LoadTextHightlight();
	// only highlight text

	void RePaintUI();
	void LoadExternalSettings(CLanguageDatabase* pDatabase);
	int GetCurrentFolddingLevel();
	CString GetUserTextLexer();
	void SetUserTextLexer(const  CString& strUserLexerName);
	CString GetFileExtension();
	CString GetLexerName();
	void ShowHideFoldingMargin(int nPosMouseX);
	void SetContextMenuPopupFlag(BOOL bFlag);
	std::string GetWordChars();
	std::string GetWhitespaceChars();
	TabSpace GetTabSpace();

	// text database transaction, actually trantraction will be processed in external dll, below functions are just pre-processing...
	void Undo();
	void Redo();
	void BeginUndoTransactions();
	void EndUndoTransactions();
	void StartRecordMacro();
	void StopRecordMacro();
	BOOL IsAllowUndo();
	BOOL IsAllowRedo();
	void UndoRedoRecordingStart();
	void UndoRedoRecordingStop();
	int  SaveUndoMultiSelection();
	void SaveRedoMultiSelection(int token);
	BOOL InUndoRedoTransaction();
	void EndUndoAction(int token);
	BOOL GetUndoCollection();
	void ResetMapUndoRedoSelection();
	int MultiCaretTransaction(int token, UndoRedoSelection& undoRedoSelection, unsigned int& utokenMap);
	BOOL RestoreMultiSelection(int token, BOOL bUndo);
	// text database transaction, actually trantraction will be processed in external dll, above functions are just pre-processing...

	// the fast way to control Scintilla, shoule be inline function
	inline LRESULT DoCommand(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0)
	{	
		return m_DirectFunc(m_pDirectPtr, Msg, wParam, lParam);
	}
private:
	BOOL SaveFileWithEncoding(const CString& strFilePath);
	void SetColorForStyle(int style, COLORREF fore, COLORREF back = RGB(0, 0, 0), int size = -1, const char *face = 0);
	int  m_nSearchflags = 0;
	BOOL m_bLinenumbers = TRUE;
	BOOL m_bSelection = TRUE;
	BOOL m_bFolding = TRUE;
	BOOL m_bIsContextMenuPopup= FALSE;
	BOOL m_bIncreaseSelectionMode = FALSE;
	BOOL m_bSearchFromStartFile = FALSE;
	BOOL m_bEditorInitiated = FALSE;
	int m_CurrentFoldingLevel = -1;
	// lexer APIs
	Lexilla::CreateLexerFn m_CreateLexerFunc = NULL;
	Lexilla::LexerNameFromIDFn m_GetLexerNameFromID = NULL;
	// direct pointers
	DirectFunc m_DirectFunc = NULL;
	DirectPtr  m_pDirectPtr = NULL;
	// default lexer text hightlight
	CString m_strUserTextLexer = _T("python");
	CString m_strFileExtension;
	CString m_strFilePath;
	CString m_strLexerName;
	FoldingLineDataList m_FoldingLineDataList;
	// undo-redo
	MapUndoRedoSelection m_MapUndoRedoSelection;
	long m_UndoActionToken = UNDOREDO_BLOCKED; // block at initial state
	// file IO
	CString					   m_strEncodingName;
	char                       m_data[ReadBlockSize + 8];
	const int                  m_wideBufSize = ReadBlockSize * 2;
	std::unique_ptr<wchar_t[]> m_wideBuf;
	const int                  m_charBufSize = ReadBlockSize * 4;
	std::unique_ptr<char[]>    m_charBuf;
	int                   m_encodingLoading = TF_INT;
	int                   m_encodingSaving = TF_INT;
	bool                  m_bHasBOM = false;
	bool                  m_bHasBOMSaving = false;
	bool                  m_bIsFileHasROAttribute = false;
	bool                  m_bIsReadOnlyEditor = false;
	bool                  m_bIsWriteProtected = false;
	TabSpace              m_tabSpace = TabSpace::Default;
	EOLFormat             m_format = EOLFormat::Unknown_Format;
	uptr_t				  m_DocumentID = 0;
};