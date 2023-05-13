/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

// FilePartition /////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////
// Original version from S.Rodriguez - Feb 2003
//////////////////////////////////////////////////////////////////////
//
//

#pragma once

typedef enum {Normal=0, Changed, Added, Deleted} LineStatus;

class CFileLine; // forward declaration
class CFileOptions; // forward declaration
class CFilePartition; // forward declaration

class CFileLine
{
	// Members
protected:
	CString m_s;
	LineStatus m_status;

	// Constructor
public:
	CFileLine();

	// Accessors
public:
	long SetLine(/*in*/CString &s, /*in*/CFileOptions &o); // store string and build token
	void SetLine(/*in*/CString &s, /*in*/LineStatus ls); // store string and status (does not eval token)
	CString GetLine(/*in*/CFileOptions &o);

	void SetStatus(/*in*/LineStatus ls);
	LineStatus GetStatus();
	
	// Helpers
protected:
	CString GetLineWithOptions(/*in*/CString s,/*in*/CFileOptions &o); // that's where options are implemented
};


typedef CArray<CFileLine*>	ArrayLines;
typedef CArray<long>		ArrayLong;
typedef CArray<CString>		ArrayCString;

class CSortedArray : public CArray<CString>
{
	// Methods
public:

	// InsertSorted
	//
	// purpose : this methods enhances InsertAt(i, szNewElement) by automatically
	//           providing a sorting mechanism ( o(n2) ).
	//
	void InsertSorted(CString& szNewElement)
	{
		if (m_nSize == 0)
		{
			Add(szNewElement);
			return;
		}
		long nbSize = static_cast<long>(GetSize());
		for (long i = 0; i < nbSize; i++)
		{
			if (GetAt(i).CompareNoCase(szNewElement) < 0)
			{
				InsertAt(i, szNewElement);
				return;
			}
		}
		// no insertion, so add it
		Add(szNewElement);
	}
};

// CFileOptions /////////////////////////////////////////////////////
//

class CFileOptions
{
	// Members
protected:
	ArrayCString m_arrOptions;

	// "indent" : should the diff engine see differences in tabs/spaces (default = yes)
	// "case" : should the diff engine see case differences (default = yes)

	// how to use this class :
	//       CFileOptions o;
	//       o.SetOption("indent","yes");

	// Constructor
public:
	CFileOptions();

	// Accessors
public:
	void SetOption(/*in*/CString &szOptionName, /*in*/CString &szOptionValue);
	CString GetOption(/*in*/CString &szOptionName);

	BOOL IsDefaultOptions();
		
	long GetOptionCount();
	CString GetOption(long i);

	// Methods
	void Copy(CFileOptions &src);
};

// CFilePartition ///////////////////////////////////////////////////
//

class CFilePartition
{

	// Members
protected:
	CString			m_szFilename;
	CFileOptions	m_options;
	ArrayLines		m_arrLines;
	ArrayLong		m_arrTokens;

	// Constructor
public:
	CFilePartition();
	virtual ~CFilePartition();

	// Accessors
public:
	void SetName(/*in*/CString &);
	CString GetName();

	void SetOptions(/*in*/CFileOptions &options);

	long GetNBLines(); // amount of lines of this file
	CString GetLine(/*in*/long i); // returns an arbitrary line
	CString GetRawLine(/*in*/long i); // returns an arbitrary line (not filtered)
	LineStatus GetStatusLine(/*in*/long i); // returns the status of an arbitrary lin
	long *GetTokens(); // token table

	void HowManyChanges(/*out*/int &nAdded, /*out*/int &nChanged, /*out*/int &nDeleted);


	// Methods
	BOOL PreProcess(/*in*/CString &szFilename, /*in*/CFileOptions &options);
	BOOL PreProcessFolder(/*in*/CString &szFolder, /*in*/CFileOptions &options);

	void AddString(/*in*/CString &s, /*in*/LineStatus ls);
	void AddBlankLine();

	BOOL MatchLine(/*in*/long i1, /*in*/CFilePartition &f2,  /*out*/long &i2);

	void Dump(/*in*/CString &szTitle);


	// Helpers
protected:
	BOOL PreProcessFolder(/*in*/CString &szFolder, /*in*/CFileOptions &options, /*in/out*/long nIndent);
	void AddString(/*in*/CString &s);
};