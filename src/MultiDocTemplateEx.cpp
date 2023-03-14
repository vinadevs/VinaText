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
#include "AppUtil.h"
#include "PathUtil.h"
#include "OSUtil.h"
#include "MultiDocTemplateEx.h"
#include "HostManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace HostManager;

CMultiDocTemplateEx::CMultiDocTemplateEx(UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass)
 : CMultiDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass)
{
}

CMultiDocTemplateEx::~CMultiDocTemplateEx()
{
}

// customize for recent file, preview with very first file
CDocument* CMultiDocTemplateEx::OpenDocumentFile(LPCTSTR lpszPathName, BOOL bAddToMRU, BOOL bMakeVisible)
{
	if (m_docList.GetCount() == 1)
	{
		CDocument* pDocument = (CDocument*)m_docList.GetHead();
		if (lpszPathName != NULL && pDocument && pDocument->GetPathName().IsEmpty() && !pDocument->IsModified())
		{
			CWaitCursor wait;
			if (!pDocument->OnOpenDocument(lpszPathName))
			{
				// user has be alerted to what failed in OnOpenDocument
				TRACE0("CDocument::OnOpenDocument returned FALSE.\n");
				return NULL;
			}
			CBaseDoc* pBaseDoc = dynamic_cast<CBaseDoc*>(pDocument);
			if (pBaseDoc)
			{
				pBaseDoc->SetPreviewMode(TRUE);
			}
			pDocument->SetPathName(lpszPathName);
			POSITION pos = pDocument->GetFirstViewPosition();
			CView* pView = pDocument->GetNextView(pos);
			ASSERT(pView); if (!pView) return NULL;
			CFrameWnd* pFrame = pView->GetParentFrame();
			ASSERT(pFrame); if (!pFrame) return NULL;
			InitialUpdateFrame(pFrame, pDocument); // will call CView::OnInitialUpdate()
			return pDocument;
		}
	}
	if (PathUtils::IsImageFile(lpszPathName))
	{
		// Open image file
		return theApp.m_pImageDocTemplate->OpenNewDocument(lpszPathName, TRUE, TRUE);
	}
	else if (PathUtils::IsPdfFile(lpszPathName))
	{
		// Open pdf file
		return theApp.m_pPdfDocTemplate->OpenNewDocument(lpszPathName, TRUE, TRUE);
	}
	else if (PathUtils::IsMediaFile(lpszPathName))
	{
		// Open media file
		return theApp.m_pMediaDocTemplate->OpenNewDocument(lpszPathName, TRUE, TRUE);
	}
	else
	{
		// Open text file
		return theApp.m_pEditorDocTemplate->OpenNewDocument(lpszPathName, TRUE, TRUE);
	}
}

 CDocument * CMultiDocTemplateEx::OpenNewDocument(LPCTSTR lpszPathName, BOOL bAddToMRU, BOOL bMakeVisible)
{
	return CMultiDocTemplate::OpenDocumentFile(lpszPathName, bAddToMRU, bMakeVisible);
	/*if (PathUtils::IsOfficePptFile(lpszPathName))
	{
		// Open office ppt
		CString strMSPPTPath = OSUtils::GetRegistryAppPath(L"POWERPNT.EXE");
		if (!PathFileExists(strMSPPTPath))
		{
			AfxMessageBox(_T("[Host Error] Can not found Microsoft Powerpoint on this PC!")); return NULL;
		}
		return HostApplicaton(HOST_APP_TYPE::MS_OFFICE_PPT, strMSPPTPath, lpszPathName, TRUE);
	}
	else if (PathUtils::IsOfficeExcelFile(lpszPathName))
	{
		// Open office excel
		CString strMSExcelPath = OSUtils::GetRegistryAppPath(L"EXCEL.EXE");
		if (!PathFileExists(strMSExcelPath))
		{
			AfxMessageBox(_T("[Host Error] Can not found Microsoft Excel on this PC!")); return NULL;
		}
		return HostApplicaton(HOST_APP_TYPE::MS_OFFICE_EXCEL, strMSExcelPath, lpszPathName, TRUE);
	}
	else if (PathUtils::IsOfficeWordFile(lpszPathName))
	{
		// Open office word
		CString strMSWordPath = OSUtils::GetRegistryAppPath(L"WINWORD.EXE");
		if (!PathFileExists(strMSWordPath))
		{
			AfxMessageBox(_T("[Host Error] Can not found Microsoft Word on this PC!")); return NULL;
		}
		return HostApplicaton(HOST_APP_TYPE::MS_OFFICE_WORD, strMSWordPath, lpszPathName, TRUE);
	}
	else return CMultiDocTemplate::OpenDocumentFile(lpszPathName, bAddToMRU, bMakeVisible);*/
} 
