// ProgrammingSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ProgrammingSettingDlg.h"
#include "AppSettings.h"
#include "AppUtil.h"
#include "PathUtil.h"
#include "ScrollHelper.h"

// ProgrammingSettingDlg dialog

IMPLEMENT_DYNAMIC(ProgrammingSettingDlg, CDialogEx)

ProgrammingSettingDlg::ProgrammingSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING_PROGRAMMING, pParent) {
	m_pScrollHelper = std::make_unique<CScrollHelper>();
	m_pScrollHelper->AttachWnd(this);
	m_pScrollHelper->SetDisplaySize(0, 1500);
}

ProgrammingSettingDlg::~ProgrammingSettingDlg() {}

void ProgrammingSettingDlg::UpdateGUISettings(BOOL bFromGUI)
{
	if (bFromGUI)
	{
		UpdateData(TRUE);
		FromDefaultTerminalWindowsCombobox();
		AppSettingMgr.m_bAllowOpenFileHasErrorBuild = m_bAllowOpenFileHasErrorBuild;
		AppSettingMgr.m_bAskBeforeTerminateProgram = m_bAskBeforeTerminateProgram;
		AppSettingMgr.m_bAutoSaveDocumentWhenbuild = m_bAutoSaveDocumentWhenbuild;
		AppSettingMgr.m_bEnableDisplayBuildErrorOnEditor = m_bEnableDisplayBuildErrorOnEditor;
		AppSettingMgr.m_bEnableWarningFlagForCAndCPP = m_bEnableWarningFlagForCAndCPP;
		AppSettingMgr.m_bEnableWindowSubsytemFlagForCAndCPP = m_bEnableWindowSubsytemFlagForCAndCPP;
		AppSettingMgr.m_bOpenWindowCmdWhenRunProgram = m_bOpenWindowCmdWhenRunProgram;
		AppSettingMgr.m_strNodeJSFolderPath = m_strNodeJSFolderPath;
		AppSettingMgr.m_strPythonFolderPath = m_strPythonFolderPath;
	}
	else
	{
		InitDefaultTerminalWindowsCombobox();
		m_bAllowOpenFileHasErrorBuild = AppSettingMgr.m_bAllowOpenFileHasErrorBuild;
		m_bAskBeforeTerminateProgram = AppSettingMgr.m_bAskBeforeTerminateProgram;
		m_bAutoSaveDocumentWhenbuild = AppSettingMgr.m_bAutoSaveDocumentWhenbuild;
		m_bEnableDisplayBuildErrorOnEditor = AppSettingMgr.m_bEnableDisplayBuildErrorOnEditor;
		m_bEnableWarningFlagForCAndCPP = AppSettingMgr.m_bEnableWarningFlagForCAndCPP;
		m_bEnableWindowSubsytemFlagForCAndCPP = AppSettingMgr.m_bEnableWindowSubsytemFlagForCAndCPP;
		m_bOpenWindowCmdWhenRunProgram = AppSettingMgr.m_bOpenWindowCmdWhenRunProgram;
		m_strNodeJSFolderPath = AppSettingMgr.m_strNodeJSFolderPath;
		m_strPythonFolderPath = AppSettingMgr.m_strPythonFolderPath;
		UpdateData(FALSE);
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
	DDX_Text(pDX, ID_NODE_JS_FOLDER_PATH_EDIT, m_strNodeJSFolderPath);
	DDX_Text(pDX, ID_PYTHON_FOLDER_PATH_EDIT, m_strPythonFolderPath);
	DDX_Control(pDX, IDC_COMBO_DEFAULT_TERMINAL_WINDOWS, m_DefaultToolbarTerminalWindows);
}

BOOL ProgrammingSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_EditNodeJSFolderPath.EnableFolderBrowseButton();
	m_EditPythonFolderPath.EnableFolderBrowseButton();

	UpdateGUISettings(FALSE);

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
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// for scrolling //////////////////////////////////////////////////////////////

void ProgrammingSettingDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pScrollHelper->OnHScroll(nSBCode, nPos, pScrollBar);
}

void ProgrammingSettingDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pScrollHelper->OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL ProgrammingSettingDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	BOOL wasScrolled = m_pScrollHelper->OnMouseWheel(nFlags, zDelta, pt);

	return wasScrolled;
}

void ProgrammingSettingDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_pScrollHelper->OnSize(nType, cx, cy);
}

void ProgrammingSettingDlg::InitDefaultTerminalWindowsCombobox()
{
	m_DefaultToolbarTerminalWindows.ResetContent();
	m_DefaultToolbarTerminalWindows.AddString(_T("Windows Command Prompt (CMD)"));
	m_DefaultToolbarTerminalWindows.AddString(_T("Windows PowerShell"));
	m_DefaultToolbarTerminalWindows.AddString(_T("Windows Subsystem Linux (WSL)"));
	switch (AppSettingMgr.m_DefaultToolbarTerminal)
	{
	case DEFAULT_TOOLBAR_TERMINAL::MS_CMD:
		m_DefaultToolbarTerminalWindows.SetCurSel(0);
		break;
	case DEFAULT_TOOLBAR_TERMINAL::MS_POWERSHELL:
		m_DefaultToolbarTerminalWindows.SetCurSel(1);
		break;
	case DEFAULT_TOOLBAR_TERMINAL::LINUX_WSL:
		m_DefaultToolbarTerminalWindows.SetCurSel(2);
		break;
	default:
		m_DefaultToolbarTerminalWindows.SetCurSel(0);
		break;
	}
}

void ProgrammingSettingDlg::FromDefaultTerminalWindowsCombobox()
{
	int iSel = m_DefaultToolbarTerminalWindows.GetCurSel();
	switch (iSel)
	{
	case 0:
		AppSettingMgr.m_DefaultToolbarTerminal = DEFAULT_TOOLBAR_TERMINAL::MS_CMD;
		break;
	case 1:
		AppSettingMgr.m_DefaultToolbarTerminal = DEFAULT_TOOLBAR_TERMINAL::MS_POWERSHELL;
		break;
	case 2:
		AppSettingMgr.m_DefaultToolbarTerminal = DEFAULT_TOOLBAR_TERMINAL::LINUX_WSL;
		break;
	default:
		AppSettingMgr.m_DefaultToolbarTerminal = DEFAULT_TOOLBAR_TERMINAL::MS_CMD;
		break;
	}
}

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
