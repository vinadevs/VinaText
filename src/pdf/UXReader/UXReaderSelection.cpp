//
//	UXReaderSelection.cpp
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderSelection.h"

using namespace UXReader;

//
//	UXReaderSelection methods
//

UXReader::UXReaderSelection::UXReaderSelection(const int pageIndex, const int charIndex, const int charCount, const std::vector<UXRect>& rectangles, const int selection)
{

	m_PageIndex = pageIndex; m_CharIndex = charIndex; m_CharCount = charCount; m_Rectangles = rectangles; m_Selection = selection;
}

UXReader::UXReaderSelection::~UXReaderSelection(void)
{
}

const std::vector<UXRect> UXReader::UXReaderSelection::Rectangles(void) const
{

	return m_Rectangles;
}

int UXReader::UXReaderSelection::PageIndex(void) const
{

	return m_PageIndex;
}

int UXReader::UXReaderSelection::CharIndex(void) const
{

	return m_CharIndex;
}

int UXReader::UXReaderSelection::CharCount(void) const
{

	return m_CharCount;
}

int UXReader::UXReaderSelection::Selection(void) const
{

	return m_Selection;
}

void UXReader::UXReaderSelection::Description(void) const
{
	DBLog(L"%S %i (%zu) %i\n", __FUNCSIG__, m_PageIndex, m_Rectangles.size(), m_Selection);
}
