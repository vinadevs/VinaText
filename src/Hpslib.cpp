// Minimal, exportable version of HPSLIB
// Copyright (c) 2007, AlpineSoft http://www.alpinesoft.co.uk
// LGPL applies - i.e. if you use it, please give us a credit

#include "stdafx.h"
#include "Hpsutils.h"

__declspec (thread) TCHAR *last_error_string;

// Set last error string (per thread)
void SetLastErrorString (const TCHAR *err)
{
    free (last_error_string);
    last_error_string = copy_string (err);
}


// Retrieve last error string (per thread); caller must not free
TCHAR * GetLastErrorString (void)
{
    return last_error_string;
}


// Log an error message
void vLogError (const TCHAR *format, va_list ap)
{
    DWORD err = GetLastError ();
    TCHAR *msg = vFormatPString (format, ap);
    SetLastErrorString (msg);
    free (msg);
    SetLastError (err);
}


// Log an error message
void _cdecl LogError (const TCHAR *format, ...)
{
    va_list ap;
    va_start (ap, format);

    vLogError (format, ap);
}


// Lookup a system error message.  Caller must free the pointer returned.
TCHAR * LookupSystemError (DWORD err)
{
    TCHAR *buf;

    if (FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
            0, err, 0, (TCHAR *) &buf, 1, NULL) == 0)
        return copy_string (NULL);

    if (buf [0] && buf [1])
        buf [_tcslen (buf) - 2] = 0;        // remove trailing \r\n

    TCHAR *result = copy_string (buf);
    LocalFree (buf);
    return result;
}


// Set this to the module handle of your resource file, if any
HMODULE ghResInst;

// Format a string.  Caller must free
// Use MAKEINTRESOURCE to pass the ID of a string resource in message.
TCHAR * vFormatPString (const TCHAR *message, va_list ap)
{
    TCHAR buf1 [T2B (4096)];
    TCHAR buf2 [T2B (4096)];

    if (IS_INTRESOURCE (message))
    {
        LoadString ((ghResInst) ? ghResInst : GetModuleHandle (NULL),
            LOWORD (message), buf1, tsizeof (buf1));
        message = buf1;
    }
    
    _vsntprintf_s (buf2, tsizeof (buf2), _TRUNCATE, message, ap);
    return copy_string (buf2);
}


TCHAR * _cdecl FormatPString (const TCHAR *message, ...)
{
    va_list ap;
    va_start (ap, message);
    TCHAR *result = vFormatPString (message, ap);
    va_end (ap);
    return result;
}


// Return a copy of string s.  Caller must free when done
TCHAR * copy_string (const TCHAR *s)
{
    if (s == NULL)
    {
        TCHAR *result = (TCHAR *) malloc (T2B (1));
        result [0] = 0;
        return result;
    }

    TCHAR *result = (TCHAR *) malloc (T2B (_tcslen (s) + 1));
    return _tcscpy (result, s);
}


// Make a copy of an ANSI string.  Caller must free
char * AtoA (const char *a)
{
    char *result = (char *) malloc (strlen (a) + 1);
    return strcpy (result, a);
}


// -----------------------------------------------------------------------------
// Allocation functions for growable blocks

#define DB_SIG      'GSDB'

typedef struct
{
    int     signature;
    int     space_allocated;        /* net of DATA_BLOCK */
    int     datalen;
} DATA_BLOCK;


// Allocate memory in 1k chunks.  Stores the data and allocated lengths
// immediately before the data (and returns a pointer to the data part).
void * alloc_block (void *current_block, int datalen)
{
    DATA_BLOCK *pb = (DATA_BLOCK *) current_block;
    int     space_needed;

    space_needed = ((datalen + 1023) / 1024) * 1024;
    if (pb)
    {
        --pb;
        assert (pb->signature == DB_SIG);
        if (pb->space_allocated >= space_needed)
            goto done;
    }

    pb = (DATA_BLOCK *) realloc (pb, space_needed + sizeof (DATA_BLOCK));
    assert (pb);
    pb->signature = DB_SIG;
    pb->space_allocated = space_needed;

done:
    pb->datalen = datalen;
    return pb + 1;
}


// Free a block of data allocated with alloc_block
void free_block (void *block)
{
    if (block)
    {
        DATA_BLOCK *pb = (DATA_BLOCK *) block;

        --pb;
        assert (pb->signature == DB_SIG);
        free (pb);
    }
}   


// Copy a block of data allocated with alloc_block
void * copy_block (const void *block)
{
    DATA_BLOCK *pb, *pnb;
    int     blocksize;

    assert (block);

    pb = (DATA_BLOCK *) block;
    --pb;
    assert (pb->signature == DB_SIG);
    blocksize = pb->space_allocated + sizeof (DATA_BLOCK);
    pnb = (DATA_BLOCK *) malloc (blocksize);
    assert (pnb);
    memcpy (pnb, pb, blocksize);
    return pnb + 1;
}


// Return the length (not the allocated size) of a block of data allocated with alloc_block
int get_blocklen (const void *block)
{
    DATA_BLOCK *pb = (DATA_BLOCK *) block;

    if (pb == NULL)
        return 0;
    --pb;
    assert (pb->signature == DB_SIG);
    return pb->datalen;
}


// Return the amount of space allocated to this block
int get_buflen (const void *block)
{
    DATA_BLOCK *pb = (DATA_BLOCK *) block;

    if (pb == NULL)
        return 0;
    --pb;
    assert (pb->signature == DB_SIG);
    return pb->space_allocated;
}
