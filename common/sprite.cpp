#include <sstream>
#include <SOIL.h>

#include "common/sprite.h"
#include "common/node_visitor.h"
#include "common/image.h"
#include "common/animation.h"
#include "renderer/gl_program.h"
#include "renderer/gl_texture.h"
#include "renderer/gl_databuffer.h"
#include "renderer/renderer.h"
#include "base/director.h"
#include "math/transform.h"

std::string Sprite::VERTEX_SHADER = "glshader_texture.vert";
std::string Sprite::FRAGMENT_SHADER = "glshader_texture.frag";

int Sprite::SPRITE_ID = 0;

Sprite::Sprite()
:_image(new Image),
_ui(false)
{
    setAnchorPoint(0.5, 0.5);

    _id = SPRITE_ID;
    SPRITE_ID ++;
}

Sprite::~Sprite()
{
}


bool Sprite::loadTexture(Image* image)
{
    _image = image;
    return true;
}

bool Sprite::loadTexture(const std::string& image_file)
{
    if (_image->load(image_file))
    {
        setContentSize((float)_image->getWidth(), (float)_image->getHeight());
        return true;
    }
    else return false;
}

void Sprite::accept(NodeVisitor* node_visitor)
{
    node_visitor->apply(this);
}

void Sprite::draw(Renderer* renderer)
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
    
    Transform mvp = _ui != true ? (ortho_transform * view_transform * model_transform) : (ortho_transform * model_transform);

    data_buffer->setPosition(position_array);
    data_buffer->setTexture(texture_array);
    data_buffer->setElement(element_array, 6);
    data_buffer->bind();
    data_buffer->locateAttribute();
    data_buffer->locateUniform(shader, mvp);


    texture->load(_image.get());
    texture->bind();

    glEnable(GL_BLEND);  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    // Draw a rectangle from the 2 triangles using 6 indices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDisable(GL_BLEND);

    data_buffer->clear();
    texture->clear();
    shader->clear();

}

void Sprite::updateInLocalReference()
{
    Vec2 origin = Vec2(0.0, 0.0);
    Vec2 t = _anchor_point;
    Size size = _content_size;
    TE_ASSERT(!size.hasZero(), "Please set right sprite's size");

    _v0 = Vec2(origin.x()-t.x()*size.width, origin.y()-t.y()*size.height);
    _v1 = Vec2(origin.x()+(1-t.x())*size.width, origin.y()-t.y()*size.height);
    _v2 = Vec2(origin.x()+(1-t.x())*size.width, origin.y()+(1-t.y())*size.height);
    _v3 = Vec2(origin.x()-t.x()*size.width, origin.y()+(1-t.y())*size.height);
}

void Sprite::updateInWorldReference()
{
    assembleTransform();
}

void Sprite::update(float delta_time)
{
}

void Sprite::registerAnimation(const std::string& anim_name, Animation* animation)
{
    // patch for different sprites with the same animation name...
    std::stringstream ss;
    ss << _id;
    std::string wrapped_anim_name = ss.str() + anim_name;

    if (_animations.find(wrapped_anim_name) == _animations.end())
    {
        _animations.insert(std::make_pair(wrapped_anim_name, animation));
        animation->bindSprite(this);   
    }
}


void Sprite::play(const std::string& anim_name)
{
    // patch for different sprites with the same animation name...
    std::stringstream ss;
    ss << _id;
    std::string wrapped_anim_name = ss.str() + anim_name;

    if (_animations.find(wrapped_anim_name) == _animations.end())
        TE_ERROR("Animation doesn't exists!");
    else
    {
        Director* director = Director::getInstance();
        director->getScheduler()->schedule(wrapped_anim_name, new TimerAnimationCallback(_animations[wrapped_anim_name].get(), wrapped_anim_name, 0));
    }
    
}

void Sprite::stop(const std::string& anim_name)
{
    // patch for different sprites with the same animation name...
    std::stringstream ss;
    ss << _id;
    std::string wrapped_anim_name = ss.str() + anim_name;

    if (_animations.find(wrapped_anim_name) == _animations.end())
        TE_ERROR("Animation doesn't exists!");
    else
    {
        Director* director = Director::getInstance();
        director->getScheduler()->unschedule(wrapped_anim_name);
    }
}

void Sprite::setUI(bool ui)
{
    _ui = ui;
}
