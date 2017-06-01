#include "renderer/resource/RenderCameraObject.h"

#include "renderer/device/RenderContext.h"
#include "renderer/device/RenderDevice.h"
#include "renderer/runtime/RenderCamera.h"
#include "renderer/resource/RenderResourceContext.h"
#include "renderer/resource/ResourceStream.h"
#include "renderer/runtime/StateStream.h"



namespace te
{
    RenderObject::Type RenderCameraObject::TYPE = RenderObject::NOT_INITIALIZED;

    RenderCameraObject::RenderCameraObject()
        :_camera_handle(0xFFFFFFFF)
    {
    }

    RenderCameraObject::~RenderCameraObject()
    {
    }

    void RenderCameraObject::create(RenderResourceContext* context)
    {
    }

    void RenderCameraObject::update(RenderResourceContext* context)
    {
        // no gpu resource allocated 
    }

    void RenderCameraObject::render(RenderContext* context)
    {
        setCamera(context);
    }

    void RenderCameraObject::parseStreamMsg(StreamMsg* msg)
    {
        Camera* camera = static_cast<Camera*>(msg->getData());
        CameraState* cs = camera->getComponent<CameraState>();
        
        _view_port = cs->getViewPort();
        _proj_mat = cs->getProjectTransform().rawMatrix();
        _view_mat = cs->getViewTransform().rawMatrix();
    }

    void RenderCameraObject::setCamera(RenderContext* context)
    {
        RenderContext::CameraCmdStream* ccs = new RenderContext::CameraCmdStream;
        ccs->view_port = _view_port;
        ccs->proj_mat = _proj_mat;
        ccs->view_mat = _view_mat;
        RenderContext::Command set_camera = { 0, (void*)ccs, RenderContext::CommandType::UPDATE_CAMERA };
        context->commands().push_back(set_camera);
    }

}

