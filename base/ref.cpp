
#include "base/ref.h"
#include "base/macros.h"

Ref::Ref()
:_reference_count(0)
{
}

Ref::~Ref(){}