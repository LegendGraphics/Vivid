#ifndef RENDERER_RENDER_WORLD_H
#define RENDERER_RENDER_WORLD_H

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
            class RenderDevice* device;
            class Pipeline*     pipeline;
            class RenderCamera* camera;
        };

        void update(StateStream& stream, RenderDevice* device);
        void render(StateStream& stream, RenderParams& params);

        auto& getRenderObject() { return _objects; }

    protected:
        void renderKernel(StateStream& stream, RenderParams& params, RenderContext* render_context);

    protected:
        HandleObjects<RenderObject> _objects;
    };
}

#endif
