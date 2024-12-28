#pragma once

#include <vector>

class CUserCustomizeData final
{
public:
	void LoadSyntaxHighlightUserData();
	const std::vector<CString>& GetSyntaxHighlightUserData() const;
private:
	std::vector<CString> m_syntaxHighlightUserData;
};
