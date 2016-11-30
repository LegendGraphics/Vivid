
#include "common/camera.h"
#include "base/director.h"

Camera::Camera()
{
}

Camera::~Camera(){}

void Camera::setViewTransform(const Transform& view_transform)
{
    _view_transform = view_transform;
}

void Camera::setOrthoTransform(const Transform& ortho_transform)
{
    _ortho_transform = ortho_transform;
}

void Camera::setViewPort(float width, float height)
{
    setContentSize(width, height);
    setOrthoTransform(Transform::ortho(0.0f, width, 0.0f, height));
    updateViewBoundary(); 
}

void Camera::setPosition(float x, float y)
{
    Node::setPosition(x, y);
  //  _world_position = Vec2(x, y);
  //  setViewTransform(Transform::lookAt(Node::getWorldPosition()));
    setViewTransform(Transform::lookAt(Vec2(x, y)));
    updateViewBoundary();
}

void Camera::updateViewBoundary()
{
    _view_bound.left = _position.x();
    _view_bound.right = _position.x() + _content_size.width;
    _view_bound.bottom = _position.y();
    _view_bound.top = _position.y() + _content_size.height;
}

const Vec2 Camera::convertScreenToWorld(float x, float y)
{
    // origin from left-top to left-bottom
    const Size& window_size = Director::getInstance()->getWindowSize();
    float ox = x;
    float oy = window_size.height - y;

    // from screen coordinate to world coordinate
    return Vec2(_position.x() + ox, _position.y() + oy);
}