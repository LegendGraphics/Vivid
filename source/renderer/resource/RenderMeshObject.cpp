#include "RenderMeshObject.h"

#include "renderer/device/RenderDevice.h"
#include "renderer/runtime/RenderCamera.h"
#include "renderer/device/RenderContext.h"

namespace te
{
    RenderObject::Type RenderMeshObject::TYPE = RenderObject::NOT_INITIALIZED;

    RenderMeshObject::RenderMeshObject()
        : RenderObject(TYPE)
    {
    }
    RenderMeshObject::~RenderMeshObject()
    {
    }

    void RenderMeshObject::render(RenderContext* context, RenderCamera* camera, RenderDevice* device)
    {
        RenderContext::Command setVertexBuffer = { 0, nullptr, RenderContext::CommandType::UPDATE_VERTEX_BUFFER };
        context->commands().push_back(setVertexBuffer);
    }

}
