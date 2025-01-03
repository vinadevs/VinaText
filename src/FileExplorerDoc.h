/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "BaseDoc.h"

class CFileExplorerView;

class CFileExplorerDoc : public CBaseDoc
{
protected: // create from serialization only
	CFileExplorerDoc();
	DECLARE_DYNCREATE(CFileExplorerDoc)

// Implementation
public:
	virtual ~CFileExplorerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	DECLARE_MESSAGE_MAP()
};


