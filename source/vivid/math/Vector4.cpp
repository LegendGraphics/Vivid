
#include "vivid/math/Vector4.h"
#include <cmath>

namespace te
{
    Vector4::Vector4()
        :x(0.0),
        y(0.0),
        z(0.0),
        w(0.0)
    {
    }

    Vector4::Vector4(const Vector4& v)
        :x(v.x),
        y(v.y),
        z(v.z),
        w(v.w)
    {
    }

    Vector4::Vector4(float x, float y, float z, float w)
        :x(x),
        y(y),
        z(z),
        w(w)
    {}

    Vector4::~Vector4(){}

    Vector4& Vector4::operator=(const Vector4& v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        this->w = v.w;
        return *this;
    }

    void Vector4::set(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void Vector4::normalize()
    {
        (*this) /= length();
    }

    Vector4 Vector4::normalized() const
    {
        return (*this) / length();
    }

    float Vector4::length() const
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    float Vector4::squaredLength() const
    {
        return (x * x + y * y + z * z + w * w);
    }

    float Vector4::dot(const Vector4& v1, const Vector4& v2)
    {
        return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
    }

    Vector2 Vector4to2(const Vector4& vec4)
    {
        return Vector2(vec4.x, vec4.y);
    }

    Vector3 Vector4to3(const Vector4& vec4)
    {
        return Vector3(vec4.x, vec4.y, vec4.z);
    }

    Vector4 Vector2to4(const Vector2& vec2)
    {
        return Vector4(vec2.x, vec2.y, 0, 0);
    }

    Vector4 Vector3to4(const Vector3& vec3)
    {
        return Vector4(vec3.x, vec3.y, vec3.z, 1);
    }
}

