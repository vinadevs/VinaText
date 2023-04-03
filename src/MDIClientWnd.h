/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#define MDI_CLIENT_WND_CLASS_NAME _T("CustomMDIClientWnd")

class CMDIClientWnd : public CWnd
{
	DECLARE_DYNAMIC(CMDIClientWnd)

public:
	CMDIClientWnd();
	virtual ~CMDIClientWnd();

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

protected:
	DECLARE_MESSAGE_MAP()
};


