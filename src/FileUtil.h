/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "EditorDataStructure.h"
#include "json\picojson.h"
#include "StringHelper.h"
#include "AppUtil.h"

//////////////////////////////////
// CSV

class CSVReader
{
public:
	CSVReader(const CString& csvPath);
	~CSVReader();
	bool ReadLine(CString& line);
	void SplitLine(CString& line, CStringArray& toks);
	BOOL OpenError();
	void Close();

protected:
	int CountDoubleQuot(CString& line);
	void SplitCString(const CString& strFields, const CString& strDelimiters, CStringArray& arFields);

private:
	CString m_csvPath;
	CStdioFile m_stdFile;
	BOOL m_ret;
	bool m_isOpened;
};

//////////////////////////////////
// JSON

namespace PICOJSON
{
	template <typename T> void AddValue(picojson::object& obj, const char* key, T value)
	{
		obj.insert(std::make_pair(key, picojson::value(value)));
	}

	template <typename T> void ReadValue(picojson::value& value, const char* key, T& result)
	{
		picojson::value pvalue = value.get(key); if (pvalue.is<T>())
		{
			result = pvalue.get<T>();
		}
	}

	inline void AddInteger(picojson::object& obj, const char* key, int inter)
	{
		std::ostringstream ostr;
		ostr << inter;
		obj.insert(std::make_pair(key, picojson::value(ostr.str())));
	}

	inline void ReadInteger(picojson::value& v, const char* key, int& inter)
	{
		picojson::value pvalue = v.get(key);
		if (pvalue.is<std::string>())
		{
			std::istringstream istr(pvalue.get<std::string>());
			istr >> inter;
		}
	}

	inline void ReadInteger(picojson::object& obj, const char* key, int& inter)
	{
		if (obj.find(key) != obj.end())
		{
			std::istringstream istr(obj[key].get<std::string>());
			istr >> inter;
		}
	}

	inline void AddBOOL(picojson::object& obj, const char* key, BOOL boolValue)
	{
		std::ostringstream ostr;
		ostr << boolValue;
		obj.insert(std::make_pair(key, picojson::value(ostr.str())));
	}

	inline void ReadBOOL(picojson::value& v, const char* key, BOOL& boolValue)
	{
		picojson::value pvalue = v.get(key);
		if (pvalue.is<std::string>())
		{
			std::istringstream istr(pvalue.get<std::string>());
			istr >> boolValue;
		}
	}

	template <typename T> void AddStdUnMap(picojson::object& parentObject, const char* key, const std::unordered_map<std::string, T>& valueMap)
	{
		picojson::object obj;
		for (auto itr = valueMap.begin(); itr != valueMap.end(); ++itr)
		{
			AddValue(obj, itr->first.c_str(), itr->second);
		}
		parentObject.insert(std::make_pair(key, obj));
	}

	template <typename T> void ReadStdUnMap(picojson::value& v, const char* key, std::unordered_map<std::string, T>& valueMap)
	{
		picojson::value value = v.get(key);
		if (value.is<picojson::object>())
		{
			picojson::object obj = value.get<picojson::object>();
			for (auto itr = obj.begin(); itr != obj.end(); ++itr)
			{
				valueMap[itr->first] = itr->second.get<T>();
			}
		}
	}
}

////////////////////////////////////////////////////////////////////
// JSON HELPERS, SUPPORT SINGLE ROOT ONLY
/*
{
	"ROOT NAME": 
	{
		"DATA1": "1",
		"DATA2": "2",
	}
}
*/

#define SAPERATOR_JSON_DATA _T("#$#$#$#$#$#$")

class JSonReader
{
public:
	// streams are not copyable
	JSonReader(const JSonReader&) = delete;
	JSonReader& operator=(const JSonReader&) = delete;

	JSonReader(const CString& strJsonFilePath, const std::string& strRootName);
	~JSonReader() = default;
	CString GetData(const std::string& strKey);

	template <typename T> void ReadValue(const std::string& strKey, T& value)
	{
		PICOJSON::ReadValue(m_JsonRootValue, strKey.c_str(), value);
	}

	void ReadCString(const std::string& strKey, CString& value);

	void ReadColor(const std::string& strKey, int& value);

	inline void ReadInteger(const std::string& strKey, int& value)
	{
		PICOJSON::ReadInteger(m_JsonRootValue, strKey.c_str(), value);
	}

	inline void ReadBOOL(const std::string& strKey, BOOL& boolValue)
	{
		PICOJSON::ReadBOOL(m_JsonRootValue, strKey.c_str(), boolValue);
	}

	template <typename T> void ReadStdUnMap(const std::string& strKey, std::unordered_map<std::string, T>& valueMap)
	{
		PICOJSON::ReadStdUnMap(m_JsonRootValue, strKey.c_str(), valueMap);
	}

	void ReadRecentEditorInfo(const std::string& strKey, std::unordered_map<std::string, RecentEditorInfo>& valueMap);

	void ReadStdStringVector(const std::string& strKey, std::vector<std::string>& valueVec);

	void ReadBookmarkDataList(const std::string& strKey, BOOKMARK_LINE_DATA_LIST& bookmarkList);

	BOOL LoadFile();

private:
	std::string m_strRootName;
	std::ifstream m_JsonFileStreamIn;
	picojson::value m_JsonRootValue;
};

class JSonWriter
{
public:
	// streams are not copyable
	JSonWriter(const JSonWriter&) = delete;
	JSonWriter& operator=(const JSonWriter&) = delete;

	JSonWriter(const CString& strJsonFilePath, const std::string& strRootName);
	~JSonWriter() = default;

	template <typename T> void AddValue(const std::string& strKey, T value)
	{
		PICOJSON::AddValue(m_JsonObject, strKey.c_str(), value);
	}

	inline void AddInteger(const std::string& strKey, int value)
	{
		PICOJSON::AddInteger(m_JsonObject, strKey.c_str(), value);
	}

	inline void AddBOOL(const std::string& strKey, BOOL boolValue)
	{
		PICOJSON::AddBOOL(m_JsonObject, strKey.c_str(), boolValue);
	}

	template <typename T> void AddStdUnMap(const std::string& strKey, const std::unordered_map<std::string, T>& valueMap)
	{
		PICOJSON::AddStdUnMap(m_JsonObject, strKey.c_str(), valueMap);
	}

	void AddRecentEditorInfo(const std::string& strKey, const std::unordered_map<std::string, RecentEditorInfo>& info);

	void AddStdStringVector(const std::string& strKey, const std::vector<std::string>& valueVec);

	void AddBookmarkDataList(const std::string& strKey, const BOOKMARK_LINE_DATA_LIST& bookmarkList);

	void SaveFile();

private:
	CString m_JsonFilePath;
	std::string m_strRootName;
	std::ofstream m_JsonFileStreamOut;
	picojson::object m_JsonObject;
};

//////////////////////////////////
// App Data File

class CAppDataFile
{
public:
	enum SERIALIZE_MODE
	{
		READ,
		WRITE,
	};
	// streams are not copyable
	CAppDataFile(const CAppDataFile&) = delete;
	CAppDataFile& operator=(const CAppDataFile&) = delete;

	CAppDataFile(const CString& strFilePath, const SERIALIZE_MODE& mode);
	~CAppDataFile();

	// reader/writer
	BOOL SerializeBookmarkDataIn(const BOOKMARK_LINE_DATA_LIST& list);
	BOOL SerializeBookmarkDataOut(BOOKMARK_LINE_DATA_LIST& list);

private:
	void CloseFile();

	void __fputws(const CString& strLine);
	FILE* m_pFile = NULL;
};

//////////////////////////////////
// XML 