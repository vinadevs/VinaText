/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

//////////////////////////////////
// path utils

namespace PathUtils
{
	HMODULE LoadEditorDll(CString strEditorDll = NULL);
	HMODULE LoadLexerDll(CString strLexerDll = NULL);
	CString	GetVinaTextPath();
	CString	GetVinaTextExePath();
	CString	GetVinaTextTempPath();
	CString GetVinaTextBookmarkPath();
	CString GetVinaTextBackUpPath();
	CString	GetVinaTextAppDataPath();
	CString GetLanguageSettingFilePath(const CString & strLanguageName);
	CString GetLanguageTemplateFilePath(VINATEXT_SUPPORTED_LANGUAGE language);
	CString	GetUserExtensionPath();
	CString	GetVinaTextPackagePath();
	CString	GetVinaTextLocalizationPath();
	CString GetAbsolutePath(const CString& strPath);
	CString GetDataBaseFileFilter();
	CString	GetWindowSystemPath();
	CString	GetProgramFilePath();
	CString GetDataBaseFileFilter();
	CString GetFileExtention(const CString& strFile);
	CString GetFilePathWithoutExtention(const CString& strFile);
	CString GetFileNameWithoutExtension(const CString& strFileName);
	CString GetLastLevelPath(const CString& strPath);
	void DeleteFilesInFolderPermanently(const CString& strFolder, const CString&  csExt);
	void DeleteFilesInFolder(HWND hParentHWND, const CString & strFolder, const CString & csExt);
	BOOL RenameFile(const CString& strFileOld, const CString& strFileNew);
	CString GetContainerPath(const CString&  path);
	CString GetFilenameFromPath(LPCTSTR path);
	void GetPathComponents(const CString& strPath, CString& strDrive, CString& strDir, CString& strFName, CString& strExt);
	CString GetCopyFileFromSourceFile(const CString& strDestFolder, const CString& strSourceFile, BOOL bIsCutFileOperation = FALSE);
	CString BackslashToForwardslash(LPCTSTR path);
	BOOL IsDirectory(const CString& strPath);
	BOOL IsFileAlreadyOpened(const CString& strPath);
	BOOL GetAllPathsByExtensionFromFolder(const CString& path, std::vector<CString>& vecFileName, std::vector<CString>& vecPath, CString strStringInFilePath, CString strFileExt = _T("\\*.*"));
	void GetAllFilesFromFolder(const CString& sDir, std::vector<CString>& vecFiles, BOOL bIncludeSubFolder = TRUE);
	void GetAllFolderFromFolder(const CString& sDir, std::vector<CString>& vecPaths, BOOL bIncludeSubFolder = TRUE);
	void GetAllPathFromFolder(const CString& sDir, std::vector<CString>& vecPaths, BOOL bIncludeSubFolder = TRUE);
	BOOL CreateNewEmptyFile(const CString& szFile);
	BOOL SaveFileTruncate(const CString& szFile, const CString& strContent);
	BOOL SaveFileAppend(const CString& szFile, CString& strContentToAppend);
	BOOL SaveFileAppendNoDuplicateLine(const CString& szFile, CString& strContentToAppend);
	CString FileContentToUtf8(const CString& szFile);
	BOOL OpenFile(const CString& szFile, CString & strContent);
	BOOL OpenFile(const CString& szFile, CStringArray& arrLine);
	BOOL OpenFileBinaryMode(const CString & strFile, std::string & str);
	char* OpenFileToBuffer(const CString&  szFile, long* lSize);
	BOOL IsFileChanged(const CString& strFilePath1, const CString& strFilePath2);
	BOOL IsFileContentChanged(const CString& strFilePath, const CString& strContent);
	void DeletePathPermanently(LPCTSTR pstrPath);
	BOOL SendToRecycleBin(HWND hParentHWND, const CString& strPath, BOOL bAllowUndo = TRUE);
	BOOL CreateDirectoryIfNotExited(LPCTSTR pstrPath);
	BOOL IsFileReadOnly(const CString& szFile);
	LONGLONG GetFileSize(const CString& szFile);
	char * SizeMemoryToString(uint64_t size);
	BOOL OpenFileSystem(CString szFile);
	BOOL IsBlockFormatFileMailServer(const CString & strFile);
	BOOL IsExeFile(const CString& strPath);
	BOOL IsBinaryFile(const CString & strFile, BINARY_FILE_TYPE BinnaryFileType = FILE_BINNARY);
	BOOL IsBinaryFileByContent(const CString & strFile);
	BOOL IsImageFile(const CString & strFile);
	BOOL IsGifFile(const CString & strFile);
	BOOL IsPdfFile(const CString & strFile);
	BOOL IsMediaFile(const CString & strFile);
	BOOL IsOfficeFile(const CString & strFile);
	BOOL IsOfficeWordFile(const CString & strFile);
	BOOL IsOfficePptFile(const CString & strFile);
	BOOL IsOfficeExcelFile(const CString & strFile);
	int CountWordsFromFile(const CString & strFile);
	CString GetFileTimePropertyCString(const CString & strFile, FILE_TIME_PROPERTY fileTime);
	FILETIME GetFileTimeProperty(const CString & strFile, FILE_TIME_PROPERTY fileTime);
	BOOL IsFileExistsAtCurrentPath(CString & strFile);
	BOOL CopyDirectory(const CString & strSourceFolder, const CString & strDestFolder);
	CString ReadLastCharacterFromFile(const CString& strFile);
	BOOL IsFileHasTrailingReturn(const CString& strFile);
	CString GetFileSystemInformation(const CString & strFullPath);
}