#ifndef COMMON_MESH_H
#define COMMON_MESH_H

#include "Core/common/Object.h"
#include "Core/math/Vector4.h"
#include "Core/math/Vector3.h"
#include "Core/math/Vector2.h"

namespace te
{
    struct TE_VERTEX_P3T4TG4N3
    {
        Vector3 position;
        Vector4 texcoord;
        Vector4 tangent;
        Vector3 normal;

        TE_VERTEX_ATTRIBUTE getVertexType()
        {
            TE_VERTEX_ATTRIBUTE type = 
                TE_VERTEX_ATTRIBUTE::TE_VERTEX_POSITION | 
                TE_VERTEX_ATTRIBUTE::TE_VERTEX_TEXCOORD0 |
                TE_VERTEX_ATTRIBUTE::TE_VERTEX_TANGENT |
                TE_VERTEX_ATTRIBUTE::TE_VERTEX_NORMAL;
            return type;
        };
    };

    enum class TE_VERTEX_ATTRIBUTE
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

        void setData(void* src_data, int index)
        {
            if (index < element_count)
            {
                memcpy( data + element_size * index, src_data, element_size);
            }
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

        void setData(void* src_data, int index)
        {
            if (index < element_count)
            {
                memcpy( data + element_size * index, src_data, element_size);
            }
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

    class Mesh: public Object
    {
    public:
        Mesh();
        virtual ~Mesh();

        void clear();

        void setVertexArray(const Vec3Array& vertices);
        void setNormalArray(const Vec3Array& normals);
        void setColorArray(const Vec3Array& colors);
        void setUVArray(const Vec2Array& uvs);
        void setTangentArray(const Vec4Array& tangents);
        void setTriangleArray(const Vec3Array& triangles);

        int getVertexCount() const;
        int getIndexCount() const;

    protected:
        RefPtr<Vec3Array> _vertices;
        RefPtr<Vec3Array> _normals;
        RefPtr<Vec3Array> _colors;
        RefPtr<Vec2Array> _uvs;
        RefPtr<Vec4Array> _tangents;
        RefPtr<Vec3Array> _triangles;

        RefPtr<BoundingBox> _bounding;



    };
}



#endif // COMMON_MESH_H