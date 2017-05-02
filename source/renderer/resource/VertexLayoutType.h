#ifndef RENDERER_VERTEXLAYOUTTYPE_H
#define RENDERER_VERTEXLAYOUTTYPE_H

namespace te
{
    namespace vertex_layout
    {
        enum Type {
            Position,
            PN,
            PNTB,
            PNTB_SKINNED,
            Overlay, // Position with Texture Coordinate
            Model,
            Partical,
        };
    }
}

#endif
