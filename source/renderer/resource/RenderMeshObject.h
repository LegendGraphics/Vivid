#ifndef RENDERER_RENDERMESHOBJECT_H
#define RENDERER_RENDERMESHOBJECT_H

#include "renderer/resource/RenderObject.h"
#include "renderer/resource/RenderResource.h"

#include "math/Matrix.h"

namespace te
{
    class RenderContext;
    class RenderResourceContext;
    class RenderDevice;
    class RenderCamera;
    class RenderResource;
    class GPUResource;

    class RenderMeshObject : public RenderObject
    {
    public:
        static RenderObject::Type TYPE;

        RenderMeshObject();
        ~RenderMeshObject();

        void render(RenderContext* context, RenderCamera* camera, RenderDevice* device);
        void generateGPUResource(RenderResourceContext* context);

        inline void setNumIndices(uint32 numIndices) { _numIndices = numIndices; };
        inline void setShaderObject(RenderResource* res) { _shader_object = res; };
        inline void setVertexDeclaration(GPUResource* res) { _vertex_declaration = res; };
        inline void setModelMat(const Mat4x4& model_mat) { _model_mat = model_mat; };

    private:
        GPUHandle* _index_buffer;
        GPUHandle* _vertex_buffer;
        GPUHandle* _vao;



        RenderResource*  _shader_object;
        uint32  _numIndices; // temporary to put it here
        GPUResource*  _vertex_declaration;
        Mat4x4 _model_mat;
        // TODO: consider move this to a GeometryObject? Shader belongs to Material, Material
        // belongs to Mesh, Geometry also belongs to Mesh
    };
}

#endif
