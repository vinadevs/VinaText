//
//	UXReaderDestination.hpp
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderDestination final
	{
		private: // Variables
			int m_PageIndex = 0;

			double m_X = 0.0;
			double m_Y = 0.0;
			double m_Z = 0.0;

			bool m_HasX = false;
			bool m_HasY = false;
			bool m_HasZ = false;

		public: // Methods
			UXReaderDestination(void);
			UXReaderDestination(const int index, bool hasX, bool hasY, bool hasZ, double x, double y, double z);
			~UXReaderDestination(void);

			UXReaderDestination(const UXReaderDestination&) = default;
			UXReaderDestination& operator=(const UXReaderDestination&) = default;
			UXReaderDestination& operator=(UXReaderDestination&&) = default;
			UXReaderDestination(UXReaderDestination&&) = default;

			int PageIndex(void) const; int PageNumber(void) const;

			bool hasX(void) const; double X(void) const;
			bool hasY(void) const; double Y(void) const;
			bool hasZ(void) const; double Z(void) const;

			void Description(void) const;
	};
}
