/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "UserCustomizeData.h"
#include "PathUtil.h"

#include <fstream>
#include <string>

void CUserCustomizeData::LoadSyntaxHighlightUserData()
{
    std::ifstream file(PathUtils::GetSyntaxHighlightUserDataPath().GetString());
    if (!file.is_open())
    {
        return;
    }
    std::string line;
    while (std::getline(file, line))
    {
        CString cstrLine(line.c_str()); // Convert std::string to CString
        cstrLine.Trim(); // Remove leading/trailing whitespace
        // Ignore lines starting with "//"
        if (cstrLine.Left(2) == _T("//")) 
        {
            continue;
        }
        const int colonPos = cstrLine.Find(':');
        if (colonPos != -1) 
        {
            CString value = cstrLine.Mid(colonPos + 1); // Extract the substring after ':'
            value.Trim(); // Remove any leading/trailing whitespace
            m_syntaxHighlightUserData.emplace_back(value);
        }
    }
    m_syntaxHighlightUserData.emplace_back(_T("")); // empty CString to end while loop
    file.close(); // Close the file
}

const std::vector<CString>& CUserCustomizeData::GetSyntaxHighlightUserData() const
{
    return m_syntaxHighlightUserData;
}
