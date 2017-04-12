#ifndef RENDERER_VERTEXLAYOUT_H
#define RENDERER_VERTEXLAYOUT_H
#include <unordered_map>
#include "base/Types.h"
#include "base/String.h"
#include "RenderResource.h"

namespace te
{
    // Vertex Layout should be loaded from file like pipeline resource

    namespace vertex_layout
    {
        enum Type {
            Position,
            Overlay, // Position with Texture Coordinate
            Model,
            Partical,
            PNTB
        };

        struct IndexStream
        {
            uint32 size; // size in bytes
            void* raw_data;
            RenderResource* res;
        };

        struct VertexStream
        {
            uint32 stride;
            uint32 size; // size in bytes
            void* raw_data;
            RenderResource* res;
        };

        struct VertexDeclarationStream
        {
            vertex_layout::Type layout_type;
            std::vector<RenderResource*> vertex_buffers; // notice: vertex_buffers might be duplicated here
                                                         // because multiple attributes may share one vertex buffer
            RenderResource*              index_buffer;
            RenderResource*              res;
        };
    }

    // this seems to be a common concept
    // in all platforms, put it here for now
    // Vertex Layout is to tell the GPU
    // how attributes of a vertex is
    // stored in a chunk of memory
    struct VertexLayoutAttrib
    {
        String  semanticName;
        uint32       vbSlot;
        uint32       size; // number of component
        uint32       offset; // offset in bytes, for example, after a size 2 of float, offset will be 2 * (32 / 8) = 8
        //uint32       stride; // stride in bytes, for example, if two attributes XYZ and RGBA are stored together,
                             // the stride will be 7 * (32 / 8) = 28
                             // I decide to compute the stride when creating VAO
    };

    typedef std::vector<VertexLayoutAttrib> VertexLayout;

    struct VertexDeclaration : public RenderResource
    {
        std::unordered_map<vertex_layout::Type, VertexLayout> vertexLayoutMap;

        void init();
        const VertexLayout& getLayout(vertex_layout::Type vlType);

        VertexDeclaration() : RenderResource(OTHER) { init(); }
        VertexDeclaration(RenderResource::Type t) : RenderResource(t) { init(); }
    };
}

#endif
