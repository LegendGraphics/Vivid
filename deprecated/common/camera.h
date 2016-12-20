#ifndef COMMON_CAMERA_H
#define COMMON_CAMERA_H

#include "common/node.h"
#include "math/transform.h"


class Camera: public Node
{
public:
    struct ViewBoundary
    {
        float left;
        float right;
        float top;
        float bottom;
    };

public:
    Camera();
    virtual ~Camera();

    void setViewPort(float width, float height);
    void setPosition(float x, float y);
    
    void setViewTransform(const Transform& view_transform);
    const Transform& getViewTransform() const { return _view_transform; }
    
    void setOrthoTransform(const Transform& ortho_transform);
    const Transform& getOrthoTransform() const { return _ortho_transform; }
    
    void updateViewBoundary();
    const ViewBoundary& getViewBoundary() { return _view_bound; }

    const Vec2 convertScreenToWorld(float x, float y);

protected:
    Transform _view_transform;
    Transform _ortho_transform;

    ViewBoundary _view_bound;

};
#endif // COMMON_CAMERA_H