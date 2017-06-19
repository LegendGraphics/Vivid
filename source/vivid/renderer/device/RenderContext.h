#ifndef RENDERER_RENDER_CONTEXT_H
#define RENDERER_RENDER_CONTEXT_H

#include "vivid/base/Types.h"

#include "vivid/renderer/device/CommandStream.h"

namespace te
{
    class RenderCamera; // used in RenderContext, to pass the camera
    // matrix into XXXRenderDevice. Just for current dev stage

    class RenderContext
    {
    public:
        RenderContext();
        virtual ~RenderContext();

        struct Command
        {
            uint64 sort_key;
            // not sure if we should use inherit to trigger different behavior or not
            void* head; // command stream, use flag to get correct type
            command_stream::CommandType command_type;
        };
        typedef std::vector<Command> Commands;

        Commands& commands() { return _commands; };
        const Commands& commands() const { return _commands; };

        RenderCamera* _camera; // TODO: can be generalized to a RenderStateObject

    private:
        Commands _commands;
    };
}

#endif
