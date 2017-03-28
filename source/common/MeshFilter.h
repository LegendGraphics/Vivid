#ifndef COMMON_MESH_FILTER_H
#define COMMON_MESH_FILTER_H

#include "common/Component.h"
#include "common/Mesh.h"

namespace te
{
    class MeshFilter: public Component
    {
    public:
        MeshFilter();
        bool load(const std::string& res);
        Mesh* getMesh();

    protected:
        ResourceHandle  _mes_handle;
    };
}


#endif // COMMON_MESH_FILTER_H