#include "StateStream.h"

#include "renderer/resource/RenderMeshObject.h"

namespace te
{
    void StreamMsg::process(RenderObject*& render_object, RenderContext* rc, RenderResourceContext* rrc)
    {
        switch (_type)
        {
        case MsgType::CREATE:
            create(render_object, rrc);
            break;
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