#include "common/MeshFilter.h"

namespace te
{
    MeshFilter::MeshFilter()
        :_mes_handle(0)
    {}

    bool MeshFilter::load(const String& res)
    {
        _mes_handle = ResourceMapper::getInstance()->get<MeshManager>()->create(res);
        return _mes_handle;
    }

    Mesh* MeshFilter::getMesh()
    {
        return ResourceMapper::getInstance()->get<MeshManager>()->getMesh(_mes_handle);
    }
}

