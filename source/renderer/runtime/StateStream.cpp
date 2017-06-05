#include "renderer/runtime/StateStream.h"

namespace te
{
    void RenderStreamMsg::process(RenderWorld* rw, RenderContext* rc, RenderResourceContext* rrc)
    {
        switch (_msg_type)
        {
        case MsgType::UPDATE:
            update(rw, rrc);
            break;
        case MsgType::RENDER:
            render(rw, rc);
            break;
        default: break;
        }
    }

    void ResourceStreamMsg::process(RenderObject*& render_object, RenderContext* rc, RenderResourceContext* rrc)
    {
        switch (_msg_type)
        {
        case MsgType::UPDATE:
            update(render_object, rrc);
            break;
        case MsgType::RENDER:
            render(render_object, rc);
            break;
        default: break;
        }
    }
}