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
    enum class VertexAttribute
    {
        TE_VERTEX_POSITION =        1 << 0,
        TE_VERTEX_NORMAL =          1 << 1,
        TE_VERTEX_TANGENT =         1 << 2,
        TE_VERTEX_BITANGENT =       1 << 3,
        TE_VERTEX_SKINNED =         1 << 4,
        TE_VERTEX_TEXCOORD0 =       1 << 5,
        TE_VERTEX_TEXCOORD1 =       1 << 6,    
    };

    enum class VertexType
    {
        VERTEX_P,
        VERTEX_PN,
        VERTEX_PNTB,
        VERTEX_PNTB_SKINNED
    };

    /*struct VertexAttributes
    {

    };*/

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

    using Vertex_P_Array = std::vector<Vertex_P>;
    using Vertex_PN_Array = std::vector<Vertex_PN>;
    using Vertex_PNTB_Array = std::vector<Vertex_PNTB>;
    using Vertex_PNTB_Skinned_Array = std::vector<Vertex_PNTB_Skinned>;

    struct VertexArray
    {
        union Array
        {
            Vertex_P_Array              p_array;
            Vertex_PN_Array             pn_array;
            Vertex_PNTB_Array           pntb_array;
            Vertex_PNTB_Skinned_Array   pntb_skinned_array;
        };

        VertexType  type;
        Array       varray;

        Vertex_P_Array& toVertex_P_Array() { return varray.p_array; }
        Vertex_PN_Array& toVertex_PN_Array() { return varray.pn_array; }
        Vertex_PNTB_Array& toVertex_PNTB_Array() { return varray.pntb_array; }
        Vertex_PNTB_Skinned_Array& toVertex_PNTB_Skinned_Array() { return varray.pntb_skinned_array; }
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