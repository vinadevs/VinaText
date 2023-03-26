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

#include "pdf/UXReader/UXReaderMainWindow.h"
#include "pdf/UXReader/UXReaderDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CPdfView

IMPLEMENT_DYNCREATE(CPdfView, CViewBase)

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

BOOL CPdfView::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
		case WM_MOUSEWHEEL:
		{
			if (m_DocumentView != nullptr) m_DocumentView->MouseWheelV(pMsg->wParam, pMsg->lParam);
			return TRUE;
		}
		// add more messages ...
	}
	return CViewBase::PreTranslateMessage(pMsg);
}

void CPdfView::OnInitialUpdate()
{
	CViewBase::OnInitialUpdate();
	CString strFilePDFPath = m_pDocument->GetPathName();
	if (PathUtils::IsPdfFile(strFilePDFPath))
	{
		DWORD style = WS_CHILD | WS_VISIBLE;
		CRect dump(0, 0, 0, 0);
		// try to open with Adode Acrobat Pdf
		m_bIsArobatInstalled = m_wndPdf.Create(_T("AcrobatWnd"), style, dump, this, IDC_PDFCTRL);
		if (m_bIsArobatInstalled)
		{
			m_wndPdf.put_src(strFilePDFPath);
			m_wndPdf.setShowToolbar(TRUE);
			m_wndPdf.setShowScrollbars(TRUE);
		}
		else
		{
			const HCURSOR oldCursor = SetCursor(UXReader::UXReaderSupport::WaitCursor());
			auto document = std::make_shared<UXReader::UXReaderDocument>(strFilePDFPath);
			int errorCode = 0;
			if (document->OpenWithPassword(nullptr, errorCode))
			{
				CRect rectClient;
				GetClientRect(rectClient);
				const int cx = 0; const int cy = 0;
				const int cw = (rectClient.right - rectClient.left);
				const int ch = (rectClient.bottom - rectClient.top);
				m_DocumentView = std::make_unique<UXReader::UXReaderDocumentView>(document);
				if (!m_DocumentView->Create(m_hWnd, cx, cy, cw, ch)) {
					m_DocumentView = NULL;
				}
			}
			SetCursor(oldCursor);
		}
		// check last write time point
		UpdateFileLastWriteTime(strFilePDFPath);
	}
}

void CPdfView::OnSetFocus(CWnd* pOldWnd)
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

void CPdfView::OnSize(UINT nType, int cx, int cy)
{
	CViewBase::OnSize(nType, cx, cy);
	if (m_bIsArobatInstalled)
	{
		m_wndPdf.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
	}
	else
	{
		if (m_DocumentView) m_DocumentView->UpdateWH(cx, cy);
	}
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

	CBaseDoc* pDoc = GetBaseDocument();
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
			return nFileState;
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
