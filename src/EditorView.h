/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "EditorDoc.h"
#include "Editor.h"
#include "ViewBase.h"
#include "StringHelper.h"
#include "Compiler.h"
#include "SpellChecker.h"

class CMainFrame;
class CVinaTextProgressBar;

class CEditorView : public CViewBase
{
public:
	CEditorView();
	DECLARE_DYNCREATE(CEditorView)

	// global helpers
	CEditorDoc* GetEditorDocument() const;
	CLanguageDatabase* GetLanguageDatabase() const;
	CEditorCtrl *GetEditorCtrl() { return &m_EditorCtrl; };
	VINATEXT_SUPPORTED_LANGUAGE GetCurrentDocLanguague() { return m_CurrentDocLanguage; }
	BOOL SaveFileAndInitilizeEditor(const CString& szPath);
	void RenderIndicatorWordsAndCount(const CString & strWord, int nSearchOption = SCFIND_WHOLEWORD | SCFIND_MATCHCASE, BOOL bClearSelection = TRUE);
	void ChangeToEditorReadOnly();
	void DisableAllDocumemtReadOnly();
	CString DetectCurrentDocLanguage();
	void AddAutoCompleteFromFile(const CString & strFilePath);
	void AddAutoCompleteFromFolder(const CString & strFolderPath);
	void ReupdateTrackingBar();
	void ToggleAddBreakPoint();
	void ToggleAddBookmark();
	void SetEncodingFromUser(int newEncoding) { m_encodingUser = newEncoding; }

protected: 
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void UpdateFileLastWriteTime(const CString& strFilePath);
	virtual int WatchFileSystemState();

// Implementation
public:
	virtual ~CEditorView();
	virtual void UpdatePreviewFileContent();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	DECLARE_MESSAGE_MAP()
// Generated message map functions
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd * pOldWnd);

public:
	// from edit menu
	afx_msg void OnOptionsEditCopy();
	afx_msg void OnOptionsEditCopyWithQuote();
	afx_msg void OnOptionsEditVisibleCopy();
	afx_msg void OnOptionsEditShowCopyHistory();
	afx_msg void OnEmptyClipboard();
	afx_msg void OnOptionsEditCut();
	afx_msg void OnUpdateOptionsEditCut(CCmdUI* pCmdUI);
	afx_msg void OnOptionsEditPaste();
	afx_msg void OnUpdateOptionsEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnOptionsEditPasteHTML();
	afx_msg void OnUpdateOptionsEditPasteHTML(CCmdUI* pCmdUI);
	afx_msg void OnOptionsEditPasteRFT();
	afx_msg void OnUpdateOptionsEditPasteRFT(CCmdUI* pCmdUI);
	afx_msg void OnPasteWithDoubleQuote();
	afx_msg void OnUpdateOptionsPasteWithDoubleQuote(CCmdUI* pCmdUI);
	afx_msg void OnPasteAtBeginAllFile();
	afx_msg void OnPasteAtEndAllFile();
	afx_msg void OnPasteWithForwardSlash();
	afx_msg void OnUpdateOptionsPasteWithForwardSlash(CCmdUI* pCmdUI);
	afx_msg void OnOptionsEditSelectionToDoubleQuote();
	afx_msg void OnOptionsEditSelectionToNextParagraph();
	afx_msg void OnOptionsEditSelectionToPrevParagraph();
	afx_msg void OnOptionsEditGotoNextParagraph();
	afx_msg void OnOptionsEditGotoPrevParagraph();
	afx_msg void OnOptionsEditUndo();
	afx_msg void OnUpdateOptionsEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnOptionsEditUndoAll();
	afx_msg void OnUpdateOptionsEditUndoAll(CCmdUI* pCmdUI);
	afx_msg void OnOptionsEditRedoAll();
	afx_msg void OnUpdateOptionsEditRedoAll(CCmdUI* pCmdUI);
	afx_msg void OnOptionsEditUndoAllFile();
	afx_msg void OnUpdateOptionsEditUndoAllFile(CCmdUI* pCmdUI);
	afx_msg void OnOptionsEditRedoAllFile();
	afx_msg void OnUpdateOptionsEditRedoAllFile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsCaretInfo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsLength(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsSelections(CCmdUI * pCmdUI);
	afx_msg void OnUpdateOptionsFileType(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsEncoding(CCmdUI* pCmdUI);
	afx_msg void OnOptionsEditClear();
	afx_msg void OnUpdateOptionsEditClear(CCmdUI* pCmdUI);
	afx_msg void OnOptionsEditRedo();
	afx_msg void OnUpdateOptionsEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnOptionsEditSelectAll();
	afx_msg void OnOptionsEditSelectAllOccurrences();
	afx_msg void OnOptionsEditSelectAllOccurrencesNotMCMW();
	afx_msg void OnOptionsViewLinenumbers();
	afx_msg void OnUpdateOptionsViewLinenumbers(CCmdUI* pCmdUI);
	afx_msg void OnOptionsAddBreakPoint();
	afx_msg void OnUpdateOptionsAddBreakPoint(CCmdUI* pCmdUI);
	afx_msg void OnOptionsDeleteBreakPoint();
	afx_msg void OnUpdateOptionsDeleteBreakPoint(CCmdUI* pCmdUI);
	afx_msg void OnOptionsDeleteAllBreakPoint();
	afx_msg void OnUpdateOptionsDeleteAllBreakPoints(CCmdUI* pCmdUI);
	afx_msg void OnOptionsFindNextBreakPoint();
	afx_msg void OnUpdateOptionsFindNextBreakPoint(CCmdUI* pCmdUI);
	afx_msg void OnOptionsFindPrevBreakPoint();
	afx_msg void OnUpdateOptionsFindPrevBreakPoint(CCmdUI* pCmdUI);
	afx_msg void OnOptionsAddBookmark();
	afx_msg void OnUpdateOptionsAddBookmark(CCmdUI* pCmdUI);
	afx_msg void OnOptionsDeleteBookmark();
	afx_msg void OnUpdateOptionsDeleteBookmark(CCmdUI* pCmdUI);
	afx_msg void OnOptionsDeleteAllBookmark();
	afx_msg void OnUpdateOptionsDeleteAllBookmark(CCmdUI* pCmdUI);
	afx_msg void OnOptionsToggleAutoComplete();
	afx_msg void OnUpdateOptionsToggleAutoComplete(CCmdUI* pCmdUI);
	afx_msg void OnOptionsFindNextBookmark();
	afx_msg void OnOptionsFindPrevBookmark();
	afx_msg void OnOptionsGotopos();
	afx_msg void OnOptionGotoline();
	afx_msg void OnOptionSearch();
	afx_msg void OnOptionReplace();
	afx_msg void OnOptionsForeground();
	afx_msg void OnOptionsBackground();
	afx_msg void OnOptionsWrapLine();
	afx_msg void OnUpdateOptionsWrapLine(CCmdUI* pCmdUI);
	afx_msg void OnOptionsLongLineChecker();
	afx_msg void OnUpdateOptionsLongLineChecker(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
	afx_msg void OnOptionsToggleInsert();
	afx_msg void OnOptionsFoldMargin();
	afx_msg void OnOptionsSelectionMargin();
	afx_msg void OnUpdateOptionsSelectionMargin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsFoldMargin(CCmdUI* pCmdUI);
	afx_msg void OnEditComment();
	afx_msg void OnEditUnComment();
	afx_msg void OnUpdateEditUnComment(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditComment(CCmdUI* pCmdUI);
	afx_msg void OnToggleComment();
	afx_msg void OnBlockComment();
	afx_msg void OnBlockUnComment();
	afx_msg void OnUpdateEditToggleComment(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditBlockComment(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditBlockUnComment(CCmdUI* pCmdUI);
	afx_msg void OnOptionsSelectToEnd();
	afx_msg void OnOptionsSelectToBegin();
	afx_msg void OnOptionsSelectToWordLeft();
	afx_msg void OnOptionsSelectToWordRight();
	afx_msg void OnOptionsSelectToPartLeft();
	afx_msg void OnOptionsSelectToPartRight();
	afx_msg void OnOptionsRemoveDuplicateLineNotKeep();
	afx_msg void OnOptionsRemoveDuplicateLine ();
	afx_msg void OnOptionsRemoveDuplicateWordInLine();
	afx_msg void OnOptionsRemoveDuplicateWord();
	afx_msg void OnOptionsRemoveDuplicateMatchCaseWord();
	afx_msg void OnOptionsRemoveEmptyLine();
	afx_msg void OnOptionsRemoveLineContainX();
	afx_msg void OnOptionsRemoveLineNotContainX();
	afx_msg void OnOptionsTrimLine();
	afx_msg void OnOptionsTrimTrailingLine();
	afx_msg void OnOptionsTrimHeadingLine();
	afx_msg void OnOptionsInsertFileAsText();
	afx_msg void OnOptionsInsertLineAbove();
	afx_msg void OnOptionsInsertLineBelow();
	afx_msg void OnOptionsDuplicateSelection();
	afx_msg void OnOptionsIncreaseSelectionToWordLeft();
	afx_msg void OnOptionsIncreaseSelectionToWordRight();
	afx_msg void OnOptionsIncreaseSelectionToPartLeft();
	afx_msg void OnOptionsIncreaseSelectionToPartRight();
	afx_msg void OnOptionsIncreaseSelectionToWord();
	afx_msg void OnOptionsIncreaseSelectionToQuote();
	afx_msg void OnOptionsIncreaseSelectionToLine();
	afx_msg void OnOptionsDeleteLine();
	afx_msg void OnOptionsSelectionColumnMode();
	afx_msg void OnOptionsInsertXAtBeginLine();
	afx_msg void OnOptionsInsertXAtEndLine();
	afx_msg void OnOptionsInsertEndLineNumberIndex();
	afx_msg void OnOptionsInsertLineNumberIndex();
	afx_msg void OnOptionsInsertLineAlphabetIndex();
	afx_msg void OnOptionsInsertLineRomanIndex();
	afx_msg void OnOptionsSplitLineWithDemiliter();
	afx_msg void OnOptionsJoinLineWithDemiliter();
	afx_msg void OnOptionsSortLineAscending();
	afx_msg void OnOptionsSortLineDescending();
	afx_msg void OnOptionsSortLineAZ();
	afx_msg void OnOptionsSortLineZA();
	afx_msg void OnOptionsMoveSelectedLineUp();
	afx_msg void OnOptionsMoveSelectedLineDown();
	afx_msg void OnOptionsToUpperCase();
	afx_msg void OnOptionsToLowerCase();
	afx_msg void OnOptionsToReverseText();
	afx_msg void OnOptionsToCamelCase();
	afx_msg void OnOptionsToPascalCase();
	afx_msg void OnOptionsToLowerSnakeCase();
	afx_msg void OnOptionsToUpperSnakeCase();
	afx_msg void OnOptionsToPascalSnakeCase();
	afx_msg void OnOptionsToPascalKebabCase();
	afx_msg void OnOptionsToLowerKebabCase();
	afx_msg void OnOptionsToUpperKebabCase();
	afx_msg void OnOptionsToTitleUpperCase();
	afx_msg void OnOptionsToDotCase();
	afx_msg void OnOptionsToSentenceCase();
	afx_msg void OnOptionsPascalCaseToSplitCase();
	afx_msg void OnOptionsSnakeCaseToSplitCase();
	afx_msg void OnOptionsEOLToCRLF();
	afx_msg void OnOptionsEOLToLF();
	afx_msg void OnOptionsEOLToCR();
	afx_msg void OnEditCountWords();
	afx_msg void OnEditCountDuplicateWords();
	afx_msg void OnEditCountDuplicateLines();
	afx_msg void OnEditShowAllCharacter();
	afx_msg void OnEditRemoveFromXToYLine();
	afx_msg void OnEditRemoveAfterWordLine();
	afx_msg void OnEditRemoveBeforWordLine();
	afx_msg void OnEditInsertAfterWordLine();
	afx_msg void OnEditInsertBetweenLines();
	afx_msg void OnEditRemoveSpace();
	afx_msg void OnEditInsertBeforeWordLine();
	afx_msg void OnEditInsertAtPositionLine();
	afx_msg void OnEditConvertToInvertCase();
	afx_msg void OnEditConvertToRandomCase();
	afx_msg void OnEditOpenFromSelection();
	afx_msg void OnEditRevealFromSelection();
	afx_msg void OnUpdateEditShowAllCharacter(CCmdUI * pCmdUI);
	afx_msg void OnEditChangeBidirectional();
	afx_msg void OnUpdateEditChangeBidirectional(CCmdUI * pCmdUI);
	afx_msg void OnOptionsStartMoniterFile();
	afx_msg void OnUpdateStartMoniterFile(CCmdUI * pCmdUI);
	afx_msg void OnOptionsChangeTextLexerCPP();
	afx_msg void OnOptionsChangeTextLexerPython();
	afx_msg void OnOptionsChangeTextLexerHtmlXml();
	afx_msg void OnOptionsChangeTextLexerNon();
	afx_msg void OnOptionAlignLeft();
	afx_msg void OnOptionAlignRight();
	afx_msg void OnOptionAlignCenter();
	afx_msg void OnOptionAlignJustify();
	afx_msg void OnOptionAlignLeftNotKeepLine();
	afx_msg void OnOptionAlignRightNotKeepLine();
	afx_msg void OnOptionAlignCenterNotKeepLine();
	afx_msg void OnOptionAlignJustifyNotKeepLine();
	afx_msg void OnOptionsSwapTwoSelections();
	afx_msg void OnOptionsConvertBackSlashToForwardSlash();
	afx_msg void OnOptionsConvertForwardSlashToBackSlash();
	afx_msg void OnOptionsConvertBackSlashToDoubleSlash();
	afx_msg void OnOptionsEncodeToBase64();
	afx_msg void OnOptionsDecodeFromBase64();
	afx_msg void OnOptionsEncodeToHexa();
	afx_msg void OnOptionsDecodeFromHexa();
	afx_msg void OnOptionsEncodeToDecimal();
	afx_msg void OnOptionsDecodeFromDecimal();
	afx_msg void OnOptionsEncodeToBinary();
	afx_msg void OnOptionsDecodeFromBinary();
	afx_msg void OnOptionsEncodeToOcta();
	afx_msg void OnOptionsDecodeFromOcta();
	afx_msg void OnOptionsGenerateTimeDate();
	afx_msg void OnOptionsDeleteLeftWord();
	afx_msg void OnOptionsDeleteRightWord();
	afx_msg void OnOptionsDeleteToBeginLine();
	afx_msg void OnOptionsDeleteToEndLine();
	afx_msg void OnOptionsRemoveFromCharXToYInLine();
	afx_msg void OnOptionsLineTranspose();
	afx_msg void OnOptionsSplitSelectionIntoLines();
	afx_msg void OnOptionsSelectionAddPreviousLine();
	afx_msg void OnOptionsSelectionAddNextLine();
	afx_msg void OnOptionsUrlEscapse();
	afx_msg void OnOptionsSelectionInvert();

	// run codes
	afx_msg void OnExecutePython();
	afx_msg void OnExecuteHTML();
	afx_msg void OnExecuteCPP();
	afx_msg void OnExecuteJava();
	afx_msg void OnExecuteJavaScript();
	afx_msg void OnExecutePascal();
	afx_msg void OnExecuteCShape();
	afx_msg void OnExecuteC();
	afx_msg void OnExecuteAssembly();
	afx_msg void OnExecuteBatch();
	afx_msg void OnExecutePHP();
	afx_msg void OnExecuteVisualBasic();
	afx_msg void OnExecuteSQL();
	afx_msg void OnExecutePowerShell();
	afx_msg void OnExecuteVerilog();
	afx_msg void OnExecutePerl();
	afx_msg void OnExecuteRuby();
	afx_msg void OnExecuteGo();
	afx_msg void OnExecuteTCL();
	afx_msg void OnExecuteAutoIT();
	afx_msg void OnExecuteRust();
	afx_msg void OnExecuteR();

	// from document menu
	afx_msg void OnDocumentShowSystemMenu();
	afx_msg void OnDocumentSelectToSync();
	afx_msg void OnDocumentExpandAllBrackets();
	afx_msg void OnDocumentCollapseAllBrackets();
	afx_msg void OnDocumentToggleCurrentBracket();
	afx_msg void OnDocumentToggleBracketlevel1();
	afx_msg void OnDocumentToggleBracketlevel2();
	afx_msg void OnDocumentToggleBracketlevel3();
	afx_msg void OnDocumentToggleBracketlevel4();
	afx_msg void OnDocumentToggleBracketlevel5();
	afx_msg void OnDocumentToggleBracketlevel6();
	afx_msg void OnDocumentToggleBracketlevel7();
	afx_msg void OnDocumentToggleBracketlevel8();
	afx_msg void OnDocumentToggleBracketlevel9();
	afx_msg void OnDocumentShowBracketsMap();
	afx_msg void OnDocumentFormatFile();
	afx_msg void OnUpdateDocumentFormatFile(CCmdUI * pCmdUI);
	afx_msg void OnDocumentShowTrackingBar();
	afx_msg void OnUpdateDocumentShowTrackingBar(CCmdUI * pCmdUI);
	afx_msg void OnDocumentSetReadOnly();
	afx_msg void OnUpdateDocumentSetReadOnly(CCmdUI * pCmdUI);
	afx_msg void OnDocumentSetLargeFileEditMode();
	afx_msg void OnUpdateDocumentSetLargeFileEditMode(CCmdUI * pCmdUI);
	afx_msg void OnDocumentHideLines();
	afx_msg void OnDocumentDisplayWhiteSpace();
	afx_msg void OnUpdateDocumentDisplayWhiteSpace(CCmdUI * pCmdUI);
	afx_msg void OnDocumentDisplayEOL();
	afx_msg void OnUpdateDocumentDisplayEOL(CCmdUI * pCmdUI);
	afx_msg void OnDocumentGoogleIt();
	afx_msg void OnDocumentGoogleStackoverflow();
	afx_msg void OnDocumentWikiIt();
	afx_msg void OnDocumentGoogleTranlate();
	afx_msg void OnDocumentTranlateText();
	afx_msg void OnOptionsCopyTranslateResult();
	afx_msg void OnOptionsGenerateTranslateResult();
	afx_msg void OnViewDisplayTabIndentation();
	afx_msg void OnUpdateDisplayTabIndentation(CCmdUI * pCmdUI);
	afx_msg void OnReplace4SpacesByTab();
	afx_msg void OnReplaceTabBy4Spaces();
	afx_msg void OnOptionsDecreaseTabIndentation();
	afx_msg void OnOptionsIncreaseTabIndentation();
	afx_msg void OnFileSummary();
	afx_msg void OnOptionsScrollRightView();
	afx_msg	void OnOptionsScrollLeftView();
	afx_msg void OnOptionsSyncScrollRightView();
	afx_msg void OnOptionsSyncScrollLeftView();
	afx_msg void OnOptionsSyncZoomInView();
	afx_msg void OnOptionsSyncZoomOutView();
	afx_msg void OnOptionsSyncScrollUpView();
	afx_msg void OnOptionsSyncScrollDownView();
	afx_msg void OnOptionsZoomResetView();
	afx_msg void OnOptionsEnableSyncScrolling();
	afx_msg void OnOptionsScrollToCaret();
	afx_msg void OnOptionsLineUp();
	afx_msg void OnOptionsLineDown();
	afx_msg void OnUpdateOptionsSyncVerticalScrolling(CCmdUI * pCmdUI);
	afx_msg void OnAddAutoCompleteFromFile();
	afx_msg void OnAddAutoCompleteFromFolder();
	afx_msg void OnAddAutoCompleteVietnameseDataset();
	afx_msg void OnAddAutoCompleteEnglishDataset();
	afx_msg void OnClearAutoCompleteDataset();
	afx_msg void OnOptionsEditSpellChecker();
	afx_msg void OnOptionsEditMisspelledReplaceWith();
	afx_msg void OnOptionsUpdateEditSpellChecker(CCmdUI * pCmdUI);
	afx_msg void OnOptionsUpdateFileSummary(CCmdUI * pCmdUI);

	// from build menu
	afx_msg void OnOpenFileLanguageConfigPython();
	afx_msg void OnOpenFileLanguageConfigHTML();
	afx_msg void OnOpenFileLanguageConfigCPP();
	afx_msg void OnOpenFileLanguageConfigJavaScript();
	afx_msg void OnOpenFileLanguageConfigC();
	afx_msg void OnOpenFileLanguageConfigCShape();
	afx_msg void OnOpenFileLanguageConfigJava();
	afx_msg void OnOpenFileLanguageConfigAssembly();
	afx_msg void OnOpenFileLanguageConfigBatch();
	afx_msg void OnOpenFileLanguageConfigPascal();
	afx_msg void OnOpenFileLanguageConfigSQL();
	afx_msg void OnOpenFileLanguageConfigPerl();
	afx_msg void OnOpenFileLanguageConfigPHP();
	afx_msg void OnOpenFileLanguageConfigPowerShell();
	afx_msg void OnOpenFileLanguageConfigVerilog();
	afx_msg void OnOpenFileLanguageConfigRuby();
	afx_msg void OnOpenFileLanguageConfigGo();
	afx_msg void OnOpenFileLanguageConfigTCL();
	afx_msg void OnOpenFileLanguageConfigAutoIT();
	afx_msg void OnOpenFileLanguageConfigR();
	afx_msg void OnOpenFileLanguageConfigRust();
	afx_msg void OnOpenFileLanguageConfigVB();

	// from terminal
	afx_msg void OnTerminalRunSelectedText();
	afx_msg void OnTerminalRunActiveFile();
	afx_msg void OnUpdateTerminalRunActiveFile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTerminalRunSelectedText(CCmdUI* pCmdUI);

	// from worker threads
	afx_msg LRESULT OnCompilerNotifyProgress(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCompilerNotifyBuildExitCode(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCompilerNotifyRunExitCode(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCompilerNotifyDebugExitCode(WPARAM wParam, LPARAM lParam);

	// from Tools menu
	afx_msg void OnToolCreateGUID();
	afx_msg void OnToolCreateMd5();
	afx_msg void OnToolCreateCRC();
	afx_msg void OnToolCreateSha256();
	afx_msg void OnToolCreateSha1();

	afx_msg void OnQuickFindAllInFile();
	afx_msg void OnBuildSource();
	afx_msg void OnRemoveAllDebugPointer();

	// debugger Operations
	afx_msg void OnStartDebugger();
	afx_msg void OnShowCallStack();
	afx_msg void OnStopDebugger();
	afx_msg void OnRestartDebugger();
	afx_msg void OnStepOver();
	afx_msg void OnStepInto();
	afx_msg void OnStepOut();
	afx_msg void OnWatchVariableValue();
	afx_msg void OnWatchVariableType();
	afx_msg void OnShowBuildErrors();
	afx_msg void OnGenerateBuildFile();
	afx_msg void OnUpdateStopDebugger(CCmdUI * pCmdUI);
	afx_msg void OnUpdateStartDebugger(CCmdUI * pCmdUI);
	afx_msg void OnUpdateReStartDebugger(CCmdUI * pCmdUI);
	afx_msg void OnUpdateShowCallStack(CCmdUI * pCmdUI);
	afx_msg void OnUpdateStepInto(CCmdUI * pCmdUI);
	afx_msg void OnUpdateStepOver(CCmdUI * pCmdUI);
	afx_msg void OnUpdateStepOut(CCmdUI * pCmdUI);
	afx_msg void OnUpdateWatchVariableValue(CCmdUI * pCmdUI);
	afx_msg void OnUpdateWatchVariableType(CCmdUI * pCmdUI);
	afx_msg void OnUpdateShowBuildErrors(CCmdUI * pCmdUI);
	afx_msg void OnUpdateGenerateBuildFile(CCmdUI* pCmdUI);

protected:

	// general helpers
	void SortLineByOptions(int sortOptions);
	void TrimLine(int trimOption);
	void GetAutoCompleteList(CString strWord, std::vector<CString>& listWord);
	void GetIntellisenseList(CString strPreviousWord, std::vector<CString>& listMethod);
	void AutoIndentationText();
	void ProcessIndentationTab();
	void SelectAllOccurrences(const CString & strWord, int nSearchOption = SCFIND_WHOLEWORD | SCFIND_MATCHCASE);
	void ShowAutoCompleteByAddedWord(CString strWord);
	void UpdateFunctionDocStringMapPython();
	void ShowCallTipPython(CString strLine, CString strWord);
	void ShowFuncProtypeDocPython(CString strLine);
	void ShowIntellisensePython();
	void UpdateFunctionDocStringMapCPP();
	void ShowCallTipCPP(CString strLine, CString strWord);
	void ShowFuncProtypeDocCPP(CString strLine);
	void ShowIntellisenseCPP();
	void ActiveDockWindow(DOCKABLE_PANE_TYPE type);
	void Replace4SpacesByTab(BOOL bTabToSpace);
	BOOL BlockComment(BLOCK_COMMENT_OPERATION blockCommentOperation);
	BOOL Comment();
	BOOL UnComment(BOOL bBlockComment = TRUE);
	BOOL CanResetHightlight();
	void DoFileSaveAs();
	BOOL IsCommentLineCode(const CString& strLine);
	void PushTextToClipBoard(const CString & str);
	void ConvertSlash(int option);
	void TextAlignment(CTextAlignment::Alignment option);
	void TextAlignmentNotKeepLine(CTextAlignment::Alignment option);
	CString TranlateText(CString strSelectedText, int nLineEnd);
	CString GetClipboardPlainText();
	CString GetClipboardAsFormatID(UINT idFormatID);
	void UpdateEditCommandComment(CCmdUI * pCmdUI);
	void GetMatchedWordsOnFile(std::vector<CString>& listWord, const CString & inputChars);
	void ToggleBracketAslevel(int level);
	void StartSpellChecker();
	void CHAR_ADDED_PROCESSOR(SCNotification *pScinNotification);
	void OpenFileLanguageConfig(const CString & strLexerName);
	void AdjustEditorPosition(int cx, int cy);

	void UpdateDockPaneBreakpoint(int nLineNumber, BOOL bDeleteFromList, const CString & strPathName, const CString & strProcessName);
	void UpdateDockPaneBookmark(int nLineNumber, BOOL bDeleteFromList, const CString& strPathName);

	// run program...
	void RunExeAfterCompile();
	void RunGDBDebuggerAfterCompile();
	void RunJavaExeAfterCompile(const CString& strCommandLine);
	void RunJavaDebuggerAfterCompile();

	void DoConvertTextFormat(CONVERT_TEXT_FORMAT formatText, BOOL bEncode);

protected:
	int m_nSpaceDelta = 0;
	int m_nIndicatorPos = 0;
	int m_nIndicatorCount = 0;
	int m_nIncreaseSelectionSearchFlag = 0;
	int m_nOriginalMutilCaretColumn = 0;
	int m_nFirstVisualLineModified = 0;
	int m_encodingUser = TF_INT;
	CString m_czLexerFromFile;
	CString m_strTab;
	CString m_strSelectedWord;
	CString m_strCurrentDocLanguageName;
	BOOL m_bChangedExtensionFile = FALSE;
	BOOL m_bToggleMoniterFileRealTime = FALSE;
	BOOL m_bToggleShowAllCharater = FALSE;
	BOOL m_bActiveIndentationText = FALSE;
	BOOL m_bIsIndicatorChar = FALSE;
	BOOL m_bIsDeltaSpaceEnable = FALSE;
	BOOL m_bDocumentReadOnly = FALSE;
	BOOL m_bUseIntellisense = FALSE;
	BOOL m_bSelectionByMouseDrag = TRUE;
	BOOL m_bIsWatchFileProcessing = FALSE;
	BOOL m_bEnableSpellChecker = FALSE;
	BOOL m_bCtrlPress = FALSE;
	BOOL m_bAlreadyRepainted = FALSE;
	BOOL m_bAlreadyRestoreState = FALSE;
	BOOL m_bBackSpaceKeyDown = FALSE;
	BOOL m_bEnableLargeFileEditMode = FALSE;
	FILETIME m_FileSystemTime = {};
	CEditorCtrl m_EditorCtrl;
	FuncDocStringDataset m_mapFuncDocString;
	FuncProtypeDocStringDataset m_mapFuncProtypeDocString;
	FuntionCalltipDataset m_FuntionCalltipDataset;
	IntellisenseDataset   m_IntellisenseDataset;
	LangKeywordDataset    m_LangKeywordDataset;
	AutoCompelteDataset   m_AutoCompelteDataset;
	UpdateWordsDataset    m_UpdateWordsDataset;
	MatchedLineDataset    m_MatchedLineDataset;
	CSpellChecker         m_SpellChecker;
	std::vector<int>	  m_LineMutilpleCaretsBuffer;
	std::unique_ptr<CVinaTextProgressBar> m_pBuildProgressBar = NULL;
	VINATEXT_SUPPORTED_LANGUAGE m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_TEXT;

public: // for compiler...
	BuildSessionInfo m_BuildSessionInfo;
	void LOG_BUILD_INFO_MESSAGE_SHELL(const CString & strCMD, const CString & m_strCurrentDocLanguageName);
	void LOG_BUILD_INFO_MESSAGE(const CString& strCMD, const CString& strLanguage, BOOL bDebugMode = FALSE, const CString& strFileBuildconfig = _T(""));
};

#ifndef _DEBUG  
inline CEditorDoc* CEditorView::GetEditorDocument() const
{
	return reinterpret_cast<CEditorDoc*>(m_pDocument);
}
#endif