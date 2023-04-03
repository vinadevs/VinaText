/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "ProjectTempateCreatorDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "TemplateCreator.h"
#include "AppUtil.h"

// CProjectTempateCreator dialog

static CString g_strLatestFileName;

IMPLEMENT_DYNAMIC(CProjectTempateCreator, CDialogEx)

CProjectTempateCreator::CProjectTempateCreator(const CString& strFolder, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PROJECT_TEMPLATE, pParent)
{
	m_strFolder = strFolder;
}

CProjectTempateCreator::~CProjectTempateCreator()
{
}

void CProjectTempateCreator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PROJECT_TEMPLATE_LANGUAGE, m_ComboProjectLanguage);
	DDX_Control(pDX, IDC_COMBO_PROJECT_TEMPLATE_TYPE, m_ComboProjectType);
	DDX_Control(pDX, IDC_EDIT_PROJECT_TEMPLATE_LOCATION, m_EditProjectLocation);
	DDX_Control(pDX, IDC_EDIT_PROJECT_TEMPLATE_PROJECT_NAME, m_EditProjectName);
	DDX_Text(pDX, IDC_EDIT_PROJECT_TEMPLATE_LOCATION, m_strFolder);
}

BOOL CProjectTempateCreator::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	auto hCalc = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hCalc, TRUE);

	// enable the browse button and put the control in file browse mode
	m_EditProjectLocation.EnableFolderBrowseButton();
	m_EditProjectName.SetWindowTextW(g_strLatestFileName);

	InitComboProjectLanguage();
	InitComboProjectType();

	UpdateData(FALSE);

	SET_FOCUS_ON_CHILD_DLG_CONTROL(m_EditProjectName);

	return FALSE;
}

BEGIN_MESSAGE_MAP(CProjectTempateCreator, CDialogEx)
	ON_BN_CLICKED(IDOK, &CProjectTempateCreator::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_PROJECT_TEMPLATE_TYPE, OnCbnSelchangeComboProjectType)
	ON_CBN_SELCHANGE(IDC_COMBO_PROJECT_TEMPLATE_LANGUAGE, OnCbnSelchangeComboProjectLanguage)
END_MESSAGE_MAP()

// CProjectTempateCreator message handlers

void CProjectTempateCreator::InitComboProjectLanguage()
{
	m_ComboProjectLanguage.ResetContent();
	m_ComboProjectLanguage.InsertString(0, _T("Python"));
	m_ComboProjectLanguage.InsertString(1, _T("C"));
	m_ComboProjectLanguage.InsertString(2, _T("C++"));
	m_ComboProjectLanguage.InsertString(3, _T("JavaScript"));
	m_ComboProjectLanguage.InsertString(4, _T("Java"));
	m_ComboProjectLanguage.InsertString(5, _T("C#"));
	m_ComboProjectLanguage.InsertString(6, _T("Visual Basic"));
	m_ComboProjectLanguage.InsertString(7, _T("Go Lang"));
	m_ComboProjectLanguage.InsertString(8, _T("Rust"));
	m_ComboProjectLanguage.InsertString(9, _T("Pascal"));
	m_ComboProjectLanguage.InsertString(10, _T("PHP"));
	m_ComboProjectLanguage.SetCurSel(0);
}

void CProjectTempateCreator::InitComboProjectType()
{
	m_ComboProjectType.ResetContent();
	m_ComboProjectType.InsertString(0, _T("Empty File Template"));
	m_ComboProjectType.InsertString(1, _T("Function File Template"));
	m_ComboProjectType.InsertString(2, _T("Only Main Template"));
	m_ComboProjectType.SetCurSel(0);
}

void CProjectTempateCreator::OnCbnSelchangeComboProjectLanguage()
{
}

void CProjectTempateCreator::OnCbnSelchangeComboProjectType()
{
}

void CProjectTempateCreator::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_EditProjectName.GetWindowText(g_strLatestFileName);

	if (g_strLatestFileName.IsEmpty())
	{
		AfxMessageBox(_T("[Error] File name is invalid!"));
		return;
	}

	if (!PathFileExists(m_strFolder))
	{
		AfxMessageBox(_T("[Error] File location is invalid!"));
		return;
	}

	FILE_TEMPLATE_PARAM param;
	//////////////////////////
	param._strFileLocation = m_strFolder;
	//////////////////////////
	param._strFileName = g_strLatestFileName;
	//////////////////////////
	int nSel = m_ComboProjectType.GetCurSel();
	if (nSel == 0)
	{
		param._templateType = FILE_TEMPLATE_TYPE::Template_Empty;
	}
	else if (nSel == 1)
	{
		param._templateType = FILE_TEMPLATE_TYPE::Template_Function;
	}
	else if (nSel == 2)
	{
		param._templateType = FILE_TEMPLATE_TYPE::Template_OnlyMain;
	}
	//////////////////////////
	int nSelLanguage = m_ComboProjectLanguage.GetCurSel();
	if (nSelLanguage == 0)
	{
		param._targetLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON;
	}
	else if (nSelLanguage == 1)
	{
		param._targetLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C;
	}
	else if (nSelLanguage == 2)
	{
		param._targetLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP;
	}
	else if (nSelLanguage == 3)
	{
		param._targetLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT;
	}
	else if (nSelLanguage == 4)
	{
		param._targetLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA;
	}
	else if (nSelLanguage == 5)
	{
		param._targetLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CSHAPE;
	}
	else if (nSelLanguage == 6)
	{
		param._targetLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VISUALBASIC;
	}
	else if (nSelLanguage == 7)
	{
		param._targetLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_GOLANG;
	}
	else if (nSelLanguage == 8)
	{
		param._targetLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUST;
	}
	else if (nSelLanguage == 9)
	{
		param._targetLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL;
	}
	else if (nSelLanguage == 10)
	{
		param._targetLanguage = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PHP;
	}
	//////////////////////////
	if (TemplateCreator::GenerateFile(param))
	{
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [Template Creator] File generation succeed..."));
		CDialogEx::OnOK();
	}
	else
	{
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [Template Creator] File generation failed..."));
	}
}
