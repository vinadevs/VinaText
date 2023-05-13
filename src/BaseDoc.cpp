/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "VinaTextApp.h"
#include "BaseDoc.h"
#include "FileExplorerDoc.h"
#include "AppUtil.h"
#include "MainFrm.h"
#include "RecentCloseFileManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBaseDoc

IMPLEMENT_DYNCREATE(CBaseDoc, CDocument)

BEGIN_MESSAGE_MAP(CBaseDoc, CDocument)
END_MESSAGE_MAP()

// CBaseDoc construction/destruction

CBaseDoc::CBaseDoc() {}

CBaseDoc::~CBaseDoc() {}

BOOL CBaseDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	AppUtils::GetVinaTextApp()->m_bIsReloadByPreviewMode = FALSE;
	return CDocument::OnOpenDocument(lpszPathName);
}

void CBaseDoc::OnCloseDocument() // not for CEditorDoc 
{
	// save recent data
	CString strPathName = GetPathName();
	if (PathFileExists(strPathName))
	{
		RecentCloseMDITabManager.PushTab(strPathName);
	}

	// every data get from document must be done before this...
	CDocument::OnCloseDocument();
	AppUtils::CheckLastOpenDocument();
}

BOOL CBaseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument()) return FALSE;
	return TRUE;
}

BOOL CBaseDoc::IsPreviewMode() const
{
	return m_bIsPreviewMode;
}

void CBaseDoc::SetPreviewMode(BOOL bFlag)
{
	m_bIsPreviewMode = bFlag;
}

BOOL CBaseDoc::PreSaveFile(LPCTSTR lpszPathName)
{
	CString strFilePath(lpszPathName);
	if (strFilePath.IsEmpty()) return FALSE;
	int nPos = strFilePath.ReverseFind('\\');
	if (nPos == -1) return FALSE;
	CString strFileTitle = strFilePath.Mid(nPos + 1);
	SetTitle(strFileTitle.GetBuffer());
	strFileTitle.ReleaseBuffer();
	AppUtils::GetVinaTextApp()->m_bIsSaveDocument = TRUE;
	return TRUE;
}

void CBaseDoc::OnFileSendMailEx()
{
	if (PathUtils::IsBlockFormatFileMailServer(GetPathName()))
	{
		AfxMessageBox(_T("[Warning] This format file has been blocked from mail server. Please try to rename file extention!"));
	}
	OnFileSendMail();
}

// CBaseDoc diagnostics

#ifdef _DEBUG
void CBaseDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBaseDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG