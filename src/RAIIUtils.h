/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#ifndef _RAII_IDIOM_H
#define _RAII_IDIOM_H

////////////////////////////////////////////////////////////////////
// Thread critical session lock

class CCriticalSectionLock
{
private:
	CCriticalSection* m_session;
public:
	CCriticalSectionLock(CCriticalSection *session)
	{
		m_session = session;
		m_session->Lock();
	};
	virtual ~CCriticalSectionLock()
	{
		m_session->Unlock();
	};
};

////////////////////////////////////////////////////////////////////
// Automatically free memory allocated with malloc and calloc.

class CMemoryGuard
{
public:
	explicit CMemoryGuard(void* ptr) : m_ptr(ptr) {}
	~CMemoryGuard()
	{
		free(m_ptr);
		m_ptr = NULL;
	}
	CMemoryGuard(const CMemoryGuard& other) = delete;
	CMemoryGuard& operator=(const CMemoryGuard& other) = delete;
private:
	void* m_ptr;
};

////////////////////////////////////////////////////////////////////
// avoid flicker when redraw control

class CLockCtrlRedraw
{
public:
	CLockCtrlRedraw(CWnd* pCtrl)
	{
		m_pCtrl = pCtrl;
		if (m_pCtrl)
		{
			m_pCtrl->SetRedraw(FALSE);
		}
	}
	~CLockCtrlRedraw()
	{
		if (m_pCtrl)
		{
			m_pCtrl->SetRedraw(TRUE);
			m_pCtrl->Invalidate();
		}
	}
private:
	CWnd* m_pCtrl;
};

class CLockCtrlUpdate
{
public:
	CLockCtrlUpdate(CWnd* pCtrl)
	{
		m_pCtrl = pCtrl;
		if (m_pCtrl)
		{
			m_pCtrl->LockWindowUpdate();
		}
	}
	~CLockCtrlUpdate()
	{
		if (m_pCtrl)
		{
			m_pCtrl->UnlockWindowUpdate();
		}
	}
private:
	CWnd* m_pCtrl;
};

////////////////////////////////////////////////////////////////////
// keep multiple selection status after text update

class CEditorCtrl;

class CMultipleSelectionKeeper
{
public:
	CMultipleSelectionKeeper(CEditorCtrl* pEditor);
	~CMultipleSelectionKeeper();
	void BeginUpdateOnMultiSelections();
	void EndUpdateOnMultiSelections();
private:
	CEditorCtrl* m_pEditor;
	std::unordered_map<long, long> m_MultiSelectionStartEnd;
};

////////////////////////////////////////////////////////////////////
// keep multiple selection status after text update

class CBenchmarkTest
{
public:
	CBenchmarkTest(const CString& strTestMessage);
	~CBenchmarkTest();
private:
	CString m_strTestMessage;
	LONGLONG m_counter;
};

#endif // _RAII_IDIOM_H