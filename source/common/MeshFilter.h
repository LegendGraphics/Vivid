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
        MeshFilter(const String& res);
        bool load(const String& res);
        MeshPtr getMesh();

    protected:
        ResourceHandle  _mes_handle;
    };
}


#endif // COMMON_MESH_FILTER_H