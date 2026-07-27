/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

// Verifies core/LanguageData against the real shipped data files.
//
// This runs on macOS/Linux/Windows with any C++11 compiler - no MFC, no Qt, no
// test framework. It exists because the MFC application cannot be built outside
// Windows, so this is the only executable check available on a developer machine
// until the CI matrix lands in Phase 0.
//
// Build and run:
//   c++ -std=c++11 -I include -I core core/LanguageData.cpp \
//       core/tests/TestLanguageData.cpp -o /tmp/testlangdata && /tmp/testlangdata

#include "LanguageData.h"

#include <cstdlib>
#include <iostream>
#include <string>

namespace
{
	int g_Failures = 0;
	int g_Checks = 0;

	void Check(bool bCondition, const std::string& strWhat)
	{
		++g_Checks;
		if (!bCondition)
		{
			++g_Failures;
			std::cout << "  FAIL: " << strWhat << "\n";
		}
	}

	template <typename T>
	void CheckEqual(const T& actual, const T& expected, const std::string& strWhat)
	{
		++g_Checks;
		if (!(actual == expected))
		{
			++g_Failures;
			std::cout << "  FAIL: " << strWhat << "\n"
				<< "        actual   = " << actual << "\n"
				<< "        expected = " << expected << "\n";
		}
	}
}

int main(int argc, char** argv)
{
	const std::string strDataDir = (argc > 1) ? argv[1] : "Packages/data-packages";
	std::string strError;

	//----------------------------------------------------------------------
	// languages.json
	//----------------------------------------------------------------------
	Core::CLanguageTable languages;
	if (!languages.LoadFromFile(strDataDir + "/languages.json", strError))
	{
		std::cout << "FATAL: " << strError << "\n";
		return 1;
	}

	CheckEqual<size_t>(languages.GetLanguages().size(), 42, "language count");
	CheckEqual<std::string>(languages.GetPlainTextLabel(), "plain text", "plain text label");

	const Core::SLanguageInfo* pPython = languages.FindById("python");
	Check(pPython != nullptr, "python is present");
	if (pPython != nullptr)
	{
		CheckEqual<std::string>(pPython->_Extension, "py", "python extension");
		CheckEqual<std::string>(pPython->_CommentLine, "#", "python comment line");
		Check(pPython->_CommentStart.empty(), "python has no block comment start");
		Check(pPython->_Keywords.find("lambda") != std::string::npos,
			"python keywords contain 'lambda'");
	}

	const Core::SLanguageInfo* pCpp = languages.FindById("cpp");
	Check(pCpp != nullptr, "cpp is present");
	if (pCpp != nullptr)
	{
		CheckEqual<std::string>(pCpp->_CommentLine, "//", "cpp comment line");
		CheckEqual<std::string>(pCpp->_CommentStart, "/*", "cpp comment start");
		CheckEqual<std::string>(pCpp->_CommentEnd, "*/", "cpp comment end");
	}

	Check(languages.FindById("no_such_language") == nullptr, "unknown language returns nullptr");

	// Known data quirks, asserted so they stay visible rather than becoming folklore.
	const Core::SLanguageInfo* pVcxproject = languages.FindById("vcxproject");
	Check(pVcxproject != nullptr && pVcxproject->_Keywords.empty(),
		"vcxproject has no keyword blob (matches the C++ table)");

	size_t nWithKeywords = 0;
	for (size_t i = 0; i < languages.GetLanguages().size(); ++i)
	{
		if (!languages.GetLanguages()[i]._Keywords.empty())
		{
			++nWithKeywords;
		}
	}
	CheckEqual<size_t>(nWithKeywords, 39, "languages carrying a non-empty keyword blob");

	//----------------------------------------------------------------------
	// theme-light.json / theme-dark.json
	//----------------------------------------------------------------------
	const char* aThemes[] = { "light", "dark" };
	for (int i = 0; i < 2; ++i)
	{
		const std::string strName = aThemes[i];
		Core::CEditorTheme theme;
		if (!theme.LoadFromFile(strDataDir + "/theme-" + strName + ".json", strError))
		{
			std::cout << "FATAL: " << strError << "\n";
			return 1;
		}

		CheckEqual<std::string>(theme.GetName(), strName, strName + ": name");
		CheckEqual<size_t>(theme.GetPalette().size(), 33, strName + ": palette size");

		// Pin a couple of concrete values. tools/extract_language_data.py --verify is
		// the authority on JSON-vs-C++ equivalence, but these catch a stray edit to the
		// data files without needing the C++ headers around.
		Core::SColor probe;
		Check(theme.ResolveColor("black", probe) && probe._Red == 0
			&& probe._Green == 0 && probe._Blue == 0, strName + ": black is #000000");
		if (strName == "light")
		{
			Check(theme.ResolveColor("comment", probe) && probe._Red == 10
				&& probe._Green == 103 && probe._Blue == 4, "light: comment is #0A6704");
		}
		else
		{
			Check(theme.ResolveColor("editorTextColor", probe) && probe._Red == 255
				&& probe._Green == 255 && probe._Blue == 255, "dark: text is #FFFFFF");
		}

		// python_2 has a style table but no language metadata - preserved deliberately.
		Check(theme.FindStyles("python_2") != nullptr,
			strName + ": python_2 style table is preserved");

		const std::vector<Core::SStyleMapping>* pStyles = theme.FindStyles("python");
		Check(pStyles != nullptr, strName + ": python style table");
		if (pStyles != nullptr && !pStyles->empty())
		{
			CheckEqual<std::string>((*pStyles)[0]._Style, "SCE_P_DEFAULT",
				strName + ": first python style symbol");
			CheckEqual<int>((*pStyles)[0]._Value, 0, strName + ": SCE_P_DEFAULT value");
		}

		// Every style in every language must resolve against the palette. The loader
		// already rejects a dangling reference, so reaching here means it held - but
		// assert it explicitly so the guarantee is tested, not merely assumed.
		size_t nStyles = 0;
		Core::SColor color;
		const char* aLangs[] = { "python", "cpp", "java", "rust", "python_2" };
		for (size_t l = 0; l < sizeof(aLangs) / sizeof(aLangs[0]); ++l)
		{
			const std::vector<Core::SStyleMapping>* p = theme.FindStyles(aLangs[l]);
			if (p == nullptr)
			{
				continue;
			}
			for (size_t s = 0; s < p->size(); ++s)
			{
				++nStyles;
				Check(theme.ResolveColor((*p)[s]._Color, color),
					strName + ": " + aLangs[l] + " style " + (*p)[s]._Style
					+ " resolves colour " + (*p)[s]._Color);
			}
		}
		Check(nStyles > 0, strName + ": sampled style mappings is non-empty");
	}

	//----------------------------------------------------------------------
	// malformed input must fail loudly, not silently
	//----------------------------------------------------------------------
	{
		Core::CEditorTheme bad;
		Check(!bad.LoadFromString("{ \"name\": \"x\" }", strError),
			"theme without a palette is rejected");

		Check(!bad.LoadFromString(
			"{\"name\":\"x\",\"palette\":{\"a\":\"#000000\"},"
			"\"languages\":{\"z\":[{\"style\":\"SCE_X\",\"value\":1,\"color\":\"missing\"}]}}",
			strError), "style referencing an undefined colour is rejected");

		Check(!bad.LoadFromString("{\"name\":\"x\",\"palette\":{\"a\":\"red\"},\"languages\":{}}",
			strError), "non-hex palette entry is rejected");

		Core::CLanguageTable badLang;
		Check(!badLang.LoadFromString("not json at all", strError), "garbage input is rejected");
		Check(!badLang.LoadFromString("{}", strError), "document without languages is rejected");
	}

	std::cout << "\n" << (g_Checks - g_Failures) << "/" << g_Checks << " checks passed\n";
	if (g_Failures != 0)
	{
		std::cout << g_Failures << " FAILED\n";
		return 1;
	}
	std::cout << "OK\n";
	return 0;
}
