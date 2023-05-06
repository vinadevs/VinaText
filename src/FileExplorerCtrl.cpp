/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

/////////////////////////////////  Includes  //////////////////////////////////

#include "stdafx.h"

#ifndef FILETREECTRL_NO_RESOURCES
#include "VinaTextApp.h"
#include "MainFrm.h"
#include "EditorDoc.h"
#include "EditorView.h"
#include "ImageDoc.h"
#include "ImageView.h"
#include "PdfDoc.h"
#include "PdfView.h"
#include "MediaDoc.h"
#include "MediaView.h"
#endif //#ifndef FILETREECTRL_NO_RESOURCES

#include "FileExplorerCtrl.h"
#include "AppUtil.h"
#include "ShellContextMenu.h"
#include "RAIIUtils.h"
#include "GuiUtils.h"

#include "SearchNavigatePathDlg.h"
#include "SetBookmarkPathDlg.h"
#include "BookMarkPathDlg.h"
#include "SetDeleteFileByExtDlg.h"
#include "SelectedPathDlg.h"
#include "FilenameFilterDlg.h"
#include "CreateNewMultiplePath.h"

#include "AppSettings.h"
#include "HostManager.h"
#include "FindPathWorker.h"

#include "LocalizationHandler.h"

//////////////////////////////// Defines / Locals /////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#endif //#ifdef _DEBUG

#pragma warning(disable:4996)

#pragma warning(suppress: 26426)
const UINT WM_TREEUPDATE_CHANGE = ::RegisterWindowMessage(_T("FileExplorerCtrlUpdateChange"));
constexpr int FILETREECTRL_TIMERID = 1;
constexpr int FILETREECTRL_TIMERTICK_FOR_EXPANSION = 3;

//Pull in the libs automatically
#pragma comment(lib, "mpr.lib")
#pragma comment(lib, "Netapi32.lib")
#pragma warning(disable: 4800)
////////////////////////////// Implementation /////////////////////////////////

CFileExplorerCtrlItemInfo::CFileExplorerCtrlItemInfo() noexcept : m_NodeType(NodeType::UnknownNode),
m_bExtensionHidden(false),
m_dwNetResourceScope(0),
m_dwNetResourceType(0),
m_dwNetResourceDisplayType(0),
m_dwNetResourceUsage(0)
{
}

#pragma warning(suppress: 26455)
CSystemImageList::CSystemImageList()
{
	//Get the temp directory. This is used to then bring back the system image list
	CString sTempDir;
	GetTempPath(_MAX_PATH, sTempDir.GetBuffer(_MAX_PATH));
	sTempDir.ReleaseBuffer();
	CString sDrive;
	_tsplitpath_s(sTempDir, sDrive.GetBuffer(_MAX_DRIVE), _MAX_DRIVE, NULL, 0, NULL, 0, NULL, 0);
	sDrive.ReleaseBuffer();
	const int nLen = sDrive.GetLength();
	if (nLen)
	{
		if (sDrive[nLen - 1] != _T('\\'))
			sDrive += _T("\\");

		//Attach to the system image list
		SHFILEINFO sfi{};
#pragma warning(suppress: 26490)
		Attach(reinterpret_cast<HIMAGELIST>(SHGetFileInfo(sTempDir, 0, &sfi, sizeof(SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_SMALLICON)));
	}
}

CShareEnumerator::CShareEnumerator() noexcept : m_pNTShareInfo(NULL),
m_dwShares(0)

{
	//Update the array of shares we know about
	Refresh();
}

CShareEnumerator::~CShareEnumerator()
{
	//Free the buffer if valid
	if (m_pNTShareInfo != NULL)
	{
		NetApiBufferFree(m_pNTShareInfo);
		m_pNTShareInfo = NULL;
	}
}

void CShareEnumerator::Refresh() noexcept
{
	//Reset the count of shares
	m_dwShares = 0;

	//Free the buffer if valid
	if (m_pNTShareInfo != NULL)
		NetApiBufferFree(m_pNTShareInfo);

	//Call the function to enumerate the shares
	DWORD dwEntriesRead = 0;
#pragma warning(suppress: 26490)
	const NET_API_STATUS nStatus = NetShareEnum(NULL, 502, reinterpret_cast<LPBYTE*>(&m_pNTShareInfo), MAX_PREFERRED_LENGTH, &dwEntriesRead, &m_dwShares, NULL);
	UNREFERENCED_PARAMETER(nStatus);
}

bool CShareEnumerator::IsShared(_In_ const CString& sPath)
{
	if (m_pNTShareInfo != NULL)
	{
		for (DWORD i = 0; i < m_dwShares; i++)
		{
#pragma warning(suppress: 26481)
			CString sShare(m_pNTShareInfo[i].shi502_path);
#pragma warning(suppress: 26481)
			if ((sPath.CompareNoCase(sShare) == 0) && ((m_pNTShareInfo[i].shi502_type == STYPE_DISKTREE) || ((m_pNTShareInfo[i].shi502_type == STYPE_PRINTQ))))
				return true;
		}
	}
	return false;
}

#pragma warning(suppress: 26409 26440 26433 26477)
IMPLEMENT_DYNCREATE(CFileExplorerCtrl, FILETREECTRL_BASE_CLASS)

#pragma warning(suppress: 26433 26440)
BEGIN_MESSAGE_MAP(CFileExplorerCtrl, FILETREECTRL_BASE_CLASS) //NOLINT(modernize-avoid-c-arrays)
#ifndef FILETREECTRL_NO_RESOURCES
	ON_COMMAND(ID_TREEFILECTRL_VIRUS_SCANNER, &CFileExplorerCtrl::OnVirusScanner)
	ON_COMMAND(ID_TREEFILECTRL_PROPERTIES, &CFileExplorerCtrl::OnProperties)
	ON_UPDATE_COMMAND_UI(ID_TREEFILECTRL_PROPERTIES, &CFileExplorerCtrl::OnUpdateProperties)
	ON_COMMAND(ID_TREEFILECTRL_RENAME, &CFileExplorerCtrl::OnRename)
	ON_UPDATE_COMMAND_UI(ID_TREEFILECTRL_RENAME, &CFileExplorerCtrl::OnUpdateRename)
	ON_COMMAND(ID_TREEFILECTRL_OPEN, &CFileExplorerCtrl::OnOpen)
	ON_UPDATE_COMMAND_UI(ID_TREEFILECTRL_OPEN, &CFileExplorerCtrl::OnUpdateOpen)
	ON_COMMAND(ID_TREEFILECTRL_CLOSE, &CFileExplorerCtrl::OnClose)
	ON_COMMAND(ID_TREEFILECTRL_DELETE, &CFileExplorerCtrl::OnDelete)
	ON_UPDATE_COMMAND_UI(ID_TREEFILECTRL_DELETE, &CFileExplorerCtrl::OnUpdateDelete)
	ON_COMMAND(ID_TREEFILECTRL_CREATEFOLDER, &CFileExplorerCtrl::OnCreateFolder)
	ON_COMMAND(ID_TREEFILECTRL_CREATE_MULTIPLE, &CFileExplorerCtrl::OnCreateNewMutiple)
	ON_COMMAND(ID_TREEFILECTRL_EXPAND_ALL, &CFileExplorerCtrl::OnExpandAll)
	ON_COMMAND(ID_TREEFILECTRL_COLLAPSE_ALL, &CFileExplorerCtrl::OnCollapseAll)
	ON_COMMAND(ID_TREEFILECTRL_COLLAPSE_PARENT, &CFileExplorerCtrl::OnCollapseParent)
	ON_COMMAND(ID_TREEFILECTRL_ADD_NEW_FOLDER, &CFileExplorerCtrl::OnAddMoreFolderToWorkSpace)
	ON_COMMAND(ID_TREEFILECTRL_BOOKMARKPATH, &CFileExplorerCtrl::OnBookMarkPath)
	ON_COMMAND(ID_TREEFILECTRL_REMOVE_FOLDER, &CFileExplorerCtrl::OnRemoveFolderFromWorkSpace)
	ON_COMMAND(ID_TREEFILECTRL_SETSELECTEDPATH, &CFileExplorerCtrl::OnJumpToPath)
	ON_COMMAND(ID_TREEFILECTRL_SETROOTFOLDER, &CFileExplorerCtrl::OnSetAsWorkspaceFolder)
	ON_COMMAND(ID_TREEFILECTRL_BACK_TO_ORIGINAL, &CFileExplorerCtrl::OnBackToOriginalExplorer)
	ON_COMMAND(ID_TREEFILECTRL_FILENAME_FILTER, &CFileExplorerCtrl::OnSetFileExtensionFilter)
	ON_COMMAND(ID_TREEFILECTRL_CREATEFILE, &CFileExplorerCtrl::OnCreateFile)
	ON_COMMAND(ID_TREEFILECTRL_SHOW_RECYCLE_BIN, &CFileExplorerCtrl::OnOpenRecycleBin)
	ON_COMMAND(ID_TREEFILECTRL_GET_FULL_FILE_PATH, &CFileExplorerCtrl::OnGetFullPath)
	ON_COMMAND(ID_TREEFILECTRL_GET_FULL_FILE_PATH_DOUBLE_QUOTE, &CFileExplorerCtrl::OnGetFullPathDoubleQuote)
	ON_COMMAND(ID_TREEFILECTRL_GET_FULL_FILE_PATH_DOUBLE_SLASH, &CFileExplorerCtrl::OnGetFullPathDoubleSlash)
	ON_COMMAND(ID_TREEFILECTRL_GET_FULL_FILE_PATH_FORWARD_SLASH, &CFileExplorerCtrl::OnGetFullPathForwardSlash)
	ON_COMMAND(ID_TREEFILECTRL_GET_FOLDER_PATH, &CFileExplorerCtrl::OnGetContainerPath)
	ON_COMMAND(ID_TREEFILECTRL_GET_FILE_NAME, &CFileExplorerCtrl::OnGetName)
	ON_COMMAND(ID_TREEFILECTRL_OPEN_NEW_CMD_TAB, &CFileExplorerCtrl::OnTerminalOpenNewCMDTab)
	ON_COMMAND(ID_TREEFILECTRL_OPEN_NEW_POWERSHELL_TAB, &CFileExplorerCtrl::OnTerminalOpenNewPowerShellTab)
	ON_COMMAND(ID_TREEFILECTRL_OPEN_NEW_WSL_TAB, &CFileExplorerCtrl::OnTerminalOpenNewWSLTab)
	ON_COMMAND(ID_TREEFILECTRL_RUN_ACTIVE_FILE, &CFileExplorerCtrl::OnTerminalRunActiveFile)
	ON_UPDATE_COMMAND_UI(ID_TREEFILECTRL_RUN_ACTIVE_FILE, &CFileExplorerCtrl::OnUpdateTerminalRunActiveFile)
	ON_COMMAND(ID_TREEFILECTRL_OPEN_CMD, &CFileExplorerCtrl::OnOpenCMDHere)
	ON_COMMAND(ID_TREEFILECTRL_OPEN_CMD_APPEND_FILE, &CFileExplorerCtrl::OnOpenCMDAppendFileHere)
	ON_COMMAND(ID_TREEFILECTRL_OPEN_CMD_APPEND_PATH, &CFileExplorerCtrl::OnOpenCMDAppendPathHere)
	ON_COMMAND(ID_TREEFILECTRL_OPEN_CMD_PASTE_CLIPBOARD, &CFileExplorerCtrl::OnOpenCMDPatseClipboardHere)
	ON_COMMAND(ID_TREEFILECTRL_OPEN_POWERSHELL, &CFileExplorerCtrl::OnOpenPowerShellHere)
	ON_COMMAND(ID_TREEFILECTRL_OPEN_GITBASH, &CFileExplorerCtrl::OnOpenGitBashHere)
	ON_COMMAND(ID_TREEFILECTRL_OPEN_WSL, &CFileExplorerCtrl::OnOpenGitWslHere)
	ON_COMMAND(ID_TREEFILECTRL_LIST_ALL_FILE, &CFileExplorerCtrl::OnOptionsEditListAllFile)
	ON_COMMAND(ID_TREEFILECTRL_LIST_ALL_FOLDER, &CFileExplorerCtrl::OnOptionsEditListAllFolder)
	ON_COMMAND(ID_TREEFILECTRL_SEARCH_ON_FOLDER, &CFileExplorerCtrl::OnOptionsEditSearchText)
	ON_COMMAND(ID_TREEFILECTRL_REPLACE_ON_FOLDER, &CFileExplorerCtrl::OnOptionsEditReplaceOnfolder)
	ON_COMMAND(ID_TREEFILECTRL_SEARCH_FILES, &CFileExplorerCtrl::OnOptionsEditSearchFiles)
	ON_COMMAND(ID_TREEFILECTRL_FILE_SAVE_AS, &CFileExplorerCtrl::OnOptionsEditFileSaveAs)
	ON_COMMAND(ID_TREEFILECTRL_CUT, &CFileExplorerCtrl::OnCut)
	ON_COMMAND(ID_TREEFILECTRL_COPY, &CFileExplorerCtrl::OnCopy)
	ON_COMMAND(ID_TREEFILECTRL_PASTE, &CFileExplorerCtrl::OnPaste)
	ON_UPDATE_COMMAND_UI(ID_TREEFILECTRL_PASTE, &CFileExplorerCtrl::OnUpdatePaste)
	ON_COMMAND(ID_TREEFILECTRL_REFRESH, &CFileExplorerCtrl::OnRefresh)
	ON_COMMAND(ID_TREEFILECTRL_UPONELEVEL, &CFileExplorerCtrl::OnUpOneLevel)
	ON_UPDATE_COMMAND_UI(ID_TREEFILECTRL_UPONELEVEL, &CFileExplorerCtrl::OnUpdateUpOneLevel)
	ON_COMMAND(ID_TREEFILECTRL_BACK, &CFileExplorerCtrl::OnBack)
	ON_UPDATE_COMMAND_UI(ID_TREEFILECTRL_BACK, &CFileExplorerCtrl::OnUpdateBack)
	ON_COMMAND(ID_TREEFILECTRL_FORWARD, &CFileExplorerCtrl::OnForward)
	ON_COMMAND(ID_TREEFILECTRL_SHOW_SYSTEM_MENU, &CFileExplorerCtrl::OnShowSystemMenu)
	ON_UPDATE_COMMAND_UI(ID_TREEFILECTRL_FORWARD, &CFileExplorerCtrl::OnUpdateForward)
	ON_COMMAND(ID_TREEFILECTRL_OPEN_BY_VINATEXT, &CFileExplorerCtrl::OnCreateDocumentFromFile)
	ON_COMMAND(ID_TREEFILECTRL_OPEN_BY_AS_RAW_FORMAT, &CFileExplorerCtrl::OnOpenAsRawFormat)
	ON_COMMAND(ID_TREEFILECTRL_OPEN_ALL_BY_VINATEXT, &CFileExplorerCtrl::OnOpenAllFileByVinaText)
	ON_COMMAND(ID_TREEFILECTRL_OPEN_CONTAINER, &CFileExplorerCtrl::OnOpenFileContainer)
	ON_COMMAND(ID_TREEFILECTRL_NEW_FILE_EXPLORER_TAB, &CFileExplorerCtrl::OnHostFileExplorer)
	ON_COMMAND(ID_TREEFILECTRL_LOAD_AUTOCOMPLETE, &CFileExplorerCtrl::OnLoadAutoCompleteDataset)
	ON_COMMAND(ID_TREEFILECTRL_DELETE_FILE_BY_EXTENSION, &CFileExplorerCtrl::OnDeleteFileByExtension)
	ON_COMMAND(ID_TREEFILECTRL_EDIT_WIH_MSPAINT, &CFileExplorerCtrl::OnEditWithMSPaint)
	ON_COMMAND(ID_TREEFILECTRL_FILE_CHROME, &CFileExplorerCtrl::OnOpenInChrome)
	ON_COMMAND(ID_TREEFILECTRL_FILE_EDGE, &CFileExplorerCtrl::OnOpenInEdge)
	ON_COMMAND(ID_TREEFILECTRL_FILE_FIREFOX, &CFileExplorerCtrl::OnOpenInFireFox)
#endif //#ifndef FILETREECTRL_NO_RESOURCES
	ON_WM_INITMENUPOPUP()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
#pragma warning(suppress: 26454)
	ON_NOTIFY_REFLECT_EX(NM_DBLCLK, &CFileExplorerCtrl::OnDblclk)
#pragma warning(suppress: 26454)
	ON_NOTIFY_REFLECT_EX(TVN_ITEMEXPANDING, &CFileExplorerCtrl::OnItemExpanding)
#pragma warning(suppress: 26454)
	ON_NOTIFY_REFLECT_EX(TVN_BEGINLABELEDIT, &CFileExplorerCtrl::OnBeginLabelEdit)
#pragma warning(suppress: 26454)
	ON_NOTIFY_REFLECT_EX(TVN_ENDLABELEDIT, &CFileExplorerCtrl::OnEndLabelEdit)
#pragma warning(suppress: 26454)
	ON_NOTIFY_REFLECT_EX(NM_RCLICK, &CFileExplorerCtrl::OnRclick)
#ifndef FILETREECTRL_NO_RESOURCES
#pragma warning(suppress: 26454)
	ON_NOTIFY_REFLECT_EX(TVN_BEGINDRAG, &CFileExplorerCtrl::OnBeginDrag)
#endif //#ifndef FILETREECTRL_NO_RESOURCES
#pragma warning(suppress: 26454)
	ON_NOTIFY_REFLECT_EX(NM_CUSTOMDRAW, &CFileExplorerCtrl::OnCustomDraw)
#pragma warning(suppress: 26454)
	ON_NOTIFY_REFLECT_EX(TVN_SELCHANGED, &CFileExplorerCtrl::OnSelChanged)
#pragma warning(suppress: 26454)
	ON_NOTIFY_REFLECT_EX(TVN_DELETEITEM, &CFileExplorerCtrl::OnDeleteItem)
	ON_REGISTERED_MESSAGE(WM_TREEUPDATE_CHANGE, &CFileExplorerCtrl::OnChange)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, &CFileExplorerCtrl::OnToolTipTextNotify)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, &CFileExplorerCtrl::OnToolTipTextNotify)
END_MESSAGE_MAP()

#pragma warning(suppress: 26455 26495)
CFileExplorerCtrl::CFileExplorerCtrl() : FILETREECTRL_BASE_CLASS(),
	m_bShowFiles(true),
	m_hRoot(TVI_ROOT),
	#ifndef FILETREECTRL_NO_RESOURCES
	m_hItemDrag(NULL),
	m_hItemDrop(NULL),
	#endif //#ifndef FILETREECTRL_NO_RESOURCES
	m_hNetworkRoot(NULL),
	m_hDesktop(NULL),
	m_hMyDocumentsRoot(NULL),
	m_hMyComputerRoot(NULL),
	m_hCurrentUserFolderRoot(NULL),
	m_hRootedFolder(NULL),
	m_bShowMyComputer(true),
	m_bShowDesktop(true),
	m_bShowMyDocuments(true),
	m_bShowCurrentUserFolder(true),
	#ifndef FILETREECTRL_NO_RESOURCES
	m_pilDrag(NULL),
	#endif //#ifndef FILETREECTRL_NO_RESOURCES
	m_nTimerID(0),
	#ifndef FILETREECTRL_NO_RESOURCES
	m_DropCopyCursor(NULL),
	m_NoDropCopyCursor(NULL),
	m_DropMoveCursor(NULL),
	m_NoDropMoveCursor(NULL),
	#endif //#ifndef FILETREECTRL_NO_RESOURCES
	m_TimerTicks(0),
	m_bAllowDragDrop(true),
	m_bAllowRename(true),
	m_bAllowOpen(true),
	m_bAllowProperties(true),
	m_bAllowDelete(true),
	m_bAllowCreateFileAndFolder(true),
	m_dwDriveHideFlags(m_dwDriveHideFlags | CFileExplorerCtrl::DriveType::DRIVE_ATTRIBUTE_CDROM), // Hide CDROM Drive
	m_rgbCompressed(RGB(0, 0, 255)),
	m_bShowCompressedUsingDifferentColor(true),
	m_rgbEncrypted(RGB(98, 146, 13)),
	m_bShowEncryptedUsingDifferentColor(true),
	m_nMaxHistory(20),
	m_bUpdatingHistorySelection(false),
	m_bShowNetwork(false),
	m_bShowSharedUsingDifferentIcon(true),
	m_FileExtensions(HideFileExtension::UseTheShellSetting),
	m_dwNetworkItemTypes(RESOURCETYPE_ANY),
	m_bShowDriveLabels(true),
	m_bShowRootedFolder(true),
	m_bAutoRefresh(true),
	#ifndef FILETREECTRL_NO_CACHE_COMPUTER_ICON
	m_nComputerIconIndex(-1),
	m_nSelectedComputerIconIndex(-1),
	#endif
	m_pMonitoringThread(NULL)
{
	if (AppSettingMgr.m_bHideAllTargetFileSystem)
	{
		m_dwFileHideFlags = (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_OFFLINE | FILE_ATTRIBUTE_TEMPORARY);
		m_dwFolderHideFlags = (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_OFFLINE | FILE_ATTRIBUTE_TEMPORARY);
	}
	else
	{
		m_dwFileHideFlags = (FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_OFFLINE);
		m_dwFolderHideFlags = (FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_OFFLINE);
	}

	m_FileNameMasks.emplace_back(_T("*.*"));

	for (auto& media : m_MediaIDs)
	{
		media = 0xFFFFFFFF;
	}

	//As a performance optimization we cache the indexes for the computer and selected computer icons, so that we can use it 
	//when displaying machines on the network. This helps to speed up the performance of CFileExplorerCtrl when browsing domains or 
	//workgroups with a large number of workstations and servers.
#ifndef FILETREECTRL_NO_CACHE_COMPUTER_ICON
	CString sComputerName;
	DWORD dwCompuerNameSize = MAX_COMPUTERNAME_LENGTH + 1;
	const BOOL bGetCN = GetComputerName(sComputerName.GetBuffer(MAX_COMPUTERNAME_LENGTH + 1), &dwCompuerNameSize);
	sComputerName.ReleaseBuffer();
	if (bGetCN)
	{
		sComputerName = _T("\\\\") + sComputerName;
		m_nComputerIconIndex = GetIconIndex(sComputerName);
		m_nSelectedComputerIconIndex = GetSelIconIndex(sComputerName);
	}
#endif //#ifndef FILETREECTRL_NO_CACHE_COMPUTER_ICON  
}

int CALLBACK CFileExplorerCtrl::CompareByFilenameNoCase(_In_ LPARAM lParam1, _In_ LPARAM lParam2, _In_ LPARAM /*lParamSort*/)
{
#pragma warning(suppress: 26490)
	const CFileExplorerCtrlItemInfo* pItem1 = reinterpret_cast<CFileExplorerCtrlItemInfo*>(lParam1);
#pragma warning(suppress: 26490)
	const CFileExplorerCtrlItemInfo* pItem2 = reinterpret_cast<CFileExplorerCtrlItemInfo*>(lParam2);
	//Validate our parameters
#pragma warning(suppress: 26496)
	AFXASSUME(pItem1 != NULL);
#pragma warning(suppress: 26496)
	AFXASSUME(pItem2 != NULL);

	//Handle the special ordering of some nodes
#pragma warning(suppress: 26489)
	if (pItem1->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::CurrentUserFolderNode) //Current User node come before anything else
		return -1;
#pragma warning(suppress: 26489)
	if ((pItem1->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::MyDocumentsNode) && (pItem2->m_NodeType != CFileExplorerCtrlItemInfo::NodeType::CurrentUserFolderNode)) //Then "My Documents"
		return -1;
#pragma warning(suppress: 26489)
	else if ((pItem1->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::MyComputerNode) && (pItem2->m_NodeType != CFileExplorerCtrlItemInfo::NodeType::CurrentUserFolderNode) && (pItem2->m_NodeType != CFileExplorerCtrlItemInfo::NodeType::MyDocumentsNode)) //Then "My Computer/This PC"
		return -1;
#pragma warning(suppress: 26489)
	else if ((pItem1->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::NetworkNode) && (pItem2->m_NodeType != CFileExplorerCtrlItemInfo::NodeType::CurrentUserFolderNode) && (pItem2->m_NodeType != CFileExplorerCtrlItemInfo::NodeType::MyDocumentsNode) && (pItem2->m_NodeType != CFileExplorerCtrlItemInfo::NodeType::MyComputerNode)) //Then "My Network Places" 
		return -1;

	//And then fall back to the standard sorting order
#pragma warning(suppress: 26489)
	if (pItem1->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::FileNode)
	{
#pragma warning(suppress: 26489)
		if (pItem2->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::FileNode)
			return pItem1->m_sRelativePath.CompareNoCase(pItem2->m_sRelativePath);
		else
			return 1;
	}
	else
	{
#pragma warning(suppress: 26489)
		if (pItem2->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::FileNode)
			return -1;
		else
#pragma warning(suppress: 26489)
			return pItem1->m_sRelativePath.CompareNoCase(pItem2->m_sRelativePath);
	}
}

#ifdef _DEBUG
void CFileExplorerCtrl::AssertValid() const
{
	//Let the base class do its thing
	__super::AssertValid();
}

void CFileExplorerCtrl::Dump(CDumpContext& dc) const
{
	//Let the base class do its thing
	__super::Dump(dc);
}
#endif //#ifdef _DEBUG

void CFileExplorerCtrl::SetShowFiles(_In_ bool bFiles)
{
	//Since it can be touched by more than one thead
	m_bShowFiles = bFiles;

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::SetRootFolder(_In_ const CString& sPath)
{
	m_NewAddedFolderData.clear();

	m_sRootFolder = sPath;

	//Ensure it is not terminated with a "\"
	const int nLength = m_sRootFolder.GetLength();
	if (nLength && (m_sRootFolder[nLength - 1] == _T('\\'))) //NOLINT(clang-analyzer-core.CallAndMessage)
		m_sRootFolder = m_sRootFolder.Left(nLength - 1);

	//Force a refresh
	Refresh();
}

int CFileExplorerCtrl::GetIconIndex(_In_ HTREEITEM hItem)
{
	TVITEM tvi{};
	tvi.mask = TVIF_HANDLE | TVIF_IMAGE;
	tvi.hItem = hItem;
	if (GetItem(&tvi))
		return tvi.iImage;
	else
		return -1;
}

#pragma warning(suppress: 26440)
int CFileExplorerCtrl::GetIconIndex(_In_ const CString& sFilename)
{
	SHFILEINFO sfi{};
	SHGetFileInfo(sFilename, 0, &sfi, sizeof(SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
	return sfi.iIcon;
}

#pragma warning(suppress: 26440)
int CFileExplorerCtrl::GetSelIconIndex(_In_ const CString& sFilename)
{
	SHFILEINFO sfi{};
	SHGetFileInfo(sFilename, 0, &sfi, sizeof(SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_OPENICON | SHGFI_SMALLICON);
	return sfi.iIcon;
}

#pragma warning(suppress: 26440)
int CFileExplorerCtrl::GetIconIndex(_In_ LPITEMIDLIST lpPIDL)
{
	SHFILEINFO sfi{};
#pragma warning(suppress: 26490)
	SHGetFileInfo(reinterpret_cast<LPCTSTR>(lpPIDL), 0, &sfi, sizeof(sfi), SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
	return sfi.iIcon;
}

#pragma warning(suppress: 26440)
int CFileExplorerCtrl::GetSelIconIndex(_In_ LPITEMIDLIST lpPIDL)
{
	SHFILEINFO sfi{};
#pragma warning(suppress: 26490)
	SHGetFileInfo(reinterpret_cast<LPCTSTR>(lpPIDL), 0, &sfi, sizeof(sfi), SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_OPENICON);
	return sfi.iIcon;
}

int CFileExplorerCtrl::GetSelIconIndex(_In_ HTREEITEM hItem)
{
	TVITEM tvi{};
	tvi.mask = TVIF_HANDLE | TVIF_SELECTEDIMAGE;
	tvi.hItem = hItem;
	if (GetItem(&tvi))
		return tvi.iSelectedImage;
	else
		return -1;
}

HTREEITEM CFileExplorerCtrl::FindSibling(_In_ HTREEITEM hParent, _In_ const CString& sItem) const
{
	HTREEITEM hChild = GetChildItem(hParent);
	while (hChild)
	{
#pragma warning(suppress: 26490)
		const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hChild));
#pragma warning(suppress: 26496)
		AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26489)
		if (pItem->m_sRelativePath.CompareNoCase(sItem) == 0)
			return hChild;
		hChild = GetNextItem(hChild, TVGN_NEXT);
	}
	return NULL;
}

CString CFileExplorerCtrl::GetSelectedPath()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
		return ItemToPath(hItem);
	else
		return CString();
}

HTREEITEM CFileExplorerCtrl::FindServersNode(_In_ HTREEITEM hFindFrom) const
{
	if (m_bShowNetwork)
	{
		//Try to find some "servers" in the child items of hFindFrom
		HTREEITEM hChild = GetChildItem(hFindFrom);
		while (hChild)
		{
#pragma warning(suppress: 26490)
			const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hChild));
#pragma warning(suppress: 26496)
			AFXASSUME(pItem != NULL);
			//Found a share
#pragma warning(suppress: 26489)
			if (pItem->m_dwNetResourceDisplayType == RESOURCEDISPLAYTYPE_SERVER)
				return hFindFrom;

			//Get the next sibling for the next loop around
			hChild = GetNextSiblingItem(hChild);
		}

		//Ok, since we got here, we did not find any servers in any of the child nodes of this 
		//item. In this case we need to call ourselves recursively to find one
		hChild = GetChildItem(hFindFrom);
		while (hChild)
		{
			HTREEITEM hFound = FindServersNode(hChild);
			if (hFound)
				return hFound;

			//Get the next sibling for the next loop around
			hChild = GetNextSiblingItem(hChild);
		}
	}

	//If we got as far as here then no servers were found.
	return NULL;
}

void CFileExplorerCtrl::SetHasPlusButton(_In_ HTREEITEM hItem, _In_ bool bHavePlus)
{
	TVITEM tvItem{};
	tvItem.hItem = hItem;
	tvItem.mask = TVIF_HANDLE | TVIF_CHILDREN;
	tvItem.cChildren = bHavePlus;
	SetItem(&tvItem);
}

bool CFileExplorerCtrl::HasPlusButton(_In_ HTREEITEM hItem)
{
	TVITEM tvItem{};
	tvItem.hItem = hItem;
	tvItem.mask = TVIF_HANDLE | TVIF_CHILDREN;
	return GetItem(&tvItem) && (tvItem.cChildren != 0);
}

HTREEITEM CFileExplorerCtrl::SetSelectedPath(_In_ const CString& sPath, _In_ BOOL bExpanded)
{
	CString sSearch(sPath);
	sSearch.Replace(_T("/"), _T("\\"));
	sSearch.Replace(_T("\\\\"), _T("\\"));
	sSearch.Replace(_T("\n"), _T(""));
	if (!PathFileExists(sSearch)) return NULL;
	sSearch.MakeUpper();
	int nSearchLength = sSearch.GetLength();
	if (nSearchLength == 0)
	{
		TRACE(_T("CFileExplorerCtrl::SetSelectedPath, Cannot select a empty path\n"));
		return NULL;
	}

	//Remove initial part of path if the root folder is setup
	CString sRootFolder(m_sRootFolder);
	sRootFolder.MakeUpper();
	const int nRootLength = sRootFolder.GetLength();
	if (nRootLength)
	{
		if (sSearch.Find(sRootFolder) != 0)
		{
			TRACE(_T("CFileExplorerCtrl::SetSelectedPath, Could not select the path %s as the root has been configued as %s\n"), sPath.GetString(), m_sRootFolder.GetString());
			return NULL;
		}
		sSearch = sSearch.Right(sSearch.GetLength() - nRootLength);

		//Remove leading "\" from the path
		nSearchLength = sSearch.GetLength();
		if (nSearchLength > 1 && sSearch.GetAt(0) == _T('\\'))
			sSearch = sSearch.Right(nSearchLength - 1);
	}

	//Remove trailing "\" from the path
	nSearchLength = sSearch.GetLength();
	if ((nSearchLength > 3) && sSearch.GetAt(nSearchLength - 1) == _T('\\'))
		sSearch = sSearch.Left(nSearchLength - 1);

	SetRedraw(FALSE);

	//Handle selection of the rooted folder if necessary
	HTREEITEM hItemFound = m_hRoot;
	if (nRootLength && m_hRootedFolder)
	{
		hItemFound = m_hRootedFolder;
		SelectItem(hItemFound);

		const bool bHasPlus = HasPlusButton(hItemFound);
		const bool bHasChildren = (GetChildItem(hItemFound) != NULL);

		if (bHasPlus && !bHasChildren)
			DoExpand(hItemFound);
		else
			Expand(hItemFound, TVE_EXPAND);

		if (sSearch.IsEmpty())
		{
			SetRedraw(TRUE);
			return hItemFound;
		}
	}

	if (sSearch.IsEmpty())
	{
		SetRedraw(TRUE);
		return NULL;
	}

	bool bDriveMatch = sRootFolder.IsEmpty();
	const bool bNetworkMatch = m_bShowNetwork && ((sSearch.GetLength() > 2) && sSearch.Find(_T("\\\\")) == 0);
	if (bNetworkMatch)
	{
		bDriveMatch = false;

		const bool bHasPlus = HasPlusButton(m_hNetworkRoot);
		const bool bHasChildren = (GetChildItem(m_hNetworkRoot) != NULL);

		if (bHasPlus && !bHasChildren)
			DoExpand(m_hNetworkRoot);
		else
			Expand(m_hNetworkRoot, TVE_EXPAND);
		hItemFound = FindServersNode(m_hNetworkRoot);
		sSearch = sSearch.Right(sSearch.GetLength() - 2);
	}
	if (bDriveMatch)
	{
		CString sMyDocumentsPath(m_sMyDocumentsPath);
		sMyDocumentsPath.MakeUpper();
		CString sMyDesktopPath(m_sDesktopPath);
		sMyDesktopPath.MakeUpper();
		CString sCurrentUserFolderPath(m_sCurrentUserFolderPath);
		sCurrentUserFolderPath.MakeUpper();

		if (m_hDesktop && sSearch.Find(sMyDesktopPath) == 0)
		{
			const bool bHasPlus = HasPlusButton(m_hDesktop);
			const bool bHasChildren = (GetChildItem(m_hDesktop) != NULL);

			if (bHasPlus && !bHasChildren)
				DoExpand(m_hDesktop);
			else
				Expand(m_hDesktop, TVE_EXPAND);
			hItemFound = m_hDesktop;

			//Skip over the part of the search path which contains the desktop path
			sSearch = sSearch.Right(sSearch.GetLength() - sMyDesktopPath.GetLength() - 1);

			//Because of the special way that the desktop item is shown, check to see if
			//we should collapse the desktop node
			if (sSearch.GetLength() == 0)
				Expand(m_hDesktop, TVE_COLLAPSE);

			bDriveMatch = false;
		}
		else if (m_hCurrentUserFolderRoot && sSearch.Find(sCurrentUserFolderPath) == 0)
		{
			const bool bHasPlus = HasPlusButton(m_hCurrentUserFolderRoot);
			const bool bHasChildren = (GetChildItem(m_hCurrentUserFolderRoot) != NULL);

			if (bHasPlus && !bHasChildren)
				DoExpand(m_hCurrentUserFolderRoot);
			else
				Expand(m_hCurrentUserFolderRoot, TVE_EXPAND);
			hItemFound = m_hCurrentUserFolderRoot;

			//Skip over the part of the search path which contains the Current Users path
			sSearch = sSearch.Right(sSearch.GetLength() - sCurrentUserFolderPath.GetLength() - 1);
			bDriveMatch = false;
		}
		else if (m_hMyDocumentsRoot && sSearch.Find(sMyDocumentsPath) == 0)
		{
			const bool bHasPlus = HasPlusButton(m_hMyDocumentsRoot);
			const bool bHasChildren = (GetChildItem(m_hMyDocumentsRoot) != NULL);

			if (bHasPlus && !bHasChildren)
				DoExpand(m_hMyDocumentsRoot);
			else
				Expand(m_hMyDocumentsRoot, TVE_EXPAND);
			hItemFound = m_hMyDocumentsRoot;

			//Skip over the part of the search path which contains the My documents path
			sSearch = sSearch.Right(sSearch.GetLength() - sMyDocumentsPath.GetLength() - 1);
			bDriveMatch = false;
		}
		else if (m_hMyComputerRoot)
		{
			const bool bHasPlus = HasPlusButton(m_hMyComputerRoot);
			const bool bHasChildren = (GetChildItem(m_hMyComputerRoot) != NULL);

			if (bHasPlus && !bHasChildren)
				DoExpand(m_hMyComputerRoot);
			else
				Expand(m_hMyComputerRoot, TVE_EXPAND);
			hItemFound = m_hMyComputerRoot;
		}
	}

	int nFound = sSearch.Find(_T('\\'));
	while (nFound != -1)
	{
		CString sMatch;
		if (bDriveMatch)
		{
			sMatch = sSearch.Left(nFound + 1);
			bDriveMatch = false;
		}
		else
			sMatch = sSearch.Left(nFound);

		hItemFound = FindSibling(hItemFound, sMatch);
		if (hItemFound == NULL)
			break;
		else if (!IsDrive(sPath))
		{
			ASSERT(hItemFound != TVI_ROOT);
			SelectItem(hItemFound);

			const bool bHasPlus = HasPlusButton(hItemFound);
			const bool bHasChildren = (GetChildItem(hItemFound) != NULL);

			if (bHasPlus && !bHasChildren)
				DoExpand(hItemFound);
			else
				Expand(hItemFound, TVE_EXPAND);
		}

		sSearch = sSearch.Right(sSearch.GetLength() - nFound - 1);
		nFound = sSearch.Find(_T('\\'));
	};

	//The last item
	if (hItemFound)
	{
		if (sSearch.GetLength())
		{
			HTREEITEM hTempItem = FindSibling(hItemFound, sSearch);
			if (hTempItem)
				hItemFound = hTempItem;
			else
			{
				//If we cannot find the final item, then deliberately do not expand the parent folder
				bExpanded = false;
			}
		}
		ASSERT(hItemFound != TVI_ROOT);
		SelectItem(hItemFound);
		if (bExpanded)
		{
			const bool bHasPlus = HasPlusButton(hItemFound);
			const bool bHasChildren = (GetChildItem(hItemFound) != NULL);

			if (bHasPlus && !bHasChildren)
				DoExpand(hItemFound);
			Expand(hItemFound, TVE_EXPAND);
		}
	}
	EnsureVisibleCenter(hItemFound);
	//Turn back on the redraw flag
	SetRedraw(TRUE);

	return hItemFound;
}

bool CFileExplorerCtrl::Rename(_In_ HTREEITEM hItem)
{
	if (hItem)
	{
#pragma warning(suppress: 26490)
		const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hItem));
#pragma warning(suppress: 26496)
		AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26489)
		if (m_bAllowRename && ((pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::FileNode) || (pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::FolderNode)))
		{
			m_bEditLabelFlag = TRUE;
			return (EditLabel(hItem) != NULL);
		}
		else
			return false;
	}
	else
		return false;
}

bool CFileExplorerCtrl::ShowProperties(_In_ HTREEITEM hItem)
{
	bool bSuccess = false;
	if (m_bAllowProperties && hItem)
	{
		//Show the "properties" for the selected file
		CString sFile(ItemToPath(hItem));
#pragma warning(suppress: 26476)
		SHELLEXECUTEINFO sei{};
		sei.cbSize = sizeof(sei);
		sei.hwnd = GetParent()->GetSafeHwnd();
		sei.nShow = SW_SHOW;
		sei.lpFile = sFile.GetBuffer(sFile.GetLength());
		sei.lpVerb = _T("properties");
		sei.fMask = SEE_MASK_INVOKEIDLIST;
#pragma warning(suppress: 26486)
		bSuccess = ShellExecuteEx(&sei);
		sFile.ReleaseBuffer();
	}
	return bSuccess;
}

CString CFileExplorerCtrl::CreateNewChildFolderName(_In_ const CString& sParentFolder)
{
	//What will be the return value from this function
	CString sNewFolder;

	//Remove trailing "\" from the parent folder path
	CString sLocalParentFolder(sParentFolder);
	const int nFind = sLocalParentFolder.GetLength();
	if ((nFind != -1) && sLocalParentFolder.GetAt(nFind - 1) == _T('\\'))
		sLocalParentFolder = sLocalParentFolder.Left(nFind - 1);

	bool bContinue = true;
	int nAttempt = 1;
	while (bContinue)
	{
		//Create the new potential folder name
		if (nAttempt == 1)
			sNewFolder.Format(_T("%s\\New Folder"), sLocalParentFolder.GetString());
		else
			sNewFolder.Format(_T("%s\\New Folder (%d)"), sLocalParentFolder.GetString(), nAttempt);

		//Check to see if it already exists
		const DWORD dwAttributes = GetFileAttributes(sNewFolder);
		if (dwAttributes == INVALID_FILE_ATTRIBUTES)
			bContinue = false;
		else
			++nAttempt;
	}

	return sNewFolder;
}

CString CFileExplorerCtrl::CreateNewChildFileName(const CString & sParentFolder)
{
	//What will be the return value from this function
	CString sNewFolder;

	//Remove trailing "\" from the parent folder path
	CString sLocalParentFolder(sParentFolder);
	const int nFind = sLocalParentFolder.GetLength();
	if ((nFind != -1) && sLocalParentFolder.GetAt(nFind - 1) == _T('\\'))
		sLocalParentFolder = sLocalParentFolder.Left(nFind - 1);

	bool bContinue = true;
	int nAttempt = 1;
	while (bContinue)
	{
		//Create the new potential folder name
		if (nAttempt == 1)
			sNewFolder.Format(_T("%s\\New Text Document.txt"), sLocalParentFolder.GetString());
		else
			sNewFolder.Format(_T("%s\\New Text Document (%d).txt"), sLocalParentFolder.GetString(), nAttempt);

		//Check to see if it already exists
		const DWORD dwAttributes = GetFileAttributes(sNewFolder);
		if (dwAttributes == INVALID_FILE_ATTRIBUTES)
			bContinue = false;
		else
			++nAttempt;
	}

	return sNewFolder;
}

HTREEITEM CFileExplorerCtrl::CreateFolder(_In_ HTREEITEM hItem, _In_ const CString& sNewFolderName)
{
	//What will be the return value from this function assume the worst
	HTREEITEM hNewFolder = NULL;

	if (hItem)
	{
#pragma warning(suppress: 26490)
		const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hItem));
#pragma warning(suppress: 26496)
		AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26489)
		if (m_bAllowCreateFileAndFolder 
			&& (pItem->m_NodeType != CFileExplorerCtrlItemInfo::NodeType::NetworkNode)
			&& (pItem->m_NodeType != CFileExplorerCtrlItemInfo::NodeType::MyComputerNode)
			&& (pItem->m_NodeType != CFileExplorerCtrlItemInfo::NodeType::UnknownNode))
		{
			//Get the path of the parent folder
			CString sParentFolder(ItemToPath(hItem));

			//Form the name of the new folder
			CString sNewFolder(sNewFolderName.IsEmpty() ? CreateNewChildFolderName(sParentFolder) : sNewFolderName);

			//Kill the monitoring thread if necessary
			const bool bMonitoringThread = (m_pMonitoringThread != NULL);
			CString sMonitoringPath(m_sMonitoringPath);
			if (bMonitoringThread)
				KillMonitoringThread();

			//Try to create the new folder
			if (CreateDirectory(sNewFolder, NULL))
			{
				//Notify the shell that a new folder has been created
				SHChangeNotify(SHCNE_MKDIR, SHCNF_PATH, sNewFolder, NULL);

				//Expand the parent folder
				Expand(hItem, TVE_EXPAND);

				//Break apart the new folder name ready for setting up the CFileExplorerCtrlItemInfo* item
				CString sFname;
				CString sExt;
				_tsplitpath_s(sNewFolder, NULL, 0, NULL, 0, sFname.GetBuffer(_MAX_FNAME), _MAX_FNAME, sExt.GetBuffer(_MAX_EXT), _MAX_EXT);
				sExt.ReleaseBuffer();
				sFname.ReleaseBuffer();
				CString sPath;
				_tmakepath_s(sPath.GetBuffer(_MAX_PATH), _MAX_PATH, NULL, NULL, sFname, sExt);
				sPath.ReleaseBuffer();

				//Determine if the parent item already has child items before we add the new item
				const bool bHasChildren = (GetChildItem(hItem) != NULL);

				//Insert the new item
#pragma warning(suppress: 26403 26409)
				auto pNewItem = new CFileExplorerCtrlItemInfo;
				pNewItem->m_sFQPath = sNewFolder;
				pNewItem->m_sRelativePath = sPath;
				pNewItem->m_NodeType = CFileExplorerCtrlItemInfo::NodeType::FolderNode;
#pragma warning(suppress: 26486)
				hNewFolder = InsertFileItem(hItem, pNewItem, 0, GetIconIndex(sNewFolder), GetSelIconIndex(sNewFolder), true);
				if (hNewFolder)
				{
					//Update the plus button for the parent if necessary
					if (!bHasChildren)
						SetHasPlusButton(hItem, true);

					//Select the new folder
					ASSERT(hNewFolder != TVI_ROOT);
					SelectItem(hNewFolder);

					//Attempt in place editing of the new folder
					Rename(hNewFolder);
				}
			}

			//Recreate the monitoring thread if necessary
			if (bMonitoringThread)
				CreateMonitoringThread(m_sMonitoringPath);
		}
	}

	return hNewFolder;
}

HTREEITEM CFileExplorerCtrl::CreateFileWin32(HTREEITEM hItem, const CString & sNewFileName)
{
	//What will be the return value from this function assume the worst
	HTREEITEM hNewFile = NULL;

	if (hItem)
	{
#pragma warning(suppress: 26490)
		const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hItem));
#pragma warning(suppress: 26496)
		AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26489)
		if (m_bAllowCreateFileAndFolder
			&& (pItem->m_NodeType != CFileExplorerCtrlItemInfo::NodeType::NetworkNode)
			&& (pItem->m_NodeType != CFileExplorerCtrlItemInfo::NodeType::MyComputerNode)
			&& (pItem->m_NodeType != CFileExplorerCtrlItemInfo::NodeType::UnknownNode))
		{
			//Get the path of the parent folder
			CString sParentFolder(ItemToPath(hItem));

			if (sParentFolder.CompareNoCase(_T("C:\\")) == 0) return hNewFile; // do not allow create new file at C:\\

			if (!PathUtils::IsDirectory(sParentFolder))
			{
				sParentFolder = PathUtils::GetContainerPath(sParentFolder);
			}

			//Form the name of the new file
			CString sNewFile(sNewFileName.IsEmpty() ? CreateNewChildFileName(sParentFolder) : sNewFileName);

			//Kill the monitoring thread if necessary
			const bool bMonitoringThread = (m_pMonitoringThread != NULL);
			CString sMonitoringPath(m_sMonitoringPath);
			if (bMonitoringThread)
				KillMonitoringThread();

			//Try to create the new file
			HANDLE hCreateFile =  CreateFile(sNewFile,    // name of the file
				GENERIC_READ, // open for writing
				0,             // sharing mode, none in this case
				0,             // use default security descriptor
				CREATE_ALWAYS, // overwrite if exists
				FILE_ATTRIBUTE_NORMAL,
				0);

			if (hCreateFile)
			{
				//Notify the shell that a new folder has been created
				SHChangeNotify(SHCNE_MKDIR, SHCNF_PATH, sNewFile, NULL);

				//Expand the parent folder
				Expand(hItem, TVE_EXPAND);

				//Break apart the new file name ready for setting up the CFileExplorerCtrlItemInfo* item
				CString sFname;
				CString sExt;
				_tsplitpath_s(sNewFile, NULL, 0, NULL, 0, sFname.GetBuffer(_MAX_FNAME), _MAX_FNAME, sExt.GetBuffer(_MAX_EXT), _MAX_EXT);
				sExt.ReleaseBuffer();
				sFname.ReleaseBuffer();
				CString sPath;
				_tmakepath_s(sPath.GetBuffer(_MAX_PATH), _MAX_PATH, NULL, NULL, sFname, sExt);
				sPath.ReleaseBuffer();

				//Determine if the parent item already has child items before we add the new item
				const bool bHasChildren = (GetChildItem(hItem) != NULL);

				//Insert the new item
#pragma warning(suppress: 26403 26409)
				auto pNewItem = new CFileExplorerCtrlItemInfo;
				pNewItem->m_sFQPath = sNewFile;
				pNewItem->m_sRelativePath = sPath;
				pNewItem->m_NodeType = CFileExplorerCtrlItemInfo::NodeType::FileNode;
#pragma warning(suppress: 26486)
				hNewFile = InsertFileItem(hItem, pNewItem, 0, GetIconIndex(sNewFile), GetSelIconIndex(sNewFile), true);
				if (hNewFile)
				{
					//Update the plus button for the parent if necessary
					if (!bHasChildren)
						SetHasPlusButton(hItem, true);

					//Attempt in place editing of the new folder
					Rename(hNewFile);
				}
				DELETE_WIN32_HANDLE(hCreateFile)
			}

			//Recreate the monitoring thread if necessary
			if (bMonitoringThread)
				CreateMonitoringThread(m_sMonitoringPath);
		}
	}

	if (hNewFile)
	{
		//Select the new file
		ASSERT(hNewFile != TVI_ROOT);
		SelectItem(hNewFile);
	}

	return hNewFile;
}

HTREEITEM CFileExplorerCtrl::MoveFileWin32(HTREEITEM hItem, BOOL bIsCopy)
{
	//What will be the return value from this function assume the worst
	HTREEITEM hNewFolder = NULL;

	if (hItem)
	{
#pragma warning(suppress: 26490)
		const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hItem));
#pragma warning(suppress: 26496)
		AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26489)
		if (m_bAllowCreateFileAndFolder && (pItem->m_NodeType != CFileExplorerCtrlItemInfo::NodeType::NetworkNode))
		{
			CString strDestFile;
			if (bIsCopy)
			{
				strDestFile = PathUtils::GetCopyFileFromSourceFile(ItemToPath(hItem), m_sSourceCopyPath, FALSE);
			}
			else
			{
				strDestFile = PathUtils::GetCopyFileFromSourceFile(ItemToPath(hItem), m_sSourceCopyPath, TRUE);
			}

			if (strDestFile.IsEmpty()) // skip this file 
			{
				return NULL;
			}

			if (!bIsCopy)
			{
				AppUtils::CloseDocumentByFilePath(m_sSourceCopyPath);
			}

			//Kill the monitoring thread if necessary
			const bool bMonitoringThread = (m_pMonitoringThread != NULL);
			CString sMonitoringPath(m_sMonitoringPath);
			if (bMonitoringThread)
				KillMonitoringThread();

			//Try to create the new file

			BOOL bMoveFile = bIsCopy ? CopyFile(m_sSourceCopyPath, strDestFile, FALSE) : MoveFileEx(m_sSourceCopyPath, strDestFile, MOVEFILE_REPLACE_EXISTING);

			if (bMoveFile)
			{
				//Notify the shell that a new folder has been created
				SHChangeNotify(SHCNE_MKDIR, SHCNF_PATH, strDestFile, NULL);

				//Expand the parent folder
				Expand(hItem, TVE_EXPAND);

				//Break apart the new file name ready for setting up the CFileExplorerCtrlItemInfo* item
				CString sFname;
				CString sExt;
				_tsplitpath_s(strDestFile, NULL, 0, NULL, 0, sFname.GetBuffer(_MAX_FNAME), _MAX_FNAME, sExt.GetBuffer(_MAX_EXT), _MAX_EXT);
				sExt.ReleaseBuffer();
				sFname.ReleaseBuffer();
				CString sPath;
				_tmakepath_s(sPath.GetBuffer(_MAX_PATH), _MAX_PATH, NULL, NULL, sFname, sExt);
				sPath.ReleaseBuffer();

				//Determine if the parent item already has child items before we add the new item
				const bool bHasChildren = (GetChildItem(hItem) != NULL);

				//Insert the new item
#pragma warning(suppress: 26403 26409)
				auto pNewItem = new CFileExplorerCtrlItemInfo;
				pNewItem->m_sFQPath = strDestFile;
				pNewItem->m_sRelativePath = sPath;
				pNewItem->m_NodeType = CFileExplorerCtrlItemInfo::NodeType::FolderNode;
#pragma warning(suppress: 26486)
				hNewFolder = InsertFileItem(hItem, pNewItem, 0, GetIconIndex(strDestFile), GetSelIconIndex(strDestFile), true);
				if (hNewFolder)
				{
					//Update the plus button for the parent if necessary
					if (!bHasChildren)
						SetHasPlusButton(hItem, true);

					//Select the new folder
					ASSERT(hNewFolder != TVI_ROOT);
					SelectItem(hNewFolder);

					//Attempt in place editing of the new folder
					Rename(hNewFolder);
				}
				if (bIsCopy)
				{
					LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Explorer Window] Copied file from \"%s\" to \"%s\"..."), m_sSourceCopyPath, strDestFile);
				}
				else
				{
					LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Explorer Window] Cut file from \"%s\" to \"%s\"..."), m_sSourceCopyPath, strDestFile);
				}
			}

			//Recreate the monitoring thread if necessary
			if (bMonitoringThread)
				CreateMonitoringThread(m_sMonitoringPath);
		}
	}

	return hNewFolder;
}

bool CFileExplorerCtrl::Delete(_In_ HTREEITEM hItem)
{
	bool bSuccess = false;

	if (hItem)
	{
#pragma warning(suppress: 26490)
		const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hItem));
#pragma warning(suppress: 26496)
		AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26489)
		if (m_bAllowDelete && ((pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::FileNode) || ((pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::FolderNode))))
		{
			SHFILEOPSTRUCT shfo{};
			shfo.hwnd = GetParent()->GetSafeHwnd();
			shfo.wFunc = FO_DELETE;

			//Undo is not allowed if the SHIFT key is held down
			if (!(GetKeyState(VK_SHIFT) & 0x8000))
				shfo.fFlags = FOF_ALLOWUNDO;

			//Create a Multi SZ string with the filename to delete
			CString sFileToDelete(ItemToPath(hItem));
#pragma warning(suppress: 26472)
			size_t nChars = static_cast<size_t>(sFileToDelete.GetLength()) + 1;
			nChars++;
			std::vector<TCHAR> sTempFrom;
			sTempFrom.resize(nChars);
			_tcscpy_s(sTempFrom.data(), nChars, sFileToDelete);
#pragma warning(suppress: 26446)
			sTempFrom[nChars - 1] = _T('\0');
			shfo.pFrom = sTempFrom.data();

			//Kill the monitoring thread if necessary
			const bool bMonitoringThread = (m_pMonitoringThread != NULL);
			CString sMonitoringPath(m_sMonitoringPath);
			if (bMonitoringThread)
				KillMonitoringThread();

			//Let the shell perform the actual deletion
#pragma warning(suppress: 26486)
			if (SHFileOperation(&shfo) == 0 && (shfo.fAnyOperationsAborted == FALSE))
			{
				//Gather the parent, next sibling and previous sibling before we do the delete
				HTREEITEM hParent = GetParentItem(hItem);
				HTREEITEM hPrevious = GetNextItem(hItem, TVGN_PREVIOUS);
				HTREEITEM hNext = GetNextItem(hItem, TVGN_NEXT);

				//Work out which item we should reselect after the delete
				if (hPrevious == NULL)
					hPrevious = hNext;
				if (hPrevious == NULL)
					hPrevious = hParent;

				//Delete the item from the view
				bSuccess = DeleteItem(hItem);

				//Update the selected item and plus button state of the parent if required
				if (bSuccess && hPrevious)
				{
					Select(hPrevious, TVGN_CARET);
					if (hPrevious == hParent)
						SetHasPlusButton(hParent, false);
				}
			}

			//Recreate the monitoring thread if necessary
			if (bMonitoringThread)
				CreateMonitoringThread(m_sMonitoringPath);
		}
	}
	return bSuccess;
}

void CFileExplorerCtrl::CloseCurrentMDITab(_In_ HTREEITEM hItem)
{
	CString strDocumentFile(ItemToPath(hItem));
	if (PathFileExists(strDocumentFile) && !PathUtils::IsDirectory(strDocumentFile))
	{
		auto pDoc = AppUtils::GetExistedDocument(strDocumentFile);
		if (pDoc)
		{
			POSITION p3 = pDoc->GetFirstViewPosition();
			while (p3)
			{
				CView* view = pDoc->GetNextView(p3);
				if (view && view->GetParentFrame())
				{
					view->GetParentFrame()->SendMessage(WM_CLOSE);
					SetFocus();
				}
			}
		}
	}
}

using namespace HostManager;
bool CFileExplorerCtrl::Open(_In_ HTREEITEM hItem, BOOL bOpenByDefaultApp /*= FALSE*/)
{
	bool bSuccess = false;
	if (m_bAllowOpen && hItem)
	{
		CString strFile(ItemToPath(hItem));
		if (strFile.IsEmpty()) return bSuccess;

		if (!bOpenByDefaultApp && !PathUtils::IsDirectory(strFile) && !PathUtils::IsBinaryFile(strFile))
		{
			bSuccess = true;
			AppUtils::CreateDocumentFromFile(strFile);
			SetFocus();
		}
		else // Execute the default command for the selected item
		{
#pragma warning(suppress: 26476)
			SHELLEXECUTEINFO sei{};
			sei.cbSize = sizeof(sei);
			sei.hwnd = GetParent()->GetSafeHwnd();
			sei.nShow = SW_SHOW;
			sei.lpFile = strFile.GetBuffer(strFile.GetLength());
			sei.fMask = SEE_MASK_INVOKEIDLIST;
#pragma warning(suppress: 26486)
			bSuccess = ShellExecuteEx(&sei);
			strFile.ReleaseBuffer();
		}
	}
	return bSuccess;
}

void CFileExplorerCtrl::SetDriveHideFlags(_In_ DWORD dwDriveHideFlags)
{
	m_dwDriveHideFlags = dwDriveHideFlags;

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::SetFileHideFlags(_In_ DWORD dwFileHideFlags)
{
	m_dwFileHideFlags = dwFileHideFlags;

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::SetFolderHideFlags(_In_ DWORD dwFolderHideFlags)
{
	m_dwFolderHideFlags = dwFolderHideFlags;

	//Force a refresh
	Refresh();
}

size_t CFileExplorerCtrl::AddMultipleFileNameMasks(_In_ const CString& sFileNameMasks)
{
	//Empty out the array
	m_FileNameMasks.clear();

	int nCurPos = 0;
	CString sToken(sFileNameMasks.Tokenize(_T(",;"), nCurPos));
	while (sToken != _T(""))
	{
		sToken.Trim();
		m_FileNameMasks.push_back(sToken);
		sToken = sFileNameMasks.Tokenize(_T(",;"), nCurPos);
	}

	//Force a refresh
	Refresh();

	//Return the number of recipients parsed
	return m_FileNameMasks.size();
}

CString CFileExplorerCtrl::GetFileNameMasks() const
{
	//What will be the return value from this function
	CString sMasks;

	const auto nSize = m_FileNameMasks.size();
	for (size_t i = 0; i < nSize; i++)
	{
#pragma warning(suppress: 26446)
		sMasks += m_FileNameMasks[i];
		if (i < (nSize - 1))
			sMasks += _T(",");
	}
	return sMasks;
}

void CFileExplorerCtrl::SetFileNameMask(_In_ size_t nIndex, _In_ const CString& sFileNameMask)
{
#pragma warning(suppress: 26446)
	m_FileNameMasks[nIndex] = sFileNameMask;

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::AddFileNameMask(_In_ const CString& sFileNameMask)
{
	m_FileNameMasks.push_back(sFileNameMask);

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::SetCompressedColor(_In_ COLORREF rgbCompressed)
{
	m_rgbCompressed = rgbCompressed;

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::SetEncryptedColor(_In_ COLORREF rgbEncrypted)
{
	m_rgbEncrypted = rgbEncrypted;

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::SetShowNetwork(_In_ bool bShowNetwork)
{
	m_bShowNetwork = bShowNetwork;

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::SetUsingDifferentColorForCompressed(_In_ bool bShowCompressedUsingDifferentColor)
{
	m_bShowCompressedUsingDifferentColor = bShowCompressedUsingDifferentColor;

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::SetUsingDifferentIconForSharedFolders(_In_ bool bShowSharedUsingDifferentIcon)
{
	m_bShowSharedUsingDifferentIcon = bShowSharedUsingDifferentIcon;

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::SetUsingDifferentColorForEncrypted(_In_ bool bShowEncryptedUsingDifferentColor)
{
	m_bShowEncryptedUsingDifferentColor = bShowEncryptedUsingDifferentColor;

	//Force a refresh
	Refresh();
};

void CFileExplorerCtrl::SetShowFileExtensions(_In_ HideFileExtension FileExtensions)
{
	m_FileExtensions = FileExtensions;

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::SetNetworkItemTypes(_In_ DWORD dwTypes)
{
	m_dwNetworkItemTypes = dwTypes;

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::SetShowDriveLabels(_In_ bool bShowDriveLabels)
{
	m_bShowDriveLabels = bShowDriveLabels;

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::SetShowMyComputer(_In_ bool bShowMyComputer)
{
	m_bShowMyComputer = bShowMyComputer;

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::SetShowDesktop(_In_ bool bShowDesktop)
{
	m_bShowDesktop = bShowDesktop;

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::SetShowMyDocuments(_In_ bool bShowMyDocuments)
{
	m_bShowMyDocuments = bShowMyDocuments;

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::SetShowCurrentUserFolder(_In_ bool bShowCurrentUserFolder)
{
	m_bShowCurrentUserFolder = bShowCurrentUserFolder;

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::SetShowRootedFolder(_In_ bool bShowRootedFolder)
{
	m_bShowRootedFolder = bShowRootedFolder;

	//Force a refresh
	Refresh();
}

bool CFileExplorerCtrl::CanDisplayFile(_In_ const CFileFind& find)
{
	//Derived classes can decide dynamically whether or not a certain file is to be displayed. CFileExplorerCtrl by default
	//displays all files which do not have attributes as set in m_dwFileHideFlags

	return (m_bShowFiles && !find.IsDirectory() && !find.MatchesMask(m_dwFileHideFlags));
}

bool CFileExplorerCtrl::CanDisplayFolder(_In_ const CFileFind& find)
{
	//Derived classes can decide dynamically whether or not a certain folder is to be displayed. CFileExplorerCtrl by default
	//displays all folders excluding the ".." and "." entries and which do not have attributes as set in m_dwFolderHideFlags

	return (find.IsDirectory() && !find.IsDots() && !find.MatchesMask(m_dwFolderHideFlags));
}

#pragma warning(suppress: 26440)
bool CFileExplorerCtrl::CanDisplayNetworkItem(_In_ CFileExplorerCtrlItemInfo* /*pItem*/)
{
	//Derived classes can decide dynamically whether or not a certain network item is to be displayed. 
	//CFileExplorerCtrl by default displays all items

	return true;
}

bool CFileExplorerCtrl::CanHandleChangeNotifications(_In_ const CString& sPath)
{
	//If no path was given, then fail this function
	if (sPath.IsEmpty())
		return false;

	//We are not interested in files
	if (IsFile(sPath))
		return false;

	//The path must be a folder of some kind
	if (!IsFolder(sPath))
		return false;

	//check if this drive is one of the types which can issue notification changes
	CString sDrive(sPath);
	if (!IsDrive(sDrive))
		sDrive = sPath.Left(3);

	const UINT nDrive = GetDriveType(sDrive);
	return ((nDrive != DRIVE_REMOVABLE) && nDrive != DRIVE_CDROM);
}

#pragma warning(suppress: 26440)
bool CFileExplorerCtrl::CanDisplayDrive(_In_ const CString& sDrive)
{
	//Derived classes can decide dynamically whether or not a 
	//certain drive is to be displayed. CFileExplorerCtrl by default
	//displays all drives which do not have attributes as set in
	//m_dwDriveHideFlags

	//check if this drive is one of the types to hide
	bool bDisplay = true;
	const UINT nDrive = GetDriveType(sDrive);
	switch (nDrive)
	{
	case DRIVE_REMOVABLE:
	{
		if (m_dwDriveHideFlags & static_cast<DWORD>(DriveType::DRIVE_ATTRIBUTE_REMOVABLE))
			bDisplay = false;
		break;
	}
	case DRIVE_FIXED:
	{
		if (m_dwDriveHideFlags & static_cast<DWORD>(DriveType::DRIVE_ATTRIBUTE_FIXED))
			bDisplay = false;
		break;
	}
	case DRIVE_REMOTE:
	{
		if (m_dwDriveHideFlags & static_cast<DWORD>(DriveType::DRIVE_ATTRIBUTE_REMOTE))
			bDisplay = false;
		break;
	}
	case DRIVE_CDROM:
	{
		if (m_dwDriveHideFlags & static_cast<DWORD>(DriveType::DRIVE_ATTRIBUTE_CDROM))
			bDisplay = false;
		break;
	}
	case DRIVE_RAMDISK:
	{
		if (m_dwDriveHideFlags & static_cast<DWORD>(DriveType::DRIVE_ATTRIBUTE_RAMDISK))
			bDisplay = false;
		break;
	}
	default:
	{
		break;
	}
	}

	return bDisplay;
}

void CFileExplorerCtrl::OnRename()
{
	Rename(GetSelectedItem());
}

#pragma warning(suppress: 26429)
void CFileExplorerCtrl::OnUpdateRename(CCmdUI* pCmdUI)
{
	HTREEITEM hSelItem = GetSelectedItem();
	if (hSelItem)
	{
#pragma warning(suppress: 26490)
		const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hSelItem));
#pragma warning(suppress: 26496)
		AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26486 26489)
		pCmdUI->Enable(m_bAllowRename && ((pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::FileNode) || (pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::FolderNode)));
	}
	else
#pragma warning(suppress: 26486)
		pCmdUI->Enable(FALSE);
}

void CFileExplorerCtrl::OnVirusScanner()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		if (PathFileExists(sPath))
		{
			CString strFullCmd = _T("start \"\" \"CMD \" /c \"\"") + AppSettingMgr.m_strAntiVirusProgram + _T("\" ")
				+ AppSettingMgr.m_strAntiVirusArgument + _T(" \"") + sPath + _T("\"\" ^& pause");
			OSUtils::RunSystemCMD(strFullCmd);
		}
	}
}

void CFileExplorerCtrl::OnProperties()
{
	ShowProperties(GetSelectedItem());
}

#pragma warning(suppress: 26429)
void CFileExplorerCtrl::OnUpdateProperties(CCmdUI* pCmdUI)
{
	HTREEITEM hSelItem = GetSelectedItem();
	if (hSelItem)
	{
		if (m_bAllowProperties)
		{
#pragma warning(suppress: 26490)
			const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hSelItem));
#pragma warning(suppress: 26496)
			AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26489)
			if (pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::NetworkNode)
			{
#pragma warning(suppress: 26486 26489)
				pCmdUI->Enable((pItem->m_dwNetResourceDisplayType == RESOURCEDISPLAYTYPE_SERVER) || (pItem->m_dwNetResourceDisplayType == RESOURCEDISPLAYTYPE_SHARE));
			}
			else
#pragma warning(suppress: 26486)
				pCmdUI->Enable(TRUE);
		}
		else
#pragma warning(suppress: 26486)
			pCmdUI->Enable(FALSE);
	}
	else
#pragma warning(suppress: 26486)
		pCmdUI->Enable(FALSE);
}

void CFileExplorerCtrl::OnOpen()
{
	Open(GetSelectedItem());
}

#pragma warning(suppress: 26429)
void CFileExplorerCtrl::OnUpdateOpen(CCmdUI* pCmdUI)
{
	HTREEITEM hSelItem = GetSelectedItem();
	if (hSelItem)
	{
		if (m_bAllowOpen)
		{
#pragma warning(suppress: 26490)
			const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hSelItem));
#pragma warning(suppress: 26496)
			AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26489)
			if (pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::NetworkNode)
			{
#pragma warning(suppress: 26486 26489)
				pCmdUI->Enable((pItem->m_dwNetResourceDisplayType == RESOURCEDISPLAYTYPE_SERVER) || (pItem->m_dwNetResourceDisplayType == RESOURCEDISPLAYTYPE_SHARE));
			}
			else
#pragma warning(suppress: 26486)
				pCmdUI->Enable(TRUE);
		}
		else
#pragma warning(suppress: 26486)
			pCmdUI->Enable(FALSE);
	}
	else
#pragma warning(suppress: 26486)
		pCmdUI->Enable(FALSE);
}

void CFileExplorerCtrl::OnClose()
{
	CloseCurrentMDITab(GetSelectedItem());
}

void CFileExplorerCtrl::OnDelete()
{
	if (IDYES == AfxMessageBox(_T("Are you sure want to delete it?"), MB_YESNO | MB_ICONWARNING))
	{
		HTREEITEM hSelItem = GetSelectedItem();
		if (hSelItem)
		{
			CString strFileToDelete = ItemToPath(hSelItem);
			if (PathFileExists(strFileToDelete))
			{
				AppUtils::CloseDocumentByFilePath(strFileToDelete); // close document before delete file in system...
				Sleep(500);
				if (Delete(hSelItem))
				{
					LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Explorer Window] Deleted path \"%s\", you can restore it from recycle bin..."), strFileToDelete);
				}
				else
				{
					AfxMessageBoxFormat(MB_ICONWARNING, _T("[Error] Path \"%s\" does not allow to delete!"), strFileToDelete);
				}
			}
		}
	}
}

#pragma warning(suppress: 26429)
void CFileExplorerCtrl::OnUpdateDelete(CCmdUI* pCmdUI)
{
	HTREEITEM hSelItem = GetSelectedItem();
	if (hSelItem)
	{
#pragma warning(suppress: 26490)
		const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hSelItem));
#pragma warning(suppress: 26496)
		AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26486 26489)
		pCmdUI->Enable(m_bAllowDelete && ((pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::FileNode) || ((pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::FolderNode))));
	}
	else
#pragma warning(suppress: 26486)
		pCmdUI->Enable(FALSE);
}

void CFileExplorerCtrl::OnCreateFolder()
{
	HTREEITEM hNewFolder = NULL;
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		if (IsFile(hItem))
		{
			HTREEITEM hParent = GetParentItem(hItem);
			if (hParent)
			{
				hNewFolder = CreateFolder(hParent);
			}
		}
		else
		{
			hNewFolder = CreateFolder(hItem);
		}
	}
	if (hNewFolder == NULL)
	{
		AfxMessageBox(_T("[Error] Can not create new folder at this path!"));
	}

}

void CFileExplorerCtrl::OnCreateNewMutiple()
{
	CCreateNewMultiplePathDlg dlg;
	dlg.DoModal();
}

void CFileExplorerCtrl::OnOpenInChrome()
{
	HTREEITEM hSelItem = GetSelectedItem();
	if (hSelItem)
	{
		CString strFilePath(ItemToPath(hSelItem));
		OSUtils::OpenFileInWebBrowser(_T("chrome.exe"), strFilePath);
	}
}

void CFileExplorerCtrl::OnOpenInEdge()
{
	HTREEITEM hSelItem = GetSelectedItem();
	if (hSelItem)
	{
		CString strFilePath(ItemToPath(hSelItem));
		OSUtils::OpenFileInWebBrowser(_T("shell:Appsfolder\\Microsoft.MicrosoftEdge_8wekyb3d8bbwe!MicrosoftEdge"), strFilePath);
	}
}

void CFileExplorerCtrl::OnOpenInFireFox()
{
	HTREEITEM hSelItem = GetSelectedItem();
	if (hSelItem)
	{
		CString strFilePath(ItemToPath(hSelItem));
		OSUtils::OpenFileInWebBrowser(_T("firefox.exe"), strFilePath);
	}
}

#ifndef FILETREECTRL_NO_RESOURCES
#pragma warning(suppress: 26434)
void CFileExplorerCtrl::OnContextMenu(CWnd*, CPoint point)
{
	HTREEITEM hSelItem = GetSelectedItem();
	if (hSelItem)
	{
		CString strFile(ItemToPath(hSelItem));

		CMenu menu;
		if (menu.LoadMenu(IDR_TREEFILECTRL_POPUP))
		{
			CMenu* pPopup = menu.GetSubMenu(0);
#pragma warning(suppress: 26496)
			AFXASSUME(pPopup != NULL);
			if (!pPopup) return;
			VinaTextLocalization.TranslateContextMenu(pPopup);

			if (m_sRootFolder.IsEmpty())
			{
				pPopup->DeleteMenu(ID_TREEFILECTRL_BACK_TO_ORIGINAL, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_ADD_NEW_FOLDER, MF_BYCOMMAND);
			}

			if (!m_bAllowCreateFileAndFolder)
			{
				pPopup->DeleteMenu(ID_TREEFILECTRL_CREATEFILE, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_CREATEFOLDER, MF_BYCOMMAND);
			}

			//Allow creation of a folder if the selected item is itself a directory/folder
			const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hSelItem));
			ASSERT(pItem != NULL);

			if (pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::MyComputerNode
				|| pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::UnknownNode
				|| pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::NetworkNode)
			{
				return;
			}

			if (pItem->m_sFQPath.CompareNoCase(_T("C:\\")) == 0)
			{
				pPopup->DeleteMenu(ID_TREEFILECTRL_CREATEFILE, MF_BYCOMMAND); // do not allow create new file at C
			}

			if (!PathUtils::IsImageFile(strFile))
			{
				pPopup->DeleteMenu(ID_TREEFILECTRL_EDIT_WIH_MSPAINT, MF_BYCOMMAND);
			}

			const DWORD dwAttributes = GetFileAttributes(pItem->m_sFQPath);
			if (dwAttributes != INVALID_FILE_ATTRIBUTES)
			{
				if ((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)  // NOT FOR FILE ...
				{ 
					pPopup->DeleteMenu(ID_TREEFILECTRL_SETROOTFOLDER, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_ADD_NEW_FOLDER, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_BACK_TO_ORIGINAL, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_FILENAME_FILTER, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_LIST_ALL_FILE, MF_BYCOMMAND); 
					pPopup->DeleteMenu(ID_TREEFILECTRL_LIST_ALL_FOLDER, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_SEARCH_ON_FOLDER, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_REPLACE_ON_FOLDER, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_FILE_SAVE_AS, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_OPEN_ALL_BY_VINATEXT, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_EXPAND_ALL, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_COLLAPSE_ALL, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_SEARCH_FILES, MF_BYCOMMAND);
					if (PathUtils::IsImageFile(strFile))
						pPopup->RemoveMenu(9, MF_BYPOSITION);
					else pPopup->RemoveMenu(8, MF_BYPOSITION);

				}
				else // NOT FOR FOLDER...
				{
					pPopup->DeleteMenu(ID_TREEFILECTRL_CLOSE, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_OPEN_BY_VINATEXT, MF_BYCOMMAND);	
					pPopup->DeleteMenu(ID_TREEFILECTRL_OPEN_BY_AS_RAW_FORMAT, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_OPEN_CONTAINER, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_COLLAPSE_PARENT, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_FILE_CHROME, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_FILE_EDGE, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_FILE_FIREFOX, MF_BYCOMMAND);
				}
			}
			else // NOT FOR FILE...
			{
				pPopup->DeleteMenu(ID_TREEFILECTRL_CREATEFILE, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_CREATEFOLDER, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_SETROOTFOLDER, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_SETSELECTEDPATH, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_ADD_NEW_FOLDER, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_BACK_TO_ORIGINAL, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_FILENAME_FILTER, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_LIST_ALL_FILE, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_LIST_ALL_FOLDER, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_SEARCH_ON_FOLDER, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_REPLACE_ON_FOLDER, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_FILE_SAVE_AS, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_OPEN_ALL_BY_VINATEXT, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_EXPAND_ALL, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_COLLAPSE_ALL, MF_BYCOMMAND);
				pPopup->DeleteMenu(ID_TREEFILECTRL_SEARCH_FILES, MF_BYCOMMAND);
			}

			auto pDoc = AppUtils::GetMDIActiveDocument();
			if (pDoc)
			{
				if (pDoc->IsKindOf(RUNTIME_CLASS(CImageDoc)))
				{
					pPopup->DeleteMenu(ID_TREEFILECTRL_LOAD_AUTOCOMPLETE, MF_BYCOMMAND);
				}
				if (pDoc->IsKindOf(RUNTIME_CLASS(CPdfDoc)) || pDoc->IsKindOf(RUNTIME_CLASS(CMediaDoc)))
				{
					pPopup->DeleteMenu(ID_TREEFILECTRL_FILE_SAVE_AS, MF_BYCOMMAND);
					pPopup->DeleteMenu(ID_TREEFILECTRL_LOAD_AUTOCOMPLETE, MF_BYCOMMAND);
				}
			}

			if (!AppUtils::GetExistedDocument(strFile))
			{
				pPopup->DeleteMenu(ID_TREEFILECTRL_CLOSE, MF_BYCOMMAND);
			}

			pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		}
	}
}
#endif //#ifndef FILETREECTRL_NO_RESOURCES

void CFileExplorerCtrl::UpOneLevel()
{
	OnUpOneLevel();
}

#pragma warning(suppress: 26429)
void CFileExplorerCtrl::OnUpdateUpOneLevel(CCmdUI* pCmdUI)
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
#pragma warning(suppress: 26486)
		pCmdUI->Enable(GetParentItem(hItem) != NULL);
	else
#pragma warning(suppress: 26486)
		pCmdUI->Enable(FALSE);
}

#pragma warning(suppress: 26429)
BOOL CFileExplorerCtrl::OnDblclk(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
	HTREEITEM hItem = GetSelectedItem();
	CPoint pt(GetCurrentMessage()->pt);
	ScreenToClient(&pt);
	if (hItem && (hItem == HitTest(pt)))
	{
		if (!HasPlusButton(hItem))
		{
			Open(hItem, FALSE);
		}
	}
	*pResult = 0;
	return FALSE; //Allow the message to be reflected again
}

BOOL CFileExplorerCtrl::OpenSelectedPath()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		if (!HasPlusButton(hItem))
		{
			Open(hItem, FALSE);
		}
	}
	return TRUE;
}

void CFileExplorerCtrl::DoNavigateSearchFiles(CString strFolderPath)
{
	if (PathFileExists(strFolderPath))
	{
		if (!PathUtils::IsDirectory(strFolderPath))
		{
			strFolderPath = PathUtils::GetContainerPath(strFolderPath);
		}
		if (!m_pSearchFileDlg)
		{
			m_pSearchFileDlg = new CSearchNavigatePathDlg(strFolderPath);
		}
		else
		{
			m_pSearchFileDlg->SetSearchFolder(strFolderPath);
		}
		if (!m_pSearchFileDlg->GetSafeHwnd())
		{
			m_pSearchFileDlg->Create(CSearchNavigatePathDlg::IDD, this);
			m_pSearchFileDlg->ShowWindow(SW_SHOW);
			m_pSearchFileDlg->CenterWindow();
		}
		m_pSearchFileDlg->SetForcusOnEditFileName();
	}
	else
	{
		CString strMessage = _T("> [Explorer Window] [Search Path Error] selected path does not exist or is a special path.");
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strMessage, BasicColors::orange);
	}
}

bool CFileExplorerCtrl::GoBack()
{
	bool bSuccess = false;
	if (m_PrevItems.size())
	{
		OnBack();
		bSuccess = true;
	}
	return bSuccess;
}

bool CFileExplorerCtrl::GoForward()
{
	bool bSuccess = false;
	if (m_NextItems.size())
	{
		OnForward();
		bSuccess = true;
	}
	return bSuccess;
}

void CFileExplorerCtrl::Refresh()
{
	if (GetSafeHwnd())
		OnRefresh();
}

void CFileExplorerCtrl::OnRefresh()
{
	//Just in case this will take some time
	CWaitCursor wait;

	SetRedraw(FALSE);

	//Get the item which is currently selected
	HTREEITEM hSelItem = GetSelectedItem();
	CString sItem;
	bool bExpanded = false;
	if (hSelItem)
	{
		sItem = ItemToPath(hSelItem);
		bExpanded = IsExpanded(hSelItem);
	}
	//Get tree status expanded, collapsed
	std::vector<CString> vecItemExpand;
	CItemIterator itr(this, GetRootItem());
	while (itr.HasNext())
	{
		HTREEITEM hItemExpanded = itr.GetNext();
		if (hItemExpanded && hItemExpanded != hSelItem && IsExpanded(hItemExpanded))
		{
			vecItemExpand.push_back(ItemToPath(hItemExpanded));
		}
	}

	m_SharedEnumerator.Refresh();

	KillMonitoringThread();

	//Remove all nodes that currently exist
	Clear();

	//Display the folder items in the tree
	if (m_sRootFolder.IsEmpty())
	{
		//Should we insert a desktop node
		CString sDesktopPath;
		if (m_bShowDesktop && (m_Malloc != NULL))
		{
#pragma warning(suppress: 26403 26409)
			auto pItem = new CFileExplorerCtrlItemInfo;
			pItem->m_NodeType = CFileExplorerCtrlItemInfo::NodeType::DesktopNode;
			int nIcon = 0;
			int nSelIcon = 0;

			//Get the localized name, path and correct icons for the Desktop
			LPITEMIDLIST lpDPidl = NULL;
			if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &lpDPidl)))
			{
				SHFILEINFO sfi{};
#pragma warning(suppress: 26490)
				if (SHGetFileInfo(reinterpret_cast<LPCTSTR>(lpDPidl), 0, &sfi, sizeof(sfi), SHGFI_PIDL | SHGFI_DISPLAYNAME))
#pragma warning(suppress: 26485)
					pItem->m_sRelativePath = sfi.szDisplayName;

				//While we are at it, also get the real path of the Desktop
				const HRESULT hr = SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, SHGFP_TYPE_CURRENT, sDesktopPath.GetBuffer(_MAX_PATH));
				sDesktopPath.ReleaseBuffer();
				if (SUCCEEDED(hr))
				{
					pItem->m_sFQPath = sDesktopPath;
					m_sDesktopPath = pItem->m_sFQPath; //Also maintain a copy ourselves, We use this when we are trying to select items in the control
				}

				nIcon = GetIconIndex(lpDPidl);
				nSelIcon = GetSelIconIndex(lpDPidl);

				//Free up the pidl now that we are finished with it
				m_Malloc->Free(lpDPidl);
			}

			//Add it to the tree control
#pragma warning(suppress: 26486)
			m_hRoot = InsertFileItem(TVI_ROOT, pItem, 0, nIcon, nSelIcon, false);
			m_hDesktop = m_hRoot;
		}
		else
			m_hRoot = TVI_ROOT;

		DisplayRootItems();
		Expand(m_hRoot, TVE_EXPAND);

		//Also show all items underneath the desktop
#pragma warning(suppress: 6102)
		if (sDesktopPath.GetLength())
			DisplayPath(sDesktopPath, m_hRoot, false, false);
	}
	else
	{
		if (IsUNCServerName(m_sRootFolder))
		{
			//Should we display the root machine
			if (m_bShowRootedFolder)
				m_hRootedFolder = DisplayNetworkComputer(m_hRoot, m_sRootFolder);
			else
				DisplayShares(m_hRoot, m_sRootFolder);
		}
		else
			DisplayPath(m_sRootFolder, m_hRoot, false);
	}
	//Reselect the initially expanded item
	for (auto const &hItem : vecItemExpand)
	{
		Expand(PathToItem(hItem), TVE_EXPAND);
	}
	//Reselect the initially selected item
	if (hSelItem) SetSelectedPath(sItem, bExpanded);

	//Turn back on the redraw flag
	SetRedraw(TRUE);
}

void CFileExplorerCtrl::OnJumpToPath()
{
	CSelectedPathDlg dlg;
	dlg.DoModal();
	SetFocus();
}

void CFileExplorerCtrl::OnSetAsWorkspaceFolder()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		if (PathFileExists(sPath))
		{
			if (!PathUtils::IsDirectory(sPath))
			{
				sPath = PathUtils::GetContainerPath(sPath);
				SetRootFolder(sPath);
			}
			else
			{
				SetRootFolder(sPath);
			}
			if (m_pSearchFileDlg)
			{
				m_pSearchFileDlg->SetSearchFolder(sPath);
			}
		}
	}
}

void CFileExplorerCtrl::OnAddMoreFolderToWorkSpace()
{
	CFolderPickerDialog dlg;
	dlg.m_ofn.lpstrTitle = _T("Open New Workspace Folder");
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	AddMoreFolderToWorkSpace(dlg.GetPathName());
}

void CFileExplorerCtrl::AddMoreFolderToWorkSpace(const CString& strFolder)
{
	if (strFolder.IsEmpty()) return;
	if (m_sRootFolder.IsEmpty())
	{
		SetRootFolder(strFolder);
	}
	else if (m_sRootFolder != strFolder)
	{
		AddPath(strFolder, false);
	}
}

void CFileExplorerCtrl::OnBookMarkPath()
{
	CString strAppDataFolderPath = PathUtils::GetVinaTextAppDataPath();
	if (!PathFileExists(strAppDataFolderPath))
	{
		CreateDirectory(strAppDataFolderPath, NULL);
	}
	CString strPathToBookmark = GetSelectedPath();
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
		OnOpenBookMarkTable();
	}
}

void CFileExplorerCtrl::OnOpenBookMarkTable()
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame); if (!pFrame) return;
	pFrame->OnToolsOpenBookMarkPathTable();
}

void CFileExplorerCtrl::OnRemoveFolderFromWorkSpace()
{
	bool bSuccess = false;
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		//Gather the parent, next sibling and previous sibling before we do the delete
		HTREEITEM hParent = GetParentItem(hItem);
		HTREEITEM hPrevious = GetNextItem(hItem, TVGN_PREVIOUS);
		HTREEITEM hNext = GetNextItem(hItem, TVGN_NEXT);

		//Work out which item we should reselect after the delete
		if (hPrevious == NULL)
			hPrevious = hNext;
		if (hPrevious == NULL)
			hPrevious = hParent;

		//Delete the item from the view
		CString strDeletePath = ItemToPath(hItem);
		bSuccess = DeleteItem(hItem);

		for (std::vector<CString>::iterator iter = m_NewAddedFolderData.begin(); iter != m_NewAddedFolderData.end(); ++iter)
		{
			if (*iter == strDeletePath)
			{
				m_NewAddedFolderData.erase(iter);
				break;
			}
		}

		//Update the selected item and plus button state of the parent if required
		if (bSuccess && hPrevious)
		{
			Select(hPrevious, TVGN_CARET);
			if (hPrevious == hParent)
			{
				SetHasPlusButton(hParent, false);
			}
		}
		else
		{
			OnBackToOriginalExplorer();
		}
	}
}

void CFileExplorerCtrl::OnBackToOriginalExplorer()
{
	m_sRootFolder.Empty();
	m_NewAddedFolderData.clear();
	PopulateTree();
}

void CFileExplorerCtrl::OnSetFileExtensionFilter()
{
	CFileExtensionFilterDlg dlg;
	CString strFileMarks = GetFileNameMasks().Trim();
	if (strFileMarks == _T("*.*"))
	{
		strFileMarks = _T("*.*;");
	}
	dlg.m_sMask = strFileMarks;
	if (dlg.DoModal() == IDOK)
	{
		AddMultipleFileNameMasks(dlg.m_sMask);
	}
	SetFocus();
}

void CFileExplorerCtrl::OnShowSystemMenu()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		ShowExplorerShellContextMenu(sPath);
	}
}

void CFileExplorerCtrl::OnOpenRecycleBin()
{
	OSUtils::CreateWin32Process(_T("cmd /c start shell:RecycleBinFolder"));
}

void CFileExplorerCtrl::OnCreateFile()
{
	HTREEITEM hNewFile = NULL;
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		if (IsFile(hItem))
		{
			HTREEITEM hParent = GetParentItem(hItem);
			if (hParent)
			{
				hNewFile = CreateFileWin32(hParent);
			}
		}
		else
		{
			hNewFile = CreateFileWin32(hItem);
		}
	}
	if (hNewFile == NULL)
	{
		AfxMessageBox(_T("[Error] Can not create new file at this path!"));
	}
}

void CFileExplorerCtrl::OnSetFocusActiveMDITab()
{
	if (m_pSearchFileDlg)
	{
		m_pSearchFileDlg->SetForcusOnEditFileName();
	}
	else
	{
		auto pDoc = AppUtils::GetMDIActiveDocument();
		if (pDoc)
		{
			if (pDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
			{
				CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(pDoc);
				if (pEditorDoc && pEditorDoc->GetEditorCtrl())
				{
					pEditorDoc->GetEditorCtrl()->SetFocus();
				}
			}
			else
			{
				CView* pView = AppUtils::GetMDIActiveView();
				if (pView) pView->SetFocus();
			}
		}
	}
}

void CFileExplorerCtrl::OnGetFullPath()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		OpenClipBoard(sPath);
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Explorer Window] Copied full file path \"%s\"..."), sPath);
	}
}

void CFileExplorerCtrl::OnGetFullPathDoubleQuote()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(_T("\"") + ItemToPath(hItem) + _T("\""));
		OpenClipBoard(sPath);
	}
}

void CFileExplorerCtrl::OnGetFullPathDoubleSlash()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString strPath = ItemToPath(hItem);
		strPath.Replace(_T("\\"), _T("\\\\"));
		OpenClipBoard(strPath);
	}
}

void CFileExplorerCtrl::OnGetFullPathForwardSlash()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString strPath = ItemToPath(hItem);
		strPath.Replace(_T("\\"), _T("/"));
		OpenClipBoard(strPath);
	}
}

void CFileExplorerCtrl::OpenClipBoard(const CString& str)
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

CString CFileExplorerCtrl::GetClipboardPlainText()
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

void CFileExplorerCtrl::OnGetContainerPath()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		CString strContainerPath = PathUtils::GetContainerPath(sPath);
		OpenClipBoard(strContainerPath);
	}
}

void CFileExplorerCtrl::OnGetName()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString strName = GetItemText(hItem);
		OpenClipBoard(strName);
	}
}

void CFileExplorerCtrl::OnTerminalRunActiveFile()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem && IsFile(hItem))
	{
		CString sPath(ItemToPath(hItem));
		if (PathFileExists(sPath))
		{
			CString strFullCmd = _T("start \"\" \"CMD \" /c \"") + sPath + _T("\" ^& pause");
			OSUtils::RunSystemCMD(strFullCmd);
		}
	}
}

void CFileExplorerCtrl::OnUpdateTerminalRunActiveFile(CCmdUI * pCmdUI)
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem && IsFile(hItem))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CFileExplorerCtrl::OnTerminalOpenNewCMDTab()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		if (!PathUtils::IsDirectory(sPath))
		{
			CString strContainerPath = PathUtils::GetContainerPath(sPath);
			if (!PathFileExists(strContainerPath)) return;
			SetCurrentDirectoryW(strContainerPath);
		}
		else
		{
			SetCurrentDirectoryW(sPath);
		}
		HostApplicaton(HOST_APP_TYPE::TERMINAL_CMD, L"cmd.exe");
		if (!PathUtils::IsDirectory(sPath))
		{
			Sleep(500);
			// clipboard process...
			CString strClipBoardText = GetClipboardPlainText();
			OpenClipBoard(PathUtils::GetLastLevelPath(sPath));
			OSUtils::PatseClipboardToCMD(AppUtils::GetVinaTextApp()->m_hLatestHostWND);
			OpenClipBoard(strClipBoardText);
		}
	}
}

void CFileExplorerCtrl::OnTerminalOpenNewPowerShellTab()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		if (!PathUtils::IsDirectory(sPath))
		{
			CString strContainerPath = PathUtils::GetContainerPath(sPath);
			if (!PathFileExists(strContainerPath)) return;
			SetCurrentDirectoryW(strContainerPath);
		}
		else
		{
			SetCurrentDirectoryW(sPath);
		}
		HostApplicaton(HOST_APP_TYPE::TERMINAL_POWERSHELL, L"powershell.exe");
		if (!PathUtils::IsDirectory(sPath))
		{
			Sleep(500);
			// clipboard process...
			CString strClipBoardText = GetClipboardPlainText();
			OpenClipBoard(PathUtils::GetLastLevelPath(sPath));
			OSUtils::PatseClipboardToCMD(AppUtils::GetVinaTextApp()->m_hLatestHostWND);
			OpenClipBoard(strClipBoardText);
		}
	}
}

void CFileExplorerCtrl::OnTerminalOpenNewWSLTab()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		if (!PathUtils::IsDirectory(sPath))
		{
			CString strContainerPath = PathUtils::GetContainerPath(sPath);
			if (!PathFileExists(strContainerPath)) return;
			SetCurrentDirectoryW(strContainerPath);
		}
		else
		{
			SetCurrentDirectoryW(sPath);
		}
		HostApplicaton(HOST_APP_TYPE::TERMINAL_WSL, L"wsl.exe");
		if (!PathUtils::IsDirectory(sPath))
		{
			Sleep(500);
			// clipboard process...
			CString strClipBoardText = GetClipboardPlainText();
			OpenClipBoard(PathUtils::GetLastLevelPath(sPath));
			OSUtils::PatseClipboardToCMD(AppUtils::GetVinaTextApp()->m_hLatestHostWND);
			OpenClipBoard(strClipBoardText);
		}
	}
}

void CFileExplorerCtrl::OnOpenCMDHere()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		if (!PathUtils::IsDirectory(sPath))
		{
			CString strContainerPath = PathUtils::GetContainerPath(sPath);
			if (!PathFileExists(strContainerPath)) return;
			SetCurrentDirectoryW(strContainerPath);
			OSUtils::CreateWin32Process(_T("cmd.exe"));
		}
		else
		{
			SetCurrentDirectoryW(sPath);
			OSUtils::CreateWin32Process(_T("cmd.exe"));
		}
	}
}

void CFileExplorerCtrl::OnOpenWSLHere()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		if (!PathUtils::IsDirectory(sPath))
		{
			CString strContainerPath = PathUtils::GetContainerPath(sPath);
			if (!PathFileExists(strContainerPath)) return;
			SetCurrentDirectoryW(strContainerPath);
			OSUtils::CreateWin32Process(_T("wsl.exe"));
		}
		else
		{
			SetCurrentDirectoryW(sPath);
			OSUtils::CreateWin32Process(_T("wsl.exe"));
		}
	}
}

void CFileExplorerCtrl::OnOpenCMDAppendFileHere()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		if (!PathUtils::IsDirectory(sPath))
		{
			CString strContainerPath = PathUtils::GetContainerPath(sPath);
			if (!PathFileExists(strContainerPath)) return;
			SetCurrentDirectoryW(strContainerPath);
			OSUtils::CreateWin32Process(_T("cmd.exe"));
		}
		else
		{
			SetCurrentDirectoryW(sPath);
			OSUtils::CreateWin32Process(_T("cmd.exe"));
		}
		Sleep(500);
		CString strClipBoardText = GetClipboardPlainText();
		OpenClipBoard(PathUtils::GetFilenameFromPath(sPath));
		HWND hCMD = OSUtils::GetHWNDFromClassNameAndProgramPath(L"ConsoleWindowClass", L"C:\\WINDOWS\\system32\\cmd.exe");
		OSUtils::PatseClipboardToCMD(hCMD);
		OpenClipBoard(strClipBoardText);
	}
}

void CFileExplorerCtrl::OnOpenCMDAppendPathHere()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		if (!PathUtils::IsDirectory(sPath))
		{
			CString strContainerPath = PathUtils::GetContainerPath(sPath);
			if (!PathFileExists(strContainerPath)) return;
			SetCurrentDirectoryW(strContainerPath);
			OSUtils::CreateWin32Process(_T("cmd.exe"));
		}
		else
		{
			SetCurrentDirectoryW(sPath);
			OSUtils::CreateWin32Process(_T("cmd.exe"));
		}
		Sleep(500);
		CString strClipBoardText = GetClipboardPlainText();
		OpenClipBoard(_T("\"") + sPath + _T("\""));
		HWND hCMD = OSUtils::GetHWNDFromClassNameAndProgramPath(L"ConsoleWindowClass", L"C:\\WINDOWS\\system32\\cmd.exe");
		OSUtils::PatseClipboardToCMD(hCMD);
		OpenClipBoard(strClipBoardText);
	}
}

void CFileExplorerCtrl::OnOpenCMDPatseClipboardHere()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		if (!PathUtils::IsDirectory(sPath))
		{
			CString strContainerPath = PathUtils::GetContainerPath(sPath);
			if (!PathFileExists(strContainerPath)) return;
			SetCurrentDirectoryW(strContainerPath);
			OSUtils::CreateWin32Process(_T("cmd.exe"));
		}
		else
		{
			SetCurrentDirectoryW(sPath);
			OSUtils::CreateWin32Process(_T("cmd.exe"));
		}
	}
	Sleep(500);
	HWND hCMD = OSUtils::GetHWNDFromClassNameAndProgramPath(L"ConsoleWindowClass", L"C:\\WINDOWS\\system32\\cmd.exe");
	OSUtils::PatseClipboardToCMD(hCMD);
}

void CFileExplorerCtrl::OnOpenPowerShellHere()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		if (!PathUtils::IsDirectory(sPath))
		{
			CString strContainerPath = PathUtils::GetContainerPath(sPath);
			if (!PathFileExists(strContainerPath)) return;
			SetCurrentDirectoryW(strContainerPath);
			OSUtils::CreateWin32Process(_T("powershell.exe"));
		}
		else
		{
			SetCurrentDirectoryW(sPath);
			OSUtils::CreateWin32Process(_T("powershell.exe"));
		}
	}
}

void CFileExplorerCtrl::OnOpenGitBashHere()
{
	CString strGitBash = AppSettingMgr.m_strGitWindowFolderPath + _T("\\bin\\sh.exe");
	if (!PathFileExists(strGitBash))
	{
		AfxMessageBoxFormat(MB_ICONWARNING, _T("[Path Error] \"%s\" does not exist. Please set it in [Preference > General Settings]."), strGitBash);
		return;
	}
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		if (!PathFileExists(sPath)) return;
		if (PathUtils::IsDirectory(sPath))
		{
			SetCurrentDirectoryW(sPath);
			CString strCommandLine = _T("start \"\" \"") + strGitBash + _T("\"") + _T(" --login");
			_wsystem(AppUtils::CStringToWStd(strCommandLine).c_str());
		}
		else
		{
			CString strContainerPath = PathUtils::GetContainerPath(sPath);
			if (!PathFileExists(strContainerPath)) return;
			SetCurrentDirectoryW(strContainerPath);
			CString strCommandLine = _T("start \"\" \"") + strGitBash + _T("\"") + _T(" --login");
			_wsystem(AppUtils::CStringToWStd(strCommandLine).c_str());
		}
	}
}

void CFileExplorerCtrl::OnOpenGitWslHere()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		if (!PathUtils::IsDirectory(sPath))
		{
			CString strContainerPath = PathUtils::GetContainerPath(sPath);
			if (!PathFileExists(strContainerPath)) return;
			SetCurrentDirectoryW(strContainerPath);
			OSUtils::CreateWin32Process(_T("wsl.exe"));
		}
		else
		{
			SetCurrentDirectoryW(sPath);
			OSUtils::CreateWin32Process(_T("wsl.exe"));
		}
	}
}

void CFileExplorerCtrl::OnOptionsEditListAllFile()
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame); if (!pFrame) return;

	CString strPath = GetSelectedPath();
	if (PathFileExists(strPath))
	{
		if (!PathUtils::IsDirectory(strPath))
		{
			strPath = PathUtils::GetContainerPath(strPath);
			if (!PathFileExists(strPath)) return;
		}
		auto startMeasureTime = OSUtils::StartBenchmark();
		CFindPathWorker finder(strPath);
		finder.FindAllFiles();
		pFrame->AddPathResultDataToPane(finder.m_pathResultDataList, _T(""), finder.m_nTotalSearch, OSUtils::StopBenchmark(startMeasureTime), FALSE, TRUE);
		SetFocus();
	}
	else
	{
		CString strMessage = _T("> [Explorer Window] [Path Error] \"%s\" does not exist.");
		strMessage.Format(strMessage, strPath);
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strMessage, BasicColors::orange);
	}
}

void CFileExplorerCtrl::OnOptionsEditListAllFolder()
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;

	CString strPath = GetSelectedPath();
	if (PathFileExists(strPath))
	{
		if (!PathUtils::IsDirectory(strPath))
		{
			strPath = PathUtils::GetContainerPath(strPath);
			if (!PathFileExists(strPath)) return;
		}
		auto startMeasureTime = OSUtils::StartBenchmark();
		CFindPathWorker finder(strPath);
		finder.FindAllFolders();
		pFrame->AddPathResultDataToPane(finder.m_pathResultDataList, _T(""), finder.m_nTotalSearch, OSUtils::StopBenchmark(startMeasureTime), FALSE, TRUE);
		SetFocus();
	}
	else
	{
		CString strMessage = _T("> [Explorer Window] [Path Error] \"%s\" does not exist.");
		strMessage.Format(strMessage, strPath);
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strMessage, BasicColors::orange);
	}
}

void CFileExplorerCtrl::OnOptionsEditSearchText()
{
	CString strPath = GetSelectedPath();
	if (PathFileExists(strPath))
	{
		CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
		ASSERT(pFrame); if (!pFrame) return;
		pFrame->InitSearchReplaceFromExplorer(strPath, SEARCH_REPLACE_GOTO_DLG_TYPE::SEARCH);
	}
	else
	{
		CString strMessage = _T("> [Explorer Window] [Search Path Error] selected path does not exist or is a special path.");
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strMessage, BasicColors::orange);
	}
}

void CFileExplorerCtrl::OnOptionsEditReplaceOnfolder()
{
	CString strPath = GetSelectedPath();
	if (PathFileExists(strPath))
	{
		CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
		ASSERT(pFrame); if (!pFrame) return;
		pFrame->InitSearchReplaceFromExplorer(strPath, SEARCH_REPLACE_GOTO_DLG_TYPE::REPLACE);
	}
	else
	{
		CString strMessage = _T("> [Explorer Window] [Search Path Error] selected path does not exist or is a special path.");
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strMessage, BasicColors::orange);
	}
}

void CFileExplorerCtrl::OnOptionsEditSearchFiles()
{
	DoNavigateSearchFiles(GetSelectedPath());
}

void CFileExplorerCtrl::ReleaseSearchFileDlg()
{
	m_pSearchFileDlg = NULL;
	SetFocus();
}

void CFileExplorerCtrl::OnOptionsEditFileSaveAs()
{
	CString strSelectedPath = GetSelectedPath();
	if (PathFileExists(strSelectedPath))
	{
		if (!PathUtils::IsDirectory(strSelectedPath))
		{
			strSelectedPath = PathUtils::GetContainerPath(strSelectedPath);
		}
		auto pDoc = AppUtils::GetMDIActiveDocument();
		if (pDoc)
		{
			if (pDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
			{
				CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(pDoc);
				if (pEditorDoc)
				{
					pEditorDoc->SetSaveDocumentPath(strSelectedPath);
					pEditorDoc->OnFileSaveAs();
				}
			}
			else if (pDoc->IsKindOf(RUNTIME_CLASS(CImageDoc)))
			{
				CImageDoc* pImageDoc = dynamic_cast<CImageDoc*>(pDoc);
				if (pImageDoc)
				{
					pImageDoc->SetSaveDocumentPath(strSelectedPath);
					pImageDoc->OnFileSaveAs();
				}
			}
			CString strNewSavedFilePath = strSelectedPath + _T("\\") + pDoc->GetTitle();
			if (PathFileExists(strNewSavedFilePath))
			{
				Refresh();
				SetSelectedPath(strNewSavedFilePath);
			}
		}
	}
	else
	{
		CString strMessage = _T("> [Explorer Window] [Search Path Error] selected path does not exist or is a special path.");
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strMessage, BasicColors::orange);
	}
}

void CFileExplorerCtrl::OnCut()
{
	m_sSourceCopyPath.Empty();
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		if (IsFolder(hItem))
		{
			LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Explorer Window] Please use system menu for cutting folder [Shift + Right click]..."), BasicColors::orange);
		}
		else
		{
			m_bIsCopyItemAction = FALSE;
			m_sSourceCopyPath = ItemToPath(hItem);
		}
	}
}

void CFileExplorerCtrl::OnCopy()
{
	m_sSourceCopyPath.Empty();
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		if (IsFolder(hItem))
		{
			LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [Explorer Window] Please use system menu for copying folder [Shift + Right click]..."), BasicColors::orange);
		}
		else
		{
			m_bIsCopyItemAction = TRUE;
			m_sSourceCopyPath = ItemToPath(hItem);
			if (PathFileExists(m_sSourceCopyPath))
			{
				GuiUtils::PushFileObjectToClipboard(m_sSourceCopyPath);
			}
		}
	}
}

void CFileExplorerCtrl::OnPaste()
{
	if (PathFileExists(m_sSourceCopyPath))
	{
		HTREEITEM hNewFolder = MoveFileWin32(GetSelectedItem(), m_bIsCopyItemAction);
		m_sSourceCopyPath.Empty();
		if (hNewFolder)
		{
			OnRefresh();
		}
	}
}

void CFileExplorerCtrl::OnUpdatePaste(CCmdUI * pCmdUI)
{
	HTREEITEM hSelItem = GetSelectedItem();
	if (hSelItem && m_bAllowCreateFileAndFolder && !m_sSourceCopyPath.IsEmpty())
	{
		//Allow creation of a folder if the selected item is itself a directory/folder
#pragma warning(suppress: 26490)
		const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hSelItem));
		ASSERT(pItem != NULL);
#pragma warning(suppress: 26489)
		const DWORD dwAttributes = GetFileAttributes(pItem->m_sFQPath);
		if (dwAttributes != INVALID_FILE_ATTRIBUTES)
#pragma warning(suppress: 26486)
			pCmdUI->Enable((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);
		else
#pragma warning(suppress: 26486)
			pCmdUI->Enable(FALSE);
	}
	else
#pragma warning(suppress: 26486)
		pCmdUI->Enable(FALSE);
}

HTREEITEM CFileExplorerCtrl::InsertFileItem(_In_ HTREEITEM hParent, _In_ CFileExplorerCtrlItemInfo* pItem, _In_ int nStateMask, _In_ int nIcon, _In_ int nSelIcon, _In_ bool bCheckForChildren)
{
	//Validate our parameters
	ASSERT(pItem->m_NodeType != CFileExplorerCtrlItemInfo::NodeType::UnknownNode);

	//Correct the label if need be
	CString sLabel;
	if (IsDrive(pItem->m_sFQPath) && m_bShowDriveLabels)
		sLabel = GetDriveLabel(pItem->m_sFQPath);
	else
		sLabel = GetCorrectedLabel(pItem);

	//Add the actual item
	TVINSERTSTRUCT tvis{};
	tvis.hParent = hParent;
	tvis.hInsertAfter = TVI_LAST;
	tvis.item.mask = TVIF_CHILDREN | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	tvis.item.iImage = nIcon;
	tvis.item.iSelectedImage = nSelIcon;
#pragma warning(suppress: 26490)
	tvis.item.lParam = reinterpret_cast<LPARAM>(pItem);
	tvis.item.pszText = sLabel.GetBuffer(sLabel.GetLength());
	if (bCheckForChildren)
		tvis.item.cChildren = HasGotSubEntries(pItem->m_sFQPath);
	else
		tvis.item.cChildren = TRUE;
	if (nStateMask)
	{
		tvis.item.mask |= TVIF_STATE;
		tvis.item.stateMask |= TVIS_OVERLAYMASK;
		tvis.item.state |= INDEXTOOVERLAYMASK(nStateMask);
	}

	HTREEITEM hItem = InsertItem(&tvis);
	sLabel.ReleaseBuffer();
#pragma warning(suppress: 26487)
	return hItem;
}

bool CFileExplorerCtrl::IsExpanded(_In_ HTREEITEM hItem)
{
	TVITEM tvItem{};
	tvItem.hItem = hItem;
	tvItem.mask = TVIF_HANDLE | TVIF_STATE;
	return GetItem(&tvItem) && (tvItem.state & TVIS_EXPANDED);
}

void CFileExplorerCtrl::SetFocusOnCurrentMDITab()
{
	CString strDocumentFile(ItemToPath(GetSelectedItem()));
	if (PathFileExists(strDocumentFile) && !PathUtils::IsDirectory(strDocumentFile))
	{
		auto pDoc = AppUtils::GetExistedDocument(strDocumentFile);
		if (pDoc)
		{
			AppUtils::SetActiveDocument(pDoc);
		}
	}
}

CString CFileExplorerCtrl::GetCorrectedLabel(_In_ CFileExplorerCtrlItemInfo* pItem)
{
	CString sLabel(pItem->m_sRelativePath);
	switch (m_FileExtensions)
	{
	case HideFileExtension::UseTheShellSetting:
	{
		CString sTempLabel;
		const short nGFT = GetFileTitle(pItem->m_sRelativePath, sTempLabel.GetBuffer(_MAX_PATH), _MAX_PATH);
		sTempLabel.ReleaseBuffer();
		if (IsFile(pItem->m_sFQPath) && (nGFT == 0))
		{
			pItem->m_bExtensionHidden = (sLabel.CompareNoCase(sTempLabel) != 0);
			sLabel = sTempLabel;
		}
		break;
	}
	case HideFileExtension::HideExtension:
	{
		//Remove the extension if the item is a file
		if (IsFile(pItem->m_sFQPath))
		{
			CString sDrive;
			CString sDir;
			CString sFname;
			_tsplitpath_s(pItem->m_sRelativePath, sDrive.GetBuffer(_MAX_DRIVE), _MAX_DRIVE, sDir.GetBuffer(_MAX_DIR), _MAX_DIR, sFname.GetBuffer(_MAX_FNAME), _MAX_FNAME, NULL, 0);
			sFname.ReleaseBuffer();
			sDir.ReleaseBuffer();
			sDrive.ReleaseBuffer();
			CString sPath;
			_tmakepath_s(sPath.GetBuffer(_MAX_PATH), _MAX_PATH, sDrive, sDir, sFname, NULL);
			sPath.ReleaseBuffer();
			sLabel = sPath;
			pItem->m_bExtensionHidden = true;
		}
		break;
	}
	default:
	{
		pItem->m_bExtensionHidden = false;
		break;
	}
	}
	return sLabel;
}

void CFileExplorerCtrl::DisplayRootItems()
{
	//Add Current User Folder if requested to do so
	if (m_bShowCurrentUserFolder && (m_Malloc != NULL))
	{
#pragma warning(suppress: 26403 26409)
		auto pItem = new CFileExplorerCtrlItemInfo;
		pItem->m_NodeType = CFileExplorerCtrlItemInfo::NodeType::CurrentUserFolderNode;
		int nIcon = 0;
		int nSelIcon = 0;

		//Get the localized name and correct icons for the current users folder
		LPITEMIDLIST lpDocsPidl = NULL;
		if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_PROFILE, &lpDocsPidl)))
		{
			//Get the display name of the folder
			SHFILEINFO sfi{};
#pragma warning(suppress: 26490)
			if (SHGetFileInfo(reinterpret_cast<LPCTSTR>(lpDocsPidl), 0, &sfi, sizeof(sfi), SHGFI_PIDL | SHGFI_DISPLAYNAME))
#pragma warning(suppress: 26485)
				pItem->m_sRelativePath = sfi.szDisplayName;

			//While we are at it, also get the real path of the current users folder
			CString sFolderPath;
			const HRESULT hr = SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, SHGFP_TYPE_CURRENT, sFolderPath.GetBuffer(_MAX_PATH));
			sFolderPath.ReleaseBuffer();
			if (SUCCEEDED(hr))
			{
				pItem->m_sFQPath = sFolderPath;
				m_sCurrentUserFolderPath = pItem->m_sFQPath; //Also maintain a copy ourselves, We use this when we are trying to select items in the control

				//Get the icons for the folder
				nIcon = GetIconIndex(sFolderPath);
				nSelIcon = GetSelIconIndex(sFolderPath);
			}

			//Free up the pidl now that we are finished with it
			m_Malloc->Free(lpDocsPidl);
		}

		//Add it to the tree control
#pragma warning(suppress: 26486)
		m_hCurrentUserFolderRoot = InsertFileItem(m_hRoot, pItem, 0, nIcon, nSelIcon, false);
	}

	//Add My Documents if requested to do so
	if (m_bShowMyDocuments && (m_Malloc != NULL))
	{
#pragma warning(suppress: 26403 26409)
		auto pItem = new CFileExplorerCtrlItemInfo;
		pItem->m_NodeType = CFileExplorerCtrlItemInfo::NodeType::MyDocumentsNode;
		int nIcon = 0;
		int nSelIcon = 0;

		//Get the localized name and correct icons for "My Documents"
		LPITEMIDLIST lpDocsPidl = NULL;
		if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &lpDocsPidl)))
		{
			//Get the display name of the folder
			SHFILEINFO sfi{};
#pragma warning(suppress: 26490)
			if (SHGetFileInfo(reinterpret_cast<LPCTSTR>(lpDocsPidl), 0, &sfi, sizeof(sfi), SHGFI_PIDL | SHGFI_DISPLAYNAME))
#pragma warning(suppress: 26485)
				pItem->m_sRelativePath = sfi.szDisplayName;

			//While we are at it, also get the real path of "My Documents"
			CString sFolderPath;
			const HRESULT hr = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, sFolderPath.GetBuffer(_MAX_PATH));
			sFolderPath.ReleaseBuffer();
			if (SUCCEEDED(hr))
			{
				pItem->m_sFQPath = sFolderPath;
				m_sMyDocumentsPath = pItem->m_sFQPath; //Also maintain a copy ourselves, We use this when we are trying to select items in the control

				//Get the icons for the folder
				nIcon = GetIconIndex(sFolderPath);
				nSelIcon = GetSelIconIndex(sFolderPath);
			}

			//Free up the pidl now that we are finished with it
			m_Malloc->Free(lpDocsPidl);
		}

		//Add it to the tree control
#pragma warning(suppress: 26486)
		m_hMyDocumentsRoot = InsertFileItem(m_hRoot, pItem, 0, nIcon, nSelIcon, false);
	}

	//Should we insert a "My Computer/This PC" node
	if (m_bShowMyComputer && (m_Malloc != NULL))
	{
#pragma warning(suppress: 26403 26409)
		auto pItem = new CFileExplorerCtrlItemInfo;
		pItem->m_NodeType = CFileExplorerCtrlItemInfo::NodeType::MyComputerNode;
		int nIcon = 0;
		int nSelIcon = 0;

		//Get the localized name and correct icons for "My Computer/This PC"
		LPITEMIDLIST lpMCPidl = NULL;
		if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DRIVES, &lpMCPidl)))
		{
			//Get the display name for the folder
			SHFILEINFO sfi{};
#pragma warning(suppress: 26490)
			if (SHGetFileInfo(reinterpret_cast<LPCTSTR>(lpMCPidl), 0, &sfi, sizeof(sfi), SHGFI_PIDL | SHGFI_DISPLAYNAME))
#pragma warning(suppress: 26485)
				pItem->m_sRelativePath = sfi.szDisplayName;

			//Get the icons for the folder
			nIcon = GetIconIndex(lpMCPidl);
			nSelIcon = GetSelIconIndex(lpMCPidl);

			//Free up the pidl now that we are finished with it
			m_Malloc->Free(lpMCPidl);
		}

		//Add it to the tree control
#pragma warning(suppress: 26486)
		m_hMyComputerRoot = InsertFileItem(m_hRoot, pItem, 0, nIcon, nSelIcon, false);
	}

	//Display all the drives (if we are not using My Computer/This PC")
	if (!m_bShowMyComputer)
		DisplayDrives(m_hRoot, false);

	//Also add "Network Neighborhood/Network" if requested to do so
	if (m_bShowNetwork && (m_Malloc != NULL))
	{
#pragma warning(suppress: 26403 26409)
		auto pItem = new CFileExplorerCtrlItemInfo;
		pItem->m_NodeType = CFileExplorerCtrlItemInfo::NodeType::NetworkNode;
		int nIcon = 0;
		int nSelIcon = 0;

		//Get the localized name and correct icons for "Network Neighborhood/Network"
		LPITEMIDLIST lpNNPidl = NULL;
		if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_NETWORK, &lpNNPidl)))
		{
			//Get the display name for the folder
			SHFILEINFO sfi{};
#pragma warning(suppress: 26490)
			if (SHGetFileInfo(reinterpret_cast<LPCTSTR>(lpNNPidl), 0, &sfi, sizeof(sfi), SHGFI_PIDL | SHGFI_DISPLAYNAME))
#pragma warning(suppress: 26485)
				pItem->m_sRelativePath = sfi.szDisplayName;

			//Get the icons for the folder
			nIcon = GetIconIndex(lpNNPidl);
			nSelIcon = GetSelIconIndex(lpNNPidl);

			//Free up the pidl now that we are finished with it
			m_Malloc->Free(lpNNPidl);
		}

		//Add it to the tree control
#pragma warning(suppress: 26486)
		m_hNetworkRoot = InsertFileItem(m_hRoot, pItem, 0, nIcon, nSelIcon, false);
	}
}

void CFileExplorerCtrl::EnsureVisibleCenter(HTREEITEM hItem)
{
	SetRedraw(FALSE);
	if (!hItem) return;
	//SCROLLINFO sbiBefore = { sizeof(SCROLLINFO) };
	//sbiBefore.fMask = SIF_ALL;
	//GetScrollInfo(SB_HORZ, &sbiBefore);
	EnsureVisible(hItem);
	SendMessage(WM_VSCROLL, SB_PAGEDOWN, 0);
	EnsureVisible(hItem); //item is on top now
	CRect rectClient;
	GetClientRect(&rectClient);
	for (UINT i = 0; i < GetVisibleCount(); i++)
	{
		CRect rectHitem;
		GetItemRect(hItem, &rectHitem, FALSE);
		if (rectHitem.bottom > rectClient.Height() / 2) break;
		SendMessage(WM_VSCROLL, SB_LINEUP, NULL);
	}
	//SetScrollInfo(SB_HORZ, &sbiBefore);
	SetRedraw(TRUE);
}

#define MAXIMUM_STATUS_FILE_PATH 76
void CFileExplorerCtrl::UpdateStatusBarSelectedText(const CString& sPath)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	if (pFrame)
	{
		CMFCStatusBar* pStatusBar = pFrame->GetStatusBar();
		if (pStatusBar)
		{
			if (sPath.GetLength() > MAXIMUM_STATUS_FILE_PATH)
			{
				CString strTempPath = sPath;
				strTempPath = _T("...") + strTempPath.Right(MAXIMUM_STATUS_FILE_PATH - 5);
				pStatusBar->SetPaneText(0, strTempPath);
			}
			else pStatusBar->SetPaneText(0, sPath);
		}
	}
}

#pragma warning(suppress: 26429)
BOOL CFileExplorerCtrl::OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
#pragma warning(suppress: 26490)
	auto pDispInfo = reinterpret_cast<TV_DISPINFO*>(pNMHDR);

	if (pDispInfo->item.hItem)
	{
#pragma warning(suppress: 26486 26490)
		const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(pDispInfo->item.hItem));
#pragma warning(suppress: 26496)
		AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26489)
		if (m_bEditLabelFlag && m_bAllowRename && ((pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::FileNode) || (pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::FolderNode)))
			*pResult = FALSE;
		else
			*pResult = TRUE;
	}
	else
		*pResult = TRUE;

	return TRUE; //Allow the message to be reflected again
}

#pragma warning(suppress: 26429)
BOOL CFileExplorerCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
#pragma warning(suppress: 26490)
	auto pCustomDraw = reinterpret_cast<NMTVCUSTOMDRAW*>(pNMHDR);
	switch (pCustomDraw->nmcd.dwDrawStage)
	{
		case CDDS_PREPAINT:
		{
			*pResult = CDRF_NOTIFYITEMDRAW; //Tell the control that we are interested in item notifications
			break;
		}
		case CDDS_ITEMPREPAINT:
		{
			//Let it know that we are finished doing custom draw
			*pResult = CDRF_DODEFAULT;

			//To work around what looks like a bug in Commctrl v6 we do not do custom drawing until the window is visible
			if (!IsWindowVisible())
				return TRUE;

			HTREEITEM hItem = reinterpret_cast<HTREEITEM>(pCustomDraw->nmcd.dwItemSpec);
			//Check to see if this item is compressed and if it it is, change its color just like explorer does
	#pragma warning(suppress: 26490)
			if (m_bShowCompressedUsingDifferentColor && ((pCustomDraw->nmcd.uItemState & CDIS_SELECTED) == 0) && IsCompressed(hItem))
				pCustomDraw->clrText = m_rgbCompressed;
	#pragma warning(suppress: 26490)
			else if (m_bShowEncryptedUsingDifferentColor && ((pCustomDraw->nmcd.uItemState & CDIS_SELECTED) == 0) && IsEncrypted(hItem)) //also check for encrypted files
				pCustomDraw->clrText = m_rgbEncrypted;
	#pragma warning(suppress: 26490)
			if (hItem == GetSelectedItem())
			{
				pCustomDraw->clrText = GetSysColor(COLOR_HIGHLIGHTTEXT);
				pCustomDraw->clrTextBk = GetSysColor(COLOR_HIGHLIGHT);
			}
			break;
		}
		default:
		{
			break;
		}
	}

	return TRUE; //Allow the message to be reflected again
}

#pragma warning(suppress: 26429)
BOOL CFileExplorerCtrl::OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
#pragma warning(suppress: 26490)
	auto pNMTreeView = reinterpret_cast<NMTREEVIEW*>(pNMHDR);
#pragma warning(suppress: 26496)
	AFXASSUME(pNMTreeView != NULL);

	//Nothing selected
	if (pNMTreeView->itemNew.hItem == NULL)
		return FALSE;

	//Check to see if the current item is valid, if not then delete it (Exclude special items from this check)
#pragma warning(suppress: 26486 26490)
	const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(pNMTreeView->itemNew.hItem));
#pragma warning(suppress: 26496)
	AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26489)
	CString sPath(pItem->m_sFQPath);
#pragma warning(suppress: 26489)
	if ((pNMTreeView->itemNew.hItem != m_hRoot) &&
		(pNMTreeView->itemNew.hItem != m_hMyDocumentsRoot) &&
		(pNMTreeView->itemNew.hItem != m_hCurrentUserFolderRoot) &&
		(pNMTreeView->itemNew.hItem != m_hNetworkRoot) &&
		(pItem->m_dwNetResourceScope == 0) &&
		(pNMTreeView->itemNew.hItem != m_hMyComputerRoot) && !IsDrive(sPath) && (GetFileAttributes(sPath) == 0xFFFFFFFF))
	{
		//Before we delete it see if we are the only child item
		HTREEITEM hParent = GetParentItem(pNMTreeView->itemNew.hItem);

		//Delete the item
		DeleteItem(pNMTreeView->itemNew.hItem);

		//Remove all the child items from the parent
		SetHasPlusButton(hParent, false);

		*pResult = 1;

		return FALSE; //Allow the message to be reflected again
	}

	//Add to the prev array the item we were just at
	if (pNMTreeView->itemOld.hItem && !m_bUpdatingHistorySelection)
	{
		if (m_PrevItems.size() > m_nMaxHistory)
			m_PrevItems.erase(m_PrevItems.begin());
#pragma warning(suppress: 26486)
		m_PrevItems.push_back(pNMTreeView->itemOld.hItem);
	}

	//Remeber the serial number for this item (if it is a drive)
	if (IsDrive(sPath))
	{
		const int nDrive = sPath.GetAt(0) - _T('A');
#pragma warning(suppress: 26446 26482)
		GetSerialNumber(sPath, m_MediaIDs[nDrive]);
	}

	//Setup notifications if required
	if (m_bAutoRefresh && CanHandleChangeNotifications(sPath))
#pragma warning(suppress: 26489)
		CreateMonitoringThread(pItem->m_sFQPath);
	else
		KillMonitoringThread();

	// do preview mode
	if (AppSettingMgr.m_bEnablePreviewFile)
	{
		OnPreviewFile(pNMTreeView, sPath);
		SetFocus();
	}

	UpdateStatusBarSelectedText(sPath);

	*pResult = 0;

	return FALSE; //Allow the message to be reflected again
}

#pragma warning(suppress: 26440)
void CFileExplorerCtrl::OnPreviewFile(_In_ NMTREEVIEW* /*pNMTreeView*/, _In_ const CString& sPath)
{
	if (!PathFileExists(sPath) || PathUtils::IsDirectory(sPath))
	{
		return;
	}
	if (!PathUtils::IsBinaryFile(sPath, FILE_BINNARY | FILE_OFFICE))
	{
		LONGLONG llFileSize = PathUtils::GetFileSize(sPath);
		if (llFileSize > AppSettingMgr.m_nFilePreviewSizeLimit)
		{
			CString strFileSize = CString(std::unique_ptr<char>(PathUtils::SizeMemoryToString(llFileSize)).get());
			LOG_OUTPUT_MESSAGE_ACTIVE_PANE(AfxCStringFormat(_T("> [Explorer Window] [Preview Waring] File size \"%s\" is %s, exceeded preview limitation. Please change limitation value in setting..."), sPath, strFileSize), BasicColors::orange);
			return;
		}
		CBaseDoc* pActiveDoc = dynamic_cast<CBaseDoc*>(AppUtils::GetMDIActiveDocument());
		CDocument* pOpenedDoc = AppUtils::GetExistedDocument(sPath);
		if (pOpenedDoc) // if file is already opened then active it
		{
			if (pOpenedDoc != pActiveDoc)
			{
				if (pActiveDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
				{
					AppUtils::CloseAllPreviewDocument(PREVIEW_TYPE::PREVIEW_EDITOR);
				}
				else if (pActiveDoc->IsKindOf(RUNTIME_CLASS(CImageDoc)))
				{
					AppUtils::CloseAllPreviewDocument(PREVIEW_TYPE::PREVIEW_IMAGE);
				}
				else if (pActiveDoc->IsKindOf(RUNTIME_CLASS(CPdfDoc)))
				{
					AppUtils::CloseAllPreviewDocument(PREVIEW_TYPE::PREVIEW_PDF);
				}
				else if (pActiveDoc->IsKindOf(RUNTIME_CLASS(CMediaDoc)))
				{
					AppUtils::CloseAllPreviewDocument(PREVIEW_TYPE::PREVIEW_MEDIA);
				}
				AppUtils::SetActiveDocument(pOpenedDoc);
			}
		}
		else
		{
			if (pActiveDoc)
			{
				if (pActiveDoc->IsPreviewMode() && !pActiveDoc->IsModified()) // if there is a preview doc then reload file content
				{
					if (PathUtils::IsImageFile(sPath)) // preview image file
					{
						if (pActiveDoc->IsKindOf(RUNTIME_CLASS(CImageDoc)))
						{
							CImageDoc* pImageDoc = (CImageDoc*)(pActiveDoc);
							pImageDoc->ReloadPreviewDocument(sPath);
						}
						else if (pActiveDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)) || pActiveDoc->IsKindOf(RUNTIME_CLASS(CPdfDoc)) || pActiveDoc->IsKindOf(RUNTIME_CLASS(CMediaDoc)))
						{
							CImageDoc* pImageDoc = dynamic_cast<CImageDoc*>(AppUtils::GetNextPreviewDocument(PREVIEW_TYPE::PREVIEW_IMAGE));
							if (pImageDoc)
							{
								AppUtils::SetActiveDocument(pImageDoc);
								pImageDoc->ReloadPreviewDocument(sPath);
							}
							else // create new preview document if there is no any preview doc existed
							{
								AppUtils::CreateNewPreviewDocument(sPath);
							}
						}
					}
					else if (PathUtils::IsPdfFile(sPath)) // preview pdf file
					{
						if (pActiveDoc->IsKindOf(RUNTIME_CLASS(CPdfDoc)))
						{
							CPdfDoc* pPdfDoc = (CPdfDoc*)(pActiveDoc);
							pPdfDoc->ReloadPreviewDocument(sPath);
						}
						else if (pActiveDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)) || pActiveDoc->IsKindOf(RUNTIME_CLASS(CImageDoc)) || pActiveDoc->IsKindOf(RUNTIME_CLASS(CMediaDoc)))
						{
							CPdfDoc* pPdfDoc = dynamic_cast<CPdfDoc*>(AppUtils::GetNextPreviewDocument(PREVIEW_TYPE::PREVIEW_PDF));
							if (pPdfDoc)
							{
								AppUtils::SetActiveDocument(pPdfDoc);
								pPdfDoc->ReloadPreviewDocument(sPath);
							}
							else // create new preview document if there is no any preview doc existed
							{
								AppUtils::CreateNewPreviewDocument(sPath);
							}
						}
					}
					else if (PathUtils::IsMediaFile(sPath)) // preview media file
					{
						if (pActiveDoc->IsKindOf(RUNTIME_CLASS(CMediaDoc)))
						{
							CMediaDoc* pMediaDoc = (CMediaDoc*)(pActiveDoc);
							pMediaDoc->ReloadPreviewDocument(sPath);
						}
						else if (pActiveDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)) || pActiveDoc->IsKindOf(RUNTIME_CLASS(CImageDoc)) || pActiveDoc->IsKindOf(RUNTIME_CLASS(CPdfDoc)))
						{
							CMediaDoc* pMediaDoc = dynamic_cast<CMediaDoc*>(AppUtils::GetNextPreviewDocument(PREVIEW_TYPE::PREVIEW_MEDIA));
							if (pMediaDoc)
							{
								AppUtils::SetActiveDocument(pMediaDoc);
								pMediaDoc->ReloadPreviewDocument(sPath);
							}
							else // create new preview document if there is no any preview doc existed
							{
								AppUtils::CreateNewPreviewDocument(sPath);
							}
						}
					}
					else // preview text file
					{
						if (pActiveDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
						{
							CEditorDoc* pEdtiorDoc = (CEditorDoc*)(pActiveDoc);
							pEdtiorDoc->ReloadPreviewDocument(sPath);
						}
						else if (pActiveDoc->IsKindOf(RUNTIME_CLASS(CImageDoc)) || pActiveDoc->IsKindOf(RUNTIME_CLASS(CPdfDoc)) || pActiveDoc->IsKindOf(RUNTIME_CLASS(CMediaDoc)))
						{
							CEditorDoc* pEdtiorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetNextPreviewDocument(PREVIEW_TYPE::PREVIEW_EDITOR));
							if (pEdtiorDoc)
							{
								AppUtils::SetActiveDocument(pEdtiorDoc);
								pEdtiorDoc->ReloadPreviewDocument(sPath);
							}
							else // create new preview document if there is no any preview doc existed
							{
								AppUtils::CreateNewPreviewDocument(sPath);
							}
						}
					}
				}
				else // create new preview document if there is no any preview doc existed
				{
					AppUtils::CreateNewPreviewDocument(sPath);
				}
			}
		}
	}
	else
	{
		CString strMsg;
		strMsg.Format(_T("> [Explorer Window] Can not preview binary file \"%s\"..."), sPath);
		LOG_OUTPUT_MESSAGE_COLOR(strMsg, BasicColors::orange);
	}
}

#pragma warning(suppress: 26429)
BOOL CFileExplorerCtrl::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
	// exit edit mode
	m_bEditLabelFlag = FALSE;
#pragma warning(suppress: 26490)
	auto pDispInfo = reinterpret_cast<TV_DISPINFO*>(pNMHDR);
#pragma warning(suppress: 26496)
	AFXASSUME(pDispInfo != NULL);
	if (pDispInfo->item.pszText != NULL)
	{
		SHFILEOPSTRUCT shfo{};
		shfo.hwnd = GetParent()->GetSafeHwnd();
		shfo.wFunc = FO_RENAME;
		shfo.fFlags = FOF_ALLOWUNDO;

		//Work out the "From" string
		CString sFrom(ItemToPath(pDispInfo->item.hItem));
		if (!PathFileExists(sFrom)) return FALSE;

		// close document before change file in system...
		AppUtils::CloseDocumentByFilePath(sFrom);

		const size_t nFromLength = sFrom.GetLength();
		std::vector<TCHAR> sTempFrom;
		sTempFrom.resize(nFromLength + 2);
		_tcscpy_s(sTempFrom.data(), nFromLength + 2, sFrom);
#pragma warning(suppress: 26446)
		sTempFrom[nFromLength + 1] = _T('\0');
		shfo.pFrom = sTempFrom.data();
#pragma warning(suppress: 26486)
		HTREEITEM hParent = GetParentItem(pDispInfo->item.hItem);
		CString sParent(ItemToPath(hParent));

		//Work out the "To" string
		CString sTo;
#pragma warning(suppress: 26486)
		CString sToRelative(pDispInfo->item.pszText);
		if (IsDrive(sParent))
			sTo = sParent + pDispInfo->item.pszText;
		else
			sTo = sParent + _T("\\") + pDispInfo->item.pszText;
#pragma warning(suppress: 26490)
		auto pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(pDispInfo->item.hItem));
#pragma warning(suppress: 26496)
		AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26489)
		if (pItem->m_bExtensionHidden)
		{
			CString sExt;
			_tsplitpath_s(sFrom, NULL, 0, NULL, 0, NULL, 0, sExt.GetBuffer(_MAX_EXT), _MAX_EXT);
			sExt.ReleaseBuffer();
			sTo += sExt;
			sToRelative += sExt;
		}
		const size_t nToLength = sTo.GetLength();
		std::vector<TCHAR> sTempTo;
		sTempTo.resize(nToLength + 2);
		_tcscpy_s(sTempTo.data(), nToLength + 2, sTo);
#pragma warning(suppress: 26446)
		sTempTo[nToLength + 1] = _T('\0');
		shfo.pTo = sTempTo.data();

		//Kill the monitoring thread if necessary
		const bool bMonitoringThread = (m_pMonitoringThread != NULL);
		CString sMonitoringPath(m_sMonitoringPath);
		if (bMonitoringThread)
			KillMonitoringThread();

		//Let the shell perform the actual rename
		if ((SHFileOperation(&shfo) == 0) && (shfo.fAnyOperationsAborted == FALSE))
		{
			*pResult = TRUE;

			//Update its text
			SetItemText(pDispInfo->item.hItem, pDispInfo->item.pszText);

			//Update the item data
#pragma warning(suppress: 26489)
			pItem->m_sFQPath = sTo;
#pragma warning(suppress: 26489)
			pItem->m_sRelativePath = sToRelative;

			//Also update the icons for it (if need be)
#pragma warning(suppress: 26489)
			if (!pItem->m_bExtensionHidden)
			{
				CString sPath(ItemToPath(pDispInfo->item.hItem));
				SetItemImage(pDispInfo->item.hItem, GetIconIndex(sPath), GetSelIconIndex(sPath));
			}
		}

		//Recreate the monitoring thread if necessary
		if (bMonitoringThread)
			CreateMonitoringThread(m_sMonitoringPath);

		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Explorer Window] Renamed \"%s\" to \"%s\"..."), sFrom, sTo);
	}
	*pResult = 0;
	return FALSE; //Allow the message to be reflected again
}

INT_PTR CFileExplorerCtrl::OnToolHitTest(CPoint point, TOOLINFO * pTI) const
{
	RECT rect;
	UINT nFlags;
	HTREEITEM hitem = HitTest(point, &nFlags);
	if (nFlags & TVHT_ONITEMLABEL)
	{
		GetItemRect(hitem, &rect, TRUE);
		pTI->hwnd = m_hWnd;
		pTI->uId = (UINT)hitem;
		pTI->lpszText = LPSTR_TEXTCALLBACK;
		pTI->rect = rect;
		return pTI->uId;
	}
	return -1;
}

BOOL CFileExplorerCtrl::PreTranslateMessage(MSG* pMsg)
{
	//When an item is being edited make sure the edit control
	//receives certain important key strokes
	if (GetEditControl())
	{
		::TranslateMessage(pMsg);
		::DispatchMessage(pMsg);
		return TRUE; // DO NOT process further
	}
	//Context menu via the keyboard
	if (pMsg->message == WM_CONTEXTMENU)
	{
		CRect rect;
		GetItemRect(GetSelectedItem(), rect, TRUE);
		ClientToScreen(rect);
		OnContextMenu(NULL, rect.CenterPoint());
		return TRUE;
	}
	//Hitting the Escape key cancels drag & drop
#ifndef FILETREECTRL_NO_RESOURCES
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE && IsDragging())
	{
		EndDragging(true);
		return TRUE;
	}
#endif //#ifndef FILETREECTRL_NO_RESOURCES
	//Hitting the Ctrl + P key combination shows the properties sheet 
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'P')
	{
		if ((GetKeyState(VK_CONTROL) & 0x8000))
		{
			OnProperties();
		}
		return TRUE;
	}
	//Hitting the Ctrl + W key combination close the current file
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'W')
	{
		if ((GetKeyState(VK_CONTROL) & 0x8000))
		{
			CloseCurrentMDITab(GetSelectedItem());
		}
		return TRUE;
	}
	//Hitting the Enter key opens the item
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetKeyState(VK_SHIFT) & 0x8000 && GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnOpenAsRawFormat();
		}
		else if ((GetKeyState(VK_CONTROL) & 0x8000))
		{
			Open(GetSelectedItem(), TRUE);
		}
		else
		{
			Open(GetSelectedItem(), FALSE);
		}
		return TRUE;
	}
	//Hitting the delete key deletes the item
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_DELETE)
	{
		if (GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnRemoveFolderFromWorkSpace();
		}
		else
		{
			OnDelete();
		}
		return TRUE;
	}
	//hitting the F2 key begins in-place editing of an item
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		OnRename();
		return TRUE;
	}
	//hitting the Shift + Ctrl + N expand tree
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'N')
	{
		if (GetKeyState(VK_SHIFT) & 0x8000 && GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnExpandAll();
		}
		else if (GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnCreateFile();
		}
		return TRUE;
	}
	//hitting the Shift + Ctrl + M collapse tree
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'M')
	{
		if (GetKeyState(VK_SHIFT) & 0x8000 && GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnCollapseAll();
		}
		else if (GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnCreateFolder();
		}
		return TRUE;
	}
	//hitting the Ctrl + C copy item on tree
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'C')
	{
		if (GetKeyState(VK_SHIFT) & 0x8000 && GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnGetFullPath();
		}
		else if (GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnCopy();
		}
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'Q')
	{
		if (GetKeyState(VK_SHIFT) & 0x8000 && GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnSetFocusActiveMDITab();
		}
		return TRUE;
	}
	//hitting the Ctrl + V patse item on tree
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'V')
	{
		if (GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnPaste();
		}
		return TRUE;
	}
	//hitting the Ctrl + X cut item on tree
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'X')
	{
		if (GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnCut();
		}
		return TRUE;
	}
	//hitting the F5 key refresh tree
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F5)
	{
		OnRefresh();
		return TRUE;
	}
	//Hitting the Alt-Left Arrow key combination moves to the previous item
	else if (pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_LEFT)
	{
		OnBack();
		return TRUE;
	}
	//Hitting the Alt-Right Arrow key combination moves to the next item
	else if (pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_RIGHT)
	{
		OnForward();
		return TRUE;
	}
	//Hitting the space key combination active current MDI tab
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE)
	{
		SetFocusOnCurrentMDITab();
		return TRUE;
	}
	//hitting the backspace key goes to the parent folder
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_BACK)
	{
		UpOneLevel();
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'D')
	{
		if (GetKeyState(VK_SHIFT) & 0x8000 && GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnOptionsEditListAllFolder();
		}
		else if ((GetKeyState(VK_CONTROL) & 0x8000))
		{
			OnOptionsEditListAllFile();
			return TRUE;
		}
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'B')
	{
		if (GetKeyState(VK_SHIFT) & 0x8000 && GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnOpenBookMarkTable();
		}
		else if ((GetKeyState(VK_CONTROL) & 0x8000))
		{
			OnBookMarkPath();
			return TRUE;
		}
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'G')
	{
		if (GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnJumpToPath();
		}
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'T')
	{
		if (GetKeyState(VK_CONTROL) & 0x8000 && GetKeyState(VK_MENU) & 0x8000)
		{
			OnTerminalOpenNewCMDTab();
		}
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'O')
	{
		if (GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnAddMoreFolderToWorkSpace();
		}
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'S')
	{
		if (GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnOptionsEditFileSaveAs();
		}
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'F')
	{
		if (GetKeyState(VK_SHIFT) & 0x8000 && GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnOptionsEditSearchText();
		}
		else if (GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnOptionsEditSearchFiles();
		}
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'H')
	{
		if (GetKeyState(VK_SHIFT) & 0x8000 && GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnOptionsEditReplaceOnfolder();
		}
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'E')
	{
		if (GetKeyState(VK_CONTROL) & 0x8000 && (GetKeyState(VK_SHIFT) & 0x8000))
		{
			OnHostFileExplorer();
		}
		else if (GetKeyState(VK_CONTROL) & 0x8000)
		{
			OnOpenFileContainer();
		}
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB)
	{
		if ((GetKeyState(VK_SHIFT) & 0x8000))
		{
			OnBackToOriginalExplorer();
		}
		else
		{
			OnSetAsWorkspaceFolder();
		}
	}
	else if (pMsg->message == WM_RBUTTONDOWN)
	{
		if ((GetKeyState(VK_SHIFT) & 0x8000))
		{
			OnShowSystemMenu();
			return TRUE;
		}
	}
	else if (pMsg->message == WM_MBUTTONDOWN)
	{
		CloseCurrentMDITab(GetSelectedItem());
		return TRUE;
	}
	return __super::PreTranslateMessage(pMsg);
}

void CFileExplorerCtrl::OnUpOneLevel()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		HTREEITEM hParent = GetParentItem(hItem);
		if (hParent)
		{
			Select(hParent, TVGN_CARET);
			EnsureVisibleCenter(hParent);
		}
	}
}

bool CFileExplorerCtrl::IsFile(_In_ HTREEITEM hItem)
{
	if (!hItem) return FALSE;
#pragma warning(suppress: 26490)
	const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hItem));
#pragma warning(suppress: 26496)
	AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26489)
	return pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::FileNode;
}

bool CFileExplorerCtrl::IsFolder(_In_ HTREEITEM hItem)
{
	if (!hItem) return FALSE;
#pragma warning(suppress: 26490)
	const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hItem));
#pragma warning(suppress: 26496)
	AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26489)
	return pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::FolderNode;
}

bool CFileExplorerCtrl::IsDrive(_In_ HTREEITEM hItem)
{
	if (!hItem) return FALSE;
#pragma warning(suppress: 26490)
	const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hItem));
#pragma warning(suppress: 26496)
	AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26489)
	return pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::DriveNode;
}

bool CFileExplorerCtrl::IsNetworkShare(_In_ HTREEITEM hItem)
{
	if (!hItem) return FALSE;
#pragma warning(suppress: 26490)
	const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hItem));
#pragma warning(suppress: 26496)
	AFXASSUME(pItem != NULL);

#pragma warning(suppress: 26489)
	return ((pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::NetworkNode) && (pItem->m_dwNetResourceDisplayType == RESOURCEDISPLAYTYPE_SHARE));
}

bool CFileExplorerCtrl::DriveHasRemovableMedia(_In_ const CString& sPath)
{
	bool bRemovableMedia = false;
	if (IsDrive(sPath))
	{
		const UINT nDriveType = GetDriveType(sPath);
		bRemovableMedia = ((nDriveType == DRIVE_REMOVABLE) || (nDriveType == DRIVE_CDROM));
	}
	return bRemovableMedia;
}

bool CFileExplorerCtrl::IsCompressed(_In_ HTREEITEM hItem)
{
	if (!hItem) return FALSE;
	return IsCompressed(ItemToPath(hItem));
}

bool CFileExplorerCtrl::IsEncrypted(_In_ HTREEITEM hItem)
{
	if (!hItem) return FALSE;
	return IsEncrypted(ItemToPath(hItem));
}

bool CFileExplorerCtrl::IsFile(_In_ const CString& sPath) noexcept
{
	const DWORD dwAttributes = GetFileAttributes(sPath);
	return ((dwAttributes != 0xFFFFFFFF) && ((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0));
}

bool CFileExplorerCtrl::IsFolder(_In_ const CString& sPath) noexcept
{
	const DWORD dwAttributes = GetFileAttributes(sPath);
	return ((dwAttributes != 0xFFFFFFFF) && (dwAttributes & FILE_ATTRIBUTE_DIRECTORY));
}

bool CFileExplorerCtrl::IsDrive(_In_ const CString& sPath)
{
	return (sPath.GetLength() == 3 && sPath.GetAt(1) == _T(':') && sPath.GetAt(2) == _T('\\'));
}

bool CFileExplorerCtrl::IsUNCServerName(_In_ const CString& sPath)
{
	CString sDrive;
	CString sDir;
	CString sFname;
	CString sExt;
	_tsplitpath_s(sPath, sDrive.GetBuffer(_MAX_DRIVE), _MAX_DRIVE, sDir.GetBuffer(_MAX_DIR), _MAX_DIR, sFname.GetBuffer(_MAX_FNAME), _MAX_FNAME, sExt.GetBuffer(_MAX_EXT), _MAX_EXT);
	sExt.ReleaseBuffer();
	sFname.ReleaseBuffer();
	sDir.ReleaseBuffer();
	sDrive.ReleaseBuffer();
	return (sDrive.GetLength() == 0) && (sExt.GetLength() == 0) && (sDir == _T("\\\\")) && (sFname.Find(_T('\\')) == -1);
}

bool CFileExplorerCtrl::IsCompressed(_In_ const CString& sPath)
{
	bool bCompressed = false;
	if (!IsDrive(sPath))
	{
		const DWORD dwAttributes = GetFileAttributes(sPath);
		bCompressed = ((dwAttributes != 0xFFFFFFFF) && (dwAttributes & FILE_ATTRIBUTE_COMPRESSED));
	}

	return bCompressed;
}

bool CFileExplorerCtrl::IsEncrypted(_In_ const CString& sPath)
{
	bool bEncrypted = false;
	if (!IsDrive(sPath))
	{
		const DWORD dwAttributes = GetFileAttributes(sPath);
		bEncrypted = ((dwAttributes != 0xFFFFFFFF) && (dwAttributes & FILE_ATTRIBUTE_ENCRYPTED));
	}

	return bEncrypted;
}

bool CFileExplorerCtrl::HasGotSubEntries(_In_ const CString& sDirectory)
{
	//Validate our parameters
	ASSERT(sDirectory.GetLength());

	if (DriveHasRemovableMedia(sDirectory))
	{
		return true; //we do not bother searching for files on drives which have removable media as this would cause 
					 //the drive to spin up, which for the case of a floppy is annoying
	}
	else
	{
		//First check to see if there is any sub directories
		CFileFind find1;
		CString sFile;
		if (sDirectory.GetAt(sDirectory.GetLength() - 1) == _T('\\'))
			sFile = sDirectory + _T("*.*");
		else
			sFile = sDirectory + _T("\\*.*");
		BOOL bFind = find1.FindFile(sFile);
		while (bFind)
		{
			bFind = find1.FindNextFile();
			if (CanDisplayFolder(find1))
				return true;
		}

		//Now check to see if there is any files of the specified file mask
		for (const auto& sMask : m_FileNameMasks)
		{
			CFileFind find2;
			if (sDirectory.GetAt(sDirectory.GetLength() - 1) == _T('\\'))
				sFile = sDirectory + sMask;
			else
				sFile = sDirectory + _T("\\") + sMask;
			bFind = find2.FindFile(sFile);
			while (bFind)
			{
				bFind = find2.FindNextFile();
				if (CanDisplayFile(find2))
					return true;
			}
		}
	}

	return false;
}

void CFileExplorerCtrl::PopulateTree()
{
	//Validate our parameters
	ASSERT(GetSafeHwnd()); //Should only call this function after the creation of it on screen

	//Attach the image list to the tree control
	SetImageList(&m_SystemImageList, TVSIL_NORMAL);

	//Force a refresh
	Refresh();
}

void CFileExplorerCtrl::CreateMonitoringThread(_In_ const CString& sPath)
{
	//Kill any current notification thread
	KillMonitoringThread();

	//Setup the monitoring path
	m_sMonitoringPath = sPath;
	const int nLength = m_sMonitoringPath.GetLength();
	ASSERT(nLength);
	if (nLength && m_sMonitoringPath.GetAt(nLength - 1) != _T('\\'))
		m_sMonitoringPath += _T('\\');

	TRACE(_T("CFileExplorerCtrl::CreateMonitoringThread, Creating monitoring thread for %s\n"), m_sMonitoringPath.GetString());

	ASSERT(m_pMonitoringThread == NULL);
	m_pMonitoringThread = AfxBeginThread(_MonitoringThread, this, THREAD_PRIORITY_IDLE, 0, CREATE_SUSPENDED);
	if (m_pMonitoringThread != NULL)
	{
		//We're in charge of deletion of the thread
		m_pMonitoringThread->m_bAutoDelete = FALSE;

		//Resume the thread now that everything is ready to go
		m_pMonitoringThread->ResumeThread();
	}
}

UINT CFileExplorerCtrl::_MonitoringThread(_In_ LPVOID pParam)
{
	//Validate our parameters
	ASSERT(pParam != NULL);
	auto pThis = static_cast<CFileExplorerCtrl*>(pParam);
#pragma warning(suppress: 26496)
	AFXASSUME(pThis != NULL);

	//Convert from the SDK world to the C++ world
	return pThis->MonitoringThread();
}

UINT CFileExplorerCtrl::MonitoringThread()
{
	//Form the notification flag to use
	DWORD dwNotifyFilter = FILE_NOTIFY_CHANGE_DIR_NAME;
	if (m_bShowFiles)
		dwNotifyFilter |= FILE_NOTIFY_CHANGE_FILE_NAME;

	//Get a handle to a file change notification object
	HANDLE hChange = FindFirstChangeNotification(m_sMonitoringPath, FALSE, dwNotifyFilter);
	if (hChange != INVALID_HANDLE_VALUE)
	{
		//Setup the handles to wait on
		std::array<HANDLE, 2> handles{ { hChange, m_MonitoringTerminateEvent } };

		//Sleep until a file change notification wakes this thread or m_TerminateEvent becomes
		//set indicating it's time for the thread to end
		bool bContinue = true;
		while (bContinue)
		{
#pragma warning(suppress: 26472)
			const DWORD dwWait = WaitForMultipleObjects(static_cast<DWORD>(handles.size()), handles.data(), FALSE, INFINITE);
			if ((dwWait - WAIT_OBJECT_0) == 0)
			{
				//Respond to the change notification by posting a user defined message back to the GUI thread
				if (!m_bAutoRefresh)
					bContinue = false;
				else
					PostMessage(WM_TREEUPDATE_CHANGE);

				//Move onto the next notification
				FindNextChangeNotification(hChange);
			}
			else
			{
				//Kill the thread
				bContinue = false;
			}
		}

		//Close the handle we have open
		FindCloseChangeNotification(hChange);
	}
	AppUtils::GetVinaTextApp()->m_bIsSaveDocument = FALSE;
	return 0;
}

bool CFileExplorerCtrl::GetSerialNumber(_In_ const CString& sDrive, _Out_ DWORD& dwSerialNumber) noexcept
{
	return GetVolumeInformation(sDrive, NULL, 0, &dwSerialNumber, NULL, NULL, NULL, 0);
}

bool CFileExplorerCtrl::IsMediaValid(_In_ const CString& sDrive)
{
	//return true if the drive does not support removable media
	const UINT nDriveType = GetDriveType(sDrive);
	if ((nDriveType != DRIVE_REMOVABLE) && (nDriveType != DRIVE_CDROM))
		return true;

	//Return false if the drive is empty (::GetVolumeInformation fails)
	DWORD dwSerialNumber = 0;
	const int nDrive = sDrive.GetAt(0) - _T('A');
	if (GetSerialNumber(sDrive, dwSerialNumber))
#pragma warning(suppress: 26446 26482)
		m_MediaIDs[nDrive] = dwSerialNumber;
	else
	{
#pragma warning(suppress: 26446 26482)
		m_MediaIDs[nDrive] = 0xFFFFFFFF;
		return false;
	}

	//Also return false if the disk's serial number has changed
#pragma warning(suppress: 26446 26482)
	if ((m_MediaIDs[nDrive] != dwSerialNumber) && (m_MediaIDs[nDrive] != 0xFFFFFFFF))
	{
#pragma warning(suppress: 26446 26482)
		m_MediaIDs[nDrive] = 0xFFFFFFFF;
		return false;
	}

	return true;
}

bool CFileExplorerCtrl::EnumNetwork(_In_ HTREEITEM hParent)
{
#pragma warning(suppress: 26490)
	auto pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hParent));
#pragma warning(suppress: 26496)
	AFXASSUME(pItem != NULL);

	//Delegate to the other version of this method
	NETRESOURCE netResource{};
#pragma warning(suppress: 26489)
	netResource.dwScope = pItem->m_dwNetResourceScope;
#pragma warning(suppress: 26489)
	netResource.dwType = pItem->m_dwNetResourceType;
#pragma warning(suppress: 26489)
	netResource.dwDisplayType = pItem->m_dwNetResourceDisplayType;
#pragma warning(suppress: 26489)
	netResource.dwUsage = pItem->m_dwNetResourceUsage;
#pragma warning(suppress: 26489)
	netResource.lpLocalName = pItem->m_sNetResourceLocalName.GetBuffer();
#pragma warning(suppress: 26489)
	netResource.lpRemoteName = pItem->m_sNetResourceRemoteName.GetBuffer();
#pragma warning(suppress: 26489)
	netResource.lpComment = pItem->m_sNetResourceComment.GetBuffer();
#pragma warning(suppress: 26489)
	netResource.lpProvider = pItem->m_sNetResourceProvider.GetBuffer();
	const bool bSuccess = EnumNetwork(&netResource, hParent);
#pragma warning(suppress: 26489)
	pItem->m_sNetResourceProvider.ReleaseBuffer();
#pragma warning(suppress: 26489)
	pItem->m_sNetResourceComment.ReleaseBuffer();
#pragma warning(suppress: 26489)
	pItem->m_sNetResourceRemoteName.ReleaseBuffer();
#pragma warning(suppress: 26489)
	pItem->m_sNetResourceLocalName.ReleaseBuffer();
	return bSuccess;
}

bool CFileExplorerCtrl::EnumNetwork(_In_opt_ NETRESOURCE* pParentNetResource, _In_ HTREEITEM hParent)
{
	//What will be the return value from this function
	bool bGotChildren = false;

	//Setup for the network enumeration
	HANDLE hEnum = NULL;
	DWORD dwResult = WNetOpenEnum(pParentNetResource ? RESOURCE_GLOBALNET : RESOURCE_CONTEXT, m_dwNetworkItemTypes, 0, pParentNetResource, &hEnum);

	//Was the read sucessful
	if (dwResult != NO_ERROR)
	{
		TRACE(_T("CFileExplorerCtrl::EnumNetwork, Cannot enumerate network, Error:%u\n"), dwResult);
		return false;
	}

	//Do the network enumeration
	DWORD cbBuffer = 16384;
	bool bNeedMoreMemory = true;
	bool bSuccess = false;
	std::vector<BYTE> enumBuffer;
	DWORD cEntries = 0;
	while (bNeedMoreMemory && !bSuccess)
	{
		//Allocate the memory and enumerate
		enumBuffer.resize(cbBuffer);
		cEntries = 0xFFFFFFFF;
		dwResult = WNetEnumResource(hEnum, &cEntries, enumBuffer.data(), &cbBuffer);
		if (dwResult == ERROR_MORE_DATA)
			cbBuffer *= 2;
		else if (dwResult == NO_ERROR)
			bSuccess = true;
		else
			bNeedMoreMemory = false;
	}

	//Enumeration successful?
	if (bSuccess)
	{
		//Scan through the results
#pragma warning(suppress: 26490)
		auto lpnrDrv = reinterpret_cast<const NETRESOURCE*>(enumBuffer.data());
		for (DWORD i = 0; i < cEntries; i++)
		{
			//Get the display name for the item
#pragma warning(suppress: 26481 26486)
			CString sDisplayName(lpnrDrv[i].lpRemoteName);
			if (sDisplayName.IsEmpty())
#pragma warning(suppress: 26481 26486)
				sDisplayName = lpnrDrv[i].lpComment;

			//Get the UNC path for the item
			CString sUNCPath;
			if (sDisplayName.Find(_T("\\\\")) == 0)
			{
				sUNCPath = sDisplayName;
				sDisplayName = sDisplayName.Right(sDisplayName.GetLength() - 2);
			}

			//Setup the item data for the new item
#pragma warning(suppress: 26403 26409)
			auto pNewItem = new CFileExplorerCtrlItemInfo;
#pragma warning(suppress: 26481 26486)
			pNewItem->m_sNetResourceLocalName = lpnrDrv[i].lpLocalName;
#pragma warning(suppress: 26481 26486)
			pNewItem->m_sNetResourceRemoteName = lpnrDrv[i].lpRemoteName;
#pragma warning(suppress: 26481 26486)
			pNewItem->m_sNetResourceComment = lpnrDrv[i].lpComment;
#pragma warning(suppress: 26481 26486)
			pNewItem->m_sNetResourceProvider = lpnrDrv[i].lpProvider;
			if (sUNCPath.GetLength())
				pNewItem->m_sFQPath = sUNCPath;
			pNewItem->m_sRelativePath = sDisplayName;
			pNewItem->m_NodeType = CFileExplorerCtrlItemInfo::NodeType::NetworkNode;
#pragma warning(suppress: 26481)
			pNewItem->m_dwNetResourceScope = lpnrDrv[i].dwScope;
#pragma warning(suppress: 26481)
			pNewItem->m_dwNetResourceType = lpnrDrv[i].dwType;
#pragma warning(suppress: 26481)
			pNewItem->m_dwNetResourceDisplayType = lpnrDrv[i].dwDisplayType;
#pragma warning(suppress: 26481)
			pNewItem->m_dwNetResourceUsage = lpnrDrv[i].dwUsage;

			//Display a share and the appropriate icon
#pragma warning(suppress: 26481)
			if (lpnrDrv[i].dwDisplayType == RESOURCEDISPLAYTYPE_SHARE)
			{
				//Display only the share name
				const int nPos = pNewItem->m_sRelativePath.Find(_T('\\'));
				if (nPos >= 0)
					pNewItem->m_sRelativePath = pNewItem->m_sRelativePath.Mid(nPos + 1);

				//Now add the item into the control
#pragma warning(suppress: 26486)
				if (CanDisplayNetworkItem(pNewItem))
					InsertFileItem(hParent, pNewItem, 0, GetIconIndex(pNewItem->m_sFQPath), GetSelIconIndex(pNewItem->m_sFQPath), true);
				else
					delete pNewItem;
			}
#pragma warning(suppress: 26481)
			else if (lpnrDrv[i].dwDisplayType == RESOURCEDISPLAYTYPE_SERVER)
			{
				//Now add the item into the control
#pragma warning(suppress: 26486)
				if (CanDisplayNetworkItem(pNewItem))
				{
					//Note as an optimization we use the cached computer icon indexes for network computers.This helps to
					//speed up the performance of CFileExplorerCtrl when browsing domains or workgroups with a large 
					//number of workstations and servers. You can decide to find the icon indexes at runtime if you define
					//the proprocessor value FILETREECTRL_NO_CACHE_COMPUTER_ICON
#ifndef FILETREECTRL_NO_CACHE_COMPUTER_ICON
					if ((m_nComputerIconIndex != -1) && (m_nSelectedComputerIconIndex != -1))
						InsertFileItem(hParent, pNewItem, 0, m_nComputerIconIndex, m_nSelectedComputerIconIndex, false);
					else
#endif //#ifndef FILETREECTRL_NO_CACHE_COMPUTER_ICON
					{
						CString sServer;
						sServer.Format(_T("\\\\%s"), pNewItem->m_sRelativePath.GetString());
						InsertFileItem(hParent, pNewItem, 0, GetIconIndex(sServer), GetSelIconIndex(sServer), false);
					}
				}
				else
					delete pNewItem;
			}
			else
			{
				//Now add the item into the control
#pragma warning(suppress: 26486)
				if (CanDisplayNetworkItem(pNewItem))
				{
					//Just use the generic Network Neighborhood/Network icons for everything else
					LPITEMIDLIST lpNNPidl = NULL;
					int nIcon = 0xFFFF;
					int nSelIcon = nIcon;
					if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_NETWORK, &lpNNPidl)))
					{
						nIcon = GetIconIndex(lpNNPidl);
						nSelIcon = GetSelIconIndex(lpNNPidl);

						//Free up the pidl now that we are finished with it
						m_Malloc->Free(lpNNPidl);
					}

					InsertFileItem(hParent, pNewItem, 0, nIcon, nSelIcon, false);
				}
				else
					delete pNewItem;
			}
			bGotChildren = true;
		}
	}
	else
		TRACE(_T("CFileExplorerCtrl::EnumNetwork, Cannot complete network drive enumeration, Error:%u\n"), dwResult);

	//Clean up the enumeration handle
	const DWORD dwReturn = WNetCloseEnum(hEnum);
	UNREFERENCED_PARAMETER(dwReturn);

	//Return whether or not we added any items
	return bGotChildren;
}

HTREEITEM CFileExplorerCtrl::DisplayNetworkComputer(_In_ HTREEITEM hParent, _In_ const CString& sComputer)
{
	//Setup the item data for the new item
#pragma warning(suppress: 26403 26409)
	auto pNewItem = new CFileExplorerCtrlItemInfo;
#pragma warning(suppress: 26489)
	pNewItem->m_dwNetResourceScope = RESOURCE_GLOBALNET;
	pNewItem->m_sNetResourceRemoteName = sComputer;
	pNewItem->m_dwNetResourceDisplayType = RESOURCEDISPLAYTYPE_SERVER;
	pNewItem->m_sFQPath = sComputer;
	CString sDisplayName(sComputer);
	if (sDisplayName.Find(_T("\\\\")) == 0)
		sDisplayName = sDisplayName.Right(sDisplayName.GetLength() - 2);
	pNewItem->m_sRelativePath = sDisplayName;
	pNewItem->m_NodeType = CFileExplorerCtrlItemInfo::NodeType::NetworkNode;

	//What will be the return value from this method (assume the worst)
	HTREEITEM hItem = NULL;

	//Now add the item into the control
#pragma warning(suppress: 26486)
	if (CanDisplayNetworkItem(pNewItem))
	{
		//Note as an optimization we use the cached computer icon indexes for network computers. This helps to 
		//speed up speed up the performance of CFileExplorerCtrl when browsing domains or workgroups with a large 
		//number of workstations and servers. You can decide to find the icon indexes at runtime if you define
		//the proprocessor value FILETREECTRL_NO_CACHE_COMPUTER_ICON
#ifndef FILETREECTRL_NO_CACHE_COMPUTER_ICON
		if ((m_nComputerIconIndex != -1) && (m_nSelectedComputerIconIndex != -1))
			hItem = InsertFileItem(hParent, pNewItem, 0, m_nComputerIconIndex, m_nSelectedComputerIconIndex, false);
		else
#endif //#ifndef FILETREECTRL_NO_CACHE_COMPUTER_ICON
		{
			CString sServer;
			sServer.Format(_T("\\\\%s"), pNewItem->m_sRelativePath.GetString());
			hItem = InsertFileItem(hParent, pNewItem, 0, GetIconIndex(sServer), GetSelIconIndex(sServer), false);
		}
	}
	else
		delete pNewItem;

#pragma warning(suppress: 26487)
	return hItem;
}

bool CFileExplorerCtrl::DisplayShares(_In_ HTREEITEM hParent, _In_ const CString& sComputer)
{
	//setup a NETRESOURCE which represents "sComputer"
	NETRESOURCE netResource{};
	netResource.dwScope = RESOURCE_GLOBALNET;
	netResource.dwUsage = RESOURCEUSAGE_CONTAINER;
	netResource.dwDisplayType = RESOURCEDISPLAYTYPE_SERVER;
	CString sLocalComputer(sComputer);
	netResource.lpRemoteName = sLocalComputer.GetBuffer();

	//Call the main EnumNetwork method
	const bool bSuccess = EnumNetwork(&netResource, hParent);
	sLocalComputer.ReleaseBuffer();
	return bSuccess;
}

void CFileExplorerCtrl::DisplayDrives(_In_ HTREEITEM hParent, _In_ bool bUseSetRedraw)
{
	//Display the wait cursor while we are adding the drives to the control
	CWaitCursor c;

	//Speed up the job by turning off redraw
	if (bUseSetRedraw)
		SetRedraw(FALSE);

	//Enumerate the drive letters and add them to the tree control
	const DWORD dwDrives = GetLogicalDrives();
	DWORD dwMask = 1;
	for (int i = 0; i < 32; i++)
	{
		if (dwDrives & dwMask)
		{
			CString sDrive;
			sDrive.Format(_T("%c:\\"), i + _T('A'));

			//check if this drive is one of the types to hide
			if (CanDisplayDrive(sDrive))
			{
#pragma warning(suppress: 26403 26409)
				auto pItem = new CFileExplorerCtrlItemInfo;
				pItem->m_sFQPath = sDrive;
				pItem->m_sRelativePath = sDrive;
				pItem->m_NodeType = CFileExplorerCtrlItemInfo::NodeType::DriveNode;

				//Insert the item into the view
#pragma warning(suppress: 26486)
				InsertFileItem(hParent, pItem, (m_bShowSharedUsingDifferentIcon && IsShared(sDrive)) ? 1 : 0, GetIconIndex(sDrive), GetSelIconIndex(sDrive), true);
			}
		}
		dwMask <<= 1;
	}

	if (bUseSetRedraw)
		SetRedraw(TRUE);
}

CString CFileExplorerCtrl::GetDriveLabel(_In_ const CString& sDrive)
{
	//Let's start with the drive letter
	CString sLabel(sDrive);

	//Try to find the item directory using ParseDisplayName
	if ((m_ShellFolder != NULL) && (m_Malloc != NULL))
	{
		LPITEMIDLIST lpItem = NULL;
		HRESULT hr = m_ShellFolder->ParseDisplayName(NULL, NULL, CT2W(sDrive), NULL, &lpItem, NULL);
		if (SUCCEEDED(hr))
		{
			SHFILEINFO sfi{};
#pragma warning(suppress: 26490)
			if (SHGetFileInfo(reinterpret_cast<LPCTSTR>(lpItem), 0, &sfi, sizeof(sfi), SHGFI_PIDL | SHGFI_DISPLAYNAME))
#pragma warning(suppress: 26485)
				sLabel = sfi.szDisplayName;

			//Free the pidl now that we are finished with it
			m_Malloc->Free(lpItem);
		}
	}

	return sLabel;
}

bool CFileExplorerCtrl::IsShared(_In_ const CString& sPath)
{
	//Defer all the work to the share enumerator class
	return m_SharedEnumerator.IsShared(sPath);
}

bool CFileExplorerCtrl::IsShortcut(_In_ const CString& sFilename)
{
	CString sExt;
	_tsplitpath_s(sFilename, NULL, 0, NULL, 0, NULL, 0, sExt.GetBuffer(_MAX_EXT), _MAX_EXT);
	sExt.ReleaseBuffer();
	return sExt.CompareNoCase(_T(".LNK")) == 0;
}

void CFileExplorerCtrl::DisplayPath(_In_ const CString& sPath, _In_ HTREEITEM hParent, _In_ bool bUseSetRedraw, _In_ bool bDeleteExistingSiblings)
{
	//Display the wait cursor while we are adding the items to the control
	CWaitCursor c;

	//Speed up the job by turning off redraw
	if (bUseSetRedraw)
		SetRedraw(FALSE);

	//Remove all the items currently under hParent if required
	if (bDeleteExistingSiblings)
	{
		HTREEITEM hChild = GetChildItem(hParent);
		while (hChild)
		{
			DeleteItem(hChild);
			hChild = GetChildItem(hParent);
		}
	}

	//Should we display the root folder
	if (m_bShowRootedFolder && PathFileExists(m_sRootFolder) && (hParent == m_hRoot))
	{
#pragma warning(suppress: 26403 26409)
		auto pItem = new CFileExplorerCtrlItemInfo;
		pItem->m_NodeType = CFileExplorerCtrlItemInfo::NodeType::FolderNode;
		pItem->m_sFQPath = m_sRootFolder;
		pItem->m_sRelativePath = m_sRootFolder;
#pragma warning(suppress: 26486)
		m_hRootedFolder = InsertFileItem(m_hRoot, pItem, 0, GetIconIndex(m_sRootFolder), GetSelIconIndex(m_sRootFolder), true);
		Expand(m_hRootedFolder, TVE_EXPAND);
		return;
	}

	//Find all the directories underneath sPath
	int nDirectories = 0;
	CFileFind find1;
	CString sFile;
	if (sPath.GetAt(sPath.GetLength() - 1) == _T('\\'))
		sFile = sPath + _T("*.*");
	else
		sFile = sPath + _T("\\*.*");
	BOOL bFind = find1.FindFile(sFile);
	while (bFind)
	{
		bFind = find1.FindNextFile();
		if (find1.IsDirectory())
		{
			if (CanDisplayFolder(find1))
			{
				++nDirectories;
				CString sTempPath(find1.GetFilePath());

				CString sDrive;
				CString sDir;
				CString sFname;
				CString sExt;
				_tsplitpath_s(sTempPath, sDrive.GetBuffer(_MAX_DRIVE), _MAX_DRIVE, sDir.GetBuffer(_MAX_DIR), _MAX_DIR, sFname.GetBuffer(_MAX_FNAME), _MAX_FNAME, sExt.GetBuffer(_MAX_EXT), _MAX_EXT);
				sExt.ReleaseBuffer();
				sFname.ReleaseBuffer();
				sDir.ReleaseBuffer();
				sDrive.ReleaseBuffer();
				CString sTempPath2;
				_tmakepath_s(sTempPath2.GetBuffer(_MAX_PATH), _MAX_PATH, NULL, NULL, sFname, sExt);
				sTempPath2.ReleaseBuffer();

#pragma warning(suppress: 26400 26409)
				auto pItem = new CFileExplorerCtrlItemInfo;
				pItem->m_sFQPath = sTempPath;
				pItem->m_sRelativePath = sTempPath2;
				pItem->m_NodeType = CFileExplorerCtrlItemInfo::NodeType::FolderNode;

#pragma warning(suppress: 26486)
				InsertFileItem(hParent, pItem, m_bShowSharedUsingDifferentIcon && IsShared(sTempPath) ? 1 : 0, GetIconIndex(sTempPath), GetSelIconIndex(sTempPath), true);
			}
		}
	}

	//find all the files underneath sPath
	int nFiles = 0;
	for (const auto& sMask : m_FileNameMasks)
	{
		CFileFind find2;
		if (sPath.GetAt(sPath.GetLength() - 1) == _T('\\'))
			sFile = sPath + sMask;
		else
			sFile = sPath + _T("\\") + sMask;
		bFind = find2.FindFile(sFile);
		while (bFind)
		{
			bFind = find2.FindNextFile();
			if (!find2.IsDirectory())
			{
				if (CanDisplayFile(find2))
				{
					++nFiles;
					CString sTempPath(find2.GetFilePath());

					CString sFname;
					CString sExt;
					_tsplitpath_s(sTempPath, NULL, 0, NULL, 0, sFname.GetBuffer(_MAX_FNAME), _MAX_FNAME, sExt.GetBuffer(_MAX_EXT), _MAX_EXT);
					sExt.ReleaseBuffer();
					sFname.ReleaseBuffer();
					CString sTempPath2;
					_tmakepath_s(sTempPath2.GetBuffer(_MAX_PATH), _MAX_PATH, NULL, NULL, sFname, sExt);
					sTempPath2.ReleaseBuffer();

					auto pItem = new CFileExplorerCtrlItemInfo;
					pItem->m_sFQPath = sTempPath;
					pItem->m_sRelativePath = sTempPath2;
					pItem->m_NodeType = CFileExplorerCtrlItemInfo::NodeType::FileNode;
					InsertFileItem(hParent, pItem, IsShortcut(sTempPath) ? 2 : 0, GetIconIndex(sTempPath), GetSelIconIndex(sTempPath), true);
				}
			}
		}
	}

	//Now sort the items we just added
	TVSORTCB tvsortcb;
	tvsortcb.hParent = hParent;
	tvsortcb.lpfnCompare = CompareByFilenameNoCase;
	tvsortcb.lParam = 0;
	SortChildrenCB(&tvsortcb);

	//If no items were added then remove the "+" indicator from hParent
	if (nFiles == 0 && nDirectories == 00 && hParent != m_hRoot)
		SetHasPlusButton(hParent, false);

	//Turn back on the redraw flag
	if (bUseSetRedraw)
		SetRedraw(TRUE);
}

void CFileExplorerCtrl::AddPath(const CString & sPath, bool bUseSetRedraw, bool bExpand)
{
	//Check path existed on list added paths or not...
	if (std::find(m_NewAddedFolderData.begin(), m_NewAddedFolderData.end(), sPath) != m_NewAddedFolderData.end())
	{
		return;
	}

	//Display the wait cursor while we are adding the items to the control
	CWaitCursor c;

	//Speed up the job by turning off redraw
	if (bUseSetRedraw)
		SetRedraw(FALSE);

	//Should we display the folder
	if (sPath.GetLength())
	{
#pragma warning(suppress: 26403 26409)
		auto pItem = new CFileExplorerCtrlItemInfo;
		pItem->m_NodeType = CFileExplorerCtrlItemInfo::NodeType::FolderNode;
		pItem->m_sFQPath = sPath;
		pItem->m_sRelativePath = sPath;
#pragma warning(suppress: 26486)
		HTREEITEM hNewRoot = NULL; // new folder will be a saperated node...
		HTREEITEM hNewFolder = InsertFileItem(hNewRoot, pItem, 0, GetIconIndex(sPath), GetSelIconIndex(sPath), true);
		if (bExpand)
		{
			Expand(hNewFolder, TVE_EXPAND);
		}
		if (hNewFolder)
		{
			m_NewAddedFolderData.push_back(sPath);
		}
		EnsureVisibleCenter(hNewFolder);
		return;
	}
}

void CFileExplorerCtrl::DoExpand(_In_ HTREEITEM hItem)
{
#pragma warning(suppress: 26490)
	const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hItem));
#pragma warning(suppress: 26496)
	AFXASSUME(pItem != NULL);

	if (hItem == m_hRoot && m_sRootFolder.IsEmpty())
	{
		DisplayRootItems();

		//Also show all items underneath the desktop
		if (m_sDesktopPath.GetLength())
			DisplayPath(m_sDesktopPath, m_hRoot, false, false);
	}
	else if (hItem == m_hMyComputerRoot)
	{
		//Display the wait cursor as this may take some time
		CWaitCursor wait;

		//Enumerate the local drive letters
		DisplayDrives(m_hMyComputerRoot, false);
	}
	else if (hItem == m_hNetworkRoot)
	{
		//Display the wait cursor as this may take some time
		CWaitCursor wait;

		//Enumerate the network resources
		EnumNetwork(NULL, hItem);
	}
#pragma warning(suppress: 26489)
	else if (pItem->m_dwNetResourceScope && !IsFolder(pItem->m_sFQPath))
	{
		//Display the wait cursor as this may take some time
		CWaitCursor wait;

		//Enumerate the network resources
		EnumNetwork(hItem);
	}
#pragma warning(suppress: 26489)
	else if (pItem->m_sFQPath.GetLength())
	{
#pragma warning(suppress: 26489)
		if (IsMediaValid(pItem->m_sFQPath))
		{
			//Delete the item if the path is no longer valid
#pragma warning(suppress: 26489)
			if (IsFolder(pItem->m_sFQPath))
			{
				//Add the new items to the tree if it does not have any child items already
				if (!GetChildItem(hItem))
#pragma warning(suppress: 26489)
					DisplayPath(pItem->m_sFQPath, hItem);
			}
			else
			{
				//Before we delete it see if we are the only child item
				HTREEITEM hParent = GetParentItem(hItem);

				//Delete the item
				DeleteItem(hItem);

				//Remove all the child items from the parent
				SetHasPlusButton(hParent, false);
			}
		}
		else if (hItem != m_hRoot)
		{
			//Display the wait cursor as this may take some time
			CWaitCursor wait;

			//Collapse the drive node and remove all the child items from it
			Expand(hItem, TVE_COLLAPSE | TVE_COLLAPSERESET);
			SetHasPlusButton(hItem, false);
		}
	}
}

#pragma warning(suppress: 26429)
BOOL CFileExplorerCtrl::OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult)
{
	CLockCtrlRedraw locker(this);
#pragma warning(suppress: 26490)
	auto pNMTreeView = reinterpret_cast<NMTREEVIEW*>(pNMHDR);
#pragma warning(suppress: 26496)
	AFXASSUME(pNMTreeView != NULL);

	if (pNMTreeView->action == TVE_EXPAND)
	{
		const bool bHasPlus = HasPlusButton(pNMTreeView->itemNew.hItem);
		const bool bHasChildren = (GetChildItem(pNMTreeView->itemNew.hItem) != NULL);

		if (bHasPlus && !bHasChildren)
			DoExpand(pNMTreeView->itemNew.hItem);
	}
	else if (pNMTreeView->action == TVE_COLLAPSE)
	{
#pragma warning(suppress: 26489 26490)
		const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(pNMTreeView->itemNew.hItem));
#pragma warning(suppress: 26496)
		AFXASSUME(pItem != NULL);

		//Display the wait cursor as this may take some time
		CWaitCursor wait;

		//Collapse the node and remove all the child items from it
		const bool bHasChildren = HasPlusButton(pNMTreeView->itemNew.hItem);
		Expand(pNMTreeView->itemNew.hItem, TVE_COLLAPSE | TVE_COLLAPSERESET);

		//Never uppdate the child indicator for a network node which is not a share
		bool bUpdateChildIndicator = true;
#pragma warning(suppress: 26489)
		if (pItem->m_NodeType == CFileExplorerCtrlItemInfo::NodeType::NetworkNode)
		{
#pragma warning(suppress: 26489)
			bUpdateChildIndicator = (pItem->m_dwNetResourceDisplayType == RESOURCEDISPLAYTYPE_SHARE);
		}

		if (bUpdateChildIndicator)
			SetHasPlusButton(pNMTreeView->itemNew.hItem, bHasChildren);
	}

	*pResult = 0;

	UpdateNavigationPathData();

	return FALSE; //Allow the message to be reflected again
}

HTREEITEM CFileExplorerCtrl::PathToItem(_In_ const CString& sPath) const
{
	CString sSearch(sPath);
	sSearch.MakeUpper();
	int nSearchLength = sSearch.GetLength();
	if (nSearchLength == 0)
		return NULL;

	//Remove initial part of path if the root folder is setup
	const int nRootLength = m_sRootFolder.GetLength();
	CString sRootFolder(m_sRootFolder);
	sRootFolder.MakeUpper();
	if (nRootLength)
	{
		if (sSearch.Find(sRootFolder) != 0)
		{
			TRACE(_T("CFileExplorerCtrl::PathToItem, Could not find the path %s as the root has been configured as %s\n"), sPath.GetString(), m_sRootFolder.GetString());
			return NULL;
		}
		sSearch = sSearch.Right(nSearchLength - 1 - nRootLength);
		nSearchLength = sSearch.GetLength();
	}

	//Remove trailing "\" from the path
	if (nSearchLength > 3 && sSearch.GetAt(nSearchLength - 1) == _T('\\'))
		sSearch = sSearch.Left(nSearchLength - 1);

	if (sSearch.IsEmpty())
	{
		if (m_hRootedFolder)
			return m_hRootedFolder;
		else
			return NULL;
	}

	HTREEITEM hItemFound = m_hRoot;
	if (nRootLength && m_hRootedFolder)
		hItemFound = m_hRootedFolder;
	bool bDriveMatch = sRootFolder.IsEmpty();
	const bool bNetworkMatch = m_bShowNetwork && ((sSearch.GetLength() > 2) && sSearch.Find(_T("\\\\")) == 0);
	if (bNetworkMatch)
	{
		bDriveMatch = false;
		hItemFound = FindServersNode(m_hNetworkRoot);
		sSearch = sSearch.Right(sSearch.GetLength() - 2);
	}
	if (bDriveMatch)
	{
		CString sMyDocumentsPath(m_sMyDocumentsPath);
		sMyDocumentsPath.MakeUpper();
		CString sMyDesktopPath(m_sDesktopPath);
		sMyDesktopPath.MakeUpper();
		CString sCurrentUserFolderPath(m_sCurrentUserFolderPath);
		sCurrentUserFolderPath.MakeUpper();

		if (m_hDesktop && sSearch.Find(sMyDesktopPath) == 0)
		{
			hItemFound = m_hDesktop;

			sSearch = sSearch.Right(sSearch.GetLength() - sMyDesktopPath.GetLength() - 1);
			bDriveMatch = false;
		}
		else if (m_hCurrentUserFolderRoot && sSearch.Find(sCurrentUserFolderPath) == 0)
		{
			hItemFound = m_hCurrentUserFolderRoot;

			sSearch = sSearch.Right(sSearch.GetLength() - sCurrentUserFolderPath.GetLength() - 1);
			bDriveMatch = false;
		}
		else if (m_hMyDocumentsRoot && sSearch.Find(sMyDocumentsPath) == 0)
		{
			hItemFound = m_hMyDocumentsRoot;

			sSearch = sSearch.Right(sSearch.GetLength() - sMyDocumentsPath.GetLength() - 1);
			bDriveMatch = false;
		}
		else if (m_hMyComputerRoot)
		{
			hItemFound = m_hMyComputerRoot;
		}
	}

	int nFound = sSearch.Find(_T('\\'));
	while (nFound != -1)
	{
		CString sMatch;
		if (bDriveMatch)
		{
			sMatch = sSearch.Left(nFound + 1);
			bDriveMatch = false;
		}
		else
			sMatch = sSearch.Left(nFound);
		hItemFound = FindSibling(hItemFound, sMatch);
		if (hItemFound == NULL)
			break;

		sSearch = sSearch.Right(sSearch.GetLength() - nFound - 1);
		nFound = sSearch.Find(_T('\\'));
	};

	//The last item
	if (hItemFound)
	{
		if (sSearch.GetLength())
			hItemFound = FindSibling(hItemFound, sSearch);
	}

	return hItemFound;
}

CString CFileExplorerCtrl::ItemToPath(_In_ HTREEITEM hItem) const
{
	CString sPath;
	if (hItem)
	{
#pragma warning(suppress: 26490)
		const CFileExplorerCtrlItemInfo* pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(GetItemData(hItem));
#pragma warning(suppress: 26496)
		AFXASSUME(pItem != NULL);
#pragma warning(suppress: 26489)
		sPath = pItem->m_sFQPath;
	}
	return sPath;
}

#pragma warning(suppress: 26429)
BOOL CFileExplorerCtrl::OnRclick(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
	//Work out the position of where the context menu should be
	const CPoint p(GetCurrentMessage()->pt);
#pragma warning(suppress: 26496)
	CPoint pt(p);
	ScreenToClient(&pt);
	Select(HitTest(pt), TVGN_CARET);
	OnContextMenu(NULL, p);

	*pResult = 0;

	return FALSE; //Allow the message to be reflected again
}

//Copied from CFrameWnd::OnInitMenuPopup to provide OnUpdateCmdUI functionality in the tree control
#pragma warning(suppress: 26434)
void CFileExplorerCtrl::OnInitMenuPopup(CMenu* pMenu, UINT /*nIndex*/, BOOL bSysMenu)
{
	//AfxCancelModes(m_hWnd);

	if (bSysMenu)
		return; //don't support system menu

#pragma warning(suppress: 26496)
	AFXASSUME(pMenu != NULL);
	//check the enabled state of various menu items

	CCmdUI state;
	state.m_pMenu = pMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	//determine if menu is popup in top-level menu and set m_pOther to
	// it if so (m_pParentMenu == NULL indicates that it is secondary popup)
	HMENU hParentMenu = NULL;
	if (AfxGetThreadState()->m_hTrackingMenu == pMenu->m_hMenu)
		state.m_pParentMenu = pMenu; //parent == child for tracking popup
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL) //NOLINT(clang-analyzer-deadcode.DeadStores)
	{
		CWnd* pParent = GetTopLevelParent();
		//child windows don't have menus -- need to go to the top!
#pragma warning(suppress: 26486)
		if (pParent != NULL && (hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			const int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pMenu->m_hMenu)
				{
					//when popup is found, m_pParentMenu is containing menu
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}

	state.m_nIndexMax = pMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax; state.m_nIndex++)
	{
		state.m_nID = pMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; //menu separator or invalid cmd - ignore it

		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
#pragma warning(suppress: 26472)
		if (state.m_nID == static_cast<UINT>(-1))
		{
			//possibly a popup menu, route to first item of that popup
			state.m_pSubMenu = pMenu->GetSubMenu(state.m_nIndex);
#pragma warning(suppress: 26472)
			if ((state.m_pSubMenu == NULL) ||
				((state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0) ||
				(state.m_nID == static_cast<UINT>(-1)))
			{
				continue; //first item of popup can't be routed to
			}
			state.DoUpdate(this, FALSE); //popups are never auto disabled
		}
		else
		{
			//normal menu item
			//Auto enable/disable if frame window has 'm_bAutoMenuEnable'
			//   set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			//state.DoUpdate(this, m_bAutoMenuEnable && state.m_nID < 0xF000);
			state.DoUpdate(this, TRUE && state.m_nID < 0xF000);
		}

		//adjust for menu deletions and additions
		const UINT nCount = pMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while ((state.m_nIndex < nCount) && (pMenu->GetMenuItemID(state.m_nIndex) == state.m_nID))
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
}

#ifndef FILETREECTRL_NO_RESOURCES
#pragma warning(suppress: 26429)
BOOL CFileExplorerCtrl::OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult)
{
#pragma warning(suppress: 26490)
	auto pNMTreeView = reinterpret_cast<NMTREEVIEW*>(pNMHDR);
#pragma warning(suppress: 26496)
	AFXASSUME(pNMTreeView != NULL);

	*pResult = 0;

	if (!m_bAllowDragDrop || !IsDropSource(pNMTreeView->itemNew.hItem)) //NOLINT(clang-analyzer-core.CallAndMessage)
		return FALSE; //Allow the message to be reflected again

	m_pilDrag = CreateDragImage(pNMTreeView->itemNew.hItem);
	if (!m_pilDrag)
		return FALSE; //Allow the message to be reflected again

	m_hItemDrag = pNMTreeView->itemNew.hItem;
	m_hItemDrop = NULL;

	//Calculate the offset to the hotspot
	CPoint offsetPt(8, 8); //Initialize a default offset

	const CPoint dragPt(pNMTreeView->ptDrag); //Get the Drag point
	UINT nHitFlags = 0;
	HTREEITEM hHit = HitTest(dragPt, &nHitFlags);
	if (hHit != NULL)
	{
		//The drag point has Hit an item in the tree
		CRect itemRect;
		if (GetItemRect(hHit, &itemRect, FALSE))
		{
			//Count indent levels
			HTREEITEM hParent = hHit;
			int nIndentCnt = 0;
			while (hParent != NULL)
			{
				hParent = GetParentItem(hParent);
				nIndentCnt++;
			}

			if (!(GetStyle() & TVS_LINESATROOT))
				nIndentCnt--;

			//Calculate the new offset
			offsetPt.y = dragPt.y - itemRect.top;
			offsetPt.x = dragPt.x - (nIndentCnt * GetIndent()) + GetScrollPos(SB_HORZ);
		}
	}

	//Begin the dragging
	m_pilDrag->BeginDrag(0, offsetPt);
	CPoint pt(pNMTreeView->ptDrag);
	ClientToScreen(&pt);
	m_pilDrag->DragEnter(NULL, pt);
	SetCapture();

	//Create the timer which is used for auto expansion
	m_nTimerID = SetTimer(FILETREECTRL_TIMERID, 300, NULL);

	return FALSE; //Allow the message to be reflected again
}

#pragma warning(suppress: 26434)
void CFileExplorerCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	if (IsDragging())
	{
		CRect clientRect;
		GetClientRect(&clientRect);

		//Draw the drag
		CPoint pt(point);
		ClientToScreen(&pt);
		CImageList::DragMove(pt);

		//Only select the drop item if we are in the client area
		HTREEITEM hItem = NULL;
		if (clientRect.PtInRect(point))
		{
			UINT flags = 0;
			hItem = HitTest(point, &flags);
			if (m_hItemDrop != hItem)
			{
				CImageList::DragShowNolock(FALSE);
				SelectDropTarget(hItem);
				m_hItemDrop = hItem;
				CImageList::DragShowNolock(TRUE);
			}
		}
		else //open select the drop item if we are out the client area
		{
			CString strDragPath = ItemToPath(m_hItemDrag);
			if (PathFileExists(strDragPath) && !PathUtils::IsDirectory(strDragPath))
			{
				AppUtils::CreateDocumentFromFile(strDragPath);
				EndDragging(true);
			}
		}

		if (hItem)
			hItem = GetDropTarget(hItem);

		//Change the cursor to give feedback
		if (hItem)
		{
			if ((GetKeyState(VK_CONTROL) & 0x8000))
				SetCursor(m_DropCopyCursor);
			else
				SetCursor(m_DropMoveCursor);
		}
		else
		{
			if ((GetKeyState(VK_CONTROL) & 0x8000))
				SetCursor(m_NoDropCopyCursor);
			else
				SetCursor(m_NoDropMoveCursor);
		}
	}
	__super::OnMouseMove(nFlags, point);
}

bool CFileExplorerCtrl::IsDropSource(_In_ HTREEITEM hItem)
{
	return IsFile(hItem) || IsFolder(hItem);
}

HTREEITEM CFileExplorerCtrl::GetDropTarget(_In_ HTREEITEM hItem)
{
	if (!IsFile(hItem) && (hItem != m_hItemDrag) && (hItem != GetParentItem(m_hItemDrag)) && (IsFolder(hItem) || (IsNetworkShare(hItem))))
	{
		HTREEITEM hParent = hItem;
		while ((hParent = GetParentItem(hParent)) != NULL)
		{
			if (hParent == m_hItemDrag)
				return NULL;
		}
		return hItem;
	}
	return NULL;
}

bool CFileExplorerCtrl::IsDragging() noexcept
{
	return (m_pilDrag != NULL);
}

#pragma warning(suppress: 26434)
void CFileExplorerCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect clientRect;
	GetClientRect(&clientRect);
	if (clientRect.PtInRect(point))
		EndDragging(false);
	else
		EndDragging(true);
	__super::OnLButtonUp(nFlags, point);
}

void CFileExplorerCtrl::EndDragging(_In_ bool bCancel)
{
	if (IsDragging())
	{
		//Kill the timer that is being used
		KillTimer(m_nTimerID);
		m_nTimerID = 0;

		CImageList::DragLeave(this);
		CImageList::EndDrag();
		ReleaseCapture();

		//Delete the drag image list
		delete m_pilDrag;
		m_pilDrag = NULL;

		//Remove drop target highlighting
		SelectDropTarget(NULL);

		//Find out where we are dropping
		m_hItemDrop = GetDropTarget(m_hItemDrop);
		if (m_hItemDrop == NULL)
			return;

		if (!bCancel)
		{
			//Also need to make the change on disk
			SHFILEOPSTRUCT shfo{};
			shfo.hwnd = GetSafeHwnd();

			if ((GetKeyState(VK_CONTROL) & 0x8000))
				shfo.wFunc = FO_COPY;
			else
				shfo.wFunc = FO_MOVE;

			shfo.fFlags = FOF_SILENT | FOF_NOCONFIRMMKDIR;
			//Undo is not allowed if the SHIFT key is held down
			if (!(GetKeyState(VK_SHIFT) & 0x8000))
				shfo.fFlags |= FOF_ALLOWUNDO;

			CString sFromPath(ItemToPath(m_hItemDrag));
			const size_t nFromLength = sFromPath.GetLength();
			std::vector<TCHAR> sTempFrom;
			sTempFrom.resize(nFromLength + 2);
			_tcscpy_s(sTempFrom.data(), nFromLength + 2, sFromPath);
#pragma warning(suppress: 26446)
			sTempFrom[nFromLength + 1] = _T('\0');
			shfo.pFrom = sTempFrom.data();

			CString sToPath(ItemToPath(m_hItemDrop));
			const size_t nToLength = sToPath.GetLength();
			std::vector<TCHAR> sTempTo;
			sTempTo.resize(nToLength + 2);
			_tcscpy_s(sTempTo.data(), nToLength + 2, sToPath);
#pragma warning(suppress: 26446)
			sTempTo[nToLength + 1] = _T('\0');
			shfo.pTo = sTempTo.data();

			//Kill the monitoring thread if necessary
			const bool bMonitoringThread = (m_pMonitoringThread != NULL);
			CString sMonitoringPath(m_sMonitoringPath);
			if (bMonitoringThread)
				KillMonitoringThread();

			//Let the shell perform the actual deletion
			const bool bSuccess = ((SHFileOperation(&shfo) == 0) && (shfo.fAnyOperationsAborted == FALSE));

			//Recreate the monitoring thread if necessary
			if (bMonitoringThread)
				CreateMonitoringThread(m_sMonitoringPath);

			if (bSuccess)
			{
				//Only copy the item in the tree if there is not an item with the same
				//text under m_hItemDrop
				CString sText(GetItemText(m_hItemDrag));
				if (!HasChildWithText(m_hItemDrop, sText))
				{
					ASSERT(m_hItemDrop != TVI_ROOT);
					//Update the children indicator for the folder we just dropped into
					SetHasPlusButton(m_hItemDrop, true);
				}

				if (shfo.wFunc == FO_MOVE)
				{
					//Get the parent of the item we moved prior to deleting it
					HTREEITEM hParent = GetParentItem(m_hItemDrag);

					//Delete the item we just moved
					DeleteItem(m_hItemDrag);

					//Update the children indicator for the item we just dragged from
					const bool bHasChildren = (GetChildItem(hParent) != NULL);
					if (hParent && !bHasChildren)
						SetHasPlusButton(hParent, false);
				}

				OnRefresh();

				//Select new item after refesh tree
				Expand(PathToItem(sToPath), TVE_EXPAND);
				CString sNewItemFullPath = sToPath + _T("\\") + sText;
				HTREEITEM hNewItem = PathToItem(sNewItemFullPath);
				if (hNewItem)
				{
					EnsureVisibleCenter(hNewItem);
					SelectItem(hNewItem);
				}
			}
		}
	}
}

#pragma warning(suppress: 26434)
void CFileExplorerCtrl::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent != m_nTimerID)
	{
		//Let the base class do its thing
		__super::OnTimer(nIDEvent);
		return;
	}

	//Show the dragging effect
	CPoint pt;
	GetCursorPos(&pt);
	RECT rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	CImageList::DragMove(pt);

	HTREEITEM hFirstItem = GetFirstVisibleItem();
	CRect ItemRect;
	GetItemRect(hFirstItem, &ItemRect, FALSE);
	if (hFirstItem != GetRootItem() && pt.y < (rect.top + (ItemRect.Height() * 2)) && pt.y > rect.top)
	{
		//we need to scroll up
		CImageList::DragShowNolock(FALSE);
		SendMessage(WM_VSCROLL, SB_LINEUP);
		EnsureVisibleCenter(hFirstItem);
		SelectDropTarget(hFirstItem);
		m_hItemDrop = hFirstItem;
		CImageList::DragShowNolock(TRUE);
	}
	else if (pt.y > (rect.bottom - (ItemRect.Height() * 2)) && pt.y < rect.bottom)
	{
		//we need to scroll down
		CImageList::DragShowNolock(FALSE);
		SendMessage(WM_VSCROLL, SB_LINEDOWN);
		HTREEITEM hLastItem = hFirstItem;
		const int nCount = GetVisibleCount();
		for (int i = 0; i < (nCount - 1); i++)
			hLastItem = GetNextVisibleItem(hLastItem);
		SelectDropTarget(hLastItem);
		EnsureVisibleCenter(hLastItem);
		m_hItemDrop = hLastItem;
		CImageList::DragShowNolock(TRUE);
	}

	//Expand the item if the timer ticks has expired
	if (m_TimerTicks == FILETREECTRL_TIMERTICK_FOR_EXPANSION)
	{
		m_TimerTicks = 0;
		Expand(m_hItemDrop, TVE_EXPAND);
	}

	//Expand the selected item if it is collapsed and
	//the timeout has occurred
	TVITEM tvItem{};
	tvItem.hItem = m_hItemDrop;
	tvItem.mask = TVIF_HANDLE | TVIF_CHILDREN | TVIF_STATE;
	tvItem.stateMask = TVIS_EXPANDED;
#pragma warning(suppress: 26486)
	GetItem(&tvItem);
	if (tvItem.cChildren && ((tvItem.state & TVIS_EXPANDED) == 0))
		m_TimerTicks++;
}
#endif //#ifndef FILETREECTRL_NO_RESOURCES

bool CFileExplorerCtrl::HasChildWithText(_In_ HTREEITEM hParent, _In_ const CString& sText)
{
	HTREEITEM hChild = GetChildItem(hParent);
	while (hChild)
	{
		CString sItemText(GetItemText(hChild));
		if (sItemText.CompareNoCase(sText) == 0)
			return true;
		hChild = GetNextSiblingItem(hChild);
	}
	return false;
}

HTREEITEM CFileExplorerCtrl::CopyItem(_In_ HTREEITEM hItem, _In_ HTREEITEM hNewParent, _In_ HTREEITEM hAfter)
{
	//Get the details of the item to copy
	TVINSERTSTRUCT tvstruct;
	tvstruct.item.hItem = hItem;
	tvstruct.item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	GetItem(&tvstruct.item);
	CString sText(GetItemText(hItem));
	tvstruct.item.cchTextMax = sText.GetLength();
	tvstruct.item.pszText = sText.GetBuffer(tvstruct.item.cchTextMax);

	//Make a copy of the item data we are carying around
#pragma warning(suppress: 26490 26429)
	const CFileExplorerCtrlItemInfo* pOldInfo = reinterpret_cast<CFileExplorerCtrlItemInfo*>(tvstruct.item.lParam);
#pragma warning(suppress: 26490 26409 26489)
	tvstruct.item.lParam = reinterpret_cast<LPARAM>(new CFileExplorerCtrlItemInfo(*pOldInfo));

	//Insert the item at the proper location
	tvstruct.hParent = hNewParent;
	tvstruct.hInsertAfter = hAfter;
	tvstruct.item.mask |= TVIF_TEXT;
	HTREEITEM hNewItem = InsertItem(&tvstruct);

	//Don't forget to release the CString buffer
	sText.ReleaseBuffer();

#pragma warning(suppress: 26487)
	return hNewItem;
}

HTREEITEM CFileExplorerCtrl::CopyBranch(_In_ HTREEITEM hBranch, _In_ HTREEITEM hNewParent, _In_ HTREEITEM hAfter)
{
	HTREEITEM hNewItem = CopyItem(hBranch, hNewParent, hAfter);
	HTREEITEM hChild = GetChildItem(hBranch);
	while (hChild != NULL)
	{
		//recursively transfer all the items
		CopyBranch(hChild, hNewItem);
		hChild = GetNextSiblingItem(hChild);
	}
	return hNewItem;
}

void CFileExplorerCtrl::OnBack()
{
	const auto nSize = m_PrevItems.size();
	if (nSize)
	{
		HTREEITEM hOldItem = GetSelectedItem();
#pragma warning(suppress: 26446)
		HTREEITEM hNewItem = m_PrevItems[nSize - 1];

		//Select the previous item
		m_bUpdatingHistorySelection = true;
		m_PrevItems.erase(m_PrevItems.begin() + nSize - 1);
		ASSERT(hNewItem != TVI_ROOT);
#pragma warning(suppress: 26486)
		SelectItem(hNewItem);
		EnsureVisibleCenter(hNewItem);
		m_bUpdatingHistorySelection = false;

		//Add the old item to the next stack
		m_NextItems.push_back(hOldItem);
	}
}

#pragma warning(suppress: 26429)
void CFileExplorerCtrl::OnUpdateBack(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->Enable(CanGoBack());
}

void CFileExplorerCtrl::OnForward()
{
	const auto nSize = m_NextItems.size();
	if (nSize)
	{
		HTREEITEM hOldItem = GetSelectedItem();
#pragma warning(suppress: 26446)
		HTREEITEM hNewItem = m_NextItems[nSize - 1];

		//Select the previous item
		m_bUpdatingHistorySelection = true;
		m_NextItems.erase(m_NextItems.begin() + nSize - 1);
		ASSERT(hNewItem != TVI_ROOT);
#pragma warning(suppress: 26486)
		SelectItem(hNewItem);
		EnsureVisibleCenter(hNewItem);
		m_bUpdatingHistorySelection = false;

		//Add the old item to the prev stack
		m_PrevItems.push_back(hOldItem);
	}
}

#pragma warning(suppress: 26429)
void CFileExplorerCtrl::OnUpdateForward(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
	pCmdUI->Enable(CanGoForward());
}

void CFileExplorerCtrl::OnCreateDocumentFromFile()
{
	Open(GetSelectedItem(), FALSE);
}

void CFileExplorerCtrl::OnOpenAsRawFormat()
{
	bool bSuccess = false;
	HTREEITEM hItem = GetSelectedItem();
	if (m_bAllowOpen && hItem)
	{
		CString strFile(ItemToPath(hItem));
		if (!PathFileExists(strFile)) return;
		auto pDoc = dynamic_cast<CBaseDoc*>(AppUtils::GetExistedDocument(strFile));
		if (pDoc)
		{
			AppUtils::SetActiveDocument(pDoc);
			pDoc->SetPreviewMode(FALSE);
			return;
		}
		AppUtils::GetVinaTextApp()->m_pEditorDocTemplate->OpenNewDocument(strFile, TRUE, TRUE);
		SetFocus();
	}
}

void CFileExplorerCtrl::OnOpenAllFileByVinaText()
{
	CString strFolder(ItemToPath(GetSelectedItem()));
	if (PathFileExists(strFolder))
	{
		std::vector<CString> vecFileName;
		PathUtils::GetAllFilesFromFolder(strFolder, vecFileName);
		int nCount = 0;
		if (vecFileName.size() > AppSettingMgr.m_nExplorerExpandLimitFileOpen)
		{
			if (IDYES != AfxMessageBoxFormat(MB_YESNO | MB_ICONWARNING, 
				_T("[Warning] This folder contains more than %d files, do you still want to open all?"), int(vecFileName.size())))
			{
				return;
			}
			int nMaxAllowFile = AppSettingMgr.m_nExplorerExpandLimitFileOpen + 10;
			if (vecFileName.size() > nMaxAllowFile)
			{
				AfxMessageBoxFormat(MB_OK | MB_ICONWARNING,
					_T("[Error] Can not open more than %d files, please increase limited number in setting!"), nMaxAllowFile);
				return;
			}
		}
		for (auto const& file : vecFileName)
		{
			if (!PathUtils::IsBinaryFile(file, FILE_BINNARY | FILE_OFFICE) && !PathUtils::IsDirectory(file))
			{
				nCount++;
				AppUtils::CreateDocumentFromFile(file);
				SetFocus();
			}
		}
		if (nCount == 0)
		{
			AfxMessageBox(_T("[Error] This folder contains binary file only!"));
		}
	}
}

void CFileExplorerCtrl::OnHostFileExplorer()
{
	CString strFolderPath = GetSelectedPath();
	if (PathFileExists(strFolderPath))
	{
		if (!PathUtils::IsDirectory(strFolderPath))
		{
			strFolderPath = PathUtils::GetContainerPath(strFolderPath);
		}
		HostApplicaton(HOST_APP_TYPE::FILE_EXPLORER, NULL, strFolderPath);
	}
}

void CFileExplorerCtrl::OnOpenFileContainer()
{
	CString strFilePath = GetSelectedPath();
	if (PathFileExists(strFilePath))
	{
		CString strFolderPath = PathUtils::GetContainerPath(strFilePath);
		if (!PathFileExists(strFolderPath)) return;
		PIDLIST_ABSOLUTE pidl;
		if (SUCCEEDED(SHParseDisplayName(strFolderPath, 0, &pidl, 0, 0)))
		{
			ITEMIDLIST *pidl = ILCreateFromPath(strFilePath);
			SHOpenFolderAndSelectItems(pidl, 0, 0, 0);
			ILFree(pidl);
		}
	}
	else
	{
		CString strMessage = _T("> [Explorer Window] [Search Path Error] selected path does not exist or is a special path.");
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strMessage, BasicColors::orange);
	}
}

void CFileExplorerCtrl::OnLoadAutoCompleteDataset()
{
	auto pDoc = AppUtils::GetMDIActiveDocument();
	if (pDoc)
	{
		if (pDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
		{
			CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(pDoc);
			if (pEditorDoc)
			{
				CString strPath = GetSelectedPath();
				if (PathFileExists(strPath))
				{
					if (PathUtils::IsDirectory(strPath))
					{
						pEditorDoc->GetEditorView()->AddAutoCompleteFromFolder(strPath);
					}
					else
					{
						pEditorDoc->GetEditorView()->AddAutoCompleteFromFile(strPath);
					}
				}
			}
		}
	}
}

void CFileExplorerCtrl::OnDeleteFileByExtension()
{
	CDeleteFileExtensionDlg dlg;
	dlg.m_sPath = GetSelectedPath();
	if (!PathUtils::IsDirectory(dlg.m_sPath))
	{
		dlg.m_sPath = PathUtils::GetContainerPath(dlg.m_sPath);
	}
	dlg.m_sExt = _T("*.*");
	if (dlg.DoModal() == IDOK)
	{
		int nCurPos = 0;
		CString sToken(dlg.m_sExt.Tokenize(_T(",;"), nCurPos));
		while (sToken != _T(""))
		{
			sToken.Trim();
			PathUtils::DeleteFilesInFolder(this->GetSafeHwnd(), dlg.m_sPath, sToken);
			sToken = dlg.m_sExt.Tokenize(_T(",;"), nCurPos);
		}
	}
	SetFocus();
}

void CFileExplorerCtrl::OnEditWithMSPaint()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		CString sPath(ItemToPath(hItem));
		if (PathFileExists(sPath))
		{
			if (PathUtils::IsImageFile(sPath))
			{
				HostApplicaton(HOST_APP_TYPE::MS_PAINT, L"mspaint.exe", sPath, TRUE, FALSE);
			}
		}
	}
}

void CFileExplorerCtrl::SetMaxHistory(_In_ size_t nMaxHistory)
{
	m_nMaxHistory = nMaxHistory;

	//Shrink the prev array if necessary
	auto nCurItems = m_PrevItems.size();
	if (nCurItems > m_nMaxHistory)
		m_PrevItems.erase(m_PrevItems.begin() + m_nMaxHistory, m_PrevItems.end());

	//Shrink the next array if necessary
	nCurItems = m_NextItems.size();
	if (nCurItems > m_nMaxHistory)
		m_NextItems.erase(m_NextItems.begin() + m_nMaxHistory, m_NextItems.end());
}

size_t CFileExplorerCtrl::GetBackSize() const noexcept
{
	return m_PrevItems.size();
}

CString CFileExplorerCtrl::GetBackItemText(_In_ size_t nBack) const
{
	//Validate our parameters
	ASSERT(nBack < GetBackSize());

#pragma warning(suppress: 26446)
	HTREEITEM hItem = m_PrevItems[nBack];
	return ItemToPath(hItem);
}

size_t CFileExplorerCtrl::GetForwardSize() const noexcept
{
	return m_NextItems.size();
}

CString CFileExplorerCtrl::GetForwardItemText(_In_ size_t nForward) const
{
	//Validate our parameters
	ASSERT(nForward < GetForwardSize());

#pragma warning(suppress: 26446)
	HTREEITEM hItem = m_NextItems[nForward];
	return ItemToPath(hItem);
}

void CFileExplorerCtrl::KillMonitoringThread()
{
	if (m_pMonitoringThread != NULL)
	{
		//Kill all the running file change notification thread
		TRACE(_T("CFileExplorerCtrl::KillNotificationThread, Killing monitoring thread for %s\n"), m_sMonitoringPath.GetString());

		//Signal the worker thread to exit and wait for it to return
		m_MonitoringTerminateEvent.SetEvent();
		WaitForSingleObject(m_pMonitoringThread->m_hThread, INFINITE);
		delete m_pMonitoringThread;
		m_pMonitoringThread = NULL;
	}
}

#pragma warning(suppress: 26434)
void CFileExplorerCtrl::OnDestroy()
{
	//Kill the monitoring thread
	KillMonitoringThread();

	//Remove all the items from the tree control. This ensures that all the heap memory we have used in the item datas is freed
	Clear();

	
	__super::OnDestroy();
}

LRESULT CFileExplorerCtrl::OnChange(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	if (m_bAutoRefresh && AppUtils::GetVinaTextApp()->m_bIsSaveDocument == FALSE)
	{
		//Trace message which is helpful for diagnosing autorefresh
		TRACE(_T("CFileExplorerCtrl::OnChange, Refreshing %s due to change\n"), m_sMonitoringPath.GetString()), Refresh();
	}
	return 0L;
}

BOOL CFileExplorerCtrl::OnToolTipTextNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;

	// do not process the message from built in tooltip 
	if (pNMHDR->idFrom == (UINT)m_hWnd &&
		((pNMHDR->code == TTN_NEEDTEXTA && pTTTA->uFlags & TTF_IDISHWND) ||
		(pNMHDR->code == TTN_NEEDTEXTW && pTTTW->uFlags & TTF_IDISHWND)))
	{
		return FALSE;
	}
	// get the mouse position
	const MSG* pMessage;
	CPoint pt;
	pMessage = GetCurrentMessage(); // get mouse pos 
	ASSERT(pMessage);
	pt = pMessage->pt;
	ScreenToClient(&pt);
	UINT nFlags;
	HTREEITEM hitem = HitTest(pt, &nFlags); // get item pointed by mouse
	if (hitem)
	{
		CString strTipText = PathUtils::GetFileSystemInformation(ItemToPath(hitem));
		// force multi-line tool tips
		::SendMessage(pNMHDR->hwndFrom, TTM_SETMAXTIPWIDTH, 0, SHRT_MAX);

		NMTTDISPINFO* pToolTipInfo = (NMTTDISPINFO*)pNMHDR;
		if (pToolTipInfo->hdr.code == TTN_GETDISPINFO)
		{
			pToolTipInfo->lpszText = new TCHAR[strTipText.GetLength() + 1];
			memset(pToolTipInfo->lpszText, 0, (strTipText.GetLength() + 1) * sizeof(TCHAR));
			_tcscpy_s(pToolTipInfo->lpszText, strTipText.GetLength() + 1, strTipText.GetString());
			pToolTipInfo->hinst = 0;
		}
	}
	*pResult = 0;
	return TRUE;  // message was handled
}

void CFileExplorerCtrl::SetAutoRefresh(_In_ bool bAutoRefresh)
{
	//Since it can be touched by more than one thead
	m_bAutoRefresh = bAutoRefresh;

	//Force the monitoring threads to be recreated
	Refresh();
}

void CFileExplorerCtrl::CollapseExpandBranch(_In_ HTREEITEM hItem, _In_ int nAction)
{
	if (ItemHasChildren(hItem))
	{
		if (nAction == TVE_EXPAND)
		{
			m_nExpandCounterLevel++;
			if (m_nExpandCounterLevel > AppSettingMgr.m_nExplorerExpandLimitLevel)
			{
				return;
			}
		}
		Expand(hItem, nAction);
		hItem = GetChildItem(hItem);
		while (hItem)
		{
			CollapseExpandBranch(hItem, nAction);
			hItem = GetNextSiblingItem(hItem);
		}
	}
}

void CFileExplorerCtrl::OnCollapseAll()
{
	SetRedraw(FALSE);
	HTREEITEM hItem = GetSelectedItem();
	if (ItemHasChildren(hItem))
	{
		CollapseExpandBranch(hItem, TVE_COLLAPSE);
		EnsureVisibleCenter(hItem);
	}
	else
	{
		HTREEITEM hItemParent = GetParentItem(hItem);
		CollapseExpandBranch(hItemParent, TVE_COLLAPSE);
		EnsureVisibleCenter(hItemParent);
	}
	SetRedraw(TRUE);
}

void CFileExplorerCtrl::OnCollapseParent()
{
	SetRedraw(FALSE);
	HTREEITEM hItemSelected = GetSelectedItem();
	HTREEITEM hItemParent = GetParentItem(hItemSelected);
	CollapseExpandBranch(hItemParent, TVE_COLLAPSE);
	EnsureVisibleCenter(hItemParent);
	SetRedraw(TRUE);
}

void CFileExplorerCtrl::OnExpandAll()
{
	SetRedraw(FALSE);
	HTREEITEM hItem = GetSelectedItem();
	m_nExpandCounterLevel = 0;
	CollapseExpandBranch(hItem, TVE_EXPAND);
	LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Explorer Window] Expand all childs with limited level %d..."), AppSettingMgr.m_nExplorerExpandLimitLevel);
	EnsureVisibleCenter(hItem);
	SetRedraw(TRUE);
}

void CFileExplorerCtrl::Clear()
{
	//Delete all the items
	DeleteAllItems();

	//Reset the member variables we have
	m_hMyComputerRoot = NULL;
	m_hNetworkRoot = NULL;
	m_hRootedFolder = NULL;
	m_hMyDocumentsRoot = NULL;
	m_hCurrentUserFolderRoot = NULL;
	m_hDesktop = NULL;
	m_hRoot = TVI_ROOT;
}

void CFileExplorerCtrl::SetAsWorkspaceFolder()
{
	OnSetAsWorkspaceFolder();
}

void CFileExplorerCtrl::AddMoreFolderToWorkSpace()
{
	OnAddMoreFolderToWorkSpace();
}

void CFileExplorerCtrl::RemoveFolderFromWorkSpace()
{
	OnRemoveFolderFromWorkSpace();
}

void CFileExplorerCtrl::BackToOriginalExplorer()
{
	OnBackToOriginalExplorer();
}

void CFileExplorerCtrl::PreSubclassWindow()
{
	//Let the base class do its thing
	__super::PreSubclassWindow();

	//Get a pointer to IShellFolder and IMalloc
	ASSERT(m_ShellFolder == NULL);
	HRESULT hr = SHGetDesktopFolder(&m_ShellFolder);
	if (FAILED(hr))
	{
		TRACE(_T("CFileExplorerCtrl::PreSubclassWindow, Failed in call to SHGetDesktopFolder, Error:%08X\n"), hr);
	}
	ASSERT(m_Malloc == NULL);
	hr = SHGetMalloc(&m_Malloc);
	if (FAILED(hr))
	{
		TRACE(_T("CFileExplorerCtrl::PreSubclassWindow, Failed in call to SHGetMalloc, Error:%08X\n"), hr);
	}

	//Load up the cursors we need
#ifndef FILETREECTRL_NO_RESOURCES
	const CWinApp* pApp = AfxGetApp();
#pragma warning(suppress: 26496)
	AFXASSUME(pApp != NULL);
	m_NoDropCopyCursor = pApp->LoadCursor(IDR_TREEFILECTRL_NO_DROPCOPY);
	if (m_NoDropCopyCursor == NULL)
	{
		TRACE(_T("CFileExplorerCtrl::PreSubclassWindow, Failed in load IDR_TREEFILECTRL_NO_DROPCOPY cursor\n"));
	}
	m_DropCopyCursor = pApp->LoadCursor(IDR_TREEFILECTRL_DROPCOPY);
	if (m_DropCopyCursor == NULL)
	{
		TRACE(_T("CFileExplorerCtrl::PreSubclassWindow, Failed in load IDR_TREEFILECTRL_DROPCOPY cursor\n"));
	}
	m_NoDropMoveCursor = pApp->LoadCursor(IDR_TREEFILECTRL_NO_DROPMOVE);
	if (m_NoDropMoveCursor == NULL)
	{
		TRACE(_T("CFileExplorerCtrl::PreSubclassWindow, Failed in load IDR_TREEFILECTRL_NO_DROPMOVE cursor\n"));
	}
	m_DropMoveCursor = pApp->LoadStandardCursor(IDC_ARROW);
	if (m_DropMoveCursor == NULL)
	{
		TRACE(_T("CFileExplorerCtrl::PreSubclassWindow, Failed in load IDC_ARROW cursor\n"));
	}
#endif //#ifndef FILETREECTRL_NO_RESOURCES
}

#pragma warning(suppress: 26434 26429 26440)
BOOL CFileExplorerCtrl::OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult)
{
#pragma warning(suppress: 26490)
	auto pNMTreeView = reinterpret_cast<NMTREEVIEW*>(pNMHDR);
#pragma warning(suppress: 26496)
	AFXASSUME(pNMTreeView != NULL);

	if (pNMTreeView->itemOld.hItem != TVI_ROOT)
	{
#pragma warning(suppress: 26490)
		auto pItem = reinterpret_cast<CFileExplorerCtrlItemInfo*>(pNMTreeView->itemOld.lParam);
#pragma warning(suppress: 26486)
		delete pItem;
	}
	*pResult = 0;
	return FALSE; //Allow the message to be reflected again
}

#pragma warning(suppress: 26461)
void DDX_FileTreeValue(_In_ CDataExchange* pDX, _In_ CFileExplorerCtrl& ctrlFileTree, _Inout_ CString& sItem)
{
	if (pDX->m_bSaveAndValidate)
		sItem = ctrlFileTree.GetSelectedPath();
	else
		ctrlFileTree.SetSelectedPath(NULL);
}

void CFileExplorerCtrl::ShowExplorerShellContextMenu(const CString & strPath)
{
	CStringArray arrayFiles;
	arrayFiles.Add(strPath);

	CFileExlorerContextMenu scm;
	scm.SetObjects(arrayFiles);
	
#pragma warning(suppress: 26496)
	POINT mousePoint;
	GetCursorPos(&mousePoint);
	UINT idCommand = scm.ShowContextMenu(this->GetParent(), mousePoint);

	if (idCommand) // id of custom command, do it from outside CFileExlorerContextMenu
	{
		GetParent()->SendMessage(WM_COMMAND, idCommand, 0);
	}
}

void CFileExplorerCtrl::BookMarkPath()
{
	OnBookMarkPath();
}

void CFileExplorerCtrl::UpdateNavigationPathData()
{
	HTREEITEM hItemRoot = GetRootItem();
	if (hItemRoot)
	{
		m_ExplorerPathData.clear();
		CItemIterator itr(this, hItemRoot);
		while (itr.HasNext())
		{
			HTREEITEM hItem = itr.GetNext();
			CString strPath = ItemToPath(hItem);
			if (PathFileExists(strPath))
			{
				m_ExplorerPathData.push_back(std::make_pair(GetItemText(hItem), strPath));
			}
		}
	}
}

CString CFileExplorerCtrl::GetPathNavigation(const CString& strSubPath)
{
	for (auto const& data : m_ExplorerPathData)
	{
		CString strTempPath = data.first;
		if (strTempPath.MakeLower().Find(strSubPath) != -1)
		{
			return data.second;
		}
	}
	return CString();
}

CString CFileExplorerCtrl::GetPathNavigationIgnore(const CString & strSubPath, const std::vector<CString>& listPathIgnore)
{
	for (auto const& data : m_ExplorerPathData)
	{
		CString strItemText = data.first;
		if (strItemText.MakeLower().Find(strSubPath) != -1)
		{
			if (std::find(listPathIgnore.begin(), listPathIgnore.end(), data.second) != listPathIgnore.end())
			{
				continue;
			}
			return data.second;
		}
	}
	return CString();
}
