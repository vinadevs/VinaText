/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "curl/curl.h"
#include <errno.h>

#include <iostream>
#include <string>

class CWebHandler
{
public:
	CWebHandler() = default;
	~CWebHandler() = default;

	std::wstring ResultParser(const std::wstring& strResult);
	std::wstring GetResultFromUrl(const std::string& strURL, const std::string& strReferer);
	static std::string EncodeStringForCurl(const std::string & str);

	// build what you need for
	std::string GetGoogleTranslateUrl(const std::string& strFromLang, const std::string &strTranlateToLang);

private:
	// That Curl thing needs to be static because C can't take C++ functions by reference
	static size_t CurlWriteCallBack(void* vptr_TransmittedData, size_t DataTypeSize, size_t nMemBufferElements, void* vptr_OutputStream);
};