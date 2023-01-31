// GDIPlusHelper.h: interface for the CGDIPlusHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GDIPLUSHELPER_H__BD5F6266_5686_43E2_B146_5EA1217A56FE__INCLUDED_)
#define AFX_GDIPLUSHELPER_H__BD5F6266_5686_43E2_B146_5EA1217A56FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace Gdiplus;

class CGifHandler : public Image
{
public:
	CGifHandler(IN const CString& strFileGif);
	CGifHandler(const WCHAR* filename, BOOL useEmbeddedColorManagement = FALSE);	
	~CGifHandler();
	void	Draw(CDC* pDC);
	CSize	GetSize();
	bool	IsAnimatedGIF() { return m_nFrameCount > 1; }
	void	SetPause(bool bPause);
	bool	IsPaused() { return m_bPause; }
	bool	InitAnimation(HWND hWnd, CRect rect);
	void	Destroy();
	void	SetRect(CRect rect);

protected:
	bool				TestForAnimatedGIF();
	void				Initialize();
	bool				DrawFrameGIF();

	IStream*			m_pStream;
	
	bool LoadFromBuffer(BYTE* pBuff, int nSize);
	bool GetResource(LPCTSTR lpName, LPCTSTR lpType, void* pResource, int& nBufSize);
	bool Load(const CString& strFileGif);

	void ThreadAnimation();

	static UINT WINAPI _ThreadAnimationProc(LPVOID pParam);

	HANDLE			m_hThread;
	HANDLE			m_hPause;
	HANDLE			m_hExitEvent;
	HINSTANCE		m_hInst;
	HWND			m_hWnd;
	UINT			m_nFrameCount;
	UINT			m_nFramePosition;
	bool			m_bIsInitialized;
	bool			m_bPause;
	PropertyItem*	m_pPropertyItem;
	CRect			m_rect;
};


#endif // !defined(AFX_GDIPLUSHELPER_H__BD5F6266_5686_43E2_B146_5EA1217A56FE__INCLUDED_)
