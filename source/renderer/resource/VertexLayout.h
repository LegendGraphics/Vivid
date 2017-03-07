#ifndef RENDERER_VERTEXLAYOUT_H
#define RENDERER_VERTEXLAYOUT_H

#include "base/Globals.h"
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
            Partical
        };

    }

    // this seems to be a common concept
    // in all platforms, put it here for now
    // Vertex Layout is to tell the GPU
    // how attributes of a vertex is
    // stored in a chunk of memory
    struct VertexLayoutAttrib
    {
        std::string  semanticName;
        uint32       vbSlot;
        uint32       size;
        uint32       offset;
    };

    typedef std::vector<VertexLayoutAttrib> VertexLayout;

    struct VertexDeclaration : public RenderResource
    {
        std::unordered_map<vertex_layout::Type, VertexLayout> vertexLayoutMap;

        void init();
        const VertexLayout& getLayout(vertex_layout::Type vlType);

        VertexDeclaration() : VertexDeclaration(VERTEX_DECLARATION) { init(); }
        VertexDeclaration(RenderResource::Type t) : RenderResource(t) { init(); }
    };
}

#endif
