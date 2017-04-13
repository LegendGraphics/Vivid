#include "Buffer.h"

#include "common/Mesh.h"
#include "renderer/resource/VertexLayout.h"

te::Buffer::Buffer()
{
}

te::Buffer::Buffer(gpu_resource::Type t)
    : GPUResource(t)
{
}

te::Buffer::~Buffer()
{
    unload();
}

bool te::Buffer::load(const String & res)
{
    // res here is the helper resource
    // for buffer, res should be a mesh
    String helper_res_id = res.substr(res.find_first_of(":") + 1);
    Resources helper_res;
    MeshPtr helper_m_res = ResourceMapper::getInstance()->get<MeshManager>()->getMesh(helper_res_id);
    if (!helper_m_res) return false;

    helper_res.push_back(helper_m_res.get());

    cacheStreamItem(helper_res);

    return true;
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

void te::Buffer::cacheStreamItem(const Resources& res)
{
    if (res.empty() || res.size() != 1) return;

    Mesh* mesh = dynamic_cast<Mesh*>(res[0]);
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
        vs->stride = mesh->getVertices().sizeInBytes() / mesh->getVertices().size();
        vs->raw_data = mesh->getVertices().buffer(); // assume memory in std::vector<Vertex_PNTB> is tight packed
                                                     //float* aa = &m->getVertices()[0];

        float* aa = (float*)mesh->getVertices().buffer();
        //for (int i = 0; i < 24 * 3 * 4; ++i) std::cout << *(aa + i) << " ";

        _resource_stream = (void*)vs;
    }
}