#ifndef RENDERER_RENDERRESOURCE_H
#define RENDERER_RENDERRESOURCE_H
#include <vector>
#include "base/Types.h"

namespace te
{
    enum class GPUResourceType
    {
        INDEX_STREAM,
        VERTEX_STREAM,
        VERTEX_DECLARATION,
        NUM_TYPE
    };

    typedef uint32 GPUHandle;

    struct RenderResource
    {
        enum 
        {
            PIPELINE,
            TEXTURE,
            INDEX_STREAM,
            VERTEX_STREAM,
            VERTEX_DECLARATION,
            SHADER,
            OTHER,
            NOT_INITIALIZED = 0xFFFFFFFF
        };
        typedef uint32 Type;
        typedef uint32 Handle;

        RenderResource() : type(NOT_INITIALIZED), render_resource_handle(NOT_INITIALIZED) {};
        RenderResource(Type t) : type(t), render_resource_handle(NOT_INITIALIZED) {};
        RenderResource(Type t, Handle h) : type(t), render_resource_handle(h) {};
        virtual ~RenderResource() {};

        Type type;
        Handle render_resource_handle;
    };

    struct ResourceStreamItem
    {
        GPUResourceType res_type;
        void* stream;
    };
    typedef std::vector<ResourceStreamItem> ResourceStreamQueue;
}

#endif
