#ifndef RENDERER_IMAGE_H
#define RENDERER_IMAGE_H

namespace vivid
{
    namespace image_data
    {
        enum Type {
            IMAGE2D,
            IMAGE3D,
            IMAGECUBE,
            UNKNOWN
        };

        enum Format {
            Unknown,
            BGR8,
            RGB8,
            BGRA8,
            DXT1,
            DXT3,
            DXT5,
            RGBA16F,
            RGBA32F,
            DEPTH
        };
    }
}

#endif
