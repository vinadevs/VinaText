//
//	UXReaderLibrary.cpp
//	UXReader v0.1
//
//	Copyright © 2017-2019 Julius Oklamcak. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "UXReaderLibrary.h"
#include "UXReaderMainWindow.h"
#include "UXReaderDocumentPane.h"
#include "UXReaderDocumentView.h"
#include "UXReaderToolbarPane.h"
#include "UXReaderToolbarItem.h"
#include "UXReaderToolbarText.h"
#include "UXReaderToolbarEdit.h"
#include "UXReaderStatusPane.h"

using namespace UXReader;

//
//	UXReaderLibrary methods
//

UXReader::UXReaderLibrary::UXReaderLibrary(void)
{

	OleInitialize(nullptr);

	INITCOMMONCONTROLSEX icc; icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_STANDARD_CLASSES; InitCommonControlsEx(&icc);

	Gdiplus::GdiplusStartupInput gdiPlusStartupInput;
	Gdiplus::GdiplusStartup(&m_GdiPlusToken, &gdiPlusStartupInput, nullptr);

	const FPDF_LIBRARY_CONFIG config {2, nullptr, nullptr, 0};
	FPDF_InitLibraryWithConfig(&config);
}

UXReader::UXReaderLibrary::~UXReaderLibrary(void)
{

	Gdiplus::GdiplusShutdown(m_GdiPlusToken); m_GdiPlusToken = 0;

	FPDF_DestroyLibrary(); UnRegisterWindowClasses(); OleUninitialize();

}

//
//	Module methods
//

void UXReader::UXReaderLibrary::hModule(const HMODULE hModule)
{

	if ((hModule != nullptr) && (m_Module == nullptr))
	{
		m_Module = hModule; DoRegisterWindowClasses();
	}
}

void UXReader::UXReaderLibrary::Module(const HMODULE hModule)
{

	UXReaderLibrary& Instance = UXReaderLibrary::Instance();

	Instance.hModule(hModule);
}

HMODULE UXReader::UXReaderLibrary::hModule(void)
{

	if (m_Module == nullptr) // Default
	{
		m_Module = GetModuleHandleW(nullptr);

		DoRegisterWindowClasses();
	}


	return m_Module;
}

HMODULE UXReader::UXReaderLibrary::Module(void)
{

	UXReaderLibrary& Instance = UXReaderLibrary::Instance();

	return Instance.hModule();
}

//
//	Window methods
//

void UXReader::UXReaderLibrary::DoRegisterWindowClasses(void)
{

	if (m_Module != nullptr)
	{
		UXReaderMainWindow::DoRegisterWindowClass(m_Module);

		UXReaderDocumentPane::DoRegisterWindowClass(m_Module);
		UXReaderDocumentView::DoRegisterWindowClass(m_Module);

		UXReaderToolbarPane::DoRegisterWindowClass(m_Module);
		UXReaderToolbarItem::DoRegisterWindowClass(m_Module);
		UXReaderToolbarText::DoRegisterWindowClass(m_Module);
		UXReaderToolbarEdit::DoRegisterWindowClass(m_Module);

		UXReaderStatusPane::DoRegisterWindowClass(m_Module);
	}
}

void UXReader::UXReaderLibrary::UnRegisterWindowClasses(void)
{

	if (m_Module != nullptr)
	{
		UXReaderMainWindow::UnRegisterWindowClass(m_Module);

		UXReaderDocumentPane::UnRegisterWindowClass(m_Module);
		UXReaderDocumentView::UnRegisterWindowClass(m_Module);

		UXReaderToolbarPane::UnRegisterWindowClass(m_Module);
		UXReaderToolbarItem::UnRegisterWindowClass(m_Module);
		UXReaderToolbarText::UnRegisterWindowClass(m_Module);
		UXReaderToolbarEdit::UnRegisterWindowClass(m_Module);

		UXReaderStatusPane::UnRegisterWindowClass(m_Module);
	}
}
