#ifndef RENDERER_VERTEXLAYOUTTYPE_H
#define RENDERER_VERTEXLAYOUTTYPE_H

namespace te
{
    namespace vertex_layout
    {
        enum Type {
            Position,
            Overlay, // Position with Texture Coordinate
            Model,
            Partical,
            PN,
            PNTB,
            PNTB_SKINNED
        };

        String getTypeStr(Type t);
        Type getType(const String& str);
    }
}

#endif
