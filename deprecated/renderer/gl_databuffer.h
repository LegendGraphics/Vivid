#ifndef RENDERER_GL_DATABUFFER_H
#define RENDERER_GL_DATABUFFER_H

#include <gl/glew.h>

#include "base/ref.h"
#include "math/vec2.h"
#include "math/transform.h"

class GLProgram;

// now seriously couple with particular shader...
class GLDataBuffer: public Ref
{
public:
    GLDataBuffer();
    ~GLDataBuffer();

    void setPosition(const Vec2Array& pos_array);
    void setTexture(const Vec2Array& tex_array);
  //  void setElement(const Vec3Array& tex_array); more general function needed
    void setElement(GLuint element_array[], int length);

    inline GLuint getPositionBuffer() { return _position_buffer; }
    inline GLuint getTextureBuffer() { return _texture_buffer; }
    inline GLuint getElementBuffer() { return _element_buffer; }

    void bind();
    void clear();

    void locateAttribute();
    void locateUniform(GLProgram* shader, Transform& mvp);

private:
    void setVertextArray();
    void setVertexBuffer();
    void setElementBuffer();

private:
    GLuint _vertex_array;
    // vertex consists of position, texture and color etc.
    GLuint _position_buffer;
    GLuint _texture_buffer;
    GLuint _element_buffer;

    GLfloat* _position_array;
    GLfloat* _texture_array;
    GLuint* _element_array;

    GLsizeiptr _position_length;
    GLsizeiptr _texture_length;
    GLsizeiptr _element_length;

};
#endif // RENDERER_GL_DATABUFFER_H