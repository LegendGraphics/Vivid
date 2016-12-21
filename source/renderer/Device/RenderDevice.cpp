#include "RenderDevice.h"

namespace te
{
    RenderDevice::RenderDevice()
    {

    }

    RenderDevice::~RenderDevice()
    {

    }

    RenderContext* RenderDevice::newContext()
    {
        return nullptr;
    }

    void RenderDevice::releaseContext(RenderContext* context)
    {

    }
}