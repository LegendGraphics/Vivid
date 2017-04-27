#ifndef RENDERER_RENDERWORLD_H
#define RENDERER_RENDERWORLD_H

#include "renderer/resource/HandleObjects.hpp"
#include "renderer/resource/RenderObject.h"

namespace te
{
    struct RenderQueueItem
    {
        RenderObject  *node;
        float      sortKey;

        RenderQueueItem() {}
        RenderQueueItem(float sortKey, RenderObject *node)
            : node(node), sortKey(sortKey) {}
    };
    typedef std::vector< RenderQueueItem > RenderQueue;

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
            class PipelineResource* _pipelineRes;
            class RenderCamera* _camera;
            RenderQueue _renderQueue;
        };
        void render(RenderParams& params);
        void update();

    protected:
        HandleObjects<RenderObject> _objects;
    };
}

#endif
