//
//	UXReaderGlobals.h
//	UXReader v0.1
//
//	Copyright � 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

//
//	Messages
//

#define UX_BASE WM_APP

#define UX_SEARCH_FOUND				(UX_BASE + 0x1000)
#define UX_ZOOM_DECREMENT			(UX_BASE + 0x1001)
#define UX_ZOOM_INCREMENT			(UX_BASE + 0x1002)
#define UX_ZOOM_FIT_WIDTH			(UX_BASE + 0x1003)
#define UX_NUMBER_EDIT_FIELD		(UX_BASE + 0x1004)
#define UX_SEARCH_EDIT_FIELD		(UX_BASE + 0x1005)
#define UX_SEARCH_TEXT_FIELD		(UX_BASE + 0x1006)
#define UX_DOCUMENT_VIEW			(UX_BASE + 0x1007)
#define UX_PAGE_DECREMENT			(UX_BASE + 0x1008)
#define UX_PAGE_INCREMENT			(UX_BASE + 0x1009)

//
//	Menu IDs
//

#define UXM_APP_NONE				0x1000
#define UXM_APP_EXIT				0x1001
#define UXM_APP_ABOUT				0x1002

#define UXM_OPEN_DOCUMENT			0x1010
#define UXM_CLEAR_RECENT			0x1011
#define UXM_CLOSE_ALL				0x1012
#define UXM_CLOSE_DOCUMENT			0x1013
#define UXM_DOCUMENT_INFO			0x1014
#define UXM_PRINT_DOCUMENT			0x1015

#define UXM_COPY_TEXT				0x1020
#define UXM_SELECT_ALL				0x1021
#define UXM_FIND_TEXT				0x1022
#define UXM_FIND_INCREMENT			0x1023
#define UXM_FIND_DECREMENT			0x1024
#define UXM_FIND_SELECTION			0x1025
#define UXM_GOTO_SELECTION			0x1026

#define UXM_HIDE_SIDEBAR			0x1030
#define UXM_SHOW_OUTLINE			0x1031
#define UXM_SHOW_THUMBS				0x1032
#define UXM_ZOOM_INCREMENT			0x1033
#define UXM_ZOOM_DECREMENT			0x1034
#define UXM_ZOOM_FIT_WIDTH			0x1035
#define UXM_ZOOM_ONE_TO_ONE			0x1036

#define UXM_GOTO_PAGE				0x1040
#define UXM_PAGE_INCREMENT			0x1041
#define UXM_PAGE_DECREMENT			0x1042
#define UXM_STEP_INCREMENT			0x1043
#define UXM_STEP_DECREMENT			0x1044

#define UXM_SCROLL_INCREMENT_Y		0x1050
#define UXM_SCROLL_DECREMENT_Y		0x1051
#define UXM_SCROLL_INCREMENT_X		0x1052
#define UXM_SCROLL_DECREMENT_X		0x1053
#define UXM_PAGING_INCREMENT_Y		0x1054
#define UXM_PAGING_DECREMENT_Y		0x1055
#define UXM_PAGING_INCREMENT_X		0x1056
#define UXM_PAGING_DECREMENT_X		0x1057
#define UXM_MINIMUM_DOCUMENT_Y		0x1058
#define UXM_MAXIMUM_DOCUMENT_Y		0x1059
#define UXM_MINIMUM_DOCUMENT_X		0x105A
#define UXM_MAXIMUM_DOCUMENT_X		0x105B

#define UXM_ACTIVE_TAB_INCREMENT	0x1060
#define UXM_ACTIVE_TAB_DECREMENT	0x1061

#define UXM_OPEN_RECENT_0			0x1100
#define UXM_OPEN_RECENT_1			0x1101
#define UXM_OPEN_RECENT_2			0x1102
#define UXM_OPEN_RECENT_3			0x1103
#define UXM_OPEN_RECENT_4			0x1104
#define UXM_OPEN_RECENT_5			0x1105
#define UXM_OPEN_RECENT_6			0x1106
#define UXM_OPEN_RECENT_7			0x1107
#define UXM_OPEN_RECENT_8			0x1108
#define UXM_OPEN_RECENT_9			0x1109

//
//	Icons
//

#define IDI_TINKER_ICON				0x0001

//
//	Global statics
//

extern wchar_t *const uxreader;