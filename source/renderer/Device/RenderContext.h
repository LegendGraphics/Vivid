#ifndef RENDERER_RENDERCONTEXT_H
#define RENDERER_RENDERCONTEXT_H

#include "base\Globals.h"

namespace te
{
    class RenderCamera; // used in RenderContext, to pass the camera
    // matrix into XXXRenderDevice. Just for current dev stage

    // this seems to be a common concept
    // in all platforms, put it here for now
    // Vertex Layout is to tell the GPU
    // how attributes of a vertex is
    // stored in a chunk of memory
    struct VertexLayoutAttrib
    {
        std::string  semanticName;
        uint32       vbSlot;
        uint32       size;
        uint32       offset;
    };

    enum class IndexFormat : uint8
    {
        IDXFMT_16,
        IDXFMT_32
    };

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
            BIND_SHADER_OBJECT,
            SET_RENDER_TARGET,
            CLEAR,
            RENDER,
            COMMANDS_COUNTER
        }; ///< 256 should be enough for now

        struct IndexCmdStream
        {
            uint32 bufHandle;
            IndexFormat idxFormat;
        };

        struct VertexCmdStream
        {
            std::vector<uint32> vAttribs;
        };

        struct ShaderCmdStream
        {
            uint32 shaderHandle;
            void*  data; // the data is hold by real entity, no need to be deleted here
            std::vector<ShaderVariable> variables;
        };

        struct Command
        {
            uint64 sort_key;
            // not sure if we should use inherit to trigger different behavior or not
            void* head; // command stream, use flag to get correct type
            CommandType command_type;
        };
        typedef std::vector<Command> Commands;

        Commands& commands() { return _commands; };
        const Commands& commands() const { return _commands; };

        RenderCamera* _camera;

    private:
        Commands _commands;
    };
}

#endif
