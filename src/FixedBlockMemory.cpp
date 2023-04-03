/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of The300 Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "StdAfx.h"
#include "FixedBlockMemory.h"

CFBMAllocator::CFBMAllocator(long lBlockMemorySize)
{
	ASSERT(lBlockMemorySize >= 1024); // minimum is 1024
	m_lBlockSize = lBlockMemorySize;
	m_pBlock = NULL;
	m_lUsedSize = 0;
}

CFBMAllocator::~CFBMAllocator(void)
{
	ClearMemory(); // RAII model...
}

void* CFBMAllocator::AllocNewMemory(long nBytes)
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

void CFBMAllocator::ClearMemory()
{
	BLOCK_MEMORY* pBlock = m_pBlock;
	BLOCK_MEMORY* pBlockNext = 0;
	while (pBlock)
	{
		pBlockNext = pBlock->pNext;
		delete[] (char*)pBlock;
		pBlock = pBlockNext;
	}
	m_pBlock = NULL;
	m_lUsedSize = 0;
}

void CFBMAllocator::AddNewBlock()
{
	char* pMemory = new char[m_lBlockSize];
	BLOCK_MEMORY* pBlock = (BLOCK_MEMORY*)pMemory;
	pBlock->pNext = m_pBlock;
	m_pBlock = pBlock;
	m_lUsedSize = sizeof(BLOCK_MEMORY);
}