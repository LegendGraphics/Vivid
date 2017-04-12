#ifndef RENDERER_TEXTURE_H
#define RENDERER_TEXTURE_H

#include "RenderResource.h"

namespace te
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
            BGRA8,
            DXT1,
            DXT3,
            DXT5,
            RGBA16F,
            RGBA32F,
            DEPTH
        };
    }

    struct Texture : public RenderResource {
        Texture() : RenderResource(TEXTURE) { }
        Texture(RenderResource::Type t) : RenderResource(t) { }

        image_data::Format format;
    };
}

#endif