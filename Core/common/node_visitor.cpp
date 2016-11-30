
#include "common/node_visitor.h"
#include "common/node.h"
#include "common/sprite.h"
#include "common/scene.h"
#include "ui/ui_widget.h"

NodeVisitor::NodeVisitor()
:_renderer(NULL)
{
}

NodeVisitor::~NodeVisitor()
{}

void NodeVisitor::attachRenderer(Renderer* renderer)
{
    _renderer = renderer;
}

void NodeVisitor::apply(Node* node)
{
    node->draw(_renderer.get());
}

void NodeVisitor::apply(Sprite* sprite)
{
    sprite->draw(_renderer.get());
}

void NodeVisitor::apply(Scene* scene)
{
    scene->draw(_renderer.get());
}

void NodeVisitor::apply(Camera* camera)
{

}

void NodeVisitor::apply(UIWidget* ui_widget)
{
    ui_widget->draw(_renderer.get());
}
