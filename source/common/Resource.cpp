#include "common/Resource.h"

namespace te
{
    Resource::Resource(int type, int flags)
        :_type(type),
        _flags(flags)
    {}

    Resource::Resource(const Resource& resource, const CopyOperator& copyop)
    {}

    Resource::~Resource(){}

    void Resource::release()
    {}

    bool Resource::load(const char *data, int size)
    {
        return true;
    }

    void Resource::unload()
    {}
}