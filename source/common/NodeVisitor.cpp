
#include "common/NodeVisitor.h"
#include "common/Node.h"
#include "common/Camera.h"
#include "common/SpaceState.h"
#include "renderer/RenderInterface.h"

// These header files will be moved in the future
#include "renderer/RenderWorld.h"
#include "renderer/Resource/RenderResourceGenerator.h"
#include "renderer/Runtime/RenderCamera.h"
#include "renderer/Resource/RenderMeshObject.h"
#include "renderer/Resource/PipelineResource.h"
#include "renderer/Resource/VertexLayout.h"

#include "common/MeshFilter.h"
#include "common/Mesh.h"


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

    void NodeVisitor::apply(Node* node)
    {
        std::cout << node->getName() << std::endl;
        traverse(node);
    }

    void NodeVisitor::traverse(Node* node)
    {
        if (_traversal_mode == TraversalMode::TRAVERSE_PARENTS) node->ascend(this);
        else if (_traversal_mode == TraversalMode::TRAVERSE_CHILDREN) node->descend(this);

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

    void CullingVisitor::apply(Node* node)
    {
        // Now simply frustum culling for every node
        node->setVisible(!_camera->cull(node));
        traverse(node);
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

    void SpacingVisitor::apply(Node* node)
    {
        // Now simply update space status for every node
        if (node->hasComponent<SpaceState>()) node->getComponent<SpaceState>()->update();
        traverse(node);
    }

    RenderingVisitor::RenderingVisitor()
    {
        
    }

    RenderingVisitor::RenderingVisitor(const TraversalMode& tm, RenderInterface* renderer)
        :NodeVisitor(tm, VisitorType::RENDERING_UPDATE),
        _renderer(renderer)
    {}

    RenderingVisitor::RenderingVisitor(const RenderingVisitor& node_visitor, const CopyOperator& copyop)
        : NodeVisitor(node_visitor, copyop)
    {

    }

    RenderingVisitor::~RenderingVisitor()
    {}

    void RenderingVisitor::apply(Node* node)
    {
        // Now simply rendering every node

        testRenderingPipeline(node); // for test

        traverse(node);
    }

    RenderWorld* wrapRenderWorld()
    {
        RenderWorld* rw = new RenderWorld;
        return rw;
    }

    RenderCamera* wrapRenderCamera()
    {
        RenderCamera* rc = new RenderCamera;
        rc->getViewPort()[0] = 0;
        rc->getViewPort()[1] = 0;
        rc->getViewPort()[2] = 800;
        rc->getViewPort()[3] = 600;
        return rc;
    }

    RenderQueueItem* wrapRenderQueueItem(Node* node, uint32& num)
    {
        RenderQueueItem* rqi = new RenderQueueItem[1];
        if (MeshFilter* mf = node->getComponent<MeshFilter>())
        {
            // generate RenderMeshObject
            Mesh* m = mf->getMesh();
            RenderMeshObject* rmo = new RenderMeshObject;
            rmo->setNumIndices(m->getTriangles().size());
            rmo->setVertexDeclaration(&m->getVertexDeclaration());

            // Put it into RenderQueueItem
            rqi->node = rmo;
            rqi->node->type = RenderMeshObject::TYPE;
            rqi->sortKey = 0;

            num = 1;
            return rqi;
        }

        num = 0;
        return nullptr;
    }

    PipelineResource* wrapPipelineResource()
    {
        PipelineResource* pr = new PipelineResource;
        pr->load("forward.pipeline.xml");
        return pr;
    }

    void RenderingVisitor::testRenderingPipeline(Node* node)
    {
        RenderMsg msg;
        msg.rwm.camera = wrapRenderCamera();
        msg.rwm.world = wrapRenderWorld();
        msg.rwm.rQueue = wrapRenderQueueItem(node, msg.rwm.numQueue);
        msg.rwm.pipeline = wrapPipelineResource();

        _renderer->renderWorld(&msg);
    }

    RenderResourceVisitor::RenderResourceVisitor()
    {
    }

    RenderResourceVisitor::RenderResourceVisitor(const TraversalMode & tm, RenderInterface * renderer)
        : RenderingVisitor(tm, renderer)
    {
    }

    RenderResourceVisitor::RenderResourceVisitor(const RenderResourceVisitor & node_visitor, const CopyOperator & copyop)
        : RenderingVisitor(node_visitor, copyop)
    {
    }

    RenderResourceVisitor::~RenderResourceVisitor()
    {
    }


    void RenderResourceVisitor::apply(Node * node)
    {
        RenderMsg msg;
        msg.rrm.generator = new RenderResourceGenerator;
        msg.rrm.numQueue = 0;
        if (MeshFilter* mf = node->getComponent<MeshFilter>())
        {
            // generate RenderMeshObject
            Mesh* m = mf->getMesh();
            msg.rrm.numQueue = 3;
            msg.rrm.rQueue = new ResourceStreamItem[3];

            // index stream
            msg.rrm.rQueue[0].resType = RenderResource::INDEX_STREAM;
            vertex_layout::IndexStream* is = new vertex_layout::IndexStream;
            is->res = &m->getIndexBuffer();
            is->size = 4 * m->getTriangles().size();
            is->raw_data = &m->getTriangles()[0];
            msg.rrm.rQueue[0].stream = is;

            // vertex stream
            msg.rrm.rQueue[1].resType = RenderResource::VERTEX_STREAM;
            vertex_layout::VertexStream* vs = new vertex_layout::VertexStream;
            vs->res = &m->getVertexBuffers()[0];
            vs->size = 4 * 12 * m->getVertices().size(); // 12 float for each vertex(PNTB)
            vs->stride = 12;
            vs->raw_data = &m->getVertices()[0]; // assume memory in std::vector<Vertex_PNTB> is tight packed
            msg.rrm.rQueue[1].stream = vs;

            // vertex declaration stream
            msg.rrm.rQueue[2].resType = RenderResource::VERTEX_DECLARATION;
            vertex_layout::VertexDeclarationStream* vds = new vertex_layout::VertexDeclarationStream;
            vds->res = &m->getVertexDeclaration();
            vds->index_buffer = &m->getIndexBuffer();
            vds->layout_type = vertex_layout::PNTB;
            const VertexLayout& vl =
                _renderer->getVertexDeclarationDefinition()->getLayout(vds->layout_type);
            vds->vertex_buffers.clear();
            for (const VertexLayoutAttrib& attr : vl)
            {
                vds->vertex_buffers.push_back(&m->getVertexBuffers()[attr.vbSlot]);
            }
            msg.rrm.rQueue[2].stream = vds;
            _renderer->generateResource(&msg);
        }

    }

}
