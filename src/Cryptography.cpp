/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Cryptography.h"
#include "AppUtil.h"
#include "RAIIUtils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CCryptographyIO::CCryptographyIO()
{
	m_iTotalByteRead = 0;
	m_iLenghtFileToOpen = 0;
	m_hAesAlg = NULL;
	m_hKey = NULL;
	m_pbKeyObject = NULL;
	m_pbIV = NULL;
	m_hHash = NULL;
	m_pbHashObject = NULL;
	m_hHashAlg = NULL;
}

CCryptographyIO::~CCryptographyIO()
{
	if (m_hAesAlg)
	{
		BCryptCloseAlgorithmProvider(m_hAesAlg, 0);
	}

	if (m_hKey)
	{
		BCryptDestroyKey(m_hKey);
	}

	if (m_pbKeyObject)
	{
		HeapFree(GetProcessHeap(), 0, m_pbKeyObject);
	}

	if (m_pbIV != NULL)
	{
		HeapFree(GetProcessHeap(), 0, m_pbIV);
	}

	if (m_hHash)
	{
		BCryptDestroyHash(m_hHash);
	}

	if (m_pbHashObject)
	{
		free(m_pbHashObject);
	}

	if (m_hHashAlg)
	{
		BCryptCloseAlgorithmProvider(m_hHashAlg, 0);
	}
}

BOOL CCryptographyIO::CryptFile(BOOL bEncrypt, BOOL bSHAMethod, CString strFileToOpen, CString strFileToCrypt, CString strKey)
{
	CFile		oFileToOpen, oFileToCrypt;
	NTSTATUS	ntStatus = STATUS_UNSUCCESSFUL;
	DWORD		cbKeyObject = 0;
	DWORD		cbIV = 0;
	BOOL		bFileToOpen = FALSE;
	BOOL		bFileToCrypt = FALSE;

	UINT		iBytesRead = 0;
	BYTE		pbufFileToOpen[BLOCK_BUFFER_SIZE];
	BYTE		pbufFileToSave[BLOCK_BUFFER_SIZE * 2];

	if (!InitMicrosoftProviderAES())
		return FALSE;

	if (!bSHAMethod)
	{
		if (!CreateSymmetricKeyInternal(cbKeyObject, cbIV))
			return FALSE;
	}
	else
	{
		if (!CreateSymmetricUserKeySHA1(strKey, cbKeyObject))
			return FALSE;
	}

	bFileToOpen = oFileToOpen.Open(strFileToOpen, CFile::modeRead | CFile::typeBinary);
	if (bFileToOpen == FALSE)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: opening the file '%s'"), strFileToOpen);
		return FALSE;
	}

	bFileToCrypt = oFileToCrypt.Open(strFileToCrypt, CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate);
	if (bFileToCrypt == FALSE)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: opening the file '%s'"), strFileToOpen);
		return FALSE;
	}
	SetLenghtFileToOpen(oFileToOpen.GetLength());

	DWORD iBufToSave = 0;

	while (!LastCryptBuffRead())
	{
		iBufToSave = 0;
		iBytesRead = oFileToOpen.Read(pbufFileToOpen, BLOCK_BUFFER_SIZE);
		SetTotalByteRead(iBytesRead);

		if (iBytesRead == 0)
		{
			CString sError;
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: reading the file '%s'"), strFileToOpen);
			return FALSE;
		}

		if (!LastCryptBuffRead())
		{
			if (!CryptData(bEncrypt, pbufFileToOpen, iBytesRead, cbIV, pbufFileToSave, iBufToSave))
				return FALSE;

			oFileToCrypt.Write(pbufFileToSave, iBytesRead);
		}
		else
		{
			if (!CryptLastByte(bEncrypt, pbufFileToOpen, iBytesRead, cbIV, pbufFileToSave, iBufToSave))
				return FALSE;
			oFileToCrypt.Write(pbufFileToSave, iBufToSave);
		}
	}
	oFileToOpen.Close();
	oFileToCrypt.Close();

	return TRUE;
}

BOOL CCryptographyIO::EnumProviders(CStringList *lstRegisteredProviders)
{
	NTSTATUS ntStatus = STATUS_UNSUCCESSFUL;
	DWORD cbBuffer = 0;
	PCRYPT_PROVIDERS pProviders = NULL;
	ntStatus = BCryptEnumRegisteredProviders(&cbBuffer, &pProviders);
	CString sProvider;
	if (ntStatus != STATUS_SUCCESS)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> BCryptEnumRegisteredProviders failed with error code 0x%08x"), ntStatus);
		return FALSE;
	}
	if (pProviders == NULL)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> BCryptEnumRegisteredProviders returned a NULL"));
		return FALSE;
	}
	else
	{
		for (DWORD i = 0; i < pProviders->cProviders; i++)
		{
			sProvider.Format(_T("%s\n"), pProviders->rgpszProviders[i]);
			lstRegisteredProviders->AddHead(sProvider);
		}
	}

	if (pProviders != NULL)
	{
		BCryptFreeBuffer(pProviders);
	}
	return TRUE;
}

BOOL CCryptographyIO::LastCryptBuffRead()
{
	return  (m_iLenghtFileToOpen <= m_iTotalByteRead);
}

void CCryptographyIO::SetLenghtFileToOpen(ULONGLONG iLenghtFileToOpen)
{
	m_iLenghtFileToOpen = iLenghtFileToOpen;
}

void CCryptographyIO::SetTotalByteRead(UINT iByteRead)
{
	m_iTotalByteRead += iByteRead;
}

BOOL CCryptographyIO::InitMicrosoftProviderAES()
{
	NTSTATUS ntStatus = STATUS_UNSUCCESSFUL;
	ntStatus = BCryptOpenAlgorithmProvider(&m_hAesAlg, BCRYPT_AES_ALGORITHM, NULL, 0); // use AES Symmetric algorithm 
	switch (ntStatus)
	{
		case STATUS_SUCCESS:
			return TRUE;
		case STATUS_INVALID_PARAMETER:
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: opening The algorithm handle. BCryptOpenAlgorithmProvider one or more parameters are not valid. "));
			break;
		case STATUS_NO_MEMORY:
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: opening The algorithm handle. BCryptOpenAlgorithmProvider a memory allocation failure occurred. "));
			break;
		default:
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: opening The algorithm handle. BCryptOpenAlgorithmProvider return with error 0x%08x"), ntStatus);
			break;
	}
	return FALSE;
}

BOOL CCryptographyIO::CryptData(BOOL bEncrypt, PUCHAR pbufFileToOpen, ULONG iBytesRead, ULONG cbIV, PBYTE pbufFileToSave, DWORD& iBufToSave)
{
	NTSTATUS ntStatus = STATUS_UNSUCCESSFUL;
	DWORD		cbCipherText = 0;
	if (bEncrypt)
		ntStatus = BCryptEncrypt(m_hKey, pbufFileToOpen, iBytesRead, NULL, m_pbIV, cbIV, pbufFileToSave, iBytesRead, &iBufToSave, 0);
	else
		ntStatus = BCryptDecrypt(m_hKey, pbufFileToOpen, iBytesRead, NULL, m_pbIV, cbIV, pbufFileToSave, iBytesRead, &iBufToSave, 0);

	switch (ntStatus)
	{
		case STATUS_SUCCESS:
			return TRUE;

		case STATUS_BUFFER_TOO_SMALL:
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: %s The size specified by the cbOutput parameter is not large enough to hold the ciphertext. Return with error 0x%08x"), bEncrypt ? _T("BCryptEncrypt") : _T("BCryptDecrypt"), ntStatus);
			break;
		case STATUS_INVALID_PARAMETER:
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: %s One or more parameters are not valid. Return with error 0x%08x"), bEncrypt ? "BCryptEncrypt" : "BCryptDecrypt", ntStatus);
			break;
		case STATUS_NOT_SUPPORTED:
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: %s The algorithm does not support encryption. Return with error 0x%08x"), bEncrypt ? "BCryptEncrypt" : "BCryptDecrypt", ntStatus);
			break;
		default:
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: %s return with error 0x%08x"), bEncrypt ? "BCryptEncrypt" : "BCryptDecrypt", ntStatus);
	}
	return FALSE;
}

BOOL CCryptographyIO::CryptLastByte(BOOL bEncrypt, PUCHAR pbufFileToOpen, ULONG iBytesRead, ULONG cbIV, PBYTE pbufFileToSave, DWORD& iBufToSave)
{
	NTSTATUS ntStatus = STATUS_UNSUCCESSFUL;
	DWORD		cbCipherText = 0;

	if (bEncrypt)
	{
		ntStatus = BCryptEncrypt(m_hKey, pbufFileToOpen, iBytesRead, NULL, m_pbIV, cbIV, NULL, 0, &cbCipherText, BCRYPT_BLOCK_PADDING);

		if (ntStatus != STATUS_SUCCESS)
		{
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: receiving the size required for the ciphertext. BCryptEncrypt return with error 0x%08x"), ntStatus);
			return FALSE;
		}
		ntStatus = BCryptEncrypt(m_hKey, pbufFileToOpen, iBytesRead, NULL, m_pbIV, cbIV, pbufFileToSave, cbCipherText, &cbCipherText, BCRYPT_BLOCK_PADDING);
		switch (ntStatus)
		{
		case STATUS_SUCCESS:
			iBufToSave = cbCipherText;
			return TRUE;
		default:
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: receiving wrong password. BCryptEncrypt return with error 0x%08x"), ntStatus);
			return FALSE;
		}
	}
	else
	{
		ntStatus = BCryptDecrypt(m_hKey, pbufFileToOpen, iBytesRead, NULL, m_pbIV, cbIV, NULL, 0, &cbCipherText, BCRYPT_BLOCK_PADDING);

		if (ntStatus != STATUS_SUCCESS)
		{
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: receiving the size required for the ciphertext. BCryptDecrypt return with error 0x%08x"), ntStatus);
			return FALSE;
		}
		ntStatus = BCryptDecrypt(m_hKey, pbufFileToOpen, iBytesRead, NULL, m_pbIV, cbIV, pbufFileToSave, cbCipherText, &cbCipherText, BCRYPT_BLOCK_PADDING);

		switch (ntStatus)
		{
		case STATUS_SUCCESS:
			iBufToSave = cbCipherText;
			return TRUE;
		default:
			LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: receiving wrong password. BCryptDecrypt return with error 0x%08x"), ntStatus);
			return FALSE;
		}
	}
	return FALSE;
}

BOOL CCryptographyIO::CreateSymmetricUserKeySHA1(PCWSTR pwszText, DWORD cbKeyObject)
{
	NTSTATUS ntStatus = STATUS_SUCCESS;
	BCRYPT_KEY_HANDLE	hKey = NULL;

	DWORD               cbHashObject, cbResult;
	BYTE                rgbHash[20];
	DWORD				cbData = 0;

	ntStatus = BCryptOpenAlgorithmProvider(&m_hHashAlg, BCRYPT_SHA1_ALGORITHM, NULL, 0);
	if (STATUS_SUCCESS != ntStatus)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: Open Algoritm for the key. BCryptOpenAlgorithmProvider failed with status: 0x%08x\n"), ntStatus);
		return FALSE;
	}

	ntStatus = BCryptGetProperty(m_hAesAlg, BCRYPT_OBJECT_LENGTH, (PBYTE)&cbKeyObject, sizeof(DWORD), &cbData, 0);
	if (ntStatus != STATUS_SUCCESS)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: calculating the size of KeyObject. BCryptGetProperty return with error 0x%08x"), ntStatus);
		return FALSE;
	}

	m_pbKeyObject = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbKeyObject);
	if (NULL == m_pbKeyObject)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: memory allocation key object on the heap failed"));
		return FALSE;
	}

	// Determine the size of the Hash object
	ntStatus = BCryptGetProperty(m_hHashAlg, BCRYPT_OBJECT_LENGTH, (PBYTE)&cbHashObject, sizeof(DWORD), &cbResult, 0);
	if (STATUS_SUCCESS != ntStatus)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: determining the size of the Hash object. BCryptGetProperty failed with status: 0x%08x"), ntStatus);
		return FALSE;
	}

	m_pbHashObject = (PBYTE)malloc(cbHashObject);

	if (NULL == m_pbHashObject)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: allocating Hash object memory"));
		return FALSE;
	}

	// Create the Hash object
	ntStatus = BCryptCreateHash(m_hHashAlg, &m_hHash, m_pbHashObject, cbHashObject, NULL, 0, 0);
	if (STATUS_SUCCESS != ntStatus)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: Creating the Hash object. BCryptCreateHash failed with status: 0x%08x"), ntStatus);
		return FALSE;
	}

	// Hash the data
	ntStatus = BCryptHashData(m_hHash, (PBYTE)pwszText, (ULONG)wcslen(pwszText), 0);
	if (STATUS_SUCCESS != ntStatus)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: hashing the data. BCryptHashData failed with status: 0x%08x"), ntStatus);
		return FALSE;
	}

	// Finish the hash
	ntStatus = BCryptFinishHash(m_hHash, rgbHash, sizeof(rgbHash), 0);
	if (STATUS_SUCCESS != ntStatus)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: finish the hash. BCryptFinishHash failed with status: 0x%08x"), ntStatus);
		return FALSE;
	}

	ntStatus = BCryptGenerateSymmetricKey(m_hAesAlg, &hKey, m_pbKeyObject, cbKeyObject, rgbHash, SYMM_KEY_SIZE_SECRET, 0);
	if (STATUS_SUCCESS != ntStatus)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: creating the key. BCryptGenerateSymmetricKey failed with status: 0x%08x"), ntStatus);
		hKey = NULL;
	}
	m_hKey = hKey;
	return TRUE;
}

BOOL CCryptographyIO::CreateSymmetricKeyInternal(DWORD &cbKeyObject, DWORD &cbIV)
{
	NTSTATUS	ntStatus = STATUS_UNSUCCESSFUL;
	DWORD		cbData = 0;

	cbKeyObject = 0;
	cbIV = 0;

	ntStatus = BCryptGetProperty(m_hAesAlg, BCRYPT_OBJECT_LENGTH, (PBYTE)&cbKeyObject, sizeof(DWORD), &cbData, 0);
	if (ntStatus != STATUS_SUCCESS)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: calculating the size of KeyObject. BCryptGetProperty return with error 0x%08x"), ntStatus);
		return FALSE;
	}

	m_pbKeyObject = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbKeyObject);
	if (NULL == m_pbKeyObject)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: memory allocation key object on the heap failed"));
		return FALSE;
	}

	ntStatus = BCryptGetProperty(m_hAesAlg, BCRYPT_BLOCK_LENGTH, (PBYTE)&cbIV, sizeof(DWORD), &cbData, 0);
	if (ntStatus != STATUS_SUCCESS)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: calculating the block length for the IV. BCryptGetProperty return with error 0x%08x"), ntStatus);
		return FALSE;
	}

	if (cbIV > sizeof(vectorIV))
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> Block length is longer than the provided IV length\n"));
		return FALSE;
	}

	m_pbIV = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbIV);
	if (NULL == m_pbIV)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: memory allocation buffer for the IV on the heap failed"));
		return FALSE;
	}

	memcpy(m_pbIV, vectorIV, cbIV);

	ntStatus = BCryptSetProperty(m_hAesAlg, BCRYPT_CHAINING_MODE, (PBYTE)BCRYPT_CHAIN_MODE_CBC, sizeof(BCRYPT_CHAIN_MODE_CBC), 0);
	if (ntStatus != STATUS_SUCCESS)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: setting the ChainingMode CBC. BCryptSetProperty return with error 0x%08x"), ntStatus);
		return FALSE;
	}

	// generate the key from supplied input key bytes
	ntStatus = BCryptGenerateSymmetricKey(m_hAesAlg, &m_hKey, m_pbKeyObject, cbKeyObject, (PBYTE)AES128bit_Key, sizeof(AES128bit_Key), 0);

	if (ntStatus != STATUS_SUCCESS)
	{
		LOG_OUTPUT_MESSAGE_FORMAT(_T("> [Error]: generate the key. BCryptGenerateSymmetricKey return with error 0x%08x"), ntStatus);
		return FALSE;
	}

	return TRUE;
}