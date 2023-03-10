/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
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

#include "AppSettings.h"
#include "MultiThreadWorker.h"
#include "Debugger.h"
//#include "CustomizeUserTool.h"

#include "SetBookmarkPathDlg.h"
#include "QuickSearchDialog.h"
#include "BookMarkPathDlg.h"

#include "VinaTextSettingDlg.h"

#include "GuiUtils.h"

#include "HostManager.h"
#include "SystemInfo.h"

#include "WindowsPrinter.h"

#include "translator/POHandler.h"

// CMainFrame

#pragma warning(disable: 4996 4127)

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

//const int  iMaxUserToolbars = 10;
//const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
//const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

static UINT g_Statusbar_Indicators[] =
{
	ID_INDICATOR_EXPLORER_SELECTED_PATH,
	ID_INDICATOR_CURRENT_LANGUAGE,
	ID_INDICATOR_ENCODING,
	ID_INDICATOR_CARET_INFO,
	ID_INDICATOR_MATCHEDS,
	ID_INDICATOR_SELECTIONS,
};

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_DROPFILES()
	ON_WM_SIZE()
	ON_WM_MOVING()

	ON_MESSAGE(UMW_MAIN_FRAME_UPDATE, &CMainFrame::OnMainFrameUpdate)
	ON_MESSAGE(WM_COPYDATA, &CMainFrame::OnCopyData)
	ON_MESSAGE(UWM_GUI_WORKER_HANDLER_DEBUG_NOTIFY_LINE_PONITER, &CMainFrame::OnCompilerNotifyDebugLinePointer)
	ON_COMMAND(UMW_SET_COLOR_ACTIVE_TAB_MDI, &CMainFrame::OnHighLightMDIActiveTab)
	ON_COMMAND(UMW_SET_READ_ONLY_TAB_MDI, &CMainFrame::OnUpdateIconReadOnlyTab)
	ON_COMMAND(UMW_DISABLE_ALL_READ_ONLY_TAB_MDI, &CMainFrame::OnUpdateIconAllReadOnlyTab)
	ON_COMMAND(ID_EDITOR_FULL_SCREEN_MODE, &CMainFrame::OnFullScreeenMode)
	ON_COMMAND(ID_CLEAN_UP_ALL_WINDOW, &CMainFrame::OnCleanUpAllWindows)
	ON_COMMAND(ID_HIDE_ALL_DOCKWINDOW, &CMainFrame::OnHideAllWindows)
	ON_COMMAND(ID_SHOW_ALL_DOCKWINDOW, &CMainFrame::OnShowAllWindows)
	ON_COMMAND(ID_PANE_FILE_EXPLORER, &CMainFrame::OnViewFileExplorerWindow)
	ON_COMMAND(ID_QUICK_SEARCH, &CMainFrame::OnQuickSearch)
	ON_COMMAND(ID_QUICK_REPLACE, &CMainFrame::OnQuickReplace)
	ON_UPDATE_COMMAND_UI(ID_QUICK_SEARCH, &CMainFrame::OnUpdateQuickSearch)
	ON_UPDATE_COMMAND_UI(ID_QUICK_REPLACE, &CMainFrame::OnUpdateQuickReplace)
	ON_UPDATE_COMMAND_UI(ID_PANE_FILE_EXPLORER, &CMainFrame::OnUpdateViewFileExplorerWindow)
	ON_COMMAND(ID_PANE_OUTPUT_WINDOW, &CMainFrame::OnViewOutputPane)
	ON_UPDATE_COMMAND_UI(ID_PANE_OUTPUT_WINDOW, &CMainFrame::OnUpdateViewOutputPane)
	ON_COMMAND(ID_PANE_SEARCH_AND_REPLACE_WINDOW, &CMainFrame::OnViewSearchAndReplaceWindow)
	ON_UPDATE_COMMAND_UI(ID_PANE_SEARCH_AND_REPLACE_WINDOW, &CMainFrame::OnUpdateViewSearchAndReplaceWindow)
	ON_COMMAND(ID_PANE_TEXT_RESULT_WINDOW, &CMainFrame::OnViewSearchResultPane)
	ON_UPDATE_COMMAND_UI(ID_PANE_TEXT_RESULT_WINDOW, &CMainFrame::OnUpdateViewSearchResultPane)
	ON_COMMAND(ID_PANE_BUILD_WINDOW, &CMainFrame::OnViewBuildPane)
	ON_UPDATE_COMMAND_UI(ID_PANE_BUILD_WINDOW, &CMainFrame::OnUpdateViewBuildPane)
	ON_COMMAND(ID_PANE_BOOKMARK_WINDOW, &CMainFrame::OnViewBookmarkPane)
	ON_UPDATE_COMMAND_UI(ID_PANE_BOOKMARK_WINDOW, &CMainFrame::OnUpdateViewBookmarkPane)
	ON_COMMAND(ID_PANE_FILE_RESULT_WINDOW, &CMainFrame::OnViewFileResultPane)
	ON_UPDATE_COMMAND_UI(ID_PANE_FILE_RESULT_WINDOW, &CMainFrame::OnUpdateViewFileResultPane)
	ON_COMMAND(ID_PANE_BREAKPOINT_WINDOW, &CMainFrame::OnViewBreakpointPane)
	ON_UPDATE_COMMAND_UI(ID_PANE_BREAKPOINT_WINDOW, &CMainFrame::OnUpdateViewBreakpointPane)
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	//ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND(ID_TOOLS_ALLOWCREATEFOLDER, &CMainFrame::OnToolsAllowCreateFolder)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ALLOWCREATEFOLDER, &CMainFrame::OnUpdateToolsAllowCreateFolder)
	ON_COMMAND(ID_TOOLS_ALLOWDELETE, &CMainFrame::OnToolsAllowDelete)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ALLOWDELETE, &CMainFrame::OnUpdateToolsAllowDelete)
	ON_COMMAND(ID_TOOLS_ALLOWOPEN, &CMainFrame::OnToolsAllowOpen)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ALLOWOPEN, &CMainFrame::OnUpdateToolsAllowOpen)
	ON_COMMAND(ID_TOOLS_ALLOWRENAME, &CMainFrame::OnToolsAllowRename)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ALLOWRENAME, &CMainFrame::OnUpdateToolsAllowRename)
	ON_COMMAND(ID_TOOLS_ALLOWPROPERTIES, &CMainFrame::OnToolsAllowProperties)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ALLOWPROPERTIES, &CMainFrame::OnUpdateToolsAllowProperties)
	ON_COMMAND(ID_TOOLS_SHOWFILES, &CMainFrame::OnToolsShowFiles)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SHOWFILES, &CMainFrame::OnUpdateToolsShowFiles)
	ON_COMMAND(ID_TOOLS_ALLOWDRAGDROP, &CMainFrame::OnToolsAllowDragDrop)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ALLOWDRAGDROP, &CMainFrame::OnUpdateToolsAllowDragDrop)
	ON_COMMAND(ID_TOOLS_HIDECDROM, &CMainFrame::OnToolsHideCDROM)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDECDROM, &CMainFrame::OnUpdateToolsHideCDROM)
	ON_COMMAND(ID_TOOLS_HIDEFIXED, &CMainFrame::OnToolsHideFixed)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEFIXED, &CMainFrame::OnUpdateToolsHideFixed)
	ON_COMMAND(ID_TOOLS_HIDERAMDISKS, &CMainFrame::OnToolsHideRAMDisks)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDERAMDISKS, &CMainFrame::OnUpdateToolsHideRAMDisks)
	ON_COMMAND(ID_TOOLS_HIDEREMOVABLE, &CMainFrame::OnToolsHideRemovable)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEREMOVABLE, &CMainFrame::OnUpdateToolsHideRemovable)
	ON_COMMAND(ID_TOOLS_HIDEREMOTE, &CMainFrame::OnToolsHideRemote)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEREMOTE, &CMainFrame::OnUpdateToolsHideRemote)
	ON_COMMAND(ID_TOOLS_HIDEHIDDEN, &CMainFrame::OnToolsHideHidden)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEHIDDEN, &CMainFrame::OnUpdateToolsHideHidden)
	ON_COMMAND(ID_TOOLS_HIDEARCHIVE, &CMainFrame::OnToolsHideArchive)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEARCHIVE, &CMainFrame::OnUpdateToolsHideArchive)
	ON_COMMAND(ID_TOOLS_HIDECOMPRESSED, &CMainFrame::OnToolsHideCompressed)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDECOMPRESSED, &CMainFrame::OnUpdateToolsHideCompressed)
	ON_COMMAND(ID_TOOLS_HIDESYSTEM, &CMainFrame::OnToolsHideSystem)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDESYSTEM, &CMainFrame::OnUpdateToolsHideSystem)
	ON_COMMAND(ID_TOOLS_HIDETEMPORARY, &CMainFrame::OnToolsHideTemporary)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDETEMPORARY, &CMainFrame::OnUpdateToolsHideTemporary)
	ON_COMMAND(ID_TOOLS_HIDEENCRYPTED, &CMainFrame::OnToolsHideEncrypted)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEENCRYPTED, &CMainFrame::OnUpdateToolsHideEncrypted)
	ON_COMMAND(ID_TOOLS_HIDEOFFLINE, &CMainFrame::OnToolsHideOffline)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEOFFLINE, &CMainFrame::OnUpdateToolsHideOffline)
	ON_COMMAND(ID_TOOLS_HIDEREADONLY, &CMainFrame::OnToolsHideReadOnly)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEREADONLY, &CMainFrame::OnUpdateToolsHideReadOnly)
	ON_COMMAND(ID_TOOLS_HIDEREPARSEPOINT, &CMainFrame::OnToolsHideReparsePoint)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEREPARSEPOINT, &CMainFrame::OnUpdateToolsHideReparsePoint)
	ON_COMMAND(ID_TOOLS_HIDESPARSE, &CMainFrame::OnToolsHideSparse)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDESPARSE, &CMainFrame::OnUpdateToolsHideSparse)
	ON_COMMAND(ID_TOOLS_HIDEHIDDEN2, &CMainFrame::OnToolsHideHidden2)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEHIDDEN2, &CMainFrame::OnUpdateToolsHideHidden2)
	ON_COMMAND(ID_TOOLS_HIDEARCHIVE2, &CMainFrame::OnToolsHideArchive2)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEARCHIVE2, &CMainFrame::OnUpdateToolsHideArchive2)
	ON_COMMAND(ID_TOOLS_HIDECOMPRESSED2, &CMainFrame::OnToolsHideCompressed2)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDECOMPRESSED2, &CMainFrame::OnUpdateToolsHideCompressed2)
	ON_COMMAND(ID_TOOLS_HIDESYSTEM2, &CMainFrame::OnToolsHideSystem2)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDESYSTEM2, &CMainFrame::OnUpdateToolsHideSystem2)
	ON_COMMAND(ID_TOOLS_HIDETEMPORARY2, &CMainFrame::OnToolsHideTemporary2)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDETEMPORARY2, &CMainFrame::OnUpdateToolsHideTemporary2)
	ON_COMMAND(ID_TOOLS_HIDEENCRYPTED2, &CMainFrame::OnToolsHideEncrypted2)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEENCRYPTED2, &CMainFrame::OnUpdateToolsHideEncrypted2)
	ON_COMMAND(ID_TOOLS_HIDEOFFLINE2, &CMainFrame::OnToolsHideOffline2)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEOFFLINE2, &CMainFrame::OnUpdateToolsHideOffline2)
	ON_COMMAND(ID_TOOLS_HIDEREADONLY2, &CMainFrame::OnToolsHideReadOnly2)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEREADONLY2, &CMainFrame::OnUpdateToolsHideReadOnly2)
	ON_COMMAND(ID_TOOLS_HIDEREPARSEPOINT2, &CMainFrame::OnToolsHideReparsePoint2)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEREPARSEPOINT2, &CMainFrame::OnUpdateToolsHideReparsePoint2)
	ON_COMMAND(ID_TOOLS_HIDESPARSE2, &CMainFrame::OnToolsHideSparse2)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDESPARSE2, &CMainFrame::OnUpdateToolsHideSparse2)
	ON_COMMAND(ID_TOOLS_REFRESH, &CMainFrame::OnToolsRefresh)
	ON_COMMAND(ID_TOOLS_FORWARD, &CMainFrame::OnToolsGoForward)
	ON_COMMAND(ID_TOOLS_BACK, &CMainFrame::OnToolsGoBack)
	ON_COMMAND(ID_TOOLS_UPONELEVEL, &CMainFrame::OnToolsGoUP)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_FORWARD, &CMainFrame::OnUpdateToolsGoForward)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_BACK, &CMainFrame::OnUpdateToolsGoBack)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_UPONELEVEL, &CMainFrame::OnUpdateToolsGoUp)
	ON_COMMAND(ID_TOOLS_AUTOREFRESH, &CMainFrame::OnToolsAutoRefresh)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_AUTOREFRESH, &CMainFrame::OnUpdateToolsAutoRefresh)
	ON_COMMAND(ID_TOOLS_PREVIEW_MODE, &CMainFrame::OnToolsPreviewMode)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_PREVIEW_MODE, &CMainFrame::OnUpdateToolsPreviewMode)
	ON_COMMAND(ID_SWITCH_EPLORER_TO_ACTIVE_TAB, &CMainFrame::OnToolsSwitchFocusToActiveTab)
	ON_COMMAND(ID_TOOLS_SETROOTFOLDER, &CMainFrame::OnToolsSetRootFolder)
	ON_COMMAND(ID_TOOLS_HIDENETWORK, &CMainFrame::OnToolsHideNetwork)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDENETWORK, &CMainFrame::OnUpdateToolsHideNetwork)
	ON_COMMAND(ID_TOOLS_SHOWSHAREDFOLDERS, &CMainFrame::OnToolsShowSharedFolders)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SHOWSHAREDFOLDERS, &CMainFrame::OnUpdateToolsShowSharedFolders)
	ON_COMMAND(ID_TOOLS_SHOWALLNETWORKITEMS, &CMainFrame::OnToolsShowAllNetworkItems)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SHOWALLNETWORKITEMS, &CMainFrame::OnUpdateToolsShowAllNetworkItems)
	ON_COMMAND(ID_TOOLS_SHOWNETWORKPRINTERS, &CMainFrame::OnToolsShowNetworkPrinters)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SHOWNETWORKPRINTERS, &CMainFrame::OnUpdateToolsShowNetworkPrinters)
	ON_COMMAND(ID_TOOLS_SHOWNETWORKSHARES, &CMainFrame::OnToolsShowNetworkShares)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SHOWNETWORKSHARES, &CMainFrame::OnUpdateToolsShowNetworkShares)
	ON_COMMAND(ID_TOOLS_SHOWDRIVELABELS, &CMainFrame::OnToolsShowDriveLabels)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SHOWDRIVELABELS, &CMainFrame::OnUpdateToolsShowDriveLabels)
	ON_COMMAND(ID_TOOLS_HIDEMYCOMPUTER, &CMainFrame::OnToolsHideMyComputer)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEMYCOMPUTER, &CMainFrame::OnUpdateToolsHideMyComputer)
	ON_COMMAND(ID_TOOLS_SHOWROOTEDFOLDER, &CMainFrame::OnToolsShowRootedFolder)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SHOWROOTEDFOLDER, &CMainFrame::OnUpdateToolsShowRootedFolder)
	ON_COMMAND(ID_TOOLS_HIDEDESKTOP, &CMainFrame::OnToolsHideDesktop)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEDESKTOP, &CMainFrame::OnUpdateToolsHideDesktop)
	ON_COMMAND(ID_TOOLS_HIDEMYDOCUMENTS, &CMainFrame::OnToolsHideMyDocuments)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDEMYDOCUMENTS, &CMainFrame::OnUpdateToolsHideMyDocuments)
	ON_COMMAND(ID_TOOLS_HIDECURRENTUSERFOLDER, &CMainFrame::OnToolsHideCurrentUserFolder)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_HIDECURRENTUSERFOLDER, &CMainFrame::OnUpdateToolsHideCurrentUserFolder)
	ON_COMMAND(ID_MDI_TABBED_DOCUMENT, &CMainFrame::OnMdiTabbedDocument)
	ON_UPDATE_COMMAND_UI(ID_MDI_TABBED_DOCUMENT, &CMainFrame::OnUpdateMdiTabbedDocument)	
	ON_COMMAND(ID_APP_THEME_LIGHT, &CMainFrame::OnVinaTextThemeLight)
	ON_COMMAND(ID_APP_THEME_MONOKAI, &CMainFrame::OnVinaTextThemeMonokai)
	ON_COMMAND(ID_APP_THEME_SIERRABLUE, &CMainFrame::OnVinaTextThemeSierraBlue)
	ON_COMMAND(ID_VIEW_APP_SETTINGS, &CMainFrame::OnVinaTextSettings)
	ON_COMMAND(ID_TOOLS_SETROOTFOLDER, &CMainFrame::OnToolsSetRootFolder)
	ON_COMMAND(ID_TOOLS_REMOVE_FOLDER, &CMainFrame::OnToolsRemoveFolder)
	ON_COMMAND(ID_TOOLS_BACK_TO_ORIGINAL, &CMainFrame::OnToolsBackToOriginalExplorer)
	ON_COMMAND(ID_PATH_VINATEXT_BOOKMARK, &CMainFrame::OnToolsBookMarkAPath)
	ON_COMMAND(ID_PATH_VINATEXT_BOOKMARK_TABLE, &CMainFrame::OnToolsOpenBookMarkPathTable)
	ON_COMMAND(ID_PATH_VINATEXT, &CMainFrame::OnToolsOpenFolderVinaText)
	ON_COMMAND(ID_PATH_VINATEXT_TEMP, &CMainFrame::OnToolsOpenFolderTemp)
	ON_COMMAND(ID_PATH_VINATEXT_APPDATA, &CMainFrame::OnToolsOpenFolderAppData)
	ON_COMMAND(ID_SHORTCUT_CONTROL_PANEL, &CMainFrame::OnToolsControlPanel)
	ON_COMMAND(ID_SHORTCUT_ENVIRONMENT_PATH, &CMainFrame::OnToolsOpenEnvPath)
	ON_COMMAND(ID_SHORTCUT_WINDOW_HOST_FOLDER, &CMainFrame::OnToolsOpenHost)
	ON_COMMAND(ID_OPEN_NEW_CMD_WINDOW, &CMainFrame::OnTerminalOpenNewCMDWindow)
	ON_COMMAND(ID_OPEN_NEW_POWERSHELL_WINDOW, &CMainFrame::OnTerminalOpenNewPowerShellWindow)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CMainFrame::OnFileSendMailEx)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CMainFrame::OnUpdateFileSendMailEx)
	ON_COMMAND(ID_HOST_MS_EDGE, &CMainFrame::OnHostMSEdge)
	ON_COMMAND(ID_HOST_CHROME, &CMainFrame::OnHostGoogleChrome)
	ON_COMMAND(ID_HOST_FIREFOX, &CMainFrame::OnHostMozillaFirefox)
	ON_COMMAND(ID_HOST_MS_PAINT, &CMainFrame::OnHostMSPaint)
	ON_COMMAND(ID_HOST_FILE_EXPLORER, &CMainFrame::OnHostFileExplorer)
	ON_COMMAND(ID_HOST_MS_PPT, &CMainFrame::OnHostMSPowerpoint)
	ON_COMMAND(ID_HOST_MS_EXCEL, &CMainFrame::OnHostMSExcel)
	ON_COMMAND(ID_HOST_MS_WORD, &CMainFrame::OnHostMSWord)
	ON_COMMAND(ID_TOOL_PYTHON_PIP_WINDOW, &CMainFrame::OnToolPythonPipWindow)
	ON_COMMAND(ID_TOOL_NODEJS_NPM_WINDOW, &CMainFrame::OnToolNodeJSNPMWindow)
	ON_COMMAND(ID_TOOL_GET_SYSTEM_INFO, &CMainFrame::OnOptionsGetSystemInformation)
	ON_COMMAND(ID_TOOL_GET_WIFI_INFO, &CMainFrame::OnOptionsGetWifiInformation)
	ON_COMMAND(ID_TOOL_GET_PATH_ENV_VARIABLE_INFO, &CMainFrame::OnOptionsGetPATHVariable)

	ON_UPDATE_COMMAND_UI(ID_INDICATOR_EXPLORER_SELECTED_PATH, &CMainFrame::OnUpdateExplorerSelectedFilePath)

	// register messages
	ON_REGISTERED_MESSAGE(AFX_WM_ON_GET_TAB_TOOLTIP, &CMainFrame::OnGetTabToolTip)
	ON_REGISTERED_MESSAGE(AFX_WM_CHANGE_ACTIVE_TAB, &CMainFrame::OnAfxWmChangedActiveTab)

	// from MDI tab menu
	ON_COMMAND(ID_MDI_TAB_GET_FULL_FILE_PATH_DOUBLE_QUOTE, &CMainFrame::OnOptionGetFullFilePathDoubleQuote)
	ON_COMMAND(ID_MDI_TAB_BOOKMARK_FILE, &CMainFrame::OnDocumentBookMark)
	ON_UPDATE_COMMAND_UI(ID_MDI_TAB_BOOKMARK_FILE, &CMainFrame::OnUpdateBookmarkFile)
	ON_COMMAND(ID_MDI_TAB_CLOSE_ALL_DOC_BUT_THIS, &CMainFrame::OnCloseAllDocumentButThis)
	ON_COMMAND(ID_MDI_TAB_CLOSE_ALL_DOC, &CMainFrame::OnCloseAllDocument)
	ON_COMMAND(ID_MDI_TAB_CLOSE_ALL_DOC_LEFT, &CMainFrame::OnCloseAllDocumentLeft)
	ON_COMMAND(ID_MDI_TAB_CLOSE_ALL_DOC_RIGHT, &CMainFrame::OnCloseAllDocumentRight)
	ON_COMMAND(ID_MDI_TAB_CLOSE, &CMainFrame::OnCloseDocument)
	ON_COMMAND(ID_MDI_TAB_CLOSE_ALL_UNCHANGE_FILE, &CMainFrame::OnCloseAllDocumentUnmodified)
	ON_COMMAND(ID_MDI_TAB_DELETE_FILE, &CMainFrame::OnDeleteFile)
	ON_COMMAND(ID_MDI_TAB_GET_FULL_FILE_PATH, &CMainFrame::OnGetFullPath)
	ON_COMMAND(ID_MDI_TAB_GET_FULL_FILE_PATH_DOUBLE_SLASH, &CMainFrame::OnGetFullPathDoubleSlash)
	ON_COMMAND(ID_MDI_TAB_GET_FULL_FILE_PATH_FORWARD_SLASH, &CMainFrame::OnGetFullPathForwardSlash)
	ON_COMMAND(ID_MDI_TAB_GET_FOLDER_PATH, &CMainFrame::OnGetFolderPath)
	ON_COMMAND(ID_MDI_TAB_GET_FILE_NAME, &CMainFrame::OnGetFileName)
	ON_COMMAND(ID_MDI_TAB_GET_FILE_NAME_NO_EXTENSION, &CMainFrame::OnGetFileNameNoExtension)
	ON_COMMAND(ID_MDI_TAB_OPEN_CONTAINER_FOLDER, &CMainFrame::OnOpenContainerFolder)
	ON_UPDATE_COMMAND_UI(ID_MDI_TAB_OPEN_CONTAINER_FOLDER, &CMainFrame::OnUpdateOpenContainerFolder)
	ON_COMMAND(ID_MDI_TAB_LOCATE_IN_FILE_EXPLORER, &CMainFrame::OnOpenFileExplorer)
	ON_UPDATE_COMMAND_UI(ID_MDI_TAB_LOCATE_IN_FILE_EXPLORER, &CMainFrame::OnUpdateOpenFileEplorer)
	ON_COMMAND(ID_MDI_TAB_OPEN_CMD, &CMainFrame::OnOpenCMDHere)
	ON_COMMAND(ID_MDI_TAB_OPEN_CMD_APPEND_FILE, &CMainFrame::OnOpenCMDAppendFileName)
	ON_COMMAND(ID_MDI_TAB_OPEN_CMD_APPEND_PATH, &CMainFrame::OnOpenCMDAppendFilePath)
	ON_COMMAND(ID_MDI_TAB_OPEN_CMD_PASTE_CLIPBOARD, &CMainFrame::OnOpenCMDPasteClipboard)
	ON_COMMAND(ID_MDI_TAB_OPEN_WSL, &CMainFrame::OnOpenWSLHere)
	ON_UPDATE_COMMAND_UI(ID_MDI_TAB_OPEN_CMD_APPEND_FILE, &CMainFrame::OnUpdateOpenCMDAppendFile)
	ON_UPDATE_COMMAND_UI(ID_MDI_TAB_OPEN_CMD_APPEND_PATH, &CMainFrame::OnUpdateOpenCMDAppendFilePath)
	ON_COMMAND(ID_MDI_TAB_OPEN_POWERSHELL, &CMainFrame::OnOpenPowerShellHere)
	ON_COMMAND(ID_MDI_TAB_OPEN_GITBASH, &CMainFrame::OnOpenGitBashHere)
	ON_COMMAND(ID_MDI_TAB_SHOW_PROPERTIES, &CMainFrame::OnOpenGitFileProperties)
	ON_COMMAND(ID_MDI_TAB_RENAME, &CMainFrame::OnRenameDocument)
	ON_COMMAND(ID_MDI_TAB_RELOAD, &CMainFrame::OnReLoadDocument)
	ON_COMMAND(ID_MDI_TAB_FILE_COPY, &CMainFrame::OnCopyDocument)
	ON_UPDATE_COMMAND_UI(ID_MDI_TAB_RELOAD, &CMainFrame::OnUpdateReLoadDocument)
	ON_COMMAND(ID_MDI_TAB_NEW_VERTICAL_TAB, &CMainFrame::OnNewVerticalTabGroup)
	ON_COMMAND(ID_MDI_TAB_NEW_HORIZONTAL_TAB, &CMainFrame::OnNewHorizontalTabGroup)
	ON_COMMAND(ID_MDI_SWITCH_TO_NEXT_TAB, &CMainFrame::OnSwitchToNextTab)
	ON_COMMAND(ID_MDI_SWITCH_TO_PREVIOUS_TAB, &CMainFrame::OnSwitchToPreviousTab)
	ON_COMMAND(ID_MDI_TAB_MOVE_NEW_WINDOW, &CMainFrame::OnMDITabMoveToNewVinaText)
	ON_COMMAND(ID_MDI_TAB_MOVE_NEXT_TAB, &CMainFrame::OnMDITabMoveToNextGroup)
	ON_COMMAND(ID_MDI_TAB_MOVE_PREVIOUS_TAB, &CMainFrame::OnMDITabMoveToPreviousGroup)
	ON_COMMAND(ID_MDI_TAB_CLONE_FILE, &CMainFrame::OnMDITabCloneFile)
	ON_COMMAND(ID_MDI_TAB_MOVE_ALL_NEXT_TAB, &CMainFrame::OnMDITabMoveAllToNextGroup)
	ON_COMMAND(ID_MDI_TAB_MOVE_ALL_PREVIOUS_TAB, &CMainFrame::OnMDITabMoveAllToPreviousGroup)
	ON_COMMAND(ID_MDI_TAB_NEW_FILE, &CMainFrame::OnMDINewFile)
	ON_COMMAND(ID_MDI_TAB_NEW_FILE_VERTICAL_GROUP, &CMainFrame::OnMDINewFileInNewGroup)
	ON_COMMAND(ID_MDI_TAB_FILE_CHROME, &CMainFrame::OnMDITabOpenInChrome)
	ON_COMMAND(ID_MDI_TAB_FILE_EDGE, &CMainFrame::OnMDITabOpenInEdge)
	ON_COMMAND(ID_MDI_TAB_FILE_FIREFOX, &CMainFrame::OnMDITabOpenInFireFox)

	// windows printer
	ON_COMMAND(ID_EXPLORER_PRINT_FILE_NOW, &CMainFrame::OnPrintFileNow)
	ON_COMMAND(ID_EXPLORER_PRINT_SETUP_DLG, &CMainFrame::OnPrintFileSetupDlg)
	ON_COMMAND(ID_EXPLORER_PRINT_PAGE_DLG, &CMainFrame::OnPrintPageSetupDlg)
	ON_UPDATE_COMMAND_UI(ID_EXPLORER_PRINT_FILE_NOW, &CMainFrame::OnUpdatePrintFileNow)
	ON_UPDATE_COMMAND_UI(ID_EXPLORER_PRINT_SETUP_DLG, &CMainFrame::OnUpdatePrintFileSetupDlg)
	ON_UPDATE_COMMAND_UI(ID_EXPLORER_PRINT_PAGE_DLG, &CMainFrame::OnUpdatePrintPageSetupDlg)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	CMFCPopupMenu::SetForceShadow(TRUE);
	m_bCanConvertControlBarToMDIChild = TRUE; // for converting docking pane to document tab
	// Font initiating
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	_tcscpy_s(lf.lfFaceName, 32 * sizeof(CHAR), AppSettingMgr.m_DockWindowFontSetting._font);
	lf.lfHeight = AppSettingMgr.m_DockWindowFontSetting._lfHeight;
	lf.lfWeight = AppSettingMgr.m_DockWindowFontSetting._lfWeight;
	m_Font.CreateFontIndirect(&lf);
}

CMainFrame::~CMainFrame()
{
}

LRESULT CMainFrame::OnMainFrameUpdate(WPARAM wParam, LPARAM lParam)
{
	WORD wMsgTarget = LOWORD(wParam);
	WORD wMsgHint = HIWORD(wParam);
	CDocument* pDoc = (CDocument*)lParam;

	switch (wMsgTarget)
	{
	case MAIN_FRAME_UPDATE_MSG::MAIN_FRAME_UPDATE_ALL_DOCKPANE:
		if (m_wndBuildWindow.GetSafeHwnd())
		{
			m_wndBuildWindow.SendMessage(UMW_DOCK_PANE_UPDATE, wParam, lParam);
		}
		if (m_wndFileExplorer.GetSafeHwnd())
		{
			m_wndFileExplorer.SendMessage(UMW_DOCK_PANE_UPDATE, wParam, lParam);
		}
		if (m_wndMessageWindow.GetSafeHwnd())
		{
			m_wndMessageWindow.SendMessage(UMW_DOCK_PANE_UPDATE, wParam, lParam);
		}
		if (m_wndSearchAndReplaceWindow.GetSafeHwnd())
		{
			m_wndSearchAndReplaceWindow.SendMessage(UMW_DOCK_PANE_UPDATE, wParam, lParam);
		}
		if (m_wndSearchResultPane.GetSafeHwnd())
		{
			m_wndSearchResultPane.SendMessage(UMW_DOCK_PANE_UPDATE, wParam, lParam);
		}
		if (m_wndBookmarkWindow.GetSafeHwnd())
		{
			m_wndBookmarkWindow.SendMessage(UMW_DOCK_PANE_UPDATE, wParam, lParam);
		}
		if (m_wndBreakpointWindow.GetSafeHwnd())
		{
			m_wndBreakpointWindow.SendMessage(UMW_DOCK_PANE_UPDATE, wParam, lParam);
		}
		if (m_wndPathResultWindow.GetSafeHwnd())
		{
			m_wndPathResultWindow.SendMessage(UMW_DOCK_PANE_UPDATE, wParam, lParam);
		}
		break;
	}
	return 0;
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIFrameWndEx::OnSize(nType, cx, cy);
}

void CMainFrame::OnMoving(UINT nSide, LPRECT lpRect)
{
	CMDIFrameWndEx::OnMoving(nSide, lpRect);
	ResizeQuickSearchDialog();
}

void CMainFrame::OnDropFiles(HDROP hDropInfo)
{
	if (hDropInfo)
	{
		int nNumberIntances = ::DragQueryFileW(hDropInfo, 0xffffffff, NULL, 0);
		std::vector<CString> vecFolder;
		std::vector<CString> vecFile;
		for (int i = 0; i < nNumberIntances; ++i)
		{
			TCHAR szFileName[MAX_PATH];
			::DragQueryFileW(hDropInfo, i, szFileName, MAX_PATH);
			if (::PathIsDirectory(szFileName))
			{
				size_t len = lstrlen(szFileName);
				if (len > 0 && szFileName[len - 1] != TCHAR('\\'))
				{
					szFileName[len] = TCHAR('\\');
					szFileName[len + 1] = TCHAR('\0');
				}
				vecFolder.push_back(szFileName);
			}
			else
			{
				vecFile.push_back(szFileName);
			}
		}

		for (auto const& file : vecFile)
		{
			if (PathFileExists(file))
			{
				AppUtils::CreateDocumentFromFile(file);
			}
		}

		if (vecFolder.size() > 0)
		{
			for (auto const& folder : vecFolder)
			{
				if (PathFileExists(folder))
				{
					GetFileExplorerCtrl().AddMoreFolderToWorkSpace(folder);
				}
			}
		}

		if (::IsIconic(m_hWnd))
		{
			::ShowWindow(m_hWnd, SW_RESTORE);
		}
		::SetForegroundWindow(m_hWnd);
	}
	DragFinish(hDropInfo);
}

void CMainFrame::OnClose()
{
	AppSettingMgr.ResetRecentEditorInfo();
	m_bIsClosingVinaText = TRUE;
	SaveMDIState(theApp.GetRegSectionPath());
	theApp.SaveOpenedFolderData();
	CMDIFrameWndEx::OnClose();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid = FALSE;

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_VS2005; // other styles available...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // set to FALSE to place close button at right of tab area
	mdiTabParams.m_bTabIcons = TRUE;    // set to TRUE to enable document icons on MDI taba
	mdiTabParams.m_bAutoColor = FALSE;    // set to FALSE to disable auto-coloring of MDI tabs
	mdiTabParams.m_bDocumentMenu = TRUE; // enable the document menu at the right edge of the tab area
	mdiTabParams.m_bTabCustomTooltips = TRUE;
	mdiTabParams.m_bEnableTabSwap = TRUE;
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	//if (!m_wndMenuBar.Create(this))
	//{
	//	TRACE0("Failed to create menubar\n");
	//	return -1;      // fail to create
	//}

	//m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);
	
	VERIFY(m_MainMenu.LoadMenu(IDR_MAINFRAME)); // load main menu bar
	AppTranslator.ToNativeContextMenu(&m_MainMenu); // translate to native language
	SetMenu(&m_MainMenu); // set back to mainframe

	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	// Create main toolbar:
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) || !m_wndToolBar.LoadToolBar(IDR_MAINFRAME_24))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// Create status bar:
	if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(g_Statusbar_Indicators, sizeof(g_Statusbar_Indicators) / sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetFont(&m_Font);

	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// set the visual manager used to draw all user interface elements
	switch (AppSettingMgr.m_ApplicationThemeLook)
	{
	case APPLICATION_THEME_LOOK::THEME_OFFICE_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		break;

	case APPLICATION_THEME_LOOK::THEME_VISUAL_STUDIO_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CMFCVisualManagerVS2005::m_bRoundedAutohideButtons = FALSE;
		break;

	case APPLICATION_THEME_LOOK::THEME_WINDOWS_XP_NATIVE:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		break;

	case APPLICATION_THEME_LOOK::THEME_OFFICE_2007_LUNA_BLUE:
		CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		break;

	case APPLICATION_THEME_LOOK::THEME_OFFICE_2007_OBSIDIAN_BLACK:
		CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		break;

	case APPLICATION_THEME_LOOK::THEME_OFFICE_2007_AQUA:
		CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		break;

	case APPLICATION_THEME_LOOK::THEME_OFFICE_2007_SILVER_LOOK:
		CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		break;

	case APPLICATION_THEME_LOOK::THEME_VISUAL_STUDIO_2008_LOOK:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		break;
	}
	CDockingManager::SetDockingMode(DT_SMART);

	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL, NULL, NULL);

	// Enable enhanced windows management dialog
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// Enable toolbar and docking window menu replacement
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// Allow user-defined toolbars operations:
	//InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	// Enable quick (Alt+drag) toolbar customization
	CMFCToolBar::EnableQuickCustomization();

	// Create docking control windows:
	if (!CreateDockingBars())
	{
		return -1;
	}

	// TODO: Delete these five lines if you don't want the toolbar and menubar to be dockable
	//DockPane(&m_wndMenuBar);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndToolBar);
	ShowPane(&m_wndToolBar, TRUE, FALSE, TRUE);

	// Switch the order of document name and application name on the window title bar. This
	// improves the usability of the taskbar because the document name is visible with the thumbnail.
	ModifyStyle(0, FWS_PREFIXTITLE);

	EnableFullScreenMode(ID_EDITOR_FULL_SCREEN_MODE);
	EnableFullScreenMainMenu(FALSE);
	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	RecalcLayout();

	// for auto save document...
	EnableAutoSaveDocument();

	return 0;
}

unsigned __stdcall PreCheckBeforeSaveDocument(void* pArguments)
{
	// perform any check before saving...
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->EnableStartSaveDocumentTimer();
	_endthreadex(0);
	return 0;
}

void CMainFrame::EnableStartSaveDocumentTimer()
{
	KillTimer(START_SAVE_DOCUMENT_TIMER);
	SetTimer(START_SAVE_DOCUMENT_TIMER, 1, NULL);
}

void CMainFrame::UpdateFoldingMap(BOOL bActiveDialogTab)
{
	if (m_wndSearchAndReplaceWindow.GetSafeHwnd())
	{
		if (bActiveDialogTab)
		{
			ShowPane(&m_wndSearchAndReplaceWindow, TRUE, FALSE, TRUE);
		}
		m_wndSearchAndReplaceWindow.UpdateFoldingMap(bActiveDialogTab);
	}
}

void CMainFrame::ShowErrorLineOnEditor()
{
	if (m_wndBuildWindow.GetSafeHwnd())
	{
		m_wndBuildWindow.ShowErrorLineOnEditor();
	}
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == AUTO_SAVE_DOCUMENT_TIMER)
	{
		CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
		if (pDoc == NULL) return;

		KillTimer(AUTO_SAVE_DOCUMENT_TIMER);

		CEditorDoc* pEditorDoc = NULL;
		if (pDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
		{
			pEditorDoc = dynamic_cast<CEditorDoc*>(pDoc);
		}

		if (pEditorDoc) 
		{
			HANDLE hThread;
			unsigned threadID;
			hThread = (HANDLE)_beginthreadex(NULL, 0, &PreCheckBeforeSaveDocument, pEditorDoc, 0, &threadID);
			CloseHandle(hThread);
		}
	}
	else if (nIDEvent == START_SAVE_DOCUMENT_TIMER)
	{
		KillTimer(START_SAVE_DOCUMENT_TIMER);

		// start save all document...
		POSITION pos = AfxGetApp()->GetFirstDocTemplatePosition();
		while (pos)
		{
			CDocTemplate* pDocTemplate = AfxGetApp()->GetNextDocTemplate(pos);
			if (pDocTemplate)
			{
				POSITION posDoc = pDocTemplate->GetFirstDocPosition();
				while (posDoc)
				{
					CDocument* pDoc = pDocTemplate->GetNextDoc(posDoc);
					if (pDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
					{
						CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(pDoc);
						if (pEditorDoc)
						{
							CString strDocName = pDoc->GetTitle();
							strDocName.Replace(_T("*"), _T(""));
							strDocName.Trim();
							CString strDocFile = pDoc->GetPathName();
							if (PathFileExists(strDocFile))
							{
								pEditorDoc->SetPathName(strDocFile);
								if (pEditorDoc->OnSaveDocument(strDocFile))
								{
									pEditorDoc->SetModifiedFlag(FALSE);
									CString strMessage = _T("> Auto save file ") + strDocName;
									LOG_OUTPUT_MESSAGE_WITH_TIME(strMessage);
								}
							}
							else
							{
								CString strTempFilePath = PathUtils::GetVinaTextTempPath();
								if (PathFileExists(strTempFilePath))
								{
									CString strFileSave = strTempFilePath + strDocName;
									if (pEditorDoc->OnSaveDocument(strFileSave))
									{
										pEditorDoc->SetPathName(strFileSave);
										pEditorDoc->SetModifiedFlag(FALSE);
										CString strMessage = _T("> Auto save file ") + strDocName;
										LOG_OUTPUT_MESSAGE_WITH_TIME(strMessage);
									}
								}
							}
						}
					}
				}
			}
		}
		EnableAutoSaveDocument();
	}

	CMDIFrameWndEx::OnTimer(nIDEvent);
}

#if 0
BOOL CMainFrame::OnShowPopupMenu(CMFCPopupMenu* pMenuPopup)
{
	BOOL bRes = CMDIFrameWndEx::OnShowPopupMenu(pMenuPopup);
	if (pMenuPopup != NULL)
	{
		CMFCPopupMenuBar* pMenuBar = pMenuPopup->GetMenuBar(); ASSERT(pMenuBar != NULL);
		if (pMenuBar != NULL)
		{
			HMENU hMenu = pMenuBar->ExportToMenu(); ASSERT(hMenu != NULL);
			if (hMenu != NULL)
			{
				CMenu* pSubMenu = CMenu::FromHandle(hMenu); ASSERT(pSubMenu != NULL);
				if (pSubMenu)
				{
					AppTranslator.ToNativeContextMenu(pSubMenu);
				}
				pMenuBar->ImportFromMenu(hMenu);
				::DestroyMenu(hMenu);
			}
		}
	}
	return bRes;
}
#endif

void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	CBaseDoc* pDoc = dynamic_cast<CBaseDoc*>(AppUtils::GetMDIActiveDocument());
	CString strFilePath;
	CString strTitle;
	if (pDoc)
	{
		strFilePath = pDoc->GetPathName();
		CString strDocTitle = pDoc->GetTitle();
		if (pDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
		{
			CString strUnSaved;
			if (strDocTitle.Replace(_T("*"), _T("*")))
			{
				strUnSaved = _T("*");
			}
			else
			{
				strUnSaved = _T("");
			}

			if (!strFilePath.IsEmpty())
			{
				strTitle = _T("VinaText || ") + strFilePath + strUnSaved;
			}
			else
			{
				strFilePath = pDoc->GetTitle();
				strFilePath.Replace(_T("*"), _T(""));
				strTitle = _T("VinaText || ") + strFilePath + strUnSaved;
			}
		}
		else
		{
			if (!strFilePath.IsEmpty())
			{
				strTitle = _T("VinaText || ") + strFilePath;
			}
			else
			{
				strFilePath = pDoc->GetTitle();
				strFilePath.Replace(_T("*"), _T(""));
				strTitle = _T("VinaText || ") + strFilePath;
			}
		}
	}
	else
	{
		strTitle = _T("VinaText || Non Existent Tab");
	}
	SetWindowText(strTitle);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CMDIFrameWndEx::PreCreateWindow(cs))
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

void CMainFrame::OnFullScreeenMode()
{
	CMDIFrameWndEx::ShowFullScreen();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp, LPARAM lp)
{
	LRESULT lres = CMDIFrameWndEx::OnToolbarCreateNew(wp, lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

LRESULT CMainFrame::OnCopyData(WPARAM wParam, LPARAM lParam)
{
	PCOPYDATASTRUCT pCDS = (PCOPYDATASTRUCT)lParam;
	if (pCDS->dwData == 1) 
	{
		TCHAR szBuf[4096];
		memcpy(szBuf, pCDS->lpData, sizeof(TCHAR)*(size_t)pCDS->cbData);
		szBuf[pCDS->cbData] = 0; // end string buffer...
	}
	return FALSE;
}

void CMainFrame::OnMdiTabbedDocument()
{
	CMDIChildWndEx* pMDIChild = DYNAMIC_DOWNCAST(CMDIChildWndEx, MDIGetActive());
	if (pMDIChild == NULL) return;
	TabbedDocumentToControlBar(pMDIChild);
}

void CMainFrame::OnUpdateMdiTabbedDocument(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck();
}

void CMainFrame::OnViewFileExplorerWindow()
{
	ShowPane(&m_wndFileExplorer, !m_wndFileExplorer.IsVisible(), FALSE, TRUE);
	m_wndFileExplorer.SetActiveWindow();
	RecalcLayout();
}

void CMainFrame::OnQuickSearch()
{
	CEditorView* pView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
	if (pView)
	{
		ShowQuickSearchDialog(SEARCH_REPLACE_GOTO_DLG_TYPE::SEARCH);
	}
}

void CMainFrame::OnQuickReplace()
{
	CEditorView* pView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
	if (pView)
	{
		ShowQuickSearchDialog(SEARCH_REPLACE_GOTO_DLG_TYPE::REPLACE);
	}
}

void CMainFrame::OnCleanUpAllWindows()
{
	ClearDataOnDockPane(DOCKABLE_PANE_TYPE::BUILD_PANE);
	ClearDataOnDockPane(DOCKABLE_PANE_TYPE::LOG_MESSAGE_PANE);
	ClearDataOnDockPane(DOCKABLE_PANE_TYPE::SEARCH_RESULT_PANE);
	ClearDataOnDockPane(DOCKABLE_PANE_TYPE::SEARCH_AND_REPLACE_PANE);
	ClearDataOnDockPane(DOCKABLE_PANE_TYPE::BOOKMARK_PANE);
	ClearDataOnDockPane(DOCKABLE_PANE_TYPE::BREAKPOINT_PANE);
	ClearDataOnDockPane(DOCKABLE_PANE_TYPE::PATH_RESULT_PANE);
}

void CMainFrame::OnHideAllWindows()
{
	ShowPane(&m_wndMessageWindow, FALSE, FALSE, FALSE);
	ShowPane(&m_wndFileExplorer, FALSE, FALSE, FALSE);
	ShowPane(&m_wndSearchAndReplaceWindow, FALSE, FALSE, FALSE);
	ShowPane(&m_wndSearchResultPane, FALSE, FALSE, FALSE);
	ShowPane(&m_wndBuildWindow, FALSE, FALSE, FALSE);
	ShowPane(&m_wndBookmarkWindow, FALSE, FALSE, FALSE);
	ShowPane(&m_wndPathResultWindow, FALSE, FALSE, FALSE);
	ShowPane(&m_wndBreakpointWindow, FALSE, FALSE, FALSE);
	m_wndFileExplorer.SetActiveWindow();
	RecalcLayout();
}

void CMainFrame::OnShowAllWindows()
{
	ShowPane(&m_wndMessageWindow, TRUE, FALSE, TRUE);
	ShowPane(&m_wndFileExplorer, TRUE, FALSE, TRUE);
	ShowPane(&m_wndSearchAndReplaceWindow, TRUE, FALSE, TRUE);
	ShowPane(&m_wndSearchResultPane, TRUE, FALSE, TRUE);
	ShowPane(&m_wndBuildWindow, TRUE, FALSE, TRUE);
	ShowPane(&m_wndBookmarkWindow, TRUE, FALSE, TRUE);
	ShowPane(&m_wndPathResultWindow, TRUE, FALSE, TRUE);
	ShowPane(&m_wndBreakpointWindow, TRUE, FALSE, TRUE);
	m_wndFileExplorer.SetActiveWindow();
	RecalcLayout();
}

void CMainFrame::UpdateUIForEditorView(CCmdUI * pCmdUI)
{
	CEditorView* pEditorView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
	if (pEditorView)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnUpdateQuickSearch(CCmdUI * pCmdUI)
{
	UpdateUIForEditorView(pCmdUI);
}

void CMainFrame::OnUpdateQuickReplace(CCmdUI * pCmdUI)
{
	UpdateUIForEditorView(pCmdUI);
}

void CMainFrame::OnUpdateViewFileExplorerWindow(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_wndFileExplorer.IsVisible());
}

void CMainFrame::OnViewOutputPane()
{
	ShowPane(&m_wndMessageWindow, !m_wndMessageWindow.IsVisible(), FALSE, TRUE);
	m_wndMessageWindow.SetActiveWindow();
	RecalcLayout();
}

void CMainFrame::OnUpdateViewOutputPane(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_wndMessageWindow.IsVisible());
}

void CMainFrame::OnViewBookmarkPane()
{
	ShowPane(&m_wndBookmarkWindow, !m_wndBookmarkWindow.IsVisible(), FALSE, TRUE);
	m_wndBookmarkWindow.SetActiveWindow();
	RecalcLayout();
}

void CMainFrame::OnUpdateViewBookmarkPane(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_wndBookmarkWindow.IsVisible());
}

void CMainFrame::OnViewBreakpointPane()
{
	ShowPane(&m_wndBreakpointWindow, !m_wndBreakpointWindow.IsVisible(), FALSE, TRUE);
	m_wndBreakpointWindow.SetActiveWindow();
	RecalcLayout();
}

void CMainFrame::OnUpdateViewBreakpointPane(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_wndBreakpointWindow.IsVisible());
}

void CMainFrame::OnViewFileResultPane()
{
	ShowPane(&m_wndPathResultWindow, !m_wndPathResultWindow.IsVisible(), FALSE, TRUE);
	m_wndPathResultWindow.SetActiveWindow();
	RecalcLayout();
}

void CMainFrame::OnUpdateViewFileResultPane(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_wndPathResultWindow.IsVisible());
}

void CMainFrame::OnUpdateViewSearchResultPane(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_wndSearchResultPane.IsVisible());
}

void CMainFrame::OnViewBuildPane()
{
	ShowPane(&m_wndBuildWindow, !m_wndBuildWindow.IsVisible(), FALSE, TRUE);
	m_wndBuildWindow.SetActiveWindow();
	RecalcLayout();
}

void CMainFrame::OnUpdateViewBuildPane(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_wndBuildWindow.IsVisible());
}

void CMainFrame::OnViewSearchResultPane()
{
	ShowPane(&m_wndSearchResultPane, !m_wndSearchResultPane.IsVisible(), FALSE, TRUE);
	m_wndSearchResultPane.SetActiveWindow();
	RecalcLayout();
}

void CMainFrame::OnViewSearchAndReplaceWindow()
{
	ShowPane(&m_wndSearchAndReplaceWindow, !m_wndSearchAndReplaceWindow.IsVisible(), FALSE, TRUE);
	m_wndSearchAndReplaceWindow.SetActiveWindow();
	RecalcLayout();
}

void CMainFrame::OnUpdateViewSearchAndReplaceWindow(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_wndSearchAndReplaceWindow.IsVisible());
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
{
	if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	// add some tools for example....
	/*CUserToolsManager* pUserToolsManager = theApp.GetUserToolsManager();
	if (pUserToolsManager != NULL && pUserToolsManager->GetUserTools().IsEmpty())
	{
		CCustomizeUserTool* pTool1 = (CCustomizeUserTool*)pUserToolsManager->CreateNewTool();
		if (pTool1)
		{
			pTool1->m_strLabel = _T("Resource Manager");
			pTool1->SetCommand(_T("perfmon.exe"));
		}

		CCustomizeUserTool* pTool2 = (CCustomizeUserTool*)pUserToolsManager->CreateNewTool();
		if (pTool2)
		{
			pTool2->m_strLabel = _T("System Cleanup Manager");
			pTool2->SetCommand(_T("cleanmgr.exe"));
		}

		CCustomizeUserTool* pTool3 = (CCustomizeUserTool*)pUserToolsManager->CreateNewTool();
		if (pTool3)
		{
			pTool3->m_strLabel = _T("Task Scheduler");
			pTool3->SetCommand(_T("taskschd.msc"));
		}

		CCustomizeUserTool* pTool4 = (CCustomizeUserTool*)pUserToolsManager->CreateNewTool();
		if (pTool4)
		{
			pTool4->m_strLabel = _T("Character Map");
			pTool4->SetCommand(_T("charmap.exe"));
		}

		CCustomizeUserTool* pTool5 = (CCustomizeUserTool*)pUserToolsManager->CreateNewTool();
		if (pTool5)
		{
			pTool5->m_strLabel = _T("System Information");
			pTool5->SetCommand(_T("msinfo32.exe"));
		}

		CCustomizeUserTool* pTool6 = (CCustomizeUserTool*)pUserToolsManager->CreateNewTool();
		if (pTool6)
		{
			pTool6->m_strLabel = _T("Computer Manager");
			pTool6->SetCommand(_T("compmgmt.msc"));
		}

		CCustomizeUserTool* pTool7 = (CCustomizeUserTool*)pUserToolsManager->CreateNewTool();
		if (pTool7)
		{
			pTool7->m_strLabel = _T("User Action Recorder");
			pTool7->SetCommand(_T("psr.exe"));
		}

		CCustomizeUserTool* pTool8 = (CCustomizeUserTool*)pUserToolsManager->CreateNewTool();
		if (pTool8)
		{
			pTool8->m_strLabel = _T("Window Registry Editor");
			pTool8->SetCommand(_T("regedit.exe"));
		}
	}*/
	// enable customization button for all user toolbars
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	//for (int i = 0; i < iMaxUserToolbars; i++)
	//{
	//	CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
	//	if (pUserToolbar != NULL)
	//	{
	//		pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	//	}
	//}
	// explicitly restore toolbar state
	m_wndToolBar.RestoreOriginalState();
	return TRUE;
}

void CMainFrame::OnToolsAllowDelete() noexcept
{
	GetFileExplorerCtrl().SetAllowDelete(!GetFileExplorerCtrl().GetAllowDelete());
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsAllowDelete(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetAllowDelete());
}

void CMainFrame::OnToolsAllowOpen() noexcept
{
	GetFileExplorerCtrl().SetAllowOpen(!GetFileExplorerCtrl().GetAllowOpen());
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsAllowOpen(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetAllowOpen());
}

void CMainFrame::OnToolsAllowRename() noexcept
{
	GetFileExplorerCtrl().SetAllowRename(!GetFileExplorerCtrl().GetAllowRename());
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsAllowRename(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetAllowRename());
}

void CMainFrame::OnToolsAllowProperties() noexcept
{
	GetFileExplorerCtrl().SetAllowProperties(!GetFileExplorerCtrl().GetAllowProperties());
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsAllowProperties(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetAllowProperties());
}

void CMainFrame::OnToolsShowFiles()
{
	GetFileExplorerCtrl().SetShowFiles(!GetFileExplorerCtrl().GetShowFiles());
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsShowFiles(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetShowFiles());
}

void CMainFrame::OnToolsAllowCreateFolder() noexcept
{
	GetFileExplorerCtrl().SetAllowCreateFolder(!GetFileExplorerCtrl().GetAllowCreateFolder());
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsAllowCreateFolder(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetAllowCreateFolder());
}

void CMainFrame::OnToolsAllowDragDrop() noexcept
{
	GetFileExplorerCtrl().SetAllowDragDrop(!GetFileExplorerCtrl().GetAllowDragDrop());
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsAllowDragDrop(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetAllowDragDrop());
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	//Give the control first crack
	//if (GetFileExplorerCtrl().OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	//	return TRUE;
	return CMDIFrameWndEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnToolsHideCDROM()
{
	if (GetFileExplorerCtrl().GetDriveHideFlags() & CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_CDROM)
		GetFileExplorerCtrl().SetDriveHideFlags(GetFileExplorerCtrl().GetDriveHideFlags() & ~CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_CDROM);
	else
		GetFileExplorerCtrl().SetDriveHideFlags(GetFileExplorerCtrl().GetDriveHideFlags() | CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_CDROM);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideCDROM(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetDriveHideFlags() & CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_CDROM);
}

void CMainFrame::OnToolsHideFixed()
{
	if (GetFileExplorerCtrl().GetDriveHideFlags() & CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_FIXED)
		GetFileExplorerCtrl().SetDriveHideFlags(GetFileExplorerCtrl().GetDriveHideFlags() & ~CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_FIXED);
	else
		GetFileExplorerCtrl().SetDriveHideFlags(GetFileExplorerCtrl().GetDriveHideFlags() | CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_FIXED);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideFixed(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetDriveHideFlags() & CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_FIXED);
}

void CMainFrame::OnToolsHideRAMDisks()
{
	if (GetFileExplorerCtrl().GetDriveHideFlags() & CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_RAMDISK)
		GetFileExplorerCtrl().SetDriveHideFlags(GetFileExplorerCtrl().GetDriveHideFlags() & ~CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_RAMDISK);
	else
		GetFileExplorerCtrl().SetDriveHideFlags(GetFileExplorerCtrl().GetDriveHideFlags() | CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_RAMDISK);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideRAMDisks(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetDriveHideFlags() & CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_RAMDISK);
}

void CMainFrame::OnToolsHideRemovable()
{
	if (GetFileExplorerCtrl().GetDriveHideFlags() & CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_REMOVABLE)
		GetFileExplorerCtrl().SetDriveHideFlags(GetFileExplorerCtrl().GetDriveHideFlags() & ~CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_REMOVABLE);
	else
		GetFileExplorerCtrl().SetDriveHideFlags(GetFileExplorerCtrl().GetDriveHideFlags() | CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_REMOVABLE);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideRemovable(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetDriveHideFlags() & CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_REMOVABLE);
}

void CMainFrame::OnToolsHideRemote()
{
	if (GetFileExplorerCtrl().GetDriveHideFlags() & CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_REMOTE)
		GetFileExplorerCtrl().SetDriveHideFlags(GetFileExplorerCtrl().GetDriveHideFlags() & ~CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_REMOTE);
	else
		GetFileExplorerCtrl().SetDriveHideFlags(GetFileExplorerCtrl().GetDriveHideFlags() | CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_REMOTE);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideRemote(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetDriveHideFlags() & CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_REMOTE);
}

void CMainFrame::OnToolsHideHidden()
{
	if (GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_HIDDEN)
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() & ~FILE_ATTRIBUTE_HIDDEN);
	else
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() | FILE_ATTRIBUTE_HIDDEN);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideHidden(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_HIDDEN);
}

void CMainFrame::OnToolsHideArchive()
{
	if (GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_ARCHIVE)
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() & ~FILE_ATTRIBUTE_ARCHIVE);
	else
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() | FILE_ATTRIBUTE_ARCHIVE);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideArchive(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_ARCHIVE);
}

void CMainFrame::OnToolsHideCompressed()
{
	if (GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_COMPRESSED)
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() & ~FILE_ATTRIBUTE_COMPRESSED);
	else
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() | FILE_ATTRIBUTE_COMPRESSED);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideCompressed(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_COMPRESSED);
}

void CMainFrame::OnToolsHideSystem()
{
	if (GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_SYSTEM)
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() & ~FILE_ATTRIBUTE_SYSTEM);
	else
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() | FILE_ATTRIBUTE_SYSTEM);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideSystem(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_SYSTEM);
}

void CMainFrame::OnToolsHideTemporary()
{
	if (GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_TEMPORARY)
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() & ~FILE_ATTRIBUTE_TEMPORARY);
	else
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() | FILE_ATTRIBUTE_TEMPORARY);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideTemporary(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_TEMPORARY);
}

void CMainFrame::OnToolsHideEncrypted()
{
	if (GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_ENCRYPTED)
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() & ~FILE_ATTRIBUTE_ENCRYPTED);
	else
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() | FILE_ATTRIBUTE_ENCRYPTED);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideEncrypted(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_ENCRYPTED);
}

void CMainFrame::OnToolsHideOffline()
{
	if (GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_OFFLINE)
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() & ~FILE_ATTRIBUTE_OFFLINE);
	else
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() | FILE_ATTRIBUTE_OFFLINE);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideOffline(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_OFFLINE);
}

void CMainFrame::OnToolsHideReadOnly()
{
	if (GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_READONLY)
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() & ~FILE_ATTRIBUTE_READONLY);
	else
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() | FILE_ATTRIBUTE_READONLY);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideReadOnly(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_READONLY);
}

void CMainFrame::OnToolsHideReparsePoint()
{
	if (GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_REPARSE_POINT)
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() & ~FILE_ATTRIBUTE_REPARSE_POINT);
	else
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() | FILE_ATTRIBUTE_REPARSE_POINT);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideReparsePoint(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_REPARSE_POINT);
}

void CMainFrame::OnToolsHideSparse()
{
	if (GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_SPARSE_FILE)
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() & ~FILE_ATTRIBUTE_SPARSE_FILE);
	else
		GetFileExplorerCtrl().SetFileHideFlags(GetFileExplorerCtrl().GetFileHideFlags() | FILE_ATTRIBUTE_SPARSE_FILE);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideSparse(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFileHideFlags() & FILE_ATTRIBUTE_SPARSE_FILE);
}

void CMainFrame::OnToolsHideHidden2()
{
	if (GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_HIDDEN)
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() & ~FILE_ATTRIBUTE_HIDDEN);
	else
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() | FILE_ATTRIBUTE_HIDDEN);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideHidden2(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_HIDDEN);
}

void CMainFrame::OnToolsHideArchive2()
{
	if (GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_ARCHIVE)
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() & ~FILE_ATTRIBUTE_ARCHIVE);
	else
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() | FILE_ATTRIBUTE_ARCHIVE);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideArchive2(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_ARCHIVE);
}

void CMainFrame::OnToolsHideCompressed2()
{
	if (GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_COMPRESSED)
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() & ~FILE_ATTRIBUTE_COMPRESSED);
	else
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() | FILE_ATTRIBUTE_COMPRESSED);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideCompressed2(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_COMPRESSED);
}

void CMainFrame::OnToolsHideSystem2()
{
	if (GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_SYSTEM)
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() & ~FILE_ATTRIBUTE_SYSTEM);
	else
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() | FILE_ATTRIBUTE_SYSTEM);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideSystem2(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_SYSTEM);
}

void CMainFrame::OnToolsHideTemporary2()
{
	if (GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_TEMPORARY)
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() & ~FILE_ATTRIBUTE_TEMPORARY);
	else
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() | FILE_ATTRIBUTE_TEMPORARY);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideTemporary2(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_TEMPORARY);
}

void CMainFrame::OnToolsHideEncrypted2()
{
	if (GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_ENCRYPTED)
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() & ~FILE_ATTRIBUTE_ENCRYPTED);
	else
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() | FILE_ATTRIBUTE_ENCRYPTED);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideEncrypted2(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_ENCRYPTED);
}

void CMainFrame::OnToolsHideOffline2()
{
	if (GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_OFFLINE)
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() & ~FILE_ATTRIBUTE_OFFLINE);
	else
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() | FILE_ATTRIBUTE_OFFLINE);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideOffline2(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_OFFLINE);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnToolsHideReadOnly2()
{
	if (GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_READONLY)
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() & ~FILE_ATTRIBUTE_READONLY);
	else
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() | FILE_ATTRIBUTE_READONLY);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideReadOnly2(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_READONLY);
}


void CMainFrame::OnToolsHideReparsePoint2()
{
	if (GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_REPARSE_POINT)
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() & ~FILE_ATTRIBUTE_REPARSE_POINT);
	else
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() | FILE_ATTRIBUTE_REPARSE_POINT);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideReparsePoint2(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_REPARSE_POINT);
}

void CMainFrame::OnToolsHideSparse2()
{
	if (GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_SPARSE_FILE)
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() & ~FILE_ATTRIBUTE_SPARSE_FILE);
	else
		GetFileExplorerCtrl().SetFolderHideFlags(GetFileExplorerCtrl().GetFolderHideFlags() | FILE_ATTRIBUTE_SPARSE_FILE);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideSparse2(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetFolderHideFlags() & FILE_ATTRIBUTE_SPARSE_FILE);
}

void CMainFrame::OnToolsAutoRefresh()
{
	GetFileExplorerCtrl().SetAutoRefresh(!GetFileExplorerCtrl().GetAutoRefresh());
}

void CMainFrame::OnToolsPreviewMode()
{
	TOGGLE_FLAG(AppSettingMgr.m_bEnablePreviewFile);
}

void CMainFrame::OnToolsSwitchFocusToActiveTab()
{
	GetFileExplorerCtrl().OnSetFocusActiveMDITab();
}

void CMainFrame::OnUpdateToolsPreviewMode(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(AppSettingMgr.m_bEnablePreviewFile);
}

void CMainFrame::OnToolsRefresh()
{
	GetFileExplorerCtrl().Refresh();
}

void CMainFrame::OnToolsGoForward()
{
	GetFileExplorerCtrl().OnForward();
}

void CMainFrame::OnToolsGoBack()
{
	GetFileExplorerCtrl().OnBack();
}

void CMainFrame::OnToolsGoUP()
{
	GetFileExplorerCtrl().OnUpOneLevel();
}

void CMainFrame::OnUpdateToolsGoUp(CCmdUI * pCmdUI)
{
	GetFileExplorerCtrl().OnUpdateUpOneLevel(pCmdUI);
}

void CMainFrame::OnUpdateToolsGoForward(CCmdUI * pCmdUI)
{
	GetFileExplorerCtrl().OnUpdateForward(pCmdUI);
}

void CMainFrame::OnUpdateToolsGoBack(CCmdUI * pCmdUI)
{
	GetFileExplorerCtrl().OnUpdateBack(pCmdUI);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsAutoRefresh(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetAutoRefresh());
}

void CMainFrame::OnToolsHideNetwork()
{
	GetFileExplorerCtrl().SetShowNetwork(!GetFileExplorerCtrl().GetShowNetwork());
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideNetwork(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(!GetFileExplorerCtrl().GetShowNetwork());
}

void CMainFrame::OnToolsShowSharedFolders()
{
	GetFileExplorerCtrl().SetUsingDifferentIconForSharedFolders(!GetFileExplorerCtrl().GetUsingDifferentIconForSharedFolders());
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsShowSharedFolders(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetUsingDifferentIconForSharedFolders());
}

void CMainFrame::OnToolsSetRootFolder()
{
	GetFileExplorerCtrl().SetAsWorkspaceFolder();
}

#pragma warning(suppress: 26434)
void CMainFrame::OnDestroy()
{
	// kill all worker thread...
	FinalizeWorkerThread();

	// save some GUI settings to registry...
	CWinApp* pApp = AfxGetApp();
#pragma warning(suppress: 26496)
	AFXASSUME(pApp != NULL);
	if (!pApp) return;

	// save explorer pane status
	if (GetFileExplorerCtrl().GetSafeHwnd())
	{
		CString sSelPath(GetFileExplorerCtrl().GetSelectedPath());
		CString sRootFolder(GetFileExplorerCtrl().GetRootFolder());
		pApp->WriteProfileString(_T("Settings"), _T("Last Path"), sSelPath);
		pApp->WriteProfileString(_T("Settings"), _T("Root Folder"), sRootFolder);
		auto pathData = GetFileExplorerCtrl().GetNewAddedFolderData();
		for (int i = 0; i < pathData.size(); ++i)
		{
			CString sProfileString = _T("Added Folder %d");
			sProfileString.Format(sProfileString, i);
			pApp->WriteProfileString(_T("Settings"), sProfileString, pathData[i]);
		}
		const int nAddedFolderSize = static_cast<int>(pathData.size());
		pApp->WriteProfileInt(_T("Settings"), _T("Added Folder Size"), nAddedFolderSize);
		const BOOL bExpanded = GetFileExplorerCtrl().IsExpanded(GetFileExplorerCtrl().PathToItem(sSelPath));
		pApp->WriteProfileInt(_T("Settings"), _T("Expanded"), bExpanded);
	}

	// save search and replace pane status
	if (m_wndSearchAndReplaceWindow.GetSafeHwnd())
	{
		m_wndSearchAndReplaceWindow.SaveDialogState();
	}

	CMDIFrameWndEx::OnDestroy();
}

void CMainFrame::OnToolsShowAllNetworkItems()
{
	GetFileExplorerCtrl().SetNetworkItemTypes(RESOURCETYPE_ANY);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsShowAllNetworkItems(CCmdUI* pCmdUI)
{
	const DWORD dwTypes = GetFileExplorerCtrl().GetNetworkItemTypes();
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(dwTypes == RESOURCETYPE_ANY);
}

void CMainFrame::OnToolsShowNetworkPrinters()
{
	GetFileExplorerCtrl().SetNetworkItemTypes(RESOURCETYPE_PRINT);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsShowNetworkPrinters(CCmdUI* pCmdUI)
{
	const DWORD dwTypes = GetFileExplorerCtrl().GetNetworkItemTypes();
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(dwTypes == RESOURCETYPE_PRINT);
}

void CMainFrame::OnToolsShowNetworkShares()
{
	GetFileExplorerCtrl().SetNetworkItemTypes(RESOURCETYPE_DISK);
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsShowNetworkShares(CCmdUI* pCmdUI)
{
	const DWORD dwTypes = GetFileExplorerCtrl().GetNetworkItemTypes();
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(dwTypes & RESOURCETYPE_DISK);
}

void CMainFrame::OnToolsShowDriveLabels()
{
	GetFileExplorerCtrl().SetShowDriveLabels(!GetFileExplorerCtrl().GetShowDriveLabels());
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsShowDriveLabels(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetShowDriveLabels());
}

void CMainFrame::OnToolsHideMyComputer()
{
	GetFileExplorerCtrl().SetShowMyComputer(!GetFileExplorerCtrl().GetShowMyComputer());
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideMyComputer(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(!GetFileExplorerCtrl().GetShowMyComputer());
}

void CMainFrame::OnToolsShowRootedFolder()
{
	GetFileExplorerCtrl().SetShowRootedFolder(!GetFileExplorerCtrl().GetShowRootedFolder());
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsShowRootedFolder(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(GetFileExplorerCtrl().GetShowRootedFolder());
}

void CMainFrame::OnToolsHideDesktop()
{
	GetFileExplorerCtrl().SetShowDesktop(!GetFileExplorerCtrl().GetShowDesktop());
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideDesktop(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(!GetFileExplorerCtrl().GetShowDesktop());
}

void CMainFrame::OnToolsHideMyDocuments()
{
	GetFileExplorerCtrl().SetShowMyDocuments(!GetFileExplorerCtrl().GetShowMyDocuments());
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideMyDocuments(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(!GetFileExplorerCtrl().GetShowMyDocuments());
}

void CMainFrame::OnToolsHideCurrentUserFolder()
{
	GetFileExplorerCtrl().SetShowCurrentUserFolder(!GetFileExplorerCtrl().GetShowCurrentUserFolder());
}

#pragma warning(suppress: 26429)
void CMainFrame::OnUpdateToolsHideCurrentUserFolder(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->SetCheck(!GetFileExplorerCtrl().GetShowCurrentUserFolder());
}

void CMainFrame::OnVinaTextThemeLight()
{
	AppSettingMgr.m_AppThemeColor = EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_LIGHT;
	AppUtils::UpdateSettingsForVinatext();
	AfxMessageBox(_T("Theme changed to light."), MB_ICONINFORMATION);
}

void CMainFrame::OnVinaTextThemeMonokai()
{
	AppSettingMgr.m_AppThemeColor = EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_MONOKAI;
	AppUtils::UpdateSettingsForVinatext();
	AfxMessageBox(_T("Theme changed to monokai."), MB_ICONINFORMATION);
}

void CMainFrame::OnVinaTextThemeSierraBlue()
{
	AppSettingMgr.m_AppThemeColor = EDITOR_THEME_BACKGROUND_COLOR::THEME_BACKGROUND_COLOR_SIERRA_BLUE;
	AppUtils::UpdateSettingsForVinatext();
	AfxMessageBox(_T("Theme changed to sierra blue."), MB_ICONINFORMATION);
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
	case WM_MOUSEMOVE:
	{
		CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
		if (pDoc)
		{
			CWnd* pWnd = FromHandle(pMsg->hwnd);
			CMFCTabCtrl* tabGroup = dynamic_cast<CMFCTabCtrl*>(pWnd);
			if (tabGroup)
			{
				CPoint mousePosition = pMsg->pt;
				tabGroup->ScreenToClient(&mousePosition);
				int tabIndex = tabGroup->GetTabFromPoint(mousePosition);
				if (tabIndex != -1) // tab area
				{
					for (int i = 0; i < tabGroup->GetTabsNum(); i++)
					{
						CString strTabLabel;
						tabGroup->GetTabLabel(i, strTabLabel);
						if (strTabLabel == _T("vinatext-app-settings.json")) {
							tabGroup->SetTabBkColor(i, MDITAB_SETTINGS_COLOR);
						}
						else if (i != tabIndex && pDoc->GetTitle() != strTabLabel)
						{
							tabGroup->SetTabBkColor(i, MDITAB_NON_ACTIVE_COLOR);
						}
						else
						{
							tabGroup->SetTabBkColor(tabIndex, AppSettingMgr.m_ActiveTabColor);
						}
					}
				}
				else
				{
					for (int i = 0; i < tabGroup->GetTabsNum(); i++)
					{
						CString strTabLabel;
						tabGroup->GetTabLabel(i, strTabLabel);
						if (strTabLabel == _T("vinatext-app-settings.json")) {
							tabGroup->SetTabBkColor(i, MDITAB_SETTINGS_COLOR);
						}
						else if (pDoc->GetTitle() != strTabLabel)
						{
							tabGroup->SetTabBkColor(i, MDITAB_NON_ACTIVE_COLOR);
						}
						else
						{
							tabGroup->SetTabBkColor(tabIndex, AppSettingMgr.m_ActiveTabColor);
						}
					}
				}
				tabGroup->RedrawWindow();
			}
		}
		break;
	}
	case WM_LBUTTONDBLCLK:
	{
		CWnd* pWnd = FromHandle(pMsg->hwnd);
		CMFCTabCtrl* tabGroup = dynamic_cast<CMFCTabCtrl*>(pWnd);
		if (tabGroup)
		{
			CPoint clickLocation = pMsg->pt;
			tabGroup->ScreenToClient(&clickLocation);
			int tabIndex = tabGroup->GetTabFromPoint(clickLocation);
			if (tabIndex == -1) // not tab area
			{
				AppUtils::GetVinaTextApp()->OnFileNewEditor();
			}
			else if (AppSettingMgr.m_bRevealExplorerWhenDlbClkFile) // tab area
			{
				CBaseDoc* pActiveDoc = dynamic_cast<CBaseDoc*>(AppUtils::GetMDIActiveDocument());
				if (pActiveDoc && PathFileExists(pActiveDoc->GetPathName()))
				{
					pActiveDoc->SetPreviewMode(FALSE);
					RevealInExplorerWindow(pActiveDoc->GetPathName());
				}
			}
		}
		break;
	}
	case WM_MBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	{
		CWnd* pWnd = FromHandle(pMsg->hwnd);
		CMFCTabCtrl* tabGroup = dynamic_cast<CMFCTabCtrl*>(pWnd);
		if (tabGroup)
		{
			CPoint clickLocation = pMsg->pt;
			tabGroup->ScreenToClient(&clickLocation);
			int tabIndex = tabGroup->GetTabFromPoint(clickLocation);
			if (tabIndex != -1)
			{
				CWnd* pTab = tabGroup->GetTabWnd(tabIndex);
				if (pTab)
				{
					pTab->SendMessage(WM_CLOSE, 0, 0);
				}
			}
		}
		break;
	}
	case WM_XBUTTONDOWN:
	{
		WORD fwButtonX = GET_XBUTTON_WPARAM(pMsg->wParam);
		switch (fwButtonX)
		{
			case XBUTTON1:
			{
				MDIPrev();
				return TRUE;
			}
			case XBUTTON2:
			{
				MDINext();
				return TRUE;
			}
			break;
		}
	}
	case WM_KEYDOWN:
	{
		switch (pMsg->wParam)
		{
			case 'C':
			{
				if (GetKeyState(VK_CONTROL) & 0x8000 && GetKeyState(VK_SHIFT) & 0x8000)
				{
					CMFCTabCtrl* tabGroup = GetActiveMDITabGroup();
					if (tabGroup)
					{
						CPoint clickLocation = pMsg->pt;
						tabGroup->ScreenToClient(&clickLocation);
						int tabIndex = tabGroup->GetTabFromPoint(clickLocation);
						if (tabIndex != -1)
						{
							CWnd* pTab = tabGroup->GetTabWnd(tabIndex);
							if (pTab)
							{
								CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
								if (pDoc)
								{
									CString strPathName = pDoc->GetPathName();
									if (!strPathName.IsEmpty())
									{
										PushTextToClipBoard(strPathName);
										LOG_OUTPUT_MESSAGE_FORMAT(_T("> [From Tab] Copied full file path %s..."), strPathName);
										return TRUE;
									}
								}
							}
						}
					}
				}
				else if (GetKeyState(VK_CONTROL))
				{
					CImageDoc* pImageDocActiveDoc = dynamic_cast<CImageDoc*>(AppUtils::GetMDIActiveDocument());
					{
						if (pImageDocActiveDoc)
						{
							CImageView* pImageView = pImageDocActiveDoc->GetImageView();
							if (pImageView)
							{
								pImageView->OnEditCopy();
								return TRUE;
							}
						}
					}
				}
				break;
			}
			case 'F':
			{
				if (GetKeyState(VK_CONTROL) & 0x8000 && GetKeyState(VK_SHIFT) & 0x8000)
				{
					CEditorDoc* pEditorActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
					{
						if (pEditorActiveDoc)
						{
							CEditorCtrl* pEditor = pEditorActiveDoc->GetEditorCtrl();
							if (pEditor)
							{
								InitSearchReplaceFromEditor(pEditor->GetSelectedText(), SEARCH_REPLACE_GOTO_DLG_TYPE::SEARCH);
							}
						}
					}
					return TRUE;
				}
				else if (GetKeyState(VK_CONTROL) & 0x8000)
				{
					OnQuickSearch();
					return TRUE;
				}
				break;
			}
			case 'H':
				if (GetKeyState(VK_CONTROL) & 0x8000 && GetKeyState(VK_SHIFT) & 0x8000)
				{
					CEditorDoc* pEditorActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
					{
						if (pEditorActiveDoc)
						{
							CEditorCtrl* pEditor = pEditorActiveDoc->GetEditorCtrl();
							if (pEditor)
							{
								InitSearchReplaceFromEditor(pEditor->GetSelectedText(), SEARCH_REPLACE_GOTO_DLG_TYPE::REPLACE);
							}
						}
					}
					return TRUE;
				}
				else if (GetKeyState(VK_CONTROL) & 0x8000)
				{
					OnQuickReplace();
					return TRUE;
				}
				break;
			case 'E':
			{
				if (GetKeyState(VK_CONTROL) & 0x8000 && (GetKeyState(VK_SHIFT) & 0x8000))
				{
					OnHostFileExplorer();
					return TRUE;
				}
				else if (GetKeyState(VK_CONTROL) & 0x8000)
				{
					OnOpenContainerFolder();
					return TRUE;
				}
				break;
			}
			case 'B':
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
				{
					OnToolsOpenBookMarkPathTable();
					return TRUE;
				}
				else if ((GetKeyState(VK_CONTROL) & 0x8000))
				{
					OnDocumentBookMark();
					return TRUE;
				}
				break;
			}
			case 'N':
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
				{
					OnMDITabMoveToNewVinaText();
					return TRUE;
				}
				break;
			}
			case 'P':
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
				{
					AppUtils::GetVinaTextApp()->OnNewProjectTemplate();
					return TRUE;
				}
				break;
			}
			case 'Q':
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
				{
					OnOpenFileExplorer();
					return TRUE;
				}
				break;
			}
			case 'T':
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
				{
					AppUtils::GetVinaTextApp()->OnOpenRecentClosedFile();
					return TRUE;
				}
				if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_MENU) & 0x8000))
				{
					OnTerminalOpenNewPowerShellWindow();
					return TRUE;
				}
				break;
			}
			case 'O':
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
				{
					AppUtils::GetVinaTextApp()->OnAddFolderToWorkSpace();
					return TRUE;
				}
				break;
			}
			case 'W':
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
				{
					ShowWindowsDialog();
					return TRUE;
				}
				else if ((GetKeyState(VK_CONTROL) & 0x8000))
				{
					OnCloseDocument();
					return TRUE;
				}
				break;
			}
			case 'Z':
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
				{
					CEditorView* pEditorView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
					if (pEditorView)
					{
						pEditorView->OnOptionsEditUndoAll();
						return TRUE;
					}
				}
				else if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_MENU) & 0x8000))
				{
					CEditorView* pEditorView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
					if (pEditorView)
					{
						pEditorView->OnOptionsWrapLine();
						return TRUE;
					}
				}
				else if ((GetKeyState(VK_CONTROL) & 0x8000))
				{
					CEditorView* pEditorView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
					if (pEditorView)
					{
						pEditorView->OnOptionsEditUndo();
						return TRUE;
					}
				}
			}
			break;
			case 'Y':
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
				{
					CEditorView* pEditorView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
					if (pEditorView)
					{
						pEditorView->OnOptionsEditRedoAll();
						return TRUE;
					}

				}
				else if ((GetKeyState(VK_CONTROL) & 0x8000))
				{
					CEditorView* pEditorView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
					if (pEditorView)
					{
						pEditorView->OnOptionsEditRedo();
						return TRUE;
					}
				}
			}
			break;
			case VK_ESCAPE:
			{
				if (m_pQuickSearchDialog)
				{
					m_pQuickSearchDialog->OnCancel();
				}
				CEditorView* pEditorView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
				if (pEditorView)
				{
					// remove multi-selection mode, kept main selection only
					if (pEditorView->GetEditorCtrl())
					{
						pEditorView->GetEditorCtrl()->DropSelections();
					}
					return TRUE;
				}
				return TRUE;
			}
			case VK_DELETE:
			{
				CMFCTabCtrl* tabGroup = GetActiveMDITabGroup();
				if (tabGroup)
				{
					CPoint clickLocation = pMsg->pt;
					tabGroup->ScreenToClient(&clickLocation);
					int tabIndex = tabGroup->GetTabFromPoint(clickLocation);
					if (tabIndex != -1)
					{
						CWnd* pTab = tabGroup->GetTabWnd(tabIndex);
						if (pTab)
						{
							OnDeleteFile();
							return TRUE;
						}
					}
				}
				break;
			}
			case VK_F1:
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000))
				{
					OnWindowNew();
					return TRUE;
				}
				break;
			}
			case VK_F2:
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000))
				{
					OnNewHorizontalTabGroup();
					return TRUE;
				}
				else
				{
					OnRenameDocument();
					return TRUE;
				}
				break;
			}
			case VK_F3:
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000))
				{
					OnMDITabCloneFile();
					return TRUE;
				}
				break;
			}
			case VK_NUMPAD1:
				if ((GetKeyState(VK_CONTROL) & 0x8000))
				{
					OnNewVerticalTabGroup();
					return TRUE;
				}
				break;
			case VK_NUMPAD2:
				if ((GetKeyState(VK_CONTROL) & 0x8000))
				{
					OnNewHorizontalTabGroup();
					return TRUE;
				}
				break;
			case VK_F4:
			{
				if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_MENU) & 0x8000))
				{
					OnCloseAllDocument();
					return TRUE;
				}
				else
				{
					OnReLoadDocument();
					return TRUE;
				}
				break;
			}
			case VK_F8:
			{	
				CEditorView* pEditorView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
				if (pEditorView)
				{
					pEditorView->ToggleAddBookmark();
					return TRUE;
				}
				break;
			}
			case VK_F9:
			{
				CEditorView* pEditorView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
				if (pEditorView)
				{
					pEditorView->ToggleAddBreakPoint();
					return TRUE;
				}
				break;
			}
			case VK_F11:
			{
				if ((GetKeyState(VK_MENU) & 0x8000))
				{
					OnFullScreeenMode();
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	default:
		break;
	}

	return CMDIFrameWndEx::PreTranslateMessage(pMsg);
}

CMDIChildWndEx * CMainFrame::CreateDocumentWindow(LPCTSTR lpcszDocName, CObject * pObj)
{
	if (PathFileExists(lpcszDocName) && !PathUtils::IsDirectory(lpcszDocName))
	{
		CDocument* pDoc = NULL;
		if (PathUtils::IsImageFile(lpcszDocName))
		{
			// Open image file
			pDoc = theApp.m_pImageDocTemplate->OpenNewDocument(lpcszDocName, TRUE, TRUE);
		}
		else if (PathUtils::IsPdfFile(lpcszDocName))
		{
			// Open pdf file
			pDoc = theApp.m_pPdfDocTemplate->OpenNewDocument(lpcszDocName, TRUE, TRUE);
		}
		else if (PathUtils::IsMediaFile(lpcszDocName))
		{
			// Open media file
			pDoc = theApp.m_pMediaDocTemplate->OpenNewDocument(lpcszDocName, TRUE, TRUE);
		}
		else
		{
			// Open text file
			pDoc = theApp.m_pEditorDocTemplate->OpenNewDocument(lpcszDocName, TRUE, TRUE);
		}
		if (pDoc != NULL)
		{
			POSITION pos = pDoc->GetFirstViewPosition();
			if (pos != NULL)
			{
				CView* pView = pDoc->GetNextView(pos);
				return DYNAMIC_DOWNCAST(CMDIChildWndEx, pView->GetParent());
			}
		}
	}
	return NULL;
}

BOOL CMainFrame::OnShowMDITabContextMenu(CPoint point, DWORD dwAllowedItems, BOOL bDrop)
{
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MDI_TAB_POPUP));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	auto pActiveDoc = dynamic_cast<CBaseDoc*>(AppUtils::GetMDIActiveDocument());

	if (pPopup)
	{
		if (pActiveDoc == NULL)
		{
			pPopup->DestroyMenu();
			pPopup->CreatePopupMenu();
			if (pPopup && (dwAllowedItems & AFX_MDI_CAN_BE_DOCKED) != 0)
			{
				pPopup->AppendMenu(MF_STRING, ID_MDI_TABBED_DOCUMENT, _T("UnTabbed Document"));
			}
		}
		else
		{
			if (pActiveDoc->IsKindOf(RUNTIME_CLASS(CPdfDoc)) || pActiveDoc->IsKindOf(RUNTIME_CLASS(CMediaDoc))
				|| pActiveDoc->IsKindOf(RUNTIME_CLASS(CHostDoc)) || pActiveDoc->IsKindOf(RUNTIME_CLASS(CFileExplorerDoc)))
			{
				pPopup->DeleteMenu(ID_FILE_SAVE, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_FILE_SAVE_AS, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_FILE_SAVE_ALL, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_CLONE_FILE, MF_BYCOMMAND);
				pPopup->RemoveMenu(5, MF_BYPOSITION);
			}

			if (pActiveDoc->GetPathName().IsEmpty())
			{
				pPopup->DeleteMenu(ID_MDI_TAB_GET_FULL_FILE_PATH_DOUBLE_QUOTE, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_GET_FULL_FILE_PATH, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_GET_FULL_FILE_PATH_FORWARD_SLASH, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_GET_FULL_FILE_PATH_DOUBLE_SLASH, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_GET_FOLDER_PATH, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_GET_FILE_NAME, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_GET_FILE_NAME_NO_EXTENSION, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_OPEN_CONTAINER_FOLDER, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_LOCATE_IN_FILE_EXPLORER, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_SHOW_PROPERTIES, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_CLONE_FILE, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_RELOAD, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_RENAME, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_DELETE_FILE, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_FILE_COPY, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_MOVE_NEW_WINDOW, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_BOOKMARK_FILE, MF_BYCOMMAND);
				if (AppUtils::GetDocumentCount() == 1)
				{
					pPopup->RemoveMenu(1, MF_BYPOSITION);
					pPopup->RemoveMenu(7, MF_BYPOSITION);
					pPopup->RemoveMenu(7, MF_BYPOSITION);
					pPopup->RemoveMenu(7, MF_BYPOSITION);
					pPopup->RemoveMenu(7, MF_BYPOSITION);
					pPopup->RemoveMenu(7, MF_BYPOSITION);
				}
				else if (pActiveDoc->IsKindOf(RUNTIME_CLASS(CHostDoc)))
				{
					pPopup->RemoveMenu(6, MF_BYPOSITION);
					pPopup->RemoveMenu(6, MF_BYPOSITION);
					pPopup->RemoveMenu(6, MF_BYPOSITION);
				}
				else
				{
					pPopup->RemoveMenu(8, MF_BYPOSITION);
					pPopup->RemoveMenu(8, MF_BYPOSITION);
					pPopup->RemoveMenu(8, MF_BYPOSITION);
					pPopup->RemoveMenu(8, MF_BYPOSITION);
				}
			}

			if (AppUtils::GetDocumentCount() == 1)
			{
				pPopup->RemoveMenu(1, MF_BYPOSITION);
				if (pActiveDoc->IsKindOf(RUNTIME_CLASS(CFileExplorerDoc)))
				{
					pPopup->RemoveMenu(6, MF_BYPOSITION);
				}
			}
			else
			{
				if (pActiveDoc->IsKindOf(RUNTIME_CLASS(CFileExplorerDoc)))
				{
					pPopup->RemoveMenu(7, MF_BYPOSITION);
				}
			}
		

			if ((dwAllowedItems & AFX_MDI_CREATE_HORZ_GROUP) == 0)
			{
				pPopup->DeleteMenu(ID_MDI_TAB_NEW_HORIZONTAL_TAB, MF_BYCOMMAND);
			}
			if ((dwAllowedItems & AFX_MDI_CREATE_VERT_GROUP) == 0)
			{
				pPopup->DeleteMenu(ID_MDI_TAB_NEW_VERTICAL_TAB, MF_BYCOMMAND);
			}
			if ((dwAllowedItems & AFX_MDI_CAN_MOVE_NEXT) == 0)
			{
				pPopup->DeleteMenu(ID_MDI_TAB_MOVE_NEXT_TAB, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_MOVE_ALL_NEXT_TAB, MF_BYCOMMAND);
			}
			if ((dwAllowedItems & AFX_MDI_CAN_MOVE_PREV) == 0)
			{
				pPopup->DeleteMenu(ID_MDI_TAB_MOVE_PREVIOUS_TAB, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_MOVE_ALL_PREVIOUS_TAB, MF_BYCOMMAND);
			}
			if ((dwAllowedItems & AFX_MDI_CAN_BE_DOCKED) == 0)
			{
				pPopup->DeleteMenu(ID_MDI_TABBED_DOCUMENT, MF_BYCOMMAND);
			}
			if (AppUtils::GetDocumentCount() == 1)
			{
				pPopup->DeleteMenu(ID_MDI_TAB_CLOSE_ALL_DOC_BUT_THIS, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_CLOSE_ALL_UNCHANGE_FILE, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_MDI_TAB_CLOSE_ALL_DOC, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_FILE_SAVE_ALL, MF_BYCOMMAND);
			}
			if (AppUtils::GetModifiedDocumentCount() == 0)
			{
				pPopup->DeleteMenu(ID_MDI_TAB_CLOSE_ALL_UNCHANGE_FILE, MF_BYCOMMAND);
			}
			if (!AppUtils::CanCloseAllDocumentLeft(AppUtils::GetMDIActiveView()))
			{
				pPopup->DeleteMenu(ID_MDI_TAB_CLOSE_ALL_DOC_LEFT, MF_BYCOMMAND);
			}
			if (!AppUtils::CanCloseAllDocumentRight(AppUtils::GetMDIActiveView()))
			{
				pPopup->DeleteMenu(ID_MDI_TAB_CLOSE_ALL_DOC_RIGHT, MF_BYCOMMAND);
			}
		}
		// system menu style
		AppTranslator.ToNativeContextMenu(pPopup);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	return TRUE;
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	CMDIFrameWndEx::OnMouseMove(nFlags, point);
}

void CMainFrame::SetDockingPaneIcons(BOOL bBigIcons)
{
	m_wndFileExplorer.SetIcon(AfxGetApp()->LoadIcon(IDR_FILE_EXPLORER_WINDOW), bBigIcons);
	m_wndMessageWindow.SetIcon(AfxGetApp()->LoadIcon(IDR_LOG_WINDOW), bBigIcons);
	m_wndSearchAndReplaceWindow.SetIcon(AfxGetApp()->LoadIcon(IDR_SEARCH_WINDOW), bBigIcons);
	m_wndSearchResultPane.SetIcon(AfxGetApp()->LoadIcon(IDR_SEARCH_RESULT_WINDOW), bBigIcons);
	m_wndBuildWindow.SetIcon(AfxGetApp()->LoadIcon(IDR_BUILD_WINDOW), bBigIcons);
	m_wndBookmarkWindow.SetIcon(AfxGetApp()->LoadIcon(IDR_BOOKMARK_WINDOW), bBigIcons);
	m_wndPathResultWindow.SetIcon(AfxGetApp()->LoadIcon(IDR_FILE_RESULT_WINDOW), bBigIcons);
	m_wndBreakpointWindow.SetIcon(AfxGetApp()->LoadIcon(IDR_BREAKPOINT_WINDOW), bBigIcons);
	UpdateMDITabbedBarsIcons();
}

BOOL CMainFrame::CreateDockingBars()
{
	DWORD dwLeftStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI;
	if (!m_wndFileExplorer.Create(Native_Language("Explorer Window"), this, CRect(0, 0, 300, 200), TRUE, ID_PANE_FILE_EXPLORER, dwLeftStyle))
	{
		TRACE0("Failed to create Explorer Window\n");
		return FALSE; // failed to create
	}

	DWORD dwBottomStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI;
	if (!m_wndMessageWindow.Create(Native_Language("Message Window"), this, CRect(0, 0, 300, 200), TRUE, ID_PANE_OUTPUT_WINDOW, dwBottomStyle))
	{
		TRACE0("Failed to create Message Window\n");
		return FALSE; // failed to create
	}

	DWORD dwRightStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI;
	if (!m_wndSearchAndReplaceWindow.Create(Native_Language("Search Text Window"), this, CRect(0, 0, 300, 200), TRUE, ID_PANE_SEARCH_AND_REPLACE_WINDOW, dwRightStyle))
	{
		TRACE0("Failed to create Search Text Window\n");
		return FALSE; // failed to create
	}

	if (!m_wndSearchResultPane.Create(Native_Language("Text Result Window"), this, CRect(0, 0, 300, 200), TRUE, ID_PANE_TEXT_RESULT_WINDOW, dwBottomStyle))
	{
		TRACE0("Failed to create Text Result Window\n");
		return FALSE; // failed to create
	}

	if (!m_wndBuildWindow.Create(Native_Language("Debug Window"), this, CRect(0, 0, 300, 200), TRUE, ID_PANE_BUILD_WINDOW, dwBottomStyle))
	{
		TRACE0("Failed to create Build Window\n");
		return FALSE; // failed to create
	}

	if (!m_wndBookmarkWindow.Create(Native_Language("Bookmark Window"), this, CRect(0, 0, 300, 200), TRUE, ID_PANE_BOOKMARK_WINDOW, dwBottomStyle))
	{
		TRACE0("Failed to create Bookmark Window\n");
		return FALSE; // failed to create
	}

	if (!m_wndBreakpointWindow.Create(Native_Language("Breakpoint Window"), this, CRect(0, 0, 300, 200), TRUE, ID_PANE_BREAKPOINT_WINDOW, dwBottomStyle))
	{
		TRACE0("Failed to create Breakpoint Window\n");
		return FALSE; // failed to create
	}

	if (!m_wndPathResultWindow.Create(Native_Language("Path Result Window"), this, CRect(0, 0, 300, 200), TRUE, ID_PANE_FILE_RESULT_WINDOW, dwBottomStyle))
	{
		TRACE0("Failed to create Path Result Window\n");
		return FALSE; // failed to create
	}

	SetDockingPaneIcons(FALSE);

	m_wndFileExplorer.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndFileExplorer);
	ShowPane(&m_wndFileExplorer, FALSE, FALSE, FALSE);

	m_wndMessageWindow.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMessageWindow);
	ShowPane(&m_wndMessageWindow, FALSE, FALSE, FALSE);

	m_wndSearchAndReplaceWindow.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndSearchAndReplaceWindow);
	ShowPane(&m_wndSearchAndReplaceWindow, FALSE, FALSE, FALSE);

	m_wndSearchResultPane.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndSearchResultPane);
	ShowPane(&m_wndSearchResultPane, FALSE, FALSE, FALSE);

	m_wndBuildWindow.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndBuildWindow);
	ShowPane(&m_wndBuildWindow, FALSE, FALSE, FALSE);

	m_wndBookmarkWindow.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndBookmarkWindow);
	ShowPane(&m_wndBookmarkWindow, FALSE, FALSE, FALSE);

	m_wndBreakpointWindow.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndBreakpointWindow);
	ShowPane(&m_wndBreakpointWindow, FALSE, FALSE, FALSE);

	m_wndPathResultWindow.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndPathResultWindow);
	ShowPane(&m_wndPathResultWindow, FALSE, FALSE, FALSE);

	CDockablePane* pTabbedBar = NULL;
	m_wndSearchResultPane.AttachToTabWnd(&m_wndMessageWindow, DM_SHOW, TRUE, &pTabbedBar);
	m_wndBuildWindow.AttachToTabWnd(&m_wndMessageWindow, DM_SHOW, TRUE, &pTabbedBar);
	m_wndBookmarkWindow.AttachToTabWnd(&m_wndMessageWindow, DM_SHOW, TRUE, &pTabbedBar);
	m_wndBreakpointWindow.AttachToTabWnd(&m_wndMessageWindow, DM_SHOW, TRUE, &pTabbedBar);
	m_wndPathResultWindow.AttachToTabWnd(&m_wndMessageWindow, DM_SHOW, TRUE, &pTabbedBar);

	// has to add code for ReactiveTabAfterFloatPane also !!

	return TRUE;
}

CMFCTabCtrl* CMainFrame::GetActiveMDITabGroup()
{
	CMFCTabCtrl* pActiveMDITabWnd = m_wndClientArea.FindActiveTabWndByActiveChild();
	ASSERT_VALID(pActiveMDITabWnd);
	if (pActiveMDITabWnd == NULL)
	{
		return NULL;
	}
	return pActiveMDITabWnd;
}

void CMainFrame::ClearDataOnDockPane(DOCKABLE_PANE_TYPE type)
{
	switch (type)
	{
		case DOCKABLE_PANE_TYPE::LOG_MESSAGE_PANE:
		{
			if (m_wndMessageWindow.GetSafeHwnd())
			{
				m_wndMessageWindow.ClearAll();
			}
			break;
		}
		case DOCKABLE_PANE_TYPE::BUILD_PANE:
		{
			if (m_wndBuildWindow.GetSafeHwnd())
			{
				m_wndBuildWindow.ClearAll();
			}
			break;
		}
		case DOCKABLE_PANE_TYPE::SEARCH_RESULT_PANE:
		{
			if (m_wndSearchResultPane.GetSafeHwnd())
			{
				m_wndSearchResultPane.ClearAll();
			}
			break;
		}
		case DOCKABLE_PANE_TYPE::SEARCH_AND_REPLACE_PANE:
		{
			if (m_wndSearchAndReplaceWindow.GetSafeHwnd())
			{
				m_wndSearchAndReplaceWindow.ClearAll();
			}
			break;
		}
		case DOCKABLE_PANE_TYPE::BOOKMARK_PANE:
		{
			if (m_wndBookmarkWindow.GetSafeHwnd())
			{
				m_wndBookmarkWindow.ClearAll();
			}
			break;
		}
		case DOCKABLE_PANE_TYPE::PATH_RESULT_PANE:
		{
			if (m_wndPathResultWindow.GetSafeHwnd())
			{
				m_wndPathResultWindow.ClearAll();
			}
			break;
		}
		case DOCKABLE_PANE_TYPE::BREAKPOINT_PANE:
		{
			if (m_wndBreakpointWindow.GetSafeHwnd())
			{
				m_wndBreakpointWindow.ClearAll();
			}
			break;
		}
	}
}

void CMainFrame::PrintMessage(LOG_TARGET target, CString strMsg, COLORREF col)
{
	switch (target)
	{
		case LOG_TARGET::MESSAGE_WINDOW:
		{
			if (m_wndMessageWindow.GetSafeHwnd())
			{
				m_wndMessageWindow.AddLogMessage(strMsg, col);
			}
			break;
		}
		case LOG_TARGET::BUILD_WINDOW:
		{
			if (m_wndBuildWindow.GetSafeHwnd())
			{
				m_wndBuildWindow.AddLogMessage(strMsg, col);
			}
			break;
		}
	}
}

void CMainFrame::AddSearchResultDataToPane(const TEXT_RESULT_SEARCH_REPLACE_DATA& ResultSearchData)
{
	if (m_wndSearchResultPane.GetSafeHwnd())
	{
		ShowPane(&m_wndSearchResultPane, TRUE, FALSE, TRUE);
		m_wndSearchResultPane.SetActiveWindow();
		m_wndSearchResultPane.AddResultData(ResultSearchData);
		m_wndSearchResultPane.SetFocus();
	}
}

void CMainFrame::AddPathResultDataToPane(const PATH_RESULT_DATA_LIST & ResultSearchData, const CString & strSeachWhat, int nSearchTotal, double dTimeMeasured, BOOL bAppendResult, BOOL bSearchWithoutMatchName)
{
	if (m_wndPathResultWindow.GetSafeHwnd())
	{
		ShowPane(&m_wndPathResultWindow, TRUE, FALSE, TRUE);
		m_wndPathResultWindow.SetActiveWindow();
		m_wndPathResultWindow.AddResultData(ResultSearchData, strSeachWhat, nSearchTotal, dTimeMeasured, bAppendResult, bSearchWithoutMatchName);
		m_wndPathResultWindow.SetFocus();
	}
}

void CMainFrame::AddBookmarkLineDataToPane(const BOOKMARK_LINE_DATA & BookmarkData)
{
	if (m_wndBookmarkWindow.GetSafeHwnd())
	{
		m_wndBookmarkWindow.AddBookmarkData(BookmarkData);
	}
}

void CMainFrame::AddBreakpointLineDataToPane(const BREAKPOINT_LINE_DATA & BreakpointData)
{
	if (m_wndBreakpointWindow.GetSafeHwnd())
	{
		m_wndBreakpointWindow.AddBreakpointData(BreakpointData);
	}
}

void CMainFrame::InitSearchReplaceFromEditor(const CString& strSearchWhat, SEARCH_REPLACE_GOTO_DLG_TYPE searchType)
{
	if (m_pQuickSearchDialog)
	{
		m_pQuickSearchDialog->OnCancel();
	}
	if (m_wndSearchAndReplaceWindow.GetSafeHwnd())
	{
		ShowPane(&m_wndSearchAndReplaceWindow, TRUE, FALSE, TRUE);
		m_wndSearchAndReplaceWindow.InitSearchReplaceFromEditor(strSearchWhat, searchType);
	}
}

void CMainFrame::InitQuickSearchFromEditor(const CString& strSearchWhat, SEARCH_REPLACE_GOTO_DLG_TYPE searchType)
{
	if (m_wndSearchAndReplaceWindow.GetSafeHwnd())
	{
		m_wndSearchAndReplaceWindow.InitSearchReplaceFromEditor(strSearchWhat, searchType);
	}
	if (m_pQuickSearchDialog)
	{
		m_pQuickSearchDialog->InitSearchReplaceFromEditor(strSearchWhat, searchType);
	}
}

void CMainFrame::SearchAllOnFileFromEditor(const CString& strSearchWhat, SEARCH_REPLACE_GOTO_DLG_TYPE searchType)
{
	if (m_wndSearchAndReplaceWindow.GetSafeHwnd())
	{
		m_wndSearchAndReplaceWindow.SearchAllOnFileFromEditor(strSearchWhat, searchType);
	}
}

void CMainFrame::SearchFromEditor(const CString& strSearchWhat, SEARCH_TYPE searchType,
	BOOL bSeacrhNext, BOOL bHideMessageBox, BOOL bSaveSearchWord)
{
	if (m_wndSearchAndReplaceWindow.GetSafeHwnd())
	{
		m_wndSearchAndReplaceWindow.SearchFromEditor(strSearchWhat, searchType, bSeacrhNext, bHideMessageBox, bSaveSearchWord);
	}
}

void CMainFrame::InitSearchReplaceFromExplorer(const CString& strFolderPath, SEARCH_REPLACE_GOTO_DLG_TYPE searchType)
{
	if (m_wndSearchAndReplaceWindow.GetSafeHwnd())
	{
		ShowPane(&m_wndSearchAndReplaceWindow, TRUE, FALSE, TRUE);
		m_wndSearchAndReplaceWindow.InitSearchReplaceFromExplorer(strFolderPath, searchType);
	}
}

void CMainFrame::OnChangeAppLook(BOOL bOneNoteTabs, BOOL bMDITabColors, BOOL bIsVSDotNetLook, BOOL bDockTabColors, BOOL bMDITabsVS2005Look, BOOL bActiveTabCloseButton)
{
	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_SCROLLED; // other styles available...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // set to FALSE to place close button at right of tab area
	mdiTabParams.m_bTabIcons = TRUE;    // set to TRUE to enable document icons on MDI taba
	mdiTabParams.m_bAutoColor = FALSE;    // set to FALSE to disable auto-coloring of MDI tabs
	mdiTabParams.m_bDocumentMenu = TRUE; // enable the document menu at the right edge of the tab area
	mdiTabParams.m_bTabCustomTooltips = TRUE;
	mdiTabParams.m_bEnableTabSwap = TRUE;

	if (bMDITabsVS2005Look)
	{
		mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_VS2005;
		mdiTabParams.m_bDocumentMenu = TRUE;
	}
	else if (bOneNoteTabs)
	{
		mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE;
		mdiTabParams.m_bAutoColor = FALSE;
	}

	if (bActiveTabCloseButton)
	{
		mdiTabParams.m_bTabCloseButton = FALSE;
		mdiTabParams.m_bActiveTabCloseButton = TRUE;
	}

	EnableMDITabbedGroups(TRUE, mdiTabParams);

	CTabbedPane::EnableTabAutoColor(bDockTabColors);

	// Reload toolbar images:
	CMFCToolBar::ResetAllImages();

	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDR_MAINFRAME_24 : IDR_MAINFRAME);

	CDockingManager* pDockManager = GetDockingManager();
	ASSERT_VALID(pDockManager);

	SetDockingPaneIcons(theApp.m_bHiColorIcons);

	pDockManager->AdjustPaneFrames();

	RecalcLayout();
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}

void CMainFrame::MDIMoveAllTabGroupMode(BOOL bNext)
{
	CMFCTabCtrl* pActiveWnd = m_wndClientArea.FindActiveTabWndByActiveChild();
	if (pActiveWnd == NULL)
	{
		return;
	}
	ASSERT_VALID(pActiveWnd);
	POSITION pos = GetMDITabGroups().Find(pActiveWnd);
	bNext ? GetMDITabGroups().GetNext(pos) : GetMDITabGroups().GetPrev(pos);

	if (pos == NULL)
	{
		return;
	}

	CMFCTabCtrl* pNextTabWnd = DYNAMIC_DOWNCAST(CMFCTabCtrl, GetMDITabGroups().GetAt(pos));
	ASSERT_VALID(pNextTabWnd);

	int count = pActiveWnd->GetTabsNum();
	for (int i = count - 1; i >= 0; i--)
	{
		m_wndClientArea.MoveWindowToTabGroup(pActiveWnd, pNextTabWnd, i);
	}
}

void CMainFrame::OnHighLightMDIActiveTab()
{
	CDocument* pDoc = AppUtils::GetMDIActiveDocument();
	if (!pDoc) return;
	CMFCTabCtrl* pMDITabs = m_wndClientArea.FindActiveTabWndByActiveChild();
	if (pMDITabs == NULL)
	{
		return;
	}
	ASSERT_VALID(pMDITabs);
	for (int i = 0; i < pMDITabs->GetTabsNum(); i++)
	{
		CString strTabLabel;
		pMDITabs->GetTabLabel(i, strTabLabel);
		if (strTabLabel == _T("vinatext-app-settings.json")) {
			pMDITabs->SetTabBkColor(i, MDITAB_SETTINGS_COLOR);
		}
		else if (pDoc->GetTitle() == strTabLabel)
		{
			pMDITabs->SetTabBkColor(i, AppSettingMgr.m_ActiveTabColor);
		}
		else
		{
			pMDITabs->SetTabBkColor(i, MDITAB_NON_ACTIVE_COLOR);
		}
	}
	pMDITabs->RedrawWindow();
}

void CMainFrame::OnUpdateIconReadOnlyTab()
{
	CEditorView* pView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
	if (pView)
	{
		auto pParentFrame = pView->GetParentFrame();
		auto pChildFrame = dynamic_cast<CChildFrame*>(pParentFrame);
		if (pChildFrame)
		{
			if (pView->GetEditorCtrl()->IsReadOnlyEditor())
			{
				pChildFrame->SetIcon(AfxGetApp()->LoadIcon(IDR_EDITOR_DOC_READ_ONLY), FALSE);
			}
			else
			{
				pChildFrame->SetIcon(AfxGetApp()->LoadIcon(IDR_EDITOR_DOC), FALSE);
			}
		}
	}
}

void CMainFrame::ActiveDockPane(DOCKABLE_PANE_TYPE type)
{
	switch (type)
	{
	case DOCKABLE_PANE_TYPE::LOG_MESSAGE_PANE:
		if (m_wndMessageWindow.GetSafeHwnd())
		{
			ShowPane(&m_wndMessageWindow, TRUE, FALSE, TRUE);
			m_wndMessageWindow.SetActiveWindow();
		}
		break;
	case DOCKABLE_PANE_TYPE::FILE_EXPLORER_PANE:
		if (m_wndFileExplorer.GetSafeHwnd())
		{
			ShowPane(&m_wndFileExplorer, TRUE, FALSE, TRUE);
			m_wndFileExplorer.SetActiveWindow();
		}
		break;
	case DOCKABLE_PANE_TYPE::SEARCH_AND_REPLACE_PANE:
		if (m_wndSearchAndReplaceWindow.GetSafeHwnd())
		{
			ShowPane(&m_wndSearchAndReplaceWindow, TRUE, FALSE, TRUE);
			m_wndSearchAndReplaceWindow.SetActiveWindow();
		}
		break;
	case DOCKABLE_PANE_TYPE::SEARCH_RESULT_PANE:
		if (m_wndSearchResultPane.GetSafeHwnd())
		{
			ShowPane(&m_wndSearchResultPane, TRUE, FALSE, TRUE);
			m_wndSearchResultPane.SetActiveWindow();
		}
		break;
	case DOCKABLE_PANE_TYPE::BUILD_PANE:
		if (m_wndBuildWindow.GetSafeHwnd())
		{
			ShowPane(&m_wndBuildWindow, TRUE, FALSE, TRUE);
			m_wndBuildWindow.SetActiveWindow();
		}
		break;
	case DOCKABLE_PANE_TYPE::BOOKMARK_PANE:
		if (m_wndBookmarkWindow.GetSafeHwnd())
		{
			ShowPane(&m_wndBookmarkWindow, TRUE, FALSE, TRUE);
			m_wndBookmarkWindow.SetActiveWindow();
		}
		break;
	case DOCKABLE_PANE_TYPE::PATH_RESULT_PANE:
		if (m_wndPathResultWindow.GetSafeHwnd())
		{
			ShowPane(&m_wndPathResultWindow, TRUE, FALSE, TRUE);
			m_wndPathResultWindow.SetActiveWindow();
		}
		break;
	case DOCKABLE_PANE_TYPE::BREAKPOINT_PANE:
		if (m_wndBreakpointWindow.GetSafeHwnd())
		{
			ShowPane(&m_wndBreakpointWindow, TRUE, FALSE, TRUE);
			m_wndBreakpointWindow.SetActiveWindow();
		}
		break;
	default:
		break;
	}
	RecalcLayout();
}

LRESULT CMainFrame::OnGetTabToolTip(WPARAM /*wp*/, LPARAM lp)
{
	CMFCTabToolTipInfo* pInfo = (CMFCTabToolTipInfo*)lp;
	ASSERT(pInfo != NULL);
	if (!pInfo)
	{
		return 0;
	}
	ASSERT_VALID(pInfo->m_pTabWnd);
	if (!pInfo->m_pTabWnd->IsMDITab())
	{
		return 0;
	}
	CFrameWnd* pFrame = DYNAMIC_DOWNCAST(CFrameWnd, pInfo->m_pTabWnd->GetTabWnd(pInfo->m_nTabIndex));
	if (pFrame == NULL)
	{
		return 0;
	}

	CDocument* pDoc = pFrame->GetActiveDocument();
	if (pDoc == NULL)
	{
		return 0;
	}

	if (pDoc->GetPathName().IsEmpty())
	{
		pInfo->m_strText = pDoc->GetTitle();
	}
	else
	{
		pInfo->m_strText = pDoc->GetPathName();
	}
	return 0;
}

LRESULT CMainFrame::OnAfxWmChangedActiveTab(WPARAM wParam, LPARAM lParam)
{
	CEditorView* pView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
	if (pView)
	{
		pView->ReupdateTrackingBar();
	}
	return 0;
}

void CMainFrame::OnVinaTextSettings()
{
	VinaTextSettingDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnToolsRemoveFolder()
{
	GetFileExplorerCtrl().RemoveFolderFromWorkSpace();
}

void CMainFrame::OnToolsBackToOriginalExplorer()
{
	GetFileExplorerCtrl().BackToOriginalExplorer();
}

void CMainFrame::OnToolsBookMarkAPath()
{
	GetFileExplorerCtrl().BookMarkPath();
}

void CMainFrame::OnToolsOpenBookMarkPathTable()
{
	CString strPathBookmarkSave = PathUtils::GetVinaTextBookmarkPath();

	if (m_pBookMarkPathDlg)
	{
		m_pBookMarkPathDlg->InitListBookmarkPath(TRUE);
	}

	if (!m_pBookMarkPathDlg)
		m_pBookMarkPathDlg = new CBookMarkPathDlg(strPathBookmarkSave);

	if (!m_pBookMarkPathDlg->GetSafeHwnd())
	{
		m_pBookMarkPathDlg->Create(CBookMarkPathDlg::IDD, this);
		m_pBookMarkPathDlg->ShowWindow(SW_SHOW);
		m_pBookMarkPathDlg->CenterWindow();
	}
}

void CMainFrame::ReleaseBookMarkTableDialog()
{
	m_pBookMarkPathDlg = NULL;
}

void CMainFrame::RevealInExplorerWindow(const CString& strPath)
{
	if (PathFileExists(strPath))
	{
		HTREEITEM hItemFound = GetFileExplorerCtrl().PathToItem(strPath);
		if (hItemFound)
		{
			GetFileExplorerCtrl().SetSelectedPath(strPath, TRUE);
		}
		else
		{
			GetFileExplorerCtrl().Refresh();
			hItemFound = GetFileExplorerCtrl().SetSelectedPath(strPath, TRUE);
			if (hItemFound == NULL)
			{
				LOG_OUTPUT_MESSAGE_FORMAT(_T("> Can not found revealed path in current workspace..."));
			}
		}
	}
	ActiveDockPane(DOCKABLE_PANE_TYPE::FILE_EXPLORER_PANE);
	GetFileExplorerCtrl().SetFocus();
}

void CMainFrame::ReactiveTabAfterFloatPane()
{
	if (m_wndMessageWindow.GetSafeHwnd() && m_wndMessageWindow.IsVisible() && m_wndMessageWindow.IsTabbed())
	{
		ShowPane(&m_wndMessageWindow, TRUE, FALSE, TRUE);
		m_wndMessageWindow.SetActiveWindow();
	}
	if (m_wndFileExplorer.GetSafeHwnd() && m_wndFileExplorer.IsVisible() && m_wndFileExplorer.IsTabbed())
	{
		ShowPane(&m_wndFileExplorer, TRUE, FALSE, TRUE);
		m_wndFileExplorer.SetActiveWindow();
	}
	if (m_wndSearchAndReplaceWindow.GetSafeHwnd() && m_wndSearchAndReplaceWindow.IsVisible() && m_wndSearchAndReplaceWindow.IsTabbed())
	{
		ShowPane(&m_wndSearchAndReplaceWindow, TRUE, FALSE, TRUE);
		m_wndSearchAndReplaceWindow.SetActiveWindow();
	}
	if (m_wndSearchResultPane.GetSafeHwnd() && m_wndSearchResultPane.IsVisible() && m_wndSearchResultPane.IsTabbed())
	{
		ShowPane(&m_wndSearchResultPane, TRUE, FALSE, TRUE);
		m_wndSearchResultPane.SetActiveWindow();
	}
	if (m_wndBuildWindow.GetSafeHwnd() && m_wndBuildWindow.IsVisible() && m_wndBuildWindow.IsTabbed())
	{
		ShowPane(&m_wndBuildWindow, TRUE, FALSE, TRUE);
		m_wndBuildWindow.SetActiveWindow();
	}
	if (m_wndBookmarkWindow.GetSafeHwnd() && m_wndBookmarkWindow.IsVisible() && m_wndBookmarkWindow.IsTabbed())
	{
		ShowPane(&m_wndBookmarkWindow, TRUE, FALSE, TRUE);
		m_wndBookmarkWindow.SetActiveWindow();
	}
	if (m_wndPathResultWindow.GetSafeHwnd() && m_wndPathResultWindow.IsVisible() && m_wndPathResultWindow.IsTabbed())
	{
		ShowPane(&m_wndPathResultWindow, TRUE, FALSE, TRUE);
		m_wndPathResultWindow.SetActiveWindow();
	}
	if (m_wndBreakpointWindow.GetSafeHwnd() && m_wndBreakpointWindow.IsVisible() && m_wndBreakpointWindow.IsTabbed())
	{
		ShowPane(&m_wndBreakpointWindow, TRUE, FALSE, TRUE);
		m_wndBreakpointWindow.SetActiveWindow();
	}
	RecalcLayout();
}

void CMainFrame::OnToolsOpenFolderVinaText()
{
	CString strFolderPath = PathUtils::GetVinaTextPath();
	if (!PathFileExists(strFolderPath))
	{
		AfxMessageBox(_T("[Path Error] VinaText install path does not exist!"));
		return;
	}
	RevealInExplorerWindow(strFolderPath);
}

void CMainFrame::OnToolsOpenFolderTemp()
{
	CString strFolderPath = PathUtils::GetVinaTextTempPath();
	if (!PathFileExists(strFolderPath))
	{
		AfxMessageBox(_T("[Path Error] VinaText temp path does not exist!"));
		return;
	}
	PathUtils::OpenFileSystem(strFolderPath);
}

void CMainFrame::OnToolsOpenFolderAppData()
{
	CString strAppDataFolderPath = PathUtils::GetVinaTextAppDataPath();
	if (!PathFileExists(strAppDataFolderPath))
	{
		AfxMessageBox(_T("[Path Error] VinaText app data path does not exist!"));
		return;
	}
	RevealInExplorerWindow(strAppDataFolderPath);
}

void CMainFrame::OnToolsControlPanel()
{
	OSUtils::CreateWin32Process(_T("Control Panel"));
}

void CMainFrame::OnToolsOpenEnvPath()
{
	OSUtils::CreateWin32Process(_T("rundll32 sysdm.cpl,EditEnvironmentVariables"));
}

void CMainFrame::OnToolsOpenHost()
{
	PathUtils::OpenFileSystem(_T("C:\\Windows\\System32\\drivers\\etc"));
}

void CMainFrame::FinalizeWorkerThread()
{
	ThreadWorkerMgr.FinalizeThreadWorker();
}

BOOL CMainFrame::IsSameMDITabGroup(CView* pActiveView, CView* pParentView)
{
	const CObList& tabGroups = GetMDIClientAreaWnd().GetMDITabGroups();
	if (tabGroups.GetCount() > 0)
	{
		POSITION pos = tabGroups.GetHeadPosition();
		CMFCTabCtrl* pCrtTabCtrl;
		while (pos != NULL)
		{
			pCrtTabCtrl = DYNAMIC_DOWNCAST(CMFCTabCtrl, tabGroups.GetNext(pos));
			BOOL bCheckRightTabs = FALSE;
			int count = pCrtTabCtrl->GetTabsNum();
			int nCounter = 0;
			for (int i = 0; i < count; i++)
			{
				CWnd* pWnd = pCrtTabCtrl->GetTabWndNoWrapper(i);
				CMDIChildWnd *pChild = ((CMDIChildWnd*)(pWnd));
				if (pChild)
				{
					CView *pView = pChild->GetActiveView();
					if (pView && pView->IsKindOf(RUNTIME_CLASS(CEditorView)))
					{
						if (pActiveView == pView)
						{
							nCounter++;
						}
						else if (pParentView == pView)
						{
							nCounter++;
						}
					}
				}
				if (nCounter == 2)
				{
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

void CMainFrame::QuickSearchDialogChangedActiveTab()
{
	CEditorDoc* pEditorActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pEditorActiveDoc && m_pQuickSearchDialog)
	{
		CEditorDoc* pParentDocument = m_pQuickSearchDialog->GetParentDocument();
		if (pParentDocument)
		{
			if (pParentDocument == pEditorActiveDoc)
			{
				m_pQuickSearchDialog->ShowWindow(SW_SHOW);
			}
			else if (IsSameMDITabGroup(pParentDocument->GetEditorView(), pEditorActiveDoc->GetEditorView()))
			{
				m_pQuickSearchDialog->ShowWindow(SW_HIDE);
			}
		}
	}
}

void CMainFrame::CloseQuickSearchDialog()
{
	CEditorDoc* pEditorActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pEditorActiveDoc && m_pQuickSearchDialog)
	{
		CEditorDoc* pParentDocument = m_pQuickSearchDialog->GetParentDocument();
		if (pParentDocument)
		{
			if (pParentDocument == pEditorActiveDoc)
			{
				m_pQuickSearchDialog->OnCancel();
			}
		}
	}
}

void CMainFrame::ResizeQuickSearchDialog()
{
	if (m_pQuickSearchDialog)
	{
		CEditorDoc* pParentDocument = m_pQuickSearchDialog->GetParentDocument();
		CEditorDoc* pEditorActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
		if (pParentDocument && pEditorActiveDoc)
		{
			if (IsSameMDITabGroup(pParentDocument->GetEditorView(), pEditorActiveDoc->GetEditorView()))
			{
				m_pQuickSearchDialog->ShowWindow(SW_HIDE);
			}
			else
			{
				CEditorCtrl* pEditor = pParentDocument->GetEditorCtrl();
				if (pEditor)
				{
					CRect rect;
					m_pQuickSearchDialog->GetWindowRect(rect);
					int dx = rect.Width();
					int dy = rect.Height();

					pEditor->GetWindowRect(rect);
					int wEditor = rect.Width();
					int hEditor = rect.Height();
					if (pEditor->IsVerticalScrollBarVisible())
					{
						rect.right = rect.right - MARGIN_EDITOR_SCROLLBAR;
					}
					rect.left = rect.right - dx;
					rect.bottom = rect.top + dy;
					m_pQuickSearchDialog->MoveWindow(rect);

					m_pQuickSearchDialog->GetWindowRect(rect);
					int wDlg = rect.Width();
					int hDlg = rect.Height();
					if (wEditor < wDlg || hEditor < hDlg)
					{
						m_pQuickSearchDialog->ShowWindow(SW_HIDE);
					}
					else
					{
						m_pQuickSearchDialog->ShowWindow(SW_SHOW);
					}
				}
			}
		}
		else
		{
			m_pQuickSearchDialog->ShowWindow(SW_HIDE);
		}
	}
}

void CMainFrame::ShowQuickSearchDialog(SEARCH_REPLACE_GOTO_DLG_TYPE type)
{
	if (!m_pQuickSearchDialog)
		m_pQuickSearchDialog = new CQuickSearchDialog();

	if (!m_pQuickSearchDialog->GetSafeHwnd())
	{
		m_pQuickSearchDialog->Create(CQuickSearchDialog::IDD, this);
	}

	if (m_pQuickSearchDialog)
	{
		auto pEditorActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
		{
			if (pEditorActiveDoc)
			{
				m_pQuickSearchDialog->SetParentDocument(pEditorActiveDoc);
			}
		}
	}

	ResizeQuickSearchDialog();

	CEditorDoc* pEditorActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	{
		if (pEditorActiveDoc)
		{
			CEditorCtrl* pEditor = pEditorActiveDoc->GetEditorCtrl();
			if (pEditor)
			{
				if (pEditor->GetSelectedText().IsEmpty() && m_wndSearchAndReplaceWindow.GetSafeHwnd() && m_wndSearchAndReplaceWindow.IsVisible())
				{
					InitQuickSearchFromEditor(m_wndSearchAndReplaceWindow.GetSearchWhat(), type);
				}
				else InitQuickSearchFromEditor(pEditor->GetSelectedText(), type);
			}
		}
	}
}

void CMainFrame::ReleaseQuickSearchDialog()
{
	m_pQuickSearchDialog = NULL;
}

void CMainFrame::EnableAutoSaveDocument()
{
	if (AppSettingMgr.m_bAutoSaveDocument) 
	{
		KillTimer(AUTO_SAVE_DOCUMENT_TIMER);
		SetTimer(AUTO_SAVE_DOCUMENT_TIMER, AppSettingMgr.m_nIntervalAutoSaveFileMinutes*60*1000, NULL);
	}
	else 
	{
		KillTimer(AUTO_SAVE_DOCUMENT_TIMER);
	}
}

void CMainFrame::RemoveDebuggerDocument(CEditorDoc* pDocument)
{
	m_DebuggerDocList.erase(pDocument);
}

void CMainFrame::OnUpdateIconAllReadOnlyTab()
{
	for (auto pDoc : m_DebuggerDocList)
	{
		if (!pDoc) continue;
		if (pDoc->GetEditorCtrl())
		{
			pDoc->GetEditorCtrl()->SetReadOnlyEditor(FALSE);
		}
		CEditorView* pView = pDoc->GetEditorView();
		if (pView)
		{
			auto pParentFrame = pView->GetParentFrame();
			auto pChildFrame = dynamic_cast<CChildFrame*>(pParentFrame);
			if (pChildFrame)
			{
				if (pView->GetEditorCtrl()->IsReadOnlyEditor())
				{
					pChildFrame->SetIcon(AfxGetApp()->LoadIcon(IDR_EDITOR_DOC_READ_ONLY), FALSE);
				}
				else
				{
					pChildFrame->SetIcon(AfxGetApp()->LoadIcon(IDR_EDITOR_DOC), FALSE);
				}
			}
		}
	}
	m_DebuggerDocList.clear();
}

// activate the third tabbed view from the first tab group
// VERIFY(ActivateTabInGroup(0, 2));
BOOL CMainFrame::ActivateTabInGroup(INT_PTR nTabGroupIndex, int nTabItemIndex /*= -1*/)
{
	BOOL bRet = FALSE;
	const CObList& tabGroups = GetMDIClientAreaWnd().GetMDITabGroups();
	if (tabGroups.GetCount() > 0)
	{
		POSITION pos = tabGroups.FindIndex(nTabGroupIndex);
		if (NULL != pos)
		{
			const CObject* pTabGroup = tabGroups.GetAt(pos);
			VERIFY(pTabGroup->IsKindOf(RUNTIME_CLASS(CMFCTabCtrl)));
			if (NULL != pTabGroup)
			{
				CMFCTabCtrl* pTabCtrl = (CMFCTabCtrl*)pTabGroup;
				if (pTabCtrl->GetTabsNum() > nTabItemIndex)
				{
					pTabCtrl->ActivateMDITab(nTabItemIndex);
					bRet = TRUE;
				}
			}
		}
	}
	return bRet;
}

CString CMainFrame::GetQuickSearchWhat()
{
	CEditorDoc* pEditorActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
	if (pEditorActiveDoc && m_pQuickSearchDialog)
	{
		CEditorDoc* pParentDocument = m_pQuickSearchDialog->GetParentDocument();
		if (pParentDocument)
		{
			if (pParentDocument == pEditorActiveDoc)
			{
				return m_pQuickSearchDialog->GetSearchWhat();
			}
		}
	}
	return CString();
}

unsigned int CMainFrame::GetQuickSearchOption()
{
	if (m_pQuickSearchDialog)
	{
		return m_pQuickSearchDialog->GetSearchOption();
	}
	else if (m_wndSearchAndReplaceWindow.GetSafeHwnd() && m_wndSearchAndReplaceWindow.IsVisible())
	{
		return m_wndSearchAndReplaceWindow.GetSearchOption();
	}
	return 0;
}

void CMainFrame::UPDATE_EDITOR_UI_FOR_DEBUGGER(CEditorDoc* pEditorDoc, DWORD lPointerLine)
{
	if (pEditorDoc)
	{
		m_DebuggerDocList.insert(pEditorDoc);
		auto pEditor = pEditorDoc->GetEditorCtrl();
		if (pEditor)
		{
			pEditor->AddDebugPointer(lPointerLine);
			pEditor->GotoLine(lPointerLine);
			pEditor->SetLineCenterDisplay(lPointerLine);
			pEditor->SetFocus();
			if (!pEditor->IsReadOnlyEditor())
			{
				pEditorDoc->GetEditorView()->ChangeToEditorReadOnly();
			}
		}
	}
}

void CMainFrame::RemoveAllBreakPointDebuggerDoc(VINATEXT_SUPPORTED_LANGUAGE language)
{
	for (auto pDoc : m_DebuggerDocList)
	{
		if (!pDoc) continue;
		if (pDoc->GetEditorCtrl()
			&& pDoc->GetEditorView()->GetCurrentDocLanguague() == language)
		{
			pDoc->GetEditorCtrl()->DeleteAllBreakPoint();
		}
	}
}

BOOL CMainFrame::IsDebuggerDocument(CEditorDoc* pDoc)
{
	for (auto pDocDebugger : m_DebuggerDocList)
	{
		if (pDocDebugger == pDoc)
		{
			return TRUE;
		}
	}
	return FALSE;
}

LRESULT CMainFrame::OnCompilerNotifyDebugLinePointer(WPARAM wParam, LPARAM lParam)
{
	DWORD lPointerLine = (DWORD)lParam;
	LPCTSTR szFileName = (LPCTSTR)wParam;

	if (lPointerLine > 0 && PathFileExists(szFileName))
	{
		auto pEditorActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
		{
			if (pEditorActiveDoc)
			{
				auto pEditorActive = pEditorActiveDoc->GetEditorCtrl();
				if (pEditorActive)
				{
					pEditorActive->DeleteAllDebugPointer();
				}
			}
		}

		auto pOpenedDoc = AppUtils::GetExistedDocument(szFileName);
		if (!pOpenedDoc)
		{
			AppUtils::CreateDocumentFromFile(szFileName);
			auto pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
			UPDATE_EDITOR_UI_FOR_DEBUGGER(pEditorDoc, lPointerLine);
		}
		else if (AppUtils::SetActiveDocument(pOpenedDoc))
		{
			auto pEditorDoc = dynamic_cast<CEditorDoc*>(pOpenedDoc);
			UPDATE_EDITOR_UI_FOR_DEBUGGER(pEditorDoc, lPointerLine);
		}
	}
	return 0L;
}

//////////////////// mdi tab commands ///////////////////////////

void CMainFrame::PushTextToClipBoard(const CString& str)
{
	if (OpenClipboard())
	{
		GLOBALHANDLE hGlobal;
		TCHAR* pGlobal;
		EmptyClipboard();
		hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT | GMEM_SHARE, (str.GetLength() + 1) * sizeof(TCHAR));
		pGlobal = (TCHAR*)GlobalLock(hGlobal);
		_tcscpy(pGlobal, (LPTSTR)(LPCTSTR)str);
		GlobalUnlock(hGlobal);
		SetClipboardData(CF_UNICODETEXT, hGlobal);
		CloseClipboard();
	}
}

CString CMainFrame::GetCurrentDocFolder()
{
	CString strFolderPath;
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	if (!pDoc) return strFolderPath;
	CString strPathName = pDoc->GetPathName();
	if (!PathFileExists(strPathName)) return _T("");
	if (PathUtils::IsDirectory(strPathName)) return strPathName;
	strFolderPath = PathUtils::GetContainerPath(strPathName);
	return strFolderPath;
}

void CMainFrame::ReOpenCurrentDocument(const CString & strReplaceFile)
{
	// Close current doc
	OnCloseDocument();
	if (PathFileExists(strReplaceFile))
	{
		// Open new doc
		AppUtils::CreateDocumentFromFile(strReplaceFile);
		// Refresh explorer window
		RevealInExplorerWindow(strReplaceFile);
	}
}

void CMainFrame::OnCloseDocument()
{
	AppUtils::CloseMDIDocument(GetActiveFrame()->GetActiveDocument());
}

void CMainFrame::OnCloseAllDocument()
{
	AppUtils::CloseAllDocument();
}

void CMainFrame::OnCloseAllDocumentLeft()
{
	CView* pView = AppUtils::GetMDIActiveView();
	AppUtils::CloseAllDocumentLeft(pView);
}

void CMainFrame::OnCloseAllDocumentRight()
{
	CView* pView = AppUtils::GetMDIActiveView();
	AppUtils::CloseAllDocumentRight(pView);
}

void CMainFrame::OnCloseAllDocumentButThis()
{
	CView* pView = AppUtils::GetMDIActiveView();
	AppUtils::CloseAllDocumentButThis(pView);
}

void CMainFrame::OnGetFullPath()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	if (!pDoc) return;
	CString strPathName = pDoc->GetPathName();
	if (!PathFileExists(strPathName)) return;
	PushTextToClipBoard(strPathName);
}

void CMainFrame::OnGetFullPathDoubleSlash()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	if (!pDoc) return;
	CString strPathName = pDoc->GetPathName();
	if (!PathFileExists(strPathName)) return;
	strPathName.Replace(_T("\\"), _T("\\\\"));
	PushTextToClipBoard(strPathName);
}

void CMainFrame::OnGetFullPathForwardSlash()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	if (!pDoc) return;
	CString strPathName = pDoc->GetPathName();
	if (!PathFileExists(strPathName)) return;
	strPathName.Replace(_T("\\"), _T("/"));
	PushTextToClipBoard(strPathName);
}

void CMainFrame::OnGetFolderPath()
{
	CString strFolderPath = GetCurrentDocFolder();
	PushTextToClipBoard(strFolderPath);
}

void CMainFrame::OnGetFileName()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	if (!pDoc) return;
	CString strPathName = pDoc->GetPathName();
	if (!PathFileExists(strPathName)) return;
	CString strFileName = PathUtils::GetFilenameFromPath(strPathName);
	PushTextToClipBoard(strFileName);
}

void CMainFrame::OnGetFileNameNoExtension()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	if (!pDoc) return;
	CString strPathName = pDoc->GetPathName();
	if (!PathFileExists(strPathName)) return;
	CString strFileName = PathUtils::GetFilenameFromPath(strPathName);
	CString strFileNameNoExt = PathUtils::GetFileNameWithoutExtension(strFileName);
	PushTextToClipBoard(strFileNameNoExt);
}

void CMainFrame::OnOpenContainerFolder()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	if (!pDoc) return;
	CString strPathName = pDoc->GetPathName();
	if (!PathFileExists(strPathName)) return;
	if (!PathUtils::IsDirectory(strPathName))
	{
		CString strFolderPath = PathUtils::GetContainerPath(strPathName);
		PIDLIST_ABSOLUTE pidl;
		if (SUCCEEDED(SHParseDisplayName(strFolderPath, 0, &pidl, 0, 0)))
		{
			ITEMIDLIST *pidl = static_cast<ITEMIDLIST*>(ILCreateFromPath(strPathName));
			SHOpenFolderAndSelectItems(pidl, 0, 0, 0);
			ILFree(pidl);
		}
	}
	else
	{
		PathUtils::OpenFileSystem(strPathName);
	}
	
}

void CMainFrame::OnOpenFileExplorer()
{
	CBaseDoc* pDoc = dynamic_cast<CBaseDoc*>(GetActiveFrame()->GetActiveDocument());
	if (!pDoc) return;
	CString strPathName = pDoc->GetPathName();
	if (PathFileExists(strPathName))
	{
		pDoc->SetPreviewMode(FALSE);
		RevealInExplorerWindow(strPathName);
	}
	else
	{
		ActiveDockPane(DOCKABLE_PANE_TYPE::FILE_EXPLORER_PANE);
		GetFileExplorerCtrl().SetFocus();
	}
}

BOOL CMainFrame::SetCurrentDirectoryTerminal()
{
	CString strFolderPath = GetCurrentDocFolder();
	if (PathFileExists(strFolderPath))
	{
		return SetCurrentDirectoryW(strFolderPath);
	}
	return FALSE;
}

void CMainFrame::OnOpenCMDHere()
{
	SetCurrentDirectoryTerminal();
	OSUtils::CreateWin32Process(_T("cmd.exe"));
}

CString CMainFrame::GetClipboardPlainText()
{
	if (!OpenClipboard())
		return CString();

#ifdef UNICODE
	HANDLE hglb = ::GetClipboardData(CF_UNICODETEXT);
#else
	HANDLE hglb = ::GetClipboardData(CF_TEXT);
#endif
	if (hglb == NULL)
	{
		CloseClipboard();
		return CString();
	}
	CString strClipBoardText = reinterpret_cast<LPTSTR>(::GlobalLock(hglb));
	if (!strClipBoardText.IsEmpty())
	{
		::GlobalUnlock(hglb);
	}
	CloseClipboard();
	return strClipBoardText;
}


void CMainFrame::OnOpenCMDPasteClipboard()
{
	SetCurrentDirectoryTerminal();
	OSUtils::CreateWin32Process(_T("cmd.exe"));
	Sleep(500);
	HWND hCMD = OSUtils::GetHWNDFromClassNameAndProgramPath(L"ConsoleWindowClass", L"C:\\WINDOWS\\system32\\cmd.exe");
	OSUtils::PatseClipboardToCMD(hCMD);
}

void CMainFrame::OnOpenCMDAppendFileName()
{
	if (!SetCurrentDirectoryTerminal()) return;
	OSUtils::CreateWin32Process(_T("cmd.exe"));
	Sleep(500);
	CString strClipBoardText = GetClipboardPlainText();
	OnGetFileName();
	HWND hCMD = OSUtils::GetHWNDFromClassNameAndProgramPath(L"ConsoleWindowClass", L"C:\\WINDOWS\\system32\\cmd.exe");
	OSUtils::PatseClipboardToCMD(hCMD);
	PushTextToClipBoard(strClipBoardText);
}

void CMainFrame::OnOpenCMDAppendFilePath()
{
	if (!SetCurrentDirectoryTerminal()) return;
	OSUtils::CreateWin32Process(_T("cmd.exe"));
	Sleep(500);
	CString strClipBoardText = GetClipboardPlainText();
	OnOptionGetFullFilePathDoubleQuote();
	HWND hCMD = OSUtils::GetHWNDFromClassNameAndProgramPath(L"ConsoleWindowClass", L"C:\\WINDOWS\\system32\\cmd.exe");
	OSUtils::PatseClipboardToCMD(hCMD);
	PushTextToClipBoard(strClipBoardText);
}

void CMainFrame::OnOpenWSLHere()
{
	SetCurrentDirectoryTerminal();
	OSUtils::CreateWin32Process(_T("wsl.exe"));
}

void CMainFrame::OnOpenPowerShellHere()
{
	SetCurrentDirectoryTerminal();
	OSUtils::CreateWin32Process(_T("powershell.exe"));
}

void CMainFrame::OnOpenGitBashHere()
{
	CString strGitBash = AppSettingMgr.m_strGitWindowFolderPath + _T("\\bin\\sh.exe");
	if (FALSE == PathFileExists(strGitBash))
	{
		CString strMsg;
		strMsg.Format(_T("[Path Error] %s does not exist, please install git...\n"), strGitBash);
		LOG_OUTPUT_MESSAGE_COLOR(strMsg, BasicColors::orange);
	}
	SetCurrentDirectoryTerminal();
	CString strCommandLine = _T("start \"\" \"") + strGitBash + _T("\"") + _T(" --login");
	_wsystem(AppUtils::CStringToWStd(strCommandLine).c_str());
}

void CMainFrame::OnOpenGitFileProperties()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	ASSERT(pDoc);
	if (!pDoc) return;
	CString sFile = pDoc->GetPathName();
#pragma warning(suppress: 26476)
	SHELLEXECUTEINFO sei{};
	sei.cbSize = sizeof(sei);
	sei.hwnd = GetParent()->GetSafeHwnd();
	sei.nShow = SW_SHOW;
	sei.lpFile = sFile.GetBuffer(sFile.GetLength());
	sei.lpVerb = _T("properties");
	sei.fMask = SEE_MASK_INVOKEIDLIST;
#pragma warning(suppress: 26486)
	ShellExecuteEx(&sei);
	sFile.ReleaseBuffer();
}

void CMainFrame::OnRenameDocument()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	ASSERT(pDoc);
	if (!pDoc) return;
	CString strOldFilePath = pDoc->GetPathName();
	if (!PathFileExists(strOldFilePath)) return;

	CString strTitleName = pDoc->GetTitle();
	CString strFileExt = PathUtils::GetFileExtention(strOldFilePath);
	CString strFilter;
	strFilter.Format(_T("New File (%s)|%s||"), strFileExt, strFileExt);
	CFileDialog fileDlg(FALSE, NULL, strTitleName, OFN_OVERWRITEPROMPT, strFilter);
	fileDlg.m_ofn.lpstrTitle = _T("Rename as...");
	CString strFolderParent = PathUtils::GetContainerPath(strOldFilePath);
	if (PathFileExists(strFolderParent))
	{
		fileDlg.m_ofn.lpstrInitialDir = strFolderParent;
	}
	if (fileDlg.DoModal() != IDOK)
	{
		return;
	}
	CString strNewFilePath = fileDlg.GetPathName();
	CString strFileNewName = PathUtils::GetFilenameFromPath(strNewFilePath);
	if (strFileNewName == strTitleName)
	{
		return;
	}

	AppUtils::CloseDocumentByFilePath(strOldFilePath);

	if (PathUtils::RenameFile(strOldFilePath, strNewFilePath))
	{
		if (PathFileExists(strNewFilePath))
		{
			// Open new doc
			AppUtils::CreateDocumentFromFile(strNewFilePath);
			// Refresh explorer window
			GetFileExplorerCtrl().Refresh();
			RevealInExplorerWindow(strNewFilePath);
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> Renamed %s to %s..."), strOldFilePath, strNewFilePath);
		}
	}
}

void CMainFrame::OnReLoadDocument()
{
	if (ThreadWorkerMgr.IsRunning() || ThreadWorkerMgr.IsDebuggerRunning())
	{
		AfxMessageBox(_T("Please stop running program/debugger before reload file!"));
		return;
	}
	CViewBase* pView = dynamic_cast<CViewBase*>(AppUtils::GetMDIActiveView());
	if (pView)
	{
		AppUtils::GetVinaTextApp()->m_bIsReloadDocument = TRUE;
		pView->OnInitialUpdate();
		AppUtils::GetVinaTextApp()->m_bIsReloadDocument = FALSE;
		CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
		ASSERT(pDoc); if (!pDoc) return;
		if (PathFileExists(pDoc->GetPathName()))
		{
			VinaTextDebugger.RemoveBreakPointDataInFile(pDoc->GetPathName());
			LOG_OUTPUT_MESSAGE_ACTIVE_PANE(AfxCStringFormat(_T("> [Reload File] %s..."), pDoc->GetPathName()), BasicColors::orange);
		}
	}
}

void CMainFrame::OnCopyDocument()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	ASSERT(pDoc); if (!pDoc) return;
	CString strPathName = pDoc->GetPathName();
	if (PathFileExists(strPathName))
	{
		GuiUtils::PushFileObjectToClipboard(strPathName);
	}
}

void CMainFrame::OnNewVerticalTabGroup()
{
	if (AppUtils::GetDocumentCount() > 1)
	{
		BOOL bVertical = TRUE; // true for vertical split
		MDITabNewGroup(bVertical);
		RecalcLayout();
		RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
	}
}

void CMainFrame::OnNewHorizontalTabGroup()
{
	if (AppUtils::GetDocumentCount() > 1)
	{
		BOOL bVertical = FALSE; // false for horizontal split
		MDITabNewGroup(bVertical);
		RecalcLayout();
		RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
	}
}

void CMainFrame::OnSwitchToNextTab()
{
	CMDIFrameWnd::MDINext();
}

void CMainFrame::OnSwitchToPreviousTab()
{
	CMDIFrameWnd::MDIPrev();
}

void CMainFrame::OnMDITabMoveToNewVinaText()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	ASSERT(pDoc); if (!pDoc) return;
	CString strPathName = pDoc->GetPathName();
	CString strPathVinaTextExe = PathUtils::GetVinaTextExePath();
	if (PathFileExists(strPathVinaTextExe))
	{
		// Open new app instance...
		BOOL bRet = OSUtils::CreateWin32Process(strPathVinaTextExe + _T(" -moveFileToNewInstance ") + +_T(" \"") + strPathName + _T("\""));
		if (bRet)
		{
			// Create new instance fine so close current doc
			OnCloseDocument();
		}
	}
	else
	{
		CString strMsg;
		strMsg.Format(_T("[Path Error] %s does not exist...\n"), strPathVinaTextExe);
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strMsg, BasicColors::orange);
	}
}

void CMainFrame::OnMDITabMoveToNextGroup()
{
	BOOL bNext = TRUE;
	MDITabMoveToNextGroup(bNext);
}

void CMainFrame::OnMDITabMoveToPreviousGroup()
{
	BOOL bNext = FALSE;
	MDITabMoveToNextGroup(bNext);
}

void CMainFrame::OnMDITabCloneFile()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	ASSERT(pDoc); if (!pDoc) return;
	CString strPathName = pDoc->GetPathName();
	if (!PathFileExists(strPathName)) return;

	CString strFileName = PathUtils::GetFilenameFromPath(strPathName);
	CString strFileNameNoExt = PathUtils::GetFileNameWithoutExtension(strFileName);
	CString strID = OSUtils::GetGUIDGlobal();
	CString strFileNameCopied = strFileNameNoExt + _T("_") + strID;
	strPathName.Replace(strFileNameNoExt, strFileNameCopied);

	CString stScript;
	if (pDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
	{
		CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(pDoc);
		if (pEditorDoc && pEditorDoc->GetEditorCtrl())
		{
			pEditorDoc->GetEditorCtrl()->GetText(stScript);
			if (PathUtils::SaveFileTrunc(strPathName, stScript))
			{
				// Open new doc
				AppUtils::CreateDocumentFromFile(strPathName);

				// Refresh explorer window
				GetFileExplorerCtrl().Refresh();
			}
		}
	}
}

void CMainFrame::OnMDITabMoveAllToNextGroup()
{
	BOOL bNext = TRUE;
	MDIMoveAllTabGroupMode(bNext);
}

void CMainFrame::OnMDITabMoveAllToPreviousGroup()
{
	BOOL bNext = FALSE;
	MDIMoveAllTabGroupMode(bNext);
}

void CMainFrame::OnMDINewFile()
{
	AppUtils::GetVinaTextApp()->OnFileNewEditor();
}

void CMainFrame::OnMDINewFileInNewGroup()
{
	AppUtils::GetVinaTextApp()->OnFileNewEditor();
	OnNewVerticalTabGroup();
}

void CMainFrame::OnMDITabOpenInChrome()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	ASSERT(pDoc); if (!pDoc) return;
	CString strFilePath = pDoc->GetPathName();
	if (!PathFileExists(strFilePath)) return;
	OSUtils::OpenFileInWebBrowser(_T("chrome.exe"), strFilePath);
}

void CMainFrame::OnMDITabOpenInFireFox()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	ASSERT(pDoc); if (!pDoc) return;
	CString strFilePath = pDoc->GetPathName();
	if (!PathFileExists(strFilePath)) return;
	OSUtils::OpenFileInWebBrowser(_T("firefox.exe"), strFilePath);
}

void CMainFrame::OnMDITabOpenInEdge()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	ASSERT(pDoc);
	if (!pDoc) return;
	CString strFilePath = pDoc->GetPathName();
	if (!PathFileExists(strFilePath)) return;
	OSUtils::OpenFileInWebBrowser(_T("shell:Appsfolder\\Microsoft.MicrosoftEdge_8wekyb3d8bbwe!MicrosoftEdge"), strFilePath);
}

void CMainFrame::UpdateUIByCheckExistFile(CCmdUI * pCmdUI)
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	ASSERT(pDoc); if (!pDoc) return;
	if (!PathFileExists(pDoc->GetPathName()))
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CMainFrame::OnUpdateReLoadDocument(CCmdUI * pCmdUI)
{
	UpdateUIByCheckExistFile(pCmdUI);
}

void CMainFrame::OnUpdateOpenFileEplorer(CCmdUI * pCmdUI)
{
	UpdateUIByCheckExistFile(pCmdUI);
}

void CMainFrame::OnUpdateOpenCMDAppendFile(CCmdUI * pCmdUI)
{
	UpdateUIByCheckExistFile(pCmdUI);
}

void CMainFrame::OnUpdateOpenCMDAppendFilePath(CCmdUI * pCmdUI)
{
	UpdateUIByCheckExistFile(pCmdUI);
}

void CMainFrame::OnUpdateOpenContainerFolder(CCmdUI * pCmdUI)
{
	UpdateUIByCheckExistFile(pCmdUI);
}

void CMainFrame::OnUpdateBookmarkFile(CCmdUI * pCmdUI)
{
	UpdateUIByCheckExistFile(pCmdUI);
}

void CMainFrame::OnCloseAllDocumentUnmodified()
{
	AppUtils::CloseAllDocumentUnmodified();
}

void CMainFrame::OnUpdateExplorerSelectedFilePath(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnDeleteFile()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	if (!pDoc) return;
	CString strFileToDelete = pDoc->GetPathName();
	if (!PathFileExists(strFileToDelete))
	{
		AfxMessageBoxFormat(MB_ICONWARNING, _T("[Error] Path %s does not exist!"), strFileToDelete);
		return;
	}
	if (IDYES == AfxMessageBoxFormat(MB_YESNO | MB_ICONWARNING, _T("Are you sure want to delete file %s?"), pDoc->GetTitle()))
	{
		// close document before change file in system...
		AppUtils::CloseDocumentByFilePath(strFileToDelete);
		Sleep(500); // wait for closing completed
		if (PathUtils::SendToRecycleBin(this->GetSafeHwnd(), strFileToDelete))
		{
			// remove from explorer also...
			HTREEITEM hDeleteItem = GetFileExplorerCtrl().PathToItem(strFileToDelete);
			if (hDeleteItem)
			{
				GetFileExplorerCtrl().DeleteItem(hDeleteItem);
			}
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> Deleted path %s, you can restore it from recycle bin..."), strFileToDelete);
		}
		else
		{
			AfxMessageBoxFormat(MB_ICONWARNING, _T("[Error] Path %s does not allow to delete!"), strFileToDelete);
		}
	}
}

void CMainFrame::OnDocumentBookMark()
{
	CString strAppDataFolderPath = PathUtils::GetVinaTextAppDataPath();
	if (!PathFileExists(strAppDataFolderPath))
	{
		CreateDirectory(strAppDataFolderPath, NULL);
	}
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	if (!pDoc) return; CString strPathToBookmark = pDoc->GetPathName();
	CSetPathDlg dlg;
	dlg.m_strDlgCaption = _T("Bookmark this path...");
	dlg.m_sPath = strPathToBookmark;
	if (dlg.DoModal() == IDOK)
	{
		CString strPathBookmarkSave = PathUtils::GetVinaTextBookmarkPath();
		if (PathUtils::SaveFileAppendNoDuplicateLine(strPathBookmarkSave, dlg.m_sPath + EDITOR_NEW_LINE_LF))
		{
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> Added new bookmark path: %s"), dlg.m_sPath);
		}
		else
		{
			AfxMessageBox(_T("This path was already existed in bookmark table."), MB_ICONINFORMATION);
		}
		OnToolsOpenBookMarkPathTable();
	}
}

void CMainFrame::OnOptionGetFullFilePathDoubleQuote()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	if (!pDoc) return;
	CString strPathName = pDoc->GetPathName();
	PushTextToClipBoard(_T("\"") + strPathName + _T("\""));
}

BOOL CMainFrame::OnCloseMiniFrame(CPaneFrameWnd* pWnd)
{
	CEditorView* pView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
	if (pView)
	{
		pView->RenderIndicatorWordsAndCount(_T(""), 0);
	}
	return CMDIFrameWndEx::OnCloseMiniFrame(pWnd);
}

void CMainFrame::OnFileSendMailEx()
{
	CBaseDoc* pDoc = dynamic_cast<CBaseDoc*>(AppUtils::GetMDIActiveDocument());
	if (pDoc)
	{
		pDoc->OnFileSendMailEx();
	}
}

void CMainFrame::OnUpdateFileSendMailEx(CCmdUI * pCmdUI)
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	if (!pDoc) return;
	pCmdUI->Enable(PathFileExists(pDoc->GetPathName()));
}

using namespace HostManager;
void CMainFrame::OnTerminalOpenNewCMDWindow()
{
	SetCurrentDirectoryTerminal();
	HostApplicaton(HOST_APP_TYPE::TERMINAL_CMD, L"cmd.exe");
}

void CMainFrame::OnTerminalOpenNewPowerShellWindow()
{
	SetCurrentDirectoryTerminal();
	HostApplicaton(HOST_APP_TYPE::TERMINAL_POWERSHELL, L"powershell.exe");
}

void CMainFrame::OnHostMSEdge()
{
	CString strMSEdgePath = L"C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe";
	if (!PathFileExists(strMSEdgePath))
	{
		AfxMessageBox(_T("[Host Error] Can not found Microsoft Edge on this PC!")); return;
	}
	HostApplicaton(HOST_APP_TYPE::MS_EDGE, strMSEdgePath);
}

void CMainFrame::OnHostGoogleChrome()
{
	CString strChromePath = OSUtils::GetRegistryAppPath(L"chrome.exe");
	if (!PathFileExists(strChromePath))
	{
		AfxMessageBox(_T("[Host Error] Can not found Google Chrome on this PC!")); return;
	}
	HostApplicaton(HOST_APP_TYPE::CHROME_BROWSER, strChromePath);
}

void CMainFrame::OnHostMozillaFirefox()
{
	CString strFileFoxPath = OSUtils::GetRegistryAppPath(L"chrome.exe");
	if (!PathFileExists(strFileFoxPath))
	{
		AfxMessageBox(_T("[Host Error] Can not found FireFox on this PC!")); return;
	}
	HostApplicaton(HOST_APP_TYPE::FIREFOX_BROWSER, strFileFoxPath);
}

void CMainFrame::OnHostMSPaint()
{
	HostApplicaton(HOST_APP_TYPE::MS_PAINT, L"mspaint.exe");
}

void CMainFrame::OnHostFileExplorer()
{
	CString strNavigatePath = GetCurrentDocFolder();
	HostApplicaton(HOST_APP_TYPE::FILE_EXPLORER, _T(""), strNavigatePath);
}

void CMainFrame::OnHostMSPowerpoint()
{
	CString strMSPPTPath = OSUtils::GetRegistryAppPath(L"POWERPNT.EXE");
	if (!PathFileExists(strMSPPTPath))
	{
		AfxMessageBox(_T("[Host Error] Can not found Microsoft Powerpoint on this PC!")); return;
	}
	HostApplicaton(HOST_APP_TYPE::MS_OFFICE_PPT, strMSPPTPath, L"/B");
}

void CMainFrame::OnHostMSExcel()
{
	CString strMSExcelPath = OSUtils::GetRegistryAppPath(L"EXCEL.EXE");
	if (!PathFileExists(strMSExcelPath))
	{
		AfxMessageBox(_T("[Host Error] Can not found Microsoft Excel on this PC!")); return;
	}
	HostApplicaton(HOST_APP_TYPE::MS_OFFICE_EXCEL, strMSExcelPath, L"/s");
}

void CMainFrame::OnHostMSWord()
{
	CString strMSWordPath = OSUtils::GetRegistryAppPath(L"WINWORD.EXE");
	if (!PathFileExists(strMSWordPath))
	{
		AfxMessageBox(_T("[Host Error] Can not found Microsoft Word on this PC!")); return;
	}
	HostApplicaton(HOST_APP_TYPE::MS_OFFICE_WORD, strMSWordPath, L"/s");
}

void CMainFrame::OnToolPythonPipWindow()
{
	if (AppSettingMgr.m_strPythonFolderPath == _T("C:\\"))
	{
		AfxMessageBox(_T("Python Pip3 path does not exist, please set up it in Preference > General Settings > PythonFolderPath!"));
		return;
	}
	if (FALSE == PathFileExists(AppSettingMgr.m_strPythonFolderPath))
	{
		CString strMsg;
		strMsg.Format(_T("[Pip Path Error] %s does not exist...\n"), AppSettingMgr.m_strPythonFolderPath);
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strMsg, BasicColors::orange);
		return;
	}
	SetCurrentDirectoryW(AppSettingMgr.m_strPythonFolderPath);
	HostApplicaton(HOST_APP_TYPE::TERMINAL_POWERSHELL, L"powershell.exe");
	Sleep(500);
	// clipboard process...
	CString strClipBoardText = GetClipboardPlainText();
	PushTextToClipBoard(_T(".\\python.exe -m pip install -t Lib\\site-packages -U <package-name>"));
	OSUtils::PatseClipboardToCMD(AppUtils::GetVinaTextApp()->m_hLatestHostWND);
	PushTextToClipBoard(strClipBoardText);
}

void CMainFrame::OnToolNodeJSNPMWindow()
{
	if (AppSettingMgr.m_strNodeJSFolderPath == _T("C:\\"))
	{
		AfxMessageBox(_T("NodeJS path does not exist, please set up it in Preference > General Settings > NodeJSFolderPath!"));
		return;
	}
	if (FALSE == PathFileExists(AppSettingMgr.m_strNodeJSFolderPath))
	{
		CString strMsg;
		strMsg.Format(_T("[NodeJS Path Error] %s does not exist...\n"), AppSettingMgr.m_strNodeJSFolderPath);
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strMsg, BasicColors::orange);
		return;
	}
	SetCurrentDirectoryW(AppSettingMgr.m_strNodeJSFolderPath);
	HostApplicaton(HOST_APP_TYPE::TERMINAL_POWERSHELL, L"powershell.exe");
	Sleep(500);
	// clipboard process...
	CString strClipBoardText = GetClipboardPlainText();
	PushTextToClipBoard(_T("npm install <package_name>"));
	OSUtils::PatseClipboardToCMD(AppUtils::GetVinaTextApp()->m_hLatestHostWND);
	PushTextToClipBoard(strClipBoardText);
}

void CMainFrame::OnOptionsGetWifiInformation()
{
	CString strMsg = _T("\n________________| INTERNET WIFI INFORMATION |______________________________\n");
	CSystemInfo info;
	std::vector<std::wstring> wifi = info.GetSystemWifiList();
	if (wifi.empty())
	{
		strMsg += _T("> Error, can not access wifi information...\n");
	}
	else
	{
		for (const std::wstring& ssid : wifi)
		{
			strMsg += _T("> Getting password for [") + AppUtils::WStdToCString(ssid) + _T("] ...\n");
			strMsg += _T("Password\t:\t") + AppUtils::WStdToCString(info.GetWifiPassword(ssid)) + _T("\n\n");
		}
	}
	strMsg += _T("___________________________________________________________________________\n\n");
	LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strMsg);
}

void CMainFrame::OnOptionsGetSystemInformation()
{
	CString strMsg = _T("\n________________| SYSTEM INFORMATION |_____________________________________\n");
	CSystemInfo info;
	CStringArray macAddress, ipAddress;
	info.GetMACPhysicalIPAddress(macAddress, ipAddress);
	for (int i = 0; i < macAddress.GetCount(); ++i)
	{
		CString strTemp = _T("MAC Address %d: %s");
		strTemp.Format(strTemp, i, macAddress[i]);
		strMsg += strTemp + EDITOR_NEW_LINE_LF;
	}
	for (int i = 0; i < ipAddress.GetCount(); ++i)
	{
		CString strTemp = _T("IP Address %d: %s");
		strTemp.Format(strTemp, i, ipAddress[i]);
		strMsg += strTemp + EDITOR_NEW_LINE_LF;
	}
	auto strInfoHardware = info.GetGeneralHardwareInformation();
	strMsg += AppUtils::WStdToCString(strInfoHardware);
	strMsg += _T("___________________________________________________________________________\n\n");
	LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strMsg);
}

void CMainFrame::OnOptionsGetPATHVariable()
{
	CString strMsg = _T("\n________________| PATH ENVIRONMENT VARIABLES |_____________________________\n");
	auto size = GetEnvironmentVariableW(L"PATH", NULL, 0);
	std::wstring strPath(size, 0);
	GetEnvironmentVariableW(L"PATH", &strPath[0], size);
	std::vector<std::wstring> vecPaths = AppUtils::SplitterWStdString(strPath, L";");
	std::wstring line;
	for (auto const& path : vecPaths)
	{
		if (path.empty()) continue;
		line += path + EDITOR_NEW_LINE_LF;
	}
	strMsg += AppUtils::WStdToCString(line);
	strMsg += _T("\n___________________________________________________________________________\n\n");
	LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strMsg);
}

void CMainFrame::OnPrintFileNow()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument(); if (pDoc == NULL) return;
	if (pDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
	{
		CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(pDoc);
		if (pEditorDoc == NULL) return;
		CWindowsPrinter printer(pEditorDoc->GetPathName(), this->GetSafeHwnd());
		printer.PrintText(FALSE, pEditorDoc->GetEditorCtrl());
		LOG_OUTPUT_MESSAGE_COLOR(AfxCStringFormat(_T("> [Text Printer] Printing %s..."), pEditorDoc->GetPathName()), BasicColors::orange);
	}
	else if (pDoc->IsKindOf(RUNTIME_CLASS(CImageDoc)))
	{
		CImageDoc* pImageDoc = dynamic_cast<CImageDoc*>(pDoc);
		if (pImageDoc == NULL) return;
		CWindowsPrinter printer(pImageDoc->GetPathName(), this->GetSafeHwnd());
		printer.PrintImage(FALSE, pImageDoc->GetImageView());
		LOG_OUTPUT_MESSAGE_COLOR(AfxCStringFormat(_T("> [Image Printer] Printing %s..."), pImageDoc->GetPathName()), BasicColors::orange);
	}
}

void CMainFrame::OnPrintFileSetupDlg()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument(); if (pDoc == NULL) return;
	if (pDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
	{
		CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(pDoc);
		if (pEditorDoc == NULL) return;
		CWindowsPrinter printer(pDoc->GetPathName(), this->GetSafeHwnd());
		printer.PrintText(TRUE, pEditorDoc->GetEditorCtrl());
	}
	else if (pDoc->IsKindOf(RUNTIME_CLASS(CImageDoc)))
	{
		CImageDoc* pImageDoc = dynamic_cast<CImageDoc*>(pDoc);
		if (pImageDoc == NULL) return;
		CWindowsPrinter printer(pImageDoc->GetPathName(), this->GetSafeHwnd());
		printer.PrintImage(TRUE, pImageDoc->GetImageView());
	}
}

void CMainFrame::OnPrintPageSetupDlg()
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument(); if (pDoc == NULL) return;
	if (pDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)) || pDoc->IsKindOf(RUNTIME_CLASS(CImageDoc)))
	{
		CWindowsPrinter printer(_T(""), this->GetSafeHwnd());
		printer.ShowPageSetupDlg();
	}
}

void CMainFrame::UpdateUIForPrinter(CCmdUI * pCmdUI)
{
	CDocument* pDoc = GetActiveFrame()->GetActiveDocument();
	if (pDoc == NULL)
	{
		pCmdUI->Enable(FALSE); return;
	}
	if (pDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)) || pDoc->IsKindOf(RUNTIME_CLASS(CImageDoc)))
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CMainFrame::OnUpdatePrintFileNow(CCmdUI * pCmdUI)
{
	UpdateUIForPrinter(pCmdUI);
}

void CMainFrame::OnUpdatePrintFileSetupDlg(CCmdUI * pCmdUI)
{
	UpdateUIForPrinter(pCmdUI);
}

void CMainFrame::OnUpdatePrintPageSetupDlg(CCmdUI * pCmdUI)
{
	UpdateUIForPrinter(pCmdUI);
}

///////////////////////////// TOOLBARS //////////////////////////////////////////////////

BOOL CMainFrameToolBar::OnUserToolTip(CMFCToolBarButton * pButton, CString & strTTText) const
{
	if (pButton->m_nID == ID_FILE_NEW)
		strTTText = Native_Language("New File");
	else if (pButton->m_nID == ID_FILE_OPEN)
		strTTText = Native_Language("Open File");
	else if (pButton->m_nID == ID_FILE_SAVE)
		strTTText = Native_Language("Save File");
	else if (pButton->m_nID == ID_FILE_SAVE_ALL)
		strTTText = Native_Language("Save All");
	else if (pButton->m_nID == ID_EDIT_CUT)
		strTTText = Native_Language("Cut");
	else if (pButton->m_nID == ID_EDIT_COPY)
		strTTText = Native_Language("Copy");
	else if (pButton->m_nID == ID_EDIT_PASTE)
		strTTText = Native_Language("Paste");
	else if (pButton->m_nID == ID_PANE_FILE_EXPLORER)
		strTTText = Native_Language("Explorer Window (Ctrl + Shift + Q");
	else if (pButton->m_nID == ID_EDIT_UNDO)
		strTTText = Native_Language("Undo");
	else if (pButton->m_nID == ID_EDIT_REDO)
		strTTText = Native_Language("Redo");
	else if (pButton->m_nID == ID_PANE_OUTPUT_WINDOW)
		strTTText = Native_Language("Message Window");
	else if (pButton->m_nID == ID_QUICK_SEARCH)
		strTTText = Native_Language("Quick Search Dialog");
	else if (pButton->m_nID == ID_PANE_SEARCH_AND_REPLACE_WINDOW)
		strTTText = Native_Language("Search Text Window");
	else if (pButton->m_nID == ID_WINDOW_MANAGER)
		strTTText = Native_Language("Window Manager");
	else if (pButton->m_nID == ID_EDITOR_COMMENT)
		strTTText = Native_Language("Comment");
	else if (pButton->m_nID == ID_EDITOR_UNCOMMENT)
		strTTText = Native_Language("Uncomment");
	else if (pButton->m_nID == ID_DOCUMENT_SET_READ_ONLY)
		strTTText = Native_Language("Disable Edit Mode");
	else if (pButton->m_nID == ID_MDI_TAB_CLOSE_ALL_DOC)
		strTTText = Native_Language("Close All Tabs");
	else if (pButton->m_nID == ID_EDIT_SHOW_ALL_CHARACTOR)
		strTTText = Native_Language("All Hidden Characters");
	else if (pButton->m_nID == ID_EDITOR_SHOW_TRACKING_BAR)
		strTTText = Native_Language("Right Tracking Bar");
	else if (pButton->m_nID == ID_EDITOR_FULL_SCREEN_MODE)
		strTTText = Native_Language("Full Screen Mode");
	else if (pButton->m_nID == ID_DEBUGGER_START)
		strTTText = Native_Language("Start Debugging");
	else if (pButton->m_nID == ID_TOGGLE_AUTO_COMPLETE)
		strTTText = Native_Language("Auto Show Complete");
	else if (pButton->m_nID == ID_PATH_VINATEXT_BOOKMARK_TABLE)
		strTTText = Native_Language("Open Path Bookmark Table");
	else if (pButton->m_nID == ID_DOCUMENT_FILE_SUMMARY)
		strTTText = Native_Language("Print File Information");
	else if (pButton->m_nID == ID_MDI_TAB_MOVE_PREVIOUS_TAB)
		strTTText = Native_Language("Move To Previous Tab Group");
	else if (pButton->m_nID == ID_MDI_TAB_NEW_VERTICAL_TAB)
		strTTText = Native_Language("Move To Vertical Tab Group");
	else if (pButton->m_nID == ID_MDI_TAB_OPEN_CONTAINER_FOLDER)
		strTTText = Native_Language("Reveal in Container Folder");
	else if (pButton->m_nID == ID_MDI_TAB_LOCATE_IN_FILE_EXPLORER)
		strTTText = Native_Language("Reveal in Explorer Window");
	else if (pButton->m_nID == ID_MDI_TAB_OPEN_CMD)
		strTTText = Native_Language("Open CMD Terminal");
	else if (pButton->m_nID == ID_DOCUMENT_TRANSLATE)
		strTTText = Native_Language("Translate Selected Text");
	else if (pButton->m_nID == ID_MDI_TAB_RELOAD)
		strTTText = Native_Language("Reload File");
	else if (pButton->m_nID == ID_MDI_TAB_CLOSE)
		strTTText = Native_Language("Close File");
	return TRUE;
}
