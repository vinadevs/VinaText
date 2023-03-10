/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "VinaTextApp.h"
#include "MainFrm.h"
#include "PdfDoc.h"
#include "PdfView.h"
#include "AppUtil.h"
#include "AppSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CPdfView

IMPLEMENT_DYNCREATE(CPdfView, CViewBase)

CPdfView::~CPdfView()
{
}

BEGIN_MESSAGE_MAP(CPdfView, CViewBase)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnDisableUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnDisableUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnDisableUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnDisableUpdate)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPdfView diagnostics

#ifdef _DEBUG
void CPdfView::AssertValid() const
{
	CViewBase::AssertValid();
}

void CPdfView::Dump(CDumpContext& dc) const
{
	CViewBase::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPdfView message handlers

void CPdfView::OnInitialUpdate()
{
	CViewBase::OnInitialUpdate();
	CString strFilePDFPath = m_pDocument->GetPathName();
	if (PathUtils::IsPdfFile(strFilePDFPath))
	{
		m_wndPdf.put_src(strFilePDFPath);
		m_wndPdf.setShowToolbar(TRUE);
		m_wndPdf.setShowScrollbars(TRUE);
		// check last write time point
		UpdateFileLastWriteTime(strFilePDFPath);
	}
}

void CPdfView::OnSetFocus(CWnd * pOldWnd)
{
	CViewBase::OnSetFocus(pOldWnd);
	if (!m_bIsWatchFileProcessing)
	{
		WatchFileSystemState(); // when view is actived, check file status also...
	}
}

void CPdfView::UpdatePreviewFileContent()
{
	OnInitialUpdate();
}

int CPdfView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CViewBase::OnCreate(lpCreateStruct) == -1)
		return -1;
	DWORD style = WS_CHILD | WS_VISIBLE;
	CRect dump(0, 0, 0, 0);
	if (!m_wndPdf.Create(_T("AcrobatWnd"), style, dump, this, IDC_PDFCTRL))
	{
		AfxMessageBox(_T("Please install Adode Acrobat Pdf Reader!"));
		return -1;
	}
	return 0;
}

void CPdfView::OnSize(UINT nType, int cx, int cy)
{
	CViewBase::OnSize(nType, cx, cy);
	m_wndPdf.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CPdfView::OnDisableUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void CPdfView::UpdateFileLastWriteTime(const CString& strFilePath)
{
	if (strFilePath.IsEmpty() || !PathFileExists(strFilePath)) return;
	FILETIME timeStamp = {};
	WIN32_FILE_ATTRIBUTE_DATA attributes;
	if (GetFileAttributesEx(strFilePath, GetFileExInfoStandard, &attributes) != 0)
	{
		timeStamp = attributes.ftLastWriteTime;
	}
	if (CompareFileTime(&m_FileSystemTime, &timeStamp) != 0)
	{
		m_FileSystemTime = timeStamp;
	}
}

int CPdfView::WatchFileSystemState()
{
	m_bIsWatchFileProcessing = TRUE;
	int nFileState = 0;

	CBaseDoc *pDoc = GetBaseDocument();
	ASSERT(pDoc);
	if (!pDoc)
	{
		m_bIsWatchFileProcessing = FALSE;
		return nFileState | FILE_SYSTEM_STATE::FILE_UNCHANGED;
	}

	WIN32_FILE_ATTRIBUTE_DATA attributes;
	CString strFile = pDoc->GetPathName();
	if (strFile.IsEmpty() || (pDoc->IsPreviewMode() && PathFileExists(strFile)))
	{
		m_bIsWatchFileProcessing = FALSE;
		return nFileState | FILE_SYSTEM_STATE::FILE_UNCHANGED;
	}

	if (!PathFileExists(strFile))
	{
		nFileState |= FILE_SYSTEM_STATE::FILE_DELETED;
	}
	else if (GetFileAttributesEx(strFile, GetFileExInfoStandard, &attributes) != 0)
	{
		BOOL bReadOnly = attributes.dwFileAttributes & FILE_ATTRIBUTE_READONLY;

		if (bReadOnly != m_bDocumentReadOnly)
		{
			m_bDocumentReadOnly = bReadOnly;
			nFileState |= FILE_SYSTEM_STATE::FILE_CHANGED_READONLY;
		}

		if (CompareFileTime(&m_FileSystemTime, &attributes.ftLastWriteTime) != 0)
		{
			m_FileSystemTime = attributes.ftLastWriteTime;
			nFileState |= FILE_SYSTEM_STATE::FILE_CONTENT_MODIFIED;
		}
	}

	if (nFileState != 0) // reload file...
	{
		if (nFileState & FILE_SYSTEM_STATE::FILE_DELETED)
		{
			AfxMessageBoxFormat(MB_ICONWARNING | MB_OK, _T("[System Warning] %s has been deleted from file system by an external operation!"), strFile);
			AppUtils::CloseDeletedDocument(this, strFile);
		}
		else
		{
			if (nFileState & FILE_SYSTEM_STATE::FILE_CHANGED_READONLY)
			{
				CString strCurrentTime = OSUtils::DateToCStringABDHMSY(OSUtils::GetCurrentTimeEx());
				if (AppSettingMgr.m_bDisplayMessageBoxForFileChange)
				{
					AfxMessageBox(_T("[System Warning] At ") + strCurrentTime + _T(", ") + strFile + _T(" has changed read only state..."));
				}
				else
				{
					LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [System Warning] At ") + strCurrentTime + _T(", ") + strFile + _T(" has changed read only state..."), BasicColors::orange);
				}
			}
			if (nFileState & FILE_SYSTEM_STATE::FILE_CONTENT_MODIFIED)
			{
			}
		}
	}
	m_bIsWatchFileProcessing = FALSE;
	return nFileState;
}
