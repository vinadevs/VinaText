/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

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
