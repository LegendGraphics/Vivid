#include "Buffer.h"

#include "common/Mesh.h"
#include "renderer/resource/VertexLayout.h"

bool te::Buffer::load(const String & res)
{
    return false;
}

void te::Buffer::unload()
{
}

void te::Buffer::fillStreamItem(ResourceStreamItem & item, Resource* res)
{
    Mesh* mesh = dynamic_cast<Mesh*>(res);
    if (!mesh) return;

    if (GPUResourceType::INDEX_STREAM == _gpu_resource_type)
    {
        item.res_type = GPUResourceType::INDEX_STREAM;
        vertex_layout::IndexStream* is = new vertex_layout::IndexStream;
        is->res = &_gpu_resource_handle;
        is->size = 4 * mesh->getTriangles().size();
        is->raw_data = &mesh->getTriangles()[0];
        item.stream = is;
    }
    else if (GPUResourceType::VERTEX_STREAM == _gpu_resource_type)
    {
        item.res_type = GPUResourceType::VERTEX_STREAM;
        vertex_layout::VertexStream* vs = new vertex_layout::VertexStream;
        vs->res = &_gpu_resource_handle;
        vs->size = mesh->getVertices().sizeInBytes();//4 * m->getVertices().size(); // 12 float for each vertex(PNTB)
        vs->stride = 12;
        //vs->raw_data = &m->getVertices()[0];
        vs->raw_data = mesh->getVertices().buffer(); // assume memory in std::vector<Vertex_PNTB> is tight packed
                                                  //float* aa = &m->getVertices()[0];
        float* aa = (float*)mesh->getVertices().buffer();
        for (int i = 0; i < 24 * 3 * 4; ++i) std::cout << *(aa + i) << " ";
        item.stream = vs;
    }
}
