/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#ifndef _FILE_CRYPTOGRAPHY_H_
#define _FILE_CRYPTOGRAPHY_H_

#include <bcrypt.h>

#ifndef NTSTATUS
typedef LONG NTSTATUS, *PNSTATUS;
#endif

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS                  ((NTSTATUS)0x00000000L)
#define STATUS_NOT_SUPPORTED            ((NTSTATUS)0xC00000BBL)
#define STATUS_UNSUCCESSFUL             ((NTSTATUS)0xC0000001L)
#define STATUS_HMAC_NOT_SUPPORTED       ((NTSTATUS)0xC000A001L)
#define STATUS_BUFFER_TOO_SMALL         ((NTSTATUS)0xC0000023L)
#define STATUS_NOT_IMPLEMENTED          ((NTSTATUS)0xC0000002L)
#endif

const DWORD BLOCK_BUFFER_SIZE = 1024*16;

#define SYMM_KEY_SIZE_SECRET 16

// an initialization vector (IV) will prevent repetition in data encryption, more harder to decrypt data
static const BYTE vectorIV[] =
{
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};

// internal key will be used to encrypt/decrypt file data (AES Symmetric method)
// 16 bytes ~ 128 bit ~ 10 rounds of AES encryption
static const BYTE AES128bit_Key[] =
{
	'1', '2', '3', '4', '5', '6', '7', '8'
};

class CCryptographyIO
{
public:
	BOOL EnumProviders(CStringList *lstRegisteredProviders);
	BOOL CryptFile(BOOL bEncrypt, BOOL bSHAMethod, CString strFileToOpen, CString strFileToCrypt, CString strKey);
	CCryptographyIO();
	virtual ~CCryptographyIO();

private:
	void SetLenghtFileToOpen(ULONGLONG iLenghtFileToOpen);
	BOOL LastCryptBuffRead();
	void SetTotalByteRead(UINT iByteRead);
	ULONGLONG m_iLenghtFileToOpen;
	ULONGLONG m_iTotalByteRead;

	//Handle for AES method
	BCRYPT_ALG_HANDLE       m_hAesAlg;
	BCRYPT_KEY_HANDLE       m_hKey;
	PBYTE                   m_pbKeyObject;
	PBYTE                   m_pbIV;

	//Handle for Hash function SHA-1
	BCRYPT_HASH_HANDLE		m_hHash;
	PBYTE					m_pbHashObject;
	BCRYPT_ALG_HANDLE		m_hHashAlg;

	//Init bcrypt.lib
	BOOL InitMicrosoftProviderAES();
	// for internal file
	BOOL CreateSymmetricKeyInternal(DWORD &cbKeyObject, DWORD &cbIV);
	// for normal file from dialog
	BOOL CreateSymmetricUserKeySHA1(PCWSTR pwszText, DWORD cbKeyObj);
	BOOL CryptData(BOOL bEncrypt, PUCHAR pbufFileToOpen, ULONG iBytesRead, ULONG cbIV, PBYTE pbufFileToSave, DWORD& iBufToSave);
	BOOL CryptLastByte(BOOL bEncrypt, PUCHAR pbufFileToOpen, ULONG iBytesRead, ULONG cbIV, PBYTE pbufFileToSave, DWORD& iBufToSave);
};

#endif // _FILE_CRYPTOGRAPHY_H_
