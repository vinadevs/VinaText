/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"
#include "MultiDocTemplateEx.h"
#include "HostManager.h"
#include "VinaText_i.h"

#include <memory>

class CUserCustomizeData;

class CVinaTextApp : public CWinAppEx
{
public:
	CVinaTextApp();

public:
	// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(LPMSG pMsg);
	virtual BOOL SaveAllModified();

	CDocument* OnOpenDocument(LPCTSTR lpszPathName);
	CDocument* CreateWebDocument();
	CDocument* CreateNewFileExplorerDocument(const CString& strNavigatePath);
	CDocument* CreateNewHostDocument(const CString& strAppName,
	const CString & strAppPathToHost, const CString & strAppArguments,
		BOOL bRemoveTitleBarWindow = FALSE, BOOL bSilentStartup = FALSE,
		UINT nAppIconID = -1, HostManager::HOST_METHOD HostType = HostManager::HOST_METHOD::USE_ENUMWINDOWS,
		int nWaitTime = 500, const CString& strClassAppName = NULL, BOOL bOpenFileMode = FALSE);

	BOOL SaveRecentFilesData();
	BOOL LoadRecentFilesData();

	afx_msg void OnFileOpen();
	afx_msg void OnFileNewEditor();
	afx_msg void OnNewProjectTemplate();
	afx_msg void OnHelpAppAbout();
	afx_msg void OnAddFolderToWorkSpace();
	afx_msg void OnOpenRecentClosedFile();
	afx_msg void OnOpenAllRecentClosedFile();
	afx_msg void OnClearRecentClosedFile();
	afx_msg void OnSaveFileCryptography();
	afx_msg void OnReadFileCryptography();
	afx_msg void OnUpdateSaveFileCryptography(CCmdUI * pCmdUI);
	afx_msg void OnUpdateReadFileCryptography(CCmdUI * pCmdUI);
	afx_msg void OnUpdateOpenRecentClosedFile(CCmdUI * pCmdUI);

	afx_msg void OnHelpDocumentation();
	afx_msg void OnHelpReportIssue();
	afx_msg void OnHelpReleaseNotes();
	afx_msg void OnHelpKeyboardShortcutsReference();

	// encoding...
	afx_msg void OnFileOpenASCII();
	afx_msg void OnFileOpenUTF8();
	afx_msg void OnFileOpenUTF16LE();
	afx_msg void OnFileOpenUTF16BE();
	afx_msg void OnFileOpenUTF32LE();
	afx_msg void OnFileOpenUTF32BE();
	afx_msg void OnFileOpenAsEncoding();
	afx_msg void OnUpdateFileOpenASCII(CCmdUI * pCmdUI);
	afx_msg void OnUpdateFileOpenUTF8(CCmdUI * pCmdUI);
	afx_msg void OnUpdateFileOpenUTF16LE(CCmdUI * pCmdUI);
	afx_msg void OnUpdateFileOpenUTF16BE(CCmdUI * pCmdUI);
	afx_msg void OnUpdateFileOpenUTF32LE(CCmdUI * pCmdUI);
	afx_msg void OnUpdateFileOpenUTF32BE(CCmdUI * pCmdUI);
	afx_msg void OnUpdateFileOpenAsEncoding(CCmdUI * pCmdUI);

	HINSTANCE  m_hDllEdtior = NULL;
	HINSTANCE  m_hDllLexer = NULL;
	HINSTANCE  m_hDllRichEdit = NULL;
	HostManager::STHostAppInfo m_STHostAppInfo;
	CAtlMap<CString, CString, CStringElementTraits<CString>> m_FileDescriptionData;

	// document templates
	CMultiDocTemplateEx* m_pEditorDocTemplate = NULL;
	CMultiDocTemplateEx* m_pImageDocTemplate = NULL;
	CMultiDocTemplateEx* m_pPdfDocTemplate = NULL;
	CMultiDocTemplateEx* m_pMediaDocTemplate = NULL;
	CMultiDocTemplateEx* m_pHostDocTemplate = NULL;
	CMultiDocTemplateEx* m_pFileExplorerDocTemplate = NULL;
	CMultiDocTemplateEx* m_pWebDocTemplate = NULL;

	// Customize User Data
	std::unique_ptr<CUserCustomizeData> m_userCustomizeData;

	DECLARE_MESSAGE_MAP()
protected:
	BOOL OnAnotherInstanceMessage(LPMSG pMsg);
	BOOL RegisterDocTemplates();
};

extern CVinaTextApp theApp;
