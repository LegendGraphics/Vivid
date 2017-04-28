#ifndef RENDERER_RENDERINTERFACE_H
#define RENDERER_RENDERINTERFACE_H

#include "base/Types.h"
#include "base/Singleton.hpp"
#include "renderer/resource/HandleObjects.hpp"
#include "renderer/runtime/StateStream.h"

// These header files will be moved in the future
#include "renderer/RenderWorld.h"
#include "renderer/resource/RenderResourceGenerator.h"
#include "renderer/runtime/RenderCamera.h"
#include "renderer/resource/RenderMeshObject.h"
#include "renderer/resource/PipelineResource.h"
#include "renderer/resource/RenderResource.h"
#include "renderer/resource/RenderResourceManager.h"

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

    class Mesh;
    class CameraState;

    struct RenderWorldMsg
    {
        class PipelineResource* pipeline;
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
        bool openDevice();
        void release();

        void registerWorld();
        void unregisterWorld();

        void renderWorld(RenderMsg* message);
        void generateResource(RenderMsg* message);
        void renderWorld();
        void updateWorld();
        void setCamera(CameraState* camera_state);

        class VertexLayoutPredefinition* getVertexDeclarationDefinition();

        // engine side should allocate RenderObject and RenderResource
        // from RenderInterface, so that header files won't explode there.
        // And Engine "new" Render things but Render delete them won't happen.
        //template <class T>
        //RenderObject* createRenderObject();
        //template <class T>
        //RenderResource* createRenderResource();

        void create(Mesh* mesh);

        StateStream _stream;

        void releaseStateStream();

    private:
        class RenderDevice* _renderDevice;

        using Worlds = HandleObjects<RenderWorld>;
        Worlds _worlds;

        RenderCamera* _camera;
        PipelineResource* _pipelien_res;
    };
}

#endif
