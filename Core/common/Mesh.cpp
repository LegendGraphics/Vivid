#include "Core/common/Mesh.h"

namespace te
{
    void Mesh::setVertexArray(const Vec3Array& vertices)
    {
        _vertices = vertices;
    }

    void Mesh::setNormalArray(const Vec3Array& normals)
    {
        _normals = normals;
    }

    void Mesh::setColorArray(const Vec3Array& colors)
    {
        _colors = colors;
    }

    void Mesh::setUVArray(const Vec2Array& uvs)
    {
        _uvs = uvs;
    }


}