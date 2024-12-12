/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "TreeHelper.h"

#define DEFAULT_FOLDONG_MAP_LEVEL 1

/////////////////////////////////////////////////////////////////////////////
// CBracketOutLineDlg 

class CBracketOutLineDlg final : public CDialogEx
{
	DECLARE_DYNAMIC(CBracketOutLineDlg)
public:
	CBracketOutLineDlg(CWnd* pParent = NULL);
	virtual ~CBracketOutLineDlg();

	enum { IDD = IDD_BRACKET_OUTLINE };

	void UpdateFoldingMap(int nFoldingLevel);
	void ClearAll();
	void UpdateUIVisual();

protected:
	CTreeAdvance m_BracketTree;
	CFont	m_Font;
	CString m_strFilePath;
	CImageList m_ImageList; //image list used by the tree
	CBitmap m_Bitmap; //bitmap which loads  bitmap

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK() {}
	virtual void OnCancel() {}
	virtual BOOL OnInitDialog();
	afx_msg void OnEditRefresh();
	afx_msg void OnEditLevel1();
	afx_msg void OnEditLevel2();
	afx_msg void OnEditLevel3();
	afx_msg void OnEditLevel4();
	afx_msg void OnEditLevel5();
	afx_msg void OnEditLevel6();
	afx_msg void OnEditLevel7();
	afx_msg void OnEditLevel8();
	afx_msg void OnEditLevel9();
	afx_msg void OnEditExportToEditor();
	afx_msg void OnEditClear();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnTreeItemSelect(WPARAM wParam, LPARAM lParam);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};