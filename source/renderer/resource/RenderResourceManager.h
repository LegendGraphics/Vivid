#ifndef RENDERER_RENDERRESOURCEMANAGER_H
#define RENDERER_RENDERRESOURCEMANAGER_H

#include "renderer/resource/RenderResource.h"

namespace te
{
    class RenderResourceManager : public ResourceManager
    {
    public:
        RenderResourceManager();
        ~RenderResourceManager();

        ResourceHandle create(const String& res);
        GPUResourcePtr getGPUResource(ResourceHandle handle);

        void immediateCreate();

    protected:
        std::vector<ResourceHandle> _res_wait_list; // resources wait to be created in GPU, orders matter!
    };
}

#endif
