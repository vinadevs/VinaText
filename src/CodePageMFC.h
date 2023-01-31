/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include <afxtempl.h>
#include <afxmt.h>

class CCodePage
{
private:
	// Code page ID container typedef
	// You can replace this with a container implementation of your choice
	typedef CArray<UINT, UINT> CodePageContainer;
public:
	class CCodePageObject
	{
	private:
		CodePageContainer s_arrCodePages;	// Container of code page IDs
		static CCriticalSection s_critSec;	// Critical section used for thread-safety
		static CCodePageObject* s_pCurrent;	// Current code page object being filled
	public:
		// Return the number of available code pages
		int GetCount() const;
		// Return a code page at a specific index
		int operator[](int nIndex) const;
		// Returns true if the code page container is empty
		bool IsEmpty() const; 
		// Return the name of a code page at a specific index in the container
		CString GetName(int nIndex) const;
		// Enumerate code pages using specific flags
		static void EnumerateCodePages(CCodePageObject* pObject);
	private:
		// Add a new code page to the container
		void Add(UINT nCodePage);
		// EnumSystemCodePages callback function (Installed)
		static BOOL CALLBACK EnumCodePagesProc(LPTSTR lpCodePageString);
		// Pure virtual function that returns the flags to be passed
		// to the EnumSystemCodePages function
		virtual DWORD GetFlags() const = 0;
	};

	// Class used to store installed code page IDs
	class CInstalled : public CCodePageObject
	{
	private:
		virtual DWORD GetFlags() const { return CP_INSTALLED; }
	};

	// Class used to store supported code page IDs
	class CSupported : public CCodePageObject
	{
	private:
		virtual DWORD GetFlags() const { return CP_SUPPORTED; }
	};
private:
	CInstalled m_cpInstalled;	// Installed code pages
	CSupported m_cpSupported;	// Supported code pages		
public:
	// Get the installed code pages
	const CCodePageObject& GetInstalled();
	// Get the supported code pages
	const CCodePageObject& GetSupported();
};