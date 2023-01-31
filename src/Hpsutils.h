// Minimal, exportable version of HPSLIB
// Copyright (c) 2007, AlpineSoft http://www.alpinesoft.co.uk

#define WIN32_LEAN_AND_MEAN

#include "windows.h"

#include "tchar.h"
#include "malloc.h"
#include "string.h"
#include "assert.h"


#define base_strlen(s)  strlen (s)
#define Hnew            new
#define tsizeof(x)      (sizeof (x) / sizeof (TCHAR))
#define T2B(x)          ((x) * sizeof (TCHAR))


// Log an error message
void _cdecl LogError (const TCHAR *format, ...);

// Lookup a system error message.  Caller must free the pointer returned.
TCHAR * LookupSystemError (DWORD err);

// Set last error string (per thread)
void SetLastErrorString (const TCHAR *err);

// Retrieve last error string (per thread); caller must not free
TCHAR * GetLastErrorString (void);

// Format a string.  Caller must free
// Use MAKEINTRESOURCE to pass the ID of a string resource in message.
TCHAR * vFormatPString (const TCHAR *message, va_list ap);
TCHAR * _cdecl FormatPString (const TCHAR *message, ...);

// Return a copy of string s.  Caller must free when done
TCHAR * copy_string (const TCHAR *s);

// Make a copy of an ANSI string.  Caller must free
char * AtoA (const char *a);


// -----------------------------------------------------------------------------
// Allocation functions for growable blocks

// Allocate memory in 1k chunks.  Stores the data and allocated lengths
// immediately before the data (and returns a pointer to the data part).
void * alloc_block (void *current_block, int datalen);

// Free a block of data allocated with alloc_block
void free_block (void *block);

// Copy a block of data allocated with alloc_block
void * copy_block (const void *block);

// Return the length (not the allocated size) of a block of data allocated with alloc_block
int get_blocklen (const void *block);

// Return the amount of space allocated to this block
int get_buflen (const void *block);
