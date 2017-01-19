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
        // set index buffer
        RenderContext::IndexCmdStream* ics = new RenderContext::IndexCmdStream;
        ics->bufHandle = _indexBuf;
        ics->idxFormat = IndexFormat::IDXFMT_32;
        RenderContext::Command setIndexBuffer = { 0, (void*)ics, RenderContext::CommandType::UPDATE_INDEX_BUFFER };
        context->commands().push_back(setIndexBuffer);

        // set vertex buffer
        RenderContext::VertexCmdStream* vcs = new RenderContext::VertexCmdStream;
        vcs->bufHandle = _posVBuf;
        RenderContext::Command setVertexBuffer = { 0, (void*)vcs, RenderContext::CommandType::UPDATE_VERTEX_BUFFER };

        // prepare for shader object
        // Two ways here, (choose #2 in current dev stage)
        // Shader require different constants (uniform in GLSL) set before rendering
        // 1. set the constants here (I think to prevent too much memory copy, we need to use handle)
        // 2. only set the shader and let shader get all constants it needed ready in XXXRenderDevice
        //    - still need a way to let shader get the constants it needed.
        //    - constants usually stores in Material resource
        //    - in Horde3D, the lowest level of shader structure is ShaderCombination which is kept as a 
        //      std::vector<>in ShaderContext. ShaderContext is also kept as a std::vector<> in ShaderResource.
        //      Each ShaderContext seems related to different effect pass (ShadowMap, Light, Ambient, AttribPass, etc)
        //      Since there are multiple shaders in one ShaderContext, client use a mask (uint) to decide which
        //      shader to use.
        //
        // Perhaps we should separate custom uniforms from general uniforms (projection mat, view mat, etc).
        // General uniforms should be set outside of the scope of RenderMeshObject
        // Seems in Stingray they are all written to the command stream but with a global/local tag
        // it's a pointer (resources) in the stream, not sure where the resources are managed

        RenderContext::Command setShaderObject = { 0, nullptr, RenderContext::CommandType::BIND_SHADER_OBJECT };
        context->commands().push_back(setShaderObject);
    }

}
