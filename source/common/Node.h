#ifndef COMMON_NODE_H
#define COMMON_NODE_H

#include <vector>
#include <type_traits>

#include "base/ref.h"
#include "base/refptr.hpp"
#include "common/object.h"
#include "common/ClassType.hpp"

namespace te
{

    class NodeVisitor;
    class ComponentContainer;
    class Component;

    //typedef std::vector<Node*> NodePath;

    class Node: public Object
    {
    public:
        Node();
		Node(const Node& node, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~Node();

		OBJECT_META_FUNCTION(Node);

        void addChild(Node* child);
        void removeChild(Node* child);
        inline std::vector<RefPtr<Node>>& getChildren() { return _children; }
        inline Node* getChild(int index) { return _children[index].get(); }

        void setParent(Node* parent);
        inline Node* getParent() { return _parent; }

        inline bool hasParent() { return _parent != nullptr; }

        void setVisible(bool visible);
        inline bool getVisible() { return _visible; }

        virtual void accept(NodeVisitor* node_visitor);
        virtual void ascend(NodeVisitor* node_visitor);
        virtual void descend(NodeVisitor* node_visitor);

       // Matrix getWorldMatrix();

        template <typename C, typename ... Args>
        C* addComponent(Args&& ... args);

        template <typename C>
        void removeComponent();

        template <typename C>
        C* getComponent();

        template <typename C>
        bool hasComponent() const;

    private:
        void addComponent(Component* component, int component_id);
        void removeComponent(int component_id);
        Component* getComponent(int component_id);
        bool hasComponent(int component_id);

    protected:
        std::vector<RefPtr<Node>> _children;
        Node* _parent;

        bool _visible;

        ComponentContainer* _component_container;
    };

    template <typename C, typename ... Args>
    C* Node::addComponent(Args&& ... args)
    {
        static_assert(std::is_base_of<Component, C>(), "C is not a component, cannot add C to node");
        auto component = new C{std::forward<Args>(args)...};
        addComponent(component, getComponentTypeId<C>());
        return component;
    }

    template <typename C>
    void Node::removeComponent()
    {
        static_assert(std::is_base_of<Component, C>(), "C is not a component, cannot remove C from node");
        removeComponent(getComponentTypeId<C>());
    }

    template <typename C>
    C* Node::getComponent()
    {
        static_assert(std::is_base_of<Component, C>(), "C is not a component, cannot retrieve C from node");
        return static_cast<C*>(getComponent(getComponentTypeId<C>()));
    }

    template <typename C>
    bool Node::hasComponent() const
    {
        static_assert(std::is_base_of<Component, C>(), "C is not a component, cannot determine if node has C");
        return hasComponent(getComponentTypeId<C>());
    }

}

#endif // COMMON_NODE_H