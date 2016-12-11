#ifndef COMMON_MESH_H
#define COMMON_MESH_H

#include "Core/common/Object.h"
#include "Core/math/Vector3.h"
#include "Core/math/Vector2.h"

namespace te
{
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

    protected:
        RefPtr<Vec3Array> _vertices;
        RefPtr<Vec3Array> _normals;
        RefPtr<Vec3Array> _colors;
        RefPtr<Vec2Array> _uvs;
    };
}



#endif // COMMON_MESH_H