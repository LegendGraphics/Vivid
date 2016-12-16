#ifndef RENDERER_RENDERCONTEXT_H
#define RENDERER_RENDERCONTEXT_H

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
            void* head; // command stream, use flag to get correct type
            uint32 command_flags;
        };
        typedef std::vector<Command> Commands;

        Commands& commands() { return _commands; };
        const Commands& commands() const { return _commands; };

    private:
        Commands _commands;
    };
}

#endif
