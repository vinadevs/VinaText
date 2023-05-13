/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

const UINT USER_EXTENSIONS_MAX = 30;

class CUserExtension final
{
public:
	struct CommandData
	{
		CString _strCMD;
		CString _strRunFromDirectory;
		CString _strExtensionKeepConsole;
		CommandData(const CString& strCMD, const CString& strRunFromDirectory, const CString& strExtensionKeepConsole) : _strCMD(strCMD), _strRunFromDirectory(strRunFromDirectory),
			_strExtensionKeepConsole(strExtensionKeepConsole) {}
	};
	CUserExtension() {}
	~CUserExtension() {}
	void OpenConfigFile();
	void LoadMenuUserExtensions(CMenu* pExtensionsMenu, BOOL bRefresh = FALSE);
	void InvokeCommand(UINT nIDExtension);
private:
	std::unordered_map<UINT, CommandData> m_ExtensionData;
};