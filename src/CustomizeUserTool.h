/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

class CCustomizeUserTool : public CUserTool
{
	// Serialization and Run-Time Information
	DECLARE_SERIAL(CCustomizeUserTool)
public:
	// Construction
	CCustomizeUserTool() {}
	virtual ~CCustomizeUserTool() {}
	virtual BOOL Invoke() override;
};