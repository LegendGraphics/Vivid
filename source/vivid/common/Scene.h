//#ifndef COMMON_SCENE_H
//#define COMMON_SCENE_H
//
//#include "vivid/common/Resource.h"
//
//namespace vivid
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

#include "vivid/base/Platform.h"
#include "vivid/base/Ref.h"
#include "vivid/common/Clone.h"

namespace vivid
{
    class NodeTree;
    class Camera;

    // Scene can be constructed from resource, just like the node
    class TE_DLL_EXPORT Scene: public Ref, public Cloneable
    {
    public:
        Scene();
        Scene(const Scene& scene, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~Scene();

        ENABLE_CLONE(Scene);

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