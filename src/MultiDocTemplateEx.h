/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

class CMultiDocTemplateEx : public CMultiDocTemplate  
{
public:
	CMultiDocTemplateEx(UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass);
	virtual ~CMultiDocTemplateEx();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszPathName, BOOL bAddToMRU, BOOL bMakeVisible);
	CDocument* OpenNewDocument(LPCTSTR lpszPathName, BOOL bAddToMRU, BOOL bMakeVisible);
};