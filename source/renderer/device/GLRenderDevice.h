#ifndef RENDERER_GLRENDERDEVICE_H
#define RENDERER_GLRENDERDEVICE_H

#include "renderer/Device/RenderDevice.h"

namespace te
{
    // =====================================
    // attribute related definition start
    // =====================================
    struct GLBuffer
    {
        uint32 type;
        uint32 glObj;
        uint32 size; // total size in byte
        uint32 stride; // number of component for each element
    };

    struct GLTexture
    {
        uint32 glObj;
        uint32 glType;
        image_data::Format format;
        int    width, height, depth;
        bool   hasMips;
    };

    struct GLRenderTarget
    {
        uint32 glFbo;
    };

    struct GLShader
    {
        uint32 oglProgramObj;
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

        void dispatch(RenderContext* context_) override;
        void dispatch(RenderResourceContext* context_) override;

        void clear(
            bool clearColor,
            float colorRGBA[4],
            bool clearDepth,
            float depth);

        // Buffers
        uint32 createVertexBuffer(uint32 size, uint32 stride, const void* data);
        uint32 createIndexBuffer(uint32 size, const void* data);
        uint32 createVertexArray(
            uint32 nLoc,
            const uint32* locations,
            const uint32* sizes,
            const uint32* offsets,
            const uint32* vertexHandles,
            uint32 indexHandle);
        void destroyBuffer(uint32 bufObj);
        void updateBufferData(uint32 bufObj, uint32 offset, uint32 size, void* data);

        // Shaders
        bool createDefaultShader(const char* vertexShader, const char* fragmentShader, ShaderObject& so);
        const char* getDefaultVSCode();
        const char* getDefaultFSCode();
        uint32 createShader(const char* vertexShaderSrc, const char* fragmentShaderSrc, vertex_layout::Type vlType);
        uint32 createShaderProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc);
        bool configShaderVertexLayout(uint32 programObj, vertex_layout::Type vlType);
        bool linkShaderProgram(uint32 programObj);
        int getShaderConstLoc(uint32 shaderHandle, const char* name);
        void setShaderConst(int loc, shader_data::Class type, void* values, uint32 count = 1);
        void bindShader(uint32 shaderHandle);

        // RenderBuffer
        uint32 createRenderBuffer(uint32 width, uint32 height, image_data::Format format,
            bool depth, uint32 numColBufs);

        // Textures
        uint32 createTexture(int width, int height, int depth, image_data::Type type, image_data::Format format, bool hasMips);
        void updateTextureData(uint32 texObj, int mipLevel, const void* pixels);

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
        String   _shaderLog;
        RDObjects<GLShader> _shaders;
        RDObjects<GLBuffer> _buffers;
        RDObjects<GLTexture> _textures;
        RDObjects<GLRenderTarget> _renderTargets;
        RDObjects<uint32> _vaos; // vertex array objects

        uint32 _prevShaderHandle, _curShaderHandle;
        ShaderObject _defaultShader;
        GLRenderTarget _defaultRenderTarget;

        uint32                _curBaseIndex, _curBaseVertex, _curNumIndices;
        uint32                _curVAO, _newVAO;
        int                _vpX, _vpY, _vpWidth, _vpHeight;
        
        uint32                _pending_mask;

    };
}

#endif
