#ifndef RENDERER_RENDER_NODE_OBJECT_H
#define RENDERER_RENDER_NODE_OBJECT_H

#include "renderer/resource/RenderObject.h"
#include "renderer/resource/RenderResource.h"

#include "math/Matrix.h"
#include "renderer/resource/VertexLayoutType.h"
#include "common/Mesh.h"

namespace te
{
    class RenderContext;
    class RenderResourceContext;
    class RenderDevice;
    class RenderCamera;
    struct RenderResource;

    class RenderNodeObject : public RenderObject
    {
    public:
        static RenderObject::Type TYPE;

        RenderNodeObject();
        RenderNodeObject(Mesh* mesh);
        ~RenderNodeObject();

        void render(RenderContext* context);
        void generateGPUResource(RenderResourceContext* context);
        void update(RenderResourceContext* context);

        inline void setShaderObject(RenderResource* res) { _shader_object = res; };
        inline void setModelMat(const Mat4x4& model_mat) { _model_mat = model_mat; };

    private:
        void generateIndexBuffer(RenderResourceContext* context);
        void generateVertexBuffer(RenderResourceContext* context);
        void generateVertexDeclaration(RenderResourceContext* context);

    private:
        GPUHandle _index_buffer;
        GPUHandle _vertex_buffer;
        GPUHandle _vao;

        IndexArray* _index_array;
        VertexArray* _vertex_array;
        vertex_layout::Type _layout_type;

        RenderResource*  _shader_object;
        uint32  _num_indices; // temporary to put it here
        Mat4x4 _model_mat;
        // TODO: consider move this to a GeometryObject? Shader belongs to Material, Material
        // belongs to Mesh, Geometry also belongs to Mesh
    };
}

#endif
