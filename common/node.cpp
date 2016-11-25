
#include <algorithm>

#include "base/director.h"
#include "common/node.h"
#include "common/node_visitor.h"

#include "common/component.h"
#include "common/component_container.h"

Node::Node()
:_parent(NULL),
_local_z_order(0),
_position(0.0, 0.0),
_anchor_point(0.0, 0.0),
_content_size(0.0, 0.0),
_world_position(0.0, 0.0),
_visible(true)
{

}

Node::~Node(){}

void Node::setLocalZOrder(int local_z_order)
{
    _local_z_order = local_z_order;
    if (_parent)
        _parent->ReorderByZOrder(this);  
}

void Node::setParent(Node* parent)
{
    _parent = parent;
}

void Node::addChild(Node* child, int local_order)
{
    child->setLocalZOrder(local_order);
    child->setParent(this);
    insertChildByZOrder(child);  
}

void Node::addChild(Node* child)
{
    child->setParent(this);
    insertChildByZOrder(child);
}

void Node::removeChild(Node* child)
{
    _children.erase(std::remove(_children.begin(), _children.end(), child));
}

void Node::insertChildByZOrder(Node* child)
{
    int z_order = child->getLocalZOrder();
    for (std::vector<Node*>::iterator itr = _children.begin(); 
        itr != _children.end(); ++ itr)
    {
        int itr_order = (*itr)->getLocalZOrder();
        if (z_order > itr_order)
        {
            _children.insert(itr, child);
            return;
        }
    }
    _children.insert(_children.end(), child);
    return;
}

void Node::ReorderByZOrder(Node* child)
{
    removeChild(child);
    insertChildByZOrder(child);
}

void Node::setPosition(const Vec2& pos)
{
    _position = pos;
}

void Node::setPosition(float x, float y)
{
    _position = Vec2(x, y);
}

void Node::setAnchorPoint(const Vec2& anchor_point)
{
    _anchor_point = anchor_point;
}

void Node::setAnchorPoint(float x, float y)
{
    _anchor_point = Vec2(x, y);
}

void Node::setContentSize(const Size& content_size)
{
    _content_size = content_size;
}

void Node::setContentSize(float x, float y)
{
    _content_size = Size(x, y);
}

void Node::assembleTransform()
{
    if (!_parent)
    {
        Transform trans = Transform::trans(_position.x(), _position.y());
        _transform = trans;
        _world_position = Vec4to2(trans * Vec4(0, 0, 0, 1));
    }
    else
    {
        Transform trans = Transform::trans(_position.x(), _position.y());
        const Transform& p_t = _parent->getTransform();
        _transform = trans * p_t; //  local transform * parent transform
        _world_position = Vec4to2(_transform * Vec4(0, 0, 0, 1));
    }
    
}

void Node::setVisible(bool visible)
{
    _visible = visible;
}

void Node::accept(NodeVisitor* node_visitor)
{
    node_visitor->apply(this);
}

void Node::draw(Renderer* renderer)
{

}

// pre-order traversal
void Node::traversal(NodeVisitor* node_visitor)
{
    if (!_visible) return;

    this->accept(node_visitor);

    for (std::vector<Node*>::iterator child_itr = _children.begin(); child_itr != _children.end(); ++ child_itr)
    {
        (*child_itr)->traversal(node_visitor);
    }
}

void Node::update(float delta_time)
{

}

void Node::schedule(const std::string& key)
{
    Director* director = Director::getInstance();
    director->getScheduler()->schedule(key, new TimerNodeCallback(this, key, 0));
}

void Node::unschedule(const std::string& key)
{
    Director* director = Director::getInstance();
    director->getScheduler()->unschedule(key);
}

void Node::addEventListener(EventType event_type, Node* node)
{
    Director* director = Director::getInstance();
    director->getEventDispatcher()->addEventListener(new EventListener<dynam>(event_type, callback));
}


void Node::removeEventListener(EventType event_type)
{
    Director* director = Director::getInstance();
   // director->getEventDispatcher()->removeEventListener()
}

void Node::addComponent(Component* component)
{
    _component_container->add(component);
}

void Node::removeComponent(Component* component)
{
    _component_container->remove(component);
}