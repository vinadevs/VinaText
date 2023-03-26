//
//	UXReaderGeometry.hpp
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	struct UXMatrix final
	{
		double a, b, c, d;
		double tx, ty;
	};

	struct UXPoint final
	{
		double x, y;

		UXPoint(void) : x(0.0), y(0.0) {}

		UXPoint(double x, double y) : x(x), y(y) {}

		inline UXPoint translate(const double dx, const double dy) const
		{
			UXPoint point((x + dx), (y + dy));

			return point;
		}

		inline UXPoint transform(const UXMatrix& t) const
		{
			UXPoint point; // Transformed

			point.x = ((t.a * x) + (t.c * y) + t.tx);
			point.y = ((t.b * x) + (t.d * y) + t.ty);

			return point;
		}
	};

	struct UXSize final
	{
		double w, h;

		UXSize(void) : w(0.0), h(0.0) {}

		UXSize(double w, double h) : w(w), h(h) {}

		inline bool empty(void) const
		{
			return ((w == 0.0) || (h == 0.0));
		}
	};

	struct UXPageSize final
	{
		float w, h;

		UXPageSize(void) : w(0.0f), h(0.0f) {}

		UXPageSize(double w, double h) : w(float(w)), h(float(h)) {}

		UXPageSize(float w, float h) : w(w), h(h) {}

		inline bool empty(void) const
		{
			return ((w == 0.0f) || (h == 0.0f));
		}
	};

	class UXRect final
	{
		private: // Variables
			double x1, y1, x2, y2;

		public: // Methods
			UXRect(void) : x1(0.0), y1(0.0), x2(0.0), y2(0.0) {}

			UXRect(const double x, const double y, const double w, const double h)
			{
				x1 = x; y1 = y; x2 = (x + w); y2 = (y + h);
			}

			UXRect(const float xf1, const float yf1, const float xf2, const float yf2)
			{
				x1 = xf1; y1 = yf1; x2 = xf2; y2 = yf2;
			}

			UXRect(const UXPoint origin, const UXSize size)
			{
				x1 = origin.x; y1 = origin.y; x2 = (x1 + size.w); y2 = (y1 + size.h);
			}

			UXRect(const UXPoint origin, const UXPageSize size)
			{
				x1 = origin.x; y1 = origin.y; x2 = (x1 + size.w); y2 = (y1 + size.h);
			}

			UXRect(const UXPoint pt1, const UXPoint pt2)
			{
				x1 = pt1.x; y1 = pt1.y; x2 = pt2.x; y2 = pt2.y;
			}

			UXRect(const UXRect& rhs) = default;
			UXRect& operator=(const UXRect& rhs) = default;
			~UXRect(void) = default;

			void printwh(void) const;
			void printxy(void) const;

			inline double xd(void) const { return x1; }
			inline double yd(void) const { return y1; }
			inline double wd(void) const { return (x2 - x1); }
			inline double hd(void) const { return (y2 - y1); }

			inline float xf(void) const { return float(x1); }
			inline float yf(void) const { return float(y1); }
			inline float wf(void) const { return float(x2 - x1); }
			inline float hf(void) const { return float(y2 - y1); }

			inline int xi(void) const { return int(round(x1)); }
			inline int yi(void) const { return int(round(y1)); }
			inline int wi(void) const { return int(round(x2 - x1)); }
			inline int hi(void) const { return int(round(y2 - y1)); }

			inline bool empty(void) const
			{
				return ((x1 == 0.0) && (y1 == 0.0) && (x2 == 0.0) && (y2 == 0.0));
			}

			inline bool contains(const UXPoint& point) const
			{
				return ((point.x >= x1) && (point.x <= x2) && (point.y >= y1) && (point.y <= y2));
			}

			inline bool contains(const UXRect& rect) const
			{
				return false; // TODO: Implement
			}

			inline bool intersects(const UXRect& rect) const
			{
				const bool yi = ((y2 >= rect.y1) && (y1 <= rect.y2));
				const bool xi = ((x2 >= rect.x1) && (x1 <= rect.x2));

				return (yi && xi);
			}

			inline UXRect intersect(const UXRect& rect) const
			{
				UXRect intersect; // Intersect

				intersect.x1 = ((rect.x1 > x1) ? rect.x1 : x1);
				intersect.y1 = ((rect.y1 > y1) ? rect.y1 : y1);

				intersect.x2 = ((rect.x2 < x2) ? rect.x2 : x2);
				intersect.y2 = ((rect.y2 < y2) ? rect.y2 : y2);

				return intersect;
			}

			inline UXRect inset(const double ix, const double iy) const
			{
				UXRect rect; // Inset

				rect.x1 = (x1 + ix); rect.y1 = (y1 + iy);
				rect.x2 = (x2 - ix); rect.y2 = (y2 - iy);

				return rect;
			}

			inline UXRect offset(const double dx, const double dy) const
			{
				UXRect rect; // Offset

				rect.x1 = (x1 + dx); rect.y1 = (y1 + dy);
				rect.x2 = (x2 + dx); rect.y2 = (y2 + dy);

				return rect;
			}

			inline UXRect scale(const double sx, const double sy) const
			{
				UXRect rect; // Scaled

				rect.x1 = (x1 * sx); rect.y1 = (y1 * sy);
				rect.x2 = (x2 * sx); rect.y2 = (y2 * sy);

				return rect;
			}

			inline UXPoint center(void) const
			{
				UXPoint point; // Center

				point.x = ((x1 + x2) * 0.5);
				point.y = ((y1 + y2) * 0.5);

				return point;
			}

			inline RECT RECTL(void) const
			{
				RECT rect; // long

				rect.left = LONG(x1); rect.right = LONG(x2);
				rect.top = LONG(y1); rect.bottom = LONG(y2);

				return rect;
			}

			inline UXRect transform(const UXMatrix& t) const
			{
				UXPoint pt1(x1, y1); pt1 = pt1.transform(t);
				UXPoint pt2(x2, y2); pt2 = pt2.transform(t);

				if (pt1.x > pt2.x) { const double tx = pt2.x; pt2.x = pt1.x; pt1.x = tx; }
				if (pt1.y > pt2.y) { const double ty = pt2.y; pt2.y = pt1.y; pt1.y = ty; }

				UXRect rect(pt1, pt2);

				return rect;
			}
	};

	UXRect ConvertToPageFromView(const UXRect& rect, const UXPageSize& size, const int r);
	UXPoint ConvertToPageFromView(const UXPoint& point, const UXPageSize& size, const int r);
	UXRect ConvertToViewFromPage(const UXRect& rect, const UXPageSize& size, const int r);
	UXPoint ConvertToViewFromPage(const UXPoint& point, const UXPageSize& size, const int r);
	void ConvertToViewFromPage(bool bX, bool bY, float& x, float& y, const UXPageSize& size, const int r);
}
