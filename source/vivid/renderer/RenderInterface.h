#ifndef RENDERER_RENDER_INTERFACE_H
#define RENDERER_RENDER_INTERFACE_H

#include "vivid/base/Types.h"
#include "vivid/base/Singleton.hpp"
#include "vivid/common/Pipeline.h"
#include "vivid/renderer/resource/HandleObjects.hpp"
#include "vivid/renderer/runtime/StateStream.h"

namespace te
{
    //--------------- Typical Use Case of RenderInterface ---------------//
    //
    // RenderInterface should have an instance in the main engine,
    // it needs to be init() together with the engine to prepare the 
    // run-time RenderDevice.
    //
    // For each frame, fill the StateStream and trigger an update or render
    //
    //-------------------------------------------------------------------//

    class Mesh;
    class CameraState;
    class RenderCamera;
    class RenderWorld;

    class RenderInterface : public Singleton<RenderInterface>
    {
    public:
        bool init();
        bool openDevice();
        void release();

        // hard code, init one world, camera and pipeline
        void registerWorld();
        void unregisterWorld();

        void renderWorld();
        void updateWorld();

        void setCamera(CameraState* camera_state);
        void setRenderPipeline(const String& res);

        StateStream _stream;

        void releaseStateStream();

    private:
        class RenderDevice* _render_device;

        using Worlds = HandleObjects<RenderWorld>;
        Worlds _worlds;

        RenderCamera*   _camera;
        PipelinePtr     _pipeline;
    };
}

#endif
