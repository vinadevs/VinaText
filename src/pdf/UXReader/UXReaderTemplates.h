//
//	UXReaderTemplates.hpp
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderTemplates final
	{
		private: // Variables

		public: // Methods
			UXReaderTemplates(void);
			~UXReaderTemplates(void);

			UXReaderTemplates(const UXReaderTemplates&) = delete;
			UXReaderTemplates& operator=(const UXReaderTemplates&) = delete;
			UXReaderTemplates& operator=(UXReaderTemplates&&) = delete;
			UXReaderTemplates(UXReaderTemplates&&) = delete;

		private: // Methods
	};
}

template<typename T> class UXRectZ
{
	private:
		T x_1, y_1;
		T x_2, y_2;

	public:
		UXRectZ(void) : x_1(0), y_1(0), x_2(0), y_2(0) {}

		UXRectZ(T x1, T y1, T x2, T y2) : x_1(x1), y_1(y1), x_2(x2), y_2(y2) {}

		inline T x1(void) { return x_1; }
		inline T y1(void) { return y_1; }
		inline T x2(void) { return x_2; }
		inline T y2(void) { return y_2; }

		inline T x(void) { return x_1; }
		inline T y(void) { return y_1; }
		inline T w(void) { return (x_2 - x_1); }
		inline T h(void) { return (y_2 - y_1); }

		inline bool contains(T x, T y) const
		{
			return ((x >= x_1) && (x <= x_2) && (y >= y_1) && (y <= y_2));
		}
};
