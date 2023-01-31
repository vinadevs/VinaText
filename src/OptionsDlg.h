/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "OptionsPages.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg

class COptionsDlg : public CMFCPropertySheet
{
	DECLARE_DYNAMIC(COptionsDlg)

// Construction
public:
	COptionsDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	COptionsPageEditorSetting  m_OptionsPageEditorSetting;
	COptionsPageFileSetting m_OptionsPageFileSetting;
	COptionsPageBuildDebugSetting m_OptionsPageBuildDebugSetting;
	COptionsPagePathSetting m_OptionsPagePathSetting;
	COptionsPageTranslateSetting m_OptionsPageTranslateSetting;
	COptionsPageGeneralSetting1 m_OptionsPageGeneralSetting1;
	COptionsPageGeneralSetting2 m_OptionsPageGeneralSetting2;

// Implementation
public:
	virtual ~COptionsDlg();
	virtual BOOL OnInitDialog();

protected:
	DECLARE_MESSAGE_MAP()
};

