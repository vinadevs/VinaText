﻿// sktoolslib - common files for SK tools

// Copyright (C) 2012, 2015, 2017, 2020-2021 - Stefan Kueng

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
#pragma once
#include "stdafx.h"
#include <Uxtheme.h>

template <typename Type>
struct CDefaultHandleNull
{
    static constexpr Type DefaultHandle()
    {
        return nullptr;
    }
};

struct CDefaultHandleInvalid
{
    static HANDLE DefaultHandle()
    {
        return INVALID_HANDLE_VALUE;
    }
};

/**
 * \ingroup Utils
 * Helper classes for handles.
 */
template <typename HandleType,
          template <class> class CloseFunction,
          typename NullType = CDefaultHandleNull<HandleType>>
class CSmartHandle
{
public:
    CSmartHandle()
        : m_handle(NullType::DefaultHandle())
    {
    }

    // disable any copies of handles.
    // Handles must be copied only using DuplicateHandle(). But we leave
    // that to an explicit call.
    // See compiler tests at the bottom
    CSmartHandle(const HandleType& h)   = delete;
    CSmartHandle(const CSmartHandle& h) = delete;
    HandleType&   operator=(const HandleType& h) = delete;
    CSmartHandle& operator=(const CSmartHandle& h) = delete;

    CSmartHandle(HandleType&& h)
    {
        m_handle = h;
    }

    CSmartHandle(CSmartHandle&& h) noexcept
    {
        m_handle = h.Detach();
    }

    CSmartHandle& operator=(CSmartHandle&& h) noexcept
    {
        *this = h.Detach();
        return *this;
    }

    HandleType& operator=(HandleType&& h)
    {
        if (m_handle != h)
        {
            CleanUp();
            m_handle = h;
        }

        return m_handle;
    }

    bool CloseHandle()
    {
        return CleanUp();
    }

    HandleType Detach()
    {
        HandleType p = m_handle;
        m_handle     = NullType::DefaultHandle();

        return p;
    }

    operator HandleType() const
    {
        return m_handle;
    }

    HandleType* GetPointer()
    {
        return &m_handle;
    }

    operator bool() const
    {
        return IsValid();
    }

    bool IsValid() const
    {
        return m_handle != NullType::DefaultHandle();
    }

    HandleType Duplicate() const
    {
        HandleType hDup = NullType::DefaultHandle();
        if (DuplicateHandle(GetCurrentProcess(),
                            static_cast<HANDLE>(m_handle),
                            GetCurrentProcess(),
                            &hDup,
                            0,
                            FALSE,
                            DUPLICATE_SAME_ACCESS))
        {
            return hDup;
        }
        return NullType::DefaultHandle();
    }

    ~CSmartHandle()
    {
        CleanUp();
    }

protected:
    bool CleanUp()
    {
        if (m_handle != NullType::DefaultHandle())
        {
            const bool b = CloseFunction<HandleType>::Close(m_handle);
            m_handle     = NullType::DefaultHandle();
            return b;
        }
        return false;
    }

    HandleType m_handle;
};

template <typename T>
struct CCloseHandle
{
    static bool Close(T handle)
    {
        return !!::CloseHandle(handle);
    }
};

template <typename T>
struct CCloseRegKey
{
    static bool Close(T handle)
    {
        return RegCloseKey(handle) == ERROR_SUCCESS;
    }
};

template <typename T>
struct CCloseLibrary
{
    static bool Close(T handle)
    {
        return !!::FreeLibrary(handle);
    }
};

template <typename T>
struct CCloseViewOfFile
{
    static bool Close(T handle)
    {
        return !!::UnmapViewOfFile(handle);
    }
};

template <typename T>
struct CCloseFindFile
{
    static bool Close(T handle)
    {
        return !!::FindClose(handle);
    }
};

template <typename T>
struct CCloseThemeData
{
    static bool Close(T hTheme)
    {
        return SUCCEEDED(::CloseThemeData(hTheme));
    }
};

template <typename T>
struct CCloseIcon
{
    static bool Close(T handle)
    {
        return !!DestroyIcon(handle);
    }
};

// Client code (definitions of standard Windows handles).
using CAutoGeneralHandle = CSmartHandle<HANDLE, CCloseHandle>;
using CAutoRegKey = CSmartHandle<HKEY, CCloseRegKey>;
using CAutoViewOfFile = CSmartHandle<PVOID, CCloseViewOfFile>;
using CAutoLibrary = CSmartHandle<HMODULE, CCloseLibrary>;
using CAutoFile = CSmartHandle<HANDLE, CCloseHandle, CDefaultHandleInvalid>;
using CAutoFindFile = CSmartHandle<HANDLE, CCloseFindFile, CDefaultHandleInvalid>;
using CAutoThemeData = CSmartHandle<HTHEME, CCloseThemeData>;
using CAutoIcon = CSmartHandle<HICON, CCloseIcon>;