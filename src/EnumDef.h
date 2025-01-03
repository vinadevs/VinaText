/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

// log utils
enum class LOG_TARGET : unsigned int
{
	MESSAGE_WINDOW = 1,
	BUILD_WINDOW = 2,
};

// file times
enum class FILE_TIME_PROPERTY : unsigned int
{
	FILE_TIME_CREATED = 1,
	FILE_TIME_LAST_ACCESSED = 2,
	FILE_TIME_LAST_MODIFIED = 3,
};

// file system state
enum FILE_SYSTEM_STATE
{
	FILE_UNCHANGED = 0x001,
	FILE_DELETED = 0x002,
	FILE_CONTENT_MODIFIED = 0x004,
	FILE_CHANGED_READONLY = 0x008,
};

// preview file type
enum BINARY_FILE_TYPE
{
	FILE_BINNARY = 0x0001,
	FILE_MEDIA = 0x0002,
	FILE_IMAGE = 0x0004,
	FILE_PDF = 0x0008,
};

inline BINARY_FILE_TYPE operator | (BINARY_FILE_TYPE a, BINARY_FILE_TYPE b)
{
	return static_cast<BINARY_FILE_TYPE>(static_cast<int>(a) | static_cast<int>(b));
}

// Docking pane types
enum class DOCKABLE_PANE_TYPE : unsigned int
{
	FILE_EXPLORER_PANE = 0,
	LOG_MESSAGE_PANE = 1,
	SEARCH_AND_REPLACE_PANE = 2,
	LEARN_PROGRAMMING_PANE = 3,
	SEARCH_RESULT_PANE = 4,
	BUILD_PANE = 5,
	BOOKMARK_PANE = 6,
	PATH_RESULT_PANE = 7,
	BREAKPOINT_PANE = 8,
};

// Search and replace types
enum class SEARCH_REPLACE_GOTO_DLG_TYPE : unsigned int
{
	SEARCH = 0,
	REPLACE = 1,
	GOTO = 2,
};

// Search types
enum class SEARCH_TYPE : unsigned int
{
	NORMAL = 0,
	MACTCH_WORD = 1,
	MACTCH_CASE = 2,
	REGEX = 3,
};

// VinaText supported languages
enum VINATEXT_SUPPORTED_LANGUAGE
{
	LANGUAGE_START = -1,
	LANGUAGE_TEXT = 0,
	LANGUAGE_PYTHON = 1,
	LANGUAGE_CPP = 2,
	LANGUAGE_C = 3,
	LANGUAGE_JAVASCRIPT = 4,
	LANGUAGE_BATCH = 5,
	LANGUAGE_JAVA = 6,
	LANGUAGE_PASCAL = 7,
	LANGUAGE_ASSEMBLY = 8,
	LANGUAGE_CSHAPE = 9,
	LANGUAGE_PHP = 10,
	LANGUAGE_VISUALBASIC = 11,
	LANGUAGE_SQL = 12,
	LANGUAGE_PERL = 13,
	LANGUAGE_GOLANG = 14,
	LANGUAGE_RUST = 15,
	LANGUAGE_RUBY = 16,
	LANGUAGE_MATLAB = 17,
	LANGUAGE_TCL = 18,
	LANGUAGE_AUTOIT = 19,
	LANGUAGE_R = 20,
	LANGUAGE_VERILOG = 21,
	LANGUAGE_POWERSHELL = 22,
	LANGUAGE_HTML = 23,
	LANGUAGE_XML = 24,
	LANGUAGE_INNOSETTUP = 25,
	LANGUAGE_JSON = 26,
	LANGUAGE_CSS = 27,
	LANGUAGE_MARKDOWN = 28,
	LANGUAGE_TYPESCRIPT = 29,
	LANGUAGE_PROTOBUF = 30,
	LANGUAGE_FLEXLM = 31,
	LANGUAGE_FREEBASIC = 32,
	LANGUAGE_MAKEFILE = 33,
	LANGUAGE_CMAKE = 34,
	LANGUAGE_VCXPROJECT = 34,
	LANGUAGE_END,
};

// block comment action
enum class BLOCK_COMMENT_OPERATION : unsigned int
{
	COMMENT_ACTION = 0,
	UNCOMMENT_ACTION = 1,
	TOGGLE_ACTION = 2,
};

// tree event message
enum TREE_ADVANCE_MESSAGE
{
	MSG_CLICK_CHECKBOX = WM_USER + 200,
	MSG_EXPAND_CHECKBOX,
	MSG_TREE_SELECT_ITEM,
	MSG_TREE_DOUBLE_CLICK,
	MSG_TREE_RIGHT_CLICK,
	MSG_TREE_LEFT_BUTTON_UP,
};

// numeric format
enum class DOUBLE_NUMERIC_TYPE : unsigned int
{
	REAL_TYPE = 0,
	POWER_TYPE = 1,
	SCIENTIFIC_NOTATION_TYPE = 2,
};

// preview type
enum class PREVIEW_TYPE : unsigned int
{
	PREVIEW_EDITOR = 0,
	PREVIEW_IMAGE = 1,
	PREVIEW_PDF = 2,
	PREVIEW_MEDIA = 3,
};

// main frame event message
enum MAIN_FRAME_UPDATE_MSG
{
	MAIN_FRAME_UPDATE_ALL_DOCKPANE = 0,
	MAIN_FRAME_UPDATE_TOOLBAR,
	MAIN_FRAME_UPDATE_BUILD_PANE,
	MAIN_FRAME_UPDATE_EXPLORER_PANE,
	MAIN_FRAME_UPDATE_TEXT_RESULT_PANE,
	MAIN_FRAME_UPDATE_MESSAGE_PANE,
	MAIN_FRAME_UPDATE_SEARCH_AND_REPLACE_PANE,
	MAIN_FRAME_UPDATE_PATH_RESULT_PANE,
	MAIN_FRAME_UPDATE_BOOKMARK_PANE,
	MAIN_FRAME_UPDATE_TEXT_REFERENCE_PANE,
	MAIN_FRAME_UPDATE_BREAKPOINT_PANE,
};

// main frame update hint
enum MAIN_FRAME_UPDATE_HINT
{
	MAIN_FRAME_UPDATE_HINT_SETTING_CHANGED = 0,
	MAIN_FRAME_UPDATE_HINT_EDITOR_DATABASE_CHANGED,
	MAIN_FRAME_UPDATE_HINT_NEW_DOCUMENT,
};

// view update hint
enum VIEW_UPDATE_HINT
{
	VIEW_UPDATE_HINT_SETTING_CHANGED = 0,
	VIEW_UPDATE_HINT_EDITOR_DATABASE_CHANGED,
	VIEW_UPDATE_HINT_NEW_DOCUMENT,
};

// editor text format
enum CONVERT_TEXT_FORMAT
{
	BASE64_TYPE,
	HEXA_TYPE,
	DECIMAL_TYPE,
	BINARY_TYPE,
	OCTA_TYPE,
	MD5_TYPE,
	SHA256_TYPE,
	SHA1_TYPE,
	CRC_TYPE,
};

// MDI document type
enum DOCUMENT_TYPE
{
	DOC_EDITOR = 0,
	DOC_IMAGE = 1,
	DOC_PDF = 2,
	DOC_MEDIA = 3,
	DOC_HOST = 4,
	DOC_EXPLORER = 5,
	DOC_ALL = 6,
};

// win process type
enum PROCESS_WIN32_STATUS
{
	PROCESS_STOPPED = 0,
	PROCESS_RUNNING,
};

// Sort line options
enum class SORT_LINE_OPT : unsigned int
{
	ASCENDING = 0,
	DESCENDING,
	FROMATOZ,
	FROMZTOA,
};

enum FOLDER_MARGIN_STYPE
{
	STYLE_ARROW = 0,
	STYLE_PLUS_MINUS,
	STYLE_TREE_CIRCLE,
	STYLE_TREE_BOX,
};

enum EDITOR_TAB_ACTIVE_COLOR
{
	MDITAB_ACTIVE_COLOR_GRAY = RGB(230, 230, 230),
	MDITAB_ACTIVE_COLOR_GREEN = RGB(166, 226, 46),
	MDITAB_ACTIVE_COLOR_YELLOW = RGB(230, 219, 116),
	MDITAB_NON_ACTIVE_COLOR = RGB(180, 180, 180),
};

enum EDITOR_THEME_BACKGROUND_COLOR
{
	THEME_BACKGROUND_COLOR_SIERRA_BLUE = RGB(39, 50, 50), // sierra blue
	THEME_BACKGROUND_COLOR_MONOKAI = RGB(39, 40, 34), // monokai
	THEME_BACKGROUND_COLOR_LIGHT = RGB(255, 255, 255), // light
};

enum APPLICATION_THEME_LOOK
{
	THEME_OFFICE_2003 = 0,
	THEME_VISUAL_STUDIO_2005,
	THEME_WINDOWS_XP_NATIVE,
	THEME_OFFICE_2007_AQUA,
	THEME_OFFICE_2007_OBSIDIAN_BLACK,
	THEME_OFFICE_2007_SILVER_LOOK,
	THEME_OFFICE_2007_LUNA_BLUE,
	THEME_VISUAL_STUDIO_2008_LOOK,
};

enum EDITOR_INDICATOR_COLOR
{
	INDICATOR_YELLOW = RGB(235, 245, 0),
	INDICATOR_BLUE = RGB(20, 135, 226),
	INDICATOR_ORANGE = RGB(255, 69, 0),
};

enum EDITOR_INDICATOR_STYLE
{
	BOX = 0,
	FULL_BOX = 1,
};

enum RENDER_INDICATOR_ACTION
{
	SINGLE_CLICK_ACTION = 0,
	DOUBLE_CLICK_ACTION = 1,
};

enum EDITOR_CARET_BLINK_COLOR
{
	BLINK_COLOR_WHITE = RGB(255, 255, 255),
	BLINK_COLOR_ORRANGE = RGB(255, 69, 0),
	BLINK_COLORR_GREEN = RGB(0, 255, 0),
	BLINK_COLOR_YELLOW = RGB(235, 245, 0),
	BLINK_COLOR_RED = RGB(255, 0, 0),
	BLINK_COLOR_BLACK = RGB(0, 0, 0),
};

enum VINATEXT_TEXT_FONT
{
	TOHOMA,
	CONSOLAS,
	COURIER_NEW,
};

enum VINATEXT_DISPLAY_LANGUAGE
{
	LANGUAGE_UNKNOWN = 0,
	LANGUAGE_ENGLISH = 1,
	LANGUAGE_VIETNAMESE = 2,
};

enum DEFAULT_TOOLBAR_TERMINAL
{
	MS_CMD,
	MS_POWERSHELL,
	LINUX_WSL,
};