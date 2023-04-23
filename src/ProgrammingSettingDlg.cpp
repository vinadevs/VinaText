// ProgrammingSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ProgrammingSettingDlg.h"
#include "AppSettings.h"
#include "AppUtil.h"
#include "PathUtil.h"

// ProgrammingSettingDlg dialog

IMPLEMENT_DYNAMIC(ProgrammingSettingDlg, CDialogEx)

ProgrammingSettingDlg::ProgrammingSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING_PROGRAMMING, pParent) {}


void ProgrammingSettingDlg::UpdateGUISettings(BOOL bFromGUI)
{
	if (bFromGUI)
	{
		UpdateData(TRUE);
		AppSettingMgr.m_bAllowOpenFileHasErrorBuild = m_bAllowOpenFileHasErrorBuild;
		AppSettingMgr.m_bAskBeforeTerminateProgram = m_bAskBeforeTerminateProgram;
		AppSettingMgr.m_bAutoSaveDocumentWhenbuild = m_bAutoSaveDocumentWhenbuild;
		AppSettingMgr.m_bEnableDisplayBuildErrorOnEditor = m_bEnableDisplayBuildErrorOnEditor;
		AppSettingMgr.m_bEnableWarningFlagForCAndCPP = m_bEnableWarningFlagForCAndCPP;
		AppSettingMgr.m_bEnableWindowSubsytemFlagForCAndCPP = m_bEnableWindowSubsytemFlagForCAndCPP;
		AppSettingMgr.m_bOpenWindowCmdWhenRunProgram = m_bOpenWindowCmdWhenRunProgram;
		AppSettingMgr.m_strNodeJSFolderPath = m_strNodeJSFolderPath;
		AppSettingMgr.m_strPythonFolderPath = m_strPythonFolderPath;
		AppSettingMgr.m_strGitWindowFolderPath = m_strGitWindowFolderPath;
	}
	else
	{
		m_bAllowOpenFileHasErrorBuild = AppSettingMgr.m_bAllowOpenFileHasErrorBuild;
		m_bAskBeforeTerminateProgram = AppSettingMgr.m_bAskBeforeTerminateProgram;
		m_bAutoSaveDocumentWhenbuild = AppSettingMgr.m_bAutoSaveDocumentWhenbuild;
		m_bEnableDisplayBuildErrorOnEditor = AppSettingMgr.m_bEnableDisplayBuildErrorOnEditor;
		m_bEnableWarningFlagForCAndCPP = AppSettingMgr.m_bEnableWarningFlagForCAndCPP;
		m_bEnableWindowSubsytemFlagForCAndCPP = AppSettingMgr.m_bEnableWindowSubsytemFlagForCAndCPP;
		m_bOpenWindowCmdWhenRunProgram = AppSettingMgr.m_bOpenWindowCmdWhenRunProgram;
		m_strNodeJSFolderPath = AppSettingMgr.m_strNodeJSFolderPath;
		m_strPythonFolderPath = AppSettingMgr.m_strPythonFolderPath;
		m_strGitWindowFolderPath = AppSettingMgr.m_strGitWindowFolderPath;
	}
}

void ProgrammingSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, ID_ALLOW_OPEN_FILE_HAS_ERROR_BUILD, m_bAllowOpenFileHasErrorBuild);
	DDX_Check(pDX, ID_ASK_BEFORE_TERMINATE_PROGRAM, m_bAskBeforeTerminateProgram);
	DDX_Check(pDX, ID_AUTO_SAVE_DOCUMENT_WHENBUILD, m_bAutoSaveDocumentWhenbuild);
	DDX_Check(pDX, ID_ENABLE_DISPLAY_BUILD_ERROR_ON_EDITOR, m_bEnableDisplayBuildErrorOnEditor);
	DDX_Check(pDX, ID_ENABLE_WARNING_FLAG_FOR_C_AND_CPP, m_bEnableWarningFlagForCAndCPP);
	DDX_Check(pDX, ID_ENABLE_WINDOW_SUBSYTEM_FLAG_FOR_C_AND_CPP, m_bEnableWindowSubsytemFlagForCAndCPP);
	DDX_Check(pDX, ID_OPEN_WINDOW_CMD_WHEN_RUN_PROGRAM, m_bOpenWindowCmdWhenRunProgram);
	DDX_Control(pDX, ID_NODE_JS_FOLDER_PATH_EDIT, m_EditNodeJSFolderPath);
	DDX_Control(pDX, ID_PYTHON_FOLDER_PATH_EDIT, m_EditPythonFolderPath);
	DDX_Control(pDX, ID_GIT_WINDOW_FOLDER_PATH_EDIT, m_EditGitWindowFolderPath);
	DDX_Text(pDX, ID_NODE_JS_FOLDER_PATH_EDIT, m_strNodeJSFolderPath);
	DDX_Text(pDX, ID_PYTHON_FOLDER_PATH_EDIT, m_strPythonFolderPath);
	DDX_Text(pDX, ID_GIT_WINDOW_FOLDER_PATH_EDIT, m_strGitWindowFolderPath);
}

BOOL ProgrammingSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_EditNodeJSFolderPath.EnableFolderBrowseButton();
	m_EditPythonFolderPath.EnableFolderBrowseButton();
	m_EditGitWindowFolderPath.EnableFolderBrowseButton();

	UpdateGUISettings(FALSE);

	UpdateData(FALSE);

	return TRUE;
}

BOOL ProgrammingSettingDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			GetParent()->GetParent()->SendMessage(WM_CLOSE, 0, 0);
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void ProgrammingSettingDlg::OnDropFiles(HDROP hDropInfo)
{
	CDialogEx::OnDropFiles(hDropInfo);
	int nCntFiles = DragQueryFile(hDropInfo, -1, 0, 0);
	if (nCntFiles == 1)
	{
		CEdit* pEdit = dynamic_cast<CEdit*>(FromHandle(m_hWndChildDropFile));
		if (pEdit)
		{
			TCHAR szPath[_MAX_PATH];
			szPath[0] = 0;
			::DragQueryFile(hDropInfo, 0, szPath, _MAX_PATH);
			if (!PathUtils::IsDirectory(szPath))
			{
				AfxMessageBox(_T("[Path Error] This setting requires a folder path, not file path."));
			}
			else
			{
				pEdit->SetWindowTextW(szPath);
			}
		}
	}
	DragFinish(hDropInfo);
}

BEGIN_MESSAGE_MAP(ProgrammingSettingDlg, CDialogEx)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////

BOOL ProgrammingSettingBrowse::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_DROPFILES)
	{
		ProgrammingSettingDlg* pParent = dynamic_cast<ProgrammingSettingDlg*>(GetParent());
		if (pParent)
		{
			pParent->m_hWndChildDropFile = this->m_hWnd;
			pParent->SendMessage(WM_DROPFILES, pMsg->wParam, pMsg->lParam);
			return TRUE; // got it
		}
	}
	return FALSE; // allow default processing
}
