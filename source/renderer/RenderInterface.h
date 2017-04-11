#ifndef RENDERER_RENDERINTERFACE_H
#define RENDERER_RENDERINTERFACE_H

#include "base/Types.h"
#include "base/Singleton.hpp"

//#include "RenderWorld.h"
//#include "Resource/RenderResourceGenerator.h"

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
        class PipelineResource* pipeline;
        class RenderWorld* world;
        class RenderCamera* camera;
        class RenderQueueItem* rQueue;
        uint32 numQueue;
    };

    struct RenderResourceMsg
    {
        class RenderResourceGenerator* generator;
        class ResourceStreamItem* rQueue;
        uint32 numQueue;
    };

    union RenderMsg {
        RenderWorldMsg rwm;
        RenderResourceMsg rrm;
    };

    class RenderInterface : public Singleton<RenderInterface>
    {
    public:
        bool init();
        void release();

        void renderWorld(RenderMsg* message);
        void generateResource(RenderMsg* message);

        class VertexLayoutPredefinition* getVertexDeclarationDefinition();

        // engine side should allocate RenderObject and RenderResource
        // from RenderInterface, so that header files won't explode there.
        // And Engine "new" Render things but Render delete them won't happen.
        //template <class T>
        //RenderObject* createRenderObject();
        //template <class T>
        //RenderResource* createRenderResource();

    private:
        class RenderDevice* _renderDevice;
    };
}

#endif
