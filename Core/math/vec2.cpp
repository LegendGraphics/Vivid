#include <cmath>

#include "math/vec2.h"

Vec2::Vec2()
:_x(0.0),
_y(0.0)
{
}

Vec2::Vec2(const Vec2& v)
:_x(v._x),
_y(v._y)
{
}

Vec2::Vec2(float x, float y)
:_x(x),
_y(y)
{}

Vec2::~Vec2(){}

Vec2& Vec2::operator=(const Vec2& v)
{
    this->_x = v._x;
    this->_y = v._y;
    return *this;
}

const Vec2 Vec2::normalize()
{
    return (*this) / length();
}

float Vec2::dot(const Vec2& v)
{
    return (_x * v._x + _y * v._y);
}

float Vec2::length()
{
    return sqrt(_x * _x + _y * _y);
}