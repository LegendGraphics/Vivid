
#include "common/NodeVisitor.h"

#include <iostream>

#include "common/Node.h"
#include "common/Camera.h"
#include "common/SpaceState.h"
#include "common/Scene.h"
#include "renderer/RenderInterface.h"

#include "common/MeshFilter.h"
#include "common/Mesh.h"

#include "io/Logger.h"
namespace te
{
    NodeVisitor::NodeVisitor()
        :_traversal_mode(TraversalMode::TRAVERSE_NONE),
        _visitor_type(VisitorType::NONE_UPDATE)
    {
    }

    NodeVisitor::NodeVisitor(const TraversalMode& tm, const VisitorType& vt)
        :_traversal_mode(tm),
        _visitor_type(vt)
    {}

    NodeVisitor::NodeVisitor(const NodeVisitor& node_visitor, const CopyOperator& copyop)
        :_traversal_mode(node_visitor._traversal_mode),
        _visitor_type(node_visitor._visitor_type)
    {

    }

    NodeVisitor::~NodeVisitor()
    {}

    void NodeVisitor::apply(NodeTree* node_tree)
    {
        // do nothing
        traverse(node_tree);
    }

    void NodeVisitor::traverse(NodeTree* node_tree)
    {
        if (_traversal_mode == TraversalMode::TRAVERSE_PARENTS) node_tree->ascend(this);
        else if (_traversal_mode == TraversalMode::TRAVERSE_CHILDREN) node_tree->descend(this);

    }

    CullingVisitor::CullingVisitor()
    {
    }

    CullingVisitor::CullingVisitor(const TraversalMode& tm, Camera* camera)
        :NodeVisitor(tm, VisitorType::CULLING_UPDATE),
        _camera(camera)
    {}

    CullingVisitor::CullingVisitor(const CullingVisitor& node_visitor, const CopyOperator& copyop)
        :NodeVisitor(node_visitor, copyop)
    {

    }

    CullingVisitor::~CullingVisitor()
    {}

    void CullingVisitor::apply(NodeTree* node_tree)
    {
        // Now simply frustum culling for every node
        Node* node = node_tree->node().get();
        node->setVisible(!_camera->cull(node));
        traverse(node_tree);
    }

    SpacingVisitor::SpacingVisitor()
    {
    }

    SpacingVisitor::SpacingVisitor(const TraversalMode& tm)
        :NodeVisitor(tm, VisitorType::SPACING_UPDATE)
    {}

    SpacingVisitor::SpacingVisitor(const SpacingVisitor& node_visitor, const CopyOperator& copyop)
        : NodeVisitor(node_visitor, copyop)
    {

    }

    SpacingVisitor::~SpacingVisitor()
    {}

    void SpacingVisitor::apply(NodeTree* node_tree)
    {
        Node* node = node_tree->node().get();
        node->updateComponents();
        traverse(node_tree);
    }

    RenderingVisitor::RenderingVisitor()
    {
        
    }

    RenderingVisitor::RenderingVisitor(const TraversalMode& tm, RenderInterface* renderer, Scene* scene)
        :NodeVisitor(tm, VisitorType::RENDERING_UPDATE),
        _renderer(renderer),
        _scene(scene)
    {}

    RenderingVisitor::RenderingVisitor(const RenderingVisitor& node_visitor, const CopyOperator& copyop)
        : NodeVisitor(node_visitor, copyop)
    {

    }

    RenderingVisitor::~RenderingVisitor()
    {}

    void RenderingVisitor::apply(NodeTree* node_tree)
    {
        // Now simply rendering every node
        Node* node = node_tree->node().get();

        if (MeshFilter* mf = node->getComponent<MeshFilter>())
        {
            Mesh* m = mf->getMesh().get();

            MeshStreamMsg* msg = new MeshStreamMsg;
            msg->setMsgType(StreamMsg::RENDER);
            msg->setHandle(m->getRenderObjectHandle());
            Vector3 pos = node->getComponent<SpaceState>()->getLocalPosition();
            MeshStreamMsg::Data* data = new MeshStreamMsg::Data;
            data->model_mat = Mat4x4(Transform::translate(pos.x, pos.y, pos.z).rawMatrix());
            msg->feedData(data);
            _renderer->_stream.push_back(msg);
        }

        traverse(node_tree);
    }

    RenderResourceVisitor::RenderResourceVisitor()
    {
    }

    RenderResourceVisitor::RenderResourceVisitor(const TraversalMode & tm, RenderInterface * renderer, Scene* scene)
        : RenderingVisitor(tm, renderer, scene)
    {
    }

    RenderResourceVisitor::RenderResourceVisitor(const RenderResourceVisitor & node_visitor, const CopyOperator & copyop)
        : RenderingVisitor(node_visitor, copyop)
    {
    }

    RenderResourceVisitor::~RenderResourceVisitor()
    {
    }


    void RenderResourceVisitor::apply(NodeTree * node_tree)
    {
        Node* node = node_tree->node().get();
        if (MeshFilter* mf = node->getComponent<MeshFilter>())
        {
            Mesh* m = mf->getMesh().get();

            MeshStreamMsg* msg = new MeshStreamMsg;
            msg->setMsgType(StreamMsg::UPDATE);
            msg->setHandle(m->getRenderObjectHandle());
            _renderer->_stream.push_back(msg);
        }

        traverse(node_tree);
    }

}
