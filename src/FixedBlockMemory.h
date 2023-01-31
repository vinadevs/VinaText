/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of The300 Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

// A fixed block memory allocator that increases system performance
// and offers heap fragmentation fault protection

#pragma once

#define DEFAULT_BLOCK_SIZE 1048576 // 1 Mbyte

class CFBMAllocator
{
public:
	CFBMAllocator(long lBlockMemorySize = DEFAULT_BLOCK_SIZE);
	~CFBMAllocator(void);

	void* AllocNewMemory(long nBytes);
	void  ClearMemory();

protected:
	void  AddNewBlock();

protected:
	typedef struct BLOCK_MEMORY_T
	{
		struct BLOCK_MEMORY_T* pNext;
		BLOCK_MEMORY_T() : pNext(NULL) {}
	}BLOCK_MEMORY;
	BLOCK_MEMORY* m_pBlock;
	long m_lBlockSize;
	long m_lUsedSize;
};

