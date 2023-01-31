#ifndef _TEXTPROGRESSCTRL_H_
#define _TEXTPROGRESSCTRL_H_

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

////////////////////////////////////////////////////////////////////////////////
//
// To set the range (16 bit):
//		call	SetRange(WORD wLower, WORD wUpper)
//		or		SendMessage(PBM_SETRANGE, 0, MAKELPARAM(wLower, wUpper))
//		or		::SendMessage(m_hWnd, PBM_SETRANGE, 0, MAKELPARAM(wLower, wUpper))
//
// To set the position:
//		call	SetPos(int nNewPos)
//		or		SendMessage(PBM_SETPOS, (WPARAM)nNewPos, 0)
//		or		::SendMessage(m_hWnd, PBM_SETPOS, (WPARAM)nNewPos, 0)
//
// To set the position using a delta value:
//		call	OffsetPos(int nIncrement)
//		or		SendMessage(PBM_DELTAPOS, (WPARAM)nIncrement, 0)
//		or		::SendMessage(m_hWnd, PBM_DELTAPOS, (WPARAM)nIncrement, 0)
//
// To set the step increment size:
//		call	SetStep(int nStepInc)
//		or		SendMessage(PBM_SETSTEP, (WPARAM)nStepInc, 0)
//		or		::SendMessage(m_hWnd, PBM_SETSTEP, (WPARAM)nStepInc, 0)
//
// To step the position by the step increment size:
//		call	StepIt()
//		or		SendMessage(PBM_STEPIT, 0, 0)
//		or		::SendMessage(m_hWnd, PBM_STEPIT, 0, 0)
//
// To set the range (32 bit):
//		call	SetRange32(int nLowLim, int nHighLim)
//		or		SendMessage(PBM_SETRANGE32, (WPARAM)nLowLim, (LPARAM)nHighLim)
//		or		::SendMessage(m_hWnd, PBM_SETRANGE32, (WPARAM)nLowLim, (LPARAM)nHighLim)
//
// To get the current range:
//		call	GetRange(BOOL bWhichLimit, PBRANGE* pPBRange)
//		or		SendMessage(PBM_GETRANGE, (WPARAM)bWhichLimit, (LPARAM)pBBRange)
//		or		::SendMessage(m_hWnd, PBM_GETRANGE, (WPARAM)bWhichLimit, (LPARAM)pBBRange)
//
// To get the current position:
//		call	GetPos()
//		or		SendMessage(PBM_GETPOS, 0, 0)
//		or		::SendMessage(m_hWnd, PBM_GETPOS, 0, 0)
//
// To set the bar color:
//		call	SetBarColor(COLORREF crBar)
//		or		SendMessage (PBM_SETBARCOLOR, 0, (LPARAM)crBar)
//		or		::SendMessage (m_hwnd, PBM_SETBARCOLOR, 0, (LPARAM)crBar)
//
// To get the bar color:
//		call	GetBarColor()
//		or		SendMessage (PBM_GETBARCOLOR, 0, 0)
//		or		::SendMessage (m_hwnd, PBM_GETBARCOLOR, 0, 0)
//
// To set the bar background color:
//		call	SetBkColor(COLORREF crBarBk)
//		or		SetBarBkColor(COLORREF crBarBk)
//		or		SendMessage (PBM_SETBARBKCOLOR, 0, (LPARAM)crBarBk)
//		or		::SendMessage (m_hwnd, PBM_SETBARBKCOLOR, 0, (LPARAM)crBarBk)
//
// To get the bar background color:
//		call	GetBarBkColor()
//		or		SendMessage (PBM_GETBARBKCOLOR, 0, 0)
//		or		::SendMessage (m_hwnd, PBM_GETBARBKCOLOR, 0, 0)
//
// To operate on the bar text:
//		use any of the normal CWnd window text functions, such as
//		SetWindowText, GetWindowText, GetWindowTextLength, SetFont and GetFont
//
// To set the text color:
//		call	SetTextColor(COLORREF crTextClr)
//		or		SendMessage (PBM_SETTEXTCOLOR, 0, (LPARAM)crTextClr)
//		or		::SendMessage (m_hwnd, PBM_SETTEXTCOLOR, 0, (LPARAM)crTextClr)

// To get the text color:
//		call	GetTextColor()
//		or		SendMessage (PBM_GETTEXTCOLOR, 0, 0)
//		or		::SendMessage (m_hwnd, PBM_GETTEXTCOLOR, 0, 0)
//
// To set the text background color:
//		call	SetTextBkColor(COLORREF crTextBkClr)
//		or		SendMessage (PBM_SETTEXTBKCOLOR, 0, (LPARAM)crTextBkClr)
//		or		::SendMessage (m_hwnd, PBM_SETTEXTBKCOLOR, 0, (LPARAM)crTextBkClr)
//
// To get the text background color:
//		call	GetTextBkColor()
//		or		SendMessage (PBM_GETTEXTBKCOLOR, 0, 0)
//		or		::SendMessage (m_hwnd, PBM_GETTEXTBKCOLOR, 0, 0)
//
// To show or hide percentage complete:
//		call	SetShowPercent(BOOL bShow)
//		or		SendMessage(PBM_SETSHOWPERCENT, (WPARAM)bShow, 0)
//		or		::SendMessage(m_hWnd, PBM_SETSHOWPERCENT, (WPARAM)bShow, 0)
//
// To set the text alignment mode:
//		call	AlignText(DWORD dwAlignment), where dwAlignment = DT_LEFT, DT_RIGHT or DT_CENTER
//		or		SendMessage(PBM_ALIGNTEXT, (WPARAM)dwAlignment, 0)
//		or		SendMessage(m_hWnd, PBM_ALIGNTEXT, (WPARAM)dwAlignment, 0)
//
// To turn on/off marquee mode
//		call	SetMarquee(BOOL bOn, int nMsecBetweenUpdate)
//		or		SendMessage(PBM_SETMARQUEE, (WPARAM)bOn, (LPARAM)nMsecBetweenUpdate)
//		or		::SendMessage(m_hWnd, PBM_SETMARQUEE, (WPARAM)bOn, (LPARAM)nMsecBetweenUpdate)
//
// To set marquee options
//		call	SetMarqueeOptions(int nBarSize)
//		or		SendMessage(PBM_SETMARQUEEOPTIONS, (WPARAM)nBarSize, 0)
//		or		::SendMessage(m_hWnd, PBM_SETMARQUEEOPTIONS, (WPARAM)nBarSize, 0)
//
////////////////////////////////////////////////////////////////////////////////


// setup aliases using "Colour" instead of "Color"
#define SetBarColour		SetBarColor
#define GetBarColour		GetBarColor
#define SetBgColour			SetBarBkColor
#define GetBgColour			GetBarBkColor
#define SetTextColour		SetTextColor
#define GetTextColour		GetTextColor

// define progress bar stuff that may not be elsewhere defined (if needed)
#ifndef PBS_SMOOTH
	#define PBS_SMOOTH			0x01
#endif
#ifndef PBS_VERTICAL
	#define PBS_VERTICAL		0x04
#endif
#ifndef PBS_MARQUEE
	#define PBS_MARQUEE			0x08
#endif
#ifndef PBM_SETRANGE32
	#define PBM_SETRANGE32		(WM_USER+6)
	typedef struct
	{
		int iLow;
		int iHigh;
	} PBRANGE, *PPBRANGE;
#endif
#ifndef PBM_GETRANGE
	#define PBM_GETRANGE		(WM_USER+7)
#endif
#ifndef PBM_GETPOS
	#define PBM_GETPOS			(WM_USER+8)
#endif
#ifndef PBM_SETBARCOLOR
	#define PBM_SETBARCOLOR		(WM_USER+9)
#endif
#ifndef PBM_SETBKCOLOR
	#define PBM_SETBKCOLOR		CCM_SETBKCOLOR
#endif
#ifndef PBM_SETMARQUEE
	#define PBM_SETMARQUEE		(WM_USER+10)
#endif

// setup message codes for new messages
#define PBM_SETTEXTCOLOR		(WM_USER+102)
#define PBM_GETTEXTCOLOR		(WM_USER+103)
#define PBM_SETTEXTBKCOLOR		(WM_USER+104)
#define PBM_GETTEXTBKCOLOR		(WM_USER+105)
#define PBM_SETSHOWPERCENT		(WM_USER+106)
#define PBM_ALIGNTEXT			(WM_USER+107)
#define PBM_SETMARQUEEOPTIONS	(WM_USER+108)


////////////////////////////////////////////////////////////////////////////////
// CTextProgressCtrl class

class CTextProgressCtrl : public CProgressCtrl
{
	// Constructor / Destructor
	public:
		CTextProgressCtrl();
		virtual ~CTextProgressCtrl();

	// Operations
	public:
		inline COLORREF SetBarColor(COLORREF crBarClr = CLR_DEFAULT)
			{ ASSERT(::IsWindow(m_hWnd)); return ((COLORREF) ::SendMessage(m_hWnd, PBM_SETBARCOLOR, 0, (LPARAM)crBarClr)); }
		inline COLORREF GetBarColor() const
			{ ASSERT(::IsWindow(m_hWnd)); return ((COLORREF) ::SendMessage(m_hWnd, PBM_GETBARCOLOR, 0, 0)); }
		inline COLORREF SetBarBkColor(COLORREF crBarBkClr = CLR_DEFAULT)
			{ ASSERT(::IsWindow(m_hWnd)); return ((COLORREF) ::SendMessage(m_hWnd, PBM_SETBKCOLOR, 0, (LPARAM)crBarBkClr)); }
		inline COLORREF GetBarBkColor() const
			{ ASSERT(::IsWindow(m_hWnd)); return ((COLORREF) ::SendMessage(m_hWnd, PBM_GETBKCOLOR, 0, 0)); }
		inline COLORREF SetTextColor(COLORREF crTextClr = CLR_DEFAULT)
			{ ASSERT(::IsWindow(m_hWnd)); return ((COLORREF) ::SendMessage(m_hWnd, PBM_SETTEXTCOLOR, 0, (LPARAM)crTextClr)); }
		inline COLORREF GetTextColor() const
			{ ASSERT(::IsWindow(m_hWnd)); return ((COLORREF) ::SendMessage(m_hWnd, PBM_GETTEXTCOLOR, 0, 0)); }
		inline COLORREF SetTextBkColor(COLORREF crTextBkClr = CLR_DEFAULT)
			{ ASSERT(::IsWindow(m_hWnd)); return ((COLORREF) ::SendMessage(m_hWnd, PBM_SETTEXTBKCOLOR, 0, (LPARAM)crTextBkClr)); }
		inline COLORREF GetTextBkColor() const
			{ ASSERT(::IsWindow(m_hWnd)); return ((COLORREF) ::SendMessage(m_hWnd, PBM_GETTEXTBKCOLOR, 0, 0)); }
		inline BOOL SetShowPercent(BOOL bShow)
			{ ASSERT(::IsWindow(m_hWnd)); return ((BOOL) ::SendMessage(m_hWnd, PBM_SETSHOWPERCENT, (WPARAM)bShow, 0)); }
		inline DWORD AlignText(DWORD dwAlignment = DT_CENTER)
			{ ASSERT(::IsWindow(m_hWnd)); return ((DWORD) ::SendMessage(m_hWnd, PBM_ALIGNTEXT, (WPARAM)dwAlignment, 0)); }
		inline BOOL SetMarquee(BOOL bOn, UINT uMsecBetweenUpdate)
			{ ASSERT(::IsWindow(m_hWnd)); return ((BOOL) ::SendMessage(m_hWnd, PBM_SETMARQUEE, (WPARAM)bOn, (LPARAM)uMsecBetweenUpdate)); }
		inline int SetMarqueeOptions(int nBarSize)
			{ ASSERT(::IsWindow(m_hWnd)); return ((BOOL) ::SendMessage(m_hWnd, PBM_SETMARQUEEOPTIONS, (WPARAM)nBarSize, 0)); }

	// Generated message map functions
	protected:
		//{{AFX_MSG(CTextProgressCtrl)
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg void OnPaint();
		afx_msg void OnTimer(UINT_PTR nIDEvent);
		//}}AFX_MSG

		// handlers for shell progress control standard messages
		afx_msg LRESULT OnSetRange(WPARAM, LPARAM lparamRange);
		afx_msg LRESULT OnSetPos(WPARAM nNewPos, LPARAM);
		afx_msg LRESULT OnOffsetPos(WPARAM nIncrement, LPARAM);
		afx_msg LRESULT OnSetStep(WPARAM nStepInc, LPARAM);
		afx_msg LRESULT OnStepIt(WPARAM, LPARAM);
		afx_msg LRESULT OnSetRange32(WPARAM nLowLim, LPARAM nHighLim);
		afx_msg LRESULT OnGetRange(WPARAM bWhichLimit, LPARAM pPBRange);
		afx_msg LRESULT OnGetPos(WPARAM, LPARAM);
		afx_msg LRESULT OnSetBarColor(WPARAM, LPARAM crBar);
		afx_msg LRESULT OnSetBarBkColor(WPARAM, LPARAM crBarBk);

		// new handlers added by this class
		afx_msg LRESULT OnGetBarColor(WPARAM, LPARAM);
		afx_msg LRESULT OnGetBarBkColor(WPARAM, LPARAM);
		afx_msg LRESULT OnSetTextColor(WPARAM, LPARAM crText);
		afx_msg LRESULT OnGetTextColor(WPARAM, LPARAM);
		afx_msg LRESULT OnSetTextBkColor(WPARAM, LPARAM crTextBk);
		afx_msg LRESULT OnGetTextBkColor(WPARAM, LPARAM);
		afx_msg LRESULT OnSetShowPercent(WPARAM bShow, LPARAM);
		afx_msg	LRESULT OnAlignText(WPARAM dwAlignment, LPARAM);
		afx_msg LRESULT OnSetMarquee(WPARAM bOn, LPARAM nMsecBetweenUpdate);
		afx_msg LRESULT OnSetMarqueeOptions(WPARAM nBarSize, LPARAM);

		// helper functions
		void CreateVerticalFont();
		void CommonPaint();

		DECLARE_MESSAGE_MAP()

		// variables for class
		BOOL		m_bShowPercent;				// true to show percent complete as text
		CFont		m_VerticalFont;				// font for vertical progress bars
		COLORREF	m_crBarClr, m_crBarBkClr;	// bar colors
		COLORREF	m_crTextClr, m_crTextBkClr;	// text colors
		DWORD		m_dwTextStyle;				// alignment style for text
		int			m_nPos;						// current position within range
		int			m_nStepSize;				// current step size
		int			m_nMin, m_nMax;				// minimum and maximum values of range
		int			m_nMarqueeSize;				// size of sliding marquee bar in percent (0 - 100)
};

////////////////////////////////////////////////////////////////////////////////

class CProgressCtrlEx : public CProgressCtrl
{
public:
	CProgressCtrlEx();
	virtual ~CProgressCtrlEx();

	int			SetPos(int nPos);
	int			StepIt();
	void		SetRange(int nLower, int nUpper);
	int			OffsetPos(int nPos);
	int			SetStep(int nStep);
	void		SetForeColour(COLORREF col);
	void		SetBkColour(COLORREF col);
	void		SetTextForeColour(COLORREF col);
	void		SetTextBkColour(COLORREF col);
	COLORREF	GetForeColour();
	COLORREF	GetBkColour();
	COLORREF	GetTextForeColour();
	COLORREF	GetTextBkColour();
	void		SetShowText(BOOL bShow);
	int			GetPos();

protected:
	int	     m_nPos, m_nStepSize, m_nMax, m_nMin;
	CString	 m_strText;
	BOOL	 m_bShowText;
	int		 m_nBarWidth;
	CString  m_strFontName;
	int      m_nBold;
	COLORREF m_colFore, m_colBk, m_colTextFore, m_colTextBk;

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnSetText(WPARAM, LPARAM);
	afx_msg LRESULT OnGetText(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

#endif											//#ifndef _TEXTPROGRESSCTRL_H_
