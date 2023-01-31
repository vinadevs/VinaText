#ifndef _MEMDC_H_
#define _MEMDC_H_

////////////////////////////////////////////////////////////////////////////////
// CMemDCProgressCtrl - memory DC
//
// Author: Keith Rule
// Email:  keithr@europa.com
// Copyright 1996-2002, Keith Rule
//
// You may freely use or modify this code provided this
// copyright is included in all derived versions.
//
// History -	10/03/97	Fixed scrolling bug.
//							Added print support. - KR
//
//				11/03/99	Fixed most common complaint. Added
//							background color fill. - KR
//
//				11/03/99	Added support for mapping modes other than
//							MM_TEXT as suggested by Lee Sang Hun. - KR
//
//				02/11/02	Added support for CScrollView as supplied
//							by Gary Kirkham. - KR
//
//				04/19/06	Modified background fill to try and use
//							correct background brush/color - AGB
//
// This class implements a memory device context which allows
// flicker free drawing.
////////////////////////////////////////////////////////////////////////////////

class CMemDCProgressCtrl : public CDC
{
private:
	BOOL		m_bMemDC;					// TRUE if not printing
	CBitmap		m_MemBitmap;				// offscreen bitmap
	CBitmap*	m_pOldBitmap;				// original bitmap
	CDC*		m_pDC;						// saves CDC passed in constructor
	CRect		m_rect;						// rectangle of drawing area

public:
	// constructor sets up the memory DC
	CMemDCProgressCtrl(CDC* pDC, const CRect* pRect = NULL) : CDC()
	{
		// make sure the call provided a valid device context
		ASSERT(pDC != NULL);

		// save the original device context for later BitBlt()
		m_pDC = pDC;

		// check whether we're printing
		m_bMemDC = !pDC->IsPrinting();

		// get the output rectangle
		if (pRect == NULL)
			pDC->GetClipBox(&m_rect);
		else
			m_rect = *pRect;

		if (m_bMemDC)
		{
			// do the memory DC stuff if not printing

			// create a memory DC
			CreateCompatibleDC(pDC);

			// create new bitmap and save old bitmap
			pDC->LPtoDP(&m_rect);
			m_MemBitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
			m_pOldBitmap = SelectObject(&m_MemBitmap);
			SetMapMode(pDC->GetMapMode());
			SetWindowExt(pDC->GetWindowExt());
			SetViewportExt(pDC->GetViewportExt());
			pDC->DPtoLP(&m_rect);

			// set window origin
			SetWindowOrg(m_rect.left, m_rect.top);
		}
		else
		{
			// make a copy of the relevant parts of the original DC for printing
			m_bPrinting = pDC->m_bPrinting;
			m_hDC = pDC->m_hDC;
			m_hAttribDC = pDC->m_hAttribDC;
		}

		// fill background
		CWnd* pWnd = pDC->GetWindow();
		HWND hWnd = NULL;
		if (pWnd != NULL)
		{
			hWnd = pWnd->m_hWnd;

			if (hWnd != NULL)
			{
				if (GetClassLongPtr(hWnd, GCW_ATOM) == 32770)
				{
					// if window is a dialog box, use dialog background color
					FillSolidRect(m_rect, GetSysColor(COLOR_BTNFACE));
				}
				else
				{
					// try to get background brush for window class
					ULONG_PTR ulpBrush = GetClassLongPtr(hWnd, GCLP_HBRBACKGROUND);
					if (ulpBrush)
					{
						// fill with class background brush
						FillRect(m_rect, CBrush::FromHandle((HBRUSH)ulpBrush));
					}
					else
						hWnd = NULL;
				}
			}
		}
		if (hWnd == NULL)
			FillSolidRect(m_rect, pDC->GetBkColor());
	}

	// destructor copies the contents of the memory DC to the original DC
	~CMemDCProgressCtrl()
	{
		if (m_bMemDC)
		{
			// copy the offscreen bitmap onto the screen
			m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
				this, m_rect.left, m_rect.top, SRCCOPY);

			// restore the original bitmap
			m_pDC->SelectObject(m_pOldBitmap);
		}
		else
		{
			// all we need to do is replace the DC with an illegal value,
			// this keeps us from accidently deleting the handles associated
			// with the CDC that was passed to the constructor
			m_hDC = m_hAttribDC = NULL;
		}
	}

	// allow usage as a pointer
	CMemDCProgressCtrl* operator->() { return this; }

	// allow usage as a pointer
	operator CMemDCProgressCtrl*() { return this; }
};

#endif											//#ifndef _MEMDC_H_
