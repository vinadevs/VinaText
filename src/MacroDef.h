/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "stdafx.h"

// memory free
#define DELETE_POINTER_CPP(x)		 { if(x) { delete (x); (x)=NULL;} }
#define DELETE_POINTER_CPP_ARRAY(x)  { if(x){ delete [] (x); (x)=NULL;} }
#define DELETE_POINTER_C(x)          { if (x) { free(x); x = NULL;} }
#define DELETE_WIN32_HANDLE(x)       { if (x) { ::CloseHandle(x); x = INVALID_HANDLE_VALUE;} }
#define DELETE_WIN32_HWND(x)       { if (x) { ::CloseWindow(x); x = NULL;} }

// avoid block main thread
#define USE_THREAD_PUMP_UI AfxGetApp()->PumpMessage(); ::Sleep(10);

// atomic thread
#define THREAD_SECTION_LOCK(critical_section) CSingleLock singleLock(&critical_section); singleLock.Lock(); if (singleLock.IsLocked()) { 

#define THREAD_SECTION_UNLOCK singleLock.Unlock(); }

// sync wait
#define SYNC_WAIT_UNTIL_OBJECT_BECAME_FALSE(object) while (object);

// append vector
#define APPEND_VECTOR_HELPER(vector1, vector2) \
	vector1.insert(std::end(vector1), std::begin(vector2), std::end(vector2));

// toggle flag
#define TOGGLE_FLAG(flag) flag = !flag;

#define CREATE_CSTRING_FROM_BUFFER 1

#define PIPE_CMD_OUTPUT_CONSOLE _T("\\\\.\\PIPE\\VINATEXT");  

#define SET_FOCUS_ON_CHILD_DLG_CONTROL(control) \
	SendMessage(WM_NEXTDLGCTL, (WPARAM)control.GetSafeHwnd(), TRUE);

#ifndef TVS_EX_DOUBLEBUFFER
#define TVS_EX_DOUBLEBUFFER 0x0004
#endif //#ifndef TVS_EX_DOUBLEBUFFER

#ifndef TVS_EX_AUTOHSCROLL
#define TVS_EX_AUTOHSCROLL 0x0020
#endif //#ifndef TVS_EX_AUTOHSCROLL

#ifndef TVS_EX_FADEINOUTEXPANDOS
#define TVS_EX_FADEINOUTEXPANDOS 0x0040
#endif //#ifndef TVS_EX_FADEINOUTEXPANDOS

#ifndef TVM_SETEXTENDEDSTYLE
#define TVM_SETEXTENDEDSTYLE (TV_FIRST + 44)
#endif //#ifndef TVM_SETEXTENDEDSTYLE

#define UWM_GUI_WORKER_HANDLER_NOTIFY_PROGRESS (WM_APP + 300) 
#define UWM_GUI_WORKER_HANDLER_BUILD_NOTIFY_EXIT_CODE (WM_APP + 301) 
#define UWM_GUI_WORKER_HANDLER_RUN_NOTIFY_EXIT_CODE (WM_APP + 302)
#define UWM_GUI_WORKER_HANDLER_DEBUG_NOTIFY_EXIT_CODE (WM_APP + 303)
#define UWM_GUI_DIRECTORY_NOTIFIER_FILE_CHANGE (WM_APP + 304)
#define UWM_GUI_WORKER_HANDLER_DEBUG_NOTIFY_LINE_PONITER (WM_APP + 305)
#define UMW_MAIN_FRAME_UPDATE (WM_USER + 309)
#define UMW_DOCK_PANE_UPDATE (WM_USER + 310)

#define MSG_TARGET_UPDATE_ALL_VIEW 1

#define EDITOR_NEW_LINE_CR _T("\r")
#define EDITOR_NEW_LINE_LF _T("\n")
#define EDITOR_NEW_LINE_CR_LF _T("\r\n")
#define EDITOR_NEW_LINE _T("\r")
#define EDITOR_TAB _T("\t")
#define EDITOR_TAB_4SPACE _T("    ")
#define CSTRING_SPACE _T(" ")
#define EDITOR_SPECIAL_STRINGS L"` \r\n\t~!@#$%^&*()-+=[]{}\\|;:'\",<.>/?*"
#define EDITOR_SPECIAL_CSTRINGS _T("` \r\n\t~!@#$%^&*()-+=[]{}\\|;:'\",<.>/?*")
#define EDITOR_REGEX_AUTO_COMPLETE_PATTERN "[^ \\t\\n\\r.,;:\"(){}=<>'+!\\[\\]]+"

#define GET_ARRAY_SIZE(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
#define ESCAPSE_STRING_WITH_QUOTE(str) _T("\"") + str + _T("\"")

#define GOOGLE_SEARCH_API _T("www.google.com/search?q=")
#define GOOGLE_TRANSLATE_PREFIX_API _T("https://translate.google.com/?hl=vi&sl=auto&tl=vi&text=")
#define GOOGLE_TRANSLATE_SUFFIX_API _T("%0A&op=translate")
#define STACKOVERFLOW_API _T(" site:www.stackoverflow.com")
#define WIKIPEDIA_SEARCH_API _T("http://en.wikipedia.org/wiki/Special:Search?search=")

// VinaText encoding
#define TF_INT			-1
#define TF_ANSI         CP_ACP
#define TF_UTF8         CP_UTF8
#define TF_UTF16LE      1200
#define TF_UTF16BE      1201
#define TF_UTF32LE      12000
#define TF_UTF32BE      12001

// codepage
#define CP_INVALID -1

// process
#define EXIT_CODE_TERMINATE 0

// max file size
#define FILE_SIZE_LIMITATION INT_MAX
