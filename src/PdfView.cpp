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
#include "TemporarySettings.h"

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
	
	ON_COMMAND(ID_PDF_FIND_TEXT, OnFindTextPdf)
	ON_COMMAND(ID_PDF_GOTO_PAGE, OnGotoPagePdf)
	ON_COMMAND(ID_PDF_PAGING_DECREMENT, OnPageUpPdf)
	ON_COMMAND(ID_PDF_PAGING_INCREMENT, OnPageDownPdf)
	ON_COMMAND(ID_PDF_MINIMUM_DOCUMENT, OnFirstPagePdf)
	ON_COMMAND(ID_PDF_MAXIMUM_DOCUMENT, OnLastPagePagePdf)
	ON_COMMAND(ID_PDF_ZOOM_INCREMENT, OnZoomInPdf)
	ON_COMMAND(ID_PDF_ZOOM_DECREMENT, OnZoomOutPdf)
	ON_COMMAND(ID_PDF_ZOOM_FIT_WIDTH, OnZoomFitPdf)
	ON_COMMAND(ID_PDF_ZOOM_ONE_TO_ONE, OnZoomActualPdf)

	ON_UPDATE_COMMAND_UI(ID_PDF_PAGING_DECREMENT, OnUpdatePageUpPdf)
	ON_UPDATE_COMMAND_UI(ID_PDF_PAGING_INCREMENT, OnUpdatePageDownPdf)
	ON_UPDATE_COMMAND_UI(ID_PDF_ZOOM_FIT_WIDTH, OnUpdateZoomFitPdf)
	ON_UPDATE_COMMAND_UI(ID_PDF_ZOOM_ONE_TO_ONE, OnUpdateZoomActualPdf)
	ON_UPDATE_COMMAND_UI(ID_PDF_MINIMUM_DOCUMENT, OnUpdateFirstPagePdf)
	ON_UPDATE_COMMAND_UI(ID_PDF_MAXIMUM_DOCUMENT, OnUpdateLastPagePdf)
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
		case WM_KEYDOWN:
		{
			switch (pMsg->wParam)
			{
				case VK_PRIOR:
				{
					OnPageUpPdf();
					return TRUE;
				}
				case VK_NEXT:
				{
					OnPageDownPdf();
					return TRUE;
				}
				case VK_HOME:
				{
					OnFirstPagePdf();
					return TRUE;
				}
				case VK_END:
				{
					OnLastPagePagePdf();
					return TRUE;
				}
				case VK_UP:
				{
					OnScrollUpPdf();
					return TRUE;
				}
				case VK_DOWN:
				{
					OnScrollDownPdf();
					return TRUE;
				}
				case VK_LEFT:
				{
					OnScrollLeftPdf();
					return TRUE;
				}
				case VK_RIGHT:
				{
					OnScrollRightPdf();
					return TRUE;
				}
				case 'G':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnGotoPagePdf();
						return TRUE;
					}
				}
				break;
				case 'F':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnFindTextPdf();
						return TRUE;
					}
				}
				break;
				case 'J':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnZoomFitPdf();
						return TRUE;
					}
				}
				break;
				case 'K':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnZoomActualPdf();
						return TRUE;
					}
				}
				break;
				case VK_SPACE:
				{
					return TRUE;
				}
				break;
			}
			break;
		}
		case WM_MOUSEWHEEL:
		{
			if (m_DocumentView != nullptr) m_DocumentView->MouseWheelV(pMsg->wParam, pMsg->lParam);
			return TRUE;
		}
		case WM_MOUSEHWHEEL:
		{
			if (m_DocumentView != nullptr) m_DocumentView->MouseWheelH(pMsg->wParam, pMsg->lParam);
			return TRUE;
		}
		// add more messages ...
	}
	return CViewBase::PreTranslateMessage(pMsg);
}

static CString PDFErrorString[] = {
	_T("No error."),
	_T("Unknown error."),
	_T("File not found or could not be opened."),
	_T("File not in PDF format or corrupted."),
	_T("Password required or incorrect password."),
	_T("Unsupported security scheme."),
	_T("Page not found or content error."),
	_T("The requested operation cannot be completed due to a license restrictions.")
};

void CPdfView::OnInitialUpdate()
{
	CViewBase::OnInitialUpdate();
	CString strFilePDFPath = m_pDocument->GetPathName();
	if (PathUtils::IsPdfFile(strFilePDFPath))
	{
		auto startMeasureTime = OSUtils::StartBenchmark();
		DWORD style = WS_CHILD | WS_VISIBLE;
		CRect dump(0, 0, 0, 0);
		// try to open with Adode Acrobat Pdf first
		m_bIsArobatInstalled = m_wndPdf.Create(_T("AcrobatWnd"), style, dump, this, IDC_PDFCTRL);
		if (m_bIsArobatInstalled)
		{
			m_wndPdf.put_src(strFilePDFPath);
			m_wndPdf.setShowToolbar(TRUE);
			m_wndPdf.setShowScrollbars(TRUE);
		}
		else // if Adode Acrobat is not available then we use PDFium
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
				if (m_DocumentView) // preview mode
				{
					m_DocumentView->Destroy();
					m_DocumentView.reset(nullptr);
				}
				m_DocumentView = std::make_unique<UXReader::UXReaderDocumentView>(document);
				if (!m_DocumentView->Create(m_hWnd, cx, cy, cw, ch)) {
					m_DocumentView = NULL;
				}
			}
			else {
				AfxMessageBoxFormat(MB_ICONWARNING, _T("[PDF Error] %s"), PDFErrorString[errorCode]);
			}
			SetCursor(oldCursor);
		}
		if (!TemporarySettings.m_bIsReloadByPreviewMode)
		{
			CString strMsg = AfxCStringFormat(_T("> [Load File] %s - timelapse: "), strFilePDFPath);
			OSUtils::LogStopBenchmark(LOG_TARGET::MESSAGE_WINDOW, startMeasureTime, strMsg);
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

void CPdfView::OnFindTextPdf()
{
	if (m_DocumentView && m_DocumentView->CanSearchTextFocus())
		m_DocumentView->SearchTextFocus();
}

void CPdfView::OnGotoPagePdf()
{
	if (m_DocumentView && m_DocumentView->CanPageNumberFocus())
		m_DocumentView->PageNumberFocus();
}

void CPdfView::OnPageUpPdf()
{
	if (m_DocumentView && m_DocumentView->CanPageScrollDecrementY())
		m_DocumentView->PageScrollDecrementY();
}

void CPdfView::OnPageDownPdf()
{
	if (m_DocumentView && m_DocumentView->CanPageScrollIncrementY())
		m_DocumentView->PageScrollIncrementY();
}

void CPdfView::OnFirstPagePdf()
{
	if (m_DocumentView && m_DocumentView->CanGotoMinimumDocumentY())
		m_DocumentView->GotoMinimumDocumentY();
}

void CPdfView::OnLastPagePagePdf()
{
	if (m_DocumentView && m_DocumentView->CanGotoMaximumDocumentY())
		m_DocumentView->GotoMaximumDocumentY();
}

void CPdfView::OnZoomInPdf()
{
	if (m_DocumentView && m_DocumentView->CanZoomIncrement())
		m_DocumentView->ZoomIncrement();
}

void CPdfView::OnZoomOutPdf()
{
	if (m_DocumentView && m_DocumentView->CanZoomDecrement())
		m_DocumentView->ZoomDecrement();
}

void CPdfView::OnZoomFitPdf()
{
	if (m_DocumentView && m_DocumentView->CanZoomFitWidth())
		m_DocumentView->ZoomFitWidth();
}

void CPdfView::OnZoomActualPdf()
{
	if (m_DocumentView && m_DocumentView->CanZoomOneToOne())
		m_DocumentView->ZoomOneToOne();
}

void CPdfView::OnScrollUpPdf()
{
	if (m_DocumentView && m_DocumentView->CanLineScrollDecrementY())
		m_DocumentView->LineScrollDecrementY();
}

void CPdfView::OnScrollDownPdf()
{
	if (m_DocumentView && m_DocumentView->CanLineScrollIncrementY())
		m_DocumentView->LineScrollIncrementY();
}

void CPdfView::OnScrollLeftPdf()
{
	if (m_DocumentView && m_DocumentView->CanLineScrollDecrementX())
		m_DocumentView->LineScrollDecrementX();
}

void CPdfView::OnScrollRightPdf()
{
	if (m_DocumentView && m_DocumentView->CanLineScrollIncrementX())
		m_DocumentView->LineScrollIncrementX();
}

void CPdfView::OnUpdatePageUpPdf(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_DocumentView && m_DocumentView->CanPageScrollDecrementY());
}

void CPdfView::OnUpdatePageDownPdf(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_DocumentView && m_DocumentView->CanPageScrollIncrementY());
}

void CPdfView::OnUpdateZoomFitPdf(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_DocumentView && m_DocumentView->CanZoomFitWidth());
}

void CPdfView::OnUpdateZoomActualPdf(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_DocumentView && m_DocumentView->CanZoomOneToOne());
}

void CPdfView::OnUpdateFirstPagePdf(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_DocumentView && m_DocumentView->CanGotoMinimumDocumentY());
}

void CPdfView::OnUpdateLastPagePdf(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_DocumentView && m_DocumentView->CanGotoMaximumDocumentY());
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
