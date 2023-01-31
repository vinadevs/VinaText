/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "DialogBase.h"

class CFileExtensionFilterDlg : public CDlgBase
{
public:
//Constructors / Destructors
  CFileExtensionFilterDlg(CWnd* pParent = NULL);

//Member variables
  enum { IDD = IDD_FILENAME_MASK };
  CString m_sMask;

protected:
  void DoDataExchange(CDataExchange* pDX) override;
  virtual BOOL OnInitDialog();
  afx_msg void OnFilterEditChange();
  DECLARE_MESSAGE_MAP()
};
