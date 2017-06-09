#include "renderer/RenderInterface.h"

#include "common/Mesh.h"
#include "common/Camera.h"
#include "common/Pipeline.h"

#include "renderer/runtime/RenderObjectManager.h"
#include "renderer/RenderWorld.h"
#include "renderer/runtime/RenderCamera.h"

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

        // init render device
#ifdef USE_GL
        _render_device = new GLRenderDevice;
#else
        _render_device = nullptr;
#endif // USE_GL
        if (!_render_device) return false;

        return true;
    }

    bool RenderInterface::openDevice()
    {
        // init render device here

        if (!_render_device->open()) return false;

        return true;
    }

    void RenderInterface::release()
    {
        delete _render_device; _render_device = nullptr;
        delete _camera; _camera = nullptr;
        _worlds.clear();
    }

    void RenderInterface::registerWorld()
    {
        RenderWorld* render_world = new RenderWorld();
        _worlds.add(render_world);

        _camera = new RenderCamera;
        _camera->setType(CameraData::ORTHOGRAPHIC);
        _camera->setRange(-10, -1000);
        _camera->setViewPort(0, 0, 800, 600);
        setRenderPipeline("forward.pipeline.xml");
    }

    void RenderInterface::unregisterWorld()
    {
        _worlds.clear();
    }

    void RenderInterface::renderWorld()
    {
        RenderWorld::RenderParams params;
        params.device = _render_device;
        params.pipeline = _pipeline.get();
        params.camera = _camera;
        _worlds.getPtr(1)->render(_stream, params);
        releaseStateStream();
    }

    void RenderInterface::updateWorld()
    {
        _worlds.getPtr(1)->update(_stream, _render_device);
        releaseStateStream();
    }

    void RenderInterface::setCamera(CameraState * camera_state)
    {
        Transform view = camera_state->getViewTransform();
        Transform proj = camera_state->getProjectTransform();
        _camera->setMatrix(proj.rawMatrix(), view.rawMatrix());
        _camera->setRange(-10, -1000);
    }

    void RenderInterface::setRenderPipeline(const String& res)
    {
        Pipeline* pipeline = new Pipeline;
        ResourceHandle handle = ResourceMapper::getInstance()->get<PipelineManager>()->create(res);
        _pipeline = ResourceMapper::getInstance()->get<PipelineManager>()->getPipeline(handle);
    }

    /*void RenderInterface::create(Mesh* mesh)
    {
        MeshStreamMsg* msm = new MeshStreamMsg;
        msm->setMsgType(StreamMsg::CREATE);
        msm->setHandle(mesh->getRenderObjectHandle());
        MeshStreamMsg::Data* data = new MeshStreamMsg::Data;
        data->rmo = new RenderMeshObject(mesh);
        msm->feedData(data);
        _stream.push_back(msm);
    }*/

    void RenderInterface::releaseStateStream()
    {
        for (StateStreamMsg* msg : _stream)
        {
            delete msg;
        }
        _stream.clear();
    }
}