/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

//////////////////////////////////
// c++ 11 string buffer format

template<typename ... Args> std::string explorer_extra_string_format(const std::string& format, Args ... args)
{
	int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size_s <= 0) { throw std::runtime_error("Error during formatting string."); }
	auto size = static_cast<size_t>(size_s);
	auto buf = std::make_unique<char[]>(size);
	std::snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

//////////////////////////////////
// Multiple byte buffer allocator

template <class T> class CMultiByteBuffer final
{
public:
	~CMultiByteBuffer() { if (_allocLen) delete[] _str; }

	void sizeTo(size_t size)
	{
		if (_allocLen < size)
		{
			if (_allocLen)
				delete[] _str;
			_allocLen = max(size, initSize);
			_str = new T[_allocLen];
		}
	}

	void empty()
	{
		static T nullStr = 0;
		if (_allocLen == 0)
			_str = &nullStr;
		else
			_str[0] = 0;
	}

	operator T* () { return _str; }
	operator const T* () const { return _str; }

protected:
	static const int initSize = 1024;
	size_t _allocLen = 0;
	T* _str = NULL;
};

//////////////////////////////////
// C String Helper

namespace StringHelper
{
	int xisalnum(wint_t c);
	int xisspecial(wint_t c);
	int xisalpha(wint_t c);
	int xisalnum(wint_t c);
	int xisspace(wint_t c);
	bool IsMBSTrail(const TCHAR *pszChars, int nCol);
	bool isUrlSchemeStartChar(TCHAR const c);
	bool isUrlSchemeDelimiter(TCHAR const c);
	bool isUrlTextChar(TCHAR const c);
	bool isUrlQueryDelimiter(TCHAR const c);
	bool isUrlSchemeSupported(INTERNET_SCHEME s);
	bool scanToUrlStart(TCHAR * text, int textLen, int start, int * distance, int * schemeLength);
	void scanToUrlEnd(TCHAR * text, int textLen, int start, int * distance);
	bool removeUnwantedTrailingCharFromUrl(TCHAR const * text, int * length);
	// join string
	template <class T>
	T JoinStdString(const T & strDelimiters, const std::vector<T>& arFields)
	{
		return boost::algorithm::join(arFields, strDelimiters);
	}
}

//////////////////////////////////
// C++ STD String Helper

class STDStringHelper
{
public:
	// trim from both ends
	static inline std::string& trim(std::string& s)
	{
		return ltrim(rtrim(s));
	}
	static inline std::string& trim(std::string& s, const std::string& trimchars)
	{
		return ltrim(rtrim(s, trimchars), trimchars);
	}
	static inline std::string& trim(std::string& s, wint_t trimchar)
	{
		return ltrim(rtrim(s, trimchar), trimchar);
	}

	// trim from start
	static inline std::string& ltrim(std::string& s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](wint_t c) { return !iswspace(c); }));
		return s;
	}
	static inline std::string& ltrim(std::string& s, const std::string& trimchars)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [&trimchars](wint_t c) { return trimchars.find(static_cast<char>(c)) == std::string::npos; }));
		return s;
	}
	static inline std::string& ltrim(std::string& s, wint_t trimchar)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [&trimchar](wint_t c) { return c != trimchar; }));
		return s;
	}

	// trim from end
	static inline std::string& rtrim(std::string& s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), [](wint_t c) { return !iswspace(c); }).base(), s.end());
		return s;
	}
	static inline std::string& rtrim(std::string& s, const std::string& trimchars)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), [&trimchars](wint_t c) { return trimchars.find(static_cast<char>(c)) == std::string::npos; }).base(), s.end());
		return s;
	}
	static inline std::string& rtrim(std::string& s, wint_t trimchar)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), [&trimchar](wint_t c) { return c != trimchar; }).base(), s.end());
		return s;
	}

	// trim from both ends
	static inline std::wstring& trim(std::wstring& s)
	{
		return ltrim(rtrim(s));
	}
	static inline std::wstring& trim(std::wstring& s, const std::wstring& trimchars)
	{
		return ltrim(rtrim(s, trimchars), trimchars);
	}
	static inline std::wstring& trim(std::wstring& s, wint_t trimchar)
	{
		return ltrim(rtrim(s, trimchar), trimchar);
	}

	// trim from start
	static inline std::wstring& ltrim(std::wstring& s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](wint_t c) { return !iswspace(c); }));
		return s;
	}
	static inline std::wstring& ltrim(std::wstring& s, const std::wstring& trimchars)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [&trimchars](wint_t c) { return trimchars.find(c) == std::wstring::npos; }));
		return s;
	}
	static inline std::wstring& ltrim(std::wstring& s, wint_t trimchar)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [&trimchar](wint_t c) { return c != trimchar; }));
		return s;
	}

	// trim from end
	static inline std::wstring& rtrim(std::wstring& s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), [](wint_t c) { return !iswspace(c); }).base(), s.end());
		return s;
	}
	static inline std::wstring& rtrim(std::wstring& s, const std::wstring& trimchars)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), [&trimchars](wint_t c) { return trimchars.find(c) == std::wstring::npos; }).base(), s.end());
		return s;
	}
	static inline std::wstring& rtrim(std::wstring& s, wint_t trimchar)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), [&trimchar](wint_t c) { return c != trimchar; }).base(), s.end());
		return s;
	}

	static std::wstring ExpandEnvironmentStrings(const std::wstring& s)
	{
		DWORD len = ::ExpandEnvironmentStrings(s.c_str(), nullptr, 0);
		if (len == 0)
			return s;

		auto buf = std::make_unique<wchar_t[]>(len + 1ULL);
		if (::ExpandEnvironmentStrings(s.c_str(), buf.get(), len) == 0)
			return s;

		return buf.get();
	}

	static std::wstring Format(const wchar_t* frmt, ...);
	static std::string  Format(const char* frmt, ...);

	[[deprecated("use case insensitive string comparison instead, or the ci_less container helper")]] static inline void emplace_to_lower(std::wstring& s)
	{
		std::transform(s.begin(), s.end(), s.begin(), ::towlower);
	}

	[[deprecated("use case insensitive string comparison instead, or the ci_less container helper")]] static inline void emplace_to_lower(std::string& s)
	{
		std::transform(s.begin(), s.end(), s.begin(), [](char c) { return static_cast<char>(::tolower(c)); });
	}

	/// converts a string to lowercase
	/// note: please use only where absolutely necessary!
	/// better use stricmp functions if possible since for non ANSI strings there just are too many exceptions
	/// and special cases to handle.
	static inline std::wstring to_lower(const std::wstring& s)
	{
		auto len = LCMapStringEx(LOCALE_NAME_INVARIANT, LCMAP_LOWERCASE, s.c_str(), -1, nullptr, 0, nullptr, nullptr, 0);
		auto outBuf = std::make_unique<wchar_t[]>(len + 1LL);
		LCMapStringEx(LOCALE_NAME_INVARIANT, LCMAP_LOWERCASE, s.c_str(), -1, outBuf.get(), len, nullptr, nullptr, 0);
		return outBuf.get();
	}

	[[deprecated("use case insensitive string comparison instead, or the ci_less container helper")]] static inline std::string to_lower(const std::string& s)
	{
		std::string ls(s);
		std::transform(ls.begin(), ls.end(), ls.begin(), [](char c) { return static_cast<char>(::tolower(c)); });
		return ls;
	}

	static size_t find_caseinsensitive(const std::wstring& haystack, const std::wstring& needle)
	{
		auto ret = std::wstring::npos;
		for (size_t i = 0; i < haystack.size(); ++i)
		{
			if (_wcsnicmp(&haystack[i], needle.c_str(), needle.size()) == 0)
			{
				ret = i;
				break;
			}
		}
		return ret;
	}

	template <typename T, typename T2>
	static void TrimLeading(T& s, const T2& vals)
	{
		auto it = s.begin();
		while (it != s.end())
		{
			auto whereAt = std::find(vals.begin(), vals.end(), *it);
			if (whereAt == vals.end())
				break;
			++it;
			if (it == s.end())
				break;
		}
		s.erase(s.begin(), it);
	}

	template <typename T, typename T2>
	static void TrimTrailing(T& s, const T2& vals)
	{
		while (!s.empty())
		{
			auto whereAt = std::find(vals.begin(), vals.end(), s.back());
			if (whereAt == vals.end())
				break;
			s.pop_back();
		}
	}

	// Trim container T of values in T2.
	// T1 can at least be a string, wstring, vector,
	// T2 can be simiar but initializer_list is the typical type used.
	template <typename T, typename T2>
	static void TrimLeadingAndTrailing(T& s, const T2& vals)
	{
		TrimLeading(s, vals);
		TrimTrailing(s, vals);
	}
};

//////////////////////////////////
// Text alignment

typedef std::list<std::string> WordList;

class CTextAlignment
{
public:
	CTextAlignment() = default;
	~CTextAlignment() = default;

	enum class Alignment : unsigned int
	{
		Left = 0,
		Right,
		Center,
		Justify
	};

	CString AlignText(const CString & text, Alignment align);
private:
	WordList SplitTextIntoWords(const std::string & text);
};