/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"

#include "VinaTextApp.h"
#include "MainFrm.h"
#include "ChildFrm.h"

#include "EditorDoc.h"
#include "EditorView.h"
#include "ImageDoc.h"
#include "ImageView.h"
#include "PdfDoc.h"
#include "PdfView.h"
#include "MediaDoc.h"
#include "MediaView.h"
#include "HostDoc.h"
#include "HostView.h"
#include "FileExplorerDoc.h"
#include "FileExplorerView.h"
#include "WebDoc.h"
#include "WebView.h"

#include "HostManager.h"
#include "LocalizationHandler.h"
#include "CommandLine.h"
#include "AppSettings.h"
#include "TemporarySettings.h"
#include "SingleInstanceApp.h"
#include "ProjectTempateCreatorDlg.h"
#include "CodePageMFCDlg.h"
#include "RecentCloseFileManager.h"
#include "SaveFileWithPassWordDlg.h"
#include "ReopenFileWithPasswordDlg.h"
#include "AppAboutDlg.h"

#include "pdf/UXReader/UXReaderLibrary.h"

#include "UserCustomizeData.h"

// COM/ATL
#include <initguid.h>
#include "VinaText_i.c"

namespace
{
	void ReloadDocumentWithNewEncoding(int newEncoding, const CString& strCodePageName)
	{
		CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
		if (pEditorDoc)
		{
			CEditorView* pEditorView = pEditorDoc->GetEditorView();
			if (pEditorView)
			{
				pEditorView->SetEncodingFromUser(newEncoding);
				LOG_OUTPUT_MESSAGE_COLOR(AfxCStringFormat(_T("> [Changed Code Page] %s..."), strCodePageName), BasicColors::orange);
				AppUtils::GetMainFrame()->OnReLoadDocument();
			}
		}
	}

	BOOL IsCurrentEditorDocumentCanReload()
	{
		CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
		if (pEditorDoc)
		{
			return PathFileExists(pEditorDoc->GetPathName());
		}
		return FALSE;
	}

	BOOL IsCurrentDocumentExist()
	{
		CDocument* pDoc = AppUtils::GetMDIActiveDocument();
		BOOL bRet = FALSE;
		if (pDoc)
		{
			bRet = PathFileExists(pDoc->GetPathName());
		}
		return bRet;
	}
}

// register ALT/COM/ActiveX components
class CVinaTextModule : public ATL::CAtlMfcModule
{
public:
	DECLARE_LIBID(LIBID_VinaTextLib);
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_VINATEXT, "{0714DBFF-5EE0-40C0-BE7C-074DA6AD26FC}");
};

static CVinaTextModule _AtlModule;
static CSingleInstanceApp g_SingleInstanceVinaText(_T("VinaText-{05CA3573-B449-4e0b-83F5-7FD612E378E9}"));
static ULONG_PTR g_GdiplusToken;

// CVinaTextApp message handlers

BEGIN_MESSAGE_MAP(CVinaTextApp, CWinAppEx)
	ON_COMMAND(ID_FILE_NEW, &CVinaTextApp::OnFileNewEditor)
	ON_COMMAND(ID_FILE_OPEN, &CVinaTextApp::OnFileOpen)
	ON_COMMAND(ID_OPEN_ENCODING_ANSI, &CVinaTextApp::OnFileOpenASCII)
	ON_COMMAND(ID_OPEN_ENCODING_UTF8, &CVinaTextApp::OnFileOpenUTF8)
	ON_COMMAND(ID_OPEN_ENCODING_UTF16LE, &CVinaTextApp::OnFileOpenUTF16LE)
	ON_COMMAND(ID_OPEN_ENCODING_UTF16BE, &CVinaTextApp::OnFileOpenUTF16BE)
	ON_COMMAND(ID_OPEN_ENCODING_UTF32LE, &CVinaTextApp::OnFileOpenUTF32LE)
	ON_COMMAND(ID_OPEN_ENCODING_UTF32BE, &CVinaTextApp::OnFileOpenUTF32BE)
	ON_COMMAND(ID_FILE_OPEN_AS_ENCODING, &CVinaTextApp::OnFileOpenAsEncoding)
	ON_UPDATE_COMMAND_UI(ID_OPEN_ENCODING_ANSI, &CVinaTextApp::OnUpdateFileOpenASCII)
	ON_UPDATE_COMMAND_UI(ID_OPEN_ENCODING_UTF8, &CVinaTextApp::OnUpdateFileOpenUTF8)
	ON_UPDATE_COMMAND_UI(ID_OPEN_ENCODING_UTF16LE, &CVinaTextApp::OnUpdateFileOpenUTF16LE)
	ON_UPDATE_COMMAND_UI(ID_OPEN_ENCODING_UTF16BE, &CVinaTextApp::OnUpdateFileOpenUTF16BE)
	ON_UPDATE_COMMAND_UI(ID_OPEN_ENCODING_UTF32LE, &CVinaTextApp::OnUpdateFileOpenUTF32LE)
	ON_UPDATE_COMMAND_UI(ID_OPEN_ENCODING_UTF32BE, &CVinaTextApp::OnUpdateFileOpenUTF32BE)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN_AS_ENCODING, &CVinaTextApp::OnUpdateFileOpenAsEncoding)
	ON_COMMAND(ID_CREATE_TEMPLATE_PROJECT, &CVinaTextApp::OnNewProjectTemplate)
	ON_COMMAND(ID_FILE_OPEN_FOLDER_TO_WORKSPACE, &CVinaTextApp::OnAddFolderToWorkSpace)
	ON_COMMAND(ID_FILE_OPEN_CLOSED_RECENT, &CVinaTextApp::OnOpenRecentClosedFile)
	ON_COMMAND(ID_FILE_OPEN_ALL_CLOSED_RECENT, &CVinaTextApp::OnOpenAllRecentClosedFile)
	ON_COMMAND(ID_FILE_CLEAR_CLOSED_RECENT, &CVinaTextApp::OnClearRecentClosedFile)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN_CLOSED_RECENT, &CVinaTextApp::OnUpdateOpenRecentClosedFile)
	ON_COMMAND(ID_READ_FILE_CRYPTOGRAPHY, &CVinaTextApp::OnReadFileCryptography)
	ON_COMMAND(ID_SAVE_FILE_CRYPTOGRAPHY, &CVinaTextApp::OnSaveFileCryptography)
	ON_UPDATE_COMMAND_UI(ID_READ_FILE_CRYPTOGRAPHY, &CVinaTextApp::OnUpdateReadFileCryptography)
	ON_UPDATE_COMMAND_UI(ID_SAVE_FILE_CRYPTOGRAPHY, &CVinaTextApp::OnUpdateSaveFileCryptography)

	// help menu
	ON_COMMAND(ID_VINATEXT_DOCUMENTATION, &CVinaTextApp::OnHelpDocumentation)
	ON_COMMAND(ID_VINATEXT_REPORT_ISSUE, &CVinaTextApp::OnHelpReportIssue)
	ON_COMMAND(ID_VINATEXT_RELEASE_NOTE, &CVinaTextApp::OnHelpReleaseNotes)
	ON_COMMAND(ID_KEYBOARD_SHORTCUTS_REFERENCE, &CVinaTextApp::OnHelpKeyboardShortcutsReference)
	ON_COMMAND(ID_APP_ABOUT, &CVinaTextApp::OnHelpAppAbout)

END_MESSAGE_MAP()

// CVinaTextApp construction

CVinaTextApp::CVinaTextApp() : m_userCustomizeData{ std::make_unique<CUserCustomizeData>() }
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;

#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Vinadevs.VinaText.1.0"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CVinaTextApp object

CVinaTextApp theApp;

// CVinaTextApp initialization

BOOL CVinaTextApp::InitInstance()
{
	TemporarySettings.m_bIsStartAppInstance = TRUE;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfoEx cmdInfo;
	ParseCommandLine(cmdInfo);
	#if !defined(_WIN32_WCE) || defined(_CE_DCOM)
	// Register class factories via CoRegisterClassObject().
	if (FAILED(_AtlModule.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE)))
		return FALSE;
	#endif // !defined(_WIN32_WCE) || defined(_CE_DCOM)
	// App was launched with /Embedding or /Automation switch.
	// Run app as automation server.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Don't show the main window
		return TRUE;
	}
	// App was launched with /Unregserver or /Unregister switch.
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		_AtlModule.UpdateRegistryAppId(FALSE);
		_AtlModule.UnregisterServer(TRUE);
		return FALSE;
	}
	// App was launched with /Register or /Regserver switch.
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
	{
		_AtlModule.UpdateRegistryAppId(TRUE);
		_AtlModule.RegisterServer(TRUE);
		return FALSE;
	}

	if (g_SingleInstanceVinaText.IsAppAlreadyRunning() 
		&& cmdInfo.m_cmdOption != VINATEXT_CMD_OPTION::VINATEXT_CMD_MOVE_TO_NEW_WINDOW
		&& cmdInfo.m_cmdOption != VINATEXT_CMD_OPTION::VINATEXT_CMD_REOPEN_WITH_ADMIN_RIGHT
		&& cmdInfo.m_cmdOption != VINATEXT_CMD_OPTION::VINATEXT_CMD_RESTART_APP)
	{
		if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileOpen)
		{
			g_SingleInstanceVinaText.SendMessageToExistedInstance(cmdInfo.m_strFileName);
		}
		return FALSE;
	}

	// Remove previous data in temp path...
	//PathUtils::DeletePathPermanently(PathUtils::GetVinaTextTempPath() + _T("*.*"));

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	// VinaText Application Settings
	AppSettingMgr.LoadSettingData();
	//VinaTextLocalization.InitFromSetting();
	// VinaText Application Settings

	CWinAppEx::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	// begin: initialize GDI+  
	GdiplusStartupInput gdiplusStartupInput;
	VERIFY(GdiplusStartup(&g_GdiplusToken, &gdiplusStartupInput, NULL) == Ok);

	AfxEnableControlContainer();
	EnableTaskbarInteraction();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("VinaText-Vinadevs\\Settings"));

	// Set customize dialog
	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager();

	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL, RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	//###########################################################################################################//
	// Register the application's document templates. Document templates
	// serve as the connection between documents, frame windows and views
	if (!RegisterDocTemplates())
	{
		return FALSE;
	}
	//###########################################################################################################//

	//####### DLL Loading Start ##################################################################//
	// Load RichEdit functionality
	m_hDllRichEdit = LoadLibrary(_T("RichEd20.dll"));
	if (m_hDllRichEdit == NULL)
	{
		// RichEd20.dll does not exist or an error occurred loading it, display msg and exit
		MessageBox(NULL, _T("[Missing Dll] This program requires file RichEd20.dll"), _T("Error"), MB_OK | MB_ICONERROR);
		return 0;
	}
	// Load custom editor library
	m_hDllEdtior = PathUtils::LoadEditorDll();
	if (m_hDllEdtior == NULL)
	{
		AfxMessageBox(_T("[Error] VinaTextEditor.dll not loaded. Please try to re-install VinaText!"));
		return FALSE;
	}
	// Load custom lexer library
	m_hDllLexer = PathUtils::LoadLexerDll();
	if (m_hDllLexer == NULL)
	{
		AfxMessageBox(_T("[Error] VinaTextLexer.dll not loaded. Please try to re-install VinaText!"));
		return FALSE;
	}
	// Load pdf library
	UXReader::UXReaderLibrary::Module(m_hInstance);
	//######## DLL Loading End, Must be unloaded in ExitInstance() ###############################//

	EnableLoadWindowPlacement(FALSE);

	// load user customized data
	m_userCustomizeData->LoadSyntaxHighlightUserData();

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		DELETE_POINTER_CPP(pMainFrame);
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	if (!AppSettingMgr.LoadRecentEditorCaretData())
	{
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [Warning] Load previous recent editor data failed..."));
	}

	if (cmdInfo.m_cmdOption == VINATEXT_CMD_OPTION::VINATEXT_CMD_REOPEN_WITH_ADMIN_RIGHT)
	{
		TemporarySettings.m_bIsOpenInAdminMode = TRUE;
		if (!pMainFrame->LoadMDIState(GetRegSectionPath()))
		{
			m_pEditorDocTemplate->OpenNewDocument(NULL, FALSE, TRUE);
		}
	}
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew
		&& cmdInfo.m_cmdOption != VINATEXT_CMD_OPTION::VINATEXT_CMD_MOVE_TO_NEW_WINDOW
		&& cmdInfo.m_cmdOption != VINATEXT_CMD_OPTION::VINATEXT_CMD_RESTART_APP)
	{
		if (!pMainFrame->LoadMDIState(GetRegSectionPath()))
		{
			m_pEditorDocTemplate->OpenNewDocument(NULL, FALSE, TRUE);
		}
		else
		{
			if (AppUtils::GetDocumentTypeCount(DOCUMENT_TYPE::DOC_ALL) == 0)
			{
				OnFileNewEditor();
			}
		}
	}
	else if (cmdInfo.m_cmdOption == VINATEXT_CMD_OPTION::VINATEXT_CMD_MOVE_TO_NEW_WINDOW)
	{
		if (PathFileExists(cmdInfo.m_strFileName))
		{
			OnOpenDocument(cmdInfo.m_strFileName);
		}
	}
	else
	{
		// Dispatch commands specified on the command line.  Will return FALSE if
		// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
		if (!ProcessShellCommand(cmdInfo))
			return FALSE;
	}

	m_pMainWnd->DragAcceptFiles();

	// The main window has been initialized, so show and update it.
	if (!ReloadWindowPlacement(pMainFrame))
	{
		pMainFrame->ShowWindow(m_nCmdShow);
		pMainFrame->UpdateWindow();
	}

	LoadRecentFilesData();

	TemporarySettings.m_bIsStartAppInstance = FALSE;

	return TRUE;
}

int CVinaTextApp::ExitInstance()
{
#if !defined(_WIN32_WCE) || defined(_CE_DCOM)
	_AtlModule.RevokeClassObjects();
#endif
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	// unload dlls
	if (m_hDllEdtior != NULL)
	{
		FreeLibrary(m_hDllEdtior);
	}
	if (m_hDllLexer != NULL)
	{
		FreeLibrary(m_hDllLexer);
	}
	if (m_hDllRichEdit != NULL)
	{
		FreeLibrary(m_hDllRichEdit);
	}

	// end: shutdown GDI+
	GdiplusShutdown(g_GdiplusToken);

	// save all aplication settings for next openning session
	AppSettingMgr.SaveSettingData();
	AppSettingMgr.SaveRecentEditorCaretData();

	return CWinAppEx::ExitInstance();
}

BOOL CVinaTextApp::RegisterDocTemplates()
{
	// type editor
	m_pEditorDocTemplate = new CMultiDocTemplateEx(IDR_EDITOR_DOC,
		RUNTIME_CLASS(CEditorDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CEditorView));
	if (!m_pEditorDocTemplate)
		return FALSE;
	AddDocTemplate(m_pEditorDocTemplate);

	// type image
	m_pImageDocTemplate = new CMultiDocTemplateEx(IDR_IMAGE_DOC,
		RUNTIME_CLASS(CImageDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CImageView));
	if (!m_pImageDocTemplate)
		return FALSE;
	AddDocTemplate(m_pImageDocTemplate);

	// type pdf
	m_pPdfDocTemplate = new CMultiDocTemplateEx(IDR_PDF_DOC,
		RUNTIME_CLASS(CPdfDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CPdfView));
	if (!m_pPdfDocTemplate)
		return FALSE;
	AddDocTemplate(m_pPdfDocTemplate);

	// type media
	m_pMediaDocTemplate = new CMultiDocTemplateEx(IDR_MEDIA_DOC,
		RUNTIME_CLASS(CMediaDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CMediaView));
	if (!m_pMediaDocTemplate)
		return FALSE;
	AddDocTemplate(m_pMediaDocTemplate);

	// type host
	m_pHostDocTemplate = new CMultiDocTemplateEx(IDR_HOST_DOC,
		RUNTIME_CLASS(CHostDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CHostView));
	if (!m_pHostDocTemplate)
		return FALSE;
	AddDocTemplate(m_pHostDocTemplate);

	// type file explorer
	m_pFileExplorerDocTemplate = new CMultiDocTemplateEx(IDR_FILE_EXPLORER_DOC,
		RUNTIME_CLASS(CFileExplorerDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CFileExplorerView));
	if (!m_pFileExplorerDocTemplate)
		return FALSE;
	AddDocTemplate(m_pFileExplorerDocTemplate);

	// type web html
	m_pWebDocTemplate = new CMultiDocTemplateEx(IDR_WEB_DOC,
		RUNTIME_CLASS(CWebDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CWebView));
	if (!m_pWebDocTemplate)
		return FALSE;
	AddDocTemplate(m_pWebDocTemplate);

	return TRUE;
}

void CVinaTextApp::OnAddFolderToWorkSpace()
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;
	pFrame->GetFileExplorerCtrl().AddMoreFolderToWorkSpace();
	pFrame->ActiveDockPane(DOCKABLE_PANE_TYPE::FILE_EXPLORER_PANE);
}

void CVinaTextApp::OnOpenRecentClosedFile()
{
	CString strPathName = RecentCloseMDITabManager.PopTab();
	CDocument* pDoc = AppUtils::GetExistedDocument(strPathName);
	if (pDoc)
	{
		AppUtils::SetActiveDocument(pDoc);
	}
	else if (PathFileExists(strPathName))
	{
		OnOpenDocument(strPathName);
	}
}

void CVinaTextApp::OnOpenAllRecentClosedFile()
{
	while (RecentCloseMDITabManager.HasRecentClosedTab()) {
		OnOpenRecentClosedFile();
	}
}

void CVinaTextApp::OnClearRecentClosedFile()
{
	RecentCloseMDITabManager.ResetData();
}

void CVinaTextApp::OnSaveFileCryptography()
{
	CDocument* pDoc = AppUtils::GetMDIActiveDocument();
	if (pDoc)
	{
		if (pDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
		{
			CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(pDoc);
			if (pEditorDoc)
			{
				pEditorDoc->OnFileSave();
			}
		}
		else if (pDoc->IsKindOf(RUNTIME_CLASS(CImageDoc)))
		{
			CImageDoc* pImageDoc = dynamic_cast<CImageDoc*>(pDoc);
			if (pImageDoc)
			{
				pImageDoc->OnFileSave();
			}
		}
		if (PathFileExists(pDoc->GetPathName()))
		{
			CSaveFileWithPassWordDlg dlg(pDoc->GetPathName());
			dlg.DoModal();
		}
	}
}

void CVinaTextApp::OnReadFileCryptography()
{
	CDocument* pDoc = AppUtils::GetMDIActiveDocument();
	if (pDoc)
	{
		if (PathFileExists(pDoc->GetPathName()))
		{
			CReopenFileWithPasswordDlg dlg(pDoc->GetPathName());
			dlg.DoModal();
		}
	}
}

void CVinaTextApp::OnUpdateOpenRecentClosedFile(CCmdUI * pCmdUI)
{
	if (RecentCloseMDITabManager.HasRecentClosedTab())
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CVinaTextApp::OnHelpAppAbout()
{
	CAppAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CVinaTextApp::OnHelpKeyboardShortcutsReference()
{
	OSUtils::CreateProcessAsynchronous(TEXT("open"), _T("https://vinatext.dev/#section--3"), _T(""), _T(""), SW_MAXIMIZE);
}

void CVinaTextApp::OnHelpDocumentation()
{
	OSUtils::CreateProcessAsynchronous(TEXT("open"), _T("https://vinatext.dev/#section--2"), _T(""), _T(""), SW_MAXIMIZE);
}

void CVinaTextApp::OnHelpReportIssue()
{
	OSUtils::CreateProcessAsynchronous(TEXT("open"), _T("https://github.com/vinadevs/VinaText/issues/new"), _T(""), _T(""), SW_MAXIMIZE);
}

void CVinaTextApp::OnHelpReleaseNotes()
{
	OSUtils::CreateProcessAsynchronous(TEXT("open"), _T("https://github.com/vinadevs/VinaText/releases"), _T(""), _T(""), SW_MAXIMIZE);
}

void CVinaTextApp::OnUpdateSaveFileCryptography(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(IsCurrentDocumentExist());
}

void CVinaTextApp::OnUpdateReadFileCryptography(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(IsCurrentDocumentExist());
}

void CVinaTextApp::OnFileOpenASCII()
{
	ReloadDocumentWithNewEncoding(TF_ANSI, _T("ANSI"));
}

void CVinaTextApp::OnFileOpenUTF8()
{
	ReloadDocumentWithNewEncoding(TF_UTF8, _T("UTF8"));
}

void CVinaTextApp::OnFileOpenUTF16LE()
{
	ReloadDocumentWithNewEncoding(TF_UTF16LE, _T("UTF16LE"));
}

void CVinaTextApp::OnFileOpenUTF16BE()
{
	ReloadDocumentWithNewEncoding(TF_UTF16BE, _T("UTF16BE"));
}

void CVinaTextApp::OnFileOpenUTF32LE()
{
	ReloadDocumentWithNewEncoding(TF_UTF32LE, _T("UTF32LE"));
}

void CVinaTextApp::OnFileOpenUTF32BE()
{
	ReloadDocumentWithNewEncoding(TF_UTF32BE, _T("UTF32BE"));
}

void CVinaTextApp::OnFileOpenAsEncoding()
{
	CCodePageMFCDlg dlg;
	dlg.SetDlgModeReopen(TRUE);
	if (IDOK == dlg.DoModal())
	{
		// reload file...
		AppUtils::GetMainFrame()->OnReLoadDocument();
	}
}

void CVinaTextApp::OnUpdateFileOpenASCII(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(IsCurrentEditorDocumentCanReload());
}

void CVinaTextApp::OnUpdateFileOpenUTF8(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(IsCurrentEditorDocumentCanReload());
}

void CVinaTextApp::OnUpdateFileOpenUTF16LE(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(IsCurrentEditorDocumentCanReload());
}

void CVinaTextApp::OnUpdateFileOpenUTF16BE(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(IsCurrentEditorDocumentCanReload());
}

void CVinaTextApp::OnUpdateFileOpenUTF32LE(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(IsCurrentEditorDocumentCanReload());
}

void CVinaTextApp::OnUpdateFileOpenUTF32BE(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(IsCurrentEditorDocumentCanReload());
}

void CVinaTextApp::OnUpdateFileOpenAsEncoding(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(IsCurrentEditorDocumentCanReload());
}

// CVinaTextApp customization load/save methods

BOOL CVinaTextApp::PreTranslateMessage(LPMSG pMsg)
{
	if (pMsg->message == g_SingleInstanceVinaText.GetMsgCheckInst())
	{
		return OnAnotherInstanceMessage(pMsg);
	}
	return CWinAppEx::PreTranslateMessage(pMsg);
}

CDocument* CVinaTextApp::OnOpenDocument(LPCTSTR lpszPathName)
{
	CDocument* pDoc = AppUtils::GetExistedDocument(lpszPathName);
	if (pDoc)
	{ 
		AppUtils::SetActiveDocument(pDoc); return pDoc;
	}
	if (PathUtils::IsDirectory(lpszPathName))
	{
		// Open file explorer window
		return HostManager::HostApplicaton(HostManager::HOST_APP_TYPE::FILE_EXPLORER, NULL, lpszPathName);
	}
	if (PathUtils::IsImageFile(lpszPathName))
	{
		// Open image file
		return m_pImageDocTemplate->OpenNewDocument(lpszPathName, TRUE, TRUE);
	}
	else if (PathUtils::IsPdfFile(lpszPathName))
	{
		// Open pdf file
		return m_pPdfDocTemplate->OpenNewDocument(lpszPathName, TRUE, TRUE);
	}
	else if (PathUtils::IsMediaFile(lpszPathName))
	{
		// Open media file
		return m_pMediaDocTemplate->OpenNewDocument(lpszPathName, TRUE, TRUE);
	}
	else
	{
		// Open text file
		return m_pEditorDocTemplate->OpenDocumentFile(lpszPathName, TRUE, TRUE);
	}
}

CDocument* CVinaTextApp::CreateWebDocument()
{
	CWebDoc* pExistedDoc = dynamic_cast<CWebDoc*>(AppUtils::GetExistedWebDocument(_T("Path Compare Result")));
	if (pExistedDoc)
	{
		AppUtils::SetActiveDocument(pExistedDoc);
		return pExistedDoc;
	}
	return m_pWebDocTemplate->OpenNewDocument(NULL, FALSE, TRUE);
}

CDocument * CVinaTextApp::CreateNewFileExplorerDocument(const CString& strNavigatePath)
{
	TemporarySettings.m_strFileExplorerNavigatePath = strNavigatePath;
	return m_pFileExplorerDocTemplate->OpenNewDocument(NULL, FALSE, TRUE);
}

CDocument* CVinaTextApp::CreateNewHostDocument(const CString& strAppName,
	const CString& strAppPathToHost, const CString& strAppArguments,
	BOOL bRemoveTitleBarWindow, BOOL bSilentStartup, UINT nAppIconID
	, HostManager::HOST_METHOD HostMethod, int nWaitTime, const CString& strClassAppName
	, BOOL bOpenFileMode)
{
	m_STHostAppInfo.m_strAppName = strAppName;
	m_STHostAppInfo.m_strAppPathToHost = strAppPathToHost;
	m_STHostAppInfo.m_strAppArguments = strAppArguments;
	m_STHostAppInfo.m_bRemoveTitleBarWindow = bRemoveTitleBarWindow;
	m_STHostAppInfo.m_bSilentStartup = bSilentStartup;
	m_STHostAppInfo.m_bOpenFileMode = bOpenFileMode;
	m_STHostAppInfo.m_nAppIconID = nAppIconID;
	m_STHostAppInfo.m_nWaitTime = nWaitTime;
	m_STHostAppInfo.m_HostMethod = HostMethod;
	m_STHostAppInfo.m_strClassAppName = strClassAppName;
	CDocument* pHostDoc = m_pHostDocTemplate->OpenNewDocument(NULL, FALSE, TRUE);
	if (pHostDoc && PathFileExists(m_STHostAppInfo.m_strAppArguments))
	{
		pHostDoc->SetPathName(m_STHostAppInfo.m_strAppArguments, AppSettingMgr.m_bAddHostPathToRecentList);
	}
	return pHostDoc;
}

BOOL CVinaTextApp::OnAnotherInstanceMessage(LPMSG pMsg)
{
	// Get command line arguments (if any) from new instance.

	BOOL bShellOpen = FALSE;

	if (pMsg->wParam != NULL)
	{
		::GlobalGetAtomName((ATOM)pMsg->wParam, m_lpCmdLine, _MAX_FNAME);
		::GlobalDeleteAtom((ATOM)pMsg->wParam);
		bShellOpen = TRUE;
	}

	// If got valid command line then try to open the document -
	// CDocManager will popup main window itself. Otherwise, we
	// have to popup the window 'manually' :

	CDocument* pDoc = AppUtils::GetExistedDocument(m_lpCmdLine);

	if (pDoc == NULL && m_pDocManager != NULL && bShellOpen && PathFileExists(m_lpCmdLine))
	{
		CWaitCursor wait;
		OnOpenDocument(m_lpCmdLine);
	}
	else if (::IsWindow(m_pMainWnd->GetSafeHwnd()))
	{
		// Does the main window have any popups ? If has, 
		// bring the main window or its popup to the top
		// before showing:

		CWnd* pPopupWnd = m_pMainWnd->GetLastActivePopup();
		pPopupWnd->BringWindowToTop();

		// If window is not visible then show it, else if
		// it is iconic, restore it:

		if (!m_pMainWnd->IsWindowVisible())
			m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
		else if (m_pMainWnd->IsIconic())
			m_pMainWnd->ShowWindow(SW_RESTORE);

		// And finally, bring to top after showing again:

		pPopupWnd->BringWindowToTop();
		pPopupWnd->SetForegroundWindow();
	}

	return TRUE;
}

BOOL CVinaTextApp::SaveAllModified()
{
	// backup modified documents
	if (AppUtils::GetModifiedDocumentCount() > 0)
	{
		if (AppSettingMgr.m_bAutoSaveFileWhenCloseApp)
		{
			AppUtils::BackupAllModifiedDocuments(TRUE);
		}
		else
		{
			if (AppUtils::GetModifiedDocumentCount() > 1)
			{
				int nAnwser = AfxMessageBox(_T("Do you want to save all modified files?"), MB_YESNOCANCEL | MB_ICONINFORMATION);
				if (IDYES == nAnwser)
				{
					AppUtils::SaveAllModifiedDocuments(TRUE);
				}
				else if (IDCANCEL == nAnwser)
				{
					return FALSE;
				}
			}
			else if (!CWinAppEx::SaveAllModified())
			{
				return FALSE;
			}
		}
	}
	// backup app state
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, m_pMainWnd);
	if (pMainFrame != NULL)
	{
		return pMainFrame->SaveMDIState(GetRegSectionPath());
	}
	return FALSE;
}

void CVinaTextApp::OnFileOpen()
{
	// Default File Filter
	CString strDefaultFilter = PathUtils::GetDataBaseFileFilter();

	CString strInitialPath;
	if (AppSettingMgr.m_bUseInitialFilePickerPath)
	{
		strInitialPath = AppSettingMgr.m_strInitialFilePickerPath;
	}

	// Create a file open dialog
	CFileDialog fdOpen(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_ENABLESIZING, strDefaultFilter);

	// Set current directory for file open dialog
	fdOpen.m_ofn.lpstrInitialDir = strInitialPath;

	// Set title
	fdOpen.m_ofn.lpstrTitle = _T("Open File (Accept multiple files)");

	// Open dialog
	if (fdOpen.DoModal() == IDOK)
	{
		POSITION pos = fdOpen.GetStartPosition();
		while (pos) 
		{
			CString strFileName = fdOpen.GetNextPathName(pos);
			OnOpenDocument(strFileName);
		}
	}
}

void CVinaTextApp::OnFileNewEditor()
{
	CWinAppEx::OnFileNew();
}

void CVinaTextApp::OnNewProjectTemplate()
{
	CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pEditorDoc)
	{
		CString strFilePath = pEditorDoc->GetPathName();
		if (PathFileExists(strFilePath))
		{
			CString strFolderPath = strFilePath;
			if (!PathUtils::IsDirectory(strFilePath))
			{
				strFolderPath = PathUtils::GetContainerPath(strFilePath);
			}
			CProjectTempateCreator dlg(strFolderPath);
			dlg.DoModal();
		}
		else
		{
			CProjectTempateCreator dlg(PathUtils::GetVinaTextAppDataPath());
			dlg.DoModal();
		}
	}
}

BOOL CVinaTextApp::SaveRecentFilesData()
{
	CString strFolderPath = PathUtils::GetVinaTextAppDataPath();
	if (!PathFileExists(strFolderPath)) return FALSE;
	CString strDataPath = strFolderPath + _T("recent-closed-data.dat");
	if (PathFileExists(strDataPath))
	{
		::DeleteFile(strDataPath);
	}
	std::wofstream file(AppUtils::CStringToWStd(strDataPath), std::wios::trunc);
	if (!file) return FALSE;
	file.imbue(std::locale(file.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	for (auto const& filePath : RecentCloseMDITabManager.GetData())
	{
		file << AppUtils::CStringToWStd(filePath) << std::endl;
	}
	return TRUE;
}

BOOL CVinaTextApp::LoadRecentFilesData()
{
	CString strFolderPath = PathUtils::GetVinaTextAppDataPath();
	if (!PathFileExists(strFolderPath)) return FALSE;
	CString strOpenedFolderDataPath = strFolderPath + _T("recent-closed-data.dat");
	CStringArray arrPath;
	CString strFileContent;
	PathUtils::OpenFile(strOpenedFolderDataPath, strFileContent);
	if (strFileContent.IsEmpty()) return FALSE;
	AppUtils::SplitCString(strFileContent, EDITOR_NEW_LINE, arrPath);
	for (int i = static_cast<int>(arrPath.GetSize()) - 1; i >= 0; --i)
	{
		RecentCloseMDITabManager.PushTab(arrPath[i], FALSE);
	}
	return TRUE;
}