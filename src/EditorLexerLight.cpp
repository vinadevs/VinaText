#include "stdafx.h"
#include "Editor.h"
#include "EditorColorLight.h"
#include "EditorLexerLight.h"
#include "EditorDatabase.h"
#include "AppUtil.h"
#include "AppSettings.h"

void EditorLexerLight::LoadLexer(CLanguageDatabase* pDatabase,
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
	else if (czLexer == "freebasic")
		Init_freebasic_Editor(pDatabase, pEditorCtrl);
	else
		Init_text_Editor(pEditorCtrl);
}

void EditorLexerLight::Init_ada_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("ada");
	pEditorCtrl->SetKeywords(EditorColorLight::g_ada_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_ada[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_ada[i].iItem, EditorColorLight::g_rgb_Syntax_ada[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_ada_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_ada_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_ada_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_ada_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_ada_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_asm_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("asm");
	pEditorCtrl->SetKeywords(EditorColorLight::g_asm_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_asm[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_asm[i].iItem, EditorColorLight::g_rgb_Syntax_asm[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_asm_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_asm_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_asm_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_asm_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_asm_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_inno_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("asm");
	pEditorCtrl->SetKeywords(EditorColorLight::g_inno_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_inno[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_inno[i].iItem, EditorColorLight::g_rgb_Syntax_inno[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_inno_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_inno_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_inno_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_inno_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_inno_commentEnd);
	CString strKeywords = AppUtils::StdToCString(EditorColorLight::g_inno_KeyWords);
	pDatabase->SetLanguageAutoComplete(strKeywords);
}

void EditorLexerLight::Init_bash_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("bash");
	pEditorCtrl->SetKeywords(EditorColorLight::g_bash_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_bash[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageBashFontStyle(EditorColorLight::g_rgb_Syntax_bash[i].iItem, EditorColorLight::g_rgb_Syntax_bash[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_bash_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_bash_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_bash_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_bash_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_bash_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_batch_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("batch");
	pEditorCtrl->SetKeywords(EditorColorLight::g_batch_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_batch[i].iItem != -1; i++)
	{
		auto iItem = EditorColorLight::g_rgb_Syntax_batch[i].iItem;
		auto rgb = EditorColorLight::g_rgb_Syntax_batch[i].rgb;
		if (iItem == SCE_C_COMMENTLINE || iItem == SCE_C_COMMENTDOC || iItem == SCE_C_WORD2)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else if (iItem == SCE_C_COMMENT)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_batch_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_batch_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_batch_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_batch_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_batch_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_c_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorLight::g_c_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_c[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_c[i].iItem, EditorColorLight::g_rgb_Syntax_c[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_c_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_c_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_c_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_c_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_c_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_cmake_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cmake");
	pEditorCtrl->SetKeywords(EditorColorLight::g_cmake_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_cmake[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_cmake[i].iItem, EditorColorLight::g_rgb_Syntax_cmake[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_cmake_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_cmake_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_cmake_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_cmake_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_cmake_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_cpp_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorLight::g_cpp_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_cpp[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_cpp[i].iItem, EditorColorLight::g_rgb_Syntax_cpp[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_cpp_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_cpp_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_cpp_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_cpp_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_cpp_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_cpp_Editor_NoDB(CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords("");
	for (int i = 0; EditorColorLight::g_rgb_Syntax_cpp[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_cpp[i].iItem, EditorColorLight::g_rgb_Syntax_cpp[i].rgb);
	}
}

void EditorLexerLight::Init_cshape_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorLight::g_cs_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_cs[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_cs[i].iItem, EditorColorLight::g_rgb_Syntax_cs[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_cs_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_cs_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_cs_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_cs_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_cs_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_css_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("css");
	pEditorCtrl->SetKeywords(EditorColorLight::g_css_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_css[i].iItem != -1; i++)
	{
		auto iItem = EditorColorLight::g_rgb_Syntax_css[i].iItem;
		auto rgb = EditorColorLight::g_rgb_Syntax_css[i].rgb;
		if (iItem == SCE_CSS_TAG || iItem == SCE_CSS_PSEUDOCLASS || iItem == SCE_CSS_OPERATOR || iItem == SCE_CSS_IMPORTANT)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else if (iItem == SCE_CSS_CLASS)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else if (iItem == SCE_CSS_IDENTIFIER2)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_css_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_css_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_css_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_css_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_css_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_erlang_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("erlang");
	pEditorCtrl->SetKeywords(EditorColorLight::g_erlang_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_erlang[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_erlang[i].iItem, EditorColorLight::g_rgb_Syntax_erlang[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_erlang_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_erlang_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_erlang_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_erlang_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_erlang_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_fortran_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("fortran");
	pEditorCtrl->SetKeywords(EditorColorLight::g_fortran_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_fortran[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_fortran[i].iItem, EditorColorLight::g_rgb_Syntax_fortran[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_fortran_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_fortran_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_fortran_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_fortran_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_fortran_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_html_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("hypertext");
	pEditorCtrl->SetKeywords(EditorColorLight::g_html_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_html[i].iItem != -1; i++)
	{
		auto iItem = EditorColorLight::g_rgb_Syntax_html[i].iItem;
		auto rgb = EditorColorLight::g_rgb_Syntax_html[i].rgb;
		/*if (iItem == SCE_H_ATTRIBUTE || iItem == SCE_H_ATTRIBUTEUNKNOWN)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else */if (iItem == SCE_H_TAG || iItem == SCE_H_ENTITY
			|| iItem == SCE_HB_DEFAULT || iItem == SCE_HJA_DEFAULT
			|| iItem == SCE_HBA_IDENTIFIER || iItem == SCE_HB_IDENTIFIER
			|| iItem == SCE_HPHP_OPERATOR || iItem == SCE_HPHP_DEFAULT
			|| iItem == SCE_H_OTHER || iItem == SCE_H_XMLSTART)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_html_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_html_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_html_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_html_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_html_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_html_Editor_NoDB(CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("hypertext");
	pEditorCtrl->SetKeywords("");
	for (int i = 0; EditorColorLight::g_rgb_Syntax_html[i].iItem != -1; i++)
	{
		auto iItem = EditorColorLight::g_rgb_Syntax_html[i].iItem;
		auto rgb = EditorColorLight::g_rgb_Syntax_html[i].rgb;
		if (iItem == SCE_H_ATTRIBUTE || iItem == SCE_H_ATTRIBUTEUNKNOWN)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else if (iItem == SCE_H_TAG || iItem == SCE_H_ENTITY
			|| iItem == SCE_HB_DEFAULT || iItem == SCE_HJA_DEFAULT
			|| iItem == SCE_HBA_IDENTIFIER || iItem == SCE_HB_IDENTIFIER
			|| iItem == SCE_HPHP_OPERATOR || iItem == SCE_HPHP_DEFAULT
			|| iItem == SCE_H_OTHER)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		}
	}
}

void EditorLexerLight::Init_java_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorLight::g_java_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_java[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_java[i].iItem, EditorColorLight::g_rgb_Syntax_java[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_java_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_java_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_java_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_java_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_java_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_javascript_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorLight::g_javascript_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_javascript[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_javascript[i].iItem, EditorColorLight::g_rgb_Syntax_javascript[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_javascript_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_javascript_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_javascript_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_javascript_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_javascript_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_typescript_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorLight::g_typescript_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_typescript[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_typescript[i].iItem, EditorColorLight::g_rgb_Syntax_typescript[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_typescript_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_typescript_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_typescript_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_typescript_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_typescript_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_lua_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("lua");
	pEditorCtrl->SetKeywords(EditorColorLight::g_lua_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_lua[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_lua[i].iItem, EditorColorLight::g_rgb_Syntax_lua[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_lua_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_lua_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_lua_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_lua_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_lua_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_matlab_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("matlab");
	pEditorCtrl->SetKeywords(EditorColorLight::g_matlab_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_matlab[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_matlab[i].iItem, EditorColorLight::g_rgb_Syntax_matlab[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_matlab_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_matlab_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_matlab_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_matlab_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_matlab_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_pascal_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("pascal");
	pEditorCtrl->SetKeywords(EditorColorLight::g_pascal_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_pascal[i].iItem != -1; i++)
	{
		auto iItem = EditorColorLight::g_rgb_Syntax_pascal[i].iItem;
		auto rgb = EditorColorLight::g_rgb_Syntax_pascal[i].rgb;
		if (iItem == SCE_PAS_WORD)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else if (iItem == SCE_PAS_STRING)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else if (iItem == SCE_PAS_PREPROCESSOR || iItem == SCE_PAS_PREPROCESSOR2)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_pascal_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_pascal_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_pascal_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_pascal_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_pascal_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_perl_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("perl");
	pEditorCtrl->SetKeywords(EditorColorLight::g_perl_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_perl[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_perl[i].iItem, EditorColorLight::g_rgb_Syntax_perl[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_perl_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_perl_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_perl_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_perl_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_perl_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_php_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorLight::g_php_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_php[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_php[i].iItem, EditorColorLight::g_rgb_Syntax_php[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_php_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_php_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_php_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_php_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_php_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_powershell_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("powershell");
	pEditorCtrl->SetKeywords(EditorColorLight::g_powershell_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_powershell[i].iItem != -1; i++)
	{
		auto iItem = EditorColorLight::g_rgb_Syntax_powershell[i].iItem;
		auto rgb = EditorColorLight::g_rgb_Syntax_powershell[i].rgb;
		if (iItem == SCE_C_WORD || iItem == SCE_C_PREPROCESSOR || iItem == SCE_C_OPERATOR ||
			iItem == SCE_C_UUID || iItem == SCE_C_NUMBER)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else if (iItem == SCE_C_COMMENT || iItem == SCE_C_COMMENTLINE || iItem == SCE_C_COMMENTDOC || iItem == SCE_C_WORD2)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_powershell_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_powershell_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_powershell_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_powershell_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_powershell_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_python_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("python");
	pEditorCtrl->SetKeywords(EditorColorLight::g_python_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_python[i].iItem != -1; i++)
	{
		auto iItem = EditorColorLight::g_rgb_Syntax_python[i].iItem;
		auto rgb = EditorColorLight::g_rgb_Syntax_python[i].rgb;
		if (iItem == SCE_P_WORD || iItem == SCE_P_WORD2 || iItem == SCE_P_OPERATOR)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		if (iItem == SCE_P_CLASSNAME || iItem == SCE_P_DEFNAME)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else if (iItem == SCE_P_STRING || iItem == SCE_P_CHARACTER)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_python_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_python_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_python_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_python_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_python_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_python_Editor_NoDB(CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("python");
	pEditorCtrl->SetKeywords("");
	for (int i = 0; EditorColorLight::g_rgb_Syntax_python_2[i].iItem != -1; i++)
	{
		auto iItem = EditorColorLight::g_rgb_Syntax_python_2[i].iItem;
		auto rgb = EditorColorLight::g_rgb_Syntax_python_2[i].rgb;
		pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
	}
}

void EditorLexerLight::Init_ruby_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("ruby");
	pEditorCtrl->SetKeywords(EditorColorLight::g_ruby_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_ruby[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_ruby[i].iItem, EditorColorLight::g_rgb_Syntax_ruby[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_ruby_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_ruby_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_ruby_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_ruby_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_ruby_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}
void EditorLexerLight::Init_rust_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("rust");
	pEditorCtrl->SetKeywords(EditorColorLight::g_rust_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_rust[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_rust[i].iItem, EditorColorLight::g_rgb_Syntax_rust[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_rust_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_rust_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_rust_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_rust_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_rust_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_golang_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorLight::g_go_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_go[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_go[i].iItem, EditorColorLight::g_rgb_Syntax_go[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_go_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_go_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_go_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_go_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_go_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_sql_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("sql");
	pEditorCtrl->SetKeywords(EditorColorLight::g_sql_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_sql[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_sql[i].iItem, EditorColorLight::g_rgb_Syntax_sql[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_sql_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_sql_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_sql_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_sql_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_sql_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_tcl_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("tcl");
	pEditorCtrl->SetKeywords(EditorColorLight::g_tcl_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_tcl[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_tcl[i].iItem, EditorColorLight::g_rgb_Syntax_tcl[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_tcl_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_tcl_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_tcl_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_tcl_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_tcl_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_vb_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("vb");
	pEditorCtrl->SetKeywords(EditorColorLight::g_vb_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_vb[i].iItem != -1; i++)
	{
		auto iItem = EditorColorLight::g_rgb_Syntax_vb[i].iItem;
		auto rgb = EditorColorLight::g_rgb_Syntax_vb[i].rgb;
		if (iItem == SCE_C_COMMENTDOC)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else if (iItem == SCE_C_NUMBER)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_vb_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_vb_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_vb_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_vb_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_vb_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_verilog_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("verilog");
	pEditorCtrl->SetKeywords(EditorColorLight::g_verilog_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_verilog[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_verilog[i].iItem, EditorColorLight::g_rgb_Syntax_verilog[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_verilog_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_verilog_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_verilog_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_verilog_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_verilog_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}
void EditorLexerLight::Init_vhdl_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("vhdl");
	pEditorCtrl->SetKeywords(EditorColorLight::g_vhdl_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_vhdl[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_vhdl[i].iItem, EditorColorLight::g_rgb_Syntax_vhdl[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_vhdl_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_vhdl_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_vhdl_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_vhdl_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_vhdl_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_xml_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("xml");
	pEditorCtrl->SetKeywords(EditorColorLight::g_xml_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_html[i].iItem != -1; i++)
	{
		auto iItem = EditorColorLight::g_rgb_Syntax_html[i].iItem;
		auto rgb = EditorColorLight::g_rgb_Syntax_html[i].rgb;
		/*if (iItem == SCE_H_ATTRIBUTE || iItem == SCE_H_ATTRIBUTEUNKNOWN)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else */if (iItem == SCE_H_TAG || iItem == SCE_H_ENTITY
			|| iItem == SCE_HB_DEFAULT || iItem == SCE_HJA_DEFAULT
			|| iItem == SCE_HBA_IDENTIFIER || iItem == SCE_HB_IDENTIFIER
			|| iItem == SCE_HPHP_OPERATOR || iItem == SCE_HPHP_DEFAULT
			|| iItem == SCE_H_OTHER)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_xml_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_xml_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_xml_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_xml_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_xml_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_json_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorLight::g_json_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_json[i].iItem != -1; i++)
	{
		auto iItem = EditorColorLight::g_rgb_Syntax_json[i].iItem;
		auto rgb = EditorColorLight::g_rgb_Syntax_json[i].rgb;
		if (iItem == SCE_JSON_DEFAULT || iItem == SCE_JSON_ESCAPESEQUENCE)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_json_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_json_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_json_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_json_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_json_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_markdown_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("markdown");
	pEditorCtrl->SetKeywords(EditorColorLight::g_markdown_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_markdown[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_markdown[i].iItem, EditorColorLight::g_rgb_Syntax_markdown[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_markdown_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_markdown_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_markdown_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_markdown_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_markdown_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_protobuf_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorLight::g_protobuf_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_protobuf[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_protobuf[i].iItem, EditorColorLight::g_rgb_Syntax_protobuf[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_protobuf_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_protobuf_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_protobuf_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_protobuf_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_protobuf_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_r_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("r");
	pEditorCtrl->SetKeywords(EditorColorLight::g_r_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_r[i].iItem != -1; i++)
	{
		auto iItem = EditorColorLight::g_rgb_Syntax_r[i].iItem;
		auto rgb = EditorColorLight::g_rgb_Syntax_r[i].rgb;
		if (iItem == SCE_R_KWORD || iItem == SCE_R_BASEKWORD)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		if (iItem == SCE_R_STRING || iItem == SCE_R_STRING2)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_r_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_r_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_r_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_r_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_r_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_flexlicense_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("python");
	pEditorCtrl->SetKeywords(EditorColorLight::g_flexlicense_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_flexlicense[i].iItem != -1; i++)
	{
		auto iItem = EditorColorLight::g_rgb_Syntax_flexlicense[i].iItem;
		auto rgb = EditorColorLight::g_rgb_Syntax_flexlicense[i].rgb;
		if (iItem == SCE_P_WORD || iItem == SCE_P_WORD2 || iItem == SCE_P_OPERATOR)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else if (iItem == SCE_P_STRING || iItem == SCE_P_CHARACTER)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_flexlicense_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_flexlicense_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_flexlicense_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_flexlicense_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_flexlicense_commentEnd);
	CString strKeywords = AppUtils::StdToCString(EditorColorLight::g_resource_KeyWords);
	pDatabase->SetLanguageAutoComplete(strKeywords);
}

void EditorLexerLight::Init_resource_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorLight::g_resource_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_resource[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_resource[i].iItem, EditorColorLight::g_rgb_Syntax_resource[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_resource_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_resource_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_resource_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_resource_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_resource_commentEnd);
	CString strKeywords = AppUtils::StdToCString(EditorColorLight::g_resource_KeyWords);
	pDatabase->SetLanguageAutoComplete(strKeywords);
}

void EditorLexerLight::Init_autoit_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("cpp");
	pEditorCtrl->SetKeywords(EditorColorLight::g_autoit_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_autoit[i].iItem != -1; i++)
	{
		pEditorCtrl->SetLanguageCFontStyle(EditorColorLight::g_rgb_Syntax_autoit[i].iItem, EditorColorLight::g_rgb_Syntax_autoit[i].rgb);
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_autoit_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_autoit_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_autoit_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_autoit_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_autoit_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_freebasic_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("freebasic");
	pEditorCtrl->SetKeywords(EditorColorLight::g_freebasic_KeyWords);
	for (int i = 0; EditorColorLight::g_rgb_Syntax_freebasic[i].iItem != -1; i++)
	{
		auto iItem = EditorColorLight::g_rgb_Syntax_freebasic[i].iItem;
		auto rgb = EditorColorLight::g_rgb_Syntax_freebasic[i].rgb;
		if (iItem == SCE_C_COMMENTDOC)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETBOLD, iItem, 1);
		}
		else if (iItem == SCE_C_NUMBER)
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
			pEditorCtrl->DoCommand(SCI_STYLESETITALIC, iItem, 1);
		}
		else
		{
			pEditorCtrl->SetColorForStyle(iItem, rgb, AppSettingMgr.m_AppThemeColor);
		}
	}
	pDatabase->SetLanguageName(EditorColorLight::g_str_freebasic_language);
	pDatabase->SetLanguageExtension(EditorColorLight::g_str_freebasic_extention);
	pDatabase->SetLanguageCommentSymbol(EditorColorLight::g_str_freebasic_commentline);
	pDatabase->SetLanguageCommentStart(EditorColorLight::g_str_freebasic_commentStart);
	pDatabase->SetLanguageCommentEnd(EditorColorLight::g_str_freebasic_commentEnd);
	pEditorCtrl->LoadExternalSettings(pDatabase);
}

void EditorLexerLight::Init_text_Editor(CEditorCtrl* pEditorCtrl)
{
	pEditorCtrl->SetLexer("plaintext");
	pEditorCtrl->SetKeywords("");
}