#include "stdafx.h"
#include "Editor.h"
#include "EditorColorDark.h"
#include "EditorLexerDark.h"
#include "EditorDatabase.h"
#include "AppUtil.h"
#include "AppSettings.h"

void EditorLexerDark::LoadLexer(CLanguageDatabase* pDatabase,
											CEditorCtrl* pEditorCtrl,
											const CString& czLexer)
{
	if (!pDatabase) return;
	if (czLexer == "ada")
		Init_ada_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "asm")
		Init_asm_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "inno")
		Init_inno_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "bash")
		Init_bash_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "batch")
		Init_batch_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "cmake")
		Init_cmake_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "cpp")
		Init_cpp_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "c")
		Init_c_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "css")
		Init_css_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "erlang")
		Init_erlang_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "fortran")
		Init_fortran_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "hypertext")
		Init_html_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "lua")
		Init_lua_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "matlab")
		Init_matlab_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "pascal")
		Init_pascal_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "perl")
		Init_perl_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "phpscript")
		Init_php_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "powershell")
		Init_powershell_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "python")
		Init_python_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "ruby")
		Init_ruby_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "rust")
		Init_rust_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "golang")
		Init_golang_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "sql")
		Init_sql_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "tcl")
		Init_tcl_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "vb")
		Init_vb_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "verilog")
		Init_verilog_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "vhdl")
		Init_vhdl_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "xml")
		Init_xml_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "kix")
		Init_json_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "java")
		Init_java_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "javascript")
		Init_javascript_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "typescript")
		Init_typescript_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "cs")
		Init_cshape_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "markdown")
		Init_markdown_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "protobuf")
		Init_protobuf_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "r")
		Init_r_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "FLEXlm")
		Init_flexlicense_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "Resource")
		Init_resource_Editor(pDatabase, pEditorCtrl);
	else if (czLexer == "autoit")
		Init_autoit_Editor(pDatabase, pEditorCtrl);
	else
		Init_text_Editor(pEditorCtrl);
}

void EditorLexerDark::Init_ada_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("ada");
	pEditorCtrl->SetKeywords(EditorColorDark::g_ada_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_ada[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_ada[i].iItem, EditorColorDark::g_rgb_Syntax_ada[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_ada_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_ada_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_ada_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_ada_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_ada_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_asm_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("asm");
	pEditorCtrl->SetKeywords(EditorColorDark::g_asm_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_asm[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_asm[i].iItem, EditorColorDark::g_rgb_Syntax_asm[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_asm_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_asm_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_asm_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_asm_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_asm_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_inno_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("asm");
	pEditorCtrl->SetKeywords(EditorColorDark::g_inno_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_inno[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_inno[i].iItem, EditorColorDark::g_rgb_Syntax_inno[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_inno_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_inno_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_inno_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_inno_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_inno_commentEnd);
	CString strKeywords = AppUtils::StdToCString(EditorColorDark::g_inno_KeyWords);
	pDatabase->SetLanguageAutoComplete(strKeywords);
}

void EditorLexerDark::Init_bash_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("bash");
	pEditorCtrl->SetKeywords(EditorColorDark::g_bash_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_bash[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_bash[i].iItem, EditorColorDark::g_rgb_Syntax_bash[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_bash_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_bash_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_bash_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_bash_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_bash_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_batch_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("batch");
	pEditorCtrl->SetKeywords(EditorColorDark::g_batch_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_batch[i].iItem != -1; i++)
	{
		auto iItem = EditorColorDark::g_rgb_Syntax_batch[i].iItem;
		auto rgb = EditorColorDark::g_rgb_Syntax_batch[i].rgb;
		if (iItem == SCE_C_COMMENTLINE || iItem == SCE_C_COMMENTDOC || iItem == SCE_C_WORD2)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else if (iItem == SCE_C_COMMENT)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_batch_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_batch_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_batch_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_batch_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_batch_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_c_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorDark::g_c_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_c[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_c[i].iItem, EditorColorDark::g_rgb_Syntax_c[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_c_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_c_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_c_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_c_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_c_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_cmake_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cmake");
	pEditorCtrl->SetKeywords(EditorColorDark::g_cmake_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_cmake[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_cmake[i].iItem, EditorColorDark::g_rgb_Syntax_cmake[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_cmake_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_cmake_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_cmake_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_cmake_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_cmake_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_cpp_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorDark::g_cpp_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_cpp[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_cpp[i].iItem, EditorColorDark::g_rgb_Syntax_cpp[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_cpp_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_cpp_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_cpp_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_cpp_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_cpp_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_cpp_Editor_NoDB(CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords("");
	for (int i = 0; EditorColorDark::g_rgb_Syntax_cpp[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_cpp[i].iItem, EditorColorDark::g_rgb_Syntax_cpp[i].rgb);
	}
}

void EditorLexerDark::Init_cshape_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorDark::g_cs_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_cs[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_cs[i].iItem, EditorColorDark::g_rgb_Syntax_cs[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_cs_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_cs_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_cs_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_cs_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_cs_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_css_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("css");
	pEditorCtrl->SetKeywords(EditorColorDark::g_css_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_css[i].iItem != -1; i++)
	{
		auto iItem = EditorColorDark::g_rgb_Syntax_css[i].iItem;
		auto rgb = EditorColorDark::g_rgb_Syntax_css[i].rgb;
		if (iItem == SCE_CSS_TAG || iItem == SCE_CSS_PSEUDOCLASS || iItem == SCE_CSS_OPERATOR || iItem == SCE_CSS_IMPORTANT)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else if (iItem == SCE_CSS_CLASS)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else if (iItem == SCE_CSS_IDENTIFIER2)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_css_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_css_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_css_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_css_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_css_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_erlang_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("erlang");
	pEditorCtrl->SetKeywords(EditorColorDark::g_erlang_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_erlang[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_erlang[i].iItem, EditorColorDark::g_rgb_Syntax_erlang[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_erlang_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_erlang_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_erlang_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_erlang_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_erlang_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_fortran_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("fortran");
	pEditorCtrl->SetKeywords(EditorColorDark::g_fortran_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_fortran[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_fortran[i].iItem, EditorColorDark::g_rgb_Syntax_fortran[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_fortran_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_fortran_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_fortran_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_fortran_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_fortran_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_html_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("hypertext");
	pEditorCtrl->SetKeywords(EditorColorDark::g_html_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_html[i].iItem != -1; i++)
	{
		auto iItem = EditorColorDark::g_rgb_Syntax_html[i].iItem;
		auto rgb = EditorColorDark::g_rgb_Syntax_html[i].rgb;
		/*if (iItem == SCE_H_ATTRIBUTE || iItem == SCE_H_ATTRIBUTEUNKNOWN)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else */if (iItem == SCE_H_TAG || iItem == SCE_H_ENTITY
			|| iItem == SCE_HB_DEFAULT || iItem == SCE_HJA_DEFAULT
			|| iItem == SCE_HBA_IDENTIFIER || iItem == SCE_HB_IDENTIFIER
			|| iItem == SCE_HPHP_OPERATOR || iItem == SCE_HPHP_DEFAULT
			|| iItem == SCE_H_OTHER || iItem == SCE_H_XMLSTART)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_html_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_html_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_html_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_html_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_html_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_html_Editor_NoDB(CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("hypertext");
	pEditorCtrl->SetKeywords("");
	for (int i = 0; EditorColorDark::g_rgb_Syntax_html[i].iItem != -1; i++)
	{
		auto iItem = EditorColorDark::g_rgb_Syntax_html[i].iItem;
		auto rgb = EditorColorDark::g_rgb_Syntax_html[i].rgb;
		if (iItem == SCE_H_ATTRIBUTE || iItem == SCE_H_ATTRIBUTEUNKNOWN)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else if (iItem == SCE_H_TAG || iItem == SCE_H_ENTITY
			|| iItem == SCE_HB_DEFAULT || iItem == SCE_HJA_DEFAULT
			|| iItem == SCE_HBA_IDENTIFIER || iItem == SCE_HB_IDENTIFIER
			|| iItem == SCE_HPHP_OPERATOR || iItem == SCE_HPHP_DEFAULT
			|| iItem == SCE_H_OTHER)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
		}
	}
}

void EditorLexerDark::Init_java_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorDark::g_java_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_java[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_java[i].iItem, EditorColorDark::g_rgb_Syntax_java[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_java_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_java_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_java_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_java_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_java_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_javascript_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorDark::g_javascript_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_javascript[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_javascript[i].iItem, EditorColorDark::g_rgb_Syntax_javascript[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_javascript_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_javascript_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_javascript_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_javascript_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_javascript_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_typescript_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorDark::g_typescript_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_typescript[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_typescript[i].iItem, EditorColorDark::g_rgb_Syntax_typescript[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_typescript_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_typescript_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_typescript_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_typescript_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_typescript_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_lua_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("lua");
	pEditorCtrl->SetKeywords(EditorColorDark::g_lua_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_lua[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_lua[i].iItem, EditorColorDark::g_rgb_Syntax_lua[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_lua_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_lua_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_lua_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_lua_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_lua_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_matlab_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("matlab");
	pEditorCtrl->SetKeywords(EditorColorDark::g_matlab_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_matlab[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_matlab[i].iItem, EditorColorDark::g_rgb_Syntax_matlab[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_matlab_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_matlab_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_matlab_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_matlab_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_matlab_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_pascal_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("pascal");
	pEditorCtrl->SetKeywords(EditorColorDark::g_pascal_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_pascal[i].iItem != -1; i++)
	{
		auto iItem = EditorColorDark::g_rgb_Syntax_pascal[i].iItem;
		auto rgb = EditorColorDark::g_rgb_Syntax_pascal[i].rgb;
		if (iItem == SCE_PAS_WORD)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else if (iItem == SCE_PAS_STRING)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else if (iItem == SCE_PAS_PREPROCESSOR || iItem == SCE_PAS_PREPROCESSOR2)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_pascal_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_pascal_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_pascal_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_pascal_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_pascal_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_perl_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("perl");
	pEditorCtrl->SetKeywords(EditorColorDark::g_perl_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_perl[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_perl[i].iItem, EditorColorDark::g_rgb_Syntax_perl[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_perl_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_perl_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_perl_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_perl_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_perl_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_php_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorDark::g_php_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_php[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_php[i].iItem, EditorColorDark::g_rgb_Syntax_php[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_php_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_php_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_php_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_php_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_php_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_powershell_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("powershell");
	pEditorCtrl->SetKeywords(EditorColorDark::g_powershell_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_powershell[i].iItem != -1; i++)
	{
		auto iItem = EditorColorDark::g_rgb_Syntax_powershell[i].iItem;
		auto rgb = EditorColorDark::g_rgb_Syntax_powershell[i].rgb;
		if (iItem == SCE_C_WORD || iItem == SCE_C_PREPROCESSOR || iItem == SCE_C_OPERATOR ||
			iItem == SCE_C_UUID || iItem == SCE_C_NUMBER)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else if (iItem == SCE_C_COMMENT || iItem == SCE_C_COMMENTLINE || iItem == SCE_C_COMMENTDOC || iItem == SCE_C_WORD2)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_powershell_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_powershell_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_powershell_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_powershell_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_powershell_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_python_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("python");
	pEditorCtrl->SetKeywords(EditorColorDark::g_python_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_python[i].iItem != -1; i++)
	{
		auto iItem = EditorColorDark::g_rgb_Syntax_python[i].iItem;
		auto rgb = EditorColorDark::g_rgb_Syntax_python[i].rgb;
		if (iItem == SCE_P_WORD || iItem == SCE_P_WORD2 || iItem == SCE_P_OPERATOR)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		if (iItem == SCE_P_CLASSNAME || iItem == SCE_P_DEFNAME)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else if (iItem == SCE_P_STRING || iItem == SCE_P_CHARACTER)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_python_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_python_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_python_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_python_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_python_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_python_Editor_NoDB(CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("python");
	pEditorCtrl->SetKeywords("");
	for (int i = 0; EditorColorDark::g_rgb_Syntax_python_2[i].iItem != -1; i++)
	{
		auto iItem = EditorColorDark::g_rgb_Syntax_python_2[i].iItem;
		auto rgb = EditorColorDark::g_rgb_Syntax_python_2[i].rgb;
		pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
	}
}

void EditorLexerDark::Init_ruby_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("ruby");
	pEditorCtrl->SetKeywords(EditorColorDark::g_ruby_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_ruby[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_ruby[i].iItem, EditorColorDark::g_rgb_Syntax_ruby[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_ruby_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_ruby_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_ruby_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_ruby_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_ruby_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}
void EditorLexerDark::Init_rust_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("rust");
	pEditorCtrl->SetKeywords(EditorColorDark::g_rust_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_rust[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_rust[i].iItem, EditorColorDark::g_rgb_Syntax_rust[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_rust_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_rust_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_rust_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_rust_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_rust_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_golang_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorDark::g_go_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_go[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_go[i].iItem, EditorColorDark::g_rgb_Syntax_go[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_go_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_go_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_go_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_go_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_go_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_sql_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("sql");
	pEditorCtrl->SetKeywords(EditorColorDark::g_sql_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_sql[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_sql[i].iItem, EditorColorDark::g_rgb_Syntax_sql[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_sql_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_sql_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_sql_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_sql_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_sql_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_tcl_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("tcl");
	pEditorCtrl->SetKeywords(EditorColorDark::g_tcl_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_tcl[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_tcl[i].iItem, EditorColorDark::g_rgb_Syntax_tcl[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_tcl_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_tcl_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_tcl_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_tcl_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_tcl_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_vb_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("vb");
	pEditorCtrl->SetKeywords(EditorColorDark::g_vb_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_vb[i].iItem != -1; i++)
	{
		auto iItem = EditorColorDark::g_rgb_Syntax_vb[i].iItem;
		auto rgb = EditorColorDark::g_rgb_Syntax_vb[i].rgb;
		if (iItem == SCE_C_COMMENTDOC)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else if (iItem == SCE_C_NUMBER)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_vb_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_vb_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_vb_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_vb_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_vb_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_verilog_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("verilog");
	pEditorCtrl->SetKeywords(EditorColorDark::g_verilog_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_verilog[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_verilog[i].iItem, EditorColorDark::g_rgb_Syntax_verilog[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_verilog_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_verilog_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_verilog_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_verilog_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_verilog_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}
void EditorLexerDark::Init_vhdl_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("vhdl");
	pEditorCtrl->SetKeywords(EditorColorDark::g_vhdl_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_vhdl[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_vhdl[i].iItem, EditorColorDark::g_rgb_Syntax_vhdl[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_vhdl_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_vhdl_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_vhdl_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_vhdl_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_vhdl_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_xml_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("xml");
	pEditorCtrl->SetKeywords(EditorColorDark::g_xml_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_html[i].iItem != -1; i++)
	{
		auto iItem = EditorColorDark::g_rgb_Syntax_html[i].iItem;
		auto rgb = EditorColorDark::g_rgb_Syntax_html[i].rgb;
		/*if (iItem == SCE_H_ATTRIBUTE || iItem == SCE_H_ATTRIBUTEUNKNOWN)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else */if (iItem == SCE_H_TAG || iItem == SCE_H_ENTITY
			|| iItem == SCE_HB_DEFAULT || iItem == SCE_HJA_DEFAULT
			|| iItem == SCE_HBA_IDENTIFIER || iItem == SCE_HB_IDENTIFIER
			|| iItem == SCE_HPHP_OPERATOR || iItem == SCE_HPHP_DEFAULT
			|| iItem == SCE_H_OTHER)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_xml_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_xml_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_xml_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_xml_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_xml_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_json_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("kix");
	pEditorCtrl->SetKeywords(EditorColorDark::g_json_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_json[i].iItem != -1; i++)
	{
		auto iItem = EditorColorDark::g_rgb_Syntax_json[i].iItem;
		auto rgb = EditorColorDark::g_rgb_Syntax_json[i].rgb;
		if (iItem == SCE_JSON_DEFAULT || iItem == SCE_JSON_ESCAPESEQUENCE)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_json_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_json_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_json_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_json_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_json_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_markdown_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("markdown");
	pEditorCtrl->SetKeywords(EditorColorDark::g_markdown_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_markdown[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_markdown[i].iItem, EditorColorDark::g_rgb_Syntax_markdown[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_markdown_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_markdown_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_markdown_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_markdown_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_markdown_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_protobuf_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorDark::g_protobuf_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_protobuf[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_protobuf[i].iItem, EditorColorDark::g_rgb_Syntax_protobuf[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_protobuf_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_protobuf_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_protobuf_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_protobuf_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_protobuf_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_r_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("r");
	pEditorCtrl->SetKeywords(EditorColorDark::g_r_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_r[i].iItem != -1; i++)
	{
		auto iItem = EditorColorDark::g_rgb_Syntax_r[i].iItem;
		auto rgb = EditorColorDark::g_rgb_Syntax_r[i].rgb;
		if (iItem == SCE_R_KWORD || iItem == SCE_R_BASEKWORD)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		if (iItem == SCE_R_STRING || iItem == SCE_R_STRING2)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_r_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_r_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_r_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_r_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_r_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerDark::Init_flexlicense_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("python");
	pEditorCtrl->SetKeywords(EditorColorDark::g_flexlicense_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_flexlicense[i].iItem != -1; i++)
	{
		auto iItem = EditorColorDark::g_rgb_Syntax_flexlicense[i].iItem;
		auto rgb = EditorColorDark::g_rgb_Syntax_flexlicense[i].rgb;
		if (iItem == SCE_P_WORD || iItem == SCE_P_WORD2 || iItem == SCE_P_OPERATOR)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else if (iItem == SCE_P_STRING || iItem == SCE_P_CHARACTER)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_ThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_flexlicense_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_flexlicense_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_flexlicense_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_flexlicense_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_flexlicense_commentEnd);
}

void EditorLexerDark::Init_resource_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorDark::g_resource_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_resource[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_resource[i].iItem, EditorColorDark::g_rgb_Syntax_resource[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_resource_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_resource_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_resource_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_resource_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_resource_commentEnd);
	CString strKeywords = AppUtils::StdToCString(EditorColorDark::g_resource_KeyWords);
	pDatabase->SetLanguageAutoComplete(strKeywords);
}

void EditorLexerDark::Init_autoit_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorDark::g_autoit_KeyWords);
	for (int i = 0; EditorColorDark::g_rgb_Syntax_autoit[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorDark::g_rgb_Syntax_autoit[i].iItem, EditorColorDark::g_rgb_Syntax_autoit[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorDark::g_str_autoit_language);
	pDatabase->SetLanguageExtension(EditorColorDark::g_str_autoit_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorDark::g_str_autoit_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorDark::g_str_autoit_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorDark::g_str_autoit_commentEnd);
	CString strKeywords = AppUtils::StdToCString(EditorColorDark::g_autoit_KeyWords);
	pDatabase->SetLanguageAutoComplete(strKeywords);
}

void EditorLexerDark::Init_text_Editor(CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("plaintext");
	pEditorCtrl->SetKeywords("");
}