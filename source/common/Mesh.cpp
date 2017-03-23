#include "common/Mesh.h"
#include "io/FileUtils.h"
#include "io/ResourceLoader.h"

namespace te
{
    //MeshRes::MeshRes()
    //    :Resource(ResourceType::Mesh)
    //{}

    //bool MeshRes::load(const std::string& res)
    //{
    //    if (!Resource::load(res)) return false;
    //    
    //    char *data_ptr = nullptr;
    //    int size = 0;

    //    streamFromBinaryFile(res, data_ptr, size);

    //    // Check header and version
    //    char id[3];
    //    memcpy(&id, data_ptr, 3); data_ptr += 3;
    //    if (id[0] != 'T' || id[1] != 'E' || id[2] != 'M')
    //        return false; //("Invalid mesh resource");

    //    int version;
    //    memcpy(&version, data_ptr, sizeof(int)); data_ptr += sizeof(int);
    //    if (version != 1)
    //        return false; //("Unsupported version of mesh resource");

    //    memcpy(&_skinned, data_ptr, sizeof(bool)); data_ptr += sizeof(bool);

    //    // Load mesh data
    //    // vertex stream
    //    int attribute_num;
    //    memcpy(&attribute_num, data_ptr, sizeof(int)); data_ptr += sizeof(int);

    //    int vertex_num;
    //    memcpy(&vertex_num, data_ptr, sizeof(int)); data_ptr += sizeof(int);

    //    _vertices.resize(vertex_num);

    //    for (int i = 0; i < attribute_num; ++i)
    //    {
    //        unsigned char uc;
    //        short sh;
    //        int stream_id, elem_size;
    //        memcpy(&stream_id, data_ptr, sizeof(int)); data_ptr += sizeof(int);
    //        memcpy(&elem_size, data_ptr, sizeof(int)); data_ptr += sizeof(int);
    //        std::string errormsg;

    //        switch (stream_id)
    //        {
    //        case 0:		// Position
    //            if (elem_size != 12)
    //            {
    //                errormsg = "Invalid position base stream";
    //                break;
    //            }
    //            for (int j = 0; j < vertex_num; ++j)
    //            {
    //                memcpy(&_vertices[j].position.x, data_ptr, sizeof(float)); data_ptr += sizeof(float);
    //                memcpy(&_vertices[j].position.y, data_ptr, sizeof(float)); data_ptr += sizeof(float);
    //                memcpy(&_vertices[j].position.z, data_ptr, sizeof(float)); data_ptr += sizeof(float);
    //            }
    //            break;
    //        case 1:		// Normal
    //            if (elem_size != 6)
    //            {
    //                errormsg = "Invalid normal base stream";
    //                break;
    //            }
    //            for (int j = 0; j < vertex_num; ++j)
    //            {
    //                memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); _vertices[j].normal.x = sh / 32767.0f;
    //                memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); _vertices[j].normal.y = sh / 32767.0f;
    //                memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); _vertices[j].normal.z = sh / 32767.0f;
    //            }
    //            break;
    //        case 2:		// Tangent
    //            if (elem_size != 6)
    //            {
    //                errormsg = "Invalid tangent base stream";
    //                break;
    //            }
    //            for (int j = 0; j < vertex_num; ++j)
    //            {
    //                memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); _vertices[j].tangent.x = sh / 32767.0f;
    //                memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); _vertices[j].tangent.y = sh / 32767.0f;
    //                memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); _vertices[j].tangent.z = sh / 32767.0f;
    //            }
    //            break;
    //        case 3:		// Bitangent
    //            if (elem_size != 6)
    //            {
    //                errormsg = "Invalid bitangent base stream";
    //                break;
    //            }
    //            for (int j = 0; j < vertex_num; ++j)
    //            {
    //                memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); _vertices[j].bitangent.x = sh / 32767.0f;
    //                memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); _vertices[j].bitangent.y = sh / 32767.0f;
    //                memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); _vertices[j].bitangent.z = sh / 32767.0f;
    //            }
    //            break;
    //        default:
    //            data_ptr += elem_size * vertex_num;
    //            continue;
    //        }
    //    }

    //    // triangle stream
    //    int indice_num;
    //    memcpy(&indice_num, data_ptr, sizeof(int)); data_ptr += sizeof(int);

    //    _triangles.resize(indice_num);
    //    for (int i = 0; i < indice_num; ++i)
    //    {
    //        memcpy(&_triangles[i], data_ptr, sizeof(int)); data_ptr += sizeof(int);
    //    }

    //    setResourceHandle();

    //    return true;
    //}

    //void MeshRes::release()
    //{

    //}

    
    
    Mesh::Mesh()
    {
        /*_vertex_buffers.resize(1, RenderResource(RenderResource::VERTEX_STREAM));
        _index_buffer.type = RenderResource::INDEX_STREAM;
        _vertex_declaration.type = RenderResource::VERTEX_DECLARATION;*/

    }

    bool Mesh::load(const std::string & res)
    {
        return false;
    }

    void Mesh::unload()
    {

    }

    /* Mesh::Mesh(const Mesh& mesh, const CopyOperator& copypo)
     {

     }*/

    //void Mesh::init(MeshRes* res)
    //{
    //    _skinned = res->_skinned;
    //    _vertices = res->_vertices;
    //    _triangles = std::vector<uint32>(res->_triangles.begin(), res->_triangles.end());

    //    {
    //        for (size_t i = 0; i < _vertices.size(); ++i)
    //        {
    //            _testVertices.push_back(_vertices[i].position.x);
    //            _testVertices.push_back(_vertices[i].position.y);
    //            _testVertices.push_back(_vertices[i].position.z);

    //            _testVertices.push_back(_vertices[i].normal.x);
    //            _testVertices.push_back(_vertices[i].normal.y);
    //            _testVertices.push_back(_vertices[i].normal.z);

    //            _testVertices.push_back(_vertices[i].tangent.x);
    //            _testVertices.push_back(_vertices[i].tangent.y);
    //            _testVertices.push_back(_vertices[i].tangent.z);

    //            _testVertices.push_back(_vertices[i].bitangent.x);
    //            _testVertices.push_back(_vertices[i].bitangent.y);
    //            _testVertices.push_back(_vertices[i].bitangent.z);
    //        }
    //    }

    //    // need consensus here
    //    // vertex attribute array should obey it's vertex layout definition
    //    // see renderer/resource/VertexLayout.cpp

    //    _vertex_buffers.resize(1, RenderResource(RenderResource::VERTEX_STREAM));
    //    _index_buffer.type = RenderResource::INDEX_STREAM;
    //    _vertex_declaration.type = RenderResource::VERTEX_DECLARATION;
    //}


    MeshManager::MeshManager()
        :ResourceManager(ResourceType::Mesh)
    {}

    MeshManager::~MeshManager(){}

    bool MeshManager::create(const std::string& res)
    {
        Mesh* mesh = new Mesh;
        if (ResourceLoader::load(mesh, res)) {
            add(mesh);
            return true;
        }
        else return false;
    }

}