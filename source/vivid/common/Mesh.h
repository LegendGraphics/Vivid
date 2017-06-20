#ifndef COMMON_MESH_H
#define COMMON_MESH_H

#include "vivid/common/Clone.h"
#include "vivid/math/Vector4.h"
#include "vivid/math/Vector3.h"
#include "vivid/math/Vector2.h"
#include "vivid/shape/BoundingBox.h"
#include "vivid/base/RefPtr.hpp"
#include "vivid/common/Resource.h"
#include "vivid/base/Types.h"

#include "vivid/renderer/resource/VertexLayoutType.h"

namespace vivid
{

// I use a top-down method of using polymorphism + virtual function tricks to code the run-time status of the different vertex type.
// Another way to do so is a bottom-up method by encapsulating VertexBuffer from memory structure to upper layer structure.
// Which one is better? Of course not this one....

    //namespace vertex_layout
    //{
    //    enum VertexAttribute
    //    {
    //        POSITION = 1 << 0,
    //        NORMAL = 1 << 1,
    //        TANGENT = 1 << 2,
    //        BITANGENT = 1 << 3,
    //        TEXTURE1 = 1 << 4,
    //        TEXTURE2 = 1 << 5
    //    };

    //    enum Type {
    //        P = VertexAttribute::POSITION,

    //        PN = VertexAttribute::POSITION + VertexAttribute::NORMAL,

    //        PNTB = VertexAttribute::POSITION + VertexAttribute::NORMAL
    //        + VertexAttribute::TANGENT + VertexAttribute::BITANGENT,

    //        PNTB_TEX = VertexAttribute::POSITION + VertexAttribute::NORMAL
    //        + VertexAttribute::TANGENT + VertexAttribute::BITANGENT
    //        + VertexAttribute::TEXTURE1,

    //        PNTB_SKINNED,
    //        Overlay, // Position with Texture Coordinate
    //        Model,
    //        Partical,
    //    };
    //}

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

    struct Vertex_PNTB_TEX
    {
        using TexArray = Vector2[2];

        Vector3 position;
        Vector3 normal;
        Vector3 tangent;
        Vector3 bitangent;
        TexArray tex;
    };

    // no animation temporarily
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

    using Vertex_P_Array = std::vector<Vertex_P>;
    using Vertex_PN_Array = std::vector<Vertex_PN>;
    using Vertex_PNTB_Array = std::vector<Vertex_PNTB>;
    using Vertex_PNTB_TEX_Array = std::vector<Vertex_PNTB_TEX>;
    using Vertex_PNTB_Skinned_Array = std::vector<Vertex_PNTB_Skinned>;

    struct VertexArray
    {
    private:
        class ArrayType;
        class P_Array;
        class PN_Array;
        class PNTB_Array;
        class PNTB_TEX_Array;
        class PNTB_Skinned_Array;


        void*           _vertex_buffer;
        ArrayType*      _type;
        size_t          _vertex_size;

    private:
        class ArrayType
        {
        public:
            ArrayType() {}
            virtual ~ArrayType() {}

            virtual void initialize(size_t size, void*& array) {}
            virtual void* buffer(void*& array) { return nullptr; }
            virtual size_t sizeInBytes(size_t size, void*& array) { return 0; }
            virtual Vector3& position(size_t index, void*& array) { assert("No Position Attribute!" && false); return Vector3(); }
            virtual Vector3& normal(size_t index, void*& array) { assert("No Normal Attribute!" && false); return Vector3(); }
            virtual Vector3& tangent(size_t index, void*& array) { assert("No tangent Attribute!" && false); return Vector3(); }
            virtual Vector3& bitangent(size_t index, void*& array) { assert("No bitangent Attribute!" && false); return Vector3(); }
            virtual Vector2& tex(size_t index, size_t tex_index, void*& array) { assert("No texture Attribute!" && false); return Vector2(); }
        };

        class P_Array : public ArrayType
        {
        public:
            P_Array() {}
            virtual ~P_Array() {}

            virtual void initialize(size_t size, void*& array) { array = new Vertex_P_Array(size); }
            virtual void* buffer(void*& array) { return &(*((Vertex_P_Array*)(array)))[0].position.x; }
            virtual size_t sizeInBytes(size_t size, void*& array) { return sizeof(Vertex_P) * size; }
            virtual Vector3& position(size_t index, void*& array) { return (*((Vertex_P_Array*)(array)))[index].position; }
        };

        class PN_Array : public ArrayType
        {
        public:
            PN_Array() {}
            virtual ~PN_Array() {}

            virtual void initialize(size_t size, void*& array) { array = new Vertex_PN_Array(size); }
            virtual void* buffer(void*& array) { return &(*((Vertex_PN_Array*)(array)))[0].position.x; }
            virtual size_t sizeInBytes(size_t size, void*& array) { return sizeof(Vertex_PN) * size; }
            virtual Vector3& position(size_t index, void*& array) { return (*((Vertex_PN_Array*)(array)))[index].position; }
            virtual Vector3& normal(size_t index, void*& array) { return (*((Vertex_PN_Array*)(array)))[index].normal; }
        };

        class PNTB_Array : public ArrayType
        {
        public:
            PNTB_Array() {}
            virtual ~PNTB_Array() {}

            virtual void initialize(size_t size, void*& array) { array = new Vertex_PNTB_Array(size); }
            virtual void* buffer(void*& array) { return &(*((Vertex_PNTB_Array*)(array)))[0].position.x; }
            virtual size_t sizeInBytes(size_t size, void*& array) { return sizeof(Vertex_PNTB) * size; }
            virtual Vector3& position(size_t index, void*& array) { return (*((Vertex_PNTB_Array*)(array)))[index].position; }
            virtual Vector3& normal(size_t index, void*& array) { return (*((Vertex_PNTB_Array*)(array)))[index].normal; }
            virtual Vector3& tangent(size_t index, void*& array) { return (*((Vertex_PNTB_Array*)(array)))[index].tangent; }
            virtual Vector3& bitangent(size_t index, void*& array) { return (*((Vertex_PNTB_Array*)(array)))[index].bitangent; }
        };

        class PNTB_TEX_Array : public ArrayType
        {
        public:
            PNTB_TEX_Array() {}
            virtual ~PNTB_TEX_Array() {}

            virtual void initialize(size_t size, void*& array) { array = new Vertex_PNTB_TEX_Array(size); }
            virtual void* buffer(void*& array) { return &(*((Vertex_PNTB_TEX_Array*)(array)))[0].position.x; }
            virtual size_t sizeInBytes(size_t size, void*& array) { return sizeof(Vertex_PNTB_TEX) * size; }
            virtual Vector3& position(size_t index, void*& array) { return (*((Vertex_PNTB_TEX_Array*)(array)))[index].position; }
            virtual Vector3& normal(size_t index, void*& array) { return (*((Vertex_PNTB_TEX_Array*)(array)))[index].normal; }
            virtual Vector3& tangent(size_t index, void*& array) { return (*((Vertex_PNTB_TEX_Array*)(array)))[index].tangent; }
            virtual Vector3& bitangent(size_t index, void*& array) { return (*((Vertex_PNTB_TEX_Array*)(array)))[index].bitangent; }
            virtual Vector2& tex(size_t index, size_t tex_index, void*& array) { return (*((Vertex_PNTB_TEX_Array*)(array)))[index].tex[tex_index]; }

        };

        class PNTB_Skinned_Array : public ArrayType
        {
        public:
            PNTB_Skinned_Array() {}
            virtual ~PNTB_Skinned_Array() {}

            virtual void initialize(size_t size, void*& array) { array = new Vertex_PNTB_Skinned_Array(size); }
            virtual void* buffer(void*& array) { return &(*((Vertex_PNTB_Skinned_Array*)(array)))[0].position.x; }
            virtual size_t sizeInBytes(size_t size, void*& array) { return sizeof(Vertex_PNTB_Skinned) * size; }
            virtual Vector3& position(size_t index, void*& array) { return (*((Vertex_PNTB_Skinned_Array*)(array)))[index].position; }
            virtual Vector3& normal(size_t index, void*& array) { return (*((Vertex_PNTB_Skinned_Array*)(array)))[index].normal; }
            virtual Vector3& tangent(size_t index, void*& array) { return (*((Vertex_PNTB_Skinned_Array*)(array)))[index].tangent; }
            virtual Vector3& bitangent(size_t index, void*& array) { return (*((Vertex_PNTB_Skinned_Array*)(array)))[index].bitangent; }
        };

    public:
        VertexArray()
            :_type(new ArrayType)
        {
        }
        ~VertexArray()
        {
            delete _type;
        }

        void convert(vertex_layout::Type type)
        {
            if (_type) delete _type;
            switch (type)
            {
            case vertex_layout::P:
                _type = new P_Array;
                break;
            case vertex_layout::PN:
                _type = new PN_Array;
                break;
            case vertex_layout::PNTB:
                _type = new PNTB_Array;
                break;
            case vertex_layout::PNTB_TEX:
                _type = new PNTB_TEX_Array;
                break;
            case vertex_layout::PNTB_SKINNED:
                _type = new PNTB_Skinned_Array;
                break;
            default:
                _type = new ArrayType;
                break;
            }
        }

        size_t size() { return _vertex_size; }

        void* buffer() 
        { 
            return _type->buffer(_vertex_buffer);
        }

        size_t sizeInBytes()
        {
            return _type->sizeInBytes(_vertex_size, _vertex_buffer);
        }

        void initialize(size_t size)
        {
            _type->initialize(size, _vertex_buffer);
            _vertex_size = size;
        }

        Vector3& position(size_t index)
        {
            return _type->position(index, _vertex_buffer);
        }

        Vector3& normal(size_t index)
        {
            return _type->normal(index, _vertex_buffer);
        }

        Vector3& tangent(size_t index)
        {
            return _type->tangent(index, _vertex_buffer);
        }

        Vector3& bitangent(size_t index)
        {
            return _type->bitangent(index, _vertex_buffer);
        }

        Vector2& tex(size_t index, size_t tex_index)
        {
            return _type->tex(index, tex_index, _vertex_buffer);
        }
    };

    using IndexArray = std::vector<uint32>;


    class Mesh: public Resource
    {
    public:
        Mesh();
   //     Mesh(const Mesh& mesh, const CopyOperator& copypo = CopyOperator::SHALLOW_COPY);
        virtual ~Mesh() = default;

        friend class ResourceLoader;

        bool load(const String & res);
        void unload();

        VertexArray& getVertices() { return _vertices; }
        IndexArray& getTriangles() { return _triangles; }
        vertex_layout::Type getLayoutType() { return _layout_type; }
        void setROHandle(Handle handle) { _render_object = handle; }
        Handle getROHandle() { return _render_object; }

    protected:
        VertexArray         _vertices;
        IndexArray          _triangles;
        vertex_layout::Type _layout_type;

        BoundingBox*        _bounding;

        ResourceHandle      _vertex_buffer;
        ResourceHandle      _index_buffer;
        ResourceHandle      _vertex_declaration;

        Handle              _render_object;
    };

    using MeshPtr = RefPtr<Mesh>;

    class MeshManager : public ResourceManager
    {
    public:
        MeshManager();
        ~MeshManager();

        ResourceHandle create(const String& res);

        MeshPtr   getMesh(ResourceHandle handle);
        MeshPtr   getMesh(const String& res);
    };
}



#endif // COMMON_MESH_H