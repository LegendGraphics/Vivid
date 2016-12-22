#include "RenderDevice.h"

#include "RenderContext.h"

namespace te
{
    RenderDevice::RenderDevice()
    {

    }

    RenderDevice::~RenderDevice()
    {
        for (RenderContext* i : _render_contexts)
        {
            delete i;
        }
        _render_contexts.erase(_render_contexts.begin(), _render_contexts.end());
    }

    RenderContext* RenderDevice::newContext()
    {
        _render_contexts.push_back(new RenderContext);
        return _render_contexts.back();
    }

    void RenderDevice::releaseContext(RenderContext* context)
    {
    }
}