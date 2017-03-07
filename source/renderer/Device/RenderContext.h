#ifndef RENDERER_RENDERCONTEXT_H
#define RENDERER_RENDERCONTEXT_H

#include "base\Globals.h"

#include "renderer/resource/ShaderObject.h"

namespace te
{
    class RenderCamera; // used in RenderContext, to pass the camera
    // matrix into XXXRenderDevice. Just for current dev stage

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
            uint32 vaoHandle; // vao is used in OGL, probably not a very general design here?
            uint32 baseIndex;
            uint32 baseVertex;
            uint32 numIndices;
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

        RenderCamera* _camera; // TODO: can be generalized to a RenderStateObject

    private:
        Commands _commands;
    };
}

#endif
