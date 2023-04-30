/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "afxtaskdialog.h"
#include "PathUtil.h"
#include "AppUtil.h"
#include "AppSettings.h"
#include "Hpsutils.h"
#include "FileUtil.h"
#include "Textfile.h"           

///////////////// PATH HELPERS //////////////////////////

HMODULE PathUtils::LoadEditorDll(CString strEditorDll)
{
	CString strDll = STR_EDITORDLL;
	if (!strEditorDll.IsEmpty())
	{
		strDll = strEditorDll;
	}
	HMODULE hModule = ::LoadLibrary(strDll);
	return hModule;
}

HMODULE PathUtils::LoadLexerDll(CString strLexerDll)
{
	CString strLexer = STR_LEXERDLL;
	if (!strLexerDll.IsEmpty())
	{
		strLexer = strLexerDll;
	}
	HMODULE hModule = ::LoadLibrary(strLexer);
	return hModule;
}

CString PathUtils::GetVinaTextPath()
{
	CString strPath;
	VERIFY(::GetModuleFileName(AfxGetApp()->m_hInstance, strPath.GetBufferSetLength(_MAX_PATH), _MAX_PATH));
	strPath.ReleaseBuffer();
	int nIndex = strPath.ReverseFind(_T('\\'));
	if (nIndex > 0)
	{
		strPath = strPath.Left(nIndex + 1);
	}
	else
	{
		strPath.Empty();
	}
	return strPath;
}

CString PathUtils::GetVinaTextExePath()
{
	return PathUtils::GetVinaTextPath() + _T("VinaText.exe");
}

CString PathUtils::GetVinaTextTempPath()
{
	CString strPath;
	{
		::GetTempPath(_MAX_PATH, strPath.GetBufferSetLength(_MAX_PATH));
		strPath.ReleaseBuffer();
		strPath.Append(_T("VinaText\\"));
		if (FALSE == PathFileExists(strPath))
		{
			if (FALSE == CreateDirectory(strPath, NULL))
			{
				strPath = _T("");
			}
		}
	}
	return strPath;
}

CString PathUtils::GetVinaTextBookmarkPath()
{
	return PathUtils::GetVinaTextAppDataPath() + _T("path-book-mark.dat");
}

CString PathUtils::GetVinaTextAppDataPath()
{
	CString strPath;
	{
		TCHAR* pEnviAppFolder = NULL;
		{
			::SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, strPath.GetBufferSetLength(_MAX_PATH));
			strPath.ReleaseBuffer();
		}

		strPath.Append(_T("\\VinaText\\"));
		if (FALSE == PathFileExists(strPath))
		{
			if (FALSE == CreateDirectory(strPath, NULL))
			{
				strPath = _T("");
				return strPath;
			}
		}
	}
	return strPath;
}

CString PathUtils::GetLanguageSettingFilePath(const CString& strLanguageName)
{
	CString strLanguageSettingFilePath;
	if (strLanguageName == _T("cpp"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\cpp-data.ee-package");
	}
	else if (strLanguageName == _T("asm"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\assembly-data.ee-package");
	}
	else if (strLanguageName == _T("c"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\c-data.ee-package");
	}
	else if (strLanguageName == _T("cs"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\cshape-data.ee-package");
	}
	else if (strLanguageName == _T("java"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\java-data.ee-package");
	}
	else if (strLanguageName == _T("html"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\html-data.ee-package");
	}
	else if (strLanguageName == _T("css"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\css-data.ee-package");
	}
	else if (strLanguageName == _T("javascript"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\javascript-data.ee-package");
	}
	else if (strLanguageName == _T("vb"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\visualbasic-data.ee-package");
	}
	else if (strLanguageName == _T("tcl"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\tcl-data.ee-package");
	}
	else if (strLanguageName == _T("matlab"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\matlab-data.ee-package");
	}
	else if (strLanguageName == _T("verilog"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\verilog-data.ee-package");
	}
	else if (strLanguageName == _T("rust"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\rust-data.ee-package");
	}
	else if (strLanguageName == _T("go"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\go-data.ee-package");
	}
	else if (strLanguageName == _T("php"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\php-data.ee-package");
	}
	else if (strLanguageName == _T("perl"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\perl-data.ee-package");
	}
	else if (strLanguageName == _T("ruby"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\ruby-data.ee-package");
	}
	else if (strLanguageName == _T("powershell"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\powershell-data.ee-package");
	}
	else if (strLanguageName == _T("python"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\python-data.ee-package");
	}
	else if (strLanguageName == _T("pascal"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\pascal-data.ee-package");
	}
	else if (strLanguageName == _T("json"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\json-data.ee-package");
	}
	else if (strLanguageName == _T("xml"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\xml-data.ee-package");
	}
	else if (strLanguageName == _T("ada"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\ada-data.ee-package");
	}
	else if (strLanguageName == _T("lua"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\lua-data.ee-package");
	}
	else if (strLanguageName == _T("vhdl"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\vhdl-data.ee-package");
	}
	else if (strLanguageName == _T("typescript"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\typescript-data.ee-package");
	}
	else if (strLanguageName == _T("erlang"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\erlang-data.ee-package");
	}
	else if (strLanguageName == _T("fortran"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\fortran-data.ee-package");
	}
	else if (strLanguageName == _T("cmake"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\cmake-data.ee-package");
	}
	else if (strLanguageName == _T("bash"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\bash-data.ee-package");
	}
	else if (strLanguageName == _T("markdown"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\markdown-data.ee-package");
	}
	else if (strLanguageName == _T("protobuf"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\protobuf-data.ee-package");
	}
	else if (strLanguageName == _T("r"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\r-data.ee-package");
	}
	else if (strLanguageName == _T("sql"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\sql-data.ee-package");
	}
	else if (strLanguageName == _T("autoit"))
	{
		strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\autoit-data.ee-package");
	}
	else if (strLanguageName == _T("freebasic"))
	{
	strLanguageSettingFilePath = PathUtils::GetVinaTextPackagePath() + _T("language-packages\\freebasic-data.ee-package");
	}
	return strLanguageSettingFilePath;
}

CString PathUtils::GetLanguageTemplateFilePath(VINATEXT_SUPPORTED_LANGUAGE language)
{
	CString strLanguageTemplateFilePath;
	if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP)
	{
		strLanguageTemplateFilePath = PathUtils::GetVinaTextPackagePath() + _T("template-packages\\cpp-template.ee-package");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C)
	{
		strLanguageTemplateFilePath = PathUtils::GetVinaTextPackagePath() + _T("template-packages\\c-template.ee-package");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CSHAPE)
	{
		strLanguageTemplateFilePath = PathUtils::GetVinaTextPackagePath() + _T("template-packages\\cshape-template.ee-package");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
	{
		strLanguageTemplateFilePath = PathUtils::GetVinaTextPackagePath() + _T("template-packages\\java-template.ee-package");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
	{
		strLanguageTemplateFilePath = PathUtils::GetVinaTextPackagePath() + _T("template-packages\\javascript-template.ee-package");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VISUALBASIC)
	{
		strLanguageTemplateFilePath = PathUtils::GetVinaTextPackagePath() + _T("template-packages\\visualbasic-template.ee-package");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUST)
	{
		strLanguageTemplateFilePath = PathUtils::GetVinaTextPackagePath() + _T("template-packages\\rust-template.ee-package");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_GOLANG)
	{
		strLanguageTemplateFilePath = PathUtils::GetVinaTextPackagePath() + _T("template-packages\\golang-template.ee-package");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PHP)
	{
		strLanguageTemplateFilePath = PathUtils::GetVinaTextPackagePath() + _T("template-packages\\php-template.ee-package");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
	{
		strLanguageTemplateFilePath = PathUtils::GetVinaTextPackagePath() + _T("template-packages\\python-template.ee-package");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
	{
		strLanguageTemplateFilePath = PathUtils::GetVinaTextPackagePath() + _T("template-packages\\pascal-template.ee-package");
	}
	return strLanguageTemplateFilePath;
}

CString PathUtils::GetUserExtensionPath()
{
	CString strPath = GetVinaTextPackagePath();
	strPath.Append(_T("extension-packages\\user-extensions.dat"));
	return strPath;
}

CString PathUtils::GetVinaTextPackagePath()
{
	CString strPath = GetVinaTextPath();
	strPath.Append(_T("Packages\\"));
	return strPath;
}

CString PathUtils::GetVinaTextPOPath()
{
	CString strPath = GetVinaTextPackagePath();
	strPath.Append(_T("\\localization-packages\\"));
	return strPath;
}

CString PathUtils::GetAbsolutePath(const CString& strPath)
{
	TCHAR path[_MAX_PATH];
	_wfullpath(path, strPath, _MAX_PATH);
	return CString(path);
}

CString PathUtils::GetDataBaseFileFilter()
{
	CString strDatabaseFilter;
	CString strFileFilterPath = PathUtils::GetVinaTextPackagePath() + _T("data-packages\\all-file-extension.dat");
	if (PathFileExists(strFileFilterPath))
	{
		CString strFileContent;
		PathUtils::OpenFile(strFileFilterPath, strFileContent);

		CStringArray arrFilter;
		AppUtils::SplitCString(strFileContent, EDITOR_NEW_LINE, arrFilter);
		for (int i = 0; i < arrFilter.GetSize(); ++i)
		{
			CString strFilterFull = arrFilter[i].Trim();
			if (strFilterFull.IsEmpty()) continue;
			CString strFileExt = AppUtils::GetSubCStringBetweenTwoDemiliter(strFilterFull, _T("("), _T(")")).Trim();
			CString strTempFilter = strFilterFull + _T("|") + strFileExt + _T("|");
			strDatabaseFilter += strTempFilter;
		}
	}
	else // set default file filter...
	{
		strDatabaseFilter = _T("All Files (*.*)|*.*|Text files (*.txt)|*.txt||");
	}
	return strDatabaseFilter;
}

CString PathUtils::GetWindowSystemPath()
{
	TCHAR path[MAX_PATH];
	GetWindowsDirectory(path, MAX_PATH);
	return CString(path);
}

CString PathUtils::GetProgramFilePath()
{
	TCHAR path[MAX_PATH];
	SHGetSpecialFolderPath(0, path, CSIDL_PROGRAM_FILES, FALSE);
	return CString(path);
}

CString PathUtils::GetFileExtention(const CString& strFile)
{
	CString strExtension = _T("");
	if (strFile.IsEmpty())
	{
		return strExtension;
	}
	int nIndex = strFile.ReverseFind('.');
	if (nIndex == -1) return strExtension;
	strExtension = strFile.Mid(nIndex + 1).Trim();
	return strExtension;
}

CString PathUtils::GetFilePathWithoutExtention(const CString & strFile)
{
	CString strFolder = GetContainerPath(strFile);
	CString strFileName = GetFilenameFromPath(strFile);
	CString strFileNameNoEtx = GetFileNameWithoutExtension(strFileName);
	return strFolder + _T("\\") + strFileNameNoEtx;
}

CString PathUtils::GetFileNameWithoutExtension(const CString& strFileName)
{
	CString strFileNameOnly = _T("");
	if (strFileName.IsEmpty())
	{
		return strFileNameOnly;
	}
	int nIndex = strFileName.ReverseFind('.');
	strFileNameOnly = strFileName.Mid(0, nIndex).Trim();
	if (strFileNameOnly.IsEmpty())
	{
		return strFileName;
	}
	return strFileNameOnly;
}

CString PathUtils::GetLastLevelPath(const CString & strPath)
{
	int nIndexSlash = strPath.ReverseFind('\\');
	return strPath.Mid(nIndexSlash + 1);
}

void PathUtils::DeleteFilesInFolderPermanently(const CString& strFolder, const CString& csExt)
{
	if (!PathFileExists(strFolder))
	{
		AfxMessageBoxFormat(MB_ICONWARNING, _T("[Path Error] \"%s\" does not exist!"), strFolder);
		return;
	}
	CString csFileName, csFile;
	WIN32_FIND_DATA info;
	HANDLE hp;

	csFileName = strFolder + "\\*" + csExt;

	hp = FindFirstFile((LPCTSTR)csFileName, &info);
	do
	{
		CString csFile = strFolder + "\\";
		csFile += info.cFileName;
		BOOL retVal = DeleteFile(csFile);
	} while (FindNextFile(hp, &info));

	FindClose(hp);
}

void PathUtils::DeleteFilesInFolder(HWND hParentHWND, const CString& strFolder, const CString& csExt)
{
	if (!PathFileExists(strFolder))
	{
		AfxMessageBoxFormat(MB_ICONWARNING, _T("[Path Error] \"%s\" does not exist!"), strFolder);
		return;
	}
	CString csFileName, csFile;
	WIN32_FIND_DATA info;
	HANDLE hp;

	csFileName = strFolder + "\\*" + csExt;

	hp = FindFirstFile((LPCTSTR)csFileName, &info);
	do
	{
		CString csFile = strFolder + "\\";
		csFile += info.cFileName;
		if (!IsDirectory(csFile))
		{
			BOOL retVal = SendToRecycleBin(hParentHWND, csFile);
		}
	} while (FindNextFile(hp, &info));

	FindClose(hp);
}

BOOL PathUtils::RenameFile(const CString & strFileOld, const CString & strFileNew)
{
	if (PathFileExists(strFileOld))
	{
		BOOL bSuccess = MoveFile(strFileOld, strFileNew);
		if (bSuccess)
		{
			return TRUE;
		}
	}
	return FALSE;
}

CString PathUtils::GetContainerPath(const CString& path)
{
	TCHAR szDir[_MAX_DIR];
	TCHAR szDrive[_MAX_DRIVE];
	TCHAR szName[_MAX_FNAME];
	TCHAR szExt[_MAX_EXT];
	_tsplitpath_s(path, szDrive, _MAX_DRIVE, szDir, _MAX_DIR, szName, _MAX_FNAME, szExt, _MAX_EXT);
	CString strFolder = CString(szDrive) + CString(szDir);
	int pos = strFolder.ReverseFind(_T('\\'));
	CString strFolderReturn = strFolder.Mid(0, pos).Trim();
	if (strFolderReturn.Find(_T("\\")) == -1)
	{
		return strFolderReturn + _T("\\");
	}
	return strFolderReturn;
}

CString PathUtils::GetFilenameFromPath(LPCTSTR path)
{
	TCHAR szDir[_MAX_DIR];
	TCHAR szDrive[_MAX_DRIVE];
	TCHAR szName[_MAX_FNAME];
	TCHAR szExt[_MAX_EXT];
	_tsplitpath_s(path, szDrive, _MAX_DRIVE, szDir, _MAX_DIR, szName, _MAX_FNAME, szExt, _MAX_EXT);
	return CString(szName) + CString(szExt);
}

void PathUtils::GetPathComponents(const CString& strPath, CString& strDrive, CString& strDir, CString& strFName, CString& strExt)
{
	TCHAR lpszDrive[_MAX_DRIVE], lpszDir[_MAX_DIR], lpszFName[_MAX_FNAME], lpszExt[_MAX_EXT];
	_tsplitpath_s(strPath, lpszDrive, _MAX_DRIVE, lpszDir, _MAX_DIR, lpszFName, _MAX_DIR, lpszExt, _MAX_EXT);
	strDrive = CString(lpszDrive);
	strDir = CString(lpszDir);
	strFName = CString(lpszFName);
	strExt = CString(lpszExt);
}

CString PathUtils::GetCopyFileFromSourceFile(const CString & strDestFolder, const CString & strSourceFile, BOOL bIsCutFileOperation /*= FALSE*/)
{
	const int REPLACE_FILE_ID = 201;
	const int SKIP_FILE_ID = 202;
	auto fTaskDialog = [&](const CString& strCopyFileDest, BOOL bIsCutFile) -> BOOL
	{
		CString strMessage = bIsCutFile ? _T("[Cut Warning] The destination already has a file named \"%s\"") : _T("[Copy Warning] The destination already has a file named \"%s\"");
		strMessage.Format(strMessage, strCopyFileDest);
		CTaskDialog dlg(_T(""), strMessage, _T("VinaText"), 0/*TDCBF_OK_BUTTON*/);
		dlg.SetMainIcon(TD_WARNING_ICON);
		dlg.AddCommandControl(REPLACE_FILE_ID, _T("Replace the file in destination"));
		dlg.AddCommandControl(SKIP_FILE_ID, _T("Skip this file"));
		dlg.SetDialogWidth(300);
		dlg.SetDefaultCommandControl(REPLACE_FILE_ID);
		dlg.DoModal();
		int nSel = dlg.GetSelectedCommandControlID();
		if (nSel != REPLACE_FILE_ID)
		{
			return FALSE;
		}
		return TRUE;
	};

	CString strCopyFileDest;
	if (PathFileExists(strDestFolder) && PathFileExists(strSourceFile))
	{
		if (bIsCutFileOperation)
		{
			if (PathUtils::IsDirectory(strDestFolder))
			{
				strCopyFileDest = strDestFolder + _T("\\") + PathUtils::GetFilenameFromPath(strSourceFile);
				if (strCopyFileDest != strSourceFile && PathFileExists(strCopyFileDest))
				{
					if (fTaskDialog(strCopyFileDest, TRUE) == FALSE)
					{
						return _T("");
					}
				}
			}
			else
			{
				CString strDestFolderNew = PathUtils::GetContainerPath(strDestFolder);
				strCopyFileDest = strDestFolderNew + _T("\\") + PathUtils::GetFilenameFromPath(strSourceFile);
				if (strCopyFileDest != strSourceFile && PathFileExists(strCopyFileDest))
				{
					if (fTaskDialog(strCopyFileDest, TRUE) == FALSE)
					{
						return _T("");
					}
				}
			}
		}
		else
		{
			if (PathUtils::IsDirectory(strDestFolder))
			{
				strCopyFileDest = strDestFolder + _T("\\") + PathUtils::GetFilenameFromPath(strSourceFile);
				if (strCopyFileDest == strSourceFile)
				{
					CString strFileName = PathUtils::GetFilenameFromPath(strSourceFile);
					CString strParrentFolder = PathUtils::GetContainerPath(strSourceFile);
					CString strFileNameNoExt = PathUtils::GetFileNameWithoutExtension(strFileName);
					CString strFileExt = PathUtils::GetFileExtention(strSourceFile);
					CString strFileCopySuffix = _T("-copied-") + AppUtils::IntToCString(AppSettingMgr.GetNewFileCopyID()) + _T(".");
					int nPosCopied = strFileNameNoExt.Find(_T("-copied-"));
					strCopyFileDest.Empty();
					if (nPosCopied == -1)
					{
						strCopyFileDest += strParrentFolder + _T("\\") + strFileNameNoExt + strFileCopySuffix + strFileExt;
					}
					else
					{
						strCopyFileDest += strParrentFolder + _T("\\") + strFileNameNoExt.Mid(0, nPosCopied) + strFileCopySuffix + strFileExt;
					}
				}
				else if (PathFileExists(strCopyFileDest))
				{
					if (fTaskDialog(strCopyFileDest, FALSE) == FALSE)
					{
						return _T("");
					}
				}
			}
			else
			{
				CString strDestFolderNew = PathUtils::GetContainerPath(strDestFolder);
				strCopyFileDest = strDestFolderNew + _T("\\") + PathUtils::GetFilenameFromPath(strSourceFile);
				if (strCopyFileDest == strSourceFile)
				{
					CString strFileName = PathUtils::GetFilenameFromPath(strSourceFile);
					CString strParrentFolder = PathUtils::GetContainerPath(strSourceFile);
					CString strFileNameNoExt = PathUtils::GetFileNameWithoutExtension(strFileName);
					CString strFileExt = PathUtils::GetFileExtention(strSourceFile);
					CString strFileCopySuffix = _T("-copied-") + AppUtils::IntToCString(AppSettingMgr.GetNewFileCopyID()) + _T(".");
					int nPosCopied = strFileNameNoExt.Find(_T("-copied-"));
					strCopyFileDest.Empty();
					if (nPosCopied == -1)
					{
						strCopyFileDest += strParrentFolder + _T("\\") + strFileNameNoExt + strFileCopySuffix + strFileExt;
					}
					else
					{
						strCopyFileDest += strParrentFolder + _T("\\") + strFileNameNoExt.Mid(0, nPosCopied) + strFileCopySuffix + strFileExt;
					}
				}
				else if (PathFileExists(strCopyFileDest))
				{
					if (fTaskDialog(strCopyFileDest, FALSE) == FALSE)
					{
						return _T("");
					}
				}
			}
		}
	}
	return strCopyFileDest;
}

CString PathUtils::BackslashToForwardslash(LPCTSTR path)
{
	CString strNewPath = path;
	strNewPath.Replace(_T("\\"), _T("/"));
	return strNewPath;
}

BOOL PathUtils::IsDirectory(const CString& strPath)
{
	DWORD dwAttrs = ::GetFileAttributes(strPath);
	if ((dwAttrs != DWORD(-1)) && (0 != (dwAttrs & FILE_ATTRIBUTE_DIRECTORY)))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL PathUtils::IsExeFile(const CString& strPath)
{
	CString strExt = PathUtils::GetFileExtention(strPath);
	if (strExt.IsEmpty()) return FALSE;
	if (strExt.MakeLower() == _T("exe")) return TRUE;
	return FALSE;
}

BOOL PathUtils::IsFileAlreadyOpened(const CString & strPath)
{
	HANDLE hFile;
	hFile = CreateFile(strPath, GENERIC_READ, 0 /* no sharing! exclusive */, NULL, OPEN_EXISTING, 0, NULL);
	if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
	{
		CloseHandle(hFile);
		return TRUE;
	}
	return FALSE;
}

BOOL PathUtils::GetAllPathsByExtensionFromFolder(const CString& path, std::vector<CString>& vecFileName, std::vector<CString>& vecPath, CString strStringInFilePath, CString strFileExt)
{
	std::vector<CString> tmpFile;
	std::vector<CString> tmppathFile;
	CFileFind hFile;
	BOOL bFound = FALSE;
	bFound = hFile.FindFile(path + strFileExt); //_T("\\*.csv*")
	CString name;
	CString pathFile;
	while (bFound)
	{
		bFound = hFile.FindNextFile();
		if (!hFile.IsDots())
		{
			name = hFile.GetFileName();
			pathFile = hFile.GetFilePath();
			if (!hFile.IsDirectory())
			{
				tmpFile.push_back(name);
				tmppathFile.push_back(pathFile);
			}
		}
	}
	hFile.Close();
	if (!tmpFile.empty() && tmpFile.size() == tmppathFile.size())
	{
		for (int i = 0; i < tmpFile.size(); ++i)
		{
			if (tmpFile.at(i).Find(strStringInFilePath) != -1)
			{
				vecFileName.push_back(tmpFile.at(i));
				vecPath.push_back(tmppathFile.at(i));
			}
		}
		return TRUE;
	}
	return FALSE;
}

void PathUtils::GetAllFilesFromFolder(const CString& sDir, std::vector<CString>& vecFiles, BOOL bIncludeSubFolder /*=TRUE*/)
{
	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;
	wchar_t sPath[2048];
	//Specify a file mask. *.* = We want everything! 
	wsprintf(sPath, L"%s\\*.*", sDir);
	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		return;
	}
	do
	{
		//Find first file will always return "." and ".." as the first two directories. 
		if (wcscmp(fdFile.cFileName, L".") != 0 && wcscmp(fdFile.cFileName, L"..") != 0)
		{
			//Build up our file path using the passed in [sDir] and the file/foldername we just found: 
			wsprintf(sPath, L"%s\\%s", sDir, fdFile.cFileName);

			//Is the entity a File or Folder? 
			if (fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && bIncludeSubFolder)
			{
				GetAllFilesFromFolder(sPath, vecFiles); // Recursion.
			}
			else
			{
				vecFiles.push_back(sPath);
			}
		}
	} while (FindNextFile(hFind, &fdFile)); //Find the next file. 
	FindClose(hFind); //Free handle 
}

void PathUtils::GetAllFolderFromFolder(const CString & sDir, std::vector<CString>& vecPaths, BOOL bIncludeSubFolder /*=TRUE*/)
{
	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;
	wchar_t sPath[2048];
	//Specify a file mask. *.* = We want everything! 
	wsprintf(sPath, L"%s\\*.*", sDir);
	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		return;
	}
	do
	{
		//Find first file will always return "." and ".." as the first two directories. 
		if (wcscmp(fdFile.cFileName, L".") != 0 && wcscmp(fdFile.cFileName, L"..") != 0)
		{
			//Build up our file path using the passed in  [sDir] and the file/foldername we just found: 
			wsprintf(sPath, L"%s\\%s", sDir, fdFile.cFileName);
			//Is the entity a File or Folder? 
			if (fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && bIncludeSubFolder)
			{
				vecPaths.push_back(sPath);
				GetAllFolderFromFolder(sPath, vecPaths); // Recursion
			}
		}
	} while (FindNextFile(hFind, &fdFile)); //Find the next file. 
	FindClose(hFind); //Free handle 
}

void PathUtils::GetAllPathFromFolder(const CString & sDir, std::vector<CString>& vecPaths, BOOL bIncludeSubFolder)
{
	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;
	wchar_t sPath[2048];
	//Specify a file mask. *.* = We want everything! 
	wsprintf(sPath, L"%s\\*.*", sDir);
	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		return;
	}
	do
	{
		//Find first file will always return "." and ".." as the first two directories. 
		if (wcscmp(fdFile.cFileName, L".") != 0 && wcscmp(fdFile.cFileName, L"..") != 0)
		{
			//Build up our file path using the passed in [sDir] and the file/foldername we just found: 
			wsprintf(sPath, L"%s\\%s", sDir, fdFile.cFileName);

			//Is the entity a File or Folder? 
			if (fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && bIncludeSubFolder)
			{
				vecPaths.push_back(sPath);
				GetAllPathFromFolder(sPath, vecPaths); // Recursion.
			}
			else
			{
				vecPaths.push_back(sPath);
			}
		}
	} while (FindNextFile(hFind, &fdFile)); //Find the next file. 
	FindClose(hFind); //Free handle 
}

BOOL PathUtils::SaveFileTrunc(const CString& szFile, CString strContent)
{
	// if pathname is empty do nothing
	if (szFile.IsEmpty())
	{
		return FALSE;
	}
	strContent.Replace(_T("\r"), _T("\n"));
	std::wofstream out_file(AppUtils::CStringToWStd(szFile), std::wios::trunc);
	out_file.imbue(std::locale(out_file.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	out_file << AppUtils::CStringToWStd(strContent);
	out_file.close();
	return TRUE;
}

BOOL PathUtils::SaveFileAppend(const CString & szFile, CString strContent)
{
	// if pathname is empty do nothing
	if (szFile.IsEmpty())
	{
		return FALSE;
	}
	strContent.Replace(_T("\r"), _T("\n"));
	std::wofstream out_file(AppUtils::CStringToWStd(szFile), std::wios::app);
	if (!out_file) return FALSE;
	out_file.imbue(std::locale(out_file.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	out_file << std::endl << AppUtils::CStringToWStd(strContent);
	out_file.close();
	return TRUE;
}

BOOL PathUtils::SaveFileAppendNoDuplicateLine(const CString & szFile, CString strContent)
{
	// if pathname is empty do nothing
	if (szFile.IsEmpty())
	{
		return FALSE;
	}
	// check if line already existed in file
	std::wifstream in_file(AppUtils::CStringToWStd(szFile), std::wios::app);
	if (!in_file)
	{
		return FALSE;
	}
	std::wstring line;
	while (std::getline(in_file, line))
	{
		if (line.empty()) continue;
		line += EDITOR_NEW_LINE_LF;
		if (line == AppUtils::CStringToWStd(strContent))
		{
			return FALSE;
		}
	}
	strContent.Replace(_T("\r"), _T("\n"));
	std::wofstream out_file(AppUtils::CStringToWStd(szFile), std::wios::app);
	if (!out_file) return FALSE;
	out_file.imbue(std::locale(out_file.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	out_file << std::endl << AppUtils::CStringToWStd(strContent);
	out_file.close();
	return TRUE;
}

//#include <boost/iostreams/device/mapped_file.hpp> 
//#include <boost/iostreams/stream.hpp>  
//BOOL PathUtils::OpenFileByMappedFile(const char* fname, CString& strContent)
//{
//	using boost::iostreams::mapped_file_source;
//	using boost::iostreams::stream;
//	mapped_file_source mmap(fname);
//	stream<mapped_file_source> is(mmap, std::ios::binary);
//
//	if (!is.is_open())
//	{
//		return FALSE;
//	}
//
//	std::string line;
//	std::string totalLines;
//	uintmax_t m_numLines = 0;
//	while (std::getline(is, line))
//	{
//		totalLines += line + "\n";
//	}
//	strContent = AppUtils::StdToCString(totalLines);
//	return TRUE;
//}


BOOL PathUtils::OpenFile(const CString& szFile, CString& strContent)
{
	if (!PathFileExists(szFile)) return FALSE;
	std::unique_ptr<TextFile> tf_in = std::make_unique<TextFile>();
	int result = tf_in->Open(szFile, TF_READ, TF_UTF8);
	if (result < 0)
	{
		TCHAR *errmsg = GetLastErrorString();
		LOG_OUTPUT_MESSAGE_FORMAT(_T("%s\n"), errmsg);
		return FALSE;
	}

	TCHAR *lineBuffer = NULL;
	while (1)
	{
		result = tf_in->ReadLine(NULL, &lineBuffer);
		if (result < 0)
		{
			if (result == TF_ERROR) // else TF_EOF
			{
				TCHAR *errmsg = GetLastErrorString();
				LOG_OUTPUT_MESSAGE_FORMAT(_T("%s\n"), errmsg);
			}
			break;
		}
		else
		{
			strContent += lineBuffer;
		}
	}
	free_block(lineBuffer);
	tf_in->Close();
	return TRUE;
}

BOOL PathUtils::OpenFile(const CString & szFile, CStringArray & arrLine)
{
	CString strFileContent;
	if (OpenFile(szFile, strFileContent))
	{
		AppUtils::SplitCString(strFileContent, EDITOR_NEW_LINE_CR, arrLine);
		return TRUE;
	}
	return FALSE;
}

BOOL PathUtils::OpenFileBinaryMode(const CString & strFile, std::string& str)
{
	std::ifstream binary(strFile, std::ios::binary);
	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(binary), {});
	std::string strBinary(buffer.begin(), buffer.end());
	str = strBinary;
	return TRUE;
}

char * PathUtils::OpenFileToBuffer(const CString & szFile, long* lSize)
{
	// IMPORTANT: CALLER NEED TO FREE MEMORY!!!
	FILE *fp;
	char *buffer = NULL;

	fp = fopen(AppUtils::CStringToStd(szFile).c_str(), "rb");
	if (!fp) return NULL;

	fseek(fp, 0L, SEEK_END);
	*lSize = ftell(fp);
	rewind(fp);

	/* allocate memory for entire content */
	buffer = reinterpret_cast<char*>(calloc(1, *lSize + 1));
	if (!buffer)
	{
		fclose(fp);
		return NULL;
	}

	/* copy the file into the buffer */
	if (1 != fread(buffer, *lSize, 1, fp))
	{
		fclose(fp);
		return NULL;
	}

	/* do your work here, buffer is a string contains the whole text */
	fclose(fp);
	return buffer;
}

BOOL PathUtils::IsFileChanged(const CString & strFilePath1, const CString & strFilePath2)
{
	// compare file size
	ULONGLONG size1 = 0L, size2 = 0L;
	CFileStatus fileStatus;
	if (CFile::GetStatus(strFilePath1, fileStatus))
	{
		size1 = fileStatus.m_size;
	}
	if (CFile::GetStatus(strFilePath2, fileStatus))
	{
		size2 = fileStatus.m_size;
	}
	if (size1 != size2) return TRUE;

	// compare file contents
	auto f1 = std::unique_ptr<CSVReader>(std::make_unique<CSVReader>(strFilePath1));
	auto f2 = std::unique_ptr<CSVReader>(std::make_unique<CSVReader>(strFilePath2));
	if (f1->OpenError()) return TRUE;
	if (f2->OpenError()) return TRUE;
	CString line1, line2;
	while (f1->ReadLine(line1))
	{
		auto ret = f2->ReadLine(line2);
		if (!ret) return TRUE;
		if (line1 != line2) return TRUE;
	}

	return FALSE;
}

BOOL PathUtils::IsFileContentChanged(const CString & strFilePath, const CString & strContent)
{
	CString strFileContent;
	if (OpenFile(strFilePath, strFileContent))
	{
		if (strFileContent == strContent)
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

static void RecurseDelete(LPCTSTR pDir)
{
	CFileFind finder;
	// build a string with wildcards
	CString strWildcard(pDir);
	strWildcard += _T("\\*.*");

	// start working for files
	BOOL bWorking = finder.FindFile(strWildcard);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		// skip . and .. files; otherwise, we'd
		// recur infinitely!
		if (finder.IsDots()) continue;
		// if it's a directory, recursively search it
		if (finder.IsDirectory())
		{
			CString str = finder.GetFilePath();
			RecurseDelete(str);
			::RemoveDirectory(str);
		}
		else
		{
			::DeleteFile(finder.GetFilePath());
		}
	}
	finder.Close();
	::RemoveDirectory(pDir);
}

void PathUtils::DeletePathPermanently(LPCTSTR pstrPath)
{
	CFileFind finder;
	BOOL bWorking = finder.FindFile(pstrPath);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots()) continue;
		if (finder.IsDirectory())
		{
			RecurseDelete(finder.GetFilePath());
		}
		else
		{
			::DeleteFile(finder.GetFilePath());
		}
	}
	finder.Close();
}

BOOL PathUtils::SendToRecycleBin(HWND hParentHWND, const CString& strPath, BOOL bAllowUndo)
{
	if (!hParentHWND) return FALSE;

	SHFILEOPSTRUCT shfo{};
	shfo.hwnd = hParentHWND;
	shfo.wFunc = FO_DELETE;

	//Undo is not allowed if the SHIFT key is held down
	if (!(GetKeyState(VK_SHIFT) & 0x8000))
		shfo.fFlags = FOF_ALLOWUNDO;

#pragma warning(suppress: 26472)
	size_t nChars = static_cast<size_t>(strPath.GetLength()) + 1;
	nChars++;
	std::vector<TCHAR> sTempFrom;
	sTempFrom.resize(nChars);
	_tcscpy_s(sTempFrom.data(), nChars, strPath);
#pragma warning(suppress: 26446)
	sTempFrom[nChars - 1] = _T('\0');
	shfo.pFrom = sTempFrom.data();

	//Let the shell perform the actual deletion
#pragma warning(suppress: 26486)
	if (SHFileOperation(&shfo) == 0 && (shfo.fAnyOperationsAborted == FALSE))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL PathUtils::CreateDirectoryIfNotExited(LPCTSTR pstrPath)
{
	if (FALSE == PathFileExists(pstrPath))
	{
		if (CreateDirectory(pstrPath, NULL))
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL PathUtils::IsFileReadOnly(const CString& szFile)
{
	DWORD attr = GetFileAttributes(szFile);
	if (attr != INVALID_FILE_ATTRIBUTES)
	{
		return static_cast<BOOL>(attr & FILE_ATTRIBUTE_READONLY);
	}
	return FALSE;
}

LONGLONG PathUtils::GetFileSize(const CString & szFile)
{
	HANDLE hFile = CreateFile(szFile, GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return -1; // error condition, could call GetLastError to find out more
	}

	LARGE_INTEGER size;
	if (!GetFileSizeEx(hFile, &size))
	{
		DELETE_WIN32_HANDLE(hFile)
			return -1; // error condition, could call GetLastError to find out more
	}

	DELETE_WIN32_HANDLE(hFile)
		return size.QuadPart;
}

#define DIM(x) (sizeof(x)/sizeof(*(x)))
static const char *sizes[] = { "EiB", "PiB", "TiB", "GiB", "MiB", "KiB", "Byte" };
static const uint64_t exbibytes = 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL;
char* PathUtils::SizeMemoryToString(uint64_t size) // NEED TO FREE MEMORY FFROM CALLER
{
	char *result = (char *)malloc(sizeof(char) * 20);
	uint64_t  multiplier = exbibytes;
	for (int i = 0; i < DIM(sizes); i++, multiplier /= 1024)
	{
		if (size < multiplier)
		{
			continue;
		}
		if (size % multiplier == 0)
		{
			sprintf(result, "%" PRIu64 " %s", size / multiplier, sizes[i]);
		}
		else
		{
			sprintf(result, "%.1f %s", (float)size / multiplier, sizes[i]);
		}
		return result;
	}
	strcpy(result, "0");
	return result;
}

BOOL PathUtils::OpenFileSystem(CString szFile)
{
	SHELLEXECUTEINFO sei{};
	sei.cbSize = sizeof(sei);
	sei.nShow = SW_SHOW;
	sei.lpFile = szFile.GetBuffer(szFile.GetLength());
	sei.fMask = SEE_MASK_INVOKEIDLIST;
#pragma warning(suppress: 26486)
	BOOL ret = ShellExecuteEx(&sei);
	szFile.ReleaseBuffer();
	return ret;
}

// list candicates, update more...
const CString arrBlockFormatFileMailServer[] = {
	_T("ade"), _T("adp"), _T("app"), _T("asp"), _T("aspx"), _T("asx"), _T("bas"), _T("bat"), _T("cer"), _T("chm"), _T("cmd"), _T("cnt"),
	_T("com"), _T("cpl"), _T("crt"), _T("csh"), _T("der"), _T("diagcab"), _T("exe"), _T("fxp"), _T("gadget"), _T("grp"), _T("hlp"), _T("hpj"),
	_T("hta"), _T("htc"), _T("inf"), _T("ins"), _T("isp"), _T("its"), _T("jar"), _T("jnlp"), _T("js"), _T("jse"), _T("ksh"), _T("lnk"), _T("mad"),
	_T("maf"), _T("mag"), _T("mam"), _T("maq"), _T("mar"), _T("mas"), _T("mat"), _T("mau"), _T("mav"), _T("maw"), _T("mcf"), _T("mda"), _T("mdb"),
	_T("mde"), _T("mdt"), _T("mdw"), _T("mdz"), _T("msc"), _T("msh"), _T("msh1"), _T("msh2"), _T("mshxml"), _T("msh1xml"), _T("msh2xml"), _T("msi"),
	_T("msp"), _T("mst"), _T("msu"), _T("ops"), _T("osd"), _T("pcd"), _T("pif"), _T("pl"), _T("plg"), _T("prf"), _T("prg"), _T("printerexport"), _T("ps1"),
	_T("ps1xml"), _T("ps2"), _T("ps2xml"), _T("psc1"), _T("psc2"), _T("psd1"), _T("psdm1"), _T("pst"), _T("py"), _T("pyc"), _T("pyo"), _T("pyw"), _T("pyz"),
	_T("pyzw"), _T("reg"), _T("scf"), _T("scr"), _T("sct"), _T("shb"), _T("shs"), _T("theme"), _T("tmp"), _T("url"), _T("vb"), _T("vbe"), _T("vbp"), _T("vbs"), _T("vhd"),
	_T("vhdx"), _T("vsmacros"), _T("vsw"), _T("webpnp"), _T("website"), _T("ws"), _T("wsc"), _T("wsf"), _T("wsh"), _T("xbap"), _T("xll"), _T("xnk"),
};

BOOL PathUtils::IsBlockFormatFileMailServer(const CString& strFile)
{
	CString strExt = PathUtils::GetFileExtention(strFile);
	for (int i = 0; i < GET_ARRAY_SIZE(arrBlockFormatFileMailServer); ++i)
	{
		if ((strExt.MakeLower()) == arrBlockFormatFileMailServer[i]) return TRUE;
	}
	return FALSE;
}

BOOL PathUtils::IsBinaryFile(const CString& strFile, BINARY_FILE_TYPE BinnaryFileType)
{
	if (BinnaryFileType & BINARY_FILE_TYPE::FILE_BINNARY)
	{
		CString strExt = PathUtils::GetFileExtention(strFile);
		if (strExt.IsEmpty()) return FALSE;
		for (int i = 0; i < AppSettingMgr.m_BinaryFileExtensionList.GetCount(); ++i)
		{
			if (strExt.MakeLower() == AppSettingMgr.m_BinaryFileExtensionList[i]) return TRUE;
		}
	}
	if (BinnaryFileType & BINARY_FILE_TYPE::FILE_OFFICE)
	{
		if (PathUtils::IsOfficeFile(strFile)) return TRUE;
	}
	if (BinnaryFileType & BINARY_FILE_TYPE::FILE_PDF)
	{
		if (PathUtils::IsPdfFile(strFile)) return TRUE;
	}
	if (BinnaryFileType & BINARY_FILE_TYPE::FILE_IMAGE)
	{
		if (PathUtils::IsImageFile(strFile)) return TRUE;
	}
	if (BinnaryFileType & BINARY_FILE_TYPE::FILE_MEDIA)
	{
		if (PathUtils::IsMediaFile(strFile)) return TRUE;
	}
	return FALSE;
}

BOOL PathUtils::IsBinaryFileByContent(const CString & strFile)
{
	int char_;
	std::ifstream file(strFile);
	while ((char_ = file.get()) != EOF && char_ <= 127);
	if (char_ == EOF)
	{
		/* maybe file is all ASCII */
		return FALSE;
	}
	return TRUE;
}

// list image candicates, update more...
const std::string image_file_list[] = { "jpg", "jpeg", "png", "gif", "ttf",
"bmp", "tiff", "dib", "jpe", "jfif", "tif", "webp", "ico" };

BOOL PathUtils::IsImageFile(const CString& strFile)
{
	CString strExt = PathUtils::GetFileExtention(strFile);
	for (int i = 0; i < GET_ARRAY_SIZE(image_file_list); ++i)
	{
		if (AppUtils::CStringToStd(strExt.MakeLower()) == image_file_list[i]) return TRUE;
	}
	return FALSE;
}

BOOL PathUtils::IsGifFile(const CString& strFile)
{
	CString strExt = PathUtils::GetFileExtention(strFile);
	if (AppUtils::CStringToStd(strExt.MakeLower()) == "gif") return TRUE;
	return FALSE;
}

BOOL PathUtils::IsPdfFile(const CString & strFile)
{
	return PathFileExists(strFile) && strFile.Right(4).CompareNoCase(_T(".pdf")) == 0;
}

// list media candicates, update more...
const std::string media_file_list[] = { "asf","wma","wmv","wm", "asx", "wax","wvx", "wmx", "wpl", "dvr-ms",
"wmd", "avi", "mpg","mpeg","m1v","mp2","mp3","mpa","mpe","m3u", "mid","midi","rmi", "aif",
"aifc", "aiff", "au", "snd", "wav", "cda", "ivf", "wmz","wms", "mov", "m4a", "mp4", "m4v",
"mp4v", "3g2", "3gp2", "3gp", "3gpp", "aac", "adt", "adts", "m2ts", "flac" };

BOOL PathUtils::IsMediaFile(const CString & strFile)
{
	CString strExt = PathUtils::GetFileExtention(strFile);
	for (int i = 0; i < GET_ARRAY_SIZE(media_file_list); ++i)
	{
		if (AppUtils::CStringToStd(strExt.MakeLower()) == media_file_list[i]) return TRUE;
	}
	return FALSE;
}

// list office candicates, update more...
const std::string office_file_list[] = { "docx", "docm", "dotx", "dotm", "doc", "dot", "rtf", "htm", "mht", "mhtml",
"xml", "odt", "xl", "xlsx", "xlsb", "xlam", "xlsm", "xltx", "xltm", "xls", "xlt", "xla", "xlm", "xlw", "ppt", "pptx",
"pptm", "potx", "potm", "pot", "ppsx", "ppsm", "pps", "vsd", "vsdx", "vdx", "vdw", "vtx", "vss", "vst", "vsx", "mpp",
"mpt", "mpd", "mpx" };

BOOL PathUtils::IsOfficeFile(const CString & strFile)
{
	CString strExt = PathUtils::GetFileExtention(strFile);
	for (int i = 0; i < GET_ARRAY_SIZE(office_file_list); ++i)
	{
		if (AppUtils::CStringToStd(strExt.MakeLower()) == office_file_list[i]) return TRUE;
	}
	return FALSE;
}

// list office word candicates, update more...
const std::string office_word_file_list[] = { "docx", "docm", "dotx", "dotm", "doc", "dot" };

BOOL PathUtils::IsOfficeWordFile(const CString & strFile)
{
	CString strExt = PathUtils::GetFileExtention(strFile);
	for (int i = 0; i < GET_ARRAY_SIZE(office_word_file_list); ++i)
	{
		if (AppUtils::CStringToStd(strExt.MakeLower()) == office_word_file_list[i]) return TRUE;
	}
	return FALSE;
}

// list office ppt candicates, update more...
const std::string office_ppt_file_list[] = { "ppt", "pptx", "pptm", "potx", "potm", "pot", "ppsx", "ppsm", "pps" };

BOOL PathUtils::IsOfficePptFile(const CString & strFile)
{
	CString strExt = PathUtils::GetFileExtention(strFile);
	for (int i = 0; i < GET_ARRAY_SIZE(office_ppt_file_list); ++i)
	{
		if (AppUtils::CStringToStd(strExt.MakeLower()) == office_ppt_file_list[i]) return TRUE;
	}
	return FALSE;
}

// list office excel candicates, update more...
const std::string office_excel_file_list[] = { "xl", "xlsx", "xlsb", "xlam", "xlsm", "xltx", "xltm", "xls", "xlt", "xla", "xlm", "xlw" };

BOOL PathUtils::IsOfficeExcelFile(const CString & strFile)
{
	CString strExt = PathUtils::GetFileExtention(strFile);
	for (int i = 0; i < GET_ARRAY_SIZE(office_excel_file_list); ++i)
	{
		if (AppUtils::CStringToStd(strExt.MakeLower()) == office_excel_file_list[i]) return TRUE;
	}
	return FALSE;
}

int PathUtils::CountWordsFromFile(const CString & strFile) // file must not be opening!
{
	std::ifstream infile(strFile);
	if (infile)
	{
		std::istream_iterator<std::string> in{ infile }, end;
		return static_cast<int>(std::distance(in, end));
	}
	return 0;
}

CString PathUtils::GetFileTimePropertyCString(const CString & strFile, FILE_TIME_PROPERTY fileTime)
{
	CString strFileTime;
	WIN32_FILE_ATTRIBUTE_DATA attributes;
	if (GetFileAttributesEx(strFile, GetFileExInfoStandard, &attributes) != 0)
	{
		FILETIME ft;
		switch (fileTime)
		{
		case FILE_TIME_PROPERTY::FILE_TIME_CREATED:
			ft = attributes.ftCreationTime;
			break;
		case FILE_TIME_PROPERTY::FILE_TIME_LAST_MODIFIED:
			ft = attributes.ftLastWriteTime;
			break;
		default:
			ft = attributes.ftLastAccessTime;
			break;
		}

		SYSTEMTIME utcSystemTime, localSystemTime;
		FileTimeToSystemTime(&ft, &utcSystemTime);
		SystemTimeToTzSpecificLocalTime(NULL, &utcSystemTime, &localSystemTime);

		const size_t dateTimeStrLen = 256;
		TCHAR bufTime[dateTimeStrLen] = { '\0' };
		GetTimeFormat(LOCALE_USER_DEFAULT, 0, &localSystemTime, NULL, bufTime, dateTimeStrLen);
		strFileTime += bufTime;
		strFileTime += " - Date: ";

		TCHAR bufDate[dateTimeStrLen] = { '\0' };
		GetDateFormat(LOCALE_USER_DEFAULT, 0, &localSystemTime, NULL, bufDate, dateTimeStrLen);
		strFileTime += bufDate;
	}
	return strFileTime;
}

FILETIME PathUtils::GetFileTimeProperty(const CString & strFile, FILE_TIME_PROPERTY fileTime)
{
	FILETIME ft;
	WIN32_FILE_ATTRIBUTE_DATA attributes;
	if (GetFileAttributesEx(strFile, GetFileExInfoStandard, &attributes) != 0)
	{
		switch (fileTime)
		{
		case FILE_TIME_PROPERTY::FILE_TIME_CREATED:
			ft = attributes.ftCreationTime;
			break;
		case FILE_TIME_PROPERTY::FILE_TIME_LAST_MODIFIED:
			ft = attributes.ftLastWriteTime;
			break;
		default:
			ft = attributes.ftLastAccessTime;
			break;
		}
	}
	return ft;
}

BOOL PathUtils::IsFileExistsAtCurrentPath(CString & strFile)
{
	if (PathFileExists(strFile)) return TRUE;
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	strFile = CString(buffer) + _T("\\") + strFile;
	if (PathFileExists(strFile)) return TRUE;
	return FALSE;
}

BOOL PathUtils::CopyDirectory(const CString & strSourceFolder, const CString & strDestFolder)
{
	CString new_sf = strSourceFolder + _T("\\*");
	new_sf.Replace(_T("/"), _T("\\"));
	new_sf.Replace(_T("\\\\"), _T("\\"));

	CString new_tf = strDestFolder;
	new_tf.Replace(_T("/"), _T("\\"));
	new_tf.Replace(_T("\\\\"), _T("\\"));

	WCHAR sf[MAX_PATH + 1];
	WCHAR tf[MAX_PATH + 1];

	wcscpy_s(sf, MAX_PATH, new_sf);
	wcscpy_s(tf, MAX_PATH, new_tf);

	sf[lstrlenW(sf) + 1] = 0;
	tf[lstrlenW(tf) + 1] = 0;

	SHFILEOPSTRUCTW s = { 0 };
	s.wFunc = FO_COPY;
	s.pTo = tf;
	s.pFrom = sf;
	s.fFlags = FOF_SILENT | FOF_NOCONFIRMMKDIR | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NO_UI;
	int res = SHFileOperationW(&s);

	return res == 0;
}

CString PathUtils::ReadLastCharacterFromFile(const CString & strFile)
{
	char last[1];
	FILE *f = fopen(AppUtils::CStringToStd(strFile).c_str(), "rb");
	if (f == 0) throw 0;
	try
	{
		if (fseek(f, -1, SEEK_END) != 0) throw 0;
		if (fread(last, 1, 1, f) != 1) throw 0;
	}
	catch (...)
	{
		fclose(f);
		throw;
	}
	fclose(f);
	return CString(last);
}

BOOL PathUtils::IsFileHasTrailingReturn(const CString & strFile)
{
	std::wifstream ifs(strFile);
	if (!ifs) return FALSE;
	ifs.seekg(-1, std::ios_base::end); // go to one position before the EOF
	wchar_t charBeforeEOL;
	ifs.get(charBeforeEOL); // read current character
	if (charBeforeEOL == L'\n' || charBeforeEOL == L'\r')
	{
		return TRUE;
	}
	return FALSE;
}

CString PathUtils::GetFileSystemInformation(const CString & strFullPath)
{
	if (PathFileExists(strFullPath))
	{
		if (IsDirectory(strFullPath))
		{
			CString strFilePath = strFullPath + EDITOR_NEW_LINE_LF;
			CString strSerparator = _T("____________________________________________________________");
			CString strCreatedAt = _T("Created:            ") + PathUtils::GetFileTimePropertyCString(strFullPath, FILE_TIME_PROPERTY::FILE_TIME_CREATED);
			CString strLastestModifiedate = _T("Last Modified:  ") + PathUtils::GetFileTimePropertyCString(strFullPath, FILE_TIME_PROPERTY::FILE_TIME_LAST_MODIFIED);
			CString strLastestAccessedate = _T("Last Accsess:     ") + PathUtils::GetFileTimePropertyCString(strFullPath, FILE_TIME_PROPERTY::FILE_TIME_LAST_ACCESSED);
			CString strFileDescription = _T("Description:      Directory");
			// join information...
			strFilePath += strSerparator + EDITOR_NEW_LINE_LF;
			strFilePath += strCreatedAt + EDITOR_NEW_LINE_LF;
			strFilePath += strLastestModifiedate + EDITOR_NEW_LINE_LF;
			strFilePath += strLastestAccessedate + EDITOR_NEW_LINE_LF;
			strFilePath += strFileDescription + EDITOR_NEW_LINE_LF;
			return strFilePath;
		}
		else
		{
			CString strFilePath = strFullPath + EDITOR_NEW_LINE_LF;
			CString strSerparator = _T("____________________________________________________________");
			CString strCreatedAt = _T("Created:             ") + PathUtils::GetFileTimePropertyCString(strFullPath, FILE_TIME_PROPERTY::FILE_TIME_CREATED);
			CString strLastestModifiedate = _T("Last Modified:  ") + PathUtils::GetFileTimePropertyCString(strFullPath, FILE_TIME_PROPERTY::FILE_TIME_LAST_MODIFIED);
			CString strLastestAccessedate = _T("Last Accsess:     ") + PathUtils::GetFileTimePropertyCString(strFullPath, FILE_TIME_PROPERTY::FILE_TIME_LAST_ACCESSED);
			CString strFileDescription = _T("Description:      ") + AppUtils::GetFileFormatDescription(GetFileExtention(strFullPath));
			LONGLONG llFileSize = PathUtils::GetFileSize(strFullPath);
			CString strFileSize = _T("Size:                   ") + CString(std::unique_ptr<char>(PathUtils::SizeMemoryToString(llFileSize)).get());
			CString strReadonly = _T("Read Only:        ");
			if (PathUtils::IsFileReadOnly(strFullPath))
			{
				strReadonly += _T("Yes");
			}
			else
			{
				strReadonly += _T("No");
			}
			// join information...
			strFilePath += strSerparator + EDITOR_NEW_LINE_LF;
			strFilePath += strLastestModifiedate + EDITOR_NEW_LINE_LF;
			strFilePath += strLastestAccessedate + EDITOR_NEW_LINE_LF;
			strFilePath += strFileDescription + EDITOR_NEW_LINE_LF;
			strFilePath += strFileSize + EDITOR_NEW_LINE_LF;
			strFilePath += strReadonly + EDITOR_NEW_LINE_LF;
			return strFilePath;
		}
	}
	else
	{
		return _T("Can not find system information from this path...\n");
	}
}