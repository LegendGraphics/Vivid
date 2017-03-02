#ifndef RENDERER_RENDERINTERFACE_H
#define RENDERER_RENDERINTERFACE_H

#include "base\Globals.h"

namespace te
{
    //--------------- Typical Use Case of RenderInterface ---------------//
    //
    // RenderInterface should have an instance in the main engine,
    // it needs to be init() together with the engine to prepare the 
    // run-time RenderDevice.
    //
    // For each frame, create a new RenderWorldMsg and pass it into
    // the run-time instance of RenderInterface.
    //
    //-------------------------------------------------------------------//

    struct RenderWorldMsg
    {
        class RenderWorld* world;
        class RenderCamera* camera;
        class RenderQueueItem* rQueue;
        uint32 numQueue;
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
