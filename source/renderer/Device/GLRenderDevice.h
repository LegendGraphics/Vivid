#ifndef RENDERER_GLRENDERDEVICE_H
#define RENDERER_GLRENDERDEVICE_H

#include "renderer/Device/RenderDevice.h"

namespace te
{
    struct GLShader
    {
        uint32 oglProgramObj;
    };

    class GLRenderDevice : public RenderDevice
    {
    public:

        GLRenderDevice();
        ~GLRenderDevice();

        bool open();

        // Shaders
        const char* getDefaultVSCode();
        const char* getDefaultFSCode();

        uint32 createShader(const char* vertexShaderSrc, const char* fragmentShaderSrc);
        uint32 createShaderProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc);
        bool linkShaderProgram(uint32 programObj);
        int getShaderConstLoc(uint32 shaderHandle, const char* name);
        void bindShader(uint32 shaderHandle);


    protected:
        std::string   _shaderLog;
        RDObjects<GLShader> _shaders;

        uint32 _prevShaderHandle, _curShaderHandle;
    };
}

#endif
