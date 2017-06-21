#include "vivid/common/MeshRender.h"
#include "vivid/io/ResourceLoader.h"
#include "vivid/io/Logger.h"

namespace vivid
{
    MeshRender* MeshRender::create(const String& res)
    {
        MeshRender* mr = new MeshRender;
        ResourceLoader::load(mr, res);
        return mr;
    }


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

    bool MeshRender::load(const String& mesh_res, const String& material_res)
    {
        bool flag = true;
        if (!loadMesh(mesh_res))
        {
            cLog << "No such mesh resource";
            flag = false;
        }

        if (loadMaterial(material_res))
        {
            cLog << "No such material resource";
            flag = false;
        }

        return flag;
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

