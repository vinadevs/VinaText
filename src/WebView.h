/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include <afxhtml.h>

class CWebDoc;

class CWebView : public CHtmlView
{
protected:
	CWebView();
	DECLARE_DYNCREATE(CWebView)
public:
	CWebDoc* GetWebDocument();
	HRESULT Render(CString& html);

// Implementation
public:
	virtual ~CWebView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in IEDemoView.cpp
inline CWebDoc* CWebView::GetWebDocument()
{
	return (CWebDoc*)m_pDocument;
}
#endif
