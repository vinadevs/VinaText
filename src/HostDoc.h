/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "BaseDoc.h"

class CHostView;

class CHostDoc : public CBaseDoc
{
protected: // create from serialization only
	CHostDoc();
	DECLARE_DYNCREATE(CHostDoc)

	// Overrides
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	CHostView * GetHostView() const;

	// Implementation
public:
	virtual ~CHostDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	DECLARE_MESSAGE_MAP()
};
