#include "vivid/common/MeshRender.h"

namespace te
{
    MeshRender::MeshRender()
        :ComData(ComponentType::MESH_RENDER),
        _mes_handle(0),
        _mat_handle(0)
    {
    }

    MeshRender::MeshRender(const String& mesh_res, const String& material_res)
        :ComData(ComponentType::MESH_RENDER)
    {
        loadMesh(mesh_res);
        loadMaterial(material_res);
    }

    bool MeshRender::loadMesh(const String& res)
    {
        _mes_handle = ResourceMapper::getInstance()->get<MeshManager>()->create(res);
        return bool(_mes_handle);
    }

    bool MeshRender::loadMaterial(const String& res)
    {
        _mat_handle = ResourceMapper::getInstance()->get<MaterialManager>()->create(res);
        return bool(_mat_handle);
    }

    MeshPtr MeshRender::getMesh()
    {
        return ResourceMapper::getInstance()->get<MeshManager>()->getMesh(_mes_handle);
    }

    MaterialPtr MeshRender::getMaterial()
    {
        return ResourceMapper::getInstance()->get<MaterialManager>()->getMaterial(_mat_handle);
    }

    
}

