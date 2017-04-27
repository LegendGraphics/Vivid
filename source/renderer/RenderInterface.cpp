#include "RenderInterface.h"
#include "RenderWorld.h"
#include "resource/RenderResourceGenerator.h"
#include "runtime/RenderObjectManager.h"

#ifdef USE_GL
#include "renderer/device/GLRenderDevice.h"
#endif

namespace te
{
    RenderInterface* Singleton<RenderInterface>::_singleton = nullptr;

    bool RenderInterface::init()
    {
        // register render objects here
        render_object::register_objects();

        // init render device here
#ifdef USE_GL
        _renderDevice = new GLRenderDevice;
#else
        _renderDevice = nullptr;
#endif // USE_GL
        if (!_renderDevice || !_renderDevice->open()) return false;

        return true;
    }

    void RenderInterface::release()
    {
        delete _renderDevice; _renderDevice = nullptr;
    }

    void RenderInterface::renderWorld(RenderMsg* message)
    {
        // message should contain some state object camera, viewport
        RenderWorldMsg& msg = message->rwm;
        RenderWorld::RenderParams params;
        params._device = _renderDevice;
        params._pipelineRes = msg.pipeline;
        params._camera = msg.camera;
        params._renderQueue = RenderQueue(msg.rQueue, msg.rQueue + msg.numQueue);
        msg.world->render(params);

        // For now
        // delete world, pipelineRes, camera here
        // and RenderObject in RenderQueue
        delete msg.pipeline;
        delete msg.camera;
        delete msg.world;
        for (uint32 i = 0; i < msg.numQueue; ++i)
        {
            delete msg.rQueue[i].node;
        }
        delete[] msg.rQueue;
    }

    void RenderInterface::generateResource(RenderMsg* message)
    {
        const RenderResourceMsg& msg = message->rrm;
        RenderResourceGenerator::RenderResourceParams params;
        params._device = _renderDevice;
        params._resourceQueue = ResourceStreamQueue(msg.rQueue, msg.rQueue + msg.numQueue);
        msg.generator->allocResource(params);

        // no need to delete stream and render resource insde each item
        delete msg.generator;
        delete[] msg.rQueue;
    }
    VertexLayoutPredefinition * RenderInterface::getVertexDeclarationDefinition()
    {
        return _renderDevice->getVertexDeclarationDefinition();
    }
}