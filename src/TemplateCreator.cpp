/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "TemplateCreator.h"
#include "AppUtil.h"
#include "PathUtil.h"
#include "afxtaskdialog.h"
#include "MainFrm.h"
#include "EditorDoc.h"
#include "Editor.h"

namespace
{
	void GetTemplateText(CString& strTemplateText, FILE_TEMPLATE_TYPE type, VINATEXT_SUPPORTED_LANGUAGE language)
	{
		CString strLanguageTemplateFilePath = PathUtils::GetLanguageTemplateFilePath(language);

		if (!PathFileExists(strLanguageTemplateFilePath)) return;

		CStdioFile stdFile;
		if (stdFile.Open(strLanguageTemplateFilePath, CFile::modeRead))
		{
			CString strLine;
			BOOL bStartReadTemplateSession = FALSE;
			if (type == FILE_TEMPLATE_TYPE::Template_Function)
			{
				while (stdFile.ReadString(strLine))
				{
					if (strLine.IsEmpty()) continue;
					if (strLine.Find(_T("@@ function file template:")) != -1)
					{
						bStartReadTemplateSession = TRUE;
						continue;
					}
					if (strLine.Find(_T("@@ only main file template:")) != -1)
					{
						return;
					}
					if (bStartReadTemplateSession)
					{
						strTemplateText += strLine + _T("\r\n");
					}
				}
			}
			else if (type == FILE_TEMPLATE_TYPE::Template_OnlyMain)
			{
				while (stdFile.ReadString(strLine))
				{
					if (strLine.IsEmpty()) continue;
					if (strLine.Find(_T("@@ only main file template:")) != -1)
					{
						bStartReadTemplateSession = TRUE;
						continue;
					}
					if (bStartReadTemplateSession)
					{
						strTemplateText += strLine + _T("\r\n");
					}
				}
			}
		}
		stdFile.Close();
	}
}

BOOL TemplateCreator::GenerateFile(FILE_TEMPLATE_PARAM param)
{
	CString strFileName = PathUtils::GetFileNameWithoutExtension(param._strFileName);
	CString strTitle = _T(" untitled");
	CString strFullFilePath = param._strFileLocation + _T("\\") + strTitle;
	if (param._targetLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
	{
		strTitle = strFileName + _T(".py");
	}
	else if (param._targetLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C)
	{
		strTitle = strFileName + _T(".c");
	}
	else if (param._targetLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP)
	{
		strTitle = strFileName + _T(".cpp");
	}
	else if (param._targetLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
	{
		strTitle = strFileName + _T(".js");
	}
	else if (param._targetLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
	{
		strTitle = strFileName + _T(".java");
	}
	else if (param._targetLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VISUALBASIC)
	{
		strTitle = strFileName + _T(".vb");
	}
	else if (param._targetLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_GOLANG)
	{
		strTitle = strFileName + _T(".go");
	}
	else if (param._targetLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUST)
	{
		strTitle = strFileName + _T(".rs");
	}
	else if (param._targetLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
	{
		strTitle = strFileName + _T(".pas");
	}
	else if (param._targetLanguage == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PHP)
	{
		strTitle = strFileName + _T(".php");
	}
	strFullFilePath = param._strFileLocation + _T("\\") + strTitle;
	CDocument* pNewDoc = AppUtils::CreateDocumentCheckFileExistence(strFullFilePath);
	if (pNewDoc)
	{
		CMainFrame* pFrame = AppUtils::GetMainFrame();
		if (!pFrame) return FALSE;
		pFrame->RevealInExplorerWindow(strFullFilePath);
		if (param._templateType != FILE_TEMPLATE_TYPE::Template_Empty)
		{
			auto pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
			if (pEditorDoc)
			{
				CEditorCtrl* pEditor = pEditorDoc->GetEditorCtrl();
				if (pEditor)
				{
					CString strTemplateText;
					GetTemplateText(strTemplateText, param._templateType, param._targetLanguage);
					pEditor->SetTextToEditor(strTemplateText);
					pEditorDoc->OnFileSave();
					pEditor->ResetMapUndoRedoSelection();
					pEditor->ResetUndoSavePoint();
					return TRUE;
				}
			}
		}
		else return TRUE;
	}
	return FALSE;
}
