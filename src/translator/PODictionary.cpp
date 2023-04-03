/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "PODictionary.h"

///////////////////////// MEMORY ALLOCATOR ////////////////////////////////////

CFixedBlockMemoryAllocator::CFixedBlockMemoryAllocator(long lBlockMemorySize)
{
	ASSERT(lBlockMemorySize >= 1024); // minimum is 1024
	m_lBlockSize = lBlockMemorySize;
	m_pBlock = NULL;
	m_lUsedSize = 0;
}

CFixedBlockMemoryAllocator::~CFixedBlockMemoryAllocator()
{
	ClearMemory(); // RAII model...
}

void* CFixedBlockMemoryAllocator::AllocNewMemory(long nBytes)
{
	// first check if remain memory in block (1MB) is avalable...
	if (nBytes > (m_lBlockSize - m_lUsedSize) || m_pBlock == NULL)
	{
		AddNewBlock();
	}
	void* pMemory = (char*)m_pBlock + m_lUsedSize;
	m_lUsedSize += nBytes;
	return pMemory;
}

void CFixedBlockMemoryAllocator::ClearMemory()
{
	BLOCK_MEMORY* pBlock = m_pBlock;
	BLOCK_MEMORY* pBlockNext = 0;
	while (pBlock)
	{
		pBlockNext = pBlock->pNext;
		delete[](char*)pBlock;
		pBlock = pBlockNext;
	}
	m_pBlock = NULL;
	m_lUsedSize = 0;
}

void CFixedBlockMemoryAllocator::AddNewBlock()
{
	char* pMemory = new char[m_lBlockSize];
	BLOCK_MEMORY* pBlock = (BLOCK_MEMORY*)pMemory;
	pBlock->pNext = m_pBlock;
	m_pBlock = pBlock;
	m_lUsedSize = sizeof(BLOCK_MEMORY);
}

/////////////////////////////////////////////////////////////

CDictionaryPortableObject::~CDictionaryPortableObject()
{
	m_DictPO.clear();
}

BOOL CDictionaryPortableObject::Load(CString const& strPath)
{
	CDictionaryPortableObjectFile file;
	if(!file.LoadPOFile(strPath)) return FALSE;
	file.BuildPOHashTable(m_DictPO, &m_FBMA);
	return TRUE;
}

const WCHAR* CDictionaryPortableObject::GetStringPO(const WCHAR *sz)
{
	const auto itr = m_DictPO.find(sz);
	if(itr != m_DictPO.end()) return itr->second;
	else return NULL;
}

/////////////////////////////////////////////////////////////

CDictionaryPortableObjectFile::CDictionaryPortableObjectFile()
{
	m_nSize = 0;
	m_pData = NULL;
	m_pOrigTable = m_pTransTable = NULL;
	m_numStrings = 0;
}

CDictionaryPortableObjectFile::~CDictionaryPortableObjectFile()
{
	if(m_pData != NULL)
	{
		delete[] m_pData;
	}
}

wchar_t* CDictionaryPortableObjectFile::Uft8ToUnicode(char* szU8, CFixedBlockMemoryAllocator* pAx)
{
	if(szU8 == NULL)
		return NULL;	
	int len = (int)strlen(szU8);
    int wcsLen = MultiByteToWideChar(CP_UTF8, NULL, szU8, len, NULL, 0);	
    wchar_t* wszString = (wchar_t *)pAx->AllocNewMemory(sizeof(wchar_t)*(wcsLen+1));
    MultiByteToWideChar(CP_UTF8, NULL, szU8, len, wszString, wcsLen);	
    wszString[wcsLen] = '\0';
	return wszString;
}

char *CDictionaryPortableObjectFile::StringAt(CDictionaryPortableObjectFile::POHeaderTable *pTable, unsigned int n)
{
	const POHeaderTable * const ent = pTable + n;
	unsigned int String = ent->nString;
	if ( String + ent->nLen > m_nSize)
	{
		return NULL;
	}
	return (m_pData + String);
}

BOOL CDictionaryPortableObjectFile::LoadPOFile(const CString& szName)
{
	if(!GetFilePOData(szName))
		return FALSE;

	bool bValid = m_nSize > sizeof(POHeader);
	POHeader *pHeader = (POHeader*)m_pData;

	if(!bValid || pHeader==NULL)
		return FALSE;

	if(pHeader->Magic != PO_MAGIC)
		return FALSE;
	
	m_numStrings = pHeader->NumStrings;
	m_pOrigTable  = (POHeaderTable *)(m_pData + pHeader->OrigTable);
	m_pTransTable = (POHeaderTable *)(m_pData + pHeader->TransTable);

	return TRUE;
}

void CDictionaryPortableObjectFile::BuildPOHashTable(CDictionaryPortableObject::DictPO& hashTable, CFixedBlockMemoryAllocator* pFBMA)
{
	wchar_t* strKey;
	wchar_t* strValue;
	char *data;
	for (unsigned int i = 0; i < m_numStrings; i++)
    {
        data = StringAt(m_pOrigTable, i);
		strKey = Uft8ToUnicode(data, pFBMA);
		data = StringAt(m_pTransTable, i);
		strValue = Uft8ToUnicode(data, pFBMA);
		hashTable[strKey] = strValue;
    }
}

BOOL CDictionaryPortableObjectFile::GetFilePOData(LPCTSTR szName)
{
	if(szName == NULL)
		return FALSE;

	bool bRet = FALSE;
	DWORD nReadSize = 0;
	HANDLE hFile = CreateFile(szName, GENERIC_READ,FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		return FALSE;
		
	m_nSize = GetFileSize(hFile,NULL);
	if(m_nSize > 0)
	{
		delete[] m_pData;
		m_pData = new char[m_nSize];
		ReadFile(hFile,m_pData,m_nSize,&nReadSize,NULL);
		bRet = (m_nSize==nReadSize);
	}
	CloseHandle(hFile);

	return bRet;
}