/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "BaseDoc.h"

class CLanguageDatabase;
class CEditorView;
class CEditorCtrl;

class CEditorDoc : public CBaseDoc
{
protected: // create from serialization only
	CEditorDoc();
	virtual ~CEditorDoc();
	DECLARE_DYNCREATE(CEditorDoc)

// Operations
public:
	CEditorView * GetEditorView() const;
	CEditorCtrl *GetEditorCtrl() const;
	CLanguageDatabase* GetDocLanguageDatabase() const;

	void SetSaveDocumentPath(const CString& strSaveDocumentPath);
	void ReloadPreviewDocument(const CString& strFilePath);

// OverrEditors
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();

	// custom save as dialog...
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileSaveAll();

	// encoding...
	afx_msg void OnFileSaveASCII();
	afx_msg void OnFileSaveUTF8();
	afx_msg void OnFileSaveUTF16LE();
	afx_msg void OnFileSaveUTF16BE();
	afx_msg void OnFileSaveUTF32LE();
	afx_msg void OnFileSaveUTF32BE();
	afx_msg void OnFileSaveAsEncoding();
	afx_msg void OnUpdateFileOSaveUTFASCII(CCmdUI * pCmdUI);
	afx_msg void OnUpdateFileSaveUTF8(CCmdUI * pCmdUI);
	afx_msg void OnUpdateFileOSaveUTF16LE(CCmdUI * pCmdUI);
	afx_msg void OnUpdateFileSaveUTF16BE(CCmdUI * pCmdUI);
	afx_msg void OnUpdateFileSaveUTF32LE(CCmdUI * pCmdUI);
	afx_msg void OnUpdateFileSaveUTF32BE(CCmdUI * pCmdUI);
	afx_msg void OnupdateFileSaveAsEncoding(CCmdUI * pCmdUI);

// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	std::unique_ptr<CLanguageDatabase> m_pLangDatabase = NULL;
	CString m_strSaveDocumentPath;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};