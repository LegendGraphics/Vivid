//#ifndef COMMON_SCENE_H
//#define COMMON_SCENE_H
//
//#include "common/Resource.h"
//
//namespace te
//{
//    // xml file
//    class SceneGraphRes : public Resource
//    {
//    public:
//        void release();
//        bool load(const char *data, int size);
//
//        Node* getRootNode() { return _root_node; }
//
//    private:
//        void parseBaseAttributes(XMLNode& xmlNode, Node& nodeTpl);
//        void parseNode(XMLNode& xmlNode, Node* parentTpl);
//
//    private:
//        Node*   _root_node;
//    };
//}
//
//#endif // COMMON_SCENE_H

#ifndef COMMON_SCENE_H
#define COMMON_SCENE_H

#include "common/Node.h"

namespace te
{
    class SceneTree : public Node
    {
    public:
        SceneTree();
        virtual ~SceneTree();

    private:
        void initComponents();
    };

    class Camera;

    class Scene: public Ref
    {
    public:
        Scene();
        Scene(const Scene& scene, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~Scene();

        // init from SceneRes?

        NodeTree* getSceneRoot() const { return _scene_root; }
        Camera* getActiveCamera() const { return _camera; }
        
        void setSceneRoot(NodeTree* tree);
        void setActiveCamera(Camera* camera);

    protected:
        NodeTree*       _scene_root;
        Camera*         _camera;
    };

}

#endif // COMMON_SCENE_H