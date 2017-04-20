#ifndef RENDERER_VERTEXDECLARATION_H
#define RENDERER_VERTEXDECLARATION_H

#include "renderer/resource/RenderResource.h"
#include "renderer/resource/VertexLayoutType.h"

namespace te
{
    namespace vertex_layout
    {
        struct VertexDeclarationStream
        {
            vertex_layout::Type layout_type;
            std::vector<GPUResourceHandle*> vertex_buffers; // notice: vertex_buffers might be duplicated here
                                                            // because multiple attributes may share one vertex buffer
            GPUResourceHandle*              index_buffer;
            GPUResourceHandle*              res;
        };
    }

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