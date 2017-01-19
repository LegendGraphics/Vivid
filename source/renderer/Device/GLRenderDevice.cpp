#include "GLRenderDevice.h"

#include "RenderContext.h"

#include "../3rdparty/glew/include/GL/glew.h"

namespace te
{

    static const char *defaultShaderVS =
        "uniform mat4 viewProjMat;\n"
        "uniform mat4 worldMat;\n"
        "attribute vec3 vertPos;\n"
        "void main() {\n"
        "	gl_Position = viewProjMat * worldMat * vec4( vertPos, 1.0 );\n"
        "}\n";

    static const char *defaultShaderFS =
        "uniform vec4 color;\n"
        "void main() {\n"
        "	gl_FragColor = color;\n"
        "}\n";

    GLRenderDevice::GLRenderDevice()
        : RenderDevice()
    {

    }

    GLRenderDevice::~GLRenderDevice()
    {

    }

    bool GLRenderDevice::open()
    {
        char* vendor = (char*)glGetString(GL_VENDOR);
        char* renderer = (char*)glGetString(GL_RENDERER);
        char* version = (char*)glGetString(GL_VERSION);

        return true;
    }

    void GLRenderDevice::dispatch(RenderContext * context_)
    {
        // do actual command
        // in stingray, this is done by GLRenderContext, which is an internal
        // class within GLRenderDevice and has nothing to do with RenderContext
        // XXXRenderDevice may hold an immediate_context. For deferred rendering
        // there might be other context, need investigation

        // For current dev stage, we simply let the device do the actual command
        for (RenderContext::Command& command : context_->commands())
        {
            if (RenderContext::CommandType::UPDATE_INDEX_BUFFER == command.command_type)
            {
                RenderContext::IndexCmdStream* c_stream = static_cast<RenderContext::IndexCmdStream*>(command.head);
                _newIndexBuf = c_stream->bufHandle;
                _indexFormat = c_stream->idxFormat;
                delete c_stream;
            }
            else if (RenderContext::CommandType::UPDATE_VERTEX_BUFFER == command.command_type)
            {

            }
        }
    }

    uint32 GLRenderDevice::createVertexBuffer(uint32 size, const void * data)
    {
        GLBuffer buf;
        buf.type = GL_ARRAY_BUFFER;
        buf.size = size;
        glGenBuffers(1, &buf.glObj);
        glBindBuffer(buf.type, size, data, GL_DYNAMIC_DRAW);
        glBindBuffer(buf.type, 0);

        return _buffers.add(buf);
    }

    uint32 GLRenderDevice::createIndexBuffer(uint32 size, const void * data)
    {
        GLBuffer buf;

        buf.type = GL_ELEMENT_ARRAY_BUFFER;
        buf.size = size;
        glGenBuffers(1, &buf.glObj);
        glBindBuffer(buf.type, buf.glObj);
        glBufferData(buf.type, size, data, GL_DYNAMIC_DRAW);
        glBindBuffer(buf.type, 0);

        return _buffers.add(buf);
    }

    void GLRenderDevice::destroyBuffer(uint32 bufObj)
    {
        if (0 == bufObj) return;

        GLBuffer& buf = _buffers.getRef(bufObj);
        glDeleteBuffers(1, &buf.glObj);

        _buffers.remove(bufObj);
    }

    void GLRenderDevice::updateBufferData(uint32 bufObj, uint32 offset, uint32 size, void * data)
    {
        const GLBuffer& buf = _buffers.getRef(bufObj);
        TE_ASSERT(offset + size <= buf.size, "offset + size should be no larger than buf.size!");

        glBindBuffer(buf.type, buf.glObj);
        
        if (0 == offset && size == buf.size)
        {
            glBufferData(buf.type, size, data, GL_DYNAMIC_DRAW);
            return;
        }

        glBufferSubData(buf.type, offset, size, data);
    }

    const char* GLRenderDevice::getDefaultVSCode()
    {
        return defaultShaderVS;
    }

    const char* GLRenderDevice::getDefaultFSCode()
    {
        return defaultShaderFS;
    }

    uint32 GLRenderDevice::createShader(const char * vertexShaderSrc, const char * fragmentShaderSrc)
    {
        uint32 programObj = createShaderProgram(vertexShaderSrc, fragmentShaderSrc);
        if (0 == programObj) return 0;
        if (!linkShaderProgram(programObj)) return 0;

        uint32 shaderHandle = _shaders.add(GLShader());
        GLShader& shader = _shaders.getRef(shaderHandle);
        shader.oglProgramObj = programObj;

        return shaderHandle;
    }

    uint32 GLRenderDevice::createShaderProgram(const char * vertexShaderSrc, const char * fragmentShaderSrc)
    {
        int infologLength = 0;
        int charsWritten = 0;
        char *infoLog = 0x0;
        int status;

        // vertex shader
        uint32 vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertexShaderSrc, 0x0);
        glCompileShader(vs);
        glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            // Get info
            glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &infologLength);
            if (infologLength > 1)
            {
                infoLog = new char[infologLength];
                glGetShaderInfoLog(vs, infologLength, &charsWritten, infoLog);
                _shaderLog = _shaderLog + "[Vertex Shader]\n" + infoLog;
                delete[] infoLog; infoLog = 0x0;
            }

            glDeleteShader(vs);
            return 0;
        }

        // Fragment shader
        uint32 fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragmentShaderSrc, 0x0);
        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &infologLength);
            if (infologLength > 1)
            {
                infoLog = new char[infologLength];
                glGetShaderInfoLog(fs, infologLength, &charsWritten, infoLog);
                _shaderLog = _shaderLog + "[Fragment Shader]\n" + infoLog;
                delete[] infoLog; infoLog = 0x0;
            }

            glDeleteShader(vs);
            glDeleteShader(fs);
            return 0;
        }

        // Shader program
        uint32 program = glCreateProgram();
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    bool GLRenderDevice::linkShaderProgram(uint32 programObj)
    {
        int infologLength = 0;
        int charsWritten = 0;
        char *infoLog = 0x0;
        int status;

        _shaderLog = "";

        glLinkProgram(programObj);
        glGetProgramiv(programObj, GL_INFO_LOG_LENGTH, &infologLength);
        if (infologLength > 1)
        {
            infoLog = new char[infologLength];
            glGetProgramInfoLog(programObj, infologLength, &charsWritten, infoLog);
            _shaderLog = _shaderLog + "[Linking]\n" + infoLog;
            delete[] infoLog; infoLog = 0x0;
        }

        glGetProgramiv(programObj, GL_LINK_STATUS, &status);
        if (!status) return false;

        return true;
    }

    int GLRenderDevice::getShaderConstLoc(uint32 shaderHandle, const char* name)
    {
        GLShader& shader = _shaders.getRef(shaderHandle);
        return glGetUniformLocation(shader.oglProgramObj, name);
    }

    void GLRenderDevice::bindShader(uint32 shaderHandle)
    {
        if (0 != shaderHandle)
        {
            GLShader& shader = _shaders.getRef(shaderHandle);
            glUseProgram(shader.oglProgramObj);
        }
        else
        {
            glUseProgram(0);
        }

        _curShaderHandle = shaderHandle;
    }
}