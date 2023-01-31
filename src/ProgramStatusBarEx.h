//
// TextProgressCtrl.h : header file for CTextProgressCtrl class
//
// Written by Chris Maunder (chris@codeproject.com)
// Copyright 1998-2005.
//
// TextProgressCtrl is a drop-in replacement for the standard
// CProgressCtrl that displays text in a progress control.
//
// Homepage: http://www.codeproject.com/miscctrl/text_progressctrl.asp
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed by any means PROVIDING it is not sold for
// profit without the author's written consent, and providing that this
// notice and the author's name is included. If the source code in
// this file is used in any commercial application then an email to
// me would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to your
// computer, causes your pet cat to fall ill, increases baldness or
// makes you car start emitting strange noises when you start it up.
//
// Expect bugs.
//
// Please use and enjoy. Please let me know of any bugs/mods/improvements
// that you have found/implemented and I will fix/incorporate them into this
// file.
//
// See file TextProgressCtrl.cpp for modification history.
//

#pragma once

#include "VinaTextProgressBar.h"
#include "TextProgressCtrl.h"

class CVinaTextStatusBar : public CAbstractProgressBar
{
public:
	CVinaTextStatusBar();
	virtual ~CVinaTextStatusBar();
	virtual void		CreateProgressBar();
	virtual void		ColoriseProgressBarBuild();
	virtual void		ColoriseProgressBarSearch();
	virtual void		DestroyProgressBar();
	virtual void		SetWindowText( LPCTSTR lpszText );
	virtual int			SetPos(int nPos);
	virtual int			StepIt();
	virtual void		SetRange(int nLower, int nUpper);
	virtual int			OffsetPos(int nPos);
	virtual int			SetStep(int nStep);
	virtual void		SetForeColour(COLORREF col);
	virtual void		SetBkColour(COLORREF col);
	virtual void		SetTextForeColour(COLORREF col);
	virtual void		SetTextBkColour(COLORREF col);
	virtual COLORREF	GetForeColour();
	virtual COLORREF	GetBkColour();
	virtual COLORREF	GetTextForeColour();
	virtual COLORREF	GetTextBkColour();
	virtual void		SetShowText(BOOL bShow);
	virtual int			GetPos();
protected:
	CProgressCtrlEx*	m_pProgressBar;
};
