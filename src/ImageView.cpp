/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "VinaTextApp.h"
#include "MainFrm.h"
#include "ImageDoc.h"
#include "ImageView.h"
#include "Memdc.h"
#include "AppSettings.h"
#include "AppUtil.h"
#include "GuiUtils.h"
#include "GammaDlg.h"
#include "HostManager.h"
#include "LocalizationHandler.h"

ColorMatrix	clrMatrix;

/////////////////////////////////////////////////////////////////////////////
// CImageView

IMPLEMENT_DYNCREATE(CImageView, CViewBase)

CImageView::CImageView()
{
	m_fZoomFactor = 0.5;
	m_pLoadImage = NULL;
	m_pGifHandler = NULL;
	m_bPauseToggle = false;
}

CImageView::~CImageView()
{
	DELETE_POINTER_CPP(m_pLoadImage);
	DELETE_POINTER_CPP(m_pGifHandler);
}

BEGIN_MESSAGE_MAP(CImageView, CViewBase)
	ON_WM_CREATE()
	ON_WM_DRAWITEM()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_SETFOCUS()

	ON_COMMAND(ID_IMAGE_EDIT_WIH_MSPAINT, OnEditWithMsPaint)
	ON_COMMAND(ID_IMAGE_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_IMAGE_ZOOM_IN, OnOptionsZoomUp)
	ON_COMMAND(ID_IMAGE_ZOOM_OUT, OnOptionsZoomDown)
	ON_COMMAND(ID_IMAGE_LEFT_ROTATE, OnOptionsLeftRotate)
	ON_COMMAND(ID_IMAGE_RIGHT_ROTATE, OnOptionsRightRotate)
	ON_COMMAND(ID_IMAGE_FLIP, OnOptionsFlip)
	ON_COMMAND(ID_IMAGE_MIRROR, OnOptionsMirror)
	ON_COMMAND(ID_IMAGE_NEGATIVE, OnOptionsNegative)
	ON_COMMAND(ID_IMAGE_GRAYSCALE, OnOptionsGrayScale)
	ON_COMMAND(ID_IMAGE_THRESHOLD, OnOptionsThreshold)
	ON_COMMAND(ID_IMAGE_LIGHTEN, OnOptionsLighten)
	ON_COMMAND(ID_IMAGE_DARKEN, OnOptionsDarken)
	ON_COMMAND(ID_IMAGE_CONTRAST, OnOptionsContrast)
	ON_COMMAND(ID_IMAGE_SHARPEN, OnOptionsSharpen)
	ON_COMMAND(ID_IMAGE_GAMMA, OnOptionsGamma)
	ON_COMMAND(ID_IMAGE_GIF_PAUSE, OnOptionsPause)
	ON_COMMAND(ID_IMAGE_RETURN_ORIGINAL, OnOptionsReturn)
	ON_COMMAND(ID_IMAGE_SHOW_SYSTEM_MENU, OnOptionsShowSystemMenu)

	ON_UPDATE_COMMAND_UI(ID_IMAGE_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_LEFT_ROTATE, OnUpdateOptionsLeftRotate)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_RIGHT_ROTATE, OnUpdateOptionsRightRotate)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_FLIP, OnUpdateOptionsFlip)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_MIRROR, OnUpdateOptionsMirror)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_NEGATIVE, OnUpdateOptionsNegative)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_GRAYSCALE, OnUpdateOptionsGrayScale)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_THRESHOLD, OnUpdateOptionsThreshold)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_LIGHTEN, OnUpdateOptionsLighten)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_DARKEN, OnUpdateOptionsDarken)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_CONTRAST, OnUpdateOptionsContrast)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_SHARPEN, OnUpdateOptionsSharpen)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_GAMMA, OnUpdateOptionsGamma)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_GIF_PAUSE, OnUpdateOptionsPause)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageView diagnostics

#ifdef _DEBUG
void CImageView::AssertValid() const
{
	CViewBase::AssertValid();
}

void CImageView::Dump(CDumpContext& dc) const
{
	CViewBase::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageView message handlers

void CImageView::OnInitialUpdate()
{
	CViewBase::OnInitialUpdate();
	CString strFileImagePath = m_pDocument->GetPathName();
	if (PathUtils::IsImageFile(strFileImagePath))
	{
		m_ImageStream.Release();
		DELETE_POINTER_CPP(m_pLoadImage);
		DELETE_POINTER_CPP(m_pGifHandler);

		auto startMeasureTime = OSUtils::StartBenchmark();
		if (PathUtils::IsGifFile(strFileImagePath))
		{
			// GDI+
			m_pGifHandler = new CGifHandler(strFileImagePath); // need to free m_pGifHandler
			CRect rc;
			GetClientRect(rc);
			float fBitmapWidth = (float)m_pGifHandler->GetWidth();
			float fBitmapHeight = (float)m_pGifHandler->GetHeight();
			int nX = static_cast<int>((rc.right - rc.left - fBitmapWidth * m_fZoomFactor) / 2);
			int nY = static_cast<int>((rc.bottom - rc.top - fBitmapHeight * m_fZoomFactor) / 2);
			m_pGifHandler->InitAnimation(m_hWnd, CRect(nX, nY, (int)(fBitmapWidth * m_fZoomFactor), (int)(fBitmapHeight * m_fZoomFactor)));
		}
		else
		{
			// Read from image file into buffer:
			HANDLE hFile = CreateFile(strFileImagePath, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (!hFile) return;
			DWORD bufsize = GetFileSize(hFile, NULL);
			if (bufsize > 0)
			{
				BYTE *buffer = new BYTE[bufsize];
				DWORD temp = 0;
				if (ReadFile(hFile, buffer, bufsize, &temp, 0)) {
					// Convert buffer to IStream    
					m_ImageStream.Attach(SHCreateMemStream(buffer, bufsize));
					m_pLoadImage = Bitmap::FromStream(m_ImageStream); // need to free m_pLoadImage
				}
				DELETE_POINTER_CPP_ARRAY(buffer);
			}
			CloseHandle(hFile);
		}
		
		if (!AppUtils::GetVinaTextApp()->m_bIsReloadByPreviewMode)
		{
			CString strMsg = AfxCStringFormat(_T("> [Load File] %s - timelapse: "), strFileImagePath);
			OSUtils::LogStopBenchmark(LOG_TARGET::MESSAGE_WINDOW, startMeasureTime, strMsg);
		}

		this->SendMessage(WM_SIZE);

		// check last write time point
		UpdateFileLastWriteTime(strFileImagePath);
	}
}

HBITMAP CImageView::GetCurrentBitmap()
{
	HBITMAP hbitmap = NULL;
	if (m_pLoadImage)
	{
		CWaitCursor aCursor;
		if (m_pLoadImage->GetLastStatus() != Gdiplus::Ok) return NULL;
		Status status = m_pLoadImage->GetHBITMAP(0, &hbitmap);
		if (status != Gdiplus::Ok) return NULL;
	}
	return hbitmap;
}

void CImageView::OnSetFocus(CWnd * pOldWnd)
{
	CViewBase::OnSetFocus(pOldWnd);
	if (!m_bIsWatchFileProcessing)
	{
		WatchFileSystemState(); // when view is actived, check file status also...
	}
}

void CImageView::UpdatePreviewFileContent()
{
	OnInitialUpdate();
}

BOOL CImageView::GetImageEncoderClsid(const WCHAR * format, CLSID * pClsid)
{
	// format can be:
	/*image / bmp
	image / jpeg
	image / gif
	image / tiff
	image / png*/

	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	using namespace Gdiplus;

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return FALSE;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return FALSE;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return TRUE;  // Success
		}
	}

	free(pImageCodecInfo);
	return FALSE;  // Failure
}


BOOL CImageView::SaveImage(const CString & szPath)
{
	if (m_pLoadImage && PathUtils::IsImageFile(szPath))
	{
		auto startMeasureTime = OSUtils::StartBenchmark();

		CLSID encoderClsid;
		INT result;
		if (GetImageTypeFromFile(szPath) == SaveImageType::Png)
		{
			// Get the CLSID of the PNG encoder.
			result = GetImageEncoderClsid(L"image/png", &encoderClsid);
			if (result < 0)
			{
				AfxMessageBox(_T("[Save Error] The PNG encoder is not installed!"));
				return FALSE;
			}
		}
		else if (GetImageTypeFromFile(szPath) == SaveImageType::Jpeg)
		{
			// Get the CLSID of the JPEG encoder.
			result = GetImageEncoderClsid(L"image/jpeg", &encoderClsid);
			if (result < 0)
			{
				AfxMessageBox(_T("[Save Error] The JPEG encoder is not installed!"));
				return FALSE;
			}
		}
		else if (GetImageTypeFromFile(szPath) == SaveImageType::Bmp)
		{
			// Get the CLSID of the Bitmap encoder.
			result = GetImageEncoderClsid(L"image/bmp", &encoderClsid);
			if (result < 0)
			{
				AfxMessageBox(_T("[Save Error] The Bitmap encoder is not installed!"));
				return FALSE;
			}
		}
		else if (GetImageTypeFromFile(szPath) == SaveImageType::Gif)
		{
			// Get the CLSID of the gif encoder.
			result = GetImageEncoderClsid(L"image/gif", &encoderClsid);
			if (result < 0)
			{
				AfxMessageBox(_T("[Save Error] The Gif encoder is not installed!"));
				return FALSE;
			}
		}
		else if (GetImageTypeFromFile(szPath) == SaveImageType::Tiff)
		{
			// Get the CLSID of the tiff encoder.
			result = GetImageEncoderClsid(L"image/tiff", &encoderClsid);
			if (result < 0)
			{
				AfxMessageBox(_T("[Save Error] The Tiff encoder is not installed!"));
				return FALSE;
			}
		}
		// Before we call Image::Save, we must initialize an
		// EncoderParameters object. The EncoderParameters object
		// has an array of EncoderParameter objects. In this
		// case, there is only one EncoderParameter object in the array.
		// The one EncoderParameter object has an array of values.
		// In this case, there is only one value (of type ULONG)
		// in the array. We will let this value vary from 0 to 100.
		EncoderParameters encoderParameters;
		encoderParameters.Count = 1;
		encoderParameters.Parameter[0].Guid = EncoderQuality;
		encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
		encoderParameters.Parameter[0].NumberOfValues = 1;
		// Save the image as a JPEG with quality level 0.
		// A quality level of 0 corresponds to the greatest compression,
		// and a quality level of 100 corresponds to the least compression.
		ULONG quality = 0;
		encoderParameters.Parameter[0].Value = &quality;
		CWaitCursor aCursor;
		Gdiplus::Status saveStatus = m_pLoadImage->Save(szPath, &encoderClsid, &encoderParameters);
		if (saveStatus == Gdiplus::Ok)
		{
			CString strMsg;
			if (AppUtils::GetVinaTextApp()->m_bIsOpenInAdminMode)
			{
				strMsg = AfxCStringFormat(_T("> [Save File Administrator] %s - timelapse: "), szPath);
			}
			else
			{
				strMsg = AfxCStringFormat(_T("> [Save File] %s - timelapse: "), szPath);
			}
			OSUtils::LogStopBenchmark(LOG_TARGET::MESSAGE_WINDOW, startMeasureTime, strMsg);
			// update modified time
			UpdateFileLastWriteTime(szPath);
			return TRUE;
		}
	}
	return FALSE;
}

SaveImageType CImageView::GetImageTypeFromFile(const CString & szPath)
{
	CString strExt = PathUtils::GetFileExtention(szPath);
	if (strExt.CompareNoCase(_T("png")) == 0)
	{
		return SaveImageType::Png;
	}
	else if (strExt.CompareNoCase(_T("jpg")) == 0)
	{
		return SaveImageType::Jpeg;
	}
	else if (strExt.CompareNoCase(_T("bmp")) == 0)
	{
		return SaveImageType::Bmp;
	}
	else if (strExt.CompareNoCase(_T("gif")) == 0)
	{
		return SaveImageType::Gif;
	}
	else if (strExt.CompareNoCase(_T("tiff")) == 0)
	{
		return SaveImageType::Tiff;
	}
	return SaveImageType::Png;
}

void CImageView::OnDraw(CDC * pDC)
{
	// draw background
	CRect rect; GetClientRect(rect);
	HBRUSH hBrush = ::CreateSolidBrush(IS_LIGHT_THEME ? 0x00484848 : AppSettingMgr.m_AppThemeColor);
	::FillRect(pDC->m_hDC, rect, hBrush);
	DeleteObject(hBrush);
}

BOOL CImageView::PreTranslateMessage(MSG * pMsg)
{
	switch (pMsg->message)
	{
	case WM_RBUTTONDOWN:
	{
		if ((GetKeyState(VK_SHIFT) & 0x8000))
		{
			OnOptionsShowSystemMenu();
			return TRUE;
		}
		break;
	}
	case WM_KEYDOWN:
	{
		if (AfxGetMainWnd()->PreTranslateMessage(pMsg))
		{
			return TRUE;
		}
		else
		{
			switch (pMsg->wParam)
			{
				case 'S':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
					{
						DoFileSaveAs();
						return TRUE;
					}
				}
				break;
				case 'D':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnOptionsFlip();
						return TRUE;
					}
				}
				break;
				case 'M':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnOptionsMirror();
						return TRUE;
					}
				}
				break;
				case 'R':
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnOptionsReturn();
						return TRUE;
					}
				}
				break;
				case VK_LEFT:
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnOptionsLeftRotate();
						return TRUE;
					}
				}
				break;
				case VK_RIGHT:
				{
					if ((GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnOptionsRightRotate();
						return TRUE;
					}
				}
				break;
				case VK_DOWN:
				{
					OnOptionsZoomDown();
					return TRUE;
				}
				break;
				case VK_UP:
				{
					OnOptionsZoomUp();
					return TRUE;
				}
				break;
				case VK_SPACE:
				{
					OnOptionsPause();
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	case WM_MOUSEWHEEL:
	{
		short sDelta = GET_WHEEL_DELTA_WPARAM(pMsg->wParam);
		if (sDelta > 0) // wheel mouse up
		{
			OnOptionsZoomUp();
		}
		else
		{
			OnOptionsZoomDown();
		}
		return TRUE;
	}
	}
	return CViewBase::PreTranslateMessage(pMsg);
}

int CImageView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_pLoadImage = NULL;
	if (CViewBase::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	// SS_OWNERDRAW - The owner of the static control is responsible for drawing the control.
	// The owner window receives a WM_DRAWITEM message whenever the control needs to be drawn.
	CRect rect; GetClientRect(&rect);
	m_wndCanvas.Create(_T("Image Preview Canvas"),
		WS_VISIBLE | WS_CHILD | SS_OWNERDRAW,
		rect,
		this,
		80);
	return 0;
}

/* The images possible to be displayed are given by the graphics file formats
supported by GDI + : -BMP(Windows bitmap), -EMF(Enhanced Metafile),
-Exif(Exchangeable Image File), -GIF(Graphics Interchange Format), -Icon,
-Indicates the JPEG(Joint Photographic Experts Group), -PNG(Portable Network Graphics),
-TIFF(Tag Image File Format), -WMF(Windows Metafile), basically everything that can be
loaded into a GDI + Bitmap object. */

void CImageView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
	{
		// create new draw session
		CMemDCEx *pMemDC = NULL;
		pMemDC = new CMemDCEx(lpDrawItemStruct->hDC);
		lpDrawItemStruct->hDC = pMemDC->m_hDC;

		// draw background
		HBRUSH hBrush = ::CreateSolidBrush(IS_LIGHT_THEME ? 0x00484848 : AppSettingMgr.m_AppThemeColor);
		::FillRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, hBrush);
		DeleteObject(hBrush);

		if (m_pLoadImage != NULL)
		{
			float fBitmapWidth = (float)m_pLoadImage->GetWidth();
			float fBitmapHeight =(float)m_pLoadImage->GetHeight();
			Graphics drawer(lpDrawItemStruct->hDC);
			if (drawer.GetLastStatus() == Ok)
			{
				drawer.SetInterpolationMode(InterpolationModeHighQualityBicubic);
				int nX = static_cast<int>((lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left - fBitmapWidth * m_fZoomFactor) / 2);
				int nY = static_cast<int>((lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top - fBitmapHeight* m_fZoomFactor) / 2);
				drawer.DrawImage(m_pLoadImage, nX, nY, (int)(fBitmapWidth * m_fZoomFactor), (int)(fBitmapHeight * m_fZoomFactor));
			}
		}

		DELETE_POINTER_CPP(pMemDC);
	}
}

void CImageView::OnSize(UINT nType, int cx, int cy)
{
	CViewBase::OnSize(nType, cx, cy);
	CRect rc; GetClientRect(rc);
	if (!m_pLoadImage && !m_pGifHandler)
	{
		rc.SetRectEmpty();
		m_wndCanvas.MoveWindow(rc);
	}
	else if (m_pLoadImage)
	{
		const int   nWidth = rc.Width();
		const int   nHeight = rc.Height();
		const float fRatio = (float)nHeight / nWidth;
		const float fImgRatio = (float)m_pLoadImage->GetHeight() / m_pLoadImage->GetWidth();

		int XDest, YDest, nDestWidth, nDestHeight;

		if (fImgRatio > fRatio)
		{
			nDestWidth = static_cast<int>(nHeight / fImgRatio);
			XDest = (nWidth - nDestWidth) / 2;
			YDest = 0;
			nDestHeight = nHeight;
		}
		else
		{
			XDest = 0;
			nDestWidth = nWidth;
			nDestHeight = static_cast<int>(nWidth * fImgRatio);
			YDest = (nHeight - nDestHeight) / 2;
		}

		CRect rect(XDest, YDest, XDest + nDestWidth, YDest + nDestHeight);
		m_wndCanvas.MoveWindow(rect);
		m_wndCanvas.Invalidate();
	}
	else if (m_pGifHandler)
	{
		float fBitmapWidth = (float)m_pGifHandler->GetWidth();
		float fBitmapHeight = (float)m_pGifHandler->GetHeight();
		int nX = static_cast<int>((rc.right - rc.left - fBitmapWidth * m_fZoomFactor) / 2);
		int nY = static_cast<int>((rc.bottom - rc.top - fBitmapHeight * m_fZoomFactor) / 2);
		m_pGifHandler->SetRect(CRect(nX, nY, (int)(fBitmapWidth * m_fZoomFactor), (int)(fBitmapHeight * m_fZoomFactor)));
		GuiUtils::ForceRedrawCWnd(this);
	}
}

void CImageView::OnContextMenu(CWnd * pWnd, CPoint point)
{
	ASSERT(m_pDocument);
	if (!m_pDocument) return;
	CMenu menu;
	if (menu.LoadMenu(IDR_IMAGE_POPUP))
	{
		CMenu* pSubMenu = menu.GetSubMenu(0);
#pragma warning(suppress: 26496)
		AFXASSUME(pSubMenu != NULL);
		if (!pSubMenu) return;
		VinaTextLocalization.TranslateContextMenu(pSubMenu);

		if (PathUtils::IsGifFile(m_pDocument->GetPathName()))
		{
			pSubMenu->DeleteMenu(ID_IMAGE_EDIT_COPY, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_IMAGE_LEFT_ROTATE, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_IMAGE_RIGHT_ROTATE, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_IMAGE_FLIP, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_IMAGE_MIRROR, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_IMAGE_NEGATIVE, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_IMAGE_GRAYSCALE, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_IMAGE_THRESHOLD, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_IMAGE_LIGHTEN, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_IMAGE_DARKEN, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_IMAGE_CONTRAST, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_IMAGE_SHARPEN, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_IMAGE_GAMMA, MF_BYCOMMAND);
			pSubMenu->DeleteMenu(ID_EDIT_COPY, MF_BYCOMMAND);
		}
		else
		{
			pSubMenu->DeleteMenu(ID_IMAGE_GIF_PAUSE, MF_BYCOMMAND);
		}

		// system menu style
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

void CImageView::OnOptionsZoomUp()
{
	if (m_pLoadImage || m_pGifHandler)
	{
		m_fZoomFactor *= 1.1f;
		this->SendMessage(WM_SIZE);
	}
}

void CImageView::OnOptionsZoomDown()
{
	if (m_pLoadImage || m_pGifHandler)
	{
		m_fZoomFactor /= 1.1f;
		this->SendMessage(WM_SIZE);
	}
}

void CImageView::OnOptionsLeftRotate()
{
	if (m_pLoadImage)
	{
		m_pLoadImage->RotateFlip(Rotate270FlipNone);
		UpdateImageChange();
	}
}

void CImageView::OnOptionsRightRotate()
{
	if (m_pLoadImage)
	{
		m_pLoadImage->RotateFlip(Rotate90FlipNone);
		UpdateImageChange();
	}
}

void CImageView::OnOptionsFlip()
{
	if (m_pLoadImage)
	{
		m_pLoadImage->RotateFlip(RotateNoneFlipY);
		UpdateImageChange();
	}
}

void CImageView::OnOptionsMirror()
{
	if (m_pLoadImage)
	{
		m_pLoadImage->RotateFlip(RotateNoneFlipX);
		UpdateImageChange();;
	}
}

void CImageView::OnOptionsNegative()
{
	if (m_pLoadImage)
	{
		Graphics* imageGraphics = Graphics::FromImage(m_pLoadImage);
		ImageAttributes	imAtt;

		int W = (int)(m_pLoadImage->GetWidth());
		int H = (int)(m_pLoadImage->GetHeight());

		ColorMatrix matrix = {
			-1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			0.0f,  -1.0f,  0.0f, 0.0f, 0.0f,
			0.0f,   0.0f, -1.0f, 0.0f, 0.0f,
			0.0f,   0.0f,  0.0f, 1.0f, 0.0f,
			1.0f,   1.0f,  1.0f, 0.0f, 1.0f };

		clrMatrix = matrix;
		imAtt.SetColorMatrix(&clrMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
		imageGraphics->DrawImage(m_pLoadImage,
			Rect(0, 0, W, H),
			0, 0, W, H,
			UnitPixel,
			&imAtt);

		UpdateImageChange();
	}
}

void CImageView::OnOptionsGrayScale()
{
	if (m_pLoadImage)
	{
		Graphics* imageGraphics = Graphics::FromImage(m_pLoadImage);
		ImageAttributes	imAtt;

		int W = (int)(m_pLoadImage->GetWidth());
		int H = (int)(m_pLoadImage->GetHeight());

		ColorMatrix matrix = {
			0.299f, 0.299f,	0.299f,	0.0f, 0.0f,
			0.587f,	0.587f, 0.587f,	0.0f, 0.0f,
			0.114f,	0.114f,	0.114f, 0.0f, 0.0f,
			0.0f,	0.0f,	0.0f,	1.0f, 0.0f,
			0.0f,	0.0f,	0.0f,	0.0f, 1.0f };

		clrMatrix = matrix;
		imAtt.SetColorMatrix(&clrMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
		imageGraphics->DrawImage(m_pLoadImage,
			Rect(0, 0, W, H),
			0, 0, W, H,
			UnitPixel,
			&imAtt);

		UpdateImageChange();
	}
}

void CImageView::OnOptionsThreshold()
{
	if (m_pLoadImage)
	{
		Graphics* imageGraphics = Graphics::FromImage(m_pLoadImage);
		ImageAttributes	imAtt;

		int W = (int)(m_pLoadImage->GetWidth());
		int H = (int)(m_pLoadImage->GetHeight());

		float factor = 0.5f;
		imAtt.SetThreshold(factor, ColorAdjustTypeBitmap);
		imageGraphics->DrawImage(m_pLoadImage,
			Rect(0, 0, W, H),
			0, 0, W, H,
			UnitPixel,
			&imAtt);

		UpdateImageChange();
	}
}

void CImageView::OnOptionsLighten()
{
	if (m_pLoadImage)
	{
		Graphics* imageGraphics = Graphics::FromImage(m_pLoadImage);
		ImageAttributes	imAtt;

		int W = (int)(m_pLoadImage->GetWidth());
		int H = (int)(m_pLoadImage->GetHeight());

		float factor = 0.2f;
		ColorMatrix matrix = {
			1.0f,   0.0f,   0.0f,   0.0f, 0.0f,
			0.0f,   1.0f,   0.0f,   0.0f, 0.0f,
			0.0f,   0.0f,   1.0f,   0.0f, 0.0f,
			0.0f,   0.0f,   0.0f,   1.0f, 0.0f,
			factor, factor, factor, 0.0f, 1.0f };

		clrMatrix = matrix;
		imAtt.SetColorMatrix(&clrMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
		imageGraphics->DrawImage(m_pLoadImage,
			Rect(0, 0, W, H),
			0, 0, W, H,
			UnitPixel,
			&imAtt);

		UpdateImageChange();
	}
}

void CImageView::OnOptionsDarken()
{
	if (m_pLoadImage)
	{
		Graphics* imageGraphics = Graphics::FromImage(m_pLoadImage);
		ImageAttributes	imAtt;

		int W = (int)(m_pLoadImage->GetWidth());
		int H = (int)(m_pLoadImage->GetHeight());

		float factor = -0.2f;

		ColorMatrix matrix = {
			1.0f,   0.0f,   0.0f,   0.0f, 0.0f,
			0.0f,   1.0f,   0.0f,   0.0f, 0.0f,
			0.0f,   0.0f,   1.0f,   0.0f, 0.0f,
			0.0f,   0.0f,   0.0f,   1.0f, 0.0f,
			factor, factor, factor, 0.0f, 1.0f };

		clrMatrix = matrix;
		imAtt.SetColorMatrix(&clrMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
		imageGraphics->DrawImage(m_pLoadImage,
			Rect(0, 0, W, H),
			0, 0, W, H,
			UnitPixel,
			&imAtt);

		UpdateImageChange();
	}
}

void CImageView::OnOptionsContrast()
{
	if (m_pLoadImage)
	{
		Graphics* imageGraphics = Graphics::FromImage(m_pLoadImage);
		ImageAttributes	imAtt;

		int W = (int)(m_pLoadImage->GetWidth());
		int H = (int)(m_pLoadImage->GetHeight());

		float factor = 1.6f;
		float factorT = 0.5f*(1.0f - factor);

		ColorMatrix matrix = {
			factor,  0.0f,    0.0f,    0.0f, 0.0f,
			0.0f,    factor,  0.0f,    0.0f, 0.0f,
			0.0f,    0.0f,	  factor,  0.0f, 0.0f,
			0.0f,    0.0f,	  0.0f,    1.0f, 0.0f,
			factorT, factorT, factorT, 0.0f, 1.0f };

		clrMatrix = matrix;
		imAtt.SetColorMatrix(&clrMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
		imageGraphics->DrawImage(m_pLoadImage,
			Rect(0, 0, W, H),
			0, 0, W, H,
			UnitPixel,
			&imAtt);

		UpdateImageChange();
	}
}

void CImageView::OnOptionsSharpen()
{
	if (m_pLoadImage)
	{
		Graphics* imageGraphics = Graphics::FromImage(m_pLoadImage);
		ImageAttributes	imAtt;

		int W = (int)(m_pLoadImage->GetWidth());
		int H = (int)(m_pLoadImage->GetHeight());

		float factor = 1.2f;
		float factorT = 0.5f*(1.0f - factor);

		ColorMatrix matrix = {
			factor,  0.0f,	  0.0f,    0.0f, 0.0f,
			0.0f,    factor,  0.0f,    0.0f, 0.0f,
			0.0f,    0.0f,	  factor,  0.0f, 0.0f,
			0.0f,    0.0f,	  0.0f,    1.0f, 0.0f,
			factorT, factorT, factorT, 0.0f, 1.0f };

		clrMatrix = matrix;
		imAtt.SetColorMatrix(&clrMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
		imageGraphics->DrawImage(m_pLoadImage,
			Rect(0, 0, W, H),
			0, 0, W, H,
			UnitPixel,
			&imAtt);

		UpdateImageChange();
	}
}

void CImageView::OnOptionsGamma()
{
	if (m_pLoadImage)
	{
		Graphics* imageGraphics = Graphics::FromImage(m_pLoadImage);
		ImageAttributes	imAtt;

		int W = (int)(m_pLoadImage->GetWidth());
		int H = (int)(m_pLoadImage->GetHeight());

		CGammaDlg dlg;
		dlg.m_gamma = (float)0.5;

		if (dlg.DoModal() == IDOK)
		{
			imAtt.SetGamma((float)dlg.m_gamma, ColorAdjustTypeBitmap);
			imageGraphics->DrawImage(m_pLoadImage,
				Rect(0, 0, W, H),
				0, 0, W, H,
				UnitPixel,
				&imAtt);
		}

		UpdateImageChange();
	}
}

void CImageView::OnOptionsPause()
{
	if (m_pGifHandler)
	{
		m_bPauseToggle = !m_bPauseToggle;
		m_pGifHandler->SetPause(m_bPauseToggle);
	}
}

void CImageView::OnOptionsReturn()
{
	// reset zoom factor to return original image size
	m_fZoomFactor = 0.5;
	UpdatePreviewFileContent();
	AppUtils::UpdateModifiedDocumentTitle(m_pDocument, FALSE);
}

void CImageView::OnOptionsShowSystemMenu()
{
	CString strPathName = m_pDocument->GetPathName();
	if (!PathFileExists(strPathName)) return;
	CMainFrame* pFrame = AppUtils::GetMainFrame();
	if (!pFrame) return;
	pFrame->GetFileExplorerCtrl().ShowExplorerShellContextMenu(strPathName);
}

void CImageView::OnEditCopy()
{
	if (m_pLoadImage)
	{
		CWaitCursor aCursor;
		if (m_pLoadImage->GetLastStatus() != Gdiplus::Ok) return;
		HBITMAP hbitmap;
		Status status = m_pLoadImage->GetHBITMAP(0, &hbitmap);
		if (status != Gdiplus::Ok) return;
		BITMAP bm;
		GetObject(hbitmap, sizeof bm, &bm);
		DIBSECTION ds;
		if (sizeof ds == GetObject(hbitmap, sizeof ds, &ds))
		{
			HDC hDC = ::GetDC(NULL);
			if (!hDC)
			{
				GlobalUnlock(hDC);
				return;
			}
			HBITMAP hbitmap_ddb = CreateDIBitmap(hDC, &ds.dsBmih, CBM_INIT, ds.dsBm.bmBits, (BITMAPINFO*)&ds.dsBmih, DIB_RGB_COLORS);
			::ReleaseDC(NULL, hDC);
			if (OpenClipboard())
			{
				EmptyClipboard();
				SetClipboardData(CF_BITMAP, hbitmap_ddb);
				CloseClipboard();
			}
			DeleteObject(hbitmap_ddb);
		}
		DeleteObject(hbitmap);
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Copy Image] Bitmap data from %s has been copied to clipboard successfuly..."), m_pDocument->GetTitle());
	}
}

void CImageView::OnUpdateOptionsLeftRotate(CCmdUI * pCmdUI)
{
	if (PathUtils::IsGifFile(m_pDocument->GetPathName()))
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CImageView::OnUpdateOptionsRightRotate(CCmdUI * pCmdUI)
{
	if (PathUtils::IsGifFile(m_pDocument->GetPathName()))
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CImageView::OnUpdateOptionsFlip(CCmdUI * pCmdUI)
{
	if (PathUtils::IsGifFile(m_pDocument->GetPathName()))
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CImageView::OnUpdateOptionsMirror(CCmdUI * pCmdUI)
{
	if (PathUtils::IsGifFile(m_pDocument->GetPathName()))
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CImageView::OnUpdateOptionsNegative(CCmdUI * pCmdUI)
{
	if (PathUtils::IsGifFile(m_pDocument->GetPathName()))
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CImageView::OnUpdateOptionsGrayScale(CCmdUI * pCmdUI)
{
	if (PathUtils::IsGifFile(m_pDocument->GetPathName()))
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CImageView::OnUpdateOptionsThreshold(CCmdUI * pCmdUI)
{
	if (PathUtils::IsGifFile(m_pDocument->GetPathName()))
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CImageView::OnUpdateOptionsLighten(CCmdUI * pCmdUI)
{
	if (PathUtils::IsGifFile(m_pDocument->GetPathName()))
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CImageView::OnUpdateOptionsDarken(CCmdUI * pCmdUI)
{
	if (PathUtils::IsGifFile(m_pDocument->GetPathName()))
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CImageView::OnUpdateOptionsContrast(CCmdUI * pCmdUI)
{
	if (PathUtils::IsGifFile(m_pDocument->GetPathName()))
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CImageView::OnUpdateOptionsSharpen(CCmdUI * pCmdUI)
{
	if (PathUtils::IsGifFile(m_pDocument->GetPathName()))
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CImageView::OnUpdateOptionsGamma(CCmdUI * pCmdUI)
{
	if (PathUtils::IsGifFile(m_pDocument->GetPathName()))
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CImageView::OnUpdateOptionsPause(CCmdUI * pCmdUI)
{
	if (PathUtils::IsGifFile(m_pDocument->GetPathName()))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CImageView::OnUpdateEditCopy(CCmdUI * pCmdUI)
{
	if (PathUtils::IsGifFile(m_pDocument->GetPathName()))
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CImageView::OnEditWithMsPaint()
{
	HostManager::HostApplicaton(HostManager::HOST_APP_TYPE::MS_PAINT, L"mspaint.exe", m_pDocument->GetPathName(), TRUE, FALSE);
}

CImageDoc* CImageView::GetImageDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageDoc)));
	return (CImageDoc*)m_pDocument;
}

void CImageView::DoFileSaveAs()
{
	CImageDoc *pDoc = GetImageDocument();
	ASSERT(pDoc);
	if (!pDoc) return;
	pDoc->OnFileSaveAs();
}

void CImageView::UpdateFileLastWriteTime(const CString& strFilePath)
{
	if (strFilePath.IsEmpty() || !PathFileExists(strFilePath)) return;
	FILETIME timeStamp = {};
	WIN32_FILE_ATTRIBUTE_DATA attributes;
	if (GetFileAttributesEx(strFilePath, GetFileExInfoStandard, &attributes) != 0)
	{
		timeStamp = attributes.ftLastWriteTime;
	}
	if (CompareFileTime(&m_FileSystemTime, &timeStamp) != 0)
	{
		m_FileSystemTime = timeStamp;
	}
}

int CImageView::WatchFileSystemState()
{
	m_bIsWatchFileProcessing = TRUE;
	int nFileState = 0;

	CImageDoc *pDoc = GetImageDocument();
	ASSERT(pDoc);
	if (!pDoc)
	{
		m_bIsWatchFileProcessing = FALSE;
		return nFileState | FILE_SYSTEM_STATE::FILE_UNCHANGED;
	}

	WIN32_FILE_ATTRIBUTE_DATA attributes;
	CString strFile = pDoc->GetPathName();
	if (strFile.IsEmpty() || (pDoc->IsPreviewMode() && PathFileExists(strFile)))
	{
		m_bIsWatchFileProcessing = FALSE;
		return nFileState | FILE_SYSTEM_STATE::FILE_UNCHANGED;
	}

	if (!PathFileExists(strFile))
	{
		nFileState |= FILE_SYSTEM_STATE::FILE_DELETED;
	}
	else if (GetFileAttributesEx(strFile, GetFileExInfoStandard, &attributes) != 0)
	{
		BOOL bReadOnly = attributes.dwFileAttributes & FILE_ATTRIBUTE_READONLY;

		if (bReadOnly != m_bDocumentReadOnly)
		{
			m_bDocumentReadOnly = bReadOnly;
			nFileState |= FILE_SYSTEM_STATE::FILE_CHANGED_READONLY;
		}

		if (CompareFileTime(&m_FileSystemTime, &attributes.ftLastWriteTime) != 0)
		{
			m_FileSystemTime = attributes.ftLastWriteTime;
			nFileState |= FILE_SYSTEM_STATE::FILE_CONTENT_MODIFIED;
		}
	}

	if (nFileState != 0) // reload file...
	{
		if (nFileState & FILE_SYSTEM_STATE::FILE_DELETED)
		{
			AfxMessageBoxFormat(MB_ICONWARNING | MB_OK, _T("[System Warning] %s has been deleted from file system by an external operation!"), strFile);
			AppUtils::CloseDeletedDocument(this, strFile);
			return nFileState;
		}
		else
		{
			if (nFileState & FILE_SYSTEM_STATE::FILE_CHANGED_READONLY)
			{
				CString strCurrentTime = OSUtils::DateToCStringABDHMSY(OSUtils::GetCurrentTimeEx());
				if (AppSettingMgr.m_bDisplayMessageBoxForFileChange)
				{
					AfxMessageBox(_T("[System Warning] At ") + strCurrentTime + _T(", ") + strFile + _T(" has changed read only state..."));
				}
				else
				{
					LOG_OUTPUT_MESSAGE_ACTIVE_PANE(_T("> [System Warning] At ") + strCurrentTime + _T(", ") + strFile + _T(" has changed read only state..."), BasicColors::orange);
				}
			}
			if (nFileState & FILE_SYSTEM_STATE::FILE_CONTENT_MODIFIED)
			{			
			}
		}
	}
	m_bIsWatchFileProcessing = FALSE;
	return nFileState;
}

void CImageView::UpdateImageChange()
{
	this->SendMessage(WM_SIZE);
	CImageDoc *pDoc = GetImageDocument();
	ASSERT(pDoc);
	if (pDoc->IsPreviewMode())
	{
		pDoc->SetPreviewMode(FALSE);
	}
	AppUtils::UpdateModifiedDocumentTitle(pDoc);
}
