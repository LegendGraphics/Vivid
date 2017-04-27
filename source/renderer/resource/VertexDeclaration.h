#ifndef RENDERER_VERTEXDECLARATION_H
#define RENDERER_VERTEXDECLARATION_H

#include "renderer/resource/RenderResource.h"
#include "renderer/resource/VertexLayoutType.h"

namespace te
{
    class VertexDeclaration : public GPUResource
    {
    public:
        VertexDeclaration();
        VertexDeclaration(gpu_resource::Type t);
        VertexDeclaration(gpu_resource::Type t, vertex_layout::Type vl_t);
        virtual ~VertexDeclaration();

        bool load(const String& res);
        void unload();

        void cacheStreamItem(const Resources& res);
        void setVertexLayoutType(vertex_layout::Type t) { _vertex_layout_type = t; };

    protected:
        vertex_layout::Type     _vertex_layout_type;
    };
}

#endif // !RENDERER_VERTEXDECLARATION_H
