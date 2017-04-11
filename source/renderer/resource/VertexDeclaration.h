#ifndef RENDERER_VERTEXDECLARATION_H
#define RENDERER_VERTEXDECLARATION_H

#include "renderer/resource/RenderResource.h"

namespace te
{
    class VertexDeclaration : public GPUResource
    {
    public:
        VertexDeclaration();
        virtual ~VertexDeclaration() = default;

        bool load(const String& res);
        void unload();

        void fillStreamItem(ResourceStreamItem& item, Resource* res);
    };
}

#endif // !RENDERER_VERTEXDECLARATION_H
