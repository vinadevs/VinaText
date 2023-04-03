/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "CodePageMFC.h"

// Initialize static variables
CCriticalSection CCodePage::CCodePageObject::s_critSec;
CCodePage::CCodePageObject* CCodePage::CCodePageObject::s_pCurrent = NULL;

// Return the number of available code pages
int CCodePage::CCodePageObject::GetCount() const
{
	return static_cast<int>(s_arrCodePages.GetSize());
}

// Return a code page at a specific index
int CCodePage::CCodePageObject::operator[](int nIndex) const
{
	return s_arrCodePages[nIndex];
}

// Returns true if the code page container is empty
bool CCodePage::CCodePageObject::IsEmpty() const
{
	return s_arrCodePages.GetSize() == 0;
}

// Add a new code page to the container
void CCodePage::CCodePageObject::Add(UINT nCodePage)
{
	s_arrCodePages.Add(nCodePage);
}

// Return the name of a code page at a specific index in the container
CString CCodePage::CCodePageObject::GetName(int nIndex) const
{
#if (WINVER >= 0x410)
	CPINFOEX cpInfoEx = { 0 };
	GetCPInfoEx(s_arrCodePages[nIndex], 0, &cpInfoEx);
	return cpInfoEx.CodePageName;
#else
	// GetCPInfoEx not supported on 95/NT4
	return _T("");
#endif
}

// Enumerate code pages using specific flags
void CCodePage::CCodePageObject::EnumerateCodePages(CCodePageObject* pObject)
{
	ASSERT(pObject != NULL);
	// Lock access to this function to ensure thread safety
	CSingleLock lock(&s_critSec, TRUE);
	s_pCurrent = pObject;
	::EnumSystemCodePages(EnumCodePagesProc, pObject->GetFlags());
}

// EnumSystemCodePages callback function
BOOL CALLBACK CCodePage::CCodePageObject::EnumCodePagesProc(LPTSTR lpCodePageString)
{
	ASSERT(s_pCurrent != NULL);
	// Format the code page string as an unsigned int
	// and add to the current code page object
	s_pCurrent->Add(_ttoi(lpCodePageString));
	return TRUE;
}

// Get the installed code pages
const CCodePage::CCodePageObject& CCodePage::GetInstalled()
{
	if (m_cpInstalled.IsEmpty())
		CCodePageObject::EnumerateCodePages(&m_cpInstalled);
	return m_cpInstalled;
}

// Get the supported code pages
const CCodePage::CCodePageObject& CCodePage::GetSupported()
{
	if (m_cpSupported.IsEmpty())
		CCodePageObject::EnumerateCodePages(&m_cpSupported);
	return m_cpSupported;
}
