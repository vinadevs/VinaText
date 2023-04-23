/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "AppUtil.h"
#include "PathUtil.h"
#include "OSUtil.h"
#include "VinaTextApp.h"
#include "MainFrm.h"
#include "EditorDoc.h"
#include "EditorView.h"
#include "ImageDoc.h"
#include "PdfDoc.h"
#include "MediaDoc.h"
#include "FileExplorerDoc.h"
#include "HostDoc.h"
#include "FileUtil.h"
#include "AppSettings.h"
#include "tinyXml\tinyxml.h"
#include "StringHelper.h"        
#include <imm.h>
#include "afxtaskdialog.h"

#pragma warning(disable:4996)

///////////////// EDITOR HELPERS //////////////////////////

static unsigned int g_uiCodePage = CP_THREAD_ACP;	

CString AppUtils::ColorToRGBCString(COLORREF color)
{
	CString strColor;
	strColor.Format(_T("RGB(%d,%d,%d)"), GetRValue(color), GetGValue(color), GetBValue(color));
	return strColor;
}

COLORREF AppUtils::RGBCStringToColor(const CString& strRGBColor)
{
	COLORREF color = RGB(255,255,255);
	int nPosBracketBegin = strRGBColor.Find(_T("("));
	int nPosBracketEnd = strRGBColor.ReverseFind(_T(')'));
	if (nPosBracketBegin != -1 && nPosBracketEnd != -1)
	{
		CString strRGBValue = strRGBColor.Mid(nPosBracketBegin + 1, nPosBracketEnd - nPosBracketBegin - 1);
		CStringArray listRGB;
		SplitCString(strRGBValue, _T(", "), listRGB);
		if (listRGB.GetSize() == 3)
		{
			int nRed = CStringToInt(listRGB[0].Trim());
			int nGreen = CStringToInt(listRGB[1].Trim());
			int nBlue = CStringToInt(listRGB[2].Trim());
			return COLORREF(RGB(nRed, nGreen, nBlue));
		}
	}
	return color;
}

CString AppUtils::IntToCString(int n)
{
	CString str;
	str.Format(_T("%d"), n);
	return(str);
}

CString AppUtils::FloatToCString(float f)
{
	CString str;
	str.Format(_T("%f"), f);
	return(str);
}

CString AppUtils::LongToCString(long l)
{
	CString str;
	str.Format(_T("%ld"), l);
	return(str);
}

int AppUtils::CStringToInt(CString str)
{
	return _ttoi(str);
}

long AppUtils::CStringToLong(CString str)
{
	return _ttol(str);
}

float AppUtils::CStringToFloat(CString str)
{
	return static_cast<float>(_ttof(str));
}

char* AppUtils::CopyCharArray(const char* orig)
{
	// IMPORTANT: CALLER NEED TO FREE MEMORY!!!
	char *res = new char[strlen(orig) + 1];
	strcpy(res, orig);
	return res;
}

std::string AppUtils::CStringToStd(CString cs)
{
	CT2CA pszConvertedAnsiString(cs);
	std::string strStd(pszConvertedAnsiString);
	return strStd;
}

CString AppUtils::StdToCString(std::string stdSt)
{
	CString cs(stdSt.c_str());
	return cs;
}

std::wstring AppUtils::CStringToWStd(CString cs)
{
	std::wstring wcs(cs);
	return wcs;
}

CString AppUtils::DecimalToRomanNumerals(int nDecimalNumber)
{
	std::string strRomanNumer;
	int num[] = { 1,4,5,9,10,40,50,90,100,400,500,900,1000 };
	std::string symbolRoman[] = { "I","IV","V","IX","X","XL","L","XC","C","CD","D","CM","M" };
	int i = 12;
	while (nDecimalNumber > 0)
	{
		int div = nDecimalNumber / num[i];
		nDecimalNumber = nDecimalNumber % num[i];
		while (div--)
		{
			strRomanNumer += symbolRoman[i];
		}
		i--;
	}
	return StdToCString(strRomanNumer);
}

CStringA AppUtils::UTF16_TO_UTF8(const CStringW& utf16)
{
	if (utf16.IsEmpty()) return "";
	CStringA utf8;
	int cc = 0;

	if ((cc = WideCharToMultiByte(CP_UTF8, 0, utf16, -1, NULL, 0, 0, 0) - 1) > 0)
	{
		char * buf = utf8.GetBuffer(cc);
		if (buf) WideCharToMultiByte(CP_UTF8, 0, utf16, -1, buf, cc, 0, 0);
		utf8.ReleaseBuffer();
	}
	return utf8;
}

std::string AppUtils::UTF8_TO_STD_STRING(const std::string& str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	memset(pwBuf, 0, nwLen * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), pwBuf, nwLen);
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);
	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	std::string strRet = pBuf;
	DELETE_POINTER_CPP(pBuf)
	DELETE_POINTER_CPP(pwBuf)
	return strRet;
}

BOOL AppUtils::IsUTF8String(const char* string)
{
	if (!string) return FALSE;
	const unsigned char * bytes = (const unsigned char *)string;
	while (*bytes)
	{
		if ((// ASCII
			 // use bytes[0] <= 0x7F to allow ASCII control characters
			bytes[0] == 0x09 ||
			bytes[0] == 0x0A ||
			bytes[0] == 0x0D ||
			(0x20 <= bytes[0] && bytes[0] <= 0x7E)
			)
			) {
			bytes += 1;
			continue;
		}

		if ((// non-overlong 2-byte
			(0xC2 <= bytes[0] && bytes[0] <= 0xDF) &&
			(0x80 <= bytes[1] && bytes[1] <= 0xBF)
			)
			) {
			bytes += 2;
			continue;
		}

		if ((// excluding overlongs
			bytes[0] == 0xE0 &&
			(0xA0 <= bytes[1] && bytes[1] <= 0xBF) &&
			(0x80 <= bytes[2] && bytes[2] <= 0xBF)
			) ||
			(// straight 3-byte
			((0xE1 <= bytes[0] && bytes[0] <= 0xEC) ||
				bytes[0] == 0xEE ||
				bytes[0] == 0xEF) &&
				(0x80 <= bytes[1] && bytes[1] <= 0xBF) &&
				(0x80 <= bytes[2] && bytes[2] <= 0xBF)
				) ||
				(// excluding surrogates
					bytes[0] == 0xED &&
					(0x80 <= bytes[1] && bytes[1] <= 0x9F) &&
					(0x80 <= bytes[2] && bytes[2] <= 0xBF)
					)
			) {
			bytes += 3;
			continue;
		}

		if ((// planes 1-3
			bytes[0] == 0xF0 &&
			(0x90 <= bytes[1] && bytes[1] <= 0xBF) &&
			(0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
			(0x80 <= bytes[3] && bytes[3] <= 0xBF)
			) ||
			(// planes 4-15
			(0xF1 <= bytes[0] && bytes[0] <= 0xF3) &&
				(0x80 <= bytes[1] && bytes[1] <= 0xBF) &&
				(0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
				(0x80 <= bytes[3] && bytes[3] <= 0xBF)
				) ||
				(// plane 16
					bytes[0] == 0xF4 &&
					(0x80 <= bytes[1] && bytes[1] <= 0x8F) &&
					(0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
					(0x80 <= bytes[3] && bytes[3] <= 0xBF)
					)
			) {
			bytes += 4;
			continue;
		}
		return FALSE;
	}
	return TRUE;
}

const char* AppUtils::WideCharToCharAsCodePage(const wchar_t * wcharStr2Convert, UINT codepage, int lenWc, int *pLenMbcs)
{
	if (NULL == wcharStr2Convert)
		return NULL;

	CMultiByteBuffer<char> multiByteStr;
	int lenMbcs = WideCharToMultiByte(codepage, 0, wcharStr2Convert, lenWc, NULL, 0, NULL, NULL);
	if (lenMbcs > 0)
	{
		multiByteStr.sizeTo(lenMbcs);
		WideCharToMultiByte(codepage, 0, wcharStr2Convert, lenWc, multiByteStr, lenMbcs, NULL, NULL);
	}
	else
		multiByteStr.empty();

	if (pLenMbcs)
		*pLenMbcs = lenMbcs;
	return multiByteStr;
}

CStringW AppUtils::UTF8_TO_UTF16(const CStringA& utf8)
{
	if (utf8.IsEmpty()) return L"";
	CStringW utf16;
	int cc = 0;

	if ((cc = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0) - 1) > 0)
	{
		wchar_t *buf = utf16.GetBuffer(cc);
		if (buf) MultiByteToWideChar(CP_UTF8, 0, utf8, -1, buf, cc);
		utf16.ReleaseBuffer();
	}
	return utf16;
}

int AppUtils::FindFirstCharacterNotOf(CString str, CString strDelim)
{
	if (str.IsEmpty()) return -1;
	const std::wstring delims = CStringToWStd(strDelim);
	std::wstring::size_type pos = CStringToWStd(str).find_first_not_of(delims);
	return int(pos);
}

BOOL AppUtils::StringIsDigits(const std::wstring &str)
{
	for (const auto& i : str)
	{
		if (!isdigit(static_cast<unsigned char>(i)))
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL AppUtils::StringIsInteger(const std::wstring &str)
{
	if (str.empty() || ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+'))) return FALSE;
	wchar_t * p;
	wcstol(str.c_str(), &p, 10);
	return (*p == 0);
};

BOOL AppUtils::StringIsFloat(const std::wstring & str) 
{
	if (StringIsInteger(str))
	{
		return FALSE;
	}
	try
	{
		std::stod(str);
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

CString	AppUtils::WStdToCString(const std::wstring& stdSt)
{
	CString cs(stdSt.c_str());
	return cs;
}

std::wstring AppUtils::StdToWStd(std::string stdSt)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wcs = converter.from_bytes(stdSt);
	return wcs;
}

std::string AppUtils::WStdToStd(std::wstring stdSt)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::string strStd = converter.to_bytes(stdSt);
	return strStd;
}

CString AppUtils::GetSubCStringBetweenTwoDemiliter(const CString & strTarget, const CString & strDelimitersStart, const CString & strDelimitersStop)
{
	int nStartPos = strTarget.Find(strDelimitersStart);
	int nStopPos = strTarget.Find(strDelimitersStop);
	return strTarget.Mid(nStartPos + 1, nStopPos - nStartPos - 1);
}

// https://www.codeproject.com/Tips/676464/How-to-Parse-Empty-Tokens-using-CString-Tokenize
void AppUtils::SplitCString(const CString & strFields, const CString & strDelimiters, CStringArray & arFields, BOOL bForceTrim)
{
	arFields.RemoveAll();
	if (!strFields.IsEmpty() && !strDelimiters.IsEmpty())
	{
		int nPosition = 0, nTotalFields = 0;
		do
		{
			int nOldPosition = nPosition;
			CString strField = strFields.Tokenize(strDelimiters, nPosition);
			if (nPosition != -1)
			{
				nTotalFields += (nPosition - nOldPosition - strField.GetLength());
			}
			else
			{
				nTotalFields += (strFields.GetLength() + 1 - nOldPosition);
			}
			if (bForceTrim)
			{
				if (!strField.Trim().IsEmpty())
					arFields.SetAtGrow(nTotalFields - 1, strField);
			}
			else 
				arFields.SetAtGrow(nTotalFields - 1, strField);
		} while (nPosition != -1 && nPosition <= strFields.GetLength());
	}
}

void AppUtils::SplitCString(const CString& strFields, const CString& strDelimiters, std::list<CString>& arFields, BOOL bForceTrim)
{
	arFields.clear();
	if (!strFields.IsEmpty() && !strDelimiters.IsEmpty())
	{
		int nPosition = 0, nTotalFields = 0;
		do
		{
			int nOldPosition = nPosition;
			CString strField = strFields.Tokenize(strDelimiters, nPosition);
			if (nPosition != -1)
			{
				nTotalFields += (nPosition - nOldPosition - strField.GetLength());
			}
			else
			{
				nTotalFields += (strFields.GetLength() + 1 - nOldPosition);
			}
			if (bForceTrim)
			{
				if (!strField.Trim().IsEmpty())
					arFields.push_back(strField);
			}
			else
				arFields.push_back(strField);
		} while (nPosition != -1 && nPosition <= strFields.GetLength());
	}
}

void AppUtils::SplitCString(const CString& strFields, const CString& strDelimiters, std::vector<CString>& arFields)
{
	// Start at the beginning
	int lastPos = 0;
	// Find position of the first delimiter
	int pos = strFields.Find(strDelimiters, lastPos);
	// While we still have string to read
	while (std::wstring::npos != pos && std::wstring::npos != lastPos)
	{
		// Found a token, add it to the vector
		arFields.push_back(strFields.Mid(lastPos, pos - lastPos));
		// Look at the next token instead of skipping delimiters
		lastPos = pos + 1;
		// Find the position of the next delimiter
		pos = strFields.Find(strDelimiters, lastPos);
	}
	// Push the last token
	arFields.push_back(strFields.Mid(lastPos, pos - lastPos));
}

std::wstring AppUtils::GetUnicodeWString(const std::string& multibyte, bool stopAtNull)
{
	int len = static_cast<int>(multibyte.size());
	if (len == 0) return std::wstring();
	int  size = len * 4;
	auto wide = std::make_unique<wchar_t[]>(size);
	int  ret = MultiByteToWideChar(CP_UTF8, 0, multibyte.c_str(), len, wide.get(), size - 1);
	wide[ret] = 0;
	if (stopAtNull) return std::wstring(wide.get());
	return std::wstring(wide.get(), ret);
}


void AppUtils::SetCurrentCodePage(unsigned int uiCodePage)
{
	g_uiCodePage = uiCodePage;
}

unsigned int AppUtils::GetCurrentCodePage()
{
	return g_uiCodePage;
}

CString AppUtils::ArrayCharToCString(const char* szText)
{
	return CString(CA2CTEX<_MAX_PATH>(szText, g_uiCodePage));
}

CVinaTextApp * AppUtils::GetVinaTextApp()
{
	CVinaTextApp* pApp = ((CVinaTextApp*)AfxGetApp());
#pragma warning(suppress: 26496)
	AFXASSUME(pApp != NULL);
	return pApp;
}

CMainFrame* AppUtils::GetMainFrame()
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return NULL;
	return pFrame;
}

std::vector<CString> AppUtils::SplitterCString(const CString & str, const std::string & delimiter)
{
	std::vector<CString> strings;
	std::string::size_type pos = 0;
	std::string::size_type prev = 0;
	std::string strTemp = CStringToStd(str);
	while ((pos = strTemp.find(delimiter, prev)) != std::string::npos)
	{
		if (!strTemp.substr(prev, pos - prev).empty())
		{
			strings.push_back(StdToCString(strTemp.substr(prev, pos - prev)));
		}
		prev = pos + 1;
	}
	if (!strTemp.substr(prev).empty())
	{
		strings.push_back(StdToCString(strTemp.substr(prev)));
	}
	return strings;
}

int AppUtils::ReplaceFirstOf(CString& str, const CString& pszOld, const CString& pszNew)
{
	int found = str.Find(pszOld);
	if (found >= 0)
	{
		str.Delete(found, 1);
		str.Insert(found, pszNew);
	}
	return found;
}

#if 0
void AppUtils::RemoveSpecialCharacters(CString & strWord)
{
	std::wstring str = CStringToWStd(strWord);
	str.erase(std::remove_if(str.begin(),
		str.end(), [](char c)
	{
		return !(isalpha((unsigned char)c) || '_' == c);
	}), str.end());
	strWord = WStdToCString(str);
}
#endif

BOOL AppUtils::IsCStringAllDigits(const CString &str)
{
	for (auto const& i : CStringToWStd(str))
	{
		if (i < 48 || i > 57) return FALSE;
	}
	return TRUE;
}

BOOL AppUtils::IsUrlHyperLink(const CString & strString)
{
	BOOL bRet = FALSE;
	HRESULT hr;
	hr = IsValidURL(NULL, strString, 0);
	switch (hr)
	{
		case S_OK:
			bRet = TRUE;
			break;
		case S_FALSE:
			bRet = FALSE;
			break;
		case E_INVALIDARG:
			bRet = FALSE;
			break;
		default:
			break;
	}
	return bRet;
}

BOOL AppUtils::IsUrlHyperLink(TCHAR * text, int textLen, int start, int* segmentLen)
{
	int dist = 0, schemeLen = 0;
	if (StringHelper::scanToUrlStart(text, textLen, start, &dist, &schemeLen))
	{
		if (dist)
		{
			*segmentLen = dist;
			return false;
		}
		int len = 0;
		StringHelper::scanToUrlEnd(text, textLen, start + schemeLen, &len);
		if (len)
		{
			len += schemeLen;
			URL_COMPONENTS url;
			memset(&url, 0, sizeof(url));
			url.dwStructSize = sizeof(url);
			bool r = InternetCrackUrl(&text[start], len, 0, &url) && StringHelper::isUrlSchemeSupported(url.nScheme);
			if (r)
			{
				while (StringHelper::removeUnwantedTrailingCharFromUrl(&text[start], &len));
				*segmentLen = len;
				return true;
			}
		}
		len = 1;
		int lMax = textLen - start;
		while (StringHelper::isUrlSchemeStartChar(text[start + len]) && (len < lMax)) len++;
		*segmentLen = len;
		return false;
	}
	*segmentLen = dist;
	return false;
}

void AppUtils::BufferBYTE2String(BYTE * pBuffer, const unsigned int pBufferSize, char ** pString)
{
	unsigned int	lOutStringSize = (pBufferSize * 3) + 1;

	// it is the caller that it is on charge to delete this pointer
	char*			lOutString = new char[lOutStringSize];
	sprintf(lOutString, "%s", "");

	char lAppString[4];
	for (unsigned int i = 0; i < pBufferSize; i++)
	{
		BYTE b = pBuffer[i];

		// NOTE: 3 chars in out string for each byte in input buffer
		sprintf(lAppString, "%03u", b);
		strcat(lOutString, lAppString);
	}

	*pString = lOutString;
}

void AppUtils::String2BufferBYTE(const char * pString, BYTE ** pBuffer, unsigned int * pBufferSize)
{
	unsigned int	lOutBufferSize = static_cast<unsigned int>(strlen(pString) / 3);

	// it is the caller that it is on charge to delete this pointer
	BYTE*	lOutBuffer = new BYTE[lOutBufferSize];

	char lAppString[4];

	unsigned int j = 0;
	unsigned int j1 = 0;
	unsigned int j2 = 0;
	unsigned int j3 = 0;

	for (unsigned int i = 0; i < lOutBufferSize; i++)
	{
		j1 = j++;
		j2 = j++;
		j3 = j++;

		sprintf(
			lAppString,
			"%c%c%c",
			pString[j1],
			pString[j2],
			pString[j3]);

		// NOTE: one byte in output buffer for each 3 chars in input string
		BYTE b = (BYTE)atoi(lAppString);

		lOutBuffer[i] = b;
	}

	*pBuffer = lOutBuffer;
	*pBufferSize = lOutBufferSize;
}

CString AppUtils::RemoveJunkFromCString(const CString & strString)
{
	std::wregex reg(L"[^^(\n)\x20-\x7E]");
	auto wstringret = std::regex_replace(AppUtils::CStringToWStd(strString), reg, L"");
	CString str = AppUtils::WStdToCString(wstringret);
	return str;
}

void AppUtils::ToTitleCase(std::wstring& str)
{
	bool active = true;

	for (int i = 0; str[i] != L'\0'; i++)
	{
		if (std::isalpha((unsigned char)str[i]))
		{
			if (active) 
			{
				str[i] = std::toupper(str[i]);
				active = false;
			}
			else 
			{
				str[i] = std::tolower(str[i]);
			}
		}
		else if (str[i] == ' ' || str[i] == '\n')
		{
			active = true;
		}
	}
}

void AppUtils::ToInvertCase(std::wstring & str)
{
	for (int i = 0; str[i] != L'\0'; i++)
	{
		wchar_t c = str[i];
		if (std::isupper(str[i]))
		{
			str[i] = std::tolower(str[i]);
		}
		else if (std::islower(str[i]))
		{
			str[i] = std::toupper(str[i]);
		}
	}
}

void AppUtils::ToRandomCase(std::wstring & str)
{
	bool bToggle = rand() % 2 == 0 ? true : false;
	for (int i = 0; str[i] != L'\0'; i++)
	{
		wchar_t c = str[i];
		if (bToggle)
		{
			if (i % 2 == 0)
			{
				str[i] = std::tolower(str[i]);
			}
			else
			{
				str[i] = std::toupper(str[i]);
			}
		}
		else
		{
			if (i % 2 == 0)
			{
				str[i] = std::toupper(str[i]);
			}
			else
			{
				str[i] = std::tolower(str[i]);
			}
		}
	}
}

BOOL AppUtils::TinyXML2Format(const CString & strFile)
{
	TiXmlDocument doc;
	doc.LoadFile(CStringToStd(strFile).c_str());
	if (doc.Error())
	{
		char str[512];
		memset(str, '\0', 512);
		sprintf(str, "[Format Information] Error in %s: %s\n", doc.Value(), doc.ErrorDesc());
		CString strErrorMessage(str);
		LOG_OUTPUT_MESSAGE_ACTIVE_PANE(strErrorMessage);
		return FALSE;
	}
	if (doc.SaveFile())
	{
		return TRUE;
	}
	return FALSE;
}

void AppUtils::CreateNewEditorWithText(const CString & strTitle, const CString & strText)
{
	GetVinaTextApp()->OnFileNewEditor();
	auto pEditorDoc = dynamic_cast<CEditorDoc*>(GetMDIActiveDocument());
	if (pEditorDoc)
	{
		pEditorDoc->SetTitle(strTitle);
		if (!strText.IsEmpty())
		{
			auto pEditor = pEditorDoc->GetEditorCtrl();
			if (pEditor)
			{
				pEditor->SetTextToEditor(strText);
			}
		}
	}
}

CString AppUtils::GetFileTypeByExtension(const CString & strFileExt)
{
	if (strFileExt.CompareNoCase(_T("pyc")) == 0)
	{
		return _T("Bytecode");
	}
	else if (strFileExt.CompareNoCase(_T("reg")) == 0)
	{
		return _T("Registry");
	}
	else if (strFileExt.CompareNoCase(_T("xlsx")) == 0 || strFileExt.CompareNoCase(_T("xls")) == 0 || strFileExt.CompareNoCase(_T("csv")) == 0)
	{
		return _T("Excel");
	}
	else if (strFileExt.CompareNoCase(_T("rc")) == 0)
	{
		return _T("Resource");
	}
	else if (strFileExt.CompareNoCase(_T("sln")) == 0)
	{
		return _T("VSSolution");
	}
	else if (strFileExt.CompareNoCase(_T("jpl")) == 0)
	{
		return _T("Macro");
	}
	else if (strFileExt.CompareNoCase(_T("mk")) == 0)
	{
		return _T("MakeFile");
	}
	else if (strFileExt.CompareNoCase(_T("class")) == 0)
	{
		return _T("JavaClass");
	}
	else if (strFileExt.CompareNoCase(_T("tfrecords")) == 0)
	{
		return _T("TensorFlow");
	}
	else if (strFileExt.CompareNoCase(_T("npy")) == 0)
	{
		return _T("Numpy");
	}
	else if (strFileExt.CompareNoCase(_T("petastorm")) == 0)
	{
		return _T("Petastorm");
	}
	else if (strFileExt.CompareNoCase(_T("dat")) == 0)
	{
		return _T("Raw Data");
	}
	else if (strFileExt.CompareNoCase(_T("pb")) == 0)
	{
		return _T("Protobufer");
	}
	else if (strFileExt.CompareNoCase(_T("pkl")) == 0)
	{
		return _T("Pickle");
	}
	else if (strFileExt.CompareNoCase(_T("pem")) == 0 || strFileExt.CompareNoCase(_T("crt")) == 0)
	{
		return _T("Certificate");
	}
	else if (strFileExt.CompareNoCase(_T("hdf")) == 0 || strFileExt.CompareNoCase(_T("hdf5")) == 0)
	{
		return _T("HDF Data");
	}
	else if (strFileExt.CompareNoCase(_T("png")) == 0 || strFileExt.CompareNoCase(_T("jpg")) == 0
		|| strFileExt.CompareNoCase(_T("bmp")) == 0 || strFileExt.CompareNoCase(_T("gif")) == 0
		|| strFileExt.CompareNoCase(_T("ico")) == 0 || strFileExt.CompareNoCase(_T("jpeg")) == 0)
	{
		return _T("Image");
	}
	else if (strFileExt.CompareNoCase(_T("cfg")) == 0 || strFileExt.CompareNoCase(_T("conf")) == 0)
	{
		return _T("Config");
	}
	else if (strFileExt.CompareNoCase(_T("key")) == 0)
	{
		return _T("Security Key");
	}
	else if (strFileExt.CompareNoCase(_T("yml")) == 0 || strFileExt.CompareNoCase(_T("lock")) == 0)
	{
		return _T("Yaml");
	}
	else if (strFileExt.CompareNoCase(_T("txt")) == 0 || strFileExt.IsEmpty())
	{
		return _T("Text");
	}
	else
	{
		int nPos = AppUtils::FindFirstCharacterNotOf(strFileExt, _T(" \t"));
		std::wstring strSTD = CStringToWStd(strFileExt);
		boost::to_lower(strSTD);
		std::wstring strFirstChar(1, strSTD[nPos]);
		boost::to_upper(strFirstChar);
		std::wstring strSentenceCase = strSTD.replace(nPos, 1, strFirstChar);
		return WStdToCString(strSTD);
	}
}

CString AppUtils::GetFileFormatDescription(const CString & strFileExt)
{
	CString strFileDescription = _T("Normal File");
	if (AppUtils::GetVinaTextApp()->m_FileDescriptionData.empty())
	{
		CString strFilePath = PathUtils::GetVinaTextPackagePath() + _T("data-packages\\file-format-description.dat");
		if (PathFileExists(strFilePath))
		{
			CString strFileContent;
			PathUtils::OpenFile(strFilePath, strFileContent);
			CStringArray arrLines;
			AppUtils::SplitCString(strFileContent, EDITOR_NEW_LINE, arrLines);
			for (int i = 0; i < arrLines.GetSize(); ++i)
			{
				CString strLine = arrLines[i].Trim();
				if (strLine.IsEmpty()) continue;
				int demiliterPos = strLine.Find(_T("|"));
				CString ext = strLine.Mid(0, demiliterPos).Trim();
				CString desc = strLine.Mid(demiliterPos + 1).Trim();
				AppUtils::GetVinaTextApp()->m_FileDescriptionData[ext.MakeLower()] = desc;
				if (ext.CompareNoCase(_T(".") + strFileExt) == 0)
				{
					strFileDescription = desc;
				}
			}
		}
	}
	else
	{
		std::map<CString, CString>::const_iterator iter;
		CString strFindWhat = _T(".") + strFileExt;
		iter = AppUtils::GetVinaTextApp()->m_FileDescriptionData.find(strFindWhat);
		if (iter != AppUtils::GetVinaTextApp()->m_FileDescriptionData.end())
		{
			strFileDescription = iter->second;
		}
	}
	return strFileDescription;
}

std::vector<std::string> AppUtils::SplitterStdString(const std::string & str, const std::string & delimiter)
{
	std::vector<std::string> strings;
	std::string::size_type pos = 0;
	std::string::size_type prev = 0;
	while ((pos = str.find(delimiter, prev)) != std::string::npos)
	{
		strings.push_back(str.substr(prev, pos - prev));
		prev = pos + 1;
	}
	strings.push_back(str.substr(prev));
	return strings;
}

std::vector<std::wstring> AppUtils::SplitterWStdString(const std::wstring & str, const std::wstring & delimiter)
{
	std::vector<std::wstring> strings;
	std::wstring::size_type pos = 0;
	std::wstring::size_type prev = 0;
	while ((pos = str.find(delimiter, prev)) != std::wstring::npos)
	{
		strings.push_back(str.substr(prev, pos - prev));
		prev = pos + 1;
	}
	strings.push_back(str.substr(prev));
	return strings;
}

CFrameWnd* AppUtils::GetActiveFrame()
{
	CWnd* pWndMain = AfxGetMainWnd();
	ASSERT(pWndMain);
	if (!pWndMain) return NULL;
	ASSERT(pWndMain->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd))); // Not an MDI app.
	CFrameWnd* pFrame = ((CMDIFrameWnd*)pWndMain)->MDIGetActive();
	return pFrame;
}

CDocument* AppUtils::GetMDIActiveDocument()
{
	CDocument* pDoc = NULL;

	CWnd* pWndMain = AfxGetMainWnd();
	if (!pWndMain) return pDoc;
	ASSERT(pWndMain->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd))); // Not an MDI app.

	CFrameWnd* pFrame = ((CMDIFrameWnd*)pWndMain)->MDIGetActive();
	if (NULL != pFrame)
	{
		pDoc = pFrame->GetActiveDocument(); // get the active document
	}
	return pDoc;
}

CView* AppUtils::GetMDIActiveView()
{
	CDocument* pDoc = GetMDIActiveDocument();
	if (!pDoc) return 0;

	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
	if (!pMainFrame) return 0;
	CFrameWnd* pChildFrame = pMainFrame->GetActiveFrame();
	if (!pChildFrame) return 0;
	CView* pView = pChildFrame->GetActiveView();
	if (!pView)
	{
		return NULL;
	}
	return pView;
}

BOOL AppUtils::MDIActiveFrame()
{
	CView* pView = GetMDIActiveView();
	if (!pView)
	{
		return FALSE;
	}
	CMDIChildWnd *pChildFrame = static_cast<CMDIChildWnd*>(pView->GetParent());
	pChildFrame->MDIActivate();
	return TRUE;
}

BOOL AppUtils::SetActiveDocument(CDocument* pDoc)
{
	if (!pDoc) return FALSE;
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (!doctempl) return FALSE;
		POSITION posDoc = doctempl->GetFirstDocPosition();
		while (posDoc)
		{
			CDocument* doc = doctempl->GetNextDoc(posDoc);
			if (doc == pDoc)
			{
				POSITION p3 = doc->GetFirstViewPosition();
				while (p3)
				{
					CView* pView = doc->GetNextView(p3);
					if (pView)
					{
						pView->GetParentFrame()->ActivateFrame();
						pView->SetFocus();
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

void AppUtils::CloseAllPreviewDocument(PREVIEW_TYPE type)
{
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (!doctempl) return;
		POSITION posDoc = doctempl->GetFirstDocPosition();
		while (posDoc)
		{
			CBaseDoc* pDoc = dynamic_cast<CBaseDoc*>(doctempl->GetNextDoc(posDoc));
			if (pDoc && pDoc->IsPreviewMode())
			{
				if (type == PREVIEW_TYPE::PREVIEW_EDITOR && pDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
				{
					CloseMDIDocument(pDoc);
				}
				else if (type == PREVIEW_TYPE::PREVIEW_IMAGE && pDoc->IsKindOf(RUNTIME_CLASS(CImageDoc)))
				{
					CloseMDIDocument(pDoc);
				}
				else if (type == PREVIEW_TYPE::PREVIEW_MEDIA && pDoc->IsKindOf(RUNTIME_CLASS(CMediaDoc)))
				{
					CloseMDIDocument(pDoc);
				}
				else if (type == PREVIEW_TYPE::PREVIEW_PDF && pDoc->IsKindOf(RUNTIME_CLASS(CPdfDoc)))
				{
					CloseMDIDocument(pDoc);
				}
			}
		}
	}
}

CDocument * AppUtils::GetNextPreviewDocument(PREVIEW_TYPE type)
{
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (!doctempl) return NULL;
		POSITION posDoc = doctempl->GetFirstDocPosition();
		while (posDoc)
		{
			CBaseDoc* pDoc = dynamic_cast<CBaseDoc*>(doctempl->GetNextDoc(posDoc));
			if (pDoc && pDoc->IsPreviewMode())
			{
				if (type == PREVIEW_TYPE::PREVIEW_EDITOR && pDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
				{
					return pDoc;
				}
				else if (type == PREVIEW_TYPE::PREVIEW_IMAGE && pDoc->IsKindOf(RUNTIME_CLASS(CImageDoc)))
				{
					return pDoc;
				}
				else if (type == PREVIEW_TYPE::PREVIEW_MEDIA && pDoc->IsKindOf(RUNTIME_CLASS(CMediaDoc)))
				{
					return pDoc;
				}
				else if (type == PREVIEW_TYPE::PREVIEW_PDF && pDoc->IsKindOf(RUNTIME_CLASS(CPdfDoc)))
				{
					return pDoc;
				}
			}
		}
	}
	return NULL;
}

CDocument* AppUtils::GetExistedDocument(CString strFile)
{
	if (PathFileExists(strFile))
	{
		POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
		while (posTemplate)
		{
			CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
			if (!doctempl) return NULL;
			POSITION posDoc = doctempl->GetFirstDocPosition();
			while (posDoc)
			{
				CDocument* pDocTarget = doctempl->GetNextDoc(posDoc);
				if (pDocTarget)
				{
					CString strPathName = pDocTarget->GetPathName();
					strPathName.Replace(_T("\\"), _T("/"));
					strFile.Replace(_T("\\"), _T("/"));
					if (strFile.CompareNoCase(strPathName) == 0)
					{
						return pDocTarget;
					}
				}
			}
		}
	}
	return NULL;
}

CDocument * AppUtils::GetDocumentFromTitle(const CString& strTitleDocument)
{
	if (!strTitleDocument.IsEmpty())
	{
		POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
		while (posTemplate)
		{
			CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
			if (!doctempl) return NULL;
			POSITION posDoc = doctempl->GetFirstDocPosition();
			while (posDoc)
			{
				CDocument* pDocTarget = doctempl->GetNextDoc(posDoc);
				if (pDocTarget)
				{
					CString strTitle = pDocTarget->GetTitle();
					if (strTitleDocument == strTitle)
					{
						return pDocTarget;
					}
				}
			}
		}
	}
	return NULL;
}

void AppUtils::CloseMDIDocument(CDocument* pDocTarget)
{
	if (pDocTarget)
	{
		POSITION p3 = pDocTarget->GetFirstViewPosition();
		while (p3)
		{
			CView* view = pDocTarget->GetNextView(p3);
			if (view && view->GetParentFrame())
			{
				view->GetParentFrame()->SendMessage(WM_CLOSE);
			}
		}
	}
}

void AppUtils::CloseDocumentByFilePath(CString strFile)
{
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (!doctempl) return;
		POSITION posDoc = doctempl->GetFirstDocPosition();
		while (posDoc)
		{
			CDocument* pDocTarget = doctempl->GetNextDoc(posDoc);
			if (pDocTarget)
			{
				CString strPathName = pDocTarget->GetPathName();
				strPathName.Replace(_T("\\"), _T("/"));
				strFile.Replace(_T("\\"), _T("/"));
				if (strFile.CompareNoCase(strPathName) == 0)
				{
					CloseMDIDocument(pDocTarget);
				}
			}
		}
	}
}

void AppUtils::CloseDocumentByTitle(const CString& strTitle)
{
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (!doctempl) return;
		POSITION posDoc = doctempl->GetFirstDocPosition();
		while (posDoc)
		{
			CDocument* pDocTarget = doctempl->GetNextDoc(posDoc);
			if (pDocTarget)
			{
				CString strTitleName = pDocTarget->GetTitle();
				if (strTitle.CompareNoCase(strTitleName) == 0)
				{
					CloseMDIDocument(pDocTarget);
				}
			}
		}
	}
}

void AppUtils::CloseDeletedDocument(CView * pCloseView, const CString & strFileDeleted)
{
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate* doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (!doctempl) return;
		POSITION posDoc = doctempl->GetFirstDocPosition();
		while (posDoc)
		{
			CDocument* doc = doctempl->GetNextDoc(posDoc);
			if (doc) {
				POSITION p3 = doc->GetFirstViewPosition();
				while (p3)
				{
					CView* view = doc->GetNextView(p3);
					if (view && view->GetParentFrame() && view == pCloseView)
					{
						view->GetParentFrame()->PostMessage(WM_CLOSE);
					}
				}
			}
		}
	}
	// remove it from explorer also...
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (pFrame)
	{
		HTREEITEM hDeleteItem = pFrame->GetFileExplorerCtrl().PathToItem(strFileDeleted);
		if (hDeleteItem)
		{
			pFrame->GetFileExplorerCtrl().DeleteItem(hDeleteItem);
		}
	}
}

void AppUtils::CloseAllDocument()
{
	int nAnwser = IDNO;
	if (GetModifiedDocumentCount() > 1)
	{
		nAnwser = AfxMessageBox(_T("Do you want to save all modified files?"), MB_YESNOCANCEL | MB_ICONINFORMATION);
		if (IDYES == nAnwser)
		{
			SaveAllModifiedDocuments();
			AfxGetApp()->CloseAllDocuments(TRUE);
			return;
		}
		else if (IDCANCEL == nAnwser)
		{
			return;
		}
	}
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (!doctempl) return;
		POSITION posDoc = doctempl->GetFirstDocPosition();
		while (posDoc)
		{
			CDocument* doc = doctempl->GetNextDoc(posDoc);
			if (nAnwser == IDNO)
			{
				doc->SetModifiedFlag(FALSE);
			}
			CloseMDIDocument(doc);
		}
	}
}

void AppUtils::CloseAllDocumentUnmodified()
{
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (!doctempl) return;
		POSITION posDoc = doctempl->GetFirstDocPosition();
		while (posDoc)
		{
			CDocument* doc = doctempl->GetNextDoc(posDoc);
			if (!doc->IsModified())
			{
				CloseMDIDocument(doc);
			}
		}
	}
}

void AppUtils::CloseAllDocumentLeft(CView * pActiveView)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	if (!pFrame) return;
	std::vector<CWnd*> leftTabs;
	const CObList& tabGroups = pFrame->GetMDIClientAreaWnd().GetMDITabGroups();
	if (tabGroups.GetCount() > 0)
	{
		POSITION pos = tabGroups.GetHeadPosition();
		CMFCTabCtrl* pCrtTabCtrl;

		while (pos != NULL)
		{
			pCrtTabCtrl = DYNAMIC_DOWNCAST(CMFCTabCtrl, tabGroups.GetNext(pos));

			int count = pCrtTabCtrl->GetTabsNum();
			for (int i = 0; i < count; i++)
			{
				CWnd* pWnd = pCrtTabCtrl->GetTabWndNoWrapper(i);
				CMDIChildWnd *pChild = ((CMDIChildWnd*)(pWnd));
				if (pChild)
				{
					CView *pView = pChild->GetActiveView();
					if (pView)
					{
						if (pView != pActiveView)
						{
							leftTabs.push_back(pWnd);
						}
						else
						{
							break;
						}
					}
				}
			}
		}
	}
	for (auto const& pTab : leftTabs)
	{
		if (pTab)
		{
			pTab->SendMessage(WM_CLOSE);
		}
	}
	SetActiveDocument(pActiveView->GetDocument());
}

void AppUtils::CloseAllDocumentRight(CView * pActiveView)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	if (!pFrame) return;
	std::vector<CWnd*> rightTabs;
	const CObList& tabGroups = pFrame->GetMDIClientAreaWnd().GetMDITabGroups();
	if (tabGroups.GetCount() > 0)
	{
		POSITION pos = tabGroups.GetHeadPosition();
		CMFCTabCtrl* pCrtTabCtrl;

		while (pos != NULL)
		{
			pCrtTabCtrl = DYNAMIC_DOWNCAST(CMFCTabCtrl, tabGroups.GetNext(pos));
			BOOL bCheckRightTabs = FALSE;
			int count = pCrtTabCtrl->GetTabsNum();
			for (int i = 0; i < count; i++)
			{
				CWnd* pWnd = pCrtTabCtrl->GetTabWndNoWrapper(i);
				CMDIChildWnd *pChild = ((CMDIChildWnd*)(pWnd));
				if (pChild)
				{
					CView *pView = pChild->GetActiveView();
					if (pView)
					{
						if (pView == pActiveView)
						{
							bCheckRightTabs = TRUE;
						}
						else if (bCheckRightTabs)
						{
							rightTabs.push_back(pWnd);
						}
					}
				}
			}
		}
	}
	for (auto const& pTab : rightTabs)
	{
		if (pTab)
		{
			pTab->SendMessage(WM_CLOSE);
		}
	}
	SetActiveDocument(pActiveView->GetDocument());
}

void AppUtils::CloseAllDocumentButThis(CView * pActiveView)
{
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (!doctempl) return;
		POSITION posDoc = doctempl->GetFirstDocPosition();
		while (posDoc)
		{
			CDocument* pDocument = doctempl->GetNextDoc(posDoc);
			if (pDocument)
			{
				POSITION p3 = pDocument->GetFirstViewPosition();
				while (p3)
				{
					CView* view = pDocument->GetNextView(p3);
					if (view && view->GetParentFrame() && view != pActiveView)
					{
						view->GetParentFrame()->SendMessage(WM_CLOSE);
					}
				}
			}
		}
	}
}

BOOL AppUtils::CanCloseAllDocumentLeft(CView * pActiveView)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	if (!pFrame) return FALSE;
	std::vector<CWnd*> leftTabs;
	const CObList& tabGroups = pFrame->GetMDIClientAreaWnd().GetMDITabGroups();
	if (tabGroups.GetCount() > 0)
	{
		POSITION pos = tabGroups.GetHeadPosition();
		CMFCTabCtrl* pCrtTabCtrl;

		while (pos != NULL)
		{
			pCrtTabCtrl = DYNAMIC_DOWNCAST(CMFCTabCtrl, tabGroups.GetNext(pos));

			int count = pCrtTabCtrl->GetTabsNum();
			for (int i = 0; i < count; i++)
			{
				CWnd* pWnd = pCrtTabCtrl->GetTabWndNoWrapper(i);
				CMDIChildWnd *pChild = ((CMDIChildWnd*)(pWnd));
				if (pChild)
				{
					CView *pView = pChild->GetActiveView();
					if (pView)
					{
						if (pView != pActiveView)
						{
							leftTabs.push_back(pWnd);
						}
						else
						{
							break;
						}
					}
				}
			}
		}
	}
	if (leftTabs.size() > 0)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL AppUtils::CanCloseAllDocumentRight(CView * pActiveView)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	if (!pFrame) return FALSE;
	std::vector<CWnd*> rightTabs;
	const CObList& tabGroups = pFrame->GetMDIClientAreaWnd().GetMDITabGroups();
	if (tabGroups.GetCount() > 0)
	{
		POSITION pos = tabGroups.GetHeadPosition();
		CMFCTabCtrl* pCrtTabCtrl;

		while (pos != NULL)
		{
			pCrtTabCtrl = DYNAMIC_DOWNCAST(CMFCTabCtrl, tabGroups.GetNext(pos));
			BOOL bCheckRightTabs = FALSE;
			int count = pCrtTabCtrl->GetTabsNum();
			for (int i = 0; i < count; i++)
			{
				CWnd* pWnd = pCrtTabCtrl->GetTabWndNoWrapper(i);
				CMDIChildWnd *pChild = ((CMDIChildWnd*)(pWnd));
				if (pChild)
				{
					CView *pView = pChild->GetActiveView();
					if (pView)
					{
						if (pView == pActiveView)
						{
							bCheckRightTabs = TRUE;
						}
						else if (bCheckRightTabs)
						{
							rightTabs.push_back(pWnd);
						}
					}
				}
			}
		}
	}
	if (rightTabs.size() > 0)
	{
		return TRUE;
	}
	return FALSE;
}

void AppUtils::SaveAllModifiedDocuments()
{
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (!doctempl) return;
		POSITION posDoc = doctempl->GetFirstDocPosition();
		while (posDoc)
		{
			CDocument* pDoc = doctempl->GetNextDoc(posDoc);
			if (pDoc && pDoc->IsModified())
			{
				if (pDoc->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
				{
					CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(pDoc);
					if (pEditorDoc)
					{
						pEditorDoc->OnFileSave();
					}
				}
				else if (pDoc->IsKindOf(RUNTIME_CLASS(CImageDoc)))
				{
					CImageDoc* pImageDoc = dynamic_cast<CImageDoc*>(pDoc);
					if (pImageDoc)
					{
						pImageDoc->OnFileSave();
					}
				}
			}
		}
	}
	LOG_OUTPUT_MESSAGE_COLOR(_T("> Save all modified documents..."));
}

CDocument* AppUtils::CreateDocumentFromFile(const CString & strFile)
{
	auto pDoc = dynamic_cast<CBaseDoc*>(GetExistedDocument(strFile));
	if (pDoc)
	{
		SetActiveDocument(pDoc);
		pDoc->SetPreviewMode(FALSE);
		return pDoc;
	}
	return GetVinaTextApp()->OnOpenDocument(strFile);
}

CDocument * AppUtils::CreateNewPreviewDocument(const CString & strFile)
{
	CDocument* pNewPreviewDoc = AppUtils::CreateDocumentFromFile(strFile);
	auto pNewPreviewBaseDoc = dynamic_cast<CBaseDoc*>(pNewPreviewDoc);
	if (pNewPreviewBaseDoc)
	{
		pNewPreviewBaseDoc->SetPreviewMode(TRUE);
	}
	else
	{
		return NULL;
	}
	return (CDocument*)pNewPreviewBaseDoc;
}

CDocument * AppUtils::CreateDocumentCheckFileExistence(const CString & strFile)
{
	const int REPLACE_FILE_ID = 201;
	const int OPEN_FILE_ID = 202;
	const int CANCEL_ID = 203;
	auto fTaskReplaceDialog = [&](const CString& strFileName) -> BOOL
	{
		CString strMessage = _T("[Warning] The location already has a file named \"%s\". Please choose your option:");
		strMessage.Format(strMessage, strFileName);
		CTaskDialog dlg(_T(""), strMessage, _T("VinaText"), 0/*TDCBF_OK_BUTTON*/);
		dlg.SetMainIcon(TD_WARNING_ICON);
		dlg.AddCommandControl(REPLACE_FILE_ID, _T("Replace this file"));
		dlg.AddCommandControl(OPEN_FILE_ID, _T("Open this file"));
		dlg.AddCommandControl(CANCEL_ID, _T("Cancel"));
		dlg.SetDialogWidth(300);
		dlg.SetDefaultCommandControl(REPLACE_FILE_ID);
		dlg.DoModal();
		return dlg.GetSelectedCommandControlID();
	};

	if (FALSE == PathFileExists(strFile))
	{
		//Try to create the new file
		HANDLE hCreateFile = CreateFile(strFile,    // name of the file
			GENERIC_READ, // open for writing
			0,             // sharing mode, none in this case
			0,             // use default security descriptor
			CREATE_ALWAYS, // overwrite if exists
			FILE_ATTRIBUTE_NORMAL,
			0);
		if (hCreateFile)
		{
			DELETE_WIN32_HANDLE(hCreateFile);
			return AppUtils::CreateDocumentFromFile(strFile);
		}
	}
	else
	{
		int nUserOption = fTaskReplaceDialog(strFile);
		if (nUserOption == REPLACE_FILE_ID)
		{
			auto pDoc = dynamic_cast<CBaseDoc*>(AppUtils::GetExistedDocument(strFile));
			if (pDoc)
			{
				AppUtils::CloseDocumentByFilePath(strFile);
			}
			//Try to create the new file
			HANDLE hCreateFile = CreateFile(strFile,    // name of the file
				GENERIC_READ, // open for writing
				0,             // sharing mode, none in this case
				0,             // use default security descriptor
				CREATE_ALWAYS, // overwrite if exists
				FILE_ATTRIBUTE_NORMAL,
				0);
			if (hCreateFile)
			{
				DELETE_WIN32_HANDLE(hCreateFile);
				return AppUtils::CreateDocumentFromFile(strFile);
			}
		}
		else if (nUserOption == OPEN_FILE_ID)
		{
			return AppUtils::CreateDocumentFromFile(strFile);
		}
	}
	return NULL;
}

int AppUtils::GetModifiedDocumentCount()
{
	int nCount = 0;
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (!doctempl) return NULL;
		POSITION posDoc = doctempl->GetFirstDocPosition();
		while (posDoc)
		{
			CDocument* pDoc = doctempl->GetNextDoc(posDoc);
			if (pDoc && pDoc->IsModified())
			{
				nCount++;
			}
		}
	}
	return nCount;
}

std::vector<CDocument*> AppUtils::GetAllDocuments()
{
	std::vector<CDocument*> vecDocs;
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (doctempl)
		{
			POSITION posDoc = doctempl->GetFirstDocPosition();
			while (posDoc)
			{
				CDocument* pDocTarget = doctempl->GetNextDoc(posDoc);
				if (pDocTarget)
				{
					vecDocs.push_back(pDocTarget);
				}
			}
		}
	}
	return vecDocs;
}

std::vector<CDocument*> AppUtils::GetAllDocumentTypes(DOCUMENT_TYPE type)
{
	std::vector<CDocument*> vecDocs;
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (doctempl)
		{
			POSITION posDoc = doctempl->GetFirstDocPosition();
			while (posDoc)
			{
				CDocument* pDocTarget = doctempl->GetNextDoc(posDoc);
				if (pDocTarget)
				{
					if (type == DOCUMENT_TYPE::DOC_EDITOR && pDocTarget->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
					{
						vecDocs.push_back(pDocTarget);
					}
					else if (type == DOCUMENT_TYPE::DOC_IMAGE && pDocTarget->IsKindOf(RUNTIME_CLASS(CImageDoc)))
					{
						vecDocs.push_back(pDocTarget);
					}
					else if (type == DOCUMENT_TYPE::DOC_PDF && pDocTarget->IsKindOf(RUNTIME_CLASS(CPdfDoc)))
					{
						vecDocs.push_back(pDocTarget);
					}
					else if (type == DOCUMENT_TYPE::DOC_MEDIA && pDocTarget->IsKindOf(RUNTIME_CLASS(CMediaDoc)))
					{
						vecDocs.push_back(pDocTarget);
					}
					else if (type == DOCUMENT_TYPE::DOC_HOST && pDocTarget->IsKindOf(RUNTIME_CLASS(CHostDoc)))
					{
						vecDocs.push_back(pDocTarget);
					}
					else if (type == DOCUMENT_TYPE::DOC_EXPLORER && pDocTarget->IsKindOf(RUNTIME_CLASS(CFileExplorerDoc)))
					{
						vecDocs.push_back(pDocTarget);
					}
				}
			}
		}
	}
	return vecDocs;
}

std::vector<CEditorCtrl*> AppUtils::GetAllEditors()
{
	std::vector<CEditorCtrl*> vecEditors;
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (doctempl)
		{
			POSITION posDoc = doctempl->GetFirstDocPosition();
			while (posDoc)
			{
				CDocument* pDocTarget = doctempl->GetNextDoc(posDoc);
				if (pDocTarget)
				{
					if (pDocTarget->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
					{
						CEditorDoc* pEditorDoc = dynamic_cast<CEditorDoc*>(pDocTarget);
						if (pEditorDoc) {
							CEditorCtrl* pEditor = pEditorDoc->GetEditorCtrl();
							if (pEditor) {
								vecEditors.push_back(pEditor);
							}
						}
					}
				}
			}
		}
	}
	return vecEditors;
}

void AppUtils::ResizeAllViews()
{
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (pFrame)
	{
		const CObList& tabGroups = pFrame->GetMDIClientAreaWnd().GetMDITabGroups();
		if (tabGroups.GetCount() > 0)
		{
			POSITION pos = tabGroups.GetHeadPosition();
			CMFCTabCtrl* pCrtTabCtrl;
			while (pos != NULL)
			{
				pCrtTabCtrl = DYNAMIC_DOWNCAST(CMFCTabCtrl, tabGroups.GetNext(pos));
				BOOL bCheckRightTabs = FALSE;
				int count = pCrtTabCtrl->GetTabsNum();
				int nCounter = 0;
				for (int i = 0; i < count; i++)
				{
					CWnd* pWnd = pCrtTabCtrl->GetTabWndNoWrapper(i);
					CMDIChildWnd *pChild = ((CMDIChildWnd*)(pWnd));
					if (pChild)
					{
						CView *pView = pChild->GetActiveView();
						if (pView && pView->GetParentFrame())
						{
							pView->SendMessage(WM_SIZE);
						}
					}
				}
			}
		}
	}
}

void AppUtils::SyncActionAllEditorDocuments(std::function<void(CEditorDoc* pDoc)> pAction, CEditorDoc* pExcludeDoc)
{
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate* pDocTemplate = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (pDocTemplate)
		{
			POSITION posDoc = pDocTemplate->GetFirstDocPosition();
			while (posDoc)
			{
				CDocument* pDocument = pDocTemplate->GetNextDoc(posDoc);
				if (pDocument)
				{
					if (pDocument->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
					{
						CEditorDoc* pTmpDoc = dynamic_cast<CEditorDoc*>(pDocument);
						if (pTmpDoc)
						{
							if (pExcludeDoc && pTmpDoc == pExcludeDoc)
							{
								continue;
							}
							pAction(pTmpDoc);
						}
					}
				}
			}
		}
	}
}

BOOL AppUtils::IsDocumentExisted(CString strFile)
{
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate *doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (doctempl)
		{
			POSITION posDoc = doctempl->GetFirstDocPosition();
			while (posDoc)
			{
				CDocument* pDocTarget = doctempl->GetNextDoc(posDoc);
				if (pDocTarget)
				{
					CString strPathName = pDocTarget->GetPathName();
					if (strFile.CompareNoCase(strPathName) == 0)
					{
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

int AppUtils::GetDocumentTypeCount(DOCUMENT_TYPE type)
{
	int nCount = 0;
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate* doctempl = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (doctempl)
		{
			POSITION posDoc = doctempl->GetFirstDocPosition();
			while (posDoc)
			{
				CDocument* pDocTarget = doctempl->GetNextDoc(posDoc);
				if (pDocTarget)
				{
					if (type == DOCUMENT_TYPE::DOC_ALL)
					{
						nCount++;
					}
					else if (type == DOCUMENT_TYPE::DOC_EDITOR && pDocTarget->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
					{
						nCount++;
					}
					else if (type == DOCUMENT_TYPE::DOC_IMAGE && pDocTarget->IsKindOf(RUNTIME_CLASS(CImageDoc)))
					{
						nCount++;
					}
					else if (type == DOCUMENT_TYPE::DOC_PDF && pDocTarget->IsKindOf(RUNTIME_CLASS(CPdfDoc)))
					{
						nCount++;
					}
					else if (type == DOCUMENT_TYPE::DOC_MEDIA && pDocTarget->IsKindOf(RUNTIME_CLASS(CMediaDoc)))
					{
						nCount++;
					}
					else if (type == DOCUMENT_TYPE::DOC_HOST && pDocTarget->IsKindOf(RUNTIME_CLASS(CHostDoc)))
					{
						nCount++;
					}
					else if (type == DOCUMENT_TYPE::DOC_EXPLORER && pDocTarget->IsKindOf(RUNTIME_CLASS(CFileExplorerDoc)))
					{
						nCount++;
					}
				}
			}
		}
	}
	return nCount;
}

void AppUtils::CheckLastOpenDocument()
{
	if (GetDocumentTypeCount(DOCUMENT_TYPE::DOC_ALL) == 0) {
		const CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
		ASSERT(pFrame); if (!pFrame) return;
		if (!pFrame->IsClosingVinaText() && !GetVinaTextApp()->m_bIsReloadDocument) {
			GetVinaTextApp()->OnFileNewEditor();
		}
	}
}

void AppUtils::UpdateModifiedDocumentTitle(CDocument* pDoc, BOOL bAddMarker)
{
	ASSERT(pDoc);
	if (!pDoc) return;
	if (bAddMarker)
	{
		pDoc->SetModifiedFlag(TRUE);
		CString strTitle = pDoc->GetTitle();
		if (!strTitle.IsEmpty())
		{
			int ncount = strTitle.Replace(_T("*"), _T(""));
			if (ncount == 0)
			{
				strTitle = strTitle + _T("*");
				pDoc->SetTitle(strTitle);
				CMainFrame* pFrame = AppUtils::GetMainFrame();
				if (!pFrame) return;
				pFrame->OnUpdateFrameTitle(FALSE);
			}
		}
	}
	else
	{
		pDoc->SetModifiedFlag(FALSE);
		CString strTitle = pDoc->GetTitle();
		if (!strTitle.IsEmpty())
		{
			strTitle.Replace(_T("*"), _T(""));
			pDoc->SetTitle(strTitle);
			GetMainFrame()->OnUpdateFrameTitle(FALSE);
		}
	}
}

bool AppUtils::IsAlphaNumberString(const std::string &str)
{
	return find_if(str.begin(), str.end(), [](char c) { return !(isalnum(c)); }) == str.end();
}

void AppUtils::ReplaceAllInStdString(std::string& str, const std::string& from, const std::string& to)
{
	if (from.empty()) return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) 
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

void AppUtils::ReplaceAllInWStdString(std::wstring & str, const std::wstring & from, const std::wstring & to)
{
	if (from.empty()) return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::wstring::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

std::wstring AppUtils::RemoveDuplicateWordInString(const std::wstring& str)
{
	// Used to split string around spaces.
	std::wstringstream ss(str);
	// To store individual visited words
	std::unordered_set<std::wstring> hash_tab;
	// Traverse through all words in the string
	std::wstring line;
	do
	{
		std::wstring word;
		ss >> word;
		// check if current word already exist,if not then insert
		while (hash_tab.find(word) == hash_tab.end())
		{
			line += word + L" ";
			hash_tab.insert(word);
		}
	} while (ss);
	return line;
}

std::wstring AppUtils::RemoveDuplicateMatchCaseWordInString(const std::wstring & str)
{
	// Used to split string around spaces.
	std::wstringstream ss(str);
	// To store individual visited words
	std::unordered_set<std::wstring> hash_tab;
	// Traverse through all words in the string
	std::wstring line;
	do
	{
		std::wstring word;
		ss >> word;
		// check if current word already exist,if not then insert
		std::wstring wordCase = word;
		boost::to_lower(wordCase);
		while (hash_tab.find(word) == hash_tab.end() && hash_tab.find(wordCase) == hash_tab.end())
		{
			line += word + L" ";
			hash_tab.insert(word);
		}
	} while (ss);
	return line;
}

void AppUtils::ToLowerCaseStd(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });
}

CString AppUtils::ConvertDoubleToStringNumeric(double dValue, int uiWidth, int uiPrecision, DOUBLE_NUMERIC_TYPE nTYPE)
{
	auto IsDefaultDouble = [](double dd, bool bZeroIsDefault = FALSE) -> BOOL
	{
		if (bZeroIsDefault)
		{
			if (fabs(dd) < 1e3 * DBL_MIN)
			{
				return TRUE;
			}
		}
		if (fabs(dd) > (1e-3 * DBL_MAX) || (fabs(dd) < (1e3 * DBL_MIN) && fabs(dd) > 0.0))
		{
			return TRUE;
		}
		return FALSE;
	};

	CString strFormat, strValue;
	CString strFlag = _T("");
	if (nTYPE == DOUBLE_NUMERIC_TYPE::REAL_TYPE)
	{
		strFlag = _T("lf");
	}
	else if (nTYPE == DOUBLE_NUMERIC_TYPE::POWER_TYPE)
	{
		strFlag = _T("e");
	}
	else if (nTYPE == DOUBLE_NUMERIC_TYPE::SCIENTIFIC_NOTATION_TYPE)
	{
		strFlag = _T("g");
	}

	if (IsDefaultDouble(dValue))
	{
		strValue.Empty();
	}
	else if (fabs(dValue) < pow(10.0, -100))
	{
		strFormat.Format(_T("%c-%d.%d%s"), 0x25, uiWidth, uiPrecision, strFlag);
		strValue.Format(strFormat, 0.0);
		strValue.Trim();
	}
	else if (fabs(dValue) < pow(10.0, -uiPrecision))
	{
		strFormat.Format(_T("%c-%d.%d%s"), 0x25, uiWidth, uiPrecision, _T("e"));
		strValue.Format(strFormat, dValue);
		strValue.Trim();
	}
	else
	{
		strFormat.Format(_T("%c-%d.%d%s"), 0x25, uiWidth, uiPrecision, strFlag);
		strValue.Format(strFormat, dValue);
		strValue.Trim();
	}
	return strValue;
}

std::vector<long> AppUtils::GetNumberListFromCString(char *str)
{
	std::vector<long> vecnumber;
	char *p = str;
	while (*p) 
	{ // While there are more characters to process...
		if (isdigit(*p) || ((*p == '-' || *p == '+') && isdigit(*(p + 1)))) 
		{
			// Found a number
			long val = strtol(p, &p, 10); // Read number
			vecnumber.push_back(val);
		}
		else 
		{
			// Otherwise, move on to the next character.
			p++;
		}
	}
	return vecnumber;
}

BOOL AppUtils::IsXMLWhitespace(int ch)
{
	return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
}

CString AppUtils::GetLanguageStringName(VINATEXT_SUPPORTED_LANGUAGE language)
{
	CString strLanguage;
	if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C)
	{
		strLanguage = _T("C");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP)
	{
		strLanguage = _T("C++");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON)
	{
		strLanguage = _T("Python");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CSHAPE)
	{
		strLanguage = _T("C#");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_BATCH)
	{
		strLanguage = _T("Batch");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL)
	{
		strLanguage = _T("Pascal");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA)
	{
		strLanguage = _T("Java");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT)
	{
		strLanguage = _T("Javascript");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PHP)
	{
		strLanguage = _T("PHP");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_SQL)
	{
		strLanguage = _T("SQL");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VISUALBASIC)
	{
		strLanguage = _T("VisualBasic");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_ASSEMBLY)
	{
		strLanguage = _T("Asm");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_INNOSETTUP)
	{
		strLanguage = _T("Innosetup");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PERL)
	{
		strLanguage = _T("Perl");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_GOLANG)
	{
		strLanguage = _T("GoLang");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUST)
	{
		strLanguage = _T("Rust");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUBY)
	{
		strLanguage = _T("Ruby");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_MATLAB)
	{
		strLanguage = _T("Matlab");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_TCL)
	{
		strLanguage = _T("TCL Script");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_AUTOIT)
	{
		strLanguage = _T("AutoIT");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_VERILOG)
	{
		strLanguage = _T("Verilog");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_R)
	{
		strLanguage = _T("Any");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_POWERSHELL)
	{
		strLanguage = _T("PowerShell");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_HTML)
	{
		strLanguage = _T("HTML");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_XML)
	{
		strLanguage = _T("XML");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JSON)
	{
		strLanguage = _T("Json");
	}
	else if (language == VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_FREEBASIC)
	{
		strLanguage = _T("FreeBASIC");
	}
	else
	{
		strLanguage = _T("Text");
	}
	return strLanguage;
}

const VINATEXT_SUPPORTED_LANGUAGE arrLangSupportDebugger[] = {
	VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C,
	VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP,
	VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON,
	VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT,
	VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL,
	// update more...
};

BOOL AppUtils::IsLanguageSupportDebugger(VINATEXT_SUPPORTED_LANGUAGE language)
{
	for (int i = 0; i < _countof(arrLangSupportDebugger); ++i)
	{
		if (language == arrLangSupportDebugger[i])
		{
			return TRUE;
		}
	}
	return FALSE;
}

const VINATEXT_SUPPORTED_LANGUAGE arrLangSupportErrorAnnotation[] = {
	VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_C,
	VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CPP,
	VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PYTHON,
	VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVA,
	VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PASCAL,
	VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_JAVASCRIPT,
	VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_CSHAPE,
	VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_PHP,
	VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_RUST,
	// update more...
};

BOOL AppUtils::IsLanguageSupportErrorAnnotation(VINATEXT_SUPPORTED_LANGUAGE language)
{
	for (int i = 0; i < _countof(arrLangSupportErrorAnnotation); ++i)
	{
		if (language == arrLangSupportErrorAnnotation[i])
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL AppUtils::IsLanguageSupportLexer(VINATEXT_SUPPORTED_LANGUAGE language)
{
	for (int languageEnum = VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_TEXT + 1;
		languageEnum < VINATEXT_SUPPORTED_LANGUAGE::LANGUAGE_END; ++languageEnum)
	{
		if (language == languageEnum)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void AppUtils::UpdateSettingsForVinatext()
{
	POSITION posTemplate = AfxGetApp()->GetFirstDocTemplatePosition();
	while (posTemplate)
	{
		CDocTemplate* pDocTemplate = AfxGetApp()->GetNextDocTemplate(posTemplate);
		if (pDocTemplate)
		{
			POSITION posDoc = pDocTemplate->GetFirstDocPosition();
			while (posDoc)
			{
				CDocument* pDocument = pDocTemplate->GetNextDoc(posDoc);
				if (pDocument)
				{
					if (pDocument->IsKindOf(RUNTIME_CLASS(CEditorDoc)))
					{
						CEditorDoc* pTmpDoc = dynamic_cast<CEditorDoc*>(pDocument);
						if (pTmpDoc)
						{
							CEditorCtrl* pEditor = pTmpDoc->GetEditorCtrl();
							if (pEditor)
							{
								pEditor->InitilizeSetting(pTmpDoc->GetDocLanguageDatabase());
							}
						}
					}
				}
			}
		}
	}
	UPDATE_MAIN_FRAME(MAIN_FRAME_UPDATE_MSG::MAIN_FRAME_UPDATE_ALL_DOCKPANE,
		MAIN_FRAME_UPDATE_HINT::MAIN_FRAME_UPDATE_HINT_SETTING_CHANGED);
}

///////////////// GLOBAL HELPERS //////////////////////////

void LOG_MESSAGE(LOG_TARGET target, LPCTSTR lpszMsg, COLORREF col)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	if (pFrame)
	{
		pFrame->PrintMessage(target, lpszMsg, col);
	}
}

void LOG_OUTPUT_MESSAGE_LAST_ERROR()
{
	LOG_MESSAGE(LOG_TARGET::MESSAGE_WINDOW, _T("> ") + OSUtils::GetLastErrorAsString(), BasicColors::orange);
}

void LOG_OUTPUT_MESSAGE_COLOR(LPCTSTR lpszMsg, COLORREF col)
{
	LOG_MESSAGE(LOG_TARGET::MESSAGE_WINDOW, lpszMsg, col);
}

void LOG_OUTPUT_MESSAGE_FORMAT(const TCHAR* Fmt, ...)
{
	va_list args;
	va_start(args, Fmt);
	CString strMsg;
	strMsg.FormatV(Fmt, args);
	va_end(args);
	COLORREF col = IS_LIGHT_THEME ? BasicColors::black : BasicColors::white;
	LOG_MESSAGE(LOG_TARGET::MESSAGE_WINDOW, strMsg, col);
}

void LOG_OUTPUT_MESSAGE_WITH_TIME(LPCTSTR lpszMsg, COLORREF col)
{
	CString strCurrentTime = _T(" : ") + OSUtils::DateToCStringABDHMSY(OSUtils::GetCurrentTimeEx());
	LOG_MESSAGE(LOG_TARGET::MESSAGE_WINDOW, lpszMsg + strCurrentTime, col);
}

void LOG_BUILD_MESSAGE_COLOR(LPCTSTR lpszMsg, COLORREF col)
{
	LOG_MESSAGE(LOG_TARGET::BUILD_WINDOW, lpszMsg, col);
}

void LOG_BUILD_MESSAGE_FORMAT(const TCHAR * Fmt, ...)
{
	va_list args;
	va_start(args, Fmt);
	CString strMsg;
	strMsg.FormatV(Fmt, args);
	va_end(args);
	COLORREF col = IS_LIGHT_THEME ? BasicColors::black : BasicColors::white;
	LOG_MESSAGE(LOG_TARGET::BUILD_WINDOW, strMsg, col);
}

void LOG_OUTPUT_MESSAGE_ACTIVE_PANE(LPCTSTR lpszMsg, COLORREF col)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	if (pFrame)
	{
		pFrame->PrintMessage(LOG_TARGET::MESSAGE_WINDOW, lpszMsg, col);
		pFrame->ActiveDockPane(DOCKABLE_PANE_TYPE::LOG_MESSAGE_PANE);
	}
}

void LOG_BUILD_MESSAGE_ACTIVE_PANE(LPCTSTR lpszMsg, COLORREF col)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	if (pFrame)
	{
		pFrame->PrintMessage(LOG_TARGET::BUILD_WINDOW, lpszMsg, col);
		pFrame->ActiveDockPane(DOCKABLE_PANE_TYPE::BUILD_PANE);
	}
}

void LOG_MESSAGE_FROM_THREAD(LOG_TARGET target, CMainFrame* pFrame, LPCTSTR lpszMsg, COLORREF col, CDocument * pDoc)
{
	if (pFrame)
	{
		pFrame->PrintMessage(target, lpszMsg, col);
	}
}

int AfxMessageBoxFormat(int MB_ICON, const TCHAR * Fmt, ...)
{
	va_list args;
	va_start(args, Fmt);
	CString strMsg;
	strMsg.FormatV(Fmt, args);
	va_end(args);
	return AfxMessageBox(strMsg, MB_ICON);
}

CString AfxCStringFormat(const TCHAR * Fmt, ...)
{
	va_list args;
	va_start(args, Fmt);
	CString strMsg;
	strMsg.FormatV(Fmt, args);
	va_end(args);
	return strMsg;
}