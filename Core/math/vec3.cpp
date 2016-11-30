#include <cmath>

#include "math/vec3.h"

Vec3::Vec3()
:_x(0.0),
_y(0.0),
_z(0.0)
{
}

Vec3::Vec3(const Vec3& v)
:_x(v._x),
_y(v._y),
_z(v._z)
{
}

Vec3::Vec3(float x, float y, float z)
:_x(x),
_y(y),
_z(z)
{}

Vec3::~Vec3(){}

Vec3& Vec3::operator=(const Vec3& v)
{
    this->_x = v._x;
    this->_y = v._y;
    this->_z = v._z;
    return *this;
}

const Vec3 Vec3::cross(const Vec3& v)
{
    float x = _y * v._z - _z * v._y;
    float y = - (_x * v._z - _z * v._x);
    float z = _x * v._y - _y * v._x;

    return Vec3(x, y, z);
}

const Vec3 Vec3::normalize()
{
    return (*this) / length();
}

float Vec3::dot(const Vec3& v)
{
    return (_x * v._x + _y * v._y + _z * v._z);
}

float Vec3::length()
{
    return sqrt(_x * _x + _y * _y + _z * _z);
}