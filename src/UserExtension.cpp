/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "UserExtension.h"
#include "AppUtil.h"
#include "PathUtil.h"
#include "OSUtil.h"
#include "EditorDoc.h"
#include "EditorView.h"

void CUserExtension::OpenConfigFile()
{
	CString extensionPath = PathUtils::GetUserExtensionPath();
	if (PathFileExists(extensionPath))
	{
		AppUtils::CreateDocumentFromFile(extensionPath);
	}
	else
	{
		AfxMessageBoxFormat(MB_ICONWARNING, _T("[Path Error] \"%s\" does not exist!\n"), extensionPath);
	}
}

void CUserExtension::LoadMenuUserExtensions(CMenu* mainMenu, BOOL bRefresh/*= FALSE*/)
{
	if (bRefresh)
	{
		for (auto const& data : m_ExtensionData)
		{
			mainMenu->GetSubMenu(MENU_USER_EXTENSION)->DeleteMenu(data.first, MF_BYCOMMAND);
		}
		m_ExtensionData.clear();
	}
	CString extensionPath = PathUtils::GetUserExtensionPath();
	if (!PathFileExists(extensionPath)) return;
	CStdioFile stdFile;
	if (stdFile.Open(extensionPath, CFile::modeRead))
	{
		CString strLine;
		BOOL bStartReadExtensionSession = FALSE;
		CString strExtensionName;
		CString strExtensionCMD;
		CString strExtensionRunFromDirectory;
		CString strExtensionKeepConsole;
		UINT uExtensionCount = USER_EXTENSION_ID_1;
		while (stdFile.ReadString(strLine))
		{
			if (strLine.IsEmpty()) continue;
			if (strLine.Find(_T("EXTENSION_BEGIN-------------------------------------------")) != -1)
			{
				bStartReadExtensionSession = TRUE;
				continue;
			}
			if (strLine.Find(_T("EXTENSION_END-------------------------------------------")) != -1)
			{
				bStartReadExtensionSession = FALSE;
				if (!strExtensionName.IsEmpty() && !strExtensionCMD.IsEmpty())
				{
					mainMenu->GetSubMenu(MENU_USER_EXTENSION)->AppendMenuW(MF_STRING, uExtensionCount, strExtensionName);
					if (strExtensionRunFromDirectory.IsEmpty())
					{
						strExtensionRunFromDirectory = PathUtils::GetWindowSystemPath();
					}
					m_ExtensionData.emplace(uExtensionCount, CommandData(strExtensionCMD, strExtensionRunFromDirectory, strExtensionKeepConsole));
					++uExtensionCount;
					strExtensionName.Empty();
					strExtensionCMD.Empty();
					strExtensionRunFromDirectory.Empty();
					strExtensionKeepConsole.Empty();
				}
				continue;
			}
			if (bStartReadExtensionSession)
			{
				if (strLine.Find(_T("Extension_Name:")) != -1)
				{
					strExtensionName = strLine.Mid(strLine.Find(_T(":")) + 1).Trim();
				}
				else if (strLine.Find(_T("Extension_CMD:")) != -1)
				{
					strExtensionCMD = strLine.Mid(strLine.Find(_T(":")) + 1).Trim();
				}
				else if (strLine.Find(_T("Extension_Run_From_Directory:")) != -1)
				{
					strExtensionRunFromDirectory = strLine.Mid(strLine.Find(_T(":")) + 1).Trim();
				}
				else if (strLine.Find(_T("Extension_Keep_Console:")) != -1)
				{
					strExtensionKeepConsole = strLine.Mid(strLine.Find(_T(":")) + 1).Trim();
				}
			}
		}
	}
	stdFile.Close();
}
	
void CUserExtension::InvokeCommand(UINT nIDExtension)
{
	auto extension = m_ExtensionData.find(nIDExtension);
	if (extension != m_ExtensionData.end())
	{
		CString strCommand = extension->second._strCMD;
		CString strRunFromDirectory = extension->second._strRunFromDirectory;
		CString strExtensionKeepConsole = extension->second._strExtensionKeepConsole;
		CDocument* pDoc = AppUtils::GetMDIActiveDocument();
		if (pDoc)
		{
			if (strCommand.Find(_T("$(VAR_EDIT_LINE_NUMBER)")) != -1 || strCommand.Find(_T("$(VAR_EDIT_POSITION)")) != -1 || strCommand.Find(_T("$(VAR_FILE_PATH)")) != -1 ||
				strCommand.Find(_T("$(VAR_FILE_NAME)")) != -1 || strCommand.Find(_T("$(VAR_FILE_EXT)")) != -1 || strCommand.Find(_T("$(VAR_FILE_DIR)")) != -1 ||
				strCommand.Find(_T("$(VAR_EDIT_SELECTED_TEXT)")) != -1 || strCommand.Find(_T("$(VAR_EDIT_ALL_TEXT)")) != -1 || strRunFromDirectory.Find(_T("$(VAR_FILE_DIR)")) != -1)
			{
				if (pDoc && PathFileExists(pDoc->GetPathName())) // replace variables
				{
					auto pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
					// command line
					if (pEditorDoc)
					{
						CEditorCtrl* pEditor = pEditorDoc->GetEditorView()->GetEditorCtrl();
						if (pEditor) // only variables for editor document
						{
							strCommand.Replace(_T("$(VAR_EDIT_LINE_NUMBER)"), ESCAPSE_STRING_WITH_QUOTE(AppUtils::IntToCString(pEditor->GetCurrentLine())));
							strCommand.Replace(_T("$(VAR_EDIT_POSITION)"), ESCAPSE_STRING_WITH_QUOTE(AppUtils::IntToCString(pEditor->GetCurrentPosition())));
							strCommand.Replace(_T("$(VAR_EDIT_SELECTED_TEXT)"), ESCAPSE_STRING_WITH_QUOTE(pEditor->GetSelectedText()));
							strCommand.Replace(_T("$(ALL_TEXT)"), ESCAPSE_STRING_WITH_QUOTE(pEditor->GetAllText()));
						}
					}		
					strCommand.Replace(_T("$(VAR_FILE_PATH)"), ESCAPSE_STRING_WITH_QUOTE(pDoc->GetPathName()));
					strCommand.Replace(_T("$(VAR_FILE_NAME)"), ESCAPSE_STRING_WITH_QUOTE(pDoc->GetTitle()));
					strCommand.Replace(_T("$(VAR_FILE_EXT)"), ESCAPSE_STRING_WITH_QUOTE(PathUtils::GetFileExtention(pDoc->GetPathName())));
					strCommand.Replace(_T("$(VAR_FILE_DIR)"), ESCAPSE_STRING_WITH_QUOTE(PathUtils::GetContainerPath(pDoc->GetPathName())));
					// start dir
					strRunFromDirectory.Replace(_T("$(VAR_FILE_DIR)"), ESCAPSE_STRING_WITH_QUOTE(pDoc->GetPathName()));
				}
				else // general
				{
					AfxMessageBoxFormat(MB_ICONWARNING, _T("[Extension Error] \"%s\" does not exist!"), pDoc->GetPathName());
					return;
				}
			}
		}
		SetCurrentDirectoryW(strRunFromDirectory);
		if (strExtensionKeepConsole.CompareNoCase(_T("Yes")) == 0) 
		{
			CString strEscapsedCommandLine = ESCAPSE_STRING_WITH_QUOTE(strCommand);
			LOG_OUTPUT_MESSAGE_COLOR(_T("> Executed command line : ") + strCommand);
			OSUtils::RunSystemCMD(_T("cmd.exe /k ") + strEscapsedCommandLine);
		}
		else
		{
			LOG_OUTPUT_MESSAGE_COLOR(_T("> Executed command line : ") + strCommand);
			OSUtils::CreateWin32Process(strCommand);
		}
	}
	else
	{
		AfxMessageBox(_T("[Extension Error] Could not found extension data for this menu!"), MB_ICONWARNING);
	}
}
