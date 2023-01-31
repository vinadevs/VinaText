/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "FileUtil.h"
#include "AppUtil.h"

#pragma warning (disable : 4244)

//////////////////////////////////
// CSV reader

CSVReader::CSVReader(const CString& csvPath)
	: m_csvPath(csvPath)
{
	m_ret = m_stdFile.Open(csvPath, CFile::modeRead | CFile::shareExclusive);
	if (m_ret != 0) 
	{
		m_isOpened = true;
	}
	else 
	{
		m_isOpened = false;
	}
}

CSVReader::~CSVReader()
{
	Close();
}

void CSVReader::Close()
{
	if (m_ret != 0 && m_isOpened) 
	{
		m_stdFile.Close();
		m_isOpened = false;
	}
}

BOOL CSVReader::OpenError()
{
	return m_ret == 0;
}

int CSVReader::CountDoubleQuot(CString& line)
{
	int count = 0;
	for (int i = 0; i < line.GetLength(); i++)
	{
		TCHAR ch = line[i];
		if (ch == '\"') count++;
	}
	return count;
}

bool CSVReader::ReadLine(CString& line)
{
	if (m_stdFile.ReadString(line) == FALSE) return false;

	if (line.Find(_T("\"")) == -1) return true;

	int cnt = CountDoubleQuot(line);
	if (cnt % 2 == 0)
	{
		return true;
	}
	while (true) 
	{
		CString line2;
		if (m_stdFile.ReadString(line2) == FALSE) break;
		cnt += CountDoubleQuot(line2);
		line += EDITOR_NEW_LINE + line2;
		if (cnt % 2 == 0) break;
	}

	return true;
}

void CSVReader::SplitCString(const CString& strFields, const CString& strDelimiters, CStringArray& toks)
{
	toks.RemoveAll();

	// Do not process empty strings.
	if (!strFields.IsEmpty() && !strDelimiters.IsEmpty())
	{
		int nPosition = 0, nTotalFields = 0;

		do
		{
			int nOldPosition = nPosition;   // Store the previous position value.

			CString strField = strFields.Tokenize(strDelimiters, nPosition);
			if (nPosition != -1)
			{
				nTotalFields += (nPosition - nOldPosition - strField.GetLength());
			}
			else
			{
				nTotalFields += (strFields.GetLength() + 1 - nOldPosition);
			}

			// By using SetAtGrow(), empty strings are automatically added to the array.
			toks.SetAtGrow(nTotalFields - 1, strField);
		} while (nPosition != -1 && nPosition <= strFields.GetLength());
	}
}

void CSVReader::SplitLine(CString& line, CStringArray& toks)
{
	if (!_tcsstr(line, _T("\""))) 
	{
		SplitCString(line, _T(","), toks);
	}
	else 
	{
		CStringArray toks2;
		SplitCString(line, _T(","), toks2);
		int size = toks2.GetSize();
		for (int i = 0; i < toks2.GetSize(); i++)
		{
			CString strField = toks2[i];
			if (strField.Left(1) == _T("\"") && strField.Right(1) == _T("\""))
			{
				toks.Add(strField);
			}
			else if (strField.Left(1) == _T("\"")) 
			{
				for (int j = 0; j < size; j++) 
				{
					i++;
					if (i >= toks2.GetSize()) break;
					CString strField2 = toks2[i];
					strField += _T(",") + strField2;
					if (strField2.Right(1) == _T("\""))
					{
						break;
					}
				}
				toks.Add(strField);
			}
			else 
			{
				toks.Add(strField);
			}
		}
	}
}

//////////////////////////////////
// JSON reader

JSonReader::JSonReader(const CString & strJsonFilePath, const std::string & strRootName)
	: m_JsonFileStreamIn(strJsonFilePath)
{
	if (m_JsonFileStreamIn.fail())
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Json Error] Can not load file %s..."), strJsonFilePath);
	}
	m_strRootName = strRootName;
}

CString JSonReader::GetData(const std::string & strKey)
{
	std::string strValue = m_JsonRootValue.get(strKey).get<std::string>();
	return AppUtils::StdToCString(strValue);
}

void JSonReader::ReadCString(const std::string & strKey, CString & value)
{
	std::string str;
	PICOJSON::ReadValue(m_JsonRootValue, strKey.c_str(), str);
	value = AppUtils::StdToCString(str);
}

void JSonReader::ReadColor(const std::string & strKey, int& value)
{
	std::string str;
	PICOJSON::ReadValue(m_JsonRootValue, strKey.c_str(), str);
	value = AppUtils::RGBCStringToColor(AppUtils::StdToCString(str));
}

void JSonReader::ReadRecentEditorInfo(const std::string & strKey, std::unordered_map<std::string, RecentEditorInfo>& valueMap)
{
	picojson::value value = m_JsonRootValue.get(strKey);
	if (value.is<picojson::object>())
	{
		picojson::object obj = value.get<picojson::object>();
		for (auto itr = obj.begin(); itr != obj.end(); ++itr)
		{
			PICOJSON::ReadInteger(itr->second, "FirstVisibleLine", valueMap[itr->first]._nFirstVisibleLine);
			PICOJSON::ReadInteger(itr->second, "CurrentPosition", valueMap[itr->first]._nCurrentPosition);
			PICOJSON::ReadInteger(itr->second, "WrapMode", valueMap[itr->first]._nWrapMode);
		}
	}
}

void JSonReader::ReadStdStringVector(const std::string & strKey, std::vector<std::string>& valueVec)
{
	std::string value;
	ReadValue(strKey, value);
	valueVec = AppUtils::SplitterStdString(value, " ");
}

void JSonReader::ReadBookmarkDataList(const std::string & strKey, BOOKMARK_LINE_DATA_LIST & bookmarkList)
{
	std::string value;
	ReadValue(strKey, value);
	std::vector<std::string> valueList = AppUtils::SplitterStdString(value, ";");
	bookmarkList.reserve(valueList.size());
	for (auto iter : valueList)
	{
		std::vector<std::string> elements = AppUtils::SplitterStdString(iter, ",");
		if (elements.size() == 3)
		{
			BOOKMARK_LINE_DATA data;
			data._strTargetFile = AppUtils::StdToCString(elements[0]);
			data._strLine = AppUtils::StdToCString(elements[1]);
			data._nLineNumber = std::stoi(elements[2]);
			bookmarkList.push_back(data);
		}
	}
}

BOOL JSonReader::LoadFile()
{
	std::string line, text;
	while (std::getline(m_JsonFileStreamIn, line))
	{
		text += line + "\n";
	}
	const char* jsonsoure = text.c_str();
	std::string error;
	picojson::value JsonValue;
	const char* json_end = picojson::parse(JsonValue, jsonsoure, jsonsoure + strlen(jsonsoure), &error);
	if (!error.empty())
	{
		AfxMessageBox(_T("[Parse Json Error] ") + AppUtils::StdToCString(error));
		return FALSE;
	}
	m_JsonRootValue = JsonValue.get(m_strRootName);
	if (!m_JsonRootValue.evaluate_as_boolean())
	{
		return FALSE;
	}
	return TRUE;
}

//////////////////////////////////
// JSON writer

JSonWriter::JSonWriter(const CString & strJsonFilePath, const std::string & strRootName)
	: m_JsonFileStreamOut(strJsonFilePath)
{
	if (m_JsonFileStreamOut.fail())
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Json Error] Can not load file %s..."), strJsonFilePath);
	}
	m_strRootName = strRootName;
}

void JSonWriter::AddRecentEditorInfo(const std::string & strKey, const std::unordered_map<std::string, RecentEditorInfo>& info)
{
	picojson::object obj1;
	for (auto itr = info.begin(); itr != info.end(); ++itr)
	{
		picojson::object obj2;
		PICOJSON::AddInteger(obj2, "FirstVisibleLine", itr->second._nFirstVisibleLine);
		PICOJSON::AddInteger(obj2, "CurrentPosition", itr->second._nCurrentPosition);
		PICOJSON::AddInteger(obj2, "WrapMode", itr->second._nWrapMode);
		obj1.insert(std::make_pair(itr->first.c_str(), obj2));
	}
	m_JsonObject.insert(std::make_pair(strKey, obj1));
}

void JSonWriter::AddStdStringVector(const std::string & strKey, const std::vector<std::string>& valueVec)
{
	std::string joinStr = StringHelper::JoinStdString<std::string>(" ", valueVec);
	AddValue(strKey, joinStr);
}

void JSonWriter::AddBookmarkDataList(const std::string & strKey, const BOOKMARK_LINE_DATA_LIST & bookmarkList)
{
	std::string strJoin;
	for (auto const& data : bookmarkList)
	{
		std::string strData = AppUtils::CStringToStd(data._strTargetFile) + "," +
			AppUtils::CStringToStd(data._strLine) + "," + std::to_string(data._nLineNumber);
		strJoin += strData + ";";
	}
	AddValue(strKey, strJoin);
}

void JSonWriter::SaveFile()
{
	picojson::object jsonValue;
	jsonValue[m_strRootName] = picojson::value(m_JsonObject);
	picojson::value json = picojson::value(jsonValue);
	m_JsonFileStreamOut << json.serialize(true);
	m_JsonFileStreamOut.close();
}

//////////////////////////////////
// App Data File

#define SAPERATOR_BLOCK_START _T("BEGIN---------------------------------------------------------")
#define SAPERATOR_BLOCK_END _T("-----------------------------------------------------------END")
#define SAPERATOR_HEADER _T("*********************************************************")

CAppDataFile::CAppDataFile(const CString & strFilePath, const SERIALIZE_MODE & mode)
{
	CString strMode;
	if (mode == SERIALIZE_MODE::READ)
		strMode = _T("rt");
	else if (mode == SERIALIZE_MODE::WRITE)
		strMode = _T("wt");
	errno_t err = _wfopen_s(&m_pFile, strFilePath, strMode);
	if (!err)
	{
		LOG_OUTPUT_MESSAGE_LAST_ERROR();
	}
}

CAppDataFile::~CAppDataFile()
{
	CloseFile();
}

void CAppDataFile::CloseFile()
{
	if (m_pFile)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}
}

BOOL CAppDataFile::SerializeBookmarkDataIn(const BOOKMARK_LINE_DATA_LIST & list)
{
	if (!m_pFile) return FALSE;
	fseek(m_pFile, 0, SEEK_SET);
	__fputws(SAPERATOR_HEADER);
	__fputws(_T("		VinaText Bookmark Line Data"));
	__fputws(SAPERATOR_HEADER);
	for (const auto& iter : list)
	{
		__fputws(SAPERATOR_BLOCK_START);
		__fputws(iter._strTargetFile);
		__fputws(AppUtils::IntToCString(iter._nLineNumber));
		__fputws(iter._strLine);
		__fputws(SAPERATOR_BLOCK_END);
	}
	CloseFile();
	return TRUE;
}

BOOL CAppDataFile::SerializeBookmarkDataOut(BOOKMARK_LINE_DATA_LIST & list)
{
	if (!m_pFile) return FALSE;
	CStdioFile stdFile(m_pFile);
	CString strLine;
	BOOL bStartReadBlockLine = FALSE;
	BOOL bStartMapping = FALSE;
	std::vector<CString> vecLines;
	while (stdFile.ReadString(strLine))
	{
		if (!strLine.IsEmpty() && strLine.Find(SAPERATOR_BLOCK_START) != -1)
		{
			bStartReadBlockLine = TRUE;
			vecLines.clear();
			continue;
		}
		if (!strLine.IsEmpty() && strLine.Find(SAPERATOR_BLOCK_END) != -1)
		{
			bStartMapping = TRUE;
			bStartReadBlockLine = FALSE;
		}
		if (bStartReadBlockLine)
		{
			vecLines.push_back(strLine);
		}
		if (bStartMapping)
		{
			if (vecLines.size() == 3)
			{
				BOOKMARK_LINE_DATA data;
				data._strTargetFile = vecLines[0];
				data._nLineNumber = AppUtils::CStringToInt(vecLines[1]);
				data._strLine = vecLines[2];
				list.push_back(data);
			}
			bStartMapping = FALSE;
		}
	}
	return TRUE;
}

void CAppDataFile::__fputws(const CString & strLine)
{
	fputws(strLine + _T("\n") , m_pFile);
}
