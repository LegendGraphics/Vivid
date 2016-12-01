#ifndef COMMON_REF_H
#define COMMON_REF_H

#include "InterfaceHeaderMacros.h"

/// Ref` is a base class for an object whose lifetime is managed by a ref.

/// See \ref topic_refs for details. This class is often used in 
/// conjunction with `RefPtr`. When the ref count on the 
/// object reaches under zero, it will be deleted.

class Ref
{
    // We don't want those guys....
    Ref(const Ref& src);
    Ref& operator=(const Ref& rhs);

protected:
    Ref();
    virtual ~Ref() = 0;

public:
    inline void retain()
    {
        TE_ASSERT(_reference_count >= 0, "reference count should not be less than zero");
        _reference_count++;
    };
    inline void release()
    {
        TE_ASSERT(_reference_count > 0, "reference count should be greater than zero");
        _reference_count--;
    };
	
    unsigned int getReferenceCount() { return _reference_count; };

private:
	unsigned int _reference_count;

    TE_DECLARE_INTERFACE()
};

#endif // COMMON_REF_H