#ifndef RENDERER_GLRENDERDEVICE_H
#define RENDERER_GLRENDERDEVICE_H

#include "renderer/Device/RenderDevice.h"

namespace te
{
    const uint32 MaxNumVertexLayouts = 16;

    struct GLBuffer
    {
        uint32 type;
        uint32 glObj;
        uint32 size;
        uint32 stride;
    };

    // =====================================
    // attribute related definition start
    // =====================================
    struct GLVertexLayoutAttrib
    {
        std::string sematicName;
        uint32      vbslot; // to get the VertexBufferSlot from GLRenderDevice::_vertBufSlots
                            // which is set dynamically by shader
    };

    struct GLVertexLayout
    {
        uint32              numAttribs;
        GLVertexLayoutAttrib  attribs[16]; // TODO: need to investigate here
        // there is a corresponding structure in Shader
        // one layout may have at most 16 attributes (attributes is a key world in GLSL)
        // for different purpose, there might be different layouts
        // for example, light, overlay(ui, font, etc), model, etc
    };

    struct GLVertBufSlot
    {
        uint32 vbObj; // it is the vertex buffer object handle in engine side
                      // which is used to get the opengl buffer object from GLRenderDevice::_buffers
        uint32 offset;
        uint32 stride;
    };

    struct GLShaderInputLayout
    {
        bool valid;
        int8 attribBindPointer[16]; // the corresponding binding point for glVertexAttribPointer
                                    // it's set from glGetAttribLocation
                                    // it seems that OpenGL supports 16 attributes for a shader at most
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

    // ==================================
    // attribute related definition end
    // - not sure if these are general paradigm, may be moved to base class???
    // ==================================

    struct GLShader
    {
        uint32 oglProgramObj;
        GLShaderInputLayout inputLayouts[MaxNumVertexLayouts];
    };

    class GLRenderDevice : public RenderDevice
    {
    public:

        GLRenderDevice();
        ~GLRenderDevice();

        bool open();

        void close();

        void dispatch(RenderContext* context_) override;
        void dispatch(RenderResourceContext* context_) override;

        // Buffers
        uint32 createVertexBuffer(uint32 size, uint32 stride, const void* data);
        uint32 createIndexBuffer(uint32 size, const void* data);
        uint32 createVertexArray(uint32 nLoc, const uint32* locations, const uint32* vertexHandles, uint32 indexHandle);
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
        bool GLRenderDevice::commitStates();

    protected:
        std::string   _shaderLog;
        RDObjects<GLShader> _shaders;
        RDObjects<GLBuffer> _buffers;
        RDObjects<GLTexture> _textures;
        RDObjects<GLRenderTarget> _renderTargets;
        RDObjects<uint32> _vaos; // vertex array objects
        VertexDeclaration _vertexDeclaration;

        uint32 _prevShaderHandle, _curShaderHandle;
        ShaderObject _defaultShader;

        uint32                _curBaseIndex, _curBaseVertex, _curNumIndices;
        uint32                _curVAO, _newVAO;
        //uint32                _indexFormat;


    };
}

#endif
