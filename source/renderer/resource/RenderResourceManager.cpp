#include "RenderResourceManager.h"

#include "common/Mesh.h"

namespace te
{
    RenderResourceManager::RenderResourceManager()
        :ResourceManager(ResourceType::GPU)
    {
    }

    RenderResourceManager::~RenderResourceManager()
    {
    }

    ResourceHandle RenderResourceManager::create(const String & res)
    {
        if (ResourceHandle handle = getResourceHandle(res)) return handle;

        // for now, we parse the string to decide its type
        // Index, Vertex, VAO, etc
        String resource_type_id = res.substr(0, res.find_first_of(":"));
        String res_id = res.substr(res.find_first_of(":") + 1);
        GPUResource* gpu_res = nullptr;
        Resource* helper_res = nullptr;
        if (gpu_resource::getTypeId(gpu_resource::INDEX_STREAM) == resource_type_id)
        {
            gpu_res = new Buffer(gpu_resource::INDEX_STREAM);
            helper_res = ResourceMapper::getInstance()
                ->get<MeshManager>()
                ->getMesh(res_id).get();
        }
        else if (gpu_resource::getTypeId(gpu_resource::VERTEX_STREAM) == resource_type_id)
        {
            gpu_res = new Buffer(gpu_resource::VERTEX_STREAM);
            helper_res = ResourceMapper::getInstance()
                ->get<MeshManager>()
                ->getMesh(res_id).get();
        }
        else if (gpu_resource::getTypeId(gpu_resource::VERTEX_DECLARATION) == resource_type_id)
        {
            gpu_res = new VertexDeclaration(gpu_resource::VERTEX_DECLARATION, vertex_layout::PNTB);
            helper_res = ResourceMapper::getInstance()
                ->get<MeshManager>()
                ->getMesh(res_id).get();
        }

        if (!gpu_res) return 0;

        gpu_res->cacheStreamItem(helper_res);
        gpu_res->descriptor(buildDescriptor(res));
        add(gpu_res);
        return getResourceHandle(res);
    }

    GPUResourcePtr RenderResourceManager::getGPUResource(ResourceHandle handle)
    {
        if (has(handle)) return dynamic_cast_ptr<Resource, GPUResource>(getResourcePtr(handle));
        else return nullptr;
    }
}