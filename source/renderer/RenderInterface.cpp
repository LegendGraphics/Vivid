#include "RenderInterface.h"
#include "RenderWorld.h"
#include "resource/RenderResourceGenerator.h"
#include "runtime/RenderObjectManager.h"

#include "common/Mesh.h"
#include "common/Camera.h"
#include "renderer/runtime/StateStream.h"

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

#ifdef USE_GL
        _renderDevice = new GLRenderDevice;
#else
        _renderDevice = nullptr;
#endif // USE_GL

        if (!_renderDevice) return false;

        return true;
    }

    bool RenderInterface::openDevice()
    {
        // init render device here

        if (!_renderDevice->open()) return false;

        return true;
    }

    void RenderInterface::release()
    {
        delete _renderDevice; _renderDevice = nullptr;
        delete _camera; _camera = nullptr;
        delete _pipelien_res; _pipelien_res = nullptr;
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
        _pipelien_res = new PipelineResource();
        _pipelien_res->load("forward.pipeline.xml");
    }

    void RenderInterface::unregisterWorld()
    {
        _worlds.clear();
    }

    void RenderInterface::renderWorld(RenderMsg* message)
    {
        // message should contain some state object camera, viewport
        RenderWorldMsg& msg = message->rwm;
        RenderWorld::RenderParams params;
        params._device = _renderDevice;
        params._pipelineRes = msg.pipeline;
        params._camera = msg.camera;

        // For now
        // delete world, pipelineRes, camera here
        // and RenderObject in RenderQueue
        delete msg.pipeline;
        delete msg.camera;
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

    void RenderInterface::renderWorld()
    {
        RenderWorld::RenderParams params;
        params._device = _renderDevice;
        params._pipelineRes = _pipelien_res;
        params._camera = _camera;
        _worlds.getPtr(1)->render(_stream, params);
        releaseStateStream();
    }

    void RenderInterface::updateWorld()
    {
        _worlds.getPtr(1)->update(_stream, _renderDevice);
        releaseStateStream();
    }

    void RenderInterface::setCamera(CameraState * camera_state)
    {
        Transform view = camera_state->getViewTransform();
        Transform proj = camera_state->getProjectTransform();
        _camera->setMatrix(proj.rawMatrix(), view.rawMatrix());
        _camera->setRange(-10, -1000);
    }

    VertexLayoutPredefinition * RenderInterface::getVertexDeclarationDefinition()
    {
        return _renderDevice->getVertexDeclarationDefinition();
    }

    void RenderInterface::create(Mesh* mesh)
    {
        MeshStreamMsg* msm = new MeshStreamMsg;
        msm->setMsgType(StreamMsg::CREATE);
        msm->setHandle(mesh->getRenderObjectHandle());
        MeshStreamMsg::Data* data = new MeshStreamMsg::Data;
        data->rmo = new RenderMeshObject(mesh);
        msm->feedData(data);
        _stream.push_back(msm);
    }

    void RenderInterface::releaseStateStream()
    {
        for (StreamMsg* msg : _stream)
        {
            delete msg;
        }
        _stream.clear();
    }
}