/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "BaseDoc.h"

class CImageView;

class CImageDoc : public CBaseDoc
{
protected: // create from serialization only
	CImageDoc();
	DECLARE_DYNCREATE(CImageDoc)

// Overrides
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	CImageView * GetImageView() const;
	void ReloadPreviewDocument(const CString& strFilePath);
	void SetSaveDocumentPath(const CString & strSaveDocumentPath);

// Implementation
public:
	virtual ~CImageDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	// custom save as dialog...
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileSaveAll();

	DECLARE_MESSAGE_MAP()

	CString m_strSaveDocumentPath;
};