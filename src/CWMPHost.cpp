/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "CWMPHost.h"

/////////////////////////////////////////////////////////////////////////////
// CWMPHost

#ifndef ACTIVEX_WMP_CLSID
#define ACTIVEX_WMP_CLSID L"{6BF52A52-394A-11d3-B153-00C04F79FAA6}"
#endif

LRESULT CWMPHost::IsPlaying()
{
	HRESULT hr;
	if (m_spWMPPlayer)
	{
		WMPPlayState pwmpps;
		hr = m_spWMPPlayer->get_playState(&pwmpps);
		if (FAILED(hr)) return 0;
		if (pwmpps == WMPPlayState::wmppsPlaying)
		{
			return 1;
		}
	}
	return 0;
}

LRESULT CWMPHost::Play()
{
	HRESULT hr;
	if (m_spControls)
	{
		hr = m_spControls->play();
		if (FAILED(hr)) return 0;
		return 1;
	}
	return 0;
}

LRESULT CWMPHost::Pause()
{
	HRESULT hr;
	if (m_spControls)
	{
		hr = m_spControls->pause();
		if (FAILED(hr)) return 0;
		return 1;
	}
	return 0;
}

LRESULT CWMPHost::Stop()
{
	HRESULT hr;
	if (m_spControls)
	{
		hr = m_spControls->stop();
		if (FAILED(hr)) return 0;
		return 1;
	}
	return 0;
}

LRESULT CWMPHost::VolumeUp()
{
	HRESULT hr;
	if (m_spSettings)
	{
		long lVolume = 0;
		hr = m_spSettings->get_volume(&lVolume);
		if (FAILED(hr)) return 0;
		hr = m_spSettings->put_volume(lVolume + 10);
		if (FAILED(hr)) return 0;
		return 1;
	}
	return 0;
}

LRESULT CWMPHost::VolumeDown()
{
	HRESULT hr;
	if (m_spControls)
	{
		long lVolume = 0;
		hr = m_spSettings->get_volume(&lVolume);
		if (FAILED(hr)) return 0;
		hr = m_spSettings->put_volume(lVolume - 10);
		if (FAILED(hr)) return 0;
		return 1;
	}
	return 0;
}

LRESULT CWMPHost::NextFrame()
{
	HRESULT hr;
	if (m_spControls)
	{
		hr = m_spControls->fastForward();
		if (FAILED(hr)) return 0;
		return 1;
	}
	return 0;
}

LRESULT CWMPHost::PrevFrame()
{
	HRESULT hr;
	if (m_spControls)
	{
		hr = m_spControls->fastReverse();
		if (FAILED(hr)) return 0;
		return 1;
	}
	return 0;
}

LRESULT CWMPHost::OpenMediaFile(BSTR bstrFilePath)
{
	HRESULT hr;
	if (m_spWMPPlayer)
	{
		hr = m_spWMPPlayer->put_URL(bstrFilePath);
		if (FAILED(hr)) return 0;
		return 1;
	}
	return 0;
}

LRESULT CWMPHost::OnCreate(UINT /* uMsg */, WPARAM /* wParam */, LPARAM /* lParam */, BOOL& /* bHandled */)
{
    AtlAxWinInit();
    CComPtr<IAxWinHostWindow>           spHost;
    CComPtr<IConnectionPointContainer>  spConnectionContainer;
    CComWMPEventDispatch                *pEventListener = NULL;
    CComPtr<IWMPEvents>                 spEventListener;
    HRESULT                             hr;
    RECT                                rcClient;

    m_dwAdviseCookie = 0;

    // create window
    GetClientRect(&rcClient);
    m_wndView.Create(m_hWnd, rcClient, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);
	if (NULL == m_wndView.m_hWnd)
		return -1;
    
    // load OCX in window
    hr = m_wndView.QueryHost(&spHost);
    if (FAILED(hr))
		return -1;

    hr = spHost->CreateControl(CComBSTR(ACTIVEX_WMP_CLSID), m_wndView, 0);
    if (FAILED(hr))
		return -1;

    hr = m_wndView.QueryControl(&m_spWMPPlayer);
    if (FAILED(hr))
		return -1;

    // start listening to events

    hr = CComWMPEventDispatch::CreateInstance(&pEventListener);
    spEventListener = pEventListener;
    if (FAILED(hr))
		return -1;

    hr = m_spWMPPlayer->QueryInterface(&spConnectionContainer);
    if (FAILED(hr))
		return -1;

    // See if OCX supports the IWMPEvents interface
    hr = spConnectionContainer->FindConnectionPoint(__uuidof(IWMPEvents), &m_spConnectionPoint);
    if (FAILED(hr))
    {
        // If not, try the _WMPOCXEvents interface, which will use IDispatch
        hr = spConnectionContainer->FindConnectionPoint(__uuidof(_WMPOCXEvents), &m_spConnectionPoint);
        if (FAILED(hr))
			return -1;
    }

    hr = m_spConnectionPoint->Advise(spEventListener, &m_dwAdviseCookie);
    if (FAILED(hr))
		return -1;

	hr = m_spWMPPlayer->QueryInterface(__uuidof(IWMPControls), (void**)&m_spControls); // returned hr = S_OK
	if (FAILED(hr))
		return -1;

	hr = m_spWMPPlayer->QueryInterface(__uuidof(IWMPSettings), (void**)&m_spSettings); // returned hr = S_OK
	if (FAILED(hr))
		return -1;

    return 0;
}

LRESULT CWMPHost::OnDestroy(UINT /* uMsg */, WPARAM /* wParam */, LPARAM /* lParam */, BOOL& bHandled )
{
    // stop listening to events

    if (m_spConnectionPoint)
    {
        if (0 != m_dwAdviseCookie)
            m_spConnectionPoint->Unadvise(m_dwAdviseCookie);
        m_spConnectionPoint.Release();
    }

    // close the OCX

    if (m_spWMPPlayer)
    {
        m_spWMPPlayer->close();
        m_spWMPPlayer.Release();
    }

    bHandled = FALSE;
    return 0;
}

LRESULT CWMPHost::OnErase(UINT /* uMsg */, WPARAM /* wParam */, LPARAM /* lParam */, BOOL& /* bHandled */)
{
    return 1;
}

LRESULT CWMPHost::OnSize(UINT /* uMsg */, WPARAM /* wParam */, LPARAM /* lParam */, BOOL& /* bHandled */)
{
    RECT rcClient;
    GetClientRect(&rcClient);
    m_wndView.MoveWindow(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);
    return 0;
}