
#include "common/NodeVisitor.h"
#include "common/Node.h"

namespace te
{
    NodeVisitor::NodeVisitor()
        :_traversal_mode(TraversalMode::TRAVERSE_NONE),
        _visitor_type(VisitorType::VISITOR_NODE)
    {
    }

    NodeVisitor::~NodeVisitor()
    {}

    void NodeVisitor::apply(Node* node)
    {
        traverse(node);
    }

    void NodeVisitor::traverse(Node* node)
    {
        if (_traversal_mode == TraversalMode::TRAVERSE_PARENTS) node->ascend(this);
        else if (_traversal_mode == TraversalMode::TRAVERSE_CHILDREN) node->descend(this);

    }
}
