#ifndef COMMON_MESH_H
#define COMMON_MESH_H

#include "common/Object.h"
#include "math/Vector4.h"
#include "math/Vector3.h"
#include "math/Vector2.h"
#include "shape/BoundingBox.h"
#include "base/RefPtr.hpp"
#include "common/Resource.h"

#include "renderer/Resource/RenderResource.h"

namespace te
{

// I have no idea about how to write different kinds of vertex with different attributes.
// So now I use the Vertex_PNTB as example...
    enum VertexAttribute
    {
        VERTEX_POSITION,
        VERTEX_NORMAL,
        VERTEX_TANGENT,
        VERTEX_BITANGENT,
        VERTEX_SKINNED,
        VERTEX_TEXCOORD0,
        VERTEX_TEXCOORD1
    };

    enum VertexType
    {
        VERTEX_P,
        VERTEX_PN,
        VERTEX_PNTB,
        VERTEX_PNTB_SKINNED
    };

    struct Vertex_P
    {
        Vector3 position;
    };

    struct Vertex_PN
    {
        Vector3 position;
        Vector3 normal;
    };

    struct Vertex_PNTB
    {
        Vector3 position;
        Vector3 normal;
        Vector3 tangent;
        Vector3 bitangent;
    };

    struct Vertex_PNTB_Skinned
    {
        using JointIndices = int[4];
        using JointWeights = float[4];

        Vector3 position;
        Vector3 normal;
        Vector3 tangent;
        Vector3 bitangent;
        JointIndices joint_indices;
        JointWeights joint_weights;
    };

    void* getAttributeAddress(const Vertex_P& v, VertexAttribute attribute)
    {
        assert(attribute == VertexAttribute::VERTEX_POSITION);
        return (void*)&v.position;
    }

    void* getAttributeAddress(const Vertex_PN& v, VertexAttribute attribute)
    {
        assert(attribute <= VertexAttribute::VERTEX_NORMAL);
        return (void*)(&v.position + attribute * sizeof(Vector3));
    }

    void* getAttributeAddress(const Vertex_PNTB& v, VertexAttribute attribute)
    {
        assert(attribute <= VertexAttribute::VERTEX_BITANGENT);
        return (void*)(&v.position + attribute * sizeof(Vector3));
    }

    void* getAttributeAddress(const Vertex_PNTB_Skinned& v, VertexAttribute attribute)
    {
        return (void*)(&v.position + attribute * sizeof(Vector3));
    }

    using Vertex_P_Array = std::vector<Vertex_P>;
    using Vertex_PN_Array = std::vector<Vertex_PN>;
    using Vertex_PNTB_Array = std::vector<Vertex_PNTB>;
    using Vertex_PNTB_Skinned_Array = std::vector<Vertex_PNTB_Skinned>;

    struct VertexArray
    {
    private:
        union Array
        {
            Vertex_P_Array              p_array;
            Vertex_PN_Array             pn_array;
            Vertex_PNTB_Array           pntb_array;
            Vertex_PNTB_Skinned_Array   pntb_skinned_array;
        };

    private:
        class ArrayType
        {
        public:
            ArrayType() {}
            virtual ~ArrayType() {}

            /*virtual Vertex_P& atVertex_P(size_t index, Array& array) = 0;
            virtual Vertex_PN& atVertex_PN(size_t index, Array& array) = 0;
            virtual Vertex_PNTB& atVertex_PNTB(size_t index, Array& array) = 0;
            virtual Vertex_PNTB_Skinned& atVertex_PNTB_Skinned(size_t index, Array& array) = 0;*/
            virtual void resize(size_t size, Array& array) = 0;
            virtual void assign(size_t index, Array& array, const Vector3& v, VertexAttribute attribute) = 0;
        };

        class P_Array : public ArrayType
        {
        public:
            P_Array() {}
            virtual ~P_Array() {}

            virtual void resize(size_t size, Array& array) { array.p_array.resize(size); }
            virtual void assign(size_t index, Array& array, const Vector3& v, VertexAttribute attribute)
            {
                void* addr = getAttributeAddress(array.p_array[index], attribute);
                Vector3* old_v = (Vector3*)addr;
                *old_v = v;
            }
        };

        class PN_Array : public ArrayType
        {
        public:
            PN_Array() {}
            virtual ~PN_Array() {}

            virtual void resize(size_t size, Array& array) { array.pn_array.resize(size); }
            virtual void assign(size_t index, Array& array, const Vector3& v, VertexAttribute attribute)
            {
                void* addr = getAttributeAddress(array.pn_array[index], attribute);
                Vector3* old_v = (Vector3*)addr;
                *old_v = v;
            }
        };

        class PNTB_Array : public ArrayType
        {
        public:
            PNTB_Array() {}
            virtual ~PNTB_Array() {}

            virtual void resize(size_t size, Array& array) { array.pntb_array.resize(size); }
            virtual void assign(size_t index, Array& array, const Vector3& v, VertexAttribute attribute)
            {
                void* addr = getAttributeAddress(array.pntb_array[index], attribute);
                Vector3* old_v = (Vector3*)addr;
                *old_v = v;
            }
        };

        class PNTB_Skinned_Array : public ArrayType
        {
        public:
            PNTB_Skinned_Array() {}
            virtual ~PNTB_Skinned_Array() {}

            virtual void resize(size_t size, Array& array) { array.pntb_skinned_array.resize(size); }
            virtual void assign(size_t index, Array& array, const Vector3& v, VertexAttribute attribute)
            {
                void* addr = getAttributeAddress(array.pntb_skinned_array[index], attribute);
                Vector3* old_v = (Vector3*)addr;
                *old_v = v;
            }
        };

    public:
        /*union Array
        {
            Vertex_P_Array              p_array;
            Vertex_PN_Array             pn_array;
            Vertex_PNTB_Array           pntb_array;
            Vertex_PNTB_Skinned_Array   pntb_skinned_array;
        };*/

        ArrayType*   type;
        Array       varray;

        void assign(size_t index, const Vector3& v, VertexAttribute attribute)
        {
            type->assign(index, varray, v, attribute);
        }

        void resize(size_t size)
        {
            type->resize(size, varray);
        }
    };

    using IndexArray = std::vector<uint32>;

    /*class MeshRes : public Resource
    {
    public:
        MeshRes();
        bool load(const std::string & res);
        void release();

        friend class Mesh;

    protected:
        bool _skinned;
        std::vector<Vertex_PNTB> _vertices;
        std::vector<int>    _triangles;
    };*/

    //template <typename T>
    class Mesh: public Resource
    {
    /*public:
        using VertexArray = std::vector<T>;
        using IndexArray = std::vector<uint32>;
        using RawArray = std::vector<float>;*/

    public:
        Mesh();
   //     Mesh(const Mesh& mesh, const CopyOperator& copypo = CopyOperator::SHALLOW_COPY);
        virtual ~Mesh() = default;

   //     OBJECT_META_FUNCTION(Mesh);

        friend class ResourceLoader;

        bool load(const std::string & res);
        void unload();

        bool isSkinned() const { return _skinned; }
        VertexArray& getVertices() { return _vertices; }
        IndexArray& getTriangles() { return _triangles; }
        //std::vector<float>& getVertices() { return _testVertices; }
        //RenderResource& getVertexDeclaration() { return _vertex_declaration; }
        //RenderResource& getIndexBuffer() { return _index_buffer; }
        //std::vector<RenderResource>& getVertexBuffers() { return _vertex_buffers; }

    protected:
        VertexArray             _vertices;
        IndexArray              _triangles;
        //std::vector<float>     _testVertices;

        RefPtr<BoundingBox> _bounding;

        bool _skinned;

        /*std::vector<RenderResource> _vertex_buffers;
        RenderResource              _index_buffer;
        RenderResource              _vertex_declaration;*/
    };

    class MeshManager : public ResourceManager
    {
    public:
        MeshManager();
        ~MeshManager();

        bool create(const std::string& res);
    };
}



#endif // COMMON_MESH_H