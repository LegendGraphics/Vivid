#progma once

#include "Assert.h"

// These macros are intended to declare functions for interface handling in 
// header file of a class.

// PS. This is only a RTTI system, we might need a full reflection in the
// future which exploits new features of c++0x. Wait for further investigation.

// Somethings might be helpful.
// https://github.com/RAttab/reflect
// https://www.codeproject.com/tips/1023227/a-general-cplusplus-reflection-engine-based-on-c

// The code we want to generate.

/*  class MyClass : public MyBase
    {
        ... everything else in MyClass...

    public:
        static const te::UniqueString* interfaceId();               // return the address of a string that uniquely identifies the class
        virtual const te::UniqueString* getInterfaceId() const;     // virtual function that calls the above.
        virtual void* queryInterface(const te::UniqueString* id) const; // Derived classes must implement and forward to all the base classes.
    private:
        static const te::UniqueString* _interfaceId();              // interface id.
    }; */

// This is how the client writes it.

/*  class MyClass
    {
        ... everything else in MyClass...
        TE_DECLARE_INTERFACE()
    }; */

namespace te {
    class UniqueString;
}


#define TE_DECLARE_INTERFACE()                                      \
    public:                                                         \
        static const te::UniqueString* interfaceId();               \
        virtual const te::UniqueString* getInterfaceId() const;     \
        virtual void* queryInterface(const te::UniqueString* id);   \
    private:                                                        \
        static const te::UniqueString* _interfaceId();

#define QUERY_CAST(CastTo, obj) (obj != NULL ? static_cast<CastTo*>(obj->queryInterface(CastTo::interfaceId())) : NULL)

namespace te
{
    template<class T, class CLS>
    inline T* QueryInterface(const CLS* pCLS)
    {
        if (pCLS)
        {
            const UniqueString* iid = T::interfaceId();
            if (void* pIf = pCLS->queryInterface(iid))
                return static_cast<T*>(pIf);
        }
        return NULL;
    }
}