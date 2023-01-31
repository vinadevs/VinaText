/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

class CBaseDoc : public CDocument
{
protected: // create from serialization only
	CBaseDoc();
	DECLARE_DYNCREATE(CBaseDoc)

	// Overrides
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnNewDocument();
	virtual void OnCloseDocument();
	BOOL IsPreviewMode() const;
	void SetPreviewMode(BOOL bFlag);
	BOOL PreSaveFile(LPCTSTR lpszPathName);
	void OnFileSendMailEx(); // enable email

	// Implementation
public:
	virtual ~CBaseDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	DECLARE_MESSAGE_MAP()
protected:
	BOOL m_bIsPreviewMode = FALSE; // for control preview file mode
};
