#include "RenderResource.h"

namespace te
{
    String gpu_resource::getTypeStr(Type t)
    {
        switch (t)
        {
        case INDEX_STREAM: return "INDEX_STREAM";
        case VERTEX_STREAM: return "VERTEX_STREAM";
        case VERTEX_DECLARATION: return "VERTEX_DECLARATION";
        default: return "";
        }
    }
    String gpu_resource::appendTypeStr(Type t, const String & res_id)
    {
        return getTypeStr(t) + ":" + res_id;
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

    void GPUResource::fillStreamItem(ResourceStreamItem & item)
    {
        item.res_type = _gpu_resource_type;
        item.stream = _resource_stream;
    }
}
