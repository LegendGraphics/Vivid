#ifndef COMMON_NODE_H
#define COMMON_NODE_H

#include <vector>

#include "base/ref.h"
#include "base/data_types.h"
#include "base/event.h"
#include "base/event_listener.h"
#include "math/vec2.h"
#include "math/transform.h"



class NodeVisitor;
class Renderer;

class Node: public Ref
{
public:
    Node();
    virtual ~Node();

    void setLocalZOrder(int local_z_order);
    inline int getLocalZOrder() { return _local_z_order; }

    void addChild(Node* child, int local_order);
    void addChild(Node* child);
    void removeChild(Node* child);
    inline std::vector<Node*>& getChildren() { return _children; }
    inline Node* getChild(int index) { return _children[index]; }

    void setParent(Node* parent);
    inline Node* getParent() { return _parent; }

    void setPosition(const Vec2& pos);
    void setPosition(float x, float y);
    inline const Vec2& getPosition() const { return _position; }

    void setAnchorPoint(const Vec2& anchor_point);
    void setAnchorPoint(float x, float y);
    inline const Vec2& getAnchorPoint() const { return _anchor_point; }

    void setContentSize(const Size& content_size);
    void setContentSize(float x, float y);
    inline const Size& getContentSize() const { return _content_size; }

    inline const Transform& getTransform() const { return _transform; }
    inline const Vec2& getWorldPosition() const { return _world_position; }

    void setVisible(bool visible);
    inline bool getVisible() { return _visible; }

    virtual void accept(NodeVisitor* node_visitor);

    virtual void draw(Renderer* renderer);

    void traversal(NodeVisitor* node_visitor);

    virtual void update(float delta_time);

    void schedule(const std::string& key);
    void unschedule(const std::string& key);

    void addEventListener(EventType event_type, const EventListener::EventCallback& callback);
    void addEventListener(EventType event_type, LUA_CALLBACK callback);
    void removeEventListener(EventType event_type);

protected:
    void insertChildByZOrder(Node* child);
    void ReorderByZOrder(Node* child);

    void assembleTransform();

protected:
    std::vector<Node*> _children;   // in traversal order which is from max to min by z order
    Node* _parent;
    int _local_z_order;

    Vec2 _position;
    Vec2 _anchor_point;
    Size _content_size;

    Transform _transform;
    Vec2 _world_position;

    bool _visible;
};

#endif // COMMON_NODE_H