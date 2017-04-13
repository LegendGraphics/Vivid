#include "RenderResourceManager.h"

#include "renderer/RenderInterface.h"
#include "renderer/resource/Buffer.h"
#include "renderer/resource/VertexDeclaration.h"

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
        String helper_str = res.substr(res.find_first_of(":") + 1);
        GPUResource* gpu_res = nullptr;
        if (gpu_resource::getTypeStr(gpu_resource::INDEX_STREAM) == resource_type_id)
        {
            gpu_res = new Buffer(gpu_resource::INDEX_STREAM);
        }
        else if (gpu_resource::getTypeStr(gpu_resource::VERTEX_STREAM) == resource_type_id)
        {
            gpu_res = new Buffer(gpu_resource::VERTEX_STREAM);
        }
        else if (gpu_resource::getTypeStr(gpu_resource::VERTEX_DECLARATION) == resource_type_id)
        {
            String vl_type = helper_str.substr(0, helper_str.find_first_of(";"));
            gpu_res = new VertexDeclaration(gpu_resource::VERTEX_DECLARATION, vertex_layout::getType(vl_type));
        }

        if (!gpu_res) return 0;

        gpu_res->load(res);
        gpu_res->descriptor(buildDescriptor(res));
        add(gpu_res);
        _res_wait_list.push_back(getResourceHandle(res));
        return _res_wait_list.back();
    }

    GPUResourcePtr RenderResourceManager::getGPUResource(ResourceHandle handle)
    {
        if (has(handle)) return dynamic_cast_ptr<Resource, GPUResource>(getResourcePtr(handle));
        else return nullptr;
    }

    void RenderResourceManager::immediateCreate()
    {
        if (_res_wait_list.empty()) return;

        RenderMsg msg;
        msg.rrm.generator = new RenderResourceGenerator;
        msg.rrm.numQueue = _res_wait_list.size();
        msg.rrm.rQueue = new ResourceStreamItem[msg.rrm.numQueue];

        for (uint32 i = 0; i < msg.rrm.numQueue; ++i)
        {
            getGPUResource(_res_wait_list[i])->fillStreamItem(msg.rrm.rQueue[i]);
        }

        RenderInterface::getInstance()->generateResource(&msg);
        _res_wait_list.clear();
    }
}