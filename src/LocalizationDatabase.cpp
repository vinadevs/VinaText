/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

//This code customize Localization library from Nikolay Raspopov

/*
This file is part of Localization library
https://sourceforge.net/projects/po-localization/

Copyright (C) 2011-2015 Nikolay Raspopov <raspopov@cherubicsoft.com>

This program is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
( at your option ) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see < http://www.gnu.org/licenses/>.
*/

#include "stdafx.h"
#include "LocalizationDatabase.h"

using namespace Localization;

// https://www.codeproject.com/Articles/1083210/An-Efficient-Cplusplus-Fixed-Block-Memory-Allocator
///////////////////////// PERSISTENT MEMORY ////////////////////////////////////

PersistentMemory::PersistentMemory(long size)
{
	ASSERT(size >= MINIMUM_MEM_BLOCK_SIZE); // minimum is 1 BYTE
	m_lSize = size;
}

PersistentMemory::~PersistentMemory()
{
	ReleaseMemory(); // RAII model...
}

void* PersistentMemory::RequestNewMemory(long nBytes)
{
	// first check if remain memory in block (1MB) is avalable...
	if (nBytes > (m_lSize - m_lUsed) || m_pBlockMemory == nullptr)
	{
		AddNewBlock();
	}
	void* pMemory = (char*)m_pBlockMemory + m_lUsed;
	m_lUsed += nBytes;
	return pMemory;
}

void PersistentMemory::ReleaseMemory()
{
	BLOCK_MEMORY* pHead = m_pBlockMemory;
	BLOCK_MEMORY* pNext = 0;
	while (pHead)
	{
		pNext = pHead->pNextBlock;
		delete[](char*)pHead;
		pHead = pNext;
	}
	m_pBlockMemory = nullptr;
	m_lUsed = 0;
}

void PersistentMemory::AddNewBlock()
{
	char* pMemory = new char[m_lSize];
	BLOCK_MEMORY* pBlock = reinterpret_cast<BLOCK_MEMORY*>(pMemory);
	pBlock->pNextBlock = m_pBlockMemory;
	m_pBlockMemory = pBlock;
	m_lUsed = sizeof(BLOCK_MEMORY);
}

////// LOCALIZATION DATA /////////////////////////////////

LocalizationDatabase::LocalizationDatabase() {}

LocalizationDatabase::~LocalizationDatabase()
{
	m_Dictionary.clear();
}

BOOL LocalizationDatabase::Load(CString const& strPath)
{
	LocalizationDatabaseFile file;
	if(!file.LoadLocalization(strPath)) return FALSE;
	file.CreateLocalizationDictionary(m_Dictionary, &m_Memory);
	return TRUE;
}

const WCHAR* LocalizationDatabase::GetStringPO(const WCHAR *sz)
{
	const auto itr = m_Dictionary.find(sz);
	if(itr != m_Dictionary.end()) return itr->second;
	else return NULL;
}

////// LOCALIZATION DATA /////////////////////////////////

char *LocalizationDatabaseFile::GetTranlsatedString(LocalizationDatabaseFile::HeaderTable *pTable, unsigned int n)
{
	const HeaderTable * const ent = pTable + n;
	unsigned int String = ent->uiStrings;
	if ( String + ent->uiLenth > m_uiSize)
	{
		return nullptr;
	}
	return (m_pLocalDatabaseData.get() + String);
}

BOOL LocalizationDatabaseFile::LoadLocalization(const CString& szName)
{
	if(!GetLocalizationData(szName))
		return FALSE;
	bool bValid = m_uiSize > sizeof(LocalizationHeader);
	LocalizationHeader *pHeader = (LocalizationHeader*)m_pLocalDatabaseData.get();
	if(!bValid || pHeader == nullptr)
		return FALSE;
	if(pHeader->uiMagic != LOCALIZATION_MAGIC)
		return FALSE;	
	m_uiNumStrings = pHeader->uiNumStrings;
	m_pOrigTable  = reinterpret_cast <HeaderTable*>((m_pLocalDatabaseData.get() + pHeader->uiOrigTable));
	m_pTransTable = reinterpret_cast <HeaderTable*>((m_pLocalDatabaseData.get() + pHeader->uiTransTable));
	return TRUE;
}

void LocalizationDatabaseFile::CreateLocalizationDictionary(Dictionary& dictTable, PersistentMemory* memory)
{
	auto fCharToUnicode = [](char* rawData, PersistentMemory* pAx) -> WCHAR* {
		if (rawData == nullptr)
		return nullptr;
		int len = (int)strlen(rawData);
		int wcsLen = MultiByteToWideChar(CP_UTF8, 0, rawData, len, nullptr, 0);
		WCHAR* wszString = (WCHAR*)pAx->RequestNewMemory(sizeof(WCHAR) * (wcsLen + 1));
		MultiByteToWideChar(CP_UTF8, 0, rawData, len, wszString, wcsLen);
		wszString[wcsLen] = '\0';
		return wszString;
	};

	WCHAR* strEnglish = nullptr;
	WCHAR* strTranslation = nullptr;
	char *pRow = nullptr;
	for (unsigned int i = 0; i < m_uiNumStrings; i++)
    {
		pRow = GetTranlsatedString(m_pOrigTable, i);
		strEnglish = fCharToUnicode(pRow, memory);
		pRow = GetTranlsatedString(m_pTransTable, i);
		strTranslation = fCharToUnicode(pRow, memory);
		dictTable[strEnglish] = strTranslation;
    }
}

BOOL LocalizationDatabaseFile::GetLocalizationData(LPCTSTR szName)
{
	if(szName == nullptr)
		return FALSE;
	BOOL bResult = FALSE;
	DWORD blockSize = 0;
	HANDLE hFile = CreateFile(szName, GENERIC_READ,FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if(hFile == INVALID_HANDLE_VALUE)
		return FALSE;	
	m_uiSize = GetFileSize(hFile, nullptr);
	if(m_uiSize > 0)
	{
		m_pLocalDatabaseData.reset();
		m_pLocalDatabaseData = std::make_unique<char>(m_uiSize);
		ReadFile(hFile,m_pLocalDatabaseData.get(), m_uiSize, &blockSize, nullptr);
		bResult = (m_uiSize == blockSize);
	}
	CloseHandle(hFile);
	return bResult;
}