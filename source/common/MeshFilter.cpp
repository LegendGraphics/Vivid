#include "common/MeshFilter.h"

namespace te
{
    MeshFilter::MeshFilter()
        :Component(ComponentType::MESH_FILTER),
        _mes_handle(0)
    {
    }

    MeshFilter::MeshFilter(const String& res)
        :Component(ComponentType::MESH_FILTER)
    {
        load(res);
    }

    bool MeshFilter::load(const String& res)
    {
        _mes_handle = ResourceMapper::getInstance()->get<MeshManager>()->create(res);
        return bool(_mes_handle);
    }

    MeshPtr MeshFilter::getMesh()
    {
        return ResourceMapper::getInstance()->get<MeshManager>()->getMesh(_mes_handle);
    }
}

