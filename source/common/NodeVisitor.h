#ifndef COMMON_NODE_VISITOR_H
#define COMMON_NODE_VISITOR_H

#include "base/Refptr.hpp"
#include "base/Ref.h"
#include "common/Object.h"

namespace te
{

    class Node;

    // consider two things: traversal mode and visitor type
    class NodeVisitor: public Object
    {
    public:
        enum class TraversalMode
        {
            TRAVERSE_NONE,
            TRAVERSE_PARENTS,
            TRAVERSE_CHILDREN
        };

        enum class VisitorType
        {
            VISITOR_NODE,
            // update, cull
        };

        NodeVisitor();
        NodeVisitor(const TraversalMode& tm, const VisitorType& vt);
        NodeVisitor(const NodeVisitor& node_visitor, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);

        virtual ~NodeVisitor();

        OBJECT_META_FUNCTION(NodeVisitor);

        virtual void apply(Node* node);

        void traverse(Node* node);

    protected:
        TraversalMode   _traversal_mode;
        VisitorType     _visitor_type;
    };

}

#endif // COMMON_NODE_VISITOR_H