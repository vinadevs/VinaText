/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "WebHandler.h"
#include "AppUtil.h"
#include "PathUtil.h"

#define	ERROR_RESULT_TRANSLATOR L"[Error] Can not get translated result from internet..."

//Language Name	Language Code
//Afrikaans	af
//Irish	ga
//Albanian	sq
//Italian	it
//Arabic	ar
//Japanese	ja
//Azerbaijani	az
//Kannada	kn
//Basque	eu
//Korean	ko
//Bengali	bn
//Latin	la
//Belarusian	be
//Latvian	lv
//Bulgarian	bg
//Lithuanian	lt
//Catalan	ca
//Macedonian	mk
//Chinese Simplified	zh - CN
//Malay	ms
//Chinese Traditional	zh - TW
//Maltese	mt
//Croatian	hr
//Norwegian	no
//Czech	cs
//Persian	fa
//Danish	da
//Polish	pl
//Dutch	nl
//Portuguese	pt
//English	en
//Romanian	ro
//Esperanto	eo
//Russian	ru
//Estonian	et
//Serbian	sr
//Filipino	tl
//Slovak	sk
//Finnish	fi
//Slovenian	sl
//French	fr
//Spanish	es
//Galician	gl
//Swahili	sw
//Georgian	ka
//Swedish	sv
//German	de
//Tamil	ta
//Greek	el
//Telugu	te
//Gujarati	gu
//Thai	th
//Haitian Creole	ht
//Turkish	tr
//Hebrew	iw
//Ukrainian	uk
//Hindi	hi
//Urdu	ur
//Hungarian	hu
//Vietnamese	vi
//Icelandic	is
//Welsh	cy
//Indonesian	id
//Yiddish	yi

std::string CWebHandler::GetGoogleTranslateUrl(const std::string & strFromLang, const std::string & strTranlateToLang)
{
	std::string strUrl = "https://translate.googleapis.com/translate_a/single?client=gtx&ie=UTF-8&oe=UTF-8&sl=" +
		strFromLang + "&tl=" + strTranlateToLang + "&dt=t&q=";
	return strUrl;
}

// Getting the data from Curl
size_t CWebHandler::CurlWriteCallBack(void* vptr_TransmittedData, size_t DataTypeSize, size_t nMemBufferElements, void* vptr_OutputStream)
{
	std::string* strOutputBuffer = reinterpret_cast<std::string*>(vptr_OutputStream);
	// Check for errors
	if (strOutputBuffer != NULL)
	{
		strOutputBuffer->append(reinterpret_cast<char*>(vptr_TransmittedData), DataTypeSize * nMemBufferElements);
	}
	return (DataTypeSize * nMemBufferElements);
}

// Encoded for url text
std::string CWebHandler::EncodeStringForCurl(const std::string & str)
{
	// Escapse special characters
	// https://curl.se/libcurl/c/curl_easy_escape.html
	CURL* curl = curl_easy_init();
	std::string strResult;
	if (curl)
	{
		char *output = curl_easy_escape(curl, str.c_str(), 0);
		if (output)
		{
			strResult = output;
			curl_free(output);
		}
	}
	return strResult;
}

std::wstring CWebHandler::ResultParser(const std::wstring& strResult)
{
	auto vecLines = AppUtils::SplitterWStdString(strResult, L"[\"");
	std::wstring strTranlatedText;
	for (auto line : vecLines)
	{
		if (line.find(L",null,null,") != -1 && line.find(L".md\"]]") == -1)
		{
			AppUtils::ReplaceAllInWStdString(line, L",null,null,3,null,null,[[]", L"");
			AppUtils::ReplaceAllInWStdString(line, L",null,null,1]", L"");
			size_t pos0 = line.find(L"\"");
			size_t pos1 = line.find(L"\",\"");
			if (pos1 != std::wstring::npos)
			{
				std::wstring strTranlatedLine = line.substr(pos0, pos1 - pos0);
				strTranlatedText += strTranlatedLine;
			}
		}
	}
	return strTranlatedText;
}

std::wstring CWebHandler::GetResultFromUrl(const std::string & strURL, const std::string & strReferer)
{
	// Init
	CURL* curl = curl_easy_init();
	if (curl)
	{
		// VinaText certificate
		CString strPathCRT = PathUtils::GetVinaTextPackagePath() +_T("VinaText.pem");
		std::string strOutputBuffer;

		// Initialize Curl settings
		char CurlBufferErrorReturn[CURL_ERROR_SIZE];
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, &CurlBufferErrorReturn);
		curl_easy_setopt(curl, CURLOPT_URL, strURL.c_str());
		curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
		curl_easy_setopt(curl, CURLOPT_CAINFO, AppUtils::CStringToStd(strPathCRT).c_str());
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &CurlWriteCallBack);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strOutputBuffer);

		// Optional
		curl_easy_setopt(curl, CURLOPT_REFERER, strReferer.c_str());
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-translator/0.1");
		// End optional

		CURLcode CURLc_ReturnValue = curl_easy_perform(curl);

		// Clean up
		curl_easy_cleanup(curl);

		if (CURLc_ReturnValue == CURLE_OK)
		{
			std::wstring strOutputBufferUTF8 = AppUtils::StdToWStd(strOutputBuffer);
			return strOutputBufferUTF8;
		}
		else
		{
			// Error while trying to access the webpage
			LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [HTTP Error] ") + CString(CurlBufferErrorReturn));
			return ERROR_RESULT_TRANSLATOR;
		}
	}
	else
	{
		// Error during Curl_init
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [HTTP Error] lib Curl load failed..."), BasicColors::orangered);
		return ERROR_RESULT_TRANSLATOR;
	}
}
