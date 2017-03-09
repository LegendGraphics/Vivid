#include "RenderMeshObject.h"

#include "renderer/device/RenderContext.h"
#include "renderer/device/RenderDevice.h"
#include "renderer/runtime/RenderCamera.h"

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
        //RenderContext::IndexCmdStream* ics = new RenderContext::IndexCmdStream;
        //ics->bufHandle = _indexBuf;
        //ics->idxFormat = IndexFormat::IDXFMT_32;
        //RenderContext::Command setIndexBuffer = { 0, (void*)ics, RenderContext::CommandType::UPDATE_INDEX_BUFFER };
        //context->commands().push_back(setIndexBuffer);

        // set vertex buffer
        RenderContext::VertexCmdStream* vcs = new RenderContext::VertexCmdStream;
        vcs->vaoHandle = _vertex_declaration->render_resource_handle;
        vcs->baseIndex = 0;
        vcs->baseVertex = 0;
        vcs->numIndices = _numIndices;
        RenderContext::Command setVertexBuffer = { 0, (void*)vcs, RenderContext::CommandType::UPDATE_VERTEX_BUFFER };
        context->commands().push_back(setVertexBuffer);

        // prepare for shader object
        // Lin 1/19/2017
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
        //
        // Lin 1/20/2017
        // investigate how stingray do this
        //
        // local shader uniforms(custom unifomrs in Horde3D): std::vector<ShaderVar> local_vars and a pointer to buffer memory
        // struct ShaderVar { uint32 offset (offset for pointer); uint8 type; uint32 num_elem; };
        // buffer can be hold in MaterialResource and MaterialResource belongs to a Mesh node
        //
        // global shader uniforms(camera matrix): there is a resource manager to deal with that in Stingray
        // I will put the RenderCamera into RenderContext for current dev stage, since RenderContext is passed
        // into XXXRenderDevice.
        bool useDebug = true;
        if (useDebug)
        {
            RenderContext::Command setShaderObject = { 0, nullptr, RenderContext::CommandType::BIND_SHADER_OBJECT };
            context->commands().push_back(setShaderObject);
        }
        else
        {
            RenderContext::ShaderCmdStream* scs = new RenderContext::ShaderCmdStream;
            scs->shaderHandle = _shader_object->render_resource_handle;
            // set data
            // set variable
            RenderContext::Command setShaderObject = { 0, (void*)scs, RenderContext::CommandType::BIND_SHADER_OBJECT };
            context->commands().push_back(setShaderObject);
        }

        RenderContext::Command triggerRender = { 0, nullptr, RenderContext::CommandType::RENDER };
        context->commands().push_back(triggerRender);
    }

}
