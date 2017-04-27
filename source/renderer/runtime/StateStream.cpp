#include "StateStream.h"

namespace te
{
    void StreamMsg::process(RenderObject * render_object)
    {
        switch (_type)
        {
        case MsgType::CREATE:
            create(render_object);
            break;
        case MsgType::UPDATE:
            update(render_object);
            break;
        case MsgType::RENDER:
            render(render_object);
            break;
        default: break;
        }
    }

    void MeshStreamMsg::create(RenderObject * render_object)
    {
    }
    void MeshStreamMsg::update(RenderObject * render_object)
    {
    }
    void MeshStreamMsg::render(RenderObject * render_objcet)
    {
    }
}