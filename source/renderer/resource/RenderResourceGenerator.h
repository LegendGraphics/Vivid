#ifndef RENDERER_RENDERRESOURCEGENERATOR_H
#define RENDERER_RENDERRESOURCEGENERATOR_H

#include "RenderResource.h"

namespace te
{
    class RenderResourceGenerator
    {
    public:

        struct RenderResourceParams
        {
            class RenderDevice* _device;
            ResourceStreamQueue _resourceQueue;
        };
        void allocResource(RenderResourceParams& params);
        void deallocResource(RenderResourceParams& params);
    };
}

#endif
