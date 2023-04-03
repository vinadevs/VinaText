/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include <list>

class CObserver;

typedef std::list<CObserver*> ListObserver;

class CSubject
{
public:
	CSubject(void);
	virtual ~CSubject(void);

	virtual void AttachObserver(CObserver* pObsvr);
	virtual void DettachObserver(CObserver* pObsvr);
	virtual void ClearObservers();

	virtual int Notify(UINT Msg, WPARAM wParam = NULL, LPARAM lParam = NULL);

protected:
	ListObserver m_ListObserver;
};
