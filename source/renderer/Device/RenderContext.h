#ifndef RENDERER_RENDERCONTEXT_H
#define RENDERER_RENDERCONTEXT_H

#include "base\Globals.h"

namespace te
{
   
    class RenderContext
    {
    public:
        RenderContext();
        virtual ~RenderContext();

        enum class CommandType : uint8
        {
            UPDATE_VERTEX_BUFFER,
            UPDATE_INDEX_BUFFER,
            UPDATE_TEXTURE,
            SET_RENDER_TARGET,
            CLEAR,
            RENDER,
            COMMANDS_COUNTER
        }; ///< 256 should be enough for now

        struct Command
        {
            uint64 sort_key;
            // not sure if we should use inheritage to trigger different behavior or not
            void* head; // command stream, use flag to get correct type
            CommandType command_type;
        };
        typedef std::vector<Command> Commands;

        Commands& commands() { return _commands; };
        const Commands& commands() const { return _commands; };

    private:
        Commands _commands;
    };
}

#endif
