
#include <gl/glew.h>
//#include <gl/glut.h>

#include "renderer/gl_program.h"
#include "base/macros.h"
#include "renderer/shader_loader.h"

GLProgram::GLProgram()
:_program(0),
_vertex_shader(0),
_fragment_shader(0)
{

}

GLProgram::~GLProgram()
{
    clear();
}

bool GLProgram::load(const std::string& vertex_shader, const std::string& fragment_shader)
{
    GLchar* vertex_source = NULL;
    GLchar* fragment_source = NULL;
    int ver_res = loadShader(vertex_shader.c_str(), vertex_source);
    int frag_res = loadShader(fragment_shader.c_str(), fragment_source);
    if (ver_res == 0 && frag_res == 0)
        return initShaders(vertex_source, fragment_source);
    else
    {
        TE_ERROR("Failed to load shaders!");
        return false;
    }
}

bool GLProgram::initShaders(GLchar* vertex_source, GLchar* fragment_source)
{
    _program = glCreateProgram();
    _vertex_shader = _fragment_shader = 0;

    if (vertex_source)
    {
        if (!compileShader(&_vertex_shader, GL_VERTEX_SHADER, vertex_source))
        {
            TE_ERROR("Failed to compile vertex shader!");
            return false;
        }
        glAttachShader(_program, _vertex_shader);
        unloadShader(vertex_source);
    }

    if (fragment_source)
    {
        if (!compileShader(&_fragment_shader, GL_FRAGMENT_SHADER, fragment_source))
        {
            TE_ERROR("Failed to compile fragment shader!");
            return false;
        }
        glAttachShader(_program, _fragment_shader);
        unloadShader(fragment_source);
    }

    return true;
}

bool GLProgram::compileShader(GLuint* shader, GLenum type, const GLchar* source)
{
    GLint status;
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, (const GLchar**)&source, NULL);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);

    if (!status)
    {
        GLsizei length;
        glGetShaderiv(*shader, GL_SHADER_SOURCE_LENGTH, &length);
        GLchar* src = (GLchar *)malloc(sizeof(GLchar) * length);

        glGetShaderSource(*shader, length, NULL, src);
        TE_ERROR("Failed to compile shader!");
        free(src);
        return false;
    }

    return (status == GL_TRUE);
}

bool GLProgram::link()
{
    TE_ASSERT(_program != 0, "Cannot link invalid program!");

    GLint status = GL_TRUE;

    glLinkProgram(_program);
    glGetProgramiv(_program, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
        TE_ERROR("Failed to link program!");
        glDeleteProgram(_program);
        _program = 0;
    }

    return (status == GL_TRUE);
}

void GLProgram::use()
{
    glUseProgram(_program);
}

void GLProgram::clear()
{
    glDeleteProgram(_program);
    glDeleteShader(_vertex_shader);
    glDeleteShader(_fragment_shader);
}
