//
//	UXReaderGeometry.cpp
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderGeometry.h"

using namespace UXReader;

void UXReader::UXRect::printwh(void) const
{
	DBLog(L"%S x:%g y:%g w:%g h:%g\n", __FUNCSIG__, xd(), yd(), wd(), hd());
}

void UXReader::UXRect::printxy(void) const
{
	DBLog(L"%S x1:%g y1:%g x2:%g y2:%g\n", __FUNCSIG__, x1, y1, x2, y2);
}

//
//	Convert methods
//

UXRect UXReader::ConvertToPageFromView(const UXRect& rect, const UXPageSize& size, const int r)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXRect result(rect);

	const double pw = size.w;
	const double ph = size.h;

	switch (r)
	{
		case 0: // 0 degrees
		{
			const UXMatrix t = {1.0, 0.0, 0.0, -1.0, 0.0, ph};
			result = rect.transform(t);
			break;
		}

		case 1: // 90 degrees
		{
			const UXMatrix t = {0.0, 1.0, 1.0, 0.0, 0.0, 0.0};
			result = rect.transform(t);
			break;
		}

		case 2: // 180 degrees
		{
			const UXMatrix t = {-1.0, 0.0, 0.0, 1.0, pw, 0.0};
			result = rect.transform(t);
			break;
		}

		case 3: // 270 degrees
		{
			const UXMatrix t = {0.0, -1.0, -1.0, 0.0, ph, pw};
			result = rect.transform(t);
			break;
		}
	}

	return result;
}

UXPoint UXReader::ConvertToPageFromView(const UXPoint& point, const UXPageSize& size, const int r)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXPoint result(point);

	const double pw = size.w;
	const double ph = size.h;

	switch (r)
	{
		case 0: // 0 degrees
		{
			const UXMatrix t = {1.0, 0.0, 0.0, -1.0, 0.0, ph};
			result = point.transform(t);
			break;
		}

		case 1: // 90 degrees
		{
			const UXMatrix t = {0.0, 1.0, 1.0, 0.0, 0.0, 0.0};
			result = point.transform(t);
			break;
		}

		case 2: // 180 degrees
		{
			const UXMatrix t = {-1.0, 0.0, 0.0, 1.0, pw, 0.0};
			result = point.transform(t);
			break;
		}

		case 3: // 270 degrees
		{
			const UXMatrix t = {0.0, -1.0, -1.0, 0.0, ph, pw};
			result = point.transform(t);
			break;
		}
	}

	return result;
}

UXRect UXReader::ConvertToViewFromPage(const UXRect& rect, const UXPageSize& size, const int r)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXRect result(rect);

	const double pw = size.w;
	const double ph = size.h;

	switch (r)
	{
		case 0: // 0 degrees
		{
			const UXMatrix t = {1.0, 0.0, 0.0, -1.0, 0.0, ph};
			result = rect.transform(t);
			break;
		}

		case 1: // 90 degrees
		{
			const UXMatrix t = {0.0, 1.0, 1.0, 0.0, 0.0, 0.0};
			result = rect.transform(t);
			break;
		}

		case 2: // 180 degrees
		{
			const UXMatrix t = {-1.0, 0.0, 0.0, 1.0, pw, 0.0};
			result = rect.transform(t);
			break;
		}

		case 3: // 270 degrees
		{
			const UXMatrix t = {0.0, -1.0, -1.0, 0.0, pw, ph};
			result = rect.transform(t);
			break;
		}
	}

	return result;
}

UXPoint UXReader::ConvertToViewFromPage(const UXPoint& point, const UXPageSize& size, const int r)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	UXPoint result(point);

	const double pw = size.w;
	const double ph = size.h;

	switch (r)
	{
		case 0: // 0 degrees
		{
			const UXMatrix t = {1.0, 0.0, 0.0, -1.0, 0.0, ph};
			result = point.transform(t);
			break;
		}

		case 1: // 90 degrees
		{
			const UXMatrix t = {0.0, 1.0, 1.0, 0.0, 0.0, 0.0};
			result = point.transform(t);
			break;
		}

		case 2: // 180 degrees
		{
			const UXMatrix t = {-1.0, 0.0, 0.0, 1.0, pw, 0.0};
			result = point.transform(t);
			break;
		}

		case 3: // 270 degrees
		{
			const UXMatrix t = {0.0, -1.0, -1.0, 0.0, pw, ph};
			result = point.transform(t);
			break;
		}
	}

	return result;
}

void UXReader::ConvertToViewFromPage(bool bX, bool bY, float& x, float& y, const UXPageSize& size, const int r)
{
	//DBLog(L"%S\n", __FUNCSIG__);

	if (bX || bY)
	{
		UXPoint point(x, y);

		const double pw = size.w;
		const double ph = size.h;

		switch (r)
		{
			case 0: // 0 degrees
			{
				const UXMatrix t = {1.0, 0.0, 0.0, -1.0, 0.0, ph};
				point = point.transform(t);
				break;
			}

			case 1: // 90 degrees
			{
				const UXMatrix t = {0.0, 1.0, 1.0, 0.0, 0.0, 0.0};
				point = point.transform(t);
				break;
			}

			case 2: // 180 degrees
			{
				const UXMatrix t = {-1.0, 0.0, 0.0, 1.0, pw, 0.0};
				point = point.transform(t);
				break;
			}

			case 3: // 270 degrees
			{
				const UXMatrix t = {0.0, -1.0, -1.0, 0.0, pw, ph};
				point = point.transform(t);
				break;
			}
		}

		if (bX) x = float(point.x);
		if (bY) y = float(point.y);
	}
}
