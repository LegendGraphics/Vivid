
#include <algorithm>

#include "common/Node.h"
#include "common/NodeVisitor.h"
#include "common/Component.h"
#include "common/ComponentContainer.h"
#include "common/SpaceState.h"
#include "common/MeshFilter.h"
#include "base/EventDispatcher.h"
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
        :_parent(nullptr),
        _visible(true),
        _component_container(new ComponentContainer(this))
    {

    }

    Node::Node(const Node& node, const CopyOperator& copyop)
        /*:_parent(node._parent),
        _visible(node._visible),
        _component_container(copyop(node._component_container))*/
    {
    }

    Node::~Node(){}

    void Node::setParent(Node* parent)
    {
        _parent = parent;
    }

    void Node::addChild(Node* child)
    {
        //child->setParent(this);
        _children.insert(_children.end(), child);
    }

    void Node::removeChild(Node* child)
    {
        //_children.erase(std::remove(_children.begin(), _children.end(), child));
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
        component->setOwner(this);
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

    void Node::updateComponents()
    {
        _component_container->updateAll();
    }

    /*Matrix Node::getWorldMatrix()
    {
        ParentPathVisitor ppv;
        this->accept(ppv);
        
        NodePath* parent_path = ppv.getParentPath();
        if (parent_path->empty()) return Matrix::identity();
        else return te::computeLocalToWorld(parent_path);
    }*/

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