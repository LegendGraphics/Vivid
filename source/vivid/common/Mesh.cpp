#include "vivid/common/Mesh.h"
#include "vivid/io/FileUtils.h"
#include "vivid/io/ResourceLoader.h"


namespace te
{
    
    Mesh::Mesh()
        : _render_object(0xFFFFFFFF)
    {
    }

    bool Mesh::load(const String & res)
    {
        if (!ResourceLoader::load(this, res))
            return false;
        return true;
    }

    void Mesh::unload()
    {

    }

    MeshManager::MeshManager()
        :ResourceManager(ResourceType::Mesh)
    {}

    MeshManager::~MeshManager(){}

    ResourceHandle MeshManager::create(const String& res)
    {
        if (ResourceHandle handle = getResourceHandle(res)) return handle;
        else
        {
            MeshPtr mesh = new Mesh;
            if (mesh->load(res))
            {
                mesh->descriptor(buildDescriptor(res));
                add(mesh.get());
                return getResourceHandle(res);
            }
            else return 0;
        }
    }

    MeshPtr MeshManager::getMesh(ResourceHandle handle)
    {
        if (has(handle)) return dynamic_cast_ptr<Resource, Mesh>(getResourcePtr(handle));
        else return nullptr;
    }

    MeshPtr MeshManager::getMesh(const String& res)
    {
        return getMesh(getResourceHandle(res));
    }
}