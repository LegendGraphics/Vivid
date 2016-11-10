
#ifndef MATH_VEC3_H
#define MATH_VEC3_H

#include <vector>

class Vec3
{
public:
    Vec3();
    Vec3(const Vec3& v);
    Vec3(float x, float y, float z);
    ~Vec3();

    Vec3& operator=(const Vec3& v);

    inline const Vec3 operator+(const Vec3& v) const { return Vec3(_x + v._x, _y + v._y, _z + v._z); }
    inline Vec3& operator+=(const Vec3& v) { this->_x += v._x; this->_y += v._y; this->_z += v._z; return *this; }
    inline const Vec3 operator-(const Vec3& v) const { return Vec3(_x - v._x, _y - v._y, _z - v._z); }
    inline Vec3& operator-=(const Vec3& v) { this->_x -= v._x; this->_y -= v._y; this->_z -= v._z; return *this; }
    inline const Vec3 operator*(float s) const { return Vec3(_x * s, _y * s, _z * s); }
    inline Vec3& operator*=(float s) { this->_x *= s; this->_y *= s; this->_z *= s; return *this; }
    inline const Vec3 operator/(float s) const { return Vec3(_x / s, _y / s, _z / s); }
    inline Vec3& operator/=(float s) { this->_x /= s; this->_y /= s; this->_z /= s; return *this; }
    
    inline float& x() { return _x; }
    inline float& y() { return _y; }
    inline float& z() { return _z; }

    inline const float& x() const { return _x; }
    inline const float& y() const { return _y; }
    inline const float& z() const { return _z; }

    const Vec3 cross(const Vec3& v);
    const Vec3 normalize();
    float dot(const Vec3& v);
    float length();

private:
    float _x;
    float _y;
    float _z;
};

typedef std::vector<Vec3> Vec3Array;

#endif // MATH_VEC3_H