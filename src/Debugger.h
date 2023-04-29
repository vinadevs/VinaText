/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

////////////////////////////////////////////////////////////
// Debugger command line API

// Python PDB
#define ENABLE_PYTHON_DEBUGGER _T("\" -m pdb \"")
#define CMD_ADD_BREAKPOINT_PDB _T("b ")
#define CMD_CONTINUE_PDB _T("c")
#define CMD_STEP_INTO_PDB _T("s")
#define CMD_STEP_OVER_PDB _T("n")
#define CMD_STEP_OUT_PDB _T("r")
#define CMD_CALL_STACK_PDB _T("w")
#define CMD_RUN_PDB _T("run")
#define CMD_PRINT_PDB _T("p ")
#define CMD_PRETTY_PRINT_PDB _T("pp ")
#define CMD_PRINT_VARS_PDB _T("p vars(")
#define CMD_PRETTY_PRINT_VARS_PDB _T("pp vars(")
#define CMD_DELETE_BREAKPOINT_PDB _T("cl ")
#define CMD_PRINT_VARS_TYPE_PDB _T("type(")

// GDB
#define ENABLE_GDB_DEBUGGER _T("\" -g \"")
#define CMD_ADD_BREAKPOINT_GDB _T("break ")
#define CMD_CONTINUE_GDB _T("continue")
#define CMD_STEP_INTO_GDB _T("step")
#define CMD_STEP_OVER_GDB _T("next")
#define CMD_STEP_OUT_GDB _T("finish")
#define CMD_CALL_STACK_GDB _T("where full")
#define CMD_CURRENT_FRAME_GDB _T("frame")
#define CMD_RUN_GDB _T("run")
#define CMD_PRINT_GDB _T("print ")
#define CMD_PRINT_LOCAL_GDB _T("info locals")
#define CMD_DELETE_BREAKPOINT_GDB _T("clear ")
#define CMD_PRINT_VARS_TYPE_GDB _T("ptype ")

// NodeJS Debugger
#define ENABLE_NODEJS_DEBUGGER _T("\" inspect \"")
#define CMD_ADD_BREAKPOINT_NODEJS _T("setBreakpoint(\"")
#define CMD_CONTINUE_NODEJS _T("cont")
#define CMD_STEP_INTO_NODEJS _T("step")
#define CMD_STEP_OVER_NODEJS _T("next")
#define CMD_STEP_OUT_NODEJS _T("out")
#define CMD_CALL_STACK_NODEJS _T("backtrace")
#define CMD_RUN_NODEJS _T("run")
#define CMD_PRINT_NODEJS _T("exec(\"")
#define CMD_DELETE_BREAKPOINT_NODEJS _T("clearBreakpoint(\"")

// Java JDB
#define ENABLE_JAVA_DEBUGGER _T("\" -g \"")
#define CMD_ADD_BREAKPOINT_JDB _T("stop at ")
#define CMD_CONTINUE_JDB _T("cont")
#define CMD_STEP_INTO_JDB _T("step into")
#define CMD_STEP_OVER_JDB _T("step over")
#define CMD_STEP_OUT_JDB _T("step out")
#define CMD_CALL_STACK_JDB _T("where all")
#define CMD_RUN_JDB _T("run")
#define CMD_PRINT_JDB _T("print ")
#define CMD_PRINT_VARS_JDB _T("dump ")
#define CMD_PRINT_LOCAL_JDB _T("locals")
#define CMD_DELETE_BREAKPOINT_JDB _T("clear ")

////////////////////////////////////////////////////////////

struct BreakPointData
{
	VINATEXT_SUPPORTED_LANGUAGE _language;
	long _lineNumber;
	CString _fileName;
	BreakPointData(VINATEXT_SUPPORTED_LANGUAGE language, long lineNumber, CString fileName)
	{
		_language = language;
		_lineNumber = lineNumber;
		_fileName = fileName;
	}
};

typedef std::vector<BreakPointData> BreakPointDataList;

////////////////////////////////////////////////////////////

typedef std::deque<CString> DebuggerCommandQueue;

////////////////////////////////////////////////////////////
// Debugger Manager

#include "Singleton.h"

class CVinaTextDebugger : public CSingletonHelper<CVinaTextDebugger>
{
public:
	// breakpoints manager
	void AddBreakPointData(VINATEXT_SUPPORTED_LANGUAGE language, long lineNumber, const CString& strFileName);
	void RemoveBreakPointDataInLine(VINATEXT_SUPPORTED_LANGUAGE language, long lineNumber, const CString& strFileName);
	void RemoveBreakPointDataInFile(const CString& strFileName);
	void RemoveAllBreakPointDataInLanguage(VINATEXT_SUPPORTED_LANGUAGE language);
	BOOL HaveBreakPoints(VINATEXT_SUPPORTED_LANGUAGE language, const CString& strFileName);
	BOOL IsThisBreakPointExist(long lineNumber, const CString& strFileName);
	void RegisterInitialBreakPoints();
	BreakPointDataList GetBreakPoinDataList() const;

	// doc operations
	void SetCurrentDocLanguage(VINATEXT_SUPPORTED_LANGUAGE currentDocLanguage);
	VINATEXT_SUPPORTED_LANGUAGE GetCurrentDocLanguage() const;

	// standard debug operations
	void StepOver();
	void StepInto();
	void StepOut();
	void Restart();
	void ShowCallStack();
	void Continue();
	void WatchVariableType(const CString& strVariable);
	void WatchVariableValue(const CString& strVariable);
	void WatchVariableValueNonObject();

	// command line queue operations
	CString GetCurrentCommandLine() const;
	void PuskCommandLineToQueue(const CString& strCommand);
	void RemoveCommandLineFromQueue(const CString& strCommand);
	void RunNextCommandLine();

private:
	CString m_strWatchNonObjectCommand;
	CString m_strCurrentCommandLine;
	BreakPointDataList m_BreakPointDebuggerDataList;
	DebuggerCommandQueue m_CommandQueue;
	VINATEXT_SUPPORTED_LANGUAGE m_currentDocLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_TEXT;
};

////////////////////////////////////////////////////////////
// Debugger Interface

#define VinaTextDebugger CVinaTextDebugger::GetInstance()
