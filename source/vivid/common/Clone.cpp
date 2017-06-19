#include "vivid/common/Clone.h"
#include "vivid/common/Node.h"
#include "vivid/common/Component.h"
#include "vivid/common/ComponentContainer.h"
#include "vivid/common/Scene.h"
#include "vivid/common/Camera.h"

namespace te
{
    Node* CopyOperator::operator()(const Node* node) const
    {
        if (_flag == SHALLOW_COPY)
        {
            Node* copied = const_cast<Node*>(node);
            return copied;
        }
        else
        {
            Node* copied = new Node;
            // copy components
            return copied;
        }
    }

    NodeTree* CopyOperator::operator()(const NodeTree* node_tree) const
    {
        if (_flag == SHALLOW_COPY)
        {
            NodeTree* copied = const_cast<NodeTree*>(node_tree);
            return copied;
        }
        else
        {
            NodeTree* copied = new NodeTree;
            // copy the whole tree
            return copied;
        }
    }

    Component* CopyOperator::operator()(const Component* component) const
    {
        if (_flag == SHALLOW_COPY)
        {
            Component* copied = const_cast<Component*>(component);
            return copied;
        }
        else
        {
            Component* copied = new Component;
            // copy the all components
            return copied;
        }
    }

    ComponentContainer* CopyOperator::operator()(const ComponentContainer* ccontainer) const
    {
        if (_flag == SHALLOW_COPY)
        {
            ComponentContainer* copied = const_cast<ComponentContainer*>(ccontainer);
            return copied;
        }
        else
        {
            ComponentContainer* copied = new ComponentContainer;
            // copy the all components
            return copied;
        }
    }

    Scene* CopyOperator::operator()(const Scene* scene) const
    {
        if (_flag == SHALLOW_COPY)
        {
            Scene* copied = const_cast<Scene*>(scene);
            return copied;
        }
        else
        {
            Scene* copied = new Scene;
            // copy the all components
            return copied;
        }
    }

    Camera* CopyOperator::operator()(const Camera* camera) const
    {
        if (_flag == SHALLOW_COPY)
        {
            Camera* copied = const_cast<Camera*>(camera);
            return copied;
        }
        else
        {
            Camera* copied = new Camera;
            // copy the all components
            return copied;
        }
    }

}

