#ifndef COMMON_MESH_FILTER_H
#define COMMON_MESH_FILTER_H

#include "common/Component.h"
#include "common/Mesh.h"

namespace te
{
    class MeshFilter: public Component
    {
    public:
        inline Mesh* getMesh() { return _mesh.get(); }

    protected:
        RefPtr<Mesh> _mesh;
    };
}


#endif // COMMON_MESH_FILTER_H