
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

    void NodeVisitor::apply(Node* node)
    {
        //std::cout << node->getName() << std::endl;
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
        node->updateComponents();
        traverse(node);
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

    void RenderingVisitor::apply(Node* node)
    {
        // Now simply rendering every node

        testRenderingPipeline(node, _scene->getActiveCamera()); // for test

        traverse(node);
    }

    RenderWorld* wrapRenderWorld()
    {
        RenderWorld* rw = new RenderWorld;
        return rw;
    }

    RenderCamera* wrapRenderCamera(Camera* camera)
    {
        Transform view = camera->getComponent<CameraState>()->getViewTransform();
        Transform proj = camera->getComponent<CameraState>()->getProjectTransform();
        //Transform view = Transform::lookAt(Vector3(200, 200, 200), Vector3(0, 0, 0), Vector3(0, 1, 0));
        //Transform proj = Transform::ortho(-100, 100, -100, 100, -100, -1000);
        //cLog << view.rawMatrix() * Vector4(-50, -50, -50, 1);
        //cLog << proj.rawMatrix();
        //cLog << proj.rawMatrix() * (view.rawMatrix() * Vector4(-50, -50, -50, 1));
        //cLog << proj.rawMatrix() * view.rawMatrix() * Vector4(-50, -50, -50, 1);
        RenderCamera* rc = new RenderCamera(CameraData::ORTHOGRAPHIC, -10, -1000, 
            proj.rawMatrix(), view.rawMatrix());
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
            Mesh* m = mf->getMesh().get();
            RenderMeshObject* rmo = new RenderMeshObject;
            rmo->setNumIndices(m->getTriangles().size());
            rmo->setVertexDeclaration(
                ResourceMapper::getInstance()
                ->get<RenderResourceManager>()
                ->getGPUResource(m->getVertexDeclaration()).get());
            

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

    void RenderingVisitor::testRenderingPipeline(Node* node, Camera* camera)
    {
        RenderMsg msg;
        msg.rwm.camera = wrapRenderCamera(camera);
        msg.rwm.world = wrapRenderWorld();
        msg.rwm.rQueue = wrapRenderQueueItem(node, msg.rwm.numQueue);
        msg.rwm.pipeline = wrapPipelineResource();

        _renderer->renderWorld(&msg);
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


    void RenderResourceVisitor::apply(Node * node)
    {
        if (MeshFilter* mf = node->getComponent<MeshFilter>())
        {
            Mesh* m = mf->getMesh().get();
            String m_res_id = m->getResourceId();
            RenderResourceManager* rr_manager =
                ResourceMapper::getInstance()->get<RenderResourceManager>();

            // index stream
            String i_buffer_id = gpu_resource::appendTypeStr(gpu_resource::INDEX_STREAM, m_res_id);
            ResourceHandle i_buffer = rr_manager->create(i_buffer_id);
            m->setIndexBuffer(i_buffer);

            // vertex stream
            String v_buffer_id = gpu_resource::appendTypeStr(gpu_resource::VERTEX_STREAM, m_res_id);
            ResourceHandle v_buffer = rr_manager->create(v_buffer_id);
            m->setVertexBuffer(v_buffer);

            // vertex declaration stream
            String vao_id = gpu_resource::appendTypeStr(gpu_resource::VERTEX_DECLARATION,
                vertex_layout::getTypeStr(vertex_layout::PNTB) + ";"
                + i_buffer_id + ";"
                + v_buffer_id + ";");
            ResourceHandle vao = rr_manager->create(vao_id);
            m->setVertexDeclaration(vao);

            rr_manager->immediateCreate();
        }

    }

}
