#ifndef RENDERER_RENDERCONTEXT_H
#define RENDERER_RENDERCONTEXT_H

#include "Core\base\Globals.h"

namespace te
{
   
    class RenderContext
    {
    public:
        RenderContext();
        virtual ~RenderContext();

        struct Command
        {
            uint64 sort_key;
            // not sure if we should use inheritage to trigger different behavior or not
            void* head; // command stream, use flag to get correct type
            uint32 command_flags;
        };
        typedef std::vector<Command> Commands;

        Commands& commands() { return _commands; };
        const Commands& commands() const { return _commands; };

        virtual int dispatch() = 0;

    private:
        Commands _commands;
    };
}

#endif
