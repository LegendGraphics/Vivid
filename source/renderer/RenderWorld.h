#ifndef RENDERER_RENDERWORLD_H
#define RENDERER_RENDERWORLD_H

#include "base/Globals.h"

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

    protected:
        void createPrimitives(RenderDevice* device);

    private:
        //ShaderObject _defaultColorShader;

        //uint32  _vbCube, _ibCube, _vbSphere, _ibSphere;
        //uint32  _vbCone, _ibCone, _vbFSPoly;
    };
}

#endif
