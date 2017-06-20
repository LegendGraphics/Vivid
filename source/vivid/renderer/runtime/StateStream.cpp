#include "vivid/renderer/runtime/StateStream.h"
#include "vivid/renderer/RenderWorld.h"

namespace vivid
{
    void ResourceStreamMsg::process(RenderContext* rc, RenderResourceContext* rrc, RenderWorld* rw)
    {
        RenderObject* ro = rw->getRenderObject(getHandle());
        if (!ro)
        {
            ro = createRenderObject();
            setHandle(rw->addRenderObject(ro));
        }

        switch (_type)
        {
        case stream_message::UPDATE:
            // need assert here to check rrc is not null
            update(ro, rrc);
            break;
        case stream_message::RENDER:
            // need assert here to check rc is not null
            render(ro, rc);
            break;
        default: break;
        }
    }

    void DataStreamMsg::process(RenderContext* rc, RenderResourceContext* rrc, RenderWorld* rw)
    {
        // do whatever you want here
        //render(render_object, rc);
    }
}