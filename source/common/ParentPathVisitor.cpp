#include "common/ParentPathVisitor.h"

namespace te
{
    ParentPathVisitor::ParentPathVisitor()
        /*:_visitor_type(VisitorType::VISITOR_NODE),
        _traversal_mode(TraversalMode::TRAVERSE_PARENTS)*/
    {

    }

    ParentPathVisitor::~ParentPathVisitor(){}

    void ParentPathVisitor::apply(Node* node)
    {
        pushNodeToPath(node);
        traverse(node);
    }

    void ParentPathVisitor::pushNodeToPath(Node* node)
    {
        //_parent_path->push_back(node);
    }
}