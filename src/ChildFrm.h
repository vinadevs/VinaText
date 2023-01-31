/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:

// Operations
public:

// OverrEditors
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL CanShowOnTaskBarTabs() override;
	virtual void ActivateFrame(int nCmdShow = -1);
	virtual LPCTSTR GetDocumentName(CObject** pObj);

	BOOL IsEditorFrame();
	BOOL IsPdfFrame();
	BOOL IsImageFrame();
	BOOL IsMediaFrame();
	BOOL IsHostFrame();
	BOOL IsFileExplorerFrame();

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};
