#ifndef RENDERER_BUFFER_H
#define RENDERER_BUFFER_H

#include "common/Resource.h"

#include "renderer/resource/RenderResource.h"

namespace te
{
    class Mesh;

    struct IndexStream
    {
        uint32 size; // size in bytes
        void* raw_data;
        GPUHandle* res;
    };

    struct VertexStream
    {
        uint32 stride;
        uint32 size; // size in bytes
        void* raw_data;
        GPUHandle* res;
    };

    class Buffer : public Resource
    {
    public:
        Buffer();
        virtual ~Buffer() = default;

        bool load(const String& res);
        void unload();

        void fillStreamItem(ResourceStreamItem& item, Mesh* mesh);

    protected:
        GPUResourceType    _gpu_resource_type;
        GPUHandle          _gpu_resource_handle;
    };
}


#endif // RENDERER_BUFFER_H
