//
//	UXReaderLibrary.hpp
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderLibrary final
	{
		public: // Methods
			static UXReaderLibrary& Instance(void)
			{
				static UXReaderLibrary singleton; return singleton;
			}

			static void Module(const HMODULE hModule);
			static HMODULE Module(void);

		private: // Methods
			UXReaderLibrary(void);
			~UXReaderLibrary(void);

			UXReaderLibrary(const UXReaderLibrary&) = delete;
			UXReaderLibrary& operator=(const UXReaderLibrary&) = delete;
			UXReaderLibrary& operator=(UXReaderLibrary&&) = delete;
			UXReaderLibrary(UXReaderLibrary&&) = delete;

			void hModule(const HMODULE hModule);
			HMODULE hModule(void);

			void DoRegisterWindowClasses(void);
			void UnRegisterWindowClasses(void);

		private: // Variables
			HMODULE m_Module = nullptr;
			ULONG_PTR m_GdiPlusToken = 0;
	};
}

extern void DBLog(const wchar_t *format, ...);
extern void DBHex(const void *data, const size_t size);
extern void WMLog(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam);
