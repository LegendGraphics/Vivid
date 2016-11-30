
#include "ui/ui_widget.h"

#include "common/node_visitor.h"
#include "common/image.h"
#include "renderer/gl_program.h"
#include "renderer/gl_texture.h"
#include "renderer/gl_databuffer.h"
#include "renderer/renderer.h"
#include "base/director.h"
#include "math/transform.h"

std::string UIWidget::VERTEX_SHADER = "glshader_texture.vert";
std::string UIWidget::FRAGMENT_SHADER = "glshader_texture.frag";

UIWidget::UIWidget():
_has_image(false),
_image(new Image)
{

}

UIWidget::~UIWidget()
{

}

void UIWidget::updateInLocalReference()
{
    Vec2 origin = Vec2(0.0, 0.0);
    Vec2 t = _anchor_point;
    Size size = _content_size;
    TE_ASSERT(!size.hasZero(), "Please set right widget's size");

    _v0 = Vec2(origin.x()-t.x()*size.width, origin.y()-t.y()*size.height);
    _v1 = Vec2(origin.x()+(1-t.x())*size.width, origin.y()-t.y()*size.height);
    _v2 = Vec2(origin.x()+(1-t.x())*size.width, origin.y()+(1-t.y())*size.height);
    _v3 = Vec2(origin.x()-t.x()*size.width, origin.y()+(1-t.y())*size.height);
}

void UIWidget::updateInWorldReference()
{
    assembleTransform();
}

void UIWidget::accept(NodeVisitor* node_visitor)
{
    node_visitor->apply(this);
}

void UIWidget::draw(Renderer* renderer)
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
    const Transform& ortho_transform = camera->getOrthoTransform();

    Transform mvp = ortho_transform * model_transform;

    data_buffer->setPosition(position_array);
    data_buffer->setTexture(texture_array);
    data_buffer->setElement(element_array, 6);
    data_buffer->bind();
    data_buffer->locateAttribute();
    data_buffer->locateUniform(shader, mvp);

    
    if (_has_image)
    {
        texture->load(_image.get());
        texture->bind();
    }

    glEnable(GL_BLEND);  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
 
    // Draw a rectangle from the 2 triangles using 6 indices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDisable(GL_BLEND);

    data_buffer->clear();
    texture->clear();
    shader->clear();
}

// absolute layout
bool UIWidget::isInWidget(float x, float y)
{
    const Size& window_size = Director::getInstance()->getWindowSize();
    y = window_size.height - y;

    Vec2 origin = _world_position;
    Vec2 t = _anchor_point;
    Size size = _content_size;
    TE_ASSERT(!size.hasZero(), "Please set right widget's size");

    Vec2 left_bottom = Vec2(origin.x()-t.x()*size.width, origin.y()-t.y()*size.height);
    Vec2 right_top = Vec2(origin.x()+(1-t.x())*size.width, origin.y()+(1-t.y())*size.height);

    if (y >= left_bottom.y() && y <= right_top.y() && x >= left_bottom.x() && x <= right_top.x())
        return true;
    else
        return false;
}

void UIWidget::setWidgetName(const std::string& name)
{
    _name = name;
}

UIWidget* UIWidget::seekWidgetByName(const std::string& name)
{
    if (_name == name) return this;

    if (_children.empty()) return NULL;

    for (int i = 0, i_end = _children.size(); i < i_end; ++ i)
    {
        UIWidget* child_widget = dynamic_cast<UIWidget*>(_children[i]);
        UIWidget* widget = child_widget->seekWidgetByName(name);
        if (widget) return widget;
    }

    return NULL;
}
