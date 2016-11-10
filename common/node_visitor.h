#ifndef COMMON_NODE_VISITOR_H
#define COMMON_NODE_VISITOR_H

#include "base/refptr.hpp"
#include "base/ref.h"
#include "renderer/renderer.h"

class Node;
class Scene;
class Camera;
class Sprite;
class UIWidget;

class NodeVisitor: public Ref
{
public:
    NodeVisitor();
    virtual ~NodeVisitor();

    void attachRenderer(Renderer* renderer);

    void apply(Node* node);
    void apply(Scene* scene);
    void apply(Camera* camera);
    void apply(Sprite* sprite);
    void apply(UIWidget* ui_widget);

protected:
    RefPtr<Renderer> _renderer;
};

#endif // COMMON_NODE_VISITOR_H