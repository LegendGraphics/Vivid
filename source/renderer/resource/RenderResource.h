#ifndef RENDERER_RENDERRESOURCE_H
#define RENDERER_RENDERRESOURCE_H

#include "common/Resource.h"

#include <vector>
#include "base/Types.h"

namespace te
{
    typedef uint32 GPUResourceHandle;

    namespace gpu_resource
    {
        enum Type
        {
            INDEX_STREAM,
            VERTEX_STREAM,
            VERTEX_DECLARATION,
            NOT_INITIALIZED = 0xFFFFFFFF
        };

        String getTypeId(Type t);
        String appendTypeId(Type t, const String& res_id);
    }

    struct ResourceStreamItem
    {
        gpu_resource::Type res_type;
        void* stream;
    };
    typedef std::vector<ResourceStreamItem> ResourceStreamQueue;

    class GPUResource : public Resource
    {
    public:
        GPUResource();
        GPUResource(gpu_resource::Type t);
        GPUResource(gpu_resource::Type t, GPUResourceHandle h);
        virtual ~GPUResource() = default;

        virtual void fillStreamItem(ResourceStreamItem& item) = 0;
        virtual void cacheStreamItem(Resource* res) = 0;
        void setGPUResourceType(gpu_resource::Type t) { _gpu_resource_type = t; };
        GPUResourceHandle& getGPUResourceHandle() { return _gpu_resource_handle; };

    protected:
        gpu_resource::Type  _gpu_resource_type;
        GPUResourceHandle   _gpu_resource_handle;
        void*               _resource_stream;
    };
    using GPUResourcePtr = RefPtr<GPUResource>;

    // this need to be deprecated
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
