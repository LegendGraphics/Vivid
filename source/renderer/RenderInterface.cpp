#include "RenderInterface.h"
#include "renderer/Device/GLRenderDevice.h"
#include "RenderWorld.h"
#include "renderer/Resource/PipelineResource.h"

#ifdef USE_GL
#include "Device/GLRenderDevice.h"
#endif

namespace te
{
    bool RenderInterface::init()
    {
        // init render device here
        _renderDevice = new GLRenderDevice;
        if (!_renderDevice->open()) return false;
        // init render resource here

        return true;
    }

    void RenderInterface::release()
    {
        delete _renderDevice; _renderDevice = nullptr;
    }

    void RenderInterface::renderWorld(RenderWorldMsg* message)
    {
        // message should contain some state object camera, viewport
        RenderWorld::RenderParams params;
        params._device = _renderDevice;
        params._pipelineRes = message->pipeline;
        params._camera = message->camera;
        params._renderQueue = RenderQueue(message->rQueue, message->rQueue + message->numQueue);
        message->world->render(params);
    }
}