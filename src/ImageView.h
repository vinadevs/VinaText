/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CImageView view

#include "GifHandler.h"
#include "ViewBase.h"

class CImageDoc;

enum SaveImageType
{
	Undefined = -1,
	Png = 0,
	Jpeg = 1,
	Bmp = 2,
	Gif = 3,
	Tiff = 4,
};

class CImageView : public CViewBase
{
protected:
	CImageView(); // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CImageView)

// Attributes
protected:
	// GDI+ controls
	CGifHandler* m_pGifHandler;
	Bitmap*  m_pLoadImage;
	CComPtr<IStream> m_ImageStream; // must keep the stream open for the lifetime of m_pLoadImage

	CStatic  m_wndCanvas; // image frame
	float	 m_fZoomFactor;
	bool	 m_bPauseToggle;
	FILETIME m_FileSystemTime = {};
	BOOL m_bIsWatchFileProcessing = FALSE;
	BOOL m_bDocumentReadOnly = FALSE;

public:
	BOOL GetImageEncoderClsid(const WCHAR* format, CLSID* pClsid);
	BOOL SaveImage(const CString& szPath);
	CImageDoc * GetImageDocument() const;
	SaveImageType GetImageTypeFromFile(const CString& szPath);
	HBITMAP GetCurrentBitmap();

// Overrides
protected:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();
	void DoFileSaveAs();
	virtual void UpdateFileLastWriteTime(const CString& strFilePath);
	virtual int WatchFileSystemState();
	void UpdateImageChange();

// Implementation
public:
	virtual void UpdatePreviewFileContent();
	virtual ~CImageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	afx_msg void OnSetFocus(CWnd * pOldWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnOptionsZoomUp();
	afx_msg void OnOptionsZoomDown();
	afx_msg void OnOptionsLeftRotate();
	afx_msg void OnOptionsRightRotate();
	afx_msg void OnOptionsFlip();
	afx_msg void OnOptionsMirror();
	afx_msg void OnOptionsNegative();
	afx_msg void OnOptionsGrayScale();
	afx_msg void OnOptionsThreshold();
	afx_msg void OnOptionsLighten();
	afx_msg void OnOptionsDarken();
	afx_msg void OnOptionsContrast();
	afx_msg void OnOptionsSharpen();
	afx_msg void OnOptionsGamma();
	afx_msg void OnOptionsPause();
	afx_msg void OnOptionsReturn();
	afx_msg void OnOptionsShowSystemMenu();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI * pCmdUI);
	afx_msg void OnUpdateOptionsLeftRotate(CCmdUI * pCmdUI);
	afx_msg void OnUpdateOptionsRightRotate(CCmdUI * pCmdUI);
	afx_msg void OnUpdateOptionsFlip(CCmdUI * pCmdUI);
	afx_msg void OnUpdateOptionsMirror(CCmdUI * pCmdUI);
	afx_msg void OnUpdateOptionsNegative(CCmdUI * pCmdUI);
	afx_msg void OnUpdateOptionsGrayScale(CCmdUI * pCmdUI);
	afx_msg void OnUpdateOptionsThreshold(CCmdUI * pCmdUI);
	afx_msg void OnUpdateOptionsLighten(CCmdUI * pCmdUI);
	afx_msg void OnUpdateOptionsDarken(CCmdUI * pCmdUI);
	afx_msg void OnUpdateOptionsContrast(CCmdUI * pCmdUI);
	afx_msg void OnUpdateOptionsSharpen(CCmdUI * pCmdUI);
	afx_msg void OnUpdateOptionsGamma(CCmdUI * pCmdUI);
	afx_msg void OnUpdateOptionsPause(CCmdUI * pCmdUI);
	DECLARE_MESSAGE_MAP()
};
