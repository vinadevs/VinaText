/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "CustomizeUserTool.h"
#include "AppUtil.h"
#include "PathUtil.h"
#include "OSUtil.h"
#include "EditorDoc.h"
#include "EditorView.h"

//STRINGTABLE
//BEGIN
	//ID_MENU_ITEM1           "$(LINE_NUMBER)"
	//ID_MENU_ITEM2           "$(POSITION)"
	//ID_MENU_ITEM3           "$(FILE_PATH)"
	//ID_MENU_ITEM4           "$(FILE_NAME)"
	//ID_MENU_ITEM5           "$(FILE_EXT)"
	//ID_MENU_ITEM6           "$(FILE_DIR)"
	//ID_MENU_ITEM7           "$(SELECTED_TEXT)"
	//ID_MENU_ITEM8           "$(ALL_TEXT)"
//END

//STRINGTABLE
//BEGIN
	//ID_MENU_DIR1            "$(INIT_FILE_DIR)"
	//ID_MENU_DIR2            "$(INIT_WINDOW_DIR)"
	//ID_MENU_DIR3            "$(INIT_SYSTEM_DIR)"
//END

IMPLEMENT_SERIAL(CCustomizeUserTool, CUserTool, 1)

// pre-processing command line call
BOOL CCustomizeUserTool::Invoke()
{
	CString _strArguments = m_strArguments;
	CString _strInitialDirectory = m_strInitialDirectory;
	
	if (_strArguments.Find(_T("$(LINE_NUMBER)")) != -1 || _strArguments.Find(_T("$(POSITION)")) != -1 || _strArguments.Find(_T("$(FILE_PATH)")) != -1 ||
		_strArguments.Find(_T("$(FILE_NAME)")) != -1 || _strArguments.Find(_T("$(FILE_EXT)")) != -1 || _strArguments.Find(_T("$(FILE_DIR)")) != -1 ||
		_strArguments.Find(_T("$(SELECTED_TEXT)")) != -1 || _strArguments.Find(_T("$(ALL_TEXT)")) != -1 || _strInitialDirectory.Find(_T("$(INIT_FILE_DIR)")) != -1 ||
		_strInitialDirectory.Find(_T("$(INIT_WINDOW_DIR)")) != -1 || _strInitialDirectory.Find(_T("$(INIT_SYSTEM_DIR)")) != -1)
	{
		CDocument* pDoc = AppUtils::GetMDIActiveDocument();
		if (pDoc && pDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
		{
			auto pActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
			if (pActiveDoc && PathFileExists(pActiveDoc->GetPathName())) // replace variables
			{
				// command line argument
				CEditorCtrl *pEditor = pActiveDoc->GetEditorView()->GetEditorCtrl();
				if (pEditor)
				{
					_strArguments.Replace(_T("$(LINE_NUMBER)"), ESCAPSE_STRING_WITH_QUOTE(AppUtils::IntToCString(pEditor->GetCurrentLine())));
					_strArguments.Replace(_T("$(POSITION)"), ESCAPSE_STRING_WITH_QUOTE(AppUtils::IntToCString(pEditor->GetCurrentPosition())));
					_strArguments.Replace(_T("$(SELECTED_TEXT)"), ESCAPSE_STRING_WITH_QUOTE(pEditor->GetSelectedText()));
					_strArguments.Replace(_T("$(ALL_TEXT)"), ESCAPSE_STRING_WITH_QUOTE(pEditor->GetAllText()));
				}

				_strArguments.Replace(_T("$(FILE_PATH)"), ESCAPSE_STRING_WITH_QUOTE(pActiveDoc->GetPathName()));
				_strArguments.Replace(_T("$(FILE_NAME)"), ESCAPSE_STRING_WITH_QUOTE(pActiveDoc->GetTitle()));
				_strArguments.Replace(_T("$(FILE_EXT)"), ESCAPSE_STRING_WITH_QUOTE(PathUtils::GetFileExtention(pActiveDoc->GetPathName())));
				_strArguments.Replace(_T("$(FILE_DIR)"), ESCAPSE_STRING_WITH_QUOTE(PathUtils::GetContainerPath(pActiveDoc->GetPathName())));

				// initial directory run command
				_strInitialDirectory.Replace(_T("$(INIT_FILE_DIR)"), ESCAPSE_STRING_WITH_QUOTE(pActiveDoc->GetPathName()));
				_strInitialDirectory.Replace(_T("$(INIT_WINDOW_DIR)"), ESCAPSE_STRING_WITH_QUOTE(PathUtils::GetWindowSystemPath()));
				_strInitialDirectory.Replace(_T("$(INIT_SYSTEM_DIR)"), ESCAPSE_STRING_WITH_QUOTE(PathUtils::GetProgramFilePath()));
			}
			else
			{
				AfxMessageBoxFormat(MB_ICONWARNING, _T("[Argument Error] Variable $(FILE_PATH) does not exist!"));
				return FALSE;
			}
			CString strFullCommandLine = ESCAPSE_STRING_WITH_QUOTE(m_strCommand) + CSTRING_SPACE + _strArguments;
			SetCurrentDirectoryW(_strInitialDirectory);
			LOG_OUTPUT_MESSAGE_COLOR(_T("> Executed command line : ") + strFullCommandLine);
			return OSUtils::CreateWin32Process(strFullCommandLine);
		}
	}
	LOG_OUTPUT_MESSAGE_COLOR(_T("> Executed command line : ") + m_strCommand);
	return CUserTool::Invoke();
}