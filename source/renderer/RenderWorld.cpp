#include "RenderWorld.h"

#include "base/RefPtr.hpp"
#include "renderer/Device/RenderContext.h"

namespace te
{
    void RenderWorld::render(RenderParams& params)
    {
        RefPtr<RenderContext> renderContext(params._device->newContext());

        // culling

        // generate render job package (commands)

        // send render job package to RenderDevice
        params._device->dispatch()
    }
}