/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "SystemInfo.h"  
#include "float.h"  
#include "winperf.h"  
#include "OSUtil.h"

#pragma warning (disable : 4996)

CSystemInfo::CSystemInfo(void)
{
}

CSystemInfo::~CSystemInfo(void)
{
}

void CSystemInfo::GetOSVersion(CString &strOSVersion, CString &strServiceVersion)
{
	CString str;
	OSVERSIONINFOEX osvi;
	SYSTEM_INFO si;
	BOOL bOsVersionInfoEx;

	ZeroMemory(&si, sizeof(SYSTEM_INFO));
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if (!(bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO *)&osvi)))
	{
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx((OSVERSIONINFO *)&osvi);
	}


	GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")),
		"GetNativeSystemInfo");

	GetSystemInfo(&si);
	switch (osvi.dwPlatformId)
	{
	case VER_PLATFORM_WIN32_NT:
		if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0)
		{
			if (osvi.wProductType == VER_NT_WORKSTATION)
			{
				str.Format(_T("Windows Vista "));
			}
			else
			{
				str.Format(_T("Windows Server \"Longhorn\" "));
			}
		}
		if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
		{
			if (GetSystemMetrics(SM_SERVERR2))
			{
				str.Format(_T("Microsoft Windows Server 2003 \"R2\" "));
			}
			else if (osvi.wProductType == VER_NT_WORKSTATION &&
				si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
			{
				str.Format(_T("Microsoft Windows XP Professional x64 Edition "));
			}
			else
			{
				str.Format(_T("Microsoft Windows Server 2003, "));
			}
		}

		if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
		{
			str.Format(_T("Microsoft Windows XP "));
		}

		if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
			str.Format(_T("Microsoft Windows 2000 "));

		if (osvi.dwMajorVersion <= 4)
		{
			str.Format(_T("Microsoft Windows NT "));
		}

		// Test for specific product on Windows NT 4.0 SP6 and later.  
		if (bOsVersionInfoEx)
		{

			// Save the service pack version
			strServiceVersion.Format(_T("Service Pack %d"), osvi.wServicePackMajor);

			// Test for the workstation type.  
			if (osvi.wProductType == VER_NT_WORKSTATION &&
				si.wProcessorArchitecture != PROCESSOR_ARCHITECTURE_AMD64)
			{
				if (osvi.dwMajorVersion == 4)
					str = str + _T("Workstation 4.0");
				else if (osvi.wSuiteMask & VER_SUITE_PERSONAL)
					str = str + _T("Home Edition");
				else str = str + _T("Professional");
			}

			// Test for the server type.  
			else if (osvi.wProductType == VER_NT_SERVER ||
				osvi.wProductType == VER_NT_DOMAIN_CONTROLLER)
			{
				if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
				{
					if (si.wProcessorArchitecture ==
						PROCESSOR_ARCHITECTURE_IA64)
					{
						if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
							str = str + _T("Datacenter Edition for Itanium-based Systems");
						else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
							str = str + _T("Enterprise Edition for Itanium-based Systems");
					}

					else if (si.wProcessorArchitecture ==
						PROCESSOR_ARCHITECTURE_AMD64)
					{
						if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
							str = str + _T("Datacenter x64 Edition ");
						else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
							str = str + _T("Enterprise x64 Edition ");
						else str = str + _T("Standard x64 Edition ");
					}

					else
					{
						if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
							str = str + _T("Datacenter Edition ");
						else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
							str = str + _T("Enterprise Edition ");
						else if (osvi.wSuiteMask & VER_SUITE_BLADE)
							str = str + _T("Web Edition ");
						else str = str + _T("Standard Edition ");
					}
				}
				else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
				{
					if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
						str = str + _T("Datacenter Server ");
					else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
						str = str + _T("Advanced Server ");
					else str = str + _T("Server ");
				}
				else  // Windows NT 4.0   
				{
					if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
						str = str + _T("Server 4.0, Enterprise Edition ");
					else str = str + _T("Server 4.0 ");
				}
			}
		}
		// Test for specific product on Windows NT 4.0 SP5 and earlier  
		else
		{
			HKEY hKey;
			TCHAR szProductType[256];
			DWORD dwBufLen = 256 * sizeof(TCHAR);
			LONG lRet;

			lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
				_T("SYSTEM\\CurrentControlSet\\Control\\ProductOptions"), 0, KEY_QUERY_VALUE, &hKey);
			if (lRet != ERROR_SUCCESS)
				strOSVersion = str;
			return;

			lRet = RegQueryValueEx(hKey, TEXT("ProductType"),
				NULL, NULL, (LPBYTE)szProductType, &dwBufLen);
			RegCloseKey(hKey);

			if ((lRet != ERROR_SUCCESS) ||
				(dwBufLen > 256 * sizeof(TCHAR)))
				strOSVersion = str;
			return;

			if (lstrcmpi(TEXT("WINNT"), szProductType) == 0)
				str = str + _T("Workstation ");
			if (lstrcmpi(TEXT("LANMANNT"), szProductType) == 0)
				str = str + _T("Server ");
			if (lstrcmpi(TEXT("SERVERNT"), szProductType) == 0)
				str = str + _T("Advanced Server ");
			str.Format(_T("%d.%d "), osvi.dwMajorVersion, osvi.dwMinorVersion);
		}

		// Display service pack (if any) and build number.  

		if (osvi.dwMajorVersion == 4 &&
			lstrcmpi(osvi.szCSDVersion, TEXT("Service Pack 6")) == 0)
		{
			HKEY hKey;
			LONG lRet;

			// Test for SP6 versus SP6a.  
			lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
				_T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Hotfix\\Q246009"), 0, KEY_QUERY_VALUE, &hKey);
			if (lRet == ERROR_SUCCESS)
				str.Format(_T("Service Pack 6a (Build %d)\n"),
					osvi.dwBuildNumber & 0xFFFF);
			else // Windows NT 4.0 prior to SP6a  
			{
				_tprintf(TEXT("%s (Build %d)\n"),
					osvi.szCSDVersion,
					osvi.dwBuildNumber & 0xFFFF);
			}

			RegCloseKey(hKey);
		}
		else // not Windows NT 4.0   
		{
			_tprintf(TEXT("%s (Build %d)\n"),
				osvi.szCSDVersion,
				osvi.dwBuildNumber & 0xFFFF);
		}

		break;

		// Test for the Windows Me/98/95.  
	case VER_PLATFORM_WIN32_WINDOWS:

		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
		{
			str.Format(_T("Microsoft Windows 95 "));
			if (osvi.szCSDVersion[1] == 'C' || osvi.szCSDVersion[1] == 'B')
				str = str + _T("OSR2 ");
		}

		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
		{
			str.Format(_T("Microsoft Windows 98 "));
			if (osvi.szCSDVersion[1] == 'A' || osvi.szCSDVersion[1] == 'B')
				str = str + _T("SE ");
		}
		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
		{
			str.Format(_T("Microsoft Windows Millennium Edition\n"));
		}
		break;

	case VER_PLATFORM_WIN32s:
		str.Format(_T("Microsoft Win32s\n"));
		break;
	default:
		break;
	}

	strOSVersion = str;
}

BOOL CSystemInfo::IsWinX64()
{
	typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	LPFN_ISWOW64PROCESS fnIsWow64Process;
	BOOL bIsWow64 = FALSE;
	fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(_T("kernel32")), "IsWow64Process");
	if (NULL != fnIsWow64Process)
	{
		fnIsWow64Process(GetCurrentProcess(), &bIsWow64);
	}
	return bIsWow64;
}

void CSystemInfo::GetCurrentUserName(CString & userName)
{
	char usernamebuff[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName((LPWSTR)usernamebuff, &username_len);
	userName = usernamebuff;
}

void CSystemInfo::GetCpuInfo(CString &chProcessorName, CString &chProcessorType, DWORD &dwNum, DWORD &dwMaxClockSpeed)
{

	CString strPath = _T("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0");//Registry subkey path  
	CRegKey regkey; // define the registry class object
	LONG lResult; // LONG type variable - reaction results
	lResult = regkey.Open(HKEY_LOCAL_MACHINE, LPCTSTR(strPath), KEY_ALL_ACCESS); //Open the registry key  
	if (lResult != ERROR_SUCCESS)
	{
		return;
	}
	WCHAR chCPUName[50] = { 0 };
	DWORD dwSize = 50;

	// Get the ProcessorNameString field value
	if (ERROR_SUCCESS == regkey.QueryStringValue(_T("ProcessorNameString"), chCPUName, &dwSize))
	{
		chProcessorName = chCPUName;
	}

	// Query CPU frequency
	DWORD dwValue;
	if (ERROR_SUCCESS == regkey.QueryDWORDValue(_T("~MHz"), dwValue))
	{
		dwMaxClockSpeed = dwValue;
	}
	regkey.Close();//Close the registry  
				   //UpdateData(FALSE);  

	// Get the number of CPU cores
	SYSTEM_INFO si;
	memset(&si, 0, sizeof(SYSTEM_INFO));
	GetSystemInfo(&si);
	dwNum = si.dwNumberOfProcessors;

	switch (si.dwProcessorType)
	{
	case PROCESSOR_INTEL_386:
	{
		chProcessorType.Format(_T("Intel 386 processor"));
	}
	break;
	case PROCESSOR_INTEL_486:
	{
		chProcessorType.Format(_T("Intel 486 Processor"));
	}
	break;
	case PROCESSOR_INTEL_PENTIUM:
	{
		chProcessorType.Format(_T("Intel Pentium Processor"));
	}
	break;
	case PROCESSOR_INTEL_IA64:
	{
		chProcessorType.Format(_T("Intel IA64 Processor"));
	}
	break;
	case PROCESSOR_AMD_X8664:
	{
		chProcessorType.Format(_T("AMD X8664 Processor"));
	}
	break;
	default:
		chProcessorType.Format(_T("unknown"));
		break;
	}

	//GetDisplayName()  
}

void  CSystemInfo::GetMemoryInfo(CString &dwTotalPhys, CString &dwTotalVirtual)
{
	//   TODO:     Add   extra   initialization   here   
	MEMORYSTATUS   Mem;
	//   get   the   memory   status   
	GlobalMemoryStatus(&Mem);

	DWORD dwSize = (DWORD)Mem.dwTotalPhys / (1024 * 1024);
	DWORD dwVirtSize = (DWORD)Mem.dwTotalVirtual / (1024 * 1024);

	dwTotalPhys.Format(_T("physical memory: %ld MB"), dwSize);
	dwTotalVirtual.Format(_T("virtual memory: %ld MB"), dwVirtSize);
}

int CSystemInfo::GetInterFaceCount()
{
	/*CGetNetData pNet;
	DWORD pCount = pNet.GetNetworkInterfacesCount();
	return pCount;*/


	try
	{
#define DEFAULT_BUFFER_SIZE 40960L  

		unsigned char *data = (unsigned char*)malloc(DEFAULT_BUFFER_SIZE);
		DWORD type;
		DWORD size = DEFAULT_BUFFER_SIZE;
		DWORD ret;

		char s_key[4096];
		sprintf_s(s_key, 4096, "510");
		//RegeditValueEx's fixed invocation format          
		CString str(s_key);

		// If the RegQueryValueEx function fails to execute, enter the loop
		while ((ret = RegQueryValueEx(HKEY_PERFORMANCE_DATA, str, 0, &type, data, &size)) != ERROR_SUCCESS)
		{
			Sleep(10);
			// If the return value of RegQueryValueEx is ERROR_MORE_DATA(the requested memory area data is too small, can not accommodate the data returned by RegQueryValueEx)
			if (ret == ERROR_MORE_DATA)
			{
				Sleep(10);
				size += DEFAULT_BUFFER_SIZE;
				data = (unsigned char*)realloc(data, size);//Reallocate enough memory  

				ret = RegQueryValueEx(HKEY_PERFORMANCE_DATA, str, 0, &type, data, &size);//Re-execute the RegQueryValueEx function  
			}
			// If the return value of RegQueryValueEx is still unsuccessful, the function returns ..... (note the memory leak "free function" ~~~).
				// This if the guarantee that this while can only enter once ~~~avoid infinite loop
			if (ret != ERROR_SUCCESS)
			{
				if (NULL != data)
				{
					free(data);
					data = NULL;
				}
				return 0; // 0 interfaces
			}
		}

		// After the function is successfully executed, it is the parsing of the data in the returned data memory.This proposal is to check the description of the data structure of the RegQueryValueEx function parameter.
			// Get the data block
		PERF_DATA_BLOCK  *dataBlockPtr = (PERF_DATA_BLOCK *)data;
		// Get the first object
		PERF_OBJECT_TYPE *objectPtr = (PERF_OBJECT_TYPE *)((BYTE *)dataBlockPtr + dataBlockPtr->HeaderLength);

		for (int a = 0; a < (int)dataBlockPtr->NumObjectTypes; a++)
		{
			char nameBuffer[255] = { 0 };
			if (objectPtr->ObjectNameTitleIndex == 510)
			{
				DWORD processIdOffset = ULONG_MAX;
				PERF_COUNTER_DEFINITION *counterPtr = (PERF_COUNTER_DEFINITION *)((BYTE *)objectPtr + objectPtr->HeaderLength);

				for (int b = 0; b < (int)objectPtr->NumCounters; b++)
				{
					if (counterPtr->CounterNameTitleIndex == 520)
						processIdOffset = counterPtr->CounterOffset;

					counterPtr = (PERF_COUNTER_DEFINITION *)((BYTE *)counterPtr + counterPtr->ByteLength);
				}

				if (processIdOffset == ULONG_MAX) {
					if (data != NULL)
					{
						free(data);
						data = NULL;
					}
					return 0;
				}

				PERF_INSTANCE_DEFINITION *instancePtr = (PERF_INSTANCE_DEFINITION *)((BYTE *)objectPtr + objectPtr->DefinitionLength);

				for (int b = 0; b < objectPtr->NumInstances; b++)
				{
					wchar_t *namePtr = (wchar_t *)((BYTE *)instancePtr + instancePtr->NameOffset);
					PERF_COUNTER_BLOCK *counterBlockPtr = (PERF_COUNTER_BLOCK *)((BYTE *)instancePtr + instancePtr->ByteLength);

					char pName[256] = { 0 };
					WideCharToMultiByte(CP_ACP, 0, namePtr, -1, pName, sizeof(nameBuffer), 0, 0);

					DWORD bandwith = *((DWORD *)((BYTE *)counterBlockPtr + processIdOffset));
					DWORD tottraff = 0;

					Interfaces.AddTail(CString(pName)); //Name of each NIC  
					Bandwidths.AddTail(bandwith); //Bandwidth  
					TotalTraffics.AddTail(tottraff); // Traffic initialized to 0  

					PERF_COUNTER_BLOCK  *pCtrBlk = (PERF_COUNTER_BLOCK *)((BYTE *)instancePtr + instancePtr->ByteLength);


					instancePtr = (PERF_INSTANCE_DEFINITION *)((BYTE *)instancePtr + instancePtr->ByteLength + pCtrBlk->ByteLength);
				}
			}
			objectPtr = (PERF_OBJECT_TYPE *)((BYTE *)objectPtr + objectPtr->TotalByteLength);
		}
		if (data != NULL)
		{
			free(data);
			data = NULL;
		}
	}
	catch (...)
	{
		return 0;
	}
	return static_cast<int>(Interfaces.GetCount());
}

void CSystemInfo::GetInterFaceName(CString &InterfaceName, int pNum)
{
	/*CGetNetData pNet;
	pNet.GetNetworkInterfaceName(&InterfaceName,pNum);*/

	POSITION pos = Interfaces.FindIndex(pNum);
	if (pos == NULL)
		return;

	InterfaceName = Interfaces.GetAt(pos);
	pos = Bandwidths.FindIndex(pNum);
	if (pos == NULL)
		return;
	DWORD dwBandwidth = Bandwidths.GetAt(pos);

	CString str;
	str.Format(_T("%d"), dwBandwidth);

	InterfaceName = InterfaceName + str;
}

void CSystemInfo::GetMACPhysicalIPAddress(CStringArray & macAddress, CStringArray & ipAddress)
{
	PIP_ADAPTER_INFO AdapterInfo;
	DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);
	char *mac_addr = (char*)malloc(18);

	AdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
	if (AdapterInfo == NULL)
	{
		DELETE_POINTER_C(mac_addr);
		return; // it is safe to call free(NULL)
	}

	// Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen variable
	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW)
	{
		DELETE_POINTER_C(AdapterInfo);
		AdapterInfo = (IP_ADAPTER_INFO *)malloc(dwBufLen);
		if (AdapterInfo == NULL)
		{
			DELETE_POINTER_C(mac_addr);
			return;
		}
	}

	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR)
	{
		// Contains pointer to current adapter info
		PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
		do
		{
			// technically should look at pAdapterInfo->AddressLength
			//   and not assume it is 6.
			sprintf(mac_addr, "%02X-%02X-%02X-%02X-%02X-%02X",
				pAdapterInfo->Address[0], pAdapterInfo->Address[1],
				pAdapterInfo->Address[2], pAdapterInfo->Address[3],
				pAdapterInfo->Address[4], pAdapterInfo->Address[5]);

			ipAddress.Add(CString(pAdapterInfo->IpAddressList.IpAddress.String));
			macAddress.Add(CString(mac_addr));

			pAdapterInfo = pAdapterInfo->Next;

		} while (pAdapterInfo);
	}
	DELETE_POINTER_C(AdapterInfo);
	DELETE_POINTER_C(mac_addr);
}

void CSystemInfo::GetDiskInfo(DWORD &dwNum, CStringArray& chDriveInfo)
{
	DWORD DiskCount = 0;

	// GetLogicalDrives() function can get the number of logical drives in the system, the function returns a 32 - bit unsigned integer data.
	DWORD DiskInfo = GetLogicalDrives();

	// Check whether each bit of data is 1 by a loop operation.If it is 1, the disk is true.If it is 0, the disk does not exist.
	while (DiskInfo)
	{
		// Through the logic and operation of the bit operation, determine whether it is 1
		Sleep(10);
		if (DiskInfo & 1)
		{
			DiskCount++;
		}
		DiskInfo = DiskInfo >> 1;//The right shift operation of the bit operation ensures that the position checked once per cycle moves one bit to the right. */  
	}

	if (dwNum < DiskCount)
	{
		return; // the actual number of disks is greater than dwNum
	}
	dwNum = DiskCount; // save the number of disk partitions


		//-------------------------------------------------------------------//  
		// Get all drive string information length by GetLogicalDriveStrings() function
	int DSLength = GetLogicalDriveStrings(0, NULL);

	WCHAR* DStr = new WCHAR[DSLength];
	memset(DStr, 0, DSLength);

	// Copy the string information into the heap array via GetLogicalDriveStrings, which holds information about all the drives.  
	GetLogicalDriveStrings(DSLength, DStr);

	int DType;
	int si = 0;
	BOOL fResult;
	unsigned _int64 i64FreeBytesToCaller;
	unsigned _int64 i64TotalBytes;
	unsigned _int64 i64FreeBytes;

	// Read each drive information, because DStr internal data format is A : \ NULLB : \ NULLC : \ NULL, so DSLength / 4 can get a specific large loop range
	for (int i = 0; i < DSLength / 4; ++i)
	{
		Sleep(10);
		CString strdriver = DStr + i * 4;
		CString strTmp, strTotalBytes, strFreeBytes;
		DType = GetDriveType(strdriver); // GetDriveType function, you can get the drive type, the parameter is the root directory of the drive
		switch (DType)
		{
		case DRIVE_FIXED:
		{
			strTmp.Format(_T("local disk"));
		}
		break;
		case DRIVE_CDROM:
		{
			strTmp.Format(_T("DVD drive"));
		}
		break;
		case DRIVE_REMOVABLE:
		{
			strTmp.Format(_T("removable disk"));
		}
		break;
		case DRIVE_REMOTE:
		{
			strTmp.Format(_T("network disk"));
		}
		break;
		case DRIVE_RAMDISK:
		{
			strTmp.Format(_T("virtual RAM disk"));
		}
		break;
		case DRIVE_UNKNOWN:
		{
			strTmp.Format(_T("Virtual RAM unknown device"));
		}
		break;
		default:
			strTmp.Format(_T("unknown device"));
			break;
		}

		// GetDiskFreeSpaceEx function, you can get the space state of the drive disk, the function returns a BOOL type data
		fResult = GetDiskFreeSpaceEx(strdriver,
			(PULARGE_INTEGER)&i64FreeBytesToCaller,
			(PULARGE_INTEGER)&i64TotalBytes,
			(PULARGE_INTEGER)&i64FreeBytes);

		if (fResult)
		{
			strTotalBytes.Format(_T("disk total capacity%fMB"), (float)i64TotalBytes / 1024 / 1024);
			strFreeBytes.Format(_T("disk free space%fMB"), (float)i64FreeBytesToCaller / 1024 / 1024);
		}
		else
		{
			strTotalBytes.Format(_T(""));
			strFreeBytes.Format(_T(""));
		}
		chDriveInfo.Add(strTmp + _T("(") + strdriver + _T("):") + strTotalBytes + strFreeBytes);
		si += 4;
	}
}

void CSystemInfo::GetDisplayCardInfo(DWORD &dwNum, CStringArray& chCardName)
{
	HKEY keyServ;
	HKEY keyEnum;
	HKEY key;
	HKEY key2;
	LONG lResult; // LONG type variable - save function return value

	// Query all subkeys under "SYSTEM\\CurrentControlSet\\Services" to save to keyServ
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services"), 0, KEY_READ, &keyServ);
	if (ERROR_SUCCESS != lResult)
		return;

	//Query all subkeys under "SYSTEM\\CurrentControlSet\\Enum" to save to keyEnum  
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Enum"), 0, KEY_READ, &keyEnum);
	if (ERROR_SUCCESS != lResult)
		return;

	int i = 0, count = 0;
	DWORD size = 0, type = 0;
	for (;; ++i)
	{
		Sleep(5);
		size = 512;
		TCHAR name[512] = { 0 };//Save the field name of each subkey under keyServ  

								// Enumerate each subkey field under keyServ one by one and save it to name  
		lResult = RegEnumKeyEx(keyServ, i, name, &size, NULL, NULL, NULL, NULL);

		// The sub - item to be read does not exist, that is, the keyServ sub - items all traverse out of the loop
		if (lResult == ERROR_NO_MORE_ITEMS)
			break;

		// Open the key field of the keyServ to save the value of the field identified by the name to the key
		lResult = RegOpenKeyEx(keyServ, name, 0, KEY_READ, &key);
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(keyServ);
			return;
		}

		size = 512;
		// Query the field under the key is the sub - key field name of the Group is saved to the name
		lResult = RegQueryValueEx(key, TEXT("Group"), 0, &type, (LPBYTE)name, &size);
		if (lResult == ERROR_FILE_NOT_FOUND)
		{
			//? The key does not exist.  
			RegCloseKey(key);
			continue;
		};

		// If the name of the query is not Video, the key is not a graphics driver
		if (_tcscmp(TEXT("Video"), name) != 0)
		{
			RegCloseKey(key);
			continue; //return to for loop  
		};

		// If the program continues to execute, it shows that the information about the graphics card has been found, so after the following code is executed, the first for loop is broken, and the function returns.
		lResult = RegOpenKeyEx(key, TEXT("Enum"), 0, KEY_READ, &key2);
		RegCloseKey(key);
		key = key2;
		size = sizeof(count);
		lResult = RegQueryValueEx(key, TEXT("Count"), 0, &type, (LPBYTE)&count, &size);//Query Count field (number of graphics cards)  

		dwNum = count; // save the number of graphics cards
		for (int j = 0; j < count; ++j)
		{
			TCHAR sz[512] = { 0 };
			TCHAR name[64] = { 0 };
			wsprintf(name, TEXT("%d"), j);
			size = sizeof(sz);
			lResult = RegQueryValueEx(key, name, 0, &type, (LPBYTE)sz, &size);


			lResult = RegOpenKeyEx(keyEnum, sz, 0, KEY_READ, &key2);
			if (ERROR_SUCCESS)
			{
				RegCloseKey(keyEnum);
				return;
			}

			size = sizeof(sz);
			lResult = RegQueryValueEx(key2, TEXT("FriendlyName"), 0, &type, (LPBYTE)sz, &size);
			if (lResult == ERROR_FILE_NOT_FOUND)
			{
				size = sizeof(sz);
				lResult = RegQueryValueEx(key2, TEXT("DeviceDesc"), 0, &type, (LPBYTE)sz, &size);
				chCardName.Add(sz);//Save the name of the card  
			};
			RegCloseKey(key2);
			key2 = NULL;
		};
		RegCloseKey(key);
		key = NULL;
		break;
	}
}

std::wstring CSystemInfo::GetGeneralHardwareInformation()
{
	std::wstringstream buffer;
	int CPUInfo[4] = { -1 };
	unsigned   nExIds, i = 0;
	char CPUBrandString[0x40];
	// Get the information associated with each extended ID.
	__cpuid(CPUInfo, 0x80000000);
	nExIds = CPUInfo[0];
	for (i = 0x80000000; i <= nExIds; ++i)
	{
		__cpuid(CPUInfo, i);
		// Interpret CPU brand string
		if (i == 0x80000002)
			memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000003)
			memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000004)
			memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
	}
	//string includes manufacturer, model and clockspeed
	buffer << "CPU Type: " << CPUBrandString << std::endl;

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	buffer << "Number of Cores: " << sysInfo.dwNumberOfProcessors << std::endl;

	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	buffer << "System Memory (RAM): " << (statex.ullTotalPhys / 1024) / 1024 << "MB" << std::endl;

	DISPLAY_DEVICE dd = { sizeof(dd), 0 };
	if (EnumDisplayDevices(NULL, 0, &dd, EDD_GET_DEVICE_INTERFACE_NAME))
	{
		buffer << "Graphic Card: " << dd.DeviceString << std::endl;
	}
	return buffer.str();
}

std::vector<std::wstring> CSystemInfo::GetSystemWifiList()
{
	std::wstringstream ss(OSUtils::GetCMDConsoleResult(L"netsh wlan show profile").data());
	std::wstring input;
	std::vector<std::wstring> wifi;
	while (getline(ss, input))
		if (input.find(L"All User Profile") != std::wstring::npos)
			wifi.push_back(input.substr(27, input.length()));
	return wifi;
}

std::wstring CSystemInfo::GetWifiPassword(std::wstring ssid)
{
	std::wstring command = L"netsh wlan show profile \"" + ssid + L"\" key=clear";
	std::wstringstream ss(OSUtils::GetCMDConsoleResult(command.data()).data());
	std::wstring input;
	while (getline(ss, input))
	{
		if (input.find(L"Key Content") != std::wstring::npos)
			return input.substr(29, input.length());
	}
	return L"< Not Available >";
}