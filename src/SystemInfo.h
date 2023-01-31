/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include <afxtempl.h>
#include <atlbase.h>

class CSystemInfo
{
public:
	CSystemInfo(void);
	~CSystemInfo(void);

public:
	/********Get the operating system version, service pack version, system type **************/
	void GetOSVersion(CString &strOSVersion, CString &strServiceVersion);
	BOOL IsWinX64(); //determine whether it is a 64 - bit operating system
	void GetCurrentUserName(CString& userName);

	/***********Get the number and name of the network card***********/
	int  GetInterFaceCount();
	void GetInterFaceName(CString &InterfaceName, int pNum);
	void GetMACPhysicalIPAddress(CStringArray& macAddress, CStringArray& ipAddress);

	/*** Get physical memory and virtual memory size***/
	void GetMemoryInfo(CString &dwTotalPhys, CString &dwTotalVirtual);

	/**** Get the CPU name, the number of cores, the frequency of the main *********/
	void GetCpuInfo(CString &chProcessorName, CString &chProcessorType, DWORD &dwNum, DWORD &dwMaxClockSpeed);

	/****Get hard drive information****/
	void GetDiskInfo(DWORD &dwNum, CStringArray& chDriveInfo);

	/****Get graphics card information*****/
	void GetDisplayCardInfo(DWORD &dwNum, CStringArray& chCardName);

	/****Get general information*****/
	std::wstring GetGeneralHardwareInformation();

	/****Get wifi list information*****/
	std::vector<std::wstring> GetSystemWifiList();

	/****Get wifi password information*****/
	std::wstring GetWifiPassword(std::wstring ssid);
private:
	CStringList Interfaces; //Save the names of all NICs
	CList < DWORD, DWORD &> Bandwidths; // bandwidth of each network card
	CList < DWORD, DWORD &> TotalTraffics; // Total traffic of each NIC
};