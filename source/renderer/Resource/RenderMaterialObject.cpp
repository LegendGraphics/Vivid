#include "renderer/resource/RenderMaterialObject.h"

#include "renderer/device/RenderContext.h"
#include "renderer/device/RenderDevice.h"
#include "renderer/runtime/RenderCamera.h"
#include "renderer/resource/RenderResourceContext.h"
#include "renderer/resource/ResourceStream.h"
#include "renderer/runtime/StateStream.h"

namespace te
{
    RenderObject::Type RenderMaterialObject::TYPE = RenderObject::NOT_INITIALIZED;

    RenderMaterialObject::RenderMaterialObject()
        :_shader_handle(0xFFFFFFFF)
    {
    }

    RenderMaterialObject::~RenderMaterialObject()
    {
    }

    void RenderMaterialObject::create(RenderResourceContext* context)
    {
    }

    void RenderMaterialObject::update(RenderResourceContext* context)
    {
        createShader(context);
    }

    void RenderMaterialObject::render(RenderContext* context)
    {
        setShader(context);
    }

    void RenderMaterialObject::parseStreamMsg(StreamMsg* msg)
    {
        Shader* shader = static_cast<Shader*>(msg->getData());

        _vs = shader->getVertexShaderContext();
        _fs = shader->getFragmentShaderContext();
        _uniforms = shader->uniforms;
    }

    void RenderMaterialObject::createShader(RenderResourceContext* context)
    {
        shader_data::ShaderStream* ss = new shader_data::ShaderStream;
        ss->res = &_shader_handle;
        ss->vs = _vs;
        ss->fs = _fs;
        ss->uniforms = &_uniforms;

        RenderResourceContext::Message allc_shader = {
            RenderResourceContext::MessageType::ALLOC_SHADER, (void*)ss };
        context->messages().push_back(allc_shader);
    }

    void RenderMaterialObject::setShader(RenderContext* context)
    {
        RenderContext::ShaderCmdStream* scs = new RenderContext::ShaderCmdStream;
        scs->shader_handle = _shader_handle;
        scs->uniforms = _uniforms;
        RenderContext::Command set_shader = { 0, (void*)scs, RenderContext::CommandType::BIND_SHADER_OBJECT };
        context->commands().push_back(set_shader);
    }
}

