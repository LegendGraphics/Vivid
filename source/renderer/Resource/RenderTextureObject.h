#ifndef RENDERER_RENDER_TEXTURE_OBJECT_H
#define RENDERER_RENDER_TEXTURE_OBJECT_H

#include <unordered_map>
#include "base/Types.h"
#include "base/String.h"
#include "common/Shader.h"
#include "renderer/resource/RenderObject.h"

namespace te
{
    class RenderResourceContext;
    class RenderContext;
    class StreamMsg;

    class RenderTextureObject : public RenderObject
    {
    public:
        static RenderObject::Type TYPE;

        RenderTextureObject();
        ~RenderTextureObject();

        void create(RenderResourceContext* context);
        void update(RenderResourceContext* context);
        void render(RenderContext* context);

        void parseStreamMsg(StreamMsg* msg);

    private:
        void allocTexture(RenderResourceContext* context);

    private:
        GPUHandle   _tex_handle;
    };
}

#endif
