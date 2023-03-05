/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CGotoDlg 

#include "UndoRedoEditControl.h"

class CScrollHelper;

class CGotoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGotoDlg)
public:
	CGotoDlg(CWnd* pParent = NULL);  
	virtual ~CGotoDlg();
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	enum { IDD = IDD_POS };

	void InitGotoInfoFromEditor(CString strSearchWhat);
	void InitGotoRangeByDocument();
	void ClearAll();
	void UpdateUIVisual();

protected:
	std::unique_ptr<CScrollHelper> m_pScrollHelper;
	CUndoRedoEditControl m_EditPosition;
	CUndoRedoEditControl m_EditLine;
	CUndoRedoEditControl m_EditPointX;
	CUndoRedoEditControl m_EditPointY;

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK() {}
	virtual void OnCancel() {}
	virtual BOOL OnInitDialog();
	afx_msg void OnGotoLine();
	afx_msg void OnGotoPosition();
	afx_msg void OnGotoPoint();
	afx_msg void OnEnChangeEditLineNum();
	afx_msg void OnEnChangeEditPositionNum();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedEditorLineGoPreviousParah();
	afx_msg void OnBnClickedEditorLineGoNextParah();
	afx_msg void OnBnClickedEditorLineGoToCaret();
};