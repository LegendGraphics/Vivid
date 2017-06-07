#include "renderer/runtime/StateStream.h"

namespace te
{
    void ResourceStreamMsg::process(RenderObject*& render_object, RenderContext* rc, RenderResourceContext* rrc)
    {
        switch (_type)
        {
        case ActionType::UPDATE:
            update(render_object, rrc);
            break;
        case ActionType::RENDER:
            render(render_object, rc);
            break;
        default: break;
        }
    }

    void DataStreamMsg::process(RenderObject*& render_object, RenderContext* rc, RenderResourceContext* rrc)
    {
        render(render_object, rc);
    }
}