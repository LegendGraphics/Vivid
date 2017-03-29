#ifndef RENDERER_RENDERINTERFACE_H
#define RENDERER_RENDERINTERFACE_H

#include "base/Types.h"

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

    class RenderInterface
    {
    public:
        static RenderInterface* get();

        bool init();
        void release();

        void renderWorld(RenderMsg* message);
        void generateResource(RenderMsg* message);

        class VertexDeclaration* getVertexDeclarationDefinition();

        // engine side should allocate RenderObject and RenderResource
        // from RenderInterface, so that header files won't explode there.
        // And Engine "new" Render things but Render delete them won't happen.
        //template <class T>
        //RenderObject* createRenderObject();
        //template <class T>
        //RenderResource* createRenderResource();

    protected:
        RenderInterface() = default; // not implemented
    private:
        static RenderInterface* _renderInterface;
        class GLRenderDevice* _renderDevice;
        class RenderObjectManager* _renderObjectManager;
        class VertexDeclaration* _vertexDeclaration; // to get the predefined vertex declaration in this render
    };
}

#endif
