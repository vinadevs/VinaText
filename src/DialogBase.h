#pragma once
/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "UndoRedoEditControl.h"

class CDlgBase : public CDialogEx
{
public:
	//Constructors
	CDlgBase(UINT nIDTemplate, CWnd *pParent = NULL);

	CString m_strDlgCaption;

protected:
	//Methods
	virtual BOOL OnInitDialog();

	CUndoRedoEditControl m_EditUndoRedo;
	CUndoRedoEditControl m_EditUndoRedo2;

	DECLARE_MESSAGE_MAP()
};
