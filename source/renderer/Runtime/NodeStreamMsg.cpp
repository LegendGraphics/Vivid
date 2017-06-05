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
    }

    void NodeStreamMsg::setShaderUniforms(RenderContext* rc)
    {
        RenderContext::ShaderCmdStream* scs = new RenderContext::ShaderCmdStream;

        Node* node = static_cast<Node*>(_data);
        auto& uniform_map = node->getComponent<UploadToRender>()->getUniformValueMap();
        for (auto& uniform : uniform_map)
        {
            scs->uniforms.setUniform(uniform.first, &uniform.second.data[0], uniform.second.size, uniform.second.type);
        }

        RenderContext::Command set_shader = { 0, (void*)scs, RenderContext::CommandType::BIND_SHADER_OBJECT };
        rc->commands().push_back(set_shader);
    }
}