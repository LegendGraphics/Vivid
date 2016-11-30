
#ifndef MATH_VEC4_H
#define MATH_VEC4_H

#include <vector>

#include "math/vec2.h"

class Vec4
{
public:
    Vec4();
    Vec4(const Vec4& v);
    Vec4(float x, float y, float z, float w);
    ~Vec4();

    Vec4& operator=(const Vec4& v);

    inline const Vec4 operator+(const Vec4& v) const { return Vec4(_x + v._x, _y + v._y, _z + v._z, _w + v._w); }
    inline Vec4& operator+=(const Vec4& v) { this->_x += v._x; this->_y += v._y; this->_z += v._z; this->_w += v._w; return *this; }
    inline const Vec4 operator-(const Vec4& v) const { return Vec4(_x - v._x, _y - v._y, _z - v._z, _w - v._w); }
    inline Vec4& operator-=(const Vec4& v) { this->_x -= v._x; this->_y -= v._y; this->_z -= v._z; this->_w -= v._w; return *this; }
    inline const Vec4 operator*(float s) const { return Vec4(_x * s, _y * s, _z * s, _w * s); }
    inline Vec4& operator*=(float s) { this->_x *= s; this->_y *= s; this->_z *= s; this->_w *= s; return *this; }
    inline const Vec4 operator/(float s) const { return Vec4(_x / s, _y / s, _z / s, _w / s); }
    inline Vec4& operator/=(float s) { this->_x /= s; this->_y /= s; this->_z /= s; this->_w /= s; return *this; }

    inline float& x() { return _x; }
    inline float& y() { return _y; }
    inline float& z() { return _z; }
    inline float& w() { return _w; }

    inline const float& x() const { return _x; }
    inline const float& y() const { return _y; }
    inline const float& z() const { return _z; }
    inline const float& w() const { return _w; }

private:
    float _x;
    float _y;
    float _z;
    float _w;
};

typedef std::vector<Vec4> Vec4Array;

Vec2 Vec4to2(const Vec4& vec4);
Vec4 Vec2to4(const Vec2& vec2);

#endif // MATH_VEC4_H