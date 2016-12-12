#ifndef COMMON_MESH_FILTER_H
#define COMMON_MESH_FILTER_H

namespace te
{
    class MeshFilter: public Component
    {
    public:
        inline Mesh* getMesh() { return _mesh; }

    protected:
        RefPtr<Mesh> _mesh;
    };
}


#endif // COMMON_MESH_FILTER_H