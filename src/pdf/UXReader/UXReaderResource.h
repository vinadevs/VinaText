//
//	UXReaderResource.hpp
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderResource final
	{
		public: // Methods
			static UXReaderResource& Instance(void)
			{
				static UXReaderResource singleton; return singleton;
			}

			static const HBITMAP Icon(const HDC hDC, const int id, const int w, const int h);
			static const wchar_t *String(const int id);

		private: // Methods
			UXReaderResource(void);
			~UXReaderResource(void);

			UXReaderResource(const UXReaderResource&) = delete;
			UXReaderResource& operator=(const UXReaderResource&) = delete;
			UXReaderResource& operator=(UXReaderResource&&) = delete;
			UXReaderResource(UXReaderResource&&) = delete;

			void PopulateStrings(void);
			void PopulateIconData(void);

			HBITMAP CreateIcon(const HDC hDC, const int id, const int w, const int h);
			HBITMAP RenderIcon(const HDC hDC, const int w, const int h, const uint8_t* data, const size_t size);

		private: // Variables
			std::map<int, std::wstring> m_Strings;
			std::map<int, std::pair<uint8_t*, size_t>> m_IconData;
			std::map<int, HBITMAP> m_Icons;
	};
}
