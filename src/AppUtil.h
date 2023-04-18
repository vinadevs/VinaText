/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "STLHelper.h"
#include "AppSettings.h"

class CMainFrame;
class CVinaTextApp;
class CEditorDoc;
class CEditorCtrl;

//////////////////////////////////
// basic color

namespace BasicColors
{
	const COLORREF black = RGB(0, 0, 0);
	const COLORREF white = RGB(255, 255, 255);
	const COLORREF light_white = RGB(200, 200, 200);
	const COLORREF gray = RGB(128, 128, 128);
	const COLORREF green = RGB(0, 255, 0);
	const COLORREF light_green = RGB(47, 79, 79);
	const COLORREF red = RGB(255, 0, 0);
	const COLORREF orange = RGB(255, 69, 0);
	const COLORREF light_orange = RGB(253, 151, 31);
	const COLORREF blue = RGB(0, 0, 255);
	const COLORREF yellow = RGB(235, 245, 0);
}

//////////////////////////////////
// general utils

namespace AppUtils
{
	CString ColorToRGBCString(COLORREF color);
	COLORREF RGBCStringToColor(const CString& strRGBColor);
	CString IntToCString(int n);
	CString FloatToCString(float f);
	CString LongToCString(long l);
	int CStringToInt(CString str);
	long CStringToLong(CString str);
	float CStringToFloat(CString str);
	char* CopyCharArray(const char * orig);
	std::string  CStringToStd(CString cs);
	CString      StdToCString(std::string stdSt);
	std::wstring CStringToWStd(CString cs);
	CString DecimalToRomanNumerals(int nDecimalNumber);
	void BufferBYTE2String(BYTE* pBuffer, const unsigned int	pBufferSize, char**	pString);
	void String2BufferBYTE(const char* pString, BYTE** pBuffer, unsigned int* pBufferSize);
	CStringW UTF8_TO_UTF16(const CStringA & utf8);
	CStringA UTF16_TO_UTF8(const CStringW & utf16);
	std::string UTF8_TO_STD_STRING(const std::string & str);
	BOOL IsUTF8String(const char * string);
	const char * WideCharToCharAsCodePage(const wchar_t * wcharStr2Convert, UINT codepage, int lenIn = -1, int *pLenOut = NULL);
	CString		 WStdToCString(const std::wstring& stdSt);
	std::wstring StdToWStd(std::string stdSt);
	std::string WStdToStd(std::wstring stdSt);
	CString GetSubCStringBetweenTwoDemiliter(const CString & strTarget, const CString & strDelimitersStart, const CString & strDelimitersStop);
	void SplitCString(const CString& strFields, const CString& strDelimiters, CStringArray& arFields, BOOL bForceTrim = FALSE);
	void SplitCString(const CString& strFields, const CString& strDelimiters, std::list<CString>& arFields, BOOL bForceTrim = FALSE);
	void SplitCString(const CString& strFields, const CString& strDelimiters, std::vector<CString>& arFields); // recommend version
	std::wstring GetUnicodeWString(const std::string & multibyte, bool stopAtNull);
	void SetCurrentCodePage(unsigned int uiCodePage);
	unsigned int GetCurrentCodePage();
	CString ArrayCharToCString(const char * szText);
	CVinaTextApp* GetVinaTextApp();
	CMainFrame * GetMainFrame();
	CFrameWnd* GetActiveFrame();
	CDocument* GetMDIActiveDocument();
	CView* GetMDIActiveView();
	BOOL MDIActiveFrame();
	BOOL SetActiveDocument(CDocument* pDoc);
	void CloseAllPreviewDocument(PREVIEW_TYPE type);
	void CloseAllDocument();
	CDocument * GetNextPreviewDocument(PREVIEW_TYPE type);
	CDocument * GetExistedDocument(CString strFile);
	CDocument * GetDocumentFromTitle(const CString & strTitleDocument);;
	CDocument * CreateDocumentFromFile(const CString & strFile);
	CDocument * CreateNewPreviewDocument(const CString & strFile);
	CDocument * CreateDocumentCheckFileExistence(const CString & strFile);
	void CloseMDIDocument(CDocument * pDocTarget);
	void CloseDocumentByFilePath(CString strFile);
	void CloseDocumentByTitle(const CString& strTitle);
	void CloseDeletedDocument(CView * pCloseView, const CString& strFileDeleted);
	void CloseAllDocumentUnmodified();
	void CloseAllDocumentLeft(CView * pActiveView);
	void CloseAllDocumentRight(CView * pActiveView);
	void CloseAllDocumentButThis(CView * pActiveView);
	BOOL CanCloseAllDocumentLeft(CView * pActiveView);
	BOOL CanCloseAllDocumentRight(CView * pActiveView);
	void SaveAllModifiedDocuments();
	int GetModifiedDocumentCount();
	std::vector<CDocument*> GetAllDocuments();
	std::vector<CDocument*> GetAllDocumentTypes(DOCUMENT_TYPE type);
	std::vector<CEditorCtrl*> GetAllEditors();
	void ResizeAllViews();
	void SyncActionAllEditorDocuments(std::function<void(CEditorDoc* pDoc)> pFunctor, CEditorDoc* pExcludeDoc = NULL);
	BOOL IsDocumentExisted(CString strFile);
	int GetDocumentTypeCount(DOCUMENT_TYPE type);
	void CheckLastOpenDocument();
	void UpdateModifiedDocumentTitle(CDocument * pDoc, BOOL bAddMarker = TRUE);
	bool IsAlphaNumberString(const std::string & str);
	void ReplaceAllInStdString(std::string & str, const std::string & from, const std::string & to);
	void ReplaceAllInWStdString(std::wstring & str, const std::wstring & from, const std::wstring & to);
	std::wstring RemoveDuplicateWordInString(const std::wstring & str);
	std::wstring RemoveDuplicateMatchCaseWordInString(const std::wstring & str);
	void ToLowerCaseStd(std::string & str);
	CString ConvertDoubleToStringNumeric(double dValue, int uiWidth, int uiPrecision, DOUBLE_NUMERIC_TYPE nTYPE);
	std::vector<long> GetNumberListFromCString(char * str);
	BOOL IsXMLWhitespace(int ch);
	CString GetLanguageStringName(VINATEXT_SUPPORTED_LANGUAGE language);
	BOOL IsLanguageSupportDebugger(VINATEXT_SUPPORTED_LANGUAGE language);
	BOOL IsLanguageSupportErrorAnnotation(VINATEXT_SUPPORTED_LANGUAGE language);
	BOOL IsLanguageSupportLexer(VINATEXT_SUPPORTED_LANGUAGE language);
	std::vector<std::string> SplitterStdString(const std::string & str, const std::string & delimiter);
	std::vector<std::wstring> SplitterWStdString(const std::wstring & str, const std::wstring & delimiter);
	std::vector<CString> SplitterCString(const CString& str, const std::string& delimiter);
	int ReplaceFirstOf(CString & str, const CString& pszOld, const CString& pszNew);
	int FindFirstCharacterNotOf(CString str, CString strDelim);
	BOOL StringIsDigits(const std::wstring & str);
	BOOL StringIsInteger(const std::wstring & str);
	BOOL StringIsFloat(const std::wstring & str);
	BOOL IsCStringAllDigits(const CString & str);
	BOOL IsUrlHyperLink(const CString& strString);
	BOOL IsUrlHyperLink(TCHAR * text, int textLen, int start, int * segmentLen);
	CString RemoveJunkFromCString(const CString& strString);
	void ToTitleCase(std::wstring& str);
	void ToInvertCase(std::wstring& str);
	void ToRandomCase(std::wstring& str);
	BOOL TinyXML2Format(const CString& strFile);
	void CreateNewEditorWithText(const CString & strTitle, const CString & strText);
	CString GetFileTypeByExtension(const CString& strFileExt);
	CString GetFileFormatDescription(const CString& strFileExt);
	void UpdateSettingsForVinatext();
}

//////////////////////////////////
// GLOBAL API 
// DO NOT CALL BELOW LOG FUNCTIONS IN FOR LOOP!!!

void LOG_MESSAGE(LOG_TARGET target, LPCTSTR lpszMsg, COLORREF color);

void LOG_OUTPUT_MESSAGE_LAST_ERROR();

void LOG_OUTPUT_MESSAGE_COLOR(LPCTSTR lpszMsg, COLORREF color = IS_LIGHT_THEME ? BasicColors::black : BasicColors::white);

void LOG_OUTPUT_MESSAGE_FORMAT(const TCHAR * Fmt, ...);

void LOG_OUTPUT_MESSAGE_WITH_TIME(LPCTSTR lpszMsg, COLORREF color = IS_LIGHT_THEME ? BasicColors::black : BasicColors::white);

void LOG_BUILD_MESSAGE_COLOR(LPCTSTR lpszMsg, COLORREF color = IS_LIGHT_THEME ? BasicColors::black : BasicColors::white);

void LOG_BUILD_MESSAGE_FORMAT(const TCHAR * Fmt, ...);

// only use when log 1 time, for multi message use LOG_OUTPUT_MESSAGE
void LOG_OUTPUT_MESSAGE_ACTIVE_PANE(LPCTSTR lpszMsg, COLORREF color = IS_LIGHT_THEME ? BasicColors::black : BasicColors::white);

// only use when log 1 time, for multi message use LOG_BUILD_MESSAGE
void LOG_BUILD_MESSAGE_ACTIVE_PANE(LPCTSTR lpszMsg, COLORREF color = IS_LIGHT_THEME ? BasicColors::black : BasicColors::white);

// use for worker thread
void LOG_MESSAGE_FROM_THREAD(LOG_TARGET target, CMainFrame* pFrame, LPCTSTR lpszMsg, COLORREF color = IS_LIGHT_THEME ? BasicColors::black : BasicColors::white, CDocument* pDoc = NULL);

// Docking Window and Frames update
inline void UPDATE_MAIN_FRAME(UINT uiTarget, UINT uiHint, CDocument* pDoc = NULL)
{
	AfxGetMainWnd()->SendMessage(UMW_MAIN_FRAME_UPDATE, MAKEWPARAM(uiTarget, uiHint), (LPARAM)pDoc);
}

// View Update
inline void UPDATE_ALL_VIEWS(UINT uiTarget, UINT uiHint, CDocument* pDoc = NULL)
{
	if (pDoc == NULL) return;
	pDoc->UpdateAllViews(NULL, MAKEWPARAM(uiTarget, uiHint));
}

// helper message box
int AfxMessageBoxFormat(int MB_ICON, const TCHAR * Fmt, ...);

// helper CString format
CString AfxCStringFormat(const TCHAR * Fmt, ...);