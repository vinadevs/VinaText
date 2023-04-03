/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "RAIIUtils.h"
#include "Editor.h"
#include "AppUtil.h"
#include "OSUtil.h"

////////////////////////////////////////////////////////////////////
// keep multiple selection status after text update

CMultipleSelectionKeeper::CMultipleSelectionKeeper(CEditorCtrl* pEditor)
{
	m_pEditor = pEditor;
	BeginUpdateOnMultiSelections();
}

CMultipleSelectionKeeper::~CMultipleSelectionKeeper()
{
	EndUpdateOnMultiSelections();
}

void CMultipleSelectionKeeper::BeginUpdateOnMultiSelections()
{
	long nSelections = m_pEditor->GetSelectionNumber();
	ASSERT(nSelections > SINGLE_SELECTION);
	for (int i = 0; i < nSelections; ++i)
	{
		long nSelectionStart = m_pEditor->GetMultiSelectionStart(i);
		long nSelectionEnd = m_pEditor->GetMultiSelectionEnd(i);
		m_MultiSelectionStartEnd[nSelectionStart] = nSelectionEnd;
	}
}

void CMultipleSelectionKeeper::EndUpdateOnMultiSelections()
{
	for (auto iter = m_MultiSelectionStartEnd.begin(); iter != m_MultiSelectionStartEnd.end(); ++iter)
	{
		m_pEditor->DoCommand(SCI_ADDSELECTION, iter->second, iter->first);
	}
}

////////////////////////////////////////////////////////////////////
// for profiling

CBenchmarkTest::CBenchmarkTest(const CString& strTestMessage)
{	
	m_strTestMessage = strTestMessage;
	m_counter = OSUtils::StartBenchmark();
}

CBenchmarkTest::~CBenchmarkTest()
{
	double dResult = OSUtils::StopBenchmark(m_counter);
	LOG_OUTPUT_MESSAGE_FORMAT(m_strTestMessage, dResult);
}