//
//	UXReaderSelection.hpp
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderSelection final
	{
		private: // Variables
			std::vector<UXRect> m_Rectangles;

			int m_PageIndex = 0; int m_CharIndex = 0; int m_CharCount = 0; int m_Selection = 0;

		public: // Methods
			UXReaderSelection(const int pageIndex, const int charIndex, const int charCount, const std::vector<UXRect>& rectangles, const int selection);
			~UXReaderSelection(void);

			UXReaderSelection(void) = delete;
			UXReaderSelection(const UXReaderSelection&) = default;
			UXReaderSelection& operator=(const UXReaderSelection&) = default;
			UXReaderSelection& operator=(UXReaderSelection&&) = delete;
			//UXReaderSelection(UXReaderSelection&&) = delete;

			const std::vector<UXRect> Rectangles(void) const;

			int PageIndex(void) const;
			int CharIndex(void) const;
			int CharCount(void) const;
			int Selection(void) const;

			void Description(void) const;
	};
}
