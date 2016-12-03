
#include <algorithm>

#include "common/node.h"
#include "common/node_visitor.h"

#include "common/component.h"
#include "common/component_container.h"


namespace te
{

    Node::Node()
        :_parent(nullptr),
        _visible(true)
    {

    }

    Node::~Node(){}

    void Node::setParent(Node* parent)
    {
        _parent = parent;
    }

    void Node::addChild(Node* child)
    {
        child->setParent(this);
        _children.insert(_children.end(), child);
    }

    void Node::removeChild(Node* child)
    {
        _children.erase(std::remove(_children.begin(), _children.end(), child));
    }

    void Node::setVisible(bool visible)
    {
        _visible = visible;
    }

    void Node::accept(NodeVisitor* node_visitor)
    {
        node_visitor->apply(this);
    }

    void Node::ascend(NodeVisitor* node_visitor)
    {
        if (_parent) _parent->accept(node_visitor);
    }

    void Node::descend(NodeVisitor* node_visitor)
    {
        for (auto& itr = _children.begin(); itr != _children.end(); itr ++)
            (*itr)->accept(node_visitor);
    }

    void Node::addComponent(Component* component, int component_id)
    {
        _component_container->add(component, component_id);
    }

    void Node::removeComponent(int component_id)
    {
        _component_container->remove(component_id);
    }

    Component* Node::getComponent(int component_id)
    {
        return _component_container->get(component_id);
    }

    bool Node::hasComponent(int component_id)
    {
        return _component_container->has(component_id);
    }

    Matrix Node::getWorldMatrix()
    {
        ParentPathVisitor ppv;
        this->accept(ppv);
        
        NodePath* parent_path = ppv.getParentPath();
        if (parent_path->empty()) return Matrix::identity();
        else return te::computeLocalToWorld(parent_path);
    }
}