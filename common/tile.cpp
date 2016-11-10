#include <SOIL.h>

#include "common/tile.h"
#include "common/node_visitor.h"
#include "common/image.h"
#include "renderer/gl_program.h"
#include "renderer/gl_texture.h"
#include "renderer/gl_databuffer.h"
#include "renderer/renderer.h"
#include "base/director.h"
#include "math/transform.h"

std::string Tile::VERTEX_SHADER = "glshader_texture.vert";
std::string Tile::FRAGMENT_SHADER = "glshader_texture.frag";


Tile::Tile()
:_image(new Image)
{
}

Tile::Tile(Image* image)
:_image(image)
{
    setContentSize((float)_image->getWidth(), (float)_image->getHeight());
}

Tile::~Tile()
{
}

void Tile::draw(Renderer* renderer)
{
    GLDataBuffer* data_buffer = renderer->getGLDataBuffer();
    GLProgram* shader = renderer->getGLProgram();
    GLTexture* texture = renderer->getGLTexture();

    shader->load(VERTEX_SHADER, FRAGMENT_SHADER);
    shader->link();
    shader->use();


    Vec2Array position_array, texture_array;

    updateInLocalReference();
    updateInWorldReference();

    position_array.push_back(_v0);
    position_array.push_back(_v1);
    position_array.push_back(_v2);
    position_array.push_back(_v3);

    texture_array.push_back(Vec2(0.0f, 1.0f)); 
    texture_array.push_back(Vec2(1.0f, 1.0f));    
    texture_array.push_back(Vec2(1.0f, 0.0f));
    texture_array.push_back(Vec2(0.0f, 0.0f));

    GLuint element_array[] = {
        0, 1, 2,
        2, 3, 0
    };

    RefPtr<Camera> camera = Director::getInstance()->getActiveScene()->getActiveCamera();
    const Transform& model_transform = _transform;
    const Transform& view_transform = camera->getViewTransform();
    const Transform& ortho_transform = camera->getOrthoTransform();

    Transform mvp = ortho_transform * view_transform * model_transform;

    data_buffer->setPosition(position_array);
    data_buffer->setTexture(texture_array);
    data_buffer->setElement(element_array, 6);
    data_buffer->bind();
    data_buffer->locateAttribute();
    data_buffer->locateUniform(shader, mvp);


    texture->load(_image.get());
    texture->bind();
  
    // Draw a rectangle from the 2 triangles using 6 indices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    data_buffer->clear();
    texture->clear();
    shader->clear();

}

void Tile::updateInLocalReference()
{
    Vec2 origin = Vec2(0.0, 0.0);
    Vec2 t = _anchor_point;
    Size size = _content_size;
    TE_ASSERT(!size.hasZero(), "Please set right tile's size");

    _v0 = Vec2(origin.x()-t.x()*size.width, origin.y()-t.y()*size.height);
    _v1 = Vec2(origin.x()+(1-t.x())*size.width, origin.y()-t.y()*size.height);
    _v2 = Vec2(origin.x()+(1-t.x())*size.width, origin.y()+(1-t.y())*size.height);
    _v3 = Vec2(origin.x()-t.x()*size.width, origin.y()+(1-t.y())*size.height);
}

void Tile::updateInWorldReference()
{
    assembleTransform();
}