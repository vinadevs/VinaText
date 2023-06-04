/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#ifndef _SEARCH_ENGINE_H_
#define _SEARCH_ENGINE_H_

#include "stdafx.h"

//We will have to escape all special characters in the string with \
//The most straightforward approach would be to use another expression 
//to sanitize the input string before creating the expression regex.

///////////////////////////////////////////////////////////////////////
// advanced settings find and replace data structures

struct ADVANCED_SEARCH_DATA
{
	CString _strSearchWhat;
	int _nSearchScope;
	int _nRegexPattern;
	CString _strFileFilter;
	CString _strSpecificPath;
	BOOL	_bMatchcase;
	BOOL	_bMacthregex;
	BOOL	_bMatchwords;
	BOOL	_bAppendResult;
	BOOL	_bShowFileNameOnly;
	BOOL	_bExcludeSubFolder;
};

///////////////////////////////////////////////////////////////////////
// search file data structures

struct PATH_RESULT_DATA
{
	CString _strPathName;
	CString _strLocation;
	CString _strPathType;
	CString _strPathSize;
	CString _strPathCreatedTime;
	CString _strPathModifiedTime;
	CString _strReadOnly;
};

typedef std::vector<PATH_RESULT_DATA> PATH_RESULT_DATA_LIST;

///////////////////////////////////////////////////////////////////////
// search line data structures

struct SEARCH_DATA_LINE
{
	CString _strTargetFile;
	CString _strLine;
	unsigned int _nLineNumber;
	unsigned int _nColumnNumber;
	unsigned int _nPositionNumber;

	SEARCH_DATA_LINE() :
		_nLineNumber(0),
		_nColumnNumber(0),
		_nPositionNumber(0),
		_strTargetFile(_T("")),
		_strLine(_T("")) {}
};

struct TEXT_RESULT_SEARCH_REPLACE_DATA
{
	std::vector<SEARCH_DATA_LINE> _vecSearchDataLine;
	unsigned int _nMatchedFiles;
	unsigned int _nMatchedLines;
	unsigned int _nMatchedWords;
	unsigned int _nLineCounts;
	unsigned int _nTotalSearchFile;
	unsigned int _nSearchOptions;
	double		 _TimeMeasured;
	CString _strSearchWhat;
	CString _strReplaceWith;
	CString _strScope;
	BOOL _bAppendResult;
	BOOL _bShowFileNameOnly;
	BOOL _bIsReplaceData;

	TEXT_RESULT_SEARCH_REPLACE_DATA():
		_nMatchedFiles(0),
		_nMatchedWords(0),
		_nMatchedLines(0),
		_nLineCounts(0),
		_nTotalSearchFile(0),
		_nSearchOptions(0),
		_TimeMeasured(0.0),
		_bAppendResult(FALSE),
		_bShowFileNameOnly(FALSE),
		_bIsReplaceData(FALSE) {}

	void Reset()
	{
		_vecSearchDataLine.clear();
		std::vector<SEARCH_DATA_LINE>().swap(_vecSearchDataLine);
		_strSearchWhat.Empty();
		_strScope.Empty();
		_strReplaceWith.Empty();
		_nMatchedFiles = 0;
		_nMatchedWords = 0;
		_nMatchedLines = 0;
		_nLineCounts = 0;
		_nTotalSearchFile = 0;
		_TimeMeasured = 0.0;
		_bAppendResult = FALSE;
		_bShowFileNameOnly = FALSE;
		_bIsReplaceData = FALSE;
	}
};

///////////////////////////////////////////////////
// DIY search engine, not perfect but can work :D

namespace VinaTextSearchEngine
{
	// Definitions

	enum  OPTIONS
	{
		INT_SEARCH_OPTION = 0x0,
		MATCH_CASE = 0x4,
		MATCH_WORD = 0x2,
		REGEX = 0x00200000,
	};

	template<typename charT>
	struct st_equal_insensitive
	{
		st_equal_insensitive(const std::locale& loc) : loc_(loc) {}
		bool operator()(charT ch1, charT ch2)
		{
			return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
		}
	private:
		const std::locale& loc_;
	};

	template<typename charT>
	struct st_equal_sensitive
	{
		st_equal_sensitive(const std::locale& loc) : loc_(loc) {}
		bool operator()(charT ch1, charT ch2)
		{
			return ch1 == ch2;
		}
	private:
		const std::locale& loc_;
	};

	template<typename CharT> bool replace_helper(std::basic_string<CharT>& text, const std::basic_string<CharT>& from, const std::basic_string<CharT>& to);

	template<typename CharT> size_t find_substr_case_insensitive(const CharT& text, const CharT& findWhat, const std::locale& loc = std::locale());

	template<typename CharT> size_t find_substr_case_sensitive(const CharT& text, const CharT& findWhat, const std::locale& loc = std::locale());

	template<typename CharT> BOOL find_word_regex(const CharT* text, const CharT* findWhat);

	template<typename CharT> BOOL find_word_insensitive_regex(const CharT* text, const CharT* findWhat);

	template<typename CharT> BOOL find_match_word_sensitive_regex(const CharT* text, const CharT* findWhat);

	template<typename CharT> BOOL find_match_word_insensitive_regex(const CharT* text, const CharT* findWhat);

	template<typename CharT> std::basic_string<CharT> replace_word_regex(const CharT* text, const CharT* regex, const CharT* replaceWhat);

	template<typename CharT> std::basic_string<CharT> replace_word_insensitive_regex(const CharT* text, const CharT* findWhat, const CharT* replaceWhat);

	template<typename CharT> std::basic_string<CharT> replace_match_word_sensitive_regex(const CharT* text, const CharT* findWhat, const CharT* replaceWhat);

	template<typename CharT> std::basic_string<CharT> replace_match_word_insensitive_regex(const CharT* text, const CharT* findWhat, const CharT* replaceWhat);

	template<typename CharT> std::size_t count_word(const CharT* text, const CharT* countWhat);

	template<typename CharT> std::size_t count_word_insensitive_regex(const CharT* text, const CharT* countWhat);

	template<typename CharT> std::basic_string<CharT> REPLACE_WORD(const CharT* text, const CharT* findWhat, const CharT* replaceWhat, unsigned int nOptions);

	template<typename CharT> BOOL SEARCH_WORD(const CharT* text, const CharT* findWhat, unsigned int nOptions);

	template<typename CharT> std::size_t COUNT_WORD(const CharT* text, const CharT* countWhat, unsigned int nOptions);

	// Implementation

	////////////////////////////// HELPERS /////////////////////////////////

	template<typename CharT>
	bool replace_helper(std::basic_string<CharT>& text, const std::basic_string<CharT>& from, const std::basic_string<CharT>& to)
	{
		size_t start_pos = text.find(from);
		if (start_pos == std::basic_string<CharT>::npos)
		{
			return false;
		}
		text.replace(start_pos, from.length(), to);
		return true;
	}

	inline std::wstring escapse_regex_string(const wchar_t* text) // overload for std::wstring...
	{
		std::wstring textTarget(text);
		std::wregex specialChars { LR"([.^$|()\[\]{}*+?\\])" };
		std::wstring escapsed = std::regex_replace(textTarget, specialChars, LR"(\$&)");
		return escapsed;
	}

	inline std::string escapse_regex_string(const char* text) // overload for std::string...
	{
		std::string textTarget(text);
		std::regex specialChars { R"([.^$|()\[\]{}*+?\\])" };
		std::string escapsed = std::regex_replace(textTarget, specialChars, R"(\$&)");
		return escapsed;
	}

	////////////////////////////// FIND /////////////////////////////////

	template<typename CharT>
	size_t find_substr_case_insensitive(const CharT& text, const CharT& findWhat, const std::locale& loc)
	{
		typename CharT::const_iterator it = std::search(text.begin(), text.end(),
			findWhat.begin(), findWhat.end(), st_equal_insensitive<typename CharT::value_type>(loc));
		if (it != text.end())
		{
			return it - text.begin();
		}
		else return -1;
	}

	template<typename CharT>
	size_t find_substr_case_sensitive(const CharT& text, const CharT& findWhat, const std::locale& loc)
	{
		typename CharT::const_iterator it = std::search(text.begin(), text.end(),
			findWhat.begin(), findWhat.end(), my_equal_sensitive<typename CharT::value_type>(loc));
		if (it != text.end())
		{
			return it - text.begin();
		}
		else return -1;
	}

	template<typename CharT>
	BOOL find_word_regex(const CharT* text, const CharT* findWhat)
	{
		std::basic_string<CharT> textTarget(text);
		std::basic_regex<CharT> reg(findWhat);
		if (std::regex_search(textTarget, reg))
		{
			return TRUE;
		}
		return FALSE;
	}

	template<typename CharT>
	BOOL find_word_insensitive_regex(const CharT* text, const CharT* findWhat)
	{
		std::basic_string<CharT> textTarget(text);
		std::basic_regex<CharT> reg(findWhat, std::regex::icase);
		if (std::regex_search(textTarget, reg))
		{
			return TRUE;
		}
		return FALSE;
	}

	template<typename CharT>
	BOOL find_match_word_sensitive_regex(const CharT* text, const CharT* findWhat)
	{
		std::basic_string<CharT> textTarget(text);
		std::basic_string<CharT> find(findWhat);
		std::basic_regex<CharT> reg(L"\\b" + find + L"\\b");
		if (std::regex_search(textTarget, reg))
		{
			return TRUE;
		}
		return FALSE;
	}

	template<typename CharT>
	BOOL find_match_word_insensitive_regex(const CharT* text, const CharT* findWhat)
	{
		std::basic_string<CharT> textTarget(text);
		std::basic_string<CharT> find(findWhat);
		std::basic_regex<CharT> reg(L"\\b" + find + L"\\b", std::regex::icase);
		if (std::regex_search(textTarget, reg))
		{
			return TRUE;
		}
		return FALSE;
	}

	////////////////////////////// REPLACE /////////////////////////////////

	template<typename CharT>
	std::basic_string<CharT> replace_word_regex(const CharT* text, const CharT* regex, const CharT* replaceWhat)
	{
		std::basic_string<CharT> textTarget(text);
		std::basic_regex<CharT> reg(regex);
		std::basic_string<CharT> replaceTarget(replaceWhat);
		return std::regex_replace(textTarget, reg, replaceTarget);
	}

	template<typename CharT>
	std::basic_string<CharT> replace_word_insensitive_regex(const CharT* text, const CharT* findWhat, const CharT* replaceWhat)
	{
		std::basic_string<CharT> textTarget(text);
		std::basic_string<CharT> replaceTarget(replaceWhat);
		std::basic_regex<CharT> reg(findWhat, std::regex::icase);
		return std::regex_replace(textTarget, reg, replaceTarget);
	}

	template<typename CharT>
	std::basic_string<CharT> replace_match_word_sensitive_regex(const CharT* text, const CharT* findWhat, const CharT* replaceWhat)
	{
		std::basic_string<CharT> textTarget(text);
		std::basic_string<CharT> find(findWhat);
		std::basic_string<CharT> replaceTarget(replaceWhat);
		std::basic_regex<CharT> reg(L"\\b" + find + L"\\b");
		return std::regex_replace(textTarget, reg, replaceTarget);
	}

	template<typename CharT>
	std::basic_string<CharT> replace_match_word_insensitive_regex(const CharT* text, const CharT* findWhat, const CharT* replaceWhat)
	{
		std::basic_string<CharT> textTarget(text);
		std::basic_string<CharT> find(findWhat);
		std::basic_string<CharT> replaceTarget(replaceWhat);
		std::basic_regex<CharT> reg(L"\\b" + find + L"\\b", std::regex::icase);
		return std::regex_replace(textTarget, reg, replaceTarget);
	}

	////////////////////////////// COUNT /////////////////////////////////

	template<typename CharT>
	std::size_t count_word(const CharT* text, const CharT* countWhat)
	{
		std::basic_string<CharT> textTarget(text);
		std::basic_regex<CharT> reg(countWhat);
		typedef typename std::basic_string<CharT>::iterator iter_t;
		return std::distance(std::regex_iterator<iter_t>(textTarget.begin(), textTarget.end(), reg),
			std::regex_iterator<iter_t>());
	}

	template<typename CharT>
	std::size_t count_word_insensitive_regex(const CharT* text, const CharT* countWhat)
	{
		std::basic_string<CharT> textTarget(text);
		std::basic_string<CharT> count(countWhat);
		std::basic_regex<CharT> reg(count, std::basic_regex<CharT>::icase);
		typedef typename std::basic_string<CharT>::iterator iter_t;
		return std::distance(std::regex_iterator<iter_t>(textTarget.begin(), textTarget.end(), reg),
			std::regex_iterator<iter_t>());
	}

	inline std::size_t count_match_word_sensitive_regex(const wchar_t* text, const wchar_t* countWhat)
	{
		std::wstring textTarget(text);
		std::wstring count(countWhat);
		std::wregex reg(L"\\b" + count + L"\\b"); 
		typedef typename std::wstring::iterator iter_t;
		return std::distance(std::regex_iterator<iter_t>(textTarget.begin(), textTarget.end(), reg),
			std::regex_iterator<iter_t>());
	}

	inline std::size_t count_match_word_sensitive_regex(const char* text, const char* countWhat)
	{
		std::string textTarget(text);
		std::string count(countWhat);
		std::regex reg("\\b" + count + "\\b");
		typedef typename std::string::iterator iter_t;
		return std::distance(std::regex_iterator<iter_t>(textTarget.begin(), textTarget.end(), reg),
			std::regex_iterator<iter_t>());
	}

	inline std::size_t count_match_word_insensitive_regex(const wchar_t* text, const wchar_t* countWhat)
	{
		std::wstring textTarget(text);
		std::wstring count(countWhat);
		std::wregex reg(L"\\b" + count + L"\\b", std::wregex::icase);
		typedef typename std::wstring::iterator iter_t;
		return std::distance(std::regex_iterator<iter_t>(textTarget.begin(), textTarget.end(), reg),
			std::regex_iterator<iter_t>());
	}

	inline std::size_t count_match_word_insensitive_regex(const char* text, const char* countWhat)
	{
		std::string textTarget(text);
		std::string count(countWhat);
		std::regex reg("\\b" + count + "\\b", std::regex::icase);
		typedef typename std::string::iterator iter_t;
		return std::distance(std::regex_iterator<iter_t>(textTarget.begin(), textTarget.end(), reg),
			std::regex_iterator<iter_t>());
	}

	////////////////////////////// APIs /////////////////////////////////

	template<typename CharT>
	std::basic_string<CharT> REPLACE_WORD(const CharT* text, const CharT* findWhat, const CharT* replaceWhat, unsigned int nOptions)
	{
		try
		{
			if (nOptions & REGEX)
			{
				if (!(nOptions & MATCH_CASE) && !(nOptions & MATCH_WORD))
				{
					return replace_word_insensitive_regex(text, findWhat, replaceWhat);
				}
				else if ((nOptions & MATCH_WORD) && (nOptions & MATCH_CASE))
				{
					return replace_match_word_sensitive_regex(text, findWhat, replaceWhat);
				}
				else if ((nOptions & MATCH_WORD) && !(nOptions & MATCH_CASE))
				{
					return replace_match_word_insensitive_regex(text, findWhat, replaceWhat);
				}
				return replace_word_regex(text, findWhat, replaceWhat);
			}
			else
			{
				if (!(nOptions & MATCH_CASE) && !(nOptions & MATCH_WORD))
				{
					return replace_word_insensitive_regex(text, escapse_regex_string(findWhat).c_str(), replaceWhat);
				}
				else if ((nOptions & MATCH_WORD) && (nOptions & MATCH_CASE))
				{
					return replace_match_word_sensitive_regex(text, escapse_regex_string(findWhat).c_str(), replaceWhat);
				}
				else if ((nOptions & MATCH_WORD) && !(nOptions & MATCH_CASE))
				{
					return replace_match_word_insensitive_regex(text, escapse_regex_string(findWhat).c_str(), replaceWhat);
				}
				return replace_word_regex(text, escapse_regex_string(findWhat).c_str(), replaceWhat);
			}
		}
		catch (std::regex_error e)
		{
			//LOG_OUTPUT_MESSAGE_ACTIVE_PANE((LPCTSTR)e.what());
			return 0;
		}
	}

	template<typename CharT>
	BOOL SEARCH_WORD(const CharT* text, const CharT* findWhat, unsigned int nOptions)
	{
		try
		{
			if (nOptions & REGEX)
			{
				if (!(nOptions & MATCH_CASE) && !(nOptions & MATCH_WORD))
				{
					return find_word_insensitive_regex(text, findWhat);
				}
				else if ((nOptions & MATCH_WORD) && (nOptions & MATCH_CASE))
				{
					return find_match_word_sensitive_regex(text, findWhat);
				}
				else if ((nOptions & MATCH_WORD) && !(nOptions & MATCH_CASE))
				{
					return find_match_word_insensitive_regex(text, escapse_regex_string(findWhat).c_str());
				}
				return find_word_regex(text, findWhat);
			}
			else
			{
				if (!(nOptions & MATCH_CASE) && !(nOptions & MATCH_WORD))
				{
					return find_word_insensitive_regex(text, escapse_regex_string(findWhat).c_str());
				}
				else if ((nOptions & MATCH_WORD) && (nOptions & MATCH_CASE))
				{
					return find_match_word_sensitive_regex(text, escapse_regex_string(findWhat).c_str());
				}
				else if ((nOptions & MATCH_WORD) && !(nOptions & MATCH_CASE))
				{
					return find_match_word_insensitive_regex(text, escapse_regex_string(findWhat).c_str());
				}
				return find_word_regex(text, escapse_regex_string(findWhat).c_str());
			}
		}
		catch (std::regex_error e)
		{
			//LOG_OUTPUT_MESSAGE_ACTIVE_PANE((LPCTSTR)e.what());
			return 0;
		}
	}

	template<typename CharT>
	std::size_t COUNT_WORD(const CharT* text, const CharT* countWhat, unsigned int nOptions)
	{
		try 
		{
			if (nOptions & REGEX)
			{
				if (!(nOptions & MATCH_CASE) && !(nOptions & MATCH_WORD) && !(nOptions & REGEX))
				{
					return count_word_insensitive_regex(text, countWhat);
				}
				else if ((nOptions & MATCH_WORD) && (nOptions & MATCH_CASE) && !(nOptions & REGEX))
				{
					return count_match_word_sensitive_regex(text, countWhat);
				}
				else if ((nOptions & MATCH_WORD) && !(nOptions & MATCH_CASE) && !(nOptions & REGEX))
				{
					return count_match_word_insensitive_regex(text, countWhat);
				}
				return count_word(text, countWhat);
			}
			else
			{
				if (!(nOptions & MATCH_CASE) && !(nOptions & MATCH_WORD))
				{
					return count_word_insensitive_regex(text, escapse_regex_string(countWhat).c_str());
				}
				else if ((nOptions & MATCH_WORD) && (nOptions & MATCH_CASE))
				{
					return count_match_word_sensitive_regex(text, escapse_regex_string(countWhat).c_str());
				}
				else if ((nOptions & MATCH_WORD) && !(nOptions & MATCH_CASE))
				{
					return count_match_word_insensitive_regex(text, escapse_regex_string(countWhat).c_str());
				}
				return count_word(text, escapse_regex_string(countWhat).c_str());
			}
		}
		catch (std::regex_error e) 
		{
			//LOG_OUTPUT_MESSAGE_ACTIVE_PANE((LPCTSTR)e.what());
			return 0;
		}
	}
}

#endif // _SEARCH_ENGINE_H_