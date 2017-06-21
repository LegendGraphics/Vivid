#ifndef VIVID_RENDERER_RENDER_TEXTURE_OBJECT_H
#define VIVID_RENDERER_RENDER_TEXTURE_OBJECT_H

#include "vivid/renderer/runtime/RenderObject.h"
#include "vivid/common/Texture.h"

namespace vivid
{
    class RenderResourceContext;
    class RenderContext;
    class StateStreamMsg;

    class RenderTextureObject : public RenderObject
    {
    public:
        static RenderObject::Type TYPE;

        RenderTextureObject();
        ~RenderTextureObject();

        void update(RenderResourceContext* context);
        void render(RenderContext* context);

        void parseStreamMsg(StateStreamMsg* msg);

    private:
        void allocTexture(RenderResourceContext* context);

    private:
        GPUHandle   _tex_handle;
        void*       _img;
        uint32      _width;
        uint32      _height;
        uint32      _depth;
        int         _tex_unit; // this may be changed in each render pass
    };
}

#endif
