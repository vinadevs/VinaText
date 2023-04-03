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
#include "FileExplorerDoc.h"
#include "FileExplorerView.h"
#include "AppUtil.h"
#include "AppSettings.h"
#include "ShellContextMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFileExplorerView

IMPLEMENT_DYNCREATE(CFileExplorerView, CView)

BEGIN_MESSAGE_MAP(CFileExplorerView, CView)

    ON_COMMAND_EX(ID_VIEW_DETAILS, &CFileExplorerView::OnViewCommand)
    ON_COMMAND_EX(ID_VIEW_LARGEICON, &CFileExplorerView::OnViewCommand)
    ON_COMMAND_EX(ID_VIEW_LIST, &CFileExplorerView::OnViewCommand)
    ON_COMMAND_EX(ID_VIEW_SMALLICON, &CFileExplorerView::OnViewCommand)
	ON_COMMAND_EX(ID_VIEW_LINEUP, &CFileExplorerView::OnViewCommand)
	ON_COMMAND_EX(ID_VIEW_BYNAME, &CFileExplorerView::OnViewCommand)

	ON_WM_CREATE()
	ON_WM_SIZE()
    ON_WM_DESTROY()

END_MESSAGE_MAP()

// CFileExplorerView construction/destruction

CFileExplorerView::CFileExplorerView()
{
    m_bShowFrames = true;
    m_dwAdviseCookie = 0;

}

CFileExplorerView::~CFileExplorerView()
{
}

BOOL CFileExplorerView::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!CView::PreCreateWindow(cs))
        return FALSE;

    cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

    return TRUE;
}

// CFileExplorerView drawing

void CFileExplorerView::OnDraw(CDC* /*pDC*/)
{
    CFileExplorerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: add draw code for native data here
}


// CFileExplorerView printing

BOOL CFileExplorerView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CFileExplorerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CFileExplorerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}


// CFileExplorerView diagnostics

#ifdef _DEBUG
void CFileExplorerView::AssertValid() const
{
    CView::AssertValid();
}

void CFileExplorerView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CFileExplorerDoc* CFileExplorerView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFileExplorerDoc)));
    return (CFileExplorerDoc*)m_pDocument;
}
#endif //_DEBUG


// CFileExplorerView message handlers

int CFileExplorerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    HRESULT hr = SHCoCreateInstance(NULL, &CLSID_ExplorerBrowser, NULL, IID_PPV_ARGS(&m_spExplorerBrowser));

    if (SUCCEEDED(hr))
    { 
		m_spExplorerBrowser->SetOptions(EBO_SHOWFRAMES);
        
        FOLDERSETTINGS fs;
        fs.fFlags = 0;
        fs.ViewMode = FVM_DETAILS;
        hr = m_spExplorerBrowser->Initialize(m_hWnd, CRect(0, 0, 0, 0), &fs);
    
        if (SUCCEEDED(hr))
        {
            CComObject<CExplorerBrowserEvents>* pExplorerEvents;
            if (SUCCEEDED(CComObject<CExplorerBrowserEvents>::CreateInstance(&pExplorerEvents)))
            {
                pExplorerEvents->AddRef();
                
                pExplorerEvents->SetView(this);
                m_spExplorerBrowser->Advise(pExplorerEvents, &m_dwAdviseCookie);
                
                pExplorerEvents->Release();
            }
        }
    }

    return SUCCEEDED(hr) ? 0 : -1;
}

void CFileExplorerView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    m_spExplorerBrowser->SetRect(NULL, CRect(0, 0, cx, cy));
}

void CFileExplorerView::GetCurrentFolder(CBrowserItem& item)
{
	CComPtr<IFolderView2> spSV;
	if (SUCCEEDED(m_spExplorerBrowser->GetCurrentView(IID_PPV_ARGS(&spSV))))
	{
		CComPtr<IPersistFolder2> pf2;
		if (SUCCEEDED(spSV->GetFolder(IID_PPV_ARGS(&pf2))))
		{
			PIDLIST_ABSOLUTE pidl = nullptr;
			if (SUCCEEDED(pf2->GetCurFolder(&pidl)))
			{
				PPIDL2ExplorerBrowserItem(pidl, item);
				::CoTaskMemFree(pidl);
			}
		}
	}
}

void CFileExplorerView::PPIDL2ExplorerBrowserItem(PCIDLIST_ABSOLUTE pidl, CBrowserItem& ebi)
{
	CComPtr<IShellItem> si;
	if (SUCCEEDED(::SHCreateItemFromIDList(pidl, IID_PPV_ARGS(&si))))
	{
		IShellItem2ExplorerBrowserItem(si, ebi);
	}
}

void CFileExplorerView::IShellItem2ExplorerBrowserItem(IShellItem* item, CBrowserItem& ebi)
{
	static const SFGAOF mask = SFGAO_FILESYSTEM | SFGAO_FOLDER | SFGAO_STREAM | SFGAO_LINK;

	HRESULT hr;
	SFGAOF attr;

	hr = item->GetAttributes(mask, &attr);
	if (FAILED(hr))
	{
		return;
	}

	PWSTR name = nullptr;
	CString path, displayName;

	// will fail for non-filesystem items
	if (SUCCEEDED(item->GetDisplayName(SIGDN_FILESYSPATH, &name)))
	{
		path = name;
		::CoTaskMemFree(name);
	}

	hr = item->GetDisplayName(SIGDN_NORMALDISPLAY, &name);
	if (FAILED(hr))
	{
		return;
	}
	else
	{
		displayName = name;
		::CoTaskMemFree(name);
	}

	ebi.SetType(SFGAO2ExplorerBrowserItemType(attr));
	ebi.SetPath(path);
	ebi.SetDisplayName(displayName);
	ebi.SetSFGAO(attr);
}

CBrowserItem::Type CFileExplorerView::SFGAO2ExplorerBrowserItemType(SFGAOF attr)
{
	static const SFGAOF FileSystemFile = SFGAO_FILESYSTEM | SFGAO_STREAM;
	static const SFGAOF FileSystemDirectory = SFGAO_FILESYSTEM | SFGAO_FOLDER;
	static const SFGAOF VirtualZipDirectory = SFGAO_FILESYSTEM | SFGAO_FOLDER | SFGAO_STREAM;

	// remove the the attributes we are not interested in
	attr &= (SFGAO_FILESYSTEM | SFGAO_FOLDER | SFGAO_STREAM);

	switch (attr)
	{
	case 0:
		return CBrowserItem::Unknown;
	case FileSystemFile:
	case VirtualZipDirectory:
		return CBrowserItem::File;
	case FileSystemDirectory:
		return CBrowserItem::Directory;
	default:
		return CBrowserItem::Other;
	}
}

BOOL CFileExplorerView::HasSelectedPath() const
{
	CComPtr<IShellView> spSV;
	if (SUCCEEDED(m_spExplorerBrowser->GetCurrentView(IID_PPV_ARGS(&spSV))))
	{
		CComPtr<IDataObject> spDataObject;
		if (SUCCEEDED(spSV->GetItemObject(SVGIO_SELECTION, IID_PPV_ARGS(&spDataObject))))
		{
			FORMATETC fmt = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
			STGMEDIUM stg;
			stg.tymed = TYMED_HGLOBAL;
			if (SUCCEEDED(spDataObject->GetData(&fmt, &stg)))
			{
				HDROP hDrop = (HDROP)GlobalLock(stg.hGlobal);

				UINT uNumFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
				if (uNumFiles > 0)
				{
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

bool CFileExplorerView::NavigateTo(LPCTSTR szPath)
{
    HRESULT hr = S_OK;
	LPITEMIDLIST pidlBrowse;

	if (FAILED(hr = SHParseDisplayName(szPath, NULL, &pidlBrowse, 0, NULL)))
    {
        ATLTRACE("SHParseDisplayName Failed! hr = %d\n", hr);
		return false;
	}

    if (FAILED(hr = m_spExplorerBrowser->BrowseToIDList(pidlBrowse, 0)))
        ATLTRACE("BrowseToIDList Failed! hr = %d\n", hr);

    ILFree(pidlBrowse);

	return SUCCEEDED(hr);
}

void CFileExplorerView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    TCHAR szCurrentDir[_MAX_PATH + 1];
    szCurrentDir[_MAX_PATH] = 0;
    
	if (PathFileExists(AppUtils::GetVinaTextApp()->m_strFileExplorerNavigatePath))
	{
		if (!NavigateTo(AppUtils::GetVinaTextApp()->m_strFileExplorerNavigatePath))
		{
			OnBrowseToProfileFolder();
		}
	}
	else if (!GetCurrentDirectory(_MAX_PATH, szCurrentDir) || !NavigateTo(szCurrentDir))
	{
        OnBrowseToProfileFolder();
    }
	LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Host Application] Create host document for File Explorer successfuly..."));
}

BOOL CFileExplorerView::PreTranslateMessage(MSG * pMsg)
{
	switch (pMsg->message)
	{
		case WM_XBUTTONDOWN:
		{
			WORD fwButtonX = GET_XBUTTON_WPARAM(pMsg->wParam);
			switch (fwButtonX)
			{
				case XBUTTON1:
				{
					OnViewBack();
					return TRUE;
				}
				case XBUTTON2:
				{
					OnViewForward();
					return TRUE;
				}
				break;
			}
		}
		case WM_KEYDOWN:
		{
			switch (pMsg->wParam)
			{
				case VK_BACK:
				{
					OnViewBack();
					return TRUE;
				}
				break;
				case VK_DELETE:
				{
					OnViewDelete();
					return TRUE;
				}
				break;
				case VK_F2:
				{
					OnViewRename();
					return TRUE;
				}
				break;
				case VK_F5:
				{
					OnViewRefresh();
					return TRUE;
				}
				break;
				case 'C':
				{
					if (GetKeyState(VK_CONTROL) & 0x8000 && GetKeyState(VK_SHIFT) & 0x8000)
					{
						if (HasSelectedPath())
						{
							CStringArray arrSelectedPaths;
							GetSelectedPaths(arrSelectedPaths);
							if (arrSelectedPaths.GetCount() > 0)
							{		
								PushTextToClipBoard(arrSelectedPaths[0]);
								LOG_OUTPUT_MESSAGE_FORMAT(_T("> [From File Explorer] Copied full path %s..."), arrSelectedPaths[0]);
							}
							return TRUE;
						}
						else if (PathFileExists(m_strNavigatedPath))
						{
							PushTextToClipBoard(m_strNavigatedPath);
							LOG_OUTPUT_MESSAGE_FORMAT(_T("> [From File Explorer] Copied full path %s..."), m_strNavigatedPath);
							return TRUE;
						}
					}
					else if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnShellCopy();
						return TRUE;
					}
				}
				break;
				case 'X':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnShellCut();
						return TRUE;
					}
				}
				break;
				case 'V':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnShellPaste();
						return TRUE;
					}
				}
				break;
				case 'A':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnShellSelectAll();
						return TRUE;
					}
				}
				break;
				case 'F':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnShellSearchPath();
						return TRUE;
					}
				}
				break;
				/*case 'Z':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnShellUndo();
						return TRUE;
					}
				}
				break;
				case 'Y':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnShellRedo();
						return TRUE;
					}
				}*/
				break;
			}
		}
	}
	return CView::PreTranslateMessage(pMsg);
}

void CFileExplorerView::OnBrowseToProfileFolder()
{
    HRESULT hr = S_OK;
    LPITEMIDLIST pidlBrowse = NULL;

    if (SUCCEEDED(hr = SHGetFolderLocation(NULL, CSIDL_PROFILE, NULL, 0, &pidlBrowse)))
    {
        if (FAILED(hr = m_spExplorerBrowser->BrowseToIDList(pidlBrowse, 0)))
            ATLTRACE("BrowseToIDList Failed! hr = %d\n", hr);

        ILFree(pidlBrowse);
    }
    else
    {
        ATLTRACE("SHGetFolderLocation Failed! hr = %d\n", hr);
    }

	if (FAILED(hr))
		AfxMessageBox(_T("[Error] Navigation failed!"));
}

BOOL CFileExplorerView::OnViewCommand(UINT nID)
{
    UINT uViewMode;

    switch(nID)
    {
    case ID_VIEW_DETAILS:
        uViewMode = FVM_DETAILS;
        break;
    case ID_VIEW_LARGEICON:
        uViewMode = FVM_ICON;
        break;
    case ID_VIEW_LIST:
        uViewMode = FVM_LIST;
        break;
    case ID_VIEW_SMALLICON:
        uViewMode = FVM_SMALLICON;
        break;
    case ID_FILE_EXPLORER_VIEW_THUMBNAILS:
        uViewMode = FVM_THUMBNAIL;
        break;
    case ID_FILE_EXPLORER_VIEW_THUMBSTRIP:
        uViewMode = FVM_THUMBSTRIP;
        break;
    case ID_FILE_EXPLORER_VIEW_TILES:
        uViewMode = FVM_TILE;
        break;
    }
    
    FOLDERSETTINGS fs = {uViewMode, 0};
    m_spExplorerBrowser->SetFolderSettings(&fs);
    return TRUE;
}

void CFileExplorerView::OnDestroy()
{
    CView::OnDestroy();
    
    if(m_dwAdviseCookie)
    {
        m_spExplorerBrowser->Unadvise(m_dwAdviseCookie);
    }

    m_spExplorerBrowser->Destroy();
}

void CFileExplorerView::OnViewBack()
{
    m_spExplorerBrowser->BrowseToIDList(NULL, SBSP_NAVIGATEBACK);
}

void CFileExplorerView::OnViewForward()
{
    m_spExplorerBrowser->BrowseToIDList(NULL, SBSP_NAVIGATEFORWARD);
}

void CFileExplorerView::OnViewFrames()
{
    m_bShowFrames = !m_bShowFrames;
	if (m_bShowFrames)
	{
		m_spExplorerBrowser->SetOptions(EBO_SHOWFRAMES);
	}
	else
	{
		m_spExplorerBrowser->SetOptions(EBO_NONE);
	}
}

static CString GetFolderDisplayName(PCIDLIST_ABSOLUTE pidlFolder)
{
    CString strDisplayName;
    CComPtr<IShellFolder> spSF;
    if (SUCCEEDED(SHGetDesktopFolder(&spSF)))
    {
        STRRET srDisplayName;
        if (SUCCEEDED(spSF->GetDisplayNameOf(pidlFolder, SHGDN_FORPARSING, &srDisplayName)))
        {
            LPTSTR szDisplayName = NULL;
            StrRetToStr(&srDisplayName, pidlFolder, &szDisplayName);
            strDisplayName = szDisplayName;
            CoTaskMemFree(szDisplayName);
        }
    }    
    return strDisplayName;
}

HRESULT CFileExplorerView::OnNavigationPending(PCIDLIST_ABSOLUTE pidlFolder)
{
    ATLTRACE("OnNavigationPending %S\n", static_cast<LPCTSTR>(GetFolderDisplayName(pidlFolder)));
    return S_OK;
}

void CFileExplorerView::OnNavigationComplete(PCIDLIST_ABSOLUTE pidlFolder)
{
	//ATLTRACE("OnNavigationComplete %S\n", static_cast<LPCTSTR>(GetFolderDisplayName(pidlFolder)));
	m_strNavigatedPath = static_cast<LPCTSTR>(GetFolderDisplayName(pidlFolder));
	if (PathFileExists(m_strNavigatedPath))
	{
		m_pDocument->SetPathName(m_strNavigatedPath, FALSE);
	}
}

void CFileExplorerView::OnViewCreated(IShellView *psv)
{
    //ATLTRACE("OnViewCreated\n");
}

void CFileExplorerView::OnNavigationFailed(PCIDLIST_ABSOLUTE pidlFolder)
{
    //ATLTRACE("OnNavigationFailed %S\n", static_cast<LPCTSTR>(GetFolderDisplayName(pidlFolder)));
}

void CFileExplorerView::GetSelectedPaths(CStringArray& arrSelection)
{
    CComPtr<IShellView> spSV;
    if (SUCCEEDED(m_spExplorerBrowser->GetCurrentView(IID_PPV_ARGS(&spSV))))
    {
        CComPtr<IDataObject> spDataObject;
        if (SUCCEEDED(spSV->GetItemObject(SVGIO_SELECTION, IID_PPV_ARGS(&spDataObject))))
        {
			FORMATETC fmt = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
			STGMEDIUM stg;
			stg.tymed =  TYMED_HGLOBAL;

			if (SUCCEEDED(spDataObject->GetData(&fmt, &stg)))
			{
				HDROP hDrop = (HDROP) GlobalLock ( stg.hGlobal );

				UINT uNumFiles = DragQueryFile ( hDrop, 0xFFFFFFFF, NULL, 0 );
				HRESULT hr = S_OK;

				for(UINT i = 0; i < uNumFiles; i++)
				{
					TCHAR szPath[_MAX_PATH];
					szPath[0] = 0;
					DragQueryFile(hDrop, i, szPath, MAX_PATH);
			        
					if (szPath[0] != 0)
						arrSelection.Add(szPath);	
				}
			    
				GlobalUnlock ( stg.hGlobal );
				ReleaseStgMedium ( &stg );
            }
        }
    }
}

void CFileExplorerView::OnViewDelete()
{
	InvokeCommandExplorer(_T("Delete"));
}

void CFileExplorerView::OnViewRename()
{
	CStringArray arrSelectedPaths;
	GetSelectedPaths(arrSelectedPaths);

	CString strDisplayName;
	CComPtr<IShellFolder> spSF;
	TCHAR newName[256]; WCHAR newNameW[256];
	if (SUCCEEDED(SHGetDesktopFolder(&spSF)))
	{
#ifdef UNICODE
		wcsncpy_s(newNameW, 256, newName, _TRUNCATE);
#else
		MultiByteToWideChar(CP_ACP, 0, newName, -1, newNameW, 256);
#endif
	/*	if (IDOK == EditBox(_T("bbLean"), _T("Enter new name:"), arrSelectedPaths, newName, 256))
		{
			spSF->SetNameOf(NULL, pidlItem, newNameW, SHGDN_NORMAL, NULL);
		}*/
	}
}

void CFileExplorerView::OnViewRefresh()
{
	CComPtr<IShellView> spSV;
	if (SUCCEEDED(m_spExplorerBrowser->GetCurrentView(IID_PPV_ARGS(&spSV))))
	{
		spSV->Refresh();
	}
}

void CFileExplorerView::OnShellCopy()
{
	InvokeCommandExplorer(_T("Copy"));
}

void CFileExplorerView::OnShellCut()
{
	InvokeCommandExplorer(_T("Cut"));
}

void CFileExplorerView::OnShellPaste()
{
	InvokeCommandExplorer(_T("Paste"));
}

void CFileExplorerView::OnShellSelectAll()
{
	CBrowserItem::List allItems;
	GetAllItems(allItems, CBrowserItem::Type::File | CBrowserItem::Type::Directory);
	SelectItems(allItems, FALSE);
}

void CFileExplorerView::OnShellSearchPath()
{
	CString strSearchPath = m_strNavigatedPath;
	if (HasSelectedPath())
	{
		CStringArray arrSelectedPaths;
		GetSelectedPaths(arrSelectedPaths);
		if (arrSelectedPaths.GetCount() > 0)
		{
			strSearchPath = arrSelectedPaths[0];
		}
	}
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;
	pFrame->GetFileExplorerCtrl().DoNavigateSearchFiles(strSearchPath);
}

void CFileExplorerView::OnShellUndo()
{
	InvokeCommandExplorer(_T("Undo"));
}

void CFileExplorerView::OnShellRedo()
{
	InvokeCommandExplorer(_T("Redo"));
}

void CFileExplorerView::InvokeCommandExplorer(const CString & strCommand)
{
	CFileExlorerContextMenu scm;
	CStringArray arrSelectedPaths;
	if (strCommand == _T("Paste") || strCommand == _T("Redo") || strCommand == _T("Undo"))
	{
		arrSelectedPaths.Add(m_strNavigatedPath);
		scm.SetObjects(arrSelectedPaths);
		if (!scm.DoContextMenuCommand(this, strCommand))
		{
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> [File Explorer Error] Invoke command : %s failed..."), strCommand);
		}
	}
	else
	{
		GetSelectedPaths(arrSelectedPaths);
		if (arrSelectedPaths.GetCount() > 0)
		{
			scm.SetObjects(arrSelectedPaths);
			if (!scm.DoContextMenuCommand(this, strCommand))
			{
				LOG_OUTPUT_MESSAGE_FORMAT(_T("> [File Explorer Error] Invoke command : %s failed..."), strCommand);
			}
		}
	}
}

void CFileExplorerView::SelectItems(const CBrowserItem::List& items, BOOL notTakeFocus)
{
	CComPtr<IFolderView2> fv2;
	if (FAILED(m_spExplorerBrowser->GetCurrentView(IID_PPV_ARGS(&fv2))))
	{
		return;
	}

	UINT flags = SVSI_SELECT | SVSI_ENSUREVISIBLE;

	if (notTakeFocus)
		flags |= SVSI_NOTAKEFOCUS;

	for (int i = 0; i < items.size(); ++i)
	{
		fv2->SelectItem(i, flags);
	}
}

void CFileExplorerView::GetAllItems(CBrowserItem::List& items, int itemTypes)
{
	CComPtr<IFolderView2> fv2;
	if (FAILED(m_spExplorerBrowser->GetCurrentView(IID_PPV_ARGS(&fv2))))
	{
		return;
	}

	CComPtr<IShellItemArray> sia; 
	if (FAILED(fv2->Items(SVGIO_ALLVIEW | SVGIO_FLAG_VIEWORDER, IID_PPV_ARGS(&sia)))) // no items
	{
		return;
	}

	ShellItemArrayToExplorerBrowserItemList(sia, items, itemTypes);
}

void CFileExplorerView::ShellItemArrayToExplorerBrowserItemList(CComPtr<IShellItemArray> shellItems, CBrowserItem::List& items, int itemTypes)
{
	DWORD count = 0;
	if (FAILED(shellItems->GetCount(&count)))
	{
		return;
	}

	CBrowserItem::List tmpItems;

	tmpItems.reserve(static_cast<size_t>(count));

	for (DWORD i = 0; i < count; ++i)
	{
		CComPtr<IShellItem> si;
		CBrowserItem ebi;

		if (FAILED(shellItems->GetItemAt(i, &si)))
		{
			return;
		}

		IShellItem2ExplorerBrowserItem(si, ebi);

		if ((itemTypes & ebi.GetType()))
			tmpItems.push_back(ebi);
	}

	items = std::move(tmpItems);
}

void CFileExplorerView::PushTextToClipBoard(const CString& str)
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