//
//	DBLog.h
//	DBLog v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

void DBLog(const wchar_t *format, ...);
void DBHex(const void *data, const size_t size);
void WMLog(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam);
