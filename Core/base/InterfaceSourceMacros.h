#progma once

// These macros are intended to implement the functions needed for interface handling in the
// source file of a class.


// This is what the client writes to do it.

/*
    TE_IMPLEMENT_INTERFACE(te::MyClass)
    TE_IMPLEMENT_START_QUERYINTERFACE(MyClass)
    TE_IMPLEMENT_BASE_QUERYINTERFACE(MyBase)
    TE_IMPLEMENT_END_QUERYINTERFACE()
*/
// TE_IMPLEMENT_INTERFACE takes class name.
// TE_IMPLEMENT_BASE_QUERYINTERFACE can be called multiple times, one for each base class.

#include "UniqueString.h"

#define TE_IMPLEMENT_INTERFACE(MyClass)                                         \
const te::UniqueString* MyClass::interfaceId()                                                      \
{                                                                                                   \
    return _interfaceId();                                                                          \
}                                                                                                   \
                                                                                                    \
const te::UniqueString*                                                                             \
MyClass::_interfaceId()                                                                             \
{                                                                                                   \
    static const te::UniqueString* p_id = te::UniqueString::find(#MyClass);                         \
    return p_id;                                                                                    \
}                                                                                                   \
                                                                                                    \
const te::UniqueString*                                                                             \
MyClass::getInterfaceId() const                                                                     \
{                                                                                                   \
    return MyClass::interfaceId();                                                                  \
}

#define TE_INPLEMENT_START_QUERYINTERFACE(MyClass)                                                  \
void* MyClass::queryInterface(const te::UniqueString* id)                                           \
{                                                                                                   \
    if (id == MyClass::interfaceId())                                                               \
    {                                                                                               \
        return static_cast<MyClass*>(this);                                                         \
    }

#define TE_IMPLEMENT_BASE_QUERYINTERFACE(MyBase)                                                    \
    else if (void* pInterface = MyBase::queryInterface(id))                                         \
    {                                                                                               \
        return pInterface;                                                                          \
    }

#define TE_IMPLEMENT_END_QUERYINTERFACE()                                                           \
    return NULL;                                                                                    \
}