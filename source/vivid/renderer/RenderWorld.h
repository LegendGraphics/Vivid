#ifndef RENDERER_RENDER_WORLD_H
#define RENDERER_RENDER_WORLD_H

#include "vivid/renderer/resource/HandleObjects.hpp"
#include "vivid/renderer/runtime/RenderObject.h"
#include "vivid/renderer/runtime/StateStream.h"

namespace vivid
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

        RenderObject* getRenderObject(Handle handle);
        Handle        addRenderObject(RenderObject* ro);

    protected:
        void renderKernel(StateStream& stream, RenderParams& params, RenderContext* render_context);

    protected:
        HandleObjects<RenderObject> _objects;
    };
}

#endif
