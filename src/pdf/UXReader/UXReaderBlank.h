//
//	UXReaderBlank.hpp
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderBlank final
	{
		private: // Variables

		public: // Methods
			UXReaderBlank(void) {};
			~UXReaderBlank(void) {};

			UXReaderBlank(const UXReaderBlank&) = delete;
			UXReaderBlank& operator=(const UXReaderBlank&) = delete;
			UXReaderBlank& operator=(UXReaderBlank&&) = delete;
			UXReaderBlank(UXReaderBlank&&) = delete;

		private: // Methods
	};
}
