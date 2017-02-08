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
    };

    // =====================================
    // attribute related definition start
    // =====================================
    struct VertexLayoutAttrib
    {
        std::string sematicName;
        uint32      vbslot; // to get the VertexBufferSlot from GLRenderDevice::_vertBufSlots
                            // which is set dynamically by shader
    };

    struct GLVertexLayout
    {
        uint32              numAttribs;
        VertexLayoutAttrib  attribs[16]; // TODO: need to investigate here
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

        void dispatch(RenderContext* context_) override;

        // Buffers
        uint32 createVertexBuffer(uint32 size, const void* data);
        uint32 createIndexBuffer(uint32 size, const void* data);
        void destroyBuffer(uint32 bufObj);
        void updateBufferData(uint32 bufObj, uint32 offset, uint32 size, void* data);

        // Shaders
        const char* getDefaultVSCode();
        const char* getDefaultFSCode();
        uint32 createShader(const char* vertexShaderSrc, const char* fragmentShaderSrc);
        uint32 createShaderProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc);
        bool linkShaderProgram(uint32 programObj);
        int getShaderConstLoc(uint32 shaderHandle, const char* name);
        void bindShader(uint32 shaderHandle);

        // RenderBuffer
        //uint32 createRenderBuffer(uint32 width, uint32 height, )

    protected:
        void commitGeneralUniforms();

    protected:
        std::string   _shaderLog;
        RDObjects<GLShader> _shaders;
        RDObjects<GLBuffer> _buffers;

        uint32 _prevShaderHandle, _curShaderHandle;

        uint32                _curIndexBuf, _newIndexBuf;
        uint32                _indexFormat;
    };
}

#endif
