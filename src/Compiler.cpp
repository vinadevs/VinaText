/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "FileUtil.h"
#include "Compiler.h"
#include "Debugger.h"
#include "MainFrm.h"
#include "EditorDoc.h"
#include "EditorView.h"
#include "EditorDatabase.h"
#include "AppUtil.h"
#include "MultiThreadWorker.h"
#include "AppSettings.h"

#pragma warning(disable:4996)

void VinaTextCompiler::START_COMPILER(VINATEXT_SUPPORTED_LANGUAGE docLanguage, CEditorDoc* pDoc)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;
	pFrame->ClearDataOnDockPane(DOCKABLE_PANE_TYPE::BUILD_PANE);

	ASSERT(pDoc);
	if (!pDoc) return;

	CEditorView* pView = pDoc->GetEditorView();
	ASSERT(pView);
	if (!pDoc) return;
	pDoc->SetPreviewMode(FALSE);

	CLanguageDatabase* pLangDatabase = pDoc->GetDocLanguageDatabase();
	ASSERT(pLangDatabase);
	if (!pLangDatabase) return;

	CString strFilePath = pDoc->GetPathName();
	if (FALSE == PathFileExists(strFilePath))
	{
		CString strMsg;
		strMsg.Format(_T("> [Path Error] \"%s\" does not exist...\n"), strFilePath);
		LOG_BUILD_MESSAGE_COLOR(strMsg, BasicColors::orange);
		return;
	}

	if (strFilePath.Find(_T(" ")) != -1) // check spaces
	{
		if (IDNO == AfxMessageBox(_T("[Warning] The current file has SPACE in file path, Compiler and Debugger sometime can not deal with it! Continue run?"), MB_YESNO | MB_ICONWARNING))
		{
			return;
		}	
	}

	CString strCompilerPath = pLangDatabase->GetCompilerPath();
	if (PathIsRelative(strCompilerPath)) // compiler will not accept relative path
	{
		strCompilerPath = PathUtils::GetVinaTextPath() + strCompilerPath;
	}
	if (!PathFileExists(strCompilerPath)
		&& docLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_HTML
		&& docLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_POWERSHELL
		&& docLanguage != VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_BATCH)
	{
		CString strMsg; strMsg.Format(_T("[Path Error] Compiler path \"%s\" does not exist, please setup path in [Code > Programing Language Setting(s)] and reopen current file to active it!\n"), strCompilerPath);
		AfxMessageBox(strMsg);
		return;
	}

	pView->m_BuildSessionInfo._strFilePath = strFilePath;

	// BUILD AS CURRENT DOCUMENT LANGUAGE
	if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP)
	{
		BuildCPP(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C)
	{
		BuildC(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
	{
		BuildJavaScript(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
	{
		BuildPython(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
	{
		BuildJava(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_HTML)
	{
		BuildHTML(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
	{
		BuildPascal(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CSHAPE)
	{
		BuildCShape(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_ASSEMBLY)
	{
		BuildAssembly(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_BATCH)
	{
		BuildBatch(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PHP)
	{
		BuildPHP(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VISUALBASIC)
	{
		BuildVisualBasic(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_SQL)
	{
		BuildSQL(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_POWERSHELL)
	{
		BuildPowerShell(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VERILOG)
	{
		BuildVerilog(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PERL)
	{
		BuildPerl(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUBY)
	{
		BuildRuby(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_GOLANG)
	{
		BuildGo(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_TCL)
	{
		BuildTCL(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_AUTOIT)
	{
		BuildAutoIT(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUST)
	{
		BuildRust(pFrame, pView, strFilePath, strCompilerPath);
	}
	else if (docLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_R)
	{
		BuildR(pFrame, pView, strFilePath, strCompilerPath);
	}
}

//  VinaText USE GDB TO DEBUG BELOW PROGRAMING LANGUAGES
//  GDB supports the following languages(in alphabetical order):
//	Ada
//	Assembly
//	C
//	C++
//	D
//	Fortran
//	Go
//	Objective - C
//	OpenCL
//	Modula - 2
//	Pascal
//	Rust

void VinaTextCompiler::START_GDB_CMD(VINATEXT_SUPPORTED_LANGUAGE docLanguage, CEditorDoc * pDoc)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;

	ASSERT(pDoc);
	if (!pDoc) return;
	pDoc->SetPreviewMode(FALSE);

	CEditorView* pView = pDoc->GetEditorView();
	ASSERT(pView);
	if (!pDoc) return;

	CLanguageDatabase* pLangDatabase = pDoc->GetDocLanguageDatabase();
	ASSERT(pLangDatabase);
	if (!pLangDatabase) return;

	if (VinaTextDebugger.HaveBreakPoints(docLanguage, pView->m_BuildSessionInfo._strFilePath)) // debug mode
	{
		CString strGdbDebugger = pLangDatabase->GetDebuggerPath();
		if (PathIsRelative(strGdbDebugger)) // compiler will not accept relative path
		{
			strGdbDebugger = PathUtils::GetVinaTextPath() + strGdbDebugger;
		}
		if (!PathFileExists(strGdbDebugger))
		{
			CString strMsg;
			strMsg.Format(_T("> [Debugger Error] \"%s\" does not exist...\n"), strGdbDebugger);
			LOG_BUILD_MESSAGE_COLOR(strMsg, BasicColors::orange);
			return;
		}
		SetCurrentDirectoryW(pView->m_BuildSessionInfo._strExeFolderPath);
		CString strFullCmd = _T("cmd.exe /C \"") + strGdbDebugger + CSTRING_SPACE + pView->m_BuildSessionInfo._strExeFilePath + _T("\" && pause");
		OSUtils::CreateWin32Process(strFullCmd);
	}
}

void VinaTextCompiler::START_GDB_DEBUGGER(VINATEXT_SUPPORTED_LANGUAGE docLanguage, CEditorDoc * pDoc)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;

	ASSERT(pDoc);
	if (!pDoc) return;
	pDoc->SetPreviewMode(FALSE);

	CEditorView* pView = pDoc->GetEditorView();
	ASSERT(pView);
	if (!pDoc) return;

	CLanguageDatabase* pLangDatabase = pDoc->GetDocLanguageDatabase();
	ASSERT(pLangDatabase);
	if (!pLangDatabase) return;

	if (VinaTextDebugger.HaveBreakPoints(docLanguage, pView->m_BuildSessionInfo._strFilePath)) // debug mode
	{
		CString strGdbDebugger = pLangDatabase->GetDebuggerPath();
		if (PathIsRelative(strGdbDebugger)) // compiler will not accept relative path
		{
			strGdbDebugger = PathUtils::GetVinaTextPath() + strGdbDebugger;
		}
		if (!PathFileExists(strGdbDebugger))
		{
			CString strMsg;
			strMsg.Format(_T("> [Debugger Error] \"%s\" does not exist...\n"), strGdbDebugger);
			LOG_BUILD_MESSAGE_COLOR(strMsg, BasicColors::orange);
			return;
		}

		CEditorThreadCompiler::TaskItem taskRun;
		taskRun.currentLanguage = docLanguage;
		taskRun.processType = CEditorThreadCompiler::PROCESS_TYPE::DEBUGGING_TYPE;
		taskRun.pWndGUI = pView;
		taskRun.pWndFrame = pFrame;
		taskRun.strCommandLine = _T("\"") + strGdbDebugger + _T("\" \"") + pView->m_BuildSessionInfo._strExeFilePath + _T("\"");
		taskRun.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
		taskRun.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
		ThreadWorkerMgr.CreateWorkerThread(taskRun);
	}
}

void VinaTextCompiler::START_CMD(const BuildSessionInfo & Info)
{
	SetCurrentDirectoryW(Info._strExeFolderPath);
	CString strFullCmd = _T("start \"\" \"CMD \" /c \"") + Info._strCommandLine + _T("\" ^& pause");
	OSUtils::RunSystemCMD(strFullCmd);
}

void VinaTextCompiler::START_EXE_CMD(const BuildSessionInfo & Info)
{
	SetCurrentDirectoryW(Info._strExeFolderPath);
	CString strFullCmd = _T("start \"\" \"CMD \" /c \"") + Info._strExeFilePath + _T("\" ^& pause");
	OSUtils::RunSystemCMD(strFullCmd);
}

void VinaTextCompiler::START_EXE_LOADER(VINATEXT_SUPPORTED_LANGUAGE docLanguage, CEditorDoc * pDoc)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;

	ASSERT(pDoc);
	if (!pDoc) return;
	pDoc->SetPreviewMode(FALSE);

	CEditorView* pView = pDoc->GetEditorView();
	ASSERT(pView);
	if (!pDoc) return;

	CEditorThreadCompiler::TaskItem taskRun;
	taskRun.currentLanguage = docLanguage;
	taskRun.processType = CEditorThreadCompiler::PROCESS_TYPE::RUNNING_TYPE;
	taskRun.pWndGUI = pView;
	taskRun.pWndFrame = pFrame;
	taskRun.strCommandLine = _T("\"") + pView->m_BuildSessionInfo._strExeFilePath + _T("\"");
	taskRun.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
	taskRun.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
	ThreadWorkerMgr.CreateWorkerThread(taskRun);
}

void VinaTextCompiler::START_JAVA_LOADER(VINATEXT_SUPPORTED_LANGUAGE docLanguage, CEditorDoc * pDoc, const CString& strCommandLineJVM)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;

	ASSERT(pDoc);
	if (!pDoc) return;
	pDoc->SetPreviewMode(FALSE);

	CEditorView* pView = pDoc->GetEditorView();
	ASSERT(pView);
	if (!pDoc) return;

	CEditorThreadCompiler::TaskItem taskRun;
	taskRun.currentLanguage = docLanguage;
	taskRun.processType = CEditorThreadCompiler::PROCESS_TYPE::RUNNING_TYPE;
	taskRun.pWndGUI = pView;
	taskRun.pWndFrame = pFrame;
	taskRun.strCommandLine = strCommandLineJVM;
	taskRun.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
	taskRun.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
	ThreadWorkerMgr.CreateWorkerThread(taskRun);
}

//////////////////////////////////////////////////////////////////////////
// BuildCPP

void VinaTextCompiler::BuildCPP(CMainFrame* pFrame, CEditorView* pView, const CString& strFilePath, const CString& strCompilerPath)
{
	CString strBuildConfigPath = PathUtils::GetFilePathWithoutExtention(strFilePath) + _T("_cpp_build_config.json");

	CEditorThreadCompiler::TaskItem taskBuild;
	taskBuild.pWndGUI = pView;
	taskBuild.pWndFrame = pFrame;
	taskBuild.strRunFromDirectory = PathUtils::GetContainerPath(strCompilerPath);
	taskBuild.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;

	if (!PathFileExists(strBuildConfigPath) && AppSettingMgr.m_bAutoGenBuildConfigFile)
	{
		if (!GenerateFileBuildConfigCPP(strFilePath, FALSE))
		{
			CString strMsg;
			strMsg.Format(_T("> [Build C++ Error] Can not generate file build configuration %s...\n"), strFilePath);
			LOG_OUTPUT_MESSAGE_COLOR(strMsg, BasicColors::orange);
		}
	}

	if (PathFileExists(strBuildConfigPath))
	{
		if (VinaTextDebugger.HaveBreakPoints(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP, strFilePath)) // debug mode
		{
			taskBuild.processType = CEditorThreadCompiler::PROCESS_TYPE::DEBUGGING_TYPE;
			taskBuild.strCommandLine = GetBuildCommandlineCPP(pView, strBuildConfigPath, strCompilerPath, TRUE);
			VinaTextDebugger.SetCurrentDocLanguage(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP);
			VinaTextDebugger.RegisterInitialBreakPoints();
			pView->LOG_BUILD_INFO_MESSAGE(taskBuild.strCommandLine, _T("C++"), TRUE, strBuildConfigPath);
		}
		else // normal mode
		{
			taskBuild.strCommandLine = GetBuildCommandlineCPP(pView, strBuildConfigPath, strCompilerPath, FALSE);
			pView->LOG_BUILD_INFO_MESSAGE(taskBuild.strCommandLine, _T("C++"), FALSE, strBuildConfigPath);
		}
		pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
		ThreadWorkerMgr.CreateWorkerThread(taskBuild);
	}
}

CString VinaTextCompiler::GetBuildCommandlineCPP(CEditorView* pView, const CString & strFileBuildConfig, const CString& strCompilerPath, BOOL bDebugMode)
{
	JSonReader jsonReader(strFileBuildConfig, "C++ Build Configuration");
	if (!jsonReader.LoadFile()) return CString();
	CString libraryname = jsonReader.GetData("libraryoption");
	CString librarypath = jsonReader.GetData("librarypath");
	CString subsystem = jsonReader.GetData("subsystem");
	CString warningflag = jsonReader.GetData("warningflag");
	CString cpp11flag = jsonReader.GetData("cpp11flag");
	CString debug = jsonReader.GetData("debugoption");
	CString includepath = jsonReader.GetData("includepath");
	CString outputpath = jsonReader.GetData("outputpath");
	CString sourcepath = jsonReader.GetData("sourcepath");

	if (libraryname.IsEmpty() || librarypath.IsEmpty() || debug.IsEmpty() || warningflag.IsEmpty() ||
		cpp11flag.IsEmpty() || includepath.IsEmpty() || outputpath.IsEmpty() || sourcepath.IsEmpty())
	{
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Compiler Error] C++ Build configuration file invalid..."), BasicColors::orange);
		return CString();
	}

	auto vecSrcFile = AppUtils::SplitterCString(sourcepath, ";");
	sourcepath.Empty();
	for (auto const& file : vecSrcFile)
	{
		if (PathFileExists(file))
		{
			sourcepath += _T("\"") + file + _T("\" ");
		}
	}

	auto vecLibraryFile = AppUtils::SplitterCString(librarypath, ";");
	librarypath.Empty();
	for (auto const& file : vecLibraryFile)
	{
		if (PathFileExists(file))
		{
			librarypath += _T("\"") + file + _T("\" ");
		}
	}

	auto vecIncludeFile = AppUtils::SplitterCString(includepath, ";");
	includepath.Empty();
	for (auto const& file : vecIncludeFile)
	{
		if (PathFileExists(file))
		{
			includepath += _T("\"") + file + _T("\" ");
		}
	}

	CString fullBuildCmd;
	if (bDebugMode)
	{
		fullBuildCmd = _T("\"") + strCompilerPath + _T("\" ") + debug + CSTRING_SPACE + libraryname + CSTRING_SPACE + warningflag 
			+ CSTRING_SPACE + cpp11flag + CSTRING_SPACE + subsystem + CSTRING_SPACE +
			sourcepath + _T(" -o ") + _T("\"") + outputpath + _T("\" -I ") + includepath + _T(" -L ") + librarypath;
	}
	else
	{
		fullBuildCmd = _T("\"") + strCompilerPath + _T("\" ") + libraryname + CSTRING_SPACE + warningflag + CSTRING_SPACE 
			+ cpp11flag + CSTRING_SPACE + subsystem + CSTRING_SPACE +
			sourcepath + _T(" -o ") + _T("\"") + outputpath + _T("\" -I ") + includepath + _T(" -L ") + librarypath;
	}

	// save exe paths...
	pView->m_BuildSessionInfo._strExeFilePath = outputpath;
	pView->m_BuildSessionInfo._strExeFileName = PathUtils::GetFilenameFromPath(outputpath);
	if (pView->m_BuildSessionInfo._strExeFilePath.Find(_T(".exe")) != -1)
	{
		OSUtils::KillProcessByName(pView->m_BuildSessionInfo._strExeFileName);
		::DeleteFile(pView->m_BuildSessionInfo._strExeFilePath);
	}
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(pView->m_BuildSessionInfo._strExeFilePath);

	return fullBuildCmd;
}

BOOL VinaTextCompiler::GenerateFileBuildConfigCPP(const CString& strFilePath, BOOL bOpenFileBuildConfig)
{
	if (!PathFileExists(strFilePath)) return FALSE;

	CString strBuildConfigPath = PathUtils::GetFilePathWithoutExtention(strFilePath) + _T("_cpp_build_config.json");

	std::string strFolderPath = AppUtils::CStringToStd(PathUtils::GetContainerPath(strFilePath));
	AppUtils::ReplaceAllInStdString(strFolderPath, "\\\\", "\\");

	std::string strFileName = AppUtils::CStringToStd(PathUtils::GetFilenameFromPath(strFilePath));
	CString strFilePathTemp = strFilePath;
	strFilePathTemp.Replace(_T(".cpp"), _T(".exe"));
	std::string strFilePathExe = AppUtils::CStringToStd(strFilePathTemp);

	std::vector<std::string> vecSrcIncludeFile;
	GetIncludeSourceFileCPP(strFilePath, strFolderPath, vecSrcIncludeFile);

	std::string libraryoption = "-static-libgcc -static-libstdc++";
	std::string librarypath = strFolderPath + ";";

	std::string subsystem;
	if (AppSettingMgr.m_bEnableWindowSubsytemFlagForCAndCPP)
	{
		subsystem = "-Wl,--subsystem,windows";
	}

	std::string warningflag;
	if (AppSettingMgr.m_bEnableWarningFlagForCAndCPP)
	{
		warningflag = "-Wall -Wextra";
	}

	std::string cpp11flag;
	if (AppSettingMgr.m_bEnableWarningFlagForCAndCPP)
	{
		cpp11flag = "-Wpedantic -std=c++11";
	}

	std::string debugoption = "-g";
	std::string includepath = strFolderPath + ";";

	std::string sourcepath = strFilePath + ";";
	for (auto const& file : vecSrcIncludeFile)
	{
		sourcepath += file + ";";
	}

	std::string outputpath = strFilePathExe;

	// write json file
	JSonWriter jsonWriter(strBuildConfigPath, "C++ Build Configuration");
	jsonWriter.AddValue("subsystem", subsystem);
	jsonWriter.AddValue("warningflag", warningflag);
	jsonWriter.AddValue("cpp11flag", cpp11flag);
	jsonWriter.AddValue("debugoption", debugoption);
	jsonWriter.AddValue("libraryoption", libraryoption);
	jsonWriter.AddValue("librarypath", librarypath);
	jsonWriter.AddValue("includepath", includepath);
	jsonWriter.AddValue("sourcepath", sourcepath);
	jsonWriter.AddValue("outputpath", outputpath);
	jsonWriter.SaveFile();

	if (bOpenFileBuildConfig)
	{
		AppUtils::CreateDocumentFromFile(strBuildConfigPath);
	}

	return TRUE;
}

void VinaTextCompiler::GetIncludeSourceFileCPP(const CString & strFilePath, const std::string & strFolderPath, std::vector<std::string>& vecIncludeSrcFile)
{
	CStringArray arrLine;
	if (PathUtils::OpenFile(strFilePath, arrLine))
	{
		for (int i = 0; i < arrLine.GetSize(); ++i)
		{
			CString strLine= arrLine[i].Trim();
			if (strLine.IsEmpty()) continue;
			int pos1 = strLine.Find(_T("#include"));
			int pos2 = strLine.Find(_T(".h\""));
			if (pos1 != -1 && pos2 != -1)
			{
				std::string strFileName = AppUtils::CStringToStd(strLine.Mid(pos1 + 8).Trim());
				AppUtils::ReplaceAllInStdString(strFileName, "\"", "");
				AppUtils::ReplaceAllInStdString(strFileName, ".h", ".cpp");
				std::string strFilePath = strFolderPath + ("\\") + strFileName;
				vecIncludeSrcFile.push_back(strFilePath);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// BuildC

void VinaTextCompiler::BuildC(CMainFrame* pFrame, CEditorView* pView, const CString& strFilePath, const CString& strCompilerPath)
{
	CString strBuildConfigPath = PathUtils::GetFilePathWithoutExtention(strFilePath) + _T("_c_build_config.json");

	CEditorThreadCompiler::TaskItem taskBuild;
	taskBuild.pWndGUI = pView;
	taskBuild.pWndFrame = pFrame;
	taskBuild.strRunFromDirectory = PathUtils::GetContainerPath(strCompilerPath);
	taskBuild.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;

	if (!PathFileExists(strBuildConfigPath) && AppSettingMgr.m_bAutoGenBuildConfigFile)
	{
		if (!GenerateFileBuildConfigC(strFilePath, FALSE))
		{
			CString strMsg;
			strMsg.Format(_T("> [Build C Error] Can not generate file build configuration %s...\n"), strFilePath);
			LOG_OUTPUT_MESSAGE_COLOR(strMsg, BasicColors::orange);
		}
	}

	if (PathFileExists(strBuildConfigPath))
	{
		if (VinaTextDebugger.HaveBreakPoints(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C, strFilePath)) // debug mode
		{
			taskBuild.processType = CEditorThreadCompiler::PROCESS_TYPE::DEBUGGING_TYPE;
			taskBuild.strCommandLine = GetBuildCommandlineC(pView, strBuildConfigPath, strCompilerPath, TRUE);
			VinaTextDebugger.SetCurrentDocLanguage(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C);
			VinaTextDebugger.RegisterInitialBreakPoints();
			pView->LOG_BUILD_INFO_MESSAGE(taskBuild.strCommandLine, _T("C"), TRUE, strBuildConfigPath);
		}
		else // normal mode
		{
			taskBuild.strCommandLine = GetBuildCommandlineC(pView, strBuildConfigPath, strCompilerPath, FALSE);
			pView->LOG_BUILD_INFO_MESSAGE(taskBuild.strCommandLine, _T("C"), FALSE, strBuildConfigPath);
		}
		pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
		ThreadWorkerMgr.CreateWorkerThread(taskBuild);
	}
}

CString VinaTextCompiler::GetBuildCommandlineC(CEditorView* pView, const CString & strFileBuildConfig, const CString& strCompilerPath, BOOL bDebugMode)
{
	JSonReader jsonReader(strFileBuildConfig, "C Build Configuration");
	if (!jsonReader.LoadFile()) return CString();
	CString libraryname = jsonReader.GetData("libraryoption");
	CString librarypath = jsonReader.GetData("librarypath");
	CString subsystem = jsonReader.GetData("subsystem");
	CString warning = jsonReader.GetData("warningflag");
	CString debug = jsonReader.GetData("debugoption");
	CString includepath = jsonReader.GetData("includepath");
	CString outputpath = jsonReader.GetData("outputpath");
	CString sourcepath = jsonReader.GetData("sourcepath");

	if (libraryname.IsEmpty() || librarypath.IsEmpty() || debug.IsEmpty() ||
		warning.IsEmpty() || includepath.IsEmpty() || outputpath.IsEmpty() || sourcepath.IsEmpty())
	{
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Compiler Error] C configuration file invalid..."), BasicColors::orange);
		return CString();
	}

	auto vecSrcFile = AppUtils::SplitterCString(sourcepath, ";");
	sourcepath.Empty();
	for (auto const& file : vecSrcFile)
	{
		if (PathFileExists(file))
		{
			sourcepath += _T("\"") + file + _T("\" ");
		}
	}

	auto vecLibraryFile = AppUtils::SplitterCString(librarypath, ";");
	librarypath.Empty();
	for (auto const& file : vecLibraryFile)
	{
		if (PathFileExists(file))
		{
			librarypath += _T("\"") + file + _T("\" ");
		}
	}

	auto vecIncludeFile = AppUtils::SplitterCString(includepath, ";");
	includepath.Empty();
	for (auto const& file : vecIncludeFile)
	{
		if (PathFileExists(file))
		{
			includepath += _T("\"") + file + _T("\" ");
		}
	}

	CString fullBuildCmd;
	if (bDebugMode)
	{
		fullBuildCmd = _T("\"") + strCompilerPath + _T("\" ") + debug + CSTRING_SPACE + libraryname + CSTRING_SPACE + warning + CSTRING_SPACE + subsystem + CSTRING_SPACE +
			sourcepath + _T(" -o ") + _T("\"") + outputpath + _T("\" -I ") + includepath + _T(" -L ") + librarypath;
	}
	else
	{
		fullBuildCmd = _T("\"") + strCompilerPath + _T("\" ") + libraryname + CSTRING_SPACE + warning + CSTRING_SPACE + subsystem + CSTRING_SPACE +
			sourcepath + _T(" -o ") + _T("\"") + outputpath + _T("\" -I ") + includepath + _T(" -L ") + librarypath;
	}

	// save exe paths...
	pView->m_BuildSessionInfo._strExeFilePath = outputpath;
	pView->m_BuildSessionInfo._strExeFileName = PathUtils::GetFilenameFromPath(outputpath);
	if (pView->m_BuildSessionInfo._strExeFilePath.Find(_T(".exe")) != -1)
	{
		OSUtils::KillProcessByName(pView->m_BuildSessionInfo._strExeFileName);
		::DeleteFile(pView->m_BuildSessionInfo._strExeFilePath);
	}
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(pView->m_BuildSessionInfo._strExeFilePath);

	return fullBuildCmd;
}

BOOL VinaTextCompiler::GenerateFileBuildConfigC(const CString& strFilePath, BOOL bOpenFileBuildConfig)
{
	if (!PathFileExists(strFilePath)) return FALSE;

	CString strBuildConfigPath = PathUtils::GetFilePathWithoutExtention(strFilePath) + _T("_c_build_config.json");

	std::string strFolderPath = AppUtils::CStringToStd(PathUtils::GetContainerPath(strFilePath));
	AppUtils::ReplaceAllInStdString(strFolderPath, "\\\\", "\\");

	std::string strFileName = AppUtils::CStringToStd(PathUtils::GetFilenameFromPath(strFilePath));
	CString strFilePathTemp = strFilePath;
	strFilePathTemp.Replace(_T(".c"), _T(".exe"));
	std::string strFilePathExe = AppUtils::CStringToStd(strFilePathTemp);

	std::vector<std::string> vecSrcIncludeFile;
	GetIncludeSourceFileC(strFilePath, strFolderPath, vecSrcIncludeFile);

	std::string libraryoption = "-static-libgcc";
	std::string librarypath = strFolderPath + ";";

	std::string subsystem;
	if (AppSettingMgr.m_bEnableWindowSubsytemFlagForCAndCPP)
	{
		subsystem = "-Wl,--subsystem,windows";
	}

	std::string warningflag;
	if (AppSettingMgr.m_bEnableWarningFlagForCAndCPP)
	{
		warningflag = "-Wall -Wextra";
	}

	std::string debugoption = "-g";
	std::string includepath = strFolderPath + ";";

	std::string sourcepath = strFilePath + ";";
	for (auto const& file : vecSrcIncludeFile)
	{
		sourcepath += file + ";";
	}
	std::string outputpath = strFilePathExe;

	// write json file
	JSonWriter jsonWriter(strBuildConfigPath, "C Build Configuration");
	jsonWriter.AddValue("subsystem", subsystem);
	jsonWriter.AddValue("warningflag", warningflag);
	jsonWriter.AddValue("debugoption", debugoption);
	jsonWriter.AddValue("libraryoption", libraryoption);
	jsonWriter.AddValue("librarypath", librarypath);
	jsonWriter.AddValue("includepath", includepath);
	jsonWriter.AddValue("sourcepath", sourcepath);
	jsonWriter.AddValue("outputpath", outputpath);
	jsonWriter.SaveFile();

	if (bOpenFileBuildConfig)
	{
		AppUtils::CreateDocumentFromFile(strBuildConfigPath);
	}

	return TRUE;
}

void VinaTextCompiler::GetIncludeSourceFileC(const CString & strFilePath, const std::string & strFolderPath, std::vector<std::string>& vecIncludeSrcFile)
{
	CStringArray arrLine;
	if (PathUtils::OpenFile(strFilePath, arrLine))
	{
		for (int i = 0; i < arrLine.GetSize(); ++i)
		{
			CString strLine = arrLine[i].Trim();
			if (strLine.IsEmpty()) continue;
			int pos1 = strLine.Find(_T("#include"));
			int pos2 = strLine.Find(_T(".h\""));
			if (pos1 != -1 && pos2 != -1)
			{
				std::string strFileName = AppUtils::CStringToStd(strLine.Mid(pos1 + 8).Trim());
				AppUtils::ReplaceAllInStdString(strFileName, "\"", "");
				AppUtils::ReplaceAllInStdString(strFileName, ".h", ".c");
				std::string strFilePath = strFolderPath + ("\\") + strFileName;
				vecIncludeSrcFile.push_back(strFilePath);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// BuildJavaScript

void VinaTextCompiler::BuildJavaScript(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);

	if (PathFileExists(pView->m_BuildSessionInfo._strExeFilePath) && PathFileExists(pView->m_BuildSessionInfo._strExeFolderPath))
	{
		if (AppSettingMgr.m_bOpenWindowCmdWhenRunProgram)
		{
			if (VinaTextDebugger.HaveBreakPoints(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT, strFilePath)) // debug mode
			{
				pView->m_BuildSessionInfo._strCommandLine = _T("\"") + strCompilerPath + ENABLE_NODEJS_DEBUGGER + strFilePath + _T("\"");
				START_CMD(pView->m_BuildSessionInfo);
				pView->LOG_BUILD_INFO_MESSAGE(pView->m_BuildSessionInfo._strCommandLine, _T("Javascript"), TRUE);
				LOG_BUILD_MESSAGE_COLOR(_T("[ RUN .................................................................................."));
			}
			else // normal mode
			{
				pView->m_BuildSessionInfo._strCommandLine = _T("\"") + strCompilerPath + _T("\" \"") + strFilePath + _T("\"");
				START_CMD(pView->m_BuildSessionInfo);
				pView->LOG_BUILD_INFO_MESSAGE(pView->m_BuildSessionInfo._strCommandLine, _T("Javascript"));
				LOG_BUILD_MESSAGE_COLOR(_T("[ RUN .................................................................................."));
			}
		}
		else
		{
			CEditorThreadCompiler::TaskItem taskBuild;
			taskBuild.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT;
			taskBuild.pWndGUI = pView;
			taskBuild.pWndFrame = pFrame;
			taskBuild.strRunFromDirectory = PathUtils::GetContainerPath(strCompilerPath);
			taskBuild.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;

			if (VinaTextDebugger.HaveBreakPoints(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT, strFilePath)) // debug mode
			{
				taskBuild.processType = CEditorThreadCompiler::PROCESS_TYPE::DEBUGGING_TYPE;
				taskBuild.strCommandLine = _T("\"") + strCompilerPath + ENABLE_NODEJS_DEBUGGER + strFilePath + _T("\"");
				VinaTextDebugger.SetCurrentDocLanguage(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT);
				VinaTextDebugger.RegisterInitialBreakPoints();
				pView->LOG_BUILD_INFO_MESSAGE(taskBuild.strCommandLine, _T("Javascript"), TRUE);
			}
			else // normal mode
			{
				taskBuild.strCommandLine = _T("\"") + strCompilerPath + _T("\" \"") + strFilePath + _T("\"");
				pView->LOG_BUILD_INFO_MESSAGE(taskBuild.strCommandLine, _T("Javascript"));
			}
			LOG_BUILD_MESSAGE_COLOR(_T("[ RUN .................................................................................."));
			pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
			ThreadWorkerMgr.CreateWorkerThread(taskBuild);
		}
	}
	else
	{
		CString strMsg;
		strMsg.Format(_T("[Path Error] \"%s\" does not exist!\n"), pView->m_BuildSessionInfo._strExeFilePath);
		LOG_BUILD_MESSAGE_COLOR(strMsg, BasicColors::orange);
		return;
	}
}

//////////////////////////////////////////////////////////////////////////
// BuildPython

void VinaTextCompiler::BuildPython(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);

	if (PathFileExists(pView->m_BuildSessionInfo._strExeFilePath) && PathFileExists(pView->m_BuildSessionInfo._strExeFolderPath))
	{
		if (AppSettingMgr.m_bOpenWindowCmdWhenRunProgram)
		{
			if (VinaTextDebugger.HaveBreakPoints(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON, strFilePath)) // debug mode
			{
				pView->m_BuildSessionInfo._strCommandLine = _T("\"") + strCompilerPath + ENABLE_PYTHON_DEBUGGER + strFilePath + _T("\"");
				START_CMD(pView->m_BuildSessionInfo);
				pView->LOG_BUILD_INFO_MESSAGE(pView->m_BuildSessionInfo._strCommandLine, _T("Python"), TRUE);
				LOG_BUILD_MESSAGE_COLOR(_T("[ RUN .................................................................................."));
			}
			else // normal mode
			{
				pView->m_BuildSessionInfo._strCommandLine = _T("\"") + strCompilerPath + _T("\" \"") + strFilePath + _T("\"");
				START_CMD(pView->m_BuildSessionInfo);
				pView->LOG_BUILD_INFO_MESSAGE(pView->m_BuildSessionInfo._strCommandLine, _T("Python"));
				LOG_BUILD_MESSAGE_COLOR(_T("[ RUN .................................................................................."));
			}
		}
		else
		{
			CEditorThreadCompiler::TaskItem taskBuild;
			taskBuild.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON;
			taskBuild.pWndGUI = pView;
			taskBuild.pWndFrame = pFrame;
			taskBuild.strRunFromDirectory = PathUtils::GetContainerPath(strCompilerPath);
			taskBuild.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;

			if (VinaTextDebugger.HaveBreakPoints(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON, strFilePath)) // debug mode
			{
				taskBuild.processType = CEditorThreadCompiler::PROCESS_TYPE::DEBUGGING_TYPE;
				taskBuild.strCommandLine = _T("\"") + strCompilerPath + ENABLE_PYTHON_DEBUGGER + strFilePath + _T("\"");
				VinaTextDebugger.SetCurrentDocLanguage(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON);
				VinaTextDebugger.RegisterInitialBreakPoints();
				pView->LOG_BUILD_INFO_MESSAGE(taskBuild.strCommandLine, _T("Python"), TRUE);
			}
			else // normal mode
			{
				taskBuild.strCommandLine = _T("\"") + strCompilerPath + _T("\" \"") + strFilePath + _T("\"");
				pView->LOG_BUILD_INFO_MESSAGE(taskBuild.strCommandLine, _T("Python"));
			}
			LOG_BUILD_MESSAGE_COLOR(_T("[ RUN .................................................................................."));
			pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
			ThreadWorkerMgr.CreateWorkerThread(taskBuild);
		}
	}
	else
	{
		CString strMsg;
		strMsg.Format(_T("[Path Error] \"%s\" does not exist!\n"), pView->m_BuildSessionInfo._strExeFilePath);
		LOG_BUILD_MESSAGE_COLOR(strMsg, BasicColors::orange);
		return;
	}
}

//////////////////////////////////////////////////////////////////////////
// BuildJava

void VinaTextCompiler::BuildJava(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	pView->m_BuildSessionInfo._strExeFilePath.Replace(_T(".java"), _T(".class"));
	::DeleteFile(pView->m_BuildSessionInfo._strExeFilePath);
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);
	pView->m_BuildSessionInfo._strExeFileName = PathUtils::GetFilenameFromPath(strFilePath);
	pView->m_BuildSessionInfo._strJavaVMPath = PathUtils::GetContainerPath(strCompilerPath) + _T("\\java.exe");

	CEditorThreadCompiler::TaskItem taskBuild;
	taskBuild.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA;
	taskBuild.pWndGUI = pView;
	taskBuild.pWndFrame = pFrame;
	taskBuild.strCommandLine = _T("\"") + strCompilerPath + _T("\" \"") + strFilePath + _T("\"");
	taskBuild.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
	taskBuild.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
	pView->LOG_BUILD_INFO_MESSAGE(taskBuild.strCommandLine, _T("Java"));
	pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
	ThreadWorkerMgr.CreateWorkerThread(taskBuild);
}

CString VinaTextCompiler::GetBuildCommandlineJava(CEditorView * pView, const CString & strFileBuildConfig, const CString & strCompilerPath, BOOL bDebugMode)
{
	return CString();
}

BOOL VinaTextCompiler::GenerateFileBuildConfigJava(const CString & strFilePath, BOOL bOpenFileBuildConfig)
{
	return 0;
}

void VinaTextCompiler::GetIncludeSourceFileJava(const CString & strFilePath, const std::string & strFolderPath, std::vector<std::string>& vecIncludeSrcFile)
{
}

//////////////////////////////////////////////////////////////////////////
// BuildHTML

void VinaTextCompiler::BuildHTML(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	if (strCompilerPath.Find(_T("CHROME_BROWSER")) != -1)
	{
		OSUtils::OpenFileInWebBrowser(_T("chrome.exe"), strFilePath);
		pView->LOG_BUILD_INFO_MESSAGE(_T("chrome.exe \"") + strFilePath + _T("\""), _T("HTML"));
	}
	else if (strCompilerPath.Find(_T("FIREFOX_BROWSER")) != -1)
	{
		OSUtils::OpenFileInWebBrowser(_T("firefox.exe"), strFilePath);
		pView->LOG_BUILD_INFO_MESSAGE(_T("firefox.exe \"") + strFilePath + _T("\""), _T("HTML"));
	}
	else if (strCompilerPath.Find(_T("EDGE_BROWSER")) != -1)
	{

		OSUtils::OpenFileInWebBrowser(_T("shell:Appsfolder\\Microsoft.MicrosoftEdge_8wekyb3d8bbwe!MicrosoftEdge"), strFilePath);
		pView->LOG_BUILD_INFO_MESSAGE(_T("MicrosoftEdge.exe \"") + strFilePath + _T("\""), _T("HTML"));
	}
	else
	{
		OSUtils::CreateProcessAsynchronous(TEXT("open"), strFilePath, _T(""), _T(""));
		pView->LOG_BUILD_INFO_MESSAGE(_T("cmd.exe \"") + strFilePath + _T("\""), _T("HTML"));
	}
}

//////////////////////////////////////////////////////////////////////////
// BuildHTML

void VinaTextCompiler::BuildPascal(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	if (strFilePath.Find(_T(".pas")) != -1)
	{
		pView->m_BuildSessionInfo._strExeFilePath.Replace(_T(".pas"), _T(".exe"));
	}
	else if (strFilePath.Find(_T(".pp")) != -1)
	{
		pView->m_BuildSessionInfo._strExeFilePath.Replace(_T(".pp"), _T(".exe"));
	}
	else
	{
		AfxMessageBox(_T("[Format Error] Pascal file extension must be .pp or .pas!"));
		return;
	}
	pView->m_BuildSessionInfo._strExeFileName = PathUtils::GetFilenameFromPath(pView->m_BuildSessionInfo._strExeFilePath);
	if (pView->m_BuildSessionInfo._strExeFilePath.Find(_T(".exe")) != -1)
	{
		OSUtils::KillProcessByName(pView->m_BuildSessionInfo._strExeFileName);
		::DeleteFile(pView->m_BuildSessionInfo._strExeFilePath);
	}
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);
	// fpc.exe main.pas
	CEditorThreadCompiler::TaskItem taskBuild;
	taskBuild.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL;
	taskBuild.pWndGUI = pView;
	taskBuild.pWndFrame = pFrame;
	taskBuild.strCommandLine = _T("\"") + strCompilerPath + _T("\" \"") + strFilePath + _T("\"");
	taskBuild.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
	taskBuild.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
	pView->LOG_BUILD_INFO_MESSAGE(taskBuild.strCommandLine, _T("Pascal"));
	pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
	ThreadWorkerMgr.CreateWorkerThread(taskBuild);
}

//////////////////////////////////////////////////////////////////////////
// Build C#

void VinaTextCompiler::BuildCShape(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	pView->m_BuildSessionInfo._strExeFilePath.Replace(_T(".cs"), _T(".exe"));
	pView->m_BuildSessionInfo._strExeFileName = PathUtils::GetFilenameFromPath(pView->m_BuildSessionInfo._strExeFilePath);
	if (pView->m_BuildSessionInfo._strExeFilePath.Find(_T(".exe")) != -1)
	{
		OSUtils::KillProcessByName(pView->m_BuildSessionInfo._strExeFileName);
		::DeleteFile(pView->m_BuildSessionInfo._strExeFilePath);
	}
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);
	pView->m_BuildSessionInfo._strExeFileName = PathUtils::GetFilenameFromPath(strFilePath);
	//c:\windows\Microsoft.NET\Framework\v3.5\bin\csc.exe /t:exe /out:MyApplication.exe MyApplication.cs
	CEditorThreadCompiler::TaskItem taskBuild;
	taskBuild.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CSHAPE;
	taskBuild.pWndGUI = pView;
	taskBuild.pWndFrame = pFrame;
	taskBuild.strCommandLine = _T("\"") + strCompilerPath + _T("\"  /t:exe /out:\"") + pView->m_BuildSessionInfo._strExeFilePath + _T("\" \"") + strFilePath + _T("\"");
	taskBuild.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
	taskBuild.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
	pView->LOG_BUILD_INFO_MESSAGE(taskBuild.strCommandLine, _T("C#"));
	pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
	ThreadWorkerMgr.CreateWorkerThread(taskBuild);
}

//////////////////////////////////////////////////////////////////////////
// BuildAssembly

void VinaTextCompiler::BuildAssembly(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	pView->m_BuildSessionInfo._strExeFilePath.Replace(_T(".ASM"), _T(".exe"));
	pView->m_BuildSessionInfo._strExeFileName = PathUtils::GetFilenameFromPath(pView->m_BuildSessionInfo._strExeFilePath);
	if (pView->m_BuildSessionInfo._strExeFilePath.Find(_T(".exe")) != -1)
	{
		OSUtils::KillProcessByName(pView->m_BuildSessionInfo._strExeFileName);
		::DeleteFile(pView->m_BuildSessionInfo._strExeFilePath);
	}
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);

	CEditorThreadCompiler::TaskItem taskBuild;
	taskBuild.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_ASSEMBLY;
	taskBuild.pWndGUI = pView;
	taskBuild.pWndFrame = pFrame;
	taskBuild.strCommandLine = _T("\"") + strCompilerPath + _T("\" \"") + strFilePath + _T("\"");
	taskBuild.strRunFromDirectory = PathUtils::GetContainerPath(strCompilerPath);
	taskBuild.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
	pView->LOG_BUILD_INFO_MESSAGE(taskBuild.strCommandLine, _T("Assembly"));
	pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
	ThreadWorkerMgr.CreateWorkerThread(taskBuild);
}

//////////////////////////////////////////////////////////////////////////
// BuildPHP

void VinaTextCompiler::BuildPHP(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);

	CEditorThreadCompiler::TaskItem task;
	task.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PHP;
	task.pWndGUI = pView;
	task.pWndFrame = pFrame;
	task.strCommandLine = _T("\"") + strCompilerPath + _T("\" \"") + pView->m_BuildSessionInfo._strExeFilePath + _T("\"");
	task.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
	task.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
	pView->LOG_BUILD_INFO_MESSAGE(task.strCommandLine, _T("PHP"));
	pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
	ThreadWorkerMgr.CreateWorkerThread(task);
}

//////////////////////////////////////////////////////////////////////////
// BuildVisualBasic

void VinaTextCompiler::BuildVisualBasic(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	if (strFilePath.Find(_T(".vbs")) != -1)
	{
		pView->m_BuildSessionInfo._strExeFilePath.Replace(_T(".vbs"), _T(".exe"));
	}
	else if (strFilePath.Find(_T(".vb")) != -1)
	{
		pView->m_BuildSessionInfo._strExeFilePath.Replace(_T(".vb"), _T(".exe"));
	}
	else
	{
		AfxMessageBox(_T("[Format Error] VisualBasic file extension must be .vb or .vbs!"));
		return;
	}
	pView->m_BuildSessionInfo._strExeFileName = PathUtils::GetFilenameFromPath(pView->m_BuildSessionInfo._strExeFilePath);
	if (pView->m_BuildSessionInfo._strExeFilePath.Find(_T(".exe")) != -1)
	{
		OSUtils::KillProcessByName(pView->m_BuildSessionInfo._strExeFileName);
		::DeleteFile(pView->m_BuildSessionInfo._strExeFilePath);
	}
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);
	//	vbc -out:My.exe File.vb
	CEditorThreadCompiler::TaskItem taskBuild;
	taskBuild.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VISUALBASIC;
	taskBuild.pWndGUI = pView;
	taskBuild.pWndFrame = pFrame;
	taskBuild.strCommandLine = _T("\"") + strCompilerPath + _T("\" -out:\"") + pView->m_BuildSessionInfo._strExeFilePath + _T("\" \"") + strFilePath + _T("\"");
	taskBuild.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
	taskBuild.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
	pView->LOG_BUILD_INFO_MESSAGE(taskBuild.strCommandLine, _T("Visual Basic"));
	pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
	ThreadWorkerMgr.CreateWorkerThread(taskBuild);
}

//////////////////////////////////////////////////////////////////////////
// BuildPerl

void VinaTextCompiler::BuildPerl(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);

	CEditorThreadCompiler::TaskItem task;
	task.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PERL;
	task.pWndGUI = pView;
	task.pWndFrame = pFrame;
	task.strCommandLine = _T("\"") + strCompilerPath + _T("\" \"") + pView->m_BuildSessionInfo._strExeFilePath + _T("\"");
	
	task.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
	task.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
	pView->LOG_BUILD_INFO_MESSAGE(task.strCommandLine, _T("Perl"));
	pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
	ThreadWorkerMgr.CreateWorkerThread(task);
}

//////////////////////////////////////////////////////////////////////////
// BuildGo

void VinaTextCompiler::BuildGo(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);

	if (PathFileExists(pView->m_BuildSessionInfo._strExeFilePath) && PathFileExists(pView->m_BuildSessionInfo._strExeFolderPath))
	{
		if (AppSettingMgr.m_bOpenWindowCmdWhenRunProgram)
		{
			if (VinaTextDebugger.HaveBreakPoints(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_GOLANG, strFilePath)) // debug mode
			{
			}
			else // normal mode
			{
				pView->m_BuildSessionInfo._strCommandLine = _T("\"") + strCompilerPath + _T("\" run \"") + pView->m_BuildSessionInfo._strExeFilePath + _T("\"");
				START_CMD(pView->m_BuildSessionInfo);
				pView->LOG_BUILD_INFO_MESSAGE(pView->m_BuildSessionInfo._strCommandLine, _T("Go Lang"));
				LOG_BUILD_MESSAGE_COLOR(_T("[ RUN .................................................................................."));
			}
		}
		else
		{
			CEditorThreadCompiler::TaskItem task;
			task.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_GOLANG;
			task.pWndGUI = pView;
			task.pWndFrame = pFrame;
			task.strCommandLine = _T("\"") + strCompilerPath + _T("\" run \"") + pView->m_BuildSessionInfo._strExeFilePath + _T("\"");
			task.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
			task.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;

			if (VinaTextDebugger.HaveBreakPoints(VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON, strFilePath)) // debug mode
			{
			}
			else // normal mode
			{
				task.strCommandLine = _T("\"") + strCompilerPath + _T("\" run \"") + pView->m_BuildSessionInfo._strExeFilePath + _T("\"");
				pView->LOG_BUILD_INFO_MESSAGE(task.strCommandLine, _T("Go Lang"));
			}
			LOG_BUILD_MESSAGE_COLOR(_T("[ RUN .................................................................................."));
			pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
			ThreadWorkerMgr.CreateWorkerThread(task);
		}
	}
	else
	{
		CString strMsg;
		strMsg.Format(_T("[Path Error] \"%s\" does not exist!\n"), pView->m_BuildSessionInfo._strExeFilePath);
		LOG_BUILD_MESSAGE_COLOR(strMsg, BasicColors::orange);
		return;
	}
}

//////////////////////////////////////////////////////////////////////////
// BuildSQL

void VinaTextCompiler::BuildSQL(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);

	CEditorThreadCompiler::TaskItem task;
	task.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PERL;
	task.pWndGUI = pView;
	task.pWndFrame = pFrame;
	task.strCommandLine = _T("\"") + strCompilerPath + _T("\" \"") + pView->m_BuildSessionInfo._strExeFilePath + _T("\"");
	
	task.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
	task.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
	pView->LOG_BUILD_INFO_MESSAGE(task.strCommandLine, _T("Perl"));
	pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
	ThreadWorkerMgr.CreateWorkerThread(task);
}

//////////////////////////////////////////////////////////////////////////
// BuildPowerShell

void VinaTextCompiler::BuildPowerShell(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	if (PathFileExists(strFilePath))
	{
		CString strFullCmd = _T("start powershell.exe -noexit ") + strFilePath;
		OSUtils::RunSystemCMD(strFullCmd);
		pView->LOG_BUILD_INFO_MESSAGE_SHELL(strFullCmd, _T("PowerShell Windows"));
	}
}

//////////////////////////////////////////////////////////////////////////
// BuildBatch

void VinaTextCompiler::BuildBatch(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	if (PathFileExists(strFilePath))
	{
		CString strFullCmd = _T("start \"\" \"CMD \" /c \"") + strFilePath + _T("\" ^& pause");
		OSUtils::RunSystemCMD(strFullCmd);
		pView->LOG_BUILD_INFO_MESSAGE_SHELL(strFullCmd, _T("Batch Windows"));
	}
}

//////////////////////////////////////////////////////////////////////////
// BuildVerilog

void VinaTextCompiler::BuildVerilog(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);

	CEditorThreadCompiler::TaskItem task;
	task.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VERILOG;
	task.pWndGUI = pView;
	task.pWndFrame = pFrame;
	task.strCommandLine = _T("\"") + strCompilerPath + _T("\" \"") + pView->m_BuildSessionInfo._strExeFilePath + _T("\"");
	
	task.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
	task.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
	pView->LOG_BUILD_INFO_MESSAGE(task.strCommandLine, _T("Verilog"));
	pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
	ThreadWorkerMgr.CreateWorkerThread(task);
}

//////////////////////////////////////////////////////////////////////////
// BuildRuby

void VinaTextCompiler::BuildRuby(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);

	CEditorThreadCompiler::TaskItem task;
	task.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUBY;
	task.pWndGUI = pView;
	task.pWndFrame = pFrame;
	task.strCommandLine = _T("\"") + strCompilerPath + _T("\" \"") + pView->m_BuildSessionInfo._strExeFilePath + _T("\"");
	
	task.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
	task.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
	pView->LOG_BUILD_INFO_MESSAGE(task.strCommandLine, _T("Ruby"));
	pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
	ThreadWorkerMgr.CreateWorkerThread(task);
}

//////////////////////////////////////////////////////////////////////////
// BuildTCL

void VinaTextCompiler::BuildTCL(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);

	CEditorThreadCompiler::TaskItem task;
	task.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_TCL;
	task.pWndGUI = pView;
	task.pWndFrame = pFrame;
	task.strCommandLine = _T("\"") + strCompilerPath + _T("\" \"") + pView->m_BuildSessionInfo._strExeFilePath + _T("\"");
	
	task.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
	task.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
	pView->LOG_BUILD_INFO_MESSAGE(task.strCommandLine, _T("TCL"));
	pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
	ThreadWorkerMgr.CreateWorkerThread(task);
}

//////////////////////////////////////////////////////////////////////////
// BuildAutoIT

void VinaTextCompiler::BuildAutoIT(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{ 
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);

	CEditorThreadCompiler::TaskItem task;
	task.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_AUTOIT;
	task.pWndGUI = pView;
	task.pWndFrame = pFrame;
	task.strCommandLine = _T("\"") + strCompilerPath + _T("\" \"") + pView->m_BuildSessionInfo._strExeFilePath + _T("\"");
	
	task.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
	task.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
	pView->LOG_BUILD_INFO_MESSAGE(task.strCommandLine, _T("Auto IT"));
	pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
	ThreadWorkerMgr.CreateWorkerThread(task);
}

//////////////////////////////////////////////////////////////////////////
// BuildRust

void VinaTextCompiler::BuildRust(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	pView->m_BuildSessionInfo._strExeFilePath.Replace(_T(".rs"), _T(".exe"));
	pView->m_BuildSessionInfo._strExeFileName = PathUtils::GetFilenameFromPath(pView->m_BuildSessionInfo._strExeFilePath);
	if (pView->m_BuildSessionInfo._strExeFilePath.Find(_T(".exe")) != -1)
	{
		OSUtils::KillProcessByName(pView->m_BuildSessionInfo._strExeFileName);
		::DeleteFile(pView->m_BuildSessionInfo._strExeFilePath);
	}
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);
	// rustc main.rs
	CEditorThreadCompiler::TaskItem task;
	task.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUST;
	task.pWndGUI = pView;
	task.pWndFrame = pFrame;
	task.strCommandLine = _T("\"") + strCompilerPath + _T("\" \"") + strFilePath + _T("\"");
	task.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
	task.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
	pView->LOG_BUILD_INFO_MESSAGE(task.strCommandLine, _T("Rust"));
	pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
	ThreadWorkerMgr.CreateWorkerThread(task);
}

//////////////////////////////////////////////////////////////////////////
// BuildR

void VinaTextCompiler::BuildR(CMainFrame * pFrame, CEditorView * pView, const CString & strFilePath, const CString& strCompilerPath)
{
	pView->m_BuildSessionInfo._strExeFilePath = strFilePath;
	pView->m_BuildSessionInfo._strExeFolderPath = PathUtils::GetContainerPath(strFilePath);

	CEditorThreadCompiler::TaskItem task;
	task.currentLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_R;
	task.pWndGUI = pView;
	task.pWndFrame = pFrame;
	task.strCommandLine = _T("\"") + strCompilerPath + _T("\" \"") + pView->m_BuildSessionInfo._strExeFilePath + _T("\"");

	task.strRunFromDirectory = pView->m_BuildSessionInfo._strExeFolderPath;
	task.strRunFromDocPath = pView->m_BuildSessionInfo._strFilePath;
	pView->LOG_BUILD_INFO_MESSAGE(task.strCommandLine, _T("R"));
	pView->m_BuildSessionInfo._BuildMeasureTime = OSUtils::StartBenchmark();
	ThreadWorkerMgr.CreateWorkerThread(task);
}