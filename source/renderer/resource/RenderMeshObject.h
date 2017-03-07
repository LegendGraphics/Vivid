#ifndef RENDERER_RENDERMESHOBJECT_H
#define RENDERER_RENDERMESHOBJECT_H

#include "renderer/resource/RenderObject.h"

namespace te
{
    class RenderContext;
    class RenderDevice;
    class RenderCamera;

    class RenderMeshObject : public RenderObject
    {
    public:
        static RenderObject::Type TYPE;

        RenderMeshObject();
        ~RenderMeshObject();

        void render(RenderContext* context, RenderCamera* camera, RenderDevice* device);

    private:
        uint32  _shader_object_handle;
        uint32  _numIndices; // temporary to put it here
        uint32  _vaoHandle;
        // TODO: consider move this to a GeometryObject? Shader belongs to Material, Material
        // belongs to Mesh, Geometry also belongs to Mesh
    };
}

#endif
