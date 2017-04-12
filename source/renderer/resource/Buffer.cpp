#include "Buffer.h"

#include "common/Mesh.h"
#include "renderer/resource/VertexLayout.h"

te::Buffer::~Buffer()
{
}

bool te::Buffer::load(const String & res)
{
    return false;
}

void te::Buffer::unload()
{
    if (_resource_stream)
    {
        if (gpu_resource::INDEX_STREAM == _gpu_resource_type)
            delete static_cast<vertex_layout::IndexStream*>(_resource_stream);
        else if(gpu_resource::VERTEX_STREAM == _gpu_resource_type)
            delete static_cast<vertex_layout::VertexStream*>(_resource_stream);
    }
}

void te::Buffer::cacheStreamItem(Resource * res)
{
    Mesh* mesh = dynamic_cast<Mesh*>(res);
    if (!mesh) return;

    if (gpu_resource::INDEX_STREAM == _gpu_resource_type)
    {
        if (_resource_stream) delete static_cast<vertex_layout::IndexStream*>(_resource_stream);
        vertex_layout::IndexStream* is = new vertex_layout::IndexStream;
        is->res = &_gpu_resource_handle;
        is->size = 4 * mesh->getTriangles().size();
        is->raw_data = &mesh->getTriangles()[0];
        _resource_stream = (void*)is;
    }
    else if (gpu_resource::VERTEX_STREAM == _gpu_resource_type)
    {
        if (_resource_stream) delete static_cast<vertex_layout::VertexStream*>(_resource_stream);
        vertex_layout::VertexStream* vs = new vertex_layout::VertexStream;
        vs->res = &_gpu_resource_handle;
        vs->size = mesh->getVertices().sizeInBytes();//4 * m->getVertices().size(); // 12 float for each vertex(PNTB)
        vs->stride = 12; // TODO: this should come from the array
        vs->raw_data = mesh->getVertices().buffer(); // assume memory in std::vector<Vertex_PNTB> is tight packed
                                                     //float* aa = &m->getVertices()[0];

        float* aa = (float*)mesh->getVertices().buffer();
        //for (int i = 0; i < 24 * 3 * 4; ++i) std::cout << *(aa + i) << " ";

        _resource_stream = (void*)vs;
    }
}

void te::Buffer::fillStreamItem(ResourceStreamItem & item)
{
    item.res_type = _gpu_resource_type;
    item.stream = _resource_stream;
}
