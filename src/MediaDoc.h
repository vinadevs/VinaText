/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "BaseDoc.h"

class CMediaView;

class CMediaDoc : public CBaseDoc
{
protected: // create from serialization only
	CMediaDoc();
	DECLARE_DYNCREATE(CMediaDoc)

	// Overrides
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	CMediaView * GetMediaView() const;
	void ReloadPreviewDocument(const CString& strFilePath);

	// Implementation
public:
	virtual ~CMediaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	DECLARE_MESSAGE_MAP()
};
