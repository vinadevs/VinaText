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
#include "VinaTextProgressBar.h"
#include "MultiThreadWorker.h"

CAbstractProgressBar* CAbstractProgressBar::m_pSingleInstance = nullptr;

CAbstractProgressBar::CAbstractProgressBar()
{
	ASSERT(m_pSingleInstance == nullptr);
	m_pSingleInstance = this;
}

CAbstractProgressBar::~CAbstractProgressBar()
{
	ASSERT(m_pSingleInstance);
	m_pSingleInstance = nullptr;
}

static CVinaTextProgressBar* _pVinaTextProgressBar = nullptr;

//////////////////////////////////////////////////////////////////////////
// CVinaTextProgressBar Implementation

CVinaTextProgressBar::CVinaTextProgressBar( int nLower, int nUpper, CString strText, PROGRESS_BAR_TYPE type)
	: m_nLower(nLower), m_nUpper(nUpper), m_nSubLower(nLower), m_nSubUpper(nUpper), m_nPos(0), m_nStep(1), m_strText(strText)	
	, m_ptrThread(nullptr)
	, m_bCancelled(false)
{
	m_dUpperGlobal = 0.0;
	m_dLowerGlobal = 0.0;

	m_dLowerGlobal = double(nLower);
	m_dUpperGlobal = double(nUpper);

	if( CAbstractProgressBar::m_pSingleInstance )
	{
		m_pParentBar = _pVinaTextProgressBar;
		if( m_pParentBar == nullptr )
		{			
			CAbstractProgressBar::m_pSingleInstance->CreateProgressBar();
			CAbstractProgressBar::m_pSingleInstance->SetRange(nLower,nUpper);	
			CAbstractProgressBar::m_pSingleInstance->SetWindowText(strText);	
		}
		else 
		{			
			double dRange = ( m_pParentBar->m_dUpperGlobal - m_pParentBar->m_dLowerGlobal );				
			m_dLowerGlobal =  ( double(m_pParentBar->m_nSubLower - m_pParentBar->m_nLower) /
				double(m_pParentBar->m_nUpper - m_pParentBar->m_nLower) ) * dRange + m_pParentBar->m_dLowerGlobal;
			m_dUpperGlobal =  ( double(m_pParentBar->m_nSubUpper - m_pParentBar->m_nLower) /
				double(m_pParentBar->m_nUpper - m_pParentBar->m_nLower) ) * dRange + m_pParentBar->m_dLowerGlobal;
		}			

		if (type == PROGRESS_BAR_TYPE::TYPE_BUILD)
		{
			CAbstractProgressBar::m_pSingleInstance->ColoriseProgressBarBuild();
		}
		else if (type == PROGRESS_BAR_TYPE::TYPE_SEARCH)
		{
			CAbstractProgressBar::m_pSingleInstance->ColoriseProgressBarSearch();
		}

		_pVinaTextProgressBar = this;
	}
}

CVinaTextProgressBar::~CVinaTextProgressBar()
{
	if( m_pParentBar == nullptr )
	{
		if (CAbstractProgressBar::m_pSingleInstance)
			CAbstractProgressBar::m_pSingleInstance->DestroyProgressBar();

		_pVinaTextProgressBar = nullptr;
	}
	else
	{
		if (ThreadWorkerMgr.IsRunning() || ThreadWorkerMgr.IsDebuggerRunning())
		{
			CAbstractProgressBar::m_pSingleInstance->ColoriseProgressBarBuild();
			CAbstractProgressBar::m_pSingleInstance->SetPos(100);
		}
	}
	_pVinaTextProgressBar = m_pParentBar;
}

void CVinaTextProgressBar::SetPos( int nPos )
{	
	if( CAbstractProgressBar::m_pSingleInstance && m_nUpper - m_nLower > 0 )
	{
		nPos = min(nPos,m_nUpper);
		double dFraction =  double(nPos - m_nLower) / double(m_nUpper - m_nLower);
		double dRange = ( m_dUpperGlobal - m_dLowerGlobal );

		int nPosGlobalCur = int( ( double(  nPos - m_nLower) /
			double(m_nUpper - m_nLower) ) * dRange + m_dLowerGlobal);
		int nPosGlobalPrv = int( ( double(m_nPos - m_nLower) /
			double(m_nUpper - m_nLower) ) * dRange + m_dLowerGlobal);
		if( nPosGlobalPrv != nPosGlobalCur )
		{
			CAbstractProgressBar::m_pSingleInstance->SetPos( nPosGlobalCur );
		}	
		m_nPos = nPos;
	}
}

void CVinaTextProgressBar::SetText( CString const& strText )
{
	if( CAbstractProgressBar::m_pSingleInstance )
		CAbstractProgressBar::m_pSingleInstance->SetWindowText(strText);
}

int CVinaTextProgressBar::GetPos()
{
	return m_nPos;
}

void CVinaTextProgressBar::SetStep( int nStep )
{
	m_nStep = nStep;
}

int CVinaTextProgressBar::GetStep()
{
	return m_nStep;
}

void CVinaTextProgressBar::StepIt()
{
	SetPos( m_nPos + m_nStep );
}

void CVinaTextProgressBar::BeginSub( int nUpper )
{
	m_nSubLower = min(m_nPos, nUpper);
	m_nSubUpper = nUpper;
}

void CVinaTextProgressBar::EndSub()
{
	SetPos(m_nSubUpper);
}

void CVinaTextProgressBar::CancelThread()
{
	m_bCancelled = true;
}

bool CVinaTextProgressBar::IsCancelled()
{
	return m_bCancelled;
}
