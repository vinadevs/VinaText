//
//	UXReaderDocument.cpp
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "UXReaderDocument.h"
#include "UXReaderDocumentPage.h"
#include "UXReaderDataSource.h"

using namespace UXReader;

//
//	Constants
//

constexpr int m_MinimumPage = 0;

//
//	UXReaderDocument methods
//

UXReader::UXReaderDocument::UXReaderDocument(const wchar_t *filePath)
{
	if (filePath != nullptr) m_DocumentFile.assign(filePath);
}

UXReader::UXReaderDocument::UXReaderDocument(const void *const data, const size_t size)
{
	if ((data != nullptr) && (size > 0)) // Make a copy of the document data
	{
		m_DocumentData.resize(size); memcpy(m_DocumentData.data(), data, size);
	}
}

UXReader::UXReaderDocument::UXReaderDocument(const std::shared_ptr<UXReaderDataSource>& source)
{
	m_DataSource = source;
}

UXReader::UXReaderDocument::~UXReaderDocument(void)
{
	UXReaderSupport& support = UXReaderSupport::Instance();
	{
		std::lock_guard<std::mutex> lockGuard(support.Mutex);

		m_DocumentPages.clear(); m_PageSizes.clear(); m_PageLabels.clear();

		if (m_pdfDocument != nullptr) { FPDF_CloseDocument(m_pdfDocument); m_pdfDocument = nullptr; }
	}
}

bool UXReader::UXReaderDocument::operator==(const UXReaderDocument& rhs)
{
	if (m_DocumentFile.empty() || rhs.m_DocumentFile.empty()) return false;
	return (m_DocumentFile == rhs.m_DocumentFile);
}

int UXReader::UXReaderDocument::GetDataBlock(void *self, unsigned long offset, unsigned char *buffer, unsigned long size)
{
	const UXReaderDocument *document = static_cast<const UXReaderDocument *>(self);
	return document->m_DataSource->GetDataBlock(offset, size, buffer);
}

bool UXReader::UXReaderDocument::IsOpen(void) const
{
	return (m_pdfDocument != nullptr);
}

bool UXReader::UXReaderDocument::OpenWithPassword(const wchar_t *password, int& errorCode)
{
	UXReaderSupport& support = UXReaderSupport::Instance();
	{
		std::lock_guard<std::mutex> lockGuard(support.Mutex);
		if (m_pdfDocument == nullptr)
		{
			errorCode = 0;
			std::string phrase;
			if (password != nullptr)
			{
				phrase = UXReaderSupport::UTF8(password);
			}
			if (m_DocumentFile.empty() == false) // Open file
			{
				std::string filePath = UXReaderSupport::UTF8(m_DocumentFile);
				m_pdfDocument = FPDF_LoadDocument(filePath.c_str(), phrase.c_str());
			}
			else if (m_DocumentData.empty() == false) // Open memory
			{
				const uint8_t *data = m_DocumentData.data(); const size_t size = m_DocumentData.size();
				m_pdfDocument = FPDF_LoadMemDocument(static_cast<const void *>(data), int(size), phrase.c_str());
			}
			else if (m_DataSource != nullptr) // Open data source
			{
				FPDF_FILEACCESS fileAccess; RtlSecureZeroMemory(&fileAccess, sizeof(fileAccess));
				fileAccess.m_GetBlock = &UXReaderDocument::GetDataBlock; fileAccess.m_Param = this;
				fileAccess.m_FileLen = static_cast<unsigned long>(m_DataSource->DataLength());
				m_pdfDocument = FPDF_LoadCustomDocument(&fileAccess, phrase.c_str());
			}
			else // None of the above
			{
				return false;
			}
			if (m_pdfDocument != nullptr) // Opened
			{
				m_PageCount = FPDF_GetPageCount(m_pdfDocument);
				m_MaximumPage = (m_PageCount - 1); // Convenience
				m_PageSizes.reserve(m_PageCount); // Pre-allocate
				for (int index = 0; index < m_PageCount; ++index)
				{
					double w = 0.0; double h = 0.0; // Page size in points (1/72")
					if (FPDF_GetPageSizeByIndex(m_pdfDocument, index, &w, &h) != FALSE)
						m_PageSizes.emplace_back(ceil(w), ceil(h));
					else
						m_PageSizes.emplace_back(612.0f, 792.0f);
				}
			}
			else // Return error
			{
				errorCode = FPDF_GetLastError();
			}
		}
	}
	return (m_pdfDocument != nullptr);
}

FPDF_DOCUMENT UXReader::UXReaderDocument::pdfDocument(void) const
{
	return m_pdfDocument;
}

int UXReader::UXReaderDocument::PageCount(void) const
{
	return m_PageCount;
}

bool UXReader::UXReaderDocument::IsValidPageIndex(const int index) const
{
	return ((index >= m_MinimumPage) && (index <= m_MaximumPage));
}

int UXReader::UXReaderDocument::MinimumPage(void) const
{
	return m_MinimumPage;
}

int UXReader::UXReaderDocument::MaximumPage(void) const
{
	return m_MaximumPage;
}

const UXPageSize& UXReader::UXReaderDocument::PageSize(const int index) const
{
	return m_PageSizes.at(index);
}

std::shared_ptr<UXReaderDocumentPage> UXReader::UXReaderDocument::DocumentPage(const int index)
{
	std::shared_ptr<UXReaderDocumentPage> documentPage;
	UXReaderSupport& support = UXReaderSupport::Instance();
	{
		std::lock_guard<std::mutex> lockGuard(support.Mutex);
		if (m_pdfDocument != nullptr) // Document is open
		{
			const auto it = m_DocumentPages.find(index); // Lookup
			if (it == m_DocumentPages.end()) // Create UXReaderDocumentPage
			{
				documentPage = std::make_shared<UXReaderDocumentPage>(index, this);

				if (documentPage->IsOpen() == true)
					m_DocumentPages.emplace(index, documentPage);
				else
					documentPage = nullptr;
			}
			else // Existing UXReaderDocumentPage
			{
				documentPage = it->second;
			}
		}
	}
	return documentPage;
}

void UXReader::UXReaderDocument::EnumerateCachedPages(std::function<void(int, const std::shared_ptr<UXReaderDocumentPage>&)> fn)
{
	for (auto it : m_DocumentPages) fn(it.first, it.second);
}

std::wstring UXReader::UXReaderDocument::PageLabel(const int index)
{
	std::wstring pageLabel; // Label for page index
	UXReaderSupport& support = UXReaderSupport::Instance();
	{
		std::lock_guard<std::mutex> lockGuard(support.Mutex);
		if (m_pdfDocument != nullptr) // Document is open
		{
			const auto it = m_PageLabels.find(index); // Lookup
			if (it == m_PageLabels.end()) // Extract page label from document
			{
				if (const int bytes = int(FPDF_GetPageLabel(m_pdfDocument, index, nullptr, 0)))
				{
					pageLabel.resize(bytes / sizeof(wchar_t)); void *buffer = &pageLabel[0];

					if (FPDF_GetPageLabel(m_pdfDocument, index, buffer, bytes))
					{
						pageLabel.resize(pageLabel.size() - 1); // Trim NUL
						m_PageLabels.emplace(index, pageLabel);
					}
				}
				else // No page label - return page number
				{
					pageLabel = std::to_wstring(index + 1);

					m_PageLabels.emplace(index, pageLabel);
				}
			}
			else // Existing page label
			{
				pageLabel = it->second;
			}
		}
	}
	return pageLabel;
}

const std::wstring& UXReader::UXReaderDocument::Title(void)
{
	if (m_DocumentTitle.empty() == true)
	{
		if (m_DocumentFile.empty() == false)
		{
			wchar_t filePath[MAX_PATH] {}; // Ick
			wcscpy_s(filePath, m_DocumentFile.data());
			PathStripPathW(filePath); PathRemoveExtensionW(filePath);

			m_DocumentTitle.assign(filePath);
		}
		else // Default name
		{
			m_DocumentTitle.assign(L"noname");
		}
	}
	return m_DocumentTitle;
}

bool UXReader::UXReaderDocument::ConserveMemory(void) const
{
	return true;
}

void UXReader::UXReaderDocument::HexDump(void)
{
	HANDLE fh = CreateFileW(m_DocumentFile.data(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (fh != INVALID_HANDLE_VALUE) // Read file into memory
	{
		DWORD fileSize = GetFileSize(fh, nullptr); DWORD bytesRead = 0;
		if ((fileSize != INVALID_FILE_SIZE) && (fileSize > 0))
		{
			if (void *documentData = malloc(fileSize))
			{
				if (ReadFile(fh, documentData, fileSize, &bytesRead, nullptr) != FALSE)
				{
					HexCode(documentData, bytesRead);
				}

				free(documentData);
			}
		}
		CloseHandle(fh);
	}
}

void UXReader::UXReaderDocument::HexCode(const void *data, const size_t size)
{
	if ((data != nullptr) && (size > 0)) // Hex dump data size
	{
		const unsigned char *ptr = reinterpret_cast<const unsigned char *>(data);
		size_t count = size; int offset = 0; const int bpr = 16; wchar_t text[256];
		std::wstring ws_ptr; std::wstring ws_hex; std::wstring ws_ascii;
		swprintf_s(text, 256, L"\nstatic size_t pdfSize = %zu;\n", size);
		OutputDebugStringW(text);
		OutputDebugStringW(L"\nstatic uint8_t pdfData[] =\n{\n");
		while (count > 0) // Hex dump loop
		{
			if (offset == 0) // Start new row
			{
				ws_hex.clear(); ws_ascii.clear();
			}
			const unsigned char byte = *ptr; // Get data byte
			swprintf_s(text, 256, L"0x%02X, ", byte); ws_hex.append(text);

			count--; offset++; ptr++;

			if (offset >= bpr) // Output full row
			{
				OutputDebugStringW(ws_hex.data()); OutputDebugStringW(L"\n");

				offset = 0;
			}
		}
		if (offset > 0) // Output final row
		{
			OutputDebugStringW(ws_hex.data());
		}
		OutputDebugStringW(L"\n};\n\n/*\n");
	}
}
