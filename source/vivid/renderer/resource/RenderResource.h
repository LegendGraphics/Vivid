#ifndef RENDERER_RENDER_RESOURCE_H
#define RENDERER_RENDER_RESOURCE_H

#include <vector>
#include "vivid/base/Types.h"

namespace vivid
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
}

#endif
