#ifndef RENDERER_RENDER_SHADER_OBJECT_H
#define RENDERER_RENDER_SHADER_OBJECT_H

#include <unordered_map>
#include "base/Types.h"
#include "base/String.h"
#include "common/Shader.h"
#include "renderer/resource/RenderObject.h"

namespace te
{
    /*namespace shader_data
    {
        enum Class {
            SCALAR = 0,
            VECTOR2,
            VECTOR3,
            VECTOR4,
            MATRIX4X4,
            UINT,
            INT,
            BOOL,

            SCALAR_ARRAY,
            VECTOR2_ARRAY,
            VECTOR3_ARRAY,
            VECTOR4_ARRAY,
            MATRIX4X4_ARRAY,
            UINT_ARRAY,
            INT_ARRAY,
            BOOL_ARRAY,

            UNKNOWN_CLASS,
            NUM_CLASSES = UNKNOWN_CLASS
        };

        struct ShaderStream
        {
            RenderResource* res;
        };
    }*/

    //struct ShaderVariable
    //{
    //    unsigned klass;
    //    unsigned elements;
    //    unsigned offset;
    //    unsigned element_stride;
    //    String semantic_name;

    //    ShaderVariable() :
    //        klass(shader_data::UNKNOWN_CLASS),
    //        elements(0),
    //        offset(0xffffffff),
    //        element_stride(0),
    //        semantic_name("") {}
    //};

    //struct ShaderObject
    //{
    //    uint32 shader_handle;

    //    std::unordered_map<String, int> custom_uniform_handles; // TODO: reconsider if we need map here
    //    std::unordered_map<String, int> custom_sampler_handles;

    //    int uni_view_mat, uni_proj_mat, uni_view_proj_mat, uni_view_proj_mat_inv;
    //};

    // <del>seems in Horde3D all shader resource is managed in one
    // instance of ShaderResource??? </del>
    // one kind of mesh may have one ShaderResource; light may have its
    // own ShaderResource, etc
    /*class ShaderResource : public RenderResource
    {
        std::vector<ShaderObject> _shaders;
    };*/
    
    class RenderResourceContext;
    class RenderContext;
    class StreamMsg;

    class RenderShaderObject : public RenderObject
    {
    public:
        static RenderObject::Type TYPE;

        RenderShaderObject();
        ~RenderShaderObject();

        void update(RenderResourceContext* context);
        void render(RenderContext* context);

        void parseStreamMsg(StreamMsg* msg);

        //inline void setShaderObject(RenderResource* res) { _shader_object = res; };
        //inline void setModelMat(const Mat4x4& model_mat) { _model_mat = model_mat; };

    private:
        void createShader(RenderResourceContext* context);
        /*void allocIndexBuffer(RenderResourceContext* context);
        void allocVertexBuffer(RenderResourceContext* context);
        void allocVertexDeclaration(RenderResourceContext* context);

        void setVertexContext(RenderContext* context);*/
        //void setShader(RenderContext* context);

    private:
        GPUHandle   _shader_handle;
        String      _vs;
        String      _fs;

        ShaderUniforms*       _uniforms;
    };
}

#endif
