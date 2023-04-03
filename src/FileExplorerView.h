/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

/**
Represents a very simplified shell item.
*/
class CBrowserItem
{
public:
	typedef std::vector<CBrowserItem> List;

	/**
	Zip files are reported as File although they
	can also browsed as folders, all items inside
	zips are reported as Other.
	*/
	enum Type
	{
		Unknown = 0,    /*!< item type is unknown, unimportant, or item is invalid  */
		File = 0x01, /*!< filesystem file        */
		Directory = 0x02, /*!< filesystem directory   */
		Other = 0x08  /*!< not File or Directory  */
	};

	CBrowserItem(Type type = Unknown)
		: m_type(type), m_SFGAO(0) {}

	Type GetType() const { return m_type; }

	/*! Returns the full filesystem path if the item is File
	or Directory and empty string otherwise. */
	CString GetPath() const { return m_path; }

	/*! Returns parent-relative display name as shown in the explorer view */
	CString GetDisplayName() const { return m_displayName; }

	/**
	Returns a combination of SFGAO_FILESYSTEM, SFGAO_FOLDER, SFGAO_LINK, and SFGAO_STREAM for the item.

	@see IsFile(), IsDirectory(), IsFileSystem(), IsFolder, IsVirtualZipDirectory(), IsShortcut()
	*/
	int GetSFGAO() const { return m_SFGAO; }

	/*! Returns true if the item is a filesystem file. */
	BOOL IsFile() const { return GetType() == File; }

	/*! Returns true if the item is a filesystem folder. */
	BOOL IsDirectory() const { return GetType() == Directory; }

	/*! Returns true if the item is a filesystem file or folder. */
	BOOL IsFileSystem() const { return (IsFile() || IsDirectory()); }

	/*! Returns true if the item is Directory or a virtual folder. */
	BOOL IsFolder() const { return (GetSFGAO() & 0x20000000L); } // 0x20000000L = SFGAO_FOLDER

	/**
	Returns true if the item is a virtual zip directory, i.e.,
	a filesystem file that can also be browsed as a virtual folder.
	*/
	BOOL IsVirtualZipDirectory() const { return IsFile() && IsFolder(); }

	/*! Returns true if the item is a shortcut. */
	BOOL IsShortcut() const { return (GetSFGAO() & 0x00010000); } // 0x00010000 = SFGAO_LINK

																  /*! Sets item's type. */
	void SetType(Type type) { m_type = type; }

	/*! Sets item's path. */
	void SetPath(const CString& path) { m_path = path; }

	/*! Sets item's display name. */
	void SetDisplayName(const CString& name) { m_displayName = name; }

	/*! Sets item's SFGAO attributes. */
	void SetSFGAO(SFGAOF attr) { m_SFGAO = attr; }
private:
	Type m_type;
	CString m_path;
	CString m_displayName;
	SFGAOF m_SFGAO;
};

///////////////////////////////////////////////////////////////////////////

class CFileExplorerDoc;

class CFileExplorerView : public CView
{
private:
    CComPtr<IExplorerBrowser> m_spExplorerBrowser;
	bool m_bShowFrames;
	DWORD m_dwAdviseCookie;

protected: // create from serialization only
	CFileExplorerView();
	DECLARE_DYNCREATE(CFileExplorerView)

// Attributes
public:
	CFileExplorerDoc* GetDocument() const;

// Operations
public:
	void GetSelectedPaths(CStringArray& arrSelection);
	BOOL HasSelectedPath() const;
	bool NavigateTo(LPCTSTR szPath);

// Overrides
protected:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CFileExplorerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void OnBrowseToProfileFolder();

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnViewCommand(UINT nID);
	afx_msg void OnDestroy();
	afx_msg void OnViewBack();
	afx_msg void OnViewForward();
	afx_msg void OnViewFrames();
	afx_msg void OnViewDelete();
	afx_msg void OnViewRename();
	afx_msg void OnViewRefresh();
	afx_msg void OnShellCopy();
	afx_msg void OnShellCut();
	afx_msg void OnShellPaste();
	afx_msg void OnShellSelectAll();
	afx_msg void OnShellSearchPath();
	afx_msg void OnShellUndo();
	afx_msg void OnShellRedo();

protected:
	// forward events from IExplorerBrowserEvents to CView
	friend class CExplorerBrowserEvents;
    virtual HRESULT OnNavigationPending(PCIDLIST_ABSOLUTE pidlFolder);
    virtual void OnNavigationComplete(PCIDLIST_ABSOLUTE pidlFolder);
    virtual void OnViewCreated(IShellView *psv);
    virtual void OnNavigationFailed(PCIDLIST_ABSOLUTE pidlFolder);

	// shell helpers
	void GetCurrentFolder(CBrowserItem & item);
	void PPIDL2ExplorerBrowserItem(PCIDLIST_ABSOLUTE pidl, CBrowserItem & ebi);
	void IShellItem2ExplorerBrowserItem(IShellItem * item, CBrowserItem & ebi);
	CBrowserItem::Type SFGAO2ExplorerBrowserItemType(SFGAOF attr);
	void SelectItems(const CBrowserItem::List & items, BOOL notTakeFocus);
	void GetAllItems(CBrowserItem::List & items, int itemTypes);
	void ShellItemArrayToExplorerBrowserItemList(CComPtr<IShellItemArray> shellItems, CBrowserItem::List & items, int itemTypes);
	void PushTextToClipBoard(const CString & str);
	void InvokeCommandExplorer(const CString & strCommand);

	CString m_strNavigatedPath;
};

#ifndef _DEBUG
inline CFileExplorerDoc* CFileExplorerView::GetDocument() const
   { return reinterpret_cast<CFileExplorerDoc*>(m_pDocument); }
#endif

class CExplorerBrowserEvents : public CComObjectRootEx<CComSingleThreadModel>, public IExplorerBrowserEvents
{
private:
    CFileExplorerView* m_pView;

public:
    BEGIN_COM_MAP(CExplorerBrowserEvents)
        COM_INTERFACE_ENTRY(IExplorerBrowserEvents)
    END_COM_MAP()

public:
    void SetView(CFileExplorerView* pView)
    {
        m_pView = pView;
    }

    STDMETHOD(OnNavigationPending)(PCIDLIST_ABSOLUTE pidlFolder)
    {
        return m_pView ? m_pView->OnNavigationPending(pidlFolder) : E_FAIL;
    }

    STDMETHOD(OnViewCreated)(IShellView *psv)
    {
        if (m_pView)
            m_pView->OnViewCreated(psv);
        return S_OK;
    }

    STDMETHOD(OnNavigationComplete)(PCIDLIST_ABSOLUTE pidlFolder)
    {
        if (m_pView)
            m_pView->OnNavigationComplete(pidlFolder);
        return S_OK;
    }

    STDMETHOD(OnNavigationFailed)(PCIDLIST_ABSOLUTE pidlFolder)
    {
        if (m_pView)
            m_pView->OnNavigationFailed(pidlFolder);
        return S_OK;
    }
};