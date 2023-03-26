/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#define _ATL_APARTMENT_THREADED 
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#define _ATL_APARTMENT_THREADED

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars
#include <afxtempl.h> //MFC Template support
#include <afxmt.h> //MFC Multi-threading support
#include <afxole.h> //MFC OLE support
#include <shlobj.h> //IShellFolder support
#include <lm.h> //WNet support
#include <uxtheme.h> //XP themes support
#include <atlcom.h>
#include <atlcoll.h>
#include <atlbase.h>
#include <atlhost.h>
#include <atlctl.h>
#include <afxres.h>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <list>
#include <math.h>
#include <fstream>
#include <comdef.h>
#include <winperf.h>
#include <TlHelp32.h>
#include <sstream>
#include <iomanip>
#include <regex>
#include <locale>
#include <codecvt>
#include <string>
#include <string>
#include <fstream>
#include <io.h>
#include <iostream>
#include <cctype>
#include <memory>
#include <array>
#include <vector>
#include <atomic>
#include <windows.h> 
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>
#include <functional>
#include <chrono>
#include <ctime>
#include <queue>
#include <stack>
#include "objbase.h"
#include <Iphlpapi.h>
#include <Assert.h>
#include <stdexcept>
#include <locale.h>
#include <io.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <inttypes.h>
#include <stdlib.h>
#include <shlwapi.h>
#include <wininet.h>
#include <mutex>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "iphlpapi.lib")

// Windows headers
#include <WindowsX.h>

// VinaText definitions...
#include "EnumDef.h"
#include "MacroDef.h"
// VinaText definitions.....

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


