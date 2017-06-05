#include "renderer/runtime/StateStream.h"
#include "renderer/device/RenderContext.h"
#include "common/Uploader.h"

namespace te
{
    CameraStreamMsg::CameraStreamMsg(MsgType type, void* data)
        :RenderStreamMsg(type, data)
    {
    }

    CameraStreamMsg::~CameraStreamMsg()
    {
    }

    void CameraStreamMsg::update(RenderWorld*& rw, RenderResourceContext* rrc)
    {
        // no gpu resource needed for camera now
    }

    void CameraStreamMsg::render(RenderWorld*& rw, RenderContext* rc)
    {
        setCameraState(rc);
    }

    void CameraStreamMsg::setCameraState(RenderContext* rc)
    {
        RenderContext::CameraCmdStream* ccs = new RenderContext::CameraCmdStream;
        
        Camera* node = static_cast<Camera*>(_data);
        auto& camera_state = node->getComponent<UploadToRender>()->getCameraState();
        ccs->view_port = camera_state.getViewPort();
        ccs->proj_mat = camera_state.getProjectTransform().rawMatrix();
        ccs->view_mat = camera_state.getViewTransform().rawMatrix();

        RenderContext::Command set_camera = { 0, (void*)ccs, RenderContext::CommandType::SET_CAMERA };
        rc->commands().push_back(set_camera);
    }
}