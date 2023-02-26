/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "EditorCommonDef.h"

/////////////////////////////////////////////////////////////////////////////

struct FoldingBracketsData
{
	long _line;
	long _folderLevel;

	FoldingBracketsData(long line, long folderLevel)
	{
		_line = line;
		_folderLevel = folderLevel;
	}

	// for sorting by _folderLevel
	bool operator < (const FoldingBracketsData& data) const
	{
		return this->_folderLevel < data._folderLevel;
	}
};

inline bool operator != (const FoldingBracketsData& lhs, const FoldingBracketsData& rhs)
{
	return lhs._line == lhs._line && lhs._folderLevel == lhs._folderLevel;
}

typedef std::vector<std::vector<FoldingBracketsData>> BracketsDataGroup;

/////////////////////////////////////////////////////////////////////////////

struct FoldingLineData
{
	long _lineNumber;
	CString _lineText;
	FoldingLineData(long lineNumber, CString lineText)
	{
		_lineNumber = lineNumber;
		_lineText = lineText;
	}
};

typedef std::vector<FoldingLineData> FoldingLineDataList;

/////////////////////////////////////////////////////////////////////////////

struct XmlHtmlTagsPosition
{
	sptr_t tagOpenStart;
	sptr_t tagNameEnd;
	sptr_t tagOpenEnd;
	sptr_t tagCloseStart;
	sptr_t tagCloseEnd;
};

/////////////////////////////////////////////////////////////////////////////

struct SearchResult
{
	sptr_t start;
	sptr_t end;
	bool   success;
};

/////////////////////////////////////////////////////////////////////////////

class FoldingLevelStack
{
public:
	int levelCount = 0; // 1-based level number
	int levelStack[12]{};

	void push(int level)
	{
		while (levelCount != 0 && level <= levelStack[levelCount - 1])
		{
			--levelCount;
		}
		if (levelCount > (_countof(levelStack) - 1))
			return;
		levelStack[levelCount++] = level;
	}
};

/////////////////////////////////////////////////////////////////////////////

typedef std::vector<Sci_Position> arrayPosition;

struct UndoRedoSelection
{
	int selMode_undo = SC_SEL_STREAM;
	arrayPosition anchorPos_undo;
	arrayPosition curPos_undo;
	arrayPosition anchorVS_undo;
	arrayPosition curVS_undo;

	int selMode_redo = SC_SEL_STREAM;
	arrayPosition anchorPos_redo;
	arrayPosition curPos_redo;
	arrayPosition anchorVS_redo;
	arrayPosition curVS_redo;

	UndoRedoSelection() : selMode_undo(SC_SEL_STREAM), selMode_redo(SC_SEL_STREAM) {}

	BOOL IsEmpty()
	{
		return selMode_redo == 0 && selMode_undo == 0;
	}
};

typedef std::unordered_map<unsigned int, UndoRedoSelection> MapUndoRedoSelection;

inline Sci_Position array_front(const arrayPosition& arr)
{
	if (arr.size() > 0)
	{
		return arr.front();
	}
	else
	{
		return 0;
	}
}

inline Sci_Position array_eltptr(const arrayPosition& arr, unsigned int i)
{
	if (arr.size() > 0)
	{
		return arr[i];
	}
	else
	{
		return 0;
	}
}

#define array_len(arr) static_cast<Sci_PositionU>(arr.size())

#define array_push_back(arr, i) arr.push_back(i)

/////////////////////////////////////////////////////////////////////////////

struct RecentEditorInfo
{
	int _nFirstVisibleLine;
	int _nCurrentPosition;
	int _nWrapMode;
	RecentEditorInfo() : _nFirstVisibleLine(0), _nCurrentPosition(0), _nWrapMode(0) {}
};

/////////////////////////////////////////////////////////////////////////////

struct BOOKMARK_LINE_DATA
{
	CString _strTargetFile;
	CString _strLine;
	int _nLineNumber;
	BOOL _bDeleteFromList;
	BOOKMARK_LINE_DATA() :
		_nLineNumber(0),
		_bDeleteFromList(FALSE),
		_strTargetFile(_T("")),
		_strLine(_T("")) {}
};

typedef std::vector<BOOKMARK_LINE_DATA> BOOKMARK_LINE_DATA_LIST;

/////////////////////////////////////////////////////////////////////////////

struct BREAKPOINT_LINE_DATA
{
	CString _strTargetFile;
	CString _strLine;
	CString _strTargetLanguage;
	CString _strProcessName;
	BOOL _bDeleteFromList;
	int _nLineNumber;
	BREAKPOINT_LINE_DATA() :
		_nLineNumber(0),
		_bDeleteFromList(FALSE),
		_strTargetFile(_T("")),
		_strTargetLanguage(_T("")),
		_strProcessName(_T("")),
		_strLine(_T("")) {}
};

typedef std::vector<BREAKPOINT_LINE_DATA> BREAKPOINT_LINE_DATA_LIST;

/////////////////////////////////////////////////////////////////////////////

constexpr int ReadBlockSize = 128 * 1024; //128 kB
constexpr int WriteBlockSize = 128 * 1024; //128 kB

enum class EOLFormat : int
{
	Unknown_Format,
	Win_Format,
	Mac_Format,
	Unix_Format
};
enum class TabSpace : int
{
	Default,
	Tabs,
	Spaces
};

enum class ReadDirection : int
{
	Disabled,
	L2R,
	R2L
};

/////////////////////////////////////////////////////////////////////////////

typedef sptr_t(*DirectFunc) (void *, unsigned int, uptr_t, sptr_t);
typedef void * DirectPtr;

/////////////////////////////////////////////////////////////////////////////

struct EditorThemeColorSet
{
	COLORREF _lineNumberColor{ 0 };
	COLORREF _selectionTextColor{ 0 };
	COLORREF _editorTextColor{ 0 };
	COLORREF _editorMarginBarColor{ 0 };
	COLORREF _editorFolderBackColor{ 0 };
	COLORREF _editorFolderForeColor{ 0 };
	COLORREF _editorCaretColor{ 0 };
	COLORREF _editorIndicatorColor{ 0 };
	COLORREF _editorSpellCheckColor{ 0 };
	COLORREF _editorTagMatchColor{ 0 };
};