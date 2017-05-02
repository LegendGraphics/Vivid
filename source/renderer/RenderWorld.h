#ifndef RENDERER_RENDERWORLD_H
#define RENDERER_RENDERWORLD_H

#include "renderer/resource/HandleObjects.hpp"
#include "renderer/resource/RenderObject.h"

#include "renderer/runtime/StateStream.h"

namespace te
{
    // RenderWorld is the entrance of all "render" aspect things of the game world
    class RenderWorld : public RenderObject
    {
    public:
        static RenderObject::Type TYPE;

        RenderWorld();
        ~RenderWorld();

        struct RenderParams
        {
            class RenderDevice* _device;
            class Pipeline*     _pipeline;
            class RenderCamera* _camera;
        };
        void render(StateStream& stream, RenderParams& params);
        void update(StateStream& stream, RenderDevice* device);

    protected:
        void renderKernel(StateStream& stream, RenderParams& params, RenderContext* rContext);

    protected:
        HandleObjects<RenderObject> _objects;
    };
}

#endif
