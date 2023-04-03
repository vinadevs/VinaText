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

#include "StdAfx.h"
#include "ProgramStatusBarEx.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning(disable:4996)

CVinaTextStatusBar g_instance;

CVinaTextStatusBar::CVinaTextStatusBar()
{
	m_pProgressBar = NULL;
}

CVinaTextStatusBar::~CVinaTextStatusBar()
{
	if( m_pProgressBar )
	{
		ASSERT(FALSE);	
		DELETE_POINTER_CPP(m_pProgressBar)
	}
}

void CVinaTextStatusBar::CreateProgressBar()
{
	CWinApp* pApp = AfxGetApp();
	CMainFrame* pMainFrame = (CMainFrame*)pApp->GetMainWnd();
	ASSERT( pMainFrame );

	if( m_pProgressBar )
	{
		ASSERT(FALSE);
		DELETE_POINTER_CPP(m_pProgressBar)
	}
	m_pProgressBar = new CProgressCtrlEx;
	CMFCStatusBar* pStatusBar = pMainFrame->GetStatusBar();

	CRect rect;
	pStatusBar->GetClientRect(rect );
	rect.right = rect.Width();
	
	rect.InflateRect(0, -2);
	m_pProgressBar->Create( WS_CHILD | WS_VISIBLE | PBS_SMOOTH, rect, pStatusBar, 1 );
	m_pProgressBar->SetShowText( TRUE );
}

void CVinaTextStatusBar::ColoriseProgressBarBuild()
{
	if (!m_pProgressBar)
	{
		return;
	}
	m_pProgressBar->SetBkColor(RGB(255, 69, 0));
	m_pProgressBar->SetBkColour(RGB(255, 255, 255));
	m_pProgressBar->SetBarColor(RGB(255, 69, 0));
	m_pProgressBar->SetForeColour(RGB(255, 69, 0));
}

void CVinaTextStatusBar::ColoriseProgressBarSearch()
{
	if (!m_pProgressBar)
	{
		return;
	}
	m_pProgressBar->SetBkColor(RGB(0, 160, 0));
	m_pProgressBar->SetBkColour(RGB(255, 255, 255));
	m_pProgressBar->SetBarColor(RGB(0, 160, 0));
	m_pProgressBar->SetForeColour(RGB(0, 160, 0));
}

void CVinaTextStatusBar::DestroyProgressBar()
{
	if (m_pProgressBar)
	{
		DELETE_POINTER_CPP(m_pProgressBar)
	}
}

void CVinaTextStatusBar::SetWindowText( LPCTSTR lpszText )
{
	if( m_pProgressBar )
		m_pProgressBar->SetWindowText( lpszText );

	ASSERT( m_pProgressBar );
}

int	CVinaTextStatusBar::SetPos(int nPos)
{
	if( m_pProgressBar )
		return m_pProgressBar->SetPos( nPos );

	ASSERT( m_pProgressBar );
	return 0;
}

int	CVinaTextStatusBar::StepIt()
{
	if( m_pProgressBar )
		return m_pProgressBar->StepIt();

	ASSERT( m_pProgressBar );
	return 0;
}

void CVinaTextStatusBar::SetRange(int nLower, int nUpper)
{
	if( m_pProgressBar )
		m_pProgressBar->SetRange( nLower, nUpper );

	ASSERT( m_pProgressBar );
}

int	CVinaTextStatusBar::OffsetPos(int nPos)
{
	if( m_pProgressBar )
		return m_pProgressBar->OffsetPos( nPos );

	ASSERT( m_pProgressBar );
	return 0;
}

int	CVinaTextStatusBar::SetStep(int nStep)
{
	if( m_pProgressBar )
		return m_pProgressBar->SetStep( nStep );

	ASSERT( m_pProgressBar );
	return 0;
}

void CVinaTextStatusBar::SetForeColour(COLORREF col)
{
	if( m_pProgressBar )
		m_pProgressBar->SetForeColour( col );

	ASSERT( m_pProgressBar );
}

void CVinaTextStatusBar::SetBkColour(COLORREF col)
{
	if( m_pProgressBar )
		m_pProgressBar->SetBkColour( col );

	ASSERT( m_pProgressBar );
}

void CVinaTextStatusBar::SetTextForeColour(COLORREF col)
{
	if( m_pProgressBar )
		m_pProgressBar->SetTextForeColour( col );

	ASSERT( m_pProgressBar );
}

void CVinaTextStatusBar::SetTextBkColour(COLORREF col)
{
	if( m_pProgressBar )
		m_pProgressBar->SetTextBkColour( col );

	ASSERT( m_pProgressBar );
}

COLORREF CVinaTextStatusBar::GetForeColour()
{
	if( m_pProgressBar )
		return m_pProgressBar->GetForeColour();

	ASSERT( m_pProgressBar );
	return 0;
}

COLORREF CVinaTextStatusBar::GetBkColour()
{
	if( m_pProgressBar )
		return m_pProgressBar->GetBkColour();

	ASSERT( m_pProgressBar );
	return 0;
}

COLORREF CVinaTextStatusBar::GetTextForeColour()
{
	if( m_pProgressBar )
		return m_pProgressBar->GetTextForeColour();

	ASSERT( m_pProgressBar );
	return 0;
}

COLORREF CVinaTextStatusBar::GetTextBkColour()
{
	if( m_pProgressBar )
		return m_pProgressBar->GetTextBkColour();

	ASSERT( m_pProgressBar );
	return 0;
}

void CVinaTextStatusBar::SetShowText(BOOL bShow)
{
	if( m_pProgressBar )
		m_pProgressBar->SetShowText( bShow );

	ASSERT( m_pProgressBar );
}

int CVinaTextStatusBar::GetPos()
{
	if( m_pProgressBar )
		return m_pProgressBar->GetPos();

	ASSERT( m_pProgressBar );
	return 0;
}

