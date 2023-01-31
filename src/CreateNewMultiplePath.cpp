/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "CreateNewMultiplePath.h"
#include "afxdialogex.h"
#include "AppUtil.h"
#include "PathUtil.h"
#include "OSUtil.h"

// CCreateNewMultiplePathDlg dialog

IMPLEMENT_DYNAMIC(CCreateNewMultiplePathDlg, CDlgBase)

CCreateNewMultiplePathDlg::CCreateNewMultiplePathDlg(CWnd* pParent /*=NULL*/)
	: CDlgBase(IDD_CREATE_NEW_MULTIPLE, pParent)
	, m_bOverwriteFileIfExisted(FALSE)
{
}

CCreateNewMultiplePathDlg::~CCreateNewMultiplePathDlg()
{
}

void CCreateNewMultiplePathDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILE_DATA_PATH, m_EditDataPath);
	DDX_Check(pDX, IDC_CHECK_OVERWRITE_FILE_EXIST, m_bOverwriteFileIfExisted);
}

BOOL CCreateNewMultiplePathDlg::OnInitDialog()
{
	m_strDlgCaption = _T("Create Paths From Data File [full_path, path_type]");
	CDlgBase::OnInitDialog();
	// enable the browse button and put the control in file browse mode
	m_EditDataPath.EnableFileBrowseButton();
	m_EditDataPath.SetCueBanner(_T("path data format: [full_path, path_type]..."));
	SET_FOCUS_ON_CHILD_DLG_CONTROL(m_EditDataPath);
	return FALSE;
}

BEGIN_MESSAGE_MAP(CCreateNewMultiplePathDlg, CDlgBase)
	ON_BN_CLICKED(IDOK, &CCreateNewMultiplePathDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CCreateNewMultiplePathDlg message handlers

void CCreateNewMultiplePathDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CStringArray arrPath;
	CString strFileContent;
	CString strPathDataFile;
	m_EditDataPath.GetWindowTextW(strPathDataFile);
	if (!PathFileExists(strPathDataFile))
	{
		AfxMessageBox(_T("[Error] Input path does not exist!"));
		return;
	}
	PathUtils::OpenFile(strPathDataFile, strFileContent);
	AppUtils::SplitCString(strFileContent, EDITOR_NEW_LINE, arrPath);
	if (arrPath.IsEmpty())
	{
		AfxMessageBox(_T("[Error] Input path does not have data!"));
		return;
	}

	// create folders first
	int nCountCreated = 0;
	CString strCurrentTime = OSUtils::DateToCStringABDHMSY(OSUtils::GetCurrentTimeEx());
	LOG_OUTPUT_MESSAGE_COLOR(_T("\n[Multiple Paths Session: ") + strCurrentTime + _T("]\n"), BasicColors::green);
	for (int i = 0; i < arrPath.GetSize(); ++i)
	{
		CString strPathData = arrPath[i].Trim();
		if (strPathData.IsEmpty()) continue;
		CStringArray arrLine;
		AppUtils::SplitCString(strPathData, _T(","), arrLine, TRUE);
		if (arrLine.GetCount() == 2)
		{
			CString strFullPath = arrLine[0];
			CString strPathType = arrLine[1];
			if (strPathType.CompareNoCase(_T("Folder")) == 0)
			{
				// Try to create the new folder
				if (!PathUtils::CreateDirectoryIfNotExited(strFullPath))
				{
					LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Path Existed-Admin Right] Failed to create folder: ") + strPathData, BasicColors::orangered);
				}
				else
				{
					LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Multiple Paths] Created folder: ") + strPathData);
					nCountCreated++;
				}
			}
		}
		else
		{
			LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Invalid Data] Failed to create folder: ") + strPathData, BasicColors::orangered);
		}
	}
	// create files
	for (int i = 0; i < arrPath.GetSize(); ++i)
	{
		CString strPathData = arrPath[i].Trim();
		if (strPathData.IsEmpty()) continue;
		CStringArray arrLine;
		AppUtils::SplitCString(strPathData, _T(","), arrLine, TRUE);
		if (arrLine.GetCount() == 2)
		{
			CString strFullPath = arrLine[0];
			CString strPathType = arrLine[1];
			if (strPathType.CompareNoCase(_T("File")) == 0)
			{
				if (!m_bOverwriteFileIfExisted && PathFileExists(strFullPath))
				{
					LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Path Existed] Failed to create file: ") + strPathData, BasicColors::orangered);
					continue;
				}
				// Try to create the new file
				HANDLE hCreateFile = CreateFile(strFullPath, // name of the file
					GENERIC_READ, // open for writing
					0,             // sharing mode, none in this case
					0,             // use default security descriptor
					CREATE_ALWAYS, // overwrite if exists
					FILE_ATTRIBUTE_NORMAL,
					0);
				if (!hCreateFile)
				{
					LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Admin Right] Failed to create file: ") + strPathData, BasicColors::orangered);
				}
				else
				{
					DELETE_WIN32_HANDLE(hCreateFile)
					LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Multiple Paths] Created file: ") + strPathData);
					nCountCreated++;
				}
			}
		}
		else
		{
			LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Invalid Data] Data line is not followed by format [full_path, path_type] : ") + strPathData, BasicColors::orangered);
		}
	}
	LOG_OUTPUT_MESSAGE_FORMAT(_T("\n"));
	if (nCountCreated == arrPath.GetSize())
	{
		AfxMessageBox(_T("New paths created successfully."), MB_ICONINFORMATION);
	}
	else
	{
		AfxMessageBox(_T("Some paths failed to create!"));
	}
}
