#ifndef RENDERER_RENDERDEVICE_H
#define RENDERER_RENDERDEVICE_H

#include "base\Globals.h"

namespace te
{
    class RenderContext;

    class RenderDevice
    {
    public:
        RenderDevice();
        virtual ~RenderDevice();

        virtual bool open() = 0;
        virtual void close() = 0;

        virtual RenderContext* newContext();
        virtual void releaseContext(RenderContext* context);
        // RenderDevice will be called in the render thread loop and dispatch the 
        // commands to RenderContext, RenderContext will call actual Graphic API
        virtual void dispatch(RenderContext* context_) = 0;

    private:
        typedef std::vector<RenderContext*> RenderContexts;
        RenderContexts _render_contexts;
    };
}

#endif
