/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

enum FILE_TEMPLATE_TYPE
{
	Template_Empty,
	Template_OnlyMain,
	Template_Function,
};

struct FILE_TEMPLATE_PARAM
{
	CString _strFileName;
	CString _strFileLocation;
	FILE_TEMPLATE_TYPE _templateType;
	VINATEXT_SUPPORTED_LANGUAGE _targetLanguage;
};

namespace TemplateCreator
{
	BOOL GenerateFile(FILE_TEMPLATE_PARAM param);
}
