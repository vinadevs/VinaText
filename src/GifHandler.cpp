// GDIPlusHelper.cpp: implementation of the CGDIPlusHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GifHandler.h"
#include <process.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	CGifHandler::CGifHandler
// 
// DESCRIPTION:	Constructor for constructing images from a resource 
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
CGifHandler::CGifHandler(const CString& strFileGif)
{
	Initialize();

	if (Load(strFileGif))
	{
	   nativeImage = NULL;
	   
	   lastResult = DllExports::GdipLoadImageFromStreamICM(m_pStream, &nativeImage);
	  
	   TestForAnimatedGIF();
    }
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	CGifHandler::CGifHandler
// 
// DESCRIPTION:	Constructor for constructing images from a file
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
CGifHandler::CGifHandler(const WCHAR* filename, BOOL useEmbeddedColorManagement) : Image(filename, useEmbeddedColorManagement)
{
	Initialize();

	m_bIsInitialized = true;

	TestForAnimatedGIF();
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	CGifHandler::~CGifHandler
// 
// DESCRIPTION:	Free up fresources
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
CGifHandler::~CGifHandler()
{
	Destroy();
}

void CGifHandler::SetRect(CRect rect)
{
	m_rect = rect;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	InitAnimation
// 
// DESCRIPTION:	Prepare animated GIF
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
bool CGifHandler::InitAnimation(HWND hWnd, CRect rect)
{
	m_hWnd = hWnd;
	m_rect = rect;

	if (!m_bIsInitialized)
	{
		TRACE(_T("GIF not initialized\n"));
		return false;
	};

	if (IsAnimatedGIF())
	{
		if (m_hThread == NULL)
		{
		
			unsigned int nTID = 0;

			m_hThread = (HANDLE) _beginthreadex( NULL, 0, _ThreadAnimationProc, this, CREATE_SUSPENDED,&nTID);
			
			if (!m_hThread)
			{
				TRACE(_T("Couldn't start a GIF animation thread\n"));
				return true;
			} 
			else 
				ResumeThread(m_hThread);
		}
	} 

	return false;	
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	LoadFromBuffer
// 
// DESCRIPTION:	Helper function to copy phyical memory from buffer a IStream
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
bool CGifHandler::LoadFromBuffer(BYTE* pBuff, int nSize)
{
	bool bResult = false;

	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, nSize);
	if (hGlobal)
	{
		void* pData = GlobalLock(hGlobal);
		if (pData)
			memcpy(pData, pBuff, nSize);
		
		GlobalUnlock(hGlobal);

		if (CreateStreamOnHGlobal(hGlobal, TRUE, &m_pStream) == S_OK)
			bResult = true;

	}


	return bResult;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	GetResource
// 
// DESCRIPTION:	Helper function to lock down resource
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
bool CGifHandler::GetResource(LPCTSTR lpName, LPCTSTR lpType, void* pResource, int& nBufSize)
{ 
	HRSRC		hResInfo;
	HANDLE		hRes;
	LPSTR		lpRes	= NULL; 
	int			nLen	= 0;
	bool		bResult	= FALSE;

	// Find the resource

	hResInfo = FindResource(m_hInst , lpName, lpType);
	if (hResInfo == NULL) 
	{
		DWORD dwErr = GetLastError();
		return false;
	}

	// Load the resource
	hRes = LoadResource(m_hInst , hResInfo);

	if (hRes == NULL) 
		return false;

	// Lock the resource
	lpRes = (char*)LockResource(hRes);

	if (lpRes != NULL)
	{ 
		if (pResource == NULL)
		{
			nBufSize = SizeofResource(m_hInst , hResInfo);
			bResult = true;
		}
		else
		{
			if (nBufSize >= (int)SizeofResource(m_hInst , hResInfo))
			{
				memcpy(pResource, lpRes, nBufSize);
				bResult = true;
			}
		} 

		UnlockResource(hRes);  
	}

	// Free the resource
	FreeResource(hRes);

	return bResult;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	Load
// 
// DESCRIPTION:	Helper function to load resource from memory
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
bool CGifHandler::Load(const CString& strFileGif)
{
	bool bResult = false;
	// Read from gif file into buffer:
	HANDLE hFile = CreateFile(strFileGif, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!hFile) return false;

	DWORD bufsize = GetFileSize(hFile, NULL);
	if (bufsize > 0)
	{
		std::unique_ptr<BYTE[]> buffer = std::make_unique<BYTE[]>(bufsize);
		DWORD temp = 0;
		ReadFile(hFile, buffer.get(), bufsize, &temp, 0);
		if (LoadFromBuffer(buffer.get(), bufsize))
		{
			bResult = true;
		}
	}
	CloseHandle(hFile);
	m_bIsInitialized = bResult;
	return bResult;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	GetSize
// 
// DESCRIPTION:	Returns Width and Height object
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
CSize CGifHandler::GetSize()
{
	return CSize(GetWidth(), GetHeight());
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	TestForAnimatedGIF
// 
// DESCRIPTION:	Check GIF/Image for avialability of animation
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
bool CGifHandler::TestForAnimatedGIF()
{
   UINT count = 0;
   count = GetFrameDimensionsCount();
   std::unique_ptr<GUID[]> pDimensionIDs = std::make_unique<GUID[]>(count);
   // Get the list of frame dimensions from the Image object.
   GetFrameDimensionsList(pDimensionIDs.get(), count);

   // Get the number of frames in the first dimension.
   m_nFrameCount = GetFrameCount(&pDimensionIDs[0]);

	// Assume that the image has a property item of type PropertyItemEquipMake.
	// Get the size of that property item.
   int nSize = GetPropertyItemSize(PropertyTagFrameDelay);

   // Allocate a buffer to receive the property item.
   m_pPropertyItem = (PropertyItem*) malloc(nSize);

   GetPropertyItem(PropertyTagFrameDelay, nSize, m_pPropertyItem);

   return m_nFrameCount > 1;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	CGifHandler::Initialize
// 
// DESCRIPTION:	Common function called from Constructors
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CGifHandler::Initialize()
{
	m_pStream = NULL;
	m_nFramePosition = 0;
	m_nFrameCount = 0;
	m_pStream = NULL;
	lastResult = InvalidParameter;
	m_hThread = NULL;
	m_bIsInitialized = false;
	m_pPropertyItem = NULL;
	
#ifdef INDIGO_CTRL_PROJECT
	m_hInst = _Module.GetResourceInstance();
#else
	m_hInst = AfxGetResourceHandle();
#endif


	m_bPause = false;

	m_hExitEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

	m_hPause = CreateEvent(NULL,TRUE,TRUE,NULL);

}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	CGifHandler::_ThreadAnimationProc
// 
// DESCRIPTION:	Thread to draw animated gifs
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
UINT WINAPI CGifHandler::_ThreadAnimationProc(LPVOID pParam)
{
	ASSERT(pParam);
	CGifHandler *pImage = reinterpret_cast<CGifHandler *> (pParam);
	if (pImage)
	{
		pImage->ThreadAnimation();
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	CGifHandler::ThreadAnimation
// 
// DESCRIPTION:	Helper function
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CGifHandler::ThreadAnimation()
{
	m_nFramePosition = 0;

	bool bExit = false;
	while (bExit == false)
	{
		bExit = DrawFrameGIF();
	}
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	CGifHandler::DrawFrameGIF
// 
// DESCRIPTION:	
// 
// RETURNS:	
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
bool CGifHandler::DrawFrameGIF()
{
	::WaitForSingleObject(m_hPause, INFINITE);

	GUID   pageGuid = FrameDimensionTime;

	HDC hDC = GetDC(m_hWnd);
	if (hDC)
	{
		Graphics graphics(hDC);
		graphics.DrawImage(this, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
		ReleaseDC(m_hWnd, hDC);
	}

	SelectActiveFrame(&pageGuid, m_nFramePosition++);		
	
	if (m_nFramePosition == m_nFrameCount)
		m_nFramePosition = 0;


	long lPause = ((long*) m_pPropertyItem->value)[m_nFramePosition] * 10;

	DWORD dwErr = WaitForSingleObject(m_hExitEvent, lPause);

	return dwErr == WAIT_OBJECT_0;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	CGifHandler::SetPause
// 
// DESCRIPTION:	Toggle Pause state of GIF
// 
// RETURNS:		
// 
// NOTES:		
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       29012002	1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CGifHandler::SetPause(bool bPause)
{
	if (!IsAnimatedGIF())
		return;

	if (bPause && !m_bPause)
	{
		::ResetEvent(m_hPause);
	}
	else
	{

		if (m_bPause && !bPause)
		{
			::SetEvent(m_hPause);
		}
	}

	m_bPause = bPause;
}

void CGifHandler::Destroy()
{
	if (m_hThread)
	{
		// If pause un pause
		SetPause(false);

		SetEvent(m_hExitEvent);
		WaitForSingleObject(m_hThread, INFINITE);
	}

	CloseHandle(m_hThread);
	CloseHandle(m_hExitEvent);
	CloseHandle(m_hPause);

	free(m_pPropertyItem);

	m_pPropertyItem = NULL;
	m_hThread = NULL;
	m_hExitEvent = NULL;
	m_hPause = NULL;

	if (m_pStream)
	{
		m_pStream->Release();
	}
}