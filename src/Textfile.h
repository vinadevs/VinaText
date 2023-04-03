/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

// Text file I/O - Unicode/ASCII/ANSI/UTF-8

// ----------------------------------------------------------------------------
// class TextFile

// filemode
#define TF_READ         1                  // existing file
#define TF_WRITE        2                  // new file
#define TF_APPEND       3                  // append to existing file

#define TF_UNIX         0x100               // write out line-ends as \n, not \r\n
#define TF_NO_BOM_CHECK 0x200               // don't check for a BOM if explicit encoding
                                            // specified when opening a fiole for TF_READ access

// Error codes for ReadByte / ReadChar functions (negative)
#define TF_EOF          -1
#define TF_ERROR        -2

// Conversion between UTF-16 surrogate pairs and UTF-32
// See: http://unicode.org/faq/utf_bom.html#35
// Valid lead-in codes are in the range 0xD800 to 0xDBFF inclusive
// Valid trail codes are in the range 0xDC00 to 0xDFFF inclusive
#define LEAD_OFFSET             (0xD800 - (0x10000 >> 10))
#define SURROGATE_OFFSET        (0x10000 - (0xD800 << 10) - 0xDC00)
#define C_TO_LEAD(c)            (LEAD_OFFSET + ((c) >> 10))
#define C_TO_TRAIL(c)           (0xDC00 + ((c) & 0x3FF))
#define SP_TO_C(lead, trail)    (((lead) << 10) + (trail) + SURROGATE_OFFSET)

class TextFileReader;
class TextFileWriter;
class ANSI_TextFileReader;

class TextFile
{
public:

// Constructor
TextFile::TextFile ();

// Destructor
TextFile::~TextFile ();

// Open (not in constructor, lest it fail); sets last error code and string
int TextFile::Open (const TCHAR *filename, int filemode, int encoding = 0, int bufsize = 0);

// Close; sets last error code and string if can't flush buffer
int TextFile::Close (void);

// Flush our buffer; sets last error code and string on error
int TextFile::Flush (void);

// ReadLine; line_buf is allocated with alloc_block and may initially be NULL
// Character codes exceeding 0xFFFF in UTF-8 files are converted to surrogate pairs
int TextFile::ReadLine (BOOL *data_lost, TCHAR **line_buf);

// Read a character.  Note that, for unicode files, this reads a unicode character
// This routine correctly handles character codes exceeding 0xFFFF in UTF-8 files
// but does not convert them to surrogate pairs.  To do this, pass the value returned
// to C_TO_LEAD and C_TO_TRAIL if it exceeds 0xFFFF
int TextFile::ReadChar (void);

// Write a string; sets last error code and string on error
// Handles surrogate pairs correctly, even when writing to UTF-8 files
// Invalid surrogate pairs are output as 0xFFFD to avoid generating a
// non-conformant UTF-8 file
int TextFile::WriteString (BOOL *data_lost, const TCHAR *s);

// printf, effectively; sets last error code and string on error
int TextFile::FormatString (BOOL *data_lost, const TCHAR *s, ...);

// printf, effectively; sets last error code and string on error
int TextFile::vFormatString (BOOL *data_lost, const TCHAR *s, va_list ap);

// Write a character; sets last error code and string on error
// Correctly handles character codes > 0xFFFF when writing to UTF-8 files, but
// the caller must first convert a surrogate pair to UTF-32 (by calling SP_TO_C)
int TextFile::WriteChar (BOOL *data_lost, int ch);

// Return the file encoding (for TF_READ)
int TextFile::GetEncoding (void) { return this->encoding; }

// Set code page; can do this without opening the file
void TextFile::SetCodePage (int code_page) { this->code_page = code_page; }

// Set 'unknown' character; can do this without opening the file
void TextFile::SetUnknownChar (const char *unknown_char);

// Return ANSI characters read from file unchanged
// For ANSI-files only.
// Note that ReadLine then returns chars, not TCHAR's
void TextFile::SetAnsiPassThru (bool passthru);

// Return ANSI characters read from file unchanged (but widened)
// For ANSI-files only.
inline bool TextFile::GetAnsiPassThru (void) { return this->ansi_passthru; }

int TextFile::GuessCodepage(char * buf, size_t len, CString& strCodePageName);

private:

// Create textfile reader and read BOM
int TextFile::CreateFileReader (void);

// Create textfile writer
void TextFile::CreateFileWriter (void);

private:
    TCHAR  *filename;
    int     filemode;
    int     encoding;
    int     encoding_flags;
    bool    ansi_passthru;
    int     bufsize;
    HANDLE  hFile;
    TextFileReader *file_reader;
    TextFileWriter *file_writer;
    bool    need_bom;
    int     code_page;
    char   *unknown_char;
};

//////////////////////////////////////////////////////////////////
// use uchardet source code from http://www.mozilla.org/MPL/

struct EncodingMap
{
	int _codePage;
	const char *_aliasList;
	EncodingMap(int codePage, const char *aliasLis)
	{
		_codePage = codePage;
		_aliasList = aliasLis;
	}
};

class CEncodingManager : public CSingletonHelper<CEncodingManager>
{
public:
	int GetEncodingFromIndex(int index) const;
	int GetIndexFromEncoding(int encoding) const;
	int GetEncodingFromString(const char * encodingAlias) const;
};

#define EncodingManager CEncodingManager::GetInstance()