#include "vivid/math/Vector2.h"

#include <cmath>


namespace te
{
    Vector2::Vector2()
        :x(0.0),
        y(0.0)
    {
    }

    Vector2::Vector2(const Vector2& v)
        :x(v.x),
        y(v.y)
    {
    }

    Vector2::Vector2(float x, float y)
        :x(x),
        y(y)
    {}

    Vector2::~Vector2(){}

    Vector2& Vector2::operator=(const Vector2& v)
    {
        this->x = v.x;
        this->y = v.y;
        return *this;
    }

    void Vector2::set(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    void Vector2::normalize()
    {
        (*this) /= length();
    }

    Vector2 Vector2::normalized() const
    {
        return (*this) / length();
    }

    float Vector2::length() const
    {
        return sqrt(x * x + y * y);
    }

    float Vector2::squaredLength() const
    {
        return (x * x + y * y);
    }

    float Vector2::dot(const Vector2& v1, const Vector2& v2)
    {
        return (v1.x * v2.x + v1.y * v2.y);
    }

    float Vector2::angle(const Vector2& from_v, const Vector2& to_v)
    {
        float cos_angle = dot(from_v, to_v) / (from_v.length() * to_v.length());
        return acos(cos_angle);
    }

    Vector3 Vector2to3(const Vector2& vec2)
    {
        return Vector3(vec2.x, vec2.y, 0);
    }

    Vector2 Vector3to2(const Vector3& vec3)
    {
        return Vector2(vec3.x, vec3.y);
    }
}

