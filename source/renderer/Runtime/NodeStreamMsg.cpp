#include "renderer/runtime/StateStream.h"
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

        // other render status: position...

    }
}