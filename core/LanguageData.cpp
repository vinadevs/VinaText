/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "LanguageData.h"

#include "json/picojson.h"

#include <cstdio>
#include <fstream>
#include <sstream>

namespace Core
{
	namespace
	{
		// picojson stores every number as double; guard the narrowing explicitly so a
		// malformed file fails loudly instead of silently truncating to 0.
		bool ReadInt(const picojson::object& obj, const std::string& strKey, int& result)
		{
			const picojson::object::const_iterator it = obj.find(strKey);
			if (it == obj.end() || !it->second.is<double>())
			{
				return false;
			}
			result = static_cast<int>(it->second.get<double>());
			return true;
		}

		std::string ReadString(const picojson::object& obj, const std::string& strKey)
		{
			const picojson::object::const_iterator it = obj.find(strKey);
			if (it == obj.end() || !it->second.is<std::string>())
			{
				return std::string();
			}
			return it->second.get<std::string>();
		}

		// "#RRGGBB" -> SColor. Returns false on anything else.
		bool ParseHexColor(const std::string& strHex, SColor& color)
		{
			if (strHex.size() != 7 || strHex[0] != '#')
			{
				return false;
			}
			unsigned int r = 0, g = 0, b = 0;
			if (std::sscanf(strHex.c_str() + 1, "%02x%02x%02x", &r, &g, &b) != 3)
			{
				return false;
			}
			color._Red = static_cast<int>(r);
			color._Green = static_cast<int>(g);
			color._Blue = static_cast<int>(b);
			return true;
		}

		bool ParseDocument(const std::string& strJson, picojson::value& value, std::string& strError)
		{
			const std::string strParseError = picojson::parse(value, strJson);
			if (!strParseError.empty())
			{
				strError = strParseError;
				return false;
			}
			if (!value.is<picojson::object>())
			{
				strError = "document root is not an object";
				return false;
			}
			return true;
		}
	}

	bool ReadFileToString(const std::string& strPath, std::string& strOut, std::string& strError)
	{
		std::ifstream file(strPath.c_str(), std::ios::binary);
		if (!file.is_open())
		{
			strError = "cannot open " + strPath;
			return false;
		}
		std::ostringstream buffer;
		buffer << file.rdbuf();
		strOut = buffer.str();
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	// CLanguageTable

	bool CLanguageTable::LoadFromFile(const std::string& strPath, std::string& strError)
	{
		std::string strJson;
		if (!ReadFileToString(strPath, strJson, strError))
		{
			return false;
		}
		return LoadFromString(strJson, strError);
	}

	bool CLanguageTable::LoadFromString(const std::string& strJson, std::string& strError)
	{
		picojson::value root;
		if (!ParseDocument(strJson, root, strError))
		{
			return false;
		}

		const picojson::object& obj = root.get<picojson::object>();
		const picojson::object::const_iterator itLanguages = obj.find("languages");
		if (itLanguages == obj.end() || !itLanguages->second.is<picojson::array>())
		{
			strError = "missing \"languages\" array";
			return false;
		}

		m_PlainTextLabel = ReadString(obj, "plainTextLabel");

		std::vector<SLanguageInfo> languages;
		const picojson::array& arr = itLanguages->second.get<picojson::array>();
		for (picojson::array::const_iterator it = arr.begin(); it != arr.end(); ++it)
		{
			if (!it->is<picojson::object>())
			{
				strError = "language entry is not an object";
				return false;
			}
			const picojson::object& entry = it->get<picojson::object>();

			SLanguageInfo info;
			info._Id = ReadString(entry, "id");
			if (info._Id.empty())
			{
				strError = "language entry with empty \"id\"";
				return false;
			}
			info._Name = ReadString(entry, "name");
			info._Extension = ReadString(entry, "extension");
			info._CommentLine = ReadString(entry, "commentLine");
			info._CommentStart = ReadString(entry, "commentStart");
			info._CommentEnd = ReadString(entry, "commentEnd");
			info._Keywords = ReadString(entry, "keywords");
			languages.push_back(info);
		}

		m_Languages.swap(languages);
		return true;
	}

	const SLanguageInfo* CLanguageTable::FindById(const std::string& strId) const
	{
		for (std::vector<SLanguageInfo>::const_iterator it = m_Languages.begin();
			it != m_Languages.end(); ++it)
		{
			if (it->_Id == strId)
			{
				return &(*it);
			}
		}
		return nullptr;
	}

	//////////////////////////////////////////////////////////////////////////
	// CEditorTheme

	bool CEditorTheme::LoadFromFile(const std::string& strPath, std::string& strError)
	{
		std::string strJson;
		if (!ReadFileToString(strPath, strJson, strError))
		{
			return false;
		}
		return LoadFromString(strJson, strError);
	}

	bool CEditorTheme::LoadFromString(const std::string& strJson, std::string& strError)
	{
		picojson::value root;
		if (!ParseDocument(strJson, root, strError))
		{
			return false;
		}
		const picojson::object& obj = root.get<picojson::object>();

		m_Name = ReadString(obj, "name");

		std::map<std::string, SColor> palette;
		const picojson::object::const_iterator itPalette = obj.find("palette");
		if (itPalette == obj.end() || !itPalette->second.is<picojson::object>())
		{
			strError = "missing \"palette\" object";
			return false;
		}
		const picojson::object& paletteObj = itPalette->second.get<picojson::object>();
		for (picojson::object::const_iterator it = paletteObj.begin(); it != paletteObj.end(); ++it)
		{
			SColor color;
			if (!it->second.is<std::string>() || !ParseHexColor(it->second.get<std::string>(), color))
			{
				strError = "palette entry \"" + it->first + "\" is not a #RRGGBB string";
				return false;
			}
			palette[it->first] = color;
		}

		std::map<std::string, std::vector<SStyleMapping> > styles;
		const picojson::object::const_iterator itLanguages = obj.find("languages");
		if (itLanguages == obj.end() || !itLanguages->second.is<picojson::object>())
		{
			strError = "missing \"languages\" object";
			return false;
		}
		const picojson::object& languagesObj = itLanguages->second.get<picojson::object>();
		for (picojson::object::const_iterator it = languagesObj.begin(); it != languagesObj.end(); ++it)
		{
			if (!it->second.is<picojson::array>())
			{
				strError = "style table for \"" + it->first + "\" is not an array";
				return false;
			}
			std::vector<SStyleMapping> mappings;
			const picojson::array& arr = it->second.get<picojson::array>();
			for (picojson::array::const_iterator itEntry = arr.begin(); itEntry != arr.end(); ++itEntry)
			{
				if (!itEntry->is<picojson::object>())
				{
					strError = "style entry in \"" + it->first + "\" is not an object";
					return false;
				}
				const picojson::object& entry = itEntry->get<picojson::object>();

				SStyleMapping mapping;
				mapping._Style = ReadString(entry, "style");
				mapping._Color = ReadString(entry, "color");
				if (!ReadInt(entry, "value", mapping._Value))
				{
					strError = "style \"" + mapping._Style + "\" in \"" + it->first
						+ "\" has no numeric \"value\"";
					return false;
				}
				// A style may only reference a colour the palette actually defines,
				// otherwise the editor would silently paint it black.
				if (palette.find(mapping._Color) == palette.end())
				{
					strError = "style \"" + mapping._Style + "\" in \"" + it->first
						+ "\" references undefined colour \"" + mapping._Color + "\"";
					return false;
				}
				mappings.push_back(mapping);
			}
			styles[it->first] = mappings;
		}

		m_Palette.swap(palette);
		m_Styles.swap(styles);
		return true;
	}

	const std::vector<SStyleMapping>* CEditorTheme::FindStyles(const std::string& strLanguageId) const
	{
		const std::map<std::string, std::vector<SStyleMapping> >::const_iterator it
			= m_Styles.find(strLanguageId);
		return it == m_Styles.end() ? nullptr : &it->second;
	}

	bool CEditorTheme::ResolveColor(const std::string& strKey, SColor& color) const
	{
		const std::map<std::string, SColor>::const_iterator it = m_Palette.find(strKey);
		if (it == m_Palette.end())
		{
			return false;
		}
		color = it->second;
		return true;
	}
}
