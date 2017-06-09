#include "renderer/runtime/RenderShaderObject.h"

#include "renderer/device/RenderContext.h"
#include "renderer/device/RenderDevice.h"
#include "renderer/runtime/RenderCamera.h"
#include "renderer/resource/RenderResourceContext.h"
#include "renderer/resource/ResourceStream.h"
#include "renderer/runtime/StateStream.h"

#include "common/Mesh.h"

namespace te
{
    RenderObject::Type RenderShaderObject::TYPE = RenderObject::NOT_INITIALIZED;

    RenderShaderObject::RenderShaderObject()
        :_shader_handle(0xFFFFFFFF)
    {
    }

    RenderShaderObject::~RenderShaderObject()
    {
    }

    void RenderShaderObject::update(RenderResourceContext* context)
    {
        if (0xFFFFFFFF == _shader_handle)
            createShader(context);
    }

    void RenderShaderObject::render(RenderContext* context)
    {
        setShader(context);
        setDraw(context); // TODO: this should be moved out to a single DataStreamMsg
    }

    void RenderShaderObject::parseStreamMsg(StateStreamMsg* msg)
    {
        ShaderStreamMsg::Data* msg_data = static_cast<ShaderStreamMsg::Data*>(msg->getData());

        _vs = msg_data->shader->getVertexShaderContext();
        _fs = msg_data->shader->getFragmentShaderContext();
        _uniforms = &(msg_data->shader->uniforms);
        _samplers = &(msg_data->shader->samplers);
        _layout_type = msg_data->mesh->getLayoutType();
    }

    void RenderShaderObject::createShader(RenderResourceContext* context)
    {
        resource_stream::ShaderStream* ss = new resource_stream::ShaderStream;
        ss->res = &_shader_handle;
        ss->vs = _vs;
        ss->fs = _fs;
        ss->uniforms = _uniforms;
        ss->samplers = _samplers;
        ss->layout_type = _layout_type;

        RenderResourceContext::Message allc_shader = {
            resource_stream::MessageType::ALLOC_SHADER, (void*)ss };
        context->messages().push_back(allc_shader);
    }

    void RenderShaderObject::setShader(RenderContext* context)
    {
        command_stream::ShaderCmdStream* scs = new command_stream::ShaderCmdStream;
        scs->shader_handle = _shader_handle;
        scs->uniforms = _uniforms;
        scs->samplers = _samplers;
        RenderContext::Command set_shader = { 0, (void*)scs, command_stream::CommandType::BIND_SHADER_OBJECT };
        context->commands().push_back(set_shader);
    }

    void RenderShaderObject::setDraw(RenderContext* context)
    {
        RenderContext::Command draw = { 0, nullptr, command_stream::CommandType::RENDER };
        context->commands().push_back(draw);
    }
}

