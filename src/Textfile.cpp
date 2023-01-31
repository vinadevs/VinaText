/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#define BUILD_HPSLIB
#include "Hpsutils.h"
#include "Textfile.h"
#include "Hpslib.hr"
#include "uchardet\uchardet.h"

template <typename T> int TReadLine (TextFileReader *tf, T **line_buf, bool BE);
template <typename T> int TReadChar (TextFileReader *tf, int strip_cr);


// Flip all the words in string w; compiler should optimise when nchars is passed as 1
static inline void flip_words (WCHAR *w, int nchars)
{
    BYTE *b = (BYTE *) w;
    while (nchars--)
    {
        BYTE swap = b [0];
        b [0] = b [1];
        b [1] = swap;
        b += 2;
    }
}


// Convert from Unicode to ANSI with minimum malloc's
int linebuf_UtoA
    (const WCHAR *u, int len, char **a, int code_page, const char *unknown_char, BOOL *data_lost)
{
    if (len < 0)
        len = (int) wcslen (u);
    int nbytes = len * 2;                       // x 2 to allow for MBCS strings
    *a = (char *) alloc_block (*a, nbytes + 1);
    int bytes_out = WideCharToMultiByte
        (code_page, 0, u, len, *a, nbytes, unknown_char, data_lost);
    assert (bytes_out <= nbytes);
    (*a) [bytes_out] = 0;
    return bytes_out;
}


// Convert from ANSI to Unicode with minimum malloc's
int linebuf_AtoU
    (const char *a, int len, WCHAR **u, int code_page, const char *unknown_char, BOOL *data_lost)
{
    if (len < 0)
        len = (int) base_strlen (a);
    *u = (WCHAR *) alloc_block (*u, (len + 1) * sizeof (WCHAR));
    int chars_out = MultiByteToWideChar (code_page, 0, a, len, *u, len);
    assert (chars_out <= len);
    (*u) [chars_out] = 0;
    return chars_out;
}


// ----------------------------------------------------------------------------
// class TextFileReader: abstract class for encoding-specific functions

class TextFileReader
{
    friend int TReadLine <BYTE> (TextFileReader *tf, BYTE **line_buf, bool BE);
    friend int TReadChar <BYTE> (TextFileReader *tf, int strip_cr);
    friend int TReadLine <WCHAR> (TextFileReader *tf, WCHAR **line_buf, bool BE);
    friend int TReadChar <WCHAR> (TextFileReader *tf, int strip_cr);

public:

// Constructor
TextFileReader::TextFileReader (const TCHAR *filename, HANDLE hFile, int bufsize)
{
    this->filename = filename;
    this->hFile = hFile;
    if (bufsize >= 0)
    {
        this->bufsize = (bufsize) ? bufsize : 4096;     // must be even
        this->buf = (BYTE *) malloc (this->bufsize);
    }
    else
    {
        this->bufsize = 0;
        this->buf = NULL;
    }
    this->bufptr = 0;
    this->bufbytes = 0;
    this->eof = false;
}


// Destructor
virtual TextFileReader::~TextFileReader ()
{
    free (this->buf);
}


// ReadChar
virtual int TextFileReader::ReadChar (void)
{
    return TF_EOF;
}


// ReadLine; line_buf is allocated with alloc_block and may initially be NULL
virtual int TextFileReader::ReadLine
    (TCHAR **line_buf, int code_page, const char *unknown_char, BOOL *data_lost)
{
    return TF_EOF;
}


// FillBuffer
int TextFileReader::FillBuffer (void)
{
    if (this->bufptr < this->bufbytes)
        return 0;
    if (this->eof)
        return TF_EOF;

    DWORD bytes_read;
    if (!ReadFile (this->hFile, this->buf, this->bufsize, &bytes_read, NULL))
    {
        DWORD err = GetLastError ();
        TCHAR *s_err = LookupSystemError (err);
        LogError (MAKEINTRESOURCE (IDS_FILE_READ_ERROR), err, this->filename, s_err);
        free (s_err);
        return TF_ERROR;
    }

    if (bytes_read == 0)
        this->eof = true;
    this->bufptr = 0;
    this->bufbytes = bytes_read;
    return (this->eof) ? TF_EOF : 0;
}

protected:
    const TCHAR *filename;
    HANDLE  hFile;
    int     bufsize;
    BYTE    *buf;
    int     bufptr;
    int     bufbytes;
    bool    eof;
};


// ----------------------------------------------------------------------------
// TReadLine - does the donkey work looking for newlines when reading files

inline BYTE * t_memchr (BYTE *p, int c, size_t n) { return (BYTE *) memchr (p, c, n); };
inline WCHAR * t_memchr (WCHAR *p, int c, size_t n) { return (WCHAR *) wmemchr (p, c, n); };

template <typename T> int TReadLine (TextFileReader *tf, T **line_buf, bool BE)
{
    T *tbuf = (T *) alloc_block (*line_buf, sizeof (T));
    tbuf [0] = 0;
    int result = TF_EOF;
    int nchars = 0;
    
    WCHAR lf = '\n';
    WCHAR cr = '\r';
    if (BE)
    {
        flip_words (&lf, 1);
        flip_words (&cr, 1);
    }

    for ( ; ; )
    {
        if (tf->bufptr >= tf->bufbytes)
        {
            int result = tf->FillBuffer ();
            if (result < 0)
                break;
        }
        result = 0;

        T *bp = (T *) (tf->buf + tf->bufptr);
        int chars_available = (tf->bufbytes - tf->bufptr) / sizeof (T);
        T *nl = t_memchr (bp, lf, chars_available);
        if (nl)
            chars_available = (int) (nl - bp);

        int chars_to_copy = chars_available;
        //if (chars_to_copy > 0 && bp [chars_to_copy - 1] == cr)
        //    --chars_to_copy;
        tbuf = (T *) alloc_block (tbuf, (nchars + chars_to_copy + 1) * sizeof (T));
        memcpy (tbuf + nchars, bp, chars_to_copy * sizeof (T));
        nchars += chars_to_copy;
        tbuf [nchars] = 0;

        tf->bufptr += chars_available * sizeof (T);
        if (nl)                                     // found newline
        {
            tf->bufptr += sizeof (T);
            break;
        }
    }

    *line_buf = tbuf;
    return result;
}


// TReadChar - handles char's and WCHAR's
template <typename T> int TReadChar (TextFileReader *tf, int strip_cr)
{
    int result;

    do
    {
        if (tf->bufptr >= tf->bufbytes)
        {
            result = tf->FillBuffer ();
            if (result < 0)
                return result;
        }

        result = * (T *) (tf->buf + tf->bufptr);
        tf->bufptr += sizeof (T);
    }
    while (result == strip_cr);

    return result;
}


// ----------------------------------------------------------------------------
// class TextFileWriter: abstract class for encoding-specific functions

class TextFileWriter
{
public:

// Constructor
TextFileWriter::TextFileWriter (const TCHAR *filename, HANDLE hFile, int bufsize)
{
    this->filename = filename;
    this->hFile = hFile;
    this->bufsize = (bufsize) ? bufsize : 4096;     // must be even
    this->buf = (BYTE *) malloc (this->bufsize);
    this->bufptr = 0;
}


// Destructor
virtual TextFileWriter::~TextFileWriter ()
{
    free (this->buf);
}


// WriteChar
virtual int TextFileWriter::WriteChar
    (int ch, int code_page, const char *unknown_char, BOOL *data_lost)
{
    assert (0);
    return TF_ERROR;
}


// WriteString; caller must supply \n
virtual int TextFileWriter::WriteString
    (const TCHAR *s, int len, int code_page, const char *unknown_char, BOOL *data_lost)
{
    assert (0);
    return TF_ERROR;
}


// WriteBOM, if any
virtual int TextFileWriter::WriteBOM (void)
{
    return 0;
}


// WriteBytes
int TextFileWriter::WriteBytes (const BYTE *bytes, int nbytes)
{
    for ( ; ; )
    {
        int bufspace = this->bufsize - this->bufptr;
        if (bufspace > nbytes)
            bufspace = nbytes;
        memcpy (this->buf + this->bufptr, bytes, bufspace);
        this->bufptr += bufspace;
        nbytes -= bufspace;
        if (nbytes == 0)                        // finished, OK
            return 0;
        int result = Flush ();
        if (result < 0)
            return result;
        bytes += bufspace;
    }
}


// Flush buffer
int TextFileWriter::Flush (void)
{
    assert (this->hFile != INVALID_HANDLE_VALUE);
    if (this->bufptr > 0)
    {
        DWORD bytes_written;
        if (!WriteFile (this->hFile, this->buf, this->bufptr, &bytes_written, NULL))
        {
            DWORD err = GetLastError ();
            TCHAR *s_err = LookupSystemError (err);
            LogError (MAKEINTRESOURCE (IDS_FILE_WRITE_ERROR), err, this->filename, s_err);
            free (s_err);
            return TF_ERROR;
        }
        this->bufptr = 0;
    }
    
    return 0;
}

protected:
    const TCHAR *filename;
    HANDLE  hFile;
    int     bufsize;
    BYTE    *buf;
    int     bufptr;
};


// ----------------------------------------------------------------------------
// class ANSI_TextFileReader: read ASCII / ANSI encoded files

class ANSI_TextFileReader : public TextFileReader
{
public:

// Constructor
ANSI_TextFileReader::ANSI_TextFileReader (TextFile *tf, const TCHAR *filename,
    HANDLE hFile, int bufsize) : TextFileReader (filename, hFile, bufsize)
{
    this->tf = tf;
#ifdef _UNICODE
    this->char_buf = NULL;
#endif
}


// Destructor
ANSI_TextFileReader::~ANSI_TextFileReader ()
{
#ifdef _UNICODE
    free_block (this->char_buf);
#endif
}


// ReadLine; line_buf is allocated with alloc_block and may initially be NULL
virtual int ANSI_TextFileReader::ReadLine
    (TCHAR **line_buf, int code_page, const char *unknown_char, BOOL *data_lost)
{
#ifndef _UNICODE
    return TReadLine <BYTE> (this, (BYTE **) line_buf, false);
#else
    int result;
    if (this->tf->GetAnsiPassThru ())
        result = TReadLine <BYTE> (this, (BYTE **) line_buf, false);
    else
    {
        result = TReadLine <BYTE> (this, &this->char_buf, false);
        if (result >= 0)
            linebuf_AtoU ((char *) this->char_buf, -1, line_buf,
                code_page, unknown_char, data_lost);
    }
    return result;
#endif
}


// ReadChar
int ANSI_TextFileReader::ReadChar (void)
{
    return TReadChar <BYTE> (this, '\r');
}

private:
    TextFile *tf;
#ifdef _UNICODE
    BYTE *char_buf;
#endif
};


// ----------------------------------------------------------------------------
// class UTF16LE_TextFileReader: read little-endian UTF16 encoded files

class UTF16LE_TextFileReader : public TextFileReader
{
public:

// Constructor
UTF16LE_TextFileReader::UTF16LE_TextFileReader (const TCHAR *filename, HANDLE hFile, int bufsize) :
    TextFileReader (filename, hFile, bufsize)
{
    assert ((bufsize & 1) == 0);            // avoid buffer boundary problems
    this->utf16_buf = NULL;
}


// Destructor
UTF16LE_TextFileReader::~UTF16LE_TextFileReader ()
{
    free_block (this->utf16_buf);
}


// ReadChar; assumes WCHAR-aligned buffer
virtual int UTF16LE_TextFileReader::ReadChar (void)
{
    return TReadChar <WCHAR> (this, '\r');
}


// ReadLine; line_buf is allocated with alloc_block and may initially be NULL
virtual int UTF16LE_TextFileReader::ReadLine
    (TCHAR **line_buf, int code_page, const char *unknown_char, BOOL *data_lost)
{
#ifdef _UNICODE
    return TReadLine <WCHAR> (this, line_buf, false);
#else
    int result = TReadLine <WCHAR> (this, &this->utf16_buf, false);
    if (result >= 0)
        linebuf_UtoA (this->utf16_buf, -1, line_buf, code_page, unknown_char, data_lost);
    return result;
#endif
}

private:
    WCHAR   *utf16_buf;
};


// ----------------------------------------------------------------------------
// class UTF16BE_TextFileReader: read big-endian UTF16 encoded files

class UTF16BE_TextFileReader : public TextFileReader
{
public:

// Constructor
UTF16BE_TextFileReader::UTF16BE_TextFileReader (const TCHAR *filename, HANDLE hFile, int bufsize) :
    TextFileReader (filename, hFile, bufsize)
{
    assert ((bufsize & 1) == 0);            // avoid buffer boundary problems
#ifndef _UNICODE
    this->utf16_buf = NULL;
#endif
}


// Destructor
UTF16BE_TextFileReader::~UTF16BE_TextFileReader ()
{
#ifndef _UNICODE
    free_block (this->utf16_buf);
#endif
}


// ReadChar; assumes WCHAR-aligned buffer
virtual int UTF16BE_TextFileReader::ReadChar (void)
{
    int result = TReadChar <WCHAR> (this, 0x0d00);      // \r byte-reversed
    if (result < 0)
        return result;

    WCHAR w = result;
    flip_words (&w, 1);
    return w;
}


// ReadLine; line_buf is allocated with alloc_block and may initially be NULL
virtual int UTF16BE_TextFileReader::ReadLine
    (TCHAR **line_buf, int code_page, const char *unknown_char, BOOL *data_lost)
{
#ifdef _UNICODE
    int result = TReadLine <WCHAR> (this, line_buf, true);
    if (result < 0)
        return result;
    flip_words (*line_buf, (int) wcslen (*line_buf));
    return result;
#else
    int result = TReadLine <WCHAR> (this, &this->utf16_buf, true);
    if (result < 0)
        return result;
    flip_words (this->utf16_buf, (int) wcslen (this->utf16_buf));
    linebuf_UtoA (this->utf16_buf, -1, line_buf, code_page, unknown_char, data_lost);
    return result;
#endif
}

private:
#ifndef _UNICODE
    WCHAR   *utf16_buf;
#endif
};


// ----------------------------------------------------------------------------
// class UTF8_TextFileReader: read UTF8 encoded files

class UTF8_TextFileReader : public TextFileReader
{
public:

// Constructor
UTF8_TextFileReader::UTF8_TextFileReader (const TCHAR *filename, HANDLE hFile, int bufsize) :
    TextFileReader (filename, hFile, bufsize)
{
    this->utf8_buf = NULL;
#ifndef _UNICODE
    this->utf16_buf = NULL;
#endif
}


// Destructor
UTF8_TextFileReader::~UTF8_TextFileReader ()
{
    free_block (this->utf8_buf);
#ifndef _UNICODE
    free_block (this->utf16_buf);
#endif
}


// ReadLine; line_buf is allocated with alloc_block and may initially be NULL
virtual int UTF8_TextFileReader::ReadLine
    (TCHAR **line_buf, int code_page, const char *unknown_char, BOOL *data_lost)
{
    int result = TReadLine <BYTE> (this, &this->utf8_buf, false);
    if (result < 0)
        return result;

#ifdef _UNICODE
    WCHAR **p_utf16_buf = line_buf;
#else    
    WCHAR **p_utf16_buf = &this->utf16_buf;
#endif

    BYTE *pb = this->utf8_buf;
    WCHAR *pw = *p_utf16_buf;
    int nchars = 0;
    int ch = 0xFFFD;                        // bad character

    while (*pb)
    {
        int b1 = *pb++;
        if (b1 < 0x80)                      // U-0000 - U-007F: 0bbbbbbb
            ch = b1;
        else if (b1 < 0xe0)                 // U-0080 - U-07FF: 110bbbbb 10bbbbbb
        {
            int b2 = *pb;
            if (b2)
            {
                ch = ((b1 & 0x1F) << 6) | (b2 & 0x3F);
                pb++;
            }
        }
        else if (b1 < 0xf0)                 // U-0800 - U-FFFF: 1110bbbb 10bbbbbb 10bbbbbb
        {
            int b2 = *pb;
            if (b2)
            {
                pb++;
                int b3 = *pb;
                if (b3)
                {
                    ch = ((b1 & 0x0F) << 12) | ((b2 & 0x3F) << 6) | (b3 & 0x3F);
                    pb++;
                }
            }
        }
        else if (b1 < 0xf8)                 // U-00010000 - U-001FFFFF:
        {                                   //     11110bbb 10bbbbbb 10bbbbbb 10bbbbbb
            int b2 = *pb;
            if (b2)
            {
                pb++;
                int b3 = *pb;
                if (b3)
                {
                    pb++;
                    int b4 = *pb;
                    if (b4)
                    {
                        ch = ((b1 & 0x07) << 18) | ((b2 & 0x3F) << 12) |
                             ((b3 & 0x3F) << 6) | (b4 & 0x3f);
                        pb++;
                    }
                }
            }
        }
        else
            ch = 0xFFFD;                    // invalid leadin byte

        if (ch <= 0xFFFF)                   // 'normal' (2-byte) character
        {
            pw = (WCHAR *) alloc_block (pw, (nchars + 1) * sizeof (WCHAR));
            pw [nchars++] = ch;
        }
        else                                // convert to surrogate pair
        {
            if (ch > 0x10FFFF)              // avoid unpleasantness
                ch = 0x10FFFF;
            pw = (WCHAR *) alloc_block (pw, (nchars + 2) * sizeof (WCHAR));
            pw [nchars++] = C_TO_LEAD (ch);
            pw [nchars++] = C_TO_TRAIL (ch);
        }
    }
    
    pw = (WCHAR *) alloc_block (pw, (nchars + 1) * sizeof (WCHAR));
    pw [nchars] = 0;
    *p_utf16_buf = pw;

#ifndef _UNICODE
    linebuf_UtoA (pw, nchars, line_buf, code_page, unknown_char, data_lost);
#endif

    return 0;
}


// ReadChar
int UTF8_TextFileReader::ReadChar (void)
{
#ifndef _UNICODE
    return TReadChar <BYTE> (this, '\r');
#else
    int b1 = TReadChar <BYTE> (this, '\r');
    if (b1 < 0x80)                      // U-0000 - U-007F: 0bbbbbbb, plus EOF / ERROR
         return b1;

    if (b1 < 0xe0)                      // U-0080 - U-07FF: 110bbbbb 10bbbbbb
    {
        int b2 = TReadChar <BYTE> (this, '\r');
        if (b2 < 0)
            return b2;
        return ((b1 & 0x1F) << 6) | (b2 & 0x3F);
    }

    if (b1 < 0xf0)                      // U-0800 - U-FFFF: 1110bbbb 10bbbbbb 10bbbbbb
    {
        int b2 = TReadChar <BYTE> (this, '\r');
        if (b2 < 0)
            return b2;
        int b3 = TReadChar <BYTE> (this, '\r');
        if (b3 < 0)
            return b3;
        return ((b1 & 0x0F) << 12) | ((b2 & 0x3F) << 6) | (b3 & 0x3F);
    }
    
    if (b1 < 0xf8)                      // U-00010000 - U-001FFFFF:
    {                                   //     11110bbb 10bbbbbb 10bbbbbb 10bbbbbb
        int b2 = TReadChar <BYTE> (this, '\r');
        if (b2 < 0)
            return b2;
        int b3 = TReadChar <BYTE> (this, '\r');
        if (b3 < 0)
            return b3;
        int b4 = TReadChar <BYTE> (this, '\r');
        if (b4 < 0)
            return b4;
        return ((b1 & 0x07) << 18) | ((b2 & 0x3F) << 12) |
               ((b3 & 0x3F) << 6) | (b4 & 0x3f);
    }
    
    return 0xFFFD;                      // illegal lead-in byte
#endif
}

private:
    BYTE *utf8_buf;
#ifndef _UNICODE
    WCHAR *utf16_buf;
#endif
};


// ----------------------------------------------------------------------------
// class ANSI_TextFileWriter: write ANSI files

class ANSI_TextFileWriter : public TextFileWriter
{
public:

// Constructor
ANSI_TextFileWriter::ANSI_TextFileWriter (const TCHAR *filename, HANDLE hFile, int bufsize) :
    TextFileWriter (filename, hFile, bufsize)
{    
#ifdef _UNICODE
    this->char_buf = NULL;
#endif
}


// Destructor
ANSI_TextFileWriter::~ANSI_TextFileWriter ()
{
#ifdef _UNICODE
    free_block (this->char_buf);
#endif
}


// WriteChar
int ANSI_TextFileWriter::WriteChar
    (int ch, int code_page, const char *unknown_char, BOOL *data_lost)
{
#ifdef _UNICODE
    WCHAR u [2];
    u [0] = ch;
    u [1] = 0;
    return WriteString (u, 1, code_page, unknown_char, data_lost);
#else
    BYTE b = ch;
    return WriteBytes (&b, 1);
#endif
}


// WriteString; caller must supply \n
int ANSI_TextFileWriter::WriteString
    (const TCHAR *s, int len, int code_page, const char *unknown_char, BOOL *data_lost)
{
#ifdef _UNICODE
    int nbytes = linebuf_UtoA (s, len, (char **) &this->char_buf,
        code_page, unknown_char, data_lost);
    return WriteBytes (this->char_buf, nbytes);
#else
    return WriteBytes ((BYTE *) s, len);
#endif
}

private:
#ifdef _UNICODE
    BYTE    *char_buf;
#endif
};


// ----------------------------------------------------------------------------
// class UTF16LE_TextFileWriter: write UTF16LE files

class UTF16LE_TextFileWriter : public TextFileWriter
{
public:

// Constructor
UTF16LE_TextFileWriter::UTF16LE_TextFileWriter (const TCHAR *filename, HANDLE hFile, int bufsize) :
    TextFileWriter (filename, hFile, bufsize)
{
#ifndef _UNICODE
    this->utf16_buf = NULL;
#endif
}


// Destructor
UTF16LE_TextFileWriter::~UTF16LE_TextFileWriter ()
{
#ifndef _UNICODE
    free_block (this->utf16_buf);
#endif
}


// WriteBOM
virtual int UTF16LE_TextFileWriter::WriteBOM (void)
{
    BYTE bom [2] = { 0xFF, 0xFE };
    return WriteBytes (bom, sizeof (bom));
}


// WriteChar
int UTF16LE_TextFileWriter::WriteChar
    (int ch, int code_page, const char *unknown_char, BOOL *data_lost)
{
#ifdef _UNICODE
    return WriteBytes ((BYTE *) &ch, sizeof (WCHAR));
#else
    char a [2];
    a [0] = ch;
    a [1] = 0;
    return WriteString (a, 1, code_page, unknown_char, data_lost);
#endif
}


// WriteString; caller must supply \n
int UTF16LE_TextFileWriter::WriteString
    (const TCHAR *s, int len, int code_page, const char *unknown_char, BOOL *data_lost)
{
#ifdef _UNICODE
    return WriteBytes ((BYTE *) s, len * sizeof (WCHAR));
#else
    len = linebuf_AtoU (s, len, &this->utf16_buf, code_page, unknown_char, data_lost);
    return WriteBytes ((BYTE *) this->utf16_buf, len * sizeof (WCHAR));
#endif
}

private:
#ifndef _UNICODE
    WCHAR *utf16_buf;
#endif
};


// ----------------------------------------------------------------------------
// class UTF16BE_TextFileWriter: write UTF16BE files

class UTF16BE_TextFileWriter : public TextFileWriter
{
public:

// Constructor
UTF16BE_TextFileWriter::UTF16BE_TextFileWriter (const TCHAR *filename, HANDLE hFile, int bufsize) :
    TextFileWriter (filename, hFile, bufsize)
{
    this->utf16_buf = NULL;
}


// Destructor
UTF16BE_TextFileWriter::~UTF16BE_TextFileWriter ()
{
    free_block (this->utf16_buf);
}


// WriteBOM
virtual int UTF16BE_TextFileWriter::WriteBOM (void)
{
    BYTE bom [2] = { 0xFE, 0xFF };
    return WriteBytes (bom, sizeof (bom));
}


// WriteChar
int UTF16BE_TextFileWriter::WriteChar
    (int ch, int code_page, const char *unknown_char, BOOL *data_lost)
{
#ifdef _UNICODE
    BYTE b [2];
    b [0] = ch >> 8;
    b [1] = ch & 0xFF;
    return WriteBytes (b, 2);
#else
    char a [2];
    a [0] = ch;
    a [1] = 0;
    return WriteString (a, 1, code_page, unknown_char, data_lost);
#endif
}


// WriteString; caller must supply \n
int UTF16BE_TextFileWriter::WriteString
    (const TCHAR *s, int len, int code_page, const char *unknown_char, BOOL *data_lost)
{
#ifdef _UNICODE
    int nbytes = len * sizeof (WCHAR);
    this->utf16_buf = (WCHAR *) alloc_block (this->utf16_buf, nbytes);
    memcpy (this->utf16_buf, s, nbytes);
#else
    len = linebuf_AtoU (s, len, &this->utf16_buf, code_page, unknown_char, data_lost);
    int nbytes = len * sizeof (WCHAR);
#endif

    flip_words (this->utf16_buf, len);
    return WriteBytes ((BYTE *) this->utf16_buf, nbytes);
}

private:
    WCHAR *utf16_buf;
};


// ----------------------------------------------------------------------------
// class UTF8_TextFileWriter: write UTF8 files

// Convert one Unicode character to upto 4 UTF8 bytes
// Returns byte count
static inline int UtoUTF8 (int ch, BYTE b [4])
{
    if (ch < 0x80)              // U-0000 - U-007F: 0bbbbbbb
    {
        b [0] = (BYTE) ch;
        return 1;
    }
    
    if (ch < 0x800)             // U-0080 - U-07FF: 110bbbbb 10bbbbbb
    {
        b [0] = (ch >> 6) | 0xc0;
        b [1] = (ch & 0x3F) | 0x80;
        return 2;
    }

    if (ch < 0xFFFF)            // U-0800 - U-FFFF: 1110bbbb 10bbbbbb 10bbbbbb
    {
        b [0] = (ch >> 12) | 0xe0;
        b [1] = ((ch >> 6) & 0x3F) | 0x80;
        b [2] = (ch & 0x3F) | 0x80;
        return 3;
    }
                                // U-00010000 - U-001FFFFF:
                                //     11110bbb 10bbbbbb 10bbbbbb 10bbbbbb
    b [0] = (ch >> 18) | 0xf0;
    b [1] = ((ch >> 12) & 0x3F) | 0x80;
    b [2] = ((ch >> 6) & 0x3F) | 0x80;
    b [3] = (ch & 0x3F) | 0x80;
    return 4;
}


class UTF8_TextFileWriter : public TextFileWriter
{
public:

// Constructor
UTF8_TextFileWriter::UTF8_TextFileWriter (const TCHAR *filename, HANDLE hFile, int bufsize) :
    TextFileWriter (filename, hFile, bufsize) {}


// WriteBOM
virtual int UTF8_TextFileWriter::WriteBOM (void)
{
    BYTE bom [3] = { 0xEF, 0xBB, 0xBF };
    return WriteBytes (bom, sizeof (bom));
}


// WriteChar
int UTF8_TextFileWriter::WriteChar
    (int ch, int code_page, const char *unknown_char, BOOL *data_lost)
{
    BYTE b [4];
    int nbytes = UtoUTF8 (ch, b);
    return WriteBytes (b, nbytes);
}


// WriteString; caller must supply \n
// Handles surrogate pairs correctly, even when writing to UTF-8 files
// Invalid surrogate pairs are output as 0xFFFD to avoid generating a
// non-conformant UTF-8 file
int UTF8_TextFileWriter::WriteString
    (const TCHAR *s, int len, int code_page, const char *unknown_char, BOOL *data_lost)
{
    while (len--)                               // inline, for speed
    {
#ifdef _UNICODE
        int ch = *s++;
        if (ch >= 0xD800 && ch <= 0xDBFF)       // surrogate pair
        {
            if (len > 0)
            {
                int trail = *s++;
                len--;
                ch = (trail >= 0xDC00 && trail <= 0xDFFF) ? SP_TO_C (ch, trail) : 0xFFFD;
            }
            else
                ch = 0xFFFD;                    // missing trail byte
        }
#else
        int ch = (BYTE) *s++;                   // avoid sign-extension problems
#endif
        BYTE b [4];
        int nbytes = UtoUTF8 (ch, b);
        int result = WriteBytes (b, nbytes);
        if (result < 0)
            return result;
    }

    return 0;
}

};


// ----------------------------------------------------------------------------
// class TextFile

// Constructor
TextFile::TextFile ()
{
    this->filename = NULL;
    this->filemode = 0;
    this->encoding = 0;
    this->hFile = INVALID_HANDLE_VALUE;
    this->file_reader = NULL;
    this->file_writer = NULL;
    this->need_bom = false;
    this->code_page = CP_ACP;
    this->unknown_char = NULL;
}


// Destructor
TextFile::~TextFile ()
{
    Close ();
    free (this->unknown_char);
}


// Open (not in constructor, lest it fail); sets last error code and string
int TextFile::Open (const TCHAR *filename, int filemode, int encoding, int bufsize)
{
    DWORD dwDesiredAccess, dwCreationDisposition;
    int err_id;
    int encoding_flags = encoding;
    encoding &= 0xFF;

    if (filemode == TF_READ)
    {
        dwDesiredAccess = GENERIC_READ;
        dwCreationDisposition = OPEN_EXISTING;
//      assert (encoding == 0 || encoding == TF_ANSI);
        err_id = IDS_CANNOT_OPEN_FILE;
    }
    else
    {
        dwDesiredAccess = GENERIC_WRITE;
        dwCreationDisposition = (filemode == TF_WRITE) ? CREATE_ALWAYS : OPEN_ALWAYS;
        if (encoding == 0)
            encoding = TF_ANSI;
        err_id = IDS_CANNOT_OPEN_FILE_FOR_WRITING;
    }
    
    HANDLE hFile = CreateFile (filename, dwDesiredAccess, FILE_SHARE_READ, NULL,
        dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        DWORD err = GetLastError ();
        TCHAR *s_err = LookupSystemError (err);
        LogError (MAKEINTRESOURCE (err_id), filename, err, s_err);
        free (s_err);
        return TF_ERROR;
    }
    
    this->filename = copy_string (filename);
    this->filemode = filemode;
    this->encoding = encoding;
    this->encoding_flags = encoding_flags;
    this->ansi_passthru = false;
    this->bufsize = bufsize;
    this->hFile = hFile;

    if (filemode == TF_READ)
        return CreateFileReader ();

    this->need_bom = true;              // unless proved otherwise
    if (filemode == TF_APPEND)
    {
        DWORD filesize = GetFileSize (hFile, NULL);
        if (filesize > 0)
        {
            SetFilePointer (hFile, 0, NULL, FILE_END);
            this->need_bom = false;
        }
    }
    
    CreateFileWriter ();
    return 0;
}


// Close; sets last error code and string if can't flush buffer
int TextFile::Close (void)
{
    if (this->hFile == INVALID_HANDLE_VALUE)
        return 0;
    int result = Flush ();
    CloseHandle (this->hFile);
    this->hFile = INVALID_HANDLE_VALUE;
    this->filemode = 0;
    delete this->file_reader;
    delete this->file_writer;
    free (this->filename);
    return result;
}


// Flush our buffer; sets last error code and string on error
int TextFile::Flush (void)
{
    if (this->filemode == TF_READ)
        return 0;
    return this->file_writer->Flush ();
}


// ReadLine; line_buf is allocated with alloc_block and may initially be NULL
// Character codes exceeding 0xFFFF in UTF-8 files are converted to surrogate pairs
int TextFile::ReadLine (BOOL *data_lost, TCHAR **line_buf)
{
    assert (this->filemode == TF_READ);
    if (data_lost)
        *data_lost = FALSE;

    return this->file_reader->ReadLine (line_buf, this->code_page, this->unknown_char, data_lost);
}


// Read a character.  Note that, for unicode files, this reads a unicode character
// This routine correctly handles character codes exceeding 0xFFFF in UTF-8 files
// but does not convert them to surrogate pairs.  To do this, pass the value returned
// to C_TO_LEAD and C_TO_TRAIL if it exceeds 0xFFFF
int TextFile::ReadChar (void)
{
    assert (this->filemode == TF_READ);
    return this->file_reader->ReadChar ();
}


// Write a string; sets last error code and string on error
int TextFile::WriteString (BOOL *data_lost, const TCHAR *s)
{
    assert (this->filemode > TF_READ);
    if (data_lost)
        *data_lost = FALSE;

    if (this->need_bom)
    {
        int result = file_writer->WriteBOM ();
        if (result < 0)
            return result;
        this->need_bom = false;
    }
    
    // Convert LF to CRLF (yawn)
    int code_page = this->code_page;
    char *unknown_char = this->unknown_char;
    bool unix = (this->encoding_flags & TF_UNIX) != 0;

    while (*s)
    {
        const TCHAR *nl = (unix) ? NULL : _tcschr (s, '\n');
        if (nl)
        {
            int len = (int) (nl - s);
            int result = this->file_writer->WriteString
                (s, len, code_page, unknown_char, data_lost);
            if (result < 0)
                return result;
            result = this->file_writer->WriteString
                    (__T ("\r\n"), 2, code_page, unknown_char, data_lost);
            if (result < 0)
                return result;
            s = nl + 1;
        }
        else
            return this->file_writer->WriteString
                (s, (int) _tcslen (s), code_page, unknown_char, data_lost);
    }
    
    return 0;
}


// printf, effectively; sets last error code and string on error
int TextFile::FormatString (BOOL *data_lost, const TCHAR *s, ...)
{
    va_list ap;
    va_start (ap, s);
    TCHAR *p = vFormatPString (s, ap);
    int result = WriteString (data_lost, p);
    va_end (ap);
    free (p);
    return result;
}


// printf, effectively; sets last error code and string on error
int TextFile::vFormatString (BOOL *data_lost, const TCHAR *s, va_list ap)
{
    TCHAR *p = vFormatPString (s, ap);
    int result = WriteString (data_lost, p);
    free (p);
    return result;
}


// Write a characte; sets last error code and string on error
// Correctly handles character codes > 0xFFFF when writing to UTF-8 files, but
// the caller must first convert a surrogate pair to UTF-32 (by calling SP_TO_C)
int TextFile::WriteChar (BOOL *data_lost, int ch)
{
    assert (this->filemode > TF_READ);
    if (data_lost)
        *data_lost = FALSE;

    if (this->need_bom)
    {
        int result = file_writer->WriteBOM ();
        if (result < 0)
            return result;
        this->need_bom = false;
    }

    if (ch == '\n')                         // do LF to CRLF mapping
        return WriteString (data_lost, __T ("\n"));

    return this->file_writer->WriteChar (ch, this->code_page, this->unknown_char, data_lost);
}


// Set 'unknown' character; can do this without opening the file
void TextFile::SetUnknownChar (const char *unknown_char)
{
    free (this->unknown_char);
    this->unknown_char = (unknown_char) ? AtoA (unknown_char) : NULL;
}


// Return ANSI characters read from file unchanged
// For ANSI-files only.
// Note that ReadLine then returns chars, not TCHAR's
void TextFile::SetAnsiPassThru (bool passthru)
{
    assert (this->filemode == TF_READ);
    if (passthru)
        assert (this->encoding == TF_ANSI);
    this->ansi_passthru = passthru;
}


// read 1 byte; set last error string on error
static int read_1_byte (TCHAR *filename, HANDLE hFile)
{
    BYTE b;
    DWORD bytes_read;
    if (!ReadFile (hFile, &b, 1, &bytes_read, NULL))
    {
        DWORD err = GetLastError ();
        TCHAR *s_err = LookupSystemError (err);
        LogError (MAKEINTRESOURCE (IDS_FILE_READ_ERROR), err, filename, s_err);
        free (s_err);
        return TF_ERROR;
    }
    
    return (bytes_read) ? b : TF_EOF;
}


// Check if this file contains a BOM.  If so, read it and throw it away
static bool check_bom (TCHAR *filename, HANDLE hFile, char *bom)
{
    while (*bom)
    {
        int b = read_1_byte (filename, hFile);
        if (b != * (UCHAR *) bom++)
        {
            SetFilePointer (hFile, 0, NULL, FILE_BEGIN);
            return false;
        }
    }
    
    return true;
}


// Create textfile reader and read BOM
int TextFile::CreateFileReader (void)
{
    TCHAR *filename = this->filename;
    HANDLE hFile = this->hFile;
    bool do_check_bom = (this->encoding_flags & TF_NO_BOM_CHECK) == 0;

    // Check if the caller has specified the file encoding
    switch (this->encoding)
    {
        case TF_ANSI:
            this->file_reader = Hnew ANSI_TextFileReader (this, filename, hFile, this->bufsize);
            return 0;

        case TF_UTF8:
            if (do_check_bom)
                check_bom (filename, hFile, "\xEF\xBB\xBF");
            this->file_reader = Hnew UTF8_TextFileReader (filename, hFile, this->bufsize);
            return 0;

        case TF_UTF16LE:
            if (do_check_bom)
                check_bom (filename, hFile, "\xFF\xFE");
            this->file_reader = Hnew UTF16LE_TextFileReader (filename, hFile, this->bufsize);
            return 0;

        case TF_UTF16BE:
            if (do_check_bom)
                check_bom (filename, hFile, "\xFE\xFF");
            this->file_reader = Hnew UTF16BE_TextFileReader (filename, hFile, this->bufsize);
            return 0;
    }

    // No encoding specified
    int b1 = read_1_byte (filename, hFile);
    if (b1 == TF_ERROR)
        return TF_ERROR;
    if (b1 == TF_EOF)                           // empty file (encoding == 0)
    {
        this->file_reader = Hnew TextFileReader (filename, hFile, -1);
        return 0;
    }

    if (b1 == 0xFF)                             // UTF16LE?
    {
        int b2 = read_1_byte (filename, hFile);
        if (b2 == TF_ERROR)
            return TF_ERROR;
        if (b2 == 0xFE)
        {
            this->encoding = TF_UTF16LE;
            this->file_reader = Hnew UTF16LE_TextFileReader (filename, hFile, this->bufsize);
        }
        else
        {
            SetFilePointer (hFile, 0, NULL, FILE_BEGIN);
            this->encoding = TF_ANSI;
            this->file_reader = Hnew ANSI_TextFileReader (this, filename, hFile, this->bufsize);
        }
        return 0;
    }

    if (b1 == 0xFE)                             // UTF16BE?
    {
        int b2 = read_1_byte (filename, hFile);
        if (b2 == TF_ERROR)
            return TF_ERROR;
        if (b2 == 0xFF)
        {
            this->encoding = TF_UTF16BE;
            this->file_reader = Hnew UTF16BE_TextFileReader (filename, hFile, this->bufsize);
            return 0;
        }
    }

    if (b1 == 0xEF)                             // UTF8?
    {
        int b2 = read_1_byte (filename, hFile);
        if (b2 == TF_ERROR)
            return TF_ERROR;
        if (b2 == 0xBB)
        {
            int b3 = read_1_byte (filename, hFile);
            if (b3 == TF_ERROR)
                return TF_ERROR;
            if (b3 == 0xBF)
            {
                this->encoding = TF_UTF8;
                this->file_reader = Hnew UTF8_TextFileReader (filename, hFile, this->bufsize);
                return 0;
            }        
        }
    }

    SetFilePointer (hFile, 0, NULL, FILE_BEGIN);
    this->encoding = TF_ANSI;
    this->file_reader = Hnew ANSI_TextFileReader (this, filename, hFile, this->bufsize);
    return 0;
}


// Create textfile writer
void TextFile::CreateFileWriter (void)
{
    switch (this->encoding)
    {
        case TF_ANSI:
            this->file_writer = Hnew ANSI_TextFileWriter
                (this->filename, this->hFile, this->bufsize);
            break;

        case TF_UTF16LE:
            this->file_writer = Hnew UTF16LE_TextFileWriter
                (this->filename, this->hFile, this->bufsize);
            break;

        case TF_UTF16BE:
            this->file_writer = Hnew UTF16BE_TextFileWriter
                (this->filename, this->hFile, this->bufsize);
            break;

        case TF_UTF8:
            this->file_writer = Hnew UTF8_TextFileWriter
                (this->filename, this->hFile, this->bufsize);
            break;

        default:
            assert (0);
            break;
    }
}

int TextFile::GuessCodepage(char* buf, size_t len, CString& strCodePageName)
{
	uchardet_t ud = uchardet_new();
	uchardet_handle_data(ud, buf, len);
	uchardet_data_end(ud);
	const char* cs = uchardet_get_charset(ud);
	strCodePageName = cs;
	int codepage = EncodingManager.GetEncodingFromString(cs);
	uchardet_delete(ud);
	return codepage;
}

//////////////////////////////////////////////////////////////////
// use uchardet source code from http://www.mozilla.org/MPL/

static EncodingMap map_encodings[] = 
{
	{ 1250,  "windows-1250" },                                                                    //IDM_FORMAT_WIN_1250
	{ 1251,  "windows-1251" },                                                                    //IDM_FORMAT_WIN_1251
	{ 1252,  "windows-1252" },                                                                    //IDM_FORMAT_WIN_1252
	{ 1253,  "windows-1253" },                                                                    //IDM_FORMAT_WIN_1253
	{ 1254,  "windows-1254" },                                                                    //IDM_FORMAT_WIN_1254
	{ 1255,  "windows-1255" },                                                                    //IDM_FORMAT_WIN_1255
	{ 1256,  "windows-1256" },                                                                    //IDM_FORMAT_WIN_1256
	{ 1257,  "windows-1257" },                                                                    //IDM_FORMAT_WIN_1257
	{ 1258,  "windows-1258" },                                                                    //IDM_FORMAT_WIN_1258
	{ 28591, "latin1 ISO_8859-1 ISO-8859-1 CP819 IBM819 csISOLatin1 iso-ir-100 l1" },             //IDM_FORMAT_ISO_8859_1 
	{ 28592, "latin2 ISO_8859-2 ISO-8859-2 csISOLatin2 iso-ir-101 l2" },                          //IDM_FORMAT_ISO_8859_2 
	{ 28593, "latin3 ISO_8859-3 ISO-8859-3 csISOLatin3 iso-ir-109 l3" },                          //IDM_FORMAT_ISO_8859_3 
	{ 28594, "latin4 ISO_8859-4 ISO-8859-4 csISOLatin4 iso-ir-110 l4" },                          //IDM_FORMAT_ISO_8859_4 
	{ 28595, "cyrillic ISO_8859-5 ISO-8859-5 csISOLatinCyrillic iso-ir-144" },                    //IDM_FORMAT_ISO_8859_5 
	{ 28596, "arabic ISO_8859-6 ISO-8859-6 csISOLatinArabic iso-ir-127 ASMO-708 ECMA-114" },      //IDM_FORMAT_ISO_8859_6 
	{ 28597, "greek ISO_8859-7 ISO-8859-7 csISOLatinGreek greek8 iso-ir-126 ELOT_928 ECMA-118" }, //IDM_FORMAT_ISO_8859_7 
	{ 28598, "hebrew ISO_8859-8 ISO-8859-8 csISOLatinHebrew iso-ir-138" },                        //IDM_FORMAT_ISO_8859_8 
	{ 28599, "latin5 ISO_8859-9 ISO-8859-9 csISOLatin5 iso-ir-148 l5" },                          //IDM_FORMAT_ISO_8859_9 
	{ -1,    ""/*"latin6 ISO_8859-10 ISO-8859-10 csISOLatin6 iso-ir-157 l6"*/ },                  //IDM_FORMAT_ISO_8859_10
	{ -1,    ""/*"ISO_8859-11 ISO-8859-11"*/ },                                                   //IDM_FORMAT_ISO_8859_11
	{ 28603, "ISO_8859-13 ISO-8859-13" },                                                         //IDM_FORMAT_ISO_8859_13
	{ 28604, "iso-celtic latin8 ISO_8859-14 ISO-8859-14 18 iso-ir-199" },                         //IDM_FORMAT_ISO_8859_14
	{ 28605, "Latin-9 ISO_8859-15 ISO-8859-15" },                                                 //IDM_FORMAT_ISO_8859_15
	{ -1,    ""/*"latin10 ISO_8859-16 ISO-8859-16 110 iso-ir-226"*/ },                            //IDM_FORMAT_ISO_8859_16
	{ 437,   "IBM437 cp437 437 csPC8CodePage437" },                                               //IDM_FORMAT_DOS_437
	{ 720,   "IBM720 cp720 oem720 720" },                                                         //IDM_FORMAT_DOS_720
	{ 737,   "IBM737 cp737 oem737 737" },                                                         //IDM_FORMAT_DOS_737
	{ 775,   "IBM775 cp775 oem775 775" },                                                         //IDM_FORMAT_DOS_775
	{ 850,   "IBM850 cp850 oem850 850" },                                                         //IDM_FORMAT_DOS_850
	{ 852,   "IBM852 cp852 oem852 852" },                                                         //IDM_FORMAT_DOS_852
	{ 855,   "IBM855 cp855 oem855 855 csIBM855" },                                                //IDM_FORMAT_DOS_855
	{ 857,   "IBM857 cp857 oem857 857" },                                                         //IDM_FORMAT_DOS_857
	{ 858,   "IBM858 cp858 oem858 858" },                                                         //IDM_FORMAT_DOS_858
	{ 860,   "IBM860 cp860 oem860 860" },                                                         //IDM_FORMAT_DOS_860
	{ 861,   "IBM861 cp861 oem861 861" },                                                         //IDM_FORMAT_DOS_861
	{ 862,   "IBM862 cp862 oem862 862" },                                                         //IDM_FORMAT_DOS_862
	{ 863,   "IBM863 cp863 oem863 863" },                                                         //IDM_FORMAT_DOS_863
	{ 865,   "IBM865 cp865 oem865 865" },                                                         //IDM_FORMAT_DOS_865
	{ 866,   "IBM866 cp866 oem866 866" },                                                         //IDM_FORMAT_DOS_866
	{ 869,   "IBM869 cp869 oem869 869" },                                                         //IDM_FORMAT_DOS_869
	{ 950,   "big5 csBig5" },                                                                     //IDM_FORMAT_BIG5
	{ 936,   "gb2312 gbk csGB2312 gb18030" },                                                     //IDM_FORMAT_GB2312
	{ 932,   "Shift_JIS MS_Kanji csShiftJIS csWindows31J" },                                      //IDM_FORMAT_SHIFT_JIS
	{ 949,   "windows-949 korean" },                                                              //IDM_FORMAT_KOREAN_WIN
	{ 51949, "euc-kr csEUCKR" },                                                                  //IDM_FORMAT_EUC_KR
	{ 874,   "tis-620" },                                                                         //IDM_FORMAT_TIS_620
	{ 10007, "x-mac-cyrillic xmaccyrillic" },                                                     //IDM_FORMAT_MAC_CYRILLIC
	{ 21866, "koi8_u koi8-u" },                                                                   //IDM_FORMAT_KOI8U_CYRILLIC
	{ 20866, "koi8_r koi8-r csKOI8R" }                                                            //IDM_FORMAT_KOI8R_CYRILLIC
};

bool IsExistedInEncodingMap(const char *token, const char *list)
{
	if ((!token) || (!list))
		return false;
	char word[64];
	size_t i = 0;
	size_t j = 0;
	for (size_t len = strlen(list); i <= len; ++i)
	{
		if ((list[i] == ' ') || (list[i] == '\0'))
		{
			if (j != 0)
			{
				word[j] = '\0';
				j = 0;
				if (!_stricmp(token, word))
					return true;
			}
		}
		else
		{
			word[j] = list[i];
			++j;
		}
	}
	return false;
};

int CEncodingManager::GetEncodingFromIndex(int index) const
{
	size_t nbItem = sizeof(map_encodings) / sizeof(EncodingMap);
	if (index < 0 || (size_t)index >= nbItem)
		return -1;
	return map_encodings[index]._codePage;
}

int CEncodingManager::GetIndexFromEncoding(int encoding) const
{
	bool found = false;
	int nbItem = sizeof(map_encodings) / sizeof(EncodingMap);
	int i = 0;
	if (encoding == -1)
		return -1;
	for (; i < nbItem; ++i)
	{
		if (map_encodings[i]._codePage == encoding)
		{
			found = true;
			break;
		}
	}
	return found ? i : -1;
}

int CEncodingManager::GetEncodingFromString(const char *encodingAlias) const
{
	if (IsExistedInEncodingMap(encodingAlias, "utf-8 utf8"))
		return CP_UTF8;
	size_t nbItem = sizeof(map_encodings) / sizeof(EncodingMap);
	int enc = CP_INVALID;
	for (size_t i = 0; i < nbItem; ++i)
	{
		if (IsExistedInEncodingMap(encodingAlias, map_encodings[i]._aliasList))
		{
			enc = map_encodings[i]._codePage;
			break;
		}
	}
	return enc;
}