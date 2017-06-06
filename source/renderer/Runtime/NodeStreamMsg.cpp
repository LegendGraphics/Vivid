#include "renderer/runtime/StateStream.h"
#include "renderer/device/RenderContext.h"
#include "renderer/RenderWorld.h"
#include "common/Uploader.h"

namespace te
{
    NodeStreamMsg::NodeStreamMsg(MsgType type, void* data)
        :RenderStreamMsg(type, data)
    {
        Node* node = static_cast<Node*>(_data);
        node->getComponent<UploadToRender>()->assembleResourceMsg(_resources);
    }

    NodeStreamMsg::~NodeStreamMsg()
    {
    }

    void NodeStreamMsg::update(RenderWorld*& rw, RenderResourceContext* rrc)
    {
        auto& render_objects = rw->getRenderObject();
        for (ResourceStreamMsg* msg : _resources)
        {
            ResourceStreamMsg::MsgType type = msg->getMsgType();
            if (ResourceStreamMsg::UPDATE == type)
            {
                Handle handle = msg->getHandle();
                RenderObject* ro = nullptr;
                if (!render_objects.has(handle))
                {
                    ro = msg->createRenderObject();
                    Handle ro_handle = render_objects.add(ro);
                    msg->setHandle(ro_handle);
                }
                else ro = render_objects.getPtr(handle);
                msg->process(ro, nullptr, rrc);
            }
        }
    }

    void NodeStreamMsg::render(RenderWorld*& rw, RenderContext* rc)
    {
        // 1. set render status for the gpu resources
        // 2. set other render status of data

        auto& render_objects = rw->getRenderObject();
        for (ResourceStreamMsg* msg : _resources)
        {
            ResourceStreamMsg::MsgType type = msg->getMsgType();
            if (ResourceStreamMsg::RENDER == type)
            {
                Handle handle = msg->getHandle();
                RenderObject* ro = render_objects.getPtr(handle);
                msg->process(ro, rc, nullptr);
            }
        }

        // other render status: uniforms, position...
        setShaderUniforms(rc);
        setSpaceState(rc);
        setCameraState(rc);

        // draw command
        setDraw(rc);
    }

    void NodeStreamMsg::setShaderUniforms(RenderContext* rc)
    {
        RenderContext::ShaderCmdStream* scs = new RenderContext::ShaderCmdStream;

        Node* node = static_cast<Node*>(_data);
        scs->uniforms = node->getComponent<UploadToRender>()->getShaderUniforms();
        
        RenderContext::Command set_shader = { 0, (void*)scs, RenderContext::CommandType::BIND_SHADER_OBJECT };
        rc->commands().push_back(set_shader);
    }

    void NodeStreamMsg::setSpaceState(RenderContext* rc)
    {
        RenderContext::SpaceCmdStream* scs = new RenderContext::SpaceCmdStream;

        Node* node = static_cast<Node*>(_data);
        auto& space_state = node->getComponent<UploadToRender>()->getSpaceState();
        scs->world_mat = space_state.getSpaceTransform().rawMatrix();

        RenderContext::Command set_space = { 0, (void*)scs, RenderContext::CommandType::SET_SPACE };
        rc->commands().push_back(set_space);
    }

    void NodeStreamMsg::setCameraState(RenderContext* rc)
    {
        RenderContext::CameraCmdStream* ccs = new RenderContext::CameraCmdStream;

        Node* node = static_cast<Node*>(_data);
        auto& camera_state = node->getComponent<UploadToRender>()->getCameraState();
        ccs->view_port = camera_state.getViewPort();
        ccs->proj_mat = camera_state.getProjectTransform().rawMatrix();
        ccs->view_mat = camera_state.getViewTransform().rawMatrix();

        RenderContext::Command set_camera = { 0, (void*)ccs, RenderContext::CommandType::SET_CAMERA };
        rc->commands().push_back(set_camera);
    }


    void NodeStreamMsg::setDraw(RenderContext* rc)
    {
        RenderContext::Command draw = { 0, nullptr, RenderContext::CommandType::RENDER };
        rc->commands().push_back(draw);
    }
}