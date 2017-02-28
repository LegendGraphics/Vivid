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

#include "common/Object.h"

namespace te
{
    class Node;
    class Camera;

    class Scene: public Object
    {
    public:
        Scene();
        virtual ~Scene();

        Node* getSceneNode() const { return _root; }

    protected:
        Node*       _root;
        Camera*     _camera;
    };
}

#endif // COMMON_SCENE_H