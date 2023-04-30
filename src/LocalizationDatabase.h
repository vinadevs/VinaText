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

#pragma once

namespace Localization {

	///////////////////////// PERSISTENT ALLOCATOR ////////////////////////////////////

#define DEFAULT_MEM_BLOCK_SIZE 1048576 // 1 Megabyte
#define MINIMUM_MEM_BLOCK_SIZE 1024 // 1 Byte

	struct WcharComparator
	{
		bool operator()(const WCHAR* left, const WCHAR* right) const
		{
			return _tcscmp(left, right) < 0;
		}
	};

	using Dictionary = std::map<const WCHAR*, const WCHAR*, WcharComparator>;

	// https://www.codeproject.com/Articles/1083210/An-Efficient-Cplusplus-Fixed-Block-Memory-Allocator
	class PersistentMemory
	{
	public:
		PersistentMemory(long size = DEFAULT_MEM_BLOCK_SIZE);
		~PersistentMemory();

		void* RequestNewMemory(long nBytes); // must be free from caller!!
		void  ReleaseMemory();

	private:
		void  AddNewBlock();

		struct BLOCK_MEMORY
		{
			struct BLOCK_MEMORY* pNextBlock = nullptr;
			BLOCK_MEMORY() : pNextBlock(nullptr) {}
		};

		BLOCK_MEMORY* m_pBlockMemory{ nullptr };
		long m_lSize{0};
		long m_lUsed{0};
	};

	////// LOCALIZATION DATA /////////////////////////////////

	class LocalizationDatabase
	{
	public:
		LocalizationDatabase();
		~LocalizationDatabase();

		BOOL Load(CString const& strPath);
		const WCHAR* GetStringPO(const WCHAR* sz);


	private:
		Dictionary m_Dictionary;
		PersistentMemory m_Memory;
	};

	////// DICTIONARY PORTABLE OBJECT FILE /////////////////////////////////

	class LocalizationDatabaseFile
	{
	public:
		LocalizationDatabaseFile() {};
		~LocalizationDatabaseFile() {};
		struct HeaderTable
		{
			unsigned int uiLenth{ 0 }, uiStrings{ 0 };
		};

		struct LocalizationHeader
		{
			unsigned int uiMagic{ 0 }, uiNumStrings{ 0 };
			unsigned int uiOrigTable{ 0 }, uiTransTable{ 0 };
		};

		static const unsigned int LOCALIZATION_MAGIC = 0x950412de;

		BOOL LoadLocalization(const CString& szName);
		void CreateLocalizationDictionary(Dictionary& dict, PersistentMemory* memory);

	private:
		BOOL GetLocalizationData(LPCTSTR szName);
		char* GetTranlsatedString(HeaderTable* pTable, unsigned int n);

		HeaderTable* m_pOrigTable{ nullptr };
		HeaderTable* m_pTransTable{ nullptr };
		std::unique_ptr<char> m_pLocalDatabaseData{ nullptr };
		unsigned int m_uiNumStrings{ 0 };
		unsigned int m_uiSize{ 0 };
	};

} // namespace AppTranslator