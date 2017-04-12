#ifndef RENDERER_BUFFER_H
#define RENDERER_BUFFER_H

#include "renderer/resource/RenderResource.h"

namespace te
{
    class Mesh;

    namespace vertex_layout
    {
        struct IndexStream
        {
            uint32 size; // size in bytes
            void* raw_data;
            GPUResourceHandle* res;
        };

        struct VertexStream
        {
            uint32 stride;
            uint32 size; // size in bytes
            void* raw_data;
            GPUResourceHandle* res;
        };
    }

    class Buffer : public GPUResource
    {
    public:
        Buffer() {};
        Buffer(gpu_resource::Type t) : GPUResource(t) {};
        virtual ~Buffer();

        bool load(const String& res);
        void unload();

        void cacheStreamItem(Resource* res);
        void fillStreamItem(ResourceStreamItem& item);
    };
}


#endif // RENDERER_BUFFER_H
