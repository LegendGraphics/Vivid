#ifndef RENDERER_RENDER_SHADER_OBJECT_H
#define RENDERER_RENDER_SHADER_OBJECT_H

#include "base/Types.h"

#include "renderer/resource/VertexLayoutType.h"
#include "renderer/runtime/RenderObject.h"
#include "common/Shader.h"

namespace te
{
    class RenderResourceContext;
    class RenderContext;
    class StateStreamMsg;

    class RenderShaderObject : public RenderObject
    {
    public:
        static RenderObject::Type TYPE;

        RenderShaderObject();
        ~RenderShaderObject();

        void update(RenderResourceContext* context);
        void render(RenderContext* context);

        void parseStreamMsg(StateStreamMsg* msg);

        //inline void setShaderObject(RenderResource* res) { _shader_object = res; };
        //inline void setModelMat(const Mat4x4& model_mat) { _model_mat = model_mat; };

    private:
        void createShader(RenderResourceContext* context);
        /*void allocIndexBuffer(RenderResourceContext* context);
        void allocVertexBuffer(RenderResourceContext* context);
        void allocVertexDeclaration(RenderResourceContext* context);

        void setVertexContext(RenderContext* context);*/
        void setShader(RenderContext* context);
        void setDraw(RenderContext* context);

    private:
        GPUHandle   _shader_handle;
        String      _vs;
        String      _fs;

        ShaderUniforms*         _uniforms;
        ShaderSamplers*         _samplers;

        vertex_layout::Type     _layout_type;
    };
}

#endif
