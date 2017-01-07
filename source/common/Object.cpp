#include "common/object.h"

#include "base/InterfaceSourceMacros.h"


namespace te
{
    Object::Object()
    {
        _id = ObjectId ++;
    }

    TE_IMPLEMENT_INTERFACE(te::Object)
    TE_INPLEMENT_START_QUERYINTERFACE(Object)
    TE_IMPLEMENT_BASE_QUERYINTERFACE(Ref)
    TE_IMPLEMENT_END_QUERYINTERFACE()
}

