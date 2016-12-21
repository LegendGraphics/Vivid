
#include "base/Ref.h"
#include "base/InterfaceSourceMacros.h"


namespace te
{
    Ref::Ref()
        :_reference_count(0)
    {
    }

    Ref::~Ref() {}

    TE_IMPLEMENT_INTERFACE(Ref)
    TE_INPLEMENT_START_QUERYINTERFACE(Ref)
    TE_IMPLEMENT_END_QUERYINTERFACE()
}

