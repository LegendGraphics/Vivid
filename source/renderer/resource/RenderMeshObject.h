#ifndef RENDERER_RENDERMESHOBJECT_H
#define RENDERER_RENDERMESHOBJECT_H

#include "renderer/resource/RenderObject.h"

namespace te
{
    class RenderContext;
    class RenderDevice;
    class RenderCamera;
    class RenderResource;
    class VertexDeclaration;

    class RenderMeshObject : public RenderObject
    {
    public:
        static RenderObject::Type TYPE;

        RenderMeshObject();
        ~RenderMeshObject();

        void render(RenderContext* context, RenderCamera* camera, RenderDevice* device);

        inline void setNumIndices(uint32 numIndices) { _numIndices = numIndices; };
        inline void setShaderObject(RenderResource* res) { _shader_object = res; };
        inline void setVertexDeclaration(VertexDeclaration* res) { _vertex_declaration = res; };

    private:
        RenderResource*  _shader_object;
        uint32  _numIndices; // temporary to put it here
        VertexDeclaration*  _vertex_declaration;
        // TODO: consider move this to a GeometryObject? Shader belongs to Material, Material
        // belongs to Mesh, Geometry also belongs to Mesh
    };
}

#endif
