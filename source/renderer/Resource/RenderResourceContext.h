#ifndef RENDERER_RENDERRESOURCECONTEXT_H
#define RENDERER_RENDERRESOURCECONTEXT_H

#include "RenderResource.h"
#include "VertexLayout.h"

namespace te
{
    class RenderResourceContext
    {
    public:
        RenderResourceContext();
        virtual ~RenderResourceContext();

        enum class MessageType : uint8 
        {
            ALLOC_VERTEX_BUFFER, DEALLOC_VERTEX_BUFFER,
            ALLOC_VERTEX_DECLARATION, DEALLOC_VERTEX_DECLARATION,
            ALLOC_INDEX_BUFFER, DEALLOC_INDEX_BUFFER,
            ALLOC_SHADER, DEALLOC_SHADER,
            ALLOC_RENDER_TARGET, DEALLOC_RENDER_TARGET,
            ALLOC_TEXTURE, DEALLOC_TEXTURE, REALLOC_TEXTURE,
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

        struct ShaderStream
        {
            RenderResource* res;
        };

        struct Message
        {
            MessageType type;
            void* head;
        };
        typedef std::vector<Message> Messages;

        Messages& messages() { return _messages; };
        const Messages& messages() const { return _messages; };

    private:
        Messages _messages;
    };
}

#endif
