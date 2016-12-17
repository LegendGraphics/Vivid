#ifndef RENDERER_VKRENDERDEVICE_H
#define RENDERER_VKRENDERDEVICE_H

#include "RenderDevice.h"

namespace te
{
  class VkRenderDevice : public RenderDevice
  {
  public:
    VkRenderDevice();
    virtual ~VkRenderDevice();

    virtual void dispatch(RenderContext* context_);
  };
}

#endif // !RENDERER_VKRENDERDEVICE_H
