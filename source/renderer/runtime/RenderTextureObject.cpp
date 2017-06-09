#include "renderer/runtime/RenderTextureObject.h"

#include "renderer/device/RenderContext.h"
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

    void RenderTextureObject::update(RenderResourceContext* context)
    {
        if (0xFFFFFFFF == _tex_handle)
            allocTexture(context);
    }

    void RenderTextureObject::render(RenderContext* context)
    {
        command_stream::TextureCmdStream* tcs = new command_stream::TextureCmdStream;
        tcs->tex_handle = _tex_handle;
        tcs->tex_unit = _tex_unit;
        RenderContext::Command setTexture = { 0, (void*)tcs, command_stream::CommandType::UPDATE_TEXTURE };
        context->commands().push_back(setTexture);
    }

    void RenderTextureObject::parseStreamMsg(StateStreamMsg* msg)
    {
        TextureStreamMsg::Data* msg_data = static_cast<TextureStreamMsg::Data*>(msg->getData());

        if (stream_message::UPDATE == msg->getActionType())
        {
            _width = msg_data->texture->getWidth();
            _height = msg_data->texture->getHeight();
            _depth = msg_data->texture->getDepth();
            _img = msg_data->texture->getData();
        }
        else if (stream_message::RENDER == msg->getActionType())
        {
            ShaderSamplers& samplers = msg_data->shader->samplers;
            if (samplers.hasSampler(msg_data->texture->getName()))
                _tex_unit = samplers.getSamplers()[msg_data->texture->getName()].tex_unit;
        }
    }

    void RenderTextureObject::allocTexture(RenderResourceContext* context)
    {
        resource_stream::TextureStream* ts = new resource_stream::TextureStream;
        ts->res = &_tex_handle;
        ts->raw_data = &_img;
        ts->width = _width;
        ts->height = _height;
        ts->depth = _depth;
        ts->type = image_data::Type::IMAGE2D; // Hard code currently
        ts->format = image_data::Format::BGRA8;

        RenderResourceContext::Message allc_texture = {
            resource_stream::MessageType::ALLOC_TEXTURE, (void*)ts };
        context->messages().push_back(allc_texture);
    }
}

