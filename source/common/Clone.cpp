#include "common/Clone.h"
#include "common/Node.h"


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


}

