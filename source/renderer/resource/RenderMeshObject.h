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
        uint32 _shader_object_handle;
    };
}

#endif
