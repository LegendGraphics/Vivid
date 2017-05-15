#ifndef COMMON_MESH_RENDER_H
#define COMMON_MESH_RENDER_H

#include "common/Component.h"
#include "common/Mesh.h"
#include "common/Material.h"

namespace te
{
    // containing render resource: mesh, material, light...
    class MeshRender: public Component
    {
    public:
        MeshRender();
        MeshRender(const String& mesh_res);

        bool loadMesh(const String& res);
        bool loadMaterial(const String& res);
       // bool loadLight(const String& res);

        MeshPtr     getMesh();
        MaterialPtr getMaterial();
        //LightPtr    getLight();

    protected:
        ResourceHandle  _mes_handle;
        ResourceHandle  _mat_handle;
    };
}


#endif // COMMON_MESH_RENDER_H