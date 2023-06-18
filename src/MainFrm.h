/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "AppUtil.h"
#include "PathUtil.h"
#include "OSUtil.h"

#include "FileExplorerWindow.h"
#include "MessageWindow.h"
#include "BookmarkWindow.h"
#include "SearchResultWindow.h"
#include "BuildWindow.h"
#include "SearchAndReplaceWindow.h"
#include "PathResultWindow.h"
#include "BreakpointWindow.h"

#include "FindDlg.h"
#include "ReplaceDlg.h"

#include "UserExtension.h"

#define UMW_SET_COLOR_ACTIVE_TAB_MDI WM_APP+309
#define UMW_SET_READ_ONLY_TAB_MDI	WM_APP+310
#define UMW_DISABLE_ALL_READ_ONLY_TAB_MDI WM_APP+316

class CEditorDoc;
class CBookMarkPathDlg;
class CQuickSearchDialog;
class CPathComparatorDlg;

///////////////////////////// TOOLBARS //////////////////////////////////////////////////

class CMainFrameToolBar : public CMFCToolBar
{
public:
	CMainFrameToolBar() {};
	virtual ~CMainFrameToolBar() {};
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}
	virtual BOOL AllowShowOnList() const { return FALSE; }
	virtual BOOL OnUserToolTip(CMFCToolBarButton* pButton, CString& strTTText) const;
};

//////////////////////////// MAINFRAME /////////////////////////////////////////////////

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
	// get CWnd controls
	CMFCStatusBar* GetStatusBar() { return &m_wndStatusBar; }
	CMFCTabCtrl* GetActiveMDITabGroup();
	CQuickSearchDialog* GetQuickSearchDialog() { return m_pQuickSearchDialog; }
	CFileExplorerCtrl& GetFileExplorerCtrl() { return m_wndFileExplorer.GetFileExplorerCtrl(); }
	CMDIClientAreaWnd& GetMDIClientAreaWnd() { return m_wndClientArea; }
	BOOL IsClosingMainFrame() const { return m_bIsClosingMainFrame; }

	// update from child controls to MainFrame
	void ClearDataOnDockPane(DOCKABLE_PANE_TYPE type);
	void PrintMessage(LOG_TARGET target, CString strMsg, COLORREF col);
	void AddSearchResultDataToPane(const TEXT_RESULT_SEARCH_REPLACE_DATA& ResultSearchData);
	void AddPathResultDataToPane(const PATH_RESULT_DATA_LIST& ResultSearchData, const CString & strSeachWhat, int nSearchTotal, double dTimeMeasured, BOOL bAppendResult, BOOL bSearchWithoutMatchName);
	void AddBookmarkLineDataToPane(const BOOKMARK_LINE_DATA& BookmarkData);
	void AddBreakpointLineDataToPane(const BREAKPOINT_LINE_DATA& BreakpointData);
	void ActiveDockPane(DOCKABLE_PANE_TYPE type);
	void InitSearchReplaceFromEditor(const CString& strSearchWhat, SEARCH_REPLACE_GOTO_DLG_TYPE searchType);
	void InitQuickSearchFromEditor(const CString& strSearchWhat, SEARCH_REPLACE_GOTO_DLG_TYPE searchType);
	void SearchFromEditor(const CString& strSearchWhat, SEARCH_TYPE searchType, BOOL bSeacrhNext = TRUE, BOOL bHideMessageBox = TRUE, BOOL bSaveSearchWord = TRUE);
	void InitSearchReplaceFromExplorer(const CString& strFolderPath, SEARCH_REPLACE_GOTO_DLG_TYPE searchType);
	void OnChangeAppLook(BOOL bOneNoteTabs, BOOL bMDITabColors, BOOL bIsVSDotNetLook, BOOL bDockTabColors, BOOL bMDITabsVS2005Look, BOOL bActiveTabCloseButton);
	void MDIMoveAllTabGroupMode(BOOL bNext); // customize internal MFC...
	void UpdateFoldingMap(BOOL bActiveDialogTab = TRUE);
	void ShowErrorLineOnEditor();
	void RemoveAllBreakPointDebuggerDoc(VINATEXT_SUPPORTED_LANGUAGE language);
	BOOL IsDebuggerDocument(CEditorDoc * pDoc);
	void ReleaseBookMarkTableDialog();
	void ReleaseQuickSearchDialog();
	void ReleasePathComparatorToolDialog();
	BOOL HasDebuggerDocument(CEditorDoc* pDocument);
	void RemoveDebuggerDocument(CEditorDoc* pDocument);
	void RevealInExplorerWindow(const CString& strPath);
	void ReactiveTabAfterFloatPane();
	void PushTextToClipBoard(const CString & str);
	void ResizeQuickSearchDialog();
	void QuickSearchDialogChangedActiveTab();
	void CloseQuickSearchDialog();
	BOOL ActivateTabInGroup(INT_PTR nTabGroupIndex, int nTabItemIndex = -1);
	CString GetQuickSearchWhat();
	unsigned int GetQuickSearchOption();

// Override
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
// Implementation
public:
	virtual ~CMainFrame() {};
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	virtual CMDIChildWndEx* CreateDocumentWindow(LPCTSTR lpcszDocName, CObject* pObj);
	virtual BOOL OnShowMDITabContextMenu(CPoint point, DWORD dwAllowedItems, BOOL bDrop);
	virtual BOOL OnCloseMiniFrame(CPaneFrameWnd * pWnd);
	virtual void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);

protected:
	std::unordered_map<UINT, CString> m_FileRecentIDMap;
	BOOL				m_bIsClosingMainFrame = FALSE;
	CFont				m_Font;
	CMenu				m_MainMenu;
	CMainFrameToolBar   m_wndToolBar;
	CMFCStatusBar       m_wndStatusBar;
	CMFCToolBarImages   m_UserImages;
	CFileExplorerWindow m_wndFileExplorer;
	CMessagePane		m_wndMessageWindow;
	CBuildPane			m_wndBuildWindow;
	CSearchAndReplaceWindow  m_wndSearchAndReplaceWindow;
	CSearchResultWindow		 m_wndSearchResultPane;
	CBookmarkWindow		  m_wndBookmarkWindow;
	CPathResultWindow     m_wndPathResultWindow;
	CBreakpointWindow	  m_wndBreakpointWindow;
	CBookMarkPathDlg*     m_pBookMarkPathDlg = NULL;
	CQuickSearchDialog*   m_pQuickSearchDialog = NULL;
	CPathComparatorDlg*   m_pPathComparatorDlg = NULL;
	std::set<CEditorDoc*> m_DebuggerDocList;
	CUserExtension        m_UserExtension;

// Generated message map functions
public:
	afx_msg LRESULT OnMainFrameUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnStatusBarSize(int cx);
	afx_msg void OnMoving(UINT nSide, LPRECT lpRect);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnWindowManager();
	afx_msg void OnHighLightMDIActiveTab();
	afx_msg void OnUpdateIconReadOnlyTab();
	afx_msg void OnUpdateIconAllReadOnlyTab();
	afx_msg void OnFullScreeenMode();
	afx_msg void OnMdiTabbedDocument();
	afx_msg void OnUpdateMdiTabbedDocument(CCmdUI* pCmdUI);
	afx_msg void OnViewFileExplorerWindow();
	afx_msg void OnQuickSearch();
	afx_msg void OnQuickReplace();
	afx_msg void OnCleanUpAllWindows();
	afx_msg void OnHideAllWindows();
	afx_msg void OnShowAllWindows();
	afx_msg void OnUpdateQuickSearch(CCmdUI* pCmdUI);
	afx_msg void OnUpdateQuickReplace(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewFileExplorerWindow(CCmdUI* pCmdUI);
	afx_msg void OnViewOutputPane();
	afx_msg void OnUpdateViewSearchAndReplaceWindow(CCmdUI * pCmdUI);
	afx_msg void OnViewSearchAndReplaceWindow();
	afx_msg void OnUpdateViewBookmarkPane(CCmdUI * pCmdUI);
	afx_msg void OnViewBreakpointPane();
	afx_msg void OnUpdateViewBreakpointPane(CCmdUI * pCmdUI);
	afx_msg void OnViewFileResultPane();
	afx_msg void OnUpdateViewFileResultPane(CCmdUI * pCmdUI);
	afx_msg void OnUpdateViewSearchResultPane(CCmdUI * pCmdUI);
	afx_msg void OnViewBuildPane();
	afx_msg void OnUpdateViewBuildPane(CCmdUI* pCmdUI);
	afx_msg void OnViewSearchResultPane();
	afx_msg void OnUpdateViewOutputPane(CCmdUI* pCmdUI);
	afx_msg void OnViewBookmarkPane();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnToolsAllowDelete() noexcept;
	afx_msg void OnUpdateToolsAllowDelete(CCmdUI* pCmdUI);
	afx_msg void OnToolsAllowCreateFolder() noexcept;
	afx_msg void OnUpdateToolsAllowCreateFolder(CCmdUI* pCmdUI);
	afx_msg void OnToolsAllowOpen() noexcept;
	afx_msg void OnUpdateToolsAllowOpen(CCmdUI* pCmdUI);
	afx_msg void OnToolsAllowRename() noexcept;
	afx_msg void OnUpdateToolsAllowRename(CCmdUI* pCmdUI);
	afx_msg void OnToolsAllowProperties() noexcept;
	afx_msg void OnUpdateToolsAllowProperties(CCmdUI* pCmdUI);
	afx_msg void OnToolsShowFiles();
	afx_msg void OnUpdateToolsShowFiles(CCmdUI* pCmdUI);
	afx_msg void OnToolsAllowDragDrop() noexcept;
	afx_msg void OnUpdateToolsAllowDragDrop(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideCDROM();
	afx_msg void OnUpdateToolsHideCDROM(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideFixed();
	afx_msg void OnUpdateToolsHideFixed(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideRAMDisks();
	afx_msg void OnUpdateToolsHideRAMDisks(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideRemovable();
	afx_msg void OnUpdateToolsHideRemovable(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideRemote();
	afx_msg void OnUpdateToolsHideRemote(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideHidden();
	afx_msg void OnUpdateToolsHideHidden(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideArchive();
	afx_msg void OnUpdateToolsHideArchive(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideCompressed();
	afx_msg void OnUpdateToolsHideCompressed(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideSystem();
	afx_msg void OnUpdateToolsHideSystem(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideTemporary();
	afx_msg void OnUpdateToolsHideTemporary(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideEncrypted();
	afx_msg void OnUpdateToolsHideEncrypted(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideOffline();
	afx_msg void OnUpdateToolsHideOffline(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideReadOnly();
	afx_msg void OnUpdateToolsHideReadOnly(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideReparsePoint();
	afx_msg void OnUpdateToolsHideReparsePoint(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideSparse();
	afx_msg void OnUpdateToolsHideSparse(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideHidden2();
	afx_msg void OnUpdateToolsHideHidden2(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideArchive2();
	afx_msg void OnUpdateToolsHideArchive2(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideCompressed2();
	afx_msg void OnUpdateToolsHideCompressed2(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideSystem2();
	afx_msg void OnUpdateToolsHideSystem2(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideTemporary2();
	afx_msg void OnUpdateToolsHideTemporary2(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideEncrypted2();
	afx_msg void OnUpdateToolsHideEncrypted2(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideOffline2();
	afx_msg void OnUpdateToolsHideOffline2(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideReadOnly2();
	afx_msg void OnUpdateToolsHideReadOnly2(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideReparsePoint2();
	afx_msg void OnUpdateToolsHideReparsePoint2(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideSparse2();
	afx_msg void OnUpdateToolsHideSparse2(CCmdUI* pCmdUI);
	afx_msg void OnToolsAutoRefresh();
	afx_msg void OnToolsPreviewMode();
	afx_msg void OnToolsSwitchFocusToActiveTab();
	afx_msg void OnUpdateToolsPreviewMode(CCmdUI* pCmdUI);
	afx_msg void OnToolsRefresh();
	afx_msg void OnToolsGoForward();
	afx_msg void OnToolsGoBack();
	afx_msg void OnToolsGoUP();
	afx_msg void OnUpdateToolsGoUp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsGoForward(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsGoBack(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsAutoRefresh(CCmdUI* pCmdUI);
	afx_msg void OnToolsSetRootFolder();
	afx_msg void OnDestroy();
	afx_msg void OnToolsHideNetwork();
	afx_msg void OnUpdateToolsHideNetwork(CCmdUI* pCmdUI);
	afx_msg void OnToolsShowSharedFolders();
	afx_msg void OnUpdateToolsShowSharedFolders(CCmdUI* pCmdUI);
	afx_msg void OnToolsShowAllNetworkItems();
	afx_msg void OnUpdateToolsShowAllNetworkItems(CCmdUI* pCmdUI);
	afx_msg void OnToolsShowNetworkPrinters();
	afx_msg void OnUpdateToolsShowNetworkPrinters(CCmdUI* pCmdUI);
	afx_msg void OnToolsShowNetworkShares();
	afx_msg void OnUpdateToolsShowNetworkShares(CCmdUI* pCmdUI);
	afx_msg void OnToolsShowDriveLabels();
	afx_msg void OnUpdateToolsShowDriveLabels(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideMyComputer();
	afx_msg void OnUpdateToolsHideMyComputer(CCmdUI* pCmdUI);
	afx_msg void OnToolsShowRootedFolder();
	afx_msg void OnUpdateToolsShowRootedFolder(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideDesktop();
	afx_msg void OnUpdateToolsHideDesktop(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideMyDocuments();
	afx_msg void OnUpdateToolsHideMyDocuments(CCmdUI* pCmdUI);
	afx_msg void OnToolsHideCurrentUserFolder();
	afx_msg void OnUpdateToolsHideCurrentUserFolder(CCmdUI* pCmdUI);
	afx_msg void OnVinaTextSettings();
	afx_msg void OnToolsRemoveFolder();
	afx_msg void OnToolsBackToOriginalExplorer();
	afx_msg void OnToolsBookMarkAPath();
	afx_msg void OnToolsOpenBookMarkPathTable();
	afx_msg void OnToolsOpenFolderVinaText();
	afx_msg void OnToolsOpenFolderTemp();
	afx_msg void OnToolsOpenFolderAppData();
	afx_msg void OnFileSendMailEx();
	afx_msg void OnUpdateFileSendMailEx(CCmdUI * pCmdUI);
	afx_msg void OnTerminalOpenNewCMDWindow();
	afx_msg void OnTerminalOpenNewPowerShellWindow();
	afx_msg void OnTerminalOpenNewWSLWindow();
	afx_msg void OnHostFileExplorer();
	afx_msg void OnToolPythonPipWindow();
	afx_msg void OnToolNodeJSNPMWindow();
	afx_msg LRESULT OnGetTabToolTip(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnAfxWmChangedActiveTab(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCopyData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCompilerNotifyDebugLinePointer(WPARAM wParam, LPARAM lParam);
	// from MDI tab menu
	afx_msg void OnCloseDocument();
	afx_msg void OnCloseAllDocument();
	afx_msg void OnCloseAllDocumentLeft();
	afx_msg void OnCloseAllDocumentRight();
	afx_msg void OnCloseAllDocumentButThis();
	afx_msg void OnGetFullPath();
	afx_msg void OnGetFullPathDoubleSlash();
	afx_msg void OnGetFullPathForwardSlash();
	afx_msg void OnGetFolderPath();
	afx_msg void OnGetFileName();
	afx_msg void OnGetFileNameNoExtension();
	afx_msg void OnOpenContainerFolder();
	afx_msg void OnOpenFileExplorer();
	afx_msg void OnOpenToolbarTerminalWindows();
	afx_msg void OnOpenCMDHere();
	afx_msg void OnOpenCMDPasteClipboard();
	afx_msg void OnOpenCMDAppendFileName();
	afx_msg void OnOpenCMDAppendFilePath();
	afx_msg void OnOpenWSLHere();
	afx_msg void OnOpenPowerShellHere();
	afx_msg void OnOpenGitFileProperties();
	afx_msg void OnRenameDocument();
	afx_msg void OnReLoadDocument();
	afx_msg void OnCopyDocument();
	afx_msg void OnNewVerticalTabGroup();
	afx_msg void OnNewHorizontalTabGroup();
	afx_msg void OnSwitchToNextTab();
	afx_msg void OnSwitchToPreviousTab();
	afx_msg void OnMDITabMoveToNewVinaText();
	afx_msg void OnMDITabMoveToNextGroup();
	afx_msg void OnMDITabMoveToPreviousGroup();
	afx_msg void OnMDITabCloneFile();
	afx_msg void OnMDITabMoveAllToNextGroup();
	afx_msg void OnMDITabMoveAllToPreviousGroup();
	afx_msg void OnMDINewFile();
	afx_msg void OnMDINewFileInNewGroup();
	afx_msg void OnMDITabOpenInChrome();
	afx_msg void OnMDITabOpenInEdge();
	afx_msg void OnMDITabOpenInFireFox();
	afx_msg void OnCloseAllDocumentUnmodified();
	afx_msg void OnDeleteFile();
	afx_msg void OnDocumentBookMark();
	afx_msg void OnOptionGetFullFilePathDoubleQuote();
	afx_msg void OnOptionsGetSystemInformation();
	afx_msg void OnOptionsGetPATHVariable();
	afx_msg void OnOptionsGetWifiInformation();
	afx_msg void OnPrintFileNow();
	afx_msg void OnPrintFileSetupDlg();
	afx_msg void OnPrintPageSetupDlg();
	afx_msg void OnToolbarVerticalTabGroup();
	afx_msg void OnToolbarHorizontalTabGroup();
	afx_msg void OnUpdatePrintFileNow(CCmdUI * pCmdUI);
	afx_msg void OnUpdatePrintFileSetupDlg(CCmdUI * pCmdUI);
	afx_msg void OnUpdatePrintPageSetupDlg(CCmdUI * pCmdUI);
	afx_msg void OnUpdateReLoadDocument(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOpenFileEplorer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOpenCMDAppendFile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOpenCMDAppendFilePath(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOpenContainerFolder(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBookmarkFile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCloseAllDocument(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCloseDocument(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolbarVerticalTabGroup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolbarHorizontalTabGroup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMDITabMoveToPreviousGroup(CCmdUI* pCmdUI);
	afx_msg void OnUserExtensions();
	afx_msg void OnExtensionRefreshList();
	afx_msg void OnUserExtension(UINT nIDExtension);
	afx_msg void OnPathComparatorTool();
	afx_msg void OnOpenFileRecent(UINT nIDExtension);

	DECLARE_MESSAGE_MAP()
protected:
	void InitRecentFilesList(CMenu* pFileMenu);
	CString GetCurrentDocFolder();
	BOOL SetCurrentDirectoryTerminal();
	void ShowQuickSearchDialog(SEARCH_REPLACE_GOTO_DLG_TYPE type);
	CString GetClipboardPlainText();
	BOOL IsSameMDITabGroup(CView * pActiveview, CView * pParentview);
	void UpdateUIByCheckExistFile(CCmdUI * pCmdUI);
	void UpdateUIForEditorView(CCmdUI * pCmdUI);
	void UpdateUIForPrinter(CCmdUI * pCmdUI);
	void UpdateUIByCheckTabGroup(CCmdUI* pCmdUI);
	void SetDockingPaneIcons(BOOL bBigIcons);
	BOOL CreateDockingBars();
	void FinalizeWorkerThread();
	void UpdateEditorUiForDebugger(CEditorDoc * pEditorDoc, DWORD lPointerLine);
};
