
#include <algorithm>

#include "common/Node.h"
#include "common/NodeVisitor.h"
#include "common/SpaceState.h"
#include "common/MeshFilter.h"
#include "io/ResourceLoader.h"

namespace te
{

    Node* Node::create(const String& res)
    {
        Node* node = new Node;
        ResourceHandle handle = ResourceMapper::getInstance()->get<MetaNodeManager>()->create(res);
        MetaNodePtr meta_node = ResourceMapper::getInstance()->get<MetaNodeManager>()->getMetaNode(handle);
        for (auto& component : meta_node->components)
        {
            node->addComponent(component);
        }
        return node;
    }

    Node::Node()
        :_visible(true),
        _component_container(this)
    {

    }

    Node::Node(const Node& node, const CopyOperator& copyop)
    {
        copyop(&node);
    }

    Node::~Node()
    {
    }

    void Node::setVisible(bool visible)
    {
        _visible = visible;
    }

    void Node::addComponent(Component* component, int component_id)
    {
        _component_container.add(component, component_id);
        component->setOwner(this);
    }

    void Node::removeComponent(int component_id)
    {
        _component_container.remove(component_id);
    }

    Component* Node::getComponent(int component_id)
    {
        return _component_container.get(component_id);
    }

    bool Node::hasComponent(int component_id)
    {
        return _component_container.has(component_id);
    }

    void Node::updateComponents()
    {
        _component_container.updateAll();
    }

    void Node::addComponent(Component* component)
    {
        ComponentType type = component->getType();
        if (type == ComponentType::SPACE_STATUS)
            addComponent(component, getComponentTypeId<SpaceState>());
        else if (type == ComponentType::MESH_FILTER)
            addComponent(component, getComponentTypeId<MeshFilter>());
    }

    void Node::removeComponent(ComponentType type)
    {
        if (type == ComponentType::SPACE_STATUS)
            removeComponent(getComponentTypeId<SpaceState>());
        else if (type == ComponentType::MESH_FILTER)
            removeComponent(getComponentTypeId<MeshFilter>());
    }

    Component* Node::getComponent(ComponentType type)
    {
        if (type == ComponentType::SPACE_STATUS)
            return getComponent(getComponentTypeId<SpaceState>());
        else if (type == ComponentType::MESH_FILTER)
            return getComponent(getComponentTypeId<MeshFilter>());
        else return nullptr;
    }

    bool Node::hasComponent(ComponentType type)
    {
        if (type == ComponentType::SPACE_STATUS)
            return hasComponent(getComponentTypeId<SpaceState>());
        else if (type == ComponentType::MESH_FILTER)
            return hasComponent(getComponentTypeId<MeshFilter>());
        else return false;
    }


    NodeTree::NodeTree()
        :_node(nullptr),
        _parent(nullptr)
    {}

    NodeTree::NodeTree(Node* node)
        :_node(node),
        _parent(nullptr)
    {}

    NodeTree::NodeTree(const NodeTree& node_tree, const CopyOperator& copyop)
    {
        copyop(&node_tree);
    }

    NodeTree::~NodeTree()
    {}

    void NodeTree::attachNode(Node* node)
    {
        _node = node;
    }

    void NodeTree::unattachNode()
    {
        _node = nullptr;
    }

    void NodeTree::setParentTree(NodeTree* parent)
    {
        _parent = parent;
    }

    void NodeTree::addChildTree(NodeTree* child)
    {
        child->setParentTree(this);
        _children.push_back(child);
    }

    void NodeTree::removeChildTree(NodeTree* child)
    {
        child->setParentTree(nullptr);
        //_children.erase(std::remove(_children.begin(), _children.end(), child));
    }

    void NodeTree::accept(NodeVisitor* node_visitor)
    {
        node_visitor->apply(this);
    }

    void NodeTree::ascend(NodeVisitor* node_visitor)
    {
        if (_parent) _parent->accept(node_visitor);
    }

    void NodeTree::descend(NodeVisitor* node_visitor)
    {
        for (auto& itr = _children.begin(); itr != _children.end(); itr++)
            (*itr)->accept(node_visitor);
    }



    bool MetaNode::load(const String& res)
    {
        return ResourceLoader::load(this, res);
    }

    void MetaNode::unload()
    {

    }

    MetaNodeManager::MetaNodeManager()
        :ResourceManager(ResourceType::Mesh)
    {}

    MetaNodeManager::~MetaNodeManager() {}

    ResourceHandle MetaNodeManager::create(const String& res)
    {
        if (ResourceHandle handle = getResourceHandle(res)) return handle;
        else
        {
            MetaNodePtr meta_node = new MetaNode;
            if (meta_node->load(res))
            {
                meta_node->descriptor(buildDescriptor(res));
                add(meta_node.get());
                return getResourceHandle(res);
            }
            else return 0;
        }
    }

    MetaNodePtr MetaNodeManager::getMetaNode(ResourceHandle handle)
    {
        if (has(handle)) return dynamic_cast_ptr<Resource, MetaNode>(getResourcePtr(handle));
        else return nullptr;
    }

    MetaNodePtr MetaNodeManager::getMetaNode(const String& res)
    {
        return getMetaNode(getResourceHandle(res));
    }

}