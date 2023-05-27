//
//	UXReaderAction.cpp
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderAction.h"
#include "UXReaderDestination.h"

using namespace UXReader;

//
//	UXReaderAction methods
//

UXReader::UXReaderAction::UXReaderAction(const std::string& URI, const UXRect& rectangle)
{

	m_Type = UXReaderActionType::URI;

	m_Rectangles.push_back(rectangle);

	m_URI = UXReaderSupport::UTF16(URI);
}

UXReader::UXReaderAction::UXReaderAction(const UXReaderDestination& destination, const UXRect& rectangle)
{

	m_Type = UXReaderActionType::Goto;

	m_Destination = std::make_unique<UXReaderDestination>(destination);

	m_Rectangles.push_back(rectangle);
}

UXReader::UXReaderAction::UXReaderAction(const UXReaderDestination& destination, const std::wstring& URI, const UXRect& rectangle)
{

	m_Type = UXReaderActionType::RemoteGoto;

	m_Destination = std::make_unique<UXReaderDestination>(destination);

	m_Rectangles.push_back(rectangle); m_URI = URI;
}

UXReader::UXReaderAction::UXReaderAction(const std::wstring& URI, const UXRect& rectangle)
{

	m_Type = UXReaderActionType::Launch;

	m_Rectangles.push_back(rectangle); m_URI = URI;
}

UXReader::UXReaderAction::UXReaderAction(const std::wstring& URI, const std::vector<UXRect>& rectangles)
{

	m_Type = UXReaderActionType::Link;

	m_Rectangles = rectangles; m_URI = URI;
}

UXReader::UXReaderAction::~UXReaderAction(void)
{
}

UXReaderActionType UXReader::UXReaderAction::Type(void) const
{

	return m_Type;
}

const UXReaderDestination* UXReader::UXReaderAction::Destination(void) const
{

	return m_Destination.get();
}

const std::vector<UXRect>& UXReader::UXReaderAction::Rectangles(void) const
{

	return m_Rectangles;
}

const std::wstring& UXReader::UXReaderAction::URI(void) const
{

	return m_URI;
}

bool UXReader::UXReaderAction::Contains(const UXPoint& point) const
{

	for (const UXRect& rectangle : m_Rectangles) // O(n)
	{
		if (rectangle.contains(point)) return true;
	}

	return false;
}

void UXReader::UXReaderAction::Description(void) const
{

	switch (m_Type)
	{
		case UXReaderActionType::URI:
		{
			DBLog(L"%S URI: '%s'\n", __FUNCSIG__, m_URI.data());
			break;
		}

		case UXReaderActionType::Goto:
		{
			DBLog(L"%S Goto: %i\n", __FUNCSIG__, m_Destination->PageIndex());
			break;
		}

		case UXReaderActionType::RemoteGoto:
		{
			DBLog(L"%S RemoteGoto: '%s' %i\n", __FUNCSIG__, m_URI.data(), m_Destination->PageIndex());
			break;
		}

		case UXReaderActionType::Launch:
		{
			DBLog(L"%S Launch: '%s'\n", __FUNCSIG__, m_URI.data());
			break;
		}

		case UXReaderActionType::Link:
		{
			DBLog(L"%S Link: '%s'\n", __FUNCSIG__, m_URI.data());
			break;
		}
	}
}
