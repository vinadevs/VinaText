/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

///////////////////////// MEMORY ALLOCATOR ////////////////////////////////////

#define DEFAULT_MEM_BLOCK_SIZE 1048576 // 1 Megabyte

class CFixedBlockMemoryAllocator
{
public:
	CFixedBlockMemoryAllocator(long lBlockMemorySize = DEFAULT_MEM_BLOCK_SIZE);
	~CFixedBlockMemoryAllocator();

	void* AllocNewMemory(long nBytes); // must be free from caller!!
	void  ClearMemory();

private:
	void  AddNewBlock();

	struct BLOCK_MEMORY
	{
		struct BLOCK_MEMORY* pNext;
		BLOCK_MEMORY() : pNext(nullptr) {}
	};

	BLOCK_MEMORY* m_pBlock;
	long m_lBlockSize;
	long m_lUsedSize;
};

////// DICTIONARY TRANSLATOR /////////////////////////////////

class CDictionaryPortableObject
{
public:
	CDictionaryPortableObject() {};
	~CDictionaryPortableObject();

	BOOL Load(CString const& strPath);
	const WCHAR *GetStringPO(const WCHAR *sz);
	
	struct KeyComparator
	{	
		bool operator()(const WCHAR* strLeft, const WCHAR* strRight) const		
		{	
			return _tcscmp(strLeft, strRight)<0;
		}	
	};
	typedef std::map<const WCHAR*, const WCHAR*, KeyComparator> DictPO;
private:
	DictPO m_DictPO;
	CFixedBlockMemoryAllocator m_FBMA;
};

////// DICTIONARY PORTABLE OBJECT FILE /////////////////////////////////

class CDictionaryPortableObjectFile
{
public:
	CDictionaryPortableObjectFile();
	~CDictionaryPortableObjectFile();
	struct POHeaderTable
	{
		unsigned int nLen, nString;
	};

	struct POHeader
	{
		unsigned int Magic, NumStrings;
		unsigned int OrigTable, TransTable;
	};

	static const unsigned int PO_MAGIC_SW = 0xde120495;
	static const unsigned int PO_MAGIC = 0x950412de;

	BOOL LoadPOFile(const CString& szName);
	void BuildPOHashTable(CDictionaryPortableObject::DictPO& hashTable, CFixedBlockMemoryAllocator* pFBMA);

private:
	BOOL GetFilePOData(LPCTSTR szName);
	char* StringAt(POHeaderTable*pTable, unsigned int n);
	wchar_t* Uft8ToUnicode(char* szU8, CFixedBlockMemoryAllocator* pAx);

	POHeaderTable* m_pOrigTable;
	POHeaderTable* m_pTransTable;
	unsigned int m_nSize;
	char *m_pData;
	unsigned int m_numStrings;
};
