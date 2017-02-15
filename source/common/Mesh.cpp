#include "common/Mesh.h"

namespace te
{

    bool MeshRes::load(const char *data, int size)
    {
        if (!Resource::load(data, size)) return false;
        
        char *data_ptr = (char *)data;

        // Check header and version
        char id[3];
        memcpy(&id, data_ptr, 3); data_ptr += 3;
        if (id[0] != 'T' || id[1] != 'E' || id[2] != 'M')
            return false; //("Invalid mesh resource");

        int version;
        memcpy(&version, data_ptr, sizeof(int)); data_ptr += sizeof(int);
        if (version != 1)
            return false; //("Unsupported version of mesh resource");

        memcpy(&_skinned, data_ptr, sizeof(bool)); data_ptr += sizeof(bool);

        // Load mesh data
        // vertex stream
        int attribute_num;
        memcpy(&attribute_num, data_ptr, sizeof(int)); data_ptr += sizeof(int);

        int vertex_num;
        memcpy(&vertex_num, data_ptr, sizeof(int)); data_ptr += sizeof(int);

        _vertices.resize(vertex_num);

        for (int i = 0; i < vertex_num; ++i)
        {
            Vertex_PNTB_Skinned& vertex = _vertices[i];

            int identifier, element_size;
            memcpy(&identifier, data_ptr, sizeof(int)); data_ptr += sizeof(int);
            memcpy(&element_size, data_ptr, sizeof(int)); data_ptr += sizeof(int);
            if (identifier == 0) { memcpy(&vertex.position, data_ptr, 3 * sizeof(float)); data_ptr += sizeof(float); }
            else if (identifier == 1) { memcpy(&vertex.normal, data_ptr, 3 * sizeof(float)); data_ptr += sizeof(float); }
            else if (identifier == 2) { memcpy(&vertex.tangent, data_ptr, 3 * sizeof(float)); data_ptr += sizeof(float); }
            else if (identifier == 3) { memcpy(&vertex.bitangent, data_ptr, 3 * sizeof(float)); data_ptr += sizeof(float); }
            else if (identifier == 4) { memcpy(&vertex.joint_indices, data_ptr, 4 * sizeof(float)); data_ptr += sizeof(float); }
            else if (identifier == 5) { memcpy(&vertex.joint_weights, data_ptr, 4 * sizeof(float)); data_ptr += sizeof(float); }
        }

        // triangle stream
        int indice_num;
        memcpy(&vertex_num, data_ptr, sizeof(int)); data_ptr += sizeof(int);
        memcpy(&_triangles, data_ptr, indice_num * sizeof(int)); data_ptr += sizeof(int);

        setResourceHandle();

        return true;
    }

    void MeshRes::release()
    {

    }

    Mesh::Mesh(const Mesh& mesh, const CopyOperator& copypo)
    {

    }

    void Mesh::init(MeshRes* res)
    {
        _skinned = res->_skinned;
        _vertices = res->_vertices;
        _triangles = res->_triangles;
    }

}