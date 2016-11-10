
#include <iostream>
#include <gl/glew.h>

#include "renderer/gl_databuffer.h"
#include "renderer/gl_program.h"
#include "base/data_types.h"
#include "base/director.h"
#include "math/transform.h"

GLDataBuffer::GLDataBuffer():
_vertex_array(0),
_position_buffer(0),
_texture_buffer(0),
_element_buffer(0),
_position_array(NULL),
_texture_array(NULL),
_element_array(NULL)
{

}

GLDataBuffer::~GLDataBuffer()
{
    clear();
    delete [] _position_array;
    delete [] _texture_array;
    delete [] _element_array;
}

void GLDataBuffer::bind()
{
    setVertextArray();
    setVertexBuffer();
    setElementBuffer();
}

void GLDataBuffer::clear()
{
    glDeleteBuffers(1, &_element_buffer);
    glDeleteBuffers(1, &_texture_buffer);
    glDeleteBuffers(1, &_position_buffer);
    glDeleteVertexArrays(1, &_vertex_array);
}

void GLDataBuffer::setVertextArray()
{
    // Create Vertex Array Object
    glGenVertexArrays(1, &_vertex_array);
    glBindVertexArray(_vertex_array);
}

void GLDataBuffer::setVertexBuffer()
{
    // Create a Vertex Buffer Object
    glGenBuffers(1, &_position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _position_buffer);
    glBufferData(GL_ARRAY_BUFFER, _position_length * sizeof(GLfloat), _position_array, GL_STATIC_DRAW);
 
    glGenBuffers(1, &_texture_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _texture_buffer);
    glBufferData(GL_ARRAY_BUFFER, _texture_length * sizeof(GLfloat), _texture_array, GL_STATIC_DRAW);
}

void GLDataBuffer::setElementBuffer()
{
    // Create an element array
    glGenBuffers(1, &_element_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _element_length * sizeof(GLuint), _element_array, GL_STATIC_DRAW);
}

void GLDataBuffer::locateAttribute()
{
    // 1st attribute buffer : position
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _position_buffer);
    glVertexAttribPointer(
        0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
        2,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
        );

    // 2nd attribute buffer : vertexUV
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, _texture_buffer);
    glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        2,                                // size : U+V => 2
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
        );

}

void GLDataBuffer::locateUniform(GLProgram* shader, Transform& mvp)
{
   GLint uniform_mvp = glGetUniformLocation(shader->getGLProgram(), "MVP");
   Size size = Director::getInstance()->getWindowSize();
   glUniformMatrix4fv(uniform_mvp, 1, GL_TRUE, mvp.getMatAddress());
}

void GLDataBuffer::setPosition(const Vec2Array& pos_array)
{
    if (_position_array != NULL) delete [] _position_array;

    _position_length = pos_array.size() * 2;
    _position_array = new GLfloat[_position_length];
    for (size_t i = 0, i_end = pos_array.size(); i < i_end; ++ i)
    {
        _position_array[2*i] = pos_array[i].x();
        _position_array[2*i+1] = pos_array[i].y();

    }
}

void GLDataBuffer::setTexture(const Vec2Array& tex_array)
{
    if (_texture_array != NULL) delete [] _texture_array;

    _texture_length = tex_array.size() * 2;
    _texture_array = new GLfloat[_texture_length];
    for (size_t i = 0, i_end = tex_array.size(); i < i_end; ++ i)
    {
        _texture_array[2*i] = tex_array[i].x();
        _texture_array[2*i+1] = tex_array[i].y();
    }
}

void GLDataBuffer::setElement(GLuint element_array[], int length)
{
    if (_element_array != NULL) delete [] _element_array;

    _element_length = length;
    _element_array = new GLuint[length];
    memcpy(_element_array, element_array, length * sizeof(GLuint));
}