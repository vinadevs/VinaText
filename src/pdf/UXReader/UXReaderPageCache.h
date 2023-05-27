//
//	UXReaderPageCache.hpp
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderPageCache final
	{
		private: // Variables
			size_t m_PageCacheSizeLimit = 4194304;
			std::map<int, HBITMAP> m_PageBitmapCache;
			std::vector<int> m_PageBitmapQueue;

		public: // Methods
			UXReaderPageCache(const size_t limit);
			~UXReaderPageCache(void);

			UXReaderPageCache(void) = delete;
			UXReaderPageCache(const UXReaderPageCache&) = delete;
			UXReaderPageCache& operator=(const UXReaderPageCache&) = delete;
			UXReaderPageCache& operator=(UXReaderPageCache&&) = delete;
			UXReaderPageCache(UXReaderPageCache&&) = delete;

			void PurgePageBitmapCache(void);
			void PrunePageBitmapCache(void);
			void PurgeNotVisiblePages(const std::set<int>& visiblePages);
			void CachePageBitmap(const int index, const HBITMAP hBitmap);
			HBITMAP CachedPageBitmap(const int index);

		private: // Methods
			void RemovePageFromQueue(const int index);
			void MovePageToBackOfQueue(const int index);
			void PurgePageBitmap(const int index);
	};
}
