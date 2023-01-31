/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CPdfView view

#include "AdobeAcrobatWrapper.h"
#include "ViewBase.h"

class CPdfDoc;

class CPdfView : public CViewBase
{
protected:
	CPdfView() {} // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPdfView)

	// Attributes
protected:
	CAcrobatActiveXWrapper m_wndPdf;
	FILETIME m_FileSystemTime = {};
	BOOL m_bIsWatchFileProcessing = FALSE;
	BOOL m_bDocumentReadOnly = FALSE;

	// Overrides
public:
	virtual void OnInitialUpdate();
	virtual void UpdatePreviewFileContent();

protected:
	virtual void UpdateFileLastWriteTime(const CString& strFilePath);
	virtual int WatchFileSystemState();

	// Implementation
protected:
	virtual ~CPdfView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	afx_msg void OnSetFocus(CWnd * pOldWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDisableUpdate(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};
