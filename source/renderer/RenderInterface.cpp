#include "RenderInterface.h"
#include "RenderWorld.h"
#include "resource//RenderResourceGenerator.h"

#ifdef USE_GL
#include "renderer/Device/GLRenderDevice.h"
#endif

#include "renderer/Runtime/RenderObjectManager.h"

namespace te
{
    RenderInterface* RenderInterface::_renderInterface = nullptr;
    RenderInterface* RenderInterface::get()
    {
        if (!_renderInterface)
        {
            _renderInterface = new RenderInterface();
        }

        return _renderInterface;
    }

    bool RenderInterface::init()
    {
        // init render device here
#ifdef USE_GL
        _renderDevice = new GLRenderDevice;
#else
        _renderDevice = nullptr;
#endif // USE_GL
        if (!_renderDevice->open()) return false;
        
        // init render resource here
        _renderObjectManager = new class RenderObjectManager;
        _renderObjectManager->register_objects();

        return true;
    }

    void RenderInterface::release()
    {
        delete _renderDevice; _renderDevice = nullptr;
        delete _renderObjectManager; _renderObjectManager = nullptr;
    }

    void RenderInterface::renderWorld(RenderMsg* message)
    {
        // message should contain some state object camera, viewport
        const RenderWorldMsg& msg = message->rwm;
        RenderWorld::RenderParams params;
        params._device = _renderDevice;
        params._pipelineRes = msg.pipeline;
        params._camera = msg.camera;
        params._renderQueue = RenderQueue(msg.rQueue, msg.rQueue + msg.numQueue);
        msg.world->render(params);
    }

    void RenderInterface::generateResource(RenderMsg* message)
    {
        const RenderResourceMsg& msg = message->rrm;
        RenderResourceGenerator::RenderResourceParams params;
        params._device = _renderDevice;
        params._resourceQueue = ResourceStreamQueue(msg.rQueue, msg.rQueue + msg.numQueue);
        msg.generator->allocResource(params);
    }
}