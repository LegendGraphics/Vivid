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
        // pointer for shader object
        //ShaderResource* sr = nullptr;
        RenderContext::Command setShaderObject = { 0, nullptr, RenderContext::CommandType::BIND_SHADER_OBJECT };
        context->commands().push_back(setShaderObject);

        // set shader constant here
        

        // the pointer in command point to the vertex buffer
        RenderContext::Command setVertexBuffer = { 0, nullptr, RenderContext::CommandType::UPDATE_VERTEX_BUFFER };
        context->commands().push_back(setVertexBuffer);

        // pointer for index buffer
        RenderContext::Command setIndexBuffer = { 0, nullptr, RenderContext::CommandType::UPDATE_VERTEX_BUFFER };
        context->commands().push_back(setIndexBuffer);

    }

}
