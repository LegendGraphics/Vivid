#include "common/transform_component.h"

TransformComponent::TransformComponent()
    :_x(0.0), _y(0.0), _z(0.0),
    _sx(0.0), _sy(0.0), _sz(0.0),
    _rx(0.0), _ry(0.0), _rz(0.0)
{}

TransformComponent::~TransformComponent(){}

void TransformComponent::update(float delta_time)
{

}

void TransformComponent::setX(float x)
{
    _x = x;
}

void TransformComponent::setY(float y)
{
    _y = y;
}

void TransformComponent::setZ(float z)
{
    _z = z;
}

void TransformComponent::setPosition(float x, float y, float z)
{
    _x = x; _y = y; _z = z;
}
