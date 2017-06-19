
#include "vivid/base/Ref.h"

namespace vivid
{
    Ref::Ref()
        :_reference_count(0)
    {
    }

    Ref::~Ref() {}
}

