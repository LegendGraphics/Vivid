#include "RenderResource.h"

namespace te
{
    String gpu_resource::getTypeId(Type t)
    {
        switch (t)
        {
        case INDEX_STREAM: return "INDEX_STREAM";
        case VERTEX_STREAM: return "VERTEX_STREAM";
        case VERTEX_DECLARATION: return "VERTEX_DECLARATION";
        default: return "";
        }
    }
    String gpu_resource::appendTypeId(Type t, const String & res_id)
    {
        return getTypeId(t) + ":" + res_id;
    }

    GPUResource::GPUResource()
        : _gpu_resource_type(gpu_resource::NOT_INITIALIZED),
        _gpu_resource_handle(gpu_resource::NOT_INITIALIZED),
        _resource_stream(nullptr)
    {

    }

    GPUResource::GPUResource(gpu_resource::Type t)
        : _gpu_resource_type(t),
        _gpu_resource_handle(gpu_resource::NOT_INITIALIZED),
        _resource_stream(nullptr)
    {

    }

    GPUResource::GPUResource(gpu_resource::Type t, GPUResourceHandle h)
        : _gpu_resource_type(t),
        _gpu_resource_handle(h),
        _resource_stream(nullptr)
    {

    }
}
