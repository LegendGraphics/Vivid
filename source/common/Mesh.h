#ifndef COMMON_MESH_H
#define COMMON_MESH_H

#include "common/Object.h"
#include "math/Vector4.h"
#include "math/Vector3.h"
#include "math/Vector2.h"
#include "common/BoundingBox.h"
#include "base/RefPtr.hpp"

namespace te
{
    struct Vertex
    {
        Vector3 position;
        Vector2 texcoord;
        Vector4 tangent;
        Vector3 normal;

        /*VertexAttribute getVertexType()
        {
            VertexAttribute type =
                VertexAttribute::TE_VERTEX_POSITION |
                VertexAttribute::TE_VERTEX_TEXCOORD0 |
                VertexAttribute::TE_VERTEX_TANGENT |
                VertexAttribute::TE_VERTEX_NORMAL;
            return type;
        };*/
    };

    struct VertexIndices
    {
        int pos_idx;
        int tex_idx;
        int nrm_idx;
    };

    enum class VertexAttribute
    {
        TE_VERTEX_POSITION =        1 << 0,
        TE_VERTEX_COLOR =           1 << 1,
        TE_VERTEX_TANGENT =         1 << 2,
        TE_VERTEX_NORMAL =          1 << 3,
        TE_VERTEX_TEXCOORD0 =       1 << 4,
        TE_VERTEX_TEXCOORD1 =       1 << 5,
        TE_VERTEX_TEXCOORD2 =       1 << 6,
        TE_VERTEX_TEXCOORD3 =       1 << 7
    };

    struct VertexBuffer
    {
        int* data;
        int element_size;
        int element_count;

        VertexBuffer(int element_size, int element_count)
        {
            memset(this, 0, sizeof(VertexBuffer));
            this->element_size = element_size;
            this->element_count = element_count;

            data = (int*)(malloc(element_size * element_count));
        }
        

        ~VertexBuffer()
        {
            if (data)
            {
                free(data);
                data = nullptr;
            }
        }

        int getSize()
        {
            return element_size * element_count;
        }

        void write()
        {
            if (!data)
            {
                data = (int*)(malloc(element_size * element_count));
            }
        }

        VertexBuffer(const VertexBuffer& other) = delete;
        VertexBuffer& operator = (const VertexBuffer& other) = delete;
    };

    struct IndexBuffer
    {
        int* data;
        int element_size;
        int element_count;

        IndexBuffer(int element_size, int element_count)
        {
            memset(this, 0, sizeof(IndexBuffer));
            this->element_size = element_size;
            this->element_count = element_count;

            data = (int*)(malloc(element_size * element_count));
        }


        ~IndexBuffer()
        {
            if (data)
            {
                free(data);
                data = nullptr;
            }
        }

        int getSize()
        {
            return element_size * element_count;
        }

        void write()
        {
            if (!data)
            {
                data = (int*)(malloc(element_size * element_count));
            }
        }

        IndexBuffer(const IndexBuffer& other) = delete;
        IndexBuffer& operator = (const IndexBuffer& other) = delete;
    };

    struct MeshSubset
    {
        VertexBuffer*       vb;
        IndexBuffer*        ib;
        int                 index_start;
        int                 index_count;
        std::string         mtl_name;

        MeshSubset()
        {
            vb = 0;
            ib = 0;
            index_start = 0;
            index_count = 0;
        }
    };
    typedef std::vector<MeshSubset> MeshSubsets;

    class Mesh: public Object
    {
    public:
        Mesh() = default;
        virtual ~Mesh() = default;
        Mesh(const Mesh& mesh, const CopyOperator& copypo = CopyOperator::SHALLOW_COPY);

        OBJECT_META_FUNCTION(Mesh);

        void clear();

        void setVertexArray(const std::vector<Vertex>& vertices);
        void setTriangleArray(const std::vector<int>& triangles);

        int getVertexCount() const;
        int getIndexCount() const;

    protected:

        VertexBuffer* _vertex_buffer;
        IndexBuffer* _index_buffer;

        std::vector<Vertex> _vertices;
        std::vector<int>    _triangles;

        RefPtr<BoundingBox> _bounding;



    };
}



#endif // COMMON_MESH_H