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

// I have no idea about how to write different kinds of vertex with different attributes.
// So now I use the Vertex_PNTB_Skinned as example...
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
        VERTEX_PN,
        VERTEX_PNTB,
        VERTEX_PNTB_SKINNED
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
        typedef int[4] JointIndices;
        typedef float[4] JointWeights;

        Vector3 position;
        Vector3 normal;
        Vector3 tangent;
        Vector3 bitangent;
        JointIndices joint_indices;
        JointWeights joint_weights;
    };


    class MeshRes : public Resource
    {
    public:
        bool load(const char *data, int size);
        void release();

        friend class Mesh;

    protected:
        bool _skinned;
        std::vector<Vertex_PNTB_Skinned> _vertices;
        std::vector<int>    _triangles;
    };


    class Skeleton : public Object
    {
    public:
        Skeleton() = default;
        virtual ~Skeleton() = default;

        void init(SkeletonRes* res);

        void resize(int size);
        SkeletonJoint& getJoint(int index);
        SkeletonJoint& getParentJoint(int index);
        int getJointNum() const{ return _joints.size(); }
    protected:
        SkeletonJoints _joints;
    };


    class Mesh: public Object
    {
    public:
        Mesh() = default;
        Mesh(const Mesh& mesh, const CopyOperator& copypo = CopyOperator::SHALLOW_COPY);
        virtual ~Mesh() = default;

        OBJECT_META_FUNCTION(Mesh);

        void init(MeshRes* res);

        bool isSkinned() const { return _skinned; }

    protected:
        std::vector<Vertex_PNTB_Skinned> _vertices;
        std::vector<int>    _triangles;

        RefPtr<BoundingBox> _bounding;

        bool _skinned;

    };
}



#endif // COMMON_MESH_H