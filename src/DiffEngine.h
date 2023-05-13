/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

// DiffEngine ////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////
// Original version from S.Rodriguez - Feb 2003
//////////////////////////////////////////////////////////////////////
//
//

#pragma once

class CDiffEngine
{
	// Members
protected:
	CString m_szColorText, m_szColorBackground, m_szColorChanged, m_szColorAdded, m_szColorDeleted; // used by the html renderer
	CString m_szHeader, m_szFooter;

	// Constructor
public:
	CDiffEngine();

	// Accessors
public:

	// Methods

	// compare f1 (old version) with f2 (new version)
	// and build two new copies of those file objects with status on a line by line basis
	//
	BOOL Diff(	/*in*/CFilePartition &f1, /*in*/CFilePartition &f2,
				/*out*/CFilePartition &f1_bis, /*out*/CFilePartition &f2_bis);

	// build html report
	//
	void SetTitles(/*in*/CString &szHeader, /*in*/CString &szFooter);
	void SetColorStyles(/*in*/CString &szText, /*in*/CString &szBackground, /*in*/CString &szChanged, /*in*/CString &szAdded, /*in*/CString &szDeleted);

	CString Serialize(	/*in*/CFilePartition &f1, 
						/*in*/CFilePartition &f2);

	// Helpers
protected:
	CString Escape(CString &s);
};