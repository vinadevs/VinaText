//
//	UXReaderPageCache.cpp
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderPageCache.h"

using namespace UXReader;

//
//	UXReaderPageCache methods
//

UXReader::UXReaderPageCache::UXReaderPageCache(const size_t limit)
{
	//DBLog(L"%S 0x%p %zu\n", __FUNCSIG__, this, limit);

	if (limit > m_PageCacheSizeLimit) m_PageCacheSizeLimit = limit;
}

UXReader::UXReaderPageCache::~UXReaderPageCache(void)
{
	//DBLog(L"%S 0x%p\n", __FUNCSIG__, this);

	for (const auto& item : m_PageBitmapCache) DeleteObject(item.second);

	//DBLog(L"%S 0x%p\n", __FUNCSIG__, this);
}

void UXReader::UXReaderPageCache::RemovePageFromQueue(const int index)
{
	//DBLog(L"%S %i\n", __FUNCSIG__, index);

	if (m_PageBitmapQueue.empty() == true) return;

	for (auto it = m_PageBitmapQueue.begin(); it != m_PageBitmapQueue.end();)
	{
		if (*it == index) it = m_PageBitmapQueue.erase(it); else ++it;
	}
}

void UXReader::UXReaderPageCache::MovePageToBackOfQueue(const int index)
{
	//DBLog(L"%S %i\n", __FUNCSIG__, index);

	if (m_PageBitmapQueue.empty() == true) return;

	if (index != m_PageBitmapQueue.back()) // Move to back of queue
	{
		RemovePageFromQueue(index); m_PageBitmapQueue.push_back(index);
	}
}

void UXReader::UXReaderPageCache::PurgePageBitmap(const int index)
{
	//DBLog(L"%S %i\n", __FUNCSIG__, index);

	if (m_PageBitmapCache.empty() == true) return;

	const auto it = m_PageBitmapCache.find(index);

	if (it != m_PageBitmapCache.end()) // Purge page bitmap
	{
		//DBLog(L"%S %i\n", __FUNCSIG__, it->first);

		DeleteObject(it->second); m_PageBitmapCache.erase(it);

		RemovePageFromQueue(index);
	}
}

void UXReader::UXReaderPageCache::PurgePageBitmapCache(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (m_PageBitmapCache.empty() == true) return;

	for (const auto& item : m_PageBitmapCache) DeleteObject(item.second);

	m_PageBitmapCache.clear(); m_PageBitmapQueue.clear();
}

void UXReader::UXReaderPageCache::PrunePageBitmapCache(void)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (m_PageBitmapCache.empty() == true) return;

	size_t pageCacheSize = 0; // Total byte size

	for (const auto& item : m_PageBitmapCache)
	{
		BITMAP bm; RtlSecureZeroMemory(&bm, sizeof(bm));

		if (GetObjectW(item.second, sizeof(bm), &bm) != 0)
		{
			pageCacheSize += (bm.bmWidth * bm.bmHeight * 4);
		}
	}

	while (pageCacheSize > m_PageCacheSizeLimit)
	{
		if (m_PageBitmapQueue.empty() == true) break;

		const int index = m_PageBitmapQueue.front();

		if (const HBITMAP hBitmap = CachedPageBitmap(index))
		{
			BITMAP bm; RtlSecureZeroMemory(&bm, sizeof(bm));

			if (GetObjectW(hBitmap, sizeof(bm), &bm) != 0)
			{
				pageCacheSize -= (bm.bmWidth * bm.bmHeight * 4);
			}

			//DBLog(L"%S %i\n", __FUNCSIG__, index);

			PurgePageBitmap(index);
		}
		else // On error
		{
			break;
		}
	}
}

void UXReader::UXReaderPageCache::PurgeNotVisiblePages(const std::set<int>& visiblePages)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (m_PageBitmapCache.empty() == true) return;

	for (auto it1 = m_PageBitmapCache.begin(); it1 != m_PageBitmapCache.end();)
	{
		const auto it2 = visiblePages.find(it1->first); // Check set

		if (it2 == visiblePages.end()) // Page is not visible
		{
			//DBLog(L"%S %i\n", __FUNCSIG__, it1->first);

			RemovePageFromQueue(it1->first); DeleteObject(it1->second);

			it1 = m_PageBitmapCache.erase(it1);
		}
		else // Page is visible
		{
			++it1;
		}
	}
}

void UXReader::UXReaderPageCache::CachePageBitmap(const int index, const HBITMAP hBitmap)
{
	//DBLog(L"%S %i 0x%p\n", __FUNCSIG__, index, hBitmap);

	m_PageBitmapCache.emplace(index, hBitmap); m_PageBitmapQueue.push_back(index);
}

HBITMAP UXReader::UXReaderPageCache::CachedPageBitmap(const int index)
{
	//DBLog(L"%S %i\n", __FUNCSIG__, index);

	HBITMAP hBitmap = nullptr; // Cached page bitmap

	const auto it = m_PageBitmapCache.find(index);

	if (it != m_PageBitmapCache.end())
	{
		MovePageToBackOfQueue(index);

		hBitmap = it->second;
	}

	return hBitmap;
}
