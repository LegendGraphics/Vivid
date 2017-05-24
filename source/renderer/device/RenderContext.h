#ifndef RENDERER_RENDER_CONTEXT_H
#define RENDERER_RENDER_CONTEXT_H

#include "base/Types.h"

//#include "renderer/resource/ShaderObject.h"
#include "common/Shader.h"
#include "renderer/resource/RenderTexture.h"

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
            uint32 buf_handle;
            IndexFormat idx_format;
        };

        struct VertexCmdStream
        {
            uint32 vao_handle; // vao is used in OGL, probably not a very general design here?
            uint32 base_index;
            uint32 base_vertex;
            uint32 num_indices;
        };

        struct ShaderCmdStream
        {
            uint32          shader_handle;
            ShaderUniforms uniforms;
        };

        struct RenderTargetCmdStream
        {
            uint32 fbo_handle;
        };

        struct ClearCmdStream
        {
            float color_rgba[4];
            float depth;
            bool clear_color;
            bool clear_depth;
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
