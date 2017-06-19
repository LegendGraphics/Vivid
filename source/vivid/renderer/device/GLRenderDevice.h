#ifndef RENDERER_GL_RENDER_DEVICE_H
#define RENDERER_GL_RENDER_DEVICE_H

#include "vivid/renderer/device/RenderDevice.h"

namespace te
{
    // =====================================
    // attribute related definition start
    // =====================================
    struct GLBuffer
    {
        uint32 type;
        uint32 gl_obj;
        uint32 size; // total size in byte
        uint32 stride; // number of component for each element
    };

    struct GLTexture
    {
        uint32 gl_obj;
        uint32 gl_type;
        image_data::Format format;
        int    width, height, depth;
        bool   has_mips;
    };

    struct GLRenderTarget
    {
        uint32 gl_fbo;
    };

    struct GLShader
    {
        uint32 gl_program_obj;
    };

    // ==================================
    // attribute related definition end
    // - not sure if these are general paradigm, may be moved to base class???
    // ==================================

    class GLRenderDevice : public RenderDevice
    {
    public:

        GLRenderDevice();
        ~GLRenderDevice();

        bool open();

        void close();

        void dispatch(RenderContext* context) override;
        void dispatch(RenderResourceContext* context) override;

        void clear(
            bool clear_color,
            float color_rgba[4],
            bool clear_depth,
            float depth);

        // Buffers
        uint32 createVertexBuffer(uint32 size, uint32 stride, const void* data);
        uint32 createIndexBuffer(uint32 size, const void* data);
        uint32 createVertexArray(
            uint32 nLoc,
            const uint32* locations,
            const uint32* sizes,
            const uint32* offsets,
            const uint32* vertex_handles,
            uint32 index_handle);
        void destroyBuffer(uint32 buf_obj);
        void updateBufferData(uint32 buf_obj, uint32 offset, uint32 size, void* data);

        // Shaders
        //bool createDefaultShader(const char* vertex_shader, const char* fragment_shader, ShaderObject& so);
        const char* getDefaultVSCode();
        const char* getDefaultFSCode();
        uint32 createShader(const char* vertex_shader_src, const char* fragment_shader_src, vertex_layout::Type vl_type);
        uint32 createShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src);
        bool configShaderVertexLayout(uint32 program_obj, vertex_layout::Type vl_type);
        bool linkShaderProgram(uint32 program_obj);
        int getShaderConstLoc(uint32 shader_handle, const char* name);
        void setShaderConst(int loc, shader_data::UniformType type, void* values, uint32 count = 1);
        void bindShader(uint32 shader_handle);

        // RenderBuffer
        uint32 createRenderBuffer(uint32 width, uint32 height, image_data::Format format,
            bool depth, uint32 num_col_bufs);

        // Textures
        uint32 createTexture(int width, int height, int depth, image_data::Type type, image_data::Format format, bool has_mips);
        void updateTextureData(uint32 tex_obj, int mip_level, const void* pixels);

    protected:
        void commitGeneralUniforms();
        void draw();
        bool commitStates(uint32 filter = 0xFFFFFFFF);

        void testVao();
        uint32 _testVao;
        uint32 _testVbo;
        uint32 _testIbo;

        // TODO: temporalily put it here
        enum RDIPendingMask
        {
          PM_VIEWPORT = 0x00000001,
          PM_INDEXBUF = 0x00000002,
          PM_VERTLAYOUT = 0x00000004,
          PM_TEXTURES = 0x00000008,
          PM_SCISSOR = 0x00000010,
          PM_RENDERSTATES = 0x00000020
        };

    protected:
        String   _shader_log;
        RDObjects<GLShader> _shaders;
        RDObjects<GLBuffer> _buffers;
        RDObjects<GLTexture> _textures;
        RDObjects<GLRenderTarget> _render_targets;
        RDObjects<uint32> _vaos; // vertex array objects

        uint32 _prev_shader_handle, _cur_shader_handle;
        //ShaderObject _default_shader;
        GLRenderTarget _default_render_target;

        uint32              _cur_base_index, _cur_base_vertex, _cur_num_indices;
        uint32              _cur_vao, _new_vao;
        int                 _vp_x, _vp_y, _vp_width, _vp_height;
        struct TexSlot
        {
            uint32      tex_handle;
            uint32      tex_unit;
            TexSlot(uint32 handle, uint32 unit) : tex_handle(handle), tex_unit(unit) {};
        };
        std::vector<TexSlot>    _cur_tex_slots;
        
        uint32              _pending_mask;

    };
}

#endif
