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
#include "afxdatarecovery.h"
#include "MainFrm.h"
#include "ImageDoc.h"
#include "ImageView.h"
#include "AppUtil.h"
#include "AppSettings.h"
#include "FileBrowser.h"
#include "TemporarySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageDoc

IMPLEMENT_DYNCREATE(CImageDoc, CBaseDoc)

BEGIN_MESSAGE_MAP(CImageDoc, CBaseDoc)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE_ALL, OnFileSaveAll)
END_MESSAGE_MAP()

// CImageDoc construction/destruction

CImageDoc::CImageDoc() {}

CImageDoc::~CImageDoc() {}

BOOL CImageDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	return CBaseDoc::OnOpenDocument(lpszPathName);
}

BOOL CImageDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CDataRecoveryHandler* autohandler = AfxGetApp()->GetDataRecoveryHandler();
	CString autosavepath = autohandler->GetAutosavePath();
	if (CString(lpszPathName).Left(autosavepath.GetLength()).CompareNoCase(autosavepath) == 0)
	{
		// autosaving - just call the default
		return CBaseDoc::OnSaveDocument(lpszPathName);
	}
	// customize save file
	CImageView *pImageView = GetImageView();
	if (pImageView != NULL)
	{
		PreprocessSaveFile(lpszPathName);
		BOOL bRet = pImageView->SaveImage(lpszPathName);
		if (bRet)
		{
			SetModifiedFlag(FALSE);
		}
		return bRet;
	}
	return FALSE;
}

CImageView* CImageDoc::GetImageView() const
{
	POSITION pos = GetFirstViewPosition();
	CImageView* pView = (CImageView*)GetNextView(pos);
	if (pView)
	{
		return pView;
	}
	else
	{
		ASSERT(pView);
		return NULL;
	}
}

void CImageDoc::ReloadPreviewDocument(const CString & strFilePath)
{
	if (PathFileExists(strFilePath))
	{
		SetPathName(strFilePath);
		TemporarySettings.m_bIsReloadByPreviewMode = TRUE;
		GetImageView()->UpdatePreviewFileContent();
		TemporarySettings.m_bIsReloadByPreviewMode = FALSE;
	}
}

// CImageDoc diagnostics

#ifdef _DEBUG
void CImageDoc::AssertValid() const
{
	CBaseDoc::AssertValid();
}

void CImageDoc::Dump(CDumpContext& dc) const
{
	CBaseDoc::Dump(dc);
}
#endif //_DEBUG

void CImageDoc::SetSaveDocumentPath(const CString& strSaveDocumentPath)
{
	m_strSaveDocumentPath = strSaveDocumentPath;
}

void CImageDoc::OnFileSave()
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

void CImageDoc::OnFileSaveAs()
{
	CString strTitle = GetTitle();
	strTitle.Replace(_T("*"), _T(""));

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

	char strFilter[] = { "All files (*.*) | *.*|" 
						"JPEG files (*.jpg;*.jpeg;*.jpe;*.jfif) | *.jpg;*.jpeg;*.jpe;*.jfif|"
						"BMP files (*.bmp;*.dib;*.rle) | *.bmp;*.dib;*.rle|"
						"PNG files (*.png) | *.png|"
						"TIFF files (*.tif;*.tiff) | *.tif;*.tiff|"
						"GIF files (*.gif) | *.gif|"};

	// Create a file save as dialog
	CImageSaveDialog fdSaveAs(FALSE, NULL, strTitle.Trim(), OFN_OVERWRITEPROMPT, CString(strFilter));

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
			SetModifiedFlag(FALSE);
			// reveal in explorer
			AppUtils::GetMainFrame()->RevealInExplorerWindow(strFileName);
		}
		else
		{
			OSUtils::UseAdministrationHandler();
		}
	}
	m_strSaveDocumentPath.Empty();
}

void CImageDoc::OnFileSaveAll()
{
	AppUtils::SaveAllModifiedDocuments();
}