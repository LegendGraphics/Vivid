#ifndef RENDERER_BUFFER_H
#define RENDERER_BUFFER_H

#include "renderer/resource/RenderResource.h"

namespace te
{
    class Mesh;



    class Buffer : public GPUResource
    {
    public:
        Buffer();
        Buffer(gpu_resource::Type t);
        virtual ~Buffer();

        bool load(const String& res);
        void unload();

        void cacheStreamItem(const Resources& res);
    };
}


#endif // RENDERER_BUFFER_H
