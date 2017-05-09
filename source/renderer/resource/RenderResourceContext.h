#ifndef RENDERER_RENDER_RESOURCE_CONTEXT_H
#define RENDERER_RENDER_RESOURCE_CONTEXT_H

#include "renderer/resource/RenderResource.h"

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
