/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Debugger.h"
#include "MultiThreadWorker.h"
#include "AppUtil.h"
#include "PathUtil.h"

void CVinaTextDebugger::AddBreakPointData(VINATEXT_SUPPORTED_LANGUAGE language, long lineNumber, const CString & strFileName)
{
	m_BreakPointDebuggerDataList.push_back(BreakPointData(language, lineNumber, strFileName));
	if (ThreadWorkerMgr.IsDebuggerRunning())
	{
		if (language == ThreadWorkerMgr.GetCurrentTask().currentLanguage)
		{
			if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
			{
				CString strCommand = CMD_ADD_BREAKPOINT_PDB + strFileName + _T(":") + AppUtils::LongToCString(lineNumber);
				PuskCommandLineToQueue(strCommand);
			}
			else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
				|| language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
				|| language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
			{
				CString strCommand = CMD_ADD_BREAKPOINT_GDB + strFileName + _T(":") + AppUtils::LongToCString(lineNumber);
				PuskCommandLineToQueue(strCommand);
			}
			else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
			{
				CString strCommand = CMD_ADD_BREAKPOINT_NODEJS + PathUtils::BackslashToForwardslash(strFileName) + _T("\", ") + AppUtils::LongToCString(lineNumber) + _T(")");
				PuskCommandLineToQueue(strCommand);
			}
			else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
			{
				CString strCommand = CMD_ADD_BREAKPOINT_JDB + PathUtils::GetFileNameWithoutExtension(strFileName) + _T(":") + AppUtils::LongToCString(lineNumber);
				PuskCommandLineToQueue(strCommand);
			}
			RunNextCommandLine();
		}
		else
		{
			AfxMessageBox(_T("[Debugging Error] Can not add a breakpoint on different language file when debugger was already running!"));
		}
	}
}

void CVinaTextDebugger::RemoveBreakPointDataInLine(VINATEXT_SUPPORTED_LANGUAGE language, long lineNumber, const CString & strFileName)
{
	m_BreakPointDebuggerDataList.erase(std::remove_if(
		m_BreakPointDebuggerDataList.begin(),
		m_BreakPointDebuggerDataList.end(),
		[&](BreakPointData const & data)
	{
		return data._fileName.CompareNoCase(strFileName) == 0 && data._lineNumber == lineNumber;
	}),
	m_BreakPointDebuggerDataList.end());
	if (ThreadWorkerMgr.IsDebuggerRunning())
	{
		if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
		{
			CString strCommand = CMD_DELETE_BREAKPOINT_PDB + strFileName + _T(":") + AppUtils::LongToCString(lineNumber);
			PuskCommandLineToQueue(strCommand);
		}
		else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
			|| language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
			|| language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
		{
			CString strCommand = CMD_DELETE_BREAKPOINT_GDB + strFileName + _T(":") + AppUtils::LongToCString(lineNumber);
			PuskCommandLineToQueue(strCommand);
		}
		else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
		{
			CString strCommand = CMD_DELETE_BREAKPOINT_NODEJS + PathUtils::BackslashToForwardslash(strFileName) + _T("\", ") + AppUtils::LongToCString(lineNumber) + _T(")");
			PuskCommandLineToQueue(strCommand);
		}
		else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
		{
			CString strCommand = CMD_DELETE_BREAKPOINT_JDB + PathUtils::GetFileNameWithoutExtension(strFileName) + _T(":") + AppUtils::LongToCString(lineNumber);
			PuskCommandLineToQueue(strCommand);
		}
		RunNextCommandLine();
	}
}

void CVinaTextDebugger::RemoveBreakPointDataInFile(const CString & strFileName)
{
	m_BreakPointDebuggerDataList.erase(std::remove_if(
		m_BreakPointDebuggerDataList.begin(),
		m_BreakPointDebuggerDataList.end(),
		[&](BreakPointData const & data)
	{
		return data._fileName.CompareNoCase(strFileName) == 0;
	}),
	m_BreakPointDebuggerDataList.end());
	if (ThreadWorkerMgr.IsDebuggerRunning())
	{
		if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
		{
			for (auto const& breakpoint : m_BreakPointDebuggerDataList) // set static breakpoints!
			{
				if (breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON && breakpoint._fileName.CompareNoCase(strFileName) == 0)
				{
					CString strCommand = CMD_DELETE_BREAKPOINT_PDB + breakpoint._fileName + _T(":") + AppUtils::LongToCString(breakpoint._lineNumber);
					PuskCommandLineToQueue(strCommand);
					RunNextCommandLine();
				}
			}
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
			|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
			|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
		{
			for (auto const& breakpoint : m_BreakPointDebuggerDataList) // set static breakpoints!
			{
				if ((breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
					|| breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
					|| breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
					&& breakpoint._fileName.CompareNoCase(strFileName) == 0)
				{
					CString strCommand = CMD_DELETE_BREAKPOINT_GDB + breakpoint._fileName + _T(":") + AppUtils::LongToCString(breakpoint._lineNumber);
					PuskCommandLineToQueue(strCommand);
					RunNextCommandLine();
				}
			}
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
		{
			for (auto const& breakpoint : m_BreakPointDebuggerDataList) // set static breakpoints!
			{
				if (breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT && breakpoint._fileName.CompareNoCase(strFileName) == 0)
				{
					CString strCommand = CMD_DELETE_BREAKPOINT_NODEJS + PathUtils::BackslashToForwardslash(strFileName) + _T("\", ") + AppUtils::LongToCString(breakpoint._lineNumber) + _T(")");
					PuskCommandLineToQueue(strCommand);
					RunNextCommandLine();
				}
			}
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
		{
			for (auto const& breakpoint : m_BreakPointDebuggerDataList) // set static breakpoints!
			{
				if (breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA && breakpoint._fileName.CompareNoCase(strFileName) == 0)
				{
					CString strCommand = CMD_DELETE_BREAKPOINT_JDB + PathUtils::GetFileNameWithoutExtension(breakpoint._fileName) + _T(":") + AppUtils::LongToCString(breakpoint._lineNumber);
					PuskCommandLineToQueue(strCommand);
					RunNextCommandLine();
				}
			}
		}
	}
}

void CVinaTextDebugger::RemoveAllBreakPointDataInLanguage(VINATEXT_SUPPORTED_LANGUAGE language)
{
	m_BreakPointDebuggerDataList.erase(std::remove_if(
		m_BreakPointDebuggerDataList.begin(),
		m_BreakPointDebuggerDataList.end(),
		[&](BreakPointData const & data)
	{
		return data._language == language;
	}),
	m_BreakPointDebuggerDataList.end());
	if (ThreadWorkerMgr.IsDebuggerRunning())
	{
		if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
		{
			for (auto const& breakpoint : m_BreakPointDebuggerDataList) // set static breakpoints!
			{
				if (breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
				{
					CString strCommand = CMD_DELETE_BREAKPOINT_PDB + breakpoint._fileName + _T(":") + AppUtils::LongToCString(breakpoint._lineNumber);
					PuskCommandLineToQueue(strCommand);
					RunNextCommandLine();
				}
			}
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
			|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
			|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
		{
			for (auto const& breakpoint : m_BreakPointDebuggerDataList) // set static breakpoints!
			{
				if (breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
					|| breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
					|| breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
				{
					CString strCommand = CMD_DELETE_BREAKPOINT_GDB + breakpoint._fileName + _T(":") + AppUtils::LongToCString(breakpoint._lineNumber);
					PuskCommandLineToQueue(strCommand);
					RunNextCommandLine();
				}
			}
		}
		else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
		{
			for (auto const& breakpoint : m_BreakPointDebuggerDataList) // set static breakpoints!
			{
				if (breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
				{
					CString strCommand = CMD_DELETE_BREAKPOINT_NODEJS + PathUtils::BackslashToForwardslash(breakpoint._fileName) + _T("\", ") + AppUtils::LongToCString(breakpoint._lineNumber) + _T(")");
					PuskCommandLineToQueue(strCommand);
					RunNextCommandLine();
				}
			}
		}
		else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
		{
			for (auto const& breakpoint : m_BreakPointDebuggerDataList) // set static breakpoints!
			{
				if (breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
				{
					CString strCommand = CMD_DELETE_BREAKPOINT_JDB + PathUtils::GetFileNameWithoutExtension(breakpoint._fileName) + _T(":") + AppUtils::LongToCString(breakpoint._lineNumber);
					PuskCommandLineToQueue(strCommand);
					RunNextCommandLine();
				}
			}
		}
	}
}

BOOL CVinaTextDebugger::HaveBreakPoints(VINATEXT_SUPPORTED_LANGUAGE language, const CString & strFileName)
{
	for (auto const& breakpoint : m_BreakPointDebuggerDataList)
	{
		if (breakpoint._language == language)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CVinaTextDebugger::SetCurrentDocLanguage(VINATEXT_SUPPORTED_LANGUAGE currentDocLanguage)
{
	m_currentDocLanguage = currentDocLanguage;
}

VINATEXT_SUPPORTED_LANGUAGE CVinaTextDebugger::GetCurrentDocLanguage() const
{
	return m_currentDocLanguage;
}

CString CVinaTextDebugger::GetCurrentCommandLine() const
{
	return m_strCurrentCommandLine;
}

void CVinaTextDebugger::RegisterInitialBreakPoints()
{
	m_CommandQueue.clear();
	if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
	{
		for (auto const& breakpoint : m_BreakPointDebuggerDataList) 
		{
			if (breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
			{
				CString strCommand = CMD_ADD_BREAKPOINT_PDB + breakpoint._fileName + _T(":") + AppUtils::LongToCString(breakpoint._lineNumber);
				PuskCommandLineToQueue(strCommand);
			}
		}
		PuskCommandLineToQueue(CMD_CONTINUE_PDB);
	}
	else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
		|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
		|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
	{
		for (auto const& breakpoint : m_BreakPointDebuggerDataList)
		{
			if (breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
				|| breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
				|| breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
			{
				CString strCommand = CMD_ADD_BREAKPOINT_GDB + breakpoint._fileName + _T(":") + AppUtils::LongToCString(breakpoint._lineNumber);
				PuskCommandLineToQueue(strCommand);
			}
		}
		PuskCommandLineToQueue(CMD_RUN_GDB); 
	}
	else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
	{
		for (auto const& breakpoint : m_BreakPointDebuggerDataList)
		{
			if (breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
			{
				CString strCommand = CMD_ADD_BREAKPOINT_NODEJS + PathUtils::BackslashToForwardslash(breakpoint._fileName) + _T("\", ") + AppUtils::LongToCString(breakpoint._lineNumber) + _T(")");
				PuskCommandLineToQueue(strCommand);
			}
		}
		PuskCommandLineToQueue(CMD_CONTINUE_NODEJS);
	}
	else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
	{
		for (auto const& breakpoint : m_BreakPointDebuggerDataList)
		{
			if (breakpoint._language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
			{
				CString strCommand = CMD_ADD_BREAKPOINT_JDB + PathUtils::GetFileNameWithoutExtension(breakpoint._fileName) + _T(":") + AppUtils::LongToCString(breakpoint._lineNumber);
				PuskCommandLineToQueue(strCommand);
			}
		}
		PuskCommandLineToQueue(CMD_RUN_JDB);
	}
}

void CVinaTextDebugger::RunNextCommandLine()
{
	if (m_CommandQueue.size() > 0)
	{
		m_strCurrentCommandLine = m_CommandQueue.front();
		m_CommandQueue.pop_front();
		ThreadWorkerMgr.WriteUserInputToPipe(m_strCurrentCommandLine);
	}
}

BOOL CVinaTextDebugger::IsThisBreakPointExist(long lineNumber, const CString & strFileName)
{
	for (auto breakpoint : m_BreakPointDebuggerDataList) // set static breakpoints!
	{
		if ((breakpoint._fileName.CompareNoCase(strFileName) == 0)
			&& breakpoint._lineNumber == lineNumber)
		{
			return TRUE;
		}
	}
	return FALSE;
}

BreakPointDataList CVinaTextDebugger::GetBreakPoinDataList() const
{
	return m_BreakPointDebuggerDataList;
}

void CVinaTextDebugger::PuskCommandLineToQueue(const CString & strCommand)
{
	m_CommandQueue.push_back(strCommand);
}

void CVinaTextDebugger::RemoveCommandLineFromQueue(const CString & strCommand)
{
	m_CommandQueue.erase(std::remove(
		m_CommandQueue.begin(),
		m_CommandQueue.end(),
		strCommand),
		m_CommandQueue.end());
}

void CVinaTextDebugger::StepOver()
{
	if (ThreadWorkerMgr.IsDebuggerRunning())
	{
		if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
		{
			PuskCommandLineToQueue(CMD_STEP_OVER_PDB);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
			|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
			|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
		{
			PuskCommandLineToQueue(CMD_STEP_OVER_GDB);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
		{
			PuskCommandLineToQueue(CMD_STEP_OVER_NODEJS);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
		{
			PuskCommandLineToQueue(CMD_STEP_OVER_JDB);
		}
		RunNextCommandLine();
	}
	else
	{
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [Step Over Error] There is no debugger is running..."));
	}
}

void CVinaTextDebugger::StepInto()
{
	if (ThreadWorkerMgr.IsDebuggerRunning())
	{
		if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
		{
			PuskCommandLineToQueue(CMD_STEP_INTO_PDB);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
			|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
			|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
		{
			PuskCommandLineToQueue(CMD_STEP_INTO_GDB);
			PuskCommandLineToQueue(CMD_CURRENT_FRAME_GDB); // where we are!
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
		{
			PuskCommandLineToQueue(CMD_STEP_INTO_NODEJS);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
		{
			PuskCommandLineToQueue(CMD_STEP_INTO_JDB);
		}
		RunNextCommandLine();
	}
	else
	{
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [Step Into Error] There is no debugger is running..."));
	}
}

void CVinaTextDebugger::StepOut()
{
	if (ThreadWorkerMgr.IsDebuggerRunning())
	{
		if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
		{
			PuskCommandLineToQueue(CMD_STEP_OUT_PDB);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
			|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
			|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
		{
			PuskCommandLineToQueue(CMD_STEP_OUT_GDB);
			PuskCommandLineToQueue(CMD_CURRENT_FRAME_GDB); // where we are!
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
		{
			PuskCommandLineToQueue(CMD_STEP_OUT_NODEJS);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
		{
			PuskCommandLineToQueue(CMD_STEP_OUT_JDB);
		}
		RunNextCommandLine();
	}
	else
	{
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [Step Out Error] There is no debugger is running..."));
	}
}

void CVinaTextDebugger::Restart()
{
	if (ThreadWorkerMgr.IsDebuggerRunning())
	{
		if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
		{
			PuskCommandLineToQueue(CMD_RUN_PDB);
			PuskCommandLineToQueue(CMD_CONTINUE_PDB);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
			|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
			|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
		{
			PuskCommandLineToQueue(CMD_RUN_GDB);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
		{
			PuskCommandLineToQueue(CMD_RUN_NODEJS); 
			PuskCommandLineToQueue(CMD_CONTINUE_NODEJS);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
		{
			PuskCommandLineToQueue(CMD_RUN_JDB);
			PuskCommandLineToQueue(CMD_CONTINUE_JDB);
		}
		RunNextCommandLine();
	}
	else
	{
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [Restart Debugger Error] There is no debugger is running..."));
	}
}

void CVinaTextDebugger::ShowCallStack()
{
	if (ThreadWorkerMgr.IsDebuggerRunning())
	{
		if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
		{
			PuskCommandLineToQueue(CMD_CALL_STACK_PDB);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
			|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
			|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
		{
			PuskCommandLineToQueue(CMD_CALL_STACK_GDB);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
		{
			PuskCommandLineToQueue(CMD_CALL_STACK_NODEJS);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
		{
			PuskCommandLineToQueue(CMD_CALL_STACK_JDB);
		}
		RunNextCommandLine();
	}
	else
	{
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [Call Stack Error] There is no debugger is running..."));
	}
}

void CVinaTextDebugger::Continue()
{
	if (ThreadWorkerMgr.IsDebuggerRunning())
	{
		if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
		{
			PuskCommandLineToQueue(CMD_CONTINUE_PDB);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP
			|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C
			|| m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
		{
			PuskCommandLineToQueue(CMD_CONTINUE_GDB);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
		{
			PuskCommandLineToQueue(CMD_CONTINUE_NODEJS);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
		{
			PuskCommandLineToQueue(CMD_CONTINUE_JDB);
		}
		RunNextCommandLine();
	}
	else
	{
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [Continue Error] There is no debugger is running..."));
	}
}

void CVinaTextDebugger::WatchVariableType(const CString & strVariable)
{
	if (ThreadWorkerMgr.IsDebuggerRunning())
	{
		if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
		{
			LOG_BUILD_MESSAGE_COLOR(_T(">>> [Watch Python Object Type] : ") + strVariable, BasicColors::light_orange);
			CString strCommand = CMD_PRINT_VARS_TYPE_PDB + strVariable + _T(")");
			PuskCommandLineToQueue(strCommand);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP)
		{
			LOG_BUILD_MESSAGE_COLOR(_T(">>> [Watch C++ Object Type] : ") + strVariable, BasicColors::light_orange);
			CString strCommand = CMD_PRINT_VARS_TYPE_GDB + strVariable;
			PuskCommandLineToQueue(strCommand);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C)
		{
			LOG_BUILD_MESSAGE_COLOR(_T(">>> [Watch C Object Type] : ") + strVariable, BasicColors::light_orange);
			CString strCommand = CMD_PRINT_VARS_TYPE_GDB + strVariable;
			PuskCommandLineToQueue(strCommand);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
		{
			LOG_BUILD_MESSAGE_COLOR(_T(">>> [Watch Pascal Object Type] : ") + strVariable, BasicColors::light_orange);
			CString strCommand = CMD_PRINT_VARS_TYPE_GDB + strVariable;
			PuskCommandLineToQueue(strCommand);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
		{
			LOG_BUILD_MESSAGE_COLOR(_T(">>> [Watch JavaScript Object Type] : NodeJS debugger has not supported view object type yet..."), BasicColors::light_orange);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
		{
			LOG_BUILD_MESSAGE_COLOR(_T(">>> [Watch Java Object Type] : JVM debugger has not supported view object type yet..."), BasicColors::light_orange);
		}
		RunNextCommandLine();
	}
	else
	{
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [Watch Type Error] There is no debugger is running..."));
	}
}

void CVinaTextDebugger::WatchVariableValue(const CString & strVariable)
{
	if (ThreadWorkerMgr.IsDebuggerRunning())
	{
		if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
		{
			LOG_BUILD_MESSAGE_COLOR(_T(">>> [Watch Python Object Value] : ") + strVariable, BasicColors::light_orange);
			CString strCommand = CMD_PRETTY_PRINT_VARS_PDB + strVariable + _T(")");
			m_strWatchNonObjectCommand = CMD_PRETTY_PRINT_PDB + strVariable;
			PuskCommandLineToQueue(strCommand);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP)
		{
			LOG_BUILD_MESSAGE_COLOR(_T(">>> [Watch C++ Object Value] : ") + strVariable, BasicColors::light_orange);
			CString strCommand = CMD_PRINT_GDB + strVariable;
			PuskCommandLineToQueue(strCommand);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C)
		{
			LOG_BUILD_MESSAGE_COLOR(_T(">>> [Watch C Object Value] : ") + strVariable, BasicColors::light_orange);
			CString strCommand = CMD_PRINT_GDB + strVariable;
			PuskCommandLineToQueue(strCommand);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
		{
			LOG_BUILD_MESSAGE_COLOR(_T(">>> [Watch Pascal Object Value] : ") + strVariable, BasicColors::light_orange);
			CString strCommand = CMD_PRINT_GDB + strVariable;
			PuskCommandLineToQueue(strCommand);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
		{
			LOG_BUILD_MESSAGE_COLOR(_T(">>> [Watch JavaScript Object Value] : ") + strVariable, BasicColors::light_orange);
			CString strCommand = CMD_PRINT_NODEJS + strVariable + _T("\")");
			PuskCommandLineToQueue(strCommand);
		}
		else if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
		{
			LOG_BUILD_MESSAGE_COLOR(_T(">>> [Watch Java Object Value] : ") + strVariable, BasicColors::light_orange);
			CString strCommand = CMD_PRINT_VARS_JDB + strVariable + _T("\")");
			PuskCommandLineToQueue(strCommand);
		}
		RunNextCommandLine();
	}
	else
	{
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [Watch Value Error] There is no debugger is running..."));
	}
}

void CVinaTextDebugger::WatchVariableValueNonObject()
{
	if (ThreadWorkerMgr.IsDebuggerRunning())
	{
		if (m_currentDocLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
		{
			PuskCommandLineToQueue(m_strWatchNonObjectCommand);
		}
		RunNextCommandLine();
	}
	else
	{
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [Watch Object Error] There is no debugger is running..."));
	}
}
