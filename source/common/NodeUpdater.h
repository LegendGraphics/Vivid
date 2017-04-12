
#ifndef COMMON_NODE_UPDATER_H
#define COMMON_NODE_UPDATER_H

namespace te
{
    class Node;
    class NodeUpdater
    {
    public:
        virtual void update(Node* node);
    };

    class FocusCameraUpdater: public NodeUpdater
    {
    public:
        void update(Node* node);
    };
    
    class CullingUpdater: public NodeUpdater
    {
    public:
        void update(Node* node);
    };

    class RenderingUpdater: public NodeUpdater
    {
    public:
        void update(Node* node);
    };
}
#endif // COMMON_NODE_UPDATER_H
