#ifndef RENDERER_GLRENDERDEVICE_H
#define RENDERER_GLRENDERDEVICE_H

#include "renderer/Device/RenderDevice.h"

namespace te
{
    struct GLShader
    {
        uint32 oglProgramObj;
    };

    struct GLBuffer
    {
        uint32 type;
        uint32 glObj;
        uint32 size;
    };

    struct GLVertexLayout
    {
        uint32              numAttribs;
        //VertexLayoutAttrib  attribs[16]; // TODO: need to investigate here
        // there is a corresponding structure in Shader
        // one layout may have at most 16 attributes (attributes is a key world in GLSL)
        // for different purpose, there might be different layouts
        // for example, light, overlay(ui, font, etc), model, etc
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
        std::string   _shaderLog;
        RDObjects<GLShader> _shaders;
        RDObjects<GLBuffer> _buffers;

        uint32 _prevShaderHandle, _curShaderHandle;

        uint32                _curIndexBuf, _newIndexBuf;
        uint32                _indexFormat;
    };
}

#endif
