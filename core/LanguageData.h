/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

// Loads the editor language and theme tables from Packages/data-packages/*.json.
//
// This is core/ code (see doc/QT-PORT-BRIEF.md D5): UI-free and portable, with no
// MFC, no Win32 and no Qt dependency. It links into the MFC frontend today and the
// Qt frontend later. Deliberately std::string rather than CString or QString - the
// payload is ASCII lexer configuration, so there is nothing to gain from UTF-16
// here, and staying on std::string keeps the header free of both toolkits.

#pragma once

#include <map>
#include <string>
#include <vector>

namespace Core
{
	// One entry of a theme's per-language style table: a Scintilla style constant
	// mapped to a named colour drawn from the theme palette.
	struct SStyleMapping
	{
		std::string	_Style;		// symbolic name, e.g. "SCE_P_COMMENTLINE"
		int			_Value = 0;	// resolved numeric value from SciLexer.h
		std::string	_Color;		// palette key, e.g. "comment"
	};

	struct SLanguageInfo
	{
		std::string	_Id;
		std::string	_Name;
		std::string	_Extension;
		std::string	_CommentLine;
		std::string	_CommentStart;
		std::string	_CommentEnd;
		std::string	_Keywords;
	};

	struct SColor
	{
		int _Red = 0;
		int _Green = 0;
		int _Blue = 0;
	};

	// Language metadata shared by every theme (Packages/data-packages/languages.json).
	class CLanguageTable final
	{
	public:
		bool LoadFromFile(const std::string& strPath, std::string& strError);
		bool LoadFromString(const std::string& strJson, std::string& strError);

		const std::vector<SLanguageInfo>& GetLanguages() const { return m_Languages; }
		// Returns nullptr when the language is unknown.
		const SLanguageInfo* FindById(const std::string& strId) const;
		const std::string& GetPlainTextLabel() const { return m_PlainTextLabel; }

	private:
		std::vector<SLanguageInfo>	m_Languages;
		std::string					m_PlainTextLabel;
	};

	// One theme: a named colour palette plus per-language style tables
	// (Packages/data-packages/theme-light.json, theme-dark.json).
	class CEditorTheme final
	{
	public:
		bool LoadFromFile(const std::string& strPath, std::string& strError);
		bool LoadFromString(const std::string& strJson, std::string& strError);

		const std::string& GetName() const { return m_Name; }
		const std::map<std::string, SColor>& GetPalette() const { return m_Palette; }

		// Returns nullptr when the theme has no table for that language.
		const std::vector<SStyleMapping>* FindStyles(const std::string& strLanguageId) const;
		// Resolves a palette key. Returns false when the key is not defined.
		bool ResolveColor(const std::string& strKey, SColor& color) const;

	private:
		std::string										m_Name;
		std::map<std::string, SColor>					m_Palette;
		std::map<std::string, std::vector<SStyleMapping>> m_Styles;
	};

	// Reads a whole file into memory. Returns false and sets strError on failure.
	bool ReadFileToString(const std::string& strPath, std::string& strOut, std::string& strError);
}
