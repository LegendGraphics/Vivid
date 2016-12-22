#ifndef RENDERER_RENDERINTERFACE_H
#define RENDERER_RENDERINTERFACE_H

namespace te
{
    struct RenderWorldMsg
    {
        class RenderWorld* world;
    };

    class RenderInterface
    {
    public:
        bool init();
        void release();

        void renderWorld(RenderWorldMsg* message);

    private:
        class GLRenderDevice* _renderDevice;
    };
}

#endif
