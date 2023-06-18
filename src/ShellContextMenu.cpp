/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "stdafx.h"
#include "ShellContextMenu.h"

#define MIN_ID 1
#define MAX_ID 10000

IContextMenu2 * g_IContext2 = NULL;
IContextMenu3 * g_IContext3 = NULL;

CFileExlorerContextMenu::CFileExlorerContextMenu()
{
	m_psfFolder = NULL;
	m_pidlArray = NULL;
	m_Menu = NULL;
}

CFileExlorerContextMenu::~CFileExlorerContextMenu()
{
	// free all allocated datas
	if (m_psfFolder && bDelete)
		m_psfFolder->Release();
	m_psfFolder = NULL;
	FreePIDLArray(m_pidlArray);
	m_pidlArray = NULL;

	if (m_Menu)
		delete m_Menu;
}

// this functions determines which version of IContextMenu is avaibale for those objects (always the highest one)
// and returns that interface
BOOL CFileExlorerContextMenu::GetContextMenu(void ** ppContextMenu, int & iMenuType)
{
	*ppContextMenu = NULL;
	LPCONTEXTMENU icm1 = NULL;

	// first we retrieve the normal IContextMenu interface (every object should have it)
	m_psfFolder->GetUIObjectOf(NULL, nItems, (LPCITEMIDLIST *)m_pidlArray, IID_IContextMenu, NULL, (void**)&icm1);

	if (icm1)
	{	// since we got an IContextMenu interface we can now obtain the higher version interfaces via that
		if (icm1->QueryInterface(IID_IContextMenu3, ppContextMenu) == NOERROR)
			iMenuType = 3;
		else if (icm1->QueryInterface(IID_IContextMenu2, ppContextMenu) == NOERROR)
			iMenuType = 2;

		if (*ppContextMenu)
			icm1->Release(); // we can now release version 1 interface, cause we got a higher one
		else
		{
			iMenuType = 1;
			*ppContextMenu = icm1;	// since no higher versions were found
		}							// redirect ppContextMenu to version 1 interface
	}
	else
		return (FALSE);	// something went wrong

	return (TRUE); // success
}

LRESULT CALLBACK CFileExlorerContextMenu::HookWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MENUCHAR:	// only supported by IContextMenu3
		if (g_IContext3)
		{
			LRESULT lResult = 0;
			g_IContext3->HandleMenuMsg2(message, wParam, lParam, &lResult);
			return (lResult);
		}
		break;

	case WM_DRAWITEM:
	case WM_MEASUREITEM:
		if (wParam)
			break; // if wParam != 0 then the message is not menu-related

	case WM_INITMENUPOPUP:
		if (g_IContext2)
			g_IContext2->HandleMenuMsg(message, wParam, lParam);
		else	// version 3
			g_IContext3->HandleMenuMsg(message, wParam, lParam);
		return (message == WM_INITMENUPOPUP ? 0 : TRUE); // inform caller that we handled WM_INITPOPUPMENU by ourself
		break;

	default:
		break;
	}

	// call original WndProc of window to prevent undefined bevhaviour of window
	return ::CallWindowProc((WNDPROC)GetProp(hWnd, TEXT("OldWndProc")), hWnd, message, wParam, lParam);
}

UINT CFileExlorerContextMenu::ShowContextMenu(CWnd *pWnd, CPoint pt)
{
	int iMenuType = 0;	// to know which version of IContextMenu is supported
	LPCONTEXTMENU pContextMenu;	// common pointer to IContextMenu and higher version interface

	if (!GetContextMenu((void**)&pContextMenu, iMenuType))
		return (0);	// something went wrong

	if (!m_Menu)
	{
		delete m_Menu;
		m_Menu = NULL;
		m_Menu = new CMenu;
		m_Menu->CreatePopupMenu();
	}

	// lets fill the our popupmenu  
	pContextMenu->QueryContextMenu(m_Menu->m_hMenu, m_Menu->GetMenuItemCount(), MIN_ID, MAX_ID, CMF_NORMAL | CMF_EXPLORE);

	// subclass window to handle menurelated messages in CFileExlorerContextMenu 
	//WNDPROC OldWndProc;
	//if (iMenuType > 1)	// only subclass if its version 2 or 3
	//{
	//	OldWndProc = (WNDPROC) SetWindowLong (pWnd->m_hWnd, GWL_WNDPROC, (DWORD) HookWndProc);
	//	if (iMenuType == 2)
	//		g_IContext2 = (LPCONTEXTMENU2) pContextMenu;
	//	else	// version 3
	//		g_IContext3 = (LPCONTEXTMENU3) pContextMenu;
	//}
	//else
	//	OldWndProc = NULL;

	UINT idCommand = m_Menu->TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN, pt.x, pt.y, pWnd);

	//if (OldWndProc) // unsubclass
	//	SetWindowLong (pWnd->m_hWnd, GWL_WNDPROC, (DWORD) OldWndProc);

	if (idCommand >= MIN_ID && idCommand <= MAX_ID)	// see if returned idCommand belongs to shell menu entries
	{
		InvokeCommand(pContextMenu, idCommand - MIN_ID);	// execute related command
		idCommand = 0;
	}

	pContextMenu->Release();
	g_IContext2 = NULL;
	g_IContext3 = NULL;

	return (idCommand);
}

BOOL CFileExlorerContextMenu::DoContextMenuCommand(CWnd * pWnd, const CString& strCommand)
{
	int iMenuType = 0;	// to know which version of IContextMenu is supported
	LPCONTEXTMENU pContextMenu;	// common pointer to IContextMenu and higher version interface

	if (!GetContextMenu((void**)&pContextMenu, iMenuType))
		return (0);	// something went wrong

	if (!m_Menu)
	{
		delete m_Menu;
		m_Menu = NULL;
		m_Menu = new CMenu;
		m_Menu->CreatePopupMenu();
	}

	// lets fill the our popupmenu  
	pContextMenu->QueryContextMenu(m_Menu->m_hMenu, m_Menu->GetMenuItemCount(), MIN_ID, MAX_ID, CMF_NORMAL | CMF_EXPLORE);
	UINT idCommand = -1;
	for (UINT id = MIN_ID; id <= MAX_ID; ++id)
	{
		CString strCommandMenu;
		m_Menu->GetMenuString(id, strCommandMenu, MF_BYCOMMAND);
		strCommandMenu.Replace(_T("&"), _T(""));
		strCommandMenu.Replace(_T(" "), _T(""));
		if (strCommandMenu.Find(strCommand) != -1)
		{
			idCommand = id - MIN_ID;
			break;
		}
	}

	if (idCommand == -1) return FALSE;

	CMINVOKECOMMANDINFO cmi = { 0 };
	cmi.cbSize = sizeof(CMINVOKECOMMANDINFO);
	cmi.lpVerb = (LPSTR)MAKEINTRESOURCE(idCommand);
	cmi.nShow = SW_SHOWNORMAL;

	BOOL bRet = SUCCEEDED(pContextMenu->InvokeCommand(&cmi));

	pContextMenu->Release();
	g_IContext2 = NULL;
	g_IContext3 = NULL;

	return bRet;
}

void CFileExlorerContextMenu::InvokeCommand(LPCONTEXTMENU pContextMenu, UINT idCommand)
{
	CMINVOKECOMMANDINFO cmi = { 0 };
	cmi.cbSize = sizeof(CMINVOKECOMMANDINFO);
	cmi.lpVerb = (LPSTR)MAKEINTRESOURCE(idCommand);
	cmi.nShow = SW_SHOWNORMAL;

	pContextMenu->InvokeCommand(&cmi);
}

void CFileExlorerContextMenu::SetObjects(const CString& strObject)
{
	// only one object is passed
	CStringArray strArray;
	strArray.Add(strObject);	// create a CStringArray with one element

	SetObjects(strArray);		// and pass it to SetObjects (CStringArray &strArray)
								// for further processing
}

void CFileExlorerContextMenu::SetObjects(CStringArray &strArray)
{
	// free all allocated datas
	if (m_psfFolder && bDelete)
		m_psfFolder->Release();
	m_psfFolder = NULL;
	FreePIDLArray(m_pidlArray);
	m_pidlArray = NULL;

	// get IShellFolder interface of Desktop (root of shell namespace)
	IShellFolder * psfDesktop = NULL;
	SHGetDesktopFolder(&psfDesktop);	// needed to obtain full qualified pidl

										// ParseDisplayName creates a PIDL from a file system path relative to the IShellFolder interface
										// but since we use the Desktop as our interface and the Desktop is the namespace root
										// that means that it's a fully qualified PIDL, which is what we need
	LPITEMIDLIST pidl = NULL;

#ifndef _UNICODE
	OLECHAR * olePath = NULL;
	CString str = strArray.GetAt(0);
	olePath = (OLECHAR *)calloc(str.GetLength() + 1, sizeof(OLECHAR));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str.GetBuffer(0), -1, olePath, strArray.GetAt(0).GetLength() + 1);
	str.ReleaseBuffer();
	psfDesktop->ParseDisplayName(NULL, 0, olePath, NULL, &pidl, NULL);
	free(olePath);
#else
	CString str = strArray.GetAt(0);
	psfDesktop->ParseDisplayName(NULL, 0, str.GetBuffer(0), NULL, &pidl, NULL);
#endif

	// now we need the parent IShellFolder interface of pidl, and the relative PIDL to that interface
	LPITEMIDLIST pidlItem = NULL;	// relative pidl
	SHBindToParentEx(pidl, IID_IShellFolder, (void **)&m_psfFolder, NULL);
	free(pidlItem);
	// get interface to IMalloc (need to free the PIDLs allocated by the shell functions)
	LPMALLOC lpMalloc = NULL;
	SHGetMalloc(&lpMalloc);
	lpMalloc->Free(pidl);

	// now we have the IShellFolder interface to the parent folder specified in the first element in strArray
	// since we assume that all objects are in the same folder (as it's stated in the MSDN)
	// we now have the IShellFolder interface to every objects parent folder

	IShellFolder * psfFolder = NULL;
	nItems = static_cast<int>(strArray.GetSize());
	for (int i = 0; i < nItems; i++)
	{
#ifndef _UNICODE
		olePath = (OLECHAR *)calloc(strArray.GetAt(i).GetLength() + 1, sizeof(OLECHAR));
		CString str = strArray.GetAt(i);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str.GetBuffer(0), -1, olePath, strArray.GetAt(i).GetLength() + 1);
		str.ReleaseBuffer();
		psfDesktop->ParseDisplayName(NULL, 0, olePath, NULL, &pidl, NULL);
		free(olePath);
#else
		CString str = strArray.GetAt(i);
		psfDesktop->ParseDisplayName(NULL, 0, str.GetBuffer(0), NULL, &pidl, NULL);
		str.ReleaseBuffer();
#endif
		m_pidlArray = (LPITEMIDLIST *)realloc(m_pidlArray, (i + 1) * sizeof(LPITEMIDLIST));
		// get relative pidl via SHBindToParent
		SHBindToParentEx(pidl, IID_IShellFolder, (void **)&psfFolder, (LPCITEMIDLIST *)&pidlItem);
		m_pidlArray[i] = CopyPIDL(pidlItem);	// copy relative pidl to pidlArray
		free(pidlItem);
		lpMalloc->Free(pidl);		// free pidl allocated by ParseDisplayName
		psfFolder->Release();
	}
	lpMalloc->Release();
	psfDesktop->Release();

	bDelete = TRUE;	// indicates that m_psfFolder should be deleted by CFileExlorerContextMenu
}

// only one full qualified PIDL has been passed
void CFileExlorerContextMenu::SetObjects(LPITEMIDLIST pidl)
{
	// free all allocated datas
	if (m_psfFolder && bDelete)
		m_psfFolder->Release();
	m_psfFolder = NULL;
	FreePIDLArray(m_pidlArray);
	m_pidlArray = NULL;

	// full qualified PIDL is passed so we need
	// its parent IShellFolder interface and its relative PIDL to that
	LPITEMIDLIST pidlItem = NULL;
	SHBindToParent((LPCITEMIDLIST)pidl, IID_IShellFolder, (void **)&m_psfFolder, (LPCITEMIDLIST *)&pidlItem);

	m_pidlArray = (LPITEMIDLIST *)malloc(sizeof(LPITEMIDLIST));	// allocate ony for one elemnt
	m_pidlArray[0] = CopyPIDL(pidlItem);


	// now free pidlItem via IMalloc interface (but not m_psfFolder, that we need later
	LPMALLOC lpMalloc = NULL;
	SHGetMalloc(&lpMalloc);
	lpMalloc->Free(pidlItem);
	lpMalloc->Release();

	nItems = 1;
	bDelete = TRUE;	// indicates that m_psfFolder should be deleted by CFileExlorerContextMenu
}

// IShellFolder interface with a relative pidl has been passed
void CFileExlorerContextMenu::SetObjects(IShellFolder *psfFolder, LPITEMIDLIST pidlItem)
{
	// free all allocated datas
	if (m_psfFolder && bDelete)
		m_psfFolder->Release();
	m_psfFolder = NULL;
	FreePIDLArray(m_pidlArray);
	m_pidlArray = NULL;

	m_psfFolder = psfFolder;

	m_pidlArray = (LPITEMIDLIST *)malloc(sizeof(LPITEMIDLIST));
	m_pidlArray[0] = CopyPIDL(pidlItem);

	nItems = 1;
	bDelete = FALSE;	// indicates wheter m_psfFolder should be deleted by CFileExlorerContextMenu
}

void CFileExlorerContextMenu::SetObjects(IShellFolder * psfFolder, LPITEMIDLIST *pidlArray, int nItemCount)
{
	// free all allocated datas
	if (m_psfFolder && bDelete)
		m_psfFolder->Release();
	m_psfFolder = NULL;
	FreePIDLArray(m_pidlArray);
	m_pidlArray = NULL;

	m_psfFolder = psfFolder;

	m_pidlArray = (LPITEMIDLIST *)malloc(nItemCount * sizeof(LPITEMIDLIST));

	for (int i = 0; i < nItemCount; i++)
		m_pidlArray[i] = CopyPIDL(pidlArray[i]);

	nItems = nItemCount;
	bDelete = FALSE;	// indicates wheter m_psfFolder should be deleted by CFileExlorerContextMenu
}

void CFileExlorerContextMenu::FreePIDLArray(LPITEMIDLIST *pidlArray)
{
	if (!pidlArray)
		return;

	int iSize = static_cast<int>(_msize(pidlArray) / sizeof(LPITEMIDLIST));

	for (int i = 0; i < iSize; i++)
		free(pidlArray[i]);
	free(pidlArray);
}

LPITEMIDLIST CFileExlorerContextMenu::CopyPIDL(LPCITEMIDLIST pidl, int cb)
{
	if (cb == -1)
		cb = GetPIDLSize(pidl); // Calculate size of list.

	LPITEMIDLIST pidlRet = (LPITEMIDLIST)calloc(cb + sizeof(USHORT), sizeof(BYTE));
	if (pidlRet)
		CopyMemory(pidlRet, pidl, cb);

	return (pidlRet);
}

UINT CFileExlorerContextMenu::GetPIDLSize(LPCITEMIDLIST pidl)
{
	if (!pidl)
		return 0;
	int nSize = 0;
	LPITEMIDLIST pidlTemp = (LPITEMIDLIST)pidl;
	while (pidlTemp->mkid.cb)
	{
		nSize += pidlTemp->mkid.cb;
		pidlTemp = (LPITEMIDLIST)(((LPBYTE)pidlTemp) + pidlTemp->mkid.cb);
	}
	return nSize;
}

CMenu * CFileExlorerContextMenu::GetMenu()
{
	if (!m_Menu)
	{
		m_Menu = new CMenu;
		m_Menu->CreatePopupMenu();	// create the popupmenu (its empty)
	}
	return (m_Menu);
}

// this is workaround function for the Shell API Function SHBindToParent
// SHBindToParent is not available under Win95/98
HRESULT CFileExlorerContextMenu::SHBindToParentEx(LPCITEMIDLIST pidl, REFIID riid, VOID **ppv, LPCITEMIDLIST *ppidlLast)
{
	HRESULT hr = 0;
	if (!pidl || !ppv)
		return E_POINTER;

	int nCount = GetPIDLCount(pidl);
	if (nCount == 0)	// desktop pidl of invalid pidl
		return E_POINTER;

	IShellFolder * psfDesktop = NULL;
	SHGetDesktopFolder(&psfDesktop);
	if (nCount == 1)	// desktop pidl
	{
		if ((hr = psfDesktop->QueryInterface(riid, ppv)) == S_OK)
		{
			if (ppidlLast)
				*ppidlLast = CopyPIDL(pidl);
		}
		psfDesktop->Release();
		return hr;
	}

	LPBYTE pRel = GetPIDLPos(pidl, nCount - 1);
	LPITEMIDLIST pidlParent = NULL;
	pidlParent = CopyPIDL(pidl, static_cast<int>(pRel - (LPBYTE)pidl));
	IShellFolder * psfFolder = NULL;

	if ((hr = psfDesktop->BindToObject(pidlParent, NULL, __uuidof (psfFolder), (void **)&psfFolder)) != S_OK)
	{
		free(pidlParent);
		psfDesktop->Release();
		return hr;
	}
	if ((hr = psfFolder->QueryInterface(riid, ppv)) == S_OK)
	{
		if (ppidlLast)
			*ppidlLast = CopyPIDL((LPCITEMIDLIST)pRel);
	}
	free(pidlParent);
	psfFolder->Release();
	psfDesktop->Release();
	return hr;
}

LPBYTE CFileExlorerContextMenu::GetPIDLPos(LPCITEMIDLIST pidl, int nPos)
{
	if (!pidl)
		return 0;
	int nCount = 0;

	BYTE * pCur = (BYTE *)pidl;
	while (((LPCITEMIDLIST)pCur)->mkid.cb)
	{
		if (nCount == nPos)
			return pCur;
		nCount++;
		pCur += ((LPCITEMIDLIST)pCur)->mkid.cb;	// + sizeof(pidl->mkid.cb);
	}
	if (nCount == nPos)
		return pCur;
	return NULL;
}

int CFileExlorerContextMenu::GetPIDLCount(LPCITEMIDLIST pidl)
{
	if (!pidl)
		return 0;

	int nCount = 0;
	BYTE*  pCur = (BYTE *)pidl;
	while (((LPCITEMIDLIST)pCur)->mkid.cb)
	{
		nCount++;
		pCur += ((LPCITEMIDLIST)pCur)->mkid.cb;
	}
	return nCount;
}