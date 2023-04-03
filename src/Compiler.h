/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

class CMainFrame;
class CEditorDoc;
class CEditorView;

struct BuildSessionInfo
{
	CString _strExeFileName;
	CString _strExeFolderPath;
	CString _strExeFilePath;
	CString _strFilePath;
	CString _strJavaVMPath; // only use for run Java
	CString _strCommandLine;
	LONGLONG _BuildMeasureTime = 0;
};

namespace VinaTextCompiler
{
	// Common API
	void START_COMPILER(VINATEXT_SUPPORTED_LANGUAGE docLanguage, CEditorDoc* pDoc); // use build window
	void START_GDB_CMD(VINATEXT_SUPPORTED_LANGUAGE docLanguage, CEditorDoc* pDoc); // use cmd window
	void START_GDB_DEBUGGER(VINATEXT_SUPPORTED_LANGUAGE docLanguage, CEditorDoc* pDoc); // use build window
	void START_EXE_LOADER(VINATEXT_SUPPORTED_LANGUAGE docLanguage, CEditorDoc* pDoc); // use build window
	void START_JAVA_LOADER(VINATEXT_SUPPORTED_LANGUAGE docLanguage, CEditorDoc * pDoc, const CString & strCommandLineJVM); // use build window
	void START_EXE_CMD(const BuildSessionInfo& Info); // use cmd window
	void START_CMD(const BuildSessionInfo& Info); // use cmd window

	// C++
	void BuildCPP(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePath, const CString& strCompilerPath);
	CString GetBuildCommandlineCPP(CEditorView* pView, const CString& strFileBuildConfig, const CString & strCompilerPath, BOOL bDebugMode);
	BOOL GenerateFileBuildConfigCPP(const CString& strFilePath, BOOL bOpenFileBuildConfig = TRUE);
	void GetIncludeSourceFileCPP(const CString& strFilePath, const std::string & strFolderPath, std::vector<std::string>& vecIncludeSrcFile);

	// C
	void BuildC(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePath, const CString& strCompilerPath);
	CString GetBuildCommandlineC(CEditorView* pView, const CString& strFileBuildConfig, const CString & strCompilerPath, BOOL bDebugMode);
	BOOL GenerateFileBuildConfigC(const CString& strFilePath, BOOL bOpenFileBuildConfig = TRUE);
	void GetIncludeSourceFileC(const CString& strFilePath, const std::string & strFolderPath, std::vector<std::string>& vecIncludeSrcFile);

	// JavaScript
	void BuildJavaScript(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePath, const CString& strCompilerPath);

	// Python
	void BuildPython(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePath, const CString& strCompilerPath);

	// Java
	void BuildJava(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePath, const CString& strCompilerPath);
	CString GetBuildCommandlineJava(CEditorView* pView, const CString& strFileBuildConfig, const CString & strCompilerPath, BOOL bDebugMode);
	BOOL GenerateFileBuildConfigJava(const CString& strFilePath, BOOL bOpenFileBuildConfig = TRUE);
	void GetIncludeSourceFileJava(const CString& strFilePath, const std::string & strFolderPath, std::vector<std::string>& vecIncludeSrcFile);

	// Html
	void BuildHTML(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
	// Pascal
	void BuildPascal(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
	// C#
	void BuildCShape(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
	// Assembly
	void BuildAssembly(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
	// Batch
	void BuildBatch(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
	// C++
	void BuildPHP(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
	// VB
	void BuildVisualBasic(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
	// SQL
	void BuildSQL(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
	// Powershell
	void BuildPowerShell(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
	// Verilog
	void BuildVerilog(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
	// Perl
	void BuildPerl(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
	// Ruby
	void BuildRuby(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
	// Go
	void BuildGo(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
	// Tcl
	void BuildTCL(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
	// AutoIT
	void BuildAutoIT(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
	// Rust
	void BuildRust(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
	// R
	void BuildR(CMainFrame * pFrame, CEditorView* pView, const CString& strFilePat, const CString& strCompilerPath);
};

// below implementations will be used in EditorView Only!
#define START_VINATEXT_COMPILER(LANGGUAGE_ENUM) \
	CEditorDoc *pDoc = GetEditorDocument(); ASSERT(pDoc); if (!pDoc) return; \
	VinaTextCompiler::START_COMPILER(LANGGUAGE_ENUM, pDoc);

#define START_VINATEXT_GDB_DEBUGGER(LANGGUAGE_ENUM) \
	CEditorDoc *pDoc = GetEditorDocument(); ASSERT(pDoc); if (!pDoc) return; \
	VinaTextCompiler::START_GDB_DEBUGGER(LANGGUAGE_ENUM, pDoc);

#define START_VINATEXT_GDB_CMD(LANGGUAGE_ENUM) \
	CEditorDoc *pDoc = GetEditorDocument(); ASSERT(pDoc); if (!pDoc) return; \
	VinaTextCompiler::START_GDB_CMD(LANGGUAGE_ENUM, pDoc);

#define START_VINATEXT_START_EXE_LOADER(LANGGUAGE_ENUM) \
	CEditorDoc *pDoc = GetEditorDocument(); ASSERT(pDoc); if (!pDoc) return; \
	VinaTextCompiler::START_EXE_LOADER(LANGGUAGE_ENUM, pDoc);

#define START_VINATEXT_START_EXE_CMD(BUILD_INFO) \
	CEditorDoc *pDoc = GetEditorDocument(); ASSERT(pDoc); if (!pDoc) return; \
	VinaTextCompiler::START_EXE_CMD(BUILD_INFO);

#define START_VINATEXT_START_JAVA_LOADER(LANGGUAGE_ENUM, CMD) \
	CEditorDoc *pDoc = GetEditorDocument(); ASSERT(pDoc); if (!pDoc) return; \
	VinaTextCompiler::START_JAVA_LOADER(LANGGUAGE_ENUM, pDoc, CMD);
