/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "DialogBase.h"

class CSetPathDlg : public CDlgBase
{
public:
//Constructors
  CSetPathDlg(CWnd* pParent = NULL);

//Member variables
  enum { IDD = IDD_ROOTFOLDER };
  CString m_sPath;

protected:
//Methods
  void DoDataExchange(CDataExchange* pDX) override;

  virtual BOOL OnInitDialog();

  CMFCEditBrowseCtrl m_EditPath;

  DECLARE_MESSAGE_MAP()
};
