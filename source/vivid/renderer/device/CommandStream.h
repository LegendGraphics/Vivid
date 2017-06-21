#ifndef VIVID_RENDERER_COMMAND_STREAM_H
#define VIVID_RENDERER_COMMAND_STREAM_H

namespace vivid
{
    class ShaderUniforms;
    class ShaderSamplers;
    namespace command_stream
    {
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
            //IndexFormat idx_format;
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
            ShaderUniforms* uniforms;
            ShaderSamplers* samplers;
        };

        struct TextureCmdStream
        {
            uint32 tex_handle;
            uint32 tex_unit;
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
    }
}

#endif
