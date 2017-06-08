
#include "base/Ref.h"

namespace te
{
    Ref::Ref()
        :_reference_count(0)
    {
    }

    Ref::~Ref() {}
}

