/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VinaTextApp.h"
#endif

#include "MainFrm.h"
#include "EditorDoc.h"
#include "EditorView.h"

#include "GuiUtils.h"
#include "AppUtil.h"
#include "RAIIUtils.h"
#include "MultiThreadWorker.h"
#include "VinaTextProgressBar.h"
#include "EditorDatabase.h"
#include "AppSettings.h"
#include "TemporarySettings.h"
#include "SearchEngine.h"
#include "DirectoryNotifier.h"
#include "Debugger.h"
#include "Compiler.h"
#include "TextFormatConverter.h"
#include "WebHandler.h"
#include "Textfile.h"
#include "StringHelper.h"

#include "MisspelledReplaceWithDlg.h"
#include "EditWithXDlg.h"
#include "SetBookmarkPathDlg.h"
#include "RemoveFromXToYDlg.h"
#include "RemoveAfterBeforeWordDlg.h"
#include "InsertAfterWordInLineDlg.h"
#include "InsertFromPositionXDlg.h"
#include "InsertBetweenLines.h"
#include "BookMarkPathDlg.h"
#include "QuickGotoLine.h"

#include "LocalizationHandler.h"

#pragma warning(disable:4996 4127)

// debug
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// timmer for moniter file changes
#define START_MONITER_FILE_TIMER (WM_APP + 313)
#define MONITER_FILE_INTERVAL 500

// timmer for spell checker
#define START_SPELL_CHECKER_TIMER (WM_APP + 314)
#define SPELL_CHECKER_INTERVAL 500

// tracking bar
#define TRACKING_BAR_LEFT_POSITION 5
#define TRACKING_BAR_LINE_WIDTH 3
#define TRACKING_BAR_OFFSET_TOP 25
#define TRACKING_BAR_OFFSET_BOTTOM 90

// keep current view
#define BACKUP_VISIBLE_EDITOR_STATE \
	int nVisualLine = m_EditorCtrl.GetFirstVisibleLine(); \
	int nCurPos = m_EditorCtrl.GetCurrentPosition();

#define RESTORE_VISIBLE_EDITOR_STATE \
	m_EditorCtrl.SetFirstVisibleLine(nVisualLine); \
	m_EditorCtrl.GotoPosition(nCurPos);

// keep current view for edit operation
#define BACKUP_VISIBLE_EDITOR_STATE_EDIT \
	int nVisualLine = m_EditorCtrl.GetFirstVisibleLine(); \
	m_EditorCtrl.BeginUndoTransactions();

#define RESTORE_VISIBLE_EDITOR_STATE_EDIT \
	m_EditorCtrl.SetFirstVisibleLine(nVisualLine); \
	m_EditorCtrl.EndUndoTransactions();

// sync view actions
#define IMPLEMENT_SYNC_ACTION_VIEW(action) \
	auto fSycnAction = [](CEditorDoc* pDoc) -> void { \
		if (pDoc) { \
			auto pView = pDoc->GetEditorView(); \
			if (pView) { \
				auto pEditor = pView->GetEditorCtrl(); \
				if (pEditor) pEditor->DoCommand(action); \
			} \
		} \
	}; \
	AppUtils::SyncActionAllEditorDocuments(fSycnAction);

// verify sync view actions
#define VERIFY_SYNC_ACTION_VIEW \
if (AppUtils::GetDocumentTypeCount(DOCUMENT_TYPE::DOC_EDITOR) == 1) { \
	AfxMessageBox(_T("This operation requests at least 2 opened text files!")); \
	return; \
}

// CEditorView

IMPLEMENT_DYNCREATE(CEditorView, CViewBase)

BEGIN_MESSAGE_MAP(CEditorView, CViewBase)
	// win api
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_SETFOCUS()

	// from edit menu
	ON_COMMAND(ID_EDIT_COPY, OnOptionsEditCopy)
	ON_COMMAND(ID_OPTIONS_COPY_WITH_QUOTE, OnOptionsEditCopyWithQuote)
	ON_COMMAND(ID_EDIT_COPY_VISIBLE_LINE, OnOptionsEditVisibleCopy)
	ON_COMMAND(ID_EDIT_COPY_HISTORY, OnOptionsEditShowCopyHistory)
	ON_COMMAND(ID_EDIT_CUT, OnOptionsEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateOptionsEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnOptionsEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateOptionsEditPaste)
	ON_COMMAND(ID_EDIT_PASTE_HTML, OnOptionsEditPasteHTML)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_HTML, OnUpdateOptionsEditPasteHTML)
	ON_COMMAND(ID_EDIT_PASTE_RFT, OnOptionsEditPasteRFT)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_RFT, OnUpdateOptionsEditPasteRFT)
	ON_COMMAND(ID_EDIT_PATSE_DOUBLE_QUOTE, OnPasteWithDoubleQuote)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PATSE_DOUBLE_QUOTE, OnUpdateOptionsPasteWithDoubleQuote)
	ON_COMMAND(ID_EDIT_PATSE_FORWARD_SLASH, OnPasteWithForwardSlash)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PATSE_FORWARD_SLASH, OnUpdateOptionsPasteWithForwardSlash)
	ON_COMMAND(ID_EDIT_PATSE_BEGIN_ALL_FILE, OnPasteAtBeginAllFile)
	ON_COMMAND(ID_EDIT_PATSE_END_ALL_FILE, OnPasteAtEndAllFile)
	ON_COMMAND(ID_EDIT_SELECTION_TO_DOUBLE_QUOTE, OnOptionsEditSelectionToDoubleQuote)
	ON_COMMAND(ID_SELECTION_TO_NEXT_PARAGRAPH, OnOptionsEditSelectionToNextParagraph)
	ON_COMMAND(ID_SELECTION_TO_PREV_PARAGRAPH, OnOptionsEditSelectionToPrevParagraph)
	ON_COMMAND(ID_OPTIONS_GOTO_NEXT_PARAGRAPH, OnOptionsEditGotoNextParagraph)
	ON_COMMAND(ID_OPTIONS_GOTO_PREV_PARAGRAPH, OnOptionsEditGotoPrevParagraph)
	ON_COMMAND(ID_EDIT_UNDO, OnOptionsEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateOptionsEditUndo)
	ON_COMMAND(ID_EDIT_UNDO_ALL, OnOptionsEditUndoAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO_ALL, OnUpdateOptionsEditUndoAll)
	ON_COMMAND(ID_EDIT_REDO_ALL, OnOptionsEditRedoAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO_ALL, OnUpdateOptionsEditRedoAll)
	ON_COMMAND(ID_EDIT_UNDO_ALL_FILE, OnOptionsEditUndoAllFile)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO_ALL_FILE, OnUpdateOptionsEditUndoAllFile)
	ON_COMMAND(ID_EDIT_REDO_ALL_FILE, OnOptionsEditRedoAllFile)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO_ALL_FILE, OnUpdateOptionsEditRedoAllFile)
	ON_COMMAND(ID_OPTIONS_VIEW_LINENUMBERS, OnOptionsViewLinenumbers)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_EDITOR_EOL, OnUpdateOptionsEOLInfo)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_CARET_INFO, OnUpdateOptionsCaretInfo)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_MATCHEDS, OnUpdateOptionsLength)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_SELECTIONS, OnUpdateOptionsSelections)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_CURRENT_LANGUAGE, OnUpdateOptionsFileType)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ENCODING, OnUpdateOptionsEncoding)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_VIEW_LINENUMBERS, OnUpdateOptionsViewLinenumbers)
	ON_COMMAND(ID_EDIT_REDO, OnOptionsEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateOptionsEditRedo)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnOptionsEditSelectAll)
	ON_COMMAND(ID_EDIT_SELECT_ALL_SELECTION, OnOptionsEditSelectAllOccurrences)
	ON_COMMAND(ID_EDIT_SELECT_ALL_SELECTION_NOT_MC_MW, OnOptionsEditSelectAllOccurrencesNotMCMW)
	ON_COMMAND(ID_EDITOR_TOGGLE_COMMENT, OnToggleComment)
	ON_COMMAND(ID_EDITOR_BLOCK_COMMENT, OnBlockComment)
	ON_COMMAND(ID_EDITOR_BLOCK_UNCOMMENT, OnBlockUnComment)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_TOGGLE_COMMENT, OnUpdateEditToggleComment)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_BLOCK_COMMENT, OnUpdateEditBlockComment)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_BLOCK_UNCOMMENT, OnUpdateEditBlockUnComment)
	ON_COMMAND(ID_EDITOR_COMMENT, OnEditComment)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_COMMENT, OnUpdateEditComment)
	ON_COMMAND(ID_EDITOR_UNCOMMENT, OnEditUnComment)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_UNCOMMENT, OnUpdateEditUnComment)
	ON_COMMAND(ID_OPTIONS_GOTOLINE, OnOptionGotoline)
	ON_COMMAND(ID_TOGGLE_AUTO_COMPLETE, OnOptionsToggleAutoComplete)
	ON_UPDATE_COMMAND_UI(ID_TOGGLE_AUTO_COMPLETE, OnUpdateOptionsToggleAutoComplete)
	ON_COMMAND(ID_EDIT_FIND, OnOptionSearch)
	ON_COMMAND(ID_EDIT_REPLACE, OnOptionReplace)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_OVR, OnUpdateInsert)
	ON_COMMAND(ID_TOGGLE_INSERT, OnOptionsToggleInsert)
	ON_COMMAND(ID_OPTIONS_FOLD_MARGIN, OnOptionsFoldMargin)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FOLD_MARGIN, OnUpdateOptionsFoldMargin)
	ON_COMMAND(ID_OPTIONS_SELECTION_MARGIN, OnOptionsSelectionMargin)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SELECTION_MARGIN, OnUpdateOptionsSelectionMargin)
	ON_COMMAND(ID_OPTIONS_ADD_NEW_BREAKPOINT, OnOptionsAddBreakPoint)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_ADD_NEW_BREAKPOINT, OnUpdateOptionsAddBreakPoint)
	ON_COMMAND(ID_OPTIONS_DELETE_BREAKPOINT, OnOptionsDeleteBreakPoint)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DELETE_BREAKPOINT, OnUpdateOptionsDeleteBreakPoint)
	ON_COMMAND(ID_OPTIONS_DELETE_ALL_BREAKPOINT, OnOptionsDeleteAllBreakPoint)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DELETE_ALL_BREAKPOINT, OnUpdateOptionsDeleteAllBreakPoints)
	ON_COMMAND(ID_OPTIONS_FIND_NEXT_BREAKPOINT, OnOptionsFindNextBreakPoint)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FIND_NEXT_BREAKPOINT, OnUpdateOptionsFindNextBreakPoint)
	ON_COMMAND(ID_OPTIONS_FIND_PREV_BREAKPOINT, OnOptionsFindPrevBreakPoint)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FIND_PREV_BREAKPOINT, OnUpdateOptionsFindPrevBreakPoint)
	ON_COMMAND(ID_OPTIONS_ADD_BOOKMARK, OnOptionsAddBookmark)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_ADD_BOOKMARK, OnUpdateOptionsAddBookmark)
	ON_COMMAND(ID_OPTIONS_DELETE_BOOKMARK, OnOptionsDeleteBookmark)
	ON_COMMAND(ID_OPTIONS_DELETE_ALL_BOOKMARK, OnOptionsDeleteAllBookmark)
	ON_COMMAND(ID_OPTIONS_FIND_NEXT_BOOKMARK, OnOptionsFindNextBookmark)
	ON_COMMAND(ID_OPTIONS_FIND_PREV_BOOKMARK, OnOptionsFindPrevBookmark)
	ON_COMMAND(ID_OPTIONS_GOTOPOS, OnOptionsGotopos)
	ON_COMMAND(ID_OPTIONS_WRAPLINE, OnOptionsWrapLine)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_WRAPLINE, OnUpdateOptionsWrapLine)
	ON_COMMAND(ID_DISPLAY_LONG_LINE_CHECKER, OnOptionsLongLineChecker)
	ON_UPDATE_COMMAND_UI(ID_DISPLAY_LONG_LINE_CHECKER, OnUpdateOptionsLongLineChecker)
	ON_COMMAND(ID_DOCUMENT_DISPLAY_WHITE_SPACE, OnDocumentDisplayWhiteSpace)
	ON_UPDATE_COMMAND_UI(ID_DOCUMENT_DISPLAY_WHITE_SPACE, OnUpdateDocumentDisplayWhiteSpace)
	ON_COMMAND(ID_OPTIONS_REPLACE_SPACE_BY_TAB, OnReplace4SpacesByTab)
	ON_COMMAND(ID_OPTIONS_REPLACE_TAB_BY_SPACE, OnReplaceTabBy4Spaces)
	ON_COMMAND(ID_DECREASE_TAB_INDENTATION, OnOptionsDecreaseTabIndentation)
	ON_COMMAND(ID_INCREASE_TAB_INDENTATION, OnOptionsIncreaseTabIndentation)
	ON_COMMAND(ID_SELECTION_TO_END_FILE, OnOptionsSelectToEnd)
	ON_COMMAND(ID_SELECTION_TO_BEGIN_FILE, OnOptionsSelectToBegin)
	ON_COMMAND(ID_SELECTION_TO_WORD_LEFT, OnOptionsSelectToWordLeft)
	ON_COMMAND(ID_SELECTION_TO_WORD_RIGHT, OnOptionsSelectToWordRight)
	ON_COMMAND(ID_SELECTION_TO_PART_LEFT, OnOptionsSelectToPartLeft)
	ON_COMMAND(ID_SELECTION_TO_PART_RIGHT, OnOptionsSelectToPartRight)
	ON_COMMAND(ID_EDIT_REMOVE_DUPLICATE_LINE, OnOptionsRemoveDuplicateLine)
	ON_COMMAND(ID_EDIT_REMOVE_DUPLICATE_LINE_NOT_KEEP, OnOptionsRemoveDuplicateLineNotKeep)
	ON_COMMAND(ID_EDIT_REMOVE_DUPLICATE_WORD_IN_LINE, OnOptionsRemoveDuplicateWordInLine)
	ON_COMMAND(ID_EDIT_REMOVE_DUPLICATE_WORD, OnOptionsRemoveDuplicateWord)
	ON_COMMAND(ID_EDIT_REMOVE_DUPLICATE_MACTCH_CASE_WORD, OnOptionsRemoveDuplicateMatchCaseWord)
	ON_COMMAND(ID_EDIT_REMOVE_EMPTY_LINE, OnOptionsRemoveEmptyLine)
	ON_COMMAND(ID_EDIT_DELETE_LINE_CONTAIN, OnOptionsRemoveLineContainX)
	ON_COMMAND(ID_EDIT_DELETE_LINE_NOT_CONTAIN, OnOptionsRemoveLineNotContainX)
	ON_COMMAND(ID_EDIT_TRIM_SPACE_LINE, OnOptionsTrimLine)
	ON_COMMAND(ID_EDIT_REMOVE_TRAILING_SPACE_LINE, OnOptionsTrimTrailingLine)
	ON_COMMAND(ID_EDIT_REMOVE_HEADING_SPACE_LINE, OnOptionsTrimHeadingLine)
	ON_COMMAND(ID_INSERT_FILE_AS_TEXT, OnOptionsInsertFileAsText)
	ON_COMMAND(ID_EDIT_INSERT_LINE_ABOVE, OnOptionsInsertLineAbove)
	ON_COMMAND(ID_EDIT_INSERT_LINE_BELOW, OnOptionsInsertLineBelow)
	ON_COMMAND(ID_EDIT_DUPLICATE_SELECTION, OnOptionsDuplicateSelection)
	ON_COMMAND(ID_EDIT_INSERT_X_AT_BEGIN_LINE, OnOptionsInsertXAtBeginLine)
	ON_COMMAND(ID_EDIT_INSERT_X_AT_END_LINE, OnOptionsInsertXAtEndLine)
	ON_COMMAND(ID_EDIT_INDEXING_NUMBER_LINE, OnOptionsInsertLineNumberIndex)
	ON_COMMAND(ID_EDIT_END_INDEXING_NUMBER_LINE, OnOptionsInsertEndLineNumberIndex)
	ON_COMMAND(ID_EDIT_INDEXING_ALPHABET_LINE, OnOptionsInsertLineAlphabetIndex)
	ON_COMMAND(ID_EDIT_INDEXING_ROMAN_LINE, OnOptionsInsertLineRomanIndex)
	ON_COMMAND(ID_EDIT_SPLIT_LINE_WITH_DEMILITER, OnOptionsSplitLineWithDelimiter)
	ON_COMMAND(ID_EDIT_JOIN_LINE_WITH_DEMILITER, OnOptionsJoinLineWithDelimiter)
	ON_COMMAND(ID_EDIT_SORT_LINE_ASCENDING, OnOptionsSortLineAscending)
	ON_COMMAND(ID_EDIT_SORT_LINE_DECENDING, OnOptionsSortLineDescending)
	ON_COMMAND(ID_EDIT_SORT_LINE_AZ, OnOptionsSortLineAZ)
	ON_COMMAND(ID_EDIT_SORT_LINE_ZA, OnOptionsSortLineZA)
	ON_COMMAND(ID_EDIT_MOVE_SELECTED_LINE_UP, OnOptionsMoveSelectedLineUp)
	ON_COMMAND(ID_EDIT_MOVE_SELECTED_LINE_DOWN, OnOptionsMoveSelectedLineDown)
	ON_COMMAND(ID_DOCUMENT_TO_UPPER_CASE, OnOptionsToUpperCase)
	ON_COMMAND(ID_DOCUMENT_TO_LOWER_CASE, OnOptionsToLowerCase)
	ON_COMMAND(ID_DOCUMENT_TO_REVERSE_TEXT, OnOptionsToReverseText)
	ON_COMMAND(ID_DOCUMENT_TO_UPPER_CASE_CAMEL, OnOptionsToCamelCase)
	ON_COMMAND(ID_DOCUMENT_TO_PASCAL_CASE, OnOptionsToPascalCase)
	ON_COMMAND(ID_DOCUMENT_TO_LOWER_CASE_SNAKE, OnOptionsToLowerSnakeCase)
	ON_COMMAND(ID_DOCUMENT_TO_UPPER_CASE_SNAKE, OnOptionsToUpperSnakeCase)
	ON_COMMAND(ID_DOCUMENT_TO_PASCAL_SNAKE_CASE, OnOptionsToPascalSnakeCase)
	ON_COMMAND(ID_DOCUMENT_TO_PASCAL_KEBAB_CASE, OnOptionsToPascalKebabCase)
	ON_COMMAND(ID_DOCUMENT_TO_LOWER_KEBAB_CASE, OnOptionsToLowerKebabCase)
	ON_COMMAND(ID_DOCUMENT_TO_UPPER_KEBAB_CASE, OnOptionsToUpperKebabCase)
	ON_COMMAND(ID_DOCUMENT_TO_TIILE_UPPER, OnOptionsToTitleUpperCase)
	ON_COMMAND(ID_DOCUMENT_TO_DOT_CASE, OnOptionsToDotCase)
	ON_COMMAND(ID_DOCUMENT_TO_SENTENCE_CASE, OnOptionsToSentenceCase)
	ON_COMMAND(ID_DOCUMENT_PASCAL_CASE_TO_SPLIT_CASE, OnOptionsPascalCaseToSplitCase)
	ON_COMMAND(ID_DOCUMENT_SNAKE_CASE_TO_SPLIT_CASE, OnOptionsSnakeCaseToSplitCase)
	ON_COMMAND(ID_DOCUMENT_DISPLAY_EOL, OnDocumentDisplayEOL)
	ON_UPDATE_COMMAND_UI(ID_DOCUMENT_DISPLAY_EOL, OnUpdateDocumentDisplayEOL)
	ON_COMMAND(ID_EOL_WINDOW_CRLF, OnOptionsEOLToCRLF)
	ON_COMMAND(ID_EOL_LINUX_LF, OnOptionsEOLToLF)
	ON_COMMAND(ID_EOL_MACOS_CR, OnOptionsEOLToCR)
	ON_UPDATE_COMMAND_UI(ID_EOL_WINDOW_CRLF, OnUpdateOptionsEOLToCRLF)
	ON_UPDATE_COMMAND_UI(ID_EOL_LINUX_LF, OnUpdateOptionsEOLToLF)
	ON_UPDATE_COMMAND_UI(ID_EOL_MACOS_CR, OnUpdateOptionsEOLToCR)
	ON_COMMAND(ID_EDIT_COUNT_WORD, OnEditCountWords)
	ON_COMMAND(ID_EDIT_COUNT_DUPLICATE_WORD, OnEditCountDuplicateWords)
	ON_COMMAND(ID_EDIT_COUNT_DUPLICATE_LINE, OnEditCountDuplicateLines)
	ON_COMMAND(ID_EDIT_SHOW_ALL_CHARACTOR, OnEditShowAllCharacter)
	ON_COMMAND(ID_EDIT_REMOVE_FROM_X_Y_LINE, OnEditRemoveFromXToYLine)
	ON_COMMAND(ID_EDIT_REMOVE_AFTER_LINE, OnEditRemoveAfterWordLine)
	ON_COMMAND(ID_EDIT_REMOVE_BEFORE_LINE, OnEditRemoveBeforWordLine)
	ON_COMMAND(ID_EDIT_INSERT_X_BEFORE_WORD_LINE, OnEditInsertBeforeWordLine)
	ON_COMMAND(ID_EDIT_INSERT_X_AFTER_WORD_LINE, OnEditInsertAfterWordLine)
	ON_COMMAND(ID_VIEW_INSERT_BETWEEN_LINE, OnEditInsertBetweenLines)
	ON_COMMAND(ID_EDIT_REMOVE_SPACE, OnEditRemoveSpace)
	ON_COMMAND(ID_EDIT_INSERT_X_AT_POSITION_LINE, OnEditInsertAtPositionLine)
	ON_COMMAND(ID_DOCUMENT_TO_INVERT_CASE, OnEditConvertToInvertCase)
	ON_COMMAND(ID_DOCUMENT_TO_RANDOM_CASE, OnEditConvertToRandomCase)
	ON_COMMAND(ID_EDIT_OPEN_FROM_SELECTION, OnEditOpenFromSelection)
	ON_COMMAND(ID_EDIT_REVEAL_PATH_FROM_SELECTION, OnEditRevealFromSelection)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SHOW_ALL_CHARACTOR, OnUpdateEditShowAllCharacter)
	ON_COMMAND(ID_CHANGE_TEXT_BIDIRECTIONAL, OnEditChangeBidirectional)
	ON_UPDATE_COMMAND_UI(ID_CHANGE_TEXT_BIDIRECTIONAL, OnUpdateEditChangeBidirectional)
	ON_COMMAND(ID_START_MONITER_FILE, OnOptionsStartMoniterFile)
	ON_UPDATE_COMMAND_UI(ID_START_MONITER_FILE, OnUpdateStartMoniterFile)
	ON_COMMAND(ID_DOCUMENT_TEXT_LEXER_CPP, OnEnableUserLexerLexerCPP)
	ON_COMMAND(ID_DOCUMENT_TEXT_LEXER_PYTHON, OnEnableUserLexerLexerPython)
	ON_COMMAND(ID_DOCUMENT_TEXT_LEXER_HTML_XML, OnEnableUserLexerLexerHtmlXml)
	ON_COMMAND(ID_DOCUMENT_TEXT_LEXER_BASH_BATCH, OnEnableUserLexerLexerBashBatch)
	ON_COMMAND(ID_DOCUMENT_TEXT_LEXER_VB_PASCAL, OnEnableUserLexerLexerVBPascal)
	ON_COMMAND(ID_DOCUMENT_TEXT_LEXER_NON, OnDisableUserLexer)
    ON_COMMAND(ID_DOCUMENT_TEXT_LEXER_EXTENSION, OnAddLexerForFileExtension)
	ON_COMMAND(ID_EDIT_ALIGN_LEFT, OnOptionAlignLeft)
	ON_COMMAND(ID_EDIT_ALIGN_RIGHT, OnOptionAlignRight)
	ON_COMMAND(ID_EDIT_ALIGN_CENTER, OnOptionAlignCenter)
	ON_COMMAND(ID_EDIT_ALIGN_JUSTIFY, OnOptionAlignJustify)
	ON_COMMAND(ID_EDIT_ALIGN_LEFT_MOT_KEEP_LINE, OnOptionAlignLeftNotKeepLine)
	ON_COMMAND(ID_EDIT_ALIGN_RIGHT_MOT_KEEP_LINE, OnOptionAlignRightNotKeepLine)
	ON_COMMAND(ID_EDIT_ALIGN_CENTER_MOT_KEEP_LINE, OnOptionAlignCenterNotKeepLine)
	ON_COMMAND(ID_EDIT_ALIGN_JUSTIFY_MOT_KEEP_LINE, OnOptionAlignJustifyNotKeepLine)
	ON_COMMAND(ID_EDIT_SWAP_TWO_SELECTIONS, OnOptionsSwapTwoSelections)
	ON_COMMAND(ID_EDIT_CONVERT_BACKSLASH_TO_FOWARDSLASH, OnOptionsConvertBackSlashToForwardSlash)
	ON_COMMAND(ID_EDIT_CONVERT_FOWARDSLASH_TO_BACKSLASH, OnOptionsConvertForwardSlashToBackSlash)
	ON_COMMAND(ID_EDIT_CONVERT_BACKSLASH_TO_DOUBLESLASH, OnOptionsConvertBackSlashToDoubleSlash)
	ON_COMMAND(ID_DOCUMENT_TRANSLATE_COPY, OnOptionsCopyTranslateResult)
	ON_COMMAND(ID_DOCUMENT_TRANSLATE_GENERATE, OnOptionsGenerateTranslateResult)
	ON_COMMAND(ID_VIEW_ZOOM_IN, OnOptionsSyncZoomInView)
	ON_COMMAND(ID_VIEW_ZOOM_OUT, OnOptionsSyncZoomOutView)
	ON_COMMAND(ID_VIEW_ZOOM_RESET, OnOptionsZoomResetView)
	ON_COMMAND(ID_EDIT_SYNC_SCROLL_VIEW, OnOptionsEnableSyncScrolling)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SYNC_SCROLL_VIEW, OnUpdateOptionsSyncVerticalScrolling)
	ON_COMMAND(ID_TOOL_TO_BASE64, OnOptionsEncodeToBase64)
	ON_COMMAND(ID_TOOLS_CONVERT_TEXT_TO_HEXA, OnOptionsEncodeToHexa)
	ON_COMMAND(ID_TOOLS_CONVERT_TEXT_TO_DECIMAL, OnOptionsEncodeToDecimal)
	ON_COMMAND(ID_TOOLS_CONVERT_TEXT_TO_BINARY, OnOptionsEncodeToBinary)
	ON_COMMAND(ID_TOOLS_CONVERT_TEXT_TO_OCTA, OnOptionsEncodeToOcta)
	ON_COMMAND(ID_TOOL_FROM_BASE64, OnOptionsDecodeFromBase64)
	ON_COMMAND(ID_TOOLS_CONVERT_TEXT_FROM_HEXA, OnOptionsDecodeFromHexa)
	ON_COMMAND(ID_TOOLS_CONVERT_TEXT_FROM_DECIMAL, OnOptionsDecodeFromDecimal)
	ON_COMMAND(ID_TOOLS_CONVERT_TEXT_FROM_BINARY, OnOptionsDecodeFromBinary)
	ON_COMMAND(ID_TOOLS_CONVERT_TEXT_FROM_OCTA, OnOptionsDecodeFromOcta)
	ON_COMMAND(ID_EDIT_SCROLL_TO_CARET, OnOptionsScrollToCaret)

	// from debug menu
	ON_COMMAND(ID_DEBUGGER_START, OnStartDebugger)
	ON_COMMAND(ID_DEBUGGER_STOP, OnStopDebugger)
	ON_COMMAND(ID_DEBUGGER_VARIABLE_VALUE, OnWatchVariableValue)
	ON_COMMAND(ID_DEBUGGER_VARIABLE_TYPE, OnWatchVariableType)
	ON_COMMAND(ID_DEBUGGER_CALL_STACK, OnShowCallStack)
	ON_COMMAND(ID_DEBUGGER_RESTART, OnRestartDebugger)
	ON_COMMAND(ID_DEBUGGER_STEPINTO, OnStepInto)
	ON_COMMAND(ID_DEBUGGER_STEPOVER, OnStepOver)
	ON_COMMAND(ID_DEBUGGER_STEPOUT, OnStepOut)
	ON_COMMAND(ID_OPTIONS_SHOW_ERROR, OnShowBuildErrors)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_RESTART, OnUpdateReStartDebugger)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_CALL_STACK, OnUpdateShowCallStack)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_STEPINTO, OnUpdateStepInto)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_STEPOVER, OnUpdateStepOver)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_STEPOUT, OnUpdateStepOut)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_STOP, OnUpdateStopDebugger)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_START, OnUpdateStartDebugger)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_VARIABLE_VALUE, OnUpdateWatchVariableValue)
	ON_UPDATE_COMMAND_UI(ID_DEBUGGER_VARIABLE_TYPE, OnUpdateWatchVariableType)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SHOW_ERROR, OnUpdateShowBuildErrors)

	// from terminal...
	ON_COMMAND(ID_RUN_SELECTED_TEXT, OnTerminalRunSelectedText)
	ON_UPDATE_COMMAND_UI(ID_RUN_SELECTED_TEXT, OnUpdateTerminalRunSelectedText)
	ON_COMMAND(ID_RUN_ACTIVE_FILE, OnTerminalRunActiveFile)
	ON_UPDATE_COMMAND_UI(ID_RUN_ACTIVE_FILE, OnUpdateTerminalRunActiveFile)
	ON_COMMAND(ID_RUN_ACTIVE_FILE_AS_ADMIN, OnTerminalRunActiveFileAsAdmin)
	ON_UPDATE_COMMAND_UI(ID_RUN_ACTIVE_FILE_AS_ADMIN, OnUpdateTerminalRunActiveFileAsAdmin)

	// from compiler...
	ON_MESSAGE(UWM_GUI_WORKER_HANDLER_NOTIFY_PROGRESS, OnCompilerNotifyProgress)
	ON_MESSAGE(UWM_GUI_WORKER_HANDLER_BUILD_NOTIFY_EXIT_CODE, OnCompilerNotifyBuildExitCode)
	ON_MESSAGE(UWM_GUI_WORKER_HANDLER_RUN_NOTIFY_EXIT_CODE, OnCompilerNotifyRunExitCode)
	ON_MESSAGE(UWM_GUI_WORKER_HANDLER_DEBUG_NOTIFY_EXIT_CODE, OnCompilerNotifyDebugExitCode)

	// from Editor menu
	ON_COMMAND(ID_DOCUMENT_SHOW_MENU_SYSTEM, OnDocumentShowSystemMenu)
	ON_COMMAND(ID_DOCUMENT_COMPARE_SYNC, OnDocumentSelectToSync)
	ON_COMMAND(ID_DOCUMENT_EXPAND_BRACKETS, OnDocumentExpandAllBrackets)
	ON_COMMAND(ID_DOCUMENT_COLLAPSE_BRACKETS, OnDocumentCollapseAllBrackets)
	ON_COMMAND(ID_DOCUMENT_TOGGLE_CURRENT_BRACKET, OnDocumentToggleCurrentBracket)
	ON_COMMAND(ID_DOCUMENT_TOGGLE_BRACKETS_LEVEL_1, OnDocumentToggleBracketlevel1)
	ON_COMMAND(ID_DOCUMENT_TOGGLE_BRACKETS_LEVEL_2, OnDocumentToggleBracketlevel2)
	ON_COMMAND(ID_DOCUMENT_TOGGLE_BRACKETS_LEVEL_3, OnDocumentToggleBracketlevel3)
	ON_COMMAND(ID_DOCUMENT_TOGGLE_BRACKETS_LEVEL_4, OnDocumentToggleBracketlevel4)
	ON_COMMAND(ID_DOCUMENT_TOGGLE_BRACKETS_LEVEL_5, OnDocumentToggleBracketlevel5)
	ON_COMMAND(ID_DOCUMENT_TOGGLE_BRACKETS_LEVEL_6, OnDocumentToggleBracketlevel6)
	ON_COMMAND(ID_DOCUMENT_TOGGLE_BRACKETS_LEVEL_7, OnDocumentToggleBracketlevel7)
	ON_COMMAND(ID_DOCUMENT_TOGGLE_BRACKETS_LEVEL_8, OnDocumentToggleBracketlevel8)
	ON_COMMAND(ID_DOCUMENT_TOGGLE_BRACKETS_LEVEL_9, OnDocumentToggleBracketlevel9)
	ON_COMMAND(ID_DOCUMENT_SHOW_FUNCTION_LIST, OnDocumentShowBracketsMap)
	ON_COMMAND(ID_DOCUMENT_FORMAT_FILE, OnDocumentFormatFile)
	ON_UPDATE_COMMAND_UI(ID_DOCUMENT_FORMAT_FILE, OnUpdateDocumentFormatFile)
	ON_COMMAND(ID_EDITOR_SHOW_TRACKING_BAR, OnDocumentShowTrackingBar)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_SHOW_TRACKING_BAR, OnUpdateDocumentShowTrackingBar)
	ON_COMMAND(ID_DOCUMENT_SET_READ_ONLY, OnDocumentSetReadOnly)
	ON_UPDATE_COMMAND_UI(ID_DOCUMENT_SET_READ_ONLY, OnUpdateDocumentSetReadOnly)
	ON_COMMAND(ID_DOCUMENT_SET_EDIT_LARGE_FILE, OnDocumentSetLargeFileEditMode)
	ON_UPDATE_COMMAND_UI(ID_DOCUMENT_SET_EDIT_LARGE_FILE, OnUpdateDocumentSetLargeFileEditMode)
	ON_COMMAND(ID_DOCUMENT_HIDE_LINES, OnDocumentHideLines)
	ON_COMMAND(ID_DOCUMENT_GOOGLE_IT, OnDocumentGoogleIt)
	ON_COMMAND(ID_DOCUMENT_GOOGLE_STACKOVERFLOW, OnDocumentGoogleStackoverflow)
	ON_COMMAND(ID_DOCUMENT_WIKI_IT,  OnDocumentWikiIt)
	ON_COMMAND(ID_DOCUMENT_TRANSLATE_WEB, OnDocumentGoogleTranlate)
	ON_COMMAND(ID_DOCUMENT_TRANSLATE, OnDocumentTranlateText)
	ON_COMMAND(ID_DISPLAY_TAB_INDENT, OnViewDisplayTabIndentation)
	ON_UPDATE_COMMAND_UI(ID_DISPLAY_TAB_INDENT, OnUpdateDisplayTabIndentation)
	ON_COMMAND(ID_EDIT_EMPTY_CLIPBOARD, OnEmptyClipboard)
	ON_COMMAND(ID_SELECTION_TO_WORD, OnOptionsIncreaseSelectionToWord)
	ON_COMMAND(ID_SELECTION_TO_QUOTE, OnOptionsIncreaseSelectionToQuote)
	ON_COMMAND(ID_SELECTION_TO_LINE, OnOptionsIncreaseSelectionToLine)
	ON_COMMAND(ID_EDIT_DELETE_LINE, OnOptionsDeleteLine)
	ON_COMMAND(ID_SELECTION_WITH_COLUMN_MODE, OnOptionsSelectionColumnMode)
	ON_COMMAND(ID_DELETE_LEFT_WORD, OnOptionsDeleteLeftWord)
	ON_COMMAND(ID_DELETE_RIGHT_WORD, OnOptionsDeleteRightWord)
	ON_COMMAND(ID_DELETE_TO_BEGIN_LINE, OnOptionsDeleteToBeginLine)
	ON_COMMAND(ID_DELETE_TO_END_LINE, OnOptionsDeleteToEndLine)
	ON_COMMAND(ID_EDIT_REMOVE_FROM_CHAR_X_Y_LINE, OnOptionsRemoveFromCharXToYInLine)
	ON_COMMAND(ID_LINE_TRANSPOSE, OnOptionsLineTranspose)
	ON_COMMAND(ID_SPLIT_SELECTION_INTO_LINES, OnOptionsSplitSelectionIntoLines)
	ON_COMMAND(ID_ADD_PREIVOUS_LINE_SELECTION, OnOptionsSelectionAddPreviousLine)
	ON_COMMAND(ID_ADD_NEXT_LINE_SELECTION, OnOptionsSelectionAddNextLine)
	ON_COMMAND(ID_INVERT_SELECTION, OnOptionsSelectionInvert)

	// load auto complete data set from external resource
	ON_COMMAND(ID_DOCUMENT_ADD_AC_DATASET_FROM_FILE, OnAddAutoCompleteFromFile)
	ON_COMMAND(ID_DOCUMENT_ADD_AC_DATASET_FROM_FOLDER, OnAddAutoCompleteFromFolder)
	ON_COMMAND(ID_DOCUMENT_ADD_AC_DATASET_ENGLISH, OnAddAutoCompleteEnglishDataset)
	ON_COMMAND(ID_DOCUMENT_CLEAR_AC_DATASET, OnClearAutoCompleteDataset)

	ON_COMMAND(ID_EDIT_SPELL_CHECK, OnOptionsEditSpellChecker)
	ON_COMMAND(ID_EDIT_SPELL_CHECK_REPLACE, OnOptionsEditMisspelledReplaceWith)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SPELL_CHECK, OnOptionsUpdateEditSpellChecker)

	// from Tools menu
	ON_COMMAND(ID_TOOL_CREATE_GUID, OnToolCreateGUID)
	ON_COMMAND(ID_TOOL_CREATE_MD5, OnToolCreateMd5)
	ON_COMMAND(ID_TOOL_CREATE_CRC, OnToolCreateCRC)
	ON_COMMAND(ID_TOOL_CREATE_SHA256, OnToolCreateSha256)
	ON_COMMAND(ID_TOOL_CREATE_SHA1, OnToolCreateSha1)
	ON_COMMAND(ID_TOOL_CREATE_TIMEDATE, OnOptionsGenerateTimeDate)
	ON_COMMAND(ID_DOCUMENT_FILE_SUMMARY, OnFileSummary)
	ON_UPDATE_COMMAND_UI(ID_DOCUMENT_FILE_SUMMARY, OnOptionsUpdateFileSummary)

	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_PYTHON, OnOpenFileLanguageConfigPython)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_HTML, OnOpenFileLanguageConfigHTML)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_CPP, OnOpenFileLanguageConfigCPP)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_JAVASCRIPT, OnOpenFileLanguageConfigJavaScript)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_C, OnOpenFileLanguageConfigC)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_CSHAPE, OnOpenFileLanguageConfigCShape)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_JAVA, OnOpenFileLanguageConfigJava)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_ASSEMBLY, OnOpenFileLanguageConfigAssembly)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_BATCH, OnOpenFileLanguageConfigBatch)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_PASCAL, OnOpenFileLanguageConfigPascal)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_SQL, OnOpenFileLanguageConfigSQL)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_PERL, OnOpenFileLanguageConfigPerl)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_PHP, OnOpenFileLanguageConfigPHP)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_POWERSHELL, OnOpenFileLanguageConfigPowerShell)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_VERILOG, OnOpenFileLanguageConfigVerilog)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_RUBY, OnOpenFileLanguageConfigRuby)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_GO, OnOpenFileLanguageConfigGo)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_TCL, OnOpenFileLanguageConfigTCL)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_AUTOIT, OnOpenFileLanguageConfigAutoIT)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_R, OnOpenFileLanguageConfigR)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_RUST, OnOpenFileLanguageConfigRust)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_VISUALBASIC, OnOpenFileLanguageConfigVisualBasic)
	ON_COMMAND(ID_LANGUAGE_FILE_CONFIG_FREEBASIC, OnOpenFileLanguageConfigFreeBasic)

END_MESSAGE_MAP()

// CEditorView construction/destruction

CEditorView::~CEditorView()
{
	CEditorDoc *pDoc = GetEditorDocument();
	if (pDoc && PathFileExists(pDoc->GetPathName()))
	{
		VinaTextDebugger.RemoveBreakPointDataInFile(pDoc->GetPathName());
	}
}

BOOL CEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CViewBase::PreCreateWindow(cs);
}

// CEditorView drawing

int CEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CViewBase::OnCreate(lpCreateStruct) == -1) return -1;
	CRect rectEditor;
	rectEditor.SetRectEmpty();
	m_EditorCtrl.Create(_T("VinaText Editor"), WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_EX_RTLREADING, rectEditor, this, ID_EDITOR_EDIT_CTRL);
	if (::IsWindow(m_EditorCtrl.GetSafeHwnd()) == NULL)
	{
		TRACE(_T("[Error] The VinaText editor not created."));
		return -1;
	}
	return 0;
}

void CEditorView::OnDraw(CDC* pDC)
{
	if (AppSettingMgr.m_bShowTrackingBar && m_MatchedLineDataset.size() > 0)
	{
		CEditorDoc* pDoc = GetEditorDocument();
		ASSERT_VALID(pDoc);
		if (pDoc)
		{
			CRect rect;
			GetClientRect(&rect);
			int nRectHeight = rect.Height();
			CPen pen(PS_SOLID, TRACKING_BAR_LINE_WIDTH, BasicColors::red);
			CPen* pOldPen = pDC->SelectObject(&pen);
			for (auto const& line : m_MatchedLineDataset)
			{
				int nY = line * (nRectHeight - TRACKING_BAR_OFFSET_BOTTOM) / m_EditorCtrl.GetLineCount() + TRACKING_BAR_OFFSET_TOP;
				pDC->MoveTo(rect.Width() - TRACKING_BAR_LEFT_POSITION, nY);
				pDC->LineTo(rect.Width(), nY);
			}
			pDC->SelectObject(pOldPen);
		}
	}
}

BOOL CEditorView::PreTranslateMessage(MSG * pMsg)
{
	switch (pMsg->message)
	{
		case WM_RBUTTONDOWN:
		{
			if ((GetKeyState(VK_CONTROL) & 0x8000))
			{
				// return TRUE to keep multiple carets when open context menu
				return TRUE;
			}
			else if ((GetKeyState(VK_SHIFT) & 0x8000))
			{
				OnDocumentShowSystemMenu();
				return TRUE;
			}
			break;
		}
		case WM_MOUSEWHEEL:
		{
			short sDelta = GET_WHEEL_DELTA_WPARAM(pMsg->wParam);
			if (AppSettingMgr.m_bEnableSynchronizeScrolling)
			{
				if ((GetKeyState(VK_SHIFT) & 0x8000))
				{
					if (sDelta > 0) // wheel mouse up
					{
						OnOptionsSyncScrollLeftView();
					}
					else
					{
						OnOptionsSyncScrollRightView();
					}
					return TRUE;
				}
				else
				{
					if (sDelta > 0) // wheel mouse up
					{
						OnOptionsSyncScrollUpView();
					}
					else
					{
						OnOptionsSyncScrollDownView();
					}
					return TRUE;
				}
			}
			else
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000))
				{
					if (sDelta > 0) // wheel mouse up
					{
						OnOptionsSyncZoomInView();
					}
					else
					{
						OnOptionsSyncZoomOutView();
					}
					return TRUE;
				}
				else if ((GetKeyState(VK_SHIFT) & 0x8000))
				{
					if (sDelta > 0) // wheel mouse up
					{
						OnOptionsScrollLeftView();
					}
					else
					{
						OnOptionsScrollRightView();
					}
					return TRUE;
				}
			}
			break;
		}
		case WM_MBUTTONDOWN:
		{
			OnOptionsScrollToCaret();
			return TRUE;
		}
		case WM_SYSKEYUP:
		case WM_KEYUP:
		{
			switch (pMsg->wParam)
			{
				case VK_MENU:
					if (m_EditorCtrl.IsMultiOrRectangleSelection())
					{
						m_EditorCtrl.SetFocus();
						return TRUE;
					}
					break;
			}
			break;
		}
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		{
			if (AfxGetMainWnd()->PreTranslateMessage(pMsg))
			{
				return TRUE;
			}
			else
			{
				switch (pMsg->wParam)
				{
				case VK_F5:
					if (GetKeyState(VK_SHIFT) & 0x8000)
					{
						OnStopDebugger();
						break;
					}
					OnStartDebugger();
					break;
				case 'D':
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
					{
						OnOptionsDuplicateSelection();
						return TRUE;
					}
					else if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnOptionsIncreaseSelectionToWord();
						return TRUE;
					}
					break;
				case 'R':
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
					{
						OnEditChangeBidirectional();
						return TRUE;
					}
					else if (GetKeyState(VK_CONTROL) & 0x8000)
					{
						OnOptionsToReverseText();
						return TRUE;
					}
					break;
				case 'C':
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
					{
						OnEditComment();
						return TRUE;
					}
					else if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_MENU) & 0x8000))
					{
						OnShowCallStack();
						return TRUE;
					}
					break;
				case 'V':
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
					{
						OnPasteWithDoubleQuote();
						return TRUE;
					}
					break;
				case 'X':
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
					{
						OnEditUnComment();
						return TRUE;
					}
					break;
				case 'M':
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
					{
						m_EditorCtrl.ToggleAllFoldings();
						return TRUE;
					}
					else if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						m_EditorCtrl.ToggleCurrentFolding();
						return TRUE;
					}
					else if ((GetKeyState(VK_MENU) & 0x8000))
					{
						OnDocumentShowBracketsMap();
						return TRUE;
					}
					break;
				case 'I':
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
					{
						OnOptionsSelectionInvert();
						return TRUE;
					}
					else if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnEditConvertToInvertCase();
						return TRUE;
					}
					break;
				case 'J':
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
					{
						OnDocumentFormatFile();
						return TRUE;
					}
					else if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnDocumentSetReadOnly();
						return TRUE;
					}
					break;
				case 'S':
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
					{
						DoFileSaveAs();
						return TRUE;
					}
					break;
				case 'L':
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
					{
						OnOptionsDeleteLine();
						return TRUE;
					}
					else if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnOptionsIncreaseSelectionToLine();
						return TRUE;
					}
					else if ((GetKeyState(VK_MENU) & 0x8000))
					{
						OnOptionsSplitSelectionIntoLines();
						return TRUE;
					}
					break;
				case 'K':
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
					{
						OnBlockUnComment();
						return TRUE;
					}
					else if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnBlockComment();
						return TRUE;
					}
					else if ((GetKeyState(VK_MENU) & 0x8000))
					{
						OnToggleComment();
						return TRUE;
					}
					break;
				case 'G':
					if (GetKeyState(VK_CONTROL) & 0x8000)
					{
						OnOptionGotoline();
						return TRUE;
					}
					break;
				case 'Q':
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnEditShowAllCharacter();
						return TRUE;
					}
					break;
				case 'A':
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
					{
						CString strSelectedWord = m_EditorCtrl.GetSelectedText();
						if (strSelectedWord.IsEmpty())
						{
							OnOptionsIncreaseSelectionToQuote();
						}
						else if (strSelectedWord.GetLength() < m_EditorCtrl.GetTextLength())
						{
							SelectAllOccurrences(strSelectedWord, SCFIND_NONE);
						}
						return TRUE;
					}
					else if (GetKeyState(VK_CONTROL) & 0x8000)
					{
						CString strSelectedWord = m_EditorCtrl.GetSelectedText();
						if (strSelectedWord.IsEmpty())
						{
							OnOptionsEditSelectAll();
						}
						else if (strSelectedWord.GetLength() < m_EditorCtrl.GetTextLength())
						{
							SelectAllOccurrences(strSelectedWord);
						}
						return TRUE;
					}
					else if ((GetKeyState(VK_MENU) & 0x8000))
					{
						OnOptionsToggleAutoComplete();
						return TRUE;
					}
					break;
				case VK_OEM_102:
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnOptionsIncreaseSelectionToPartRight();
						return TRUE;
					}
					break;
				case VK_RETURN:
					if (AppSettingMgr.m_bEnableProcessIndentationTab && AppUtils::IsLanguageSupportLexer(m_CurrentDocLanguage) && !m_bEnableLargeFileEditMode)
					{
						AutoIndentationText();
					}
					break;
				case VK_SPACE:
					if (GetKeyState(VK_CONTROL) & 0x8000)
					{
						CString strWord = m_EditorCtrl.GetRecentAddedText();
						if (!strWord.IsEmpty())
						{
							ShowAutoCompleteByAddedWord(strWord);
						}
						return TRUE;
					}
					break;
				case VK_DELETE:
				{
					if (m_EditorCtrl.IsTextSelected())
					{
						m_EditorCtrl.Clear();
					}
					else 
					{
						m_EditorCtrl.RemoveTextRange(m_EditorCtrl.GetCurrentPosition(), 1);
					}
					return TRUE;
				}
				case VK_BACK:
					m_bBackSpaceKeyDown = TRUE;
					break;
				case VK_F1:
					OnDocumentTranlateText();
					return TRUE;
				case VK_F3:
					OnDocumentGoogleIt();
					return TRUE;
				case VK_F10:
					OnStepOver();
					return TRUE;
				case VK_F11:
					if ((GetKeyState(VK_SHIFT) & 0x8000))
					{
						OnStepOut();
						return TRUE;
					}
					else
					{
						OnStepInto();
						return TRUE;
					}
				case VK_F12:
					if ((GetKeyState(VK_SHIFT) & 0x8000))
					{
						OnWatchVariableType();
						return TRUE;
					}
					else
					{
						OnWatchVariableValue();
						return TRUE;
					}
				case VK_UP:
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
					{
						OnOptionsMoveSelectedLineUp();
						return TRUE;
					}
					else if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_MENU) & 0x8000))
					{
						OnOptionsSelectionAddPreviousLine();
						return TRUE;
					}
					break;
				case VK_DOWN:
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
					{
						OnOptionsMoveSelectedLineDown();
						return TRUE;
					}
					else if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_MENU) & 0x8000))
					{
						OnOptionsSelectionAddNextLine();
						return TRUE;
					}
					break;
				}
			}
		}
		break;
	}
	return CViewBase::PreTranslateMessage(pMsg);
}

void CEditorView::OnInitialUpdate()
{
	CViewBase::OnInitialUpdate();
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;
	CEditorDoc *pDoc = GetEditorDocument();
	if (!pDoc) return;
	// view will create an empty editor when path file does not exist, so do not need to check path exist
	CString strEditorPathName = pDoc->GetPathName();

	if (AppSettingMgr.m_bCheckFileSizeBeforeOpen && PathUtils::GetFileSize(strEditorPathName) > FILE_SIZE_LIMITATION)
	{
		if (IDNO == AfxMessageBox(_T("[File Size Warning] This file is very big, continue open?"), MB_YESNO | MB_ICONWARNING))
		{
			return;
		}
	}

	if (strEditorPathName.IsEmpty())
	{
		pDoc->SetTitle(AppSettingMgr.CreateDocumentUndefTitle());
		// set default new file eol
		m_EditorCtrl.DoCommand(SCI_SETEOLMODE, AppSettingMgr.m_DefaultFileEOL);
	}
	else
	{
		// load file content to editor
		m_EditorCtrl.LoadFile(strEditorPathName, m_encodingUser);
		pDoc->SetModifiedFlag(FALSE); // disable save file when file path exist
	}

	// set the modification notifications
	m_EditorCtrl.SetModEventMask(SCI_MODEVENTMASK_FULL);

	// init editor style
	CLanguageDatabase* pDatabase = pDoc->GetDocLanguageDatabase();
	if (!pDatabase) return;
	m_EditorCtrl.InitilizeSetting(pDatabase);
	m_EditorCtrl.ResetUndoSavePoint();
	m_EditorCtrl.ResetMapUndoRedoSelection();
	m_LangKeywordDataset = AppUtils::SplitterCString(pDatabase->GetLanguageKeyWords(), " ");

	// update MDI tab Icon
	if (m_EditorCtrl.IsReadOnlyEditor())
	{
		m_bDocumentReadOnly = TRUE;
		pFrame->PostMessage(WM_COMMAND, (WPARAM)UMW_SET_READ_ONLY_TAB_MDI);
		pFrame->PostMessage(WM_COMMAND, (WPARAM)UMW_SET_COLOR_ACTIVE_TAB_MDI);
	}

	// check last write time point
	UpdateFileLastWriteTime(strEditorPathName);

	// return previous state
	if (AppSettingMgr.m_bKeepPreviousEditorState && PathFileExists(strEditorPathName))
	{
		RecentEditorInfo info = AppSettingMgr.GetRecentEditorCaretInfo(strEditorPathName);
		if (!info._nWrapMode)
		{
			m_EditorCtrl.SetFirstVisibleLine(info._nFirstVisibleLine);
			m_EditorCtrl.SetCurrentAnchor(info._nCurrentPosition);
			m_EditorCtrl.SetCurrentPosition(info._nCurrentPosition);
			m_bAlreadyRestoreState = TRUE;
		}
	}
}

void CEditorView::OnActivateView(BOOL bActivate, CView * pActivateView, CView * pDeactiveView)
{
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
	DetectCurrentDocLanguage();
	if (AppSettingMgr.m_bRevealExplorerWhenSwitchFile)
	{
		pFrame->OnOpenFileExplorer();
	}
	if (AppUtils::GetMainFrame()->GetQuickSearchDialog())
		pFrame->QuickSearchDialogChangedActiveTab();
	pFrame->PostMessage(WM_COMMAND, (WPARAM)UMW_SET_READ_ONLY_TAB_MDI);
	pFrame->PostMessage(WM_COMMAND, (WPARAM)UMW_SET_COLOR_ACTIVE_TAB_MDI);
}

CString CEditorView::DetectCurrentDocLanguage()
{
	if (m_czLexerFromFile != m_EditorCtrl.GetLexerName())
	{
		m_strCurrentDocLanguageName.Empty();
		m_czLexerFromFile = m_EditorCtrl.GetLexerName();
		m_bChangedExtensionFile = TRUE;
	}
	else
	{
		m_bChangedExtensionFile = FALSE; return m_strCurrentDocLanguageName;
	}
	if (m_czLexerFromFile == "c")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C;
		m_strCurrentDocLanguageName = _T("C");
	}
	else if (m_czLexerFromFile == "cpp")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP;
		m_strCurrentDocLanguageName = _T("C++");
	}
	else if (m_czLexerFromFile == "python")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON;
		m_strCurrentDocLanguageName = _T("Python");
	}
	else if (m_czLexerFromFile == "cs")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CSHAPE;
		m_strCurrentDocLanguageName = _T("C#");
	}
	else if (m_czLexerFromFile == "batch")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_BATCH;
		m_strCurrentDocLanguageName = _T("Batch Script");
	}
	else if (m_czLexerFromFile == "pascal")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL;
		m_strCurrentDocLanguageName = _T("Pascal");
	}
	else if (m_czLexerFromFile == "java")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA;
		m_strCurrentDocLanguageName = _T("Java");
	}
	else if (m_czLexerFromFile == "javascript")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT;
		m_strCurrentDocLanguageName = _T("Javascript");
	}
	else if (m_czLexerFromFile == "phpscript")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PHP;
		m_strCurrentDocLanguageName = _T("PHP");
	}
	else if (m_czLexerFromFile == "sql")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_SQL;
		m_strCurrentDocLanguageName = _T("SQL");
	}
	else if (m_czLexerFromFile == "vb")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VISUALBASIC;
		m_strCurrentDocLanguageName = _T("Visual Basic");
	}
	else if (m_czLexerFromFile == "asm")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_ASSEMBLY;
		m_strCurrentDocLanguageName = _T("Asm");
	}
	else if (m_czLexerFromFile == "inno")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_INNOSETTUP;
		m_strCurrentDocLanguageName = _T("Innosetup Script");
	}
	else if (m_czLexerFromFile == "perl")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PERL;
		m_strCurrentDocLanguageName = _T("Perl");
	}
	else if (m_czLexerFromFile == "golang")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_GOLANG;
		m_strCurrentDocLanguageName = _T("GoLang");
	}
	else if (m_czLexerFromFile == "rust")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUST;
		m_strCurrentDocLanguageName = _T("Rust");
	}
	else if (m_czLexerFromFile == "ruby")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUBY;
		m_strCurrentDocLanguageName = _T("Ruby");
	}
	else if (m_czLexerFromFile == "matlab")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_MATLAB;
		m_strCurrentDocLanguageName = _T("Matlab");
	}
	else if (m_czLexerFromFile == "tcl")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_TCL;
		m_strCurrentDocLanguageName = _T("TCL Script");
	}
	else if (m_czLexerFromFile == "autoit")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_AUTOIT;
		m_strCurrentDocLanguageName = _T("AutoIT Script");
	}
	else if (m_czLexerFromFile == "verilog")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VERILOG;
		m_strCurrentDocLanguageName = _T("Verilog");
	}
	else if (m_czLexerFromFile == "r")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_R;
		m_strCurrentDocLanguageName = _T("R Language");
	}
	else if (m_czLexerFromFile == "powershell")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_POWERSHELL;
		m_strCurrentDocLanguageName = _T("PowerShell");
	}
	else if (m_czLexerFromFile == "hypertext")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_HTML;
		m_strCurrentDocLanguageName = _T("HTML");
	}
	else if (m_czLexerFromFile == "xml")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_XML;
		m_strCurrentDocLanguageName = _T("XML");
	}
	else if (m_czLexerFromFile == "kix")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JSON;
		m_strCurrentDocLanguageName = _T("JSON");
	}
	else if (m_czLexerFromFile == "markdown")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_MARKDOWN;
		m_strCurrentDocLanguageName = _T("Markdown Script");
	}
	else if (m_czLexerFromFile == "typescript")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_TYPESCRIPT;
		m_strCurrentDocLanguageName = _T("Typescript");
	}
	else if (m_czLexerFromFile == "protobuf")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PROTOBUF;
		m_strCurrentDocLanguageName = _T("Google Protobuf");
	}
	else if (m_czLexerFromFile == "css")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CSS;
		m_strCurrentDocLanguageName = _T("CSS");
	}
	else if (m_czLexerFromFile == "FLEXlm")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_FLEXLM;
		m_strCurrentDocLanguageName = _T("FLEXlm Script");
	}
	else if (m_czLexerFromFile == "freebasic")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_FREEBASIC;
		m_strCurrentDocLanguageName = _T("FreeBASIC");
	}
	else if (m_czLexerFromFile == "makefile")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_MAKEFILE;
		m_strCurrentDocLanguageName = _T("Makefile Script");
	}
	else if (m_czLexerFromFile == "cmake")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CMAKE;
		m_strCurrentDocLanguageName = _T("CMake Script");
	}
	else if (m_czLexerFromFile == "vcxproj")
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VCXPROJECT;
		m_strCurrentDocLanguageName = _T("Visual Studio Project");
	}
	else
	{
		m_CurrentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_TEXT;
		m_strCurrentDocLanguageName = AppUtils::GetFileTypeByExtension(m_EditorCtrl.GetFileExtension());
	}
	return m_strCurrentDocLanguageName;
}

void CEditorView::LOG_BUILD_INFO_MESSAGE_SHELL(const CString& strCMD, const CString& m_strCurrentDocLanguageName)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;
	pFrame->ClearDataOnDockPane(DOCKABLE_PANE_TYPE::BUILD_PANE);
	LOG_BUILD_INFO_MESSAGE(strCMD, m_strCurrentDocLanguageName);
}

void CEditorView::LOG_BUILD_INFO_MESSAGE(const CString& strCMD, const CString& m_strCurrentDocLanguageName, BOOL bDebugMode, const CString& strFileBuildconfig /*= _T("")*/)
{
	m_EditorCtrl.ClearAllAnnotationText();
	if (m_pDocument->IsModified())
	{
		if (AppSettingMgr.m_bAutoSaveDocumentWhenbuild)
		{
			m_pDocument->OnSaveDocument(m_pDocument->GetPathName());
		}
		else
		{
			LOG_BUILD_MESSAGE_COLOR(_T("[Build Warning] Current file has been modified but not saved yet. This build will used previous script data...\n"), BasicColors::orange);
		}
	}
	CString strPathName = m_pDocument->GetPathName();
	CString strFileName = PathUtils::GetFilenameFromPath(strPathName);
	CString strFileNameNoExt = PathUtils::GetFileNameWithoutExtension(strFileName);
	CString strBuildMode= bDebugMode ? _T("debug mode") : _T("release mode");
	CString strTitleBuild = _T(">------ VinaText build started | Project: %s | Configuration: %s for Windows platform ------");
	strTitleBuild.Format(strTitleBuild, strFileNameNoExt, strBuildMode);
	CString strCurrentTime = OSUtils::DateToCStringABDHMSY(OSUtils::GetCurrentTimeEx());
	LOG_BUILD_MESSAGE_COLOR(strTitleBuild, IS_LIGHT_THEME? BasicColors::black : BasicColors::light_orange);
	LOG_BUILD_MESSAGE_COLOR(_T("[SystemTime] ") + strCurrentTime, IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
	LOG_BUILD_MESSAGE_COLOR(_T("[MainFile] " + strPathName), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
	LOG_BUILD_MESSAGE_COLOR(_T("[Language] " + m_strCurrentDocLanguageName), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
	LOG_BUILD_MESSAGE_COLOR(_T("[CommandLine] ") + strCMD, IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
	if (PathFileExists(strFileBuildconfig))
	{
		CString strMessage = _T("[Message] Generated file build configuration %s...");
		strMessage.Format(strMessage, strFileBuildconfig);
		LOG_BUILD_MESSAGE_COLOR(strMessage, IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
	}
	if (bDebugMode)
	{
		LOG_BUILD_MESSAGE_COLOR(_T("[Message] Start build process for debug mode..."), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
	}
	else
	{
		LOG_BUILD_MESSAGE_COLOR(_T("[Message] Start build process for release mode..."), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
	}
	ActiveDockWindow(DOCKABLE_PANE_TYPE::BUILD_PANE);
}

BOOL CEditorView::CHAR_ADDED_PROCESSOR(SCNotification * pScinNotification)
{
	if (m_EditorCtrl.GetSelectionNumber() == SINGLE_SELECTION)
	{
		if (pScinNotification->ch == '{')
		{
			int lcurPos = m_EditorCtrl.GetCurrentPosition();
			int nChar = m_EditorCtrl.GetCharacterAtPosition(lcurPos);
			if (nChar == '\t' || nChar == '\n' || nChar == '\r' || nChar == ' ' || nChar == ')' || nChar == '}' || nChar == ']' || lcurPos == m_EditorCtrl.GetTextLength())
			{
				m_EditorCtrl.InsertText(_T("}"), lcurPos);
				return FALSE;
			}
		}
		else if (pScinNotification->ch == '[')
		{
			int lcurPos = m_EditorCtrl.GetCurrentPosition();
			int nChar = m_EditorCtrl.GetCharacterAtPosition(lcurPos);
			if (nChar == '\t' || nChar == '\n' || nChar == '\r' || nChar == ' ' || nChar == ')' || nChar == '}' || nChar == ']' || lcurPos == m_EditorCtrl.GetTextLength())
			{
				m_EditorCtrl.InsertText(_T("]"), lcurPos);
				return FALSE;
			}
		}
		else if (pScinNotification->ch == '(')
		{
			int lcurPos = m_EditorCtrl.GetCurrentPosition();
			int nChar = m_EditorCtrl.GetCharacterAtPosition(lcurPos);
			if (nChar == '\t' || nChar == '\n' || nChar == '\r' || nChar == ' ' || nChar == ')' || nChar == '}' || nChar == ']' || lcurPos == m_EditorCtrl.GetTextLength())
			{
				m_EditorCtrl.InsertText(_T(")"), lcurPos);
				return FALSE;
			}
		}
	}
	return TRUE;
}

void CEditorView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == START_MONITER_FILE_TIMER)
	{
		if (!m_bIsWatchFileProcessing)
		{
			WatchFileSystemState();
		}
	}
	else if (nIDEvent == START_SPELL_CHECKER_TIMER)
	{
		if (m_bEnableSpellChecker)
		{
			KillTimer(START_SPELL_CHECKER_TIMER);
			StartSpellChecker();
		}
	}
	CViewBase::OnTimer(nIDEvent);
}

void CEditorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	CEditorDoc *pDoc = GetEditorDocument();
	ASSERT(pDoc);
	if (!pDoc) return;

	CMenu menu;
	if (menu.LoadMenu(IDR_EDITOR_POPUP))
	{
		CMenu* pSubMenu = menu.GetSubMenu(0);
#pragma warning(suppress: 26496)
		AFXASSUME(pSubMenu != NULL);
		if (!pSubMenu) return;
		VinaTextLocalization.TranslateContextMenu(pSubMenu);

		CString stSelectedScript = m_EditorCtrl.GetSelectedText().Trim();

		//clang-format and can be used to format C/C++/Java/JavaScript/Objective-C/Protobuf/C# code
		if (m_CurrentDocLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
			&& m_CurrentDocLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
			&& m_CurrentDocLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CSHAPE
			&& m_CurrentDocLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA
			&& m_CurrentDocLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT
			&& m_CurrentDocLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_HTML
			&& m_CurrentDocLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_XML
			&& m_CurrentDocLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON
			&& m_CurrentDocLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JSON
			&& m_CurrentDocLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_TYPESCRIPT
			&& m_CurrentDocLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PROTOBUF
			|| m_EditorCtrl.IsReadOnlyEditor())
		{
			pSubMenu->DeleteMenu(ID_DOCUMENT_FORMAT_FILE, MF_BYCOMMAND);
		}

		CLanguageDatabase* pDatabase = GetLanguageDatabase();
		if (pDatabase && (pDatabase->GetLanguageCommentEnd().IsEmpty() &&
			pDatabase->GetLanguageCommentStart().IsEmpty() &&
			pDatabase->GetLanguageCommentSymbol().IsEmpty())
			|| m_EditorCtrl.IsReadOnlyEditor())
		{
			pSubMenu->DeleteMenu(ID_EDITOR_COMMENT, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_EDITOR_UNCOMMENT, MF_BYCOMMAND);
		}

		if (!PathFileExists(stSelectedScript))
		{
			pSubMenu->DeleteMenu(ID_EDIT_OPEN_FROM_SELECTION, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_EDIT_REVEAL_PATH_FROM_SELECTION, MF_BYCOMMAND);
		}

		if (!PathFileExists(pDoc->GetPathName()))
		{
			pSubMenu->DeleteMenu(ID_DOCUMENT_SHOW_MENU_SYSTEM, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_DOCUMENT_FILE_SUMMARY, MF_BYCOMMAND);
		}

		if (m_EditorCtrl.IsReadOnlyEditor())
		{
			pSubMenu->DeleteMenu(ID_EDIT_CUT, MF_BYCOMMAND);
			pSubMenu->RemoveMenu(2, MF_BYPOSITION);
			pSubMenu->CheckMenuItem(ID_DOCUMENT_SET_READ_ONLY, MF_CHECKED | MF_BYCOMMAND);
		}

		if (m_bToggleShowAllCharater)
		{
			pSubMenu->CheckMenuItem(ID_EDIT_SHOW_ALL_CHARACTOR, MF_CHECKED | MF_BYCOMMAND);
		}

		if (m_bToggleMoniterFileRealTime)
		{
			pSubMenu->CheckMenuItem(ID_START_MONITER_FILE, MF_CHECKED | MF_BYCOMMAND);
		}
		
		if (m_EditorCtrl.IsEditorInWrapMode())
		{
			pSubMenu->CheckMenuItem(ID_OPTIONS_WRAPLINE, MF_CHECKED | MF_BYCOMMAND);
		}

		if (m_EditorCtrl.GetBidirectionalRightToLeft())
		{
			pSubMenu->CheckMenuItem(ID_CHANGE_TEXT_BIDIRECTIONAL, MF_CHECKED | MF_BYCOMMAND);
		}

		if (m_EditorCtrl.GetDisplayLinenumbers())
		{
			pSubMenu->CheckMenuItem(ID_OPTIONS_VIEW_LINENUMBERS, MF_CHECKED | MF_BYCOMMAND);
		}

		if (m_EditorCtrl.GetDisplaySelection())
		{
			pSubMenu->CheckMenuItem(ID_OPTIONS_SELECTION_MARGIN, MF_CHECKED | MF_BYCOMMAND);
		}

		if (m_EditorCtrl.GetDisplayFolding())
		{
			pSubMenu->CheckMenuItem(ID_OPTIONS_FOLD_MARGIN, MF_CHECKED | MF_BYCOMMAND);
		}

		if (AppSettingMgr.m_bEnableAutoComplete)
		{
			pSubMenu->CheckMenuItem(ID_TOGGLE_AUTO_COMPLETE, MF_CHECKED | MF_BYCOMMAND);
		}

		if (m_bEnableSpellChecker)
		{
			pSubMenu->CheckMenuItem(ID_EDIT_SPELL_CHECK, MF_CHECKED | MF_BYCOMMAND);
			pSubMenu->AppendMenu(MF_STRING , ID_EDIT_SPELL_CHECK_REPLACE, _T("Missspelled Replace With..."));
		}

		m_EditorCtrl.SetContextMenuPopupFlag(TRUE);
		// system menu style
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		m_EditorCtrl.SetContextMenuPopupFlag(FALSE);
	}
	SetFocus();
}

BOOL CEditorView::SaveFileAndInitilizeEditor(const CString& szPath)
{
	BOOL bSaveResult = m_EditorCtrl.SaveFile(szPath);
	if (bSaveResult && !TemporarySettings.m_bIsClosingMainFrame)
	{
		DetectCurrentDocLanguage();
		CLanguageDatabase* pDatabase = GetLanguageDatabase();
		if (pDatabase)
		{
			m_EditorCtrl.InitilizeSetting(pDatabase);
			if (m_bChangedExtensionFile)
			{
				m_LangKeywordDataset = AppUtils::SplitterCString(pDatabase->GetLanguageKeyWords(), " ");
				if (m_czLexerFromFile.IsEmpty())
				{
					m_LangKeywordDataset.clear();
				}
			}
		}
		// update modified time
		UpdateFileLastWriteTime(szPath);
	}
	return bSaveResult;
}

void CEditorView::Replace4SpacesByTab(BOOL bTabToSpace)
{
	CString strEditorScript;
	int nVisualLine = m_EditorCtrl.GetFirstVisibleLine();
	m_EditorCtrl.GetText(strEditorScript);
	if (bTabToSpace)
	{
		strEditorScript.Replace(EDITOR_TAB, EDITOR_TAB_4SPACE);
	}
	else
	{
		strEditorScript.Replace(EDITOR_TAB_4SPACE, EDITOR_TAB);
	}
	m_EditorCtrl.SetTextToEditor(strEditorScript);
	m_EditorCtrl.SetFirstVisibleLine(nVisualLine);
}

void CEditorView::OnEditComment()
{
#if 0
	auto pLangDatabase = GetLanguageDatabase();
	if (!pLangDatabase) return;
	CString strCommentBlockStart = pLangDatabase->GetLanguageCommentStart().Trim();
	CString strCommentBlockEnd = pLangDatabase->GetLanguageCommentEnd().Trim();
	if (strCommentBlockStart.IsEmpty() || strCommentBlockEnd.IsEmpty()) return;

	m_EditorCtrl.BeginUndoTransactions();

	CString strInput = m_EditorCtrl.GetSelectedText();
	if (strInput.IsEmpty())
	{
		int nCurrentLine = m_EditorCtrl.GetCurrentLine();
		m_EditorCtrl.GetTextFromLine(nCurrentLine, strInput);
		CString strTemp = strInput;
		if (strTemp.Trim().IsEmpty()) return;
		int pos0 = m_EditorCtrl.GetLineStartPosition(nCurrentLine - 1);
		int pos1 = AppUtils::FindFirstCharacterNotOf(strInput, _T(" \t"));
		int pos2 = m_EditorCtrl.GetLineEndPosition(nCurrentLine - 1);
		m_EditorCtrl.InsertText(strCommentBlockStart, pos0 + pos1);
		m_EditorCtrl.InsertText(strCommentBlockEnd, pos2 + 2);
	}
	else
	{
		int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
		int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
		m_EditorCtrl.InsertText(strCommentBlockStart, lStartPos);
		m_EditorCtrl.InsertText(strCommentBlockEnd, lEndPos + 2);
	}

	m_EditorCtrl.EndUndoTransactions();
#endif
	BlockComment(BLOCK_COMMENT_OPERATION::COMMENT_ACTION);
}

void CEditorView::OnEditUnComment()
{
#if 0
	auto pLangDatabase = GetLanguageDatabase();
	if (!pLangDatabase) return;
	CString strCommentBlockStart = pLangDatabase->GetLanguageCommentStart().Trim();
	CString strCommentBlockEnd = pLangDatabase->GetLanguageCommentEnd().Trim();
	if (strCommentBlockStart.IsEmpty() || strCommentBlockEnd.IsEmpty()) return;

	m_EditorCtrl.BeginUndoTransactions();

	CString strInput = m_EditorCtrl.GetSelectedText();
	if (strInput.IsEmpty())
	{
		int nCurrentLine = m_EditorCtrl.GetCurrentLine();
		m_EditorCtrl.GetTextFromLine(nCurrentLine, strInput);
		CString strTemp = strInput;
		if (strTemp.Trim().IsEmpty()) return;
		int pos0 = m_EditorCtrl.GetLineStartPosition(nCurrentLine - 1);
		int pos1 = AppUtils::FindFirstCharacterNotOf(strInput, _T(" \t"));
		int pos2 = m_EditorCtrl.GetLineEndPosition(nCurrentLine - 1);
		m_EditorCtrl.InsertText(strCommentBlockStart, pos0 + pos1);
		m_EditorCtrl.InsertText(strCommentBlockEnd, pos2 + 2);
	}
	else
	{
		int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
		int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
		m_EditorCtrl.InsertText(strCommentBlockStart, lStartPos);
		m_EditorCtrl.InsertText(strCommentBlockEnd, lEndPos + 2);
	}

	m_EditorCtrl.EndUndoTransactions();
#endif
	BlockComment(BLOCK_COMMENT_OPERATION::UNCOMMENT_ACTION);
}

void CEditorView::OnUpdateEditUnComment(CCmdUI * pCmdUI)
{
	UpdateEditCommandComment(pCmdUI);
}

void CEditorView::OnUpdateEditComment(CCmdUI * pCmdUI)
{
	UpdateEditCommandComment(pCmdUI);
}

void CEditorView::OnToggleComment()
{
#if 0
	auto pLangDatabase = GetLanguageDatabase();
	if (!pLangDatabase) return;
	CString strCommentBlockStart = pLangDatabase->GetLanguageCommentStart().Trim();
	CString strCommentBlockEnd = pLangDatabase->GetLanguageCommentEnd().Trim();
	if (strCommentBlockStart.IsEmpty() || strCommentBlockEnd.IsEmpty()) return;

	m_EditorCtrl.BeginUndoTransactions();

	CString strInput = m_EditorCtrl.GetSelectedText();
	if (strInput.IsEmpty())
	{
		int nCurrentLine = m_EditorCtrl.GetCurrentLine();
		m_EditorCtrl.GetTextFromLine(nCurrentLine, strInput);
		CString strTemp = strInput;
		if (strTemp.Trim().IsEmpty()) return;
		int pos0 = m_EditorCtrl.GetLineStartPosition(nCurrentLine - 1);
		int pos1 = AppUtils::FindFirstCharacterNotOf(strInput, _T(" \t"));
		int pos2 = m_EditorCtrl.GetLineEndPosition(nCurrentLine - 1);
		m_EditorCtrl.InsertText(strCommentBlockStart, pos0 + pos1);
		m_EditorCtrl.InsertText(strCommentBlockEnd, pos2 + 2);
	}
	else
	{
		int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
		int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
		m_EditorCtrl.InsertText(strCommentBlockStart, lStartPos);
		m_EditorCtrl.InsertText(strCommentBlockEnd, lEndPos + 2);
	}

	m_EditorCtrl.EndUndoTransactions();
#endif
	BlockComment(BLOCK_COMMENT_OPERATION::TOGGLE_ACTION);
}

void CEditorView::OnBlockComment()
{
#if 0
	auto pLangDatabase = GetLanguageDatabase();
	if (!pLangDatabase) return;
	CString strCommentBlockStart = pLangDatabase->GetLanguageCommentStart().Trim();
	CString strCommentBlockEnd = pLangDatabase->GetLanguageCommentEnd().Trim();
	if (strCommentBlockStart.IsEmpty() || strCommentBlockEnd.IsEmpty()) return;

	m_EditorCtrl.BeginUndoTransactions();

	CString strInput = m_EditorCtrl.GetSelectedText();
	if (strInput.IsEmpty())
	{
		int nCurrentLine = m_EditorCtrl.GetCurrentLine();
		m_EditorCtrl.GetTextFromLine(nCurrentLine, strInput);
		CString strTemp = strInput;
		if (strTemp.Trim().IsEmpty()) return;
		int pos0 = m_EditorCtrl.GetLineStartPosition(nCurrentLine - 1);
		int pos1 = AppUtils::FindFirstCharacterNotOf(strInput, _T(" \t"));
		int pos2 = m_EditorCtrl.GetLineEndPosition(nCurrentLine - 1);
		m_EditorCtrl.InsertText(strCommentBlockStart, pos0 + pos1);
		m_EditorCtrl.InsertText(strCommentBlockEnd, pos2 + 2);
	}
	else
	{
		int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
		int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
		m_EditorCtrl.InsertText(strCommentBlockStart, lStartPos);
		m_EditorCtrl.InsertText(strCommentBlockEnd, lEndPos + 2);
	}

	m_EditorCtrl.EndUndoTransactions();
#endif
	Comment();
}

void CEditorView::OnBlockUnComment()
{
#if 0
	auto pLangDatabase = GetLanguageDatabase();
	if (!pLangDatabase) return;
	CString strCommentSymbol = pLangDatabase->GetLanguageCommentSymbol().Trim();
	if (strCommentSymbol.IsEmpty()) return;

	CString strInput = m_EditorCtrl.GetSelectedText();
	if (strInput.IsEmpty())
	{
		int nCurrentLine = m_EditorCtrl.GetCurrentLine();
		m_EditorCtrl.GetTextFromLine(nCurrentLine, strInput);

		CString strTemp = strInput;
		if (strTemp.Trim().Left(2) == pLangDatabase->GetLanguageCommentStart()
			&& strTemp.Trim().Right(2) == pLangDatabase->GetLanguageCommentEnd())
		{
			int pos = AppUtils::FindFirstCharacterNotOf(strInput, _T(" \t,."));
			if (pos == -1) return;
			strInput = strInput.Mid(0, pos) + strTemp.Mid(2, strTemp.GetLength() - 4);
		}
		else
		{
			if (strInput == m_EditorCtrl.GetEOLCString()) return;
			int pos = AppUtils::FindFirstCharacterNotOf(strInput, _T(" \t,."));
			if (pos == -1) return;
			CString strCmp = strInput.Mid(pos, 1);
			if (strCommentSymbol.GetLength() == 2)
			{
				strCmp = strInput.Mid(pos, 2);
			}
			if (strCmp == strCommentSymbol)
			{
				CString str = strInput.Mid(0, pos) + strInput.Mid(pos + 1);
				if (strCommentSymbol.GetLength() == 2)
				{
					str = strInput.Mid(0, pos) + strInput.Mid(pos + 2);
				}
				strInput = str;
			}
		}
		int lselected_startpos = (int)m_EditorCtrl.DoCommand(SCI_POSITIONFROMLINE, nCurrentLine - 1, 0);
		int lselected_endpos = (int)m_EditorCtrl.DoCommand(SCI_GETLINEENDPOSITION, nCurrentLine - 1, 0);
		m_EditorCtrl.DoCommand(SCI_SETTARGETRANGE, lselected_startpos, lselected_endpos);

		char* bufUtf8 = NULL;
		CREATE_BUFFER_FROM_CSTRING(bufUtf8, strInput)
			m_EditorCtrl.DoCommand(SCI_REPLACETARGET, strInput.GetLength(), (LPARAM)bufUtf8);
		DELETE_POINTER_CPP_ARRAY(bufUtf8);

		m_EditorCtrl.DoCommand(SCI_SETSEL, lselected_startpos, lselected_startpos + strInput.GetLength());
	}
	else
	{
		CString strInputNew;
		CString strTemp = strInput;
		if (strTemp.Trim().Left(2) == pLangDatabase->GetLanguageCommentStart()
			&& strTemp.Trim().Right(2) == pLangDatabase->GetLanguageCommentEnd())
		{
			int pos = AppUtils::FindFirstCharacterNotOf(strInput, _T(" \t,."));
			if (pos == -1)
			{
				return;
			}
			strInputNew = strInput.Mid(0, pos) + strTemp.Mid(2, strTemp.GetLength() - 4);
		}
		else
		{
			CStringArray arrLine;
			AppUtils::SplitCString(strInput, m_EditorCtrl.GetEOLCString(), arrLine);
			for (int i = 0; i < arrLine.GetSize(); ++i)
			{
				if (arrLine[i] == m_EditorCtrl.GetEOLCString() || arrLine[i].IsEmpty()) continue;
				int pos = AppUtils::FindFirstCharacterNotOf(arrLine[i], _T(" \t,."));
				if (pos == -1)
				{
					return;
				}
				CString strCmp = arrLine[i].Mid(pos, 1);
				if (strCommentSymbol.GetLength() == 2)
				{
					strCmp = arrLine[i].Mid(pos, 2);
				}
				if (strCmp == strCommentSymbol)
				{
					CString str = arrLine[i].Mid(0, pos) + arrLine[i].Mid(pos + 1);
					if (strCommentSymbol.GetLength() == 2)
					{
						str = arrLine[i].Mid(0, pos) + arrLine[i].Mid(pos + 2);
					}
					strInputNew.Append(str);
					if (i != arrLine.GetSize() - 1)
					{
						strInputNew.Append(m_EditorCtrl.GetEOLCString());
					}
				}
				else
				{
					CString str = +arrLine[i];
					strInputNew.Append(str);
					if (i != arrLine.GetSize() - 1)
					{
						strInputNew.Append(m_EditorCtrl.GetEOLCString());
					}
				}
			}
		}
		int lselected_startpos = (int)m_EditorCtrl.GetSelectionStartPosition();
		int lselected_endpos = (int)m_EditorCtrl.GetSelectionEndPosition();
		m_EditorCtrl.DoCommand(SCI_SETTARGETRANGE, lselected_startpos, lselected_endpos);

		char* bufUtf8 = NULL;
		CREATE_BUFFER_FROM_CSTRING(bufUtf8, strInputNew)
			m_EditorCtrl.DoCommand(SCI_REPLACETARGET, strInputNew.GetLength(), (LPARAM)bufUtf8);
		DELETE_POINTER_CPP_ARRAY(bufUtf8);
		m_EditorCtrl.DoCommand(SCI_SETSEL, lselected_startpos, lselected_startpos + strInputNew.GetLength());
	}
#endif
	UnComment();
}

void CEditorView::UpdateEditCommandComment(CCmdUI * pCmdUI)
{
	CLanguageDatabase* pDatabase = GetLanguageDatabase();
	if (pDatabase && (pDatabase->GetLanguageCommentEnd().IsEmpty() &&
		pDatabase->GetLanguageCommentStart().IsEmpty() &&
		pDatabase->GetLanguageCommentSymbol().IsEmpty())
		|| m_EditorCtrl.IsReadOnlyEditor())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CEditorView::OnUpdateEditToggleComment(CCmdUI * pCmdUI)
{
	UpdateEditCommandComment(pCmdUI);
}

void CEditorView::OnUpdateEditBlockComment(CCmdUI * pCmdUI)
{
	UpdateEditCommandComment(pCmdUI);
}

void CEditorView::OnUpdateEditBlockUnComment(CCmdUI * pCmdUI)
{
	UpdateEditCommandComment(pCmdUI);
}

BOOL CEditorView::BlockComment(BLOCK_COMMENT_OPERATION blockCommentOperation)
{
#if 0
	auto pLangDatabase = GetLanguageDatabase();
	if (!pLangDatabase) return;
	CString strCommentSymbol = pLangDatabase->GetLanguageCommentSymbol().Trim();
	if (strCommentSymbol.IsEmpty()) return;

	m_EditorCtrl.BeginUndoTransactions();

	CString strInput = m_EditorCtrl.GetSelectedText();
	if (strInput.IsEmpty())
	{
		int nCurrentLine = m_EditorCtrl.GetCurrentLine();
		m_EditorCtrl.GetTextFromLine(nCurrentLine, strInput);
		CString strTemp = strInput;
		if (strTemp.Trim().IsEmpty()) return;
		int pos0 = m_EditorCtrl.GetLineStartPosition(nCurrentLine - 1);
		int pos1 = AppUtils::FindFirstCharacterNotOf(strInput, _T(" \t"));
		m_EditorCtrl.InsertText(strCommentSymbol, pos0 + pos1);
	}
	else
	{
		int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
		int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
		int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
		int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);

		for (int i = lLineStart; i <= lLineEnd; ++i)
		{
			CString strCurLineText;
			m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
			CString strTemp = strCurLineText;
			if (strTemp.Trim().IsEmpty()) continue;
			int pos0 = m_EditorCtrl.GetLineStartPosition(i);
			int pos1 = AppUtils::FindFirstCharacterNotOf(strCurLineText, _T(" \t"));
			m_EditorCtrl.InsertText(strCommentSymbol, pos0 + pos1);
		}
	}
	m_EditorCtrl.EndUndoTransactions();
#endif

	if (m_EditorCtrl.IsReadOnlyEditor()) return FALSE;

	auto pLangDatabase = GetLanguageDatabase();
	if (!pLangDatabase) return FALSE;

	const TCHAR *commentStart;
	const TCHAR *commentEnd;
	CString symbolStart;
	CString symbolEnd;

	const TCHAR *commentLineSymbol;
	CString symbol;

	bool isSingleLineAdvancedMode = false;

	commentLineSymbol = pLangDatabase->GetLanguageCommentSymbol();
	commentStart = pLangDatabase->GetLanguageCommentStart();
	commentEnd = pLangDatabase->GetLanguageCommentEnd();

	if ((!commentLineSymbol) || (!commentLineSymbol[0]) || (commentLineSymbol == NULL))
	{
		if (!(!commentStart || !commentStart[0] || commentStart == NULL || !commentEnd || !commentEnd[0] || commentEnd == NULL))
		{
			if (blockCommentOperation == BLOCK_COMMENT_OPERATION::COMMENT_ACTION)
			{
				isSingleLineAdvancedMode = true;
			}
			else if (blockCommentOperation == BLOCK_COMMENT_OPERATION::UNCOMMENT_ACTION)
			{
				return UnComment(FALSE);
			}
			else if (blockCommentOperation == BLOCK_COMMENT_OPERATION::TOGGLE_ACTION)
			{
				isSingleLineAdvancedMode = true;
			}
			else
				return FALSE;
		}
		else
			return FALSE;
	}

#if 0
	auto pLangDatabase = GetLanguageDatabase();
	if (!pLangDatabase) return;
	CString strCommentBlockStart = pLangDatabase->GetLanguageCommentStart().Trim();
	CString strCommentBlockEnd = pLangDatabase->GetLanguageCommentEnd().Trim();
	if (strCommentBlockStart.IsEmpty() || strCommentBlockEnd.IsEmpty()) return;

	m_EditorCtrl.BeginUndoTransactions();

	CString strInput = m_EditorCtrl.GetSelectedText();
	if (strInput.IsEmpty())
	{
		int nCurrentLine = m_EditorCtrl.GetCurrentLine();
		m_EditorCtrl.GetTextFromLine(nCurrentLine, strInput);
		CString strTemp = strInput;
		if (strTemp.Trim().IsEmpty()) return;
		int pos0 = m_EditorCtrl.GetLineStartPosition(nCurrentLine - 1);
		int pos1 = AppUtils::FindFirstCharacterNotOf(strInput, _T(" \t"));
		int pos2 = m_EditorCtrl.GetLineEndPosition(nCurrentLine - 1);
		m_EditorCtrl.InsertText(strCommentBlockStart, pos0 + pos1);
		m_EditorCtrl.InsertText(strCommentBlockEnd, pos2 + 2);
	}
	else
	{
		int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
		int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
		m_EditorCtrl.InsertText(strCommentBlockStart, lStartPos);
		m_EditorCtrl.InsertText(strCommentBlockEnd, lEndPos + 2);
	}

	m_EditorCtrl.EndUndoTransactions();
#endif

	CString comment;
	unsigned int comment_length = 0;

	CString advCommentStart;
	CString advCommentEnd;
	unsigned int advCommentStart_length = 0;
	unsigned int advCommentEnd_length = 0;

	const TCHAR aSpace[]{ TEXT(" ") };

	if (!isSingleLineAdvancedMode)
	{
		comment = commentLineSymbol;
		comment += aSpace;
		comment_length = comment.GetLength();
	}
	else 
	{
		advCommentStart = commentStart;
		advCommentStart += aSpace;
		advCommentEnd = aSpace;
		advCommentEnd += commentEnd;

		advCommentStart_length = advCommentStart.GetLength();
		advCommentEnd_length = advCommentEnd.GetLength();
	}

	int selectionStart = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETSELECTIONSTART));
	int selectionEnd = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETSELECTIONEND));
	int caretPosition = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETCURRENTPOS));
	bool move_caret = caretPosition < selectionEnd;
	int selStartLine = static_cast<int>(m_EditorCtrl.DoCommand(SCI_LINEFROMPOSITION, selectionStart));
	int selEndLine = static_cast<int>(m_EditorCtrl.DoCommand(SCI_LINEFROMPOSITION, selectionEnd));
	int lines = selEndLine - selStartLine;
	if ((lines > 0) && (selectionEnd == static_cast<unsigned int>(m_EditorCtrl.DoCommand(SCI_POSITIONFROMLINE, selEndLine))))
		selEndLine--;
	int nUncomments = 0;
	const bool avoidIndent = false;
	const bool commentEmptyLines = false;

	m_EditorCtrl.BeginUndoTransactions();

	for (int i = selStartLine; i <= selEndLine; ++i)
	{
		int lineStart = static_cast<int>(m_EditorCtrl.DoCommand(SCI_POSITIONFROMLINE, i));
		int lineIndent = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETLINEINDENTPOSITION, i));
		int lineEnd = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETLINEENDPOSITION, i));

		if (lineIndent == lineEnd && !commentEmptyLines)
			continue;

		if (avoidIndent)
			lineIndent = lineStart;

		CString linebufStr;
		m_EditorCtrl.GetTextRange(linebufStr, lineIndent, lineEnd);

		if (blockCommentOperation != BLOCK_COMMENT_OPERATION::COMMENT_ACTION) 
		{
			if (!isSingleLineAdvancedMode)
			{
				if (wcsnicmp(linebufStr, comment, comment_length - 1) == 0)
				{
					int len = linebufStr[comment_length - 1] == aSpace[0] ? comment_length : comment_length - 1;

					m_EditorCtrl.DoCommand(SCI_SETSEL, lineIndent, lineIndent + len);
					m_EditorCtrl.ReplaceSelectionWithText(_T(""));

					if (i == selStartLine)
					{
						if (selectionStart > lineIndent + len)
							selectionStart -= len;
						else if (selectionStart > lineIndent)
							selectionStart = lineIndent;
					}
					if (i == selEndLine)
					{
						if (selectionEnd > lineIndent + len)
							selectionEnd -= len;
						else if (selectionEnd > lineIndent)
						{
							selectionEnd = lineIndent;
							if (lineIndent == lineStart && i != selStartLine)
								++selectionEnd;
						}
					}
					else 
						selectionEnd -= len;

					++nUncomments;
					continue;
				}
			}
			else 
			{
				if ((wcsnicmp(linebufStr, advCommentStart, advCommentStart_length - 1) == 0) &&
					(wcsnicmp(linebufStr.Mid(linebufStr.GetLength() - advCommentEnd_length + 1, advCommentEnd_length - 1), advCommentEnd.Mid(1, advCommentEnd_length - 1), advCommentEnd_length - 1) == 0))
				{
					int startLen = linebufStr[advCommentStart_length - 1] == aSpace[0] ? advCommentStart_length : advCommentStart_length - 1;
					int endLen = linebufStr[linebufStr.GetLength() - advCommentEnd_length] == aSpace[0] ? advCommentEnd_length : advCommentEnd_length - 1;

					m_EditorCtrl.DoCommand(SCI_SETSEL, lineIndent, lineIndent + startLen);
					m_EditorCtrl.ReplaceSelectionWithText(_T(""));
					m_EditorCtrl.DoCommand(SCI_SETSEL, lineEnd - startLen - endLen, lineEnd - startLen);
					m_EditorCtrl.ReplaceSelectionWithText(_T(""));

					if (i == selStartLine)
					{
						if (selectionStart > lineEnd - endLen)
							selectionStart = lineEnd - startLen - endLen;
						else if (selectionStart > lineIndent + startLen)
							selectionStart -= startLen;
						else if (selectionStart > lineIndent)
							selectionStart = lineIndent;
					}
					if (i == selEndLine)
					{
						if (selectionEnd > lineEnd)
							selectionEnd -= (startLen + endLen);
						else if (selectionEnd > lineEnd - endLen)
							selectionEnd = lineEnd - startLen - endLen;
						else if (selectionEnd > lineIndent + startLen)
							selectionEnd -= startLen;
						else if (selectionEnd > lineIndent)
						{
							selectionEnd = lineIndent;
							if (lineIndent == lineStart && i != selStartLine)
								++selectionEnd;
						}
					} 
					else 
						selectionEnd -= (startLen + endLen);

					++nUncomments;
					continue;
				}
			}
		}

		if (blockCommentOperation != BLOCK_COMMENT_OPERATION::UNCOMMENT_ACTION)
		{
			if (!isSingleLineAdvancedMode)
			{
				m_EditorCtrl.InsertText(comment, lineIndent);

				if (i == selStartLine)
				{
					if (selectionStart >= lineIndent)
						selectionStart += comment_length;
				}
				if (i == selEndLine)
				{
					if (selectionEnd >= lineIndent)
						selectionEnd += comment_length;
				}
				else
					selectionEnd += comment_length;
			}
			else
			{
				m_EditorCtrl.InsertText(advCommentStart, lineIndent);
				m_EditorCtrl.InsertText(advCommentEnd, lineEnd + advCommentStart_length);

				if (i == selStartLine)
				{
					if (selectionStart >= lineIndent)
						selectionStart += advCommentStart_length;
				}
				if (i == selEndLine)
				{
					if (selectionEnd > lineEnd)
						selectionEnd += (advCommentStart_length + advCommentEnd_length);
					else if (selectionEnd >= lineIndent)
						selectionEnd += advCommentStart_length;
				}
				else
					selectionEnd += (advCommentStart_length + advCommentEnd_length);
			}
		} 
	} 

	if (move_caret)
	{
		m_EditorCtrl.DoCommand(SCI_GOTOPOS, selectionEnd);
		m_EditorCtrl.DoCommand(SCI_SETCURRENTPOS, selectionStart);
	}
	else
	{
		m_EditorCtrl.DoCommand(SCI_SETSEL, selectionStart, selectionEnd);
	}
	m_EditorCtrl.EndUndoTransactions();

	if ((blockCommentOperation == BLOCK_COMMENT_OPERATION::UNCOMMENT_ACTION) && (nUncomments == 0))
	{
		return UnComment(FALSE);
	}
	return TRUE;
}

BOOL CEditorView::Comment()
{
#if 0
	auto pLangDatabase = GetLanguageDatabase();
	if (!pLangDatabase) return;
	CString strCommentSymbol = pLangDatabase->GetLanguageCommentSymbol().Trim();
	if (strCommentSymbol.IsEmpty()) return;

	m_EditorCtrl.BeginUndoTransactions();

	CString strInput = m_EditorCtrl.GetSelectedText();
	CString strInputNew;
	CStringArray arrLine;
	AppUtils::SplitCString(strInput, m_EditorCtrl.GetEOLCString(), arrLine);
	for (int i = 0; i < arrLine.GetSize(); ++i)
	{
		if (arrLine[i] == m_EditorCtrl.GetEOLCString()) continue;
		int pos = AppUtils::FindFirstCharacterNotOf(arrLine[i], _T(" \t,.;"));
		if (pos == -1) return;
		CString strCmp = arrLine[i].Mid(pos, 1);
		if (strCommentSymbol.GetLength() == 2)
		{
			strCmp = arrLine[i].Mid(pos, 2);
		}
		if (strCmp == strCommentSymbol)
		{
			CString str = arrLine[i].Mid(0, pos) + arrLine[i].Mid(pos + 1);
			if (strCommentSymbol.GetLength() == 2)
			{
				str = arrLine[i].Mid(0, pos) + arrLine[i].Mid(pos + 2);
			}
			strInputNew.Append(str);
			if (i != arrLine.GetSize() - 1)
			{
				strInputNew.Append(m_EditorCtrl.GetEOLCString());
			}
		}
		else
		{
			CString str = strCommentSymbol + arrLine[i];
			strInputNew.Append(str);
			if (i != arrLine.GetSize() - 1)
			{
				strInputNew.Append(m_EditorCtrl.GetEOLCString());
			}
		}
	}

	int lselected_startpos = (int)m_EditorCtrl.GetSelectionStartPosition();
	int lselected_endpos = (int)m_EditorCtrl.GetSelectionEndPosition();
	m_EditorCtrl.DoCommand(SCI_SETTARGETRANGE, lselected_startpos, lselected_endpos);

	char* bufUtf8 = NULL;
	CREATE_BUFFER_FROM_CSTRING(bufUtf8, strInputNew)
		m_EditorCtrl.DoCommand(SCI_REPLACETARGET, strInputNew.GetLength(), (LPARAM)bufUtf8);
	DELETE_POINTER_CPP_ARRAY(bufUtf8);
	m_EditorCtrl.DoCommand(SCI_SETSEL, lselected_startpos, lselected_startpos + strInputNew.GetLength());

	m_EditorCtrl.EndUndoTransactions();
#endif

	const TCHAR *commentStart;
	const TCHAR *commentEnd;
	CString symbolStart;
	CString symbolEnd;
	const TCHAR *commentLineSymbol;
	CString symbol;

	if (m_EditorCtrl.IsReadOnlyEditor()) return FALSE;

	auto pLangDatabase = GetLanguageDatabase();
	if (!pLangDatabase) return FALSE;

	commentLineSymbol = pLangDatabase->GetLanguageCommentSymbol();
	commentStart = pLangDatabase->GetLanguageCommentStart();
	commentEnd = pLangDatabase->GetLanguageCommentEnd();

	if ((!commentStart) || (!commentStart[0]) || (commentStart == NULL) || (!commentEnd) || (!commentEnd[0]) || (commentEnd == NULL))
	{
		if (!(!commentLineSymbol || !commentLineSymbol[0] || commentLineSymbol == NULL))
			return BlockComment(BLOCK_COMMENT_OPERATION::COMMENT_ACTION);
		else
			return FALSE;
	}

	CString start_comment(commentStart);
	CString end_comment(commentEnd);
	CString white_space(TEXT(" "));
	start_comment += white_space;
	white_space += end_comment;
	end_comment = white_space;
	int start_comment_length = start_comment.GetLength();
	int selectionStart = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETSELECTIONSTART));
	int selectionEnd = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETSELECTIONEND));
	int caretPosition = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETCURRENTPOS));

	bool move_caret = caretPosition < selectionEnd;

	if (selectionEnd - selectionStart <= 0)
	{
		int selLine = static_cast<int>(m_EditorCtrl.DoCommand(SCI_LINEFROMPOSITION, selectionStart));
		selectionStart = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETLINEINDENTPOSITION, selLine));
		selectionEnd = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETLINEENDPOSITION, selLine));
	}
	m_EditorCtrl.BeginUndoTransactions();
	m_EditorCtrl.InsertText(start_comment, selectionStart);
	selectionEnd += start_comment_length;
	selectionStart += start_comment_length;
	m_EditorCtrl.InsertText(end_comment, selectionEnd);
	if (move_caret)
	{
		m_EditorCtrl.DoCommand(SCI_GOTOPOS, selectionEnd);
		m_EditorCtrl.DoCommand(SCI_SETCURRENTPOS, selectionStart);
	}
	else
	{
		m_EditorCtrl.DoCommand(SCI_SETSEL, selectionStart, selectionEnd);
	}
	m_EditorCtrl.EndUndoTransactions();
	return TRUE;
}

BOOL CEditorView::UnComment(BOOL bBlockComment)
{
#if 0
	auto pLangDatabase = GetLanguageDatabase();
	if (!pLangDatabase) return;
	CString strCommentSymbol = pLangDatabase->GetLanguageCommentSymbol().Trim();
	if (strCommentSymbol.IsEmpty()) return;

	CString strInput = m_EditorCtrl.GetSelectedText();
	if (strInput.IsEmpty())
	{
		int nCurrentLine = m_EditorCtrl.GetCurrentLine();
		m_EditorCtrl.GetTextFromLine(nCurrentLine, strInput);

		CString strTemp = strInput;
		if (strTemp.Trim().Left(2) == pLangDatabase->GetLanguageCommentStart()
			&& strTemp.Trim().Right(2) == pLangDatabase->GetLanguageCommentEnd())
		{
			int pos = AppUtils::FindFirstCharacterNotOf(strInput, _T(" \t,."));
			if (pos == -1) return;
			strInput = strInput.Mid(0, pos) + strTemp.Mid(2, strTemp.GetLength() - 4);
		}
		else
		{
			if (strInput == m_EditorCtrl.GetEOLCString()) return;
			int pos = AppUtils::FindFirstCharacterNotOf(strInput, _T(" \t,."));
			if (pos == -1) return;
			CString strCmp = strInput.Mid(pos, 1);
			if (strCommentSymbol.GetLength() == 2)
			{
				strCmp = strInput.Mid(pos, 2);
			}
			if (strCmp == strCommentSymbol)
			{
				CString str = strInput.Mid(0, pos) + strInput.Mid(pos + 1);
				if (strCommentSymbol.GetLength() == 2)
				{
					str = strInput.Mid(0, pos) + strInput.Mid(pos + 2);
				}
				strInput = str;
			}
		}
		int lselected_startpos = (int)m_EditorCtrl.DoCommand(SCI_POSITIONFROMLINE, nCurrentLine - 1, 0);
		int lselected_endpos = (int)m_EditorCtrl.DoCommand(SCI_GETLINEENDPOSITION, nCurrentLine - 1, 0);
		m_EditorCtrl.DoCommand(SCI_SETTARGETRANGE, lselected_startpos, lselected_endpos);

		char* bufUtf8 = NULL;
		CREATE_BUFFER_FROM_CSTRING(bufUtf8, strInput)
			m_EditorCtrl.DoCommand(SCI_REPLACETARGET, strInput.GetLength(), (LPARAM)bufUtf8);
		DELETE_POINTER_CPP_ARRAY(bufUtf8);

		m_EditorCtrl.DoCommand(SCI_SETSEL, lselected_startpos, lselected_startpos + strInput.GetLength());
	}
	else
	{
		CString strInputNew;
		CString strTemp = strInput;
		if (strTemp.Trim().Left(2) == pLangDatabase->GetLanguageCommentStart()
			&& strTemp.Trim().Right(2) == pLangDatabase->GetLanguageCommentEnd())
		{
			int pos = AppUtils::FindFirstCharacterNotOf(strInput, _T(" \t,."));
			if (pos == -1)
			{
				return;
			}
			strInputNew = strInput.Mid(0, pos) + strTemp.Mid(2, strTemp.GetLength() - 4);
		}
		else
		{
			CStringArray arrLine;
			AppUtils::SplitCString(strInput, m_EditorCtrl.GetEOLCString(), arrLine);
			for (int i = 0; i < arrLine.GetSize(); ++i)
			{
				if (arrLine[i] == m_EditorCtrl.GetEOLCString() || arrLine[i].IsEmpty()) continue;
				int pos = AppUtils::FindFirstCharacterNotOf(arrLine[i], _T(" \t,."));
				if (pos == -1)
				{
					return;
				}
				CString strCmp = arrLine[i].Mid(pos, 1);
				if (strCommentSymbol.GetLength() == 2)
				{
					strCmp = arrLine[i].Mid(pos, 2);
				}
				if (strCmp == strCommentSymbol)
				{
					CString str = arrLine[i].Mid(0, pos) + arrLine[i].Mid(pos + 1);
					if (strCommentSymbol.GetLength() == 2)
					{
						str = arrLine[i].Mid(0, pos) + arrLine[i].Mid(pos + 2);
					}
					strInputNew.Append(str);
					if (i != arrLine.GetSize() - 1)
					{
						strInputNew.Append(m_EditorCtrl.GetEOLCString());
					}
				}
				else
				{
					CString str = +arrLine[i];
					strInputNew.Append(str);
					if (i != arrLine.GetSize() - 1)
					{
						strInputNew.Append(m_EditorCtrl.GetEOLCString());
					}
				}
			}
		}
		int lselected_startpos = (int)m_EditorCtrl.GetSelectionStartPosition();
		int lselected_endpos = (int)m_EditorCtrl.GetSelectionEndPosition();
		m_EditorCtrl.DoCommand(SCI_SETTARGETRANGE, lselected_startpos, lselected_endpos);

		char* bufUtf8 = NULL;
		CREATE_BUFFER_FROM_CSTRING(bufUtf8, strInputNew)
			m_EditorCtrl.DoCommand(SCI_REPLACETARGET, strInputNew.GetLength(), (LPARAM)bufUtf8);
		DELETE_POINTER_CPP_ARRAY(bufUtf8);
		m_EditorCtrl.DoCommand(SCI_SETSEL, lselected_startpos, lselected_startpos + strInputNew.GetLength());
	}
#endif
	const TCHAR *commentStart;
	const TCHAR *commentEnd;
	const TCHAR *commentLineSymbol;
	CString symbolStart;
	CString symbolEnd;
	CString symbol;
	BOOL retVal = FALSE;

	if (m_EditorCtrl.IsReadOnlyEditor()) return FALSE;

	auto pLangDatabase = GetLanguageDatabase();
	if (!pLangDatabase) return FALSE;

	commentLineSymbol = pLangDatabase->GetLanguageCommentSymbol();
	commentStart = pLangDatabase->GetLanguageCommentStart();
	commentEnd = pLangDatabase->GetLanguageCommentEnd();

	if ((!commentStart) || (!commentStart[0]) || (commentStart == NULL) || (!commentEnd) || (!commentEnd[0]) || (commentEnd == NULL))
	{
		if (!(!commentLineSymbol || !commentLineSymbol[0] || commentLineSymbol == NULL) && bBlockComment)
			return BlockComment(BLOCK_COMMENT_OPERATION::UNCOMMENT_ACTION);
		else
			return FALSE;
	}

	CString start_comment(commentStart);
	CString end_comment(commentEnd);
	CString white_space(TEXT(" "));
	unsigned int start_comment_length = start_comment.GetLength();
	unsigned int end_comment_length = end_comment.GetLength();

#if 0
	auto pLangDatabase = GetLanguageDatabase();
	if (!pLangDatabase) return;
	CString strCommentBlockStart = pLangDatabase->GetLanguageCommentStart().Trim();
	CString strCommentBlockEnd = pLangDatabase->GetLanguageCommentEnd().Trim();
	if (strCommentBlockStart.IsEmpty() || strCommentBlockEnd.IsEmpty()) return;

	m_EditorCtrl.BeginUndoTransactions();

	CString strInput = m_EditorCtrl.GetSelectedText();
	if (strInput.IsEmpty())
	{
		int nCurrentLine = m_EditorCtrl.GetCurrentLine();
		m_EditorCtrl.GetTextFromLine(nCurrentLine, strInput);
		CString strTemp = strInput;
		if (strTemp.Trim().IsEmpty()) return;
		int pos0 = m_EditorCtrl.GetLineStartPosition(nCurrentLine - 1);
		int pos1 = AppUtils::FindFirstCharacterNotOf(strInput, _T(" \t"));
		int pos2 = m_EditorCtrl.GetLineEndPosition(nCurrentLine - 1);
		m_EditorCtrl.InsertText(strCommentBlockStart, pos0 + pos1);
		m_EditorCtrl.InsertText(strCommentBlockEnd, pos2 + 2);
	}
	else
	{
		int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
		int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
		m_EditorCtrl.InsertText(strCommentBlockStart, lStartPos);
		m_EditorCtrl.InsertText(strCommentBlockEnd, lEndPos + 2);
	}

	m_EditorCtrl.EndUndoTransactions();
#endif
	do
	{
		int selectionStart = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETSELECTIONSTART));
		int selectionEnd = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETSELECTIONEND));
		int caretPosition = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETCURRENTPOS));
		int docLength = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETLENGTH));

		bool move_caret = caretPosition < selectionEnd;

		const int iSelStart = 0, iSelEnd = 1;
		const unsigned int N_CMNT = 2;
		int posStartCommentBefore[N_CMNT], posEndCommentBefore[N_CMNT], posStartCommentAfter[N_CMNT], posEndCommentAfter[N_CMNT];
		bool blnStartCommentBefore[N_CMNT], blnEndCommentBefore[N_CMNT], blnStartCommentAfter[N_CMNT], blnEndCommentAfter[N_CMNT];
		int posStartComment, posEndComment;
		int selectionStartMove, selectionEndMove;
		int flags;

		flags = SCFIND_WORDSTART;
		m_EditorCtrl.DoCommand(SCI_SETSEARCHFLAGS, flags);

		posStartCommentBefore[iSelStart] = m_EditorCtrl.SearchTextInRange(start_comment, selectionStart, 0);
		(posStartCommentBefore[iSelStart] == -1 ? blnStartCommentBefore[iSelStart] = false : blnStartCommentBefore[iSelStart] = true);
		posEndCommentBefore[iSelStart] = m_EditorCtrl.SearchTextInRange(end_comment, selectionStart, 0);
		(posEndCommentBefore[iSelStart] == -1 ? blnEndCommentBefore[iSelStart] = false : blnEndCommentBefore[iSelStart] = true);

		posStartCommentAfter[iSelStart] = m_EditorCtrl.SearchTextInRange(start_comment, selectionStart, docLength);
		(posStartCommentAfter[iSelStart] == -1 ? blnStartCommentAfter[iSelStart] = false : blnStartCommentAfter[iSelStart] = true);
		posEndCommentAfter[iSelStart] = m_EditorCtrl.SearchTextInRange(end_comment, selectionStart, docLength);
		(posEndCommentAfter[iSelStart] == -1 ? blnEndCommentAfter[iSelStart] = false : blnEndCommentAfter[iSelStart] = true);

		if ((blnStartCommentBefore[iSelStart] && blnEndCommentAfter[iSelStart])
			&& (!blnEndCommentBefore[iSelStart] || (posStartCommentBefore[iSelStart] >= posEndCommentBefore[iSelStart]))
			&& (!blnStartCommentAfter[iSelStart] || (posEndCommentAfter[iSelStart] <= posStartCommentAfter[iSelStart])))
		{
			posStartComment = posStartCommentBefore[iSelStart];
			posEndComment = posEndCommentAfter[iSelStart];
		}
		else
		{
			posStartCommentBefore[iSelEnd] = m_EditorCtrl.SearchTextInRange(start_comment, selectionEnd, 0);
			(posStartCommentBefore[iSelEnd] == -1 ? blnStartCommentBefore[iSelEnd] = false : blnStartCommentBefore[iSelEnd] = true);
			posEndCommentBefore[iSelEnd] = m_EditorCtrl.SearchTextInRange(end_comment, selectionEnd, 0);
			(posEndCommentBefore[iSelEnd] == -1 ? blnEndCommentBefore[iSelEnd] = false : blnEndCommentBefore[iSelEnd] = true);
			posStartCommentAfter[iSelEnd] = m_EditorCtrl.SearchTextInRange(start_comment, selectionEnd, docLength);
			(posStartCommentAfter[iSelEnd] == -1 ? blnStartCommentAfter[iSelEnd] = false : blnStartCommentAfter[iSelEnd] = true);
			posEndCommentAfter[iSelEnd] = m_EditorCtrl.SearchTextInRange(end_comment, selectionEnd, docLength);
			(posEndCommentAfter[iSelEnd] == -1 ? blnEndCommentAfter[iSelEnd] = false : blnEndCommentAfter[iSelEnd] = true);

			if ((blnStartCommentBefore[iSelEnd] && blnEndCommentAfter[iSelEnd])
				&& (!blnEndCommentBefore[iSelEnd] || (posStartCommentBefore[iSelEnd] >= posEndCommentBefore[iSelEnd]))
				&& (!blnStartCommentAfter[iSelEnd] || (posEndCommentAfter[iSelEnd] <= posStartCommentAfter[iSelEnd])))
			{
				posStartComment = posStartCommentBefore[iSelEnd];
				posEndComment = posEndCommentAfter[iSelEnd];
			}
			else if ((blnStartCommentAfter[iSelStart] && (posStartCommentAfter[iSelStart] < selectionEnd))
				&& (blnEndCommentBefore[iSelEnd] && (posEndCommentBefore[iSelEnd] >  selectionStart)))
			{
				posEndComment = posEndCommentAfter[iSelStart];
			}
			else
				return retVal;
		}

		retVal = TRUE;
		int startCommentLength = static_cast<int32_t>(start_comment_length);
		int endCommentLength = static_cast<int32_t>(end_comment_length);

		CString charbuf;
		m_EditorCtrl.GetTextRange(charbuf, posEndComment - 1, posEndComment);

		if (wcsnicmp(charbuf, white_space, white_space.GetLength()) == 0)
		{
			endCommentLength += 1;
			posEndComment -= 1;
		}

		m_EditorCtrl.BeginUndoTransactions();
		m_EditorCtrl.DoCommand(SCI_SETSEL, posEndComment, posEndComment + endCommentLength);
		m_EditorCtrl.DoCommand(SCI_REPLACESEL, 0, reinterpret_cast<LPARAM>(""));

		m_EditorCtrl.GetTextRange(charbuf, posStartComment + startCommentLength, posStartComment + startCommentLength + 1);
		if (wcsnicmp(charbuf, white_space, white_space.GetLength()) == 0)
			startCommentLength += 1;

		m_EditorCtrl.DoCommand(SCI_SETSEL, posStartComment, posStartComment + startCommentLength);
		m_EditorCtrl.DoCommand(SCI_REPLACESEL, 0, reinterpret_cast<LPARAM>(""));
		m_EditorCtrl.EndUndoTransactions();

		if (selectionStart > posStartComment)
		{
			if (selectionStart >= posStartComment + startCommentLength)
				selectionStartMove = -static_cast<int>(startCommentLength);
			else
				selectionStartMove = -static_cast<int>(selectionStart - posStartComment);
		}
		else
			selectionStartMove = 0;

		if (selectionEnd >= posEndComment + endCommentLength)
			selectionEndMove = -static_cast<int>(startCommentLength + endCommentLength);
		else if (selectionEnd <= posEndComment)
			selectionEndMove = -static_cast<int>(startCommentLength);
		else
			selectionEndMove = -static_cast<int>(startCommentLength + (selectionEnd - posEndComment));

		if (move_caret)
		{
			m_EditorCtrl.DoCommand(SCI_GOTOPOS, selectionEnd + selectionEndMove);
			m_EditorCtrl.DoCommand(SCI_SETCURRENTPOS, selectionStart + selectionStartMove);
		}
		else
		{
			m_EditorCtrl.DoCommand(SCI_SETSEL, selectionStart + selectionStartMove, selectionEnd + selectionEndMove);
		}
	} while (1); 
}

BOOL CEditorView::CanResetHightlight()
{
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (pFrame)
	{
		CString strSearchWhat = pFrame->GetQuickSearchWhat();
		if (strSearchWhat.IsEmpty()) return TRUE;
		unsigned int uiSearchOption = pFrame->GetQuickSearchOption();
		m_EditorCtrl.DoCommand(SCI_SETSEARCHFLAGS, uiSearchOption);
		int targetMatched = m_EditorCtrl.SearchTextInEditor(strSearchWhat);
		if (targetMatched == -1)
		{
			return TRUE;
		}
		else
		{
			RenderIndicatorWordsAndCount(strSearchWhat, uiSearchOption);
			return FALSE;
		}
	}
	return FALSE;
}

void CEditorView::DoFileSaveAs()
{
	CEditorDoc *pDoc = GetEditorDocument();
	ASSERT(pDoc);
	if (!pDoc) return;
	pDoc->OnFileSaveAs();
}

void CEditorView::UpdateFileLastWriteTime(const CString& strFilePath)
{
	if (strFilePath.IsEmpty() || !PathFileExists(strFilePath)) return;
	FILETIME timeStamp = {};
	WIN32_FILE_ATTRIBUTE_DATA attributes;
	if (GetFileAttributesEx(strFilePath, GetFileExInfoStandard, &attributes) != 0)
	{
		timeStamp = attributes.ftLastWriteTime;
	}
	if (CompareFileTime(&m_FileSystemTime, &timeStamp) != 0)
	{
		m_FileSystemTime = timeStamp;
	}
}

int CEditorView::WatchFileSystemState()
{
	m_bIsWatchFileProcessing = TRUE;
	int nFileState = 0;

	CEditorDoc *pDoc = GetEditorDocument();
	ASSERT(pDoc);
	if (!pDoc)
	{
		m_bIsWatchFileProcessing = FALSE;
		return nFileState | FILE_SYSTEM_STATE::FILE_UNCHANGED;
	}

	WIN32_FILE_ATTRIBUTE_DATA attributes;
	CString strFile = pDoc->GetPathName();
	if (strFile.IsEmpty() || (pDoc->IsPreviewMode() && PathFileExists(strFile)))
	{
		m_bIsWatchFileProcessing = FALSE;
		return nFileState | FILE_SYSTEM_STATE::FILE_UNCHANGED;
	}

	if (!PathFileExists(strFile))
	{
		nFileState |= FILE_SYSTEM_STATE::FILE_DELETED;
	}
	else if (GetFileAttributesEx(strFile, GetFileExInfoStandard, &attributes) != 0)
	{
		BOOL bReadOnly = attributes.dwFileAttributes & FILE_ATTRIBUTE_READONLY;

		if (bReadOnly != m_bDocumentReadOnly)
		{
			m_bDocumentReadOnly = bReadOnly;
			nFileState |= FILE_SYSTEM_STATE::FILE_CHANGED_READONLY;
		}

		if (CompareFileTime(&m_FileSystemTime, &attributes.ftLastWriteTime) != 0)
		{
			m_FileSystemTime = attributes.ftLastWriteTime;
			nFileState |= FILE_SYSTEM_STATE::FILE_CONTENT_MODIFIED;
		}
	}

	if (nFileState != 0) // reload file...
	{
		if (nFileState & FILE_SYSTEM_STATE::FILE_DELETED)
		{
			CString strMsg;
			strMsg.Format(_T(R"([System Warning] %s has been deleted from file system, do you want keep it on VinaText?)"), strFile);
			if (IDYES == AfxMessageBox(strMsg, MB_YESNO | MB_ICONWARNING))
			{
				pDoc->OnSaveDocument(strFile);
			}
			else 
			{
				AppUtils::CloseDeletedDocument(this, strFile);
				return nFileState;
			}
		}
		else
		{
			if (nFileState & FILE_SYSTEM_STATE::FILE_CHANGED_READONLY)
			{
				if (!m_EditorCtrl.IsReadOnlyEditor() && m_bDocumentReadOnly)
				{
					OnDocumentSetReadOnly();
					CString strCurrentTime = OSUtils::DateToCStringABDHMSY(OSUtils::GetCurrentTimeEx());
					if (AppSettingMgr.m_bDisplayMessageBoxForFileChange)
					{
						AfxMessageBox(_T("[System Warning] At ") + strCurrentTime + _T(", ") + strFile + _T(" has changed to read only file!"));
					}
					else
					{
						LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [System Warning] At ") + strCurrentTime + _T(", ") + strFile + _T(" has changed to read only file..."), BasicColors::orange);
					}
				}
				else
				{
					OnDocumentSetReadOnly();
					CString strCurrentTime = OSUtils::DateToCStringABDHMSY(OSUtils::GetCurrentTimeEx());
					if (AppSettingMgr.m_bDisplayMessageBoxForFileChange)
					{
						AfxMessageBox(_T("[System Warning] At ") + strCurrentTime + _T(", ") + strFile + _T(" has removed read only attribute!"));
					}
					else
					{
						LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [System Warning] At ") + strCurrentTime + _T(", ") + strFile + _T(" has removed read only attribute..."), BasicColors::orange);
					}
				}
			}
			if (nFileState & FILE_SYSTEM_STATE::FILE_CONTENT_MODIFIED)
			{
				BACKUP_VISIBLE_EDITOR_STATE
				if (m_EditorCtrl.LoadFile(strFile, m_encodingUser))
				{
					m_EditorCtrl.InitilizeSetting(pDoc->GetDocLanguageDatabase());
					m_EditorCtrl.ResetUndoSavePoint();
					m_EditorCtrl.ResetMapUndoRedoSelection();

					UpdateFileLastWriteTime(strFile);
					CString strCurrentTime = OSUtils::DateToCStringABDHMSY(OSUtils::GetCurrentTimeEx());
					if (AppSettingMgr.m_bDisplayMessageBoxForFileChange)
					{
						AfxMessageBox(_T("[System Warning] At ") + strCurrentTime + _T(", ") + strFile + _T(" has been modified by other process, file content updated!"));
					}
					else
					{
						LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [System Warning] At ") + strCurrentTime + _T(", ") + strFile + _T(" has been modified by other process, file content updated..."), BasicColors::orange);
					}
					AppUtils::UpdateModifiedDocumentTitle(m_pDocument, FALSE);
				}
				RESTORE_VISIBLE_EDITOR_STATE
			}
		}
	}
	m_bIsWatchFileProcessing = FALSE;
	return nFileState;
}

void CEditorView::ToggleAddBreakPoint()
{
	if (!m_EditorCtrl.IsLineHasBreakPoint(m_EditorCtrl.GetCurrentLine()))
	{
		OnOptionsAddBreakPoint();
	}
	else
	{
		OnOptionsDeleteBreakPoint();
	}
}

void CEditorView::ToggleAddBookmark()
{
	if (!m_EditorCtrl.IsLineHasBookMark(m_EditorCtrl.GetCurrentLine()))
	{
		OnOptionsAddBookmark();
	}
	else
	{
		OnOptionsDeleteBookmark();
	}
}

BOOL CEditorView::IsCommentLineCode(const CString & strLine)
{
	auto pLangDatabase = GetLanguageDatabase();
	if (pLangDatabase)
	{
		CString strTemp = strLine;
		strTemp.Trim();
		if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON
			|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_ASSEMBLY)
		{
			strTemp = strTemp.Mid(0, 1);
		}
		else
		{
			strTemp = strTemp.Mid(0, 2);
		}
		if (strTemp == pLangDatabase->GetLanguageCommentSymbol()
			|| strTemp == pLangDatabase->GetLanguageCommentEnd()
			|| strTemp == pLangDatabase->GetLanguageCommentStart())
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CEditorView::OnOptionsEditCopy()
{
	AppSettingMgr.m_MultipleClipboardBuffer.clear();
	int nSels = m_EditorCtrl.GetSelectionNumber();
	if (nSels > 1)
	{
		AppSettingMgr.m_MultipleClipboardBuffer.reserve(nSels);
		for (int i = 0; i < nSels; ++i)
		{
			CString strSelectedTextI = m_EditorCtrl.GetSelectedTextAtSelection(i);
			if (!strSelectedTextI.IsEmpty())
			{
				AppSettingMgr.m_MultipleClipboardBuffer.push_back(strSelectedTextI);
			}
		}
		CString strClipBoardNewText;
		for (int i = 0; i < AppSettingMgr.m_MultipleClipboardBuffer.size(); ++i)
		{
			if (i != AppSettingMgr.m_MultipleClipboardBuffer.size() - 1)
			{
				strClipBoardNewText += AppSettingMgr.m_MultipleClipboardBuffer[i] + m_EditorCtrl.GetEOLCString();
			}
			else
			{
				strClipBoardNewText += AppSettingMgr.m_MultipleClipboardBuffer[i];
			}
		}
		PushTextToClipBoard(strClipBoardNewText);
	}
	else
	{
		if (m_EditorCtrl.GetSelectedText().IsEmpty())
		{
			m_EditorCtrl.CopyLine();
		}
		else
		{
			m_EditorCtrl.Copy();
		}
	}
}

void CEditorView::OnOptionsEditCopyWithQuote()
{
	AppSettingMgr.m_MultipleClipboardBuffer.clear();
	int nSels = m_EditorCtrl.GetSelectionNumber();
	if (nSels > 1)
	{
		AppSettingMgr.m_MultipleClipboardBuffer.reserve(nSels);
		for (int i = 0; i < nSels; ++i)
		{
			CString strSelectedTextI = m_EditorCtrl.GetSelectedTextAtSelection(i);
			if (!strSelectedTextI.IsEmpty())
			{
				AppSettingMgr.m_MultipleClipboardBuffer.push_back(strSelectedTextI);
			}
		}
		CString strClipBoardNewText;
		for (int i = 0; i < AppSettingMgr.m_MultipleClipboardBuffer.size(); ++i)
		{
			if (i != AppSettingMgr.m_MultipleClipboardBuffer.size() - 1)
			{
				strClipBoardNewText += _T("\"") + AppSettingMgr.m_MultipleClipboardBuffer[i] + _T("\"") + m_EditorCtrl.GetEOLCString();
			}
			else
			{
				strClipBoardNewText += _T("\"") + AppSettingMgr.m_MultipleClipboardBuffer[i] + _T("\"");
			}
		}
		PushTextToClipBoard(strClipBoardNewText);
	}
	else
	{
		CString strSelectedText = m_EditorCtrl.GetSelectedText();
		if (strSelectedText.IsEmpty())
		{
			m_EditorCtrl.GetTextFromLine(m_EditorCtrl.GetCurrentLine(), strSelectedText);
			CString strSelectedTextQuote = _T("\"") + strSelectedText + _T("\"");
			PushTextToClipBoard(strSelectedTextQuote);
		}
		else
		{
			CString strSelectedTextQuote = _T("\"") + strSelectedText + _T("\"");
			PushTextToClipBoard(strSelectedTextQuote);
		}
	}
}

void CEditorView::OnOptionsEditVisibleCopy()
{
	int nFirstVisualLine = m_EditorCtrl.GetFirstVisibleLine();
	int nbLineOnScreen = static_cast<int>(m_EditorCtrl.DoCommand(SCI_LINESONSCREEN));
	int nbLines = min(nbLineOnScreen, 400);
	int nEndLineOnScreen = nFirstVisualLine + nbLines;
	int nFirstVisualPos = m_EditorCtrl.GetLineStartPosition(nFirstVisualLine);
	int nEndPosOnScreen = m_EditorCtrl.GetLineEndPosition(nEndLineOnScreen);
	m_EditorCtrl.SetSelectionRange(nFirstVisualPos, nEndPosOnScreen);
	m_EditorCtrl.Copy();
}

void CEditorView::OnOptionsEditShowCopyHistory()
{
	// Create a generic keyboard event structure
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press the "Window" key
	ip.ki.wVk = VK_LWIN;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Press the "V" key
	ip.ki.wVk = 'V';
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "V" key
	ip.ki.wVk = 'V';
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "Window" key
	ip.ki.wVk = VK_LWIN;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	m_EditorCtrl.SetFocus();
}

void CEditorView::OnEmptyClipboard()
{
	if (OpenClipboard())
	{
		EmptyClipboard();
		CloseClipboard();
		AfxMessageBox(_T("The clipboard data has been cleared!"), MB_ICONINFORMATION);
	}
}

void CEditorView::OnOptionsEditCut()
{
	AppSettingMgr.m_MultipleClipboardBuffer.clear();
	if (!m_EditorCtrl.IsReadOnlyEditor())
	{
		int nSels = m_EditorCtrl.GetSelectionNumber();
		if (nSels > 1)
		{
			// get selection buffers
			AppSettingMgr.m_MultipleClipboardBuffer.reserve(nSels);
			for (int i = 0; i < nSels; ++i)
			{
				CString strSelectedTextI = m_EditorCtrl.GetSelectedTextAtSelection(i);
				if (!strSelectedTextI.IsEmpty())
				{
					AppSettingMgr.m_MultipleClipboardBuffer.push_back(strSelectedTextI);
				}
			}
			CString strClipBoardNewText;
			for (int i = 0; i < AppSettingMgr.m_MultipleClipboardBuffer.size(); ++i)
			{
				if (i != AppSettingMgr.m_MultipleClipboardBuffer.size() - 1)
				{
					strClipBoardNewText += AppSettingMgr.m_MultipleClipboardBuffer[i] + m_EditorCtrl.GetEOLCString();
				}
				else
				{
					strClipBoardNewText += AppSettingMgr.m_MultipleClipboardBuffer[i];
				}
			}
			PushTextToClipBoard(strClipBoardNewText);

			// remove selection buffers
			m_EditorCtrl.BeginUndoTransactions();
			for (int i = nSels - 1; i >= 0; --i)
			{
				// remove selection buffers
				m_EditorCtrl.ReplaceSelectionNWithText(_T(""), i);
			}
			m_EditorCtrl.EndUndoTransactions();
		}
		else
		{
			CString strSelectedText = m_EditorCtrl.GetSelectedText();
			if (strSelectedText.IsEmpty())
			{
				m_EditorCtrl.CutLine();
			}
			else
			{
				m_EditorCtrl.Cut();
			}
		}
	}
}

void CEditorView::OnUpdateOptionsEditCut(CCmdUI * pCmdUI)
{
	CEditorDoc *pDoc = GetEditorDocument();
	ASSERT(pDoc);
	if (!pDoc) return;
	if (m_EditorCtrl.IsReadOnlyEditor())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CEditorView::OnOptionsEditPaste()
{
	if (m_EditorCtrl.CanPaste())
	{
		if (AppSettingMgr.m_MultipleClipboardBuffer.empty())
		{
			m_EditorCtrl.Paste();
		}
		else
		{
			int nSels = m_EditorCtrl.GetSelectionNumber();
			if (nSels > 1)
			{
				m_EditorCtrl.BeginUndoTransactions();
				std::vector<int> beforePasteCarets, afterPasteCarets;
				beforePasteCarets.reserve(nSels); afterPasteCarets.reserve(nSels);
				for (int i = 0; i < nSels; ++i)
				{
					beforePasteCarets.push_back(m_EditorCtrl.GetSelectionNumberCaret(i));
				}
				std::sort(beforePasteCarets.begin(), beforePasteCarets.end());
				for (int i = 0; i < beforePasteCarets.size(); ++i)
				{
					if (i == 0)
					{
						m_EditorCtrl.InsertTextAtSelectionNumber(AppSettingMgr.m_MultipleClipboardBuffer[i], beforePasteCarets[i]);
						afterPasteCarets.push_back(beforePasteCarets[i] + AppSettingMgr.m_MultipleClipboardBuffer[i].GetLength());
					}
					else
					{
						int caretPos = beforePasteCarets[i];
						for (int j = 0; j < i; ++j)
						{
							caretPos += AppSettingMgr.m_MultipleClipboardBuffer[j].GetLength();
						}
						m_EditorCtrl.InsertTextAtSelectionNumber(AppSettingMgr.m_MultipleClipboardBuffer[i], caretPos);
						afterPasteCarets.push_back(caretPos + AppSettingMgr.m_MultipleClipboardBuffer[i].GetLength());
					}
				}
				for (int i = 0; i < afterPasteCarets.size(); ++i)
				{
					m_EditorCtrl.DoCommand(SCI_ADDSELECTION, afterPasteCarets[i], afterPasteCarets[i]);
				}
				m_EditorCtrl.DoCommand(SCI_DROPSELECTIONN, 0, 0);
				m_EditorCtrl.EndUndoTransactions();
			}
			else
			{
				m_EditorCtrl.Paste();
			}
		}
	}
}

void CEditorView::OnUpdateOptionsEditPaste(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(m_EditorCtrl.CanPaste());
}

void CEditorView::OnOptionsEditPasteHTML()
{
	UINT cfid = RegisterClipboardFormat(TEXT("HTML Format"));

	if (!IsClipboardFormatAvailable(cfid))
		return;

	CString strClipBoardText = GetClipboardAsFormatID(cfid);
	if (!strClipBoardText.IsEmpty() && m_EditorCtrl.CanPaste())
	{
		m_EditorCtrl.ReplaceSelectionWithText(strClipBoardText);
	}
}

void CEditorView::OnUpdateOptionsEditPasteHTML(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(m_EditorCtrl.CanPaste());
}

void CEditorView::OnOptionsEditPasteRFT()
{
	UINT cfid = RegisterClipboardFormat(TEXT("Rich Text Format"));

	if (!IsClipboardFormatAvailable(cfid))
		return;

	CString strClipBoardText = GetClipboardAsFormatID(cfid);
	if (!strClipBoardText.IsEmpty() && m_EditorCtrl.CanPaste())
	{
		m_EditorCtrl.ReplaceSelectionWithText(strClipBoardText);
	}
}

void CEditorView::OnUpdateOptionsEditPasteRFT(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(m_EditorCtrl.CanPaste());
}

CString CEditorView::GetClipboardPlainText()
{
	if (!OpenClipboard())
		return CString();

#ifdef UNICODE
	HANDLE hglb = ::GetClipboardData(CF_UNICODETEXT);
#else
	HANDLE hglb = ::GetClipboardData(CF_TEXT);
#endif
	if (hglb == NULL)
	{
		CloseClipboard();
		return CString();
	}
	CString strClipBoardText = reinterpret_cast<LPTSTR>(::GlobalLock(hglb));
	if (!strClipBoardText.IsEmpty())
	{
		::GlobalUnlock(hglb);
	}
	CloseClipboard();
	return strClipBoardText;
}

CString CEditorView::GetClipboardAsFormatID(UINT idFormatID)
{
	if (!OpenClipboard())
		return CString();

	HANDLE hglb = ::GetClipboardData(idFormatID);

	if (hglb == NULL)
	{
		CloseClipboard();
		return CString();
	}

	auto strClipBoardText = reinterpret_cast<LPSTR>(::GlobalLock(hglb));
	CString str(strClipBoardText);
	if (!str.IsEmpty())
	{
		::GlobalUnlock(hglb);
	}
	CloseClipboard();
	return str;
}

void CEditorView::OnPasteWithDoubleQuote()
{
	CString strClipBoardText = GetClipboardPlainText();
	if (m_EditorCtrl.CanPaste() && !strClipBoardText.IsEmpty())
	{
		PushTextToClipBoard(_T("\"") + strClipBoardText + _T("\""));
		m_EditorCtrl.Paste();
		PushTextToClipBoard(strClipBoardText);
	}
}

void CEditorView::OnUpdateOptionsPasteWithDoubleQuote(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(m_EditorCtrl.CanPaste());
}

void CEditorView::OnPasteAtBeginAllFile()
{
	VERIFY_SYNC_ACTION_VIEW
	auto fSycnAction = [](CEditorDoc* pDoc) -> void {
		if (pDoc) {
			auto pView = pDoc->GetEditorView();
			if (pView) 
			{
				auto pEditor = pView->GetEditorCtrl();
				pEditor->GotoPosition(0);
				pEditor->DoCommand(SCI_PASTE);
			}
		}
	};
	AppUtils::SyncActionAllEditorDocuments(fSycnAction, GetEditorDocument());
}

void CEditorView::OnPasteAtEndAllFile()
{
	VERIFY_SYNC_ACTION_VIEW
	auto fSycnAction = [](CEditorDoc* pDoc) -> void {
		if (pDoc) {
			auto pView = pDoc->GetEditorView();
			if (pView)
			{
				auto pEditor = pView->GetEditorCtrl();
				pEditor->GotoPosition(pEditor->GetTextLength());
				pEditor->DoCommand(SCI_PASTE);
			}
		}
	};
	AppUtils::SyncActionAllEditorDocuments(fSycnAction, GetEditorDocument());
}

void CEditorView::OnPasteWithForwardSlash()
{
	CString strClipBoardText = GetClipboardPlainText();
	if (m_EditorCtrl.CanPaste() && !strClipBoardText.IsEmpty())
	{
		CString strClipBoardNewText = strClipBoardText;
		strClipBoardNewText.Replace(_T("\\"), _T("/"));
		PushTextToClipBoard(strClipBoardNewText);
		m_EditorCtrl.Paste();
		PushTextToClipBoard(strClipBoardText);
	}
}

void CEditorView::OnUpdateOptionsPasteWithForwardSlash(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(m_EditorCtrl.CanPaste());
}

void CEditorView::OnOptionsEditSelectionToDoubleQuote()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stScript;
	m_EditorCtrl.GetText(stScript);
	if (!stScript.IsEmpty())
	{
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		if (stSelectedScript.IsEmpty())
		{
			m_EditorCtrl.SetTextToEditor(_T("\"") + stScript + _T("\""));
		}
		else
		{
			stSelectedScript = _T("\"") + stSelectedScript + _T("\"");
			m_EditorCtrl.ReplaceSelectionWithText(stSelectedScript);
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsEditSelectionToNextParagraph()
{
	m_EditorCtrl.DoCommand(SCI_PARADOWNEXTEND);
}

void CEditorView::OnOptionsEditSelectionToPrevParagraph()
{
	m_EditorCtrl.DoCommand(SCI_PARAUPEXTEND);
}

void CEditorView::OnOptionsEditGotoNextParagraph()
{
	m_EditorCtrl.DoCommand(SCI_PARADOWN);
}

void CEditorView::OnOptionsEditGotoPrevParagraph()
{
	m_EditorCtrl.DoCommand(SCI_PARAUP);
}

void CEditorView::OnOptionsEditUndo()
{
	if (m_EditorCtrl.IsAllowUndo())
	{
		m_EditorCtrl.Undo();
	}
	if (!m_EditorCtrl.IsAllowUndo() && !m_pDocument->IsModified())
	{
		AppUtils::UpdateModifiedDocumentTitle(m_pDocument, FALSE);
	}
}

void CEditorView::OnUpdateOptionsEditUndo(CCmdUI * pCmdUI)
{
	BOOL bIsAllowUndo = m_EditorCtrl.IsAllowUndo();
	pCmdUI->Enable(bIsAllowUndo);
	if (!bIsAllowUndo && !m_pDocument->IsModified())
	{
		AppUtils::UpdateModifiedDocumentTitle(m_pDocument, FALSE);
	}
}

void CEditorView::OnOptionsEditUndoAll()
{
	if (m_EditorCtrl.GetSelectionNumber() == SINGLE_SELECTION)
	{
		int nActionCount = 0;
		while (m_EditorCtrl.IsAllowUndo())
		{
			nActionCount++;
			OnOptionsEditUndo();
		}
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> Undo all %d actions..."), nActionCount);
	}
}

void CEditorView::OnUpdateOptionsEditUndoAll(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(m_EditorCtrl.IsAllowUndo() && m_EditorCtrl.GetSelectionNumber() == SINGLE_SELECTION);
}

void CEditorView::OnOptionsEditRedoAll()
{
	if (m_EditorCtrl.GetSelectionNumber() == SINGLE_SELECTION)
	{
		int nActionCount = 0;
		while (m_EditorCtrl.IsAllowRedo())
		{
			nActionCount++;
			OnOptionsEditRedo();
		}
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> Redo all %d actions..."), nActionCount);
	}
}

void CEditorView::OnUpdateOptionsEditRedoAll(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(m_EditorCtrl.IsAllowRedo() && m_EditorCtrl.GetSelectionNumber() == SINGLE_SELECTION);
}

void CEditorView::OnOptionsEditUndoAllFile()
{
	auto fSycnAction = [](CEditorDoc* pDoc) -> void {
		if (pDoc) {
			auto pView = pDoc->GetEditorView();
			if (pView)
			{
				auto pEditor = pView->GetEditorCtrl();
				if (pEditor->IsAllowUndo())
				{
					pEditor->Undo();
				}
				if (!pEditor->IsAllowUndo() && !pDoc->IsModified())
				{
					AppUtils::UpdateModifiedDocumentTitle(pDoc, FALSE);
				}			
			}
		}
	};
	AppUtils::SyncActionAllEditorDocuments(fSycnAction);
}

void CEditorView::OnUpdateOptionsEditUndoAllFile(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(m_EditorCtrl.IsAllowUndo());
}

void CEditorView::OnOptionsEditRedoAllFile()
{
	auto fSycnAction = [](CEditorDoc* pDoc) -> void {
		if (pDoc) {
			auto pView = pDoc->GetEditorView();
			if (pView)
			{
				auto pEditor = pView->GetEditorCtrl();
				if (pEditor->IsAllowRedo())
				{
					pEditor->Redo();
				}
			}
		}
	};
	AppUtils::SyncActionAllEditorDocuments(fSycnAction);
}

void CEditorView::OnUpdateOptionsEditRedoAllFile(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(m_EditorCtrl.IsAllowRedo());
}

void CEditorView::OnUpdateOptionsEOLInfo(CCmdUI* pCmdUI)
{
	pCmdUI->SetText(m_EditorCtrl.GetEOLName());
	pCmdUI->Enable(TRUE);
}

void CEditorView::OnUpdateOptionsCaretInfo(CCmdUI * pCmdUI)
{
	CString strInfo;
	int lLine = m_EditorCtrl.GetCurrentLine();
	int lColumn = m_EditorCtrl.GetCurrentColumn();
	int lPos = m_EditorCtrl.GetCurrentPosition();
	int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
	int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
	int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
	int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
	if (m_EditorCtrl.IsSelectionEmpty())
	{
		strInfo.Format(IDS_INDICATOR_CARET_INFO_CURRENT, lLine, lColumn, lPos);
	}
	else
	{
		strInfo.Format(IDS_INDICATOR_CARET_INFO_SELECTED, lLineEnd - lLineStart + 1,  lEndPos - lStartPos);
	}
	pCmdUI->SetText(strInfo);
	pCmdUI->Enable(TRUE);
}

void CEditorView::OnUpdateOptionsLength(CCmdUI * pCmdUI)
{
	CString strLine;
	strLine.Format(IDS_LENGTH_INDICATOR, m_nIndicatorCount);
	pCmdUI->SetText(strLine);
	pCmdUI->Enable(TRUE);
}

void CEditorView::OnUpdateOptionsSelections(CCmdUI * pCmdUI)
{
	CString strLine;
	strLine.Format(IDS_SELECTIONS_INDICATOR, m_EditorCtrl.GetSelectionNumber());
	pCmdUI->SetText(strLine);
	pCmdUI->Enable(TRUE);
}

void CEditorView::OnUpdateOptionsFileType(CCmdUI * pCmdUI)
{
	CString strLine = DetectCurrentDocLanguage();
	strLine.Format(IDS_CURRENT_LANGUAGE_INDICATOR, strLine);
	pCmdUI->SetText(strLine);
	pCmdUI->Enable(TRUE);
}

void CEditorView::OnUpdateOptionsEncoding(CCmdUI * pCmdUI)
{
	//Code page can be set to 65001 (UTF-8), 932 (Japanese Shift-JIS), 936 (Simplified Chinese GBK),
	//949 (Korean Unified Hangul Code), 950 (Traditional Chinese Big5), or 1361 (Korean Johab).
	CString strLine;
	CString strCodePageName = m_EditorCtrl.GetEncodingName();
	if (!PathFileExists(m_pDocument->GetPathName()))
	{
		strCodePageName = _T("UTF-8");
	}
	else if (strCodePageName.IsEmpty())
	{
		strCodePageName = _T("Undefined");
	}
	strLine.Format(IDS_ENCODING_INDICATOR, strCodePageName);
	pCmdUI->SetText(strLine);
	pCmdUI->Enable(TRUE);
}

void CEditorView::OnOptionsEditRedo()
{
	if (m_EditorCtrl.IsAllowRedo())
	{
		m_EditorCtrl.Redo();
	}
}

void CEditorView::OnUpdateOptionsEditRedo(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(m_EditorCtrl.IsAllowRedo());
}

void CEditorView::OnOptionsEditSelectAll()
{
	m_EditorCtrl.SelectAll();
}

void CEditorView::OnOptionsEditSelectAllOccurrences()
{
	SelectAllOccurrences(m_EditorCtrl.GetSelectedText());
}

void CEditorView::OnOptionsEditSelectAllOccurrencesNotMCMW()
{
	SelectAllOccurrences(m_EditorCtrl.GetSelectedText(), SCFIND_NONE);
}

void CEditorView::OnOptionsViewLinenumbers()
{
	m_EditorCtrl.SetDisplayLinenumbers(!m_EditorCtrl.GetDisplayLinenumbers());
}

void CEditorView::UpdateDockPaneBreakpoint(int nLineNumber, BOOL bDeleteFromList, const CString& strPathName, const CString& strProcessName)
{
	// update dock pane
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;

	CString strTextLine;
	m_EditorCtrl.GetTextFromLine(nLineNumber, strTextLine);

	BREAKPOINT_LINE_DATA data;
	data._bDeleteFromList = bDeleteFromList;
	data._nLineNumber = nLineNumber;
	data._strLine = strTextLine;
	data._strTargetFile = strPathName;
	data._strProcessName = strProcessName;
	data._strTargetLanguage = m_strCurrentDocLanguageName;
	pFrame->AddBreakpointLineDataToPane(data);
}

void CEditorView::UpdateDockPaneBookmark(int nLineNumber, BOOL bDeleteFromList, const CString& strPathName)
{
	// update dock pane
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;

	CString strTextLine;
	m_EditorCtrl.GetTextFromLine(nLineNumber, strTextLine);

	BOOKMARK_LINE_DATA data;
	data._bDeleteFromList = bDeleteFromList;
	data._nLineNumber = nLineNumber;
	data._strLine = strTextLine;
	data._strTargetFile = strPathName;
	pFrame->AddBookmarkLineDataToPane(data);
}

void CEditorView::OnOptionsAddBreakPoint()
{
	CEditorDoc *pDoc = GetEditorDocument();
	if (!pDoc) return;
	CString strPathName = pDoc->GetPathName();
	if (!PathFileExists(strPathName)) return;
	CString strLine;
	m_EditorCtrl.GetTextFromLine(m_EditorCtrl.GetCurrentLine(), strLine);
	if (!strLine.Trim().IsEmpty() && !IsCommentLineCode(strLine))
	{
		if (m_EditorCtrl.AddBreakPoint(m_CurrentDocLanguage, m_EditorCtrl.GetCurrentLine(), strPathName))
		{
			UpdateDockPaneBreakpoint(m_EditorCtrl.GetCurrentLine(), FALSE, strPathName, PathUtils::GetFileNameWithoutExtension(pDoc->GetTitle()));
		}
	}
}

void CEditorView::OnUpdateOptionsAddBreakPoint(CCmdUI * pCmdUI)
{
	int curLine = m_EditorCtrl.GetCurrentLine();
	CString strLine;
	m_EditorCtrl.GetTextFromLine(curLine, strLine);
	pCmdUI->Enable(!m_EditorCtrl.IsLineHasBreakPoint(curLine)
	&& AppUtils::IsLanguageSupportDebugger(m_CurrentDocLanguage) && !IsCommentLineCode(strLine));
}

void CEditorView::OnOptionsDeleteBreakPoint()
{
	CEditorDoc *pDoc = GetEditorDocument();
	if (!pDoc) return;
	CString strPathName = pDoc->GetPathName();
	if (!PathFileExists(strPathName)) return;
	if (m_EditorCtrl.DeleteBreakPoint(m_CurrentDocLanguage, m_EditorCtrl.GetCurrentLine(), strPathName))
	{
		UpdateDockPaneBreakpoint(m_EditorCtrl.GetCurrentLine(), TRUE, strPathName, PathUtils::GetFileNameWithoutExtension(pDoc->GetTitle()));
	}
}

void CEditorView::OnUpdateOptionsDeleteBreakPoint(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(m_EditorCtrl.IsLineHasBreakPoint(m_EditorCtrl.GetCurrentLine()));
}

void CEditorView::OnOptionsDeleteAllBreakPoint()
{
	if (ThreadWorkerMgr.IsDebuggerRunning())
	{
		VinaTextDebugger.RemoveAllBreakPointDataInLanguage(m_CurrentDocLanguage);
		CMainFrame* pFrame = AppUtils::GetMainFrame();
		if (!pFrame) return;
		pFrame->RemoveAllBreakPointDebuggerDoc(m_CurrentDocLanguage);
	}
	else
	{
		POSITION p1 = AfxGetApp()->GetFirstDocTemplatePosition();
		while (p1)
		{
			CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(p1);
			POSITION p2 = doctempl->GetFirstDocPosition();
			while (p2)
			{
				CEditorDoc* pDoc = dynamic_cast<CEditorDoc*>(doctempl->GetNextDoc(p2));
				if (pDoc && pDoc->GetEditorView() &&  AppUtils::IsLanguageSupportDebugger(pDoc->GetEditorView()->GetCurrentDocLanguague()))
				{
					pDoc->GetEditorCtrl()->DeleteAllBreakPoint();
					if (PathFileExists(pDoc->GetPathName()))
					{
						VinaTextDebugger.RemoveBreakPointDataInFile(pDoc->GetPathName());
					}
				}
			}
		}
	}
}

void CEditorView::OnUpdateOptionsDeleteAllBreakPoints(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(m_EditorCtrl.HasBreakPoints());
}

void CEditorView::OnOptionsFindNextBreakPoint()
{
	m_EditorCtrl.FindNextBreakPoint();
}

void CEditorView::OnUpdateOptionsFindNextBreakPoint(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(m_EditorCtrl.HasBreakPoints());
}

void CEditorView::OnOptionsFindPrevBreakPoint()
{
	m_EditorCtrl.FindPreviousBreakPoint();
}

void CEditorView::OnUpdateOptionsFindPrevBreakPoint(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(m_EditorCtrl.HasBreakPoints());
}

void CEditorView::OnOptionsAddBookmark()
{
	CEditorDoc *pDoc = GetEditorDocument();
	if (!pDoc) return;
	CString strPathName = pDoc->GetPathName();
	if (!PathFileExists(strPathName)) return;
	int nBookmarkLine = m_EditorCtrl.GetCurrentLine();
	if (!m_EditorCtrl.IsLineHasBookMark(nBookmarkLine)
		&& m_EditorCtrl.AddBookMark(nBookmarkLine, strPathName))
	{
		UpdateDockPaneBookmark(nBookmarkLine, FALSE, strPathName);
	}
}

void CEditorView::OnUpdateOptionsAddBookmark(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(!m_EditorCtrl.IsLineHasBookMark(m_EditorCtrl.GetCurrentLine()));
}

void CEditorView::OnOptionsDeleteBookmark()
{
	CEditorDoc *pDoc = GetEditorDocument();
	if (!pDoc) return;
	CString strPathName = pDoc->GetPathName();
	if (!PathFileExists(strPathName)) return;
	int nBookmarkLine = m_EditorCtrl.GetCurrentLine();
	if (m_EditorCtrl.IsLineHasBookMark(nBookmarkLine) 
		&& m_EditorCtrl.DeleteBookMark(nBookmarkLine, strPathName))
	{
		UpdateDockPaneBookmark(nBookmarkLine, TRUE, strPathName);
	}
}

void CEditorView::OnUpdateOptionsDeleteBookmark(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(m_EditorCtrl.IsLineHasBookMark(m_EditorCtrl.GetCurrentLine()));
}

void CEditorView::OnOptionsDeleteAllBookmark()
{
	m_EditorCtrl.DeleteAllBookMark();
}

void CEditorView::OnUpdateOptionsDeleteAllBookmark(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(m_EditorCtrl.HasBookmarks());
}

void CEditorView::OnOptionsToggleAutoComplete()
{
	TOGGLE_FLAG(AppSettingMgr.m_bEnableAutoComplete);
	if (!AppSettingMgr.m_bEnableAutoComplete)
	{
		LOG_OUTPUT_MESSAGE_COLOR(_T("> Auto show complete list box was disable, you can use Ctrl + Space instead."));
	}
}

void CEditorView::OnUpdateOptionsToggleAutoComplete(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(AppSettingMgr.m_bEnableAutoComplete);
}

void CEditorView::OnOptionsFindNextBookmark()
{
	m_EditorCtrl.FindNextBreakPoint();
}

void CEditorView::OnOptionsFindPrevBookmark()
{
	m_EditorCtrl.FindPreviousBreakPoint();
}

void CEditorView::OnOptionsGotopos()
{
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;
	CString strCurLine = AppUtils::IntToCString(m_EditorCtrl.GetCurrentLine());
	pFrame->InitSearchReplaceFromEditor(strCurLine, SEARCH_REPLACE_GOTO_DLG_TYPE::GOTO);
}

void CEditorView::OnOptionGotoline()
{
	QuickGotoLine dlg;
	dlg.DoModal();
}

void CEditorView::OnOptionSearch()
{
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;
	pFrame->InitSearchReplaceFromEditor(m_EditorCtrl.GetSelectedText(), SEARCH_REPLACE_GOTO_DLG_TYPE::SEARCH);
}

void CEditorView::OnOptionReplace()
{
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;
	pFrame->InitSearchReplaceFromEditor(m_EditorCtrl.GetSelectedText(), SEARCH_REPLACE_GOTO_DLG_TYPE::REPLACE);
}

void CEditorView::OnOptionsWrapLine()
{
	m_EditorCtrl.EnableTextWrappingMode(!m_EditorCtrl.IsEditorInWrapMode());
}

void CEditorView::OnUpdateOptionsWrapLine(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_EditorCtrl.IsEditorInWrapMode());
}

void CEditorView::OnOptionsLongLineChecker()
{
	m_EditorCtrl.EnableLongLineChecker(!m_EditorCtrl.IsEditorLongLineCheckerEnable());
}

void CEditorView::OnUpdateOptionsLongLineChecker(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_EditorCtrl.IsEditorLongLineCheckerEnable());
}

void CEditorView::OnUpdateInsert(CCmdUI * pCmdUI)
{
	CString strText;
	if (m_EditorCtrl.GetOverstrike())
	{
		strText.LoadString(ID_INDICATOR_OVR);
	}
	else
	{
		strText.LoadString(ID_INDICATOR_INS);
	}
	pCmdUI->SetText(strText);
}

void CEditorView::OnOptionsToggleInsert()
{
	m_EditorCtrl.SetOverstrike(!m_EditorCtrl.GetOverstrike());
}

void CEditorView::OnOptionsFoldMargin()
{
	m_EditorCtrl.SetDisplayFolding(!m_EditorCtrl.GetDisplayFolding());
}

void CEditorView::OnUpdateOptionsFoldMargin(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_EditorCtrl.GetDisplayFolding());
}

void CEditorView::OnOptionsSelectionMargin()
{
	m_EditorCtrl.SetDisplaySelection(!m_EditorCtrl.GetDisplaySelection());
}

void CEditorView::OnUpdateOptionsSelectionMargin(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_EditorCtrl.GetDisplaySelection());
}

void CEditorView::OnUpdateOptionsViewLinenumbers(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_EditorCtrl.GetDisplayLinenumbers());
}

void CEditorView::OnOptionsSelectToEnd()
{
	m_EditorCtrl.SetStartSelection(m_EditorCtrl.GetCurrentPosition());
	m_EditorCtrl.SetEndSelection(m_EditorCtrl.GetTextLength());
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsSelectToBegin()
{
	m_EditorCtrl.SetStartSelection(0);
	m_EditorCtrl.SetEndSelection(m_EditorCtrl.GetCurrentPosition());
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsSelectToWordLeft()
{
	m_EditorCtrl.DoCommand(SCI_WORDLEFTENDEXTEND);
}

void CEditorView::OnOptionsSelectToWordRight()
{
	m_EditorCtrl.DoCommand(SCI_WORDRIGHTENDEXTEND);
}

void CEditorView::OnOptionsSelectToPartLeft()
{
	m_EditorCtrl.DoCommand(SCI_WORDPARTLEFTEXTEND);
}

void CEditorView::OnOptionsSelectToPartRight()
{
	m_EditorCtrl.DoCommand(SCI_WORDPARTRIGHTEXTEND);
}

void CEditorView::OnOptionsRemoveDuplicateLineNotKeep()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stScript;
	m_EditorCtrl.GetText(stScript);
	if (!stScript.IsEmpty())
	{
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		if (stSelectedScript.IsEmpty())
		{
			typedef std::map<std::wstring, int> line_record;
			line_record lines;
			int line_number = 1;
			std::wstring line;
			std::wistringstream iss(AppUtils::CStringToWStd(stScript));

			while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
			{
				AppUtils::ReplaceAllInWStdString(line, L"\n", L"");
				AppUtils::ReplaceAllInWStdString(line, L"\r", L"");
				line_record::iterator existing = lines.find(line);
				if (existing != lines.end()) // if it was already in the map
				{
					existing->second = -1;    // indicate that it's duplicated
				}
				else
				{
					lines.insert(std::make_pair(line, line_number)); // otherwise, add it to map
				}
				++line_number;
			}

			line_record::iterator pos;

			std::vector<line_record::iterator> sortable_lines;

			for (pos = lines.begin(); pos != lines.end(); ++pos)
			{
				if (pos->second != -1)
				{
					sortable_lines.push_back(pos);
				}
			}

			struct inline_struct_by_line_number
			{
				bool operator()(line_record::iterator a, line_record::iterator b)
				{
					return a->second < b->second;
				}
			};

			std::sort(sortable_lines.begin(), sortable_lines.end(), inline_struct_by_line_number());

			CString strNewScripts;
			for (int i = 0; i < sortable_lines.size(); i++)
			{
				strNewScripts += AppUtils::WStdToCString(sortable_lines[i]->first) + m_EditorCtrl.GetEOLCString();
			}
			m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
		}
		else
		{
			int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
			int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
			int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
			int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
			int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
			int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

			typedef std::map<std::wstring, int> line_record;
			line_record lines;
			int line_number = 1;

			for (int i = lLineStart; i <= lLineEnd; ++i)
			{
				CString strCurLineText;
				m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
				AppUtils::ReplaceAllInWStdString(AppUtils::CStringToWStd(strCurLineText), L"\n", L"");
				AppUtils::ReplaceAllInWStdString(AppUtils::CStringToWStd(strCurLineText), L"\r", L"");
				line_record::iterator existing = lines.find(AppUtils::CStringToWStd(strCurLineText));
				if (existing != lines.end()) // if it was already in the map
				{
					existing->second = -1;    // indicate that it's duplicated
				}
				else
				{
					lines.insert(std::make_pair(AppUtils::CStringToWStd(strCurLineText), line_number)); // otherwise, add it to map
				}
				++line_number;
			}

			line_record::iterator pos;

			std::vector<line_record::iterator> sortable_lines;

			for (pos = lines.begin(); pos != lines.end(); ++pos)
			{
				if (pos->second != -1)
				{
					sortable_lines.push_back(pos);
				}
			}

			struct inline_struct_by_line_number
			{
				bool operator()(line_record::iterator a, line_record::iterator b)
				{
					return a->second < b->second;
				}
			};

			std::sort(sortable_lines.begin(), sortable_lines.end(), inline_struct_by_line_number());

			CString strNewScripts;
			for (int i = 0; i < sortable_lines.size(); i++)
			{
				strNewScripts += AppUtils::WStdToCString(sortable_lines[i]->first) + m_EditorCtrl.GetEOLCString();
			}

			m_EditorCtrl.SetStartSelection(StartLinePos);
			m_EditorCtrl.SetEndSelection(EndLinePos);
			m_EditorCtrl.ReplaceSelectionWithText(strNewScripts.Mid(0, strNewScripts.GetLength()));
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsRemoveDuplicateLine()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stScript;
	m_EditorCtrl.GetText(stScript);
	if (!stScript.IsEmpty())
	{
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		if (stSelectedScript.IsEmpty())
		{
			typedef std::map<std::wstring, int> line_record;
			line_record lines;
			int line_number = 1;
			std::wstring line;
			std::wistringstream iss(AppUtils::CStringToWStd(stScript));

			while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
			{
				AppUtils::ReplaceAllInWStdString(line, L"\n", L"");
				AppUtils::ReplaceAllInWStdString(line, L"\r", L"");
				line_record::iterator existing = lines.find(line);
				if (existing == lines.end()) // if it was already in the map
				{
					lines.insert(std::make_pair(line, line_number)); // otherwise, add it to map
				}
				++line_number;
			}

			line_record::iterator pos;

			std::vector<line_record::iterator> sortable_lines;

			for (pos = lines.begin(); pos != lines.end(); ++pos)
			{
				if (pos->second != -1)
				{
					sortable_lines.push_back(pos);
				}
			}

			struct inline_struct_by_line_number
			{
				bool operator()(line_record::iterator a, line_record::iterator b)
				{
					return a->second < b->second;
				}
			};

			std::sort(sortable_lines.begin(), sortable_lines.end(), inline_struct_by_line_number());

			CString strNewScripts;
			for (int i = 0; i < sortable_lines.size(); i++)
			{
				strNewScripts += AppUtils::WStdToCString(sortable_lines[i]->first) + m_EditorCtrl.GetEOLCString();
			}
			m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
		}
		else
		{
			int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
			int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
			int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
			int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
			int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
			int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

			typedef std::map<std::wstring, int> line_record;
			line_record lines;
			int line_number = 1;

			for (int i = lLineStart; i <= lLineEnd; ++i)
			{
				CString strCurLineText;
				m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
				AppUtils::ReplaceAllInWStdString(AppUtils::CStringToWStd(strCurLineText), L"\n", L"");
				AppUtils::ReplaceAllInWStdString(AppUtils::CStringToWStd(strCurLineText), L"\r", L"");
				line_record::iterator existing = lines.find(AppUtils::CStringToWStd(strCurLineText));
				if (existing == lines.end()) // if it was already in the map
				{
					lines.insert(std::make_pair(AppUtils::CStringToWStd(strCurLineText), line_number)); // otherwise, add it to map
				}
				++line_number;
			}

			line_record::iterator pos;

			std::vector<line_record::iterator> sortable_lines;

			for (pos = lines.begin(); pos != lines.end(); ++pos)
			{
				if (pos->second != -1)
				{
					sortable_lines.push_back(pos);
				}
			}

			struct inline_struct_by_line_number
			{
				bool operator()(line_record::iterator a, line_record::iterator b)
				{
					return a->second < b->second;
				}
			};

			std::sort(sortable_lines.begin(), sortable_lines.end(), inline_struct_by_line_number());

			CString strNewScripts;
			for (int i = 0; i < sortable_lines.size(); i++)
			{
				strNewScripts += AppUtils::WStdToCString(sortable_lines[i]->first) + m_EditorCtrl.GetEOLCString();
			}

			m_EditorCtrl.SetStartSelection(StartLinePos);
			m_EditorCtrl.SetEndSelection(EndLinePos);
			m_EditorCtrl.ReplaceSelectionWithText(strNewScripts.Mid(0, strNewScripts.GetLength()));
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsRemoveDuplicateWordInLine()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stScript;
	m_EditorCtrl.GetText(stScript);
	if (!stScript.IsEmpty())
	{
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		if (stSelectedScript.IsEmpty())
		{
			std::wstring line;
			std::wistringstream iss(AppUtils::CStringToWStd(stScript));

			CString strNewScripts;
			while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
			{
				CString strLine = AppUtils::WStdToCString(line);
				strLine.Replace(_T("\n"), _T(""));
				CString strTemp = strLine;
				if (!strTemp.Trim().IsEmpty())
				{
					std::wstring newLine = AppUtils::RemoveDuplicateWordInString(line);
					strNewScripts += AppUtils::WStdToCString(newLine).Trim() + m_EditorCtrl.GetEOLCString();
				}
			}

			m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
		}
		else
		{
			int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
			int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
			int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
			int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
			int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
			int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

			CString strNewScripts;
			for (int i = lLineStart; i <= lLineEnd; ++i)
			{
				CString strCurLineText;
				m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
				CString strTemp = strCurLineText;
				if (!strTemp.Trim().IsEmpty())
				{
					std::wstring newLine = AppUtils::RemoveDuplicateWordInString(AppUtils::CStringToWStd(strCurLineText));
					strNewScripts += AppUtils::WStdToCString(newLine).Trim() + m_EditorCtrl.GetEOLCString();
				}
			}

			m_EditorCtrl.SetStartSelection(StartLinePos);
			m_EditorCtrl.SetEndSelection(EndLinePos);
			m_EditorCtrl.ReplaceSelectionWithText(strNewScripts.Mid(0, strNewScripts.GetLength()));
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsRemoveDuplicateWord()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
		CString stScript;
	m_EditorCtrl.GetText(stScript);
	if (!stScript.IsEmpty())
	{
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		if (stSelectedScript.IsEmpty())
		{
			CStringArray arrLine;
			std::vector<std::wstring> vecOutString;
			std::unordered_set<std::wstring> hash_tab;
			AppUtils::SplitCString(stScript, m_EditorCtrl.GetEOLCString(), arrLine);
			for (int i = 0; i < arrLine.GetSize(); ++i)
			{
				std::vector<std::wstring> vecCString = AppUtils::SplitterWStdString(AppUtils::CStringToWStd(arrLine[i]), L" ");
				std::wstring line = L"";
				for (auto const& str : vecCString)
				{
					std::wstring wordCase = str;
					boost::to_lower(wordCase);
					while (hash_tab.find(str) == hash_tab.end()
						&& hash_tab.find(wordCase) == hash_tab.end())
					{
						line += str + L" ";
						hash_tab.insert(str);
					}
				}

				boost::trim(line);
				if (!line.empty())
				{
					vecOutString.push_back(line);
				}
			}
			std::wstring strSTD = StringHelper::JoinStdString<std::wstring>(L"\n", vecOutString);
			m_EditorCtrl.SetTextToEditor(AppUtils::WStdToCString(strSTD));
		}
		else
		{
			int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
			int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
			int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
			int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
			int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
			int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

			CString strNewScripts;
			std::vector<std::wstring> vecOutString;
			std::unordered_set<std::wstring> hash_tab;
			for (int i = lLineStart; i <= lLineEnd; ++i)
			{
				CString strCurLineText;
				m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
				std::vector<std::wstring> vecCString = AppUtils::SplitterWStdString(AppUtils::CStringToWStd(strCurLineText), L" ");
				std::wstring line = L"";
				for (auto const& str : vecCString)
				{
					std::wstring wordCase = str;
					boost::to_lower(wordCase);
					while (hash_tab.find(str) == hash_tab.end()
						&& hash_tab.find(wordCase) == hash_tab.end())
					{
						line += str + L" ";
						hash_tab.insert(str);
					}
				}

				boost::trim(line);
				if (!line.empty())
				{
					vecOutString.push_back(line);
				}
			}
			std::wstring strSTD = StringHelper::JoinStdString<std::wstring>(L"\n", vecOutString);
			strNewScripts = AppUtils::WStdToCString(strSTD);
			m_EditorCtrl.SetStartSelection(StartLinePos);
			m_EditorCtrl.SetEndSelection(EndLinePos);
			m_EditorCtrl.ReplaceSelectionWithText(strNewScripts);
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsRemoveDuplicateMatchCaseWord()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
		CString stScript;
	m_EditorCtrl.GetText(stScript);
	if (!stScript.IsEmpty())
	{
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		if (stSelectedScript.IsEmpty())
		{
			CStringArray arrLine;
			std::vector<std::wstring> vecOutString;
			std::unordered_set<std::wstring> hash_tab;
			AppUtils::SplitCString(stScript, m_EditorCtrl.GetEOLCString(), arrLine);
			for (int i = 0; i < arrLine.GetSize(); ++i)
			{
				std::vector<std::wstring> vecCString = AppUtils::SplitterWStdString(AppUtils::CStringToWStd(arrLine[i]), L" ");
				std::wstring line = L"";
				for (auto const& str : vecCString)
				{
					while (hash_tab.find(str) == hash_tab.end())
					{
						line += str + L" ";
						hash_tab.insert(str);
					}
				}

				boost::trim(line);
				if (!line.empty())
				{
					vecOutString.push_back(line);
				}
			}
			std::wstring strSTD = StringHelper::JoinStdString<std::wstring>(L"\n", vecOutString);
			m_EditorCtrl.SetTextToEditor(AppUtils::WStdToCString(strSTD));
		}
		else
		{
			int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
			int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
			int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
			int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
			int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
			int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

			CString strNewScripts;
			std::vector<std::wstring> vecOutString;
			std::unordered_set<std::wstring> hash_tab;
			for (int i = lLineStart; i <= lLineEnd; ++i)
			{
				CString strCurLineText;
				m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
				std::vector<std::wstring> vecCString = AppUtils::SplitterWStdString(AppUtils::CStringToWStd(strCurLineText), L" ");
				std::wstring line = L"";
				for (auto const& str : vecCString)
				{
					while (hash_tab.find(str) == hash_tab.end())
					{
						line += str + L" ";
						hash_tab.insert(str);
					}
				}

				boost::trim(line);
				if (!line.empty())
				{
					vecOutString.push_back(line);
				}
			}
			std::wstring strSTD = StringHelper::JoinStdString<std::wstring>(L"\n", vecOutString);
			strNewScripts = AppUtils::WStdToCString(strSTD);
			m_EditorCtrl.SetStartSelection(StartLinePos);
			m_EditorCtrl.SetEndSelection(EndLinePos);
			m_EditorCtrl.ReplaceSelectionWithText(strNewScripts);
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsRemoveEmptyLine()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stScript;
	m_EditorCtrl.GetText(stScript);
	if (!stScript.IsEmpty())
	{
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		if (stSelectedScript.IsEmpty())
		{
			std::wstring line;
			std::wistringstream iss(AppUtils::CStringToWStd(stScript));

			CString strNewScripts;
			while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
			{
				CString strLine = AppUtils::WStdToCString(line);
				strLine.Replace(_T("\n"), _T(""));
				CString strTemp = strLine;
				if (!strTemp.Trim().IsEmpty())
				{
					strNewScripts += strLine + m_EditorCtrl.GetEOLCString();
				}
			}

			m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength() -2));
		}
		else
		{
			int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
			int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
			int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
			int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
			int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
			int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

			CString strNewScripts;
			for (int i = lLineStart; i <= lLineEnd; ++i)
			{
				CString strCurLineText;
				m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
				CString strTemp = strCurLineText;
				if (!strTemp.Trim().IsEmpty())
				{
					strNewScripts += strCurLineText + m_EditorCtrl.GetEOLCString();
				}
			}

			m_EditorCtrl.SetStartSelection(StartLinePos);
			m_EditorCtrl.SetEndSelection(EndLinePos);
			m_EditorCtrl.ReplaceSelectionWithText(strNewScripts.Mid(0, strNewScripts.GetLength()));
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsRemoveLineContainX()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CEditWithXDlg dlg;
	dlg.m_strDlgCaption = _T("Remove line contain word...");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_sXInput.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}
		std::vector<CString> vecX = AppUtils::SplitterCString(dlg.m_sXInput, ",");
		auto fChecker = [&](const CString& strLine) -> BOOL
		{
			int nCount = 0;
			for (auto const& x : vecX)
			{
				if (strLine.Find(x) != -1) nCount++;
			}
			if (nCount == static_cast<int>(vecX.size()))
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		};
		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));

				CString strNewScripts;
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					if (fChecker(strLine) == FALSE)
					{
						strNewScripts += strLine + m_EditorCtrl.GetEOLCString();
					}
				}

				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
				int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
				int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

				CString strNewScripts;
				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					if (fChecker(strCurLineText) == FALSE)
					{
						strNewScripts += strCurLineText + m_EditorCtrl.GetEOLCString();
					}
				}

				m_EditorCtrl.SetStartSelection(StartLinePos);
				m_EditorCtrl.SetEndSelection(EndLinePos);
				m_EditorCtrl.ReplaceSelectionWithText(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsRemoveLineNotContainX()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CEditWithXDlg dlg;
	dlg.m_strDlgCaption = _T("Remove line NOT contain word...");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_sXInput.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}
		std::vector<CString> vecX = AppUtils::SplitterCString(dlg.m_sXInput, ",");
		auto fChecker = [&](const CString& strLine) -> BOOL
		{
			int nCount = 0;
			for (auto const& x : vecX)
			{
				if (strLine.Find(x) != -1) nCount++;
			}
			if (nCount == static_cast<int>(vecX.size()))
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		};
		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));

				CString strNewScripts;
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					if (fChecker(strLine))
					{
						strNewScripts += strLine + m_EditorCtrl.GetEOLCString();
					}
				}
				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
				int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
				int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

				CString strNewScripts;
				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					if (fChecker(strCurLineText))
					{
						strNewScripts += strCurLineText + m_EditorCtrl.GetEOLCString();
					}
				}
				m_EditorCtrl.SetStartSelection(StartLinePos);
				m_EditorCtrl.SetEndSelection(EndLinePos);
				m_EditorCtrl.ReplaceSelectionWithText(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsTrimLine()
{
	TrimLine(1);
}

void CEditorView::OnOptionsTrimTrailingLine()
{
	TrimLine(3);
}

void CEditorView::OnOptionsTrimHeadingLine()
{
	TrimLine(2);
}

void CEditorView::OnOptionsInsertFileAsText()
{
	// Default File Filter
	CString strDefaultFilter = PathUtils::GetDataBaseFileFilter();
	CFileDialog fileDlg(TRUE, NULL, _T("*.*"), OFN_FILEMUSTEXIST, strDefaultFilter);
	fileDlg.m_ofn.lpstrTitle = _T("Please select file to insert...");
	if (fileDlg.DoModal() != IDOK)
	{
		return;
	}
	CString stFilePath = fileDlg.GetPathName();

	CString stScript;
	if (PathUtils::OpenFile(stFilePath, stScript))
	{
		int lCurPos = m_EditorCtrl.GetCurrentPosition();
		m_EditorCtrl.InsertText(stScript, lCurPos);
	}
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsInsertLineAbove()
{
	int lCurPos = m_EditorCtrl.GetCurrentPosition();
	int lCurLine = m_EditorCtrl.GetLineFromPosition(lCurPos);
	int lStartPosLine = m_EditorCtrl.GetLineStartPosition(lCurLine);
	m_EditorCtrl.InsertText(m_EditorCtrl.GetEOLCString(), lStartPosLine);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsInsertLineBelow()
{
	int lCurPos = m_EditorCtrl.GetCurrentPosition();
	int lCurLine = m_EditorCtrl.GetLineFromPosition(lCurPos);
	int lEndPosLine = m_EditorCtrl.GetLineEndPosition(lCurLine);
	m_EditorCtrl.InsertText(m_EditorCtrl.GetEOLCString(), lEndPosLine);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsDuplicateSelection()
{
	if (m_EditorCtrl.IsTextSelected())
		m_EditorCtrl.DoCommand(SCI_SELECTIONDUPLICATE);
	else
		m_EditorCtrl.DoCommand(SCI_LINEDUPLICATE);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsIncreaseSelectionToWordLeft()
{
	m_EditorCtrl.DoCommand(SCI_WORDLEFTEXTEND);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsIncreaseSelectionToWordRight()
{
	m_EditorCtrl.DoCommand(SCI_WORDRIGHTEXTEND);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsIncreaseSelectionToPartLeft()
{
	m_EditorCtrl.DoCommand(SCI_WORDPARTLEFTEXTEND);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsIncreaseSelectionToPartRight()
{
	m_EditorCtrl.DoCommand(SCI_WORDPARTRIGHTEXTEND);
	m_EditorCtrl.SetFocus();
}

void CEditorView::ResetMultipleSelectionsBuffer()
{
	m_strSelectedWord.Empty();
	m_nLatestCaretPosition = 0;
	m_PositionMultipleCaretsBuffer.clear();
	m_nIncreaseSelectionSearchFlag = SCFIND_WHOLEWORD | SCFIND_MATCHCASE;
	m_bSelectionByMouseDrag = FALSE;
}

void CEditorView::OnOptionsIncreaseSelectionToWord()
{
	auto fAddNewSelection = [&](int lNextPos, int lAnchorPos) -> BOOL {
		m_nLatestCaretPosition = lNextPos + m_strSelectedWord.GetLength();
		if (m_PositionMultipleCaretsBuffer.find(m_nLatestCaretPosition) != m_PositionMultipleCaretsBuffer.end()) return FALSE;
		m_PositionMultipleCaretsBuffer.insert(m_nLatestCaretPosition);
		if (m_nLatestCaretPosition != lAnchorPos)
		{
			m_EditorCtrl.DoCommand(SCI_ADDSELECTION, m_nLatestCaretPosition, lNextPos);
			m_EditorCtrl.RemoveEachIndicatorHightLight(lNextPos, m_nLatestCaretPosition);
		}
		else
		{
			lNextPos = m_EditorCtrl.FindNextMatchWordPostion(m_strSelectedWord, lAnchorPos, m_nIncreaseSelectionSearchFlag);
			if (lNextPos >= 0)
			{
				m_EditorCtrl.DoCommand(SCI_ADDSELECTION, m_nLatestCaretPosition, lNextPos);
				m_EditorCtrl.RemoveEachIndicatorHightLight(lNextPos, m_nLatestCaretPosition);
			}
		}
		return TRUE;
	};

	BOOL bIsSearchFromStartFile = FALSE;
	m_EditorCtrl.SetIncreaseSelectionMode(FALSE, FALSE);
	int nSels = m_EditorCtrl.GetSelectionNumber();
	if (nSels == 1 && m_EditorCtrl.GetSelectedText().IsEmpty()) // reset conditions
	{
		m_EditorCtrl.DoCommand(SCI_MULTIPLESELECTADDNEXT);
		m_EditorCtrl.SetLineCenterKeepView(m_EditorCtrl.GetCurrentLine());
		ResetMultipleSelectionsBuffer();
		m_strSelectedWord = m_EditorCtrl.GetSelectedText();
		// mark all to decide stop at next word or not...
		RenderIndicatorWordsAndCount(m_strSelectedWord);
	}
	else
	{ 
		if (!m_EditorCtrl.GetSelectedText().IsEmpty())
		{
			if (m_bSelectionByMouseDrag)
			{
				m_nIncreaseSelectionSearchFlag = SCFIND_MATCHCASE;
			}
			m_bSelectionByMouseDrag = TRUE;
			m_strSelectedWord = m_EditorCtrl.GetSelectedText();
			// mark all to decide stop at next word or not...
			RenderIndicatorWordsAndCount(m_strSelectedWord);
		}
		if (!m_strSelectedWord.IsEmpty())
		{
			if (m_nLatestCaretPosition == 0) {
				m_nLatestCaretPosition = m_EditorCtrl.GetSelectionEndPosition();
				m_PositionMultipleCaretsBuffer.insert(m_nLatestCaretPosition);
			}
			int lNextPos = m_EditorCtrl.FindNextMatchWordPostion(m_strSelectedWord, m_nLatestCaretPosition, m_nIncreaseSelectionSearchFlag);
			int lAnchorPos = m_EditorCtrl.GetCurrentAnchor();
			if (lNextPos >= 0)
			{
				if (fAddNewSelection(lNextPos, lAnchorPos))
					m_EditorCtrl.SetLineCenterKeepView(m_EditorCtrl.GetCurrentLine());
			}
			else // search from start file position if there is no more match word...
			{
				bIsSearchFromStartFile = TRUE;
				lNextPos = m_EditorCtrl.FindNextMatchWordPostion(m_strSelectedWord, 0, m_nIncreaseSelectionSearchFlag);
				if (lNextPos >= 0)
				{
					if (fAddNewSelection(lNextPos, lAnchorPos))
						m_EditorCtrl.SetLineCenterDisplay(m_EditorCtrl.GetCurrentLine());
				}
			}
		}
		else
		{
			if (nSels > 1)
			{
				std::vector<int> beforeSelectCarets;
				beforeSelectCarets.reserve(nSels);
				for (int i = 0; i < nSels; ++i)
				{
					beforeSelectCarets.push_back(m_EditorCtrl.GetSelectionNumberCaret(i));
				}
				for (int i = 0; i < beforeSelectCarets.size(); ++i)
				{
					int wordStart = m_EditorCtrl.GetWordStartPosition(beforeSelectCarets[i], TRUE);
					int wordEnd = m_EditorCtrl.GetWordEndPosition(beforeSelectCarets[i], TRUE);
					m_EditorCtrl.DoCommand(SCI_ADDSELECTION, wordEnd, wordStart);
				}
				m_EditorCtrl.UpdateMainSelectionInCurrentView();
			}
		}
	}
	// save information for multiple undo redo transactions
	m_EditorCtrl.SetIncreaseSelectionMode(TRUE, bIsSearchFromStartFile);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsIncreaseSelectionToQuote()
{
	int nSels = m_EditorCtrl.GetSelectionNumber();
	if (nSels > 1)
	{
		std::vector<int> beforeSelectCarets;
		beforeSelectCarets.reserve(nSels);
		for (int i = 0; i < nSels; ++i)
		{
			beforeSelectCarets.push_back(m_EditorCtrl.GetSelectionNumberCaret(i));
		}
		for (int i = 0; i < beforeSelectCarets.size(); ++i)
		{
			int current = beforeSelectCarets[i];
			int targetNextDoubleQuote = m_EditorCtrl.FindNextMatchWordPostion(_T("\""), current, 0);
			int targetPreviousDoubleQuote = m_EditorCtrl.FindPreviousMatchWordPostion(_T("\""), current, current, 0);
			int targetNextSingleQuote = m_EditorCtrl.FindNextMatchWordPostion(_T("'"), current, 0);
			int targetPreviousSingleQuote = m_EditorCtrl.FindPreviousMatchWordPostion(_T("'"), current, current, 0);

			if ((targetPreviousDoubleQuote != -1 && targetNextDoubleQuote != -1) || (targetPreviousSingleQuote != -1 && targetNextSingleQuote != -1))
			{
				if (targetPreviousDoubleQuote >= targetPreviousSingleQuote)
				{
					m_EditorCtrl.DoCommand(SCI_ADDSELECTION, targetNextDoubleQuote, targetPreviousDoubleQuote + 1);
				}
				else
				{
					m_EditorCtrl.DoCommand(SCI_ADDSELECTION, targetNextSingleQuote, targetPreviousSingleQuote + 1);
				}
			}
			else
			{
				int wordStart = m_EditorCtrl.GetWordStartPosition(current, TRUE);
				int wordEnd = m_EditorCtrl.GetWordEndPosition(current, TRUE);
				m_EditorCtrl.DoCommand(SCI_ADDSELECTION, wordEnd, wordStart);
			}
		}
	}
	else
	{
		int current = m_EditorCtrl.GetCurrentPosition();
		int targetNextDoubleQuote = m_EditorCtrl.FindNextMatchWordPostion(_T("\""), current, 0);
		int targetPreviousDoubleQuote = m_EditorCtrl.FindPreviousMatchWordPostion(_T("\""), current, m_EditorCtrl.GetSelectionStartPosition(), 0);
		int targetNextSingleQuote = m_EditorCtrl.FindNextMatchWordPostion(_T("'"), current, 0);
		int targetPreviousSingleQuote = m_EditorCtrl.FindPreviousMatchWordPostion(_T("'"), current, m_EditorCtrl.GetSelectionStartPosition(), 0);

		if ((targetPreviousDoubleQuote != -1 && targetNextDoubleQuote != -1) || (targetPreviousSingleQuote != -1 && targetNextSingleQuote != -1))
		{
			if (targetPreviousDoubleQuote >= targetPreviousSingleQuote)
			{
				m_EditorCtrl.SetSelectionRange(targetPreviousDoubleQuote + 1, targetNextDoubleQuote);
			}
			else
			{
				m_EditorCtrl.SetSelectionRange(targetPreviousSingleQuote + 1, targetNextSingleQuote);
			}
		}
		else
		{
			int wordStart = m_EditorCtrl.GetWordStartPosition(current, TRUE);
			int wordEnd = m_EditorCtrl.GetWordEndPosition(current, TRUE);
			m_EditorCtrl.SetSelectionRange(wordStart, wordEnd);
		}
	}
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsIncreaseSelectionToLine()
{
	m_EditorCtrl.DoCommand(SCI_HOME);
	m_EditorCtrl.DoCommand(SCI_LINEENDEXTEND);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsDeleteLine()
{
	m_EditorCtrl.DoCommand(SCI_LINEDELETE);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsSelectionColumnMode()
{
	LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> Selection by column mode can be used with [Ctrl + Shift + Arrow Up/Down] or [Alt + Left Mouse Drag] or [Shift + Alt + Arrow Key]..."), BasicColors::orange);
}

void CEditorView::OnOptionsInsertXAtBeginLine()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CEditWithXDlg dlg;
	dlg.m_strDlgCaption = _T("Insert Word At Begin Line");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_sXInput.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}
		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				CString strNewScripts;
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					strNewScripts += dlg.m_sXInput + strLine + m_EditorCtrl.GetEOLCString();
				}
				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);

				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					int lLineStartPos = m_EditorCtrl.GetLineStartPosition(i);
					m_EditorCtrl.InsertText(dlg.m_sXInput, lLineStartPos);
				}
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsInsertXAtEndLine()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CEditWithXDlg dlg;
	dlg.m_strDlgCaption = _T("Insert Word At End Line");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_sXInput.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}
		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				CString strNewScripts;
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					strNewScripts += strLine + dlg.m_sXInput + m_EditorCtrl.GetEOLCString();
				}
				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);

				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					int lLineEndPos = m_EditorCtrl.GetLineEndPosition(i);
					m_EditorCtrl.InsertText(dlg.m_sXInput, lLineEndPos);
				}
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsInsertEndLineNumberIndex()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CEditWithXDlg dlg;
	dlg.m_sXInput = _T("0");
	dlg.m_strDlgCaption = _T("Add suffix number for each line...");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_sXInput.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}
		int nIndex = AppUtils::CStringToInt(dlg.m_sXInput);
		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				CString strNewScripts;
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					strNewScripts += strLine + AppUtils::IntToCString(nIndex) + m_EditorCtrl.GetEOLCString();
					nIndex++;
				}
				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);

				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					int lLineEndPos = m_EditorCtrl.GetLineEndPosition(i);
					m_EditorCtrl.InsertText(AppUtils::IntToCString(nIndex), lLineEndPos);
					nIndex++;
				}
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsInsertLineNumberIndex()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CEditWithXDlg dlg;
	dlg.m_sXInput = _T("0");
	dlg.m_strDlgCaption = _T("Add prefix number for each line...");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_sXInput.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}
		int nIndex = AppUtils::CStringToInt(dlg.m_sXInput);
		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				CString strNewScripts;
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					strNewScripts += AppUtils::IntToCString(nIndex) + _T(" - ") + strLine + m_EditorCtrl.GetEOLCString();
					nIndex++;
				}
				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);

				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					int lLineStartPos = m_EditorCtrl.GetLineStartPosition(i);
					m_EditorCtrl.InsertText(AppUtils::IntToCString(nIndex) + _T(" - "), lLineStartPos);
					nIndex++;
				}
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsInsertLineAlphabetIndex()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CEditWithXDlg dlg;
	dlg.m_sXInput = _T("A");
	dlg.m_strDlgCaption = _T("Add prefix alphabet for each line...");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_sXInput.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}

		wchar_t nIndexChar = dlg.m_sXInput[0];
		if (dlg.m_sXInput.Trim().GetLength() != 1 || !isalpha(nIndexChar))
		{
			AfxMessageBox(_T("[Error] Input must be a single character aphabet!"));
			return;
		}

		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				CString strNewScripts;
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					strNewScripts += CString(static_cast<char>(nIndexChar)) + _T(" - ") + strLine + m_EditorCtrl.GetEOLCString();
					nIndexChar++;
				}
				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);

				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					int lLineStartPos = m_EditorCtrl.GetLineStartPosition(i);
					m_EditorCtrl.InsertText(CString(static_cast<char>(nIndexChar)) + _T(" - "), lLineStartPos);
					nIndexChar++;
				}
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsInsertLineRomanIndex()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CEditWithXDlg dlg;
	dlg.m_sXInput = _T("0");
	dlg.m_strDlgCaption = _T("Add prefix roman numerals for each line...");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_sXInput.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}
		int nIndex = AppUtils::CStringToInt(dlg.m_sXInput);
		if (nIndex > 3999 || nIndex < 1)
		{
			AfxMessageBox(_T("[Error] Input is limited from 1 to 3999!"));
			return;
		}

		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				CString strNewScripts;
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					strNewScripts += AppUtils::DecimalToRomanNumerals(nIndex) + _T(" - ") + strLine + m_EditorCtrl.GetEOLCString();
					nIndex++;
				}
				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);

				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					int lLineStartPos = m_EditorCtrl.GetLineStartPosition(i);
					m_EditorCtrl.InsertText(AppUtils::DecimalToRomanNumerals(nIndex) + _T(" - "), lLineStartPos);
					nIndex++;
				}
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsSplitLineWithDelimiter()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CEditWithXDlg dlg;
	dlg.m_sXInput =CSTRING_SPACE;
	dlg.m_strDlgCaption = _T("Split Line With Delimiter");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_sXInput.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}
		int lCurPos = m_EditorCtrl.GetCurrentPosition();
		int lCurLine = m_EditorCtrl.GetLineFromPosition(lCurPos);
		CString strCurLineText;
		m_EditorCtrl.GetTextFromLine(lCurLine + 1, strCurLineText);
		CStringArray arrLine;
		CString strNewText;
		CString strDelimilter = dlg.m_sXInput;
		AppUtils::SplitCString(strCurLineText, strDelimilter, arrLine);
		for (int i = 0; i < arrLine.GetSize(); ++i)
		{
			if (arrLine[i].IsEmpty()) continue;
			strNewText += arrLine[i] + m_EditorCtrl.GetEOLCString();
		}
		if (strNewText.IsEmpty()) return;
		m_EditorCtrl.ReplaceLine(lCurLine, strNewText);
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsJoinLineWithDelimiter()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CEditWithXDlg dlg;
	dlg.m_sXInput =CSTRING_SPACE;
	dlg.m_strDlgCaption = _T("Join Line With Delimiter");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_sXInput.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}
		CString strDelimilter = dlg.m_sXInput;
		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				CString strNewScripts;
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					CString strTemp = strLine;
					if (strTemp.Trim().IsEmpty()) continue;
					strNewScripts += strLine + strDelimilter;
				}
				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
				int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
				int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);
				CString strJoinedLine;
				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					strCurLineText.Replace(_T("\n"), _T(""));
					CString strTemp = strCurLineText;
					if (strTemp.Trim().IsEmpty()) continue;
					strJoinedLine += strCurLineText + strDelimilter;
				}
				m_EditorCtrl.SetStartSelection(StartLinePos);
				m_EditorCtrl.SetEndSelection(EndLinePos);
				m_EditorCtrl.ReplaceSelectionWithText(strJoinedLine);
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::SortLineByOptions(SORT_LINE_OPT sortOptions)
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	auto fSortLines = [&](std::vector<CString>& vecLine) -> void {
		if (sortOptions == SORT_LINE_OPT::ASCENDING)
		{
			std::sort(vecLine.begin(), vecLine.end(), CompareCStringAscending());
		}
		else if (sortOptions == SORT_LINE_OPT::DESCENDING)
		{
			std::sort(vecLine.begin(), vecLine.end(), CompareCStringDescending());
		}
		else if (sortOptions == SORT_LINE_OPT::FROMATOZ)
		{
			std::sort(vecLine.begin(), vecLine.end(), CompareCStringAlphabetAZ());
		}
		else if (sortOptions == SORT_LINE_OPT::FROMZTOA)
		{
			std::sort(vecLine.begin(), vecLine.end(), CompareCStringAlphabetZA());
		}
	};

	CString stScript;
	m_EditorCtrl.GetText(stScript);
	if (!stScript.IsEmpty())
	{
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		if (stSelectedScript.IsEmpty())
		{
			std::wstring line;
			std::wistringstream iss(AppUtils::CStringToWStd(stScript));

			std::vector<CString> vecLine;
			while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
			{
				CString strLine = AppUtils::WStdToCString(line);
				strLine.Replace(_T("\n"), _T(""));
				vecLine.push_back(strLine);
			}

			fSortLines(vecLine);
			CString strNewScripts;
			for (const auto& line : vecLine)
			{
				strNewScripts += line + m_EditorCtrl.GetEOLCString();
			}
			m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
		}
		else
		{
			int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
			int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
			int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
			int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
			int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
			int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

			std::vector<CString> vecLine;
			for (int i = lLineStart; i <= lLineEnd; ++i)
			{
				CString strCurLineText;
				m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
				CString strTemp = strCurLineText;
				if (strTemp.Trim().IsEmpty()) continue;
				vecLine.push_back(strCurLineText);
			}

			fSortLines(vecLine);
			CString strNewScripts;
			for (const auto& line : vecLine)
			{
				strNewScripts += line + m_EditorCtrl.GetEOLCString();
			}
			m_EditorCtrl.SetStartSelection(StartLinePos);
			m_EditorCtrl.SetEndSelection(EndLinePos);
			m_EditorCtrl.ReplaceSelectionWithText(strNewScripts);
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsSortLineAscending()
{
	SortLineByOptions(SORT_LINE_OPT::ASCENDING);
}

void CEditorView::OnOptionsSortLineDescending()
{
	SortLineByOptions(SORT_LINE_OPT::DESCENDING);
}

void CEditorView::OnOptionsSortLineAZ()
{
	SortLineByOptions(SORT_LINE_OPT::FROMATOZ);
}

void CEditorView::OnOptionsSortLineZA()
{
	SortLineByOptions(SORT_LINE_OPT::FROMZTOA);
}

void CEditorView::OnOptionsMoveSelectedLineUp()
{
	m_EditorCtrl.DoCommand(SCI_MOVESELECTEDLINESUP);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsMoveSelectedLineDown()
{
	m_EditorCtrl.DoCommand(SCI_MOVESELECTEDLINESDOWN);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsToUpperCase()
{
	m_EditorCtrl.DoCommand(SCI_UPPERCASE);
}

void CEditorView::OnOptionsToLowerCase()
{
	m_EditorCtrl.DoCommand(SCI_LOWERCASE);
}

void CEditorView::OnOptionsToReverseText()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stSelectedScript = m_EditorCtrl.GetSelectedText();
	if (!stSelectedScript.IsEmpty())
	{
		stSelectedScript.MakeReverse();
		m_EditorCtrl.ReplaceSelectionWithText(stSelectedScript);
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsToCamelCase()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stSelectedScript = m_EditorCtrl.GetSelectedText();
	if (!stSelectedScript.IsEmpty())
	{
		std::wstring strSTD = AppUtils::CStringToWStd(stSelectedScript);
		AppUtils::ToTitleCase(strSTD);
		m_EditorCtrl.ReplaceSelectionWithText(AppUtils::WStdToCString(strSTD));
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsToPascalCase()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
    CString stSelectedScript = m_EditorCtrl.GetSelectedText();
	if (!stSelectedScript.IsEmpty())
	{
		int nPos = AppUtils::FindFirstCharacterNotOf(stSelectedScript, _T(" \t"));
		if (nPos >= 0)
		{
			std::wstring strSTD = AppUtils::CStringToWStd(stSelectedScript);
			AppUtils::ToTitleCase(strSTD);
			std::wstring strTemp = strSTD.substr(nPos);
			AppUtils::ReplaceAllInWStdString(strTemp, L" ", L"");
			strSTD = strSTD.substr(0, nPos) + strTemp;
			m_EditorCtrl.ReplaceSelectionWithText(AppUtils::WStdToCString(strSTD));
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsToLowerSnakeCase()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stSelectedScript = m_EditorCtrl.GetSelectedText();
	if (!stSelectedScript.IsEmpty())
	{
		std::wstring strSTD = AppUtils::CStringToWStd(stSelectedScript);
		boost::to_lower(strSTD);
		AppUtils::ReplaceAllInWStdString(strSTD, L" ", L"_");
		m_EditorCtrl.ReplaceSelectionWithText(AppUtils::WStdToCString(strSTD));
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsToUpperSnakeCase()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stSelectedScript = m_EditorCtrl.GetSelectedText();
	if (!stSelectedScript.IsEmpty())
	{
		std::wstring strSTD = AppUtils::CStringToWStd(stSelectedScript);
		boost::to_upper(strSTD);
		AppUtils::ReplaceAllInWStdString(strSTD, L" ", L"_");
		m_EditorCtrl.ReplaceSelectionWithText(AppUtils::WStdToCString(strSTD));
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsToPascalSnakeCase()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
    CString stSelectedScript = m_EditorCtrl.GetSelectedText();
	if (!stSelectedScript.IsEmpty())
	{
		std::wstring strSTD = AppUtils::CStringToWStd(stSelectedScript);
		AppUtils::ToTitleCase(strSTD);
		AppUtils::ReplaceAllInWStdString(strSTD, L" ", L"_");
		m_EditorCtrl.ReplaceSelectionWithText(AppUtils::WStdToCString(strSTD));
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsToPascalKebabCase()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stSelectedScript = m_EditorCtrl.GetSelectedText();
	if (!stSelectedScript.IsEmpty())
	{
		std::wstring strSTD = AppUtils::CStringToWStd(stSelectedScript);
		AppUtils::ToTitleCase(strSTD);
		AppUtils::ReplaceAllInWStdString(strSTD, L" ", L"-");
		m_EditorCtrl.ReplaceSelectionWithText(AppUtils::WStdToCString(strSTD));
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsToLowerKebabCase()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stSelectedScript = m_EditorCtrl.GetSelectedText();
	if (!stSelectedScript.IsEmpty())
	{
		std::wstring strSTD = AppUtils::CStringToWStd(stSelectedScript);
		boost::to_lower(strSTD);
		AppUtils::ReplaceAllInWStdString(strSTD, L" ", L"-");
		m_EditorCtrl.ReplaceSelectionWithText(AppUtils::WStdToCString(strSTD));
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsToUpperKebabCase()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stSelectedScript = m_EditorCtrl.GetSelectedText();
	if (!stSelectedScript.IsEmpty())
	{
		std::wstring strSTD = AppUtils::CStringToWStd(stSelectedScript);
		boost::to_upper(strSTD);
		AppUtils::ReplaceAllInWStdString(strSTD, L" ", L"_");
		m_EditorCtrl.ReplaceSelectionWithText(AppUtils::WStdToCString(strSTD));
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsToTitleUpperCase()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stSelectedScript = m_EditorCtrl.GetSelectedText();
	if (!stSelectedScript.IsEmpty())
	{
		std::wstring strSTD = AppUtils::CStringToWStd(stSelectedScript);
		AppUtils::ToTitleCase(strSTD);
		m_EditorCtrl.ReplaceSelectionWithText(AppUtils::WStdToCString(strSTD));
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsToDotCase()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stSelectedScript = m_EditorCtrl.GetSelectedText();
	if (!stSelectedScript.IsEmpty())
	{
		std::wstring strSTD = AppUtils::CStringToWStd(stSelectedScript);
		AppUtils::ReplaceAllInWStdString(strSTD, L" ", L".");
		m_EditorCtrl.ReplaceSelectionWithText(AppUtils::WStdToCString(strSTD));
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsToSentenceCase()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stSelectedScript = m_EditorCtrl.GetSelectedText();
	if (!stSelectedScript.IsEmpty())
	{
		std::wstring strSTD = AppUtils::CStringToWStd(stSelectedScript);
		int nPos = AppUtils::FindFirstCharacterNotOf(stSelectedScript, _T(" \t"));
		if (nPos >= 0)
		{
			boost::to_lower(strSTD);
			std::wstring strFirstChar(1, strSTD[nPos]);
			boost::to_upper(strFirstChar);
			std::wstring strSentenceCase = strSTD.replace(nPos, 1, strFirstChar);
			m_EditorCtrl.ReplaceSelectionWithText(AppUtils::WStdToCString(strSentenceCase));
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsPascalCaseToSplitCase()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stSelectedScript = m_EditorCtrl.GetSelectedText();
	if (!stSelectedScript.IsEmpty())
	{
		std::wstring strSTD = AppUtils::CStringToWStd(stSelectedScript);
		std::wstring strNewString = VinaTextSearchEngine::replace_word_regex(strSTD.c_str(), L"(\\B[A-Z])", L" $1");
		m_EditorCtrl.ReplaceSelectionWithText(AppUtils::WStdToCString(strNewString));
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsEOLToCRLF()
{
	m_EditorCtrl.ConvertEOL(SC_EOL_CRLF);
}

void CEditorView::OnOptionsEOLToLF()
{
	m_EditorCtrl.ConvertEOL(SC_EOL_LF);
}

void CEditorView::OnOptionsEOLToCR()
{
	m_EditorCtrl.ConvertEOL(SC_EOL_CR);
}

void CEditorView::OnUpdateOptionsEOLToCRLF(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_EditorCtrl.DoCommand(SCI_GETEOLMODE) == SC_EOL_CRLF);
}

void CEditorView::OnUpdateOptionsEOLToLF(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_EditorCtrl.DoCommand(SCI_GETEOLMODE) == SC_EOL_LF);
}

void CEditorView::OnUpdateOptionsEOLToCR(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_EditorCtrl.DoCommand(SCI_GETEOLMODE) == SC_EOL_CR);
}

void CEditorView::OnOptionsSnakeCaseToSplitCase()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stSelectedScript = m_EditorCtrl.GetSelectedText();
	if (!stSelectedScript.IsEmpty())
	{
		std::wstring strSTD = AppUtils::CStringToWStd(stSelectedScript);
		AppUtils::ReplaceAllInWStdString(strSTD, L"_", L" ");
		m_EditorCtrl.ReplaceSelectionWithText(AppUtils::WStdToCString(strSTD));
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::TrimLine(int trimOption)
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stScript;
	m_EditorCtrl.GetText(stScript);
	if (!stScript.IsEmpty())
	{
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		if (stSelectedScript.IsEmpty())
		{
			CString strNewScripts;
			std::wstring line;
			std::wistringstream iss(AppUtils::CStringToWStd(stScript));
			while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
			{
				CString strLine = AppUtils::WStdToCString(line);
				strLine.Replace(_T("\n"), _T(""));
				if (trimOption == 1)
				{
					strNewScripts += strLine.Trim() + m_EditorCtrl.GetEOLCString();
				}
				else if (trimOption == 2)
				{
					strNewScripts += strLine.TrimLeft() + m_EditorCtrl.GetEOLCString();
				}
				else if (trimOption == 3)
				{
					strNewScripts += strLine.TrimRight() + m_EditorCtrl.GetEOLCString();
				}
			}
			m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
		}
		else
		{
			int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
			int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
			int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
			int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);

			for (int i = lLineStart; i <= lLineEnd; ++i)
			{
				CString strCurLineText;
				m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
				if (trimOption == 1)
				{
					m_EditorCtrl.ReplaceLine(i, strCurLineText.Trim());
				}
				else if (trimOption == 2)
				{
					m_EditorCtrl.ReplaceLine(i, strCurLineText.TrimLeft());
				}
				else if (trimOption == 3)
				{
					m_EditorCtrl.ReplaceLine(i, strCurLineText.TrimRight());
				}
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
	m_EditorCtrl.EnableDisplayWhiteSpace(TRUE);
}

void CEditorView::OnDocumentDisplayEOL()
{
	m_EditorCtrl.EnableShowEOL(!m_EditorCtrl.GetShowEOL());
}

void CEditorView::OnUpdateDocumentDisplayEOL(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_EditorCtrl.GetShowEOL());
}

void CEditorView::OnEditCountWords()
{
	int lCountWord = 0;
	CString stScript;
	m_EditorCtrl.GetText(stScript);
	CString strMsg;
	LOG_OUTPUT_MESSAGE_COLOR(_T("\n___________| COUNTER INFORMATION |________________________________________\n"));
	if (!stScript.IsEmpty())
	{
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		if (stSelectedScript.IsEmpty())
		{
			CStringArray arrLine;
			stSelectedScript.Replace(_T("\r"),CSTRING_SPACE);
			AppUtils::SplitCString(stScript,CSTRING_SPACE, arrLine);
			for (int i = 0; i < arrLine.GetSize(); ++i)
			{
				if (arrLine[i].Trim().IsEmpty()) continue;
				lCountWord++;
			}
			strMsg.Format(_T("> [Count statistics] Total %d word(s) saperated by space in current file.\n"), lCountWord);
			LOG_OUTPUT_MESSAGE_COLOR(strMsg);
		}
		else
		{
			CStringArray arrLine;
			stSelectedScript.Replace(_T("\r"),CSTRING_SPACE);
			AppUtils::SplitCString(stSelectedScript,CSTRING_SPACE, arrLine);
			for (int i = 0; i < arrLine.GetSize(); ++i)
			{
				if (arrLine[i].Trim().IsEmpty()) continue;
				lCountWord++;
			}
			strMsg.Format(_T("> [Count statistics] Total %d word(s) saperated by space in selection.\n"), lCountWord);
			LOG_OUTPUT_MESSAGE_COLOR(strMsg);
		}
	}
	if (strMsg.IsEmpty())
	{
		strMsg.Format(_T("> [Count statistics] Total 0 word(s) saperated by space in current file.\n"), lCountWord);
		LOG_OUTPUT_MESSAGE_COLOR(strMsg);
	}
	ActiveDockWindow(DOCKABLE_PANE_TYPE::LOG_MESSAGE_PANE);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnEditCountDuplicateWords()
{
	int lCountWord = 0;
	CString strMsg;
	CString stScript;
	m_EditorCtrl.GetText(stScript);
	LOG_OUTPUT_MESSAGE_COLOR(_T("\n___________| COUNTER INFORMATION |________________________________________\n"));
	if (!stScript.IsEmpty())
	{
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		if (stSelectedScript.IsEmpty())
		{
			std::wstringstream input(AppUtils::CStringToWStd(stScript));
			std::map<std::wstring, unsigned int> word_data;
			std::wstring word;
			while (input >> word)
			{
				if (word_data.find(word) != word_data.end())
				{
					word_data[word]++;
				}
				else
				{
					word_data[word] = 1;
				}
			}
			std::map<std::wstring, unsigned int>::iterator iter;
			for (iter = word_data.begin(); iter != word_data.end(); ++iter)
			{
				std::wstring strLine = iter->first + L" (" + std::to_wstring(iter->second) +  L")\n";
				strMsg += AppUtils::WStdToCString(strLine);
			}
			CString strStatistics;
			strStatistics.Format(_T("> [Count statistics] Total %d unique word(s) saperated by space in current file.\n\n"), static_cast<int>(word_data.size()));
			strMsg += strStatistics;
			LOG_OUTPUT_MESSAGE_COLOR(strMsg);

		}
		else
		{
			std::wstringstream input(AppUtils::CStringToWStd(stSelectedScript));
			std::map<std::wstring, unsigned int> word_data;
			std::wstring word;
			while (input >> word)
			{
				if (word_data.find(word) != word_data.end())
				{
					word_data[word]++;
				}
				else
				{
					word_data[word] = 1;
				}
			}
			std::map<std::wstring, unsigned int>::iterator iter;
			for (iter = word_data.begin(); iter != word_data.end(); ++iter)
			{
				std::wstring strLine = iter->first + L" (" + std::to_wstring(iter->second) + L")\n";
				strMsg += AppUtils::WStdToCString(strLine);
			}
			CString strStatistics;
			strStatistics.Format(_T("> [Count statistics] Total %d unique word(s) saperated by space in selection.\n"), static_cast<int>(word_data.size()));
			strMsg += strStatistics;
			LOG_OUTPUT_MESSAGE_COLOR(strMsg);
		}
	}
	if (strMsg.IsEmpty())
	{
		strMsg.Format(_T("> [Count statistics] Total 0 word(s) unique word(s) saperated by space in current file.\n\n"), lCountWord);
		LOG_OUTPUT_MESSAGE_COLOR(strMsg);
	}
	ActiveDockWindow(DOCKABLE_PANE_TYPE::LOG_MESSAGE_PANE);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnEditCountDuplicateLines()
{
	int lCountWord = 0;
	CString strMsg;
	CString stScript;
	m_EditorCtrl.GetText(stScript);
	LOG_OUTPUT_MESSAGE_COLOR(_T("\n___________| COUNTER INFORMATION |________________________________________\n"));
	if (!stScript.IsEmpty())
	{
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		if (stSelectedScript.IsEmpty())
		{
			std::wstringstream input(AppUtils::CStringToWStd(stScript));
			std::wstring line;
			typedef std::multimap<std::wstring, unsigned int> line_record;
			line_record lines;
			line_record duplicatelines;
			unsigned int line_number = 1;
			while (std::getline(input, line))
			{
				AppUtils::ReplaceAllInWStdString(line, L"\n", L"");
				AppUtils::ReplaceAllInWStdString(line, L"\r", L"");
				line_record::iterator existing = lines.find(line);
				if (existing == lines.end()) // if it was already in the map
				{
					lines.insert(std::make_pair(line, line_number)); // otherwise, add it to map
				}
				else
				{
					boost::algorithm::trim(line);
					if (!line.empty())
					{
						duplicatelines.insert(std::make_pair(line, line_number));
					}
				}
				++line_number;
			}
			std::map<std::wstring, unsigned int>::iterator iter;
			for (iter = duplicatelines.begin(); iter != duplicatelines.end(); ++iter)
			{
				std::wstring strLine = iter->first + L" , Line : " + std::to_wstring(iter->second) + L"\n";
				strMsg += AppUtils::WStdToCString(strLine);
			}
			CString strStatistics;
			strStatistics.Format(_T("> [Line statistics] Total %d duplicate line(s) in current file.\n\n"), static_cast<int>(duplicatelines.size()));
			strMsg += strStatistics;
			LOG_OUTPUT_MESSAGE_COLOR(strMsg);

		}
		else
		{
			std::wstringstream input(AppUtils::CStringToWStd(stSelectedScript));
			std::wstring line;
			typedef std::multimap<std::wstring, unsigned int> line_record;
			line_record lines;
			line_record duplicatelines;
			unsigned int line_number = 1;
			while (std::getline(input, line))
			{
				AppUtils::ReplaceAllInWStdString(line, L"\n", L"");
				AppUtils::ReplaceAllInWStdString(line, L"\r", L"");
				line_record::iterator existing = lines.find(line);
				if (existing == lines.end()) // if it was already in the map
				{
					lines.insert(std::make_pair(line, line_number)); // otherwise, add it to map
				}
				else
				{
					boost::algorithm::trim(line);
					if (!line.empty())
					{
						duplicatelines.insert(std::make_pair(line, line_number));
					}
				}
				++line_number;
			}
			std::map<std::wstring, unsigned int>::iterator iter;
			for (iter = duplicatelines.begin(); iter != duplicatelines.end(); ++iter)
			{
				std::wstring strLine = iter->first + L" , Line : " + std::to_wstring(iter->second) + L"\n";
				strMsg += AppUtils::WStdToCString(strLine);
			}
			CString strStatistics;
			strStatistics.Format(_T("> [Line statistics] Total %d duplicate line(s) in current file.\n"), static_cast<int>(duplicatelines.size()));
			strMsg += strStatistics;
			LOG_OUTPUT_MESSAGE_COLOR(strMsg);
		}
	}
	if (strMsg.IsEmpty())
	{
		strMsg.Format(_T("> [Line statistics] Total 0 duplicate line(s) in current file.\n"), lCountWord);
		LOG_OUTPUT_MESSAGE_COLOR(strMsg);
	}
	ActiveDockWindow(DOCKABLE_PANE_TYPE::LOG_MESSAGE_PANE);
	m_EditorCtrl.SetFocus();
}

void CEditorView::GetMatchedWordsOnFile(std::vector<CString>& listWord, const CString& inputChars)
{
	auto fIsWordExisted = [](const CString& word, const std::vector<CString>& listWord) -> BOOL
	{
		 for (size_t i = 0, len = listWord.size(); i < len; ++i)
		 {
			 if (listWord[i] == word) return TRUE;
		 }
		return FALSE;
	};

	if (AppSettingMgr.m_bAutoCompleteIgnoreNumbers && AppUtils::IsCStringAllDigits(inputChars)) return;

	CString strReExpress(TEXT("\\<"));
	strReExpress += inputChars;
	strReExpress += TEXT(EDITOR_REGEX_AUTO_COMPLETE_PATTERN);

	int docLength = m_EditorCtrl.GetTextLength();

	int searchFlags = SCFIND_WORDSTART | SCFIND_MATCHCASE | SCFIND_REGEXP | SCFIND_POSIX;

	if (AppSettingMgr.m_bAutoCompleteIgnoreCase)
	{
		searchFlags = SCFIND_WORDSTART | SCFIND_REGEXP | SCFIND_POSIX;
	}

	m_EditorCtrl.DoCommand(SCI_SETSEARCHFLAGS, searchFlags);
	int nPosFound = m_EditorCtrl.SearchTextInRange(strReExpress, 0, docLength);

	const size_t bufSize = 256;
	while (nPosFound != -1 && nPosFound != -2)
	{
		int wordStart = (int)m_EditorCtrl.DoCommand(SCI_GETTARGETSTART);
		int wordEnd = (int)m_EditorCtrl.DoCommand(SCI_GETTARGETEND);

		size_t foundTextLen = wordEnd - wordStart;
		if (foundTextLen < bufSize)
		{
			CString strTargetWord;
			m_EditorCtrl.GetTextRange(strTargetWord, wordStart, wordEnd);

			if (!fIsWordExisted(strTargetWord, listWord))
			{
				listWord.emplace_back(strTargetWord);
			}
		}
		nPosFound = m_EditorCtrl.SearchTextInRange(strReExpress, wordEnd, docLength);
	}
}

void CEditorView::GetAutoCompleteList(const CString& strWord, std::vector<CString>& listWord)
{
	if (strWord.IsEmpty()) return;
	for (auto const& onedataset : m_AutoCompelteDataset)
	{
		CString strCmp = onedataset.Mid(0, strWord.GetLength());
		if (strCmp.CompareNoCase(strWord) == 0)
		{
			listWord.emplace_back(onedataset);
		}
	}
	for (int i = 0; i < m_LangKeywordDataset.size(); ++i)
	{
		CString strCmp = m_LangKeywordDataset[i].Mid(0, strWord.GetLength());
		if (strCmp.CompareNoCase(strWord) == 0)
		{
			listWord.emplace_back(m_LangKeywordDataset[i]);
		}
	}
	GetMatchedWordsOnFile(listWord, strWord);
}

void CEditorView::RenderIndicatorWordsAndCount(const CString & strWord, int nSearchOption /*= SCFIND_WHOLEWORD | SCFIND_MATCHCASE*/, BOOL bClearSelection/*= TRUE*/)
{
	int nCurPosition = m_EditorCtrl.GetCurrentPosition();
	m_nIndicatorCount = 0;
	m_MatchedLineDataset.clear();
	m_EditorCtrl.RemoveIndicatorHightLightRenders();
	if (strWord.IsEmpty())
	{
		if (bClearSelection)
		{
			m_EditorCtrl.ClearSelection(nCurPosition);
		}
		GuiUtils::ForceRedrawCWnd(this);  // force tracking bar refresh...
		return;
	}
	m_EditorCtrl.SetIndicatorForHighlightWord();
	int startRange = 0;
	int endRange = m_EditorCtrl.GetTextLength();
	int targetStart = 0;
	int targetEnd = 0;
	m_EditorCtrl.DoCommand(SCI_SETSEARCHFLAGS, nSearchOption);
	while (targetStart != -1 && targetStart != -2)
	{
		targetStart = m_EditorCtrl.SearchTextInRange(strWord, startRange, endRange);

		if (targetStart == -1 || targetStart == -2)
		{
			break;
		}
		targetEnd = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETTARGETEND));

		if (targetEnd > endRange)
		{
			break;
		}

		int indicatorLength = targetEnd - targetStart;

		if (indicatorLength > 0)
		{
			m_nIndicatorCount++;
			if (targetEnd != nCurPosition)
				m_EditorCtrl.DoCommand(SCI_INDICATORFILLRANGE, targetStart, indicatorLength);
			if (AppSettingMgr.m_bShowTrackingBar)
			{
				m_MatchedLineDataset.insert(m_EditorCtrl.GetLineFromPosition(targetStart));
			}
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
	GuiUtils::ForceRedrawCWnd(this);  // force tracking bar refresh...
}

int CEditorView::SelectAllOccurrences(const CString & strWord, int nSearchOption /*= SCFIND_WHOLEWORD | SCFIND_MATCHCASE*/)
{
	m_nIndicatorCount = 0;
	m_MatchedLineDataset.clear();
	if (strWord.IsEmpty() || !m_EditorCtrl.GetMultiSelectionModeState()) return 0;
	int startRange = 0;
	int endRange = m_EditorCtrl.GetTextLength();
	int targetStart = 0;
	int targetEnd = 0;
	int targetCaretFirstFound = 0;
	int targetAnchorFirstFound = 0;
	int curCaret = m_EditorCtrl.GetCurrentPosition();
	int firstVisibleLine = m_EditorCtrl.GetFirstVisibleLine();
	m_EditorCtrl.DoCommand(SCI_SETSEARCHFLAGS, nSearchOption);
	while (targetStart != -1 && targetStart != -2)
	{
		targetStart = m_EditorCtrl.SearchTextInRange(strWord, startRange, endRange);

		if (targetStart == -1 || targetStart == -2)
		{
			break;
		}
		targetEnd = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETTARGETEND));

		if (targetEnd > endRange)
		{
			break;
		}

		int indicatorLength = targetEnd - targetStart;

		if (indicatorLength > 0)
		{
			m_nIndicatorCount++;
			if (AppSettingMgr.m_bShowTrackingBar)
			{
				m_MatchedLineDataset.insert(m_EditorCtrl.GetLineFromPosition(targetStart));
			}
			if (curCaret == targetEnd)
			{
				targetCaretFirstFound = targetStart + indicatorLength;
				targetAnchorFirstFound = targetStart;
			}
			else
			{
				m_EditorCtrl.DoCommand(SCI_ADDSELECTION, targetStart + indicatorLength, targetStart);
				m_EditorCtrl.RemoveEachIndicatorHightLight(targetStart, targetStart + indicatorLength);
			}
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
	if (targetAnchorFirstFound > 0)
	{
		m_EditorCtrl.DoCommand(SCI_ADDSELECTION, targetCaretFirstFound, targetAnchorFirstFound);
		m_EditorCtrl.RemoveEachIndicatorHightLight(targetAnchorFirstFound, targetCaretFirstFound);
	}
	else if (m_EditorCtrl.GetSelectionNumber() > m_nIndicatorCount)
	{
		m_EditorCtrl.DoCommand(SCI_DROPSELECTIONN, 0, 0);
	}
	GuiUtils::ForceRedrawCWnd(this);  // force tracking bar refresh...
	return m_nIndicatorCount;
}

int CEditorView::BookmarkAllOccurrences(const CString& strWord, int nSearchOption)
{
	int nCurPosition = m_EditorCtrl.GetCurrentPosition();
	int startRange = 0;
	int endRange = m_EditorCtrl.GetTextLength();
	int targetStart = 0;
	int targetEnd = 0;
	int bookmarkCount = 0;
	m_EditorCtrl.DoCommand(SCI_SETSEARCHFLAGS, nSearchOption);
	while (targetStart != -1 && targetStart != -2)
	{
		targetStart = m_EditorCtrl.SearchTextInRange(strWord, startRange, endRange);
		if (targetStart == -1 || targetStart == -2)
		{
			break;
		}
		targetEnd = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETTARGETEND));
		if (targetEnd > endRange)
		{
			break;
		}
		int indicatorLength = targetEnd - targetStart;
		if (indicatorLength > 0)
		{
			CString strPathName = m_pDocument->GetPathName();
			if (PathFileExists(strPathName))
			{
				const int line = m_EditorCtrl.GetLineFromPosition(targetStart) + 1;
				if (m_EditorCtrl.AddBookMark(line, strPathName))
				{
					UpdateDockPaneBookmark(line, FALSE, strPathName);
				}
				bookmarkCount++;
			}
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
	return bookmarkCount;
}

// CEditorView diagnostics

#ifdef _DEBUG
void CEditorView::AssertValid() const
{
	CViewBase::AssertValid();
}

void CEditorView::Dump(CDumpContext& dc) const
{
	CViewBase::Dump(dc);
}

CEditorDoc* CEditorView::GetEditorDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditorDoc)));
	return (CEditorDoc*)m_pDocument;
}
#endif //_DEBUG

CEditorView::CEditorView() {}

CLanguageDatabase * CEditorView::GetLanguageDatabase() const
{
	CEditorDoc *pDoc = GetEditorDocument();
	if (!pDoc) return NULL;
	CLanguageDatabase* pDatabase = pDoc->GetDocLanguageDatabase();
	if (!pDatabase) return NULL;
	return pDatabase;
}

void CEditorView::OnSize(UINT nType, int cx, int cy)
{
	CViewBase::OnSize(nType, cx, cy);
	if (m_EditorCtrl.GetSafeHwnd())
	{
		AdjustEditorPosition(cx, cy);
	}
	if (AppUtils::GetMainFrame()->GetQuickSearchDialog())
		AppUtils::GetMainFrame()->ResizeQuickSearchDialog();
}

void CEditorView::OnSetFocus(CWnd * pOldWnd)
{
	CViewBase::OnSetFocus(pOldWnd);
	m_EditorCtrl.SetFocus(); // get focus from view to editor...
	if (!m_bIsWatchFileProcessing)
	{
		WatchFileSystemState(); // when view is actived, check file status also...
	}
}

BOOL CEditorView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT * pResult)
{
	NMHDR *phDR;
	phDR = (NMHDR*)lParam;
	if (phDR != NULL && phDR->hwndFrom == m_EditorCtrl.m_hWnd)
	{
		SCNotification *pScinNotification = (SCNotification*)lParam;

		switch (phDR->code)
		{
		case SCN_PAINTED:
		{
			// update dynamic line number width
			m_EditorCtrl.SetDisplayLinenumbers(TRUE);
			// return previous state
			if (!m_bAlreadyRestoreState)
			{
				CString strEditorPathName = m_pDocument->GetPathName();
				if (AppSettingMgr.m_bKeepPreviousEditorState && PathFileExists(strEditorPathName))
				{
					RecentEditorInfo info = AppSettingMgr.GetRecentEditorCaretInfo(strEditorPathName);
					if (info._nWrapMode && !m_EditorCtrl.IsEditorInWrapMode())
					{
						m_EditorCtrl.EnableTextWrappingMode(TRUE);
					}
					if (m_bAlreadyRepainted)
					{
						m_EditorCtrl.SetFirstVisibleLine(info._nFirstVisibleLine);
						m_EditorCtrl.SetCurrentAnchor(info._nCurrentPosition);
						m_EditorCtrl.SetCurrentPosition(info._nCurrentPosition);
						m_bAlreadyRestoreState = TRUE;
					}
					m_bAlreadyRepainted = TRUE;
				}
			}
			break;
		}
		// this feature is for a future release because it affects mouse moving
		/*case SCN_DWELLSTART:
		{
			m_EditorCtrl.ShowHideFoldingMargin(pScinNotification->x);
			break;
		}
		case SCN_DWELLEND:
		{
			m_EditorCtrl.ShowHideFoldingMargin(pScinNotification->x);
			break;
		}*/
		case SCN_INDICATORCLICK:
			{
				LRESULT IndicatorBmp = m_EditorCtrl.DoCommand(SCI_INDICATORALLONFOR, pScinNotification->position);
				if (!(IndicatorBmp & (1 << INDIC_URL_HOTSPOT))) break; // only process url click...
				LRESULT startPos = m_EditorCtrl.DoCommand(SCI_INDICATORSTART, INDIC_URL_HOTSPOT, pScinNotification->position);
				LRESULT endPos = m_EditorCtrl.DoCommand(SCI_INDICATOREND, INDIC_URL_HOTSPOT, pScinNotification->position);
				if ((pScinNotification->position < startPos) || (pScinNotification->position > endPos)) break;
				::PostMessage(this->GetSafeHwnd(), WM_LBUTTONUP, 0, 0);
				m_EditorCtrl.DoCommand(SCI_SETSEL, pScinNotification->position, pScinNotification->position);
				CString strUrlLink;
				m_EditorCtrl.GetTextRange(strUrlLink, startPos, endPos);
				if (!strUrlLink.IsEmpty() && GetKeyState(VK_CONTROL) & 0x8000)
				{
					OSUtils::CreateProcessAsynchronous(TEXT("open"), strUrlLink, _T(""), _T(""), SW_MAXIMIZE);
				}
				else
				{
					LOG_OUTPUT_MESSAGE_COLOR(_T("> [Url Link] To open url link in web browser, use ctrl + left mouse click..."), BasicColors::orange);
				}
			}
			break;
		case SCN_SAVEPOINTLEFT:
		{
			m_pDocument->SetModifiedFlag(TRUE);
		}
		break;
		case SCN_SAVEPOINTREACHED:
		{
			m_pDocument->SetModifiedFlag(FALSE);
		}
		break;
		case SCN_CHARADDED:
		{
			//auto typingProfiler = OSUtils::StartBenchmark();
			if (m_EditorCtrl.IsReadOnlyEditor()) break;
			if (CHAR_ADDED_PROCESSOR(pScinNotification))
			{
				if (AppSettingMgr.m_bEnableAutoComplete && !m_bEnableLargeFileEditMode && (isalpha(pScinNotification->ch) || '_' == pScinNotification->ch))
				{
					CString strWord = m_EditorCtrl.GetRecentAddedText();
					if (!strWord.IsEmpty())
					{
						ShowAutoCompleteByAddedWord(strWord);
					}
				}
				if (AppSettingMgr.m_bEnableProcessIndentationTab && VK_RETURN == pScinNotification->ch && AppUtils::IsLanguageSupportLexer(m_CurrentDocLanguage) && !m_bEnableLargeFileEditMode)
				{
					ProcessIndentationTab();
				}
			}
			//OSUtils::LogStopBenchmark(LOG_TARGET::MESSAGE_WINDOW, typingProfiler, _T("> Benchmark charadded : "), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
		}
		break;
		case SCN_UPDATEUI: // the speed is most important for this event, so avoid wrapping function as much as possible...
		{
			//auto selectionProfiler = OSUtils::StartBenchmark();
			m_EditorCtrl.UpdateCaretLineVisible();
			m_EditorCtrl.DoBraceMatchHighlight();
			if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_XML ||
				m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_HTML ||
				m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PHP)
			{
				if (m_EditorCtrl.DoCommand(SCI_GETSELECTIONEMPTY, 0, 0))
				{
					m_EditorCtrl.DoXMLHTMLTagsHightlight();
				}
			}
			if (pScinNotification->updated == SC_UPDATE_SELECTION)
			{
				if (m_EditorCtrl.DoCommand(SCI_GETSELECTIONS) == SINGLE_SELECTION)
				{
					if (!m_strSelectedWord.IsEmpty())
					{
						ResetMultipleSelectionsBuffer();
					}
					if (CanResetHightlight())
					{
						// reset matched word highlights
						if (m_MatchedLineDataset.size() > 0)
						{
							m_MatchedLineDataset.clear();
							GuiUtils::ForceRedrawCWnd(this);  // force tracking bar refresh...
						}
						m_nIndicatorCount = 0;
						m_EditorCtrl.RemoveIndicatorHightLightRenders();

						// re-render matched words by single dragging selection if any
						if (!m_bEnableLargeFileEditMode)
						{
							if (AppSettingMgr.m_RenderIndicatorAction == RENDER_INDICATOR_ACTION::SINGLE_CLICK_ACTION)
							{
								CString strWordAroundCaret = m_EditorCtrl.GetWordFromPosition(m_EditorCtrl.GetCurrentPosition());
								if (!strWordAroundCaret.IsEmpty() && !m_EditorCtrl.IsTextSelected())
								{
									RenderIndicatorWordsAndCount(strWordAroundCaret);
								}
							}
							else
							{
								int nCurPosition = m_EditorCtrl.GetCurrentPosition();
								int nWordStart = static_cast<int>(m_EditorCtrl.DoCommand(SCI_WORDSTARTPOSITION, nCurPosition, true));
								int nWordEnd = static_cast<int>(m_EditorCtrl.DoCommand(SCI_WORDENDPOSITION, nWordStart, true));
								if (nWordStart != nWordEnd && nWordStart == m_EditorCtrl.GetSelectionStartPosition() && nWordEnd == m_EditorCtrl.GetSelectionEndPosition()) {
									CString strSelectedWord = m_EditorCtrl.GetSelectedText();
									RenderIndicatorWordsAndCount(strSelectedWord);
								}
							}
						}
					}
				}
			}
			if ((pScinNotification->updated & (SC_UPDATE_V_SCROLL | SC_UPDATE_H_SCROLL)) != 0)
			{
				if (m_bEnableSpellChecker)
				{
					KillTimer(START_SPELL_CHECKER_TIMER);
					SetTimer(START_SPELL_CHECKER_TIMER, SPELL_CHECKER_INTERVAL, NULL);
				}
				if (m_EditorCtrl.GetSelectionNumber() > SINGLE_SELECTION)
				{
					m_EditorCtrl.UpdateMainSelectionInCurrentView();
				}
			}
			//OSUtils::LogStopBenchmark(LOG_TARGET::MESSAGE_WINDOW, selectionProfiler, _T("> Benchmark selection : "), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
		}
		break;
		case SCN_MODIFIED:
		{
			//static int nModInsdelToken = -1;
			int const iModType = pScinNotification->modificationType;
			if ((iModType & SC_MULTISTEPUNDOREDO) && !(iModType & SC_LASTSTEPINUNDOREDO))
			{
				return TRUE;
			}
			if (iModType & (SC_MOD_BEFOREINSERT | SC_MOD_BEFOREDELETE))
			{
				/*if (!(iModType & (SC_PERFORMED_UNDO | SC_PERFORMED_REDO)))
				{
					if (!m_EditorCtrl.InUndoRedoTransaction() && (nModInsdelToken < 0))
					{
						BOOL const bIsSelEmpty = !m_EditorCtrl.IsSelectionEmpty();
						BOOL const bIsMultiRectSel = m_EditorCtrl.IsMultiOrRectangleSelection();
						if (bIsSelEmpty || bIsMultiRectSel)
						{
							int const token = m_EditorCtrl.SaveUndoMultiSelection();
							nModInsdelToken = (token >= 0) ? token : nModInsdelToken;
						}
						if (bIsSelEmpty && bIsMultiRectSel)
						{
							BOOL const bAddSelTyping = static_cast<BOOL>(m_EditorCtrl.DoCommand(SCI_GETADDITIONALSELECTIONTYPING));
							m_EditorCtrl.DoCommand(SCI_SETADDITIONALSELECTIONTYPING, bAddSelTyping);
						}
					}
				}*/
				if (iModType & SC_MOD_BEFOREDELETE)
				{
					int lcurPos = m_EditorCtrl.GetCurrentPosition();
					int nCurChar = m_EditorCtrl.GetCharacterAtPosition(lcurPos - 1);
					int nCharNext = m_EditorCtrl.GetCharacterAtPosition(lcurPos);
					if (nCurChar == '\"' && nCharNext == '\"' || nCurChar == '(' && nCharNext == ')' || nCurChar == '{' && nCharNext == '}' || nCurChar == '[' && nCharNext == ']')
					{
						if (m_bBackSpaceKeyDown)
						{
							m_bBackSpaceKeyDown = FALSE;
							m_EditorCtrl.PostMessageW(SCI_DELETERANGE, lcurPos - 1, 1);
						}
					}
				}
			}
			else if (iModType & (SC_MOD_INSERTTEXT | SC_MOD_DELETETEXT) && !TemporarySettings.m_bIsReloadByPreviewMode)
			{
				/*if (!(iModType & (SC_PERFORMED_UNDO | SC_PERFORMED_REDO)))
				{
					if (!m_EditorCtrl.InUndoRedoTransaction() && (nModInsdelToken >= 0))
					{
						m_EditorCtrl.SaveRedoMultiSelection(nModInsdelToken);
						nModInsdelToken = -1;
					}
				}*/
				CEditorDoc *pDoc = GetEditorDocument();
				if (pDoc->IsPreviewMode())
				{
					pDoc->SetPreviewMode(FALSE);
				}
				AppUtils::UpdateModifiedDocumentTitle(m_pDocument);
				m_EditorCtrl.DeleteAllBreakPoint();
				if (PathFileExists(pDoc->GetPathName()))
				{
					VinaTextDebugger.RemoveBreakPointDataInFile(pDoc->GetPathName());
				}

				if (!ThreadWorkerMgr.IsDebuggerRunning() && m_EditorCtrl.HasBreakPoints())
				{
					m_EditorCtrl.DeleteAllDebugPointer();
				}
			}
			// performance issue, will be improved soon...
			/*if (iModType & SC_MOD_CONTAINER) 
			{
				if (iModType & SC_PERFORMED_UNDO) 
				{
					m_EditorCtrl.RestoreMultiSelection(pScinNotification->token, TRUE);
				}
				else if (iModType & SC_PERFORMED_REDO)
				{
					m_EditorCtrl.RestoreMultiSelection(pScinNotification->token, FALSE);
				}
				AppUtils::UpdateModifiedDocumentTitle(m_pDocument);
			}*/
			if (m_bEnableSpellChecker && (iModType & (SC_MOD_DELETETEXT | SC_MOD_INSERTTEXT)) != 0)
			{
				KillTimer(START_SPELL_CHECKER_TIMER);
				SetTimer(START_SPELL_CHECKER_TIMER, SPELL_CHECKER_INTERVAL, NULL);
			}
		}
		break;
		case SCN_MARGINCLICK:
		{
			if (pScinNotification->margin == SC_SETMARGINTYPE_FOLDING)
			{
				m_EditorCtrl.DoToggleFolding(static_cast<int>(pScinNotification->position));
			}
			else if (pScinNotification->margin == SC_SETMARGINTYPE_MAKER)
			{
				int lLine = m_EditorCtrl.GetLineFromPosition(static_cast<int>(pScinNotification->position)) + 1;
				if (m_EditorCtrl.IsLineHasBookMark(lLine))
				{
					CString strPathName = m_pDocument->GetPathName();
					if (PathFileExists(strPathName))
					{
						if (m_EditorCtrl.DeleteBookMark(lLine, strPathName))
						{
							UpdateDockPaneBookmark(lLine, TRUE, strPathName);
						}
					}
				}
				else
				{
					CString strPathName = m_pDocument->GetPathName();
					if (PathFileExists(strPathName))
					{
						if (m_EditorCtrl.AddBookMark(lLine, strPathName))
						{
							UpdateDockPaneBookmark(lLine, FALSE, strPathName);
						}
					}
				}
			}
		}
		break;
		case SCN_DOUBLECLICK:
		{
			// clear annotations
			m_EditorCtrl.ClearAllAnnotationText();
			m_EditorCtrl.UpdateCaretLineVisible();
			if (CanResetHightlight() && m_EditorCtrl.DoCommand(SCI_GETSELECTIONS) == SINGLE_SELECTION)
			{
				if (AppSettingMgr.m_RenderIndicatorAction == RENDER_INDICATOR_ACTION::DOUBLE_CLICK_ACTION && !m_bEnableLargeFileEditMode)
				{
					RenderIndicatorWordsAndCount(m_EditorCtrl.GetSelectedText());
				}
			}
			// expand a folded line
			m_EditorCtrl.ExpandFoldedLine(m_EditorCtrl.GetCurrentPosition());
		}
		break;
		case SCN_AUTOCSELECTION:
		{
			int pos = (int)m_EditorCtrl.GetCurrentPosition();
			int startpos = (int)m_EditorCtrl.DoCommand(SCI_WORDSTARTPOSITION, pos - 1);
			int endpos = (int)m_EditorCtrl.DoCommand(SCI_WORDENDPOSITION, pos - 1);
			m_EditorCtrl.DoCommand(SCI_SETTARGETRANGE, startpos, endpos);
		}
		break;
		case SCN_ZOOM:
		{
			m_EditorCtrl.SetDisplayLinenumbers(TRUE);
		}
		break;
		}
		return TRUE;
	}
	return CViewBase::OnNotify(wParam, lParam, pResult);
}

void CEditorView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	WORD wMsgTarget = LOWORD(lHint);
	WORD wMsgHint = HIWORD(lHint);

	if (wMsgTarget == MSG_TARGET_UPDATE_ALL_VIEW)
	{
		switch (wMsgHint)
		{
			case VIEW_UPDATE_HINT::VIEW_UPDATE_HINT_SETTING_CHANGED:
				break;
			case VIEW_UPDATE_HINT::VIEW_UPDATE_HINT_EDITOR_DATABASE_CHANGED:
				break;
		}
	}
}

void CEditorView::AutoIndentationText() // IMPORTANT FUNCTION!!!
{
	m_nSpaceDelta = 0;
	m_nIndicatorPos = 0;
	m_bIsIndicatorChar = FALSE;
	m_bIsDeltaSpaceEnable = FALSE;

	CString stScript;
	m_EditorCtrl.GetText(stScript);
	if (stScript.IsEmpty()) return;
	int lcurLine = m_EditorCtrl.GetCurrentLine();
	int lendLinePos = m_EditorCtrl.GetLineEndPosition(lcurLine - 1);
	int lcurPos = m_EditorCtrl.GetCurrentPosition();
	int lStartLinePos = m_EditorCtrl.GetLineStartPosition(lcurLine - 1);
	int deltaSpace = lcurPos - lStartLinePos;

	CString strCurrentLine;
	m_EditorCtrl.GetTextFromLine(lcurLine, strCurrentLine);
	m_nIndicatorPos = AppUtils::FindFirstCharacterNotOf(strCurrentLine, _T(" \t"));
	if (strCurrentLine.GetAt(0) == _T('\t'))
	{
		m_nIndicatorPos = strCurrentLine.Replace(_T("\t"), _T("\t")) * 4; // change to tab!
	}
	CString strNextLine;
	m_EditorCtrl.GetTextFromLine(lcurLine + 1, strNextLine);
	int nNextIndicatorPos = AppUtils::FindFirstCharacterNotOf(strNextLine, _T(" \t"));

	if (nNextIndicatorPos == 0 && m_nIndicatorPos == -1)
	{
		m_strTab.Empty();
		return;
	}
	if (deltaSpace != m_nIndicatorPos)
	{
		m_nSpaceDelta = m_nIndicatorPos - deltaSpace;
		m_bIsDeltaSpaceEnable = TRUE;
	}
	else
	{
		m_bIsDeltaSpaceEnable = FALSE;
	}

	if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
	{
		int ncount1 = strCurrentLine.Replace(_T("def "), _T("def "));
		int ncount2 = strCurrentLine.Replace(_T("if "), _T("if "));
		int ncount3 = strCurrentLine.Replace(_T("for "), _T("for "));
		int ncount4 = strCurrentLine.Replace(_T("while "), _T("while "));
		int ncount5 = strCurrentLine.Replace(_T("class "), _T("class "));
		int ncount6 = strCurrentLine.Replace(_T(":"), _T(":"));
		int ncount7 = strCurrentLine.Replace(_T("()"), _T("()"));
		int ncount9 = strCurrentLine.Replace(_T("{}"), _T("{}"));
		int ncount11 = strCurrentLine.Replace(_T("[]"), _T("[]"));
		int ncount13 = strCurrentLine.Replace(_T("else "), _T("else "));
		int ncount14 = strCurrentLine.Replace(_T("elseif "), _T("elseif "));
		int ncount15 = strCurrentLine.Replace(_T("finally "), _T("finally "));
		int ncount16 = strCurrentLine.Replace(_T("try "), _T("try "));
		int ncount17 = strCurrentLine.Replace(_T("except "), _T("except "));

		int find1 = strCurrentLine.Find(_T("def "));
		int find2 = strCurrentLine.Find(_T("if "));
		int find3 = strCurrentLine.Find(_T("for "));
		int find4 = strCurrentLine.Find(_T("while "));
		int find5 = strCurrentLine.Find(_T("class "));
		int find6 = strCurrentLine.Find(_T(":"));
		int find13 = strCurrentLine.Find(_T("else "));
		int find14 = strCurrentLine.Find(_T("elseif "));
		int find15 = strCurrentLine.Find(_T("finally "));
		int find16 = strCurrentLine.Find(_T("try "));
		int find17 = strCurrentLine.Find(_T("except "));

		m_bIsIndicatorChar = FALSE;

		if ((ncount1 == 1 || ncount2 == 1 || ncount3 == 1 || ncount4 == 1 || ncount5 == 1
			|| ncount13 == 1 || ncount14 == 1 || ncount9 == 1 || ncount15 == 1 || ncount16 == 1 || ncount17 == 1)
			&& ncount6 == 1)
		{
			m_bIsIndicatorChar = TRUE;
		}

		if (find6 < deltaSpace && find6 != -1 && (find1 >= 0
			|| find2 >= 0 || find3 >= 0 || find4 >= 0 || find5 >= 0 || find13 >= 0 
			|| find14 >= 0 || find15 >= 0 || find16 >= 0 || find17 >= 0))
		{
			m_bIsIndicatorChar = TRUE;
		}
		else
		{
			m_bIsIndicatorChar = FALSE;
		}
	}
	else
	{
		int ncount1 = strCurrentLine.Replace(_T("()"), _T("()"));
		int ncount2 = strCurrentLine.Replace(_T("{}"), _T("{}"));
		int ncount3 = strCurrentLine.Replace(_T("[]"), _T("[]"));

		int find11 = strCurrentLine.Find(_T("("));
		int find12 = strCurrentLine.Find(_T(")"));
		int find21 = strCurrentLine.Find(_T("{"));
		int find22 = strCurrentLine.Find(_T("}"));
		int find31 = strCurrentLine.Find(_T("["));
		int find32 = strCurrentLine.Find(_T("]"));

		m_bIsIndicatorChar = FALSE;

		if (ncount1 == 1 || ncount2 == 1 || ncount3 == 1)
		{
			m_bIsIndicatorChar = TRUE;
		}

		if ((find11 < deltaSpace && deltaSpace <= find12)
			|| (find21 < deltaSpace && deltaSpace <= find22)
			|| (find31 < deltaSpace && deltaSpace <= find32))
		{
			m_bIsIndicatorChar = TRUE;
		}
		else
		{
			m_bIsIndicatorChar = FALSE;
		}
	}

	if (m_bIsIndicatorChar)
	{
		int pos = AppUtils::FindFirstCharacterNotOf(strCurrentLine, _T(" \t"));
		if (pos == -1) return;
		m_strTab = strCurrentLine.Mid(0, pos);
		if (m_EditorCtrl.GetTabSpace() == TabSpace::Tabs)
		{
			m_strTab += EDITOR_TAB;
		}
		else
		{
			if (AppSettingMgr.m_bUseUserIndentationSettings)
			{
				for (int i = 0; i < AppSettingMgr.m_nEditorIndentationWidth; ++i) {
					m_strTab += CSTRING_SPACE;
				}
			}
			else
			{
				m_strTab += EDITOR_TAB_4SPACE;
			}
		}
	}
	else
	{
		int pos1 = AppUtils::FindFirstCharacterNotOf(strCurrentLine, _T(" \t"));
		if (pos1 != -1)
		{
			m_strTab = strCurrentLine.Mid(0, pos1);
		}
	}
}

void CEditorView::ProcessIndentationTab()
{
	int lcurPos = m_EditorCtrl.GetCurrentPosition();
	if (m_bIsIndicatorChar)
	{
		CString strInicatorTab;
		for (int i = 0; i < m_nIndicatorPos; ++i)
		{
			strInicatorTab += CSTRING_SPACE;
		}
		if (m_EditorCtrl.GetTabSpace() == TabSpace::Tabs)
		{
			strInicatorTab.Replace(EDITOR_TAB_4SPACE, EDITOR_TAB);
		}
		if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
		{
			m_EditorCtrl.InsertText(m_strTab + strInicatorTab, lcurPos);
		}
		else
		{
			m_EditorCtrl.InsertText(m_strTab + m_EditorCtrl.GetEOLCString() + strInicatorTab, lcurPos);
		}
	}
	else
	{
		if (!m_bIsDeltaSpaceEnable)
		{
			m_EditorCtrl.InsertText(m_strTab, lcurPos);
		}
		else
		{
			for (int i = 0; i < m_nSpaceDelta; ++i)
			{
				AppUtils::ReplaceFirstOf(m_strTab, CSTRING_SPACE, _T(""));
			}
			m_EditorCtrl.InsertText(m_strTab, lcurPos);
		}
	}
	if (m_EditorCtrl.GetSelectionNumber() == SINGLE_SELECTION)
	{
		m_EditorCtrl.GotoPosition(lcurPos + m_strTab.GetLength());
	}
}

void CEditorView::ActiveDockWindow(DOCKABLE_PANE_TYPE type)
{
	AppUtils::GetMainFrame()->ActiveDockPane(type);
}

void CEditorView::ShowAutoCompleteByAddedWord(const CString& strWord)
{
	std::vector<CString> vecListword;
	GetAutoCompleteList(strWord, vecListword);
	if (vecListword.size() > 0)
	{
		CString strCompleteWords;
		strCompleteWords.Empty();
		for (int i = 0; i < vecListword.size(); ++i)
		{
			if (i != vecListword.size() - 1)
			{
				strCompleteWords.Append(vecListword[i] + _T("?0$"));
			}
			else
			{
				strCompleteWords.Append(vecListword[i] + _T("?0"));
			}
		}
		if (!strCompleteWords.IsEmpty())
		{
			char* bufUtf8 = NULL;
			int curPos = m_EditorCtrl.GetCurrentPosition();
			int startPos = m_EditorCtrl.GetWordStartPosition(curPos, true);
			CREATE_BUFFER_FROM_CSTRING(bufUtf8, strCompleteWords)
				m_EditorCtrl.DoCommand(SCI_AUTOCSHOW, curPos - startPos, sptr_t(bufUtf8));
			DELETE_POINTER_CPP_ARRAY(bufUtf8);
		}
	}
}

///// document menu //////////////////////////////////////////////////////////

void CEditorView::OnDocumentGoogleTranlate()
{
	CString strSelectedText = m_EditorCtrl.GetSelectedText();
	std::string strEncoded = CWebHandler::EncodeStringForCurl(AppUtils::CStringToStd(strSelectedText));
	CString strGoogleTranslatePrefix = GOOGLE_TRANSLATE_PREFIX_API;
	CString strGoogleTranslateSuffix = GOOGLE_TRANSLATE_SUFFIX_API;
	strGoogleTranslatePrefix += AppUtils::StdToCString(strEncoded) + strGoogleTranslateSuffix;
	OSUtils::CreateProcessAsynchronous(TEXT("open"), strGoogleTranslatePrefix, _T(""), _T(""), SW_MAXIMIZE);
}

CString CEditorView::TranlateText(CString strSelectedText, int nLineEnd)
{
	if (strSelectedText.IsEmpty())
	{
		strSelectedText = _T("[Translate Error] Text selection is empty.");
		m_EditorCtrl.SetLineCenterDisplay(nLineEnd);
		m_EditorCtrl.SetAnnotationText(strSelectedText, nLineEnd);
		return strSelectedText;
	}
	strSelectedText.MakeLower();
	std::string strEncoded = CWebHandler::EncodeStringForCurl(AppUtils::CStringToStd(strSelectedText));
	std::unique_ptr<CWebHandler> pWebHandler = std::make_unique<CWebHandler>();
	if (!pWebHandler)
	{
		strSelectedText = _T("[Translate Error] Translator module is not available...");
		m_EditorCtrl.SetLineCenterDisplay(nLineEnd);
		m_EditorCtrl.SetAnnotationText(strSelectedText, nLineEnd);
		return strSelectedText;
	}
	std::string strUrlRequest = pWebHandler->GetGoogleTranslateUrl(
		AppUtils::CStringToStd(AppSettingMgr.m_strLanguageTranslateFrom), 
		AppUtils::CStringToStd(AppSettingMgr.m_strLanguageTranslateTo)) + strEncoded;
	std::wstring strResult = pWebHandler->GetResultFromUrl(strUrlRequest, "");
	std::wstring strTranlatedText = pWebHandler->ResultParser(strResult);
	if (strTranlatedText.empty())
	{
		strSelectedText = _T("[Translate Error] Translated result is not available...");
		m_EditorCtrl.SetLineCenterDisplay(nLineEnd);
		m_EditorCtrl.SetAnnotationText(strSelectedText, nLineEnd);
		return strSelectedText;
	}

	if (m_EditorCtrl.GetEOLCString() == _T("\r\n"))
		AppUtils::ReplaceAllInWStdString(strTranlatedText, L"\\r\\n", L"\n");
	else
		AppUtils::ReplaceAllInWStdString(strTranlatedText, L"\\n", L"\n");
	AppUtils::ReplaceAllInWStdString(strTranlatedText, L"\"", L"");
	return AppUtils::WStdToCString(strTranlatedText); 
}

void CEditorView::OnDocumentTranlateText()
{
	CString strSelectedText = m_EditorCtrl.GetSelectedText();
	int lSelEnd = m_EditorCtrl.GetSelectionEndPosition();
	int lLineEnd = m_EditorCtrl.GetLineFromPosition(lSelEnd);
	CString strTranlatedTextCStr = TranlateText(strSelectedText, lLineEnd);
	m_EditorCtrl.SetLineCenterDisplay(lLineEnd);
	m_EditorCtrl.SetAnnotationText(strTranlatedTextCStr, lLineEnd);
}

void CEditorView::OnOptionsCopyTranslateResult()
{
	CString strSelectedText = m_EditorCtrl.GetSelectedText();
	int lSelEnd = m_EditorCtrl.GetSelectionEndPosition();
	int lLineEnd = m_EditorCtrl.GetLineFromPosition(lSelEnd);
	CString strTranlatedTextCStr = TranlateText(strSelectedText, lLineEnd);
	PushTextToClipBoard(strTranlatedTextCStr);
}

void CEditorView::OnOptionsGenerateTranslateResult()
{
	CString strSelectedText = m_EditorCtrl.GetSelectedText();
	int lSelEnd = m_EditorCtrl.GetSelectionEndPosition();
	int lLineEnd = m_EditorCtrl.GetLineFromPosition(lSelEnd);
	CString strTranlatedTextCStr = TranlateText(strSelectedText, lLineEnd);
	int lEndFilePos = m_EditorCtrl.GetTextLength();
	m_EditorCtrl.InsertText(_T("\r------ TRANSLATE RESULT -------------\r") + strTranlatedTextCStr, lEndFilePos);
}

void CEditorView::OnViewDisplayTabIndentation()
{
	m_EditorCtrl.EnableDisplayTabIndentation(!m_EditorCtrl.GetDisplayTabIndentation());
}

void CEditorView::OnUpdateDisplayTabIndentation(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_EditorCtrl.GetDisplayTabIndentation());
}

void CEditorView::OnDocumentShowSystemMenu()
{
	CString strPathName = m_pDocument->GetPathName();
	if (!PathFileExists(strPathName)) return;
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;
	pFrame->GetFileExplorerCtrl().ShowExplorerShellContextMenu(strPathName);
}

void CEditorView::OnDocumentSelectToSync()
{
	CEditorDoc *pDoc = GetEditorDocument();
	ASSERT(pDoc);
	if (!pDoc) return;
	//pDoc->AddView(this);
}

void CEditorView::OnDocumentExpandAllBrackets()
{
	m_EditorCtrl.ExpandAllFoldings();
}

void CEditorView::OnDocumentCollapseAllBrackets()
{
	m_EditorCtrl.CollapseAllFoldings();
}

void CEditorView::OnDocumentToggleCurrentBracket()
{
	m_EditorCtrl.ToggleCurrentFolding();
}

void CEditorView::ToggleBracketAslevel(int level)
{
	int nVisualLine = m_EditorCtrl.GetFirstVisibleLine();
	int curLevel = m_EditorCtrl.GetCurrentFolddingLevel();
	if (curLevel != level)
	{
		m_EditorCtrl.ExpandAllFoldings();
		m_EditorCtrl.FoldingWithLevel(level);
	}
	else
	{
		m_EditorCtrl.FoldingWithLevel(level);
	}
	m_EditorCtrl.SetFirstVisibleLine(nVisualLine);
}

void CEditorView::UpdatePreviewFileContent()
{
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;
	if (pFrame->GetQuickSearchDialog())
	{
		pFrame->CloseQuickSearchDialog();
	}
	OnInitialUpdate();
}

void CEditorView::OnDocumentToggleBracketlevel1()
{
	ToggleBracketAslevel(1);
}

void CEditorView::OnDocumentToggleBracketlevel2()
{
	ToggleBracketAslevel(2);
}

void CEditorView::OnDocumentToggleBracketlevel3()
{
	ToggleBracketAslevel(3);
}

void CEditorView::OnDocumentToggleBracketlevel4()
{
	ToggleBracketAslevel(4);
}

void CEditorView::OnDocumentToggleBracketlevel5()
{
	ToggleBracketAslevel(5);
}

void CEditorView::OnDocumentToggleBracketlevel6()
{
	ToggleBracketAslevel(6);
}

void CEditorView::OnDocumentToggleBracketlevel7()
{
	ToggleBracketAslevel(7);
}

void CEditorView::OnDocumentToggleBracketlevel8()
{
	ToggleBracketAslevel(8);
}

void CEditorView::OnDocumentToggleBracketlevel9()
{
	ToggleBracketAslevel(9);
}

void CEditorView::OnDocumentShowBracketsMap()
{
	BACKUP_VISIBLE_EDITOR_STATE
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;
	pFrame->UpdateFoldingMap();
	RESTORE_VISIBLE_EDITOR_STATE
}

void CEditorView::OnDocumentFormatFile()
{
	CEditorDoc *pDoc = GetEditorDocument();
	ASSERT(pDoc);
	if (!pDoc) return;

	CString strFilePath = pDoc->GetPathName();
	if (!PathFileExists(strFilePath))
	{
		CString strMsg;
		strMsg.Format(_T("[Path Error] \"%s\" does not exist...\n"), strFilePath);
		LOG_OUTPUT_MESSAGE_COLOR(strMsg, BasicColors::orange);
		return;
	}
	if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
		|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
		|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CSHAPE
		|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA
		|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT
		|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JSON)
	{
		//clang-format -i path/to/electron/file.c
		CString strFolderPath = AppSettingMgr.m_strNodeJSFolderPath;
		if (!PathFileExists(strFolderPath))
		{
			CString strMsg;
			strMsg.Format(_T("> [Path Error] \"%s\" does not exist, this file need NodeJS for formatting. Please be sure to install it on your computer...\n"), strFolderPath);
			LOG_OUTPUT_MESSAGE_COLOR(strMsg, BasicColors::orange);
			AfxMessageBox(strMsg);
			return;
		}
		SetCurrentDirectoryW(strFolderPath);
		CString strCommandLine = _T("\"clang-format -i \"") + strFilePath + _T("\"");
		_wsystem(AppUtils::CStringToWStd(strCommandLine).c_str());
		AfxMessageBox(_T("File formatted."), MB_ICONINFORMATION);
	}
	else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_HTML
		|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_XML)
	{
		//tiny XML support format xml syntax
		BOOL resultFormat = AppUtils::TinyXML2Format(strFilePath);
		if (resultFormat)
		{
			AfxMessageBox(_T("File XML/HTML formatted."), MB_ICONINFORMATION);
		}
		else
		{
			AfxMessageBox(_T("[Format Error] Formatting File XML/HTML failed."));
		}
	}
	else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
	{
		//autopep8 standard .\Lib\site-packages\bin\autopep8.exe -i\test.py
		CString strAutopep8Path = AppSettingMgr.m_strPythonFolderPath + _T("\\Lib\\site-packages\\bin\\autopep8.exe");
		if (!PathFileExists(strAutopep8Path))
		{
			CString strMsg;
			strMsg.Format(_T("> [Path Error] \"%s\" does not exist, this file need autopep8 for formatting. Please be sure to install it on your computer.\n"), strAutopep8Path);
			LOG_OUTPUT_MESSAGE_COLOR(strMsg, BasicColors::orange);
			AfxMessageBoxFormat(MB_ICONWARNING, _T("[Path Error]  \"%s\" does not exist, this file need autopep8 program for formatting. Please be sure to install it on your computer.\n"), strAutopep8Path);
			return;
		}
		SetCurrentDirectoryW(PathUtils::GetContainerPath(strAutopep8Path));
		CString strCommandLine = _T("\"autopep8.exe -i \"") + strFilePath + _T("\"");
		_wsystem(AppUtils::CStringToWStd(strCommandLine).c_str());
		AfxMessageBox(_T("File Python formatted."), MB_ICONINFORMATION);
	}
}

void CEditorView::OnUpdateDocumentFormatFile(CCmdUI * pCmdUI)
{
	CEditorDoc *pDoc = GetEditorDocument();
	ASSERT(pDoc);
	if (!pDoc) return;
	if (!m_EditorCtrl.IsReadOnlyEditor()
		&& (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
		|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
		|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CSHAPE
		|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA
		|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT
		|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JSON
		|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_HTML
		|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_XML
		|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CEditorView::AdjustEditorPosition(int cx, int cy)
{
	if (AppSettingMgr.m_bShowTrackingBar)
	{
		m_EditorCtrl.MoveWindow(0, 0, cx - TRACKING_BAR_LEFT_POSITION, cy);
	}
	else
	{
		m_EditorCtrl.MoveWindow(0, 0, cx, cy);
	}
}

void CEditorView::ReupdateTrackingBar()
{
	CRect rect;
	GetClientRect(&rect);
	AdjustEditorPosition(rect.Width(), rect.Height());
	if (AppSettingMgr.m_bShowTrackingBar) // re-update hightlighs
	{
		if (CanResetHightlight() && m_EditorCtrl.GetSelectionNumber() == SINGLE_SELECTION && !m_bEnableLargeFileEditMode)
		{
			RenderIndicatorWordsAndCount(m_EditorCtrl.GetSelectedText());
		}
	}
	if (AppUtils::GetMainFrame()->GetQuickSearchDialog())
		AppUtils::GetMainFrame()->ResizeQuickSearchDialog();
}

void CEditorView::OnDocumentShowTrackingBar()
{
	TOGGLE_FLAG(AppSettingMgr.m_bShowTrackingBar);
	ReupdateTrackingBar();
}

void CEditorView::OnUpdateDocumentShowTrackingBar(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(AppSettingMgr.m_bShowTrackingBar);
}

void CEditorView::OnDocumentSetReadOnly()
{
	if (ThreadWorkerMgr.IsRunning() || ThreadWorkerMgr.IsDebuggerRunning()) return;
	m_EditorCtrl.SetReadOnlyEditor(!m_EditorCtrl.IsReadOnlyEditor());
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;
	pFrame->PostMessage(WM_COMMAND, (WPARAM)UMW_SET_READ_ONLY_TAB_MDI);
	pFrame->PostMessage(WM_COMMAND, (WPARAM)UMW_SET_COLOR_ACTIVE_TAB_MDI);
}

void CEditorView::OnUpdateDocumentSetReadOnly(CCmdUI * pCmdUI)
{
	CEditorDoc *pDoc = GetEditorDocument();
	ASSERT(pDoc);
	if (!pDoc) return;
	BOOL bReadOnly = m_EditorCtrl.IsReadOnlyEditor();
	pCmdUI->SetCheck(bReadOnly);
}

void CEditorView::OnDocumentSetLargeFileEditMode()
{
	TOGGLE_FLAG(m_bEnableLargeFileEditMode);
	if (m_bEnableLargeFileEditMode)
	{
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Large File Edit] To boost up editor performance, following features will be disabled [auto complete, auto tab indentation, render duplicate word]..."), BasicColors::orange);
	}
	else
	{
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Large File Edit] return normal mode..."), BasicColors::orange);
	}
}

void CEditorView::OnUpdateDocumentSetLargeFileEditMode(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_bEnableLargeFileEditMode);
	pCmdUI->Enable(PathFileExists(m_pDocument->GetPathName()));
}

void CEditorView::OnDocumentHideLines()
{
	int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
	int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
	int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
	int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
	m_EditorCtrl.HideLines(lLineStart, lLineEnd);
}

void CEditorView::OnDocumentDisplayWhiteSpace()
{
	m_EditorCtrl.EnableDisplayWhiteSpace(!m_EditorCtrl.GetDisplayWhiteSpace());
}

void CEditorView::OnUpdateDocumentDisplayWhiteSpace(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_EditorCtrl.GetDisplayWhiteSpace());
}

void CEditorView::OnDocumentGoogleIt()
{
	CString strTargetSearch = m_EditorCtrl.GetSelectedText();
	std::string strEncoded = CWebHandler::EncodeStringForCurl(AppUtils::CStringToStd(strTargetSearch));
	CString strGoogleInstance = GOOGLE_SEARCH_API;
	strGoogleInstance += AppUtils::StdToCString(strEncoded);
	OSUtils::CreateProcessAsynchronous(TEXT("open"), strGoogleInstance, _T(""), _T(""), SW_MAXIMIZE);
}

void CEditorView::OnDocumentGoogleStackoverflow()
{
	CString strTargetSearch = m_EditorCtrl.GetSelectedText();
	std::string strEncoded = CWebHandler::EncodeStringForCurl(AppUtils::CStringToStd(strTargetSearch));
	CString strGoogleInstance = GOOGLE_SEARCH_API;
	strGoogleInstance += AppUtils::StdToCString(strEncoded) + STACKOVERFLOW_API;
	OSUtils::CreateProcessAsynchronous(TEXT("open"), strGoogleInstance, _T(""), _T(""), SW_MAXIMIZE);
}

void CEditorView::OnDocumentWikiIt()
{
	CString strTargetSearch = m_EditorCtrl.GetSelectedText();
	std::string strEncoded = CWebHandler::EncodeStringForCurl(AppUtils::CStringToStd(strTargetSearch));
	CString strGoogleInstance = WIKIPEDIA_SEARCH_API;
	strGoogleInstance += AppUtils::StdToCString(strEncoded);
	OSUtils::CreateProcessAsynchronous(TEXT("open"), strGoogleInstance, _T(""), _T(""), SW_MAXIMIZE);
}

///// compiler for languages ////////////////////////////////////////////////////////////

void CEditorView::OnExecutePython()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON);
}

void CEditorView::OnExecuteHTML()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_HTML);
}

void CEditorView::OnExecuteCPP()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP);
}

void CEditorView::OnExecuteJava()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA);
}

void CEditorView::OnExecuteJavaScript()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT);
}

void CEditorView::OnExecutePascal()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL);
}

void CEditorView::OnExecuteCShape()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CSHAPE);
}

void CEditorView::OnExecuteC()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C);
}

void CEditorView::OnExecuteAssembly()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_ASSEMBLY);
}

void CEditorView::OnExecutePHP()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PHP);
}

void CEditorView::OnExecutePerl()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PERL);
}

void CEditorView::OnExecuteGo()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_GOLANG);
}

void CEditorView::OnExecuteVisualBasic()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VISUALBASIC);
}

void CEditorView::OnExecuteSQL()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_SQL);
}

void CEditorView::OnExecuteTCL()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_TCL);
}

void CEditorView::OnExecuteAutoIT()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_AUTOIT);
}

void CEditorView::OnExecuteRust()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUST);
}

void CEditorView::OnExecuteR()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_R);
}

void CEditorView::OnExecuteBatch()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_BATCH);
}

void CEditorView::OnExecutePowerShell()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_POWERSHELL);
}

void CEditorView::OnExecuteVerilog()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VERILOG);
}

void CEditorView::OnExecuteRuby()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUBY);
}

void CEditorView::OnExecuteFreeBasic()
{
	START_VINATEXT_COMPILER(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_FREEBASIC);
}

void CEditorView::OnStartDebugger()
{
	if (!ThreadWorkerMgr.IsRunning())
	{
		if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP)
		{
			OnExecuteCPP();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C)
		{
			OnExecuteC();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_ASSEMBLY)
		{
			OnExecuteAssembly();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_BATCH)
		{
			OnExecuteBatch();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CSHAPE)
		{
			OnExecuteCShape();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
		{
			OnExecuteJava();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
		{
			OnExecuteJavaScript();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
		{
			OnExecutePascal();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
		{
			OnExecutePython();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PHP)
		{
			OnExecutePHP();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_SQL)
		{
			OnExecuteSQL();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VISUALBASIC)
		{
			OnExecuteVisualBasic();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PERL)
		{
			OnExecutePerl();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_GOLANG)
		{
			OnExecuteGo();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUST)
		{
			OnExecuteRust();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUBY)
		{
			OnExecuteRuby();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_TCL)
		{
			OnExecuteTCL();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_AUTOIT)
		{
			OnExecuteAutoIT();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VERILOG)
		{
			OnExecuteVerilog();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_POWERSHELL)
		{
			OnExecutePowerShell();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_HTML)
		{
			OnExecuteHTML();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_R)
		{
			OnExecuteR();
		}
		else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_FREEBASIC)
		{
			OnExecuteFreeBasic();
		}
		else
		{
			CMainFrame* pFrame = AppUtils::GetMainFrame();
			if (!pFrame) return;
			pFrame->ClearDataOnDockPane(DOCKABLE_PANE_TYPE::BUILD_PANE);
			OnTerminalRunActiveFile();
			return;
		}
	}
	else if (ThreadWorkerMgr.GetCurrentTask().processType == CEditorThreadCompiler::PROCESS_TYPE::DEBUGGING_TYPE)
	{
		VinaTextDebugger.Continue();
	}
	else
	{
		AfxMessageBoxFormat(MB_ICONINFORMATION, _T("Your program was already running!"));
	}
}

void CEditorView::OnUpdateStartDebugger(CCmdUI * pCmdUI)
{
	if (PathFileExists(m_pDocument->GetPathName()) && (!ThreadWorkerMgr.IsRunning() || ThreadWorkerMgr.IsDebuggerRunning()))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CEditorView::OnUpdateReStartDebugger(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(ThreadWorkerMgr.IsDebuggerRunning());
}

void CEditorView::OnStopDebugger()
{
	if (ThreadWorkerMgr.IsRunning())
	{
		ThreadWorkerMgr.StopThreadWorker();
	}
}

void CEditorView::OnUpdateStopDebugger(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(ThreadWorkerMgr.IsRunning());
}

void CEditorView::OnShowCallStack()
{
	VinaTextDebugger.ShowCallStack();
}

void CEditorView::OnRestartDebugger()
{
	VinaTextDebugger.Restart();
}

void CEditorView::OnStepOver()
{
	VinaTextDebugger.StepOver();
}

void CEditorView::OnStepInto()
{
	VinaTextDebugger.StepInto();
}

void CEditorView::OnStepOut()
{
	VinaTextDebugger.StepOut();
}

void CEditorView::OnWatchVariableValue()
{
	CString stSelectedVariable = m_EditorCtrl.GetSelectedText();
	if (!stSelectedVariable.IsEmpty())
	{
		VinaTextDebugger.WatchVariableValue(stSelectedVariable);
	}
}

void CEditorView::OnWatchVariableType()
{
	CString stSelectedVariable = m_EditorCtrl.GetSelectedText();
	if (!stSelectedVariable.IsEmpty())
	{
		VinaTextDebugger.WatchVariableType(stSelectedVariable);
	}
}

void CEditorView::OnUpdateShowCallStack(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(ThreadWorkerMgr.IsDebuggerRunning());
}

void CEditorView::OnUpdateStepInto(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(ThreadWorkerMgr.IsDebuggerRunning());
}

void CEditorView::OnUpdateStepOver(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(ThreadWorkerMgr.IsDebuggerRunning());
}

void CEditorView::OnUpdateStepOut(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(ThreadWorkerMgr.IsDebuggerRunning());
}

void CEditorView::OnUpdateWatchVariableValue(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(ThreadWorkerMgr.IsDebuggerRunning() && m_EditorCtrl.IsTextSelected());
}

void CEditorView::OnUpdateWatchVariableType(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(ThreadWorkerMgr.IsDebuggerRunning() && m_EditorCtrl.IsTextSelected());
}

void CEditorView::OnShowBuildErrors()
{
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (pFrame)
	{
		pFrame->ShowErrorLineOnEditor();
	}
}

void CEditorView::OnGenerateBuildFile()
{
	if (m_CurrentDocLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
		&& m_CurrentDocLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP)
	{
		AfxMessageBox(_T("This feature support C and C++ programming language only!"), MB_ICONINFORMATION);
		return;
	}
	CEditorDoc *pDoc = GetEditorDocument();
	if (!pDoc) return;
	CString strPathName = pDoc->GetPathName();
	if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP)
	{
		if (VinaTextCompiler::GenerateFileBuildConfigCPP(strPathName))
		{
			AfxMessageBox(_T("Generate C++ build configuration file suceeed."), MB_ICONINFORMATION);
		}
		else
		{
			AfxMessageBox(_T("[Error] Generate C++ build configuration file failed!"));
		}
	}
	else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C)
	{
		if (VinaTextCompiler::GenerateFileBuildConfigC(strPathName))
		{
			AfxMessageBox(_T("Generate C build configuration file suceeed."), MB_ICONINFORMATION);
		}
		else
		{
			AfxMessageBox(_T("[Error] Generate C build configuration file failed!"));
		}
	}
	/*else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
	{
	if (VinaTextCompiler::GenerateFileBuildConfigCPP(strPathName))
	{
	AfxMessageBox(_T("Generate Java build configuration file suceeed."), MB_ICONINFORMATION);
	}
	else
	{
	AfxMessageBox(_T("[Error] Generate Java build configuration file failed!"));
	}
	}
	else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CSHAPE)
	{
	if (VinaTextCompiler::GenerateFileBuildConfigCPP(strPathName))
	{
	AfxMessageBox(_T("Generate C# build configuration file suceeed."), MB_ICONINFORMATION);
	}
	else
	{
	AfxMessageBox(_T("[Error] Generate C# build configuration file failed!"));
	}
	}*/
}

void CEditorView::OnUpdateShowBuildErrors(CCmdUI * pCmdUI)
{
	if (!ThreadWorkerMgr.IsRunning() && PathFileExists(m_pDocument->GetPathName())
		&& AppUtils::IsLanguageSupportErrorAnnotation(m_CurrentDocLanguage))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CEditorView::OnUpdateGenerateBuildFile(CCmdUI * pCmdUI)
{
	BOOL bCheck = TRUE;
	if (m_CurrentDocLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
		&& m_CurrentDocLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP)
	{
		bCheck = FALSE;
	}
	if (!ThreadWorkerMgr.IsRunning() && bCheck)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CEditorView::RunExeAfterCompile()
{
	if (PathFileExists(m_BuildSessionInfo._strExeFilePath) && PathFileExists(m_BuildSessionInfo._strExeFolderPath))
	{
		if (AppSettingMgr.m_bOpenWindowCmdWhenRunProgram)
		{
			START_VINATEXT_START_EXE_CMD(m_BuildSessionInfo);
		}
		else
		{
			START_VINATEXT_START_EXE_LOADER(m_CurrentDocLanguage)
		}
	}
	else
	{
		CString strMsg;
		strMsg.Format(_T("[Path Error] \"%s\" does not exist!\n"), m_BuildSessionInfo._strExeFilePath);
		LOG_BUILD_MESSAGE_COLOR(strMsg, BasicColors::orange);
		return;
	}
}

void CEditorView::RunGDBDebuggerAfterCompile()
{
	if (PathFileExists(m_BuildSessionInfo._strExeFilePath) && PathFileExists(m_BuildSessionInfo._strExeFolderPath))
	{
		if (AppSettingMgr.m_bOpenWindowCmdWhenRunProgram)
		{
			START_VINATEXT_GDB_CMD(m_CurrentDocLanguage);
		}
		else
		{
			START_VINATEXT_GDB_DEBUGGER(m_CurrentDocLanguage);
		}
	}
	else
	{
		CString strMsg;
		strMsg.Format(_T("[Path Error] \"%s\" does not exist!\n"), m_BuildSessionInfo._strExeFilePath);
		LOG_BUILD_MESSAGE_COLOR(strMsg, BasicColors::orange);
		return;
	}
}

void CEditorView::RunJavaDebuggerAfterCompile()
{
}

void CEditorView::RunJavaExeAfterCompile(const CString& strCommandLine)
{
	if (PathFileExists(m_BuildSessionInfo._strExeFilePath) && PathFileExists(m_BuildSessionInfo._strExeFolderPath))
	{
		m_BuildSessionInfo._strExeFilePath.Replace(_T(".class"), _T(""));
		if (AppSettingMgr.m_bOpenWindowCmdWhenRunProgram)
		{
			START_VINATEXT_START_EXE_CMD(m_BuildSessionInfo);
		}
		else
		{
			START_VINATEXT_START_JAVA_LOADER(m_CurrentDocLanguage, strCommandLine);
		}
	}
	else
	{
		CString strMsg;
		strMsg.Format(_T("[Path Error] \"%s\" does not exist!\nPlease check class name and file name are matched or not..."), m_BuildSessionInfo._strExeFilePath);
		LOG_BUILD_MESSAGE_COLOR(strMsg, BasicColors::orange);
		return;
	}
}

LRESULT CEditorView::OnCompilerNotifyProgress(WPARAM wParam, LPARAM lParam)
{
	DWORD dwPos = (DWORD)lParam;

	if (!m_pBuildProgressBar)
	{
		m_pBuildProgressBar = std::make_unique<CVinaTextProgressBar>(0, 100, _T("VinaText Status Bar..."));
	}

	if (m_pBuildProgressBar)
	{
		m_pBuildProgressBar->SetText((LPCTSTR)wParam);
		m_pBuildProgressBar->SetPos(dwPos);
	}

	return 0L;
}

LRESULT CEditorView::OnCompilerNotifyBuildExitCode(WPARAM wParam, LPARAM lParam)
{
	if (m_pBuildProgressBar)
	{
		m_pBuildProgressBar.reset();
	}

	CEditorThreadCompiler::THREAD_STATUS threadStatus = (CEditorThreadCompiler::THREAD_STATUS)wParam;
	DWORD nExitCode = (DWORD)lParam;
	if (threadStatus == CEditorThreadCompiler::THREAD_STATUS::THREAD_STATUS_FINISHED)
	{
		if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON
			|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT
			|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PERL
			|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_GOLANG
			|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PHP)
		{						   
			LOG_BUILD_MESSAGE_COLOR(_T("\n.................................................................................... END ]\n"));
		}

		OSUtils::LogStopBenchmark(LOG_TARGET::BUILD_WINDOW, m_BuildSessionInfo._BuildMeasureTime, _T("[Message] Build process finished after : "), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);

		m_BuildSessionInfo._BuildMeasureTime = 0;
		if (nExitCode == 0)
		{
			if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
				|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
				|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL
				|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CSHAPE
				|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUST
				|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_ASSEMBLY
				|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VISUALBASIC
				|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_FREEBASIC)
			{
				LOG_BUILD_MESSAGE_COLOR(_T("[Message] Build process succeed..."), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
				LOG_BUILD_MESSAGE_COLOR(_T("[Message] Initialize loader for execution..."), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
				LOG_BUILD_MESSAGE_COLOR(_T("[ RUN .................................................................................."));
				m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
				RunExeAfterCompile();
			}
			else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
			{
				LOG_BUILD_MESSAGE_COLOR(_T("[Message] Java build process succeed..."), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
				LOG_BUILD_MESSAGE_COLOR(_T("[Message] Lauching Java virtual machine (JVM), initiating loader for execution..."), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
				if (!PathFileExists(m_BuildSessionInfo._strJavaVMPath))
				{
					CString strMsg;
					strMsg.Format(_T("[Path Error] \"%s\" does not exist...\n"), m_BuildSessionInfo._strJavaVMPath);
					LOG_BUILD_MESSAGE_COLOR(strMsg, BasicColors::orange);
					return 1L;
				}
				CString strCommandLine = _T("\"") + m_BuildSessionInfo._strJavaVMPath + _T("\" -classpath \"") + m_BuildSessionInfo._strExeFolderPath + _T("\" \"") + m_BuildSessionInfo._strExeFileName + _T("\"");
				LOG_BUILD_MESSAGE_COLOR(_T("[CommandLine] ") + strCommandLine, IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
				LOG_BUILD_MESSAGE_COLOR(_T("[ RUN .................................................................................."));
				m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
				RunJavaExeAfterCompile(strCommandLine);
			}
			else
			{
				LOG_BUILD_MESSAGE_ACTIVE_PANE(_T("[Message] Build process succeed..."), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
			}
		}
		else
		{
			LOG_BUILD_MESSAGE_ACTIVE_PANE(_T("\n[Error] Build process failed by errors...\n"), BasicColors::orange);
			OnShowBuildErrors();
			return 1L;
		}
	}
	else if (threadStatus == CEditorThreadCompiler::THREAD_STATUS::THREAD_STATUS_ABORT)
	{
		CString strMsg;
		strMsg.Format(_T("\n[Message] Build process exit by user, exit code is %d...\n"), nExitCode);
		LOG_BUILD_MESSAGE_ACTIVE_PANE(strMsg, IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
	}
	else if (threadStatus == CEditorThreadCompiler::THREAD_STATUS::THREAD_STATUS_FAILED)
	{
		CString strMsg;
		strMsg.Format(_T("\n[Error] Build process failed, exit code is %d...\n"), nExitCode);
		LOG_BUILD_MESSAGE_ACTIVE_PANE(strMsg, BasicColors::orange);
		DisableAllDocumemtReadOnly();
		return 1L;
	}
	DisableAllDocumemtReadOnly();
	return 0L;
}

LRESULT CEditorView::OnCompilerNotifyRunExitCode(WPARAM wParam, LPARAM lParam)
{
	if (m_pBuildProgressBar)
	{
		m_pBuildProgressBar.reset();
	}
						   
	LOG_BUILD_MESSAGE_COLOR(_T("\n..................................................................................... END ]\n"));

	OSUtils::LogStopBenchmark(LOG_TARGET::BUILD_WINDOW, m_BuildSessionInfo._BuildMeasureTime, _T("[Message] Run finished after : "), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
	m_BuildSessionInfo._BuildMeasureTime = 0;

	CEditorThreadCompiler::THREAD_STATUS threadStatus = (CEditorThreadCompiler::THREAD_STATUS)wParam;
	DWORD nExitCode = (DWORD)lParam;
	if (threadStatus == CEditorThreadCompiler::THREAD_STATUS::THREAD_STATUS_FINISHED)
	{
		if (nExitCode == 0)
		{
			CString strMsg;
			strMsg.Format(_T("[Message] Program exit as a succeed run, exit code is %d...\n"), nExitCode);
			LOG_BUILD_MESSAGE_COLOR(strMsg, IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
		}
		else
		{
			CString strMsg;
			strMsg.Format(_T("[Error] Program exit as a failed run, exit code is %d...\n"), nExitCode);
			LOG_BUILD_MESSAGE_COLOR(strMsg, IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
		}
	}
	else if (threadStatus == CEditorThreadCompiler::THREAD_STATUS::THREAD_STATUS_ABORT)
	{
		CString strMsg;
		strMsg.Format(_T("[Message] Program exit by user, exit code is %d...\n"), nExitCode);
		LOG_BUILD_MESSAGE_COLOR(strMsg, IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
	}
	else if (threadStatus == CEditorThreadCompiler::THREAD_STATUS::THREAD_STATUS_FAILED)
	{
		CString strMsg;
		strMsg.Format(_T("[Error] Program start failed, exit code is %d...\n"), nExitCode);
		LOG_BUILD_MESSAGE_COLOR(strMsg, BasicColors::orange);
		OnRemoveAllDebugPointer();
		DisableAllDocumemtReadOnly();
		return 1L;
	}
	OnRemoveAllDebugPointer();
	DisableAllDocumemtReadOnly();
	return 0L;
}


LRESULT CEditorView::OnCompilerNotifyDebugExitCode(WPARAM wParam, LPARAM lParam)
{
	if (m_pBuildProgressBar)
	{
		m_pBuildProgressBar.reset();
	}

	CEditorThreadCompiler::THREAD_STATUS threadStatus = (CEditorThreadCompiler::THREAD_STATUS)wParam;
	DWORD nExitCode = (DWORD)lParam;
	if (threadStatus == CEditorThreadCompiler::THREAD_STATUS::THREAD_STATUS_FINISHED)
	{
		if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON
			|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT
			|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PERL
			|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_GOLANG
			|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PHP)
		{
			LOG_BUILD_MESSAGE_COLOR(_T("\n.................................................................................... END ]\n"));
		}

		OSUtils::LogStopBenchmark(LOG_TARGET::BUILD_WINDOW, m_BuildSessionInfo._BuildMeasureTime, _T("[Message] Build process for debugger finished after : "), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);

		m_BuildSessionInfo._BuildMeasureTime = 0;
		if (nExitCode == 0)
		{
			if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
				|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
				|| m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
			{
				LOG_BUILD_MESSAGE_COLOR(_T("[Message] Build process for debugger succeed..."), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
				LOG_BUILD_MESSAGE_COLOR(_T("[Message] Initiating debugger..."), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
				LOG_BUILD_MESSAGE_COLOR(_T("[ DEBUG ................................................................................"));
				m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
				RunGDBDebuggerAfterCompile();
			}
			else if (m_CurrentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
			{
				LOG_BUILD_MESSAGE_COLOR(_T("[Message] Build process for Java debugger succeed..."), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
				LOG_BUILD_MESSAGE_COLOR(_T("[Message] Lauching Java virtual machine (JVM), Initialize loader for execution..."), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
				LOG_BUILD_MESSAGE_COLOR(_T("[ DEBUG ................................................................................"));
				m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
				RunJavaDebuggerAfterCompile();
			}
			else
			{
				LOG_BUILD_MESSAGE_ACTIVE_PANE(_T("[Message] Build process for debugger succeed..."), IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
			}
		}
		else
		{
			LOG_BUILD_MESSAGE_ACTIVE_PANE(_T("\n[Error] Build process for debugger failed by errors...\n"), BasicColors::orange);
			OnShowBuildErrors();
			return 1L;
		}
	}
	else if (threadStatus == CEditorThreadCompiler::THREAD_STATUS::THREAD_STATUS_ABORT)
	{
		CString strMsg;
		strMsg.Format(_T("\n[Message] Build process for debugger exit by user, exit code is %d...\n"), nExitCode);
		LOG_BUILD_MESSAGE_ACTIVE_PANE(strMsg, IS_LIGHT_THEME ? BasicColors::black : BasicColors::green);
	}
	else if (threadStatus == CEditorThreadCompiler::THREAD_STATUS::THREAD_STATUS_FAILED)
	{
		CString strMsg;
		strMsg.Format(_T("\n[Error] Build process for debugger failed, exit code is %d...\n"), nExitCode);
		LOG_BUILD_MESSAGE_ACTIVE_PANE(strMsg, BasicColors::orange);
		OnRemoveAllDebugPointer();
		DisableAllDocumemtReadOnly();
		return 1L;
	}
	OnRemoveAllDebugPointer();
	DisableAllDocumemtReadOnly();
	return 0L;
}

void CEditorView::PushTextToClipBoard(const CString& str)
{
	if (OpenClipboard())
	{
		GLOBALHANDLE hGlobal;
		TCHAR* pGlobal;
		EmptyClipboard();
		hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT | GMEM_SHARE, (str.GetLength() + 1) * sizeof(TCHAR));
		pGlobal = (TCHAR*)GlobalLock(hGlobal);
		_tcscpy(pGlobal, (LPTSTR)(LPCTSTR)str);
		GlobalUnlock(hGlobal);
		SetClipboardData(CF_UNICODETEXT, hGlobal);
		CloseClipboard();
	}
}

namespace
{
	BOOL IsOneDatasetValid(const CString& strOneDataset)
	{
		if (strOneDataset.IsEmpty()) return FALSE;
		if (strOneDataset.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_")) == strOneDataset)
		{
			return TRUE;
		}
		return FALSE;
	}
}

void CEditorView::AddAutoCompleteFromFile(const CString& strFilePath)
{
	if (PathUtils::IsBinaryFile(strFilePath, FILE_BINNARY | FILE_MEDIA | FILE_IMAGE | FILE_PDF))
	{
		AfxMessageBox(_T("[Error] Auto complete data does not support binary file!"));
		return;
	}
	CString strFileContent;
	PathUtils::OpenFile(strFilePath, strFileContent);
	std::wstring strTarget = AppUtils::CStringToWStd(strFileContent);
	strFileContent = AppUtils::RemoveJunkFromCString(strFileContent);
	std::wstring const strDelimiters{ EDITOR_SPECIAL_STRINGS };
	size_t beg, pos = 0;
	while ((beg = strTarget.find_first_not_of(strDelimiters, pos)) != std::wstring::npos)
	{
		pos = strTarget.find_first_of(strDelimiters, beg + 1);
		CString strFound = AppUtils::WStdToCString(strTarget.substr(beg, pos - beg));
		if (IsOneDatasetValid(strFound))
		{
			m_AutoCompelteDataset.insert(strFound.Trim());
		}
	}
	AfxMessageBox(_T("AutoComplete dataset successfully loaded from file."), MB_ICONINFORMATION);
}

void CEditorView::OnAddAutoCompleteFromFile()
{
	CString strDefaultFilter = PathUtils::GetDataBaseFileFilter();
	CFileDialog fileDlg(TRUE, _T(""), _T("*.*"), OFN_FILEMUSTEXIST, strDefaultFilter);
	fileDlg.m_ofn.lpstrTitle = _T("Please select auto complete dataset file...");
	if (fileDlg.DoModal() != IDOK)
	{
		return;
	}
	CString stFilePath = fileDlg.GetPathName();
	AddAutoCompleteFromFile(stFilePath);
}

void CEditorView::AddAutoCompleteFromFolder(const CString& strFolderPath)
{
	if (!PathFileExists(strFolderPath)) return;
	auto startMeasureTime = OSUtils::StartBenchmark();
	std::vector<CString> vecFileName;
	PathUtils::GetAllFilesFromFolder(strFolderPath, vecFileName);
	for (auto const& stFilePath : vecFileName)
	{
		if (PathUtils::IsBinaryFile(stFilePath, FILE_BINNARY | FILE_MEDIA | FILE_IMAGE | FILE_PDF)) continue;
		CString strFileContent;
		PathUtils::OpenFile(stFilePath, strFileContent);
		std::wstring strTarget = AppUtils::CStringToWStd(strFileContent);
		strFileContent = AppUtils::RemoveJunkFromCString(strFileContent);
		std::wstring const strDelimiters{ EDITOR_SPECIAL_STRINGS };
		size_t beg, pos = 0;
		while ((beg = strTarget.find_first_not_of(strDelimiters, pos)) != std::wstring::npos)
		{
			pos = strTarget.find_first_of(strDelimiters, beg + 1);
			CString strFound = AppUtils::WStdToCString(strTarget.substr(beg, pos - beg));
			if (IsOneDatasetValid(strFound))
			{
				m_AutoCompelteDataset.insert(strFound.Trim());
			}
		}
	}
	CString strMsg;
	strMsg.Format(_T("> Loaded dataset from folder %s - timelapse: "), strFolderPath);
	OSUtils::LogStopBenchmark(LOG_TARGET::MESSAGE_WINDOW, startMeasureTime, strMsg);
	AfxMessageBox(_T("AutoComplete dataset successfully loaded from folder."), MB_ICONINFORMATION);
}

void CEditorView::OnAddAutoCompleteFromFolder()
{
	CFolderPickerDialog dlg;
	dlg.m_ofn.lpstrTitle = _T("Please select auto complete dataset folder...");
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	CString strFolderDataset = dlg.GetPathName();
	AddAutoCompleteFromFolder(strFolderDataset);
}

void CEditorView::OnAddAutoCompleteEnglishDataset()
{
	CString strDataSetPath = PathUtils::GetVinaTextPackagePath() + _T("\\translator-packages\\english-words.ee-package");
	if (PathFileExists(strDataSetPath))
	{
		m_AutoCompelteDataset.clear();
		CStringArray arrLine;
		PathUtils::OpenFile(strDataSetPath, arrLine);
		for (int i = 0; i < arrLine.GetSize(); ++i)
		{
			m_AutoCompelteDataset.insert(arrLine[i].Trim());
		}
		AfxMessageBox(_T("AutoComplete dataset english successfully loaded."), MB_ICONINFORMATION);
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> Loaded dataset english, total %d vocabulary words..."), static_cast<int>(m_AutoCompelteDataset.size()));
	}
	else
	{
		AfxMessageBoxFormat(MB_ICONWARNING, _T("[Path Error] \"%s\" does not exist."), strDataSetPath);
	}
}

void CEditorView::OnClearAutoCompleteDataset()
{
	m_AutoCompelteDataset.clear();
	AfxMessageBox(_T("Auto complete dataset successfully cleared."), MB_ICONINFORMATION);
	LOG_OUTPUT_MESSAGE_COLOR(_T("Auto complete dataset successfully cleared!"));
}

void CEditorView::OnOptionsEditMisspelledReplaceWith()
{
	std::vector<std::wstring> suggestionList;
	std::wstring strCurrentWord;
	m_SpellChecker.GetSuggestionReplaceList(suggestionList, strCurrentWord);
	if (!strCurrentWord.empty())
	{
		MisspelledReplaceWithDlg dlg;
		dlg.SetTargetWord(AppUtils::WStdToCString(strCurrentWord));
		dlg.SetSuggestionList(suggestionList);
		dlg.DoModal();
	}
	else
	{
		AfxMessageBox(_T("[Error] Can not find misspelled word at current position!"));
	}
}

void CEditorView::OnOptionsEditSpellChecker()
{
	if (!m_bEnableSpellChecker)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> Started spell checker for languague %s..."), AppSettingMgr.m_strLanguageSpellCheck);
		m_bEnableSpellChecker = TRUE;
		m_SpellChecker.Initilize(&m_EditorCtrl, AppUtils::CStringToWStd(AppSettingMgr.m_strLanguageSpellCheck), m_LangKeywordDataset);
		// start check
		KillTimer(START_SPELL_CHECKER_TIMER);
		SetTimer(START_SPELL_CHECKER_TIMER, SPELL_CHECKER_INTERVAL, NULL);
	}
	else
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> Stopped spell checker for languague %s..."), AppSettingMgr.m_strLanguageSpellCheck);
		m_bEnableSpellChecker = FALSE;
		m_SpellChecker.Finalize();
		// stop check
		KillTimer(START_SPELL_CHECKER_TIMER);
		m_EditorCtrl.RemoveIndicatorSpellCheck();
	}
}

void CEditorView::OnOptionsUpdateEditSpellChecker(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_bEnableSpellChecker);
}

void CEditorView::OnOptionsUpdateFileSummary(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(PathFileExists(m_pDocument->GetPathName()));
}

void CEditorView::StartSpellChecker()
{
	m_SpellChecker.StartSpellCheckingSession();
}

void CEditorView::OnRemoveAllDebugPointer()
{
	POSITION p1 = AfxGetApp()->GetFirstDocTemplatePosition();
	while (p1)
	{
		CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(p1);
		POSITION p2 = doctempl->GetFirstDocPosition();
		while (p2)
		{
			CEditorDoc* pDoc = dynamic_cast<CEditorDoc*>(doctempl->GetNextDoc(p2));
			if (pDoc)
			{
				auto pEditor = pDoc->GetEditorCtrl();
				if (pEditor)
				{
					pEditor->DeleteAllDebugPointer();
				}
			}
		}
	}
}

void CEditorView::OnReplace4SpacesByTab()
{
	Replace4SpacesByTab(FALSE);
	m_EditorCtrl.EnableDisplayWhiteSpace(TRUE);
}

void CEditorView::OnReplaceTabBy4Spaces()
{
	Replace4SpacesByTab(TRUE);
	m_EditorCtrl.EnableDisplayWhiteSpace(TRUE);
}

void CEditorView::OnOptionsDecreaseTabIndentation()
{
	m_EditorCtrl.DoCommand(SCI_BACKTAB);
}

void CEditorView::OnOptionsIncreaseTabIndentation()
{
	m_EditorCtrl.DoCommand(SCI_TAB);
}

void CEditorView::OnFileSummary()
{
	CEditorDoc *pDoc = GetEditorDocument();
	ASSERT(pDoc);
	if (!pDoc) return;

	CString strFilePath = _T("File Path: ") + pDoc->GetPathName();
	CString strCreatedAt = _T("Created At: ") + PathUtils::GetFileTimePropertyCString(pDoc->GetPathName(), FILE_TIME_PROPERTY::FILE_TIME_CREATED);
	CString strLastestModifiedat = _T("Last Modified At: ") + PathUtils::GetFileTimePropertyCString(pDoc->GetPathName(), FILE_TIME_PROPERTY::FILE_TIME_LAST_MODIFIED);
	CString strLastestAccessedat = _T("Last Accsess At: ") + PathUtils::GetFileTimePropertyCString(pDoc->GetPathName(), FILE_TIME_PROPERTY::FILE_TIME_LAST_ACCESSED);
	CString strCharacters = _T("Total Characters: ") + AppUtils::IntToCString(m_EditorCtrl.GetTextLength());

	CString strEditorText;
	m_EditorCtrl.GetText(strEditorText);
	int lCountWord = 0;
	if (!strEditorText.IsEmpty())
	{
		CStringArray arrLine;
		strEditorText.Replace(_T("\n"),CSTRING_SPACE);
		AppUtils::SplitCString(strEditorText,CSTRING_SPACE, arrLine);
		for (int i = 0; i < arrLine.GetSize(); ++i)
		{
			if (arrLine[i].Trim().IsEmpty()) continue;
			lCountWord++;
		}
	}
	CString strWords = _T("Total Words: ") + AppUtils::IntToCString(lCountWord);
	CString strLines = _T("Total Lines: ") + AppUtils::IntToCString(m_EditorCtrl.GetLineCount());
	CString strFileType = _T("File Type: ") + DetectCurrentDocLanguage();
	CString strFileDescription = _T("File Description: ") + AppUtils::GetFileFormatDescription(m_EditorCtrl.GetFileExtension());
	LONGLONG llFileSize = PathUtils::GetFileSize(pDoc->GetPathName());
	CString strFileSize = _T("File Size: ") + CString(std::unique_ptr<char>(PathUtils::SizeMemoryToString(llFileSize)).get());
	CString strFileEncoding = _T("File Encoding: ") + m_EditorCtrl.GetEncodingName();;
	CString strFileContentTemp = PathUtils::IsBinaryFile(pDoc->GetPathName()) ? _T("Binary") : _T("PlainText");
	CString strFileContent = _T("File Content: ") + strFileContentTemp;
	CString strFileEOL = _T("End Of Line: ") + m_EditorCtrl.GetEOLName();
	CString strReadonly = _T("Read Only: ");
	if (PathUtils::IsFileReadOnly(pDoc->GetPathName()))
	{
		strReadonly += _T("Yes");
	}
	else
	{
		strReadonly += _T("No");
	}
	// join information...
	CString strMessageFileSummary = _T("\n________________| FILE INFORMATION |_______________________________________\n");
	strMessageFileSummary += strFilePath + EDITOR_NEW_LINE_LF;
	strMessageFileSummary += strCreatedAt + EDITOR_NEW_LINE_LF;
	strMessageFileSummary += strLastestModifiedat + EDITOR_NEW_LINE_LF;
	strMessageFileSummary += strLastestAccessedat + EDITOR_NEW_LINE_LF;
	strMessageFileSummary += strWords + EDITOR_NEW_LINE_LF;
	strMessageFileSummary += strCharacters + EDITOR_NEW_LINE_LF;
	strMessageFileSummary += strLines + EDITOR_NEW_LINE_LF;
	strMessageFileSummary += strFileType + EDITOR_NEW_LINE_LF;
	strMessageFileSummary += strFileDescription + EDITOR_NEW_LINE_LF;
	strMessageFileSummary += strFileSize + EDITOR_NEW_LINE_LF;
	strMessageFileSummary += strFileEncoding + EDITOR_NEW_LINE_LF;
	strMessageFileSummary += strFileContent + EDITOR_NEW_LINE_LF;
	strMessageFileSummary += strFileEOL + EDITOR_NEW_LINE_LF;
	strMessageFileSummary += strReadonly + EDITOR_NEW_LINE_LF;
	strMessageFileSummary += _T("___________________________________________________________________________\n\n");
	// dump to log window...
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;
	LOG_OUTPUT_MESSAGE_COLOR(strMessageFileSummary);
	ActiveDockWindow(DOCKABLE_PANE_TYPE::LOG_MESSAGE_PANE);
}

void CEditorView::OnOptionsScrollRightView()
{
	for (int i = 0 ; i < 2; ++i) m_EditorCtrl.DoCommand(WM_HSCROLL, SB_LINERIGHT, NULL);
}

void CEditorView::OnOptionsScrollLeftView()
{
	for (int i = 0; i < 2; ++i) m_EditorCtrl.DoCommand(WM_HSCROLL, SB_LINELEFT, NULL);
}

void CEditorView::OnOptionsSyncScrollRightView()
{
	auto fSycnAction = [](CEditorDoc* pDoc) -> void {
		if (pDoc) {
			auto pView = pDoc->GetEditorView();
			if (pView)
			{
				auto pEditor = pView->GetEditorCtrl();
				for (int i = 0; i < 2; ++i) pEditor->DoCommand(WM_HSCROLL, SB_LINERIGHT, NULL);
			}
		}
	};
	AppUtils::SyncActionAllEditorDocuments(fSycnAction);
}

void CEditorView::OnOptionsSyncScrollLeftView()
{
	auto fSycnAction = [](CEditorDoc* pDoc) -> void {
		if (pDoc) {
			auto pView = pDoc->GetEditorView();
			if (pView)
			{
				auto pEditor = pView->GetEditorCtrl();
				for (int i = 0; i < 2; ++i) pEditor->DoCommand(WM_HSCROLL, SB_LINELEFT, NULL);
			}
		}
	};
	AppUtils::SyncActionAllEditorDocuments(fSycnAction);
}

void CEditorView::OnOptionsSyncScrollUpView()
{
	IMPLEMENT_SYNC_ACTION_VIEW(SCI_LINESCROLLUP);
}

void CEditorView::OnOptionsSyncScrollDownView()
{
	IMPLEMENT_SYNC_ACTION_VIEW(SCI_LINESCROLLDOWN);
}

void CEditorView::OnOptionsSyncZoomInView()
{
	IMPLEMENT_SYNC_ACTION_VIEW(SCI_ZOOMIN);
	AppSettingMgr.m_nEditorZoomFactor = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETZOOM));
}

void CEditorView::OnOptionsSyncZoomOutView()
{
	IMPLEMENT_SYNC_ACTION_VIEW(SCI_ZOOMOUT);
	AppSettingMgr.m_nEditorZoomFactor = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETZOOM));
}

void CEditorView::OnOptionsZoomResetView()
{
	IMPLEMENT_SYNC_ACTION_VIEW(SCI_SETZOOM);
	AppSettingMgr.m_nEditorZoomFactor = static_cast<int>(m_EditorCtrl.DoCommand(SCI_GETZOOM));
}

void CEditorView::OnOptionsEnableSyncScrolling()
{
	TOGGLE_FLAG(AppSettingMgr.m_bEnableSynchronizeScrolling);
	if (AppSettingMgr.m_bEnableSynchronizeScrolling)
		AfxMessageBox(_T("Synchronization of scrolling views was enabled. You can use [MiddleMouse] for vertical scrolling and [Shift+MiddleMouse] for horizontal scrolling."), MB_ICONINFORMATION);
	else 
		AfxMessageBox(_T("Synchronization of scrolling views was disabled!"), MB_ICONINFORMATION);
}

void CEditorView::OnOptionsScrollToCaret()
{
	m_EditorCtrl.SetLineCenterDisplay(m_EditorCtrl.GetCurrentLine());
}

void CEditorView::OnUpdateOptionsSyncVerticalScrolling(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(AppSettingMgr.m_bEnableSynchronizeScrolling);
}

void CEditorView::OnEditShowAllCharacter()
{
	TOGGLE_FLAG(m_bToggleShowAllCharater);
	m_EditorCtrl.EnableDisplayTabIndentation(m_bToggleShowAllCharater);
	m_EditorCtrl.EnableDisplayWhiteSpace(m_bToggleShowAllCharater);
	m_EditorCtrl.EnableShowEOL(m_bToggleShowAllCharater);
}

void CEditorView::OnEditRemoveFromXToYLine()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CRemoveFromXToYDlg dlg;
	dlg.m_strFromX = AppUtils::IntToCString(m_EditorCtrl.GetCurrentColumn());
	dlg.m_strDlgCaption = _T("Remove From Postion X To Y In Line");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_strFromX.IsEmpty() || dlg.m_strToY.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}

		int posX = AppUtils::CStringToInt(dlg.m_strFromX);
		int posY = AppUtils::CStringToInt(dlg.m_strToY);

		if (posX < 0 || posY < 0 || posY < posX)
		{
			AfxMessageBox(_T("[Error] Inputs are invalid!"));
			return;
		}

		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));

				CString strNewScripts;
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					if (dlg.m_bRemoveFromEndLine)
					{
						strLine.MakeReverse();
						strLine = strLine.Mid(0, posX) + strLine.Mid(posY);
						strLine.MakeReverse();
					}
					else
					{
						strLine = strLine.Mid(0, posX) + strLine.Mid(posY);
					}
					strNewScripts += strLine + m_EditorCtrl.GetEOLCString();
				}
				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
				int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
				int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

				CString strNewScripts;
				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					if (dlg.m_bRemoveFromEndLine)
					{
						strCurLineText.MakeReverse();
						strCurLineText = strCurLineText.Mid(0, posX) + strCurLineText.Mid(posY);
						strCurLineText.MakeReverse();
					}
					else
					{
						strCurLineText = strCurLineText.Mid(0, posX) + strCurLineText.Mid(posY);
					}
					if (lLineStart != lLineEnd)
					{
						strNewScripts += strCurLineText + m_EditorCtrl.GetEOLCString();
					}
					else
					{
						strNewScripts += strCurLineText;
					}
				}
				m_EditorCtrl.SetStartSelection(StartLinePos);
				m_EditorCtrl.SetEndSelection(EndLinePos);
				m_EditorCtrl.ReplaceSelectionWithText(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsRemoveFromCharXToYInLine()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CRemoveFromXToYDlg dlg;
	dlg.m_strDlgCaption = _T("Remove From Character X To Y In Line");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_strFromX.IsEmpty() || dlg.m_strToY.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}

		if (dlg.m_strFromX.GetLength() != 1 || dlg.m_strToY.GetLength() != 1)
		{
			AfxMessageBox(_T("[Error] Inputs are invalid, must be a character!"));
			return;
		}

		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));

				CString strNewScripts;
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					if (dlg.m_bRemoveFromEndLine)
					{
						int posX = strLine.ReverseFind(dlg.m_strFromX[0]);
						int posY = strLine.ReverseFind(dlg.m_strFromX[0]);
						strLine.MakeReverse();
						strLine = strLine.Mid(0, posX + 1) + strLine.Mid(posY);
						strLine.MakeReverse();
					}
					else
					{
						int posX = strLine.Find(dlg.m_strFromX);
						int posY = strLine.Find(dlg.m_strToY);
						strLine = strLine.Mid(0, posX + 1) + strLine.Mid(posY);
					}
					strNewScripts += strLine + m_EditorCtrl.GetEOLCString();
				}
				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
				int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
				int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

				CString strNewScripts;
				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					if (dlg.m_bRemoveFromEndLine)
					{
						int posX = strCurLineText.ReverseFind(dlg.m_strFromX[0]);
						int posY = strCurLineText.ReverseFind(dlg.m_strFromX[0]);
						strCurLineText.MakeReverse();
						strCurLineText = strCurLineText.Mid(0, posX + 1) + strCurLineText.Mid(posY);
						strCurLineText.MakeReverse();
					}
					else
					{
						int posX = strCurLineText.Find(dlg.m_strFromX);
						int posY = strCurLineText.Find(dlg.m_strToY);
						strCurLineText = strCurLineText.Mid(0, posX + 1) + strCurLineText.Mid(posY);
					}
					if (lLineStart != lLineEnd)
					{
						strNewScripts += strCurLineText + m_EditorCtrl.GetEOLCString();
					}
					else
					{
						strNewScripts += strCurLineText;
					}
				}
				m_EditorCtrl.SetStartSelection(StartLinePos);
				m_EditorCtrl.SetEndSelection(EndLinePos);
				m_EditorCtrl.ReplaceSelectionWithText(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnEditRemoveBeforWordLine()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CRemoveAfterBeforeWordDlg dlg;
	dlg.m_strDlgCaption = _T("Remove Before Word In Line");
	dlg.m_strDlgStatic = _T("Before Word:");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_strWord.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}

		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));

				CString strNewScripts;
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					int posBefore = strLine.Find(dlg.m_strWord);
					if (posBefore != -1)
					{
						strLine = strLine.Mid(posBefore);
					}
					strNewScripts += strLine + m_EditorCtrl.GetEOLCString();
				}
				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
				int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
				int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

				CString strNewScripts;
				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					int posBefore = strCurLineText.Find(dlg.m_strWord);
					if (posBefore != -1)
					{
						strCurLineText = strCurLineText.Mid(posBefore);
					}
					strNewScripts += strCurLineText + m_EditorCtrl.GetEOLCString();
					if (lLineStart != lLineEnd)
					{
						strNewScripts += strCurLineText + m_EditorCtrl.GetEOLCString();
					}
					else
					{
						strNewScripts += strCurLineText;
					}
				}
				m_EditorCtrl.SetStartSelection(StartLinePos);
				m_EditorCtrl.SetEndSelection(EndLinePos);
				m_EditorCtrl.ReplaceSelectionWithText(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnEditRemoveAfterWordLine()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CRemoveAfterBeforeWordDlg dlg;
	dlg.m_strDlgCaption = _T("Remove After Word In Line");
	dlg.m_strDlgStatic = _T("After Word:");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_strWord.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}

		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));

				CString strNewScripts;
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					int posAfter = strLine.Find(dlg.m_strWord);
					if (posAfter != -1)
					{
						strLine = strLine.Mid(0, posAfter + dlg.m_strWord.GetLength());
					}
					strNewScripts += strLine + m_EditorCtrl.GetEOLCString();
				}
				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
				int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
				int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

				CString strNewScripts;
				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					int posAfter = strCurLineText.Find(dlg.m_strWord);
					if (posAfter != -1)
					{
						strCurLineText = strCurLineText.Mid(0, posAfter + dlg.m_strWord.GetLength());
					}
					strNewScripts += strCurLineText + m_EditorCtrl.GetEOLCString();
					if (lLineStart != lLineEnd)
					{
						strNewScripts += strCurLineText + m_EditorCtrl.GetEOLCString();
					}
					else
					{
						strNewScripts += strCurLineText;
					}
				}
				m_EditorCtrl.SetStartSelection(StartLinePos);
				m_EditorCtrl.SetEndSelection(EndLinePos);
				m_EditorCtrl.ReplaceSelectionWithText(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnEditInsertAfterWordLine()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CInsertAfterWordInLineDlg dlg;
	dlg.m_strDlgCaption = _T("Insert After Word In Line");
	dlg.m_strDlgStatic = _T("After Word:");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_strWord.IsEmpty() || dlg.m_strInsertWhat.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}

		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));

				CString strNewScripts;
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					int posAfter = strLine.Find(dlg.m_strWord);
					if (posAfter != -1)
					{
						strLine = strLine.Mid(0, posAfter + dlg.m_strWord.GetLength()) + dlg.m_strInsertWhat + strLine.Mid(posAfter + dlg.m_strWord.GetLength());
					}
					strNewScripts += strLine + m_EditorCtrl.GetEOLCString();
				}

				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
				int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
				int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

				CString strNewScripts;
				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					int posAfter = strCurLineText.Find(dlg.m_strWord);
					if (posAfter != -1)
					{
						strCurLineText = strCurLineText.Mid(0, posAfter + dlg.m_strWord.GetLength()) + dlg.m_strInsertWhat + strCurLineText.Mid(posAfter + dlg.m_strWord.GetLength());
					}
					strNewScripts += strCurLineText + m_EditorCtrl.GetEOLCString();
					if (lLineStart != lLineEnd)
					{
						strNewScripts += strCurLineText + m_EditorCtrl.GetEOLCString();
					}
					else
					{
						strNewScripts += strCurLineText;
					}
				}
				m_EditorCtrl.SetStartSelection(StartLinePos);
				m_EditorCtrl.SetEndSelection(EndLinePos);
				m_EditorCtrl.ReplaceSelectionWithText(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnEditInsertBetweenLines()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CInsertBetweenLines dlg;
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_strInsertWhat.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}
		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				CString strNewScripts;
				if (dlg.m_bInsertTopMost)
				{
					strNewScripts += dlg.m_strInsertWhat + m_EditorCtrl.GetEOLCString();
				}
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					if (iss.eof())
					{
						strNewScripts += strLine + m_EditorCtrl.GetEOLCString();
					}
					else
					{
						strNewScripts += strLine + m_EditorCtrl.GetEOLCString() + dlg.m_strInsertWhat + m_EditorCtrl.GetEOLCString();
					}
				}
				if (dlg.m_bInsertBottomMost)
				{
					strNewScripts += dlg.m_strInsertWhat + m_EditorCtrl.GetEOLCString();
				}
				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
				int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
				int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

				CString strNewScripts;
				if (dlg.m_bInsertTopMost)
				{
					strNewScripts += dlg.m_strInsertWhat + m_EditorCtrl.GetEOLCString();
				}
				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					if (lLineStart != lLineEnd)
					{
						strNewScripts += strCurLineText + m_EditorCtrl.GetEOLCString() + dlg.m_strInsertWhat + m_EditorCtrl.GetEOLCString();
					}
					else
					{
						strNewScripts += strCurLineText;
					}
				}
				if (dlg.m_bInsertBottomMost)
				{
					strNewScripts += dlg.m_strInsertWhat + m_EditorCtrl.GetEOLCString();
				}
				m_EditorCtrl.SetStartSelection(StartLinePos);
				m_EditorCtrl.SetEndSelection(EndLinePos);
				m_EditorCtrl.ReplaceSelectionWithText(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnEditRemoveSpace()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stScript;
	m_EditorCtrl.GetText(stScript);
	if (!stScript.IsEmpty())
	{
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		if (stSelectedScript.IsEmpty())
		{
			stScript.Replace(_T(" "), _T(""));
			m_EditorCtrl.SetTextToEditor(stScript);
		}
		else
		{
			int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
			int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
			int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
			int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
			int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
			int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

			CString strNewScripts;
			for (int i = lLineStart; i <= lLineEnd; ++i)
			{
				CString strCurLineText;
				m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
				strCurLineText.Replace(_T(" "), _T(""));
				strNewScripts += strCurLineText + m_EditorCtrl.GetEOLCString();
			}

			m_EditorCtrl.SetStartSelection(StartLinePos);
			m_EditorCtrl.SetEndSelection(EndLinePos);
			m_EditorCtrl.ReplaceSelectionWithText(strNewScripts.Mid(0, strNewScripts.GetLength()));
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnEditInsertBeforeWordLine()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CInsertAfterWordInLineDlg dlg;
	dlg.m_strDlgCaption = _T("Insert Before Word In Line");
	dlg.m_strDlgStatic = _T("Before Word:");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_strInsertWhat.IsEmpty() || dlg.m_strWord.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}

		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));

				CString strNewScripts;
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					int posBefore = strLine.Find(dlg.m_strWord);
					if (posBefore != -1)
					{
						strLine = strLine.Mid(0, posBefore) + dlg.m_strInsertWhat + dlg.m_strWord + strLine.Mid(posBefore + dlg.m_strWord.GetLength());
					}
					strNewScripts += strLine + m_EditorCtrl.GetEOLCString();
				}

				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
				int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
				int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

				CString strNewScripts;
				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					int posBefore = strCurLineText.Find(dlg.m_strWord);
					if (posBefore != -1)
					{
						strNewScripts = strNewScripts.Mid(0, posBefore) + dlg.m_strInsertWhat + dlg.m_strWord + strNewScripts.Mid(posBefore + dlg.m_strWord.GetLength());
					}
					strNewScripts += strCurLineText + m_EditorCtrl.GetEOLCString();
					if (lLineStart != lLineEnd)
					{
						strNewScripts += strCurLineText + m_EditorCtrl.GetEOLCString();
					}
					else
					{
						strNewScripts += strCurLineText;
					}
				}
				m_EditorCtrl.SetStartSelection(StartLinePos);
				m_EditorCtrl.SetEndSelection(EndLinePos);
				m_EditorCtrl.ReplaceSelectionWithText(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnEditInsertAtPositionLine()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CInsertFromPositionXDlg dlg;
	dlg.m_strPositionX = AppUtils::IntToCString(m_EditorCtrl.GetCurrentColumn());
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_strPositionX.IsEmpty() || dlg.m_strInsertWhat.IsEmpty())
		{
			AfxMessageBox(_T("[Error] Inputs are empty!"));
			return;
		}

		int posX = AppUtils::CStringToInt(dlg.m_strPositionX);
		if (posX < 0)
		{
			AfxMessageBox(_T("[Error] Inputs are invalid!"));
			return;
		}

		CString stScript;
		m_EditorCtrl.GetText(stScript);
		if (!stScript.IsEmpty())
		{
			CString stSelectedScript = m_EditorCtrl.GetSelectedText();
			if (stSelectedScript.IsEmpty())
			{
				std::wstring line;
				std::wistringstream iss(AppUtils::CStringToWStd(stScript));

				CString strNewScripts;
				while (std::getline(iss, line, AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())[0]))
				{
					CString strLine = AppUtils::WStdToCString(line);
					strLine.Replace(_T("\n"), _T(""));
					if (dlg.m_bInsertFromLineEnd)
					{
						strLine.MakeReverse();
						strLine = strLine.Mid(0, posX) + dlg.m_strInsertWhat.MakeReverse() + strLine.Mid(posX);
						dlg.m_strInsertWhat.MakeReverse();
						strLine.MakeReverse();
					}
					else
					{
						strLine = strLine.Mid(0, posX) + dlg.m_strInsertWhat + strLine.Mid(posX);
					}
					strNewScripts += strLine + m_EditorCtrl.GetEOLCString();
				}

				m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
			else
			{
				int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
				int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
				int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
				int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
				int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
				int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);

				CString strNewScripts;
				for (int i = lLineStart; i <= lLineEnd; ++i)
				{
					CString strCurLineText;
					m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
					if (dlg.m_bInsertFromLineEnd)
					{
						strCurLineText.MakeReverse();
						strCurLineText = strCurLineText.Mid(0, posX) + dlg.m_strInsertWhat.MakeReverse() + strCurLineText.Mid(posX);
						dlg.m_strInsertWhat.MakeReverse();
						strCurLineText.MakeReverse();
					}
					else
					{
						strCurLineText = strCurLineText.Mid(0, posX) + dlg.m_strInsertWhat + strCurLineText.Mid(posX);
					}
					if (lLineStart != lLineEnd)
					{
						strNewScripts += strCurLineText + m_EditorCtrl.GetEOLCString();
					}
					else
					{
						strNewScripts += strCurLineText;
					}
				}
				m_EditorCtrl.SetStartSelection(StartLinePos);
				m_EditorCtrl.SetEndSelection(EndLinePos);
				m_EditorCtrl.ReplaceSelectionWithText(strNewScripts.Mid(0, strNewScripts.GetLength()));
			}
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnEditConvertToInvertCase()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stSelectedScript = m_EditorCtrl.GetSelectedText();
	if (!stSelectedScript.IsEmpty())
	{
		std::wstring strSTD = AppUtils::CStringToWStd(stSelectedScript);
		int nPos = AppUtils::FindFirstCharacterNotOf(stSelectedScript, _T(" \t"));
		if (nPos >= 0)
		{
			AppUtils::ToInvertCase(strSTD);
			m_EditorCtrl.ReplaceSelectionWithText(AppUtils::WStdToCString(strSTD));
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnEditConvertToRandomCase()
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stSelectedScript = m_EditorCtrl.GetSelectedText();
	if (!stSelectedScript.IsEmpty())
	{
		std::wstring strSTD = AppUtils::CStringToWStd(stSelectedScript);
		int nPos = AppUtils::FindFirstCharacterNotOf(stSelectedScript, _T(" \t"));
		if (nPos >= 0)
		{
			AppUtils::ToRandomCase(strSTD);
			m_EditorCtrl.ReplaceSelectionWithText(AppUtils::WStdToCString(strSTD));
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnEditOpenFromSelection()
{
	CString stSelectedScript = m_EditorCtrl.GetSelectedText().Trim();
	if (PathFileExists(stSelectedScript))
	{
		if (PathUtils::IsDirectory(stSelectedScript))
		{
			PathUtils::OpenFileSystem(stSelectedScript);
		}
		else
		{
			AppUtils::CreateDocumentFromFile(stSelectedScript);
		}
	}
}

void CEditorView::OnEditRevealFromSelection()
{
	CString stSelectedScript = m_EditorCtrl.GetSelectedText().Trim();
	stSelectedScript.Replace(_T("\""), _T(""));
	if (PathFileExists(stSelectedScript))
	{
		CMainFrame* pFrame = AppUtils::GetMainFrame();
		if (!pFrame) return;
		pFrame->RevealInExplorerWindow(stSelectedScript);
	}
}

void CEditorView::OnUpdateEditShowAllCharacter(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_bToggleShowAllCharater);
}

void CEditorView::OnEditChangeBidirectional()
{
	m_EditorCtrl.EnableBidirectionalRightToLeft(!m_EditorCtrl.GetBidirectionalRightToLeft());
}

void CEditorView::OnUpdateEditChangeBidirectional(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_EditorCtrl.GetBidirectionalRightToLeft());
}

void CEditorView::OnOptionsStartMoniterFile()
{
	if (!m_bToggleMoniterFileRealTime)
	{
		m_bToggleMoniterFileRealTime = TRUE;
		KillTimer(START_MONITER_FILE_TIMER);
		SetTimer(START_MONITER_FILE_TIMER, MONITER_FILE_INTERVAL, NULL);
	}
	else
	{
		m_bToggleMoniterFileRealTime = FALSE;
		KillTimer(START_MONITER_FILE_TIMER);
	}
}

void CEditorView::OnUpdateStartMoniterFile(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_bToggleMoniterFileRealTime);
}

void CEditorView::ChangeUserLexer(const CString& strLexerName)
{
	if (strLexerName.IsEmpty())
		m_EditorCtrl.DisableUserLexer();
	else
		m_EditorCtrl.EnableUserLexer(strLexerName);
	m_EditorCtrl.InitilizeSetting(GetLanguageDatabase());
}

void CEditorView::OnEnableUserLexerLexerCPP()
{
	ChangeUserLexer(_T("cpp"));
}

void CEditorView::OnEnableUserLexerLexerPython()
{
	ChangeUserLexer(_T("python"));
}

void CEditorView::OnEnableUserLexerLexerHtmlXml()
{
	ChangeUserLexer(_T("hypertext"));
}

void CEditorView::OnEnableUserLexerLexerBashBatch()
{
	ChangeUserLexer(_T("batch"));
}

void CEditorView::OnEnableUserLexerLexerVBPascal()
{
	ChangeUserLexer(_T("vb"));
}

void CEditorView::OnDisableUserLexer()
{
	ChangeUserLexer(_T(""));
}

void CEditorView::OnAddLexerForFileExtension()
{
	const CString syntaxHighlightUserDataPath = PathUtils::GetSyntaxHighlightUserDataPath();
	if (PathFileExists(syntaxHighlightUserDataPath))
	{
		AppUtils::CreateDocumentFromFile(syntaxHighlightUserDataPath);
	}
	else
	{
		AfxMessageBoxFormat(MB_ICONWARNING, _T("[Path Error] \"%s\" does not exist!\n"), syntaxHighlightUserDataPath);
	}
}

void CEditorView::ChangeToEditorReadOnly()
{
	m_EditorCtrl.SetReadOnlyEditor(TRUE);
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;
	pFrame->PostMessage(WM_COMMAND, (WPARAM)UMW_SET_READ_ONLY_TAB_MDI);
	pFrame->PostMessage(WM_COMMAND, (WPARAM)UMW_SET_COLOR_ACTIVE_TAB_MDI);
}

void CEditorView::DisableAllDocumemtReadOnly()
{
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;
	pFrame->PostMessage(WM_COMMAND, (WPARAM)UMW_DISABLE_ALL_READ_ONLY_TAB_MDI);
	pFrame->PostMessage(WM_COMMAND, (WPARAM)UMW_SET_COLOR_ACTIVE_TAB_MDI);
}

void CEditorView::OnBuildSource()
{
}

void CEditorView::OnToolCreateGUID()
{
	CString strID = OSUtils::GetGUIDGlobal();
	CString strResultText = AfxCStringFormat(_T("> [GUID Generator] result: %s"), strID);
	LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strResultText, BasicColors::orange);
}

void CEditorView::OnToolCreateMd5()
{
	CString strSelectedText = m_EditorCtrl.GetSelectedText();
	if (strSelectedText.IsEmpty())
	{
		AfxMessageBox(_T("[Generator Error] Text selection is empty."));
		return;
	}
	CString strConvertedText = AppUtils::WStdToCString(md5_digest(AppUtils::CStringToStd(strSelectedText)));
	CString strResultText = AfxCStringFormat(_T("> [MD5 Generator] result: %s"), strConvertedText);
	LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strResultText, BasicColors::orange);
}

void CEditorView::OnToolCreateCRC()
{
	CString strSelectedText = m_EditorCtrl.GetSelectedText();
	if (strSelectedText.IsEmpty())
	{
		AfxMessageBox(_T("[Generator Error] Text selection is empty."));
		return;
	}
	CString strConvertedText = AppUtils::IntToCString(crc32_generate(AppUtils::CStringToStd(strSelectedText)));
	CString strResultText = AfxCStringFormat(_T("> [CRC32 Generator] result: %s"), strConvertedText);
	LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strResultText, BasicColors::orange);
}

void CEditorView::OnToolCreateSha256()
{
	CString strSelectedText = m_EditorCtrl.GetSelectedText();
	if (strSelectedText.IsEmpty())
	{
		AfxMessageBox(_T("[Generator Error] Text selection is empty."));
		return;
	}
	CString strConvertedText = AppUtils::WStdToCString(sha256_hash(AppUtils::CStringToStd(strSelectedText)));
	CString strResultText = AfxCStringFormat(_T("> [SHA256 Generator] result: %s"), strConvertedText);
	LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strResultText, BasicColors::orange);
}

void CEditorView::OnToolCreateSha1()
{
	CString strSelectedText = m_EditorCtrl.GetSelectedText();
	if (strSelectedText.IsEmpty())
	{
		AfxMessageBox(_T("[Generator Error] Text selection is empty."));
		return;
	}
	CString strConvertedText = AppUtils::StdToCString(sha1_hash(AppUtils::CStringToStd(strSelectedText)));
	CString strResultText = AfxCStringFormat(_T("> [SHA1 Generator] result: %s"), strConvertedText);
	LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strResultText, BasicColors::orange);
}

void CEditorView::OnOptionsGenerateTimeDate()
{
	CString strCurrentTime = OSUtils::DateToCStringABDHMSY(OSUtils::GetCurrentTimeEx());
	CString strResultText = AfxCStringFormat(_T("> [Timedate Generator] result: %s"), strCurrentTime);
	LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strResultText, BasicColors::orange);
}

void CEditorView::ConvertSlash(int option)
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stScript;
	m_EditorCtrl.GetText(stScript);
	if (!stScript.IsEmpty())
	{
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		if (stSelectedScript.IsEmpty())
		{
			if (option == 0)
				stScript.Replace(_T("\\"), _T("/"));
			if (option == 1)
				stScript.Replace(_T("/"), _T("\\"));
			if (option == 2)
				stScript.Replace(_T("\\"), _T("\\\\"));
			m_EditorCtrl.SetTextToEditor(stScript);
		}
		else
		{
			if (option == 0)
				stSelectedScript.Replace(_T("\\"), _T("/"));
			if (option == 1)
				stSelectedScript.Replace(_T("/"), _T("\\"));
			if (option == 2)
				stSelectedScript.Replace(_T("\\"), _T("\\\\"));
			m_EditorCtrl.ReplaceSelectionWithText(stSelectedScript);
		}
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionsConvertBackSlashToForwardSlash()
{
	ConvertSlash(0);
}

void CEditorView::OnOptionsConvertForwardSlashToBackSlash()
{
	ConvertSlash(1);
}

void CEditorView::OnOptionsConvertBackSlashToDoubleSlash()
{
	ConvertSlash(2);
}

void CEditorView::DoConvertTextFormat(CONVERT_TEXT_FORMAT formatText, BOOL bEncode)
{
	int nVisualLine = m_EditorCtrl.GetFirstVisibleLine();
	CString stScript;
	m_EditorCtrl.GetText(stScript);
	if (!stScript.IsEmpty())
	{
		m_EditorCtrl.BeginUndoTransactions();
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		BOOL bReplaceSelection = TRUE;
		if (stSelectedScript.IsEmpty())
		{
			bReplaceSelection = FALSE;
			stSelectedScript = stScript;
		}
		if (bEncode)
		{
			if (formatText == CONVERT_TEXT_FORMAT::BASE64_TYPE)
			{
				CString strConvertedText = AppUtils::StdToCString(base64_encode(AppUtils::CStringToStd(stSelectedScript)));
				if (bReplaceSelection == FALSE)  
					m_EditorCtrl.SetTextToEditor(strConvertedText);
				else
					m_EditorCtrl.ReplaceSelectionWithText(strConvertedText);
			}
			else if (formatText == CONVERT_TEXT_FORMAT::HEXA_TYPE)
			{
				CString strConvertedText = AppUtils::StdToCString(hexa_encode(AppUtils::CStringToStd(stSelectedScript)));
				if (bReplaceSelection == FALSE) 
					m_EditorCtrl.SetTextToEditor(strConvertedText);
				else
					m_EditorCtrl.ReplaceSelectionWithText(strConvertedText);
			}
			else if (formatText == CONVERT_TEXT_FORMAT::DECIMAL_TYPE)
			{
				CString strConvertedText = AppUtils::StdToCString(decimal_encode(AppUtils::CStringToStd(stSelectedScript)));
				if (bReplaceSelection == FALSE) 
					m_EditorCtrl.SetTextToEditor(strConvertedText);
				else
					m_EditorCtrl.ReplaceSelectionWithText(strConvertedText);
			}
			else if (formatText == CONVERT_TEXT_FORMAT::BINARY_TYPE)
			{
				CString strConvertedText = AppUtils::StdToCString(binary_encode(AppUtils::CStringToStd(stSelectedScript)));
				if (bReplaceSelection == FALSE) 
					m_EditorCtrl.SetTextToEditor(strConvertedText);
				else
					m_EditorCtrl.ReplaceSelectionWithText(strConvertedText);
			}
			else if (formatText == CONVERT_TEXT_FORMAT::OCTA_TYPE)
			{
				CString strConvertedText = AppUtils::StdToCString(octa_encode(AppUtils::CStringToStd(stSelectedScript)));
				if (bReplaceSelection == FALSE) 
					m_EditorCtrl.SetTextToEditor(strConvertedText);
				else
					m_EditorCtrl.ReplaceSelectionWithText(strConvertedText);
			}
		}
		else
		{
			if (formatText == CONVERT_TEXT_FORMAT::BASE64_TYPE)
			{
				CString strConvertedText = AppUtils::StdToCString(base64_decode(AppUtils::CStringToStd(stSelectedScript)));
				if (bReplaceSelection == FALSE) 
					m_EditorCtrl.SetTextToEditor(strConvertedText);
				else
					m_EditorCtrl.ReplaceSelectionWithText(strConvertedText);
			}
			else if (formatText == CONVERT_TEXT_FORMAT::HEXA_TYPE)
			{
				CString strConvertedText = AppUtils::StdToCString(hexa_decode(AppUtils::CStringToStd(stSelectedScript)));
				if (bReplaceSelection == FALSE) 
					m_EditorCtrl.SetTextToEditor(strConvertedText);
				else
					m_EditorCtrl.ReplaceSelectionWithText(strConvertedText);
			}
			else if (formatText == CONVERT_TEXT_FORMAT::DECIMAL_TYPE)
			{
				CString strConvertedText = AppUtils::StdToCString(decimal_decode(AppUtils::CStringToStd(stSelectedScript)));
				if (bReplaceSelection == FALSE) 
					m_EditorCtrl.SetTextToEditor(strConvertedText);
				else
					m_EditorCtrl.ReplaceSelectionWithText(strConvertedText);
			}
			else if (formatText == CONVERT_TEXT_FORMAT::BINARY_TYPE)
			{
				CString strConvertedText = AppUtils::StdToCString(binary_decode(AppUtils::CStringToStd(stSelectedScript)));
				if (bReplaceSelection == FALSE) 
					m_EditorCtrl.SetTextToEditor(strConvertedText);
				else
					m_EditorCtrl.ReplaceSelectionWithText(strConvertedText);
			}
			else if (formatText == CONVERT_TEXT_FORMAT::OCTA_TYPE)
			{
				CString strConvertedText = AppUtils::StdToCString(octa_decode(AppUtils::CStringToStd(stSelectedScript)));
				if (bReplaceSelection == FALSE) 
					m_EditorCtrl.SetTextToEditor(strConvertedText);
				else
					m_EditorCtrl.ReplaceSelectionWithText(strConvertedText);
			}
		}
		m_EditorCtrl.EndUndoTransactions();
	}
	m_EditorCtrl.SetFirstVisibleLine(nVisualLine);
}

void CEditorView::OnOptionsEncodeToBase64()
{
	DoConvertTextFormat(CONVERT_TEXT_FORMAT::BASE64_TYPE, TRUE);
}

void CEditorView::OnOptionsDecodeFromBase64()
{
	DoConvertTextFormat(CONVERT_TEXT_FORMAT::BASE64_TYPE, FALSE);
}

void CEditorView::OnOptionsEncodeToHexa()
{
	DoConvertTextFormat(CONVERT_TEXT_FORMAT::HEXA_TYPE, TRUE);
}

void CEditorView::OnOptionsDecodeFromHexa()
{
	DoConvertTextFormat(CONVERT_TEXT_FORMAT::HEXA_TYPE, FALSE);
}

void CEditorView::OnOptionsEncodeToDecimal()
{
	DoConvertTextFormat(CONVERT_TEXT_FORMAT::DECIMAL_TYPE, TRUE);
}

void CEditorView::OnOptionsDecodeFromDecimal()
{
	DoConvertTextFormat(CONVERT_TEXT_FORMAT::DECIMAL_TYPE, FALSE);
}

void CEditorView::OnOptionsEncodeToBinary()
{
	DoConvertTextFormat(CONVERT_TEXT_FORMAT::BINARY_TYPE, TRUE);
}

void CEditorView::OnOptionsDecodeFromBinary()
{
	DoConvertTextFormat(CONVERT_TEXT_FORMAT::BINARY_TYPE, FALSE);
}

void CEditorView::OnOptionsEncodeToOcta()
{
	DoConvertTextFormat(CONVERT_TEXT_FORMAT::OCTA_TYPE, TRUE);
}

void CEditorView::OnOptionsDecodeFromOcta()
{
	DoConvertTextFormat(CONVERT_TEXT_FORMAT::OCTA_TYPE, FALSE);
}

void CEditorView::OnOptionsDeleteLeftWord()
{
	m_EditorCtrl.DoCommand(SCI_DELWORDLEFT);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsDeleteRightWord()
{
	m_EditorCtrl.DoCommand(SCI_DELWORDRIGHT);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsDeleteToBeginLine()
{
	m_EditorCtrl.DoCommand(SCI_DELLINERIGHT);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsDeleteToEndLine()
{
	m_EditorCtrl.DoCommand(SCI_DELLINERIGHT);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsLineTranspose()
{
	m_EditorCtrl.DoCommand(SCI_LINETRANSPOSE);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsSplitSelectionIntoLines()
{
	if (m_EditorCtrl.GetSelectionNumber() == SINGLE_SELECTION)
	{
		int lStartSelectionPos = m_EditorCtrl.GetSelectionStartPosition();
		int lEndSelectionPos = m_EditorCtrl.GetSelectionEndPosition();
		int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartSelectionPos);
		int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndSelectionPos);
		int nLines = lLineEnd - lLineStart + 1;
		if (nLines == 1) return;
		for (int nLine = lLineStart; nLine <= lLineEnd; ++nLine)
		{
			int lEndLinePos = m_EditorCtrl.GetLineEndPosition(nLine);
			int lStartLinePos = m_EditorCtrl.GetLineStartPosition(nLine);
			m_EditorCtrl.DoCommand(SCI_ADDSELECTION, lEndLinePos, lStartLinePos);
		}
		if (nLines != m_EditorCtrl.GetSelectionNumber())
		{
			m_EditorCtrl.DoCommand(SCI_DROPSELECTIONN, 0, 0);
		}
		m_EditorCtrl.UpdateMainSelectionInCurrentView();
		m_EditorCtrl.SetFocus();
	}
}

void CEditorView::OnOptionsSelectionAddPreviousLine()
{
	if (m_EditorCtrl.GetSelectionNumber() == SINGLE_SELECTION)
	{
		m_LineMultipleCaretsBuffer.clear();
		m_nOriginalMultiCaretColumn = m_EditorCtrl.GetCurrentColumn();
	}
	int lCurrentLine = m_EditorCtrl.GetCurrentLine();
	m_LineMultipleCaretsBuffer.push_back(lCurrentLine);
	for (auto const& line : m_LineMultipleCaretsBuffer)
	{
		if (lCurrentLine == line)
		{
			lCurrentLine = *std::min_element(m_LineMultipleCaretsBuffer.begin(), m_LineMultipleCaretsBuffer.end());
			break;
		}
	}
	int lPreviousLineStartPos = m_EditorCtrl.GetLineStartPosition(lCurrentLine - 2);
	int lPreviousLineEndPos = m_EditorCtrl.GetLineEndPosition(lCurrentLine - 2);
	if (m_nOriginalMultiCaretColumn > 0)
	{
		while (true)
		{
			lPreviousLineStartPos++;
			if (lPreviousLineStartPos >= lPreviousLineEndPos)
			{
				lPreviousLineStartPos = lPreviousLineEndPos;
				break;
			}
			int lColumn = m_EditorCtrl.GetColumnAtPosition(lPreviousLineStartPos);
			if (lColumn == m_nOriginalMultiCaretColumn) break;
		}
	}
	m_EditorCtrl.DoCommand(SCI_ADDSELECTION, lPreviousLineStartPos, lPreviousLineStartPos);
	m_EditorCtrl.SetLineCenterBackwardDisplay(lCurrentLine - 2);
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsSelectionAddNextLine()
{
	if (m_EditorCtrl.GetSelectionNumber() == SINGLE_SELECTION)
	{
		m_LineMultipleCaretsBuffer.clear();
		m_nOriginalMultiCaretColumn = m_EditorCtrl.GetCurrentColumn();
	}
	int lCurrentLine = m_EditorCtrl.GetCurrentLine();
	m_LineMultipleCaretsBuffer.push_back(lCurrentLine);
	for (auto const& line : m_LineMultipleCaretsBuffer)
	{
		if (lCurrentLine == line)
		{
			lCurrentLine = *std::max_element(m_LineMultipleCaretsBuffer.begin(), m_LineMultipleCaretsBuffer.end());
			break;
		}
	}
	int llNextStartPos = m_EditorCtrl.GetLineStartPosition(lCurrentLine);
	int lNextLineEndPos = m_EditorCtrl.GetLineEndPosition(lCurrentLine);
	if (m_nOriginalMultiCaretColumn > 0)
	{
		while (true)
		{
			llNextStartPos++;
			if (llNextStartPos >= lNextLineEndPos)
			{
				llNextStartPos = lNextLineEndPos;
				break;
			}
			int lColumn = m_EditorCtrl.GetColumnAtPosition(llNextStartPos);
			if (lColumn == m_nOriginalMultiCaretColumn) break;
		}
	}
	if (llNextStartPos <= m_EditorCtrl.GetTextLength() && lCurrentLine != m_EditorCtrl.GetLineEnd() + 1)
	{
		m_EditorCtrl.DoCommand(SCI_ADDSELECTION, llNextStartPos, llNextStartPos);
		m_EditorCtrl.SetLineCenterKeepView(lCurrentLine);
	}
	m_EditorCtrl.SetFocus();
}

void CEditorView::OnOptionsSelectionInvert()
{
	int nSelNumber = m_EditorCtrl.GetSelectionNumber();
	if (nSelNumber == 1)
	{
		int lCurPos = m_EditorCtrl.GetCurrentPosition();
		int lCurAnchor = m_EditorCtrl.GetCurrentAnchor();
		if (lCurPos >= lCurAnchor)
		{
			m_EditorCtrl.DoCommand(SCI_ADDSELECTION, lCurAnchor, 0);
			m_EditorCtrl.DoCommand(SCI_ADDSELECTION, m_EditorCtrl.GetTextLength(), lCurPos);
		}
		else
		{
			m_EditorCtrl.DoCommand(SCI_ADDSELECTION, lCurPos, 0);
			m_EditorCtrl.DoCommand(SCI_ADDSELECTION, m_EditorCtrl.GetTextLength(), lCurAnchor);
		}
		m_EditorCtrl.DoCommand(SCI_DROPSELECTIONN, 0, 0);
	}
	else if (nSelNumber > 1)
	{
		AfxMessageBox(_T("Invert selection only support for single selection."), MB_ICONINFORMATION);
	}
	m_EditorCtrl.SetFocus();
}

void CEditorView::TextAlignment(CTextAlignment::Alignment option)
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stScript, strNewScripts;
	m_EditorCtrl.GetText(stScript);
	if (!stScript.IsEmpty())
	{
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		if (stSelectedScript.IsEmpty())
		{
			std::vector<CString> listLine;
			listLine.reserve(m_EditorCtrl.GetLineCount());
			AppUtils::SplitFileContent(stScript, m_EditorCtrl.GetEOLCString(), listLine);
			CTextAlignment textAlignment;
			for (const auto& line : listLine)
			{
				CString strAlignedText = AppUtils::WStdToCString(textAlignment.AlignText(AppUtils::CStringToWStd(line), option,
					AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())));
				strNewScripts += strAlignedText + m_EditorCtrl.GetEOLCString();
			}
			m_EditorCtrl.SetTextToEditor(strNewScripts.Mid(0, strNewScripts.GetLength()));
		}
		else
		{
			int lStartPos = m_EditorCtrl.GetSelectionStartPosition();
			int lEndPos = m_EditorCtrl.GetSelectionEndPosition();
			int lLineStart = m_EditorCtrl.GetLineFromPosition(lStartPos);
			int lLineEnd = m_EditorCtrl.GetLineFromPosition(lEndPos);
			int StartLinePos = m_EditorCtrl.GetLineStartPosition(lLineStart);
			int EndLinePos = m_EditorCtrl.GetLineEndPosition(lLineEnd);
			CTextAlignment textAlignment;
			for (int i = lLineStart; i <= lLineEnd; ++i)
			{
				CString strCurLineText;
				m_EditorCtrl.GetTextFromLine(i + 1, strCurLineText);
				CString strAlignedText = AppUtils::WStdToCString(textAlignment.AlignText(AppUtils::CStringToWStd(strCurLineText), option,
					AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())));
				strNewScripts += strAlignedText + m_EditorCtrl.GetEOLCString();
			}
			m_EditorCtrl.SetStartSelection(StartLinePos);
			m_EditorCtrl.SetEndSelection(EndLinePos);
			m_EditorCtrl.ReplaceSelectionWithText(strNewScripts.Mid(0, strNewScripts.GetLength()));
		}
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Line Alignment] Aligned line(s) with maximum length %d..."), AppSettingMgr.m_nPageAlignmentWidth);
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::TextAlignmentNotKeepLine(CTextAlignment::Alignment option)
{
	BACKUP_VISIBLE_EDITOR_STATE_EDIT
	CString stScript;
	m_EditorCtrl.GetText(stScript);
	if (!stScript.IsEmpty())
	{
		CTextAlignment textAlignment;
		CString stSelectedScript = m_EditorCtrl.GetSelectedText();
		if (stSelectedScript.IsEmpty())
		{
			CString strAlignedText = AppUtils::WStdToCString(textAlignment.AlignText(AppUtils::CStringToWStd(stScript), option,
				AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())));
			m_EditorCtrl.SetTextToEditor(strAlignedText);
		}
		else
		{
			CString strAlignedText = AppUtils::WStdToCString(textAlignment.AlignText(AppUtils::CStringToWStd(stSelectedScript), option,
				AppUtils::CStringToWStd(m_EditorCtrl.GetEOLCString())));
			m_EditorCtrl.ReplaceSelectionWithText(strAlignedText);
		}
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [File Alignment] Aligned line(s) with maximum length %d..."), AppSettingMgr.m_nPageAlignmentWidth);
	}
	RESTORE_VISIBLE_EDITOR_STATE_EDIT
}

void CEditorView::OnOptionAlignLeft()
{
	TextAlignment(CTextAlignment::Alignment::Left);
}

void CEditorView::OnOptionAlignRight()
{
	TextAlignment(CTextAlignment::Alignment::Right);
}

void CEditorView::OnOptionAlignCenter()
{
	TextAlignment(CTextAlignment::Alignment::Center);
}

void CEditorView::OnOptionAlignJustify()
{
	TextAlignment(CTextAlignment::Alignment::Justify);
}

void CEditorView::OnOptionAlignLeftNotKeepLine()
{
	TextAlignmentNotKeepLine(CTextAlignment::Alignment::Left);
}

void CEditorView::OnOptionAlignRightNotKeepLine()
{
	TextAlignmentNotKeepLine(CTextAlignment::Alignment::Right);
}

void CEditorView::OnOptionAlignCenterNotKeepLine()
{
	TextAlignmentNotKeepLine(CTextAlignment::Alignment::Center);
}

void CEditorView::OnOptionAlignJustifyNotKeepLine()
{
	TextAlignmentNotKeepLine(CTextAlignment::Alignment::Justify);
}

void CEditorView::OnOptionsSwapTwoSelections()
{
	int nSelections = m_EditorCtrl.GetSelectionNumber();

	if (nSelections == 2) // only support swap 2 selections
	{
		int nSelectionStart1 = m_EditorCtrl.GetMultiSelectionStart(0);
		int nSelectionStart2 = m_EditorCtrl.GetMultiSelectionStart(1);
		int nSelectionEnd1 = m_EditorCtrl.GetMultiSelectionEnd(0);
		int nSelectionEnd2 = m_EditorCtrl.GetMultiSelectionEnd(1);

		m_EditorCtrl.BeginUndoTransactions();

		CString strSelectedText1;
		m_EditorCtrl.GetTextRange(strSelectedText1, nSelectionStart1, nSelectionEnd1);
		CString strSelectedText2;
		m_EditorCtrl.GetTextRange(strSelectedText2, nSelectionStart2, nSelectionEnd2);

		m_EditorCtrl.RemoveTextRange(nSelectionStart1, nSelectionEnd1 - nSelectionStart1);
		m_EditorCtrl.RemoveTextRange(nSelectionStart2 - (nSelectionEnd1 - nSelectionStart1), nSelectionEnd2 - nSelectionStart2);

		int lSelectionCaretPosN1 = m_EditorCtrl.GetSelectionNumberCaret(0);
		m_EditorCtrl.InsertTextAtSelectionNumber(strSelectedText2, lSelectionCaretPosN1);

		int lSelectionCaretPosN2 = m_EditorCtrl.GetSelectionNumberCaret(1);
		m_EditorCtrl.InsertTextAtSelectionNumber(strSelectedText1, lSelectionCaretPosN2);

		m_EditorCtrl.DoCommand(SCI_ADDSELECTION, lSelectionCaretPosN1 + strSelectedText2.GetLength(), lSelectionCaretPosN1);
		m_EditorCtrl.DoCommand(SCI_ADDSELECTION, lSelectionCaretPosN2 + strSelectedText1.GetLength(), lSelectionCaretPosN2);

		m_EditorCtrl.EndUndoTransactions();
	}
	else
	{
		AfxMessageBox(_T("This operation need to have 2 selections!"));
	}
}

void CEditorView::OpenFileLanguageConfig(const CString& czLexerName)
{
	CString languageSettingPath = PathUtils::GetLanguageSettingFilePath(czLexerName);
	if (PathFileExists(languageSettingPath))
	{
		AppUtils::CreateDocumentFromFile(languageSettingPath);
	}
	else
	{
		AfxMessageBoxFormat(MB_ICONWARNING, _T("[Path Error] \"%s\" does not exist!\n"), languageSettingPath);
	}
}

void CEditorView::OnTerminalRunActiveFile()
{
	if (PathFileExists(m_pDocument->GetPathName()))
	{
		CString strFullCmd = _T("start \"\" \"CMD \" /c \"") + m_pDocument->GetPathName() + _T("\" ^& pause");
		OSUtils::RunSystemCMD(strFullCmd);
	}
}

void CEditorView::OnUpdateTerminalRunActiveFile(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(PathFileExists(m_pDocument->GetPathName()));
}

void CEditorView::OnTerminalRunActiveFileAsAdmin()
{
	if (PathFileExists(m_pDocument->GetPathName()))
	{
		CString strFullCmd = _T("start \"\" \"CMD \" /c \"") + m_pDocument->GetPathName() + _T("\"");
		OSUtils::RunSystemCMD(strFullCmd);
	}
}

void CEditorView::OnUpdateTerminalRunActiveFileAsAdmin(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(PathFileExists(m_pDocument->GetPathName()));
}

void CEditorView::OnTerminalRunSelectedText()
{
	CString strSelectedText = m_EditorCtrl.GetSelectedText();
	strSelectedText.Replace(_T("\r"), _T(""));
	strSelectedText.Replace(_T("\n"), _T(""));
	if (!strSelectedText.IsEmpty())
	{
		OSUtils::CreateWin32Process(strSelectedText);
	}
}

void CEditorView::OnUpdateTerminalRunSelectedText(CCmdUI * pCmdUI)
{
	if (m_EditorCtrl.GetSelectedText().IsEmpty())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CEditorView::OnOpenFileLanguageConfigCShape()
{
	OpenFileLanguageConfig(_T("cs"));
}

void CEditorView::OnOpenFileLanguageConfigJava()
{
	OpenFileLanguageConfig(_T("java"));
}

void CEditorView::OnOpenFileLanguageConfigAssembly()
{
	OpenFileLanguageConfig(_T("asm"));
}

void CEditorView::OnOpenFileLanguageConfigBatch()
{
	OpenFileLanguageConfig(_T("bash"));
}

void CEditorView::OnOpenFileLanguageConfigPascal()
{
	OpenFileLanguageConfig(_T("pascal"));
}

void CEditorView::OnOpenFileLanguageConfigSQL()
{
	OpenFileLanguageConfig(_T("sql"));
}

void CEditorView::OnOpenFileLanguageConfigPerl()
{
	OpenFileLanguageConfig(_T("perl"));
}

void CEditorView::OnOpenFileLanguageConfigPHP()
{
	OpenFileLanguageConfig(_T("php"));
}

void CEditorView::OnOpenFileLanguageConfigPowerShell()
{
	OpenFileLanguageConfig(_T("powershell"));
}

void CEditorView::OnOpenFileLanguageConfigVerilog()
{
	OpenFileLanguageConfig(_T("verilog"));
}

void CEditorView::OnOpenFileLanguageConfigRuby()
{
	OpenFileLanguageConfig(_T("ruby"));
}

void CEditorView::OnOpenFileLanguageConfigGo()
{
	OpenFileLanguageConfig(_T("go"));
}

void CEditorView::OnOpenFileLanguageConfigTCL()
{
	OpenFileLanguageConfig(_T("tcl"));
}

void CEditorView::OnOpenFileLanguageConfigAutoIT()
{
	OpenFileLanguageConfig(_T("autoit"));
}

void CEditorView::OnOpenFileLanguageConfigR()
{
	OpenFileLanguageConfig(_T("r"));
}

void CEditorView::OnOpenFileLanguageConfigRust()
{
	OpenFileLanguageConfig(_T("rust"));
}

void CEditorView::OnOpenFileLanguageConfigVisualBasic()
{
	OpenFileLanguageConfig(_T("vb"));
}

void CEditorView::OnOpenFileLanguageConfigFreeBasic()
{
	OpenFileLanguageConfig(_T("freebasic"));
}

void CEditorView::OnOpenFileLanguageConfigPython()
{
	OpenFileLanguageConfig(_T("python"));
}

void CEditorView::OnOpenFileLanguageConfigHTML()
{
	OpenFileLanguageConfig(_T("html"));
}

void CEditorView::OnOpenFileLanguageConfigCPP()
{
	OpenFileLanguageConfig(_T("cpp"));
}

void CEditorView::OnOpenFileLanguageConfigJavaScript()
{
	OpenFileLanguageConfig(_T("javascript"));
}

void CEditorView::OnOpenFileLanguageConfigC()
{
	OpenFileLanguageConfig(_T("c"));
}