﻿/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

class CEditorCtrl;
class CImageView;

class CWindowsPrinter
{
public:
	CWindowsPrinter(const CString& strDocumentPath, HWND hParent);
    ~CWindowsPrinter() = default;
	BOOL ShowPageSetupDlg();
    void PrintText(BOOL bShowPrinterDlg = FALSE, CEditorCtrl* pEditorCtrl = NULL);
	void PrintImage(BOOL bShowPrinterDlg = FALSE, CImageView* pView = NULL);
private:
	HWND m_hParentUI;
	CString m_strDocumentPath;
};
