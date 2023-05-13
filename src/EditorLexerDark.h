#pragma once

class CLanguageDatabase;
class CEditorCtrl;

namespace EditorLexerDark 
{
	void LoadLexer(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl, const CString& czLexer);

	void Init_python_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_cpp_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_ada_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_asm_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_inno_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_bash_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_batch_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_c_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_cmake_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_makefile_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_cshape_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_css_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_erlang_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_fortran_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_html_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_java_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_javascript_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_typescript_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_lua_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_matlab_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_pascal_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_perl_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_php_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_powershell_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_ruby_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_rust_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_golang_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_sql_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_tcl_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_vb_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_verilog_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_vhdl_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_xml_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_json_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_markdown_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_protobuf_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_r_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_flexlicense_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_resource_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_autoit_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_freebasic_Editor(CLanguageDatabase* pDatabase, CEditorCtrl* pEditorCtrl);
	void Init_text_Editor(CEditorCtrl* pEditorCtrl);
}
