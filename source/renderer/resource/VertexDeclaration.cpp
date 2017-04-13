#include "VertexDeclaration.h"

#include "renderer/resource/VertexLayout.h"
#include "renderer/resource/RenderResourceManager.h"
#include "renderer/resource/Buffer.h"

te::VertexDeclaration::VertexDeclaration()
{
}

te::VertexDeclaration::VertexDeclaration(gpu_resource::Type t)
    : GPUResource(t)
{
}

te::VertexDeclaration::VertexDeclaration(gpu_resource::Type t, vertex_layout::Type vl_t)
    : GPUResource(t),
    _vertex_layout_type(vl_t)
{
}

te::VertexDeclaration::~VertexDeclaration()
{
    unload();
}

bool te::VertexDeclaration::load(const String & res)
{
    // res here is the helper resource
    // for vao, res should be a index buffer and several vertex buffers
    RenderResourceManager* res_manager = ResourceMapper::getInstance()->get<RenderResourceManager>();
    String helper_res_id = res.substr(res.find_first_of(":") + 1);
    Resources helper_res;
    while (!helper_res_id.empty())
    {
        String cur_res_id = helper_res_id.substr(0, helper_res_id.find_first_of(";"));
        helper_res_id = helper_res_id.substr(helper_res_id.find_first_of(";") + 1);
        ResourcePtr cur_res = res_manager->getResourcePtr(res_manager->getResourceHandle(cur_res_id));
        if (!cur_res) continue;

        helper_res.push_back(cur_res.get());
    }

    if (helper_res.empty()) return false;

    cacheStreamItem(helper_res);

    return true;
}

void te::VertexDeclaration::unload()
{
    if (_resource_stream) delete static_cast<vertex_layout::VertexDeclarationStream*>(_resource_stream);
}

void te::VertexDeclaration::cacheStreamItem(const Resources& res)
{
    if (res.empty() || res.size() < 2) return; // res should be >= 2, one index buffer and at least one vertex buffer

    if (gpu_resource::VERTEX_DECLARATION != _gpu_resource_type) return;

    if (_resource_stream) delete static_cast<vertex_layout::VertexDeclarationStream*>(_resource_stream);
    RenderResourceManager* res_manager = ResourceMapper::getInstance()->get<RenderResourceManager>();
    vertex_layout::VertexDeclarationStream* vds = new vertex_layout::VertexDeclarationStream;
    vds->res = &_gpu_resource_handle;
    vds->layout_type = _vertex_layout_type; // TODO: layout type come from mesh
    for (Resource* cur_res : res)
    {
        GPUResource* gpu_res = dynamic_cast<GPUResource*>(cur_res);
        if (!gpu_res) continue;

        if (gpu_resource::INDEX_STREAM == gpu_res->getGPUResourceType())
            vds->index_buffer = &(gpu_res->getGPUResourceHandle());
        if (gpu_resource::VERTEX_STREAM == gpu_res->getGPUResourceType())
            vds->vertex_buffers.push_back(&(gpu_res->getGPUResourceHandle()));
    }
    _resource_stream = vds;
}
