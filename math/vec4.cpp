
#include "math/vec4.h"

Vec4::Vec4()
:_x(0.0),
_y(0.0),
_z(0.0),
_w(0.0)
{
}

Vec4::Vec4(const Vec4& v)
:_x(v._x),
_y(v._y),
_z(v._z),
_w(v._w)
{
}

Vec4::Vec4(float x, float y, float z, float w)
:_x(x),
_y(y),
_z(z),
_w(w)
{}

Vec4::~Vec4(){}

Vec4& Vec4::operator=(const Vec4& v)
{
    this->_x = v._x;
    this->_y = v._y;
    this->_z = v._z;
    this->_w = v._w;
    return *this;
}

Vec2 Vec4to2(const Vec4& vec4)
{
    return Vec2(vec4.x(), vec4.y());
}

Vec4 Vec2to4(const Vec2& vec2)
{
    return Vec4(vec2.x(), vec2.y(), 0, 1);
}