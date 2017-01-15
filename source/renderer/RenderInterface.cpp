#include "RenderInterface.h"

#include "RenderWorld.h"

#ifdef USE_GL
#include "Device/GLRenderDevice.h"
#endif

namespace te
{
    bool RenderInterface::init()
    {
        // init render device here
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
        message->world->render(params);
    }
}