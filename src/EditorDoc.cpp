/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VinaTextApp.h"
#endif

#include <propkey.h>
#include "MainFrm.h"
#include "EditorDoc.h"
#include "EditorView.h"
#include "afxdatarecovery.h"
#include "EditorDatabase.h"
#include "AppUtil.h"
#include "Editor.h"
#include "AppSettings.h"
#include "CodePageMFCDlg.h"
#include "MultiThreadWorker.h"
#include "RecentCloseFileManager.h"
#include "FileBrowser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SUCCESS_SHELL_EXEC_RET 32

// CEditorDoc

IMPLEMENT_DYNCREATE(CEditorDoc, CBaseDoc)

BEGIN_MESSAGE_MAP(CEditorDoc, CBaseDoc)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE_ALL, OnFileSaveAll)
	ON_COMMAND(ID_SAVE_ENCODING_ANSI, OnFileSaveASCII)
	ON_COMMAND(ID_SAVE_ENCODING_UTF8, OnFileSaveUTF8)
	ON_COMMAND(ID_SAVE_ENCODING_UTF16LE,OnFileSaveUTF16LE)
	ON_COMMAND(ID_SAVE_ENCODING_UTF16BE, OnFileSaveUTF16BE)
	ON_COMMAND(ID_SAVE_ENCODING_UTF32LE, OnFileSaveUTF32LE)
	ON_COMMAND(ID_SAVE_ENCODING_UTF32BE, OnFileSaveUTF32BE)
	ON_COMMAND(ID_FILE_SAVE_AS_ENCODING, OnFileSaveAsEncoding)
END_MESSAGE_MAP()

// CEditorDoc construction/destruction

CEditorDoc::CEditorDoc()
{
	// TODO: add one-time construction code here
	if (m_pLangDatabase == NULL)
	{
		m_pLangDatabase = std::make_unique<CLanguageDatabase>();
	}
}

CEditorDoc::~CEditorDoc()
{
	if (GetPathName().IsEmpty())
	{
		AppSettingMgr.RemoveDocumentUndefTitle(GetTitle());
	}
}

CLanguageDatabase* CEditorDoc::GetDocLanguageDatabase() const
{
	return m_pLangDatabase.get();
}

BOOL CEditorDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!PathFileExists(lpszPathName))
	{
		if (AppSettingMgr.m_bWarningForFileNotExist)
		{
			CString strMessage = _T("[Path Error] File %s does not exist. Do you want to create it?");
			strMessage.Format(strMessage, lpszPathName);
			if (IDYES == AfxMessageBox(strMessage, MB_YESNO | MB_ICONWARNING))
			{
				if (!PathUtils::SaveFileTrunc(lpszPathName, _T("")))
				{
					return FALSE;
				}
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}

	if (!CBaseDoc::OnOpenDocument(lpszPathName))
		return FALSE;

	CEditorView* pView = GetEditorView();
	ASSERT(pView); if (!pView) return FALSE;
	CEditorCtrl* pEditor = pView->GetEditorCtrl();
	if (pEditor)
	{
		// disable modification notifications to editor while OnOpenDocument is being called
		pEditor->SetModEventMask(SC_MOD_NONE);
	}
	return TRUE;
}

BOOL CEditorDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CDataRecoveryHandler* autohandler = AfxGetApp()->GetDataRecoveryHandler();
	CString autosavepath = autohandler->GetAutosavePath();
	if (CString(lpszPathName).Left(autosavepath.GetLength()).CompareNoCase(autosavepath) == 0)
	{
		// autosaving - just call the default
		return CBaseDoc::OnSaveDocument(lpszPathName);
	}
	// customize save file
	CEditorView *pEditorView = GetEditorView();
	if (pEditorView != NULL)
	{
		CEditorCtrl* pEditor = pEditorView->GetEditorCtrl();
		if (pEditor)
		{
			pEditor->SetEditorInitiationState(TRUE);
		}
		PreSaveFile(lpszPathName);
		BOOL bRet = pEditorView->SaveFileAndInitilizeEditor(lpszPathName);
		if (bRet)
		{
			SetModifiedFlag(FALSE);
		}
		return bRet;
	}
	return FALSE;
}

CEditorView* CEditorDoc::GetEditorView() const
{
	POSITION pos = GetFirstViewPosition();
	CEditorView* pView = (CEditorView*)GetNextView(pos);
	if (pView)
	{
		return pView;
	}
	else
	{
		//ASSERT(pView);
		return NULL;
	}
}

CEditorCtrl* CEditorDoc::GetEditorCtrl() const
{
	CEditorView* pView = GetEditorView();
	ASSERT(pView);
	if (!pView) return NULL;
	CEditorCtrl* pEditor = pView->GetEditorCtrl();
	if (pEditor) return pEditor;
	ASSERT(pEditor);
	return NULL;
}

void CEditorDoc::SetSaveDocumentPath(const CString& strSaveDocumentPath)
{
	m_strSaveDocumentPath = strSaveDocumentPath;
}

void CEditorDoc::ReloadPreviewDocument(const CString & strFilePath)
{
	if (PathFileExists(strFilePath))
	{
		AppSettingMgr.SaveRecentEditorInfo(GetPathName()); // save old editor state
		SetPathName(strFilePath);
		AppUtils::GetVinaTextApp()->m_bIsReloadByPreviewMode = TRUE;
		GetEditorView()->UpdatePreviewFileContent();
		AppUtils::GetVinaTextApp()->m_bIsReloadByPreviewMode = FALSE;
	}
}

void CEditorDoc::OnCloseDocument()
{
	CString strPathName = GetPathName();
	if (AppUtils::GetDocumentTypeCount(DOCUMENT_TYPE::DOC_ALL) == 1 && strPathName.IsEmpty() && !IsModified())
	{
		AppSettingMgr.RemoveDocumentUndefTitle(GetTitle());
		SetTitle(AppSettingMgr.CreateDocumentUndefTitle());
		return;
	}

	// clean up from mainframe
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;
	pFrame->RemoveDebuggerDocument(this);
	pFrame->CloseQuickSearchDialog();

	// clean up from worker thread
	if (strPathName.CompareNoCase(ThreadWorkerMgr.GetCurrentTask().strRunFromDocPath) == 0 && ThreadWorkerMgr.IsRunning())
	{
		ThreadWorkerMgr.StopThreadWorker();
	}

	// save recent data
	RecentCloseMDITabManager.PushTab(strPathName);
	AppSettingMgr.SaveRecentEditorInfo(strPathName);

	// this must be called so the reference count of the document is decreased and the memory can be released
	GetEditorCtrl()->ReleaseDocument();

	// every data get from document must be done before this...
	CDocument::OnCloseDocument();
	AppUtils::CheckLastOpenDocument();
}

void CEditorDoc::OnFileSave()
{
	if (!IsModified())
	{
		AppUtils::UpdateModifiedDocumentTitle(this, FALSE);
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Save File] Unmodified file..."));
		return;
	}
	CString strFileName = GetPathName();
	if (PathFileExists(strFileName))
	{
		// Save document
		if (!OnSaveDocument(strFileName))
		{
			OSUtils::UseAdministrationHandler();
		}
	}
	else
	{
		// Call file save as function
		OnFileSaveAs();
	}
}

void CEditorDoc::OnFileSaveAs()
{
	CString strTitle = GetTitle();
	strTitle.Replace(_T("*"), _T(""));

	// Default File Filter
	CString strDefaultFilter = PathUtils::GetDataBaseFileFilter();

	if (m_strSaveDocumentPath.IsEmpty())
	{
		if (AppSettingMgr.m_bUseInitialFilePickerPath)
		{
			m_strSaveDocumentPath = AppSettingMgr.m_strInitialFilePickerPath;
		}
		else if (PathFileExists(GetPathName()))
		{
			CString strFolderParent = PathUtils::GetContainerPath(GetPathName());
			if (PathFileExists(strFolderParent))
			{
				m_strSaveDocumentPath = strFolderParent;
			}
		}
	}

	// Create a file save as dialog
	CEditSaveDialog fdSaveAs(FALSE, NULL, strTitle.Trim(), OFN_OVERWRITEPROMPT, strDefaultFilter);

	// Set current directory for file save as dialog
	fdSaveAs.m_ofn.lpstrInitialDir = m_strSaveDocumentPath;

	// Open dialog
	if (fdSaveAs.DoModal() == IDOK)
	{
		// Get file name
		CString strFileName = fdSaveAs.GetPathName();
		if (strFileName.IsEmpty()) return;

		// Close same name document before save
		if (!PathFileExists(GetPathName()))
		{
			AppUtils::CloseDocumentByFilePath(strFileName);
		}

		// Save document
		if (OnSaveDocument(strFileName))
		{
			if (PathFileExists(strFileName))
			{
				// Set new file name
				SetPathName(strFileName);
			}
			// reveal in explorer
			//AppUtils::GetMainFrame()->RevealInExplorerWindow(strFileName);
		}
		else
		{
			OSUtils::UseAdministrationHandler();
		}
	}
	m_strSaveDocumentPath.Empty();
}

void CEditorDoc::OnFileSaveAll()
{
	AppUtils::SaveAllModifiedDocuments();
}

void CEditorDoc::OnFileSaveASCII()
{
	GetEditorCtrl()->SetSaveEncoding(TF_ANSI);
	OnFileSave();
}

void CEditorDoc::OnFileSaveUTF8()
{
	GetEditorCtrl()->SetSaveEncoding(TF_UTF8);
	OnFileSave();
}

void CEditorDoc::OnFileSaveUTF16LE()
{
	GetEditorCtrl()->SetSaveEncoding(TF_UTF16LE);
	OnFileSave();
}

void CEditorDoc::OnFileSaveUTF16BE()
{
	GetEditorCtrl()->SetSaveEncoding(TF_UTF16BE);
	OnFileSave();
}

void CEditorDoc::OnFileSaveUTF32LE()
{
	GetEditorCtrl()->SetSaveEncoding(TF_UTF32LE);
	OnFileSave();
}

void CEditorDoc::OnFileSaveUTF32BE()
{
	GetEditorCtrl()->SetSaveEncoding(TF_UTF32BE);
	OnFileSave();
}

void CEditorDoc::OnUpdateFileOSaveUTFASCII(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(GetEditorCtrl()->IsReadOnlyEditor());
}

void CEditorDoc::OnUpdateFileSaveUTF8(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(GetEditorCtrl()->IsReadOnlyEditor());
}

void CEditorDoc::OnUpdateFileOSaveUTF16LE(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(GetEditorCtrl()->IsReadOnlyEditor());
}

void CEditorDoc::OnUpdateFileSaveUTF16BE(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(GetEditorCtrl()->IsReadOnlyEditor());
}

void CEditorDoc::OnUpdateFileSaveUTF32LE(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(GetEditorCtrl()->IsReadOnlyEditor());
}

void CEditorDoc::OnUpdateFileSaveUTF32BE(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(GetEditorCtrl()->IsReadOnlyEditor());
}

void CEditorDoc::OnupdateFileSaveAsEncoding(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(GetEditorCtrl()->IsReadOnlyEditor());
}

void CEditorDoc::OnFileSaveAsEncoding()
{
	CCodePageMFCDlg dlg;
	dlg.SetDlgModeReopen(FALSE);
	if (IDOK == dlg.DoModal())
	{
		CString strFileName = GetPathName();
		if (PathFileExists(strFileName))
		{
			// Save document
			if (!OnSaveDocument(strFileName))
			{
				OSUtils::UseAdministrationHandler();
			}
		}
		else
		{
			// Call file save as function
			OnFileSaveAs();
		}
	}
}

// CEditorDoc diagnostics
#ifdef _DEBUG
void CEditorDoc::AssertValid() const
{
	CBaseDoc::AssertValid();
}

void CEditorDoc::Dump(CDumpContext& dc) const
{
	CBaseDoc::Dump(dc);
}
#endif //_DEBUG