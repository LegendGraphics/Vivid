#ifndef COMMON_NODE_H
#define COMMON_NODE_H

#include <vector>
#include <type_traits>

#include "base/ref.h"
#include "base/refptr.hpp"


class NodeVisitor;
class Renderer;

class ComponentContainer;
class Component;

class Node: public Ref
{
public:
    Node();
    virtual ~Node();

    void addChild(Node* child);
    void removeChild(Node* child);
    inline std::vector<RefPtr<Node>>& getChildren() { return _children; }
    inline Node* getChild(int index) { return _children[index].get(); }

    void setParent(Node* parent);
    inline Node* getParent() { return _parent.get(); }

    void setVisible(bool visible);
    inline bool getVisible() { return _visible; }

    virtual void accept(NodeVisitor* node_visitor);
    virtual void draw(Renderer* renderer);
    virtual void update(float delta_time);

    void traversal(NodeVisitor* node_visitor);

    template <typename C, typename ... Args>
    C& addComponent(Args&& ... args);

    template <typename C>
    void removeComponent();

    template <typename C>
    C& getComponent() const;

    template <typename C>
    bool hasComponent() const;

private:
    void addComponent(Component* component);
    void removeComponent();
    Component& getComponent();
    bool hasComponent();

protected:
    std::vector<RefPtr<Node>> _children;
    RefPtr<Node> _parent;

    bool _visible;

    ComponentContainer* _component_container;
};

template <typename C, typename ... Args>
C& Node::addComponent(Args&& ... args);
{
    TE_ASSERT(std::is_base_of<Component, C>(), "C is not a component, cannot add C to node");
    auto component = new C{std::forward<Args>(args)...};
    // to do component type
    addComponent(component);
    return *component;
}

template <typename C>
void Node::removeComponent()
{
    TE_ASSERT(std::is_base_of<Component, C>(), "C is not a component, cannot remove C from node");
    removeComponent();
}

template <typename C>
C& Node::getComponent() const
{
    TE_ASSERT(std::is_base_of<Component, C>(), "C is not a component, cannot retrieve C from node");
    return static_cast<C&>(getComponent());
}

template <typename C>
bool Node::hasComponent() const
{
    static_assert(std::is_base_of<Component, C>(), "C is not a component, cannot determine if node has C");
    return hasComponent();
}

#endif // COMMON_NODE_H