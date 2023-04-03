/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "StringHelper.h"
#include "AppSettings.h"
#include "AppUtil.h"

//////////////////////////////////
// C String Helper

namespace StringHelper
{
	static wint_t normch(wint_t c);

	// Convert any negative inputs to negative char equivalents
	// This is aimed at correcting any chars mistakenly 
	// sign-extended to negative ints.
	// This is ok for the UNICODE build because UCS-2LE code bytes
	// do not extend as high as 2Gig (actually even full Unicode
	// codepoints don't extend that high).
	static wint_t normch(wint_t c)
	{
#ifdef _UNICODE
		return (unsigned short)(short)c;
#else
		return (unsigned char)(char)c;
#endif
	}

	/** @brief Return nonzero if input is outside ASCII or is underline. */
	int xisspecial(wint_t c)
	{
		return normch(c) > (unsigned)_T('\x7f') || c == _T('_');
	}

	/**
	 * @brief Return non-zero if input is alphabetic or "special" (see xisspecial).
	 * Also converts any negative inputs to negative char equivalents (see normch).
	 */
	int xisalpha(wint_t c)
	{
		return _istalpha(normch(c)) || xisspecial(normch(c));
	}

	/**
	 * @brief Return non-zero if input is alphanumeric or "special" (see xisspecial).
	 * Also converts any negative inputs to negative char equivalents (see normch).
	 */
	int xisalnum(wint_t c)
	{
		return _istalnum(normch(c)) || xisspecial(normch(c));
	}

	/**
	 * @brief Return non-zero if input character is a space.
	 * Also converts any negative inputs to negative char equivalents (see normch).
	 */
	int xisspace(wint_t c)
	{
		return _istspace(normch(c));
	}

	bool IsMBSTrail(const TCHAR *pszChars, int nCol)
	{
#ifdef _UNICODE
		const wchar_t *current = pszChars + nCol;
		if (*current >= 0xDC00 && *current <= 0xDFFF) // surrogate pair 
			return true;
		return false;
#else // _UNICODE
		const unsigned char *string = (const unsigned char *)pszChars;
		const unsigned char *current = string + nCol;
		if (_ismbstrail(string, current) < 0)
			return true;
		return false;
#endif // _UNICODE
	}


	bool isUrlSchemeStartChar(TCHAR const c)
	{
		return ((c >= 'A') && (c <= 'Z'))
			|| ((c >= 'a') && (c <= 'z'));
	}

	bool isUrlSchemeDelimiter(TCHAR const c) // characters allowed immedeately before scheme
	{
		return   !(((c >= '0') && (c <= '9'))
			|| ((c >= 'A') && (c <= 'Z'))
			|| ((c >= 'a') && (c <= 'z'))
			|| (c == '_'));
	}

	bool isUrlTextChar(TCHAR const c)
	{
		if (c <= ' ') return false;
		switch (c)
		{
		case '"':
		case '#':
		case '\'':
		case '<':
		case '>':
		case '{':
		case '}':
		case '?':
		case '\0x7f':
			return false;
		}
		return true;
	}

	bool isUrlQueryDelimiter(TCHAR const c)
	{
		switch (c)
		{
		case '&':
		case '+':
		case '=':
		case ';':
			return true;
		}
		return false;
	}

	bool isUrlSchemeSupported(INTERNET_SCHEME s)
	{
		switch (s)
		{
		case INTERNET_SCHEME_FTP:
		case INTERNET_SCHEME_HTTP:
		case INTERNET_SCHEME_HTTPS:
		case INTERNET_SCHEME_MAILTO:
		case INTERNET_SCHEME_FILE:
			return true;
		}
		return false;
	}

	// scanToUrlStart searches for a possible URL in <text>.
	// If a possible URL is found, then:
	// - True is returned.
	// - The number of characters between <text[start]> and the beginning of the URL candidate is stored in <distance>.
	// - The length of the URL scheme is stored in <schemeLength>.
	// If no URL is found, then:
	// - False is returned.
	// - The number of characters between <text[start]> and the end of text is stored in <distance>.
	bool scanToUrlStart(TCHAR *text, int textLen, int start, int* distance, int* schemeLength)
	{
		int p = start;
		int p0 = 0;
		enum { sUnknown, sScheme } s = sUnknown;
		while (p < textLen)
		{
			switch (s)
			{
			case sUnknown:
				if (isUrlSchemeStartChar(text[p]) && ((p == 0) || isUrlSchemeDelimiter(text[p - 1])))
				{
					p0 = p;
					s = sScheme;
				}
				break;

			case sScheme:
				if (text[p] == ':')
				{
					*distance = p0 - start;
					*schemeLength = p - p0 + 1;
					return true;
				}
				if (!isUrlSchemeStartChar(text[p]))
					s = sUnknown;
				break;
			}
			p++;
		}
		*schemeLength = 0;
		*distance = p - start;
		return false;
	}

	// scanToUrlEnd searches the end of an URL, coarsly parsing its main parts HostAndPath, Query and Fragment.
	//
	// In the query part, a simple pattern is enforced, to avoid that everything goes through as a query.
	// The pattern is kept simple, since there seem to be many different forms of queries used in the world.
	// The objective here is not to detect whether or not a query is malformed. The objective is, to let through
	// most of the real world's queries, and to sort out what is certainly not a query.
	//
	// The approach is:
	// - A query begins with '?', followed by any number of values,
	//   which are separated by a single delimiter character '&', '+', '=' or ';'.
	// - Each value may be enclosed in single or double quotes.
	//
	// The query pattern going through looks like this:
	// - ?abc;def;fgh="i j k"&'l m n'+opq
	//
	void scanToUrlEnd(TCHAR *text, int textLen, int start, int* distance)
	{
		int p = start;
		TCHAR q = 0;
		enum { sHostAndPath, sQuery, sQueryAfterDelimiter, sQueryQuotes, sQueryAfterQuotes, sFragment } s = sHostAndPath;
		while (p < textLen)
		{
			switch (s)
			{
			case sHostAndPath:
				if (text[p] == '?')
					s = sQuery;
				else if (text[p] == '#')
					s = sFragment;
				else if (!isUrlTextChar(text[p]))
				{
					*distance = p - start;
					return;
				}
				break;

			case sQuery:
				if (text[p] == '#')
					s = sFragment;
				else if (isUrlQueryDelimiter(text[p]))
					s = sQueryAfterDelimiter;
				else if (!isUrlTextChar(text[p]))
				{
					*distance = p - start;
					return;
				}
				break;

			case sQueryAfterDelimiter:
				if ((text[p] == '\'') || (text[p] == '"'))
				{
					q = text[p];
					s = sQueryQuotes;
				}
				else if (text[p] == '{')
				{
					q = '}';
					s = sQueryQuotes;
				}
				else if (isUrlTextChar(text[p]))
					s = sQuery;
				else
				{
					*distance = p - start;
					return;
				}
				break;

			case sQueryQuotes:
				if (text[p] < ' ')
				{
					*distance = p - start;
					return;
				}
				if (text[p] == q)
					s = sQueryAfterQuotes;
				break;

			case sQueryAfterQuotes:
				if (isUrlQueryDelimiter(text[p]))
					s = sQueryAfterDelimiter;
				else
				{
					*distance = p - start;
					return;
				}
				break;

			case sFragment:
				if (!isUrlTextChar(text[p]))
				{
					*distance = p - start;
					return;
				}
				break;
			}
			p++;
		}
		*distance = p - start;
	}

	// removeUnwantedTrailingCharFromUrl removes a single unwanted trailing character from an URL.
	// It has to be called repeatedly, until it returns false, meaning that all unwanted characters are gone.
	bool removeUnwantedTrailingCharFromUrl(TCHAR const *text, int* length)
	{
		int l = *length - 1;
		if (l <= 0) return false;
		{ // remove unwanted single characters
			const TCHAR *singleChars = L".,:;?!#";
			for (int i = 0; singleChars[i]; i++)
				if (text[l] == singleChars[i])
				{
					*length = l;
					return true;
				}
		}
		{ // remove unwanted closing parenthesis
			const TCHAR *closingParenthesis = L")]>";
			const TCHAR *openingParenthesis = L"([<";
			for (int i = 0; closingParenthesis[i]; i++)
				if (text[l] == closingParenthesis[i])
				{
					int count = 1;
					for (int j = l - 1; j >= 0; j--)
					{
						if (text[j] == closingParenthesis[i])
							count++;
						if (text[j] == openingParenthesis[i])
							count--;
					}
					if (count == 0)
						return false;
					*length = l;
					return true;
				}
		}
		{ // remove unwanted quotes
			const TCHAR *quotes = L"\"'`";
			for (int i = 0; quotes[i]; i++)
			{
				if (text[l] == quotes[i])
				{
					int count = 0;
					for (int j = l - 1; j >= 0; j--)
						if (text[j] == quotes[i])
							count++;

					if (count & 1)
						return false;
					*length = l;
					return true;
				}
			}
		}
		return false;
	}
}

//////////////////////////////////
// Text alignment

WordList CTextAlignment::SplitTextIntoWords(const std::wstring &text)
{
	WordList words;
	std::wistringstream  in(text);
	std::copy(std::istream_iterator<std::wstring, wchar_t, std::char_traits<wchar_t>>(in),
		std::istream_iterator<std::wstring, wchar_t, std::char_traits<wchar_t>>(), std::back_inserter(words));
	return words;
}

std::wstring CTextAlignment::AlignText(const std::wstring& text, Alignment align, const std::wstring& eol)
{
	std::wstringstream m_OutputBuffer;
	WordList words = SplitTextIntoWords(text);
	std::wstring line;
	for (const std::wstring& word : words)
	{
		if (line.size() + word.size() + 1 > AppSettingMgr.m_nPageAlignmentWidth)
		{
			// next word doesn't fit into the line.
			if (align == Alignment::Center)
			{
				m_OutputBuffer << std::wstring((AppSettingMgr.m_nPageAlignmentWidth - line.size()) / 2, ' ') << line << eol;
			}
			else if (align == Alignment::Justify)
			{
				size_t pos = line.find_first_of(' ');
				if (pos != std::wstring::npos)
				{
					while (line.size() < AppSettingMgr.m_nPageAlignmentWidth)
					{
						pos = line.find_first_not_of(' ', pos);
						line.insert(pos, L" ");
						pos = line.find_first_of(' ', pos + 1);
						if (pos == std::string::npos)
						{
							pos = line.find_first_of(' ');
						}
					}
				}
				m_OutputBuffer << line << eol;
			}
			else if (align == Alignment::Left)
			{
				m_OutputBuffer << line << eol;
			}
			else if (align == Alignment::Right)
			{
				m_OutputBuffer << std::setw(AppSettingMgr.m_nPageAlignmentWidth) << std::right << line << eol;
			}
			line.clear();
			line = word;
		}
		else
		{
			if (!line.empty())
			{
				line.append(L" ");
			}
			line.append(word);
		}
	}
	if (align == Alignment::Center)
	{
		m_OutputBuffer << std::wstring((AppSettingMgr.m_nPageAlignmentWidth - line.size()) / 2, ' ') << line << eol;
	}
	else if (align == Alignment::Left)
	{
		m_OutputBuffer << line << eol;
	}
	else if (align == Alignment::Right)
	{
		m_OutputBuffer << std::setw(AppSettingMgr.m_nPageAlignmentWidth) << std::right << line << eol;
	}
	else if (align == Alignment::Justify)
	{
		m_OutputBuffer << line << eol;
	}
	return m_OutputBuffer.str().substr(0, m_OutputBuffer.str().size() - eol.length());
}

//////////////////////////////////
// C++ STD String Helper

std::wstring STDStringHelper::Format(const wchar_t* frmt, ...)
{
	std::wstring buffer;
	if (frmt != nullptr)
	{
		va_list marker;

		va_start(marker, frmt);

		// Get formatted string length adding one for the NUL
		auto len = _vscwprintf(frmt, marker);
		if (len > 0)
		{
			buffer.resize(len + 1);
			_vsnwprintf_s(&buffer[0], buffer.size(), len, frmt, marker);
			buffer.resize(len);
		}

		va_end(marker);
	}
	return buffer;
}

std::string STDStringHelper::Format(const char* frmt, ...)
{
	std::string buffer;
	if (frmt != nullptr)
	{
		va_list marker;

		va_start(marker, frmt);

		// Get formatted string length adding one for the NUL
		auto len = _vscprintf(frmt, marker);
		if (len > 0)
		{
			buffer.resize(len + 1);
			_vsnprintf_s(&buffer[0], buffer.size(), len, frmt, marker);
			buffer.resize(len);
		}

		va_end(marker);
	}
	return buffer;
}
