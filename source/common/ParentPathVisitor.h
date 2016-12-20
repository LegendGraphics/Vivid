#ifndef COMMON_PARENT_PATH_VISITOR_H
#define COMMON_PARENT_PATH_VISITOR_H

#include "common/NodeVisitor.h"
#include "common/Node.h"

namespace te
{
    class ParentPathVisitor: public NodeVisitor
    {
    public:
        ParentPathVisitor();
        virtual ~ParentPathVisitor();

        virtual void apply(Node* node);

        void pushNodeToPath(Node* node);

        inline NodePath* getParentPath() { return _parent_path.get(); }

    protected:
        RefPtr<NodePath>    _parent_path;
    };
}

#endif // COMMON_PARENT_PATH_VISITOR_H