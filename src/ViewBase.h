/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CViewBase view

class CBaseDoc;

class CViewBase : public CView
{
protected:
	CViewBase() {} // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewBase)

	// Overrides
public:
	// interfaces
	virtual void UpdatePreviewFileContent() {}
	virtual void UpdateFileLastWriteTime(const CString& strFilePath) {}
	virtual int  WatchFileSystemState() { return 0; }

protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnDraw(CDC* pDC);
	CBaseDoc * GetBaseDocument() const;

	// Implementation
protected:
	virtual ~CViewBase();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	DECLARE_MESSAGE_MAP()
};
