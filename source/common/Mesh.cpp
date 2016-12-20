#include "common/Mesh.h"

namespace te
{
    void Mesh::setVertexArray(const std::vector<Vertex>& vertices)
    {
        _vertices = vertices;
    }

    void Mesh::setTriangleArray(const std::vector<int>& triangles)
    {
        _triangles = triangles;
    }

    int Mesh::getVertexCount() const 
    {
        return _vertices.size();
    }

    int Mesh::getIndexCount() const
    {
        return _triangles.size();
    }

}