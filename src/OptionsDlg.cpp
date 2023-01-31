/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "OptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg

IMPLEMENT_DYNAMIC(COptionsDlg, CMFCPropertySheet)

COptionsDlg::COptionsDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
:CMFCPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	SetLook(CMFCPropertySheet::PropSheetLook_Tree, 150 /* Tree control width */);
	SetIconsList(IDB_OPTIONSIMAGES, 16 /* Image width */);

	CMFCPropertySheetCategoryInfo* pRoot = AddTreeCategory(_T("All Settings"), 0, 1);

	AddPageToTree(pRoot, &m_OptionsPageEditorSetting, -1, 2);
	AddPageToTree(pRoot, &m_OptionsPageFileSetting, -1, 2);
	AddPageToTree(pRoot, &m_OptionsPageBuildDebugSetting, -1, 2);
	AddPageToTree(pRoot, &m_OptionsPagePathSetting, -1, 2);
	AddPageToTree(pRoot, &m_OptionsPageTranslateSetting, -1, 2);
	AddPageToTree(pRoot, &m_OptionsPageGeneralSetting1, -1, 2);
	AddPageToTree(pRoot, &m_OptionsPageGeneralSetting2, -1, 2);
}

COptionsDlg::~COptionsDlg()
{
}

BOOL COptionsDlg::OnInitDialog()
{
	CMFCPropertySheet::OnInitDialog();
	auto hCalc = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hCalc, TRUE);
	return TRUE;
}

BEGIN_MESSAGE_MAP(COptionsDlg, CMFCPropertySheet)
END_MESSAGE_MAP()

