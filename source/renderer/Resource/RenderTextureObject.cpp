#include "renderer/resource/RenderTextureObject.h"

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
        allocTexture(context);
    }

    void RenderTextureObject::render(RenderContext* context)
    {

    }

    void RenderTextureObject::parseStreamMsg(StateStreamMsg* msg)
    {
        Texture* texture = static_cast<Texture*>(msg->getData());
        _width = texture->getWidth();
        _height = texture->getHeight();
        _depth = texture->getDepth();
        _img = texture->getData();
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

