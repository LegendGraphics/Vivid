#ifndef COMMON_NODE_H
#define COMMON_NODE_H

#include <vector>
#include <type_traits>

#include "base/Ref.h"
#include "base/Refptr.hpp"
#include "common/Clone.h"
#include "common/ClassType.hpp"
#include "common/Resource.h"
#include "common/Component.h"
#include "common/ComponentContainer.h"


namespace te
{

    class NodeVisitor;

    class Node;
    class NodeTree;
    using NodePtr = RefPtr<Node>;
    using NodeTreePtr = RefPtr<NodeTree>;
    using NodeTreeList = std::vector<NodeTreePtr>;

    // some special nodes
    enum class NodeType
    {
        NODE,
        CAMERA,
        SCENE
    };

    class Node: public Ref, public Cloneable
    {
    public:
        static Node* create(const String& res);
    public:
        Node();
        Node(const Node& node, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~Node();

        friend class CopyOperator;
        ENABLE_CLONE(Node);

        void setVisible(bool visible);
        inline bool getVisible() { return _visible; }

        inline NodeType getNodeType() { return _node_type; }

        template <typename C, typename ... Args>
        C* addComponent(Args&& ... args);

        template <typename C>
        void removeComponent();

        template <typename C>
        C* getComponent();

        template <typename C>
        bool hasComponent();

        // need to check type, slower than template methods
        void addComponent(Component* component);
        void removeComponent(ComponentType type);
        Component* getComponent(ComponentType type);
        bool hasComponent(ComponentType type);

        void updateComponents();

    private:
        void addComponent(Component* component, int component_id);
        void removeComponent(int component_id);
        Component* getComponent(int component_id);
        bool hasComponent(int component_id);

    protected:
        bool        _visible;
        NodeType    _node_type;
        ComponentContainer _component_container;
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
    bool Node::hasComponent()
    {
        static_assert(std::is_base_of<Component, C>(), "C is not a component, cannot determine if node has C");
        return hasComponent(getComponentTypeId<C>());
    }


    class NodeTree : public Ref, public Cloneable
    {
    public:
        NodeTree();
        NodeTree(Node* node);
        NodeTree(const NodeTree& node_tree, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~NodeTree();

        friend class CopyOperator;
        ENABLE_CLONE(NodeTree);

        NodePtr node() const { return _node; }
        void attachNode(Node* node);
        void unattachNode();

        void addChildTree(NodeTree* child);
        void removeChildTree(NodeTree* child);
        inline NodeTreeList& getChildrenTree() { return _children; }
        inline NodeTree* getChildTree(int index) { return _children[index].get(); }

        void setParentTree(NodeTree* parent);
        inline NodeTree* getParentTree() { return _parent; }
        inline bool hasParentTree() { return _parent != nullptr; }

        virtual void accept(NodeVisitor* node_visitor);
        void ascend(NodeVisitor* node_visitor);
        void descend(NodeVisitor* node_visitor);
    protected:
        NodePtr             _node;
        NodeTreeList        _children;
        NodeTree*           _parent; // cycle reference problem, so using raw pointer
    };


    class MetaNode : public Resource
    {
    private:
        typedef std::vector<Component*>  MetaComponents;
    public:
        MetaComponents  components;

        friend class ResourceLoader;

        virtual bool load(const String& res);
        virtual void unload();
    };

    using MetaNodePtr = RefPtr<MetaNode>;

    class MetaNodeManager : public ResourceManager
    {
    public:
        MetaNodeManager();
        ~MetaNodeManager();

        ResourceHandle create(const String& res);

        MetaNodePtr   getMetaNode(ResourceHandle handle);
        MetaNodePtr   getMetaNode(const String& res);
    };
}

#endif // COMMON_NODE_H