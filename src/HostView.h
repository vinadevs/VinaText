/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CHostView view

class CHostView : public CView
{
protected:
	CHostView() {} // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHostView)

	// Attributes
protected:
	// external process
	HANDLE CreateWin32ProcessWithHWND(const CString& strAppPathToHost, const CString& strAppArguments, BOOL bOpenFileMode, int nWaitTime, BOOL bSilentStartup, HostManager::HOST_METHOD HostMethod, const CString& strClassName);
	HANDLE CreateWin32ProcessJob(const CString& strJobName);
	void TerminateHostProcess();
	HANDLE m_hProcess = NULL; // app process handle
	HANDLE m_hJob = NULL; // app job handle
	HWND m_hWWND = NULL; // window handle
	DWORD m_dwThreadId = 0;

	BOOL m_bIsWatchFileProcessing = FALSE;
	BOOL m_bDocumentReadOnly = FALSE;
	FILETIME m_FileSystemTime = {};

	// Overrides
public:
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* pDC);
	int WatchFileSystemState();
	void UpdateFileLastWriteTime(const CString& strFilePath);

	int CheckThreadID(HWND hwnd);

	// Implementation
protected:
	virtual ~CHostView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDisableUpdate(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd * pOldWnd);
	DECLARE_MESSAGE_MAP()
};
