//
//	UXReaderDocument.hpp
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

#include "common.h"

namespace UXReader
{
	class UXReaderDataSource;
	class UXReaderDocumentPage;

	class UXReaderDocument final
	{
		private: // Variables
			std::wstring m_DocumentFile;

			std::vector<uint8_t> m_DocumentData;

			std::shared_ptr<UXReaderDataSource> m_DataSource;

			std::unordered_map<int, std::shared_ptr<UXReaderDocumentPage>> m_DocumentPages;

			std::unordered_map<int, std::wstring> m_PageLabels;

			FPDF_DOCUMENT m_pdfDocument = nullptr;

			std::vector<UXPageSize> m_PageSizes;

			int m_PageCount = 0; int m_MaximumPage = 0;

			std::wstring m_DocumentTitle;

		public: // Methods
			UXReaderDocument(const wchar_t *filePath);
			UXReaderDocument(const void *const data, const size_t size);
			UXReaderDocument(const std::shared_ptr<UXReaderDataSource>& source);
			~UXReaderDocument(void);

			UXReaderDocument(void) = delete;
			UXReaderDocument(const UXReaderDocument&) = delete;
			UXReaderDocument& operator=(const UXReaderDocument&) = delete;
			UXReaderDocument& operator=(UXReaderDocument&&) = delete;
			UXReaderDocument(UXReaderDocument&&) = delete;

			bool operator==(const UXReaderDocument& rhs);

			bool IsOpen(void) const;
			bool OpenWithPassword(const wchar_t *password, int& errorCode);
			FPDF_DOCUMENT pdfDocument(void) const;

			int PageCount(void) const;
			bool IsValidPageIndex(const int index) const;
			int MinimumPage(void) const;
			int MaximumPage(void) const;

			const UXPageSize& PageSize(const int index) const;
			std::shared_ptr<UXReaderDocumentPage> DocumentPage(const int index);
			void EnumerateCachedPages(std::function<void(int, const std::shared_ptr<UXReaderDocumentPage>&)> fn);
			std::wstring PageLabel(const int index);

			const std::wstring& Title(void);

			bool ConserveMemory(void) const;

			void HexDump(void);

		private: // Methods
			static int GetDataBlock(void *self, unsigned long offset, unsigned char *buffer, unsigned long size);

			void HexCode(const void *data, const size_t size);
	};
}
