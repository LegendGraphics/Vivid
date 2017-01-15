#ifndef RENDERER_RENDERWORLD_H
#define RENDERER_RENDERWORLD_H

namespace te
{
    class RenderCamera;
    class PipelineResource;

    // RenderWorld is the entrance of all "render" aspect things of the game world
    class RenderWorld
    {
    public:

        struct RenderParams
        {
            class RenderDevice* _device;
            PipelineResource* _pipelineRes;
            RenderCamera* _camera;
        };
        void render(RenderParams& params);

    private:
        //ShaderObject _defaultColorShader;
    };
}

#endif
