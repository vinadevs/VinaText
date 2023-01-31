/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "stdafx.h"

////////////////////////////////////////////////////////////////////
// Custom comparator that compares the string objects by length

struct CompareCStringAscending
{
	inline bool operator()(const CString& first, const CString& second) const
	{
		return first.GetLength() < second.GetLength();
	}
};

struct CompareCStringDescending
{
	inline bool operator()(const CString& first, const CString& second) const
	{
		return first.GetLength() > second.GetLength();
	}
};

struct CompareCStringAlphabetAZ
{
	inline bool operator()(const CString& first, const CString& second) const
	{
		return first < second;
	}
};

struct CompareCStringAlphabetZA
{
	inline bool operator()(const CString& first, const CString& second) const
	{
		return first > second;
	}
};

/////////////////////////////////////
// vector helps

namespace VectorUtils
{
	struct lesser
	{
		template<class T>
		bool operator()(T const &lhs, T const &rhs) const
		{
			return *lhs < *rhs;
		}
	};
	struct equaler
	{
		template<class T>
		bool operator()(T const &lhs, T const &rhs) const
		{
			return *lhs == *rhs;
		}
	};
	template<class T>
	T Uniquify(T begin, T const end)
	{
		std::vector<T> v;
		v.reserve(static_cast<size_t>(std::distance(begin, end)));
		for (T i = begin; i != end; ++i)
		{
			v.push_back(i);
		}
		std::sort(v.begin(), v.end(), lesser());
		v.erase(std::unique(v.begin(), v.end(), equaler()), v.end());
		std::sort(v.begin(), v.end());
		size_t j = 0;
		for (T i = begin; i != end && j != v.size(); ++i)
		{
			if (i == v[j])
			{
				std::iter_swap(i, begin);
				++j;
				++begin;
			}
		}
		return begin;
	}

	template <class T>
	std::vector<std::vector<T>> GroupSimilarElementGroup(std::vector<T>& v)
	{
		std::vector<std::vector<T>> clusters;
		auto group_begin = v.begin();
		while (group_begin != v.end())
		{
			auto elem = *group_begin;

			auto group_end = std::find_if(group_begin, v.end(),
				[&](int e) { return e != elem; });
			clusters.emplace_back(std::distance(group_begin, group_end), elem);

			group_begin = group_end;
		}
		return clusters;
	};
	template <class T>
	void RemoveElement(std::vector<T>& vec, size_t pos)
	{
		std::vector<T>::iterator it = vec.begin();
		std::advance(it, pos);
		vec.erase(it);
	}
}