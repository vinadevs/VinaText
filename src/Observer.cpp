/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Observer.h"

CObserver::CObserver(void)
{
}

CObserver::~CObserver(void)
{
}

int CObserver::UpdateObserver( CSubject* pSubject, UINT Msg, WPARAM wParam, LPARAM lParam ) 
{
	// return value
	// 0		: continuously update next observer
	// not 0	: Stop updating observer, and return value 
	return 0;
}