//
//	UXReaderDataSource.hpp
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderDataSource
	{
		public: // Methods
			UXReaderDataSource(void);
			UXReaderDataSource(const UXReaderDataSource&) = default;
			UXReaderDataSource& operator=(const UXReaderDataSource&) = default;
			UXReaderDataSource& operator=(UXReaderDataSource&&) = default;
			UXReaderDataSource(UXReaderDataSource&&) = default;
			virtual ~UXReaderDataSource(void);

			virtual bool GetDataBlock(const size_t offset, const size_t size, const void *buffer) = 0;
			virtual size_t DataLength(void) = 0;
	};
}
