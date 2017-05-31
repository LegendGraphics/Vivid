#include "renderer/resource/RenderTextureObject.h"

#include "renderer/device/RenderContext.h"
#include "renderer/device/RenderDevice.h"
#include "renderer/runtime/RenderCamera.h"
#include "renderer/resource/RenderResourceContext.h"
#include "renderer/resource/ResourceStream.h"
#include "renderer/runtime/StateStream.h"

namespace te
{
    RenderObject::Type RenderTextureObject::TYPE = RenderObject::NOT_INITIALIZED;

    RenderTextureObject::RenderTextureObject()
        :_tex_handle(0xFFFFFFFF)
    {
    }

    RenderTextureObject::~RenderTextureObject()
    {
    }

    void RenderTextureObject::create(RenderResourceContext* context)
    {
    }

    void RenderTextureObject::update(RenderResourceContext* context)
    {
    }

    void RenderTextureObject::render(RenderContext* context)
    {

    }

    void RenderTextureObject::parseStreamMsg(StreamMsg* msg)
    {
        /*Shader* shader = static_cast<Shader*>(msg->getData());

        _vs = shader->getVertexShaderContext();
        _fs = shader->getFragmentShaderContext();
        _uniforms = shader->getShaderUniforms();*/
    }

    void RenderTextureObject::allocTexture(RenderResourceContext* context)
    {
        /*shader_data::ShaderStream* ss = new shader_data::ShaderStream;
        ss->res = &_shader_handle;
        ss->vs = _vs;
        ss->fs = _fs;
        ss->uniforms = &_uniforms;

        RenderResourceContext::Message allc_shader = {
            RenderResourceContext::MessageType::ALLOC_SHADER, (void*)ss };
        context->messages().push_back(allc_shader);*/
    }
}

