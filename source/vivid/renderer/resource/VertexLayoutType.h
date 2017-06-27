#ifndef RENDERER_VERTEX_LAYOUT_TYPE_H
#define RENDERER_VERTEX_LAYOUT_TYPE_H

namespace vivid
{
    namespace vertex_layout
    {
        enum VertexAttribute
        {
            POSITVIVID_ION = 1 << 0,
            NORMAL = 1 << 1,
            TANGENT = 1 << 2,
            BITANGENT = 1 << 3,
            TEXTURE1 = 1 << 4,
            TEXTURE2 = 1 << 5
        };

        enum Type {
            P = VertexAttribute::POSITVIVID_ION,

            PN = VertexAttribute::POSITVIVID_ION + VertexAttribute::NORMAL,

            PNTB = VertexAttribute::POSITVIVID_ION + VertexAttribute::NORMAL
            + VertexAttribute::TANGENT + VertexAttribute::BITANGENT,

            PNTB_TEX = VertexAttribute::POSITVIVID_ION + VertexAttribute::NORMAL
            + VertexAttribute::TANGENT + VertexAttribute::BITANGENT
            + VertexAttribute::TEXTURE1,

            PNTB_SKINNED,
            Overlay, // Position with Texture Coordinate
            Model,
            Partical,
        };
    }
}

#endif
