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
#include "MediaDoc.h"
#include "MediaView.h"
#include "AppUtil.h"
#include "AppSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CMediaView

IMPLEMENT_DYNCREATE(CMediaView, CViewBase)

CMediaView::CMediaView()
{
	m_bIsWatchFileProcessing = FALSE;
	m_bDocumentReadOnly = FALSE;
}

CMediaView::~CMediaView()
{
}

BEGIN_MESSAGE_MAP(CMediaView, CViewBase)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()

	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnDisableUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnDisableUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnDisableUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnDisableUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnDisableUpdate)

	ON_COMMAND(ID_MEDIA_PLAY, OnPlayVideo)
	ON_COMMAND(ID_MEDIA_PAUSE, OnPauseVideo)
	ON_COMMAND(ID_MEDIA_STOP, OnStopVideo)
	ON_COMMAND(ID_MEDIA_VOLUME_UP, OnVolumeUp)
	ON_COMMAND(ID_MEDIA_VOLUME_DOWN, OnVolumeDown)
	ON_COMMAND(ID_MEDIA_NEXT_FRAME, OnNextFrame)
	ON_COMMAND(ID_MEDIA_PREVIOUS_FRAME, OnPreviousFrame)
	ON_UPDATE_COMMAND_UI(ID_MEDIA_PLAY, OnUpdatePlayVideo)
	ON_UPDATE_COMMAND_UI(ID_MEDIA_PAUSE, OnUpdatePauseVideo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMediaView diagnostics

#ifdef _DEBUG
void CMediaView::AssertValid() const
{
	CViewBase::AssertValid();
}

void CMediaView::Dump(CDumpContext& dc) const
{
	CViewBase::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMediaView message handlers

void CMediaView::OnInitialUpdate()
{
	CViewBase::OnInitialUpdate();
	CString strFileMediaPath = m_pDocument->GetPathName();
	if (PathUtils::IsMediaFile(strFileMediaPath))
	{
		auto startMeasureTime = OSUtils::StartBenchmark();
		if (!m_wndMWP.OpenMediaFile(ATL::CComBSTR(strFileMediaPath)))
		{
			AfxMessageBox(_T("[Media Error] Can not open this file!"));
			return;
		}
		if (!AppUtils::GetVinaTextApp()->m_bIsReloadByPreviewMode)
		{
			CString strMsg = AfxCStringFormat(_T("> [Load File] %s - timelapse: "), strFileMediaPath);
			OSUtils::LogStopBenchmark(LOG_TARGET::MESSAGE_WINDOW, startMeasureTime, strMsg);
		}
		// check last write time point
		UpdateFileLastWriteTime(strFileMediaPath);
	}
}

void CMediaView::OnSetFocus(CWnd * pOldWnd)
{
	CViewBase::OnSetFocus(pOldWnd);
	if (!m_bIsWatchFileProcessing)
	{
		WatchFileSystemState(); // when view is actived, check file status also...
	}
}

void CMediaView::UpdatePreviewFileContent()
{
	OnInitialUpdate();
}

int CMediaView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CViewBase::OnCreate(lpCreateStruct) == -1)
		return -1;
	DWORD style = WS_CHILD | WS_VISIBLE;
	CRect dump(0, 0, 0, 0);
	if (!m_wndMWP.Create(GetSafeHwnd(), dump, L"WMP Host Container", style, 0, (UINT)0))
	{
		AfxMessageBox(_T("[Media Error] Can not initialize Window Media Player!"));
		return -1;
	}
	return 0;
}

void CMediaView::OnSize(UINT nType, int cx, int cy)
{
	CViewBase::OnSize(nType, cx, cy);
	m_wndMWP.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CMediaView::OnDisableUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void CMediaView::UpdateFileLastWriteTime(const CString& strFilePath)
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

int CMediaView::WatchFileSystemState()
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

void CMediaView::OnOptionsShowSystemMenu()
{
	CString strPathName = m_pDocument->GetPathName();
	if (!PathFileExists(strPathName)) return;
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;
	pFrame->GetFileExplorerCtrl().ShowExplorerShellContextMenu(strPathName);
}

BOOL CMediaView::PreTranslateMessage(MSG * pMsg)
{
	switch (pMsg->message)
	{
	case WM_RBUTTONDOWN:
	{
		if ((GetKeyState(VK_SHIFT) & 0x8000))
		{
			OnOptionsShowSystemMenu();
			return TRUE;
		}
		break;
	}
	case WM_KEYDOWN:
	{
		if (AfxGetMainWnd()->PreTranslateMessage(pMsg))
		{
			return TRUE;
		}
		else
		{
			switch (pMsg->wParam)
			{
			case VK_LEFT:
			{
				m_wndMWP.PrevFrame();
				return TRUE;
			}
			break;
			case VK_RIGHT:
			{
				m_wndMWP.NextFrame();
				return TRUE;
			}
			break;
			case VK_SPACE:
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000))
				{
					m_wndMWP.Stop();
					return TRUE;
				}
				else
				{
					if (m_wndMWP.IsPlaying())
					{
						m_wndMWP.Pause();
					}
					else
					{
						m_wndMWP.Play();
					}
					return TRUE;
				}
			}
			break;
			}
		}
		break;
	}
	case WM_MOUSEWHEEL:
	{
		short sDelta = GET_WHEEL_DELTA_WPARAM(pMsg->wParam);
		if (sDelta > 0) // wheel mouse up
		{
			m_wndMWP.VolumeUp();
		}
		else
		{
			m_wndMWP.VolumeDown();
		}
		return TRUE;
		break;
	}
	}
	return CViewBase::PreTranslateMessage(pMsg);
}
