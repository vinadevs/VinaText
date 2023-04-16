/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CMediaView view

#include "CWMPHost.h"
#include "ViewBase.h"

class CMediaDoc;

class CMediaView : public CViewBase
{
protected:
	CMediaView();
	DECLARE_DYNCREATE(CMediaView)

	// Attributes
protected:
	CWMPHost m_wndMWP;
	FILETIME m_FileSystemTime = {};
	BOOL     m_bIsWatchFileProcessing = FALSE;
	BOOL     m_bDocumentReadOnly = FALSE;

public:
	virtual void UpdatePreviewFileContent();

	// Overrides
protected:
	virtual void OnInitialUpdate();
	virtual void UpdateFileLastWriteTime(const CString& strFilePath);
	virtual int WatchFileSystemState();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// Implementation
protected:
	virtual ~CMediaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	afx_msg void OnSetFocus(CWnd * pOldWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDisableUpdate(CCmdUI* pCmdUI);
	afx_msg void OnOptionsShowSystemMenu();
	afx_msg void OnPlayVideo() { m_wndMWP.Play(); }
	afx_msg void OnPauseVideo() { m_wndMWP.Pause(); };
	afx_msg void OnStopVideo() { m_wndMWP.Stop(); };
	afx_msg void OnVolumeUp() { m_wndMWP.VolumeUp(); };
	afx_msg void OnVolumeDown() { m_wndMWP.VolumeDown(); };
	afx_msg void OnNextFrame() { m_wndMWP.NextFrame(); };
	afx_msg void OnPreviousFrame() { m_wndMWP.Stop(); };
	afx_msg void OnUpdatePlayVideo(CCmdUI* pCmdUI) { pCmdUI->Enable(~static_cast<BOOL>(m_wndMWP.IsPlaying())); };
	afx_msg void OnUpdatePauseVideo(CCmdUI* pCmdUI) { pCmdUI->Enable(~static_cast<BOOL>(m_wndMWP.IsPlaying())); };
	DECLARE_MESSAGE_MAP()
};
