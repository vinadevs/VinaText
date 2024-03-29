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
 : CMultiDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass) {}

// customize for recent file, preview with very first file
CDocument* CMultiDocTemplateEx::OpenDocumentFile(LPCTSTR lpszPathName, BOOL bAddToMRU, BOOL bMakeVisible)
{
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
	// Open text file
	if (m_docList.GetCount() == 1)
	{
		CDocument* pDocument = (CDocument*)m_docList.GetHead();
		if (lpszPathName != NULL && pDocument && pDocument->GetPathName().IsEmpty() && !pDocument->IsModified())
		{
			CWaitCursor wait;
			if (!pDocument->OnOpenDocument(lpszPathName))
			{
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
	return theApp.m_pEditorDocTemplate->OpenNewDocument(lpszPathName, TRUE, TRUE);
}

 CDocument * CMultiDocTemplateEx::OpenNewDocument(LPCTSTR lpszPathName, BOOL bAddToMRU, BOOL bMakeVisible)
{
	if (lpszPathName != NULL && !PathFileExists(lpszPathName))
	{
		if (AppSettingMgr.m_bWarningForFileNotExist)
		{
			CString strMessage = _T("[Path Error] File \"%s\" does not exist. Do you want to create it?");
			strMessage.Format(strMessage, lpszPathName);
			if (IDYES == AfxMessageBox(strMessage, MB_YESNO | MB_ICONWARNING))
			{
				if (!PathUtils::CreateNewEmptyFile(lpszPathName))
				{
					return NULL;
				}
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			return NULL;
		}
	}
	return CMultiDocTemplate::OpenDocumentFile(lpszPathName, bAddToMRU, bMakeVisible);
} 
