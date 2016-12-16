#ifndef RENDERER_GLPROGRAM_H
#define RENDERER_GLPROGRAM_H

#include <string>
#include <gl/glew.h>

#include "base/ref.h"

class GLProgram: public Ref 
{
public:
    GLProgram();
    virtual ~GLProgram();

    bool load(const std::string& vertex_shader, const std::string& fragment_shader);
    bool link();
    void use();

    void clear();

    GLuint& getGLProgram() { return _program; }

private:
    bool initShaders(GLchar* vertex_source, GLchar* fragment_source);
    bool compileShader(GLuint * shader, GLenum type, const GLchar* source);
    

private:
    GLuint _program;
    GLuint _vertex_shader;
    GLuint _fragment_shader;
};


#endif // RENDERER_GLPROGRAM_H