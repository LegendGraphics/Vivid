#ifndef RENDERER_RENDER_MATERIAL_OBJECT_H
#define RENDERER_RENDER_MATERIAL_OBJECT_H

#include <unordered_map>
#include "base/Types.h"
#include "base/String.h"
#include "common/Material.h"
#include "renderer/resource/RenderObject.h"

namespace te
{

    class RenderResourceContext;
    class RenderContext;
    class StreamMsg;

    class RenderMaterialObject : public RenderObject
    {
    public:
        static RenderObject::Type TYPE;

        RenderMaterialObject();
        ~RenderMaterialObject();

        void create(RenderResourceContext* context);
        void update(RenderResourceContext* context);
        void render(RenderContext* context);

        void parseStreamMsg(StreamMsg* msg);

    private:
        void setShader(RenderContext* context);

    private:
        GPUHandle       _material_handle;

        ShaderUniforms  _uniforms;
    };
}

#endif
