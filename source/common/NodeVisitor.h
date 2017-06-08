#ifndef COMMON_NODE_VISITOR_H
#define COMMON_NODE_VISITOR_H

#include "base/Refptr.hpp"
#include "base/Ref.h"
#include "common/Clone.h"

namespace te
{

    class Node;
    class Camera;
    class Scene;
    class RenderInterface;

    // consider two things: traversal mode and visitor type
    class NodeVisitor
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
            NONE_UPDATE,
            CULLING_UPDATE,
            SPACING_UPDATE,
            RENDERING_UPDATE
        };

        NodeVisitor();
        NodeVisitor(const TraversalMode& tm, const VisitorType& vt);
        NodeVisitor(const NodeVisitor& node_visitor, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);

        virtual ~NodeVisitor();

        virtual void apply(NodeTree* node_tree);

        void traverse(NodeTree* node_tree);

    protected:
        TraversalMode   _traversal_mode;
        VisitorType     _visitor_type;
    };

    class CullingVisitor : public NodeVisitor
    {
    public:
        CullingVisitor();
        CullingVisitor(const TraversalMode& tm, Camera* camera);
        CullingVisitor(const CullingVisitor& node_visitor, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);

        virtual ~CullingVisitor();

        virtual void apply(NodeTree* node_tree);

    protected:
        Camera*     _camera;
    };

    class BehaviorVisitor : public NodeVisitor
    {
    public:
        BehaviorVisitor();
        BehaviorVisitor(const TraversalMode& tm);
        BehaviorVisitor(const BehaviorVisitor& node_visitor, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);

        virtual ~BehaviorVisitor();

        virtual void apply(NodeTree* node_tree);

    protected:
        Scene*      _scene;
    };

    class RenderWorld;
    class RenderCamera;
    class RenderQueueItem;
    class PipelineResource;

    class RenderVisitor : public NodeVisitor
    {
    public:
        RenderVisitor();
        RenderVisitor(const TraversalMode& tm, RenderInterface* renderer, Scene* scene);
        RenderVisitor(const RenderVisitor& node_visitor, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);

        virtual ~RenderVisitor();

        virtual void apply(NodeTree* node_tree);

    protected:
        RenderInterface*    _renderer;
        Scene*              _scene;

    };

    class RenderResourceVisitor : public RenderVisitor
    {
    public:
        RenderResourceVisitor();
        RenderResourceVisitor(const TraversalMode& tm, RenderInterface* renderer, Scene* scene);
        RenderResourceVisitor(const RenderResourceVisitor& node_visitor, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~RenderResourceVisitor();

        virtual void apply(NodeTree* node_tree);
    };


}

#endif // COMMON_NODE_VISITOR_H