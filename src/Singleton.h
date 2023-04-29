/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#include "stdafx.h"

#define SINGLETON_IMPLEMENT(classname) \
public: \
    classname(classname const&) = delete; \
    classname& operator=(classname const&) = delete; \
    static classname& GetInstance() { \
        static classname instance; \
        return instance; \
    } \
private: \
    classname() = default; \
    ~classname() = default;

#define SINGLETON_CUSTOM_CON_DESTRUCTOR(classname) \
public: \
    classname(classname const&) = delete; \
    classname& operator=(classname const&) = delete; \
    static classname& GetInstance() { \
        static classname instance; \
        return instance; \
    } 

#define DISABLE_COPY_AND_ASSIGNMENT(TypeName)  \
    TypeName(const TypeName&) = delete;  \
    void operator=(const TypeName&) = delete;

#define DISABLE_MOVE_SEMANTICS(TypeName)  \
    TypeName(const TypeName&&) = delete;  \
    void operator=(const TypeName&&) = delete;

///////////////////////////////////////////////////

template <typename T>
class CSingletonHelper
{
    friend T;
public:
    static T& GetInstance();
private:
    CSingletonHelper() = default;
    ~CSingletonHelper() = default;
    CSingletonHelper(const CSingletonHelper&) = delete;
    CSingletonHelper& operator=(const CSingletonHelper&) = delete;
    CSingletonHelper(CSingletonHelper&&) = delete;
    CSingletonHelper& operator=(CSingletonHelper&&) = delete;
};
template <typename T>
T& CSingletonHelper<T>::GetInstance()
{
    static T inst;
    return inst;
}