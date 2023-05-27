//
//	UXReaderTemplates.cpp
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderTemplates.h"

using namespace UXReader;

//
//	UXReaderTemplates methods
//

UXReader::UXReaderTemplates::UXReaderTemplates(void)
{

	UXRectZ<double> rect(4.0, 4.0, 32.0, 32.0);

	DBLog(L"%S %g %g %g %g\n", __FUNCSIG__, rect.x1(), rect.y1(), rect.x2(), rect.y2());

	DBLog(L"%S %g %g %g %g\n", __FUNCSIG__, rect.x(), rect.y(), rect.w(), rect.h());

	DBLog(L"%S %i\n", __FUNCSIG__, rect.contains(8.0, 16.0));
}

UXReader::UXReaderTemplates::~UXReaderTemplates(void)
{
}
