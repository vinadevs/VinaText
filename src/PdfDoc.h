/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "BaseDoc.h"

class CPdfView;

class CPdfDoc : public CBaseDoc
{
protected: // create from serialization only
	CPdfDoc();
	DECLARE_DYNCREATE(CPdfDoc)

	// Overrides
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	CPdfView * GetPdfView() const;
	void ReloadPreviewDocument(const CString& strFilePath);

	// Implementation
public:
	virtual ~CPdfDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	DECLARE_MESSAGE_MAP()
};
