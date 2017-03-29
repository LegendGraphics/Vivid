#ifndef COMMON_REF_H
#define COMMON_REF_H

#include "base/Assert.h"
/// Ref` is a base class for an object whose lifetime is managed by a ref.

/// See \ref topic_refs for details. This class is often used in 
/// conjunction with `RefPtr`. When the ref count on the 
/// object reaches under zero, it will be deleted.


namespace te
{
    // cycle reference problem exists...
    class Ref
    {
    protected:
        Ref();
        virtual ~Ref();

        Ref(const Ref& src) = delete;
        Ref& operator=(const Ref& rhs) = delete;

    public:
        inline void retain()
        {
            mASSERT(_reference_count >= 0, "reference count should not be less than zero");
            _reference_count++;
        };
        inline void release()
        {
            mASSERT(_reference_count > 0, "reference count should be greater than zero");
            _reference_count--;
        };

        unsigned int getReferenceCount() { return _reference_count; };

    private:
        unsigned int _reference_count;
    };
}

#endif // COMMON_REF_H