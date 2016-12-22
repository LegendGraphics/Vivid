#ifndef RENDERER_RENDERWORLD_H
#define RENDERER_RENDERWORLD_H

namespace te
{
    // RenderWorld is the entrance of all "render" aspect things of the game world
    class RenderWorld
    {
    public:

        struct RenderParams
        {
            class RenderDevice* _device;
        };
        void render(RenderParams& params);
    };
}

#endif
