#ifndef RENDERER_RENDERRESOURCE_H
#define RENDERER_RENDERRESOURCE_H

#include "base/Globals.h"

namespace te
{
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
        RenderResource::Type resType;
        void* stream;
    };
    typedef std::vector<ResourceStreamItem> ResourceStreamQueue;

    enum class IndexFormat : uint8
    {
        IDXFMT_16,
        IDXFMT_32
    };
}

#endif
