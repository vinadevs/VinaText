/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

////////////////////////////////// Macros / Defines  //////////////////////////

#pragma once

#ifndef __FILETREECTRL_H__
#define __FILETREECTRL_H__

#ifndef FILETREECTRL_EXT_CLASS
#define FILETREECTRL_EXT_CLASS
#endif //#ifndef FILETREECTRL_EXT_CLASS

#ifndef FILETREECTRL_EXT_API
#define FILETREECTRL_EXT_API
#endif //#ifndef FILETREECTRL_EXT_API

#ifndef FILETREECTRL_BASE_CLASS
#define FILETREECTRL_BASE_CLASS CTreeCtrl
#endif //#ifndef FILETREECTRL_BASE_CLASS

/////////////////////////// Includes //////////////////////////////////////////

#ifndef __AFXMT_H__
#pragma message("To avoid this message, put afxmt.h in your pre compiled header (normally stdafx.h)")
#include <afxmt.h>
#endif //#ifndef __AFXMT_H__

#ifndef _SHLOBJ_H_
#pragma message("To avoid this message, put shlobj.h in your pre compiled header (normally stdafx.h)")
#include <shlobj.h>
#endif //#ifndef _SHLOBJ_H_

#ifndef _LM_
#pragma message("To avoid this message, put lm.h in your pre compiled header (normally stdafx.h)")
#include <lm.h>
#endif //#ifndef _LM_

#ifndef __AFXMT_H__
#pragma message("To avoid this message, put afxmt.h in your pre compiled header (normally stdafx.h)")
#include <afxmt.h>
#endif //#ifndef __AFXMT_H__

#ifndef _ARRAY_
#pragma message("To avoid this message, put array in your pre compiled header (normally stdafx.h)")
#include <array>
#endif //#ifndef _ARRAY_

#ifndef _VECTOR_
#pragma message("To avoid this message, put vector in your pre compiled header (normally stdafx.h)")
#include <vector>
#endif //#ifndef _VECTOR_

#ifndef _ATOMIC_
#pragma message("To avoid this message, put atomic in your pre compiled header (normally stdafx.h)")
#include <atomic>
#endif //#ifndef _ATOMIC_

#ifndef __ATLCOM_H__
#pragma message("To avoid this message, put atlcom.h in your pre compiled header (normally stdafx.h)")
#include <atlcom.h>
#endif //#ifndef __ATLCOM_H__

/////////////////////////// Classes ///////////////////////////////////////////

class CSearchNavigatePathDlg;

//Class which gets stored int the item data on the tree control
class FILETREECTRL_EXT_CLASS CFileExplorerCtrlItemInfo
{
public:
//Enums
  enum class NodeType
  {
    UnknownNode,
    DesktopNode,
    NetworkNode,
    MyDocumentsNode,
    MyComputerNode,
    CurrentUserFolderNode,
    FileNode,
    FolderNode,
    DriveNode
  };

//Constructors / Destructors
  CFileExplorerCtrlItemInfo() noexcept;
  CFileExplorerCtrlItemInfo(const CFileExplorerCtrlItemInfo&) = default;
  CFileExplorerCtrlItemInfo(CFileExplorerCtrlItemInfo&&) = default;
  ~CFileExplorerCtrlItemInfo() = default;

//Methods
  CFileExplorerCtrlItemInfo& operator=(const CFileExplorerCtrlItemInfo&) = default;
  CFileExplorerCtrlItemInfo& operator=(CFileExplorerCtrlItemInfo&&) = default;

//Member variables
  CString m_sFQPath;                //Fully qualified path for this item
  CString m_sRelativePath;          //The "Display name" for this item, Normally will be a relative bit of the path from "m_sFQPath"
  NodeType m_NodeType;              //The type of node this is
  bool m_bExtensionHidden;          //Is the extension being hidden for this item
  DWORD m_dwNetResourceScope;       //Used if this item is under Network Neighborhood
  DWORD m_dwNetResourceType;        //Used if this item is under Network Neighborhood
  DWORD m_dwNetResourceDisplayType; //Used if this item is under Network Neighborhood
  DWORD m_dwNetResourceUsage;       //Used if this item is under Network Neighborhood
  CString m_sNetResourceLocalName;  //Used if this item is under Network Neighborhood
  CString m_sNetResourceRemoteName; //Used if this item is under Network Neighborhood
  CString m_sNetResourceComment;    //Used if this item is under Network Neighborhood
  CString m_sNetResourceProvider;   //Used if this item is under Network Neighborhood
};

//Class which encapsulates access to the System image list which contains
//all the icons used by the shell to represent the file system
class FILETREECTRL_EXT_CLASS CSystemImageList : public CImageList
{
public:
//Constructors / Destructors
  CSystemImageList();

protected:
  friend class CFileExplorerCtrl; //Allow the FileTreeCtrl access to our internals
};

//class which manages enumeration of shares. This is used for determining 
//if an item is shared or not
class FILETREECTRL_EXT_CLASS CShareEnumerator
{
public:
//Constructors / Destructors
  CShareEnumerator() noexcept;
  CShareEnumerator(const CShareEnumerator&) = delete;
  CShareEnumerator(CShareEnumerator&&) = delete;
  virtual ~CShareEnumerator();

//Methods
  CShareEnumerator& operator=(const CShareEnumerator&) = delete;
  CShareEnumerator& operator=(CShareEnumerator&&) = delete;
  void Refresh() noexcept; //Updates the internal enumeration list
  bool IsShared(_In_ const CString& sPath);

protected:
//Data
  SHARE_INFO_502* m_pNTShareInfo; //share info
  DWORD m_dwShares;               //The number of shares enumerated
};

//Class which implements the tree control representation of the file system
class FILETREECTRL_EXT_CLASS CFileExplorerCtrl : public FILETREECTRL_BASE_CLASS
{
public:
//Enums
  enum class HideFileExtension
  {
    HideExtension,
    DoNoHideExtension,
    UseTheShellSetting
  };

  enum DriveType
  {
    DRIVE_ATTRIBUTE_REMOVABLE = 0x00000001,
    DRIVE_ATTRIBUTE_FIXED     = 0x00000002,
    DRIVE_ATTRIBUTE_REMOTE    = 0x00000004,
    DRIVE_ATTRIBUTE_CDROM     = 0x00000010,
    DRIVE_ATTRIBUTE_RAMDISK   = 0x00000020
  };

//Constructors / Destructors
  CFileExplorerCtrl();
  ~CFileExplorerCtrl() = default;
//Public methods
  void SetRootFolder(_In_ const CString& sPath);
  CString GetRootFolder() const { return m_sRootFolder; };
  CString GetSelectedPath();
  HTREEITEM SetSelectedPath(_In_ const CString& sPath, _In_ BOOL bExpanded = false);
  void SetShowFiles(_In_ bool bFiles);
  bool GetShowFiles() const noexcept { return m_bShowFiles; };
  void SetShowNetwork(_In_ bool bShowNetwork);
  bool GetShowNetwork() const noexcept { return m_bShowNetwork; };
  void SetUsingDifferentIconForSharedFolders(_In_ bool bShowSharedUsingDifferentIcon);
  bool GetUsingDifferentIconForSharedFolders() const noexcept { return m_bShowSharedUsingDifferentIcon; };
  void SetAllowDragDrop(_In_ bool bAllowDragDrop) noexcept { m_bAllowDragDrop = bAllowDragDrop; };
  bool GetAllowDragDrop() const noexcept { return m_bAllowDragDrop; };
  void SetAllowRename(_In_ bool bAllowRename) noexcept { m_bAllowRename = bAllowRename; };
  bool GetAllowRename() const noexcept { return m_bAllowRename; };
  void SetAllowOpen(_In_ bool bAllowOpen) noexcept { m_bAllowOpen = bAllowOpen; };
  bool GetAllowOpen() const noexcept { return m_bAllowOpen; };
  void SetAllowProperties(_In_ bool bAllowProperties) noexcept { m_bAllowProperties = bAllowProperties; };
  bool GetAllowProperties() const noexcept { return m_bAllowProperties; };
  void SetAllowDelete(_In_ bool bAllowDelete) noexcept { m_bAllowDelete = bAllowDelete; };
  bool GetAllowDelete() const noexcept { return m_bAllowDelete; };
  void SetAllowCreateFolder(_In_ bool bAllowCreateFolder) noexcept { m_bAllowCreateFileAndFolder = bAllowCreateFolder; };
  bool GetAllowCreateFolder() const noexcept { return m_bAllowCreateFileAndFolder; };
  void SetDriveHideFlags(_In_ DWORD dwDriveHideFlags);
  DWORD GetDriveHideFlags() const noexcept { return m_dwDriveHideFlags; };
  void SetFileHideFlags(_In_ DWORD dwFileHideFlags);
  DWORD GetFileHideFlags() const noexcept { return m_dwFileHideFlags; };
  void SetFolderHideFlags(_In_ DWORD dwFolderHideFlags);
  DWORD GetFolderHideFlags() const noexcept { return m_dwFolderHideFlags; };
  size_t AddMultipleFileNameMasks(_In_ const CString& sFileNameMasks);
  void SetFileNameMask(_In_ size_t nIndex, _In_ const CString& sFileNameMask);
  void AddFileNameMask(_In_ const CString& sFileNameMask);
  void RemoveFileNameMask(_In_ int nIndex) { m_FileNameMasks.erase(m_FileNameMasks.begin() + nIndex); };
#pragma warning(suppress: 26446)
  CString GetFileNameMask(_In_ int nIndex) const { return m_FileNameMasks[nIndex]; };
  CString GetFileNameMasks() const;
  void SetNetworkItemTypes(_In_ DWORD dwTypes);
  DWORD GetNetworkItemTypes() const noexcept { return m_dwNetworkItemTypes; };
  void SetShowDriveLabels(_In_ bool bShowDriveLabels);
  bool GetShowDriveLabels() const noexcept { return m_bShowDriveLabels; };
  COLORREF GetCompressedColor() const noexcept { return m_rgbCompressed; };
  void SetCompressedColor(_In_ COLORREF rgbCompressed);
  bool GetUsingDifferentColorForCompressed() const noexcept { return m_bShowCompressedUsingDifferentColor; };
  void SetUsingDifferentColorForCompressed(_In_ bool bShowCompressedUsingDifferentColor);
  COLORREF GetEncryptedColor() const noexcept { return m_rgbEncrypted; };
  void SetEncryptedColor(_In_ COLORREF rgbEncrypted);
  bool GetUsingDifferentColorForEncrypted() const noexcept { return m_bShowEncryptedUsingDifferentColor; };
  void SetUsingDifferentColorForEncrypted(_In_ bool bShowEncryptedUsingDifferentColor);
  HideFileExtension GetShowFileExtensions() const noexcept { return m_FileExtensions; };
  void SetShowFileExtensions(_In_ HideFileExtension FileExtensions);
  bool GetShowMyComputer() const noexcept { return m_bShowMyComputer; };
  void SetShowMyComputer(_In_ bool bShowMyComputer);
  bool GetShowDesktop() const noexcept { return m_bShowDesktop; };
  void SetShowDesktop(_In_ bool bShowDesktop);
  bool GetShowMyDocuments() const noexcept { return m_bShowMyDocuments; };
  void SetShowMyDocuments(_In_ bool bShowMyDocuments);
  bool GetShowCurrentUserFolder() const noexcept { return m_bShowCurrentUserFolder; };
  void SetShowCurrentUserFolder(_In_ bool bShowCurrentUserFolder);
  bool GetShowRootedFolder() const noexcept { return m_bShowRootedFolder; };
  void SetShowRootedFolder(_In_ bool bShowRootedFolder);
  void SetAutoRefresh(_In_ bool bAutoRefresh);
  bool GetAutoRefresh() const noexcept { return m_bAutoRefresh; };
  virtual CString ItemToPath(_In_ HTREEITEM hItem) const;
  virtual HTREEITEM PathToItem(_In_ const CString& sPath) const;
  virtual bool IsFile(_In_ HTREEITEM hItem);
  virtual bool IsFolder(_In_ HTREEITEM hItem);
  virtual bool IsDrive(_In_ HTREEITEM hItem);
  virtual bool IsNetworkShare(_In_ HTREEITEM hItem);
  virtual bool IsCompressed(_In_ HTREEITEM hItem);
  virtual bool IsEncrypted(_In_ HTREEITEM hItem);
  virtual bool IsShared(_In_ const CString& sPath);
  static bool IsFile(_In_ const CString& sPath) noexcept;
  static bool IsFolder(_In_ const CString& sPath) noexcept;
  static bool IsDrive(_In_ const CString& sPath);
  static bool IsUNCServerName(_In_ const CString& sPath);
  static bool IsCompressed(_In_ const CString& sPath);
  static bool IsEncrypted(_In_ const CString& sPath);
  static bool IsShortcut(_In_ const CString& sFilename);
  virtual bool Rename(_In_ HTREEITEM hItem);
  virtual bool ShowProperties(_In_ HTREEITEM hItem);
  virtual bool Delete(_In_ HTREEITEM hItem);
  virtual void CloseCurrentMDITab(HTREEITEM hItem);
  virtual bool Open(_In_ HTREEITEM hItem, BOOL bOpenByDefaultApp = TRUE);
  virtual HTREEITEM CreateFolder(_In_ HTREEITEM hItem, _In_ const CString& sNewFolderName = _T(""));
  virtual HTREEITEM CreateFileWin32(_In_ HTREEITEM hItem, _In_ const CString& sNewFileName = _T(""));
  virtual HTREEITEM MoveFileWin32(_In_ HTREEITEM hItem, _In_ BOOL bIsCopy = FALSE);
  virtual void PopulateTree(); 
  virtual void UpOneLevel();
  virtual void Refresh();
  virtual bool GoBack();
  virtual bool CanGoBack() const noexcept { return m_PrevItems.size() != 0; };
  virtual bool GoForward();
  virtual bool CanGoForward() const noexcept { return m_NextItems.size() != 0; };
  virtual size_t GetMaxHistory() const noexcept { return m_nMaxHistory; };
  virtual void SetMaxHistory(_In_ size_t nMaxHistory);
  size_t GetBackSize() const noexcept;
  CString GetBackItemText(_In_ size_t nBack) const;
  size_t GetForwardSize() const noexcept;
  CString GetForwardItemText(_In_ size_t nForward) const;
  void CollapseExpandBranch(_In_ HTREEITEM hItem, _In_ int nAction);
  void Clear();
  void SetAsWorkspaceFolder();
  void AddMoreFolderToWorkSpace();
  void RemoveFolderFromWorkSpace();
  void BackToOriginalExplorer();
  std::vector<CString> GetNewAddedFolderData() const { return m_NewAddedFolderData; }
  void ShowExplorerShellContextMenu(const CString & strPath);
  void BookMarkPath();
  void AddMoreFolderToWorkSpace(const CString & strFolder);
  void OpenClipBoard(const CString & str);
  CString GetClipboardPlainText();
  void ReleaseSearchFileDlg();
  void UpdateNavigationPathData();
  CString GetPathNavigation(const CString& strSubPath);
  CString GetPathNavigationIgnore(const CString& strSubPath, const std::vector<CString>& listPathIgnore);

//Debug / Assert help
#ifdef _DEBUG
  void AssertValid() const override;
  void Dump(CDumpContext& dc) const override;
#endif //#ifdef _DEBUG

#ifndef FILETREECTRL_NO_RESOURCES
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  afx_msg BOOL OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
#endif //#ifndef FILETREECTRL_NO_RESOURCES

  afx_msg void OnVirusScanner();
  afx_msg void OnProperties();
  afx_msg void OnUpdateProperties(CCmdUI* pCmdUI);
  afx_msg void OnRename();
  afx_msg void OnUpdateRename(CCmdUI* pCmdUI);
  afx_msg void OnOpen();
  afx_msg void OnUpdateOpen(CCmdUI* pCmdUI);
  afx_msg void OnClose();
  afx_msg void OnDelete();
  afx_msg void OnUpdateDelete(CCmdUI* pCmdUI);
  afx_msg void OnUpdateUpOneLevel(CCmdUI* pCmdUI);
  afx_msg void OnBack();
  afx_msg void OnUpdateBack(CCmdUI* pCmdUI);
  afx_msg void OnForward();
  afx_msg void OnUpdateForward(CCmdUI* pCmdUI);
  afx_msg void OnCreateDocumentFromFile();
  afx_msg void OnOpenAsRawFormat();
  afx_msg void OnOpenAllFileByVinaText();
  afx_msg void OnHostFileExplorer();
  afx_msg void OnOpenFileContainer();
  afx_msg void OnLoadAutoCompleteDataset();
  afx_msg void OnDeleteFileByExtension();
  afx_msg void OnEditWithMSPaint();
  afx_msg void OnUpOneLevel();
  afx_msg void OnRefresh();
  afx_msg void OnExpandAll();
  afx_msg void OnCollapseAll();
  afx_msg void OnCollapseParent();
  afx_msg void OnJumpToPath();
  afx_msg void OnSetAsWorkspaceFolder();
  afx_msg void OnAddMoreFolderToWorkSpace();
  afx_msg void OnBookMarkPath();
  afx_msg void OnOpenBookMarkTable();
  afx_msg void OnRemoveFolderFromWorkSpace();
  afx_msg void OnBackToOriginalExplorer();
  afx_msg void OnSetFileExtensionFilter();
  afx_msg void OnShowSystemMenu();
  afx_msg void OnOpenRecycleBin();
  afx_msg void OnCreateFile();
  afx_msg void OnSetFocusActiveMDITab();
  afx_msg void OnGetFullPath();
  afx_msg void OnGetFullPathDoubleQuote();
  afx_msg void OnGetFullPathDoubleSlash();
  afx_msg void OnGetFullPathForwardSlash();
  afx_msg void OnGetContainerPath();
  afx_msg void OnGetName();
  afx_msg void OnTerminalRunActiveFile();
  afx_msg void OnUpdateTerminalRunActiveFile(CCmdUI* pCmdUI);
  afx_msg void OnTerminalOpenNewCMDWindow();
  afx_msg void OnTerminalOpenNewPowerShellWindow();
  afx_msg void OnOpenCMDHere();
  afx_msg void OnOpenWSLHere();
  afx_msg void OnOpenCMDAppendFileHere();
  afx_msg void OnOpenCMDAppendPathHere();
  afx_msg void OnOpenCMDPatseClipboardHere();
  afx_msg void OnOpenPowerShellHere();
  afx_msg void OnOpenGitBashHere();
  afx_msg void OnOpenGitWslHere();
  afx_msg void OnOptionsEditListAllFile();
  afx_msg void OnOptionsEditListAllFolder();
  afx_msg void OnOptionsEditSearchText();
  afx_msg void OnOptionsEditReplaceOnfolder();
  afx_msg void OnOptionsEditSearchFiles();
  afx_msg void OnOptionsEditFileSaveAs();
  afx_msg void OnCut();
  afx_msg void OnCopy();
  afx_msg void OnPaste();
  afx_msg void OnUpdatePaste(CCmdUI* pCmdUI);
  afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
  afx_msg void OnDestroy();
  afx_msg void OnCreateFolder();
  afx_msg void OnCreateNewMutiple();
  afx_msg void OnOpenInChrome();
  afx_msg void OnOpenInEdge();
  afx_msg void OnOpenInFireFox();
  afx_msg BOOL OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg BOOL OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg BOOL OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg BOOL OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg BOOL OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg BOOL OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg BOOL OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg BOOL OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg LRESULT OnChange(WPARAM wParam, LPARAM lParam);
  afx_msg BOOL OnToolTipTextNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult);

  DECLARE_MESSAGE_MAP()
  DECLARE_DYNCREATE(CFileExplorerCtrl)

//Methods
  virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO * pTI) const;
  BOOL PreTranslateMessage(MSG* pMsg) override;
  void PreSubclassWindow() override;
  virtual void DisplayPath(_In_ const CString& sPath, _In_ HTREEITEM hParent, _In_ bool bUseSetRedraw = true, _In_ bool bDeleteExistingSiblings = true);
  virtual void AddPath(_In_ const CString& sPath, _In_ bool bUseSetRedraw = true, _In_ bool bExpand = false);
  virtual void DisplayDrives(_In_ HTREEITEM hParent, _In_ bool bUseSetRedraw = true);
  virtual bool DisplayShares(_In_ HTREEITEM hParent, _In_ const CString& sComputer);
  virtual HTREEITEM DisplayNetworkComputer(_In_ HTREEITEM hParent, _In_ const CString& sComputer);
  virtual int GetIconIndex(_In_ const CString& sFilename);
  virtual int GetIconIndex(_In_ HTREEITEM hItem);
  virtual int GetSelIconIndex(_In_ const CString& sFilename);
  virtual int GetSelIconIndex(_In_ HTREEITEM hItem);
  virtual int GetIconIndex(_In_ LPITEMIDLIST lpPIDL);
  virtual int GetSelIconIndex(_In_ LPITEMIDLIST lpPIDL);
  virtual bool HasGotSubEntries(_In_ const CString& sDirectory);
  virtual bool HasChildWithText(_In_ HTREEITEM hParent, _In_ const CString& sText);
  virtual HTREEITEM InsertFileItem(_In_ HTREEITEM hParent, _In_ CFileExplorerCtrlItemInfo* pItem, _In_ int nOverlayMask, _In_ int nIcon, _In_ int nSelIcon, _In_ bool bCheckForChildren);
  virtual HTREEITEM FindSibling(_In_ HTREEITEM hParent, _In_ const CString& sItem) const;
  virtual bool DriveHasRemovableMedia(_In_ const CString& sPath);
  bool IsExpanded(_In_ HTREEITEM hItem);
  void SetFocusOnCurrentMDITab();

#ifndef FILETREECTRL_NO_RESOURCES
  virtual bool IsDropSource(_In_ HTREEITEM hItem);
  bool IsDragging() noexcept;
  void EndDragging(_In_ bool bCancel);
  virtual HTREEITEM GetDropTarget(_In_ HTREEITEM hItem);
#endif //#ifndef FILETREECTRL_NO_RESOURCES

  virtual HTREEITEM CopyItem(_In_ HTREEITEM hItem, _In_ HTREEITEM hNewParent, _In_ HTREEITEM hAfter = TVI_LAST);
  virtual HTREEITEM CopyBranch(_In_ HTREEITEM hBranch, _In_ HTREEITEM hNewParent, _In_ HTREEITEM hAfter = TVI_LAST);
  virtual bool CanDisplayFile(_In_ const CFileFind& find);
  virtual bool CanDisplayFolder(_In_ const CFileFind& find);
  virtual bool CanDisplayDrive(_In_ const CString& sDrive);
  virtual bool CanDisplayNetworkItem(_In_ CFileExplorerCtrlItemInfo* pItem);
  virtual bool CanHandleChangeNotifications(_In_ const CString& sPath);
  static int CALLBACK CompareByFilenameNoCase(_In_ LPARAM lParam1, _In_ LPARAM lParam2, _In_ LPARAM lParamSort);
  virtual void CreateMonitoringThread(_In_ const CString& sPath);
  static UINT _MonitoringThread(_In_ LPVOID pParam);
  virtual UINT MonitoringThread();
  virtual void KillMonitoringThread();
  virtual bool GetSerialNumber(_In_ const CString& sDrive, _Out_ DWORD& dwSerialNumber) noexcept;
  virtual bool IsMediaValid(_In_ const CString& sDrive);
  virtual void OnPreviewFile(_In_ NM_TREEVIEW* pNMTreeView, _In_ const CString& sPath);
  virtual bool EnumNetwork(_In_ HTREEITEM hParent);
  virtual bool EnumNetwork(_In_opt_ NETRESOURCE* pParentNetResource, _In_ HTREEITEM hParentItem);
  virtual CString GetDriveLabel(_In_ const CString& sDrive);
  virtual CString CreateNewChildFolderName(_In_ const CString& sParentFolder);
  virtual CString CreateNewChildFileName(_In_ const CString& sParentFolder);
  CString GetCorrectedLabel(_In_ CFileExplorerCtrlItemInfo* pItem);
  HTREEITEM FindServersNode(_In_ HTREEITEM hFindFrom) const;
  bool HasPlusButton(_In_ HTREEITEM hItem);
  void SetHasPlusButton(_In_ HTREEITEM hItem, _In_ bool bHavePlus);
  void DoExpand(_In_ HTREEITEM hItem);
  virtual void DisplayRootItems();
  void EnsureVisibleCenter(_In_ HTREEITEM hItem);
  void UpdateStatusBarSelectedText( _In_ const CString& sPath);
  BOOL OpenSelectedPath();
  void DoNavigateSearchFiles(CString strFolderPath);

//Member variables
  CString m_sRootFolder;
  std::vector<CString> m_NewAddedFolderData;
  CString m_sMyDocumentsPath;
  CString m_sCurrentUserFolderPath;
  CString m_sDesktopPath;
  std::atomic<bool> m_bShowFiles;
  HTREEITEM m_hRoot;

#ifndef FILETREECTRL_NO_RESOURCES
  HTREEITEM m_hItemDrag;
  HTREEITEM m_hItemDrop;
#endif //#ifndef FILETREECTRL_NO_RESOURCES

  HTREEITEM m_hNetworkRoot;
  HTREEITEM m_hDesktop;
  HTREEITEM m_hMyDocumentsRoot;
  HTREEITEM m_hMyComputerRoot;
  HTREEITEM m_hCurrentUserFolderRoot;
  HTREEITEM m_hRootedFolder;
  bool m_bShowMyComputer;
  bool m_bShowDesktop;
  bool m_bShowMyDocuments;
  bool m_bShowCurrentUserFolder;

#ifndef FILETREECTRL_NO_RESOURCES
  CImageList* m_pilDrag;
#endif //#ifndef FILETREECTRL_NO_RESOURCES
  UINT_PTR m_nTimerID;

#ifndef FILETREECTRL_NO_RESOURCES
  HCURSOR m_DropCopyCursor;
  HCURSOR m_NoDropCopyCursor;
  HCURSOR m_DropMoveCursor;
  HCURSOR m_NoDropMoveCursor;
#endif //#ifndef FILETREECTRL_NO_RESOURCES

  UINT m_TimerTicks;
  bool m_bAllowDragDrop;
  bool m_bAllowRename;
  bool m_bAllowOpen;
  bool m_bAllowProperties;
  bool m_bAllowDelete;
  bool m_bAllowCreateFileAndFolder;
  DWORD m_dwDriveHideFlags;
  DWORD m_dwFileHideFlags;
  DWORD m_dwFolderHideFlags;
  std::vector<CString> m_FileNameMasks;
  COLORREF m_rgbCompressed;
  bool m_bShowCompressedUsingDifferentColor;
  COLORREF m_rgbEncrypted;
  bool m_bShowEncryptedUsingDifferentColor;
  std::vector<HTREEITEM> m_PrevItems;
  std::vector<HTREEITEM> m_NextItems;
  size_t m_nMaxHistory;
  bool m_bUpdatingHistorySelection;
  bool m_bShowNetwork;
  bool m_bShowSharedUsingDifferentIcon;
  HideFileExtension m_FileExtensions;
  std::array<DWORD, 26> m_MediaIDs;
  ATL::CComPtr<IMalloc> m_Malloc;
  ATL::CComPtr<IShellFolder> m_ShellFolder;
  DWORD m_dwNetworkItemTypes;
  bool m_bShowDriveLabels;
  bool m_bShowRootedFolder;
  std::atomic<bool> m_bAutoRefresh;
  CString m_sMonitoringPath; //The path we are monitoring
  CWinThread* m_pMonitoringThread; //The pointer for the monitor thread
  CEvent m_MonitoringTerminateEvent; //Event using to terminate the thread
  CSystemImageList m_SystemImageList; //The one and only system image list instance
  CShareEnumerator m_SharedEnumerator; //The one and only share enumerator
  CString m_sSourceCopyPath;
  BOOL	m_bIsCopyItemAction = FALSE;
  BOOL m_bEditLabelFlag = FALSE;
  CString m_sDestinationCopyPath;
  int m_nExpandCounterLevel = 0;

  typedef std::vector<std::pair<CString, CString>> ExplorerPathData;
  ExplorerPathData m_ExplorerPathData;
  CSearchNavigatePathDlg* m_pSearchFileDlg = NULL;

#ifndef FILETREECTRL_NO_CACHE_COMPUTER_ICON
  int m_nComputerIconIndex;
  int m_nSelectedComputerIconIndex;
#endif
};

//MFC Data exchange routines
void FILETREECTRL_EXT_API DDX_FileTreeValue(_In_ CDataExchange* pDX, _In_ CFileExplorerCtrl& ctrlFileTree, _Inout_ CString& sItem);

#endif //#ifndef __FILETREECTRL_H__
