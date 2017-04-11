#include "VertexDeclaration.h"

#include "common/Mesh.h"
#include "renderer/resource/VertexLayout.h"

te::VertexDeclaration::VertexDeclaration()
{
}

bool te::VertexDeclaration::load(const String & res)
{
    return false;
}

void te::VertexDeclaration::unload()
{
}

void te::VertexDeclaration::fillStreamItem(ResourceStreamItem & item, Resource * res)
{
    Mesh* mesh = dynamic_cast<Mesh*>(res);
    if (!mesh) return;

    item.res_type = GPUResourceType::VERTEX_DECLARATION;
    vertex_layout::VertexDeclarationStream* vds = new vertex_layout::VertexDeclarationStream;
    vds->res = &_gpu_resource_handle;
    vds->index_buffer = &mesh->getIndexBuffer().getGPUResourceHandle();
    vds->layout_type = vertex_layout::PNTB;
    vds->vertex_buffers.push_back(&mesh->getVertexBuffer().getGPUResourceHandle());
    item.stream = vds;
}
