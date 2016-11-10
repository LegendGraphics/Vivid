
#include "base/ref.h"
#include "base/macros.h"

Ref::Ref()
:_reference_count(0)
{
}

Ref::~Ref(){}

void Ref::retain()
{
    TE_ASSERT(_reference_count >= 0, "reference count should not be less than zero");
    _reference_count ++;
}

void Ref::release()
{
    TE_ASSERT(_reference_count > 0, "reference count should be greater than zero");
    _reference_count --;
}

unsigned int Ref::getReferenceCount()
{   
    return _reference_count;
}
