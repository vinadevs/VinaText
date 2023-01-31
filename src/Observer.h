/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

class CSubject;

class CObserver
{
public:
	CObserver(void);
	virtual ~CObserver(void);

	virtual int UpdateObserver(CSubject* pSubject, UINT Msg, WPARAM wParam, LPARAM lParam);
};
