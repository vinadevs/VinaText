/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "FileBrowser.h"

/////////////////////////////////////////////////////////////////////////////
//
// for save as image
//

CImageSaveDialog::CImageSaveDialog(BOOL bOpenFileDialog,
	LPCTSTR lpszDefExt /*= NULL*/,
	LPCTSTR lpszFileName/*= NULL*/,
	DWORD dwFlags /*= OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT*/,
	LPCTSTR lpszFilter/*= NULL*/,
	CWnd* pParentWnd/*= NULL*/,
	DWORD dwSize /*= 0*/,
	BOOL bVistaStyle /*= TRUE*/)
	: CFileDialog(bOpenFileDialog,
		lpszDefExt,
		lpszFileName,
		dwFlags, lpszFilter,
		pParentWnd,
		dwSize,
		bVistaStyle)
{
}

void CImageSaveDialog::OnTypeChange()
{
	// TODO: Add your specialized code here and/or call the base class
	CString sFileName(GetFileName());
	if (sFileName.IsEmpty())
	{
		CFileDialog::OnTypeChange();
		return;
	}
	CString sExt(GetFileExt());
	switch (GetOFN().nFilterIndex)
	{
	case 2:
		sExt.Format(_T("jpg"));
		break;
	case 3:
		sExt.Format(_T("bmp"));
		break;
	case 4:
		sExt.Format(_T("png"));
		break;
	case 5:
		sExt.Format(_T("tiff"));
		break;
	case 6:
		sExt.Format(_T("gif"));
		break;
	}
	int nDotIndex = sFileName.ReverseFind('.');
	if (-1 != nDotIndex)
	{
		int nDiff = sFileName.GetLength() - nDotIndex;
		if (nDotIndex == (sFileName.GetLength() - nDiff))
		{
			sFileName = sFileName.Left(sFileName.GetLength() - nDiff);
		}
	}
	CString sTemp;
	sTemp.Format(_T("%s.%s"), sFileName, sExt);
	IFileDialog* pIFD = GetIFileSaveDialog();
	CStringW sFileNameW(sTemp);
	pIFD->SetFileName(sFileNameW);
	pIFD->Release();
}

/////////////////////////////////////////////////////////////////////////////
//
// for save as text
//

CEditSaveDialog::CEditSaveDialog(BOOL bOpenFileDialog,
	LPCTSTR lpszDefExt /*= NULL*/,
	LPCTSTR lpszFileName/*= NULL*/,
	DWORD dwFlags /*= OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT*/,
	LPCTSTR lpszFilter/*= NULL*/,
	CWnd* pParentWnd/*= NULL*/,
	DWORD dwSize /*= 0*/,
	BOOL bVistaStyle /*= TRUE*/)
	: CFileDialog(bOpenFileDialog,
		lpszDefExt,
		lpszFileName,
		dwFlags, lpszFilter,
		pParentWnd,
		dwSize,
		bVistaStyle)
{
}

void CEditSaveDialog::OnTypeChange()
{
	// TODO: Add your specialized code here and/or call the base class
	CString sFileName(GetFileName());
	if (sFileName.IsEmpty())
	{
		CFileDialog::OnTypeChange();
		return;
	}
	CString sExt(GetFileExt());
	switch (GetOFN().nFilterIndex)
	{
		case 2: sExt.Format(_T("txt")); break;
		case 3: sExt.Format(_T("py")); break;
		case 4: sExt.Format(_T("c")); break;
		case 5: sExt.Format(_T("cs")); break;
		case 6: sExt.Format(_T("cpp")); break;
		case 7: sExt.Format(_T("json")); break;
		case 8: sExt.Format(_T("java")); break;
		case 9: sExt.Format(_T("js")); break;
		case 10: sExt.Format(_T("xml")); break;
		case 11: sExt.Format(_T("mib")); break;
		case 12: sExt.Format(_T("asp")); break;
		case 13: sExt.Format(_T("ada")); break;
		case 14: sExt.Format(_T("asm")); break;
		case 15: sExt.Format(_T("au3")); break;
		case 16: sExt.Format(_T("avs")); break;
		case 17: sExt.Format(_T("bc")); break;
		case 18: sExt.Format(_T("bat")); break;
		case 19: sExt.Format(_T("bb")); break;
		case 20: sExt.Format(_T("cmake")); break;
		case 21: sExt.Format(_T("cbl")); break;
		case 22: sExt.Format(_T("css")); break;
		case 23: sExt.Format(_T("ml")); break;
		case 24: sExt.Format(_T("coffee")); break;
		case 25: sExt.Format(_T("orc")); break;
		case 26: sExt.Format(_T("d")); break;
		case 27: sExt.Format(_T("diff")); break;
		case 28: sExt.Format(_T("src")); break;
		case 29: sExt.Format(_T("erl")); break;
		case 30: sExt.Format(_T("as")); break;
		case 31: sExt.Format(_T("forth")); break;
		case 32: sExt.Format(_T("f77")); break;
		case 33: sExt.Format(_T("f")); break;
		case 34: sExt.Format(_T("bas")); break;
		case 35: sExt.Format(_T("hs")); break;
		case 36: sExt.Format(_T("html")); break;
		case 37: sExt.Format(_T("iss")); break;
		case 38: sExt.Format(_T("hex")); break;
		case 39: sExt.Format(_T("jsp")); break;
		case 40: sExt.Format(_T("kix")); break;
		case 41: sExt.Format(_T("tex")); break;
		case 42: sExt.Format(_T("lsp")); break;
		case 43: sExt.Format(_T("lua")); break;
		case 44: sExt.Format(_T("m")); break;
		case 45: sExt.Format(_T("mms")); break;
		case 46: sExt.Format(_T("ini")); break;
		case 47: sExt.Format(_T("nfo")); break;
		case 48: sExt.Format(_T("mak")); break;
		case 49: sExt.Format(_T("mot")); break;
		case 50: sExt.Format(_T("nim")); break;
		case 51: sExt.Format(_T("txt")); break;
		case 52: sExt.Format(_T("nsi")); break;
		case 53: sExt.Format(_T("osx")); break;
		case 54: sExt.Format(_T("mm")); break;
		case 55: sExt.Format(_T("php")); break;
		case 56: sExt.Format(_T("pas")); break;
		case 57: sExt.Format(_T("pl")); break;
		case 58: sExt.Format(_T("ps")); break;
		case 59: sExt.Format(_T("properties")); break;
		case 60: sExt.Format(_T("pb")); break;
		case 61: sExt.Format(_T("r")); break;
		case 62: sExt.Format(_T("r2")); break;
		case 63: sExt.Format(_T("rb")); break;
		case 64: sExt.Format(_T("rs")); break;
		case 65: sExt.Format(_T("scm")); break;
		case 66: sExt.Format(_T("st")); break;
		case 67: sExt.Format(_T("sql")); break;
		case 68: sExt.Format(_T("swift")); break;
		case 69: sExt.Format(_T("tex")); break;
		case 70: sExt.Format(_T("tek")); break;
		case 71: sExt.Format(_T("tcl")); break;
		case 72: sExt.Format(_T("bash")); break;
		case 73: sExt.Format(_T("vhd")); break;
		case 74: sExt.Format(_T("v")); break;
		case 75: sExt.Format(_T("vb")); break;
		case 76: sExt.Format(_T("pro")); break;
		case 77: sExt.Format(_T("ps1")); break;
		case 78: sExt.Format(_T("rc")); break;
		case 79: sExt.Format(_T("yml")); break;
		case 80: sExt.Format(_T("tab")); break;
		case 81: sExt.Format(_T("reg")); break;
		case 82: sExt.Format(_T("scp")); break;
		case 83: sExt.Format(_T("t2tz")); break;
	}
	int nDotIndex = sFileName.ReverseFind('.');
	if (-1 != nDotIndex)
	{
		int nDiff = sFileName.GetLength() - nDotIndex;
		if (nDotIndex == (sFileName.GetLength() - nDiff))
		{
			sFileName = sFileName.Left(sFileName.GetLength() - nDiff);
		}
	}
	CString sTemp;
	sTemp.Format(_T("%s.%s"), sFileName, sExt);
	IFileDialog* pIFD = GetIFileSaveDialog();
	CStringW sFileNameW(sTemp);
	pIFD->SetFileName(sFileNameW);
	pIFD->Release();
}