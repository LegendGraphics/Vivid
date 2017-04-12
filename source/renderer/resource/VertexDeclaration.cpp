#include "VertexDeclaration.h"

#include "common/Mesh.h"
#include "renderer/resource/VertexLayout.h"
#include "renderer/resource/RenderResourceManager.h"

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
    if (_resource_stream) delete static_cast<vertex_layout::VertexDeclarationStream*>(_resource_stream);
}

bool te::VertexDeclaration::load(const String & res)
{
    return false;
}

void te::VertexDeclaration::unload()
{
}

void te::VertexDeclaration::fillStreamItem(ResourceStreamItem & item)
{
    item.res_type = _gpu_resource_type;
    item.stream = _resource_stream;
}

void te::VertexDeclaration::cacheStreamItem(Resource * res)
{
    Mesh* mesh = dynamic_cast<Mesh*>(res);
    if (!mesh) return;

    if (gpu_resource::VERTEX_DECLARATION != _gpu_resource_type) return;

    if (_resource_stream) delete static_cast<vertex_layout::VertexDeclarationStream*>(_resource_stream);
    RenderResourceManager* res_manager = ResourceMapper::getInstance()->get<RenderResourceManager>();
    vertex_layout::VertexDeclarationStream* vds = new vertex_layout::VertexDeclarationStream;
    vds->res = &_gpu_resource_handle;
    vds->index_buffer = &(res_manager->getGPUResource(mesh->getIndexBuffer())->getGPUResourceHandle());
    vds->layout_type = _vertex_layout_type; // TODO: layout type come from mesh
    vds->vertex_buffers.push_back(
        &(res_manager->getGPUResource(mesh->getVertexBuffer())->getGPUResourceHandle()));
    _resource_stream = vds;
}
