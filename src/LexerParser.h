/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#define BOOL_TRUE  _T("true")
#define BOOL_FALSE  _T("false")

class CLexingParser  
{
public:
	CLexingParser();
	CLexingParser(const CString string, CString strDelim =CSTRING_SPACE);
	virtual ~CLexingParser();

public:
   virtual CString Next();
   virtual CString NextString(BOOL bRemoveQuotes = FALSE, CString strDefault = _T(""));
   virtual int     NextInt(int nDefault = 0);
   virtual long    NextLong(long nDefault = 0L);
   virtual float   NextFloat(float fDefault = 0.0);
   virtual double  NextDouble(double fDefault = 0.0);
   virtual BOOL    NextBool(BOOL bDefault = FALSE);
   virtual BOOL HasMoreTokens();
   virtual void SetDelimiter(CString strDelim){m_Delimiter = strDelim;};
   virtual void SetString(const CString string);

protected:
   CString m_Copy;
   CString m_Delimiter;
   int m_nPosition;
};
