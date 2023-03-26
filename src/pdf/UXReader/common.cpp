//
//	stdafx.cpp
//	UXReader v0.1
//
//	Copyright � 2017-2019 Julius Oklamcak. All rights reserved.
//
//	Source file that includes just the standard includes. UXReader.pch will be the
//	pre-compiled header and stdafx.obj will contain the pre-compiled type information.
//

#include "stdafx.h"
#include "common.h"

#if _M_X64
	#if _DEBUG
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\bigint.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\fdrm.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\formfiller.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\fpdfapi.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\fpdfdoc.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\fpdftext.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\fxcodec.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\fxcrt.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\fxedit.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\fxge.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\fx_agg.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\fx_freetype.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\fx_lcms2.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\fx_libopenjpeg.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\fx_lpng.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\javascript.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\libjpeg.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\minizip.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\pdfium.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\pdfium_base.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\pdfwindow.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\simd.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\simd_asm.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\yasm_utils.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\zlib.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64d\\zlib_x86_simd.lib")
	#else
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\bigint.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\fdrm.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\formfiller.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\fpdfapi.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\fpdfdoc.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\fpdftext.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\fxcodec.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\fxcrt.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\fxedit.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\fxge.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\fx_agg.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\fx_freetype.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\fx_lcms2.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\fx_libopenjpeg.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\fx_lpng.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\javascript.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\libjpeg.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\minizip.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\pdfium.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\pdfium_base.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\pdfwindow.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\simd.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\simd_asm.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\yasm_utils.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\zlib.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x64r\\zlib_x86_simd.lib")
	#endif
#else
	#if _DEBUG
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\bigint.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\fdrm.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\formfiller.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\fpdfapi.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\fpdfdoc.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\fpdftext.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\fxcodec.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\fxcrt.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\fxedit.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\fxge.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\fx_agg.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\fx_freetype.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\fx_lcms2.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\fx_libopenjpeg.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\fx_lpng.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\javascript.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\libjpeg.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\minizip.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\pdfium.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\pdfium_base.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\pdfwindow.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\simd.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\simd_asm.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\yasm_utils.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\zlib.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86d\\zlib_x86_simd.lib")
	#else
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\bigint.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\fdrm.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\formfiller.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\fpdfapi.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\fpdfdoc.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\fpdftext.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\fxcodec.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\fxcrt.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\fxedit.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\fxge.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\fx_agg.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\fx_freetype.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\fx_lcms2.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\fx_libopenjpeg.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\fx_lpng.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\javascript.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\libjpeg.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\minizip.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\pdfium.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\pdfium_base.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\pdfwindow.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\simd.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\simd_asm.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\yasm_utils.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\zlib.lib")
		#pragma comment(lib, "pdf\\PDFium\\lib\\x86r\\zlib_x86_simd.lib")
	#endif
#endif
