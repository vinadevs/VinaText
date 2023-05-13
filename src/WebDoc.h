/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

class CWebView;

class CWebDoc : public CDocument
{
protected: // create from serialization only
	CWebDoc();
	DECLARE_DYNCREATE(CWebDoc)

	// Overrides
public:
	virtual void OnCloseDocument();
	CWebView* GetWebView() const;
	HRESULT LoadHTMLContent(CString& strHTMLContent);
	// Implementation
public:
	virtual ~CWebDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	DECLARE_MESSAGE_MAP()
};
