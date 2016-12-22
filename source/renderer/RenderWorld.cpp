#include "RenderWorld.h"

#include "renderer/Device/RenderContext.h"
#include "renderer/Device/RenderDevice.h"

namespace te
{
    void RenderWorld::render(RenderParams& params)
    {
        RenderContext* renderContext = (params._device->newContext());

        // culling

        // generate render job package (commands)

        // send render job package to RenderDevice
        params._device->dispatch(renderContext);
    }
}