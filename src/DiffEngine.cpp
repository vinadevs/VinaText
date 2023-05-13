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

#include "stdafx.h"
#include "FilePartition.h"
#include "DiffEngine.h"
#include "PathUtil.h"

CDiffEngine::CDiffEngine()
{
	m_szColorText		= _T("#888888"); // default colors
	m_szColorBackground = _T("white");
	m_szColorChanged	= _T("#FFFFBB");
	m_szColorAdded		= _T("#BBFFBB");
	m_szColorDeleted	= _T("#FFBBBB");
	m_szFooter = _T("<br><font size='-2' color='#BBBBBB'></font>");
}

// compare f1 (old version) with f2 (new version)
// and build two new copies of those file objects with status on a line by line basis
//
BOOL CDiffEngine::Diff(	/*in*/CFilePartition &f1, /*in*/CFilePartition &f2,
						/*out*/CFilePartition &f1_bis, /*out*/CFilePartition &f2_bis)
{
	f1_bis.SetName( f1.GetName() );
	f2_bis.SetName( f2.GetName() );
	long nbf1Lines = f1.GetNBLines();
	long nbf2Lines = f2.GetNBLines();
	// special empty file case
	if ( nbf1Lines==0 )
	{
		long nLinef2 = 0;
		CString s;
		while ( nLinef2<nbf2Lines )
		{
			f1_bis.AddBlankLine();
			f2_bis.AddString( f2.GetRawLine(nLinef2++), Normal);
		}
		return TRUE;
	}
	long i = 0;
	long nf2CurrentLine = 0;
	while ( i<nbf1Lines )
	{
		// process this line (and possibly update indexes as well)
		long nLinef2 = nf2CurrentLine;
		if ( nLinef2 >= nbf2Lines )
		{
			// it's time to end the game now
			while ( i < nbf1Lines )
			{
				f1_bis.AddString( f1.GetRawLine(i), Deleted);
				f2_bis.AddBlankLine();
				i++;
			}
			break;
		}
		if ( f1.MatchLine(i, f2, /*out*/nLinef2) )
		{
			BOOL bDeleted = FALSE;
			if (nLinef2 > nf2CurrentLine)
			{
				long itmp = nf2CurrentLine;
				bDeleted = f2.MatchLine(nf2CurrentLine, f1, /*out*/itmp) && (itmp<nLinef2);
				if (bDeleted)
				{
					long j = itmp - i;
					while ( j>0 )
					{
						f1_bis.AddString( f1.GetRawLine(i), Deleted);
						f2_bis.AddBlankLine();

						i++;
						j--;
					}
					// please note nf2CurrentLine is not updated
					continue; // jump here to loop iteration
				}
			}
			// matched, so either the lines were identical, or f2 has added one or more lines
			if (nLinef2 > nf2CurrentLine)
			{
				// add blank lines to f1_bis
				long j = nLinef2 - nf2CurrentLine;
				while ( j>0 )
				{
					f1_bis.AddBlankLine();
					f2_bis.AddString( f2.GetRawLine(nLinef2-j), Added );

					j--;
				}
			}
			// exactly matched
			f1_bis.AddString( f1.GetRawLine(i), Normal);
			f2_bis.AddString( f2.GetRawLine(nLinef2), Normal);
			nf2CurrentLine = nLinef2 + 1; // next line in f2
		}
		else
		{
			// this line is not found at all in f2, either it's because it has been changed, or even deleted
			long nLinef1 = i;
			if ( f2.MatchLine(nLinef2, f1, /*out*/nLinef1) )
			{
				// the dual line in f2 can be found in f1, that's because
				// the current line in f1 has been deleted
				f1_bis.AddString( f1.GetRawLine(i), Deleted);
				f2_bis.AddBlankLine();
				// this whole block is flagged as deleted
				if (nLinef1>i+1)
				{
					long j = nLinef1 - (i+1);
					while ( j>0 )
					{
						i++;

						f1_bis.AddString( f1.GetRawLine(i), Deleted);
						f2_bis.AddBlankLine();
						j--;
					}
				}
				// note : nf2CurrentLine is not incremented
			}
			else
			{
				// neither added, nor deleted, so it's flagged as changed
				f1_bis.AddString( f1.GetRawLine(i), Changed);
				f2_bis.AddString( f2.GetRawLine(nLinef2), Changed);

				nf2CurrentLine = nLinef2 + 1; // next line in f2
			}
		}
		i++; // next line in f1
	}
	// are there any remaining lines from f2?
	while ( nf2CurrentLine < nbf2Lines )
	{
		f1_bis.AddBlankLine();
		f2_bis.AddString( f2.GetRawLine(nf2CurrentLine), Added );
		nf2CurrentLine++;
	}
	return TRUE;
}







// build html report
//



void CDiffEngine::SetTitles(CString &szHeader, CString &szFooter)
{
	m_szHeader = szHeader;
	m_szFooter = szFooter;
}

void CDiffEngine::SetColorStyles(CString &szText, CString &szBackground, CString &szChanged, CString &szAdded, CString &szDeleted)
{
	m_szColorText = szText;
	m_szColorBackground = szBackground;
	m_szColorChanged = szChanged;
	m_szColorAdded = szAdded;
	m_szColorDeleted = szDeleted;
}

CString CDiffEngine::Serialize(	/*in*/CFilePartition &f1, 
								/*in*/CFilePartition &f2)
{

	// eval amount of differences between the two files
	int nAdded_f1, nChanged_f1, nDeleted_f1;
	f1.HowManyChanges(/*out*/nAdded_f1, /*out*/nChanged_f1, /*out*/nDeleted_f1);
	int nAdded_f2, nChanged_f2, nDeleted_f2;
	f2.HowManyChanges(/*out*/nAdded_f2, /*out*/nChanged_f2, /*out*/nDeleted_f2);

	int nTotal = nAdded_f1 + nDeleted_f1 + nChanged_f1 + nAdded_f2 + nDeleted_f2;

	if (nTotal==0)
		m_szHeader += _T("<font size=-1><b>Compare Result: 2 paths are identical.</font><br>");
	else
	{
		TCHAR szTmp[128];
		wsprintf(szTmp, _T("<font size=-1><b>Compare Result: there are %d change(s) between 2 paths.</font><br>"), nTotal);
		m_szHeader += szTmp;
	}

	// write html header
	CString s = _T("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\r\n") \
		_T("<!-- diff html gen -->\r\n") \
		_T("<HTML>\r\n") \
		_T("<HEAD>\r\n") \
		_T("<TITLE> File Diff </TITLE>\r\n") \
		_T("<style type='text/css'>\r\n") \
		_T("<!--\r\n") \
		_T(".N { background-color:white; }\r\n") \
		_T(".C { background-color:") + m_szColorChanged + _T("; }\r\n") \
		_T(".A { background-color:") + m_szColorAdded + _T("; }\r\n") \
		_T(".D { background-color:") + m_szColorDeleted + _T("; }\r\n") \
		_T("-->\r\n") \
		_T("</style>\r\n") \
		_T("</HEAD>\r\n") \
		_T("\r\n") \
		_T("<BODY BGCOLOR='#FFFFFF'>\r\n") \
		_T("\r\n") + m_szHeader + \
		_T("<table border=0 bgcolor=0 cellpadding=1 cellspacing=1 width=100%><tr><td>\r\n") \
		_T("<table width=100% bgcolor=white border=0 cellpadding=0 cellspacing=0>\r\n") \
		_T("<tr bgColor='#EEEEEE' style='color:0'><td width=50%>Left Side</td><td width=50%>Right Side") \
		_T("&nbsp;&nbsp;&nbsp;(<b style='background-color:") + m_szColorChanged + _T(";width:20'>&nbsp;</b>changed&nbsp;&nbsp;") \
		_T("<b style='background-color:") + m_szColorAdded + _T(";width:20'>&nbsp;</b>added&nbsp;&nbsp;") \
		_T("<b style='background-color:") + m_szColorDeleted + _T(";width:20'>&nbsp;</b>deleted)&nbsp;&nbsp;") \
		_T("<FORM ACTION='' style='display:inline'><SELECT id='fontoptions' ") \
		_T("onchange='maintable.style.fontSize=this.options[this.selectedIndex].value'>") \
		_T("<option value='6pt'>6pt<option value='7pt'>7pt<option value='8pt'>8pt<option value='9pt' selected>9pt</SELECT> ") \
		_T("</FORM></td></tr>\r\n") \
		_T("<tr bgColor='#EEEEEE' style='color:0'><td width=50%><code>") + f1.GetName() + _T("</code></td><td width=50%><code>") + f2.GetName() + _T("</code></td></tr>") \
		_T("</table>\r\n") \
		_T("</td></tr>\r\n") \
		_T("</table>\r\n") \
		_T("\r\n") \
		_T("<br>\r\n") \
		_T("\r\n") ;

	long nbLines = f1.GetNBLines();
	if (nbLines==0)
	{
		s += _T("<br>empty files");
	}
	else
	{
		s += _T("<table border=0 bgcolor=0 cellpadding=1 cellspacing=1 width=100%><tr><td>") \
			_T("<table id='maintable' width=100% bgcolor='") + m_szColorBackground + _T("' cellpadding=0 cellspacing=0 border=0 style='color:")
			+ m_szColorText + _T(";font-family: Courier New, Helvetica, sans-serif; font-size: 8pt'>\r\n");
	}

	
	CString arrStatus[4] = {
		_T(""),
		_T(" class='C'"),
		_T(" class='A'"),
		_T(" class='D'") };

	CString sc;

	TCHAR szLine[16];

	// write content
	//
	for (long i=0; i<nbLines; i++)
	{
		wsprintf(szLine, _T("<b>%d</b>"), i);
		sc += _T("<tr><td width=50%") + CString(arrStatus[ f1.GetStatusLine(i) ]) + _T(">") +
			  CString(szLine) + 
			  _T(" ") +
			  Escape(f1.GetRawLine(i)) + _T("</td>");
		sc += _T("<td width=50%") + CString(arrStatus[ f2.GetStatusLine(i) ]) + _T(">") +
			  CString(szLine) + 
			  _T(" ") +
			  Escape(f2.GetRawLine(i)) + _T("</td></tr>");
		
	} // for i

	s += sc;

	if (nbLines>0)
		s += _T("</table></td></tr></table>\r\n");

	// write html footer
	s += m_szFooter + _T("</BODY>\r\n") \
		_T("</HTML>\r\n");

	return s;
}

CString CDiffEngine::Escape(CString &s) // a helper aimed to make sure tag symbols are passed as content
{
	CString o;
	long nSize = s.GetLength();
	if (nSize==0) return CString("&nbsp;");

	TCHAR c;
	BOOL bIndentation = TRUE;

	for (long i=0; i<nSize; i++)
	{
		c = s.GetAt(i);
		if (bIndentation && (c == _T(' ') || c == _T('\t')))
		{
			if (c == _T(' '))
				o += _T("&nbsp;");
			else
				o += _T("&nbsp;&nbsp;&nbsp;&nbsp;");
			continue;
		}
		bIndentation = FALSE;

		if (c == _T('<'))
			o += _T("&lt;");
		else if (c == _T('>'))
			o += _T("&gt;");
		else if (c == _T('&'))
			o += _T("&amp;");
		else
			o += c;
	}
	return o;
}