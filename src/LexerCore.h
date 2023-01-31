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

namespace EditorRules
{
	//----------------------------------------------------------------------------
	// File extension definitions [MUST BE SAME ORDER WITH LEXER NAME DEFINITIONS]
	//----------------------------------------------------------------------------
	static CString strLangExtensions[] =
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

	//----------------------------------------------------------------------------
	// Color definitions
	//----------------------------------------------------------------------------
	struct SScintillaColors
	{
		int			iItem;
		COLORREF	rgb;
	};

	// reference color
	const COLORREF black = RGB(0, 0, 0);
	const COLORREF darkslategray = RGB(47, 79, 79);
	const COLORREF visualBackground = RGB(39, 50, 50);
	const COLORREF visualForeground = RGB(220, 220, 220);
	const COLORREF foregroundMonokai = RGB(248, 248, 240);
	const COLORREF linenumberLight = RGB(200, 200, 200);
	const COLORREF linenumberDark = RGB(0, 0, 0);
	const COLORREF visualCommentColor = RGB(87, 166, 74);
	const COLORREF visualStringColor = RGB(214, 157, 133);
	const COLORREF white = RGB(255, 255, 255);
	const COLORREF navajowhite = RGB(255, 222, 173);
	const COLORREF darkgray = RGB(30, 30, 30);
	const COLORREF gray = RGB(128, 128, 128);
	const COLORREF green = RGB(0, 255, 0);
	const COLORREF springgreen = RGB(0, 255, 127);
	const COLORREF red = RGB(255, 0, 0);
	const COLORREF orangered = RGB(255, 69, 0);
	const COLORREF blue = RGB(0, 0, 255);
	const COLORREF blueviolet = RGB(138, 43, 226);
	const COLORREF yellow = RGB(235, 245, 0);
	const COLORREF olive = RGB(128, 128, 0);
	const COLORREF magenta = RGB(255, 0, 255);
	const COLORREF peachpuff = RGB(255, 200, 185);
	const COLORREF cyan = RGB(0, 255, 255);
	const COLORREF teal = RGB(0, 128, 128);
	const COLORREF darkorange = RGB(255, 140, 0);
	const COLORREF coral = RGB(255, 127, 80);
	const COLORREF yellowgreen = RGB(154, 205, 50);
	const COLORREF indigo = RGB(75, 0, 130);

	// main text color
	const COLORREF keyword = RGB(255, 40, 120); // Red
	const COLORREF definition = RGB(0, 255, 0); // Green
	const COLORREF comment = RGB(166, 226, 46);
	const COLORREF comment_monokai = RGB(170, 170, 170);
	const COLORREF string = RGB(230, 159, 102); // orange
	const COLORREF background_editor = RGB(39, 50, 50);
	const COLORREF currentline = RGB(249, 38, 114);
	const COLORREF builtin = RGB(102, 217, 239); // Blue
	const COLORREF number = RGB(174, 129, 255); // Purple
	const COLORREF instance = RGB(146, 73, 0);
	const COLORREF Orange = RGB(253, 151, 31);
	const COLORREF light_orange = RGB(255, 140, 0);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------------------------
	//---- plain text
	//----------------------------------------------------------------------------
	// language
	static CString g_str_plantext= _T("plain text");

	//----------------------------------------------------------------------------
	//---- cpp Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_cpp_language = _T("cpp");
	// extentions
	static CString g_str_cpp_extention = _T("cpp");
	// comment line
	static CString g_str_cpp_commentline = _T("//");
	// comment start
	static CString g_str_cpp_commentStart = _T("/*");
	// comment end
	static CString g_str_cpp_commentEnd = _T("*/");
	//  keywords
	static const char* g_cpp_KeyWords =
		"asm auto bool break case catch char class const "
		"const_cast continue default delete do double "
		"dynamic_cast else enum explicit extern false finally "
		"float for friend goto if inline int long mutable "
		"namespace new operator private protected public "
		"register reinterpret_cast register return short signed "
		"sizeof static static_cast struct switch template "
		"this throw true try typedef typeid typename "
		"union unsigned using virtual void volatile "
		"wchar_t while elif endif ifdef ifndef define undef "
		"array bitset deque forward_list list map queue set stack unordered_map "
		"unordered_set vector atomic condition_variable future mutex thread algorithm "
		"chrono static_assert ifstream ofstream wfilebuf wfstream wifstream wofstream "
		"close is_open open rdbuf in string "
		"out binary ate app trunc basic_istringstream basic_ostringstream basic_stringbuf "
		"basic_stringstream istringstream ostringstream stringbuf stringstream wistringstream "
		"wostringstream wstringbuf wstringstream "
		"__asm __asume __based __box __cdecl __declspec "
		"__delegate delegate depreciated dllexport dllimport "
		"event __event __except __fastcall __finally __forceinline "
		"__int8 __int16 __int32 __int64 __int128 __interface "
		"interface __leave naked noinline __noop noreturn "
		"nothrow novtable NULL safecast __stdcall "
		"__try __except __finally __unaligned uuid __uuidof "
		"__virtual_inheritance ";
	// text color 
	static SScintillaColors g_rgb_Syntax_cpp[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			definition },
	{ SCE_C_UUID,				instance },
	{ SCE_C_PREPROCESSOR,				comment_monokai },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				instance },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				comment },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- python Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_python_language = _T("python");
	// extentions
	static CString g_str_python_extention = _T("py");
	// comment line
	static CString g_str_python_commentline = _T("#");
	// comment start
	static CString g_str_python_commentStart = _T("");
	// comment end
	static CString g_str_python_commentEnd = _T("");
	// keywords
	static const char* g_python_KeyWords =
		"and as assert async await break class continue def del elif else except finally for "
		"from global if import in is lambda nonlocal not or pass raise return try while with yield "
		"ArithmeticError AssertionError AttributeError BaseException BlockingIOError BrokenPipeError "
		"BufferError BytesWarning ChildProcessError ConnectionAbortedError ConnectionError ConnectionRefusedError ConnectionResetError "
		"DeprecationWarning EOFError Ellipsis EnvironmentError Exception False FileExistsError FileNotFoundError FloatingPointError FutureWarning "
		"GeneratorExit IOError ImportError ImportWarning IndentationError IndexError InterruptedError IsADirectoryError KeyError KeyboardInterrupt "
		"LookupError MemoryError ModuleNotFoundError NameError None NotADirectoryError NotImplemented NotImplementedError OSError OverflowError "
		"PendingDeprecationWarning PermissionError ProcessLookupError RecursionError ReferenceError ResourceWarning RuntimeError RuntimeWarning "
		"StopAsyncIteration StopIteration SyntaxError SyntaxWarning SystemError SystemExit TabError TimeoutError True TypeError UnboundLocalError "
		"UnicodeDecodeError UnicodeEncodeError UnicodeError UnicodeTranslateError UnicodeWarning UserWarning ValueError Warning WindowsError "
		"ZeroDivisionError abs all any ascii bin bool breakpoint bytearray bytes callable chr classmethod compile complex copyright credit "
		"delattr dict dir divmod enumerate eval exec exit filter float format frozenset getattr globals hasattr hash help hex id "
		"input int isinstance issubclass iter len license list locals map max memoryview min next object oct open ord pow print "
		"property quit range repr reversed round set setattr slice sorted staticmethod str sum super tuple type vars zip ";
	// color text 
	static SScintillaColors g_rgb_Syntax_python[] =
	{
		{ SCE_P_DEFAULT,		foregroundMonokai },
		{ SCE_P_COMMENTLINE,		comment_monokai },
		{ SCE_P_NUMBER,				number },
		{ SCE_P_STRING,		    string },
		{ SCE_P_CHARACTER,			string },
		{ SCE_P_WORD,				keyword },
		{ SCE_P_TRIPLE,			comment_monokai },
		{ SCE_P_TRIPLEDOUBLE,			comment_monokai },
		{ SCE_P_CLASSNAME,			comment },
		{ SCE_P_DEFNAME,			comment },
		{ SCE_P_OPERATOR,			builtin },
		{ SCE_P_IDENTIFIER,		        foregroundMonokai },
		{ SCE_P_COMMENTBLOCK,		        comment_monokai },
		{ SCE_P_STRINGEOL,		        string },
		{ SCE_P_WORD2,				keyword },
		{ SCE_P_DECORATOR,		    foregroundMonokai },
		{ SCE_P_FSTRING,		    string },
		{ SCE_P_FCHARACTER,		    string },
		{ SCE_P_FTRIPLE,		    string },
		{ SCE_P_FTRIPLEDOUBLE,		string },
		{ -1,						0 }
	};

	static SScintillaColors g_rgb_Syntax_python_2[] =
	{
		{ SCE_P_COMMENTLINE,		comment },
		{ SCE_P_COMMENTBLOCK,		comment },
		{ SCE_P_NUMBER,				yellowgreen },
		{ SCE_P_DEFAULT,		    foregroundMonokai },
		{ SCE_P_CLASSNAME,			cyan },
		{ SCE_P_STRING,				string },
		{ SCE_P_CHARACTER,			string },
		{ SCE_P_IDENTIFIER,			foregroundMonokai },
		{ SCE_P_OPERATOR,			keyword },
		{ SCE_P_DEFNAME,			magenta },
		{ SCE_P_STRINGEOL,			foregroundMonokai },
		{ SCE_P_WORD,		        darkorange },
		{ SCE_P_WORD2,		        darkorange },
		{ SCE_P_TRIPLE,		        comment },
		{ SCE_P_TRIPLEDOUBLE,		comment },
		{ SCE_P_DECORATOR,		    builtin },
		{ -1,						0 }
	};

	//----------------------------------------------------------------------------
	//---- ada Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_ada_language = _T("ada");
	// extentions
	static CString g_str_ada_extention = _T("ada");
	// comment line
	static CString g_str_ada_commentline = _T("--");
	// comment start
	static CString g_str_ada_commentStart = _T("");
	// comment end
	static CString g_str_ada_commentEnd = _T("");
	// keywords
	static const char* g_ada_KeyWords =
		"abort abs abstract accept access aliased all and array at begin body case constant declare delay delta digits do else elsif end entry exception exit for function generic goto if in interface is limited loop mod new not null of or others out overriding package pragma private procedure protected raise range record rem renames requeue return reverse select separate some subtype synchronized tagged task terminate then type until use when while with xor ";
	// color text
	static SScintillaColors g_rgb_Syntax_ada[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };


	//----------------------------------------------------------------------------
	//---- asm Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_asm_language = _T("asm");
	// extentions
	static CString g_str_asm_extention = _T("asm");
	// comment line
	static CString g_str_asm_commentline = _T(";");
	// comment start
	static CString g_str_asm_commentStart = _T("");
	// comment end
	static CString g_str_asm_commentEnd = _T("");
	// keywords
	static const char* g_asm_KeyWords =
		"aaa aad aam aas adc add and call cbw cdqe clc cld cli cmc cmp cmps cmpsb cmpsw cwd daa das dec div esc hlt idiv imul in inc int into iret ja jae jb jbe jc jcxz je jg jge jl jle jmp jna jnae jnb jnbe jnc jne jng jnge jnl jnle jno jnp jns jnz jo jp jpe jpo js jz lahf lds lea les lods lodsb lodsw loop loope loopew loopne loopnew loopnz loopnzw loopw loopz loopzw mov movabs movs movsb movsw mul neg nop not or out pop popf push pushf rcl rcr ret retf retn rol ror sahf sal sar sbb scas scasb scasw shl shr stc std sti stos stosb stosw sub test wait xchg xlat xlatb xor bound enter ins insb insw leave outs outsb outsw popa pusha pushw arpl lar lsl sgdt sidt sldt smsw str verr verw clts lgdt lidt lldt lmsw ltr bsf bsr bt btc btr bts cdq cmpsd cwde insd iretd iretdf iretf jecxz lfs lgs lodsd loopd looped loopned loopnzd loopzd lss movsd movsx movsxd movzx outsd popad popfd pushad pushd pushfd scasd seta setae setb setbe setc sete setg setge setl setle setna setnae setnb setnbe setnc setne setng setnge setnl setnle setno setnp setns setnz seto setp setpe setpo sets setz shld shrd stosd bswap cmpxchg invd invlpg wbinvd xadd lock rep repe repne repnz repz cflush cpuid emms femms cmovo cmovno cmovb cmovc cmovnae cmovae cmovnb cmovnc cmove cmovz cmovne cmovnz cmovbe cmovna cmova cmovnbe cmovs cmovns cmovp cmovpe cmovnp cmovpo cmovl cmovnge cmovge cmovnl cmovle cmovng cmovg cmovnle cmpxchg486 cmpxchg8b loadall loadall286 ibts icebp int1 int3 int01 int03 iretw popaw popfw pushaw pushfw rdmsr rdpmc rdshr rdtsc rsdc rsldt rsm rsts salc smi smint smintold svdc svldt svts syscall sysenter sysexit sysret ud0 ud1 ud2 umov xbts wrmsr wrshr "
		"f2xm1 fabs fadd faddp fbld fbstp fchs fclex fcom fcomp fcompp fdecstp fdisi fdiv fdivp fdivr fdivrp feni ffree fiadd ficom ficomp fidiv fidivr fild fimul fincstp finit fist fistp fisub fisubr fld fld1 fldcw fldenv fldenvw fldl2e fldl2t fldlg2 fldln2 fldpi fldz fmul fmulp fnclex fndisi fneni fninit fnop fnsave fnsavew fnstcw fnstenv fnstenvw fnstsw fpatan fprem fptan frndint frstor frstorw fsave fsavew fscale fsqrt fst fstcw fstenv fstenvw fstp fstsw fsub fsubp fsubr fsubrp ftst fwait fxam fxch fxtract fyl2x fyl2xp1 fsetpm fcos fldenvd fnsaved fnstenvd fprem1 frstord fsaved fsin fsincos fstenvd fucom fucomp fucompp fcomi fcomip ffreep fcmovb fcmove fcmovbe fcmovu fcmovnb fcmovne fcmovnbe fcmovnu "
		"ah al ax bh bl bp bx ch cl cr0 cr2 cr3 cr4 cs cx dh di dl dr0 dr1 dr2 dr3 dr6 dr7 ds dx eax ebp ebx ecx edi edx es esi esp fs gs rax rbx rcx rdx rdi rsi rbp rsp r8 r9 r10 r11 r12 r13 r14 r15 r8d r9d r10d r11d r12d r13d r14d r15d r8w r9w r10w r11w r12w r13w r14w r15w r8b r9b r10b r11b r12b r13b r14b r15b si sp ss st tr3 tr4 tr5 tr6 tr7 st0 st1 st2 st3 st4 st5 st6 st7 mm0 mm1 mm2 mm3 mm4 mm5 mm6 mm7 xmm0 xmm1 xmm2 xmm3 xmm4 xmm5 xmm6 xmm7 xmm8 xmm9 xmm10 xmm11 xmm12 xmm13 xmm14 xmm15 "
		".186 .286 .286c .286p .287 .386 .386c .386p .387 .486 .486p .8086 .8087 .alpha .break .code .const .continue .cref .data .data? .dosseg .else .elseif .endif .endw .err .err1 .err2 .errb .errdef .errdif .errdifi .erre .erridn .erridni .errnb .errndef .errnz .exit .fardata .fardata? .if .lall .lfcond .list .listall .listif .listmacro .listmacroall .model .no87 .nocref .nolist .nolistif .nolistmacro .radix .repeat .sall .seq .sfcond .stack .startup .tfcond .type .until .untilcxz .while .xall .xcref .xlist alias align assume catstr comm comment db dd df dosseg dq dt dup dw echo else elseif elseif1 elseif2 elseifb elseifdef elseifdif elseifdifi elseife elseifidn elseifidni elseifnb elseifndef end endif endm endp ends eq equ even exitm extern externdef extrn for forc ge goto group gt high highword if if1 if2 ifb ifdef ifdif ifdifi ife ifidn ifidni ifnb ifndef include includelib instr invoke irp irpc label le length lengthof local low lowword lroffset lt macro mask mod .msfloat name ne offset opattr option org %out page popcontext proc proto ptr public purge pushcontext record repeat rept seg segment short size sizeof sizestr struc struct substr subtitle subttl textequ this title type typedef union while width resb resw resd resq rest incbin times %define %IDEfine %xdefine %xIDEfine %undef %assign %iassign %strlen %substr %macro %imacro %endmacro %rotate %if %elif %else %endif %ifdef %ifndef %elifdef %elifndef %ifmacro %ifnmacro %elifmacro %elifnmacro %ifctk %ifnctk %elifctk %elifnctk %ifidn %ifnidn %elifidn %elifnidn %ifidni %ifnidni %elifidni %elifnidni %ifid %ifnid %elifid %elifnid %ifstr %ifnstr %elifstr %elifnstr %ifnum %ifnnum %elifnum %elifnnum %error %rep %endrep %exitrep %include %push %pop %repl endstruc istruc at iend alignb %arg %stacksize %local %line bits use16 use32 section absolute global common cpu import export "
		"$ ? @b @f addr basic byte c carry? dword far far16 fortran fword near near16 overflow? parity? pascal qword real4 real8 real10 sbyte sdword sign? stdcall sword syscall tbyte vararg word zero? flat near32 far32 abs all assumes at casemap common compact cpu dotname emulator epilogue error export expr16 expr32 farstack forceframe huge language large listing ljmp loadds m510 medium memory nearstack nodotname noemulator nokeyword noljmp nom510 none nonunique nooldmacros nooldstructs noreadonly noscoped nosignextend nothing notpublic oldmacros oldstructs os_dos para private prologue radix readonly req scoped setif2 smallstack tiny use16 use32 uses a16 a32 o16 o32 nosplit $$ seq wrt small .text .data .bss %0 %1 %2 %3 %4 %5 %6 %7 %8 %9 "
		"addpd addps addsd addss andpd andps andnpd andnps cmpeqpd cmpltpd cmplepd cmpunordpd cmpnepd cmpnltpd cmpnlepd cmpordpd cmpeqps cmpltps cmpleps cmpunordps cmpneps cmpnltps cmpnleps cmpordps cmpeqsd cmpltsd cmplesd cmpunordsd cmpnesd cmpnltsd cmpnlesd cmpordsd cmpeqss cmpltss cmpless cmpunordss cmpness cmpnltss cmpnless cmpordss comisd comiss cvtdq2pd cvtdq2ps cvtpd2dq cvtpd2pi cvtpd2ps cvtpi2pd cvtpi2ps cvtps2dq cvtps2pd cvtps2pi cvtss2sd cvtss2si cvtsd2si cvtsd2ss cvtsi2sd cvtsi2ss cvttpd2dq cvttpd2pi cvttps2dq cvttps2pi cvttsd2si cvttss2si divpd divps divsd divss fxrstor fxsave ldmxscr lfence mfence maskmovdqu maskmovdq maxpd maxps paxsd maxss minpd minps minsd minss movapd movaps movdq2q movdqa movdqu movhlps movhpd movhps movd movq movlhps movlpd movlps movmskpd movmskps movntdq movnti movntpd movntps movntq movq2dq movsd movss movupd movups mulpd mulps mulsd mulss orpd orps packssdw packsswb packuswb paddb paddsb paddw paddsw paddd paddsiw paddq paddusb paddusw pand pandn pause paveb pavgb pavgw pavgusb pdistib pextrw pcmpeqb pcmpeqw pcmpeqd pcmpgtb pcmpgtw pcmpgtd pf2id pf2iw pfacc pfadd pfcmpeq pfcmpge pfcmpgt pfmax pfmin pfmul pmachriw pmaddwd pmagw pmaxsw pmaxub pminsw pminub pmovmskb pmulhrwc pmulhriw pmulhrwa pmulhuw pmulhw pmullw pmuludq pmvzb pmvnzb pmvlzb pmvgezb pfnacc pfpnacc por prefetch prefetchw prefetchnta prefetcht0 prefetcht1 prefetcht2 pfrcp pfrcpit1 pfrcpit2 pfrsqit1 pfrsqrt pfsub pfsubr pi2fd pinsrw psadbw pshufd pshufhw pshuflw pshufw psllw pslld psllq pslldq psraw psrad psrlw psrld psrlq psrldq psubb psubw psubd psubq psubsb psubsw psubusb psubusw psubsiw pswapd punpckhbw punpckhwd punpckhdq punpckhqdq punpcklbw punpcklwd punpckldq punpcklqdq pxor rcpps rcpss rsqrtps rsqrtss sfence shufpd shufps sqrtpd sqrtps sqrtsd sqrtss stmxcsr subpd subps subsd subss ucomisd ucomiss unpckhpd unpckhps unpcklpd unpcklps xorpd xorps ";
	// color text
	static SScintillaColors g_rgb_Syntax_asm[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			keyword },
	{ SCE_C_COMMENTDOC,				keyword },
	{ SCE_C_NUMBER,				builtin },
	{ SCE_C_WORD,			foregroundMonokai },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				foregroundMonokai },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    string },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				keyword },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				keyword },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				keyword },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				keyword },
	{ SCE_C_TRIPLEVERBATIM,				keyword },
	{ SCE_C_HASHQUOTEDSTRING,				keyword },
	{ SCE_C_PREPROCESSORCOMMENT,				keyword },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				keyword },
	{ SCE_C_TASKMARKER,				keyword },
	{ SCE_C_ESCAPESEQUENCE,				keyword },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- bash Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_bash_language = _T("bash");
	// extentions
	static CString g_str_bash_extention = _T("bash");
	// comment line
	static CString g_str_bash_commentline = _T("#");
	// comment start
	static CString g_str_bash_commentStart = _T("");
	// comment end
	static CString g_str_bash_commentEnd = _T("");
	// keywords
	static const char* g_bash_KeyWords =
		"7z adduser alias apt-get ar as asa autoconf automake awk banner base64 basename bash bc bdiff blkid break bsdcpio bsdtar bunzip2 bzcmp bzdiff bzegrep bzfgrep bzgrep bzip2 bzip2recover bzless bzmore c++ cal calendar case cat cc cd cfdisk chattr chgrp chmod chown chroot chvt cksum clang clang++ clear cmp col column comm compgen compress continue convert cp cpio crontab crypt csplit ctags curl cut date dc dd deallocvt declare deluser depmod deroff df dialog diff diff3 dig dircmp dirname disown dmesg do done dpkg dpkg-deb du echo ed egrep elif else env esac eval ex exec exit expand export expr fakeroot false fc fdisk ffmpeg fgrep fi file find flex flock fmt fold for fsck function functions fuser fusermount g++ gas gawk gcc gdb genisoimage getconf getopt getopts git gpg gpgsplit gpgv grep gres groff groups gunzip gzexe hash hd head help hexdump hg history httpd iconv id if ifconfig ifdown ifquery ifup in insmod integer inxi ip ip6tables ip6tables-save ip6tables-restore iptables iptables-save iptables-restore ip jobs join kill killall killall5 lc ld ldd let lex line ln local logname look ls lsattr lsb_release lsblk lscpu lshw lslocks lsmod lsusb lzcmp lzegrep lzfgrep lzgrep lzless lzma lzmainfo lzmore m4 mail mailx make man mkdir mkfifo mkswap mktemp modinfo modprobe mogrify more mount msgfmt mt mv nameif nasm nc ndisasm netcat newgrp nl nm nohup ntps objdump od openssl p7zip pacman passwd paste patch pathchk pax pcat pcregrep pcretest perl pg ping ping6 pivot_root poweroff pr print printf ps pwd python python2 python3 ranlib read readlink readonly reboot reset return rev rm rmdir rmmod rpm rsync sed select service set sh sha1sum sha224sum sha256sum sha3sum sha512sum shift shred shuf shutdown size sleep sort spell split start stop strings strip stty su sudo sum suspend switch_root sync systemctl tac tail tar tee test then time times touch tr trap troff true tsort tty type typeset ulimit umask umount unalias uname uncompress unexpand uniq unlink unlzma unset until unzip unzipsfx useradd userdel uudecode uuencode vi vim wait wc wget whence which while who wpaste wstart xargs xdotool xxd xz xzcat xzcmp xzdiff xzfgrep xzgrep xzless xzmore yes yum zcat zcmp zdiff zegrep zfgrep zforce zgrep zless zmore znew zsh ";
	// color text
	static SScintillaColors g_rgb_Syntax_bash[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };


	//----------------------------------------------------------------------------
	//---- batch Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_batch_language = _T("batch");
	// extentions
	static CString g_str_batch_extention = _T("batch");
	// comment line
	static CString g_str_batch_commentline = _T("REM");
	// comment start
	static CString g_str_batch_commentStart = _T("");
	// comment end
	static CString g_str_batch_commentEnd = _T("");
	// keywords
	static const char* g_batch_KeyWords =
		"assoc aux break call cd chcp chdir choice cls cmdextversion color com com1 com2 com3 com4 con copy country ctty date defined del dir do dpath echo else endlocal erase errorlevel exist exit for ftype goto if in loadfix loadhigh lpt lpt1 lpt2 lpt3 lpt4 md mkdir move not nul path pause popd prn prompt pushd rd rem ren rename rmdir set setlocal shift start time title type ver verify vol ";
	// color text
	static SScintillaColors g_rgb_Syntax_batch[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		string },
	{ SCE_C_COMMENTLINE,			definition },
	{ SCE_C_COMMENTDOC,				definition },
	{ SCE_C_NUMBER,				keyword },
	{ SCE_C_WORD,			builtin },
	{ SCE_C_STRING,				foregroundMonokai },
	{ SCE_C_CHARACTER,			foregroundMonokai },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				builtin },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				foregroundMonokai },
	{ SCE_C_WORD2,				definition },
	{ SCE_C_COMMENTDOCKEYWORD,				foregroundMonokai },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				foregroundMonokai },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				foregroundMonokai },
	{ SCE_C_TRIPLEVERBATIM,				foregroundMonokai },
	{ SCE_C_HASHQUOTEDSTRING,				foregroundMonokai },
	{ SCE_C_PREPROCESSORCOMMENT,				foregroundMonokai },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				foregroundMonokai },
	{ SCE_C_TASKMARKER,				foregroundMonokai },
	{ SCE_C_ESCAPESEQUENCE,				foregroundMonokai },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- c Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_c_language = _T("c");
	// extentions
	static CString g_str_c_extention = _T("c");
	// comment line
	static CString g_str_c_commentline = _T("//");
	// comment start
	static CString g_str_c_commentStart = _T("/*");
	// comment end
	static CString g_str_c_commentEnd = _T("*/");
	// keywords
	static const char* g_c_KeyWords =
		"if else switch case default break goto return for while do continue typedef sizeof offsetof alignof _Alignof _Generic _Static_assert and and_eq bitand bitor compl not not_eq or or_eq xor xor_eq NULL "
		"void struct union enum char short int long double float signed unsigned const static extern auto register volatile restrict _Atomic bool _Bool complex _Complex imaginary _Imaginary inline noreturn _Noreturn alignas _Alignas thread_local _Thread_local uint8_t uint16_t uint32_t uint64_t int8_t int16_t int32_t int64_t uint_least8_t uint_least16_t uint_least32_t uint_least64_t int_least8_t int_least16_t int_least32_t int_least64_t uint_fast8_t uint_fast16_t uint_fast32_t uint_fast64_t int_fast8_t int_fast16_t int_fast32_t int_fast64_t uintptr_t intptr_t uintmax_t intmax_t ptrdiff_t max_align_t div_t ldiv_t lldiv_t imaxdiv_t size_t time_t clock_t wchar_t char16_t char32_t sig_atomic_t FILE ";
	// color text
	static SScintillaColors g_rgb_Syntax_c[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			definition },
	{ SCE_C_UUID,				instance },
	{ SCE_C_PREPROCESSOR,				comment_monokai },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				instance },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				comment },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- cmake Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_cmake_language = _T("cmake");
	// extentions
	static CString g_str_cmake_extention = _T("cmake");
	// comment line
	static CString g_str_cmake_commentline = _T("#");
	// comment start
	static CString g_str_cmake_commentStart = _T("");
	// comment end
	static CString g_str_cmake_commentEnd = _T("");
	// keywords
	static const char* g_cmake_KeyWords =
		"add_custom_command add_compile_definitions add_compile_options add_custom_command add_custom_target add_definitions add_dependencies add_executable add_library add_link_options add_subdirectory add_test aux_source_directory build_command build_name cmake_minimum_required configure_file create_test_sourcelist else elseif enable_language enable_testing endforeach endfunction endif endmacro endwhile exec_program execute_process export export_library_dependencies file find_file find_library find_package find_path find_program fltk_wrap_ui foreach function get_cmake_property get_directory_property get_filename_component get_source_file_property get_target_property get_test_property if include include_directories include_external_msproject include_regular_expression install install_files install_programs install_targets link_directories link_libraries list load_cache load_command macro make_directory mark_as_advanced math message option output_required_files project qt_wrap_cpp qt_wrap_ui remove remove_definitions separate_arguments set set_directory_properties set_source_files_properties set_target_properties set_tests_properties site_name source_group string subdir_depends subdirs target_compile_definitions target_compile_features target_compile_options target_include_directories target_link_directories target_link_libraries target_link_options target_sources try_compile try_run use_mangled_mesa utility_source variable_requires vtk_make_instantiator vtk_wrap_java vtk_wrap_python vtk_wrap_tcl while write_file "
		"ABSOLUTE ABSTRACT ADDITIONAL_MAKE_CLEAN_FILES ALL AND APPEND ARGS ASCII BEFORE CACHE CACHE_VARIABLES CLEAR COMMAND COMMANDS COMMAND_NAME COMMENT COMPARE COMPILE_FLAGS COPYONLY DEFINED DEFINE_SYMBOL DEPENDS DOC EQUAL ESCAPE_QUOTES EXCLUDE EXCLUDE_FROM_ALL EXISTS EXPORT_MACRO EXT EXTRA_INCLUDE FATAL_ERROR FILE FILES FORCE FUNCTION GENERATED GLOB GLOB_RECURSE GREATER GROUP_SIZE HEADER_FILE_ONLY HEADER_LOCATION IMMEDIATE INCLUDES INCLUDE_DIRECTORIES INCLUDE_INTERNALS INCLUDE_REGULAR_EXPRESSION LESS LINK_DIRECTORIES LINK_FLAGS LOCATION MACOSX_BUNDLE MACROS MAIN_DEPENDENCY MAKE_DIRECTORY MATCH MATCHALL MATCHES MODULE NAME NAME_WE NOT NOTEQUAL NO_SYSTEM_PATH OBJECT_DEPENDS OPTIONAL OR OUTPUT OUTPUT_VARIABLE PATH PATHS POST_BUILD POST_INSTALL_SCRIPT PREFIX PREORDER PRE_BUILD PRE_INSTALL_SCRIPT PRE_LINK PROGRAM PROGRAM_ARGS PROPERTIES QUIET RANGE READ REGEX REGULAR_EXPRESSION REPLACE REQUIRED RETURN_VALUE RUNTIME_DIRECTORY SEND_ERROR SHARED SOURCES STATIC STATUS STREQUAL STRGREATER STRLESS SUFFIX TARGET TOLOWER TOUPPER VAR VARIABLES VERSION WIN32 WRAP_EXCLUDE WRITE APPLE MINGW MSYS CYGWIN BORLAND WATCOM MSVC MSVC_IDE MSVC60 MSVC70 MSVC71 MSVC80 CMAKE_COMPILER_2005 OFF ON ";
	// color text
	static SScintillaColors g_rgb_Syntax_cmake[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- cs Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_cs_language = _T("cs");
	// extentions
	static CString g_str_cs_extention = _T("cs");
	// comment line
	static CString g_str_cs_commentline = _T("//");
	// comment start
	static CString g_str_cs_commentStart = _T("/*");
	// comment end
	static CString g_str_cs_commentEnd = _T("*/");
	// keywords
	static const char* g_cs_KeyWords =
		"abstract add alias as ascending async await base break case catch checked continue default delegate descending do dynamic else event explicit extern false finally fixed for foreach from get global goto group if implicit in interface internal into is join let lock namespace new null object operator orderby out overrIDE params partial private protected public readonly ref remove return sealed select set sizeof stackalloc switch this throw true try typeof unchecked unsafe using value virtual where while yield "
		"bool byte char class const decimal double enum float int long sbyte short static string struct uint ulong ushort var void ";
	// color text
	static SScintillaColors g_rgb_Syntax_cs[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- css Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_css_language = _T("css");
	// extentions
	static CString g_str_css_extention = _T("css");
	// comment line
	static CString g_str_css_commentline = _T("");
	// comment start
	static CString g_str_css_commentStart = _T("/*");
	// comment end
	static CString g_str_css_commentEnd = _T("*/");
	// keywords
	static const char* g_css_KeyWords =
		"-khtml-background-clip -khtml-background-origin -khtml-background-size -khtml-border-bottom-left-radius -khtml-border-bottom-right-radius -khtml-border-radius -khtml-border-top-left-radius -khtml-border-top-right-radius -khtml-opacity -moz-animation -moz-animation-delay -moz-animation-direction -moz-animation-duration -moz-animation-fill-mode -moz-animation-iteration-count -moz-animation-name -moz-animation-play-state -moz-animation-timing-function -moz-appearance -moz-background-clip -moz-background-inline-policy -moz-background-origin -moz-background-size -moz-binding -moz-border-bottom-colors -moz-border-end -moz-border-end-color -moz-border-end-style -moz-border-end-width -moz-border-image -moz-border-left-colors -moz-border-radius -moz-border-radius-bottomleft -moz-border-radius-bottomright -moz-border-radius-topleft -moz-border-radius-topright -moz-border-right-colors -moz-border-start -moz-border-start-color -moz-border-start-style -moz-border-start-width -moz-border-top-colors -moz-box-align -moz-box-direction -moz-box-flex -moz-box-flex-group -moz-box-flexgroup -moz-box-ordinal-group -moz-box-orient -moz-box-pack -moz-box-shadow -moz-box-sizing -moz-column-count -moz-column-gap -moz-column-rule -moz-column-rule-color -moz-column-rule-style -moz-column-rule-width -moz-column-width -moz-context-properties -moz-float-edge -moz-force-broken-image-icon -moz-image-region -moz-linear-gradient -moz-margin-end -moz-margin-start -moz-opacity -moz-outline -moz-outline-color -moz-outline-offset -moz-outline-radius -moz-outline-radius-bottomleft -moz-outline-radius-bottomright -moz-outline-radius-topleft -moz-outline-radius-topright -moz-outline-style -moz-outline-width -moz-padding-end -moz-padding-start -moz-radial-gradient -moz-stack-sizing -moz-text-decoration-color -moz-text-decoration-line -moz-text-decoration-style -moz-transform -moz-transform-origin -moz-transition -moz-transition-delay -moz-transition-duration -moz-transition-property -moz-transition-timing-function -moz-user-focus -moz-user-input -moz-user-modify -moz-user-select -moz-window-shadow -ms-filter -ms-transform -ms-transform-origin -o-transform -webkit-animation -webkit-animation-delay -webkit-animation-direction -webkit-animation-duration -webkit-animation-fill-mode -webkit-animation-iteration-count -webkit-animation-name -webkit-animation-play-state -webkit-animation-timing-function -webkit-appearance -webkit-backface-visibility -webkit-background-clip -webkit-background-composite -webkit-background-origin -webkit-background-size -webkit-border-bottom-left-radius -webkit-border-bottom-right-radius -webkit-border-horizontal-spacing -webkit-border-image -webkit-border-radius -webkit-border-top-left-radius -webkit-border-top-right-radius -webkit-border-vertical-spacing -webkit-box-align -webkit-box-direction -webkit-box-flex -webkit-box-flex-group -webkit-box-lines -webkit-box-ordinal-group -webkit-box-orient -webkit-box-pack -webkit-box-reflect -webkit-box-shadow -webkit-box-sizing -webkit-column-break-after -webkit-column-break-before -webkit-column-break-insIDE -webkit-column-count -webkit-column-gap -webkit-column-rule -webkit-column-rule-color -webkit-column-rule-style -webkit-column-rule-width -webkit-column-width -webkit-columns -webkit-dashboard-region -webkit-font-smoothing -webkit-gradient -webkit-line-break -webkit-linear-gradient -webkit-margin-bottom-collapse -webkit-margin-collapse -webkit-margin-start -webkit-margin-top-collapse -webkit-marquee -webkit-marquee-direction -webkit-marquee-increment -webkit-marquee-repetition -webkit-marquee-speed -webkit-marquee-style -webkit-mask -webkit-mask-attachment -webkit-mask-box-image -webkit-mask-clip -webkit-mask-composite -webkit-mask-image -webkit-mask-origin -webkit-mask-position -webkit-mask-position-x -webkit-mask-position-y -webkit-mask-repeat -webkit-mask-size -webkit-nbsp-mode -webkit-padding-start -webkit-perspective -webkit-perspective-origin -webkit-radial-gradient -webkit-rtl-ordering -webkit-tap-highlight-color -webkit-text-fill-color -webkit-text-security -webkit-text-size-adjust -webkit-text-stroke -webkit-text-stroke-color -webkit-text-stroke-width -webkit-touch-callout -webkit-transform -webkit-transform-origin -webkit-transform-origin-x -webkit-transform-origin-y -webkit-transform-origin-z -webkit-transform-style -webkit-transition -webkit-transition-delay -webkit-transition-duration -webkit-transition-property -webkit-transition-timing-function -webkit-user-drag -webkit-user-modify -webkit-user-select align-content align-items align-self alignment-adjust alignment-baseline all animation animation-delay animation-direction animation-duration animation-fill-mode animation-iteration-count animation-name animation-play-state animation-timing-function appearance azimuth backface-visibility background background-attachment background-blend-mode background-break background-clip background-color background-image background-origin background-position background-position-x background-position-y background-repeat background-size baseline-shift binding bleed block-size bookmark-label bookmark-level bookmark-state bookmark-target border border-block border-block-end border-block-start border-bottom border-bottom-color border-bottom-left-radius border-bottom-right-radius border-bottom-style border-bottom-width border-collapse border-color border-image border-image-outset border-image-repeat border-image-slice border-image-source border-image-width border-inline border-inline-end border-inline-end-width border-inline-start border-inline-start-color border-inline-start-style border-inline-start-width border-left border-left-color border-left-style border-left-width border-radius border-right border-right-color border-right-style border-right-width border-spacing border-style border-top border-top-color border-top-left-radius border-top-right-radius border-top-style border-top-width border-width bottom box-align box-decoration-break box-direction box-flex box-flex-group box-lines box-ordinal-group box-orient box-pack box-shadow box-sizing break-after break-before break-insIDE caption-sIDE caret-color clear clip color color-profile column-count column-fill column-gap column-rule column-rule-color column-rule-style column-rule-width column-span column-width columns content counter-increment counter-reset crop cue cue-after cue-before cursor direction display dominant-baseline drop-initial-after-adjust drop-initial-after-align drop-initial-before-adjust drop-initial-before-align drop-initial-size drop-initial-value elevation empty-cells fill fill-opacity filter fit fit-position flex flex-basis flex-direction flex-flow flex-grow flex-shrink flex-wrap float float-offset font font-effect font-emphasize font-family font-size font-size-adjust font-stretch font-style font-variant font-variant-ligatures font-weight gap grid-area grid-auto-flow grid-auto-rows grid-column grid-column-end grid-column-gap grid-column-start grid-columns grid-gap grid-row grid-row-gap grid-rows grid-template-areas grid-template-columns grid-template-rows hanging-punctuation height hyphenate-after hyphenate-before hyphenate-character hyphenate-lines hyphenate-resource hyphens icon image-orientation image-rendering image-resolution inline-box-align inline-size inset inset-inline-end inset-inline-start justify-content justify-items justify-self left letter-spacing line-height line-stacking line-stacking-ruby line-stacking-shift line-stacking-strategy list-style list-style-image list-style-position list-style-type margin margin-block margin-block-end margin-block-start margin-bottom margin-inline margin-inline-end margin-inline-start margin-left margin-right margin-top mark mark-after mark-before marker-offset marks marquee-direction marquee-play-count marquee-speed marquee-style mask mask-clip mask-image mask-origin mask-position mask-position-x mask-repeat mask-size max-height max-width min-block-size min-height min-inline-size min-width mix-blend-mode move-to nav-down nav-index nav-left nav-right nav-up object-fit opacity order orphans outline outline-color outline-offset outline-style outline-width overflow overflow-anchor overflow-style overflow-wrap overflow-x overflow-y padding padding-block padding-block-end padding-block-start padding-bottom padding-inline padding-inline-end padding-inline-start padding-left padding-right padding-top page page-break-after page-break-before page-break-insIDE page-policy paint-order pause pause-after pause-before perspective perspective-origin phonemes pitch pitch-range play-during pointer-events position presentation-level punctuation-trim quotes rendering-intent resize rest rest-after rest-before richness right rotation rotation-point ruby-align ruby-overhang ruby-position ruby-span scrollbar-color size speak speak-header speak-numeral speak-punctuation speech-rate stress string-set stroke stroke-dasharray stroke-linejoin stroke-opacity stroke-width tab-size table-layout target target-name target-new target-position text-align text-align-last text-anchor text-decoration text-decoration-color text-decoration-line text-decoration-style text-emphasis text-height text-indent text-justify text-outline text-overflow text-rendering text-shadow text-transform text-wrap top transform transform-origin transform-style transition transition-delay transition-duration transition-property transition-timing-function unicode-bidi user-select vector-effect vertical-align visibility voice-balance voice-duration voice-family voice-pitch voice-pitch-range voice-rate voice-stress voice-volume volume white-space white-space-collapse widows width will-change word-break word-spacing word-wrap z-index "
		"active after before check checked disabled empty enabled first first-child first-letter first-line first-of-type focus hover indeterminate invalid lang last-child last-of-type left link not nth-child nth-last-child nth-of-type nth-last-of-type only-child only-of-type optional read-only read-write required right root selection target valid visited ";
	// color text
	static SScintillaColors g_rgb_Syntax_css[] =
	{ { SCE_CSS_DEFAULT,		foregroundMonokai },
	{ SCE_CSS_TAG,		keyword },
	{ SCE_CSS_CLASS,			comment },
	{ SCE_CSS_PSEUDOCLASS,				keyword },
	{ SCE_CSS_UNKNOWN_PSEUDOCLASS,				foregroundMonokai },
	{ SCE_CSS_OPERATOR,			foregroundMonokai },
	{ SCE_CSS_IDENTIFIER,				builtin },
	{ SCE_CSS_UNKNOWN_IDENTIFIER,			builtin },
	{ SCE_CSS_VALUE,		number },
	{ SCE_CSS_COMMENT,				comment_monokai },
	{ SCE_CSS_ID,				builtin },
	{ SCE_CSS_IMPORTANT,				orangered },
	{ SCE_CSS_DIRECTIVE,    keyword },
	{ SCE_CSS_DOUBLESTRING,				string },
	{ SCE_CSS_SINGLESTRING,				string },
	{ SCE_CSS_IDENTIFIER2,				keyword },
	{ SCE_CSS_ATTRIBUTE,				peachpuff },
	{ SCE_CSS_IDENTIFIER3,				keyword },
	{ SCE_CSS_PSEUDOELEMENT,				keyword },
	{ SCE_CSS_EXTENDED_IDENTIFIER,				keyword },
	{ SCE_CSS_EXTENDED_PSEUDOCLASS,				keyword },
	{ SCE_CSS_EXTENDED_PSEUDOELEMENT,				keyword },
	{ SCE_CSS_MEDIA,				keyword },
	{ SCE_CSS_VARIABLE,				foregroundMonokai },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- erlang Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_erlang_language = _T("erlang");
	// extentions
	static CString g_str_erlang_extention = _T("erlang");
	// comment line
	static CString g_str_erlang_commentline = _T("%");
	// comment start
	static CString g_str_erlang_commentStart = _T("");
	// comment end
	static CString g_str_erlang_commentEnd = _T("");
	// keywords
	static const char* g_erlang_KeyWords =
		"after and andalso band begin bnot bor bsl bsr bxor case catch cond div end fun if let not of or orelse query receive rem try when xor "
		"erlang: abs adler32 adler32_combine erlang:append_element apply atom_to_binary atom_to_list binary_to_atom binary_to_existing_atom binary_to_list bitstring_to_list binary_to_term bit_size erlang:bump_reductions byte_size erlang:cancel_timer check_process_code concat_binary crc32 crc32_combine date decode_packet delete_module erlang:demonitor disconnect_node erlang:display element erase erlang:error exit float float_to_list erlang:fun_info erlang:fun_to_list erlang:function_exported garbage_collect get erlang:get_cookie get_keys erlang:get_stacktrace group_leader halt erlang:hash hd erlang:hibernate integer_to_list erlang:integer_to_list iolist_to_binary iolist_size is_alive is_atom is_binary is_bitstring is_boolean erlang:is_builtin is_float is_function is_integer is_list is_number is_pid is_port is_process_alive is_record is_reference is_tuple length link list_to_atom list_to_binary list_to_bitstring list_to_existing_atom list_to_float list_to_integer erlang:list_to_integer list_to_pid list_to_tuple load_module erlang:load_nif erlang:loaded erlang:localtime erlang:localtime_to_universaltime make_ref erlang:make_tuple erlang:max erlang:md5 erlang:md5_final erlang:md5_init erlang:md5_update erlang:memory erlang:min module_loaded erlang:monitor monitor_node node nodes now open_port erlang:phash erlang:phash2 pid_to_list port_close port_command erlang:port_command port_connect port_control erlang:port_call erlang:port_info erlang:port_to_list erlang:ports pre_loaded erlang:process_display process_flag process_info processes purge_module put erlang:raise erlang:read_timer erlang:ref_to_list register registered erlang:resume_process round self erlang:send erlang:send_after erlang:send_nosuspend erlang:set_cookie setelement size spawn spawn_link spawn_monitor spawn_opt split_binary erlang:start_timer statistics erlang:suspend_process erlang:system_flag erlang:system_info erlang:system_monitor erlang:system_profile term_to_binary throw time tl erlang:trace erlang:trace_delivered erlang:trace_info erlang:trace_pattern trunc tuple_size tuple_to_list erlang:universaltime erlang:universaltime_to_localtime unlink unregister whereis erlang:yield "
		"-define -else -endif -ifdef -ifndef -include -include_lib -undef "
		"-behavior -behaviour -compile -created -created_by -export -file -import -module -modified -modified_by -record -revision -spec -type -vsn "
		"@author @clear @copyright @deprecated @doc @docfile @end @equiv @headerfile @hidden @private @reference @see @since @spec @throws @title @todo @TODO "
		"@date @docRoot @link @module @package @section @time @type @version ";
	// color text
	static SScintillaColors g_rgb_Syntax_erlang[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- fortran Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_fortran_language = _T("fortran");
	// extentions
	static CString g_str_fortran_extention = _T("fortran");
	// comment line
	static CString g_str_fortran_commentline = _T("!");
	// comment start
	static CString g_str_fortran_commentStart = _T("");
	// comment end
	static CString g_str_fortran_commentEnd = _T("");
	// keywords
	static const char* g_fortran_KeyWords =
		"access action advance allocatable allocate apostrophe assign assignment associate asynchronous backspace bind blank blockdata call case character class close common complex contains continue critical cycle data deallocate decimal delim default dimension direct do dowhile double doubleprecision else elseif elsewhere encoding end endassociate endblockdata endcritical enddo endenum endfile endforall endfunction endif endinterface endmodule endprocedure endprogram endselect endsubmodule endsubroutine endtype endwhere entry enum eor equivalence err errmsg exist exit external file flush fmt forall form format formatted function go goto id if implicit in include inout integer inquire intent interface intrinsic iomsg iolength iostat kind len logical module name named namelist nextrec nml none nullify number only open opened operator optional out pad parameter pass pause pending pointer pos position precision print private procedure program protected public quote read readwrite real rec recl recursive result return rewind save select selectcase selecttype sequential sign size stat status stop stream submodule subroutine target then to type unformatted unit use value volatile wait where while write "
		"abs achar acos acosd adjustl adjustr aimag aimax0 aimin0 aint ajmax0 ajmin0 akmax0 akmin0 all allocated alog alog10 amax0 amax1 amin0 amin1 amod anint any asin asind associated atan atan2 atan2d atand bitest bitl bitlr bitrl bjtest bit_size bktest break btest cabs ccos cdabs cdcos cdexp cdlog cdsin cdsqrt ceiling cexp char clog cmplx conjg cos cosd cosh count cpu_time cshift csin csqrt dabs dacos dacosd dasin dasind datan datan2 datan2d datand date date_and_time dble dcmplx dconjg dcos dcosd dcosh dcotan ddim dexp dfloat dflotk dfloti dflotj digits dim dimag dint dlog dlog10 dmax1 dmin1 dmod dnint dot_product dprod dreal dsign dsin dsind dsinh dsqrt dtan dtand dtanh eoshift epsilon errsns exp exponent float floati floatj floatk floor fraction free huge iabs iachar iand ibclr ibits ibset ichar idate idim idint idnint ieor ifix iiabs iiand iibclr iibits iibset iidim iidint iidnnt iieor iifix iint iior iiqint iiqnnt iishft iishftc iisign ilen imax0 imax1 imin0 imin1 imod index inint inot int int1 int2 int4 int8 iqint iqnint ior ishft ishftc isign isnan izext jiand jibclr jibits jibset jidim jidint jidnnt jieor jifix jint jior jiqint jiqnnt jishft jishftc jisign jmax0 jmax1 jmin0 jmin1 jmod jnint jnot jzext kiabs kiand kibclr kibits kibset kidim kidint kidnnt kieor kifix kind kint kior kishft kishftc kisign kmax0 kmax1 kmin0 kmin1 kmod knint knot kzext lbound leadz len len_trim lenlge lge lgt lle llt log log10 logical lshift malloc matmul max max0 max1 maxexponent maxloc maxval merge min min0 min1 minexponent minloc minval mod modulo mvbits nearest nint not nworkers number_of_processors pack popcnt poppar precision present product radix random random_number random_seed range real repeat reshape rrspacing rshift scale scan secnds selected_int_kind selected_real_kind set_exponent shape sign sin sind sinh size sizeof sngl snglq spacing spread sqrt sum system_clock tan tand tanh tiny transfer transpose trim ubound unpack verify "
		"cdabs cdcos cdexp cdlog cdsin cdsqrt cotan cotand dcmplx dconjg dcotan dcotand decode dimag dll_export dll_import doublecomplex dreal dvchk encode find flen flush getarg getcharqq getcl getdat getenv gettim hfix ibchng IDEntifier imag int1 int2 int4 intc intrup invalop iostat_msg isha ishc ishl jfix lacfar locking locnear map nargs nbreak ndperr ndpexc offset ovefl peekcharqq precfill prompt qabs qacos qacosd qasin qasind qatan qatand qatan2 qcmplx qconjg qcos qcosd qcosh qdim qexp qext qextd qfloat qimag qlog qlog10 qmax1 qmin1 qmod qreal qsign qsin qsind qsinh qsqrt qtan qtand qtanh ran rand randu rewrite segment setdat settim system timer undfl unlock union val virtual volatile zabs zcos zexp zlog zsin zsqrt ";
	// color text
	static SScintillaColors g_rgb_Syntax_fortran[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- html Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_html_language = _T("html");
	// extentions
	static CString g_str_html_extention = _T("html");
	// comment line
	static CString g_str_html_commentline = _T("");
	// comment start
	static CString g_str_html_commentStart = _T("<!--");
	// comment end
	static CString g_str_html_commentEnd = _T("-->");
	// keywords
	static const char* g_html_KeyWords =
		"!doctype a abbr accept accept-charset accesskey acronym action address align alink alt applet archive area article asIDE async audio autocomplete autofocus axis b background base basefont bdi bdo bgcolor bgsound big blink blockquote body border br button canvas caption cellpadding cellspacing center char charoff charset checkbox checked cite class classid clear code codebase codetype col colgroup color cols colspan command compact content contenteditable contextmenu coords data datafld dataformatas datalist datapagesize datasrc datetime dd declare defer del details dfn dialog dir disabled div dl draggable dropzone dt element em embed enctype event face fieldset figcaption figure file font footer for form formaction formenctype formmethod formnovalidate formtarget frame frameborder frameset h1 h2 h3 h4 h5 h6 head header headers height hgroup hidden hr href hreflang hspace html http-equiv i id iframe image img input ins isindex ismap kbd keygen label lang language leftmargin legend li link list listing longdesc main manifest map marginheight marginwidth mark marquee max maxlength media menu menuitem meta meter method min multicol multiple name nav nobr noembed noframes nohref noresize noscript noshade novalidate nowrap object ol onabort onafterprint onautocomplete onautocompleteerror onbeforeonload onbeforeprint onblur oncancel oncanplay oncanplaythrough onchange onclick onclose oncontextmenu oncuechange ondblclick ondrag ondragend ondragenter ondragleave ondragover ondragstart ondrop ondurationchange onemptied onended onerror onfocus onhashchange oninput oninvalid onkeydown onkeypress onkeyup onload onloadeddata onloadedmetadata onloadstart onmessage onmousedown onmouseenter onmouseleave onmousemove onmouseout onmouseover onmouseup onmousewheel onoffline ononline onpagehIDE onpageshow onpause onplay onplaying onpointercancel onpointerdown onpointerenter onpointerleave onpointerlockchange onpointerlockerror onpointermove onpointerout onpointerover onpointerup onpopstate onprogress onratechange onreadystatechange onredo onreset onresize onscroll onseeked onseeking onselect onshow onsort onstalled onstorage onsubmit onsuspend ontimeupdate ontoggle onundo onunload onvolumechange onwaiting optgroup option output p param password pattern picture placeholder plaintext pre profile progress prompt public q radio readonly rel required reset rev reversed role rows rowspan rp rt rtc ruby rules s samp sandbox scheme scope scoped script seamless section select selected shadow shape size sizes small source spacer span spellcheck src srcdoc standby start step strike strong style sub submit summary sup svg svg:svg tabindex table target tbody td template text textarea tfoot th thead time title topmargin tr track tt type u ul usemap valign value valuetype var version vIDEo vlink vspace wbr width xml xmlns xmp ";
	// color text
	static SScintillaColors g_rgb_Syntax_html[] =
	{ { SCE_H_DEFAULT,		foregroundMonokai },
	{ SCE_H_TAG,		keyword },
	{ SCE_H_TAGUNKNOWN,			foregroundMonokai },
	{ SCE_H_ATTRIBUTE,				comment },
	{ SCE_H_ATTRIBUTEUNKNOWN,				comment },
	{ SCE_H_NUMBER,			number },
	{ SCE_H_DOUBLESTRING,				foregroundMonokai },
	{ SCE_H_SINGLESTRING,			foregroundMonokai },
	{ SCE_H_OTHER,		builtin },
	{ SCE_H_COMMENT,				comment_monokai },
	{ SCE_H_ENTITY,				builtin },
	{ SCE_H_TAGEND,				keyword },
	{ SCE_H_XMLSTART,    light_orange },
	{ SCE_H_XMLEND,				yellow },
	{ SCE_H_SCRIPT,				light_orange },
	{ SCE_H_ASP,				comment },
	{ SCE_H_ASPAT,				comment },
	{ SCE_H_CDATA,				comment },
	{ SCE_H_QUESTION,				comment },
	{ SCE_H_VALUE,				magenta },
	{ SCE_H_XCCOMMENT,				light_orange },
	{ SCE_H_SGML_DEFAULT,				light_orange },
	{ SCE_H_SGML_COMMAND,				light_orange },
	{ SCE_H_SGML_1ST_PARAM,				light_orange },
	{ SCE_H_SGML_DOUBLESTRING,				yellow },
	{ SCE_H_SGML_SIMPLESTRING,				light_orange },
	{ SCE_H_SGML_ERROR,				light_orange },
	{ SCE_H_SGML_SPECIAL,				light_orange },
	{ SCE_H_SGML_ENTITY,				light_orange },
	{ SCE_H_SGML_COMMENT,				light_orange },
	{ SCE_H_SGML_1ST_PARAM_COMMENT,				light_orange },
	{ SCE_H_SGML_BLOCK_DEFAULT,				light_orange },
	{ SCE_HJ_START,				light_orange },
	{ SCE_HJ_DEFAULT,				light_orange },
	{ SCE_HJ_COMMENT,				comment_monokai },
	{ SCE_HJ_COMMENTLINE,				comment_monokai },
	{ SCE_HJ_COMMENTDOC,				comment_monokai },
	{ SCE_HJ_NUMBER,				number },
	{ SCE_HJ_WORD,				foregroundMonokai },
	{ SCE_HJ_KEYWORD,				keyword },
	{ SCE_HJ_DOUBLESTRING,				string },
	{ SCE_HJ_SINGLESTRING,				string },
	{ SCE_HJ_SYMBOLS,				builtin },
	{ SCE_HJ_STRINGEOL,				string },
	{ SCE_HJ_REGEX,				string },
	{ SCE_HJA_START, orangered },
	{ SCE_HJA_DEFAULT, builtin },
	{ SCE_HJA_COMMENT, comment_monokai },
	{ SCE_HJA_COMMENTLINE, comment_monokai },
	{ SCE_HJA_COMMENTDOC, comment_monokai },
	{ SCE_HJA_NUMBER, number },
	{ SCE_HJA_WORD, keyword },
	{ SCE_HJA_KEYWORD, keyword },
	{ SCE_HJA_DOUBLESTRING , string },
	{ SCE_HJA_SINGLESTRING , string },
	{ SCE_HJA_SYMBOLS, comment },
	{ SCE_HJA_STRINGEOL, string },
	{ SCE_HJA_REGEX, string },
	{ SCE_HB_START, string },
	{ SCE_HB_DEFAULT, builtin },
	{ SCE_HB_COMMENTLINE, comment_monokai },
	{ SCE_HB_NUMBER, number },
	{ SCE_HB_WORD, comment },
	{ SCE_HB_STRING, string },
	{ SCE_HB_IDENTIFIER, builtin },
	{ SCE_HB_STRINGEOL, string },
	{ SCE_HBA_START, string },
	{ SCE_HBA_DEFAULT, string },
	{ SCE_HBA_COMMENTLINE, comment_monokai },
	{ SCE_HBA_NUMBER, number },
	{ SCE_HBA_WORD, comment },
	{ SCE_HBA_STRING, string },
	{ SCE_HBA_IDENTIFIER, builtin },
	{ SCE_HBA_STRINGEOL, string },
	{ SCE_HP_START, string },
	{ SCE_HP_DEFAULT, string },
	{ SCE_HP_COMMENTLINE, comment_monokai },
	{ SCE_HP_NUMBER, number },
	{ SCE_HP_STRING, string },
	{ SCE_HP_CHARACTER, string },
	{ SCE_HP_WORD, comment },
	{ SCE_HP_TRIPLE, string },
	{ SCE_HP_TRIPLEDOUBLE, string },
	{ SCE_HP_CLASSNAME, comment },
	{ SCE_HP_DEFNAME, comment },
	{ SCE_HP_OPERATOR, string },
	{ SCE_HP_IDENTIFIER, string },
	{ SCE_HPHP_COMPLEX_VARIABLE , string },
	{ SCE_HPA_START, string },
	{ SCE_HPA_DEFAULT, string },
	{ SCE_HPA_COMMENTLINE, comment_monokai },
	{ SCE_HPA_NUMBER, number },
	{ SCE_HPA_STRING, string },
	{ SCE_HPA_CHARACTER, string },
	{ SCE_HPA_WORD, comment },
	{ SCE_HPA_TRIPLE, string },
	{ SCE_HPA_TRIPLEDOUBLE , string },
	{ SCE_HPA_CLASSNAME, comment },
	{ SCE_HPA_DEFNAME, string },
	{ SCE_HPA_OPERATOR, comment },
	{ SCE_HPA_IDENTIFIER, string },
	{ SCE_HPHP_DEFAULT, builtin },
	{ SCE_HPHP_HSTRING, string },
	{ SCE_HPHP_SIMPLESTRING , string },
	{ SCE_HPHP_WORD, comment },
	{ SCE_HPHP_NUMBER, number },
	{ SCE_HPHP_VARIABLE, string },
	{ SCE_HPHP_COMMENT, comment_monokai },
	{ SCE_HPHP_COMMENTLINE, comment_monokai },
	{ SCE_HPHP_HSTRING_VARIABLE, string },
	{ SCE_HPHP_OPERATOR, builtin },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- java Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_java_language = _T("java");
	// extentions
	static CString g_str_java_extention = _T("java");
	// comment line
	static CString g_str_java_commentline = _T("//");
	// comment start
	static CString g_str_java_commentStart = _T("/*");
	// comment end
	static CString g_str_java_commentEnd = _T("*/");
	// keywords
	static const char* g_java_KeyWords =
		"instanceof assert if else switch case default break goto return for while do continue new throw throws try catch finally this super extends implements import true false null "
		"package transient strictfp void char short int long double float const static volatile byte boolean class interface native private protected public final abstract synchronized enum ";
	// color text
	static SScintillaColors g_rgb_Syntax_java[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- javascript Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_javascript_language = _T("javascript");
	// extentions
	static CString g_str_javascript_extention = _T("javascript");
	// comment line
	static CString g_str_javascript_commentline = _T("//");
	// comment start
	static CString g_str_javascript_commentStart = _T("/*");
	// comment end
	static CString g_str_javascript_commentEnd = _T("*/");
	// keywords
	static const char* g_javascript_KeyWords =
		"abstract arguments await boolean break byte case catch char class const continue debugger default delete do double else enum eval export extends false final finally float for function goto if implements import in instanceof int interface let long native new null package private protected public return short static super switch synchronized this throw throws transient true try typeof var void volatile while with yield Array Date eval function hasOwnProperty Infinity isFinite isNaN isPrototypeOf length Math NaN Number Object prototype String toString undefined valueOf from ";
	// color text
	static SScintillaColors g_rgb_Syntax_javascript[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- typescript Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_typescript_language = _T("typescript");
	// extentions
	static CString g_str_typescript_extention = _T("typescript");
	// comment line
	static CString g_str_typescript_commentline = _T("//");
	// comment start
	static CString g_str_typescript_commentStart = _T("/*");
	// comment end
	static CString g_str_typescript_commentEnd = _T("*/");
	// keywords
	static const char* g_typescript_KeyWords =
		"break case catch class const continue debugger default delete do else enum export extends false finally for function if import in instanceof new null return super switch this throw true try typeof var void while with as implements interface let package private protected public static yield any boolean constructor declare get module require number set string symbol type from of ";
	// color text
	static SScintillaColors g_rgb_Syntax_typescript[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- lua Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_lua_language = _T("lua");
	// extentions
	static CString g_str_lua_extention = _T("lua");
	// comment line
	static CString g_str_lua_commentline = _T("--");
	// comment start
	static CString g_str_lua_commentStart = _T("");
	// comment end
	static CString g_str_lua_commentEnd = _T("");
	// keywords
	static const char* g_lua_KeyWords =
		"and break do else elseif end false for function goto if in local nil not or repeat return then true until while "
		"_ENV _G _VERSION assert collectgarbage dofile error getfenv getmetatable ipairs load loadfile loadstring module next pairs pcall print rawequal rawget rawlen rawset require select setfenv setmetatable tonumber tostring type unpack xpcall string table math bit32 coroutine io os debug package __index __newindex __call __add __sub __mul __div __mod __pow __unm __concat __len __eq __lt __le __gc __mode "
		"byte char dump find format gmatch gsub len lower match rep reverse sub upper abs acos asin atan atan2 ceil cos cosh deg exp floor fmod frexp ldexp log log10 max min modf pow rad random randomseed sin sinh sqrt tan tanh arshift band bnot bor btest bxor extract lrotate lshift replace rrotate rshift shift string.byte string.char string.dump string.find string.format string.gmatch string.gsub string.len string.lower string.match string.rep string.reverse string.sub string.upper table.concat table.insert table.maxn table.pack table.remove table.sort table.unpack math.abs math.acos math.asin math.atan math.atan2 math.ceil math.cos math.cosh math.deg math.exp math.floor math.fmod math.frexp math.huge math.ldexp math.log math.log10 math.max math.min math.modf math.pi math.pow math.rad math.random math.randomseed math.sin math.sinh math.sqrt math.tan math.tanh bit32.arshift bit32.band bit32.bnot bit32.bor bit32.btest bit32.bxor bit32.extract bit32.lrotate bit32.lshift bit32.replace bit32.rrotate bit32.rshift "
		"close flush lines read seek setvbuf write clock date difftime execute exit getenv remove rename setlocale time tmpname coroutine.create coroutine.resume coroutine.running coroutine.status coroutine.wrap coroutine.yield io.close io.flush io.input io.lines io.open io.output io.popen io.read io.tmpfile io.type io.write io.stderr io.stdin io.stdout os.clock os.date os.difftime os.execute os.exit os.getenv os.remove os.rename os.setlocale os.time os.tmpname debug.debug debug.getfenv debug.gethook debug.getinfo debug.getlocal debug.getmetatable debug.getregistry debug.getupvalue debug.getuservalue debug.setfenv debug.sethook debug.setlocal debug.setmetatable debug.setupvalue debug.setuservalue debug.traceback debug.upvalueid debug.upvaluejoin package.cpath package.loaded package.loaders package.loadlib package.path package.preload package.seeall ";
	// color text
	static SScintillaColors g_rgb_Syntax_lua[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- matlab Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_matlab_language = _T("matlab");
	// extentions
	static CString g_str_matlab_extention = _T("matlab");
	// comment line
	static CString g_str_matlab_commentline = _T("%");
	// comment start
	static CString g_str_matlab_commentStart = _T("");
	// comment end
	static CString g_str_matlab_commentEnd = _T("");
	// keywords
	static const char* g_matlab_KeyWords =
		"break case catch classdef continue else elseif end for function global if otherwise parfor persistent return switch try while ";
	// color text
	static SScintillaColors g_rgb_Syntax_matlab[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- pascal Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_pascal_language = _T("pascal");
	// extentions
	static CString g_str_pascal_extention = _T("pascal");
	// comment line
	static CString g_str_pascal_commentline = _T("//");
	// comment start
	static CString g_str_pascal_commentStart = _T("{");
	// comment end
	static CString g_str_pascal_commentEnd = _T("}");
	// keywords
	static const char* g_pascal_KeyWords =
		"and array asm begin case cdecl class const constructor default destructor div do downto else end end. except exit exports external far file finalization finally for function goto if implementation in index inherited initialization inline interface label library message mod near nil not object of on or out overload overrIDE packed pascal private procedure program property protected public published raise read record register repeat resourcestring safecall set shl shr stdcall stored string then threadvar to try type unit until uses var virtual while with write xor ";
	// color text
	static SScintillaColors g_rgb_Syntax_pascal[] =
	{ { SCE_PAS_DEFAULT,		foregroundMonokai },
	{ SCE_PAS_IDENTIFIER,		foregroundMonokai },
	{ SCE_PAS_COMMENT,			comment },
	{ SCE_PAS_COMMENT2,				comment },
	{ SCE_PAS_COMMENTLINE,				comment },
	{ SCE_PAS_PREPROCESSOR,			builtin },
	{ SCE_PAS_PREPROCESSOR2,				builtin },
	{ SCE_PAS_HEXNUMBER,			number },
	{ SCE_PAS_WORD,				keyword },
	{ SCE_PAS_STRING,				string },
	{ SCE_PAS_STRINGEOL,				yellow },
	{ SCE_PAS_CHARACTER,				yellow },
	{ SCE_PAS_OPERATOR,    builtin },
	{ SCE_PAS_ASM,				red },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- perl Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_perl_language = _T("perl");
	// extentions
	static CString g_str_perl_extention = _T("perl");
	// comment line
	static CString g_str_perl_commentline = _T("#");
	// comment start
	static CString g_str_perl_commentStart = _T("");
	// comment end
	static CString g_str_perl_commentEnd = _T("");
	// keywords
	static const char* g_perl_KeyWords =
		"NULL __FILE__ __LINE__ __PACKAGE__ __DATA__ __END__ AUTOLOAD BEGIN CORE DESTROY END EQ GE GT INIT LE LT NE CHECK abs accept alarm and atan2 bind binmode bless caller chdir chmod chomp chop chown chr chroot close closedir cmp connect continue cos crypt dbmclose dbmopen defined delete die do dump each else elsif endgrent endhostent endnetent endprotoent endpwent endservent eof eq eval exec exists exit exp fcntl fileno flock for foreach fork format formline ge getc getgrent getgrgid getgrnam gethostbyaddr gethostbyname gethostent getlogin getnetbyaddr getnetbyname getnetent getpeername getpgrp getppid getpriority getprotobyname getprotobynumber getprotoent getpwent getpwnam getpwuid getservbyname getservbyport getservent getsockname getsockopt glob gmtime goto grep gt hex if index int ioctl join keys kill last lc lcfirst le length link listen local localtime lock log lstat lt m map mkdir msgctl msgget msgrcv msgsnd my ne next no not oct open opendir or ord our pack package pipe pop pos print printf prototype push q qq qr quotemeta qu qw qx rand read readdir readline readlink readpipe recv redo ref rename require reset return reverse rewinddir rindex rmdir s scalar seek seekdir select semctl semget semop send setgrent sethostent setnetent setpgrp setpriority setprotoent setpwent setservent setsockopt shift shmctl shmget shmread shmwrite shutdown sin sleep socket socketpair sort splice split sprintf sqrt srand stat study sub substr symlink syscall sysopen sysread sysseek system syswrite tell telldir tie tied time times tr truncate uc ucfirst umask undef unless unlink unpack unshift untie until use utime values vec wait waitpid wantarray warn while write x xor y ";
	// color text
	static SScintillaColors g_rgb_Syntax_perl[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- php Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_php_language = _T("php");
	// extentions
	static CString g_str_php_extention = _T("php");
	// comment line
	static CString g_str_php_commentline = _T("//");
	// comment start
	static CString g_str_php_commentStart = _T("/*");
	// comment end
	static CString g_str_php_commentEnd = _T("*/");
	// keywords
	static const char* g_php_KeyWords =
	"__autoload __class__ __compiler_halt_offset__ __construct __destruct __dir__ __file__ __function__ __halt_compiler __line__ __method__ __namespace__ __sleep __trait__ __wakeup _cookie _files _get _post abday_1 abday_2 abday_3 abday_4 abday_5 abday_6 abday_7 abmon_1 abmon_10 abmon_11 abmon_12 abmon_2 abmon_3 abmon_4 abmon_5 abmon_6 abmon_7 abmon_8 abmon_9 abs abstract acos acosh addcslashes addslashes af_inet af_inet6 af_unix al_bits al_buffer al_channels al_cone_inner_angle al_cone_outer_angle al_cone_outer_gain al_direction al_false al_format_mono16 al_format_mono8 al_format_stereo16 al_format_stereo8 al_frequency al_gain al_initial al_looping al_max_distance al_max_gain al_min_gain al_orientation al_paused al_pitch al_playing al_position al_reference_distance al_rolloff_factor al_size al_source_relative al_source_state al_stopped al_true al_velocity alc_frequency alc_refresh alc_sync alt_digits am_str and apache_child_terminate apache_get_modules apache_get_version apache_getenv apache_lookup_uri apache_map apache_note apache_request_headers apache_reset_timeout apache_response_headers apache_setenv apc_add apc_bin_dump apc_bin_dumpfile apc_bin_load apc_bin_loadfile apc_bin_verify_crc32 apc_bin_verify_md5 apc_cache_info apc_cas apc_clear_cache apc_compile_file apc_dec apc_define_constants apc_delete apc_delete_file apc_exists apc_fetch apc_inc apc_iter_all apc_iter_atime apc_iter_ctime apc_iter_device apc_iter_dtime apc_iter_filename apc_iter_inode apc_iter_key apc_iter_md5 apc_iter_mem_size apc_iter_mtime apc_iter_none apc_iter_num_hits apc_iter_refcount apc_iter_ttl apc_iter_type apc_iter_value apc_list_active apc_list_deleted apc_load_constants apc_sma_info apc_store apd_breakpoint apd_callstack apd_clunk apd_continue apd_croak apd_dump_function_table apd_dump_persistent_resources apd_dump_regular_resources apd_echo apd_get_active_symbols apd_set_pprof_trace apd_set_session apd_set_session_trace apd_set_session_trace_socket apd_version args_trace array array_change_key_case array_chunk array_column array_combine array_count_values array_diff array_diff_assoc array_diff_key array_diff_uassoc array_diff_ukey array_fill array_fill_keys array_filter array_filter_use_both array_filter_use_key array_flip array_intersect array_intersect_assoc array_intersect_key array_intersect_uassoc array_intersect_ukey array_key_exists array_keys array_map array_merge array_merge_recursive array_multisort array_pad array_pop array_product array_push array_rand array_reduce array_replace array_replace_recursive array_reverse array_search array_shift array_slice array_sort array_splice array_sum array_udiff array_udiff_assoc array_udiff_uassoc array_uintersect array_uintersect_assoc array_uintersect_uassoc array_unique array_unshift array_values array_walk array_walk_recursive arrayaccess arrayiterator arrayobject arsort as asin asinh asort assert assert_active assert_bail assert_callback assert_options assert_quiet_eval assert_warning assignment_trace atan atan2 atanh base64_decode base64_encode base_convert basename bbcode_add_element bbcode_add_smiley bbcode_arg_double_quote bbcode_arg_html_quote bbcode_arg_quote_escaping bbcode_arg_single_quote bbcode_auto_correct bbcode_correct_reopen_tags bbcode_create bbcode_default_smileys_off bbcode_default_smileys_on bbcode_destroy bbcode_disable_tree_build bbcode_flags_arg_parsing bbcode_flags_cdata_not_allowed bbcode_flags_deny_reopen_child bbcode_flags_one_open_per_level bbcode_flags_remove_if_empty bbcode_flags_smileys_off bbcode_flags_smileys_on bbcode_force_smileys_off bbcode_parse bbcode_set_arg_parser bbcode_set_flags bbcode_set_flags_add bbcode_set_flags_remove bbcode_set_flags_set bbcode_smileys_case_insensitive bbcode_type_arg bbcode_type_noarg bbcode_type_optarg bbcode_type_root bbcode_type_single bcadd bccomp bcdiv bcmod bcmul bcompiler_load bcompiler_load_exe bcompiler_parse_class bcompiler_read bcompiler_write_class bcompiler_write_constant bcompiler_write_exe_footer bcompiler_write_file bcompiler_write_footer bcompiler_write_function bcompiler_write_functions_from_file bcompiler_write_header bcompiler_write_included_filename bcpow bcpowmod bcscale bcsqrt bcsub bin2hex bind_textdomain_codeset bindec bindtextdomain blenc_encrypt blenc_ext_version bool boolean boolval break bson_decode bson_encode bus_adraln bus_adrerr bus_objerr bzclose bzcompress bzdecompress bzerrno bzerror bzerrstr bzflush bzopen bzread bzwrite cairo_antialias_default cairo_antialias_gray cairo_antialias_none cairo_antialias_subpixel cairo_content_alpha cairo_content_color cairo_content_color_alpha cairo_create cairo_extend_none cairo_extend_pad cairo_extend_reflect cairo_extend_repeat cairo_fill_rule_even_odd cairo_fill_rule_winding cairo_filter_best cairo_filter_bilinear cairo_filter_fast cairo_filter_gaussian cairo_filter_good cairo_filter_nearest cairo_font_face_get_type cairo_font_face_status cairo_font_options_create cairo_font_options_equal cairo_font_options_get_antialias cairo_font_options_get_hint_metrics cairo_font_options_get_hint_style cairo_font_options_get_subpixel_order cairo_font_options_hash cairo_font_options_merge cairo_font_options_set_antialias cairo_font_options_set_hint_metrics cairo_font_options_set_hint_style cairo_font_options_set_subpixel_order cairo_font_options_status cairo_font_slant_italic cairo_font_slant_normal cairo_font_slant_oblique cairo_font_type_ft cairo_font_type_quartz cairo_font_type_toy cairo_font_type_win32 cairo_font_weight_bold cairo_font_weight_normal cairo_format_a1 cairo_format_a8 cairo_format_argb32 cairo_format_rgb24 cairo_format_strIDE_for_width cairo_hint_metrics_default cairo_hint_metrics_off cairo_hint_metrics_on cairo_hint_style_default cairo_hint_style_full cairo_hint_style_medium cairo_hint_style_none cairo_hint_style_slight cairo_image_surface_create cairo_image_surface_create_for_data cairo_image_surface_create_from_png cairo_image_surface_get_data cairo_image_surface_get_format cairo_image_surface_get_height cairo_image_surface_get_strIDE cairo_image_surface_get_width cairo_line_cap_butt cairo_line_cap_round cairo_line_cap_square cairo_line_join_bevel cairo_line_join_miter cairo_line_join_round cairo_matrix_create_scale cairo_matrix_create_translate cairo_matrix_invert cairo_matrix_multiply cairo_matrix_rotate cairo_matrix_transform_distance cairo_matrix_transform_point cairo_matrix_translate cairo_operator_add cairo_operator_atop cairo_operator_clear cairo_operator_dest cairo_operator_dest_atop cairo_operator_dest_in cairo_operator_dest_out cairo_operator_dest_over cairo_operator_in cairo_operator_out cairo_operator_over cairo_operator_saturate cairo_operator_source cairo_operator_xor cairo_pattern_add_color_stop_rgb cairo_pattern_add_color_stop_rgba cairo_pattern_create_for_surface cairo_pattern_create_linear cairo_pattern_create_radial cairo_pattern_create_rgb cairo_pattern_create_rgba cairo_pattern_get_color_stop_count cairo_pattern_get_color_stop_rgba cairo_pattern_get_extend cairo_pattern_get_filter cairo_pattern_get_linear_points cairo_pattern_get_matrix cairo_pattern_get_radial_circles cairo_pattern_get_rgba cairo_pattern_get_surface cairo_pattern_get_type cairo_pattern_set_extend cairo_pattern_set_filter cairo_pattern_set_matrix cairo_pattern_status cairo_pattern_type_linear cairo_pattern_type_radial cairo_pattern_type_solid cairo_pattern_type_surface cairo_pdf_surface_create cairo_pdf_surface_set_size cairo_ps_get_levels cairo_ps_level_2 cairo_ps_level_3 cairo_ps_level_to_string cairo_ps_surface_create cairo_ps_surface_dsc_begin_page_setup cairo_ps_surface_dsc_begin_setup cairo_ps_surface_dsc_comment cairo_ps_surface_get_eps cairo_ps_surface_restrict_to_level cairo_ps_surface_set_eps cairo_ps_surface_set_size cairo_scaled_font_create cairo_scaled_font_extents cairo_scaled_font_get_ctm cairo_scaled_font_get_font_face cairo_scaled_font_get_font_matrix cairo_scaled_font_get_font_options cairo_scaled_font_get_scale_matrix cairo_scaled_font_get_type cairo_scaled_font_glyph_extents cairo_scaled_font_status cairo_scaled_font_text_extents cairo_status_clip_not_representable cairo_status_file_not_found cairo_status_invalid_content cairo_status_invalid_dash cairo_status_invalid_dsc_comment cairo_status_invalid_format cairo_status_invalid_index cairo_status_invalid_matrix cairo_status_invalid_path_data cairo_status_invalid_pop_group cairo_status_invalid_restore cairo_status_invalid_status cairo_status_invalid_strIDE cairo_status_invalid_string cairo_status_invalid_visual cairo_status_no_current_point cairo_status_no_memory cairo_status_null_pointer cairo_status_pattern_type_mismatch cairo_status_read_error cairo_status_success cairo_status_surface_finished cairo_status_surface_type_mismatch cairo_status_temp_file_error cairo_status_write_error cairo_subpixel_order_bgr cairo_subpixel_order_default cairo_subpixel_order_rgb cairo_subpixel_order_vbgr cairo_subpixel_order_vrgb cairo_surface_copy_page cairo_surface_create_similar cairo_surface_finish cairo_surface_flush cairo_surface_get_content cairo_surface_get_device_offset cairo_surface_get_font_options cairo_surface_get_type cairo_surface_mark_dirty cairo_surface_mark_dirty_rectangle cairo_surface_set_device_offset cairo_surface_set_fallback_resolution cairo_surface_show_page cairo_surface_status cairo_surface_type_beos cairo_surface_type_directfb cairo_surface_type_glitz cairo_surface_type_image cairo_surface_type_os2 cairo_surface_type_pdf cairo_surface_type_ps cairo_surface_type_quartz cairo_surface_type_quartz_image cairo_surface_type_svg cairo_surface_type_win32 cairo_surface_type_win32_printing cairo_surface_type_xcb cairo_surface_type_xlib cairo_surface_write_to_png cairo_svg_surface_create cairo_svg_surface_restrict_to_version cairo_svg_version_1_1 cairo_svg_version_1_2 "
	"cairo_svg_version_to_string cal_days_in_month cal_dow_dayno cal_dow_long cal_dow_short cal_easter_always_gregorian cal_easter_always_julian cal_easter_default cal_easter_roman cal_french cal_from_jd cal_gregorian cal_info cal_jewish cal_jewish_add_alafim cal_jewish_add_alafim_geresh cal_jewish_add_gereshayim cal_julian cal_month_french cal_month_gregorian_long cal_month_gregorian_short cal_month_jewish cal_month_julian_long cal_month_julian_short cal_num_cals cal_to_jd calcul_hmac calculhmac call_user_func call_user_func_array call_user_method call_user_method_array callable case case_lower case_upper catch ceil cfunction char_max chdb_create chdir checkdate checkdnsrr chgrp chmod chop chown chr chroot chunk_split cl_expunge class class_alias class_exists class_implements class_parents class_uses cld_continued cld_dumped cld_exited cld_killed cld_stopped cld_trapped clearstatcache cli_get_process_title cli_set_process_title clone closedir closelog clsctx_all clsctx_inproc_handler clsctx_inproc_server clsctx_local_server clsctx_remote_server clsctx_server codeset collator_asort collator_compare collator_create collator_get_attribute collator_get_error_code collator_get_error_message collator_get_locale collator_get_sort_key collator_get_strength collator_set_attribute collator_set_strength collator_sort collator_sort_with_sort_keys com_create_guid com_event_sink com_get com_get_active_object com_invoke com_load com_load_typelib com_message_pump com_print_typeinfo com_propget com_propput com_set compact connection_aborted connection_normal connection_status connection_timeout const constant continue convert_cyr_string convert_uudecode convert_uuencode copy cos cosh count count_chars count_normal count_recursive cp_acp cp_maccp cp_move cp_oemcp cp_symbol cp_thread_acp cp_uid cp_utf7 cp_utf8 crc32 create_function credits_all credits_docs credits_fullpage credits_general credits_group credits_modules credits_qa credits_sapi crncystr crypt crypt_blowfish crypt_ext_des crypt_md5 crypt_salt_length crypt_sha256 crypt_sha512 crypt_std_des ctype_alnum ctype_alpha ctype_cntrl ctype_digit ctype_graph ctype_lower ctype_print ctype_punct ctype_space ctype_upper ctype_xdigit cubrid_affected_rows cubrid_assoc cubrid_async cubrid_autocommit_false cubrid_autocommit_true cubrid_bind cubrid_both cubrid_client_encoding cubrid_close cubrid_close_prepare cubrid_close_request cubrid_col_get cubrid_col_size cubrid_column_names cubrid_column_types cubrid_commit cubrid_connect cubrid_connect_with_url cubrid_current_oid cubrid_cursor_current cubrid_cursor_error cubrid_cursor_first cubrid_cursor_last cubrid_cursor_success cubrid_data_seek cubrid_db_name cubrid_disconnect cubrid_drop cubrid_errno cubrid_error cubrid_error_code cubrid_error_code_facility cubrid_error_msg cubrid_exec_query_all cubrid_execute cubrid_facility_cas cubrid_facility_cci cubrid_facility_client cubrid_facility_dbms cubrid_fetch cubrid_fetch_array cubrid_fetch_assoc cubrid_fetch_field cubrid_fetch_lengths cubrid_fetch_object cubrid_fetch_row cubrid_field_flags cubrid_field_len cubrid_field_name cubrid_field_seek cubrid_field_table cubrid_field_type cubrid_free_result cubrid_get cubrid_get_autocommit cubrid_get_charset cubrid_get_class_name cubrid_get_client_info cubrid_get_db_parameter cubrid_get_query_timeout cubrid_get_server_info cubrid_include_oid cubrid_insert_id cubrid_is_instance cubrid_list_dbs cubrid_lob cubrid_lob2_bind cubrid_lob2_close cubrid_lob2_export cubrid_lob2_import cubrid_lob2_new cubrid_lob2_read cubrid_lob2_seek cubrid_lob2_seek64 cubrid_lob2_size cubrid_lob2_size64 cubrid_lob2_tell cubrid_lob2_tell64 cubrid_lob2_write cubrid_lob_close cubrid_lob_export cubrid_lob_get cubrid_lob_send cubrid_lob_size cubrid_lock_read cubrid_lock_write cubrid_move_cursor cubrid_next_result cubrid_no_more_data cubrid_num cubrid_num_cols cubrid_num_fields cubrid_num_rows cubrid_object cubrid_param_isolation_level cubrid_param_lock_timeout cubrid_pconnect cubrid_pconnect_with_url cubrid_ping cubrid_prepare cubrid_put cubrid_query cubrid_real_escape_string cubrid_result cubrid_rollback cubrid_sch_attr_privilege cubrid_sch_attribute cubrid_sch_class cubrid_sch_class_attribute cubrid_sch_class_method cubrid_sch_class_privilege cubrid_sch_constraint cubrid_sch_cross_reference cubrid_sch_direct_super_class cubrid_sch_exported_keys cubrid_sch_imported_keys cubrid_sch_method cubrid_sch_method_file cubrid_sch_primary_key cubrid_sch_query_spec cubrid_sch_subclass cubrid_sch_superclass cubrid_sch_trigger cubrid_sch_vclass cubrid_schema cubrid_seq_drop cubrid_seq_insert cubrid_seq_put cubrid_set_add cubrid_set_autocommit cubrid_set_db_parameter cubrid_set_drop cubrid_set_query_timeout cubrid_unbuffered_query cubrid_version curl_close curl_copy_handle curl_errno curl_error curl_escape curl_exec curl_file_create curl_fnmatchfunc_fail curl_fnmatchfunc_match curl_fnmatchfunc_nomatch curl_getinfo curl_http_version_1_0 curl_http_version_1_1 curl_http_version_2_0 curl_http_version_none curl_init curl_ipresolve_v4 curl_ipresolve_v6 curl_ipresolve_whatever curl_lock_data_cookie curl_lock_data_dns curl_lock_data_ssl_session curl_multi_add_handle curl_multi_close curl_multi_exec curl_multi_getcontent curl_multi_info_read curl_multi_init curl_multi_remove_handle curl_multi_select curl_multi_setopt curl_multi_strerror curl_netrc_ignored curl_netrc_optional curl_netrc_required curl_pause curl_readfunc_pause curl_reset curl_rtspreq_announce curl_rtspreq_describe curl_rtspreq_get_parameter curl_rtspreq_options curl_rtspreq_pause curl_rtspreq_play curl_rtspreq_receive curl_rtspreq_record curl_rtspreq_set_parameter curl_rtspreq_setup curl_rtspreq_teardown curl_setopt curl_setopt_array curl_share_close curl_share_init curl_share_setopt curl_sslversion_default curl_sslversion_sslv2 curl_sslversion_sslv3 curl_sslversion_tlsv1 curl_sslversion_tlsv1_0 curl_sslversion_tlsv1_1 curl_sslversion_tlsv1_2 curl_strerror curl_timecond_ifmodsince curl_timecond_ifunmodsince curl_timecond_lastmod curl_timecond_none curl_tlsauth_srp curl_unescape curl_version curl_version_http2 curl_version_ipv6 curl_version_kerberos4 curl_version_libz curl_version_ssl curl_wrappers_enabled curl_writefunc_pause curlauth_any curlauth_anysafe curlauth_basic curlauth_digest curlauth_digest_ie curlauth_gssnegotiate curlauth_none curlauth_ntlm curlauth_only curlclosepolicy_callback curlclosepolicy_least_recently_used curlclosepolicy_least_traffic curlclosepolicy_oldest curlclosepolicy_slowest curle_aborted_by_callback curle_bad_calling_order curle_bad_content_encoding curle_bad_download_resume curle_bad_function_argument curle_bad_password_entered curle_couldnt_connect curle_couldnt_resolve_host curle_couldnt_resolve_proxy curle_failed_init curle_file_couldnt_read_file curle_filesize_exceeded curle_ftp_access_denied curle_ftp_bad_download_resume curle_ftp_cant_get_host curle_ftp_cant_reconnect curle_ftp_couldnt_get_size curle_ftp_couldnt_retr_file curle_ftp_couldnt_set_ascii curle_ftp_couldnt_set_binary curle_ftp_couldnt_stor_file curle_ftp_couldnt_use_rest curle_ftp_partial_file curle_ftp_port_failed curle_ftp_quote_error curle_ftp_ssl_failed curle_ftp_user_password_incorrect curle_ftp_weird_227_format curle_ftp_weird_pass_reply curle_ftp_weird_pasv_reply curle_ftp_weird_server_reply curle_ftp_weird_user_reply curle_ftp_write_error curle_function_not_found curle_got_nothing curle_http_not_found curle_http_port_failed curle_http_post_error curle_http_range_error curle_http_returned_error curle_ldap_cannot_bind curle_ldap_invalid_url curle_ldap_search_failed curle_library_not_found curle_malformat_user curle_obsolete curle_ok curle_operation_timedout curle_operation_timeouted curle_out_of_memory curle_partial_file curle_read_error curle_recv_error curle_send_error curle_share_in_use curle_ssh curle_ssl_cacert curle_ssl_certproblem curle_ssl_cipher curle_ssl_connect_error curle_ssl_engine_notfound curle_ssl_engine_setfailed curle_ssl_peer_certificate curle_telnet_option_syntax curle_too_many_redirects curle_unknown_telnet_option curle_unsupported_protocol curle_url_malformat curle_url_malformat_user curle_write_error curlftpauth_default curlftpauth_ssl curlftpauth_tls curlftpmethod_multicwd curlftpmethod_nocwd curlftpmethod_singlecwd curlftpssl_all curlftpssl_ccc_active curlftpssl_ccc_none curlftpssl_ccc_passive curlftpssl_control curlftpssl_none curlftpssl_try curlgssapi_delegation_flag curlgssapi_delegation_policy_flag curlinfo_appconnect_time curlinfo_certinfo curlinfo_condition_unmet curlinfo_connect_time curlinfo_content_length_download curlinfo_content_length_upload curlinfo_content_type curlinfo_cookielist curlinfo_effective_url curlinfo_filetime curlinfo_ftp_entry_path curlinfo_header_out curlinfo_header_size curlinfo_http_code curlinfo_http_connectcode curlinfo_httpauth_avail curlinfo_lastone curlinfo_local_ip curlinfo_local_port curlinfo_namelookup_time curlinfo_num_connects curlinfo_os_errno curlinfo_pretransfer_time curlinfo_primary_ip curlinfo_primary_port curlinfo_private curlinfo_proxyauth_avail curlinfo_redirect_count curlinfo_redirect_time curlinfo_redirect_url curlinfo_request_size curlinfo_response_code curlinfo_rtsp_client_cseq curlinfo_rtsp_cseq_recv curlinfo_rtsp_server_cseq curlinfo_rtsp_session_id curlinfo_size_download curlinfo_size_upload curlinfo_speed_download curlinfo_speed_upload curlinfo_ssl_engines curlinfo_ssl_verifyresult curlinfo_starttransfer_time curlinfo_total_time curlm_bad_easy_handle curlm_bad_handle curlm_call_multi_perform curlm_internal_error curlm_ok curlm_out_of_memory curlmopt_maxconnects curlmopt_pipelining curlmsg_done curlopt_accept_encoding curlopt_accepttimeout_ms curlopt_address_scope curlopt_append curlopt_autoreferer curlopt_binarytransfer curlopt_buffersize curlopt_cainfo "
	"curlopt_capath curlopt_certinfo curlopt_closepolicy curlopt_connect_only curlopt_connecttimeout curlopt_connecttimeout_ms curlopt_cookie curlopt_cookiefile curlopt_cookiejar curlopt_cookielist curlopt_cookiesession curlopt_crlf curlopt_crlfile curlopt_customrequest curlopt_dirlistonly curlopt_dns_cache_timeout curlopt_dns_servers curlopt_dns_use_global_cache curlopt_egdsocket curlopt_encoding curlopt_failonerror curlopt_file curlopt_filetime curlopt_fnmatch_function curlopt_followlocation curlopt_forbid_reuse curlopt_fresh_connect curlopt_ftp_account curlopt_ftp_alternative_to_user curlopt_ftp_create_missing_dirs curlopt_ftp_filemethod curlopt_ftp_response_timeout curlopt_ftp_skip_pasv_ip curlopt_ftp_ssl curlopt_ftp_ssl_ccc curlopt_ftp_use_eprt curlopt_ftp_use_epsv curlopt_ftp_use_pret curlopt_ftpappend curlopt_ftpascii curlopt_ftplistonly curlopt_ftpport curlopt_ftpsslauth curlopt_gssapi_delegation curlopt_header curlopt_headerfunction curlopt_http200aliases curlopt_http_content_decoding curlopt_http_transfer_decoding curlopt_http_version curlopt_httpauth curlopt_httpget curlopt_httpheader curlopt_httpproxytunnel curlopt_ignore_content_length curlopt_infile curlopt_infilesize curlopt_interface curlopt_ipresolve curlopt_issuercert curlopt_keypasswd curlopt_krb4level curlopt_krblevel curlopt_localport curlopt_localportrange curlopt_low_speed_limit curlopt_low_speed_time curlopt_mail_auth curlopt_mail_from curlopt_mail_rcpt curlopt_max_recv_speed_large curlopt_max_send_speed_large curlopt_maxconnects curlopt_maxfilesize curlopt_maxredirs curlopt_mute curlopt_netrc curlopt_netrc_file curlopt_new_directory_perms curlopt_new_file_perms curlopt_nobody curlopt_noprogress curlopt_noproxy curlopt_nosignal curlopt_passwdfunction curlopt_password curlopt_port curlopt_post curlopt_postfields curlopt_postquote curlopt_postredir curlopt_prequote curlopt_private curlopt_progressfunction curlopt_protocols curlopt_proxy curlopt_proxy_transfer_mode curlopt_proxyauth curlopt_proxypassword curlopt_proxyport curlopt_proxytype curlopt_proxyusername curlopt_proxyuserpwd curlopt_put curlopt_quote curlopt_random_file curlopt_range curlopt_readdata curlopt_readfunction curlopt_redir_protocols curlopt_referer curlopt_resolve curlopt_resume_from curlopt_returntransfer curlopt_rtsp_client_cseq curlopt_rtsp_request curlopt_rtsp_server_cseq curlopt_rtsp_session_id curlopt_rtsp_stream_uri curlopt_rtsp_transport curlopt_safe_upload curlopt_share curlopt_socks5_gssapi_nec curlopt_socks5_gssapi_service curlopt_ssh_auth_types curlopt_ssh_host_public_key_md5 curlopt_ssh_knownhosts curlopt_ssh_private_keyfile curlopt_ssh_public_keyfile curlopt_ssl_cipher_list curlopt_ssl_options curlopt_ssl_sessionid_cache curlopt_ssl_verifyhost curlopt_ssl_verifypeer curlopt_sslcert curlopt_sslcertpasswd curlopt_sslcerttype curlopt_sslengine curlopt_sslengine_default curlopt_sslkey curlopt_sslkeypasswd curlopt_sslkeytype curlopt_sslversion curlopt_stderr curlopt_tcp_keepalive curlopt_tcp_keepidle curlopt_tcp_keepintvl curlopt_tcp_nodelay curlopt_telnetoptions curlopt_tftp_blksize curlopt_timecondition curlopt_timeout curlopt_timeout_ms curlopt_timevalue curlopt_tlsauth_password curlopt_tlsauth_type curlopt_tlsauth_username curlopt_transfer_encoding curlopt_transfertext curlopt_unrestricted_auth curlopt_upload curlopt_url curlopt_use_ssl curlopt_useragent curlopt_username curlopt_userpwd curlopt_verbose curlopt_wildcardmatch curlopt_writefunction curlopt_writeheader curlpause_all curlpause_cont curlpause_recv curlpause_recv_cont curlpause_send curlpause_send_cont curlproto_all curlproto_dict curlproto_file curlproto_ftp curlproto_ftps curlproto_gopher curlproto_http curlproto_https curlproto_imap curlproto_imaps curlproto_ldap curlproto_ldaps curlproto_pop3 curlproto_pop3s curlproto_rtmp curlproto_rtmpe curlproto_rtmps curlproto_rtmpt curlproto_rtmpte curlproto_rtmpts curlproto_rtsp curlproto_scp curlproto_sftp curlproto_smtp curlproto_smtps curlproto_telnet curlproto_tftp curlproxy_http curlproxy_socks4 curlproxy_socks4a curlproxy_socks5 curlproxy_socks5_hostname curlshopt_none curlshopt_share curlshopt_unshare curlssh_auth_any curlssh_auth_default curlssh_auth_host curlssh_auth_keyboard curlssh_auth_none curlssh_auth_password curlssh_auth_publickey curlsslopt_allow_beast curlusessl_all curlusessl_control curlusessl_none curlusessl_try curlversion_now currency_symbol current cyrus_authenticate cyrus_bind cyrus_callback_noliteral cyrus_callback_numbered cyrus_close cyrus_conn_initialresponse cyrus_conn_nonsyncliteral cyrus_connect cyrus_query cyrus_unbind d_fmt d_t_fmt date date_add date_atom date_cookie date_create date_create_from_format date_create_immutable date_create_immutable_from_format date_date_set date_default_timezone_get date_default_timezone_set date_diff date_format date_get_last_errors date_interval_create_from_date_string date_interval_format date_iso8601 date_isodate_set date_modify date_offset_get date_parse date_parse_from_format date_rfc1036 date_rfc1123 date_rfc2822 date_rfc3339 date_rfc822 date_rfc850 date_rss date_sub date_sun_info date_sunrise date_sunset date_time_set date_timestamp_get date_timestamp_set date_timezone_get date_timezone_set date_w3c datefmt_create datefmt_format datefmt_get_calendar datefmt_get_datetype datefmt_get_error_code datefmt_get_error_message datefmt_get_locale datefmt_get_pattern datefmt_get_timetype datefmt_get_timezone_id datefmt_is_lenient datefmt_localtime datefmt_parse datefmt_set_calendar datefmt_set_lenient datefmt_set_pattern datefmt_set_timezone_id day_1 day_2 day_3 day_4 day_5 day_6 day_7 db2_autocommit db2_autocommit_off db2_autocommit_on db2_binary db2_bind_param db2_case_lower db2_case_natural db2_case_upper db2_char db2_client_info db2_close db2_column_privileges db2_columns db2_commit db2_conn_error db2_conn_errormsg db2_connect db2_convert db2_cursor_type db2_deferred_prepare_off db2_deferred_prepare_on db2_double db2_escape_string db2_exec db2_execute db2_fetch_array db2_fetch_assoc db2_fetch_both db2_fetch_object db2_fetch_row db2_field_display_size db2_field_name db2_field_num db2_field_precision db2_field_scale db2_field_type db2_field_width db2_foreign_keys db2_forward_only db2_free_result db2_free_stmt db2_get_option db2_last_insert_id db2_lob_read db2_long db2_next_result db2_num_fields db2_num_rows db2_param_file db2_param_in db2_param_inout db2_param_out db2_passthru db2_pclose db2_pconnect db2_prepare db2_primary_keys db2_procedure_columns db2_procedures db2_result db2_rollback db2_scrollable db2_server_info db2_set_option db2_special_columns db2_statistics db2_stmt_error db2_stmt_errormsg db2_table_privileges db2_tables dba_close dba_delete dba_exists dba_fetch dba_firstkey dba_handlers dba_insert dba_key_split dba_list dba_nextkey dba_open dba_optimize dba_popen dba_replace dba_sync dbase_add_record dbase_close dbase_create dbase_delete_record dbase_get_header_info dbase_get_record dbase_get_record_with_names dbase_numfields dbase_numrecords dbase_open dbase_pack dbase_replace_record dbplus_add dbplus_aql dbplus_chdir dbplus_close dbplus_curr dbplus_err_close dbplus_err_corrupt_tuple dbplus_err_crc dbplus_err_create dbplus_err_dbparse dbplus_err_dbpreexit dbplus_err_dbrunerr dbplus_err_duplicate dbplus_err_empty dbplus_err_eoscan dbplus_err_fifo dbplus_err_length dbplus_err_locked dbplus_err_lseek dbplus_err_magic dbplus_err_malloc dbplus_err_nidx dbplus_err_noerr dbplus_err_nolock dbplus_err_nusers dbplus_err_ontrap dbplus_err_open dbplus_err_panic dbplus_err_perm dbplus_err_pgsize dbplus_err_pipe dbplus_err_preexit dbplus_err_preproc dbplus_err_read dbplus_err_restricted dbplus_err_tcl dbplus_err_unknown dbplus_err_user dbplus_err_version dbplus_err_wait dbplus_err_warning0 dbplus_err_wlocked dbplus_err_wopen dbplus_err_write dbplus_errcode dbplus_errno dbplus_find dbplus_first dbplus_flush dbplus_freealllocks dbplus_freelock dbplus_freerlocks dbplus_getlock dbplus_getunique dbplus_info dbplus_last dbplus_lockrel dbplus_next dbplus_open dbplus_prev dbplus_rchperm dbplus_rcreate dbplus_rcrtexact dbplus_rcrtlike dbplus_resolve dbplus_restorepos dbplus_rkeys dbplus_ropen dbplus_rquery dbplus_rrename dbplus_rsecindex dbplus_runlink dbplus_rzap dbplus_savepos dbplus_setindex dbplus_setindexbynumber dbplus_sql dbplus_tcl dbplus_tremove dbplus_undo dbplus_undoprepare dbplus_unlockrel dbplus_unselect dbplus_update dbplus_xlockrel dbplus_xunlockrel dbx_close dbx_cmp_asc dbx_cmp_desc dbx_cmp_native dbx_cmp_number dbx_cmp_text dbx_colnames_lowercase dbx_colnames_unchanged dbx_colnames_uppercase dbx_compare dbx_connect dbx_error dbx_escape_string dbx_fbsql dbx_fetch_row dbx_mssql dbx_mysql dbx_oci8 dbx_odbc dbx_persistent dbx_pgsql dbx_query dbx_result_assoc dbx_result_index dbx_result_info dbx_result_unbuffered dbx_sort dbx_sqlite dbx_sybasect dcgettext dcngettext debug_backtrace debug_backtrace_ignore_args debug_backtrace_provIDE_object debug_print_backtrace debug_zval_dump decbin dechex decimal_point declare decoct default default_include_path define define_syslog_variables defined deg2rad delete dgettext die dio_close dio_fcntl dio_open dio_read dio_seek dio_stat dio_tcsetattr dio_truncate dio_write dir directory directory_separator dirname disk_free_space disk_total_space diskfreespace disp_e_badindex disp_e_divbyzero disp_e_overflow dl dngettext dns_a dns_a6 dns_aaaa dns_all dns_any dns_check_record dns_cname dns_get_mx dns_get_record dns_hinfo dns_mx dns_naptr dns_ns dns_ptr dns_soa dns_srv dns_txt do dom_hierarchy_request_err dom_import_simplexml dom_index_size_err dom_inuse_attribute_err dom_invalid_access_err dom_invalid_character_err dom_invalid_modification_err dom_invalid_state_err dom_namespace_err dom_no_data_allowed_err dom_no_modification_allowed_err dom_not_found_err "
	"dom_not_supported_err dom_php_err dom_syntax_err dom_validation_err dom_wrong_document_err domstring_size_err double doubleval e_all e_compile_error e_compile_warning e_core_error e_core_warning e_deprecated e_error e_notice e_parse e_recoverable_error e_strict e_user_deprecated e_user_error e_user_notice e_user_warning e_warning each easter_date easter_days echo eio_busy eio_cancel eio_chmod eio_chown eio_close eio_custom eio_dt_blk eio_dt_chr eio_dt_cmp eio_dt_dir eio_dt_door eio_dt_fifo eio_dt_lnk eio_dt_max eio_dt_mpb eio_dt_mpc eio_dt_nam eio_dt_nwk eio_dt_reg eio_dt_sock eio_dt_unknown eio_dt_wht eio_dup2 eio_event_loop eio_falloc_fl_keep_size eio_fallocate eio_fchmod eio_fchown eio_fdatasync eio_fstat eio_fstatvfs eio_fsync eio_ftruncate eio_futime eio_get_event_stream eio_get_last_error eio_grp eio_grp_add eio_grp_cancel eio_grp_limit eio_init eio_link eio_lstat eio_mkdir eio_mknod eio_nop eio_npending eio_nready eio_nreqs eio_nthreads eio_o_append eio_o_creat eio_o_excl eio_o_fsync eio_o_nonblock eio_o_rdonly eio_o_rdwr eio_o_trunc eio_o_wronly eio_open eio_poll eio_pri_default eio_pri_max eio_pri_min eio_read eio_readahead eio_readdir eio_readdir_dents eio_readdir_dirs_first eio_readdir_found_unknown eio_readdir_stat_order eio_readlink eio_realpath eio_rename eio_rmdir eio_s_ifblk eio_s_ifchr eio_s_ififo eio_s_ifreg eio_s_ifsock eio_s_irgrp eio_s_iroth eio_s_irusr eio_s_iwgrp eio_s_iwoth eio_s_iwusr eio_s_ixgrp eio_s_ixoth eio_s_ixusr eio_seek eio_seek_cur eio_seek_end eio_seek_set eio_sendfile eio_set_max_idle eio_set_max_parallel eio_set_max_poll_reqs eio_set_max_poll_time eio_set_min_parallel eio_stat eio_statvfs eio_symlink eio_sync eio_sync_file_range eio_sync_file_range_wait_after eio_sync_file_range_wait_before eio_sync_file_range_write eio_syncfs eio_truncate eio_unlink eio_utime eio_write else elseif empty enc7bit enc8bit encbase64 encbinary encother encquotedprintable end enddeclare endfor endforeach endif endswitch endwhile ent_compat ent_disallowed ent_html401 ent_html5 ent_ignore ent_noquotes ent_quotes ent_substitute ent_xhtml ent_xml1 era era_d_fmt era_d_t_fmt era_t_fmt era_year ereg ereg_replace eregi eregi_replace error_clear_last error_get_last error_log error_reporting error_trace escapeshellarg escapeshellcmd ev_persist ev_read ev_signal ev_timeout ev_write eval event_add event_base_free event_base_loop event_base_loopbreak event_base_loopexit event_base_new event_base_priority_init event_base_reinit event_base_set event_buffer_base_set event_buffer_disable event_buffer_enable event_buffer_fd_set event_buffer_free event_buffer_new event_buffer_priority_set event_buffer_read event_buffer_set_callback event_buffer_timeout_set event_buffer_watermark_set event_buffer_write event_del event_free event_new event_priority_set event_set event_timer_add event_timer_del event_timer_new event_timer_set evloop_nonblock evloop_once exec exif_imagetype exif_read_data exif_tagname exif_thumbnail exif_use_mbstring exit exp exp_eof exp_exact exp_fullbuffer exp_glob exp_regexp exp_timeout expect_expectl expect_popen explode expm1 extends extension_loaded extr_if_exists extr_overwrite extr_prefix_all extr_prefix_if_exists extr_prefix_invalid extr_prefix_same extr_refs extr_skip extract ezmlm_hash f_dupfd f_getfd f_getfl f_getlk f_getown f_rdlck f_setfl f_setlk f_setlkw f_setown f_unlck f_wrlck false fann_cascadetrain_on_data fann_cascadetrain_on_file fann_clear_scaling_params fann_copy fann_cos fann_cos_symmetric fann_create_from_file fann_create_shortcut fann_create_shortcut_array fann_create_sparse fann_create_sparse_array fann_create_standard fann_create_standard_array fann_create_train fann_create_train_from_callback fann_descale_input fann_descale_output fann_descale_train fann_destroy fann_destroy_train fann_duplicate_train_data fann_e_cant_allocate_mem fann_e_cant_open_config_r fann_e_cant_open_config_w fann_e_cant_open_td_r fann_e_cant_open_td_w fann_e_cant_read_config fann_e_cant_read_connections fann_e_cant_read_neuron fann_e_cant_read_td fann_e_cant_train_activation fann_e_cant_use_activation fann_e_cant_use_train_alg fann_e_index_out_of_bound fann_e_input_no_match fann_e_no_error fann_e_output_no_match fann_e_scale_not_present fann_e_train_data_mismatch fann_e_train_data_subset fann_e_wrong_config_version fann_e_wrong_num_connections fann_elliot fann_elliot_symmetric fann_errorfunc_linear fann_errorfunc_tanh fann_gaussian fann_gaussian_stepwise fann_gaussian_symmetric fann_get_activation_function fann_get_activation_steepness fann_get_bias_array fann_get_bit_fail fann_get_bit_fail_limit fann_get_cascade_activation_functions fann_get_cascade_activation_functions_count fann_get_cascade_activation_steepnesses fann_get_cascade_activation_steepnesses_count fann_get_cascade_candidate_change_fraction fann_get_cascade_candidate_limit fann_get_cascade_candidate_stagnation_epochs fann_get_cascade_max_cand_epochs fann_get_cascade_max_out_epochs fann_get_cascade_min_cand_epochs fann_get_cascade_min_out_epochs fann_get_cascade_num_candidate_groups fann_get_cascade_num_candidates fann_get_cascade_output_change_fraction fann_get_cascade_output_stagnation_epochs fann_get_cascade_weight_multiplier fann_get_connection_array fann_get_connection_rate fann_get_errno fann_get_errstr fann_get_layer_array fann_get_learning_momentum fann_get_learning_rate fann_get_mse fann_get_network_type fann_get_num_input fann_get_num_layers fann_get_num_output fann_get_quickprop_decay fann_get_quickprop_mu fann_get_rprop_decrease_factor fann_get_rprop_delta_max fann_get_rprop_delta_min fann_get_rprop_delta_zero fann_get_rprop_increase_factor fann_get_sarprop_step_error_shift fann_get_sarprop_step_error_threshold_factor fann_get_sarprop_temperature fann_get_sarprop_weight_decay_shift fann_get_total_connections fann_get_total_neurons fann_get_train_error_function fann_get_train_stop_function fann_get_training_algorithm fann_init_weights fann_length_train_data fann_linear fann_linear_piece fann_linear_piece_symmetric fann_merge_train_data fann_nettype_layer fann_nettype_shortcut fann_num_input_train_data fann_num_output_train_data fann_print_error fann_randomize_weights fann_read_train_from_file fann_reset_errno fann_reset_errstr fann_reset_mse fann_run fann_save fann_save_train fann_scale_input fann_scale_input_train_data fann_scale_output fann_scale_output_train_data fann_scale_train fann_scale_train_data fann_set_activation_function fann_set_activation_function_hidden fann_set_activation_function_layer fann_set_activation_function_output fann_set_activation_steepness fann_set_activation_steepness_hidden fann_set_activation_steepness_layer fann_set_activation_steepness_output fann_set_bit_fail_limit fann_set_callback fann_set_cascade_activation_functions fann_set_cascade_activation_steepnesses fann_set_cascade_candidate_change_fraction fann_set_cascade_candidate_limit fann_set_cascade_candidate_stagnation_epochs fann_set_cascade_max_cand_epochs fann_set_cascade_max_out_epochs fann_set_cascade_min_cand_epochs fann_set_cascade_min_out_epochs fann_set_cascade_num_candidate_groups fann_set_cascade_output_change_fraction fann_set_cascade_output_stagnation_epochs fann_set_cascade_weight_multiplier fann_set_error_log fann_set_input_scaling_params fann_set_learning_momentum fann_set_learning_rate fann_set_output_scaling_params fann_set_quickprop_decay fann_set_quickprop_mu fann_set_rprop_decrease_factor fann_set_rprop_delta_max fann_set_rprop_delta_min fann_set_rprop_delta_zero fann_set_rprop_increase_factor fann_set_sarprop_step_error_shift fann_set_sarprop_step_error_threshold_factor fann_set_sarprop_temperature fann_set_sarprop_weight_decay_shift fann_set_scaling_params fann_set_train_error_function fann_set_train_stop_function fann_set_training_algorithm fann_set_weight fann_set_weight_array fann_shuffle_train_data fann_sigmoid fann_sigmoid_stepwise fann_sigmoid_symmetric fann_sigmoid_symmetric_stepwise fann_sin fann_sin_symmetric fann_stopfunc_bit fann_stopfunc_mse fann_subset_train_data fann_test fann_test_data fann_threshold fann_threshold_symmetric fann_train fann_train_batch fann_train_epoch fann_train_incremental fann_train_on_data fann_train_on_file fann_train_quickprop fann_train_rprop fann_train_sarprop fastcgi_finish_request fbsql_affected_rows fbsql_assoc fbsql_autocommit fbsql_blob_size fbsql_both fbsql_change_user fbsql_clob_size fbsql_close fbsql_commit fbsql_connect fbsql_create_blob fbsql_create_clob fbsql_create_db fbsql_data_seek fbsql_database fbsql_database_password fbsql_db_query fbsql_db_status fbsql_drop_db fbsql_errno fbsql_error fbsql_fetch_array fbsql_fetch_assoc fbsql_fetch_field fbsql_fetch_lengths fbsql_fetch_object fbsql_fetch_row fbsql_field_flags fbsql_field_len fbsql_field_name fbsql_field_seek fbsql_field_table fbsql_field_type fbsql_free_result fbsql_get_autostart_info fbsql_hostname fbsql_insert_id fbsql_iso_read_committed fbsql_iso_read_uncommitted fbsql_iso_repeatable_read fbsql_iso_serializable fbsql_iso_versioned fbsql_list_dbs fbsql_list_fields fbsql_list_tables fbsql_lob_direct fbsql_lob_handle fbsql_lock_deferred fbsql_lock_optimistic fbsql_lock_pessimistic fbsql_next_result fbsql_noexec fbsql_num fbsql_num_fields fbsql_num_rows fbsql_password fbsql_pconnect fbsql_query fbsql_read_blob fbsql_read_clob fbsql_result fbsql_rollback fbsql_rows_fetched fbsql_running fbsql_select_db fbsql_set_characterset fbsql_set_lob_mode fbsql_set_password fbsql_set_transaction fbsql_start_db fbsql_starting fbsql_stop_db fbsql_stopped fbsql_stopping fbsql_table_name fbsql_tablename fbsql_unknown fbsql_username fbsql_warnings fclose fdf_add_doc_javascript fdf_add_template fdf_close fdf_create fdf_enum_values fdf_errno fdf_error fdf_get_ap fdf_get_attachment fdf_get_encoding fdf_get_file fdf_get_flags fdf_get_opt "
	"fdf_get_status fdf_get_value fdf_get_version fdf_header fdf_next_field_name fdf_open fdf_open_string fdf_remove_item fdf_save fdf_save_string fdf_set_ap fdf_set_encoding fdf_set_file fdf_set_flags fdf_set_javascript_action fdf_set_on_import_javascript fdf_set_opt fdf_set_status fdf_set_submit_form_action fdf_set_target_frame fdf_set_value fdf_set_version fdfaa fdfaction fdfap fdfapref fdfas fdfcalculate fdfclearff fdfclrf fdfdown fdfdownap fdfenter fdfexit fdfff fdffile fdfflags fdfformat fdfid fdfif fdfkeystroke fdfnormalap fdfrolloverap fdfsetf fdfsetff fdfstatus fdfup fdfvalidate fdfvalue feof fflush fgetc fgetcsv fgets fgetss file file_append file_binary file_exists file_get_contents file_ignore_new_lines file_no_default_context file_put_contents file_skip_empty_lines file_text file_use_include_path fileatime filectime filegroup fileinfo_continue fileinfo_devices fileinfo_mime fileinfo_mime_encoding fileinfo_mime_type fileinfo_none fileinfo_preserve_atime fileinfo_raw fileinfo_symlink fileinode filemtime fileowner fileperms filepro filepro_fieldcount filepro_fieldname filepro_fieldtype filepro_fieldwidth filepro_retrieve filepro_rowcount filesize filetype filter_callback filter_default filter_flag_allow_fraction filter_flag_allow_hex filter_flag_allow_octal filter_flag_allow_scientific filter_flag_allow_thousand filter_flag_empty_string_null filter_flag_encode_amp filter_flag_encode_high filter_flag_encode_low filter_flag_host_required filter_flag_ipv4 filter_flag_ipv6 filter_flag_no_encode_quotes filter_flag_no_priv_range filter_flag_no_res_range filter_flag_none filter_flag_path_required filter_flag_query_required filter_flag_scheme_required filter_flag_strip_backtick filter_flag_strip_high filter_flag_strip_low filter_force_array filter_has_var filter_id filter_input filter_input_array filter_list filter_null_on_failure filter_require_array filter_require_scalar filter_sanitize_email filter_sanitize_encoded filter_sanitize_full_special_chars filter_sanitize_magic_quotes filter_sanitize_number_float filter_sanitize_number_int filter_sanitize_special_chars filter_sanitize_string filter_sanitize_stripped filter_sanitize_url filter_unsafe_raw filter_validate_boolean filter_validate_email filter_validate_float filter_validate_int filter_validate_ip filter_validate_mac filter_validate_regexp filter_validate_url filter_var filter_var_array final finally finfo_buffer finfo_close finfo_file finfo_open finfo_set_flags firebird / interbase float floatval flock floor flush fmod fnm_casefold fnm_noescape fnm_pathname fnm_period fnmatch fopen for force_deflate force_gzip foreach forward_static_call forward_static_call_array fpassthru fpe_fltdiv fpe_fltinv fpe_fltovf fpe_fltres fpe_fltsub fpe_fltund fpe_intdiv fpe_intovf fprintf fputcsv fputs frac_digits fread frenchtojd fscanf fseek fsockopen fstat ft_internal ft_not ft_peek ft_prefetchtext ft_uid ftell ftok ftp_alloc ftp_ascii ftp_autoresume ftp_autoseek ftp_binary ftp_cdup ftp_chdir ftp_chmod ftp_close ftp_connect ftp_delete ftp_exec ftp_failed ftp_fget ftp_finished ftp_fput ftp_get ftp_get_option ftp_image ftp_login ftp_mdtm ftp_mkdir ftp_moredata ftp_nb_continue ftp_nb_fget ftp_nb_fput ftp_nb_get ftp_nb_put ftp_nlist ftp_pasv ftp_put ftp_pwd ftp_quit ftp_raw ftp_rawlist ftp_rename ftp_rmdir ftp_set_option ftp_site ftp_size ftp_ssl_connect ftp_systype ftp_text ftp_timeout_sec ftruncate func_get_arg func_get_args func_num_args function function_exists function_trace fwrite gc_collect_cycles gc_disable gc_enable gc_enabled gd_bundled gd_extra_version gd_info gd_major_version gc_mem_caches gd_minor_version gd_release_version gd_version geoip_asnum_by_name geoip_asnum_edition geoip_cabledsl_speed geoip_city_edition_rev0 geoip_city_edition_rev1 geoip_continent_code_by_name geoip_corporate_speed geoip_country_code3_by_name geoip_country_code_by_name geoip_country_edition geoip_country_name_by_name geoip_database_info geoip_db_avail geoip_db_filename geoip_db_get_all_info geoip_dialup_speed geoip_domain_by_name geoip_domain_edition geoip_id_by_name geoip_isp_by_name geoip_isp_edition geoip_netspeed_edition geoip_netspeedcell_by_name geoip_org_by_name geoip_org_edition geoip_proxy_edition geoip_record_by_name geoip_region_by_name geoip_region_edition_rev0 geoip_region_edition_rev1 geoip_region_name_by_code geoip_setup_custom_directory geoip_time_zone_by_country_and_region geoip_unknown_speed get_browser get_called_class get_cfg_var get_class get_class_methods get_class_vars get_current_user get_declared_classes get_declared_interfaces get_declared_traits get_defined_constants get_defined_functions get_defined_vars get_extension_funcs get_headers get_html_translation_table get_include_path get_included_files get_loaded_extensions get_magic_quotes_gpc get_magic_quotes_runtime get_meta_tags get_object_vars get_parent_class get_required_files get_resource_type get_resources getallheaders getcwd getdate getdir getenv gethostbyaddr gethostbyname gethostbynamel gethostname getimagesize getimagesizefromstring getlastmod getmxrr getmygid getmyinode getmypid getmyuid getopt getprotobyname getprotobynumber getrandmax getrusage getservbyname getservbyport gettext gettimeofday gettype glob glob_available_flags glob_brace glob_err glob_mark glob_nocheck glob_noescape glob_nosort glob_onlydir global globals gmdate gmmktime gmp_abs gmp_add gmp_and gmp_big_endian gmp_clrbit gmp_cmp gmp_com gmp_div gmp_div_q gmp_div_qr gmp_div_r gmp_divexact gmp_export gmp_fact gmp_gcd gmp_gcdext gmp_hamdist gmp_import gmp_init gmp_intval gmp_invert gmp_jacobi gmp_legendre gmp_little_endian gmp_lsw_first gmp_mod gmp_mpir_version gmp_msw_first gmp_mul gmp_native_endian gmp_neg gmp_nextprime gmp_or gmp_perfect_square gmp_popcount gmp_pow gmp_powm gmp_prob_prime gmp_random gmp_random_bits gmp_random_range gmp_random_seed gmp_root gmp_rootrem gmp_round_minusinf gmp_round_plusinf gmp_round_zero gmp_scan0 gmp_scan1 gmp_setbit gmp_sign gmp_sqrt gmp_sqrtrem gmp_strval gmp_sub gmp_testbit gmp_version gmp_xor gmstrftime gnupg_adddecryptkey gnupg_addencryptkey gnupg_addsignkey gnupg_cleardecryptkeys gnupg_clearencryptkeys gnupg_clearsignkeys gnupg_decrypt gnupg_decryptverify gnupg_encrypt gnupg_encryptsign gnupg_error_exception gnupg_error_silent gnupg_error_warning gnupg_export gnupg_geterror gnupg_getprotocol gnupg_import gnupg_init gnupg_keyinfo gnupg_protocol_cms gnupg_protocol_openpgp gnupg_setarmor gnupg_seterrormode gnupg_setsignmode gnupg_sig_mode_clear gnupg_sig_mode_detach gnupg_sig_mode_normal gnupg_sign gnupg_sigsum_bad_policy gnupg_sigsum_crl_missing gnupg_sigsum_crl_too_old gnupg_sigsum_green gnupg_sigsum_key_expired gnupg_sigsum_key_missing gnupg_sigsum_key_revoked gnupg_sigsum_red gnupg_sigsum_sig_expired gnupg_sigsum_sys_error gnupg_sigsum_valid gnupg_validity_full gnupg_validity_marginal gnupg_validity_never gnupg_validity_ultimate gnupg_validity_undefined gnupg_validity_unknown gnupg_verify gopher_binary gopher_binhex gopher_directory gopher_document gopher_dosbinary gopher_http gopher_info gopher_parsedir gopher_unknown gopher_uuencoded goto grapheme_extr_count grapheme_extr_maxbytes grapheme_extr_maxchars grapheme_extract grapheme_stripos grapheme_stristr grapheme_strlen grapheme_strpos grapheme_strripos grapheme_strrpos grapheme_strstr grapheme_substr gregoriantojd grouping gupnp_context_get_host_ip gupnp_context_get_port gupnp_context_get_subscription_timeout gupnp_context_host_path gupnp_context_new gupnp_context_set_subscription_timeout gupnp_context_timeout_add gupnp_context_unhost_path gupnp_control_error_action_failed gupnp_control_error_invalid_action gupnp_control_error_invalid_args gupnp_control_error_out_of_sync gupnp_control_point_browse_start gupnp_control_point_browse_stop gupnp_control_point_callback_set gupnp_control_point_new gupnp_device_action_callback_set gupnp_device_info_get gupnp_device_info_get_service gupnp_root_device_get_available gupnp_root_device_get_relative_location gupnp_root_device_new gupnp_root_device_set_available gupnp_root_device_start gupnp_root_device_stop gupnp_service_action_get gupnp_service_action_return gupnp_service_action_return_error gupnp_service_action_set gupnp_service_freeze_notify gupnp_service_info_get gupnp_service_info_get_introspection gupnp_service_introspection_get_state_variable gupnp_service_notify gupnp_service_proxy_action_get gupnp_service_proxy_action_set gupnp_service_proxy_add_notify gupnp_service_proxy_callback_set gupnp_service_proxy_get_subscribed gupnp_service_proxy_remove_notify gupnp_service_proxy_send_action gupnp_service_proxy_set_subscribed gupnp_service_thaw_notify gupnp_signal_action_invoked gupnp_signal_device_proxy_available gupnp_signal_device_proxy_unavailable gupnp_signal_notify_failed gupnp_signal_service_proxy_available gupnp_signal_service_proxy_unavailable gupnp_signal_subscription_lost gupnp_type_boolean gupnp_type_double gupnp_type_float gupnp_type_int gupnp_type_long gupnp_type_string gzclose gzcompress gzdecode gzdeflate gzencode gzeof gzfile gzgetc gzgets gzgetss gzinflate gzopen gzpassthru gzputs gzread gzrewind gzseek gztell gzuncompress gzwrite hash hash_algos hash_copy hash_equals hash_file hash_final hash_hmac hash_hmac_file hash_init hash_pbkdf2 hash_update hash_update_file hash_update_stream header header_register_callback header_remove headers_list headers_sent hebrev hebrevc hex2bin hexdec highlight_file highlight_string html_entities html_entity_decode html_specialchars htmlentities htmlspecialchars htmlspecialchars_decode http_auth_any http_auth_basic http_auth_digest http_auth_gssneg http_auth_ntlm http_build_cookie http_build_query http_build_str http_build_url http_cache_etag http_cache_last_modified http_chunked_decode http_cookie_httponly http_cookie_parse_raw http_cookie_secure http_date http_deflate http_deflate_level_def "
	"http_deflate_level_max http_deflate_level_min http_deflate_strategy_def http_deflate_strategy_filt http_deflate_strategy_fixed http_deflate_strategy_huff http_deflate_strategy_rle http_deflate_type_gzip http_deflate_type_raw http_deflate_type_zlib http_e_encoding http_e_header http_e_invalid_param http_e_malformed_headers http_e_message_type http_e_querystring http_e_request http_e_request_method http_e_request_pool http_e_response http_e_runtime http_e_socket http_e_url http_encoding_stream_flush_full http_encoding_stream_flush_none http_encoding_stream_flush_sync http_get http_get_request_body http_get_request_body_stream http_get_request_headers http_head http_inflate http_ipresolve_any http_ipresolve_v4 http_ipresolve_v6 http_match_etag http_match_modified http_match_request_header http_meth_acl http_meth_baseline_control http_meth_checkin http_meth_checkout http_meth_connect http_meth_copy http_meth_delete http_meth_get http_meth_head http_meth_label http_meth_lock http_meth_merge http_meth_mkactivity http_meth_mkcol http_meth_mkworkspace http_meth_move http_meth_options http_meth_post http_meth_propfind http_meth_proppatch http_meth_put http_meth_report http_meth_trace http_meth_uncheckout http_meth_unlock http_meth_update http_meth_version_control http_msg_none http_msg_request http_msg_response http_negotiate_charset http_negotiate_content_type http_negotiate_language http_params_allow_comma http_params_allow_failure http_params_default http_params_raise_error http_parse_cookie http_parse_headers http_parse_message http_parse_params http_persistent_handles_clean http_persistent_handles_count http_persistent_handles_IDEnt http_post_data http_post_fields http_proxy_http http_proxy_socks4 http_proxy_socks5 http_put_data http_put_file http_put_stream http_querystring_type_array http_querystring_type_bool http_querystring_type_float http_querystring_type_int http_querystring_type_object http_querystring_type_string http_redirect http_redirect_found http_redirect_perm http_redirect_post http_redirect_proxy http_redirect_temp http_request http_request_body_encode http_request_method_exists http_request_method_name http_request_method_register http_request_method_unregister http_response_code http_send_content_disposition http_send_content_type http_send_data http_send_file http_send_last_modified http_send_status http_send_stream http_ssl_version_any http_ssl_version_sslv2 http_ssl_version_sslv3 http_ssl_version_tlsv1 http_support http_support_encodings http_support_magicmime http_support_requests http_support_sslrequests http_throttle http_url_join_path http_url_join_query http_url_replace http_url_strip_all http_url_strip_auth http_url_strip_fragment http_url_strip_pass http_url_strip_path http_url_strip_port http_url_strip_query http_url_strip_user http_version_1_0 http_version_1_1 http_version_any hypot ibase_add_user ibase_affected_rows ibase_backup ibase_bkp_convert ibase_bkp_ignore_checksums ibase_bkp_ignore_limbo ibase_bkp_metadata_only ibase_bkp_no_garbage_collect ibase_bkp_non_transportable ibase_bkp_old_descriptions ibase_blob_add ibase_blob_cancel ibase_blob_close ibase_blob_create ibase_blob_echo ibase_blob_get ibase_blob_import ibase_blob_info ibase_blob_open ibase_close ibase_commit ibase_commit_ret ibase_committed ibase_concurrency ibase_connect ibase_consistency ibase_db_info ibase_default ibase_delete_user ibase_drop_db ibase_errcode ibase_errmsg ibase_execute ibase_fetch_arrays ibase_fetch_assoc ibase_fetch_blobs ibase_fetch_object ibase_fetch_row ibase_field_info ibase_free_event_handler ibase_free_query ibase_free_result ibase_gen_id ibase_maintain_db ibase_modify_user ibase_name_result ibase_nowait ibase_num_fields ibase_num_params ibase_param_info ibase_pconnect ibase_prepare ibase_prp_access_mode ibase_prp_activate ibase_prp_am_readonly ibase_prp_am_readwrite ibase_prp_db_online ibase_prp_deny_new_attachments ibase_prp_deny_new_transactions ibase_prp_page_buffers ibase_prp_res ibase_prp_res_use_full ibase_prp_reserve_space ibase_prp_set_sql_dialect ibase_prp_shutdown_db ibase_prp_sweep_interval ibase_prp_wm_async ibase_prp_wm_sync ibase_prp_write_mode ibase_query ibase_read ibase_res_create ibase_res_deactivate_idx ibase_res_no_shadow ibase_res_no_validity ibase_res_one_at_a_time ibase_res_replace ibase_res_use_all_space ibase_restore ibase_rollback ibase_rollback_ret ibase_rpr_check_db ibase_rpr_full ibase_rpr_ignore_checksum ibase_rpr_kill_shadows ibase_rpr_mend_db ibase_rpr_sweep_db ibase_rpr_validate_db ibase_server_info ibase_service_attach ibase_service_detach ibase_set_event_handler ibase_sts_data_pages ibase_sts_db_log ibase_sts_hdr_pages ibase_sts_idx_pages ibase_sts_sys_relations ibase_svc_get_env ibase_svc_get_env_lock ibase_svc_get_env_msg ibase_svc_get_users ibase_svc_implementation ibase_svc_server_version ibase_svc_svr_db_info ibase_svc_user_dbpath ibase_trans ibase_unixtime ibase_wait ibase_wait_event ibase_write iconv iconv_get_encoding iconv_impl iconv_mime_decode iconv_mime_decode_continue_on_error iconv_mime_decode_headers iconv_mime_decode_strict iconv_mime_encode iconv_set_encoding iconv_strlen iconv_strpos iconv_strrpos iconv_substr iconv_version id3_best id3_get_frame_long_name id3_get_frame_short_name id3_get_genre_id id3_get_genre_list id3_get_genre_name id3_get_tag id3_get_version id3_remove_tag id3_set_tag id3_v1_0 id3_v1_1 id3_v2_1 id3_v2_2 id3_v2_3 id3_v2_4 idate idn_to_ascii idn_to_unicode idn_to_utf8 idna_allow_unassigned idna_check_bidi idna_check_contextj idna_default idna_error_bidi idna_error_contextj idna_error_disallowed idna_error_domain_name_too_long idna_error_empty_label idna_error_hyphen_3_4 idna_error_invalid_ace_label idna_error_label_has_dot idna_error_label_too_long idna_error_leading_combining_mark idna_error_leading_hyphen idna_error_punycode idna_error_trailing_hyphen idna_nontransitional_to_ascii idna_nontransitional_to_unicode idna_use_std3_rules if ifx_affected_rows ifx_blobinfile_mode ifx_byteasvarchar ifx_close ifx_connect ifx_copy_blob ifx_create_blob ifx_create_char ifx_do ifx_error ifx_errormsg ifx_fetch_row ifx_fieldproperties ifx_fieldtypes ifx_free_blob ifx_free_char ifx_free_result ifx_get_blob ifx_get_char ifx_getsqlca ifx_hold ifx_htmltbl_result ifx_lo_append ifx_lo_buffer ifx_lo_nobuffer ifx_lo_rdonly ifx_lo_rdwr ifx_lo_wronly ifx_nullformat ifx_num_fields ifx_num_rows ifx_pconnect ifx_prepare ifx_query ifx_scroll ifx_textasvarchar ifx_update_blob ifx_update_char ifxus_close_slob ifxus_create_slob ifxus_free_slob ifxus_open_slob ifxus_read_slob ifxus_seek_slob ifxus_tell_slob ifxus_write_slob ignore_user_abort iis_add_server iis_anonymous iis_basic iis_execute iis_get_dir_security iis_get_script_map iis_get_server_by_comment iis_get_server_by_path iis_get_server_rights iis_get_service_state iis_ntlm iis_paused iis_read iis_remove_server iis_running iis_script iis_set_app_settings iis_set_dir_security iis_set_script_map iis_set_server_rights iis_start_server iis_start_service iis_starting iis_stop_server iis_stop_service iis_stopped iis_write ill_badstk ill_coproc ill_illadr ill_illopc ill_illopn ill_illtrp ill_prvopc ill_prvreg image2wbmp image_type_to_extension image_type_to_mime_type imageaffine imageaffinematrixconcat imageaffinematrixget imagealphablending imageantialias imagearc imagechar imagecharup imagecolorallocate imagecolorallocatealpha imagecolorat imagecolorclosest imagecolorclosestalpha imagecolorclosesthwb imagecolordeallocate imagecolorexact imagecolorexactalpha imagecolormatch imagecolorresolve imagecolorresolvealpha imagecolorset imagecolorsforindex imagecolorstotal imagecolortransparent imageconvolution imagecopy imagecopymerge imagecopymergegray imagecopyresampled imagecopyresized imagecreate imagecreatefromgd imagecreatefromgd2 imagecreatefromgd2part imagecreatefromgif imagecreatefromjpeg imagecreatefrompng imagecreatefromstring imagecreatefromwbmp imagecreatefromwebp imagecreatefromxbm imagecreatefromxpm imagecreatetruecolor imagecrop imagecropauto imagedashedline imagedestroy imageellipse imagefill imagefilledarc imagefilledellipse imagefilledpolygon imagefilledrectangle imagefilltoborder imagefilter imageflip imagefontheight imagefontwidth imageftbbox imagefttext imagegammacorrect imagegd imagegd2 imagegif imagegrabscreen imagegrabwindow imageinterlace imageistruecolor imagejpeg imagelayereffect imageline imageloadfont imagepalettecopy imagepalettetotruecolor imagepng imagepolygon imagepsbbox imagepsencodefont imagepsextendfont imagepsfreefont imagepsloadfont imagepsslantfont imagepstext imagerectangle imagerotate imagesavealpha imagescale imagesetbrush imagesetinterpolation imagesetpixel imagesetstyle imagesetthickness imagesettile imagestring imagestringup imagesx imagesy imagetruecolortopalette imagettfbbox imagettftext imagetype_bmp imagetype_count imagetype_gif imagetype_ico imagetype_iff imagetype_jb2 imagetype_jp2 imagetype_jpc imagetype_jpeg imagetype_jpeg2000 imagetype_jpx imagetype_png imagetype_psd imagetype_swc imagetype_swf imagetype_tiff_ii imagetype_tiff_mm imagetype_unknown imagetype_wbmp imagetype_xbm imagetypes imagewbmp imagewebp imagexbm imap_8bit imap_alerts imap_append imap_base64 imap_binary imap_body imap_bodystruct imap_check imap_clearflag_full imap_close imap_closetimeout imap_create imap_createmailbox imap_delete imap_deletemailbox imap_errors imap_expunge imap_fetch_overview imap_fetchbody imap_fetchheader imap_fetchmime imap_fetchstructure imap_fetchtext imap_gc imap_gc_elt imap_gc_env imap_gc_texts imap_get_quota imap_get_quotaroot imap_getacl imap_getmailboxes imap_getsubscribed imap_header imap_headerinfo imap_headers imap_last_error imap_list imap_listmailbox imap_listscan imap_listsubscribed imap_lsub imap_mail imap_mail_compose imap_mail_copy imap_mail_move "
	"imap_mailboxmsginfo imap_mime_header_decode imap_msgno imap_mutf7_to_utf8 imap_num_msg imap_num_recent imap_open imap_opentimeout imap_ping imap_qprint imap_readtimeout imap_rename imap_renamemailbox imap_reopen imap_rfc822_parse_adrlist imap_rfc822_parse_headers imap_rfc822_write_address imap_savebody imap_scan imap_scanmailbox imap_search imap_set_quota imap_setacl imap_setflag_full imap_sort imap_status imap_subscribe imap_thread imap_timeout imap_uid imap_undelete imap_unsubscribe imap_utf7_decode imap_utf7_encode imap_utf8 imap_utf8_to_mutf7 imap_writetimeout img_affine_rotate img_affine_scale img_affine_shear_horizontal img_affine_shear_vertical img_affine_translate img_arc_chord img_arc_edged img_arc_nofill img_arc_pie img_arc_rounded img_bell img_bessel img_bicubic img_bicubic_fixed img_bilinear_fixed img_blackman img_box img_bspline img_catmullrom img_color_brushed img_color_styled img_color_styledbrushed img_color_tiled img_color_transparent img_crop_black img_crop_default img_crop_sIDEs img_crop_threshold img_crop_transparent img_crop_white img_effect_alphablend img_effect_normal img_effect_overlay img_effect_replace img_filter_brightness img_filter_colorize img_filter_contrast img_filter_edgedetect img_filter_emboss img_filter_gaussian_blur img_filter_grayscale img_filter_mean_removal img_filter_negate img_filter_pixelate img_filter_selective_blur img_filter_smooth img_flip_both img_flip_horizontal img_flip_vertical img_gaussian img_gd2_compressed img_gd2_raw img_generalized_cubic img_gif img_hamming img_hanning img_hermite img_jpeg img_jpg img_mitchell img_nearest_neighbour img_png img_power img_quadratic img_sinc img_triangle img_wbmp img_weighted4 img_xpm implements implode import_request_variables in_access in_all_events in_array in_attrib in_close in_close_nowrite in_close_write in_create in_delete in_delete_self in_dont_follow in_ignored in_isdir in_mask_add in_modify in_move in_move_self in_moved_from in_moved_to in_oneshot in_onlydir in_open in_q_overflow in_unmount include include_once inet_ntop inet_pton inf info_all info_configuration info_credits info_environment info_general info_license info_modules info_variables ingres_api_version ingres_assoc ingres_autocommit ingres_autocommit_state ingres_both ingres_charset ingres_close ingres_commit ingres_connect ingres_cursor ingres_cursor_readonly ingres_cursor_update ingres_date_dmy ingres_date_finnish ingres_date_german ingres_date_iso ingres_date_iso4 ingres_date_mdy ingres_date_multinational ingres_date_multinational4 ingres_date_ymd ingres_errno ingres_error ingres_errsqlstate ingres_escape_string ingres_execute ingres_ext_version ingres_fetch_array ingres_fetch_assoc ingres_fetch_object ingres_fetch_proc_return ingres_fetch_row ingres_field_length ingres_field_name ingres_field_nullable ingres_field_precision ingres_field_scale ingres_field_type ingres_free_result ingres_money_leading ingres_money_trailing ingres_next_error ingres_num ingres_num_fields ingres_num_rows ingres_pconnect ingres_prepare ingres_query ingres_result_seek ingres_rollback ingres_set_environment ingres_structure_btree ingres_structure_cbtree ingres_structure_chash ingres_structure_cheap ingres_structure_cisam ingres_structure_hash ingres_structure_heap ingres_structure_isam ingres_unbuffered_query ini_all ini_alter ini_get ini_get_all ini_perdir ini_restore ini_scanner_normal ini_scanner_raw ini_scanner_typed ini_set ini_system ini_user inotify_add_watch inotify_init inotify_queue_len inotify_read inotify_rm_watch input_cookie input_env input_get input_post input_request input_server input_session instanceof insteadof int int_curr_symbol int_frac_digits intdiv integer interface interface_exists intl_error_name intl_get_error_code intl_get_error_message intl_icu_data_version intl_icu_version intl_idna_variant_2003 intl_idna_variant_uts46 intl_is_failure intl_max_locale_len intval ion_clock_skew ion_corrupt_file ion_expired_file ion_license_corrupt ion_license_expired ion_license_header_invalid ion_license_not_found ion_license_property_invalid ion_license_server_invalid ion_no_permissions ion_unauth_append_prepend_file ion_unauth_included_file ion_unauth_including_file ion_untrusted_extension ioncube_check_license_properties ioncube_file_info ioncube_file_is_encoded ioncube_file_not_permissioned ioncube_file_properties ioncube_license_has_expired ioncube_license_matches_server ioncube_license_properties ioncube_licensed_servers ioncube_loader_iversion ioncube_loader_version ioncube_read_file ioncube_server_data ioncube_write_file ip2long ip_multicast_if ip_multicast_loop ip_multicast_ttl ipproto_ip ipproto_ipv6 iptcembed iptcparse ipv6_hoplimit ipv6_multicast_hops ipv6_multicast_if ipv6_multicast_loop "
	"ipv6_pktinfo ipv6_recvhoplimit ipv6_recvpktinfo ipv6_recvtclass ipv6_tclass ipv6_unicast_hops is_a "
	"is_array is_bool is_callable is_dir is_double is_executable is_file is_finite is_float is_infinite "
	"is_int is_integer is_link is_long is_nan is_null is_numeric is_object is_readable is_real "
	"is_resource is_scalar is_soap_fault is_string is_subclass_of is_tainted is_uploaded_file is_writable "
	"is_writeable isset iterator_apply iterator_count iterator_to_array jddayofweek jdmonthname jdtofrench "
	"jdtogregorian jdtojewish jdtojulian jdtounix jewishtojd join jpeg2wbmp json_bigint_as_string json_decode "
	"json_encode json_error_ctrl_char json_error_depth json_error_inf_or_nan json_error_none json_error_recursion "
	"json_error_state_mismatch json_error_syntax json_error_unsupported_type json_error_utf8 json_force_object "
	"json_hex_amp json_hex_apos json_hex_quot json_hex_tag json_last_error json_last_error_msg json_numeric_check "
	"json_object_as_array json_partial_output_on_error json_preserve_zero_fraction json_pretty_print json_unescaped_slashes "
	"json_unescaped_unicode judy_type judy_version juliantojd kadm5_attributes kadm5_chpass_principal kadm5_clearpolicy "
	"kadm5_create_principal kadm5_delete_principal kadm5_destroy kadm5_fail_auth_count kadm5_flush kadm5_get_policies "
	"kadm5_get_principal kadm5_get_principals kadm5_init_with_password kadm5_kvno kadm5_last_failed kadm5_last_pw_change "
	"kadm5_last_success kadm5_max_life kadm5_max_rlife kadm5_mod_name kadm5_mod_time kadm5_modify_principal kadm5_policy "
	"kadm5_princ_expire_time kadm5_principal kadm5_pw_expiration kadm5_randkey key key_exists krb5_kdb_disallow_all_tix ";
			// color text
	static SScintillaColors g_rgb_Syntax_php[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- ruby Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_ruby_language = _T("ruby");
	// extentions
	static CString g_str_ruby_extention = _T("ruby");
	// comment line
	static CString g_str_ruby_commentline = _T("#");
	// comment start
	static CString g_str_ruby_commentStart = _T("");
	// comment end
	static CString g_str_ruby_commentEnd = _T("");
	// keywords
	static const char* g_ruby_KeyWords =
		"ARGF ARGV BEGIN END ENV FALSE DATA NIL RUBY_PATCHLEVEL RUBY_PLATFORM RUBY_RELEASE_DATE RUBY_VERSION PLATFORM RELEASE_DATE STDERR STDIN STDOUT TOPLEVEL_BINDING TRUE __ENCODING__ __END__ __FILE__ __LINE__ alias and begin break case class def defined? do else elsif end ensure false for if in module next nil not or redo rescue retry return self super then true undef unless until when while yield ";
	// color text
	static SScintillaColors g_rgb_Syntax_ruby[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- rust Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_rust_language = _T("rust");
	// extentions
	static CString g_str_rust_extention = _T("rust");
	// comment line
	static CString g_str_rust_commentline = _T("//");
	// comment start
	static CString g_str_rust_commentStart = _T("/*");
	// comment end
	static CString g_str_rust_commentEnd = _T("*/");
	// keywords
	static const char* g_rust_KeyWords =
		"abstract as async become box break const continue crate do dyn else enum extern false final fn for if impl in let loop macro match mod move mut overrIDE priv pub ref return self static struct super trait true try type typeof unsafe unsized use virtual where while yield "
		"bool char f32 f64 i128 i16 i32 i64 i8 isize str u128 u16 u32 u64 u8 usize Self ";
	// color text
	static SScintillaColors g_rgb_Syntax_rust[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				builtin },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				foregroundMonokai },
	{ SCE_C_REGEX,				builtin },
	{ SCE_C_COMMENTLINEDOC,				foregroundMonokai },
	{ SCE_C_WORD2,				foregroundMonokai },
	{ SCE_C_COMMENTDOCKEYWORD,				builtin },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				foregroundMonokai },
	{ SCE_C_GLOBALCLASS,				builtin },
	{ SCE_C_STRINGRAW,				builtin },
	{ SCE_C_TRIPLEVERBATIM,				builtin },
	{ SCE_C_HASHQUOTEDSTRING,				builtin },
	{ SCE_C_PREPROCESSORCOMMENT,				builtin },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				foregroundMonokai },
	{ SCE_C_USERLITERAL,				foregroundMonokai },
	{ SCE_C_TASKMARKER,				foregroundMonokai },
	{ SCE_C_ESCAPESEQUENCE,				foregroundMonokai },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- sql Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_sql_language = _T("sql");
	// extentions
	static CString g_str_sql_extention = _T("sql");
	// comment line
	static CString g_str_sql_commentline = _T("--");
	// comment start
	static CString g_str_sql_commentStart = _T("/*");
	// comment end
	static CString g_str_sql_commentEnd = _T("*/");
	// keywords
	static const char* g_sql_KeyWords =
		"abs absolute access acos add add_months adddate admin after aggregate all allocate alter and any app_name applock_mode applock_test are array as asc ascii asin assemblyproperty assertion asymkey_id at atan atn2 audit authid authorization autonomous_transaction avg backup before begin benchmark between bfilename bin binary_checksum bit_and bit_count bit_or body both breadth break browse bulk by call cascade cascaded case cast catalog catch ceil ceiling cert_id certproperty character charindex chartorowid check checkpoint checksum checksum_agg chr class clause close cluster clustered coalesce col_length col_name collate collation collect column columnproperty columns_updated comment commit completion compress compute concat concat_ws connect connection connectionproperty constant constraint constraints constructorcreate contains containsable containstable context_info continue conv convert corr corresponding cos cot count count_big covar_pop covar_samp create cross cube cume_dist current current_date current_path current_request_id current_role current_time current_timestamp current_user currval cursor_status cycle data database database_principal_id databasepropertyex datalength date_add date_format date_sub dateadd datediff datefirst dateformat datename datepart db_id db_name dbcc deallocate declare decode decryptbyasmkey decryptbycert decryptbykey decryptbykeyautocert decryptbypassphrase default deferrable deferred degrees delete dense_rank deny depth deref desc describe descriptor destroy destructor deterministic diagnostics dictionary difference disconnect disk distinct distributed do domain drop dump dynamic each else elsif empth encode encrypt encryptbyasmkey encryptbycert encryptbykey encryptbypassphrase end end-exec equals errlvl error_line error_message error_number error_procedure error_severity error_state escape eventdata every except exception exclusive exec execute exists exit exp export_set extends external extract false fetch file file_id file_IDEx file_name filegroup_id filegroup_name filegroupproperty fileproperty fillfactor first first_value floor fn_virtualfilestats for forall foreign format formatmessage found freetext freetexttable from from_days full fulltextcatalog fulltextcatalogproperty fulltextservice fulltextserviceproperty function general get get_filestream_transaction_context get_lock getansinull getdate getutcdate global go goto grant greatest group grouping grouping_id has_perms_by_name hashbytes having heap hex hextoraw holdlock host host_id host_name hour IDEnt_current IDEnt_incr IDEnt_seed IDEntified IDEntity IDEntity_insert IDEntitycol if ifnull ignore immediate in include increment index index_col indexkey_property indexproperty indicator initcap initial initialize initially inner inout input insert instr instrb interface intersect into is is_member is_null is_numeric is_srvrolemember isdate isnull isnumeric isolation iterate java join key key_guid key_id kill lag language large last last_day last_value lateral lcase lead leading least left len length lengthb less level like limit limited lineno ln load local localtime localtimestamp locator lock log log10 loop lower lpad ltrim make_ref map match max maxextents merge mid min min_active_rowversion minus minute mlslabel mod mode modifies modify module month months_between names national natural naturaln new new_time newid newsequentialid next next_day nextval no noaudit nocheck nocompress nocopy nonclustered none not nowait ntile null nullif number_base nvl nvl2 object object_definition object_id object_name object_property object_schema_name objectproperty objectpropertyex ocirowid oct of off offline offsets old on online only opaque open opendatasource openquery openrowset openxml operation operator option or ord order ordinalityorganization original_db_name original_login others out outer output over package pad parameter parameters parsename partial partition path pathname patindex pctfree percent percent_rank permissions pi pivot plan pls_integer positive positiven postfix pow power pragma prefix preorder prepare preserve primary print prior private privileges proc procedure public publishingservername pwdcompare pwdencrypt quotename radians raise raiserror rand range rank ratio_to_export rawtohex read reads readtext reconfigure record recursive ref references referencing reftohex relative release release_lock rename repeat replace replicate replication resource restore restrict result return returns reverse revert revoke right rollback rollup round routine row row_number rowcount rowcount_big rowguidcol rowidtochar rowlabel rownum rows rowtype rpad rtrim rule save savepoint schema schema_id schema_name scope scope_IDEntity scroll search second section securityaudit seddev_samp select separate sequence serverproperty session session_user set sets setuser share shutdown sign signbyasymkey signbycert sin sinh size some soundex sp_helplanguage space specific specifictype sql sql_variant_property sqlcode sqlerrm sqlexception sqlstate sqlwarning sqrt square start state statement static statistics stats_date std stddev stdev stdev_pop stdevp str strcmp structure stuff subdate substr substrb substring substring_index subtype successful sum suser_id suser_name suser_sid suser_sname switchoffset synonym sys_context sys_guid sysdate sysdatetime sysdatetimeoffset system_user sysutcdatetime table tablesample tan tanh temporary terminate textptr textsize textvalid than then timezone_abbr timezone_hour timezone_minute timezone_region to to_char to_date to_days to_number to_single_byte todatetimeoffset top trailing tran transaction translate translation treat trigger trigger_nestlevel trim true trunc truncate try tsequal type type_id type_name typeproperty ucase uid under unicode union unique unknown unnest unpivot update updatetext upper usage use user user_id user_name userenv using validate value values var var_pop var_samp variable variance varp varying verifysignedbyasmkey verifysignedbycert view vsize waitfor when whenever where while with without work write writetext xact_state zone "
		"bfile bigint binary binary_integer bit blob bool boolean char char_base clob cursor date datetime datetime2 datetimeoffset day dec decimal double enum float hierarchyid image int integer interval long longblob longtext mediumblob mediumint mediumtext money nchar nclob ntext number numeric nvarchar precision raw real rowid smalldatetime smallint smallmoney sql_variant text time timestamp tinyblob tinyint tinytext uniqueIDEntifier urowid varbinary varchar varchar2 xml year ";
	// color text
	static SScintillaColors g_rgb_Syntax_sql[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- tcl Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_tcl_language = _T("tcl");
	// extentions
	static CString g_str_tcl_extention = _T("tcl");
	// comment line
	static CString g_str_tcl_commentline = _T("#");
	// comment start
	static CString g_str_tcl_commentStart = _T("");
	// comment end
	static CString g_str_tcl_commentEnd = _T("");
	// keywords
	static const char* g_tcl_KeyWords =
		"after append apply array auto_execok auto_import auto_load auto_load_index auto_qualify auto_reset bgerror binary break catch cd chan clock close concat continue coroutine dde dict default else elseif encoding env eof error eval exec exit expr fblocked fconfigure fcopy file fileevent filename flush for foreach format gets glob global history http if incr info interp join lappend lassign lindex linsert list llength lmap load lrange lrepeat lreplace lreverse lsearch lset lsort memory my namespace next nextto oo::class oo::copy oo::define oo::objdefine oo::object open package parray pid pkg_mkIndex platform proc puts pwd read regexp registry regsub rename return scan seek self set socket source split string subst switch tailcall tclLog tclMacPkgSearch tclPkgSetup tclPkgUnknown tell throw time trace try unknown unload unset update uplevel upvar variable vwait while yield yeildto zlib "
		"bell bind bindtags button canvas checkbutton console destroy entry event focus font frame grab grid image label labelframe listbox lower menu menubutton message option pack panedwindow place radiobutton raise scale scrollbar selection send spinbox text tk tkerror tkwait toplevel ttk::button ttk::checkbutton ttk::combobox ttk::entry ttk::frame ttk::intro ttk::label ttk::labeframe ttk::menubutton ttk::notebook ttk::panedwindow ttk::progressbar ttk::radiobutton ttk::scale ttk::scrollbar ttk::sizegrip ttk::spinbox ttk::style winfo wm "
		"@scope body class code common component configbody constructor define destructor hull import inherit itcl itk itk_component itk_initialize itk_interior itk_option iwidgets keep method private protected public "
		"tkButtonDown tkButtonEnter tkButtonInvoke tkButtonLeave tkButtonUp tkCancelRepeat tkCheckRadioInvoke tkDarken tkEntryAutoScan tkEntryBackspace tkEntryButton1 tkEntryClosestGap tkEntryInsert tkEntryKeySelect tkEntryMouseSelect tkEntryNextWord tkEntryPaste tkEntryPreviousWord tkEntrySeeInsert tkEntrySetCursor tkEntryTranspose tkEventMotifBindings tkFDGetFileTypes tkFirstMenu tkFocusGroup_Destroy tkFocusGroup_In tkFocusGroup_Out tkFocusOK tkListboxAutoScan tkListboxBeginExtend tkListboxBeginSelect tkListboxBeginToggle tkListboxCancel tkListboxDataExtend tkListboxExtendUpDown tkListboxMotion tkListboxSelectAll tkListboxUpDown tkMbButtonUp tkMbEnter tkMbLeave tkMbMotion tkMbPost tkMenuButtonDown tkMenuDownArrow tkMenuDup tkMenuEscape tkMenuFind tkMenuFindName tkMenuFirstEntry tkMenuInvoke tkMenuLeave tkMenuLeftArrow tkMenuMotion tkMenuNextEntry tkMenuNextMenu tkMenuRightArrow tkMenuUnpost tkMenuUpArrow tkMessageBox tkPostOverPoint tkRecolorTree tkRestoreOldGrab tkSaveGrabInfo tkScaleActivate tkScaleButton2Down tkScaleButtonDown tkScaleControlPress tkScaleDrag tkScaleEndDrag tkScaleIncrement tkScreenChanged tkScrollButton2Down tkScrollButtonDown tkScrollButtonUp tkScrollByPages tkScrollByUnits tkScrollDrag tkScrollEndDrag tkScrollSelect tkScrollStartDrag tkScrollToPos  tkScrollTopBottom tkTabToWindow tkTearOffMenu tkTextAutoScan tkTextButton1 tkTextClosestGap tkTextInsert tkTextKeyExtend tkTextKeySelect tkTextNextPara tkTextNextPos tkTextNextWord tkTextPaste tkTextPrevPara tkTextPrevPos tkTextResetAnchor tkTextScrollPages tkTextSelectTo tkTextSetCursor tkTextTranspose tkTextUpDownLine tkTraverseToMenu tkTraverseWithinMenu tk_bisque tk_chooseColor tk_dialog tk_focusFollowsMouse tk_focusNext tk_focusPrev tk_getOpenFile tk_getSaveFile tk_messageBox tk_optionMenu tk_popup tk_setPalette tk_textCopy tk_textCut tk_textPaste ";
	// color text
	static SScintillaColors g_rgb_Syntax_tcl[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- vb Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_vb_language = _T("vb");
	// extentions
	static CString g_str_vb_extention = _T("vb");
	// comment line
	static CString g_str_vb_commentline = _T("'");
	// comment start
	static CString g_str_vb_commentStart = _T("");
	// comment end
	static CString g_str_vb_commentEnd = _T("");
	// keywords
	static const char* g_vb_KeyWords =
		"addhandler addressof alias and andalso as boolean by byref byte byval call case catch cbool cbyte cchar cdate cdbl cdec char cint class clng cobj const continue csbyte cshort csng cstr ctype cuint culng cushort date decimal declare default delegate dim directcast do double each else elseif end endif enum erase error event exit false finally for friend function get gettype global gosub goto handles if implements imports in inherits integer interface is isnot let lib like long loop me mod module mustinherit mustoverrIDE mybase myclass namespace narrowing new next not nothing notinheritable notoverridable object of on operator option optional or orelse out overloads overridable overrIDEs paramarray partial private property protected public raiseevent readonly redim rem removehandler resume return sbyte select set shadows shared short single static step stop strict string structure sub synclock then throw to true try trycast typeof uinteger ulong ushort using variant wend when while wIDEning with withevents writeonly xor attribute begin currency implement load lset rset type unload aggregate ansi assembly async auto await binary compare custom distinct equals explicit from group into isfalse istrue iterator join key mid off order preserve skip take text unicode until where yield ";
	// color text
	static SScintillaColors g_rgb_Syntax_vb[] =
	{ { SCE_C_DEFAULT,		builtin },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			definition },
	{ SCE_C_COMMENTDOC,				keyword },
	{ SCE_C_NUMBER,				string },
	{ SCE_C_WORD,			comment },
	{ SCE_C_STRING,				orangered },
	{ SCE_C_CHARACTER,			foregroundMonokai },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				comment },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- verilog Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_verilog_language = _T("verilog");
	// extentions
	static CString g_str_verilog_extention = _T("verilog");
	// comment line
	static CString g_str_verilog_commentline = _T("//");
	// comment start
	static CString g_str_verilog_commentStart = _T("/*");
	// comment end
	static CString g_str_verilog_commentEnd = _T("*/");
	// keywords
	static const char* g_verilog_KeyWords =
		"accept_on alias always always_comb always_ff always_latch and assert assign assume attribute automatic before begin bind bins binsof bit break buf bufif0 bufif1 byte case casex casez cell chandle checker class clocking cmos config const constraint context continue cover covergroup coverpoint cross deassign default defparam design disable dist do edge else end endattribute endcase endchecker endclass endclocking endconfig endfunction endgenerate endgroup endinterface endmodule endpackage endprimitive endprogram endproperty endsequence endspecify endtable endtask enum event eventually expect export extends extern final first_match for force foreach forever fork forkjoin function generate genvar global highz0 highz1 if iff ifnone ignore_bins illegal_bins implements implies import incdir include initial inout input insIDE instance int integer interconnect interface intersect join join_any join_none large let liblist library local localparam logic longint macromodule matches medium modport module nand negedge nettype new nexttime nmos nor noshowcancelled not notif0 notif1 null or output package packed parameter pmos posedge primitive priority program property protected pull0 pull1 pulldown pullup pulsestyle_ondetect pulsestyle_onevent pure rand randc randcase randsequence rcmos real realtime ref reg reject_on release repeat restrict return rnmos rpmos rtran rtranif0 rtranif1 scalared sequence shortint shortreal showcancelled signed small soft solve specify specparam static string strong strong0 strong1 struct super supply0 supply1 sync_accept_on sync_reject_on s_always s_eventually s_nexttime s_until s_until_with table tagged task this throughout time timeprecision timeunit tran tranif0 tranif1 tri tri0 tri1 triand trior trireg type typedef union unique unique0 unsigned until until_with untyped use var vectored virtual void wait wait_order wand weak weak0 weak1 while wildcard wire with within wor xnor xor "
		"$acos $acosh $asin $asinh $assertcontrol $assertkill $assertoff $asserton $assertpasson $assertpassoff $assertfailon $assertfailoff $assertnonvacuouson $assertvacuousoff $async$and$array $async$and$plane $async$nand$array $async$nand$plane $async$nor$array $async$nor$plane $async$or$array $async$or$plane $atan $atan2 $atanh $bits $bitstoreal $bitstoshortreal $cast $ceil $changed_gclk $changing_gclk $clog2 $comment $cos $cosh $countdrivers $countones $coverage_control $coverage_get $coverage_get_max $coverage_merge $coverage_save $date $dimensions $display $displayb $displayh $displayo $dist_chi_square $dist_erlang $dist_exponential $dist_normal $dist_poisson $dist_t $dist_uniform $dumpall $dumpfile $dumpflush $dumplimit $dumpoff $dumpon $dumpportsall $dumpportsflush $dumpportslimit $dumpportsoff $dumpportson $dumpvars $end $enddefinitions $error $exit $exp $falling_gclk $fatal $fclose $fdisplay $fdisplayb $fdisplayh $fdisplayo $fell $fell_gclk $feof $ferror $fflush $fgetc $fgets $finish $floor $fmonitor $fmonitorb $fmonitorh $fmonitoro $fopen $fread $fscanf $fseek $fstrobe $ftell $fullskew $future_gclk $fwrite $fwriteb $fwriteh $fwriteo $getpattern $get_coverage $high $history $hold $hypot $increment $incsave $info $input $isunbounded $isunknown $itor $key $left $list $ln $load_coverage_db $log $log10 $low $monitor $monitorb $monitorh $monitoro $monitoroff $monitoron $nochange $nokey $nolog $onehot $onehot0 $past $past_gclk $period $pow $printtimescale $q_add $q_exam $q_full $q_initialize $q_remove $random $readmemb $readmemh $realtime $realtobits $recovery $recrem $removal $reset $reset_count $reset_value $restart $rewind $right $rising_gclk $root $rose $rose_gclk $rtoi $sampled $save $scale $scope $setup $setuphold $set_coverage_db_name $sformat $sformatf $shortrealtobits $showscopes $showvariables $showvars $signed $sin $sinh $size $skew $sqrt $sreadmemb $sreadmemh $sscanf $stable $stable_gclk $steady_gclk $stime $stop $strobe $strobeb $strobeh $strobeo $swrite $sync$and$array $sync$and$plane $sync$nand$array $sync$nand$plane $sync$nor$array $sync$nor$plane $sync$or$array $sync$or$plane $system $tan $tanh $test$plusargs $time $timeformat $timescale $timeskew $typename $typeof $uandom $ungetc $unit $unpacked_dimensions $unsigned $upscope $urandom_range $value$plusargs $var $vcdclose $version $warning $width $write $writeb $writeh $writememb $writememh $writeo ";
	// color text
	static SScintillaColors g_rgb_Syntax_verilog[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- vhdl Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_vhdl_language = _T("vhdl");
	// extentions
	static CString g_str_vhdl_extention = _T("vhdl");
	// comment line
	static CString g_str_vhdl_commentline = _T("--");
	// comment start
	static CString g_str_vhdl_commentStart = _T("");
	// comment end
	static CString g_str_vhdl_commentEnd = _T("");
	// keywords
	static const char* g_vhdl_KeyWords =
		"access after alias all architecture array assert attribute begin block body buffer bus case component configuration constant disconnect downto else elsif end entity exit file for function generate generic group guarded if impure in inertial inout is label library linkage literal loop map new next null of on open others out package port postponed procedure process pure range record register reject report return select severity shared signal subtype then to transport type unaffected units until use variable wait when while with assume assume_guarantee context cover default fairness force parameter property protected release restrict restrict_guarantee sequence strong vmode vprop vunit "
		"abs and mod nand nor not or rem rol ror sla sll sra srl xnor xor "
		"left right low high ascending image value pos val succ pred leftof rightof base range reverse_range length delayed stable quiet transaction event active last_event last_active last_value driving driving_value simple_name path_name instance_name "
		"now readline read writeline write endfile resolved to_bit to_bitvector to_stdulogic to_stdlogicvector to_stdulogicvector to_x01 to_x01z to_UX01 rising_edge falling_edge is_x shift_left shift_right rotate_left rotate_right resize to_integer to_unsigned to_signed std_match to_01 "
		"std ieee work standard textio std_logic_1164 std_logic_arith std_logic_misc std_logic_signed std_logic_textio std_logic_unsigned numeric_bit numeric_std math_complex math_real vital_primitives vital_timing "
		"boolean bit character severity_level integer real time delay_length natural positive string bit_vector file_open_kind file_open_status line text sIDE width std_ulogic std_ulogic_vector std_logic std_logic_vector X01 X01Z UX01 UX01Z unsigned signed ";
	// color text
	static SScintillaColors g_rgb_Syntax_vhdl[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				comment },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				comment },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				comment },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				comment },
	{ SCE_C_TRIPLEVERBATIM,				comment },
	{ SCE_C_HASHQUOTEDSTRING,				comment },
	{ SCE_C_PREPROCESSORCOMMENT,				comment },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				comment },
	{ SCE_C_TASKMARKER,				comment },
	{ SCE_C_ESCAPESEQUENCE,				comment },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- xml Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_xml_language = _T("xml");
	// extentions
	static CString g_str_xml_extention = _T("xml");
	// comment line
	static CString g_str_xml_commentline = _T("");
	// comment start
	static CString g_str_xml_commentStart = _T("<!--");
	// comment end
	static CString g_str_xml_commentEnd = _T("-->");
	// keywords
	static const char* g_xml_KeyWords = "";
	// color text
	static SScintillaColors g_rgb_Syntax_xml[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		keyword },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			comment },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		builtin },
	{ SCE_C_PREPROCESSOR,				definition },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				definition },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				definition },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				definition },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				definition },
	{ SCE_C_TRIPLEVERBATIM,				definition },
	{ SCE_C_HASHQUOTEDSTRING,				definition },
	{ SCE_C_PREPROCESSORCOMMENT,				definition },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				definition },
	{ SCE_C_TASKMARKER,				definition },
	{ SCE_C_ESCAPESEQUENCE,				definition },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- json Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_json_language = _T("json");
	// extentions
	static CString g_str_json_extention = _T("json");
	// comment line
	static CString g_str_json_commentline = _T("");
	// comment start
	static CString g_str_json_commentStart = _T("");
	// comment end
	static CString g_str_json_commentEnd = _T("");
	// keywords
	static const char* g_json_KeyWords =
		"false null true "
		"@id @context @type @value @language @container @list @set @reverse @index @base @vocab @graph ";
	// color text
	static SScintillaColors g_rgb_Syntax_json[] =
	{ { SCE_JSON_DEFAULT,		foregroundMonokai },
	{ SCE_JSON_NUMBER,		number },
	{ SCE_JSON_STRING,			string },
	{ SCE_JSON_STRINGEOL,				string },
	{ SCE_JSON_PROPERTYNAME,				keyword },
	{ SCE_JSON_ESCAPESEQUENCE,			foregroundMonokai },
	{ SCE_JSON_LINECOMMENT,				comment },
	{ SCE_JSON_BLOCKCOMMENT,			comment },
	{ SCE_JSON_OPERATOR,		builtin },
	{ SCE_JSON_URI,				string },
	{ SCE_JSON_COMPACTIRI,				string },
	{ SCE_JSON_KEYWORD,				keyword },
	{ SCE_JSON_LDKEYWORD,    keyword },
	{ SCE_JSON_ERROR,				keyword },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- markdown Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_markdown_language = _T("markdown");
	// extentions
	static CString g_str_markdown_extention = _T("md");
	// comment line
	static CString g_str_markdown_commentline = _T("[//]: # ");
	// comment start
	static CString g_str_markdown_commentStart = _T("<!---");
	// comment end
	static CString g_str_markdown_commentEnd = _T("-->");
	// keywords
	static const char* g_markdown_KeyWords = "";
	// color text
	static SScintillaColors g_rgb_Syntax_markdown[] =
	{ { SCE_MARKDOWN_DEFAULT,		foregroundMonokai },
	{ SCE_MARKDOWN_LINE_BEGIN,		instance },
	{ SCE_MARKDOWN_STRONG1,			keyword },
	{ SCE_MARKDOWN_STRONG2,				keyword },
	{ SCE_MARKDOWN_EM1,				orangered },
	{ SCE_MARKDOWN_EM2,			orangered },
	{ SCE_MARKDOWN_HEADER1,				magenta },
	{ SCE_MARKDOWN_HEADER2,			builtin },
	{ SCE_MARKDOWN_HEADER3,		definition },
	{ SCE_MARKDOWN_HEADER4,				orangered },
	{ SCE_MARKDOWN_HEADER5,				instance },
	{ SCE_MARKDOWN_HEADER6,				yellowgreen },
	{ SCE_MARKDOWN_PRECHAR,    string },
	{ SCE_MARKDOWN_ULIST_ITEM,				instance },
	{ SCE_MARKDOWN_BLOCKQUOTE,				string },
	{ SCE_MARKDOWN_STRIKEOUT,				comment },
	{ SCE_MARKDOWN_HRULE,				orangered },
	{ SCE_MARKDOWN_LINK,				comment },
	{ SCE_MARKDOWN_CODE,				string },
	{ SCE_MARKDOWN_CODE2,				string },
	{ SCE_MARKDOWN_CODEBK,				string },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- powershell Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_powershell_language = _T("powershell");
	// extentions
	static CString g_str_powershell_extention = _T("powershell");
	// comment line
	static CString g_str_powershell_commentline = _T("#");
	// comment start
	static CString g_str_powershell_commentStart = _T("<#");
	// comment end
	static CString g_str_powershell_commentEnd = _T("#>");
	// keywords
	static const char* g_powershell_KeyWords =
		"break continue do else elseif filter for foreach function if in return switch until where while "
		"add-content add-history add-member add-pssnapin clear-content clear-item clear-itemproperty clear-variable compare-object convertfrom-securestring convert-path convertto-html convertto-securestring copy-item copy-itemproperty export-alias export-clixml export-console export-csv foreach-object format-custom format-list format-table format-wIDE get-acl get-alias get-authenticodesignature get-childitem get-command get-content get-credential get-culture get-date get-eventlog get-executionpolicy get-help get-history get-host get-item get-itemproperty get-location get-member get-pfxcertificate get-process get-psdrive get-psprovIDEr get-pssnapin get-service get-tracesource get-uiculture get-unique get-variable get-wmiobject group-object import-alias import-clixml import-csv invoke-expression invoke-history invoke-item join-path measure-command measure-object move-item move-itemproperty new-alias new-item new-itemproperty new-object new-psdrive new-service new-timespan new-variable out-default out-file out-host out-null out-printer out-string pop-location push-location read-host remove-item remove-itemproperty remove-psdrive remove-pssnapin remove-variable rename-item rename-itemproperty resolve-path restart-service resume-service select-object select-string set-acl set-alias set-authenticodesignature set-content set-date set-executionpolicy set-item set-itemproperty set-location set-psdebug set-service set-tracesource set-variable sort-object split-path start-service start-sleep start-transcript stop-process stop-service stop-transcript suspend-service tee-object test-path trace-command update-formatdata update-typedata where-object write-debug write-error write-host write-output write-progress write-verbose write-warning "
		"ac asnp clc cli clp clv cpi cpp cvpa diff epal epcsv fc fl foreach ft fw gal gc gci gcm gdr ghy gi gl gm gp gps group gsv gsnp gu gv gwmi iex ihy ii ipal ipcsv mi mp nal ndr ni nv oh rdr ri rni rnp rp rsnp rv rvpa sal sasv sc select si sl sleep sort sp spps spsv sv tee where write cat cd clear cp h history kill lp ls mount mv popd ps pushd pwd r rm rmdir echo cls chdir copy del dir erase move rd ren set type "
		"component description example externalhelp forwardhelpcategory forwardhelptargetname functionality inputs link notes outputs parameter remotehelprunspace role synopsis ";
	// color text
	static SScintillaColors g_rgb_Syntax_powershell[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment_monokai },
	{ SCE_C_COMMENTLINE,			comment_monokai },
	{ SCE_C_COMMENTDOC,				string },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			builtin },
	{ SCE_C_STRING,				foregroundMonokai },
	{ SCE_C_CHARACTER,			foregroundMonokai },
	{ SCE_C_UUID,		definition },
	{ SCE_C_PREPROCESSOR,				builtin },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				foregroundMonokai },
	{ SCE_C_WORD2,				string },
	{ SCE_C_COMMENTDOCKEYWORD,				foregroundMonokai },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				foregroundMonokai },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				foregroundMonokai },
	{ SCE_C_TRIPLEVERBATIM,				foregroundMonokai },
	{ SCE_C_HASHQUOTEDSTRING,				foregroundMonokai },
	{ SCE_C_PREPROCESSORCOMMENT,				foregroundMonokai },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				foregroundMonokai },
	{ SCE_C_TASKMARKER,				foregroundMonokai },
	{ SCE_C_ESCAPESEQUENCE,				foregroundMonokai },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- go Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_go_language = _T("go");
	// extentions
	static CString g_str_go_extention = _T("go");
	// comment line
	static CString g_str_go_commentline = _T("//");
	// comment start
	static CString g_str_go_commentStart = _T("/*");
	// comment end
	static CString g_str_go_commentEnd = _T("*/");
	// keywords
	static const char* g_go_KeyWords =
		"break default func interface select case defer go map struct chan else goto package switch const fallthrough if range type continue for import return var ";
	// color text
	static SScintillaColors g_rgb_Syntax_go[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				number },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    red },
	{ SCE_C_VERBATIM,				foregroundMonokai },
	{ SCE_C_REGEX,				foregroundMonokai },
	{ SCE_C_COMMENTLINEDOC,				foregroundMonokai },
	{ SCE_C_WORD2,				foregroundMonokai },
	{ SCE_C_COMMENTDOCKEYWORD,				foregroundMonokai },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				foregroundMonokai },
	{ SCE_C_GLOBALCLASS,				foregroundMonokai },
	{ SCE_C_STRINGRAW,				foregroundMonokai },
	{ SCE_C_TRIPLEVERBATIM,				foregroundMonokai },
	{ SCE_C_HASHQUOTEDSTRING,				foregroundMonokai },
	{ SCE_C_PREPROCESSORCOMMENT,				foregroundMonokai },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				foregroundMonokai },
	{ SCE_C_USERLITERAL,				foregroundMonokai },
	{ SCE_C_TASKMARKER,				foregroundMonokai },
	{ SCE_C_ESCAPESEQUENCE,				foregroundMonokai },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- inno Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_inno_language = _T("inno");
	// extentions
	static CString g_str_inno_extention = _T("iss");
	// comment line
	static CString g_str_inno_commentline = _T(";");
	// comment start
	static CString g_str_inno_commentStart = _T("");
	// comment end
	static CString g_str_inno_commentEnd = _T("");
	// keywords
	static const char* g_inno_KeyWords =
		"and array asm begin case cdecl class const constructor default destructor div do downto else end end. except exit exports external far file finalization finally for function goto if implementation in index inherited initialization inline interface label library message mod near nil not object of on or out overload overrIDE packed pascal private procedure program property protected public published raise read record register repeat resourcestring safecall set shl shr stdcall stored string then threadvar to try type unit until uses var virtual while with write xor ";
	// color text
	static SScintillaColors g_rgb_Syntax_inno[] =
	{ { SCE_C_DEFAULT,		foregroundMonokai },
	{ SCE_C_COMMENT,		foregroundMonokai },
	{ SCE_C_COMMENTLINE,			keyword },
	{ SCE_C_COMMENTDOC,				keyword },
	{ SCE_C_NUMBER,				builtin },
	{ SCE_C_WORD,			foregroundMonokai },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		instance },
	{ SCE_C_PREPROCESSOR,				foregroundMonokai },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    string },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				keyword },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				keyword },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				keyword },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				keyword },
	{ SCE_C_TRIPLEVERBATIM,				keyword },
	{ SCE_C_HASHQUOTEDSTRING,				keyword },
	{ SCE_C_PREPROCESSORCOMMENT,				keyword },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				keyword },
	{ SCE_C_TASKMARKER,				keyword },
	{ SCE_C_ESCAPESEQUENCE,				keyword },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- protobuf Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_protobuf_language = _T("protobuf");
	// extentions
	static CString g_str_protobuf_extention = _T("proto");
	// comment line
	static CString g_str_protobuf_commentline = _T("//");
	// comment start
	static CString g_str_protobuf_commentStart = _T("/*");
	// comment end
	static CString g_str_protobuf_commentEnd = _T("*/");
	// keywords
	static const char* g_protobuf_KeyWords =
		"for while if else switch case do class struct returns service rpc const message string int32 uint32 int64 uint64 sint32 enum option true false to max min repeated import bool sint64 bytes ";
	// color text
	static SScintillaColors g_rgb_Syntax_protobuf[] =
	{ { SCE_C_DEFAULT,		keyword },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				builtin },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		keyword },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    string },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				keyword },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				keyword },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				keyword },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				keyword },
	{ SCE_C_TRIPLEVERBATIM,				keyword },
	{ SCE_C_HASHQUOTEDSTRING,				keyword },
	{ SCE_C_PREPROCESSORCOMMENT,				keyword },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				keyword },
	{ SCE_C_TASKMARKER,				keyword },
	{ SCE_C_ESCAPESEQUENCE,				keyword },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- r Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_r_language = _T("r");
	// extentions
	static CString g_str_r_extention = _T("r");
	// comment line
	static CString g_str_r_commentline = _T("#");
	// comment start
	static CString g_str_r_commentStart = _T("\"");
	// comment end
	static CString g_str_r_commentEnd = _T("\"");
	// keywords
	static const char* g_r_KeyWords =
		"if else while repeat for function in next break TRUE FALSE NULL Inf NaN NA NA_integer NA_real NA_complex_ NA_character_ ";
	// color text
	static SScintillaColors g_rgb_Syntax_r[] =
	{ { SCE_R_DEFAULT,		foregroundMonokai },
	{ SCE_R_COMMENT,		comment },
	{ SCE_R_KWORD,			keyword },
	{ SCE_R_BASEKWORD,				comment },
	{ SCE_R_OTHERKWORD,				number },
	{ SCE_R_NUMBER,			number },
	{ SCE_R_STRING,				foregroundMonokai },
	{ SCE_R_STRING2,			foregroundMonokai },
	{ SCE_R_OPERATOR,		builtin },
	{ SCE_R_IDENTIFIER,				light_orange },
	{ SCE_R_INFIX,				yellow },
	{ SCE_R_INFIXEOL,				yellow },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- autoit Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_autoit_language = _T("r");
	// extentions
	static CString g_str_autoit_extention = _T("r");
	// comment line
	static CString g_str_autoit_commentline = _T(";");
	// comment start
	static CString g_str_autoit_commentStart = _T("");
	// comment end
	static CString g_str_autoit_commentEnd = _T("");
	// keywords
	static const char* g_autoit_KeyWords =
		"False True comments-start ContinueCase ContinueLoop Default Dim Global Local Const Do Until Enum Exit ExitLoop For To Step Next For In Next Func Return EndFunc If Then If ElseIf Else EndIf include-once include NoTrayIcon Null OnAutoItStartRegister pragma ReDim RequireAdmin Select Case EndSelect Static Switch Case EndSwitch Volatile While WEnd With EndWith ";
	// color text
	static SScintillaColors g_rgb_Syntax_autoit[] =
	{ { SCE_C_DEFAULT,		keyword },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				builtin },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		keyword },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    string },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				keyword },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				keyword },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				keyword },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				keyword },
	{ SCE_C_TRIPLEVERBATIM,				keyword },
	{ SCE_C_HASHQUOTEDSTRING,				keyword },
	{ SCE_C_PREPROCESSORCOMMENT,				keyword },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				keyword },
	{ SCE_C_TASKMARKER,				keyword },
	{ SCE_C_ESCAPESEQUENCE,				keyword },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- flexlicense Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_flexlicense_language = _T("flexlicense");
	// extentions
	static CString g_str_flexlicense_extention = _T("lic");
	// comment line
	static CString g_str_flexlicense_commentline = _T("#");
	// comment start
	static CString g_str_flexlicense_commentStart = _T("");
	// comment end
	static CString g_str_flexlicense_commentEnd = _T("");
	// keywords
	static const char* g_flexlicense_KeyWords =
		"INCREMENT uncounted HOSTID SIGN ISSUED ";
	// color text 
	static SScintillaColors g_rgb_Syntax_flexlicense[] =
	{ { SCE_P_DEFAULT,		foregroundMonokai },
	{ SCE_P_COMMENTLINE,		comment_monokai },
	{ SCE_P_NUMBER,				foregroundMonokai },
	{ SCE_P_STRING,		    string },
	{ SCE_P_CHARACTER,			string },
	{ SCE_P_WORD,				keyword },
	{ SCE_P_TRIPLE,			comment_monokai },
	{ SCE_P_TRIPLEDOUBLE,			comment_monokai },
	{ SCE_P_CLASSNAME,			comment },
	{ SCE_P_DEFNAME,			comment },
	{ SCE_P_OPERATOR,			builtin },
	{ SCE_P_IDENTIFIER,		        foregroundMonokai },
	{ SCE_P_COMMENTBLOCK,		        comment_monokai },
	{ SCE_P_STRINGEOL,		        string },
	{ SCE_P_WORD2,				keyword },
	{ SCE_P_DECORATOR,		    foregroundMonokai },
	{ SCE_P_FSTRING,		    string },
	{ SCE_P_FCHARACTER,		    string },
	{ SCE_P_FTRIPLE,		    string },
	{ SCE_P_FTRIPLEDOUBLE,		string },
	{ -1,						0 } };

	//----------------------------------------------------------------------------
	//---- resource Language
	//----------------------------------------------------------------------------
	// language
	static CString g_str_resource_language = _T("resource");
	// extentions
	static CString g_str_resource_extention = _T("rc");
	// comment line
	static CString g_str_resource_commentline = _T("//");
	// comment start
	static CString g_str_resource_commentStart = _T("/*");
	// comment end
	static CString g_str_resource_commentEnd = _T("*/");
	// keywords
	static const char* g_resource_KeyWords =
		"ACCELERATORS ALT AUTO3STATE AUTOCHECKBOX AUTORADIOBUTTON BEGIN BITMAP BLOCK BUTTON CAPTION CHARACTERISTICS CHECKBOX CLASS COMBOBOX CONTROL CTEXT CURSOR DEFPUSHBUTTON DIALOG DIALOGEX DISCARDABLE EDITTEXT END EXSTYLE FONT GROUPBOX ICON LANGUAGE LISTBOX LTEXT MENU MENUEX MENUITEM MESSAGETABLE POPUP PUSHBUTTON RADIOBUTTON RCDATA RTEXT SCROLLBAR SEPARATOR SHIFT STATE3 STRINGTABLE STYLE TEXTINCLUDE VALUE VERSION VERSIONINFO VIRTKEY ";
	// color text
	static SScintillaColors g_rgb_Syntax_resource[] =
	{ { SCE_C_DEFAULT,		keyword },
	{ SCE_C_COMMENT,		comment },
	{ SCE_C_COMMENTLINE,			comment },
	{ SCE_C_COMMENTDOC,				comment },
	{ SCE_C_NUMBER,				builtin },
	{ SCE_C_WORD,			keyword },
	{ SCE_C_STRING,				string },
	{ SCE_C_CHARACTER,			string },
	{ SCE_C_UUID,		keyword },
	{ SCE_C_PREPROCESSOR,				keyword },
	{ SCE_C_OPERATOR,				builtin },
	{ SCE_C_IDENTIFIER,				foregroundMonokai },
	{ SCE_C_STRINGEOL,    string },
	{ SCE_C_VERBATIM,				yellow },
	{ SCE_C_REGEX,				yellow },
	{ SCE_C_COMMENTLINEDOC,				keyword },
	{ SCE_C_WORD2,				orangered },
	{ SCE_C_COMMENTDOCKEYWORD,				keyword },
	{ SCE_C_COMMENTDOCKEYWORDERROR,				keyword },
	{ SCE_C_GLOBALCLASS,				magenta },
	{ SCE_C_STRINGRAW,				keyword },
	{ SCE_C_TRIPLEVERBATIM,				keyword },
	{ SCE_C_HASHQUOTEDSTRING,				keyword },
	{ SCE_C_PREPROCESSORCOMMENT,				keyword },
	{ SCE_C_PREPROCESSORCOMMENTDOC,				yellow },
	{ SCE_C_USERLITERAL,				keyword },
	{ SCE_C_TASKMARKER,				keyword },
	{ SCE_C_ESCAPESEQUENCE,				keyword },
	{ -1,						0 } };
}

//----------------------------------------------------------------------------
//---- RESOURCE REFERENCE LEXERS
//----------------------------------------------------------------------------
/*
	lmA68k(SCLEX_A68K, ColouriseA68kDoc, "a68k", 0, a68kWordListDesc)
	lmAbaqus(SCLEX_ABAQUS, ColouriseABAQUSDoc, "abaqus", FoldABAQUSDoc, abaqusWordListDesc)
	lmAda(SCLEX_ADA, ColouriseDocument, "ada", NULL, adaWordListDesc)
	lmAPDL(SCLEX_APDL, ColouriseAPDLDoc, "apdl", FoldAPDLDoc, apdlWordListDesc)
	lmAsm(SCLEX_ASM, LexerAsm::LexerFactoryAsm, "asm", asmWordListDesc)
	lmAs(SCLEX_AS, LexerAsm::LexerFactoryAs, "as", asmWordListDesc)
	lmAsn1(SCLEX_ASN1, ColouriseAsn1Doc, "asn1", FoldAsn1Doc, asn1WordLists)
	lmASY(SCLEX_ASYMPTOTE, ColouriseAsyDoc, "asy", FoldAsyDoc, asyWordLists)
	lmAU3(SCLEX_AU3, ColouriseAU3Doc, "au3", FoldAU3Doc, AU3WordLists)
	lmAVE(SCLEX_AVE, ColouriseAveDoc, "ave", FoldAveDoc)
	lmAVS(SCLEX_AVS, ColouriseAvsDoc, "avs", FoldAvsDoc, avsWordLists)
	lmBaan(SCLEX_BAAN, LexerBaan::LexerFactoryBaan, "baan", baanWordLists)
	lmBash(SCLEX_BASH, LexerBash::LexerFactoryBash, "bash", bashWordListDesc)
	lmBlitzBasic(SCLEX_BLITZBASIC, LexerBasic::LexerFactoryBlitzBasic, "blitzbasic", blitzbasicWordListDesc)
	lmPureBasic(SCLEX_PUREBASIC, LexerBasic::LexerFactoryPureBasic, "purebasic", purebasicWordListDesc)
	lmFreeBasic(SCLEX_FREEBASIC, LexerBasic::LexerFactoryFreeBasic, "freebasic", freebasicWordListDesc)
	lmBatch(SCLEX_BATCH, ColouriseBatchDoc, "batch", 0, batchWordListDesc)
	lmBibTeX(SCLEX_BIBTEX, ColorizeBibTeX, "bib", 0, BibTeXWordLists)
	lmBullant(SCLEX_BULLANT, ColouriseBullantDoc, "bullant", 0, bullantWordListDesc)
	lmCaml(SCLEX_CAML, ColouriseCamlDoc, "caml", FoldCamlDoc, camlWordListDesc)
	lmCIL(SCLEX_CIL, LexerCIL::LexerFactoryCIL, "cil", cilWordListDesc)
	lmClw(SCLEX_CLW, ColouriseClarionDocSensitive, "clarion", FoldClarionDoc, rgWordListDescriptions)
	lmClwNoCase(SCLEX_CLWNOCASE, ColouriseClarionDocInsensitive, "clarionnocase", FoldClarionDoc, rgWordListDescriptions)
	lmCmake(SCLEX_CMAKE, ColouriseCmakeDoc, "cmake", FoldCmakeDoc, cmakeWordLists)
	lmCOBOL(SCLEX_COBOL, ColouriseCOBOLDoc, "COBOL", FoldCOBOLDoc, COBOLWordListDesc)
	lmCoffeeScript(SCLEX_COFFEESCRIPT, ColouriseCoffeeScriptDoc, "coffeescript", FoldCoffeeScriptDoc, csWordLists)
	lmConf(SCLEX_CONF, ColouriseConfDoc, "conf", 0, confWordListDesc)
	lmCPP(SCLEX_CPP, LexerCPP::LexerFactoryCPP, "cpp", cppWordLists)
	lmCPPNoCase(SCLEX_CPPNOCASE, LexerCPP::LexerFactoryCPPInsensitive, "cppnocase", cppWordLists)
	lmNncrontab(SCLEX_NNCRONTAB, ColouriseNncrontabDoc, "nncrontab", 0, cronWordListDesc)
	lmCsound(SCLEX_CSOUND, ColouriseCsoundDoc, "csound", FoldCsoundInstruments, csoundWordListDesc)
	lmCss(SCLEX_CSS, ColouriseCssDoc, "css", FoldCSSDoc, cssWordListDesc)
	lmD(SCLEX_D, LexerD::LexerFactoryD, "d", dWordLists)
	lmDataflex(SCLEX_DATAFLEX, ColouriseDataFlexDoc, "dataflex", FoldDataFlexDoc, dataflexWordListDesc)
	lmDiff(SCLEX_DIFF, ColouriseDiffDoc, "diff", FoldDiffDoc, emptyWordListDesc)
	lmDMAP(SCLEX_DMAP, ColouriseDMAPDoc, "DMAP", FoldDMAPDoc, DMAPWordLists)
	lmDMIS(SCLEX_DMIS, LexerDMIS::LexerFactoryDMIS, "DMIS", DMISWordListDesc)
	lmECL(scite501\lexilla\lexers\LexEDIFACT.cxx | 129 | LexerModule lmEDIFACT(SCLEX_EDIFACT, LexerEDIFACT::Factory, "edifact")
	lmEiffel(SCLEX_EIFFEL, ColouriseEiffelDoc, "eiffel", FoldEiffelDocIndent, eiffelWordListDesc)
	lmEiffelkw(SCLEX_EIFFELKW, ColouriseEiffelDoc, "eiffelkw", FoldEiffelDocKeyWords, eiffelWordListDesc)
	lmErlang(scite501\lexilla\lexers\LexErrorList.cxx | 414 | LexerModule lmErrorList(SCLEX_ERRORLIST, ColouriseErrorListDoc, "errorlist", 0, emptyWordListDesc)
	lmESCRIPT(SCLEX_ESCRIPT, ColouriseESCRIPTDoc, "escript", FoldESCRIPTDoc, ESCRIPTWordLists)
	lmFlagShip(SCLEX_FLAGSHIP, ColouriseFlagShipDoc, "flagship", FoldFlagShipDoc, FSWordListDesc)
	lmForth(SCLEX_FORTH, ColouriseForthDoc, "forth", FoldForthDoc, forthWordLists)
	lmFortran(SCLEX_FORTRAN, ColouriseFortranDocFreeFormat, "fortran", FoldFortranDocFreeFormat, FortranWordLists)
	lmF77(SCLEX_F77, ColouriseFortranDocFixFormat, "f77", FoldFortranDocFixFormat, FortranWordLists)
	lmFSharp(SCLEX_FSHARP, LexerFSharp::LexerFactoryFSharp, lexerName, fsharpWordLists)
	lmGAP(scite501\lexilla\lexers\LexGui4Cli.cxx | 309 | LexerModule lmGui4Cli(SCLEX_GUI4CLI, ColouriseGui4CliDoc, "gui4cli", FoldGui4Cli, gui4cliWordListDesc)
	lmHaskell(SCLEX_HASKELL, LexerHaskell::LexerFactoryHaskell, "haskell", haskellWordListDesc)
	lmLiterateHaskell(SCLEX_LITERATEHASKELL, LexerHaskell::LexerFactoryLiterateHaskell, "literatehaskell", haskellWordListDesc)
	lmSrec(SCLEX_SREC, ColouriseSrecDoc, "srec", 0, NULL)
	lmIHex(SCLEX_IHEX, ColouriseIHexDoc, "ihex", FoldIHexDoc, NULL)
	lmTEHex(SCLEX_TEHEX, ColouriseTEHexDoc, "tehex", 0, NULL)
	lmHollywood(SCLEX_HOLLYWOOD, LexerHollywood::LexerFactoryHollywood, "hollywood", hollywoodWordListDesc)
	lmHTML(SCLEX_HTML, LexerHTML::LexerFactoryHTML, "hypertext", htmlWordListDesc)
	lmXML(SCLEX_XML, LexerHTML::LexerFactoryXML, "xml", htmlWordListDesc)
	lmPHPSCRIPT(SCLEX_PHPSCRIPT, LexerHTML::LexerFactoryPHPScript, "phpscript", phpscriptWordListDesc)
	lmIndent(SCLEX_INDENT, ColouriseIndentDoc, "indent", FoldIndentDoc)
	lmInno(SCLEX_INNOSETUP, ColouriseInnoDoc, "inno", FoldInnoDoc, innoWordListDesc)
	lmJSON(SCLEX_JSON, scite501\lexilla\lexers\LexKix.cxx | 133 | LexerModule lmKix(SCLEX_KIX, ColouriseKixDoc, "kix")
	lmKVIrc(SCLEX_KVIRC, ColouriseKVIrcDoc, "kvirc", FoldKVIrcDoc, scite501\lexilla\lexers\LexLaTeX.cxx | 559 | LexerModule lmLatex(SCLEX_LATEX, LexerLaTeX::LexerFactoryLaTeX, "latex", emptyWordListDesc)
	lmLISP(SCLEX_LISP, ColouriseLispDoc, "lisp", FoldLispDoc, lispWordListDesc)
	lmLout(SCLEX_LOUT, ColouriseLoutDoc, "lout", FoldLoutDoc, loutWordLists)
	lmLua(SCLEX_LUA, ColouriseLuaDoc, "lua", FoldLuaDoc, luaWordListDesc, lexicalClasses, ELEMENTS(lexicalClasses))
	lmMagikSF(scite501\lexilla\lexers\LexMake.cxx | 142 | LexerModule lmMake(SCLEX_MAKEFILE, ColouriseMakeDoc, "makefile", 0, emptyWordListDesc)
	lmMarkdown(SCLEX_MARKDOWN, ColorizeMarkdownDoc, "markdown")
	lmMatlab(SCLEX_MATLAB, ColouriseMatlabDoc, "matlab", FoldMatlabDoc, matlabWordListDesc)
	lmOctave(SCLEX_OCTAVE, ColouriseOctaveDoc, "octave", FoldOctaveDoc, octaveWordListDesc)
	lmMaxima(SCLEX_MAXIMA, ColouriseMaximaDoc, "maxima", 0, 0)
	lmMETAPOST(SCLEX_METAPOST, ColouriseMETAPOSTDoc, "metapost", FoldMetapostDoc, metapostWordListDesc)
	lmMMIXAL(SCLEX_MMIXAL, ColouriseMMIXALDoc, "mmixal", 0, MMIXALWordListDesc)
	lmModula(SCLEX_MODULA, ColouriseModulaDoc, "modula", FoldModulaDoc, scite501\lexilla\lexers\LexMPT.cxx | 191 | LexerModule lmLot(SCLEX_LOT, ColourizeLotDoc, "lot", FoldLotDoc, emptyWordListDesc)
	lmMSSQL(SCLEX_MSSQL, ColouriseMSSQLDoc, "mssql", FoldMSSQLDoc, sqlWordListDesc)
	lmMySQL(SCLEX_MYSQL, ColouriseMySQLDoc, "mysql", FoldMySQLDoc, mysqlWordListDesc)
	lmNim(SCLEX_NIM, LexerNim::LexerFactoryNim, "nim", nimWordListDesc)
	lmNimrod(SCLEX_NIMROD, ColouriseNimrodDoc, "nimrod", FoldNimrodDoc, scite501\lexilla\lexers\LexNsis.cxx | 659 | LexerModule lmNsis(SCLEX_NSIS, ColouriseNsisDoc, "nsis", FoldNsisDoc, nsisWordLists)
	lmNull(SCLEX_NULL, ColouriseNullDoc, "null")
	lmOpal(SCLEX_OPAL, ColouriseOpalDoc, "opal", NULL, opalWordListDesc)
	lmOScript(SCLEX_OSCRIPT, ColouriseOScriptDoc, "oscript", FoldOScriptDoc, oscriptWordListDesc)
	lmPascal(SCLEX_PASCAL, ColourisePascalDoc, "pascal", FoldPascalDoc, pascalWordListDesc)
	lmPB(SCLEX_POWERBASIC, ColourisePBDoc, "powerbasic", FoldPBDoc, pbWordListDesc)
	lmPerl(SCLEX_PERL, LexerPerl::LexerFactoryPerl, "perl", perlWordListDesc)
	lmPLM(SCLEX_PLM, ColourisePlmDoc, "PL/M", FoldPlmDoc, plmWordListDesc)
	lmPO(SCLEX_PO, ColourisePODoc, "po", FoldPODoc, poWordListDesc)
	lmPOV(SCLEX_POV, ColourisePovDoc, "pov", FoldPovDoc, povWordLists)
	lmPowerPro(SCLEX_POWERPRO, ColourisePowerProDocWrapper, "powerpro", FoldPowerProDoc, powerProWordLists)
	lmPowerShell(SCLEX_POWERSHELL, ColourisePowerShellDoc, "powershell", FoldPowerShellDoc, powershellWordLists)
	lmProgress(SCLEX_PROGRESS, LexerABL::LexerFactoryABL, "abl", ablWordLists)
	lmProps(SCLEX_PROPERTIES, ColourisePropsDoc, "props", FoldPropsDoc, emptyWordListDesc)
	lmPS(SCLEX_PS, ColourisePSDoc, "ps", FoldPSDoc, psWordListDesc)
	lmPython(SCLEX_PYTHON, LexerPython::LexerFactoryPython, "python", scite501\lexilla\lexers\LexR.cxx | 214 | LexerModule lmR(SCLEX_R, ColouriseRDoc, "r", FoldRDoc, RWordLists)
	lmRaku(SCLEX_RAKU, LexerRaku::LexerFactoryRaku, "raku", rakuWordLists)
	lmREBOL(SCLEX_REBOL, ColouriseRebolDoc, "rebol", FoldRebolDoc, rebolWordListDesc)
	lmRegistry(SCLEX_REGISTRY, scite501\lexilla\lexers\LexRuby.cxx | 1879 | LexerModule lmRuby(SCLEX_RUBY, ColouriseRbDoc, "ruby", FoldRbDoc, rubyWordListDesc)
	lmRust(SCLEX_RUST, LexerRust::LexerFactoryRust, "rust", rustWordLists)
	lmSAS(SCLEX_SAS, ColouriseSASDoc, "sas", FoldSASDoc, SASWordLists)
	lmScriptol(SCLEX_SCRIPTOL, ColouriseSolDoc, "scriptol", FoldSolDoc)
	lmSmalltalk(SCLEX_SMALLTALK, colorizeSmalltalkDoc, "smalltalk", NULL, smalltalkWordListDesc)
	lmSML(SCLEX_SML, ColouriseSMLDoc, "SML", FoldSMLDoc, SMLWordListDesc)
	lmSorc(SCLEX_SORCUS, ColouriseSorcusDoc, "sorcins", 0, SorcusWordListDesc)
	lmSpecman(SCLEX_SPECMAN, ColouriseSpecmanDocSensitive, "specman", FoldSpecmanDoc, specmanWordLists)
	lmSpice(SCLEX_SPICE, ColouriseDocument, "spice", NULL, spiceWordListDesc)
	lmSQL(SCLEX_SQL, LexerSQL::LexerFactorySQL, "sql", sqlWordListDesc)
	lmStata(SCLEX_STATA, ColouriseStataDoc, "stata", FoldStataDoc, StataWordLists)
	lmSTTXT(SCLEX_STTXT, ColouriseSTTXTDoc, "fcST", FoldSTTXTDoc, STTXTWordListDesc)
	lmTACL(SCLEX_TACL, ColouriseTACLDoc, "TACL", FoldTACLDoc, TACLWordListDesc)
	lmTADS3(SCLEX_TADS3, ColouriseTADS3Doc, "tads3", FoldTADS3Doc, tads3WordList)
	lmTAL(SCLEX_TAL, ColouriseTALDoc, "TAL", FoldTALDoc, TALWordListDesc)
	lmTCL(SCLEX_TCL, ColouriseTCLDoc, "tcl", 0, tclWordListDesc)
	lmTCMD(SCLEX_TCMD, ColouriseTCMDDoc, "tcmd", FoldTCMDDoc, tcmdWordListDesc)
	lmTeX(SCLEX_TEX, ColouriseTeXDoc, "tex", FoldTexDoc, texWordListDesc)
	lmTxt2tags(SCLEX_TXT2TAGS, ColorizeTxt2tagsDoc, "txt2tags")
	lmVB(SCLEX_VB, ColouriseVBNetDoc, "vb", FoldVBDoc, vbWordListDesc)
	lmVBScript(SCLEX_VBSCRIPT, ColouriseVBScriptDoc, "vbscript", FoldVBDoc, vbWordListDesc)
	lmVerilog(SCLEX_VERILOG, LexerVerilog::LexerFactoryVerilog, "verilog", verilogWordLists)
	lmVHDL(SCLEX_VHDL, ColouriseVHDLDoc, "vhdl", FoldVHDLDoc, VHDLWordLists)
	lmVisualProlog(SCLEX_VISUALPROLOG, LexerVisualProlog::LexerFactoryVisualProlog, "visualprolog", visualPrologWordLists)
	lmX12(SCLEX_X12, LexerX12::Factory, "x12")
	lmYAML(SCLEX_YAML, ColouriseYAMLDoc, "yaml", FoldYAMLDoc, yamlWordListDesc)
*/