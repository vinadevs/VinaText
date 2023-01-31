/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) vinadev.vn - anhsayvimen
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Subject.h"
#include "Observer.h"

CSubject::CSubject(void)
{
}

CSubject::~CSubject(void)
{
	ClearObservers();
}

void CSubject::AttachObserver( CObserver* pObsvr ) 
{
	if( pObsvr != NULL )
	{
		if(m_ListObserver.end() == std::find(m_ListObserver.begin(), m_ListObserver.end(), pObsvr))
		{
			m_ListObserver.push_back(pObsvr);
		}
	}
}

void CSubject::DettachObserver( CObserver* pObsvr ) 
{
	if( pObsvr != NULL )
	{
		m_ListObserver.remove(pObsvr);
	}
}

void CSubject::ClearObservers() 
{
	m_ListObserver.clear();
}

int CSubject::Notify( UINT Msg, WPARAM wParam /*= NULL*/, LPARAM lParam /*= NULL*/ ) 
{
	ListObserver::iterator itr;
	for(itr = m_ListObserver.begin(); itr != m_ListObserver.end(); ++itr)
	{
		int res = (*itr)->UpdateObserver(this, Msg, wParam, lParam);
		if (res != 0)
		{
			return res;
		}
	}
    return 0;
}