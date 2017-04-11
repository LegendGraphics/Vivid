#ifndef RENDERER_RENDERRESOURCE_H
#define RENDERER_RENDERRESOURCE_H

#include "common/Resource.h"

#include <vector>
#include "base/Types.h"

namespace te
{
    enum GPUResourceType
    {
        INDEX_STREAM,
        VERTEX_STREAM,
        VERTEX_DECLARATION,
        NOT_INITIALIZED = 0xFFFFFFFF
    };

    typedef uint32 GPUResourceHandle;

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

    class GPUResource : public Resource
    {
    public:
        GPUResource() : _gpu_resource_type(GPUResourceType::NOT_INITIALIZED), _gpu_resource_handle(GPUResourceType::NOT_INITIALIZED) {};
        GPUResource(GPUResourceType t) : _gpu_resource_type(t), _gpu_resource_handle(GPUResourceType::NOT_INITIALIZED) {};
        GPUResource(GPUResourceType t, GPUResourceHandle h) : _gpu_resource_type(t), _gpu_resource_handle(h) {};
        virtual ~GPUResource() = default;

        virtual void fillStreamItem(ResourceStreamItem& item, Resource* res) = 0;
        void setGPUResourceType(GPUResourceType t) { _gpu_resource_type = t; };
        GPUResourceHandle& getGPUResourceHandle() { return _gpu_resource_handle; };

    protected:
        GPUResourceType     _gpu_resource_type;
        GPUResourceHandle   _gpu_resource_handle;
    };
}

#endif
