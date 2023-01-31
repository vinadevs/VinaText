/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

/*
Note:  Additional file formats might be supported if you install new codecs in Windows.
For more information, see Codecs : frequently asked questions.

Windows Media formats(.asf, .wma, .wmv, .wm)

Windows Media Metafiles(.asx, .wax, .wvx, .wmx, wpl)

Microsoft Digital Video Recording(.dvr - ms)

Windows Media Download Package(.wmd)

Audio Visual Interleave(.avi)

Moving Pictures Experts Group(.mpg, .mpeg, .m1v, .mp2, .mp3, .mpa, .mpe, .m3u)

Musical Instrument Digital Interface(.mid, .midi, .rmi)

Audio Interchange File Format(.aif, .aifc, .aiff)

Sun Microsystems and NeXT(.au, .snd)

Audio for Windows(.wav)

CD Audio Track(.cda)

Indeo Video Technology(.ivf)

Windows Media Player Skins(.wmz, .wms)

QuickTime Movie file(.mov)

MP4 Audio file(.m4a)

MP4 Video file(.mp4, .m4v, .mp4v, .3g2, .3gp2, .3gp, .3gpp)

Windows audio file(.aac, .adt, .adts)

MPEG - 2 TS Video file(.m2ts)

Free Lossless Audio Codec(.flac)
*/

#pragma once

#include "Resource.h"
#include <oledlg.h>
#include "wmp.h"
#include "CWMPEventDispatch.h"

/////////////////////////////////////////////////////////////////////////////
// CWMPHost

class CWMPHost : public CWindowImpl<CWMPHost, CWindow, CWinTraits<WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE> >
{
public:
    DECLARE_WND_CLASS_EX(NULL, 0, 0)

    BEGIN_MSG_MAP(CWMPHost)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnErase)      
    END_MSG_MAP()

	// control interfaces
	LRESULT IsPlaying();
	LRESULT Play();
	LRESULT Pause();
	LRESULT Stop();
	LRESULT VolumeUp();
	LRESULT VolumeDown();
	LRESULT NextFrame();
	LRESULT PrevFrame();
	LRESULT OpenMediaFile(BSTR bstrFilePath); // auto play after open file

    LRESULT OnDestroy(UINT /* uMsg */, WPARAM /* wParam */, LPARAM /* lParam */, BOOL& bHandled );
    LRESULT OnCreate(UINT /* uMsg */, WPARAM /* wParam */, LPARAM /* lParam */, BOOL& /* bHandled */);
    LRESULT OnErase(UINT /* uMsg */, WPARAM /* wParam */, LPARAM /* lParam */, BOOL& /* bHandled */);
    LRESULT OnSize(UINT /* uMsg */, WPARAM /* wParam */, LPARAM /* lParam */, BOOL& /* bHandled */);

    CAxWindow                   m_wndView; // Need to ddd ATL class for MFC Project
    CComPtr<IWMPPlayer>         m_spWMPPlayer;
	CComPtr<IWMPControls>       m_spControls;
    CComPtr<IConnectionPoint>   m_spConnectionPoint;
	CComPtr<IWMPSettings>		m_spSettings;
    DWORD                       m_dwAdviseCookie;
};
