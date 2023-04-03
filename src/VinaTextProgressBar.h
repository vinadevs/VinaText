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
#include <afxmt.h>

class CAbstractProgressBar
{
protected:
	CAbstractProgressBar();
	virtual ~CAbstractProgressBar();

public:
	static CAbstractProgressBar* m_pSingleInstance;

	virtual void		CreateProgressBar()=0;
	virtual void		ColoriseProgressBarBuild()=0;
	virtual void		ColoriseProgressBarSearch()=0;
	virtual void		DestroyProgressBar()=0;
	virtual int			SetPos(int nPos)=0;
	virtual void		SetRange(int nLower, int nUpper)=0;
	virtual int			StepIt()=0;
	virtual void		SetWindowText( LPCTSTR lpszText )=0;
	virtual int			OffsetPos(int nPos)=0;
	virtual int			SetStep(int nStep)=0;
	virtual void		SetForeColour(COLORREF col)=0;
	virtual void		SetBkColour(COLORREF col)=0;
	virtual void		SetTextForeColour(COLORREF col)=0;
	virtual void		SetTextBkColour(COLORREF col)=0;
	virtual COLORREF	GetForeColour()=0;
	virtual COLORREF	GetBkColour()=0;
	virtual COLORREF	GetTextForeColour()=0;
	virtual COLORREF	GetTextBkColour()=0;
	virtual void		SetShowText(BOOL bShow)=0;
	virtual int			GetPos()=0;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////

enum class PROGRESS_BAR_TYPE : unsigned int
{
	TYPE_BUILD = 0,
	TYPE_SEARCH,
};

class CVinaTextProgressBar
{
public:
	CVinaTextProgressBar(int nLower, int nUpper, CString strText = _T(""), PROGRESS_BAR_TYPE type = PROGRESS_BAR_TYPE::TYPE_BUILD);
	~CVinaTextProgressBar();

	void SetPos(int nPos);	
	int  GetPos();
	void SetStep(int nStep);
	int  GetStep();
	void StepIt();
	void SetText( CString const& strText );
	void BeginSub(int nUpper);	
	void EndSub();			
	CEvent m_CancelEvent;
	CEvent m_FinishEvent;
	CWinThread *m_ptrThread;
	void CancelThread();
	bool IsCancelled();
	bool m_bCancelled;

protected:	
	int m_nLower;
	int m_nUpper;
	int m_nPos;
	int m_nStep;
	CString m_strText;
	double m_dLowerGlobal;
	double m_dUpperGlobal;

	int m_nSubLower;
	int m_nSubUpper;
	CVinaTextProgressBar* m_pParentBar = nullptr;
};
