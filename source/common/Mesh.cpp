#include "common/Mesh.h"
#include "io/FileUtils.h"
#include "io/ResourceLoader.h"

namespace te
{
    
    Mesh::Mesh()
    {
    }

    bool Mesh::load(const String & res)
    {
        return ResourceLoader::load(this, res);
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
        if (exist(res)) return _id_maps[res];
        else
        {
            Mesh* mesh = new Mesh;
            if (mesh->load(res))
            {
                mesh->descriptor(buildDescriptor(res));
                add(mesh);
                return _id_maps[res];
            }
            else return 0;
        }
    }

    Mesh* MeshManager::getMesh(ResourceHandle handle)
    {
        if (has(handle)) return dynamic_cast<Mesh*>(_resources[handle]);
        else return nullptr;
    }
}