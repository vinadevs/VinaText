/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "stdafx.h"

#include <scintilla\ILexer.h>
#include <scintilla\Lexilla.h>
#include <scintilla\Scintilla.h>
#include <scintilla\SciLexer.h>
#include <scintilla\ILoader.h>

//----------------------------------------------------------------------------
// In-house definitions, not from Scintilla
//----------------------------------------------------------------------------

#define STR_SCINTILLAWND _T("Scintilla")
#define STR_EDITORDLL     _T("VinaTextEditor.dll")
#define STR_LEXERDLL      _T("VinaTextLexer.dll")
#define LEXER_PLAIN_TEXT  _T("plaintext")
#define FOLDED_MARKER_TEXT	  " --- "
#define FOLDED_MARKER_CPP	  " { ... } "
#define FOLDED_MARKER_HTML	  " < ... > "
#define IMAGE_AUTOCSETSEPARATOR '?'
#define WORD_AUTOCSETSEPARATOR '$'
#define SC_SETMARGINTYPE_LINENUM 0
#define SC_SETMARGINTYPE_MAKER 1
#define SC_SETMARGINTYPE_FOLDING 2
#define SC_MARKER_ENABLE_BREAKPOINT 0
#define SC_MARKER_DISABLE_BREAKPOINT 1
#define SC_MARKER_INSTRUCTION_POINTER 2
#define SC_MARKER_BOOKMARK 3
#define SC_MARKER_FOLDING 4
#define SC_MARKER_LINE_NUMBER 5
#define SC_CURSOR_RIGHT_HAND 8
#define VINATEXT_MARGINWIDTH 16
#define VINATEXT_MARGINWIDTH 16
#define VINATEXT_MAXIMUM_MARGIN 3
#define SINGLE_SELECTION 1
#define SCROLLING_PIXEL_WIDTH 5
#define INDIC_BRACEMATCH  (INDIC_CONTAINER + 1)
#define INDIC_TAGMATCH    (INDIC_CONTAINER + 2)
#define INDIC_TAGATTR     (INDIC_CONTAINER + 3)
#define INDIC_HIGHLIGHT_PYTHON  (INDIC_CONTAINER + 4)
#define INDIC_HIGHLIGHT_GENERAL (INDIC_CONTAINER + 5)
#define INDIC_URL_HOTSPOT (INDIC_CONTAINER + 6)
#define INDIC_SPELL_CHECKER (INDIC_CONTAINER + 7)
#define SEL_MULTI_MODE (SC_SEL_RECTANGLE + SC_SEL_LINES + SC_SEL_THIN)

#define SCI_MODEVENTMASK_FULL (SC_MOD_CONTAINER | SC_PERFORMED_UNDO | SC_PERFORMED_REDO | SC_MULTILINEUNDOREDO \
        | SC_MOD_INSERTTEXT | SC_MOD_DELETETEXT | SC_MOD_BEFOREINSERT | SC_MOD_BEFOREDELETE \
        | SC_MULTISTEPUNDOREDO | SC_LASTSTEPINUNDOREDO)

#define UNDOREDO_FREE (-1L)
#define UNDOREDO_BLOCKED (-2L)

namespace EditorLanguageDef
{
	//----------------------------------------------------------------------------
	// File extension definitions [MUST BE SAME ORDER WITH LEXER NAME DEFINITIONS]
	//----------------------------------------------------------------------------
	static CString arrLangExtensions[] =
	{
		_T("py|pyw"),				     // SCLEX_PYTHON
		_T("cpp|cxx|h|hh|hpp|hxx"),      // SCLEX_CPP
		_T("ada|ads|adb"),               // SCLEX_ADA
		_T("asm"),                       // SCLEX_ASM
		_T("iss"),                       // SCLEX_INNOSETUP
		_T("sh"),                        // SCLEX_BASH
		_T("bat|cmd|nt"),                // SCLEX_BATCH
		_T("c|cc"),					          // SCLEX_C
		_T("cmake"),				          // SCLEX_CMAKE
		_T("cs"),					                  // SCLEX_CS
		_T("css"),                                    // SCLEX_CSS
		_T("erl|hrl"),				                  // SCLEX_CS
		_T("f|for|f90|f95|f77"),                      // SCLEX_FORTRAN
		_T("htm|html|shtml|htt|cfm|tpl|hta"),         // SCLEX_HTML
		_T("java"),							// SCLEX_CPP
		_T("js|jsx"),							// SCLEX_CPP
		_T("ts|tsx"),							// SCLEX_CPP
		_T("lua"),								// SCLEX_LUA
		_T("m"),                                      // SCLEX_MATLAB// SCLEX_LUA
		_T("pas|inc|pp"),                         // SCLEX_PASCAL
		_T("pl|pm|cgi|pod"),                          // SCLEX_PERL
		_T("php|php3|php4|php5|phps|phpt|phtml"),     // SCLEX_PHP
		_T("ps1|psm1"),								  // SCLEX_POWERSHELL
		_T("rb"),                                     // SCLEX_RUBY
		_T("rs"),                                     // SCLEX_RUST
		_T("sql|spec|body|sps|spb|sf|sp"),            // SCLEX_SQL
		_T("tcl"),                                    // SCLEX_TCL
		_T("vb|vbs|bas|frm|cls|ctl|pag|dsr|dob"),     // SCLEX_VB
		_T("v|sv|vh|svh"),							  //SCLEX_VERILOG
		_T("vhd|vhdl"),								  //SCLEX_VHDL
		_T("xml|gcl|xsl|svg|xul|xsd|dtd|xslt|axl"),   // SCLEX_XML
		_T("json"),								      // SCLEX_JSON
		_T("go"),                                     // SCLEX_GOLANG
		_T("md|markdown|rmd"),						  // SCLEX_MARKDOWN
		_T("proto"),								 //  SCLEX_CPP
		_T("r"),                                     //  SCLEX_R
		_T("lic"),                                   //  SCLEX_PYTHON
		_T("rc"),                                     // SCLEX_CPP
		_T("au3"),                                    // SCLEX_CPP
		0,
	};

	//----------------------------------------------------------------------------
	// Lexer name definitions [MUST BE SAME ORDER WITH FILE EXTENSION DEFINITIONS]
	//----------------------------------------------------------------------------
	static const char* arrLexerNames[] =
	{
		"python",
		"cpp",
		"ada",
		"asm",
		"inno",
		"bash",
		"batch",
		"c",
		"cmake",
		"cs",
		"css",
		"erlang",
		"fortran",
		"hypertext",
		"java",
		"javascript",
		"typescript",
		"lua",
		"matlab",
		"pascal",
		"perl",
		"phpscript",
		"powershell",
		"ruby",
		"rust",
		"sql",
		"tcl",
		"vb",
		"verilog",
		"vhdl",
		"xml",
		"kix",
		"golang",
		"markdown",
		"protobuf",
		"r",
		"FLEXlm",
		"Resource",
		"autoit",
		"plaintext",
		0,
	};
}